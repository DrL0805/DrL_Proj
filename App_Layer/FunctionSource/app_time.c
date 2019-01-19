
#include "app_time.h"

#include "mid_interface.h"
#include "scene_interface.h"
#include "store_interface.h"
#include "app_variable.h"
#include "app_protocal.h"
#include "app_systerm.h"
#include "ui_screen_warn.h"


static QueueHandle_t 	sTime_QueueHandle;				// ���о��
#define		TIME_TASK_QUEUE_LENGTH			3			// 
#define 	TIME_TASK_QUEUE_WAIT_TICK		100			// ��������ʱ��
#define		TIME_TASK_QUEUE_SIZE				sizeof(AppTimeTaskMsg_t)

/*******************************************************************************
 * Brief : ����Ƿ�������ʱ�����
 * Input : @NULL 
 * Return: 0 ��ǰ������ʱ��Σ�1 ��ǰ��������ʱ���
 * Call  : 
 ***************/
uint16_t App_Time_NotDisturdTimeCheck(void)
{
    rtc_time_s  timeTemp;

    uint32_t i,j,n;
    
    Mid_Rtc_TimeRead(&timeTemp);

    n = timeTemp.hour*3600 + timeTemp.min*60;
    
    i = appNotDisturdTimeInfo.StartHour*3600 + appNotDisturdTimeInfo.StartMin*60;
    j = appNotDisturdTimeInfo.StopHour *3600 + appNotDisturdTimeInfo.StopMin *60;
    
    if(TimePeriodJudge(i,j,n))
		return 1;
    
    return 0;
}

// RTCÿ������¼�����
static void App_Time_RTCSecHandler(void)
{
	Mid_Schd_TaskMsg_T Msg;	
	MID_PRESS_PARA_T*	tPressPara = Mid_Press_ParamPGet();
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	ab_value_t          tab_value;
	Scene_ABC_ABGet(&tab_value);

//	APP_TIME_RTT_LOG(0,"20%d/%d/%d %02d:%02d:%02d \r\n",
//		lMidRTC->RTC.year, lMidRTC->RTC.month, lMidRTC->RTC.day, lMidRTC->RTC.hour, lMidRTC->RTC.min, lMidRTC->RTC.sec);
//	APP_TIME_RTT_LOG(0,"UTC %d \n",lMidRTC->UTC);
	
	/* ceshi */
//	UI_Set_Curr_ScreenID(Common_Screen_MainID_Test);
//	UI_Screen_draw_Screen();
//	Scene_Hrm_RestAlgo();
	
	/* ÿ�����Ƿ���Ҫ����ѹ����̨������
	����ѹ��Ҫ��������ǰ�棬��Ϊ����ѹ����������������� */
	Scene_Stress_BGSampleCheck();
	
	/* ÿ�����Ƿ���Ҫ���ʺ�̨���� */
	Scene_Hrm_BGSampleCheck();
	
	// ÿ��������������㷨��ʱ���
	Mid_Hrm_UnwearCheck();
	Mid_Hrm_TimeoutCheck();
	
	// ÿ�����һ�μƲ��˶�ʱ���㷨
	Scene_Step_DuarationAlgo();
	
	// ÿ�����һ����¥���㷨
	Scene_Stair_Algorithm();
	
	/* ÿ�����һ���ܲ��㷨 */
	Scene_Run_Algorithm();
	
	/* ÿ�����һ�ε�ɽ�㷨 */
	Scene_Climb_Algorithm();
	
	/* ÿ�����һ����Ӿ�㷨 */
	Scene_Swim_Algorithm(NULL, eSceneSwimAlgoHr);

    //ÿ����һ�γ��״̬
	Msg.Id = eSchdTaskMsgBat;
	Msg.Param.Bat.Id = eBatEventChargCheck;
	Mid_Schd_TaskEventSet(&Msg);
	#if 0	// debug����ӡ�����ٷֱ�
	uint8_t lBatVal = 0;
	Mid_Bat_SocRead(&lBatVal);
	MID_SCHD_RTT_LOG(0, "Mid_Bat_SocRead %d \n", lBatVal);
	#endif
    
	/* ÿ��һ�κ�����ѹ�㷨����ʹû������ѹ���ݣ�ҲҪÿ�����һ�� */
	Scene_ABC_ABalgorithm();
	
	/** ÿ���ȡһ������FIFO���� */
	SceneTaskMsg_t 	tAlgoMsg;			
	tAlgoMsg.Id = eAlgoTaskMsg6Dof;
	Scene_Task_TaskEventSet(&tAlgoMsg);
	
	//�����ֻ�ǿ����״̬
	if (gtPhoneState.state != PHONE_STATE_NORMAL)
	{
		gtPhoneState.timeCnt++;

		if (gtPhoneState.timeCnt > gtPhoneState.timeMax)
		{
			switch(gtPhoneState.state)
			{
				case PHONE_STATE_PHOTO:	// ����
					UI_Screen_Close_Warn_Screen_Camera();
					APP_TIME_RTT_LOG(0,"PHONE_STATE_PHOTO TimeOut \r\n");		// 
					break;
				case PHONE_STATE_AUTHOR:
					APP_TIME_RTT_LOG(0,"PHONE_STATE_AUTHOR TimeOut \r\n");		// ��Ȩ��ʱ
					break;
				case PHONE_STATE_PAIRE:
					break;
				case PHONE_STATE_HRM:
					break;
				default: break;
			}
			gtPhoneState.state = PHONE_STATE_NORMAL;
			gtPhoneState.timeCnt  = 0;
		}
	}

    //yangrui add for lock screen
    UI_Commom_Lockinfo_Timehandle();
}

