#ifndef         APP_VARIABLE_H
#define         APP_VARIABLE_H

#include "platform_common.h"


typedef enum
{
	eDataClassifyStep = 0x0000,
	eDataClassifySleep = 0x0001,
	eDataClassifyHeartRate = 0x0002,
	eDataClassifyRun = 0x0003,
	eDataClassifyRunNew = 0x0013,
	eDataClassifyClimb = 0x0004,
	eDataClassifyClimbNew = 0x0014,
	eDataClassifySwim = 0x0005,
	eDataClassifySwimNew = 0x0015,
	eDataClassifyBloodPressure = 0x0006,
	eDataClassifyBloodOxygen = 0x0007,
	eDataClassifyBodytemp = 0x0008,
	eDataClassifyEnvTemp = 0x0009,
	eDataClassifyAirPre = 0x000A,
	eDataClassifyAccel = 0x0020,
	eDataClassifyGro = 0x0021,
	eDataClassifyMag = 0x0022,
	eDataClassifyLine = 0xFF,
	eDataClassifyStress,		// 人体压力
	eDataClassifyABC,
	eDataClassifySlpRcd,	// 睡眠档案 SleepRecord
	eDataClassifyRunRecord,
	eDataClassifyClimbRecord,
	eDataClassifySwimRecord,
	eDataClassifyGPS,
	eDataClassifyMax = 0xFFFF,
}eDataClassifyCode;

typedef enum
{
    BLE_SLEEP,               //蓝牙睡眠状态,关广播
    BLE_BROADCAST,           //蓝牙广播状态,开广播
    BLE_CONNECT,             //蓝牙连接状态
    BLE_POWERON,             //蓝牙上电
    BLE_POWEROFF,            //蓝牙掉电
}BleState_e;

typedef enum 
{
    PHONE_STATE_NORMAL = 0,
    PHONE_STATE_PHOTO,
    PHONE_STATE_AUTHOR,
    PHONE_STATE_PAIRE,
    PHONE_STATE_HRM,
}phne_state_t;

// APP的消息通知
typedef enum
{
    APP_REMIND_NONE                 = 0x00000000, //没有通知消息
    APP_REMIND_QQ                   = 0x00000001, //QQ通知消息
    APP_REMIND_WECHAT               = 0x00000002, //微信通知消息
    APP_REMIND_TXWEIBO              = 0x00000004, //腾讯微博通知消息
    APP_REMIND_SKYPE                = 0x00000008, //Skype通知消息
    APP_REMIND_XLWEIBO              = 0x00000010, //新浪微博通知消息
    APP_REMIND_FACEBOOK             = 0x00000020, //facebook通知消息
    APP_REMIND_TWITTER              = 0x00000040, //twitter通知消息
    APP_REMIND_WHATAPP              = 0x00000080, //whatapp通知消息
    APP_REMIND_LINE                 = 0x00000100, //line通知消息
    APP_REMIND_OTHER1               = 0x00000200, //其他1通知消息
    APP_REMIND_CALL                 = 0x00000400, //来电通知消息
    APP_REMIND_MSG                  = 0x00000800, //短信通知消息
    APP_REMIND_MISSCALL             = 0x00001000, //未接来电通知消息
    APP_REMIND_CALENDARMSG          = 0x00002000, //日历信息通知消息
    APP_REMIND_EMAIL                = 0x00004000, //email通知消息
    APP_REMIND_OTHER2               = 0x00008000, //其他2通知消息
    APP_REMIND_PERSON               = 0x00010000,
    APP_REMIND_TIM                  = 0x00020000, //TIM
    // APP_REMIND_ALL                  = 0xffffffff, 
}app_remind_type;


typedef enum 
{
    SWITCH_OFF,
    SWITCH_ON,
	eSysSwitchMax,
}SysSwitch_e;

typedef enum
{
    SYS_CHINESE_TYPE,	// 枚举注意与协议对应
	SYS_ENGLISH_TYPE,
	eSysLangugeMax,
}SysLanguge_e;

typedef enum
{
    SYS_TIME_24_TYPE    = 0,
    SYS_TIME_12_TYPE, 
	eSysTimeTypeMax,
}SysTimeType_e;

