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
 * Brief : 计步算法处理，读取重力数据回调处理
 * Input : @xyzData  重力三轴数据
		   @Interval 采样周期，单位ms
 * Return: @NULL
 * Call  : 25HZ频率进行调用
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
			//计步运动算法处理　
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
					
					if (false == SceneStepParam.RemindFlg)		//首次完成执行提醒
					{
						SceneStepParam.RemindFlg = true;
						
						/* 发送运动目标达成事件 */
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
 * Brief : 计步运动开启
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
 * Brief : 计步运动关闭
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
 * Brief : 运动信息清零
 * Input : @NULL
 * Return: @NULL
 * Call  : 每天调用一次
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
 * Brief : 设置计步运动目标步数
 * Input : @NULL
 * Return: @NULL
 * Call  : 外部，收到设置步数指令或者数据恢复
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
			
   	 	if (false == SceneStepParam.RemindFlg)		//首次完成执行提醒
   	 	{
   	 		SceneStepParam.RemindFlg = true;
   	 		
			/* 发送运动目标达成事件 */
			UI_Screen_Show_Warn_Screen_Steptarget();
			Mid_Motor_ShakeStart(eMidMotorShake2Hz, 5);			
   	 	}
    }
    else
    {
    	SceneStepParam.RemindFlg = false;				//标记清零
    }
}

/*******************************************************************************
 * Brief : 计步运动时长累加算法，每1秒调用一次
 * Input : @NULL
 * Return: @NULL
 * Call  : 每秒调用一次，不可1min调用一次。因为只有产生计步才算有效运动
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
	
	SceneStepParam.Step5MinCnt = 0;	// 没出读取后清空
	
	return lTmp;
}


