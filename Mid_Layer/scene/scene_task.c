
// ģ���ڲ�ͷ�ļ�����
#include "scene_task.h"
#include "scene_interface.h"

// ģ���ⲿͷ�ļ�����
#include "mid_interface.h"
#include "ui_screen_warn.h"
#include "app_protocal.h"

static QueueHandle_t 	sAlgo_QueueHandle = NULL;				// ���о��
#define		ALGO_TASK_QUEUE_LENGTH			5			// 
#define 	ALGO_TASK_QUEUE_WAIT_TICK		100			// ��������ʱ��
#define		ALGO_TASK_QUEUE_SIZE				sizeof(SceneTaskMsg_t)

static void Scene_Task_MagHandler(SceneTaskMsg_t* Msg)
{
	MID_MAG_PARA_T* ltpMagParm;
	
	ltpMagParm = Mid_Mag_ParamPGet();
	
	// �����㷨
	Scene_ABC_CompassAlgorithm(ltpMagParm->LatestData);
}

static void Scene_Task_HrmHandler(SceneTaskMsg_t* Msg)
{
	static uint32_t stCnt = 0;
	Mid_Hrm_Param_t* tMid_Hrm = Mid_Hrm_ParamPGet();;

	switch(Msg->Param.Hrm.Event)
	{
		case eMidHrmEventCalculate:
//			MOD_ALGO_RTT_LOG(0,"eMidHrmEventCalculate %d \r\n", ++stCnt);
//			taskENTER_CRITICAL(); 
			Mid_Hrm_Calculate();
//			taskEXIT_CRITICAL();  	
			break;
		case eMidHrmEventHrmComplete:
			MOD_ALGO_RTT_LOG(0,"eMidHrmEventHrmComplete %d \r\n", ++stCnt);
			Scene_Hrm_SampleComplete();
			break;
		case eMidHrmEventHrvComplete:
			MOD_ALGO_RTT_LOG(0,"eMidHrmEventHrvComplete %d \r\n", ++stCnt);
			Scene_Stress_algorithm( Msg->Param.Hrm.sdnn, 
									Msg->Param.Hrm.rmsd, 
									Msg->Param.Hrm.rri, 
									Msg->Param.Hrm.hr);
			Scene_Stress_SampleComplete();
		
			#if 0	// debug
			Scene_Stress_Param_t*	tSceneStress;
			tSceneStress = Scene_Stress_ParamPGet();
			MOD_ALGO_RTT_ERR(0,"Stress level %d score %d \n", tSceneStress->CurrStress.level, tSceneStress->CurrStress.score);
			#endif
			break;
		case eMidHrmEventHrdErr:
		case eMidHrmEventHrvErr:
			MOD_ALGO_RTT_ERR(0, "eMidHrmEventHrv/dErr \r\n");
			if(eHrmMeasureHrdOnce == tMid_Hrm->MeasureType)	/* ���ǵ��β�����ֹͣ���� */
			{
				Mid_Hrm_Stop();
			}
			Scene_Stress_CurrScoreInvalid();	// �������Ҳ��һ�ֲ������
			break;
		case eMidHrmEventUnwear:
		case eMidHrmEventTimeout:
			MOD_ALGO_RTT_ERR(0, "eMidHrmEventUnwear/Timeout \r\n");	
			if(eHrmMeasureHrdOnce == tMid_Hrm->MeasureType)	/* ���ǵ��β�����ֹͣ���� */
			{
				Mid_Hrm_Stop();			
			}
			// δ���˵����ǰ������Ч
			Scene_Stress_CurrScoreInvalid();
			// δ���Ҳ��һ�ֲ�����������ǲ���ֵΪ��Чֵ
			Scene_Hrm_SampleComplete();
			Scene_Stress_SampleComplete();				
			break;
		default: break;
	}
}

static void Scene_Task_PressureHandler(SceneTaskMsg_t* Msg)
{
	#if 0
	MID_PRESS_PARA_T*	tpPressPara;
	
	tpPressPara = Mid_Press_ParamPGet();
	MID_SCHD_RTT_LOG(0, "Scene_Task_PressureHandler, Temp %d, Press %d \r\n", tpPressPara->LastTemp, tpPressPara->LastPress);	
	#endif
	
	#if 0	/* ������ѹ�㷨��ÿ��̶�����һ�� */
	Scene_ABC_ABalgorithm();	
	
	ab_value_t          tab_value;
	Scene_ABC_ABGet(&tab_value);
	MID_SCHD_RTT_LOG(0, "Scene_ABC_ABGet, altitude %d, pressure %d, seaLevel %d \n", tab_value.altitude, tab_value.pressure, tab_value.seaLevel);
	#endif
}

static void Scene_CountDown_EventProcess(CountDownEvent_t* Event_t)
{
	switch (Event_t->Id)
	{
		case eCountDownEventTimeOut:
			UI_Screen_Show_Warn_Screen_Timer();
			Mid_Motor_ShakeStart(eMidMotorShake2Hz, 5);
			break;
		default:
			break;
	}
}

void Scene_Findphone_EventProcess(FindphoneEvent_t* Event_t)
{
	switch(Event_t->Id)
	{
		case eFindphoneEventTimerCb:
			App_Protocal_FinePhone();
			break;
		default:
			break;	
	}
}