// RTCÿ���ӵ����¼�����
static void App_Time_RTCMinHandler(void)
{
	SceneAlarmParam_t* ltpAlarmParam;
	Mid_Schd_TaskMsg_T Msg;
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();

	if(0 == (lMidRTC->RTC.min % SCENE_HRM_REST_ALGO_PERIOD))
	/* ��Ϣ�����㷨 */
	{
		Scene_Hrm_RestAlgo();
	}
	
	if(0 == (lMidRTC->RTC.min % 10))
	/* ÿ10min����һ�κ�̨���ʲ��� */	
	{
		Scene_Stress_SampleStart(eSceneMeasureBG);
	}
	
	if(0 == (lMidRTC->RTC.min % 2))
	/* ÿ2min����һ�κ�̨���ʲ��� */	
	{
		Scene_Hrm_SampleStart(eSceneMeasureBG);
	}

	if(0 == (lMidRTC->RTC.min % 5))
	/* ÿ5min�洢һ�μƲ��ۼ�ֵ */	
	{
		Store_Step_algorithm();
	}
	
	if(0 == (lMidRTC->RTC.min % 2))
	/* ÿ2���Ӵ洢һ��ABֵ */	
	{
		Store_ABC_algorithm();
	}

	if(0 == (lMidRTC->RTC.min % 5))
	/* ÿ5���Ӽ��һ�ε��� */	
	{
		Msg.Id = eSchdTaskMsgBat;
		Msg.Param.Bat.Id = eBatEventBatCheck;
		Mid_Schd_TaskEventSet(&Msg);	
	}

	if(Scene_Alarm_Check())
	/** ÿmin���һ������ */ 	
	{
		if (gtPhoneState.state != PHONE_STATE_PHOTO)
		/** ����״̬���������� */
		{
			// ��APP���������¼�
			ltpAlarmParam = Scene_Alarm_ParamPGet();
			App_Protocal_AlarmRing(ltpAlarmParam->curRingAlarmId);
			
			// ��APP�㷢�������¼�
			UI_Screen_Show_Warn_Screen_Alarm();
			Mid_Motor_ShakeStart(eMidMotorShake2Hz, 10);			
		}
	}
}

// RTCÿСʱ�����¼�����
static void App_Time_RTCHourHandler(void)
{
	// ÿСʱ����һ������UI�ļƲ�����
	Store_Step_UIDataUpdate();
	
	// ÿСʱ��APP��ȡ������Ϣ
    if(geBleState == BLE_CONNECT)
    {
       App_Protocal_GetWeatherProcess();
    }
}

