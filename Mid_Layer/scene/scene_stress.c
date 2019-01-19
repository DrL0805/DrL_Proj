#include "scene_stress.h"
#include "mid_interface.h"
#include "store_interface.h"

Scene_Stress_Param_t	Scene_Stress;

/*********************************************************************
 * Brief : 人体压力场景初始化
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ************/
void Scene_Stress_Init(void)
{
	alg_stress_init();
	
	Scene_Stress.PendCnt = 0;
	Scene_Stress.InitFlg = true;
}

/*********************************************************************
 * Brief : 人体压力算法
 * Input : @NULL
 * Return: @NULL
 * Call  : 人体压力硬件测量完成后调用
 ************/
void Scene_Stress_algorithm(float sdnn, float rmssd, float rri, uint8_t hr)
{
	if(Scene_Stress.EnableFlg)
	{
		alg_stress_process(sdnn, rmssd, rri, hr);
	}
	
	// 计算完后立马更新压力值
	stress_t	tStress;
	alg_stress_get_score(&tStress);
	memcpy(&Scene_Stress.CurrStress, &tStress, sizeof(stress_t));
	memcpy(&Scene_Stress.LastStress, &tStress, sizeof(stress_t));
	Scene_Stress.UpdateFlg = true;
}

/*********************************************************************
 * Brief : 检测是否有后台人体压力需要采样
 * Input : @NULL 
 * Return: 
 * Call  : 每秒调用一次
 ************/
