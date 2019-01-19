/**********************************************************************
**
**模块说明: mid层心率接口
**软件版本，修改日志(时间，内容),修改人:
**   V1.0   2018.4.25  修改流程  ZSL  
**
心率计场景逻辑
测量内容：心率
		  压力
测量场景：即时测量，如进入心率界面，需要即时测量一次心率值，给用户看
		  后台测量，如每2min测量一次心率值，并保持在FLASH中
		  持续测量，如跑步场景，需一直打开心率测量

优先级打断原则：高优先级可以打断低优先级
测量优先级，  持续 > 即时 > 后台

心率测量场景：
心率场景，包括即时测量、后台测量、持续测量
每2min后台测量计数值Cnt++，每秒检测Cnt值，Cnt非零时开启后台测量，测量结果保存在LogBuf中，测量完成后Cnt--
后台测量不可打断即时测量，但即时测量可以打断后台测量，当后台测量被即时测量打断时，有两种情况：
情况1：即时测量有效，则本次即时测量结果也作为后台测量结果，后台Cnt--；
情况2：即时测量无效，则当即时测量结束（关闭）后，每秒检测重新开启后台测量

若当前状态为即时测量，
	后台心率测量：为当前测量值
	后台压力测量：无效

压力测量场景：同心率


**********************************************************************/
#include "mid_hrm.h"
#include "scene_task.h"
#include "scene_stress.h"

#define SystermTickPeriod           (1000/APP_1SEC_TICK)      //TICK时钟周期

Mid_Hrm_Param_t		Mid_Hrm = 
	{
		.InitFlg = false,
		.State = eMidHrmStateIdle,
		.CurrHeartRate = HRM_INVALID_VALUE,
		.LastHeartRate = HRM_INVALID_VALUE,
	};

/*********************************************************************
 * Brief : 心率IO口中断回调函数，当心率计产生IO中断时，回调此函数。
	       上层通过IO中断类型，进行相应处理
 * Input : @event 中断类型 
 * Return: @NULL
 * Call  : Drv_Hrm_Open()函数调用，设置回调函数
 ************/	
static void Mid_Hrm_IOIsrCb(hrm_event event)
{
	SceneTaskMsg_t 	tAlgoMsg;
	
    if(event == HR_TOUCH)
    {
//		MID_HRM_RTT_LOG(0,"HR_TOUCH \r\n");	// 调用触摸函数，暂时没做处理		
    }
    else if(event == HR_DATA_READY)
    {
//		MID_HRM_RTT_LOG(0,"HR_DATA_READY \r\n");
	
		// 通知算法模块进行心率计算，尽量减少中断回调函数处理时间
		tAlgoMsg.Id = eAlgoTaskMsgHrm;
		tAlgoMsg.Param.Hrm.Event = eMidHrmEventCalculate;
		Scene_Task_TaskEventSet(&tAlgoMsg);		
    }
}

/*********************************************************************
 * Brief : 心率计算完成回调函数
 * Input : @hrmval 测量的心率值 
 * Return: @NULL
 * Call  : 
 ************/
static void Mid_Hrm_CalculateCompleteCb(uint8 hrmval)
{
	SceneTaskMsg_t 	tAlgoMsg;
	
    Mid_Hrm.CurrHeartRate     = hrmval;

    if (Mid_Hrm.CurrHeartRate >240)
    {
        Mid_Hrm.CurrHeartRate = 240;
    }
    else if (Mid_Hrm.CurrHeartRate < 30)
    {
        Mid_Hrm.CurrHeartRate = 30;
    }
	
	Mid_Hrm.HrUpdateFlg = true;
	Mid_Hrm.LastHeartRate = Mid_Hrm.CurrHeartRate;	// 更新心率值
	
	// 不能在中断调用心率停止函数，否则下次测量不正常，原因是底层回调函数位置不允许
//	Mid_Hrm_Stop();
	tAlgoMsg.Id = eAlgoTaskMsgHrm;
	tAlgoMsg.Param.Hrm.Event = eMidHrmEventHrmComplete;
	Scene_Task_TaskEventSet(&tAlgoMsg);		
	
	MID_HRM_RTT_LOG(0,"Mid_Hrm_CalculateCompleteCb %d \r\n", Mid_Hrm.LastHeartRate);
}

