#include "scene_step.h"
#include "algorithm_lis3dh.h"
#include "mid_interface.h"
#include "ui_screen_warn.h"

SceneStepParam_t	SceneStepParam;

/*************** macro define ********************************/
#define CALORIECON0 	13.63636
#define CALORIECON1 	0.000693
#define CALORIECON2 	0.00495
#define DISTANCECON0 	0.45

/*******************************************************************************
 * Brief : @NULL
 * Input : @NULL
 * Return: @NULL
 * Call  : @NULL
 ***************/
void Scene_Step_Init(void)
{
	SceneStepParam.InitFlg = true;
	
	SceneStepParam.totalStep 		= 0;
	SceneStepParam.stepComplete 		= 0;
	SceneStepParam.stepAim 			= 6000;
	
	SceneStepParam.Calorie 		= 0;
	SceneStepParam.sportDistance 	= 0;

	SceneStepParam.sportDuaration 	= 0;
	
	SceneStepParam.DurationAlgo.SecCnt 								= 0;
	SceneStepParam.DurationAlgo.LastStep						= 0;
	SceneStepParam.RemindFlg 				= false;	
}

/*******************************************************************************
 * Brief : �Ʋ��㷨������ȡ�������ݻص�����
 * Input : @xyzData  ������������
		   @Interval �������ڣ���λms
 * Return: @NULL
 * Call  : 25HZƵ�ʽ��е���
 ***************/
