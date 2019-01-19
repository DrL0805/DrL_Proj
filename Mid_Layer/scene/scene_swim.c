#include "scene_swim.h"
#include "scene_hrm.h"

#include "mid_interface.h"
#include "store_interface.h"
#include "ui_screen_swim.h"

SceneSwimParam_t	SceneSwimParam;

/*******************************************************************************
 * Brief : ��Ӿ������ʼ��
 * Input : @NULL
 * Return: @NULL
 * Call  : ϵͳ��ʼ��ʱ����һ��
 ***************/
void Scene_Swim_Init(void)
{
	SceneSwimParam.InitFlg = true;
}

static void Scene_Swim_Remind(void)
{
	swimIndoorInfo_t lswimIndoorInfo;
	Struct_swimmode_setting lswimmode_setting;
	
	Scene_Swim_InfoGet(&lswimIndoorInfo);
	UI_Screen_SwimModeSetting_Getsetting(&lswimmode_setting);

	/* Ŀ¼���ѣ�ÿ���˶���һ��Ŀ��������� */
	if(false == SceneSwimParam.TargetRemindFlg)
	{
		switch (lswimmode_setting.target_type)
		{
			case Enum_swimmode_setting_target_off:
				SceneSwimParam.TargetRemindFlg = true;
				break;
			case Enum_swimmode_setting_target_laps:
				if(lswimIndoorInfo.RecordData.Distance >= lswimmode_setting.target_laps)
				{
					SceneSwimParam.TargetRemindFlg = true;
					UI_Screen_Show_Warn_Screen_SwimMode_Target_Laps();
				}
				break;
			case Enum_swimmode_setting_target_duration:
				if(lswimIndoorInfo.RecordData.Duration >= lswimmode_setting.target_duration)
				{
					SceneSwimParam.TargetRemindFlg = true;
					UI_Screen_Show_Warn_Screen_SwimMode_Target_Duration();
				}
				break;
			case Enum_swimmode_setting_target_calorie:
				if(lswimIndoorInfo.RecordData.Calorie >= lswimmode_setting.target_calorie)
				{
					SceneSwimParam.TargetRemindFlg = true;
					UI_Screen_Show_Warn_Screen_SwimMode_Target_Calorie();
				}
				break;
			default :
				break;
		}	
	}
	
	/* �׶����� */
	if(lswimmode_setting.warn_laps > 0)	// ����
	{
		if((lswimIndoorInfo.RecordData.Laps - SceneSwimParam.LapsStageRemind) == lswimmode_setting.warn_laps)
		{
			SceneSwimParam.LapsStageRemind = lswimIndoorInfo.RecordData.Laps;
			UI_Screen_Show_Warn_Screen_SwimMode_Warn_Laps();
		}
	}
	
	if(lswimmode_setting.warn_duration > 0)	// ʱ��
	{
		if((lswimIndoorInfo.RecordData.Duration - SceneSwimParam.DurationStageRemind) == lswimmode_setting.warn_duration)
		{
			SceneSwimParam.DurationStageRemind = lswimIndoorInfo.RecordData.Duration;
			UI_Screen_Show_Warn_Screen_SwimMode_Warn_Duration();
		}
	}
	
	if(lswimmode_setting.warn_calorie > 0)	// ��·��
	{
		if((lswimIndoorInfo.RecordData.Calorie - SceneSwimParam.CaloriaStageRemind) == lswimmode_setting.warn_calorie)
		{
			SceneSwimParam.CaloriaStageRemind = lswimIndoorInfo.RecordData.Calorie;
			UI_Screen_Show_Warn_Screen_SwimMode_Warn_Calorie();
		}
	}	
}

/*******************************************************************************
 * Brief : ��Ӿ�㷨
 * Input : @AccData	���ٶ����ݣ�ֻ���㷨������eSceneSwimAlgoGsenserʱ����Ч
		   @feSceneSwimAlgoType �㷨���ͣ����ٶȻ�������	
 * Return: @NULL
 * Call  : eSceneSwimAlgoGsenser 25Hz���ã�eSceneSwimAlgoHr 1Hz����
 ***************/
