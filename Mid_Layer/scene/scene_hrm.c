/*
	心率场景，包括即时测量、后台测量、持续测量
	每2min后台测量计数值Cnt++，每秒检测Cnt值，Cnt非零时开启后台测量，测量结果保存在LogBuf中，测量完成后Cnt--
	后台测量不可打断即时测量，但即时测量可以打断后台测量，当后台测量被即时测量打断时，有两种情况：
	情况1：即时测量有效，则本次即时测量结果也作为后台测量结果，后台Cnt--；
	情况2：即时测量无效，则当即时测量结束（关闭）后，每秒检测重新开启后台测量
	
	当前状态为持续测量时，心率后台测量结果为当前测量。压力后台测量无效
*/

#include "scene_hrm.h"
#include "mid_interface.h"
#include "store_interface.h"
#include "scene_step.h"

SceneHrmParam_t	SceneHrmParam;

// 重置静息心率算法参数
static void Scene_Hrm_RestAlgoReset(void)
{
	SceneHrmParam.RestAlgo.RunningFlg 		 = false;
	SceneHrmParam.RestAlgo.RestPeriodCnt			 = 0;
	SceneHrmParam.RestAlgo.AlgoLogCnt 		 = 0; 
	SceneHrmParam.RestAlgo.HalLogCnt = 0;
	
	SCENE_HRM_RTT_LOG(0, "Scene_Hrm_RestAlgoReset \n");
}

 /*******************************************************************************
 ** Brief : 静息心率算法（移植整理东尤的H001算法）算法原理：
			每6min获取一次后台采集的心率值，若心率值有效，保存在中HalLogBuf，HalLogCnt++。
			HalLogCnt=3后，取最小值保存在AlgoLogBuf中，AlgoLogCnt++
			AlgoLogCnt=3后，可计算静息心率值
			根据算法，至少调用此函数 SCENE_HRM_REST_HAL_CNT_MAX*SCENE_HRM_REST_ALGO_CNT_MAX 次后，才能产生静息心率值
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 每6min调用一次
 ***************/
