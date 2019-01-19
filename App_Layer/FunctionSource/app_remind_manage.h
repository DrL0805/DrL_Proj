#ifndef APP_REMIND_MANAGE_H
#define APP_REMIND_MANAGE_H

#include "ble_task.h"
#include "BLE_Stack.h"  //BLE stack
#include "mid_rtc.h"

#define APP_REMIND_RTT_DEBUG	3
#if (1 == APP_REMIND_RTT_DEBUG)	// ����ȼ�
#define APP_REMIND_RTT_LOG(...)
#define APP_REMIND_RTT_WARN(...)
#define APP_REMIND_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == APP_REMIND_RTT_DEBUG)	// ����ȼ�
#define APP_REMIND_RTT_LOG(...)
#define APP_REMIND_RTT_WARN		RTT_DEBUG_WARN
#define APP_REMIND_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == APP_REMIND_RTT_DEBUG)	// ���Եȼ�
#define APP_REMIND_RTT_LOG		RTT_DEBUG_LOG
#define APP_REMIND_RTT_WARN		RTT_DEBUG_WARN
#define APP_REMIND_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define APP_REMIND_RTT_LOG(...)
#define APP_REMIND_RTT_WARN(...)
#define APP_REMIND_RTT_ERR(...)
#endif

#define 	APP_REMIND_MSG_MAX_LENGHT 			214	//ÿ����Ϣ����󳤶�
#define 	APP_REMIND_MSG_VALID_MAX_LENGHT  	192//��Ϣ��Ч���ݲ��ֵ���󳤶�

#define 	APP_REMIND_NANE_MAX_LENGHT 			30		// ������󳤶�
#define 	APP_REMIND_PHONENUM_MAX_LENGHT 		20		// �绰������󳤶�

#define 	APP_REMIND_ASCRIPTION_MAX_LENGHT 	10		// ������
#define 	APP_REMIND_DATAIL_MAX_LENGHT 		50		// ��Ϣ��������
#define 	APP_REMIND_CONTENT_MAX_LENGHT 		62		// �������ݳ���

//�ɱ���������Ϣ���ݣ�
#define MSG_STORE_NUM        5   //5��

typedef enum 
{
	FLOW_START 			= 0x00,
	FLOW_PROCESS 		= 0x01,
	FLOW_END			= 0xFF,
}remind_flow_state;

typedef enum
{
	PHONE_FAMILIAR	= 0,	//������ϵ��
	PHONE_UNFAMILIAR,
}remind_phone_relation_type;

typedef enum
{
	QQ_MESAGE 		= 0,
	WECHAT_MESAGE   = 1,	//΢��
	PHONE_CALL_IN 	= 10,	// ����
	PHONE_MESSAGE   = 11,	// ����
	MISS_PHONE_CALL = 12,	// δ������
	FAMILIAR_PHONE_CALL = 16,	// ��ϵ������
    TIM_MESAGE = 17,		// TIM
    INVALID_MESAGE = 0Xff,  //��Ч����Ϣ����
}detail_remind_type;

//��Ϣ���� 62 * 2 
typedef union
{
	uint16_t msg[APP_REMIND_CONTENT_MAX_LENGHT];
	struct 
	{		
		uint16_t 	ascription[APP_REMIND_ASCRIPTION_MAX_LENGHT];		// �����أ��磺����,�㶫
		uint16_t  	ascriptionlen;										// 
		uint16_t 	detail[APP_REMIND_DATAIL_MAX_LENGHT]; // ��Ϣ�������ݣ��磺������:[4��]������:����˵��
																		 //�磺����绰
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
		uint16_t 		totallen;	// δ�õ�
		
		uint16_t 		name[APP_REMIND_NANE_MAX_LENGHT]; 				// ��Ϣ�������ƣ��磺΢�ţ�QQ��
																		// ��Ϊ��ϵ�˵绰����Ϊ��ϵ���������磺С��
		uint16_t 		namelen;
		
		uint16_t 		phonenumber[APP_REMIND_PHONENUM_MAX_LENGHT];	// �绰���룬�磺13528722324
		uint16_t 		phonenumberlen;									// �绰���볤��
		msg_content_t 	content;
	}remindMsg;
}app_remind_msg_t;

