#include "scene_abc.h"
#include "mid_interface.h"

Scene_ABC_Param_t	Scene_ABC;

// ************************************************************
// ABC气压场景 ************************************************
// ************************************************************

 /*******************************************************************************
 * Brief : 气压高度场景初始化
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_ABC_ABInit(void)
{
	Scene_ABC.Pressure.InitFlg = true;
}

 /*******************************************************************************
 * Brief : 气压高度算法，每秒调用一次（每秒采集一起气压值），即使硬件气压没有更新，也需要调用一次
 * Input : @NULL
 * Return: @NULL
 * Call  : 每秒调用一次
 ***************/
void Scene_ABC_ABalgorithm(void)
{
	if(!Scene_ABC.Pressure.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_ABC_ABalgorithm", Ret_NoInit); 

	static uint32_t stIntervalCnt = 0;	// 气压测量间隔，性能与功耗的权衡
	MID_PRESS_PARA_T*	lpMidPressParam = Mid_Press_ParamPGet();

	if(lpMidPressParam->PressUpdateFlg)
	/* 传感器采集到气压，才传入算法 */
	{
		SCENE_ABC_RTT_LOG(0, "Scene_ABC_ABalgorithm %d \n", lpMidPressParam->LastPress);
		
		alg_ab_update_pressure(lpMidPressParam->LastPress);	// 1秒更新一次，气压算法
		Scene_ABC.Pressure.UpdateFlg = true;
		
		if(Scene_ABC.Pressure.EnableFlg && (++stIntervalCnt >= 5))
		/* AB场景使能且达到计数值，开启新一次气压温度测量 
		   注：气压算法需每秒调用一次，但考虑功耗，气压硬件不必每秒采集一次 */
		{
			stIntervalCnt = 0;

			Mid_Schd_TaskMsg_T Msg;
			
			Msg.Id = eSchdTaskMsgPressure;
			Msg.Param.Pressure.Id = ePressEventStartSample;
			Mid_Schd_TaskEventSet(&Msg);	
		}	
	}
}

/*********************************************************************
 * Brief : 开启一次硬件气压环温数据采集
 * Input : @NULL
 * Return:	
 * Call  : 需采集气压环温时调用
 ************/
void Scene_ABC_ABEnable(void)
{
	if(!Scene_ABC.Pressure.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_ABC_ABEnable", Ret_NoInit); 
	
	Mid_Schd_TaskMsg_T Msg;
	
	Msg.Id = eSchdTaskMsgPressure;
	Msg.Param.Pressure.Id = ePressEventStartSample;
	Mid_Schd_TaskEventSet(&Msg);		
	
	Scene_ABC.Pressure.EnableFlg = true;
}

/*********************************************************************
 * Brief : 停止气压高度场景
 * Input : @NULL
 * Return:	
 * Call  :
 ************/
void Scene_ABC_ABDisable(void)
{
	if(!Scene_ABC.Pressure.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_ABC_ABDisable", Ret_NoInit); 
	
	Scene_ABC.Pressure.EnableFlg = false;
}

/*********************************************************************
 * Brief : 获取海拔气压数据
 * Input : @ab_value 数据结构体
 * Return:	
 * Call  :
 ************/
void Scene_ABC_ABGet(ab_value_t *ab_value)
{
	alg_ab_get(ab_value);	
}

// *****************************************************************************
// ABC罗盘场景 *****************************************************************
// *****************************************************************************

/*********************************************************************
 * Brief : 
 * Input : 
 * Return:	
 * Call  :
 ************/
void Scene_ABC_CompassInit(void)
{
	alg_compass_init(Scene_ABC.Compass.calParm);
	Scene_ABC.Compass.InitFlg = true;
}

/*********************************************************************
 * Brief : 开始校准
 * Input : 
 * Return:	
 * Call  :
 ************/
void Scene_ABC_CompassCalibrationStart(void)
{
	SCENE_ABC_RTT_LOG(0, "Scene_ABC_CompassCalibrationStart \n");
	
	alg_compass_calibration_init();
	
	Scene_ABC.Compass.CalibrationFlg = true;
}

/*********************************************************************
 * Brief : 罗盘校准算法，罗盘使用前需要校准。校准完成后传入地磁值就可以直接
		   出结果。不需要再25Hz调用
 * Input : 
 * Return:	
 * Call  : 25Hz调用
 ************/
void Scene_ABC_CompassAlgorithm(int16* data)
{
	if(Scene_ABC.Compass.CalibrationFlg)
	{
		uint8_t CalRel = alg_compass_calibration(data, Scene_ABC.Compass.calParm);
		if(COMPASS_CAL_DONE == CalRel)
		{
			// 校准成功
			Scene_ABC.Compass.CalibrationFlg = false;
			SCENE_ABC_RTT_LOG(0, "COMPASS_CAL_DONE \n");
		}
		else if(COMPASS_CAL_NONE == CalRel)
		{
			// 校准失败
			Scene_ABC.Compass.CalibrationFlg = false;
			SCENE_ABC_RTT_LOG(0, "COMPASS_CAL_NONE \n");			
		}
		else
		{
//			SCENE_ABC_RTT_LOG(0, "COMPASS_CAL_ING \n");
		}
	}
}

/*********************************************************************
 * Brief : 使能罗盘，打开地磁25Hz采样
 * Input : 
 * Return:	
 * Call  : 
 ************/
void Scene_ABC_CompassEnable(void)
{
	SCENE_ABC_RTT_LOG(0, "Scene_ABC_CompassEnable \n");
	
	Mid_Schd_TaskMsg_T	Msg;
	
	Msg.Id = eSchdTaskMsgMagnetism;
	Msg.Param.Mag.Id = eMagEventStartSample;
	Mid_Schd_TaskEventSet(&Msg);	
	
	Scene_ABC.Compass.EnableFlg = true;
}

/*********************************************************************
 * Brief : 禁能罗盘，关闭地磁25Hz采样
 * Input : 
 * Return:	
 * Call  : 
 ************/
void Scene_ABC_CompassDisable(void)
{
	SCENE_ABC_RTT_LOG(0, "Scene_ABC_CompassDisable \n");
	
	Mid_Schd_TaskMsg_T	Msg;
	
	Msg.Id = eSchdTaskMsgMagnetism;
	Msg.Param.Mag.Id = eMagEventStopSample;
	Mid_Schd_TaskEventSet(&Msg);
	
	Scene_ABC.Compass.EnableFlg = false;
}

/*********************************************************************
 * Brief : 获取罗盘角度信息
 * Input : 
 * Return:	
 * Call  : 
 ************/
calState_e Scene_ABC_CompassAngleGet(uint16_t *angle)
{
	MID_MAG_PARA_T* ltpMagParm = Mid_Mag_ParamPGet();
	
	return alg_compass_getAngle(ltpMagParm->LatestData, angle);
}


Scene_ABC_Param_t* Scene_ABC_ParamPGet(void)
{
	return &Scene_ABC;
}









