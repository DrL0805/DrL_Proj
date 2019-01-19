#include "scene_sedentary.h"
#include "scene_step.h"
#include "mid_interface.h"
#include "ui_screen_warn.h"

SceneSedentaryParam_t	SceneSedentaryParam;

/*******************************************************************************
 * Brief : 检测是否在久坐勿扰时间段内
 * Input : @NULL 
 * Return: 0 当前非勿扰时间段，1 当前处于勿扰时间段
 * Call  : 
 ***************/
uint16_t Scene_Sedentary_NoDisturbCheck(void)
{
    uint32_t i,j,k,m,n;
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();

    //当前rtc
    n = lMidRTC->RTC.hour*3600 + lMidRTC->RTC.min*60;
    //久坐提醒生效时间段
    i = SceneSedentaryParam.Info.StartTimeHour*3600 + SceneSedentaryParam.Info.StartTimeMin*60;
    j = SceneSedentaryParam.Info.StopTimeHour *3600 + SceneSedentaryParam.Info.StopTimeMin*60;
    //久坐提醒勿扰时间段
    k = SceneSedentaryParam.Info.DisturdStartTimehour*3600 + SceneSedentaryParam.Info.DisturdStartTimeMin*60;
    m = SceneSedentaryParam.Info.DisturdStopTimehour *3600 + SceneSedentaryParam.Info.DisturdStopTimeMin*60;
    if(TimePeriodJudge(i,j,n)) //在生效时间内
    {
        if(TimePeriodJudge(k,m,n))//在勿扰时间段
        {
            return 0;
        }
        else
		{
			return 1;
		}
    }
    return 0;
}

/*******************************************************************************
 * Brief : 算法处理，读取重力数据回调处理
 * Input : @xyzData 重力三轴数据
		   @Interval 采样间隔	
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Sedentary_algorithm(int16 *xyzData, uint32_t Interval)
{
	if(!SceneSedentaryParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Sedentary_algorithm", Ret_NoInit); 
	
	if(SceneSedentaryParam.EnableFlg)
	{
		SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
		SceneSedentaryParam_t* lpSedentary = Scene_Sedentary_ParamPGet();
		uint16 tSetTime;		
		
		SceneSedentaryParam.IntervalMs += Interval;
		if(SceneSedentaryParam.IntervalMs >= SCENE_SEDENTARY_PERIOD_MS)
		{
			SceneSedentaryParam.IntervalMs -= SCENE_SEDENTARY_PERIOD_MS;
			
			/* 久坐算法 */
			alg_sedentary_process(xyzData, lpSceneStepParam->totalStep);
			
			// 获取久坐时间
			alg_sedentary_get_time(&tSetTime);
			SCENE_SEDENTARY_RTT_LOG(0, "tSetTime %d \r\n", tSetTime);
			
			/* 如果到达久坐事件，发送提交提醒事件，并重置提醒参数 */
			if(tSetTime >= lpSedentary->Info.intv_mimute)
			{
				alg_sedentary_start(lpSceneStepParam->totalStep);		// 重置久坐参数
				
				if(!Scene_Sedentary_NoDisturbCheck())
				/* 若非久坐勿扰时间，则发送久坐事件 */
				{
					UI_Screen_Show_Warn_Screen_Outsit();	// 发送久坐事件
				}
			}
		}		
	}
}

/*******************************************************************************
 * Brief : 久坐初始化
 * Input : @NULL 
 * Return: @NULL
 * Call  : 初始化调用一次
 ***************/
void Scene_Sedentary_Init(void)
{
    SceneSedentaryParam.Info.StartTimeHour          = 8,
    SceneSedentaryParam.Info.StartTimeMin           = 0,
    SceneSedentaryParam.Info.StopTimeHour           = 22,
    SceneSedentaryParam.Info.StopTimeMin            = 0,
    SceneSedentaryParam.Info.DisturdStartTimehour   = 22,
    SceneSedentaryParam.Info.DisturdStartTimeMin    = 1,
    SceneSedentaryParam.Info.DisturdStopTimehour    = 7,
    SceneSedentaryParam.Info.DisturdStopTimeMin     = 59,
    SceneSedentaryParam.Info.intv_mimute            = 60,
	
	SceneSedentaryParam.InitFlg = true;
}

/*******************************************************************************
 * Brief : 重置久坐参数 
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Sedentary_Reset(void)
{
	if(!SceneSedentaryParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Sedentary_Reset", Ret_NoInit); 
	
	SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
	
	alg_sedentary_start(lpSceneStepParam->totalStep);	
}

/*******************************************************************************
 * Brief : 
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Sedentary_Enable(void)
{
	if(!SceneSedentaryParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Sedentary_Enable", Ret_NoInit); 
	
	SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
	
	alg_sedentary_start(lpSceneStepParam->totalStep);
	
	SceneSedentaryParam.IntervalMs = 0;
	SceneSedentaryParam.EnableFlg = true;	
}


/*******************************************************************************
 * Brief : 
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Sedentary_Disable(void)
{
	if(!SceneSedentaryParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Sedentary_Disable", Ret_NoInit); 

	SceneSedentaryParam.EnableFlg = false;
}

SceneSedentaryParam_t* Scene_Sedentary_ParamPGet(void)
{
	return &SceneSedentaryParam;
}

void Scene_Sedentary_Test(void)
{
	#if 1	// 久坐勿扰时间
	{
		SceneSedentaryParam_t* lpSedentary = Scene_Sedentary_ParamPGet();
	
		RTT_DEBUG_printf(0, "appLongSitInfo %02d:%02d - %02d:%02d | %02d:%02d - %02d:%02d | %d \n", 
			lpSedentary->Info.StartTimeHour, lpSedentary->Info.StartTimeMin, lpSedentary->Info.StopTimeHour, lpSedentary->Info.StopTimeMin,
			lpSedentary->Info.DisturdStartTimehour, lpSedentary->Info.DisturdStartTimeMin, lpSedentary->Info.DisturdStopTimehour, lpSedentary->Info.DisturdStopTimeMin,
			lpSedentary->Info.intv_mimute);
	}
	#endif	
}




















