#include "scene_sleep.h"
#include "mid_interface.h"

SceneSleepParam_t	SceneSleep;

/*******************************************************************************
 ** Brief : 睡眠算法处理，读取重力数据回调处理
 ** Input : @xyzData  重力三轴数据
			@Interval 采样周期
 ** Return: @NULL
 ** Call  : 睡眠算法，1秒1次
 ***************/
void Scene_Sleep_algorithm(int16 *xyzData, uint32_t Interval)
{
	if(!SceneSleep.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Sleep_algorithm", Ret_NoInit); 
	
	if(SceneSleep.EnableFlg)
	{
		SceneSleep.IntervalMs += Interval;
		if(SceneSleep.IntervalMs >= SLEEP_SCENE_PERIOD_MS)
		{
			SceneSleep.IntervalMs -= SLEEP_SCENE_PERIOD_MS;
			
			alg_sleep_process(xyzData, 0xFF);
		}	
	}
}

/*******************************************************************************
 ** Brief : 睡眠信息初始化
 ** Input : @NULL
 ** Return: @NULL
 ** Call  : 初始化调用一次
 ***************/
void Scene_Sleep_Init(void)
{	
	SceneSleep.InitFlg = true;
}
 
/*******************************************************************************
 ** Brief : 清除前一天睡眠数据
 ** Input : @NULL
 ** Return: @NULL
 ** Call  : 每天零点调用
 ***************/
void Scene_Sleep_Clear(void)
{
	alg_sleep_clr_record();
}

/*******************************************************************************
 ** Brief : 本地获取睡眠最新信息，用于UI交互
 ** Input : @NULL
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_Sleep_RecordGet(sleep_record_t *sleepRecord)
{
	alg_sleep_get_record(sleepRecord);
}

/*******************************************************************************
 ** Brief : 睡眠场景开启
 ** Input : @NULL
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_Sleep_Enable(void)
{
	if(!SceneSleep.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Sleep_Enable", Ret_NoInit); 

	alg_sleep_init();
	alg_sleep_clr_record();
	
	SceneSleep.IntervalMs = 0;
	SceneSleep.EnableFlg = true;
}

/*******************************************************************************
 ** Brief : 睡眠场景关闭
 ** Input : @NULL
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_Sleep_Disable(void)
{
	if(!SceneSleep.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Sleep_Disable", Ret_NoInit); 

	SceneSleep.EnableFlg = false;
}












