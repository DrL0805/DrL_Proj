#include "mid_infrared_temp.h"
#include "drv_bm43.h"
#include "mid_interface.h"

Mid_IT_Param_t	Mid_IT;

static TimerHandle_t 	Mid_IT_TimerHandle;

static void Mid_IT_TimerCallBack(TimerHandle_t xTimer)
{
	Mid_Schd_TaskMsg_T Msg;
	
	Msg.Id = eSchdTaskMsgITemp;
	Msg.Param.ITemp.Id = eITempEventDataUpdate;
	Mid_Schd_TaskEventSet(&Msg);	
}


void Mid_IT_Init(void)
{
    Mid_IT_TimerHandle=xTimerCreate((const char*		)"MID_IT_Timer",
									    (TickType_t			)(1000),
							            (UBaseType_t		)pdFALSE,
							            (void*				)1,
							            (TimerCallbackFunction_t)Mid_IT_TimerCallBack);		
	
	Drv_BM43_init();
	Mid_IT.InitFlg = true;
}


void Mid_IT_ConverStart(void)
{
	Drv_BM43_Open();
	bm43_conversion_start();
	Drv_BM43_Close();
	
	xTimerStart(Mid_IT_TimerHandle,3);
	
	Mid_IT.UpdateFlg = false;
}

void Mid_IT_ConverStop(void)
{
	Drv_BM43_Open();
	bm43_conversion_stop();
	Drv_BM43_Close();	
	
	xTimerStop(Mid_IT_TimerHandle,3);
}

void Mid_IT_TempCal(void)
{
	Drv_BM43_Open();
	Mid_IT.CurrTemp = bm43_calculate_temp();
	Drv_BM43_Close();
	
	Mid_IT.UpdateFlg = true;

	MID_IT_RTT_LOG(0, "Mid_IT_TempCal %d \n", Mid_IT.CurrTemp);
	
	// 马达震动提示测量完成
	Mid_Motor_ShakeStart(eMidMotorShake1Hz, 1);
}

Mid_IT_Param_t* Mid_IT_ParamPGet(void)
{
	return &Mid_IT;
}

void Mid_IT_Test(void)
{
	MID_IT_RTT_LOG(0, "Mid_IT_Test \n");
	
	
	
	#if 0

	Drv_BM43_SelfTest();
	#endif
	
	#if 0
	MID_IT_RTT_LOG(0, "Mid_IT_Test \n");
	
	Mid_IT_ConverStart();
	vTaskDelay(50);
//	Mid_IT_ConverStop();
	Mid_IT_TempCal();
	
	MID_IT_RTT_LOG(0, "Mid_IT.CurrTemp %d \n", Mid_IT.CurrTemp);
	#endif
}