// 手机操作系统，安卓 / IOS
typedef enum
{
    IOS                     = 0x00,//0
    ANDROID                 = 0x01,//1
}PhoneSystem_e;

// 来电处理类型
typedef enum
{
	ePhoneCallReject = 0,	// 来电拒接，跟协议统一
    ePhoneCallAnswer = 1,	// 来电接听，跟协议统一
	ePhoneCallIgnore,		// 来电忽略，协议无此
}PhoneCallOpt_e;

// *************************************************************
//功能开关配置
typedef struct 
{
    SysSwitch_e     stepCountSwitch;			//计步 开关
    SysSwitch_e     heartrateSwitch;	 		//心率 开关
    SysSwitch_e     weatherSwitch;				//天气 开关
    SysSwitch_e     stepCompleteRemindSwitch;	//运动完成度开关
    SysSwitch_e     bleDiscRemindSwitch;		//蓝牙断开连接是否提醒的开关
    SysSwitch_e     longSitRemindSwitch;	 	//久坐提醒的开关
    SysSwitch_e     notDisturbSwitch;			//勿扰开关
    SysSwitch_e     gestureSwitch;				//手势开关
    uint32      	appRemindSwitch;				//app提醒开关
    uint32      	appDetailRemindSwitch;			//ＡＰＰ详情提醒开关
    SysLanguge_e    systermLanguge;	 				//系统语言
    SysTimeType_e   systermTimeType;		 		//系统时间制式
}SysConfig_t;

typedef struct 
{
    uint8_t StartHour;
    uint8_t StartMin;
    uint8_t StopHour;
    uint8_t StopMin;
}not_disturd_s;

//看门狗监测结构体
typedef struct 
{
    uint8_t     lastCnt;
    uint8_t     curCnt;
    uint8_t     taskId;
    uint8_t     taskWdtState;   
}WatchDog_t;

//手机状态计步结构体
typedef struct 
{
    uint8 state;
    uint8 timeCnt;
    uint8 timeMax;
}PhoneState_t;

// 人体信息
typedef struct 
{
	uint8  Weight;		//体重：单位：kg
	uint8  Height;		//身高：单位：cm
	uint8  sex; 				//性别
	uint8  age;	 			//年龄
}BodyInfo_t;


extern PhoneState_t    		gtPhoneState;
extern WatchDog_t 			gtWatchDog;
extern SysConfig_t    		gtSysCfg;
extern BleState_e 			geBleState;
extern BodyInfo_t			gtBodyInfo;
extern PhoneSystem_e 		gePhoneSystem;
extern not_disturd_s appNotDisturdTimeInfo;


extern void App_Var_Init(void);
extern void App_Var_BleStateSet(BleState_e fBleState);
extern BleState_e App_Var_BleStateGet(void);
extern void App_Var_BLERemindSwitchSet(SysSwitch_e  fSysSwitchState);
extern SysSwitch_e App_Var_BLERemindSwitchGet(void);
extern void App_Var_SedentaryRemindSwitchSet(SysSwitch_e  fSysSwitchState);
extern SysSwitch_e App_Var_SedentaryRemindSwitchGet(void);
extern void App_Var_NoDisturbSwitchSet(SysSwitch_e  fSysSwitchState);
extern SysSwitch_e App_Var_NoDisturbSwitchGet(void);
extern void App_Var_GestureSwitchSet(SysSwitch_e  fSysSwitchState);
extern SysSwitch_e App_Var_GestureSwitchGet(void);
extern void App_Var_AppRemindSwitchSet(uint32_t fAppRemindSwitch);
extern uint32_t App_Var_AppRemindSwitchGet(void);
extern void App_Var_AppDetailRemindSwitchSet(uint32_t fAppRemindSwitch);
extern uint32_t App_Var_AppDetailRemindSwitchGet(void);
extern void App_Var_SysLangugeSet(SysLanguge_e fSysLanguge);
extern SysLanguge_e App_Var_SysLangugeGet(void);
extern void App_Var_SysTimeTypeSet(SysTimeType_e fSysTimeType);
extern SysTimeType_e App_Var_SysTimeTypeGet(void);
extern void App_Var_Test(void);

#endif          //APP_VARIABLE_H
