#include "scene_run.h"
#include "scene_step.h"

#include "ui_screen_warn.h"
#include "store_interface.h"

SceneRunParam_t	SceneRunParam;

/*******************************************************************************
 * Brief : 跑步场景初始化
 * Input : @NULL 
 * Return: @NULL
 * Call  : 系统初始化时调用一次
 ***************/
void Scene_Run_Init(void)
{
	SceneRunParam.InitFlg = true;
}

/*******************************************************************************
 * Brief : 目标及过程提醒
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
static void Scene_Run_Remind(void)
{
	runningInfo_t lrunningInfo;
	Struct_runningmode_setting lrunningmode_setting;
	
	Scene_Run_InfoGet(&lrunningInfo);
	UI_Screen_RuningModeSetting_Getsetting(&lrunningmode_setting);
	
	/* 目录提醒，每次运动仅一次目标完成提醒 */
	if(false == SceneRunParam.TargetRemindFlg)
	{
		switch (lrunningmode_setting.target_type)
		{
			case Enum_runningmode_setting_target_off:
				SceneRunParam.TargetRemindFlg = true;
				break;
			case Enum_runningmode_setting_target_distance:
				if(lrunningInfo.RecordData.Distance >= lrunningmode_setting.target_distance)
				{
					SceneRunParam.TargetRemindFlg = true;
					UI_Screen_Show_Warn_Screen_RunningMode_Target_Distance();
				}
				break;
			case Enum_runningmode_setting_target_duration:
				if(lrunningInfo.RecordData.Duration >= lrunningmode_setting.target_duration)
				{
					SceneRunParam.TargetRemindFlg = true;
					UI_Screen_Show_Warn_Screen_RunningMode_Target_Duration();
				}
				break;
			case Enum_runningmode_setting_target_calorie:
				if(lrunningInfo.RecordData.Calorie >= lrunningmode_setting.target_calorie)
				{
					SceneRunParam.TargetRemindFlg = true;
					UI_Screen_Show_Warn_Screen_RunningMode_Target_Calorie();
				}
				break;
			default :
				break;
		}	
	}
	
	/* 阶段提醒 */
	if(lrunningmode_setting.warn_distance > 0)	// 距离
	{
		if((lrunningInfo.RecordData.Distance - SceneRunParam.DistanceStageRemind) == lrunningmode_setting.warn_distance)
		{
			SceneRunParam.DistanceStageRemind = lrunningInfo.RecordData.Distance;
			UI_Screen_Show_Warn_Screen_RunningMode_Warn_Distance();
		}
	}
	
	if(lrunningmode_setting.warn_duration > 0)	// 时长
	{
		if((lrunningInfo.RecordData.Duration - SceneRunParam.DurationStageRemind) == lrunningmode_setting.warn_duration)
		{
			SceneRunParam.DurationStageRemind = lrunningInfo.RecordData.Duration;
			UI_Screen_Show_Warn_Screen_RunningMode_Warn_Duration();
		}
	}
	
	if(lrunningmode_setting.warn_calorie > 0)	// 卡路里
	{
		if((lrunningInfo.RecordData.Calorie - SceneRunParam.CaloriaStageRemind) == lrunningmode_setting.warn_calorie)
		{
			SceneRunParam.CaloriaStageRemind = lrunningInfo.RecordData.Calorie;
			UI_Screen_Show_Warn_Screen_RunningMode_Warn_Calorie();
		}
	}
	
	/* 异常报警提醒，每隔一段时间检测一次 */
	if((lrunningInfo.RecordData.Duration > 0 ) && (0 == (lrunningInfo.RecordData.Duration % SCENE_WARN_CHECK_INTERVAL)))
	{
		/* 心率异常报警 */
		if(lrunningmode_setting.heartrate_uplimit)	// 心率上限
		{
			if(Scene_Cnm_HrLimitGet(lrunningmode_setting.heartrate_uplimit, 0) > lrunningInfo.RealTimeData.HR)
			{
				UI_Screen_Show_Warn_Screen_RunningMode_Warn_Heartrate_Uplimit();
			}			
		}
		if(lrunningmode_setting.heartrate_lowlimit)	// 心率下限
		{
			if(Scene_Cnm_HrLimitGet(lrunningmode_setting.heartrate_lowlimit, 1) < lrunningInfo.RealTimeData.HR)
			{
				UI_Screen_Show_Warn_Screen_RunningMode_Warn_Heartrate_Lowlimit();
			}
		}

		/* 配速异常报警 */
		if(lrunningmode_setting.speed_uplimit_switch)	// 最高配速
		{
			if(lrunningmode_setting.speed_uplimit < lrunningInfo.RealTimeData.Pace)
			{
				UI_Screen_Show_Warn_Screen_RunningMode_Warn_Speed_Uplimit();			
			}
		}
		if(lrunningmode_setting.speed_lowlimit_switch)	// 最低配速
		{
			if(lrunningmode_setting.speed_lowlimit > lrunningInfo.RealTimeData.Pace)
			{
				UI_Screen_Show_Warn_Screen_RunningMode_Warn_Speed_Lowlimit();
			}
		}
	}
}

/*******************************************************************************
 * Brief : 跑步算法
 * Input : @NULL 
 * Return: @NULL
 * Call  : 每秒调用一次
 ***************/
