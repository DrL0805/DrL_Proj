#ifndef APP_REMIND_MANAGE_H
#define APP_REMIND_MANAGE_H

#include "ble_task.h"
#include "BLE_Stack.h"  //BLE stack
#include "mid_rtc.h"

#define APP_REMIND_RTT_DEBUG	3
#if (1 == APP_REMIND_RTT_DEBUG)	// 错误等级
#define APP_REMIND_RTT_LOG(...)
#define APP_REMIND_RTT_WARN(...)
#define APP_REMIND_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == APP_REMIND_RTT_DEBUG)	// 警告等级
#define APP_REMIND_RTT_LOG(...)
#define APP_REMIND_RTT_WARN		RTT_DEBUG_WARN
#define APP_REMIND_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == APP_REMIND_RTT_DEBUG)	// 调试等级
#define APP_REMIND_RTT_LOG		RTT_DEBUG_LOG
#define APP_REMIND_RTT_WARN		RTT_DEBUG_WARN
#define APP_REMIND_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define APP_REMIND_RTT_LOG(...)
#define APP_REMIND_RTT_WARN(...)
#define APP_REMIND_RTT_ERR(...)
#endif

#define 	APP_REMIND_MSG_MAX_LENGHT 			214	//每条信息的最大长度
#define 	APP_REMIND_MSG_VALID_MAX_LENGHT  	192//信息有效内容部分的最大长度

#define 	APP_REMIND_NANE_MAX_LENGHT 			30		// 名字最大长度
#define 	APP_REMIND_PHONENUM_MAX_LENGHT 		20		// 电话号码最大长度

#define 	APP_REMIND_ASCRIPTION_MAX_LENGHT 	10		// 归属地
#define 	APP_REMIND_DATAIL_MAX_LENGHT 		50		// 消息具体内容
#define 	APP_REMIND_CONTENT_MAX_LENGHT 		62		// 提醒内容长度

//可保存的最大消息数据，
#define MSG_STORE_NUM        5   //5条

typedef enum 
{
	FLOW_START 			= 0x00,
	FLOW_PROCESS 		= 0x01,
	FLOW_END			= 0xFF,
}remind_flow_state;

typedef enum
{
	PHONE_FAMILIAR	= 0,	//常用联系人
	PHONE_UNFAMILIAR,
}remind_phone_relation_type;

typedef enum
{
	QQ_MESAGE 		= 0,
	WECHAT_MESAGE   = 1,	//微信
	PHONE_CALL_IN 	= 10,	// 来电
	PHONE_MESSAGE   = 11,	// 短信
	MISS_PHONE_CALL = 12,	// 未接来电
	FAMILIAR_PHONE_CALL = 16,	// 联系人来电
    TIM_MESAGE = 17,		// TIM
    INVALID_MESAGE = 0Xff,  //无效的消息类型
}detail_remind_type;

//信息内容 62 * 2 
typedef union
{
	uint16_t msg[APP_REMIND_CONTENT_MAX_LENGHT];
	struct 
	{		
		uint16_t 	ascription[APP_REMIND_ASCRIPTION_MAX_LENGHT];		// 归属地，如：深圳,广东
		uint16_t  	ascriptionlen;										// 
		uint16_t 	detail[APP_REMIND_DATAIL_MAX_LENGHT]; // 消息具体内容，如：张四龙:[4条]张四龙:我是说我
																		 //如：呼入电话
		uint16_t 	detaillen;
	}u;
}msg_content_t;


//214 = 4 + 2 + [(20  + 1) * 2] + [(20 + 1 ) *2] + (62 * 2)
typedef union 
{	
	uint8_t 		data[APP_REMIND_MSG_MAX_LENGHT];
	struct 
	{
		uint32_t		utc;
		uint16_t 		totallen;	// 未用到
		
		uint16_t 		name[APP_REMIND_NANE_MAX_LENGHT]; 				// 消息类型名称，如：微信，QQ等
																		// 若为联系人电话，则为联系人姓名，如：小明
		uint16_t 		namelen;
		
		uint16_t 		phonenumber[APP_REMIND_PHONENUM_MAX_LENGHT];	// 电话号码，如：13528722324
		uint16_t 		phonenumberlen;									// 电话号码长度
		msg_content_t 	content;
	}remindMsg;
}app_remind_msg_t;