void Scene_Hrm_RestAlgo(void)
{
	uint8 	hrdelta;
	uint8 	hrMinTemp;
	uint16 	u16Temp = 0;
	uint8 	i;
	SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
	Mid_Hrm_Param_t* lpMidHrmParam = Mid_Hrm_ParamPGet();
//	lpMidHrmParam->CurrHeartRate = 66;

	/* 如果心率值无效，重置算法。否则保存当前心率值 */
	if(HRM_INVALID_VALUE == lpMidHrmParam->CurrHeartRate)
	{
		Scene_Hrm_RestAlgoReset();
	}
	else
	{
		if(SceneHrmParam.RestAlgo.HalLogCnt >= SCENE_HRM_REST_HAL_CNT_MAX)
		/* HalLogBuf[]已满，则FIFO替换 */
		{
			for(i = 0; i < (SCENE_HRM_REST_HAL_CNT_MAX - 1); i++)
			{
				SceneHrmParam.RestAlgo.HalLogBuf[i]	= SceneHrmParam.RestAlgo.HalLogBuf[i + 1];
			}
			SceneHrmParam.RestAlgo.HalLogBuf[i]	= lpMidHrmParam->CurrHeartRate;			
		}
		else
		{
			SceneHrmParam.RestAlgo.HalLogBuf[SceneHrmParam.RestAlgo.HalLogCnt]	= lpMidHrmParam->CurrHeartRate;
			SceneHrmParam.RestAlgo.HalLogCnt++;
		}
	}

	SCENE_HRM_RTT_LOG(0, "HalLogBuf %d {[%d],[%d],[%d]} \n", SceneHrmParam.RestAlgo.HalLogCnt, SceneHrmParam.RestAlgo.HalLogBuf[0],
		SceneHrmParam.RestAlgo.HalLogBuf[1], SceneHrmParam.RestAlgo.HalLogBuf[2]);
	
	if(!SceneHrmParam.RestAlgo.RunningFlg)
	/* 若为首次运行算法，初始化参数 */
	{
		SceneHrmParam.RestAlgo.RunningFlg	= true;
		SceneHrmParam.RestAlgo.LastStep 	= lpSceneStepParam->totalStep;
		
		SCENE_HRM_RTT_LOG(0, "SceneHrmParam.RestAlgo.RunningFlg	= true \n");
	}
	else
	{
		SceneHrmParam.RestAlgo.RestPeriodCnt++;	// 静息时间累加
		if(lpSceneStepParam->totalStep != SceneHrmParam.RestAlgo.LastStep)
		/* 若产生计步，静息被打算。重置静息时间 */
		{
			SceneHrmParam.RestAlgo.RestPeriodCnt		= 0;	//静息打断，重新计时
			SceneHrmParam.RestAlgo.LastStep 		= lpSceneStepParam->totalStep;
		}

		if(SceneHrmParam.RestAlgo.HalLogCnt >= SCENE_HRM_REST_HAL_CNT_MAX)
		/* HalLogCut已满，计算一次静息数据 */
		{
			// 取最新三个log值的最小值
			u16Temp = SceneHrmParam.RestAlgo.HalLogBuf[0];
			for (i = 1; i < SCENE_HRM_REST_HAL_CNT_MAX; i++)
			{
				if (u16Temp > SceneHrmParam.RestAlgo.HalLogBuf[i])
				{
					u16Temp = SceneHrmParam.RestAlgo.HalLogBuf[i];
				}
			}

			if (SceneHrmParam.RestAlgo.AlgoLogCnt >= SCENE_HRM_REST_ALGO_CNT_MAX)
			/* AlgoLogCnt已满，计算静息心率 */
			{
				// 计算心率差值
			 	if (SceneHrmParam.RestAlgo.AlgoLogBuf[SCENE_HRM_REST_ALGO_CNT_MAX - 1] >= SceneHrmParam.RestAlgo.AlgoLogBuf[0])	// 计算首尾两个静息心率差值
			 	{
			 		hrdelta 	= SceneHrmParam.RestAlgo.AlgoLogBuf[SCENE_HRM_REST_ALGO_CNT_MAX - 1] - SceneHrmParam.RestAlgo.AlgoLogBuf[0];
			 	}
			 	else
			 	{
			 		hrdelta 	= SceneHrmParam.RestAlgo.AlgoLogBuf[0] - SceneHrmParam.RestAlgo.AlgoLogBuf[SCENE_HRM_REST_ALGO_CNT_MAX - 1];
			 	}

			 	if (hrdelta > SCENE_HRM_REST_HR_BIAS)
				/* 心率波动大，静息打断，重新计时 */
			 	{
			 		Scene_Hrm_RestAlgoReset();
			 	}
			 	else
			 	{
					if (SceneHrmParam.RestAlgo.RestPeriodCnt >= 3)
					/* 静息心率测量确认成功，且静息时间满足要求，保存静息心率值，并重新启动一次静息心率判断 */	
					{
						u16Temp	  = 0;
						//取平均值 
						for (i = 0; i < SCENE_HRM_REST_ALGO_CNT_MAX; i++)
						{
							u16Temp += SceneHrmParam.RestAlgo.AlgoLogBuf[i];
						}
						hrMinTemp = u16Temp / SCENE_HRM_REST_ALGO_CNT_MAX;

						if (hrMinTemp < SCENE_HRM_REST_HR_UP_LIMIT)
						{
							if (hrMinTemp < 30)
							{
								hrMinTemp = 30;
							}
						}
						
						SceneHrmParam.RestAlgo.RestHr = hrMinTemp;
						Scene_Hrm_RestAlgoReset();	
						
						SCENE_HRM_RTT_LOG(0, "SceneHrmParam.RestAlgo.RestHr %d \n", SceneHrmParam.RestAlgo.RestHr);					
					}
			 	}
			}
			else
			/*  AlgoLogCnt未满，AlgoLogCnt++  */
			{
				SceneHrmParam.RestAlgo.AlgoLogBuf[SceneHrmParam.RestAlgo.AlgoLogCnt] = u16Temp;		
				SceneHrmParam.RestAlgo.AlgoLogCnt++;
				
				SCENE_HRM_RTT_LOG(0, "AlgoLogBuf %d {[%d],[%d],[%d]} \n", SceneHrmParam.RestAlgo.AlgoLogCnt, SceneHrmParam.RestAlgo.AlgoLogBuf[0],
					SceneHrmParam.RestAlgo.AlgoLogBuf[1], SceneHrmParam.RestAlgo.AlgoLogBuf[2]);
			}
		}
	}	
}

/*********************************************************************
 * Brief : 检测是否有后台心率需要采样
 * Input : @NULL 
 * Output: @NULL
 * Return: 
 * Call  : 每秒调用一次
 ************/
