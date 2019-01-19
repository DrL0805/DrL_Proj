
#include "mid_pressure.h"
#include "mid_scheduler.h"

#define	PRESS_TIMER_PERIOD_MS		(pdMS_TO_TICKS(500))	

static TimerHandle_t 	Press_TimerHandle;
static MID_PRESS_PARA_T	MID_PRESS;

static void Press_TimerCallBack(TimerHandle_t xTimer)
{
	Mid_Schd_TaskMsg_T Msg;
	
	Msg.Id = eSchdTaskMsgPressure;
	Msg.Param.Pressure.Id = ePressEventDataUpdate;
	Mid_Schd_TaskEventSet(&Msg);
}

void Mid_Press_ParamSet(AirpressOSR_e Osr, eMidPressSampleType SampleType)
{
	MID_PRESS.Osr = Osr;
	MID_PRESS.SampleType = SampleType;
}

//**********************************************************************
// 函数功能：开始一次气压/温度采集
// 输入参数：
// 返回参数：
void Mid_Press_PressStart(void)
{
	Drv_AirPress_EnableIO();
	switch(MID_PRESS.SampleType)
    {
    	case eMidPressSampleTemp:
//			Drv_AirPress_TempCvtParaConfig(MID_PRESS.Osr, MID_PRESS.Mr);
			Drv_AirPress_TempSingleCvt();
    		break;
    	case eMidPressSamplePress:
//			Drv_AirPress_PressCvtParaConfig(MID_PRESS.Osr, MID_PRESS.Mr);
			Drv_AirPress_PressSingleCvt();
    		break;
		case eMidPressSampleTempPress:
//			Drv_AirPress_TempCvtParaConfig(MID_PRESS.Osr, MID_PRESS.Mr);
//			Drv_AirPress_PressCvtParaConfig(MID_PRESS.Osr, MID_PRESS.Mr);
			Drv_AirPress_TemPressContinuousCvt();
			MID_PRESS.ContinuousCvtFlg = true;
			break;
    	default:
    		break;
    }
	Drv_AirPress_DisableIO();	

	// 采集定时器，定时器超时说明采集成功，可读取新的数据
	xTimerChangePeriod(Press_TimerHandle, PRESS_TIMER_PERIOD_MS, 3);
}

void Mid_Press_Stop(void)
{
	Drv_AirPress_EnableIO();
	Drv_AirPress_Standby();
	Drv_AirPress_DisableIO();
}

//**********************************************************************
// 函数功能：	读取一次硬件数据并更新，等待有需要的外设来获取
// 输入参数：	
// 返回参数：
void Mid_Press_TempUpdate(void)
{
	Drv_AirPress_EnableIO();
	
	if(Ret_OK != Drv_AirPress_ReadTemp(&MID_PRESS.LastTemp))
	{
		MID_PRESS_RTT_WARN(0, "Drv_AirPress_ReadTemp ERR \n");
	}		
	MID_PRESS.TempUpdateFlg = true;
	
	Drv_AirPress_DisableIO();
	
	#if 1	// debug
	MID_PRESS_RTT_LOG(0, "Mid_Press_TempUpdate %d \n", MID_PRESS.LastTemp);
	#endif		
}

//**********************************************************************
// 函数功能：读取一次硬件数据并更新，等待有需要的外设来获取
// 输入参数：	
// 返回参数：
void Mid_Press_PressUpdate(void)
{
	Drv_AirPress_EnableIO();
	
	Drv_AirPress_ReadPress(&MID_PRESS.LastPress);
	MID_PRESS.PressUpdateFlg = true;
	
	Drv_AirPress_DisableIO();
	
	#if 1	// debug
	MID_PRESS_RTT_LOG(0, "Mid_Press_PressUpdate %d \n", MID_PRESS.LastPress);
	#endif	
}

MID_PRESS_PARA_T* Mid_Press_ParamPGet(void)
{
	return &MID_PRESS;
}

uint16_t Mid_Press_Init(void)
{
	uint16_t RetVal = 0xFF;
	
	if(MID_PRESS.InitedFlg)
		return Ret_Fail;
	
    Press_TimerHandle=xTimerCreate((const char*		)"Press_Timer",
									    (TickType_t			)(PRESS_TIMER_PERIOD_MS),
							            (UBaseType_t		)pdFALSE,
							            (void*				)1,
							            (TimerCallbackFunction_t)Press_TimerCallBack);										

	// 默认采样参数
//	Mid_Press_ParamSet(eAirpressOSR_128, eMidPressSampleTempPress);
	MID_PRESS.Osr = eAirpressOSR_128;
	MID_PRESS.Mr = eAirpressMR_1;
	MID_PRESS.SampleType = eMidPressSampleTempPress;

	MID_PRESS.PressUpdateFlg = false;
	MID_PRESS.TempUpdateFlg = false;
	MID_PRESS.InitedFlg = true;											

	Drv_AirPress_EnableIO();
	if(Ret_OK != Drv_AirPress_Init())
	{
		MID_PRESS_RTT_ERR(0, "Drv_AirPress_Init ERR %d \n", RetVal);
	}
	
	Drv_AirPress_TempCvtParaConfig(MID_PRESS.Osr, MID_PRESS.Mr);
	Drv_AirPress_PressCvtParaConfig(MID_PRESS.Osr, MID_PRESS.Mr);	
	Drv_AirPress_DisableIO();

	return RetVal;
}

uint16 Mid_Press_SelfTest(void)
{
	uint16_t RetVal = 0xFF;
	
	RetVal = Drv_AirPress_SelfTest();
	
	return RetVal;
}


void Mid_Press_Test(void)
{
	#if 1	// 气压环温
	Mid_Schd_TaskMsg_T Msg;
	
	Msg.Id = eSchdTaskMsgPressure;
	Msg.Param.Pressure.Id = ePressEventStartSample;
	Mid_Schd_TaskEventSet(&Msg);	
	#endif
}

void Mid_Press_ContinuousCvtCheck(void)
{
	if(MID_PRESS.ContinuousCvtFlg)
	{
		Mid_Schd_TaskMsg_T Msg;
		
		Msg.Id = eSchdTaskMsgPressure;
		Msg.Param.Pressure.Id = ePressEventDataUpdate;
		Mid_Schd_TaskEventSet(&Msg);	
	}
}