// 应用消息
typedef struct
{
	uint16_t 		namelen;
	uint16_t 		name[APP_REMIND_NANE_MAX_LENGHT]; 				// 消息类型名称，如：微信，QQ等
	
	uint16_t 		detaillen;	
	uint16_t 		detail[APP_REMIND_DATAIL_MAX_LENGHT]; 				// 消息具体内容，如：张四龙:[4条]张四龙:我是说我
}AppMsgDetail_t;

// 手机短信
typedef struct
{
	uint16_t 		namelen;										// 
	uint16_t 		name[APP_REMIND_NANE_MAX_LENGHT]; 				// 联系人姓名或者电话号码，如：杨锐或者+8613480172647

	uint16_t 		detaillen;	
	uint16_t 		detail[APP_REMIND_DATAIL_MAX_LENGHT]; 				// 消息具体内容，如：张四龙:[4条]张四龙:我是说我
}PhoneMsgDetail_t;

// 手机来电
typedef struct
{
	uint16_t 		namelen;										
	uint16_t 		name[APP_REMIND_NANE_MAX_LENGHT]; 				// 联系人姓名，如：小明

	uint16_t 		detaillen;	
	uint16_t 		detail[APP_REMIND_DATAIL_MAX_LENGHT]; 				// 消息内容，如：呼入电话
}PhoneCallDetail_t;

// 手机未接来电
typedef struct
{
	uint16_t 		namelen;										
	uint16_t 		name[APP_REMIND_NANE_MAX_LENGHT]; 				// 联系人姓名，如：小明

	uint16_t 		detaillen;	
	uint16_t 		detail[APP_REMIND_DATAIL_MAX_LENGHT]; 				// 消息内容，如：呼入电话
}PhoneMissDetail_t;

typedef struct
{
	uint32_t 	RemindType;		// 消息提醒类型，短信、来电、微信、QQ等
	rtc_time_s	RTC;
    uint16_t    u16MsgID;
	union
	{
		AppMsgDetail_t		AppMsg;		// 应用消息提醒
		PhoneMsgDetail_t	PhoneMsg;	// 手机短信
		PhoneCallDetail_t	PhoneCall;	// 来电提醒
		PhoneMissDetail_t	PhoneMiss;	// 未接来电
	}Detail;
}RemindMsg_t;

typedef struct
{
	uint32_t 		RemindCnt;		// 已存消息计数
	uint32_t		FirstPos;		// 第一个存储位置
	RemindMsg_t		RemindMsg[MSG_STORE_NUM];
}RemindStore_t;		// 消息提醒存储，暂时放在ram用于调试，后续确定后再存入flash

uint16_t App_RemindManag_StoreGet(uint8_t Serial, RemindMsg_t* tRemindMsg);
void App_RemindManage_Init(void);
void App_RemindManage_MissRemindSumRead(uint32_t msgClassify,uint8_t *listSumNum);
void App_RemindManage_MissRemindRead(app_remind_msg_t *dailyMissRemindMsg,uint32_t msgClassify,uint8_t listNum);
void App_RemindManage_MissRemindDelete(uint32_t msgClassify,uint8_t listnum);
void App_RemindManage_Process(protocal_msg_t protocal,uint8 phoneSystem);
void App_RemindManage_DetailRemindRead(RemindStore_t* tRemindStore);
void App_RemindManage_CurrDetailRead(RemindMsg_t* ftRemindMsg);
void App_RemindManage_CurrCallRead(RemindMsg_t* ftRemindMsg);
void App_RemindManage_Process_New(protocal_msg_t protocal,uint8 phoneSystem);

//**********************************************************************
// 函数功能:  取消u16MsgId指定的消息
// 输入参数： u16MsgId消息ID 
// 返回参数：	无
//**********************************************************************
extern void App_RemindManage_Cancel(uint16 u16MsgId);

//获取取消消息的ID
extern void App_RemindManage_GetCancelMsgId(uint16 *pu16MsgId);
extern void App_RemindManage_DeleteMsg(uint16 u16MsgId);

//**********************************************************************
// 函数功能: 手表APP删除所有消息
// 输入参数：u16MsgId消息ID 
// 返回参数：	
//**********************************************************************
extern void App_RemindManage_DeleteAllMsg(void);

#if((ANCS_VER_TYPE  == ANCS_VER_2) && (ANCS_DETIL_TYPE != ANCS_NONE))
//**********************************************************************
// 函数功能: 处理ancs消息
// 输入参数：
// 返回参数：	
//**********************************************************************
extern void App_RemindManage_ParseAncs(ancs_msg_info_t *info, uint8_t *pu8Msg,uint8_t u8MsgLen);
#endif

#endif