void Scene_Run_Algorithm(void)
{
	if(!SceneRunParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Run_Algorithm", Ret_NoInit); 
	
	if(SceneRunParam.EnableFlg)
	{
		ab_value_t lab_value;
		Scene_ABC_ABGet(&lab_value);		
		SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
		Mid_Hrm_Param_t* lpMid_Hrm_Param = Mid_Hrm_ParamPGet();
		
		alg_running_update(	lpSceneStepParam->totalStep, 
							lab_value.altitude, 
							lpMid_Hrm_Param->LastHeartRate, 
							0, 0);
		#if 1
		SCENE_RUN_RTT_LOG(0, "Scene_Run_Algorithm %d %d %d %d %d \n",	
							lpSceneStepParam->totalStep, 
							lab_value.altitude, 
							lpMid_Hrm_Param->LastHeartRate, 
							0, 0);
		#endif
		
		SceneRunParam.TimeCnt++;
		
		if(SceneRunParam.TimeCnt >= SCENE_STORE_TIMEOUT)	// 
		/* 每次最多存储8小时数据 */
		{
			drERROR_CHECK("Scene_Run_Algorithm", Ret_Timeout); 
		}
		
		/* 每10秒存储一次过程数据 */
		if((0 == (SceneRunParam.TimeCnt % 10)))
		{
			Store_Run_algorithm();
		}

		/* 跑步过程提醒 */
		Scene_Run_Remind();
	}
}

/*******************************************************************************
 * Brief : 跑步场景开启
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Run_Enable(void)
{
	if(!SceneRunParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Run_Enable", Ret_NoInit); 
	
	SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
	uint32_t tUTCTime = Mid_Rtc_ReadCurUtc();
	ab_value_t lab_value;
	Scene_ABC_ABGet(&lab_value);	
	
	
	Scene_Hrm_SampleStart(eSceneMeasureKeep);	// 心率持续测量
	
	alg_running_start(	gtBodyInfo.sex, gtBodyInfo.age, gtBodyInfo.Height, gtBodyInfo.Weight, 
						tUTCTime, 
						lpSceneStepParam->totalStep, 
						lab_value.altitude);

	SceneRunParam.EnableFlg = true;
	SceneRunParam.TimeCnt = 0;
	SceneRunParam.TargetRemindFlg = false;
	SceneRunParam.DistanceStageRemind = 0;
	SceneRunParam.DurationStageRemind = 0;
	SceneRunParam.CaloriaStageRemind = 0;

	#if 1
	SCENE_RUN_RTT_LOG(0, "Scene_Run_Enable %d %d %d %d %d %d %d \n",	
						gtBodyInfo.sex, gtBodyInfo.age, gtBodyInfo.Height, gtBodyInfo.Weight, 
						tUTCTime, 
						lpSceneStepParam->totalStep, 
						lab_value.altitude);
	#endif	
}

/*******************************************************************************
 * Brief : 跑步场景停止
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Run_Disable(void)
{
	if(!SceneRunParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Run_Disable", Ret_NoInit); 

	uint32_t tUTCTime = Mid_Rtc_ReadCurUtc();	
	
	alg_running_stop(tUTCTime);
	
	/* 跑步结束后，封存跑步数据 */
	Store_Run_CatalogSeal();
	
	SceneRunParam.EnableFlg = false;
	
	#if 1
	{
		STORE_RTT_LOG(0, "Scene_Run_Disable \n");
	}
	#endif
}

/*******************************************************************************
 * Brief : 跑步场景暂停
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Run_Pause(void)
{
	if(!SceneRunParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Run_Pause", Ret_NoInit); 		
	
	alg_running_pause();
	SceneRunParam.EnableFlg = false;
	
	#if 1
	SCENE_RUN_RTT_LOG(0, "Scene_Run_Pause \n");
	#endif
}

/*******************************************************************************
 * Brief : 跑步场景继续
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Run_Continue(void)
{
	if(!SceneRunParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Run_Continue", Ret_NoInit); 
	
	SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
	ab_value_t lab_value;
	Scene_ABC_ABGet(&lab_value);
	
	alg_running_continue(lpSceneStepParam->totalStep, lab_value.altitude, 0, 0);
	
	SceneRunParam.EnableFlg = true;
	
	#if 1
	SCENE_RUN_RTT_LOG(0, "Scene_Run_Continue %d %d %d %d \n",
						lpSceneStepParam->totalStep, lab_value.altitude, 0, 0);
	#endif	
}

/*******************************************************************************
 * Brief : 获取参数结构体指针
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
SceneRunParam_t* Scene_Run_ParamPGet(void)
{
	return &SceneRunParam;
}

/*******************************************************************************
 * Brief : 获取跑步信息
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Run_InfoGet(runningInfo_t *info)
{
	alg_running_get_info(info);
	
	#if 1
	SCENE_RUN_RTT_LOG(0, "Scene_Run_InfoGet %d %d %d %d \n",
						info->HrZone,
						info->RealTimeData.Pace, info->RealTimeData.Freq, info->RealTimeData.Stride, info->RealTimeData.HR);
	#endif	
}

/*******************************************************************************
 * Brief : 跑步场景测试
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Run_Test(uint8_t fEvent)
{
	#if 0
	{
		static uint8_t lsState = 0;
		
		switch (fEvent)
        {
        	case MID_KEY0_SHORT:	// 短按控制运动开关
				switch(lsState)
				{
					case 0:
						lsState = 1;
						Scene_Run_Enable();
						break;
					case 1:
						lsState = 0;
						Scene_Run_Disable();
						break;
					default:
						break;
				}
        		break;
        	case MID_KEY0_HOLDSHORT:	// 长按3秒显示运动存储信息	
//				Store_Run_DataRead();
//				vTaskDelay(10);
				Store_History_Test();
        		break;
        	default :
        		break;
        }
	}
	#endif	
}