void Scene_Swim_Algorithm(int16 *AccData, SceneSwimAlgoType_e feSceneSwimAlgoType)
{
	if(!SceneSwimParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Swim_Algorithm", Ret_NoInit); 
	
	if(SceneSwimParam.EnableFlg)
	{
		Mid_Hrm_Param_t* lpMid_Hrm_Param = Mid_Hrm_ParamPGet();
		MID_MAG_PARA_T* lpMidMagParam = Mid_Mag_ParamPGet();		
		
//		SCENE_SWIM_RTT_LOG(0, "Scene_Swim_Algorithm %d \n",feSceneSwimAlgoType);
		
		switch(feSceneSwimAlgoType)
		{
			case eSceneSwimAlgoGsenser:
				alg_swimIndoor_calculate(AccData, lpMidMagParam->LatestData);
				#if 0
				SCENE_SWIM_RTT_LOG(0, "Scene_Swim_Algorithm %d %d %d %d %d %d \n",
					lpMidAccelParam->LatestData[0], lpMidAccelParam->LatestData[1], lpMidAccelParam->LatestData[2], 
					lpMidMagParam->LatestData[0], lpMidMagParam->LatestData[1], lpMidMagParam->LatestData[2]);
				#endif
				break;
			case eSceneSwimAlgoHr:
				alg_swimIndoor_update(lpMid_Hrm_Param->LastHeartRate);
			
				SceneSwimParam.TimeCnt++;
			
				#if 0
				SCENE_SWIM_RTT_LOG(0, "Scene_Swim_Algorithm %d \n", lpMid_Hrm_Param->LastHeartRate);
				#endif			
			
				if(SceneSwimParam.TimeCnt >= SCENE_STORE_TIMEOUT)	// 
				/* ÿ�����洢8Сʱ���� */
				{
					drERROR_CHECK_RETURN_NULL("Scene_Swim_Algorithm", Ret_Timeout); 
				}
				
				/* ÿ10��洢һ�ι������� */
				if((0 == (SceneSwimParam.TimeCnt % 10)))
				{
					Store_Swim_algorithm();
				}				
				break;
			default:
				break;
		}
		
		Scene_Swim_Remind();
	}
}

/*******************************************************************************
 * Brief : ��Ӿ��������
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Swim_Enable(void)
{
	if(!SceneSwimParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Swim_Enable", Ret_NoInit); 

	uint32_t tUTCTime = Mid_Rtc_ReadCurUtc();	
	
	alg_swimIndoor_start(gtBodyInfo.sex, gtBodyInfo.age, gtBodyInfo.Height, gtBodyInfo.Weight, tUTCTime, 50);

	Scene_Hrm_SampleStart(eSceneMeasureKeep);	// ���ʳ�������
	
	SceneSwimParam.EnableFlg = true;
	SceneSwimParam.TimeCnt = 0;
	SceneSwimParam.TargetRemindFlg = false;
	SceneSwimParam.LapsStageRemind = 0;
	SceneSwimParam.DurationStageRemind = 0;
	SceneSwimParam.CaloriaStageRemind = 0;	
	
	#if 1
	SCENE_SWIM_RTT_LOG(0, "Scene_Swim_Enable %d %d %d %d %d %d \n",
		gtBodyInfo.sex, gtBodyInfo.age, gtBodyInfo.Height, gtBodyInfo.Weight, tUTCTime, 50);
	#endif		
}

/*******************************************************************************
 * Brief : ��Ӿ����ֹͣ
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Swim_Disable(void)
{
	if(!SceneSwimParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Swim_Disable", Ret_NoInit); 

	uint32_t tUTCTime = Mid_Rtc_ReadCurUtc();	
	
	alg_swimIndoor_stop(tUTCTime);
	
	/* �ܲ������󣬷���ܲ����� */
	Store_Swim_CatalogSeal();
	
	SceneSwimParam.EnableFlg = false;
	
	#if 1
	{
		SCENE_SWIM_RTT_LOG(0, "Scene_Swim_Disable \n");
	}
	#endif	
}

/*******************************************************************************
 * Brief : ��Ӿ������ͣ
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Swim_Pause(void)
{
	if(!SceneSwimParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Swim_Pause", Ret_NoInit); 	
	
	alg_swimIndoor_pause();
	
	SceneSwimParam.EnableFlg = false;
	
	#if 1
	SCENE_SWIM_RTT_LOG(0, "Scene_Swim_Pause \n");
	#endif	
}

/*******************************************************************************
 * Brief : ��Ӿ��������
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Swim_Continue(void)
{
	if(!SceneSwimParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Swim_Continue", Ret_NoInit); 

	alg_swimIndoor_continue();
	
	SceneSwimParam.EnableFlg = true;
	
	#if 1
	SCENE_SWIM_RTT_LOG(0, "Scene_Swim_Continue \n");
	#endif
}

/*******************************************************************************
 * Brief : ��ȡ�����ṹ��ָ��
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
SceneSwimParam_t* Scene_Swim_ParamPGet(void)
{
	return &SceneSwimParam;
}

/*******************************************************************************
 * Brief : ��ȡ��Ӿ��Ϣ
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Swim_InfoGet(swimIndoorInfo_t *info)
{
	alg_swimIndoor_get_info(info);
	
	#if 1
	SCENE_SWIM_RTT_LOG(0, "Scene_Swim_InfoGet %d %d \n",
						info->RealTimeData.StrokeRate, info->RealTimeData.HR);
	#endif		
}

/*******************************************************************************
 * Brief : ��Ӿ��������
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Swim_Test(uint8_t fEvent)
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
						Scene_Swim_Enable();
						break;
					case 1:
						lsState = 0;
						Scene_Swim_Disable();
						break;
					default:
						break;
				}
        		break;
        	case MID_KEY0_HOLDSHORT:	// ����3����ʾ�˶��洢��Ϣ	
//				Store_Swim_DataRead();
//				vTaskDelay(10);
				Store_History_Test();
        		break;
        	default :
        		break;
        }
	}
	#endif	
}







