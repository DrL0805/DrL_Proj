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
 * Brief : ��ȡϵͳ��λ����
 * Input : @NULL 
 * Return: @AppSysStateType_e ϵͳ��λ����ö��ֵ
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
 * Brief : ���ô���FLASH��ϵͳ��λ״̬
 * Input : @feAppSysStateType ϵͳ״̬ö��ֵ
 * Return: @NULL 
 * Call  : 
 ***************/
static void App_Sys_InfoBackupMark(AppSysStateType_e feAppSysStateType)
{
	uint8_t lpBuf[4];
	
	/* 0~3,4Byte ��λ����OTA/WDT */
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
 * Brief : ϵͳ��ʼ��
 * Input : @NULL 
 * Return: @NULL
 * Call  : ϵͳ����ʱ����һ��
 ***************/
void App_Sys_Init(void)
{
	Mid_Schd_TaskMsg_T Msg;
	
	#if 1	// ��RTC�����ڲ���
	Mid_Rtc_Start();
	#endif
	
	/* ��ȡϵͳ��λ���� */
	App_Sys_StateSet(App_Sys_RstTypeGet());
	
	/* ϵͳ��ʼ�� */
	App_Var_Init();					// ϵͳ������ʼ��
	Scene_Interface_Init();			// ������ʼ��
	App_RemindManage_Init();		// ���ѳ�ʼ��
	App_Protocal_Init();			// ͨ��Э���ʼ��
	
	// �����ɼ�һ�ε�ص���
	Msg.Id = eSchdTaskMsgBat;
	Msg.Param.Bat.Id = eBatEventBatCheck;
	Mid_Schd_TaskEventSet(&Msg);
	
	/* ���ݲ�ͬ��λ���ͣ�ϵͳ���벻ͬ״̬ */
	switch (App_Sys_StateGet())
    {
    	case eAppSysStatePwrRst:
            //step 1: �ָ�����Ĭ���������������浽flash
            Mid_Ble_SetAdvNameDefault();

			Store_Interface_ClearInit();
			App_Sys_StateSet(eAppSysStateStore);
		
//			/** ��ʾ��λͼ��1�� */
//			UI_Screen_Reset_Show();
//			vTaskDelay(1000);
		
			#if 0	// ���ڻָ�����
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
	
	App_Sys_InfoBackupMark(eAppSysStatePwrRst);	// �������޸Ĵ���FLASH�е�ϵͳ��λ״̬
	BLE_Stack_SetAncsMsgSwitch(gtSysCfg.appRemindSwitch);	// ϵͳ�ָ�����ʱ���ã����������ײ���Ϣ���ѿ���
}

/*******************************************************************************
 * Brief : ϵͳ����
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void App_Sys_StartingUp(void)
{
	App_Protocal_BleStateSet(BLE_POWERON);
	
//	Mid_Rtc_Start();
	
	Scene_Interface_Enable();	// ����ʹ��
	
	Mid_WDT_Enable();		// �����������Ź�

	Drv_Touch_Wakeup();

    UI_Common_Open_Blacklight();
	
	App_Sys_StateSet(eAppSysStateNormal);
	
	RTT_DEBUG_LOG(0, "App_Sys_StartingUp \n");
	
	#if 1 // test
//	Mid_Motor_ShakeStart(eMidMotorShake2Hz, 1);	// �������ʾ����
	
//	Scene_Hrm_SampleStart(eSceneMeasureBG);
//	Scene_Hrm_SampleStart(eSceneMeasureBG);
//	Scene_Hrm_SampleStart(eSceneMeasureBG);

//	Scene_Stress_SampleStart(eSceneMeasureBG);
//	Scene_Stress_SampleStart(eSceneMeasureBG);
	#endif
}

/*******************************************************************************
 * Brief : ϵͳ�ػ�����λ�����ִ�ģʽ��
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void App_Sys_Shutdown(void)
{
	RTT_DEBUG_LOG(0, "App_Sys_Shutdown \n");
	
	BLE_Stack_SetAncsMsgSwitch(gtSysCfg.appRemindSwitch);
	
	Mid_WDT_Disable();
	
	#if 0	// �������ʾ�ػ�
	Mid_Motor_ShakeStart(eMidMotorShake2Hz, 1);
	#endif
	
	/** ��ʾ��λͼ��1�� */
	UI_Screen_Reset_Show();
	vTaskDelay(1000);
	
	Mid_SystermReset();
}

/*******************************************************************************
 * Brief : ����ϵͳ״̬
 * Input : @feAppSysStateType ϵͳ״̬ö��ֵ
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
 * Brief : ��ȡϵͳ״̬
 * Input : @NULL 
 * Return: @AppSysStateType_e ϵͳ״̬ö��ֵ
 * Call  : 
 ***************/
AppSysStateType_e App_Sys_StateGet(void)
{
	return AppSysParam.SysState;
}

/*******************************************************************************
 * Brief : ϵͳ��Ϣ����
 * Input : @feAppSysStateType ϵͳ״̬ö��ֵ
 * Return: @NULL 
 * Call  : 
 ***************/
void App_Sys_InfoBackup(AppSysStateType_e feAppSysStateType)
{
	RTT_DEBUG_LOG(0, "App_Sys_InfoBackup %d \n", feAppSysStateType);
	
	uint8_t * lpBuf;
	
	/* 0~3,4Byte ��λ����OTA/WDT */
	App_Sys_InfoBackupMark(feAppSysStateType);
	
	lpBuf= pvPortMalloc(STORE_MAX_MALLOC_LEN);
	
	/* 4~8,4Byte UTCʱ�� */
	
	
	/* Store״̬��Ϣ */
	
	
	Store_Part_Write(eStorePart2KB, 5, lpBuf+4, STORE_MAX_MALLOC_LEN-4);
	
	vPortFree(lpBuf);
}

/*******************************************************************************
 * Brief : ϵͳ��Ϣ�ָ�
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void App_Sys_InfoRecover(void)
{
	/* FLASH�洢��Ϣ�ָ� */
	Store_Cmn_SysInfoReadUpdate();
	Store_Cmn_TimeInfoReadUpdate();
	Store_Cmn_AlarmInfoReadUpdate();
	Store_Cmn_BodyInfoReadUpdate();
	
	/*  */
	
}