void Scene_Step_Algorithm(int16 *xyzData, uint32_t Interval)
{
	if(!SceneStepParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Step_Algorithm", Ret_NoInit); 
	
	if(SceneStepParam.EnableFlg)
	{
		uint8     temp;
		uint8 	i;
		int8  	G_sensorBuf[3];		
		
		SceneStepParam.IntervalMs += Interval;
		if(SceneStepParam.IntervalMs >= SPORT_SCENE_PERIOD_MS)
		{
			SceneStepParam.IntervalMs -= SPORT_SCENE_PERIOD_MS;
			//�Ʋ��˶��㷨����
			for(i = 0; i < 3; i ++)
			{		
				G_sensorBuf[i]	= (xyzData[i]>>8);
			}
			temp  = Algorithm_Calculate_Step((uint8*)G_sensorBuf);
			
	//		SCENE_STEP_RTT_LOG(0, "Scene_Step_Algorithm %d %d %d \n", G_sensorBuf[0], G_sensorBuf[1], G_sensorBuf[2]);

			if(temp == 1 || temp == 12)
			{
				SceneStepParam.totalStep      += temp;
				SceneStepParam.Step5MinCnt += temp;
				
				SceneStepParam.stepComplete   = (uint16)(SceneStepParam.totalStep * 100 / SceneStepParam.stepAim);
				if(SceneStepParam.stepComplete >= 100)
				{
					if(SceneStepParam.stepComplete >= 999)
					{
						SceneStepParam.stepComplete = 999;
					}
					
					if (false == SceneStepParam.RemindFlg)		//�״����ִ������
					{
						SceneStepParam.RemindFlg = true;
						
						/* �����˶�Ŀ�����¼� */
						UI_Screen_Show_Warn_Screen_Steptarget();
						Mid_Motor_ShakeStart(eMidMotorShake2Hz, 5);
					}
				}

				SceneStepParam.Calorie  = SceneStepParam.totalStep * ((gtBodyInfo.Weight - CALORIECON0) * CALORIECON1 + CALORIECON2);
				SceneStepParam.sportDistance = gtBodyInfo.Height * DISTANCECON0 * SceneStepParam.totalStep / 100 ;
			
				SCENE_STEP_RTT_LOG(0, "Step Dis Dur Cal %d %d %d %d \n", 
					SceneStepParam.totalStep, SceneStepParam.sportDistance, SceneStepParam.sportDuaration, SceneStepParam.Calorie);
			}		
		}		
	}
}

/*******************************************************************************
 * Brief : �Ʋ��˶�����
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Step_Enable(void)
{
	if(!SceneStepParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Step_Enable", Ret_NoInit); 
	if(SceneStepParam.EnableFlg) drERROR_CHECK_RETURN_NULL("Scene_Step_Enable", ret_RepetitiveOperate); 

	Mid_6Dof_AccStart(BMI160_ACCEL_ODR_25HZ);
	
	SceneStepParam.IntervalMs = 0;
	SceneStepParam.EnableFlg = true;
}

/*******************************************************************************
 * Brief : �Ʋ��˶��ر�
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Step_Disable(void)
{
	if(!SceneStepParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Step_Disable", Ret_NoInit); 
	
	Mid_6Dof_AccStop(BMI160_ACCEL_ODR_25HZ);
	
	SceneStepParam.EnableFlg = false;
}

SceneStepParam_t* Scene_Step_ParamPGet(void)
{
	return &SceneStepParam;
}

/*******************************************************************************
 * Brief : �˶���Ϣ����
 * Input : @NULL
 * Return: @NULL
 * Call  : ÿ�����һ��
 ***************/
void Scene_Step_Clear(void)
{
	SceneStepParam.totalStep 		= 0;
	SceneStepParam.stepComplete 		= 0;
	
	SceneStepParam.Calorie 		= 0;
	SceneStepParam.sportDistance 	= 0;
	SceneStepParam.sportDuaration 	= 0;
	
	SceneStepParam.DurationAlgo.SecCnt 							= 0;
	SceneStepParam.DurationAlgo.LastStep							= 0;
	SceneStepParam.RemindFlg 				= false;
}

/*******************************************************************************
 * Brief : ���üƲ��˶�Ŀ�경��
 * Input : @NULL
 * Return: @NULL
 * Call  : �ⲿ���յ����ò���ָ��������ݻָ�
 ***************/
void Scene_Step_AimSet(uint32 stepAim)
{
	SceneStepParam.stepAim 		= stepAim;
	SceneStepParam.stepComplete   = (uint16)(SceneStepParam.totalStep * 100 / SceneStepParam.stepAim);
    if(SceneStepParam.stepComplete >= 100)
    {
   	 	if(SceneStepParam.stepComplete >= 999)
		{
			SceneStepParam.stepComplete = 999;
		}
			
   	 	if (false == SceneStepParam.RemindFlg)		//�״����ִ������
   	 	{
   	 		SceneStepParam.RemindFlg = true;
   	 		
			/* �����˶�Ŀ�����¼� */
			UI_Screen_Show_Warn_Screen_Steptarget();
			Mid_Motor_ShakeStart(eMidMotorShake2Hz, 5);			
   	 	}
    }
    else
    {
    	SceneStepParam.RemindFlg = false;				//�������
    }
}

/*******************************************************************************
 * Brief : �Ʋ��˶�ʱ���ۼ��㷨��ÿ1�����һ��
 * Input : @NULL
 * Return: @NULL
 * Call  : ÿ�����һ�Σ�����1min����һ�Ρ���Ϊֻ�в����Ʋ�������Ч�˶�
 ***************/
void Scene_Step_DuarationAlgo(void)
{
	if (SceneStepParam.DurationAlgo.LastStep != SceneStepParam.totalStep)
	{
		SceneStepParam.DurationAlgo.SecCnt ++;
		SceneStepParam.DurationAlgo.LastStep = SceneStepParam.totalStep;

//		SCENE_STEP_RTT_LOG(0, "SceneStepParam.DurationAlgo.SecCnt %d \n", SceneStepParam.DurationAlgo.SecCnt);
		
		if (SceneStepParam.DurationAlgo.SecCnt >= 60)
		{
			SceneStepParam.DurationAlgo.SecCnt = 0;
			SceneStepParam.sportDuaration 	+= 1;
			
//			SCENE_STEP_RTT_LOG(0, "SceneStepParam.sportDuaration %d \n", SceneStepParam.sportDuaration);
		}
	}
}

uint32 Scene_Step_5minCntRead(void)
{
	uint32_t lTmp = SceneStepParam.Step5MinCnt;
	
	SceneStepParam.Step5MinCnt = 0;	// û����ȡ�����
	
	return lTmp;
}


