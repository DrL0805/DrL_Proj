#ifndef SCENE_ABC_H
#define SCENE_ABC_H

#include "platform_common.h"
#include "algorithm_abc.h"


#define SCENE_ABC_RTT_DEBUG	2
#if (1 == SCENE_ABC_RTT_DEBUG)	// ����ȼ�
#define SCENE_ABC_RTT_LOG(...)
#define SCENE_ABC_RTT_WARN(...)
#define SCENE_ABC_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_ABC_RTT_DEBUG)	// ����ȼ�
#define SCENE_ABC_RTT_LOG(...)
#define SCENE_ABC_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_ABC_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_ABC_RTT_DEBUG)	// ���Եȼ�
#define SCENE_ABC_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_ABC_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_ABC_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define SCENE_ABC_RTT_LOG(...)
#define SCENE_ABC_RTT_WARN(...)
#define SCENE_ABC_RTT_ERR(...)
#endif

typedef struct
{
	uint8_t		InitFlg;		// ��ʼ��־
	uint8_t		EnableFlg;		// �㷨ʹ�ܱ�־
	uint8_t		UpdateFlg;		// ��ѹ�㷨���£����ݿɶ�����־
}Scene_ABC_Pressure_t;

typedef struct
{
	uint8_t		InitFlg;		// ��ʼ��־
	uint8_t		EnableFlg;		// �㷨ʹ�ܱ�־
	
	uint8_t		CalibrationFlg;	// ����У׼��־
	uint8_t		calParm[17];	// �㷨У׼����
}Scene_ABC_Compass_t;

typedef struct
{
	Scene_ABC_Pressure_t	Pressure;
	Scene_ABC_Compass_t		Compass;
}Scene_ABC_Param_t;

// ABC��ѹ���� ************************************************
void Scene_ABC_ABInit(void);
void Scene_ABC_ABalgorithm(void);
void Scene_ABC_ABEnable(void);
void Scene_ABC_ABDisable(void);
void Scene_ABC_ABGet(ab_value_t *ab_value);		// ������ѹ��ȡ

// ABC���̳��� ************************************************
void Scene_ABC_CompassInit(void);
void Scene_ABC_CompassCalibrationStart(void);	// ��ʼУ׼
void Scene_ABC_CompassAlgorithm(int16* data);
void Scene_ABC_CompassEnable(void);				// ��ʼ���̳���
void Scene_ABC_CompassDisable(void);				// ֹͣ���̳���
calState_e Scene_ABC_CompassAngleGet(uint16_t *angle);		// ��ȡ��������

extern Scene_ABC_Param_t* Scene_ABC_ParamPGet(void);

#endif



