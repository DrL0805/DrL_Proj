#ifndef SCENE_SEDENTARY_H
#define SCENE_SEDENTARY_H

#include "platform_common.h"
#include "algorithm_sedentary.h"

#define SCENE_SEDENTARY_RTT_DEBUG	1
#if (1 == SCENE_SEDENTARY_RTT_DEBUG)	// 错误等级
#define SCENE_SEDENTARY_RTT_LOG(...)
#define SCENE_SEDENTARY_RTT_WARN(...)
#define SCENE_SEDENTARY_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_SEDENTARY_RTT_DEBUG)	// 警告等级
#define SCENE_SEDENTARY_RTT_LOG(...)
#define SCENE_SEDENTARY_RTT_WARN	RTT_DEBUG_WARN
#define SCENE_SEDENTARY_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_SEDENTARY_RTT_DEBUG)	// 调试等级
#define SCENE_SEDENTARY_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_SEDENTARY_RTT_WARN	RTT_DEBUG_WARN
#define SCENE_SEDENTARY_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define SCENE_SEDENTARY_RTT_LOG(...)
#define SCENE_SEDENTARY_RTT_WARN(...)
#define SCENE_SEDENTARY_RTT_ERR(...)
#endif

#define SCENE_SEDENTARY_PERIOD_MS	(1000)	// 算法调用周期

typedef struct 
{
    uint8_t StartTimeHour;
    uint8_t StartTimeMin;
    uint8_t StopTimeHour;
    uint8_t StopTimeMin;
    uint8_t DisturdStartTimehour;
    uint8_t DisturdStartTimeMin;
    uint8_t DisturdStopTimehour;
    uint8_t DisturdStopTimeMin;      
    uint16_t intv_mimute;
}SedentaryInfo_t;

typedef struct
{
	bool		InitFlg;
	bool		EnableFlg;		
	uint8_t		SampleId;
	uint32_t 	IntervalMs;
	
	SedentaryInfo_t	Info;
}SceneSedentaryParam_t;

extern void Scene_Sedentary_algorithm(int16 *xyzData, uint32_t Interval);
extern void Scene_Sedentary_Init(void);
extern void Scene_Sedentary_Reset(void);
extern void Scene_Sedentary_Enable(void);
extern void Scene_Sedentary_Disable(void);
extern SceneSedentaryParam_t* Scene_Sedentary_ParamPGet(void);
extern void Scene_Sedentary_Test(void);

#endif

