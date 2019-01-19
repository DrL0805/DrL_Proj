/**********************************************************************
**
**模块说明: mid层stop watch接口
**软件版本，修改日志(时间，内容),修改人:
**   V1.0   2018.4.24  修改流程  ZSL  
**
**********************************************************************/
#include "sm_timer.h"
#include "scene_stopwatch.h"

SceneStopWatchParam_t	SceneStopWatchParam;

/*******************************************************************************
 ** Brief : 秒表中断回调函数
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
static void Scene_StopWatch_IsrCb(void)
{
	SceneStopWatchParam.TotalMs += STOPWATCH_PERIOD_MS;
}

/*******************************************************************************
 ** Brief : 秒表复位函数，对秒表参数全部复位为0，对秒表Timer进行硬件复位
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_StopWatch_Reset(void)
{
	SceneStopWatchParam.MeasureCnt = 0;
	SceneStopWatchParam.TotalMs = 0;
	SceneStopWatchParam.State = eStopWatchStop;
	
	// 清零并停止定时器
    SMDrv_CTimer_Clear(STOPWATCH_CTIMER_MODULE);
}

/*******************************************************************************
 ** Brief : 秒表功能初始化函数。
			对秒表Timer进行硬件进行初始化，并注册中断回调函数，对秒表参数复位
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_StopWatch_Init(void)
{
    SMDrv_CTimer_Open(STOPWATCH_CTIMER_MODULE,STOPWATCH_PERIOD_MS,Scene_StopWatch_IsrCb);
	
	Scene_StopWatch_Reset();

	SceneStopWatchParam.InitedFlg = true;
}

/*******************************************************************************
 ** Brief : 启动秒表
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_StopWatch_Start(void)
{
	SceneStopWatchParam.State = eStopWatchRuning;
	
    SMDrv_CTimer_Start(STOPWATCH_CTIMER_MODULE);
}

/*******************************************************************************
 ** Brief : 暂定秒表
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_StopWatch_Suspend(void)
{
	SceneStopWatchParam.State = eStopWatchSuspend;
	
    SMDrv_CTimer_Stop(STOPWATCH_CTIMER_MODULE);
}

/*******************************************************************************
 ** Brief : 设置秒表测量点，把当前秒表时间保存起来
			把秒表时间读取出来，带补偿
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_StopWatch_MeasureMark(void)
{
	if(SceneStopWatchParam.MeasureCnt >= STOPWATCH_MAX_STORE)
		return;	
	
	uint32 cntTemp;
	
	// 获取当前tick值，并转为ms。时钟使用的是32768Hz
	cntTemp = (uint32_t)SMDrv_CTimer_ReadCount(STOPWATCH_CTIMER_MODULE) * 0.0305;	// (1000 / 32768)
	
	// 保存当前带补偿的时间值
	SceneStopWatchParam.MeasurePoint[SceneStopWatchParam.MeasureCnt] = SceneStopWatchParam.TotalMs + cntTemp;
	SceneStopWatchParam.MeasureCnt++;
}

/*******************************************************************************
 ** Brief : 获取当前秒表计数值
 ** Input : @Methon 获取方法，0不带补偿，非0带补偿
 ** Return: @NULL
 ** Call  : 
 ***************/
uint32_t Scene_StopWatch_TotalMsGet(uint8_t Methon)
{	
	if(Methon)
	{
		uint32 cntTemp;
		
		// 获取当前tick值，并转为ms。时钟使用的是32768Hz
		cntTemp = (uint32_t)SMDrv_CTimer_ReadCount(STOPWATCH_CTIMER_MODULE) * 0.0305;	// (1000 / 32768)
		
		return (SceneStopWatchParam.TotalMs + cntTemp);
	}
	else
	{
		return SceneStopWatchParam.TotalMs;
	}
}

/*******************************************************************************
 ** Brief : 获取参数的结构体指针
 ** Input : @NULL
 ** Return: @NULL
 ** Call  : 
 ***************/
SceneStopWatchParam_t* Scene_StopWatch_ParamPGet(void)
{
	return &SceneStopWatchParam;
}

/*******************************************************************************
 ** Brief : ms值转为 h:m:s:ms模式
 ** Input : @Ms 需转换的Ms值
 ** Return: @fStopWatchFormat 保存转换结果
 ** Call  : 
 ***************/
void Scene_StopWatch_FormatSwitch(uint32_t Ms, SceneStopWatchFormat_t* fStopWatchFormat)
{
	uint32_t tMs = Ms;
	
	fStopWatchFormat->hour = tMs / 3600000;
	
	tMs %= 3600000;
	fStopWatchFormat->min = tMs / 60000;
	
	tMs %= 60000;
	fStopWatchFormat->sec = tMs / 1000;	
	
	tMs %= 1000;
	fStopWatchFormat->ms = tMs;	
}


void Scene_StopWatch_Test(void)
{
	SCENE_STOPWATCH_RTT_LOG(0,"Scene_StopWatch_Test \n");
	
	#if 1	// 秒表测试
	SceneStopWatchParam_t* tStopWatchParam;
	
	SceneStopWatchFormat_t	sStopWatchFormat;
	
	uint32_t	tStopWatchTotalMs = 0;
	
	tStopWatchParam = Scene_StopWatch_ParamPGet();
	SCENE_STOPWATCH_RTT_LOG(0,"InitedFlg %d \n", (tStopWatchParam)->InitedFlg);
	SCENE_STOPWATCH_RTT_LOG(0,"MeasureCnt %d \n", (tStopWatchParam)->MeasureCnt);
	SCENE_STOPWATCH_RTT_LOG(0,"State %d \n", (tStopWatchParam)->State);
	SCENE_STOPWATCH_RTT_LOG(0,"TotalMs %d \n", (tStopWatchParam)->TotalMs);
	
	if(eStopWatchStop == tStopWatchParam->State)
	{
		Scene_StopWatch_Start();
		SCENE_STOPWATCH_RTT_LOG(0,"Scene_StopWatch_Start \r\n");
	}
	else
	{
		Scene_StopWatch_MeasureMark();	// 测量点
		tStopWatchParam = Scene_StopWatch_ParamPGet();	// 获取新参数
		tStopWatchTotalMs = Scene_StopWatch_TotalMsGet(true);	// 带补偿方式获取当前总时间
		
		Scene_StopWatch_FormatSwitch(tStopWatchTotalMs, &sStopWatchFormat);	// 时间格式转换
		
		SCENE_STOPWATCH_RTT_LOG(0,"tStopWatchTatolMs %d, %d:%d:%d:%d \r\n", 
			tStopWatchTotalMs, sStopWatchFormat.hour, sStopWatchFormat.min, sStopWatchFormat.sec, sStopWatchFormat.ms);
		
		for(uint32_t i = 0; i < tStopWatchParam->MeasureCnt; i++)
		{
			SCENE_STOPWATCH_RTT_LOG(0,"%d ", tStopWatchParam->MeasurePoint[i]);
		}SCENE_STOPWATCH_RTT_LOG(0,"\r\n");
	}
	#endif
}










