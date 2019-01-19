#include "scene_variable.h"
#include "scene_climb.h"
#include "scene_step.h"
#include "scene_abc.h"
#include "scene_hrm.h"

#include "mid_interface.h"
#include "store_interface.h"
#include "ui_screen_climbing.h"

SceneClimbParam_t	SceneClimbParam;

/*******************************************************************************
 * Brief : 登山场景初始化
 * Input : @NULL 
 * Return: @NULL
 * Call  : 系统初始化时调用一次
 ***************/
void Scene_Climb_Init(void)
{
	SceneClimbParam.InitFlg = true;
}

/*******************************************************************************
 * Brief : 目标及过程提醒
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
static void Scene_Climb_Remind(void)
{
	climbMountainInfo_t lclimbMountainInfo;
	Struct_climbingmode_setting lclimbingmode_setting;

	Scene_Climb_InfoGet(&lclimbMountainInfo);
	UI_Screen_ClimbingModeSetting_Getsetting(&lclimbingmode_setting);

	/* 目录提醒，每次运动仅一次目标完成提醒 */
	if(false == SceneClimbParam.TargetRemindFlg)
	{
		switch (lclimbingmode_setting.target_type)
		{
			case Enum_climbingmode_setting_target_off:
				SceneClimbParam.TargetRemindFlg = true;
				break;
			case Enum_climbingmode_setting_target_climbingdistance:
				if(lclimbMountainInfo.RecordData.UpAltitude >= lclimbingmode_setting.target_climbingdistance)
				{
					SceneClimbParam.TargetRemindFlg = true;
					UI_Screen_Show_Warn_Screen_ClimbingMode_Target_ClimbingDistance();
				}
				break;
			case Enum_climbingmode_setting_target_distance:
				if(lclimbMountainInfo.RecordData.Distance >= lclimbingmode_setting.target_distance)
				{
					SceneClimbParam.TargetRemindFlg = true;
					UI_Screen_Show_Warn_Screen_ClimbingMode_Target_Distance();
				}
				break;
			case Enum_climbingmode_setting_target_duration:
				if(lclimbMountainInfo.RecordData.Duration >= lclimbingmode_setting.target_duration)
				{
					SceneClimbParam.TargetRemindFlg = true;
					UI_Screen_Show_Warn_Screen_ClimbingMode_Target_Duration();
				}
				break;
			case Enum_climbingmode_setting_target_calorie:
				if(lclimbMountainInfo.RecordData.Calorie >= lclimbingmode_setting.target_calorie)
				{
					SceneClimbParam.TargetRemindFlg = true;
					UI_Screen_Show_Warn_Screen_ClimbingMode_Target_Calorie();
				}
				break;
			default :
				break;
		}	
	}	
	
	/* 阶段提醒 */
	if(lclimbingmode_setting.warn_distance > 0)	// 距离
	{
		if((lclimbMountainInfo.RecordData.Distance - SceneClimbParam.DistanceStageRemind) == lclimbingmode_setting.warn_distance)
		{
			SceneClimbParam.DistanceStageRemind = lclimbMountainInfo.RecordData.Distance;
			UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Distance();
		}
	}
	
	if(lclimbingmode_setting.warn_duration > 0)	// 时长
	{
		if((lclimbMountainInfo.RecordData.Duration - SceneClimbParam.DurationStageRemind) == lclimbingmode_setting.warn_duration)
		{
			SceneClimbParam.DurationStageRemind = lclimbMountainInfo.RecordData.Duration;
			UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Duration();
		}
	}
	
	if(lclimbingmode_setting.warn_calorie > 0)	// 卡路里
	{
		if((lclimbMountainInfo.RecordData.Calorie - SceneClimbParam.CaloriaStageRemind) == lclimbingmode_setting.warn_calorie)
		{
			SceneClimbParam.CaloriaStageRemind = lclimbMountainInfo.RecordData.Calorie;
			UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Calorie();
		}
	}
	
	/* 异常报警提醒，每隔一段时间检测一次 */
	if((lclimbMountainInfo.RecordData.Duration > 0 ) && (0 == (lclimbMountainInfo.RecordData.Duration % SCENE_WARN_CHECK_INTERVAL)))
	{
		/* 心率异常报警 */
		if(lclimbingmode_setting.heartrate_uplimit)	// 心率上限
		{
			if(Scene_Cnm_HrLimitGet(lclimbingmode_setting.heartrate_uplimit, 0) > lclimbMountainInfo.RealTimeData.Hr)
			{
				UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Heartrate_Uplimit();
			}			
		}
		if(lclimbingmode_setting.heartrate_lowlimit)	// 心率下限
		{
			if(Scene_Cnm_HrLimitGet(lclimbingmode_setting.heartrate_lowlimit, 1) < lclimbMountainInfo.RealTimeData.Hr)
			{
				UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Heartrate_Lowlimit();
			}
		}

		/* 海拔异常报警 */
		if(lclimbingmode_setting.elevation_uplimit_switch)	// 海拔上限
		{
			if(lclimbingmode_setting.elevation_uplimit > lclimbMountainInfo.RealTimeData.Altitude)
			{
				UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Elevation_Uplimit();
			}
		}
		if(lclimbingmode_setting.elevation_lowlimit_switch)	// 海拔下限
		{
			if(lclimbingmode_setting.elevation_lowlimit < lclimbMountainInfo.RealTimeData.Altitude)
			{
				UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Elevation_Lowlimit();
			}
		}
	}
}

/*******************************************************************************
 * Brief : 登山算法
 * Input : @NULL 
 * Return: @NULL
 * Call  : 每秒调用一次
 ***************/