void Scene_Stress_BGSampleCheck(void)
{
	if(!Scene_Stress.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Stress_BGSampleCheck", Ret_NoInit);  
	
	Mid_Hrm_Param_t* tMid_Hrm = Mid_Hrm_ParamPGet();	
	
	if(Scene_Stress.EnableFlg)
	{
		if(Scene_Stress.PendCnt && (eMidHrmStateIdle == tMid_Hrm->State))
		/* 有待测量的人体压力 && 后台测量不打断当前测量 */
		{
	//		SCENE_STRESS_RTT_LOG(0, "Scene_Stress_BGSampleCheck \n");
			Mid_Hrm_Start(eHrmMeasureHrvOnce);
		}	
	}
}

/*********************************************************************
 * Brief : 算法使能
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ************/
void Scene_Stress_Enable(void)
{
	Scene_Stress.EnableFlg = true;
}

/*********************************************************************
 * Brief : 算法禁止
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ************/
void Scene_Stress_Disable(void)
{
	Scene_Stress.EnableFlg = false;
}

/*********************************************************************
 * Brief : 人体压力测量完成处理，用于对本次测量结果进行分析、存储等操作
 * Input : @NULL 
 * Return: @NULL
 * Call  : 获得一次人体压力测量结果后调用
 ************/
void Scene_Stress_SampleComplete(void)
{
	Mid_Hrm_Param_t* tMid_Hrm = Mid_Hrm_ParamPGet();
	
	/* 若有，当前测量结果作为后台测量结果（无论是即时测量结果还是后台测量结果） */ 
	if(Scene_Stress.PendCnt)
	{
		Scene_Stress.PendCnt--;
		
		/* 人体压力存储存储算法 */
		Store_Stress_algorithm();
	}
	
	if(eHrmMeasureHrvOnce == tMid_Hrm->MeasureType)
	/* 若是单次测量，停止测量 */
	{
		Mid_Hrm_Stop();
	}	
}

/*********************************************************************
 * Brief : 开始一次人体压力测量，
 * Input : @feMeasure 测量方法: 即时测量/后台测量 
 * Return: @NULL
 * Call  : 
 ************/
void Scene_Stress_SampleStart(eSceneMeasureWay feMeasure)
{
	if(!Scene_Stress.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Stress_SampleStart", Ret_NoInit); 

	Mid_Hrm_Param_t* tMid_Hrm = Mid_Hrm_ParamPGet();
	
	switch (feMeasure)
    {
    	case eSceneMeasureIM:
			/* 若当前测量为持续测量，不允许即时测量*/
			if((eHrmMeasureHrdKeep == tMid_Hrm->MeasureType) || (eHrmMeasureHrvKeep == tMid_Hrm->MeasureType))
				drERROR_CHECK_RETURN_NULL("Scene_Stress_SampleStart", Ret_DeviceBusy);				
		
			if(eMidHrmStateIdle != tMid_Hrm->State)
			/* 即时测量先关闭当前测量 */
			{
				Mid_Hrm_Stop();
			}
			Mid_Hrm_Start(eHrmMeasureHrvOnce);
			
			Scene_Stress.UpdateFlg = false;	
    		break;
    	case eSceneMeasureBG:
			/* 后台待测量次数+1，每秒检测是否需要测量 */
			Scene_Stress.PendCnt++;
		
			/* 若当前测量为持续测量，测量值为当前值 */
			if((eHrmMeasureHrdKeep == tMid_Hrm->MeasureType) || (eHrmMeasureHrvKeep == tMid_Hrm->MeasureType))
			{
				Scene_Stress_SampleComplete();
			}
    		break;
		case eSceneMeasureKeep:
			/* 若当前测量为持续测量，不重复开启*/
			if((eHrmMeasureHrdKeep == tMid_Hrm->MeasureType) || (eHrmMeasureHrvKeep == tMid_Hrm->MeasureType))
				return ;
			
			if(eMidHrmStateIdle != tMid_Hrm->State)
			/* 先关闭当前测量 */
			{
				Mid_Hrm_Stop();
			}
			Mid_Hrm_Start(eHrmMeasureHrvKeep);			
			break;
    	default :
			drERROR_CHECK("Scene_Stress_SampleStart", Ret_InvalidParam);
    		break;
    }	
}

/*********************************************************************
 * Brief : 停止当前人体压力测量
 * Input : @NULL 
 * Return: @NULL 
 * Call  : 
 ************/
void Scene_Stress_SampleStop(eSceneMeasureWay feMeasure)
{
	if(!Scene_Stress.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Stress_SampleStop", Ret_NoInit); 		
	
	Mid_Hrm_Param_t* tMid_Hrm = Mid_Hrm_ParamPGet();
	
	switch (feMeasure)
    {
    	case eSceneMeasureIM:
    	case eSceneMeasureBG:
			/* 若当前测量为持续测量，不允许停止高优先级的持续测量 
			   场景举例，当前跑步模式处于持续测量状态，用户让跑步后台运行进入心率界面在退出，
				这样可能调用 Scene_Hrm_SampleStop(IM)，这种情况下不允许停止心率采样
			*/
			if((eHrmMeasureHrdKeep == tMid_Hrm->MeasureType) || (eHrmMeasureHrvKeep == tMid_Hrm->MeasureType))
				drERROR_CHECK_RETURN_NULL("Scene_Stress_SampleStop", Ret_DeviceBusy);

			Mid_Hrm_Stop();
    		break;
		case eSceneMeasureKeep:
			Mid_Hrm_Stop();		
			break;
    	default :
			drERROR_CHECK("Scene_Stress_SampleStop", Ret_InvalidParam);
    		break;
    }
}

/*********************************************************************
 * Brief : 获取心率场景参数
 * Input : @Scene_Stress_Param 参数结构体 
 * Return: @NULL
 * Call  : 
 ************/
Scene_Stress_Param_t* Scene_Stress_ParamPGet(void)
{
	return &Scene_Stress;
}

/*********************************************************************
 * Brief : 设置当前压力值
 * Input : @Stress 参数结构体 
 * Return: @NULL
 * Call  : 
 ************/
void Scene_Stress_CurrScoreSet(stress_t* Stress)
{
	memcpy(&Scene_Stress.CurrStress, Stress, sizeof(stress_t));
}

/*********************************************************************
 * Brief : 获取当前压力值
 * Input : @Stress 参数结构体 
 * Return: @NULL
 * Call  : 
 ************/
void Scene_Stress_CurrScoreGet(stress_t* Stress)
{
	memcpy(Stress, &Scene_Stress.CurrStress, sizeof(stress_t));
}

/*********************************************************************
 * Brief : 本次测量失败，但是需设置数据参数更新（数据无效），用于UI显示
 * Input : @NULL
 * Return: @NULL
 * Call  : 测量错误/超时后调用
 ************/
void Scene_Stress_CurrScoreInvalid(void)
{
	/* 压力停止测量后，设置为可读状态，但是数据为无效数据 */
	Scene_Stress.UpdateFlg = true;
	Scene_Stress.CurrStress.level = 0;
	Scene_Stress.CurrStress.score = STRESS_INVALID_SCORE;
}



