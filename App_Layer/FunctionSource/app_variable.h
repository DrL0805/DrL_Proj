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
	eDataClassifyStress,		// ����ѹ��
	eDataClassifyABC,
	eDataClassifySlpRcd,	// ˯�ߵ��� SleepRecord
	eDataClassifyRunRecord,
	eDataClassifyClimbRecord,
	eDataClassifySwimRecord,
	eDataClassifyGPS,
	eDataClassifyMax = 0xFFFF,
}eDataClassifyCode;

typedef enum
{
    BLE_SLEEP,               //����˯��״̬,�ع㲥
    BLE_BROADCAST,           //�����㲥״̬,���㲥
    BLE_CONNECT,             //��������״̬
    BLE_POWERON,             //�����ϵ�
    BLE_POWEROFF,            //��������
}BleState_e;

typedef enum 
{
    PHONE_STATE_NORMAL = 0,
    PHONE_STATE_PHOTO,
    PHONE_STATE_AUTHOR,
    PHONE_STATE_PAIRE,
    PHONE_STATE_HRM,
}phne_state_t;

// APP����Ϣ֪ͨ
typedef enum
{
    APP_REMIND_NONE                 = 0x00000000, //û��֪ͨ��Ϣ
    APP_REMIND_QQ                   = 0x00000001, //QQ֪ͨ��Ϣ
    APP_REMIND_WECHAT               = 0x00000002, //΢��֪ͨ��Ϣ
    APP_REMIND_TXWEIBO              = 0x00000004, //��Ѷ΢��֪ͨ��Ϣ
    APP_REMIND_SKYPE                = 0x00000008, //Skype֪ͨ��Ϣ
    APP_REMIND_XLWEIBO              = 0x00000010, //����΢��֪ͨ��Ϣ
    APP_REMIND_FACEBOOK             = 0x00000020, //facebook֪ͨ��Ϣ
    APP_REMIND_TWITTER              = 0x00000040, //twitter֪ͨ��Ϣ
    APP_REMIND_WHATAPP              = 0x00000080, //whatapp֪ͨ��Ϣ
    APP_REMIND_LINE                 = 0x00000100, //line֪ͨ��Ϣ
    APP_REMIND_OTHER1               = 0x00000200, //����1֪ͨ��Ϣ
    APP_REMIND_CALL                 = 0x00000400, //����֪ͨ��Ϣ
    APP_REMIND_MSG                  = 0x00000800, //����֪ͨ��Ϣ
    APP_REMIND_MISSCALL             = 0x00001000, //δ������֪ͨ��Ϣ
    APP_REMIND_CALENDARMSG          = 0x00002000, //������Ϣ֪ͨ��Ϣ
    APP_REMIND_EMAIL                = 0x00004000, //email֪ͨ��Ϣ
    APP_REMIND_OTHER2               = 0x00008000, //����2֪ͨ��Ϣ
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
    SYS_CHINESE_TYPE,	// ö��ע����Э���Ӧ
	SYS_ENGLISH_TYPE,
	eSysLangugeMax,
}SysLanguge_e;

typedef enum
{
    SYS_TIME_24_TYPE    = 0,
    SYS_TIME_12_TYPE, 
	eSysTimeTypeMax,
}SysTimeType_e;

// �ֻ�����ϵͳ����׿ / IOS
typedef enum
{
    IOS                     = 0x00,//0
    ANDROID                 = 0x01,//1
}PhoneSystem_e;

// ���紦������
typedef enum
{
	ePhoneCallReject = 0,	// ����ܽӣ���Э��ͳһ
    ePhoneCallAnswer = 1,	// �����������Э��ͳһ
	ePhoneCallIgnore,		// ������ԣ�Э���޴�
}PhoneCallOpt_e;

// *************************************************************
//���ܿ�������
typedef struct 
{
    SysSwitch_e     stepCountSwitch;			//�Ʋ� ����
    SysSwitch_e     heartrateSwitch;	 		//���� ����
    SysSwitch_e     weatherSwitch;				//���� ����
    SysSwitch_e     stepCompleteRemindSwitch;	//�˶���ɶȿ���
    SysSwitch_e     bleDiscRemindSwitch;		//�����Ͽ������Ƿ����ѵĿ���
    SysSwitch_e     longSitRemindSwitch;	 	//�������ѵĿ���
    SysSwitch_e     notDisturbSwitch;			//���ſ���
    SysSwitch_e     gestureSwitch;				//���ƿ���
    uint32      	appRemindSwitch;				//app���ѿ���
    uint32      	appDetailRemindSwitch;			//���У��������ѿ���
    SysLanguge_e    systermLanguge;	 				//ϵͳ����
    SysTimeType_e   systermTimeType;		 		//ϵͳʱ����ʽ
}SysConfig_t;

typedef struct 
{
    uint8_t StartHour;
    uint8_t StartMin;
    uint8_t StopHour;
    uint8_t StopMin;
}not_disturd_s;

//���Ź����ṹ��
typedef struct 
{
    uint8_t     lastCnt;
    uint8_t     curCnt;
    uint8_t     taskId;
    uint8_t     taskWdtState;   
}WatchDog_t;

//�ֻ�״̬�Ʋ��ṹ��
typedef struct 
{
    uint8 state;
    uint8 timeCnt;
    uint8 timeMax;
}PhoneState_t;

// ������Ϣ
typedef struct 
{
	uint8  Weight;		//���أ���λ��kg
	uint8  Height;		//��ߣ���λ��cm
	uint8  sex; 				//�Ա�
	uint8  age;	 			//����
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
