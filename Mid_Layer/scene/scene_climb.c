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
 * Brief : ��ɽ������ʼ��
 * Input : @NULL 
 * Return: @NULL
 * Call  : ϵͳ��ʼ��ʱ����һ��
 ***************/
void Scene_Climb_Init(void)
{
	SceneClimbParam.InitFlg = true;
}

/*******************************************************************************
 * Brief : Ŀ�꼰��������
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

	/* Ŀ¼���ѣ�ÿ���˶���һ��Ŀ��������� */
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
	
	/* �׶����� */
	if(lclimbingmode_setting.warn_distance > 0)	// ����
	{
		if((lclimbMountainInfo.RecordData.Distance - SceneClimbParam.DistanceStageRemind) == lclimbingmode_setting.warn_distance)
		{
			SceneClimbParam.DistanceStageRemind = lclimbMountainInfo.RecordData.Distance;
			UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Distance();
		}
	}
	
	if(lclimbingmode_setting.warn_duration > 0)	// ʱ��
	{
		if((lclimbMountainInfo.RecordData.Duration - SceneClimbParam.DurationStageRemind) == lclimbingmode_setting.warn_duration)
		{
			SceneClimbParam.DurationStageRemind = lclimbMountainInfo.RecordData.Duration;
			UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Duration();
		}
	}
	
	if(lclimbingmode_setting.warn_calorie > 0)	// ��·��
	{
		if((lclimbMountainInfo.RecordData.Calorie - SceneClimbParam.CaloriaStageRemind) == lclimbingmode_setting.warn_calorie)
		{
			SceneClimbParam.CaloriaStageRemind = lclimbMountainInfo.RecordData.Calorie;
			UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Calorie();
		}
	}
	
	/* �쳣�������ѣ�ÿ��һ��ʱ����һ�� */
	if((lclimbMountainInfo.RecordData.Duration > 0 ) && (0 == (lclimbMountainInfo.RecordData.Duration % SCENE_WARN_CHECK_INTERVAL)))
	{
		/* �����쳣���� */
		if(lclimbingmode_setting.heartrate_uplimit)	// ��������
		{
			if(Scene_Cnm_HrLimitGet(lclimbingmode_setting.heartrate_uplimit, 0) > lclimbMountainInfo.RealTimeData.Hr)
			{
				UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Heartrate_Uplimit();
			}			
		}
		if(lclimbingmode_setting.heartrate_lowlimit)	// ��������
		{
			if(Scene_Cnm_HrLimitGet(lclimbingmode_setting.heartrate_lowlimit, 1) < lclimbMountainInfo.RealTimeData.Hr)
			{
				UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Heartrate_Lowlimit();
			}
		}

		/* �����쳣���� */
		if(lclimbingmode_setting.elevation_uplimit_switch)	// ��������
		{
			if(lclimbingmode_setting.elevation_uplimit > lclimbMountainInfo.RealTimeData.Altitude)
			{
				UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Elevation_Uplimit();
			}
		}
		if(lclimbingmode_setting.elevation_lowlimit_switch)	// ��������
		{
			if(lclimbingmode_setting.elevation_lowlimit < lclimbMountainInfo.RealTimeData.Altitude)
			{
				UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Elevation_Lowlimit();
			}
		}
	}
}

/*******************************************************************************
 * Brief : ��ɽ�㷨
 * Input : @NULL 
 * Return: @NULL
 * Call  : ÿ�����һ��
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
		/* ÿ�����洢8Сʱ���� */
		{
			drERROR_CHECK_RETURN_NULL("Scene_Climb_Algorithm", Ret_Timeout); 
		}
		
		/* ÿ10��洢һ�ι������� */
		if((0 == (SceneClimbParam.TimeCnt % 10)))
		{
			Store_Climb_algorithm();
		}
		
		/* ��ɽ�������� */
		Scene_Climb_Remind();
	}
}

/*******************************************************************************
 * Brief : ��ɽ��������
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
	
	Scene_Hrm_SampleStart(eSceneMeasureKeep);	// ���ʳ�������
	
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
 * Brief : ��ɽ��������
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Climb_Disable(void)
{
	if(!SceneClimbParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Climb_Disable", Ret_NoInit); 

	uint32_t tUTCTime = Mid_Rtc_ReadCurUtc();
	
	alg_climbMountain_stop(tUTCTime);
	
	/* ��ɽ�����󣬷���ܲ����� */
	Store_Climb_CatalogSeal();
	
	SceneClimbParam.EnableFlg = false;
	
	#if 1
	{
		STORE_RTT_LOG(0, "Scene_Climb_Disable \n");
	}
	#endif
}

/*******************************************************************************
 * Brief : ��ɽ������ͣ
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
 * Brief : ��ɽ��������
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
 * Brief : ��ȡ�����ṹ��ָ��
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
SceneClimbParam_t* Scene_Climb_ParamPGet(void)
{
	return &SceneClimbParam;
}

/*******************************************************************************
 * Brief : ��ȡ��ɽ��Ϣ
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
 * Brief : ��ɽ��������
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
        	case MID_KEY0_SHORT:	// �̰������˶�����
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
        	case MID_KEY0_HOLDSHORT:	// ����3����ʾ�˶��洢��Ϣ	
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








