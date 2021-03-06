#ifndef         APP_PROTOCAL_H
#define         APP_PROTOCAL_H

#include "ble_task.h"
#include "app_variable.h"

#define MOD_PDU_RTT_DEBUG	2
#if (1 == MOD_PDU_RTT_DEBUG)	// 错误等级
#define MOD_PDU_RTT_LOG(...)
#define MOD_PDU_RTT_WARN(...)
#define MOD_PDU_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MOD_PDU_RTT_DEBUG)	// 警告等级
#define MOD_PDU_RTT_LOG(...)
#define MOD_PDU_RTT_WARN	RTT_DEBUG_WARN
#define MOD_PDU_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MOD_PDU_RTT_DEBUG)	// 调试等级
#define MOD_PDU_RTT_LOG		RTT_DEBUG_LOG
#define MOD_PDU_RTT_WARN	RTT_DEBUG_WARN
#define MOD_PDU_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define MOD_PDU_RTT_LOG(...)
#define MOD_PDU_RTT_WARN(...)
#define MOD_PDU_RTT_ERR(...)
#endif


#define TOTAL_STEP                  0x0407
#define BLE_BRODCASTNAME_MAXLENGTH  11 

//movt pin id
typedef enum
{
    MOVT_NULL               = 0x000,//0
    MOVT_3PIN_M             = 0x01,//1
    MOVT_1PIN_6C            = 0x0f,//15
    MOVT_1PIN_9C            = 0x10,//16
    MOVT_1PIN_3C            = 0x11,//17,   
    MOVT_2PIN_M             = 0x1B,//27 
}movtid;



typedef enum
{ 
    CANCEL_REMIND           = 0x00,//1
    NEW_REMIND              = 0x01,//0
}remind_protacal_t;

typedef enum
{
    MOVT_EVENT_RECOVER      = 0x00,
    MOVT_EVENT_STOP         = 0x01,
    MOVT_EVENT_FORWARD      = 0x02,
    MOVT_EVENT_REVERSE      = 0x03,
    MOVT_EVENT_ASSIGN       = 0x04,
}movtevent;

//**********************************************************************
// 函数功能: OTA状态处理
// 输入参数：u16param: = 0x00:退出OTA界面
//           = 0x01: 进入OTA界面
//           = 0x02: OTA结束复位
// 返回参数：
//**********************************************************************
extern void App_Protocal_OTAStatus(uint16 u16param);

//**********************************************************************
// 函数功能: 蓝牙断开时设置断开状态，退出OTA升级界面
// 输入参数：
// 返回参数：
//**********************************************************************
extern void App_Protocal_BleDisConn(void);

//**********************************************************************
extern void  App_Protocal_Init(void);

//**********************************************************************
// 函数功能: 重启蓝牙广播
// 输入参数：    
// 返回参数：
//**********************************************************************
extern void App_Protocal_Monitor(void);

//**********************************************************************
// oˉêy1|?ü: êúè¨3é1|
// ê?è?2?êy￡o    
// ·μ??2?êy￡o
//**********************************************************************
extern void App_Protocal_AuthorPass(void);

//**********************************************************************
// oˉêy1|?ü: ????
// ê?è?2?êy￡o    
// ·μ??2?êy￡o
//**********************************************************************
extern void App_Protocal_TakePhoto(void);

//**********************************************************************
// oˉêy1|?ü: 2é?òê??ú
// ê?è?2?êy￡o    
// ·μ??2?êy￡o
//**********************************************************************
extern void App_Protocal_FinePhone(void);

//**********************************************************************
// oˉêy1|?ü: ?ü?óμ??°
// ê?è?2?êy￡ophoneCallSource
// ·μ??2?êy￡o
//**********************************************************************
extern void App_Protocal_AcceptCall(uint8 phoneCallSource);

//**********************************************************************
// oˉêy1|?ü: à??à×′ì?éè??
// ê?è?2?êy￡onewblestate
// ·μ??2?êy￡o
//**********************************************************************
extern void App_Protocal_BleStateSet(uint8 newblestate);

//**********************************************************************
// 函数功能: 手表主动请求同步时间
// 输入参数：
// 返回参数：
//**********************************************************************
extern void App_Protocal_AdjustTimeprocess(void);

//**********************************************************************
// 函数功能: 手表主动请求天气信息
// 输入参数：
// 返回参数：
//**********************************************************************
void App_Protocal_GetWeatherProcess(void);

//**********************************************************************
// 函数功能: 设置蓝牙广播名
// 输入参数：    
// 返回参数：
//**********************************************************************
extern void App_Protocal_SetBtAdvName(uint8 *name);


//**********************************************************************
// 函数功能: 返回闹钟响闹
// 输入参数：闹钟编号    
// 返回参数：
//**********************************************************************
void App_Protocal_AlarmRing(uint8 alarmId);

//**********************************************************************
// 函数功能: 返回心率场景下的心率值
// 输入参数：实时心率值    
// 返回参数：
//**********************************************************************
void App_Protocal_HrmRet(uint8 hrval);

//**********************************************************************
// 函数功能: 来电提醒时的反馈
// 输入参数：
//fePhoneSystem: 手机系统类型，安卓 IOS
//   op    :　拒接，或接听　
// 返回参数：
//**********************************************************************
void App_Protocal_PhoneCallRet(PhoneSystem_e fePhoneSystem, PhoneCallOpt_e fePhoneCallOpt);

//**********************************************************************
// 函数功能: 返回SN码
// 输入参数：
// protocal: 协议内容指针
// 返回参数：
//**********************************************************************
void App_Protocal_RetSN(ble_msg_t *protocal);

#endif          //APP_PROTOCAL_H