// RTCÿ������¼�����
static void App_Time_RTCDayHandler(void)
{
	// ÿ��ͬ��RTCʱ��
    if (geBleState == BLE_CONNECT)
    {
        App_Protocal_AdjustTimeprocess();
    }
	
	// ÿ����ռƲ���Ϣ
	Scene_Step_Clear();
	
	// ÿ�������¥������
	Scene_Stair_Clear();
	
	// ÿ�������һ��˯�����ݣ������ֵ�FLASH��
	Scene_Sleep_Clear();
	Store_Sleep_CatalogSeal();
}

//**********************************************************************
// ��������: ����������������
// ���������
// ���ز�����
static void App_Time_RTCHandler(AppTimeTaskMsg_t*	Msg)
{
	if(eAppSysStateStore == App_Sys_StateGet())
	/* ��ǰ���ڲִ�ģʽ��ֱ���˳������ڹ��Ĳ��� */
	{
		if(eMidRTCMsgSec == Msg->Param.RTC.Msg)
		/* 1Hz������ */
		{
//			Mid_Bat_Test();	// ��ص����ɼ�����
//			Mid_NandFlash_Test();	// nandflash ��д������
//			Mid_Front_Test();		// �ֿ��ȡ����
//			Mid_Press_Test();
//			Mid_IT_ConverStart();
			
//			Mid_Press_ContinuousCvtCheck();
		}
		
//		return;
	}

	Mid_WDT_ReStart();
	Mid_Lcd_ExtcominTog();
	Drv_Touch_IdleTimeoutCheck();	// TP���߳�ʱ���
	
	switch (Msg->Param.RTC.Msg)
	{
//		case eMidRTCMsgHalfSec:
//			break;
		case eMidRTCMsgSec:
			App_Time_RTCSecHandler();
			break;
		case eMidRTCMsgMin:
			App_Time_RTCSecHandler();
			App_Time_RTCMinHandler();
			break;
		case eMidRTCMsgHour:
			App_Time_RTCSecHandler();
			App_Time_RTCMinHandler();			
			App_Time_RTCHourHandler();
			break;
		case eMidRTCMsgDay:
			App_Time_RTCSecHandler();
			App_Time_RTCMinHandler();	
			App_Time_RTCHourHandler();		
			App_Time_RTCDayHandler();
			break;
		default:
			break;
	}
}

// ***********************************************************************
//	������������ȴ���
// ***********************************************************************
static void App_Time_TaskProcess(void *pvParameters)
{
	AppTimeTaskMsg_t	Msg;

	// ������Ϣ����
	sTime_QueueHandle = xQueueCreate(TIME_TASK_QUEUE_LENGTH, TIME_TASK_QUEUE_SIZE);
	if(sTime_QueueHandle == NULL)
	{
		APP_TIME_RTT_ERR(0,"Time_Queue Create Err \r\n");
	}

	while(1)
	{
		if(xQueueReceive(sTime_QueueHandle, &Msg, portMAX_DELAY))
		{
			switch(Msg.Id)
			{
				case eTimeTaskMsgRTC:
					App_Time_RTCHandler(&Msg);
					break;
				default:
					drERROR_CHECK("App_Time_TaskProcess", Ret_InvalidParam);
					break;
			}
		}
	}
}

void App_Time_TaskEventSet(AppTimeTaskMsg_t* Msg)
{
	 portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	
	if(xPortIsInsideInterrupt() == pdTRUE)    // �ж��Ƿ����ж�
	{
		if(pdPASS != xQueueSendToBackFromISR(sTime_QueueHandle, Msg, &xHigherPriorityTaskWoken))
		{
			APP_TIME_RTT_ERR(0,"App_Time_TaskEventSet Err \r\n");
		}
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	else
	{
		if(pdPASS != xQueueSendToBack(sTime_QueueHandle, Msg, TIME_TASK_QUEUE_WAIT_TICK))
		{
			APP_TIME_RTT_ERR(0,"App_Time_TaskEventSet Err \r\n");
		}
	}
}

void App_Time_TaskCreate(void)
{
    if(pdPASS != xTaskCreate(App_Time_TaskProcess, "TimeTask", TASK_STACKDEPTH_MOD_TIME, NULL, TASK_PRIORITY_MOD_TIME, NULL))
	{
		APP_TIME_RTT_ERR(0,"App_Time_TaskCreate Err \r\n");
	}
}













