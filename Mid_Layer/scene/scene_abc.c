#include "scene_abc.h"
#include "mid_interface.h"

Scene_ABC_Param_t	Scene_ABC;

// ************************************************************
// ABC��ѹ���� ************************************************
// ************************************************************

 /*******************************************************************************
 * Brief : ��ѹ�߶ȳ�����ʼ��
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_ABC_ABInit(void)
{
	Scene_ABC.Pressure.InitFlg = true;
}

 /*******************************************************************************
 * Brief : ��ѹ�߶��㷨��ÿ�����һ�Σ�ÿ��ɼ�һ����ѹֵ������ʹӲ����ѹû�и��£�Ҳ��Ҫ����һ��
 * Input : @NULL
 * Return: @NULL
 * Call  : ÿ�����һ��
 ***************/
void Scene_ABC_ABalgorithm(void)
{
	if(!Scene_ABC.Pressure.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_ABC_ABalgorithm", Ret_NoInit); 

	static uint32_t stIntervalCnt = 0;	// ��ѹ��������������빦�ĵ�Ȩ��
	MID_PRESS_PARA_T*	lpMidPressParam = Mid_Press_ParamPGet();

	if(lpMidPressParam->PressUpdateFlg)
	/* �������ɼ�����ѹ���Ŵ����㷨 */
	{
		SCENE_ABC_RTT_LOG(0, "Scene_ABC_ABalgorithm %d \n", lpMidPressParam->LastPress);
		
		alg_ab_update_pressure(lpMidPressParam->LastPress);	// 1�����һ�Σ���ѹ�㷨
		Scene_ABC.Pressure.UpdateFlg = true;
		
		if(Scene_ABC.Pressure.EnableFlg && (++stIntervalCnt >= 5))
		/* AB����ʹ���Ҵﵽ����ֵ��������һ����ѹ�¶Ȳ��� 
		   ע����ѹ�㷨��ÿ�����һ�Σ������ǹ��ģ���ѹӲ������ÿ��ɼ�һ�� */
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
 * Brief : ����һ��Ӳ����ѹ�������ݲɼ�
 * Input : @NULL
 * Return:	
 * Call  : ��ɼ���ѹ����ʱ����
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
 * Brief : ֹͣ��ѹ�߶ȳ���
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
 * Brief : ��ȡ������ѹ����
 * Input : @ab_value ���ݽṹ��
 * Return:	
 * Call  :
 ************/
void Scene_ABC_ABGet(ab_value_t *ab_value)
{
	alg_ab_get(ab_value);	
}

// *****************************************************************************
// ABC���̳��� *****************************************************************
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
 * Brief : ��ʼУ׼
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
 * Brief : ����У׼�㷨������ʹ��ǰ��ҪУ׼��У׼��ɺ���ش�ֵ�Ϳ���ֱ��
		   �����������Ҫ��25Hz����
 * Input : 
 * Return:	
 * Call  : 25Hz����
 ************/
void Scene_ABC_CompassAlgorithm(int16* data)
{
	if(Scene_ABC.Compass.CalibrationFlg)
	{
		uint8_t CalRel = alg_compass_calibration(data, Scene_ABC.Compass.calParm);
		if(COMPASS_CAL_DONE == CalRel)
		{
			// У׼�ɹ�
			Scene_ABC.Compass.CalibrationFlg = false;
			SCENE_ABC_RTT_LOG(0, "COMPASS_CAL_DONE \n");
		}
		else if(COMPASS_CAL_NONE == CalRel)
		{
			// У׼ʧ��
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
 * Brief : ʹ�����̣��򿪵ش�25Hz����
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
 * Brief : �������̣��رյش�25Hz����
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
 * Brief : ��ȡ���̽Ƕ���Ϣ
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









