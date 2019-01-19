#include "bsp_common.h"
#include "app_systerm.h"
#include "app_variable.h"
#include "app_protocal.h"
#include "mid_interface.h"
#include "scene_interface.h"
#include "ui_display_main.h"
#include "ui_screen_other.h"
#include "ble_db.h"

AppSysParam_t	AppSysParam;

/*******************************************************************************
 * Brief : 获取系统复位类型
 * Input : @NULL 
 * Return: @AppSysStateType_e 系统复位类型枚举值
 * Call  : 
 ***************/
static AppSysStateType_e App_Sys_RstTypeGet(void)
{
	uint8_t lStrOTA[] = "OTA";
	uint8_t lStrWDT[] = "WDT";
	uint8_t	lBuf[5];
	
	Store_Part_Read(eStorePart2KB, 5, lBuf, 5);
	
	if(drCMN_ArrayCmp(lBuf, lStrOTA, 3))
	{
		return eAppSysStateOTARst;
	}
	
	if(drCMN_ArrayCmp(lBuf, lStrWDT, 3))
	{
		return eAppSysStateWDTRst;
	}	
	
	return eAppSysStatePwrRst;
}

/*******************************************************************************
 * Brief : 设置存在FLASH的系统复位状态
 * Input : @feAppSysStateType 系统状态枚举值
 * Return: @NULL 
 * Call  : 
 ***************/
static void App_Sys_InfoBackupMark(AppSysStateType_e feAppSysStateType)
{
	uint8_t lpBuf[4];
	
	/* 0~3,4Byte 复位类型OTA/WDT */
	switch(feAppSysStateType)
	{
		case eAppSysStateOTARst: lpBuf[0] = 'O', lpBuf[1] = 'T', lpBuf[2] = 'A';
			break;
		case eAppSysStateWDTRst: lpBuf[0] = 'W', lpBuf[1] = 'D', lpBuf[2] = 'T';
			break;
		default: 
			memset(lpBuf, 0xFF, 4);
			break;
	}
	
	Store_Part_Write(eStorePart2KB, 5, lpBuf, 4);
}

/*******************************************************************************
 * Brief : 系统初始化
 * Input : @NULL 
 * Return: @NULL
 * Call  : 系统开机时调用一次
 ***************/
void App_Sys_Init(void)
{
	Mid_Schd_TaskMsg_T Msg;
	
	#if 1	// 打开RTC，用于测试
	Mid_Rtc_Start();
	#endif
	
	/* 获取系统复位类型 */
	App_Sys_StateSet(App_Sys_RstTypeGet());
	
	/* 系统初始化 */
	App_Var_Init();					// 系统参数初始化
	Scene_Interface_Init();			// 场景初始化
	App_RemindManage_Init();		// 提醒初始化
	App_Protocal_Init();			// 通信协议初始化
	
	// 开机采集一次电池电量
	Msg.Id = eSchdTaskMsgBat;
	Msg.Param.Bat.Id = eBatEventBatCheck;
	Mid_Schd_TaskEventSet(&Msg);
	
	/* 根据不同复位类型，系统进入不同状态 */
	switch (App_Sys_StateGet())
    {
    	case eAppSysStatePwrRst:
            //step 1: 恢复出厂默认蓝牙名，并保存到flash
            Mid_Ble_SetAdvNameDefault();

			Store_Interface_ClearInit();
			App_Sys_StateSet(eAppSysStateStore);
		
//			/** 显示复位图标1秒 */
//			UI_Screen_Reset_Show();
//			vTaskDelay(1000);
		
			#if 0	// 用于恢复测试
			App_Sys_InfoRecover();
//			Store_Interface_RecoverInit();
			#endif
    		break;
    	case eAppSysStateOTARst:
		case eAppSysStateWDTRst:
			Store_Interface_RecoverInit();
			App_Sys_InfoRecover();
			App_Sys_StateSet(eAppSysStateStore);
    		break;
    	default :
			drERROR_CHECK("App_Sys_Init", Ret_InvalidParam);
    		break;
    }
	
	App_Sys_InfoBackupMark(eAppSysStatePwrRst);	// 开机后修改存于FLASH中的系统复位状态
	BLE_Stack_SetAncsMsgSwitch(gtSysCfg.appRemindSwitch);	// 系统恢复数据时调用，告诉蓝牙底层消息提醒开关
}

