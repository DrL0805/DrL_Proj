/*
	���ʳ�����������ʱ��������̨��������������
	ÿ2min��̨��������ֵCnt++��ÿ����Cntֵ��Cnt����ʱ������̨�������������������LogBuf�У�������ɺ�Cnt--
	��̨�������ɴ�ϼ�ʱ����������ʱ�������Դ�Ϻ�̨����������̨��������ʱ�������ʱ�������������
	���1����ʱ������Ч���򱾴μ�ʱ�������Ҳ��Ϊ��̨�����������̨Cnt--��
	���2����ʱ������Ч���򵱼�ʱ�����������رգ���ÿ�������¿�����̨����
	
	��ǰ״̬Ϊ��������ʱ�����ʺ�̨�������Ϊ��ǰ������ѹ����̨������Ч
*/

#include "scene_hrm.h"
#include "mid_interface.h"
#include "store_interface.h"
#include "scene_step.h"

SceneHrmParam_t	SceneHrmParam;

// ���þ�Ϣ�����㷨����
static void Scene_Hrm_RestAlgoReset(void)
{
	SceneHrmParam.RestAlgo.RunningFlg 		 = false;
	SceneHrmParam.RestAlgo.RestPeriodCnt			 = 0;
	SceneHrmParam.RestAlgo.AlgoLogCnt 		 = 0; 
	SceneHrmParam.RestAlgo.HalLogCnt = 0;
	
	SCENE_HRM_RTT_LOG(0, "Scene_Hrm_RestAlgoReset \n");
}

 /*******************************************************************************
 ** Brief : ��Ϣ�����㷨����ֲ�����ȵ�H001�㷨���㷨ԭ��
			ÿ6min��ȡһ�κ�̨�ɼ�������ֵ��������ֵ��Ч����������HalLogBuf��HalLogCnt++��
			HalLogCnt=3��ȡ��Сֵ������AlgoLogBuf�У�AlgoLogCnt++
			AlgoLogCnt=3�󣬿ɼ��㾲Ϣ����ֵ
			�����㷨�����ٵ��ô˺��� SCENE_HRM_REST_HAL_CNT_MAX*SCENE_HRM_REST_ALGO_CNT_MAX �κ󣬲��ܲ�����Ϣ����ֵ
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : ÿ6min����һ��
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

	/* �������ֵ��Ч�������㷨�����򱣴浱ǰ����ֵ */
	if(HRM_INVALID_VALUE == lpMidHrmParam->CurrHeartRate)
	{
		Scene_Hrm_RestAlgoReset();
	}
	else
	{
		if(SceneHrmParam.RestAlgo.HalLogCnt >= SCENE_HRM_REST_HAL_CNT_MAX)
		/* HalLogBuf[]��������FIFO�滻 */
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
	/* ��Ϊ�״������㷨����ʼ������ */
	{
		SceneHrmParam.RestAlgo.RunningFlg	= true;
		SceneHrmParam.RestAlgo.LastStep 	= lpSceneStepParam->totalStep;
		
		SCENE_HRM_RTT_LOG(0, "SceneHrmParam.RestAlgo.RunningFlg	= true \n");
	}
	else
	{
		SceneHrmParam.RestAlgo.RestPeriodCnt++;	// ��Ϣʱ���ۼ�
		if(lpSceneStepParam->totalStep != SceneHrmParam.RestAlgo.LastStep)
		/* �������Ʋ�����Ϣ�����㡣���þ�Ϣʱ�� */
		{
			SceneHrmParam.RestAlgo.RestPeriodCnt		= 0;	//��Ϣ��ϣ����¼�ʱ
			SceneHrmParam.RestAlgo.LastStep 		= lpSceneStepParam->totalStep;
		}

		if(SceneHrmParam.RestAlgo.HalLogCnt >= SCENE_HRM_REST_HAL_CNT_MAX)
		/* HalLogCut����������һ�ξ�Ϣ���� */
		{
			// ȡ��������logֵ����Сֵ
			u16Temp = SceneHrmParam.RestAlgo.HalLogBuf[0];
			for (i = 1; i < SCENE_HRM_REST_HAL_CNT_MAX; i++)
			{
				if (u16Temp > SceneHrmParam.RestAlgo.HalLogBuf[i])
				{
					u16Temp = SceneHrmParam.RestAlgo.HalLogBuf[i];
				}
			}

			if (SceneHrmParam.RestAlgo.AlgoLogCnt >= SCENE_HRM_REST_ALGO_CNT_MAX)
			/* AlgoLogCnt���������㾲Ϣ���� */
			{
				// �������ʲ�ֵ
			 	if (SceneHrmParam.RestAlgo.AlgoLogBuf[SCENE_HRM_REST_ALGO_CNT_MAX - 1] >= SceneHrmParam.RestAlgo.AlgoLogBuf[0])	// ������β������Ϣ���ʲ�ֵ
			 	{
			 		hrdelta 	= SceneHrmParam.RestAlgo.AlgoLogBuf[SCENE_HRM_REST_ALGO_CNT_MAX - 1] - SceneHrmParam.RestAlgo.AlgoLogBuf[0];
			 	}
			 	else
			 	{
			 		hrdelta 	= SceneHrmParam.RestAlgo.AlgoLogBuf[0] - SceneHrmParam.RestAlgo.AlgoLogBuf[SCENE_HRM_REST_ALGO_CNT_MAX - 1];
			 	}

			 	if (hrdelta > SCENE_HRM_REST_HR_BIAS)
				/* ���ʲ����󣬾�Ϣ��ϣ����¼�ʱ */
			 	{
			 		Scene_Hrm_RestAlgoReset();
			 	}
			 	else
			 	{
					if (SceneHrmParam.RestAlgo.RestPeriodCnt >= 3)
					/* ��Ϣ���ʲ���ȷ�ϳɹ����Ҿ�Ϣʱ������Ҫ�󣬱��澲Ϣ����ֵ������������һ�ξ�Ϣ�����ж� */	
					{
						u16Temp	  = 0;
						//ȡƽ��ֵ 
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
			/*  AlgoLogCntδ����AlgoLogCnt++  */
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
 * Brief : ����Ƿ��к�̨������Ҫ����
 * Input : @NULL 
 * Output: @NULL
 * Return: 
 * Call  : ÿ�����һ��
 ************/
void Scene_Hrm_BGSampleCheck(void)
{
	if(!SceneHrmParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Hrm_BGSampleCheck", Ret_NoInit);  
	
	Mid_Hrm_Param_t* tMid_Hrm = Mid_Hrm_ParamPGet();	
	
	if(SceneHrmParam.EnableFlg)
	{
		if(SceneHrmParam.PendCnt && (eMidHrmStateIdle == tMid_Hrm->State))
		/* �д����������� && ��̨��������ϵ�ǰ���� */
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
 * Brief : ���ʲ�����ɴ������ڶԱ��β���������з������洢�Ȳ���
 * Input : @NULL  
 * Return: @NULL 
 * Call  : ���ʲ�����ɺ����
 ************/
void Scene_Hrm_SampleComplete(void)
{
	if(!SceneHrmParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Hrm_SampleComplete", Ret_NoInit); 	
	
	Mid_Hrm_Param_t* tMid_Hrm = Mid_Hrm_ParamPGet();
	
	/* ���У���ǰ���������Ϊ��̨��������������Ǽ�ʱ����������Ǻ�̨��������� */ 
	if(SceneHrmParam.PendCnt)
	{
		SceneHrmParam.PendCnt--;
		
		SceneHrmParam.LatestHrm = tMid_Hrm->CurrHeartRate;
//		SceneHrmParam.LogCnt = (SceneHrmParam.LogCnt >= SCENE_HRM_MAX_LOG) ? 0 : (++SceneHrmParam.LogCnt);
//		SceneHrmParam.LogBuf[SceneHrmParam.LogCnt++] = SceneHrmParam.LatestHrm;			
		
		/* ���ʴ洢�㷨 */
		Store_Hrd_algorithm();
	}
	
	if(eHrmMeasureHrdOnce == tMid_Hrm->MeasureType)
	/* ���ǵ��β�����ֹͣ���� */
	{
		Mid_Hrm_Stop();
	}
}

/*********************************************************************
 * Brief : ��ʼһ�����ʲ�����
 * Input : @feMeasure ��������: ��ʱ����/��̨����/��������
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
			/* ����ǰ����Ϊ����������������ʱ����*/
			if((eHrmMeasureHrdKeep == tMid_Hrm->MeasureType) || (eHrmMeasureHrvKeep == tMid_Hrm->MeasureType))
				drERROR_CHECK_RETURN_NULL("Scene_Hrm_SampleStart", Ret_DeviceBusy);			
		
			if(eMidHrmStateIdle != tMid_Hrm->State)
			/* �ȹرյ�ǰ���� */
			{
				Mid_Hrm_Stop();
			}
			Mid_Hrm_Start(eHrmMeasureHrdOnce);
    		break;
    	case eSceneMeasureBG:
			/* ��̨����������+1��ÿ�����Ƿ���Ҫ���� */
			SceneHrmParam.PendCnt++;
		
			/* ����ǰ����Ϊ��������������ֵΪ��ǰֵ */
			if((eHrmMeasureHrdKeep == tMid_Hrm->MeasureType) || (eHrmMeasureHrvKeep == tMid_Hrm->MeasureType))
			{
				Scene_Hrm_SampleComplete();
			}				
    		break;
		case eSceneMeasureKeep:
			/* ����ǰ����Ϊ�������������ظ�����*/
			if((eHrmMeasureHrdKeep == tMid_Hrm->MeasureType) || (eHrmMeasureHrvKeep == tMid_Hrm->MeasureType))
				drERROR_CHECK_RETURN_NULL("Scene_Hrm_SampleStart", ret_RepetitiveOperate);	

			if(eMidHrmStateIdle != tMid_Hrm->State)
			/* �ȹرյ�ǰ���� */
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
 * Brief : ֹͣ��ǰ���ʲ���
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
			/* ����ǰ����Ϊ����������������ֹͣ�����ȼ��ĳ������� 
			   ������������ǰ�ܲ�ģʽ���ڳ�������״̬���û����ܲ���̨���н������ʽ������˳���
				�������ܵ��� Scene_Hrm_SampleStop(IM)����������²�����ֹͣ���ʲ���
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
 * Brief : ��ȡ���ʳ�������
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ************/
SceneHrmParam_t* Scene_Hrm_ParamPGet(void)
{
	return &SceneHrmParam;
}



/*********************************************************************
 * Brief : ��ȡ��Ϣ����ֵ
 * Input : @NULL
 * Output: @NULL 
 * Return: @��Ϣ����ֵ
 * Call  : 
 ************/
uint8_t Scene_Hrm_RestingHrvGet(void)
{
	return SceneHrmParam.RestAlgo.RestHr;
}