void Scene_Climb_Algorithm(void)
{
	if(!SceneClimbParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Climb_Algorithm", Ret_NoInit); 
	
	if(SceneClimbParam.EnableFlg)
	{
		ab_value_t lab_value;
		Scene_ABC_ABGet(&lab_value);		
		SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
		Mid_Hrm_Param_t* lpMid_Hrm_Param = Mid_Hrm_ParamPGet();		

		alg_climbMountain_update(lpSceneStepParam->totalStep, 
							lab_value.altitude, 
							lpMid_Hrm_Param->LastHeartRate, 
							0, 0);
		
		#if 1
		SCENE_CLIMB_RTT_LOG(0, "Scene_Climb_Algorithm %d %d %d %d %d \n",	
							lpSceneStepParam->totalStep, 
							lab_value.altitude, 
							lpMid_Hrm_Param->LastHeartRate, 
							0, 0);
		#endif

		SceneClimbParam.TimeCnt++;
		
		if(SceneClimbParam.TimeCnt >= SCENE_STORE_TIMEOUT)	// 
		/* 每次最多存储8小时数据 */
		{
			drERROR_CHECK_RETURN_NULL("Scene_Climb_Algorithm", Ret_Timeout); 
		}
		
		/* 每10秒存储一次过程数据 */
		if((0 == (SceneClimbParam.TimeCnt % 10)))
		{
			Store_Climb_algorithm();
		}
		
		/* 登山过程提醒 */
		Scene_Climb_Remind();
	}
}

/*******************************************************************************
 * Brief : 登山场景开启
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Climb_Enable(void)
{
	if(!SceneClimbParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Climb_Enable", Ret_NoInit); 
	
	SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
	uint32_t tUTCTime = Mid_Rtc_ReadCurUtc();
	ab_value_t lab_value;
	Scene_ABC_ABGet(&lab_value);	
	
	alg_climbMountain_start(gtBodyInfo.sex, gtBodyInfo.age, gtBodyInfo.Height, gtBodyInfo.Weight,
		tUTCTime, lpSceneStepParam->totalStep, lab_value.altitude);
	
	Scene_Hrm_SampleStart(eSceneMeasureKeep);	// 心率持续测量
	
	SceneClimbParam.EnableFlg = true;
	SceneClimbParam.TimeCnt = 0;
	SceneClimbParam.TargetRemindFlg = false;
	SceneClimbParam.DistanceStageRemind = 0;
	SceneClimbParam.DurationStageRemind = 0;
	SceneClimbParam.CaloriaStageRemind = 0;
	
	#if 1
	SCENE_CLIMB_RTT_LOG(0, "Scene_Climb_Enable %d %d %d %d %d %d %d \n",	
						gtBodyInfo.sex, gtBodyInfo.age, gtBodyInfo.Height, gtBodyInfo.Weight, 
						tUTCTime, 
						lpSceneStepParam->totalStep, 
						lab_value.altitude);
	#endif	
}

/*******************************************************************************
 * Brief : 登山场景结束
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Climb_Disable(void)
{
	if(!SceneClimbParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Climb_Disable", Ret_NoInit); 

	uint32_t tUTCTime = Mid_Rtc_ReadCurUtc();
	
	alg_climbMountain_stop(tUTCTime);
	
	/* 登山结束后，封存跑步数据 */
	Store_Climb_CatalogSeal();
	
	SceneClimbParam.EnableFlg = false;
	
	#if 1
	{
		STORE_RTT_LOG(0, "Scene_Climb_Disable \n");
	}
	#endif
}

/*******************************************************************************
 * Brief : 登山场景暂停
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Climb_Pause(void)
{
	if(!SceneClimbParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Climb_Pause", Ret_NoInit); 

	alg_climbMountain_pause();
	SceneClimbParam.EnableFlg = false;
	
	#if 1
	SCENE_CLIMB_RTT_LOG(0, "Scene_Climb_Pause \n");
	#endif	
}

/*******************************************************************************
 * Brief : 登山场景继续
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Climb_Continue(void)
{
	if(!SceneClimbParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Climb_Continue", Ret_NoInit); 
	
	SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
	ab_value_t lab_value;
	Scene_ABC_ABGet(&lab_value);	
	
	alg_climbMountain_continue(lpSceneStepParam->totalStep, lab_value.altitude, 0, 0);
	
	SceneClimbParam.EnableFlg = true;
	
	#if 1
	SCENE_CLIMB_RTT_LOG(0, "Scene_Climb_Continue %d %d %d %d \n",
						lpSceneStepParam->totalStep, lab_value.altitude, 0, 0);
	#endif		
}

/*******************************************************************************
 * Brief : 获取参数结构体指针
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
SceneClimbParam_t* Scene_Climb_ParamPGet(void)
{
	return &SceneClimbParam;
}

/*******************************************************************************
 * Brief : 获取登山信息
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Climb_InfoGet(climbMountainInfo_t *info)
{
	alg_climbMountain_get_info(info);
	
	#if 1
	SCENE_CLIMB_RTT_LOG(0, "Scene_Climb_InfoGet %d %d %d %d %d \n",
						info->RealTimeData.Altitude, info->RealTimeData.Speed, info->RealTimeData.Hr, 
						(uint32_t)(info->RealTimeData.Longitude.f), (uint32_t)(info->RealTimeData.Latitude.f));
	#endif
}

/*******************************************************************************
 * Brief : 登山场景测试
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Climb_Test(uint8_t fEvent)
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
						Scene_Climb_Enable();
						break;
					case 1:
						lsState = 0;
						Scene_Climb_Disable();
						break;
					default:
						break;
				}
        		break;
        	case MID_KEY0_HOLDSHORT:	// 长按3秒显示运动存储信息	
				Store_Climb_DataRead();
				vTaskDelay(10);
				Store_History_Test();
        		break;
        	default :
        		break;
        }
	}
	#endif		
}








