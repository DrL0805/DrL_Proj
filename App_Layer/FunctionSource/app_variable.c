#include "app_variable.h"
#include "app_protocal.h"


// *************************系统配置信息************************************
SysConfig_t    gtSysCfg;

// 开门狗 ***********************************************************
WatchDog_t gtWatchDog =
{
    .lastCnt         = 0,
    .curCnt          = 0,
    .taskId          = 0,
    .taskWdtState    = 0,   
};

// 手机状态 ***********************************************************
PhoneState_t    gtPhoneState =
{
    .state      = PHONE_STATE_NORMAL,
    .timeCnt    = 0,
    .timeMax    = 30,   //最大计时30秒
};

BodyInfo_t	gtBodyInfo = 
{
	.Weight = 60,
	.Height = 175,
	.sex = 0,
	.age = 18,
};

// 蓝牙状态 ***********************************************************
BleState_e    geBleState = BLE_BROADCAST;;

// 勿扰信息 ***********************************************************
not_disturd_s appNotDisturdTimeInfo =
{
    .StartHour              = 9,
    .StartMin               = 0,
    .StopHour               = 17,
    .StopMin                = 0,
};

PhoneSystem_e gePhoneSystem;

// 系统参数初始化
void App_Var_Init(void)
{
	App_Var_BLERemindSwitchSet(SWITCH_OFF);
	
	App_Var_SedentaryRemindSwitchSet(SWITCH_ON);
	
	App_Var_NoDisturbSwitchSet(SWITCH_OFF);
	
	App_Var_GestureSwitchSet(SWITCH_ON);
	
	App_Var_AppRemindSwitchSet(0xFFFFFFFF);
	
	App_Var_AppDetailRemindSwitchSet(0xFFFFFFFF);
	
	App_Var_SysLangugeSet(SYS_ENGLISH_TYPE);
	
	App_Var_SysTimeTypeSet(SYS_TIME_24_TYPE);	
}

// 蓝牙状态
void App_Var_BleStateSet(BleState_e fBleState)
{
	geBleState = fBleState;
}

BleState_e App_Var_BleStateGet(void)
{
	return geBleState;
}

// 蓝牙提醒开关
void App_Var_BLERemindSwitchSet(SysSwitch_e  fSysSwitchState)
{
	gtSysCfg.bleDiscRemindSwitch = fSysSwitchState;
}

SysSwitch_e App_Var_BLERemindSwitchGet(void)
{
	return gtSysCfg.bleDiscRemindSwitch;
}

// 久坐提醒开关
void App_Var_SedentaryRemindSwitchSet(SysSwitch_e  fSysSwitchState)
{
	gtSysCfg.longSitRemindSwitch = fSysSwitchState;
}

SysSwitch_e App_Var_SedentaryRemindSwitchGet(void)
{
	return gtSysCfg.longSitRemindSwitch;
}

// 勿扰开关
void App_Var_NoDisturbSwitchSet(SysSwitch_e  fSysSwitchState)
{
	gtSysCfg.notDisturbSwitch = fSysSwitchState;
}

SysSwitch_e App_Var_NoDisturbSwitchGet(void)
{
	return gtSysCfg.notDisturbSwitch;
}

// 手势开关
void App_Var_GestureSwitchSet(SysSwitch_e  fSysSwitchState)
{
	gtSysCfg.gestureSwitch = fSysSwitchState;
}

SysSwitch_e App_Var_GestureSwitchGet(void)
{
	return gtSysCfg.gestureSwitch;
}

// app提醒开关
void App_Var_AppRemindSwitchSet(uint32_t fAppRemindSwitch)
{
	gtSysCfg.appRemindSwitch = fAppRemindSwitch;
}

uint32_t App_Var_AppRemindSwitchGet(void)
{
	return gtSysCfg.appRemindSwitch;
}

// app详情提醒开关
void App_Var_AppDetailRemindSwitchSet(uint32_t fAppRemindSwitch)
{
	gtSysCfg.appDetailRemindSwitch = fAppRemindSwitch;
}

uint32_t App_Var_AppDetailRemindSwitchGet(void)
{
	return gtSysCfg.appDetailRemindSwitch;
}

// 系统语言
void App_Var_SysLangugeSet(SysLanguge_e fSysLanguge)
{
	gtSysCfg.systermLanguge = fSysLanguge;
}

SysLanguge_e App_Var_SysLangugeGet(void)
{
	return gtSysCfg.systermLanguge;
}

// 系统时间制式
void App_Var_SysTimeTypeSet(SysTimeType_e fSysTimeType)
{
	gtSysCfg.systermTimeType = fSysTimeType;
}

SysTimeType_e App_Var_SysTimeTypeGet(void)
{
	return gtSysCfg.systermTimeType;
}






void App_Var_Test(void)
{
	#if 0	// 系统配置信息
	{
		RTT_DEBUG_printf(0, "gtSysCfg: \n");
//		RTT_DEBUG_printf(0, ".stepCountSwitch %d \n", gtSysCfg.stepCountSwitch);
//		RTT_DEBUG_printf(0, ".heartrateSwitch %d \n", gtSysCfg.heartrateSwitch);
//		RTT_DEBUG_printf(0, ".weatherSwitch %d \n", gtSysCfg.weatherSwitch);
//		RTT_DEBUG_printf(0, ".stepCompleteRemindSwitch %d \n", gtSysCfg.stepCompleteRemindSwitch);
//		RTT_DEBUG_printf(0, ".bleDiscRemindSwitch %d \n", gtSysCfg.bleDiscRemindSwitch);
		RTT_DEBUG_printf(0, ".longSitRemindSwitch %d \n", gtSysCfg.longSitRemindSwitch);
//		RTT_DEBUG_printf(0, ".notDisturbSwitch %d \n", gtSysCfg.notDisturbSwitch);
//		RTT_DEBUG_printf(0, ".gestureSwitch %d \n", gtSysCfg.gestureSwitch);
//		RTT_DEBUG_printf(0, ".appRemindSwitch %d \n", gtSysCfg.appRemindSwitch);
//		RTT_DEBUG_printf(0, ".appDetailRemindSwitch %d \n", gtSysCfg.appDetailRemindSwitch);
//		RTT_DEBUG_printf(0, ".systermLanguge %d \n", gtSysCfg.systermLanguge);
//		RTT_DEBUG_printf(0, ".systermTimeType %d \n", gtSysCfg.systermTimeType);	
	}
	#endif
	
	#if 0	// 勿扰信息
	{
		RTT_DEBUG_printf(0, "appNotDisturdTimeInfo %02d:%02d - %02d:%02d \n", 
			appNotDisturdTimeInfo.StartHour, appNotDisturdTimeInfo.StartMin, appNotDisturdTimeInfo.StopHour, appNotDisturdTimeInfo.StopMin);
	}
	#endif
}



