/*********************************************************************
 * Brief : 人体压力计算完成回调函数
 * Input : 
 * Return: @NULL
 * Call  : 
 ************/
static void Mid_Hrv_CalculateCompleteCb(float sdnn, float rmsd, float rri, uint8_t hr)
{
	SceneTaskMsg_t 	tAlgoMsg;

	tAlgoMsg.Id = eAlgoTaskMsgHrm;
	tAlgoMsg.Param.Hrm.Event = eMidHrmEventHrvComplete;
	tAlgoMsg.Param.Hrm.sdnn = sdnn;
	tAlgoMsg.Param.Hrm.rmsd = rmsd;
	tAlgoMsg.Param.Hrm.rri= rri;
	tAlgoMsg.Param.Hrm.hr= hr;
	Scene_Task_TaskEventSet(&tAlgoMsg);		
	
	MID_HRM_RTT_LOG(0,"Mid_HrvCb sdnn %d, rmsd %d, rri %d, hr %d \r\n", (uint32_t)sdnn, (uint32_t)rmsd, (uint32_t)rri, hr);
}

/*********************************************************************
 * Brief : 心率计算错误回调函数
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ************/
static void Mid_Hrm_CalculateErrCb(void)
{
	MID_HRM_RTT_LOG(0,"Mid_Hrm_CalculateErrCb \n");
	
	SceneTaskMsg_t 	tAlgoMsg;
	
	tAlgoMsg.Id = eAlgoTaskMsgHrm;
	tAlgoMsg.Param.Hrm.Event = eMidHrmEventHrdErr;
	Scene_Task_TaskEventSet(&tAlgoMsg);	
}

/*********************************************************************
 * Brief : 人体压力计算错误回调函数
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ************/
static void Mid_Hrv_CalculateErrCb(void)
{
	MID_HRM_RTT_LOG(0,"Mid_Hrv_CalculateErrCb \n");
	
	SceneTaskMsg_t 	tAlgoMsg;
	
	tAlgoMsg.Id = eAlgoTaskMsgHrm;
	tAlgoMsg.Param.Hrm.Event = eMidHrmEventHrvErr;
	Scene_Task_TaskEventSet(&tAlgoMsg);		
}

/*********************************************************************
 * Brief : 存储心率算法重力数据
 * Input : @fifodata 重力数据指针,三轴数据各一
 * Return: @NULL
 * Call  : 25Hz频率调用，传入Gsensor数据
 ************/
void Mid_Hrm_AccelMenSet(int16 *fifodata)
{
//    uint16     hrmAccelRate;
	
    //检测重力计量程并实现更新
//    Mid_Accel_SettingRead(&hrmAccelRate, &hrmAccelRange);
//    Drv_Hrm_SetAccelRange(hrmAccelRange);//获取当前的重力计配置更新给心率模块 
	Drv_Hrm_SetAccelRange(0);// 2g, 这版本算法好像没有设置Gsensor范围的接口
    Drv_Hrm_SetAccelMen(fifodata,3);
}

/*********************************************************************
 * Brief : 心率算法启动，注意心率和人体压力互斥，重复开启无效
 * Input : @Type 算法类型，心率or人体压力
 * Output: @NULL 
 * Return: 函数执行结果
 * Call  : 
 ************/
void Mid_Hrm_Start(eHrmMeasuretype Type)
{
	if(!Mid_Hrm.InitFlg) drERROR_CHECK_RETURN_NULL("Mid_Hrm_Start", Ret_NoInit);
	if(eMidHrmStateIdle != Mid_Hrm.State) drERROR_CHECK_RETURN_NULL("Mid_Hrm_Start", Ret_DeviceBusy);
	
	MID_HRM_RTT_LOG(0, "Mid_Hrm_Start %d \n", Type);	
	
	Drv_Hrm_MeasureTypeSet(Type);
	Drv_Hrm_Open(Mid_Hrm_IOIsrCb);
	Drv_Hrm_Start();
	
	Mid_Hrm.HrUpdateFlg = false;
	Mid_Hrm.UnwearCnt = 0;
	Mid_Hrm.TimeoutCnt = 0;
	Mid_Hrm.State = eMidHrmStateMeasuring;
	Mid_Hrm.MeasureType = Type;
}

