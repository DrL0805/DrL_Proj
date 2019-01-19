
#include "app_time.h"

#include "mid_interface.h"
#include "scene_interface.h"
#include "store_interface.h"
#include "app_variable.h"
#include "app_protocal.h"
#include "app_systerm.h"
#include "ui_screen_warn.h"


static QueueHandle_t 	sTime_QueueHandle;				// 队列句柄
#define		TIME_TASK_QUEUE_LENGTH			3			// 
#define 	TIME_TASK_QUEUE_WAIT_TICK		100			// 队列阻塞时间
#define		TIME_TASK_QUEUE_SIZE				sizeof(AppTimeTaskMsg_t)

/*******************************************************************************
 * Brief : 检测是否在勿扰时间段内
 * Input : @NULL 
 * Return: 0 当前非勿扰时间段，1 当前处于勿扰时间段
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

// RTC每秒调用事件处理
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
	
	/* 每秒检测是否需要人体压力后台采样，
	人体压力要放在心率前面，因为人体压力测量结果包含心率 */
	Scene_Stress_BGSampleCheck();
	
	/* 每秒检测是否需要心率后台采样 */
	Scene_Hrm_BGSampleCheck();
	
	// 每秒检测心率佩戴和算法超时情况
	Mid_Hrm_UnwearCheck();
	Mid_Hrm_TimeoutCheck();
	
	// 每秒调用一次计步运动时长算法
	Scene_Step_DuarationAlgo();
	
	// 每秒调用一次爬楼梯算法
	Scene_Stair_Algorithm();
	
	/* 每秒调用一次跑步算法 */
	Scene_Run_Algorithm();
	
	/* 每秒调用一次登山算法 */
	Scene_Climb_Algorithm();
	
	/* 每秒调用一次游泳算法 */
	Scene_Swim_Algorithm(NULL, eSceneSwimAlgoHr);

    //每秒检测一次充电状态
	Msg.Id = eSchdTaskMsgBat;
	Msg.Param.Bat.Id = eBatEventChargCheck;
	Mid_Schd_TaskEventSet(&Msg);
	#if 0	// debug，打印电量百分比
	uint8_t lBatVal = 0;
	Mid_Bat_SocRead(&lBatVal);
	MID_SCHD_RTT_LOG(0, "Mid_Bat_SocRead %d \n", lBatVal);
	#endif
    
	/* 每秒一次海拔气压算法，即使没更新气压数据，也要每秒调用一次 */
	Scene_ABC_ABalgorithm();
	
	/** 每秒读取一次六轴FIFO数据 */
	SceneTaskMsg_t 	tAlgoMsg;			
	tAlgoMsg.Id = eAlgoTaskMsg6Dof;
	Scene_Task_TaskEventSet(&tAlgoMsg);
	
	//有与手机强关联状态
	if (gtPhoneState.state != PHONE_STATE_NORMAL)
	{
		gtPhoneState.timeCnt++;

		if (gtPhoneState.timeCnt > gtPhoneState.timeMax)
		{
			switch(gtPhoneState.state)
			{
				case PHONE_STATE_PHOTO:	// 拍照
					UI_Screen_Close_Warn_Screen_Camera();
					APP_TIME_RTT_LOG(0,"PHONE_STATE_PHOTO TimeOut \r\n");		// 
					break;
				case PHONE_STATE_AUTHOR:
					APP_TIME_RTT_LOG(0,"PHONE_STATE_AUTHOR TimeOut \r\n");		// 授权超时
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

// RTC每分钟调用事件处理
static void App_Time_RTCMinHandler(void)
{
	SceneAlarmParam_t* ltpAlarmParam;
	Mid_Schd_TaskMsg_T Msg;
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();

	if(0 == (lMidRTC->RTC.min % SCENE_HRM_REST_ALGO_PERIOD))
	/* 静息心率算法 */
	{
		Scene_Hrm_RestAlgo();
	}
	
	if(0 == (lMidRTC->RTC.min % 10))
	/* 每10min开启一次后台心率测量 */	
	{
		Scene_Stress_SampleStart(eSceneMeasureBG);
	}
	
	if(0 == (lMidRTC->RTC.min % 2))
	/* 每2min开启一次后台心率测量 */	
	{
		Scene_Hrm_SampleStart(eSceneMeasureBG);
	}

	if(0 == (lMidRTC->RTC.min % 5))
	/* 每5min存储一次计步累加值 */	
	{
		Store_Step_algorithm();
	}
	
	if(0 == (lMidRTC->RTC.min % 2))
	/* 每2分钟存储一次AB值 */	
	{
		Store_ABC_algorithm();
	}

	if(0 == (lMidRTC->RTC.min % 5))
	/* 每5分钟检测一次电量 */	
	{
		Msg.Id = eSchdTaskMsgBat;
		Msg.Param.Bat.Id = eBatEventBatCheck;
		Mid_Schd_TaskEventSet(&Msg);	
	}

	if(Scene_Alarm_Check())
	/** 每min检测一次闹钟 */ 	
	{
		if (gtPhoneState.state != PHONE_STATE_PHOTO)
		/** 拍照状态不触发闹钟 */
		{
			// 向APP发送闹钟事件
			ltpAlarmParam = Scene_Alarm_ParamPGet();
			App_Protocal_AlarmRing(ltpAlarmParam->curRingAlarmId);
			
			// 向APP层发送闹钟事件
			UI_Screen_Show_Warn_Screen_Alarm();
			Mid_Motor_ShakeStart(eMidMotorShake2Hz, 10);			
		}
	}
}

// RTC每小时调用事件处理
static void App_Time_RTCHourHandler(void)
{
	// 每小时更新一次用于UI的计步数据
	Store_Step_UIDataUpdate();
	
	// 每小时向APP获取天气信息
    if(geBleState == BLE_CONNECT)
    {
       App_Protocal_GetWeatherProcess();
    }
}

// RTC每天调用事件处理
static void App_Time_RTCDayHandler(void)
{
	// 每天同步RTC时间
    if (geBleState == BLE_CONNECT)
    {
        App_Protocal_AdjustTimeprocess();
    }
	
	// 每天清空计步信息
	Scene_Step_Clear();
	
	// 每天清空爬楼梯数据
	Scene_Stair_Clear();
	
	// 每天零点上一天睡眠数据，并保持到FLASH中
	Scene_Sleep_Clear();
	Store_Sleep_CatalogSeal();
}

//**********************************************************************
// 函数功能: 按键调度任务处理函数
// 输入参数：
// 返回参数：
static void App_Time_RTCHandler(AppTimeTaskMsg_t*	Msg)
{
	if(eAppSysStateStore == App_Sys_StateGet())
	/* 当前处于仓储模式，直接退出，用于功耗测试 */
	{
		if(eMidRTCMsgSec == Msg->Param.RTC.Msg)
		/* 1Hz测试项 */
		{
//			Mid_Bat_Test();	// 电池电量采集测试
//			Mid_NandFlash_Test();	// nandflash 擦写读测试
//			Mid_Front_Test();		// 字库读取测试
//			Mid_Press_Test();
//			Mid_IT_ConverStart();
			
//			Mid_Press_ContinuousCvtCheck();
		}
		
//		return;
	}

	Mid_WDT_ReStart();
	Mid_Lcd_ExtcominTog();
	Drv_Touch_IdleTimeoutCheck();	// TP休眠超时检测
	
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
//	以下是任务调度代码
// ***********************************************************************
static void App_Time_TaskProcess(void *pvParameters)
{
	AppTimeTaskMsg_t	Msg;

	// 创建消息队列
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
	
	if(xPortIsInsideInterrupt() == pdTRUE)    // 判断是否在中断
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