void Scene_Hrm_BGSampleCheck(void)
{
	if(!SceneHrmParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Hrm_BGSampleCheck", Ret_NoInit);  
	
	Mid_Hrm_Param_t* tMid_Hrm = Mid_Hrm_ParamPGet();	
	
	if(SceneHrmParam.EnableFlg)
	{
		if(SceneHrmParam.PendCnt && (eMidHrmStateIdle == tMid_Hrm->State))
		/* 有待测量的心率 && 后台测量不打断当前测量 */
		{
	//		SCENE_HRM_RTT_LOG(0, "Scene_Hrm_BGSampleCheck \n");
			Mid_Hrm_Start(eHrmMeasureHrdOnce);
		}	
	}
}

void Scene_Hrm_Init(void)
{
	SceneHrmParam.LatestHrm = HRM_INVALID_VALUE;
	SceneHrmParam.PendCnt = 0;
	
	Scene_Hrm_RestAlgoReset();
	SceneHrmParam.RestAlgo.RestHr = HRM_INVALID_VALUE;
	
	SceneHrmParam.InitFlg = true;
}

void Scene_Hrm_Enable(void)
{
	if(!SceneHrmParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Hrm_Enable", Ret_NoInit); 
	
	SceneHrmParam.EnableFlg = true;
}

void Scene_Hrm_Disable(void)
{
	if(!SceneHrmParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Hrm_Disable", Ret_NoInit); 
	
	SceneHrmParam.EnableFlg = false;
}

/*********************************************************************
 * Brief : 心率测量完成处理，用于对本次测量结果进行分析、存储等操作
 * Input : @NULL  
 * Return: @NULL 
 * Call  : 心率测量完成后调用
 ************/
void Scene_Hrm_SampleComplete(void)
{
	if(!SceneHrmParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Hrm_SampleComplete", Ret_NoInit); 	
	
	Mid_Hrm_Param_t* tMid_Hrm = Mid_Hrm_ParamPGet();
	
	/* 若有，当前测量结果作为后台测量结果（无论是即时测量结果还是后台测量结果） */ 
	if(SceneHrmParam.PendCnt)
	{
		SceneHrmParam.PendCnt--;
		
		SceneHrmParam.LatestHrm = tMid_Hrm->CurrHeartRate;
//		SceneHrmParam.LogCnt = (SceneHrmParam.LogCnt >= SCENE_HRM_MAX_LOG) ? 0 : (++SceneHrmParam.LogCnt);
//		SceneHrmParam.LogBuf[SceneHrmParam.LogCnt++] = SceneHrmParam.LatestHrm;			
		
		/* 心率存储算法 */
		Store_Hrd_algorithm();
	}
	
	if(eHrmMeasureHrdOnce == tMid_Hrm->MeasureType)
	/* 若是单次测量，停止测量 */
	{
		Mid_Hrm_Stop();
	}
}

/*********************************************************************
 * Brief : 开始一次心率测量，
 * Input : @feMeasure 测量方法: 即时测量/后台测量/持续测量
 * Return: @NULL
 * Call  : 
 ************/
void Scene_Hrm_SampleStart(eSceneMeasureWay feMeasure)
{
	if(!SceneHrmParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Hrm_SampleStart", Ret_NoInit); 
	
	Mid_Hrm_Param_t* tMid_Hrm = Mid_Hrm_ParamPGet();
	
	switch (feMeasure)
    {
    	case eSceneMeasureIM:
			/* 若当前测量为持续测量，不允许即时测量*/
			if((eHrmMeasureHrdKeep == tMid_Hrm->MeasureType) || (eHrmMeasureHrvKeep == tMid_Hrm->MeasureType))
				drERROR_CHECK_RETURN_NULL("Scene_Hrm_SampleStart", Ret_DeviceBusy);			
		
			if(eMidHrmStateIdle != tMid_Hrm->State)
			/* 先关闭当前测量 */
			{
				Mid_Hrm_Stop();
			}
			Mid_Hrm_Start(eHrmMeasureHrdOnce);
    		break;
    	case eSceneMeasureBG:
			/* 后台待测量次数+1，每秒检测是否需要测量 */
			SceneHrmParam.PendCnt++;
		
			/* 若当前测量为持续测量，测量值为当前值 */
			if((eHrmMeasureHrdKeep == tMid_Hrm->MeasureType) || (eHrmMeasureHrvKeep == tMid_Hrm->MeasureType))
			{
				Scene_Hrm_SampleComplete();
			}				
    		break;
		case eSceneMeasureKeep:
			/* 若当前测量为持续测量，不重复开启*/
			if((eHrmMeasureHrdKeep == tMid_Hrm->MeasureType) || (eHrmMeasureHrvKeep == tMid_Hrm->MeasureType))
				drERROR_CHECK_RETURN_NULL("Scene_Hrm_SampleStart", ret_RepetitiveOperate);	

			if(eMidHrmStateIdle != tMid_Hrm->State)
			/* 先关闭当前测量 */
			{
				Mid_Hrm_Stop();
			}
			Mid_Hrm_Start(eHrmMeasureHrdKeep);
			break;
    	default :
			drERROR_CHECK("Scene_Hrm_SampleStart", Ret_InvalidParam);
    		break;
    }
}

/*********************************************************************
 * Brief : 停止当前心率测量
 * Input : @NULL 
 * Output: @NULL 
 * Return: @NULL
 * Call  : 
 ************/
void Scene_Hrm_SampleStop(eSceneMeasureWay feMeasure)
{
	if(!SceneHrmParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Hrm_SampleStop", Ret_NoInit); 		
	
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
				drERROR_CHECK_RETURN_NULL("Scene_Hrm_SampleStop", Ret_DeviceBusy);

			Mid_Hrm_Stop();
    		break;
		case eSceneMeasureKeep:
			Mid_Hrm_Stop();		
			break;
    	default :
			drERROR_CHECK("Scene_Hrm_SampleStart", Ret_InvalidParam);
    		break;
    }
}

/*********************************************************************
 * Brief : 获取心率场景参数
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ************/
SceneHrmParam_t* Scene_Hrm_ParamPGet(void)
{
	return &SceneHrmParam;
}



/*********************************************************************
 * Brief : 获取静息心率值
 * Input : @NULL
 * Output: @NULL 
 * Return: @静息心率值
 * Call  : 
 ************/
uint8_t Scene_Hrm_RestingHrvGet(void)
{
	return SceneHrmParam.RestAlgo.RestHr;
}






