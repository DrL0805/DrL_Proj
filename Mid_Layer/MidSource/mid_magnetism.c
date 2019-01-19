#include "drv_mtimer.h"
#include "mid_magnetism.h"
#include "mid_scheduler.h"

// 内部宏 **************************************************************

// 内部变量 **************************************************************
static MID_MAG_PARA_T		MID_MAG;		

//**********************************************************************
// 函数功能：	采样定时器超时回调函数
// 输入参数：	
// 返回参数：	
static void Mid_Mag_IsrCb(void)
{
	Mid_Schd_TaskMsg_T Msg;
	
	Msg.Id = eSchdTaskMsgMagnetism;
	Msg.Param.Mag.Id = eMagEventDataUpdate;
	Mid_Schd_TaskEventSet(&Msg);	
}

//**********************************************************************
// 函数功能：	获取驱动层采样率参数
// 输入参数：	Rate 中间层采样率枚举参数
// 返回参数：	驱动层采用率枚举参数
static bsp_mag_datarate Mid_Mag_DrvRateGet(eMidMagSampleRate Rate)
{
	bsp_mag_datarate RetVal;
	
	switch(Rate)
	{
		case eMidMagSampleRate1HZ:
		case eMidMagSampleRate2HZ:
			RetVal = MAG_DATA_RATE_10HZ;
			break;
		case eMidMagSampleRate25HZ:
		case eMidMagSampleRate50HZ:
			RetVal = MAG_DATA_RATE_50HZ;
			break;
		case eMidMagSampleRate100HZ:
			RetVal = MAG_DATA_RATE_100HZ;
			break;
		case eMidMagSampleRate200HZ:
			RetVal = MAG_DATA_RATE_200HZ;
			break;
		default:
			RetVal = MAG_DATA_RATE_10HZ;
			break;
	}
	
	return RetVal;	
}

//**********************************************************************
// 函数功能：	获取驱动层采样参数
// 输入参数：	Rate 中间层采样范围枚举参数
// 返回参数：	驱动层采用范围枚举参数
static bsp_mag_scalerange Mid_Mag_DrvRangeGet(eMidMagSampleRange Range)
{
	bsp_mag_scalerange RetVal;
	
	switch(Range)
	{
		case eMidMagSampleRange2GS:
			RetVal = MAG_SCALE_RANGE_2GS;
			break;
		case eMidMagSampleRange8GS:
			RetVal = MAG_SCALE_RANGE_8GS;
			break;
		case eMidMagSampleRange12GS:
			RetVal = MAG_SCALE_RANGE_12GS;
			break;
		case eMidMagSampleRange20GS:
			RetVal = MAG_SCALE_RANGE_20GS;
			break;
		default:
			RetVal = MAG_SCALE_RANGE_2GS;
			break;
	}
	
	return RetVal;
}

//**********************************************************************
// 函数功能：	初始化硬件传感器
// 输入参数：	
// 返回参数：	
//**********************************************************************
void Mid_Magnetism_Init(void)
{
	// 硬件初始并休眠
	Drv_Mag_GotoSleep();
	
	// 默认参数初始化
	MID_MAG.SampleRate = eMidMagSampleRate25HZ;
	MID_MAG.SampleRange = eMidMagSampleRange8GS;
	MID_MAG.SamplePeriod = 1000 / MID_MAG.SampleRate;
	MID_MAG.InitedFlg = true;
	
	// 创建采样定时器
	Drv_MTimer_Create(&MID_MAG.MTiemrId, MID_MAG.SamplePeriod, Mid_Mag_IsrCb);
	
	// 默认采样率和采样范围
	Mid_Mag_ParamSet(eMidMagSampleRate25HZ, eMidMagSampleRange8GS);
}

//**********************************************************************
// 函数功能：	参数设置
// 输入参数：	Rate 采样率
//				Range 采样周期
// 返回参数：	无
void Mid_Mag_ParamSet(eMidMagSampleRate Rate, eMidMagSampleRange Range)
{
	MID_MAG.SampleRate = Rate;
	MID_MAG.SampleRange = Range;
	MID_MAG.SamplePeriod = 1000 / MID_MAG.SampleRate;		
}

//**********************************************************************
// 函数功能：	开始采样
// 输入参数：	
// 返回参数：	
void Mid_Mag_StartSample(void)
{
	// 硬件配置
//	Drv_Mag_Open();
	Drv_Mag_Set(Mid_Mag_DrvRateGet(MID_MAG.SampleRate), Mid_Mag_DrvRangeGet(MID_MAG.SampleRange));
//	Drv_Mag_Close();
	
	// 更新采样定时器参数并启动
	Drv_MTimer_Stop(MID_MAG.MTiemrId);	
	Drv_MTimer_Start(MID_MAG.MTiemrId, MID_MAG.SamplePeriod);
	
	MID_MAG.SamplingFlg = true;
}

//**********************************************************************
// 函数功能：	停止采样
// 输入参数：	
// 返回参数：	
void Mid_Mag_StopSample(void)
{
	// 停止硬件采样
	Drv_Mag_GotoSleep();
	
	// 停止采样定时器
	Drv_MTimer_Stop(MID_MAG.MTiemrId);	
	
	MID_MAG.SamplingFlg = false;
}

//**********************************************************************
// 函数功能：	读取一次硬件数据并更新，等待有需要的外设来获取
// 输入参数：	
// 返回参数：
void Mid_Mag_DataUpdate(void)
{
	Drv_Mag_Open();
	Drv_Mag_Read(MID_MAG.LatestData);
	Drv_Mag_Close();
	
	MID_MAG_RTT_LOG(0,"Mag        %d        %d        %d \r\n",MID_MAG.LatestData[0],MID_MAG.LatestData[1],MID_MAG.LatestData[2]);			
}

//**********************************************************************
// 函数功能：	获取配置参数指针
// 输入参数：	无
// 返回参数：	无
MID_MAG_PARA_T* Mid_Mag_ParamPGet(void)
{
	return &MID_MAG;
}

//**********************************************************************
// 函数功能：	传感器自检,调用该函数时，确保该资源未使用
// 输入参数：	无
// 返回参数：	0x00:成功
// 				0xff:失败
//**********************************************************************
uint16 Mid_Magnetism_SelfTest(void)
{
	return Drv_Mag_SelfTest();
}


void Mid_Mag_Test(void)
{
	MID_MAG_RTT_LOG(0, "Mid_Mag_Test \n");
	
	#if 1 // 功耗测试
	static uint8_t lEnableFlg = false;
	
	if(lEnableFlg)
	{
		lEnableFlg = false;
		Mid_Mag_StopSample();
	}
	else
	{
		lEnableFlg = true;
		Mid_Mag_StartSample();
	}
	#endif	
}