// Ӧ����Ϣ
typedef struct
{
	uint16_t 		namelen;
	uint16_t 		name[APP_REMIND_NANE_MAX_LENGHT]; 				// ��Ϣ�������ƣ��磺΢�ţ�QQ��
	
	uint16_t 		detaillen;	
	uint16_t 		detail[APP_REMIND_DATAIL_MAX_LENGHT]; 				// ��Ϣ�������ݣ��磺������:[4��]������:����˵��
}AppMsgDetail_t;

// �ֻ�����
typedef struct
{
	uint16_t 		namelen;										// 
	uint16_t 		name[APP_REMIND_NANE_MAX_LENGHT]; 				// ��ϵ���������ߵ绰���룬�磺�������+8613480172647

	uint16_t 		detaillen;	
	uint16_t 		detail[APP_REMIND_DATAIL_MAX_LENGHT]; 				// ��Ϣ�������ݣ��磺������:[4��]������:����˵��
}PhoneMsgDetail_t;

// �ֻ�����
typedef struct
{
	uint16_t 		namelen;										
	uint16_t 		name[APP_REMIND_NANE_MAX_LENGHT]; 				// ��ϵ���������磺С��

	uint16_t 		detaillen;	
	uint16_t 		detail[APP_REMIND_DATAIL_MAX_LENGHT]; 				// ��Ϣ���ݣ��磺����绰
}PhoneCallDetail_t;

// �ֻ�δ������
typedef struct
{
	uint16_t 		namelen;										
	uint16_t 		name[APP_REMIND_NANE_MAX_LENGHT]; 				// ��ϵ���������磺С��

	uint16_t 		detaillen;	
	uint16_t 		detail[APP_REMIND_DATAIL_MAX_LENGHT]; 				// ��Ϣ���ݣ��磺����绰
}PhoneMissDetail_t;

typedef struct
{
	uint32_t 	RemindType;		// ��Ϣ�������ͣ����š����硢΢�š�QQ��
	rtc_time_s	RTC;
    uint16_t    u16MsgID;
	union
	{
		AppMsgDetail_t		AppMsg;		// Ӧ����Ϣ����
		PhoneMsgDetail_t	PhoneMsg;	// �ֻ�����
		PhoneCallDetail_t	PhoneCall;	// ��������
		PhoneMissDetail_t	PhoneMiss;	// δ������
	}Detail;
}RemindMsg_t;

typedef struct
{
	uint32_t 		RemindCnt;		// �Ѵ���Ϣ����
	uint32_t		FirstPos;		// ��һ���洢λ��
	RemindMsg_t		RemindMsg[MSG_STORE_NUM];
}RemindStore_t;		// ��Ϣ���Ѵ洢����ʱ����ram���ڵ��ԣ�����ȷ�����ٴ���flash

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
// ��������:  ȡ��u16MsgIdָ������Ϣ
// ��������� u16MsgId��ϢID 
// ���ز�����	��
//**********************************************************************
extern void App_RemindManage_Cancel(uint16 u16MsgId);

//��ȡȡ����Ϣ��ID
extern void App_RemindManage_GetCancelMsgId(uint16 *pu16MsgId);
extern void App_RemindManage_DeleteMsg(uint16 u16MsgId);

//**********************************************************************
// ��������: �ֱ�APPɾ��������Ϣ
// ���������u16MsgId��ϢID 
// ���ز�����	
//**********************************************************************
extern void App_RemindManage_DeleteAllMsg(void);

#if((ANCS_VER_TYPE  == ANCS_VER_2) && (ANCS_DETIL_TYPE != ANCS_NONE))
//**********************************************************************
// ��������: ����ancs��Ϣ
// ���������
// ���ز�����	
//**********************************************************************
extern void App_RemindManage_ParseAncs(ancs_msg_info_t *info, uint8_t *pu8Msg,uint8_t u8MsgLen);
#endif

#endif