void Scene_6Dof_EventProcess(void)
{
	struct bmi160_sensor_data lAccData[30];
	struct bmi160_sensor_data lGyrData[30];
	uint8_t lAccLen = 30;
	uint8_t lGyrLen = 30;
	Mid6DofParam_t* lp6DofParam = Mid_6Dof_ParamPGet();

	if(Ret_OK == Mid_6Dof_FIFORead(lAccData, &lAccLen, lGyrData, &lGyrLen))
	{
		/** ���ٶȴ��� */
		if(40 == lp6DofParam->Acc.SamplePeriod)
		/** 25Hz�������������ݾ����� */
		{
			for (uint32_t i = 0; i < lAccLen; i++) 
			{
//				MOD_ALGO_RTT_LOG(0, "[%d] %d %d %d \n", i, lAccData[i].x, lAccData[i].y, lAccData[i].z);

				Mid_Hrm_AccelMenSet(&lAccData[i].x);										// ��������Gsensor����
				
				Scene_Step_Algorithm(&lAccData[i].x, lp6DofParam->Acc.SamplePeriod);		// �Ʋ��㷨����
				
				Scene_Sleep_algorithm(&lAccData[i].x, lp6DofParam->Acc.SamplePeriod);		// ˯���㷨����
				
				Scene_Gesture_algorithm(&lAccData[i].x, lp6DofParam->Acc.SamplePeriod);		// ����ʶ���㷨����
				
				Scene_Sedentary_algorithm(&lAccData[i].x, lp6DofParam->Acc.SamplePeriod);	// �����㷨����
				
				Scene_Swim_Algorithm(&lAccData[i].x, eSceneSwimAlgoGsenser);								// ��Ӿ�㷨
			}			
		}
		else if(1000 == lp6DofParam->Acc.SamplePeriod)
		/** ��Ϊappÿ���ȡһ��FIFO���ݣ�����1Hz����ʱֻȡ��һ������ */
		{
		
		}
		
		/** ���ٶȴ��� */
		if(40 == lp6DofParam->Gyr.SamplePeriod)
		{
//			for (uint32_t i = 0; i < lGyrLen; i++) 
//			{
//				MID_6DOF_RTT_LOG(0, "[%d] %d %d %d \n", i, lGyrData[i].x, lGyrData[i].y, lGyrData[i].z);
//			}			
		}
	}
}

static void Scene_Task_TaskProcess(void *pvParameters)
{
	SceneTaskMsg_t	Msg;

	// ������Ϣ����
	sAlgo_QueueHandle = xQueueCreate(ALGO_TASK_QUEUE_LENGTH, ALGO_TASK_QUEUE_SIZE);
	if(sAlgo_QueueHandle == NULL)
	{
		MOD_ALGO_RTT_ERR(0,"Algo_Queue Create Err \r\n");
	}

	while(1)
	{
		if(xQueueReceive(sAlgo_QueueHandle, &Msg, portMAX_DELAY))
		{
			switch (Msg.Id)
            {
				case eAlgoTaskMsgMagnetism:
					Scene_Task_MagHandler(&Msg);
					break;
				case eAlgoTaskMsgGPS:
					break;
				case eAlgoTaskMsgHrm:
					Scene_Task_HrmHandler(&Msg);
					break;
				case eAlgoTaskMsgPressure:
					Scene_Task_PressureHandler(&Msg);
					break;
				case eSceneTaskMsgCountdown:
					Scene_CountDown_EventProcess(&Msg.Param.Countdown);
					break;
				case eSceneTaskMsgFindphone:
					Scene_Findphone_EventProcess(&Msg.Param.Findphone);
					break;
				case eAlgoTaskMsg6Dof:
					Scene_6Dof_EventProcess();
					break;
            	default:
					drERROR_CHECK("Scene_Task_TaskProcess", Ret_InvalidParam);
            		break;
            }
		}
	}
}

void Scene_Task_TaskEventSet(SceneTaskMsg_t* Msg)
{
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

    //fix: ��ֹ��queue����֮ǰ��call�˺�������������
    if(sAlgo_QueueHandle == NULL)
        return ;

	if(xPortIsInsideInterrupt() == pdTRUE)    // �ж��Ƿ����ж�
	{
		if(pdPASS != xQueueSendToBackFromISR(sAlgo_QueueHandle, Msg, &xHigherPriorityTaskWoken))
		{
			MOD_ALGO_RTT_ERR(0,"Scene_Task_TaskEventSet Err \r\n");
		}
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	else
	{
		if(pdPASS != xQueueSendToBack(sAlgo_QueueHandle, Msg, ALGO_TASK_QUEUE_WAIT_TICK))
		{
			MOD_ALGO_RTT_ERR(0,"Scene_Task_TaskEventSet Err \r\n");
		}
	}
}

void Scene_Task_TaskCreate(void)
{
    if(pdPASS != xTaskCreate(Scene_Task_TaskProcess, "AlgoTask", TASK_STACKDEPTH_MOD_ALGO, NULL, TASK_PRIORITY_MOD_ALGO, NULL))
	{
		MOD_ALGO_RTT_ERR(0,"Scene_Task_TaskCreate Err \r\n");
	}
}

