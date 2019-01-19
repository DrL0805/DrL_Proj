#include "scene_stress.h"
#include "mid_interface.h"
#include "store_interface.h"

Scene_Stress_Param_t	Scene_Stress;

/*********************************************************************
 * Brief : ����ѹ��������ʼ��
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
 * Brief : ����ѹ���㷨
 * Input : @NULL
 * Return: @NULL
 * Call  : ����ѹ��Ӳ��������ɺ����
 ************/
void Scene_Stress_algorithm(float sdnn, float rmssd, float rri, uint8_t hr)
{
	if(Scene_Stress.EnableFlg)
	{
		alg_stress_process(sdnn, rmssd, rri, hr);
	}
	
	// ��������������ѹ��ֵ
	stress_t	tStress;
	alg_stress_get_score(&tStress);
	memcpy(&Scene_Stress.CurrStress, &tStress, sizeof(stress_t));
	memcpy(&Scene_Stress.LastStress, &tStress, sizeof(stress_t));
	Scene_Stress.UpdateFlg = true;
}

/*********************************************************************
 * Brief : ����Ƿ��к�̨����ѹ����Ҫ����
 * Input : @NULL 
 * Return: 
 * Call  : ÿ�����һ��
 ************/
void Scene_Stress_BGSampleCheck(void)
{
	if(!Scene_Stress.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Stress_BGSampleCheck", Ret_NoInit);  
	
	Mid_Hrm_Param_t* tMid_Hrm = Mid_Hrm_ParamPGet();	
	
	if(Scene_Stress.EnableFlg)
	{
		if(Scene_Stress.PendCnt && (eMidHrmStateIdle == tMid_Hrm->State))
		/* �д�����������ѹ�� && ��̨��������ϵ�ǰ���� */
		{
	//		SCENE_STRESS_RTT_LOG(0, "Scene_Stress_BGSampleCheck \n");
			Mid_Hrm_Start(eHrmMeasureHrvOnce);
		}	
	}
}

/*********************************************************************
 * Brief : �㷨ʹ��
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ************/
void Scene_Stress_Enable(void)
{
	Scene_Stress.EnableFlg = true;
}

/*********************************************************************
 * Brief : �㷨��ֹ
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ************/
void Scene_Stress_Disable(void)
{
	Scene_Stress.EnableFlg = false;
}

/*********************************************************************
 * Brief : ����ѹ��������ɴ������ڶԱ��β���������з������洢�Ȳ���
 * Input : @NULL 
 * Return: @NULL
 * Call  : ���һ������ѹ��������������
 ************/
void Scene_Stress_SampleComplete(void)
{
	Mid_Hrm_Param_t* tMid_Hrm = Mid_Hrm_ParamPGet();
	
	/* ���У���ǰ���������Ϊ��̨��������������Ǽ�ʱ����������Ǻ�̨��������� */ 
	if(Scene_Stress.PendCnt)
	{
		Scene_Stress.PendCnt--;
		
		/* ����ѹ���洢�洢�㷨 */
		Store_Stress_algorithm();
	}
	
	if(eHrmMeasureHrvOnce == tMid_Hrm->MeasureType)
	/* ���ǵ��β�����ֹͣ���� */
	{
		Mid_Hrm_Stop();
	}	
}

/*********************************************************************
 * Brief : ��ʼһ������ѹ��������
 * Input : @feMeasure ��������: ��ʱ����/��̨���� 
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
			/* ����ǰ����Ϊ����������������ʱ����*/
			if((eHrmMeasureHrdKeep == tMid_Hrm->MeasureType) || (eHrmMeasureHrvKeep == tMid_Hrm->MeasureType))
				drERROR_CHECK_RETURN_NULL("Scene_Stress_SampleStart", Ret_DeviceBusy);				
		
			if(eMidHrmStateIdle != tMid_Hrm->State)
			/* ��ʱ�����ȹرյ�ǰ���� */
			{
				Mid_Hrm_Stop();
			}
			Mid_Hrm_Start(eHrmMeasureHrvOnce);
			
			Scene_Stress.UpdateFlg = false;	
    		break;
    	case eSceneMeasureBG:
			/* ��̨����������+1��ÿ�����Ƿ���Ҫ���� */
			Scene_Stress.PendCnt++;
		
			/* ����ǰ����Ϊ��������������ֵΪ��ǰֵ */
			if((eHrmMeasureHrdKeep == tMid_Hrm->MeasureType) || (eHrmMeasureHrvKeep == tMid_Hrm->MeasureType))
			{
				Scene_Stress_SampleComplete();
			}
    		break;
		case eSceneMeasureKeep:
			/* ����ǰ����Ϊ�������������ظ�����*/
			if((eHrmMeasureHrdKeep == tMid_Hrm->MeasureType) || (eHrmMeasureHrvKeep == tMid_Hrm->MeasureType))
				return ;
			
			if(eMidHrmStateIdle != tMid_Hrm->State)
			/* �ȹرյ�ǰ���� */
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
 * Brief : ֹͣ��ǰ����ѹ������
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
			/* ����ǰ����Ϊ����������������ֹͣ�����ȼ��ĳ������� 
			   ������������ǰ�ܲ�ģʽ���ڳ�������״̬���û����ܲ���̨���н������ʽ������˳���
				�������ܵ��� Scene_Hrm_SampleStop(IM)����������²�����ֹͣ���ʲ���
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
 * Brief : ��ȡ���ʳ�������
 * Input : @Scene_Stress_Param �����ṹ�� 
 * Return: @NULL
 * Call  : 
 ************/
Scene_Stress_Param_t* Scene_Stress_ParamPGet(void)
{
	return &Scene_Stress;
}

/*********************************************************************
 * Brief : ���õ�ǰѹ��ֵ
 * Input : @Stress �����ṹ�� 
 * Return: @NULL
 * Call  : 
 ************/
void Scene_Stress_CurrScoreSet(stress_t* Stress)
{
	memcpy(&Scene_Stress.CurrStress, Stress, sizeof(stress_t));
}

/*********************************************************************
 * Brief : ��ȡ��ǰѹ��ֵ
 * Input : @Stress �����ṹ�� 
 * Return: @NULL
 * Call  : 
 ************/
void Scene_Stress_CurrScoreGet(stress_t* Stress)
{
	memcpy(Stress, &Scene_Stress.CurrStress, sizeof(stress_t));
}

/*********************************************************************
 * Brief : ���β���ʧ�ܣ��������������ݲ������£�������Ч��������UI��ʾ
 * Input : @NULL
 * Return: @NULL
 * Call  : ��������/��ʱ�����
 ************/
void Scene_Stress_CurrScoreInvalid(void)
{
	/* ѹ��ֹͣ����������Ϊ�ɶ�״̬����������Ϊ��Ч���� */
	Scene_Stress.UpdateFlg = true;
	Scene_Stress.CurrStress.level = 0;
	Scene_Stress.CurrStress.score = STRESS_INVALID_SCORE;
}