/*********************************************************************
 * Brief : 心率算法关闭
 * Input : @NULL
 * Output: @NULL 
 * Return: 
 * Call  : 
 ************/
void Mid_Hrm_Stop(void)
{
	if(!Mid_Hrm.InitFlg) drERROR_CHECK_RETURN_NULL("Mid_Hrm_Stop", Ret_NoInit);	
	
	MID_HRM_RTT_LOG(0, "Mid_Hrm_Stop \r\n");
	
	Drv_Hrm_Stop();
	Drv_Hrm_Close();
	
	Mid_Hrm.UnwearCnt = 0;
	Mid_Hrm.State = eMidHrmStateIdle;
}

/*********************************************************************
 * Brief : 心率计算
 * Input : @NULL
 * Output: @NULL 
 * Return: 函数执行结果
 * Call  : 
 ************/
void Mid_Hrm_Calculate(void)
{
	MID_HRM_RTT_LOG(0, "Mid_Hrm_Calculate %d \n", SystermTickPeriod * xTaskGetTickCount());
	Drv_Hrm_Calculate(SystermTickPeriod * xTaskGetTickCount());
}

/*********************************************************************
 * Brief : 心率未佩戴检测，若检测到超时未佩戴，发送未佩戴事件
 * Input : @NULL
 * Return: 
 * Call  : 每秒调用一次
 ************/
void Mid_Hrm_UnwearCheck(void)
{
	SceneTaskMsg_t 	tAlgoMsg;
	uint8_t tTouchState;
	
	if(eMidHrmStateMeasuring == Mid_Hrm.State)
	{
		switch (Mid_Hrm.MeasureType)
        {
        	case eHrmMeasureHrdOnce:
        	case eHrmMeasureHrvOnce:
				Drv_Hrm_ReadTouchStatus(&tTouchState);
				if(OFF_TOUCH == tTouchState)
				{
					if(++Mid_Hrm.UnwearCnt >= HRM_UNWEAR_TIMEOUT)
					{
		//				MID_HRM_RTT_LOG(0, "eMidHrmStateUnwear \r\n");
						
						// 未佩戴依然心率可读，但心率值无效
						Mid_Hrm.HrUpdateFlg = true;
						Mid_Hrm.CurrHeartRate = HRM_INVALID_VALUE;
						
						// 发送未佩戴事件
						tAlgoMsg.Id = eAlgoTaskMsgHrm;
						tAlgoMsg.Param.Hrm.Event = eMidHrmEventUnwear;
						Scene_Task_TaskEventSet(&tAlgoMsg);
					}
				}
				else
				{
					Mid_Hrm.UnwearCnt = 0;
				}
        		break;
			case eHrmMeasureHrdKeep:	// 持续测量不检测未佩戴
        	case eHrmMeasureHrvKeep:
				break;
        	default :
        		break;
        }
	}
}

/*********************************************************************
 * Brief : 心率算法超时检测，若检测到超时则发送超时事件
 * Input : @NULL 
 * Return: 
 * Call  : 每秒调用一次
 ************/
