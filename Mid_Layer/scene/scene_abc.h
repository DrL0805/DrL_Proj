#ifndef SCENE_ABC_H
#define SCENE_ABC_H

#include "platform_common.h"
#include "algorithm_abc.h"


#define SCENE_ABC_RTT_DEBUG	2
#if (1 == SCENE_ABC_RTT_DEBUG)	// 错误等级
#define SCENE_ABC_RTT_LOG(...)
#define SCENE_ABC_RTT_WARN(...)
#define SCENE_ABC_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_ABC_RTT_DEBUG)	// 警告等级
#define SCENE_ABC_RTT_LOG(...)
#define SCENE_ABC_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_ABC_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_ABC_RTT_DEBUG)	// 调试等级
#define SCENE_ABC_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_ABC_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_ABC_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define SCENE_ABC_RTT_LOG(...)
#define SCENE_ABC_RTT_WARN(...)
#define SCENE_ABC_RTT_ERR(...)
#endif

typedef struct
{
	uint8_t		InitFlg;		// 初始标志
	uint8_t		EnableFlg;		// 算法使能标志
	uint8_t		UpdateFlg;		// 气压算法更新（数据可读）标志
}Scene_ABC_Pressure_t;

typedef struct
{
	uint8_t		InitFlg;		// 初始标志
	uint8_t		EnableFlg;		// 算法使能标志
	
	uint8_t		CalibrationFlg;	// 正在校准标志
	uint8_t		calParm[17];	// 算法校准参数
}Scene_ABC_Compass_t;

typedef struct
{
	Scene_ABC_Pressure_t	Pressure;
	Scene_ABC_Compass_t		Compass;
}Scene_ABC_Param_t;

// ABC气压场景 ************************************************
void Scene_ABC_ABInit(void);
void Scene_ABC_ABalgorithm(void);
void Scene_ABC_ABEnable(void);
void Scene_ABC_ABDisable(void);
void Scene_ABC_ABGet(ab_value_t *ab_value);		// 海拔气压获取

// ABC罗盘场景 ************************************************
void Scene_ABC_CompassInit(void);
void Scene_ABC_CompassCalibrationStart(void);	// 开始校准
void Scene_ABC_CompassAlgorithm(int16* data);
void Scene_ABC_CompassEnable(void);				// 开始罗盘场景
void Scene_ABC_CompassDisable(void);				// 停止罗盘场景
calState_e Scene_ABC_CompassAngleGet(uint16_t *angle);		// 读取罗盘数据

extern Scene_ABC_Param_t* Scene_ABC_ParamPGet(void);

#endif