/*******************************************************************************
 * Brief : 系统开机
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void App_Sys_StartingUp(void)
{
	App_Protocal_BleStateSet(BLE_POWERON);
	
//	Mid_Rtc_Start();
	
	Scene_Interface_Enable();	// 场景使能
	
	Mid_WDT_Enable();		// 开机后开启开门狗

	Drv_Touch_Wakeup();

    UI_Common_Open_Blacklight();
	
	App_Sys_StateSet(eAppSysStateNormal);
	
	RTT_DEBUG_LOG(0, "App_Sys_StartingUp \n");
	
	#if 1 // test
//	Mid_Motor_ShakeStart(eMidMotorShake2Hz, 1);	// 马达震动提示开机
	
//	Scene_Hrm_SampleStart(eSceneMeasureBG);
//	Scene_Hrm_SampleStart(eSceneMeasureBG);
//	Scene_Hrm_SampleStart(eSceneMeasureBG);

//	Scene_Stress_SampleStart(eSceneMeasureBG);
//	Scene_Stress_SampleStart(eSceneMeasureBG);
	#endif
}

/*******************************************************************************
 * Brief : 系统关机（复位后进入仓储模式）
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void App_Sys_Shutdown(void)
{
	RTT_DEBUG_LOG(0, "App_Sys_Shutdown \n");
	
	BLE_Stack_SetAncsMsgSwitch(gtSysCfg.appRemindSwitch);
	
	Mid_WDT_Disable();
	
	#if 0	// 马达震动提示关机
	Mid_Motor_ShakeStart(eMidMotorShake2Hz, 1);
	#endif
	
	/** 显示复位图标1秒 */
	UI_Screen_Reset_Show();
	vTaskDelay(1000);
	
	Mid_SystermReset();
}

/*******************************************************************************
 * Brief : 设置系统状态
 * Input : @feAppSysStateType 系统状态枚举值
 * Return: @NULL
 * Call  : 
 ***************/
void App_Sys_StateSet(AppSysStateType_e feAppSysStateType)
{
	if(feAppSysStateType >= eAppSysStateMax) drERROR_CHECK_RETURN_NULL("App_Sys_StateSet", Ret_InvalidParam); 
	
	AppSysParam.SysState = feAppSysStateType;
	
	RTT_DEBUG_LOG(0, "App_Sys_StateSet %d \n", AppSysParam.SysState);
}

/*******************************************************************************
 * Brief : 获取系统状态
 * Input : @NULL 
 * Return: @AppSysStateType_e 系统状态枚举值
 * Call  : 
 ***************/
AppSysStateType_e App_Sys_StateGet(void)
{
	return AppSysParam.SysState;
}

/*******************************************************************************
 * Brief : 系统信息备份
 * Input : @feAppSysStateType 系统状态枚举值
 * Return: @NULL 
 * Call  : 
 ***************/
void App_Sys_InfoBackup(AppSysStateType_e feAppSysStateType)
{
	RTT_DEBUG_LOG(0, "App_Sys_InfoBackup %d \n", feAppSysStateType);
	
	uint8_t * lpBuf;
	
	/* 0~3,4Byte 复位类型OTA/WDT */
	App_Sys_InfoBackupMark(feAppSysStateType);
	
	lpBuf= pvPortMalloc(STORE_MAX_MALLOC_LEN);
	
	/* 4~8,4Byte UTC时间 */
	
	
	/* Store状态信息 */
	
	
	Store_Part_Write(eStorePart2KB, 5, lpBuf+4, STORE_MAX_MALLOC_LEN-4);
	
	vPortFree(lpBuf);
}

/*******************************************************************************
 * Brief : 系统信息恢复
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void App_Sys_InfoRecover(void)
{
	/* FLASH存储信息恢复 */
	Store_Cmn_SysInfoReadUpdate();
	Store_Cmn_TimeInfoReadUpdate();
	Store_Cmn_AlarmInfoReadUpdate();
	Store_Cmn_BodyInfoReadUpdate();
	
	/*  */
	
}