void Mid_Hrm_TimeoutCheck(void)
{
	SceneTaskMsg_t 	tAlgoMsg;
	
	if(eMidHrmStateMeasuring == Mid_Hrm.State)
	{
		Mid_Hrm.TimeoutCnt++;
		switch (Mid_Hrm.MeasureType)
        {
        	case eHrmMeasureHrdOnce:
				if(Mid_Hrm.TimeoutCnt >= 30)
				{
					MID_HRM_RTT_LOG(0, "Mid_Hrm_TimeoutCheck Hrd \n");

					// 未佩戴依然心率可读，但心率值无效
					Mid_Hrm.HrUpdateFlg = true;
					Mid_Hrm.CurrHeartRate = HRM_INVALID_VALUE;
					
					// 发送未佩戴事件
					tAlgoMsg.Id = eAlgoTaskMsgHrm;
					tAlgoMsg.Param.Hrm.Event = eMidHrmEventTimeout;
					Scene_Task_TaskEventSet(&tAlgoMsg);			
				}
        		break;
        	case eHrmMeasureHrvOnce:
				if(Mid_Hrm.TimeoutCnt >= 90)
				{
					MID_HRM_RTT_LOG(0, "Mid_Hrm_TimeoutCheck Hrv \n");

					// 未佩戴依然心率可读，但心率值无效
					Mid_Hrm.HrUpdateFlg = true;
					Mid_Hrm.CurrHeartRate = HRM_INVALID_VALUE;
					
					// 发送未佩戴事件
					tAlgoMsg.Id = eAlgoTaskMsgHrm;
					tAlgoMsg.Param.Hrm.Event = eMidHrmEventTimeout;
					Scene_Task_TaskEventSet(&tAlgoMsg);						
				}
        		break;
			case eHrmMeasureHrdKeep:	// 持续测量不检测超时
        	case eHrmMeasureHrvKeep:
				break;
        	default :
        		break;
        }
	}
}

/*********************************************************************
 * Brief : 心率模块初始化
 * Input : @NULL
 * Output: @NULL 
 * Return: @NULL
 * Call  : 
 ************/
void Mid_Hrm_Init(void)
{
	Drv_Hrm_MeasureTypeSet(eHrmMeasureHrdOnce);	// 默认初始化测量心率
    Drv_Hrm_Open(Mid_Hrm_IOIsrCb);			//硬件初始化并配置心率模块
    Drv_Hrm_Close();						//硬件低功耗配置
	
	// 测量完成回调函数
    Drv_Hrm_SetCalCompleteCb(Mid_Hrm_CalculateCompleteCb);
	Drv_Hrv_SetCalCompleteCb(Mid_Hrv_CalculateCompleteCb);
	
	// 测量错误回调函数
	Drv_Hrm_SetCalErrCb(Mid_Hrm_CalculateErrCb);
	Drv_Hrv_SetCalErrCb(Mid_Hrv_CalculateErrCb);
	
	Mid_Hrm.InitFlg = true;
}

/*********************************************************************
 * Brief : 触摸状态获取
 * Input : @ui8istouch 是否佩戴  OFF_TOUCH未佩戴，ON_TOUCH佩戴
 * Return: 
 * Call  : 未用到
 ************/
void Mid_Hrm_TouchStatusRead(uint8 *ui8istouch)
{
	Drv_Hrm_ReadTouchStatus(ui8istouch);
}

Mid_Hrm_Param_t* Mid_Hrm_ParamPGet(void)
{
	return &Mid_Hrm;
}

/*********************************************************************
 * Brief : 心率模块漏光测试数据获取
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ************/
uint16 Mid_Hrm_FactoryTestRead(uint16 ui16lightleak[3])              
{
    uint16 ret;

    ret = Drv_Hrm_FactoryTest(ui16lightleak);

    return ret;
}

/*********************************************************************
 * Brief : 心率模块工厂测试
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ************/
uint8 Mid_Hrm_FactoryTest(void)
{
    uint8 u8Ret;
    Drv_Hrm_Open(Mid_Hrm_IOIsrCb);
    vTaskDelay(10);
    u8Ret = Drv_Hrm_CheckHw();
    Drv_Hrm_Close();
    return u8Ret;
}

void Mid_Hrm_Test(void)
{
	MID_HRM_RTT_LOG(0, "Mid_Mag_Test \n");
	
	#if 1 // 功耗测试
	static uint8_t lEnableFlg = false;
	
	if(lEnableFlg)
	{
		lEnableFlg = false;
		Mid_Hrm_Stop();
	}
	else
	{
		lEnableFlg = true;
		Mid_Hrm_Start(eHrmMeasureHrdKeep);	// 需关闭心率算法加速度宏 ENABLE_MEMS_ZERO
	}
	#endif
}




