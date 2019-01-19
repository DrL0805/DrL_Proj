#ifndef SCENE_STRESS_H
#define SCENE_STRESS_H

#include "scene_variable.h"
#include "algorithm_stress.h"



#define SCENE_STRESS_RTT_DEBUG	3
#if (1 == SCENE_STRESS_RTT_DEBUG)	// 错误等级
#define SCENE_STRESS_RTT_LOG(...)
#define SCENE_STRESS_RTT_WARN(...)
#define SCENE_STRESS_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_STRESS_RTT_DEBUG)	// 警告等级
#define SCENE_STRESS_RTT_LOG(...)
#define SCENE_STRESS_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_STRESS_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_STRESS_RTT_DEBUG)	// 调试等级
#define SCENE_STRESS_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_STRESS_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_STRESS_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define SCENE_STRESS_RTT_LOG(...)
#define SCENE_STRESS_RTT_WARN(...)
#define SCENE_STRESS_RTT_ERR(...)
#endif

#define STRESS_INVALID_SCORE	0x00	// 无效心率值

typedef struct
{
	bool		InitFlg;		// 初始标志
	bool		EnableFlg;		// 算法使能标志
	bool		UpdateFlg;		// 新数据可读标志
	
	uint8_t 	PendCnt;		// 待测量计数
	
	stress_t		CurrStress;		
	stress_t     	LastStress;
}Scene_Stress_Param_t;

extern void Scene_Stress_Init(void);
extern void Scene_Stress_BGSampleCheck(void);
extern void Scene_Stress_Enable(void);
extern void Scene_Stress_SampleStart(eSceneMeasureWay feMeasure);
extern void Scene_Stress_algorithm(float sdnn, float rmssd, float rri, uint8_t hr);
extern void Scene_Stress_SampleComplete(void);
extern void Scene_Stress_Start(void);
extern void Scene_Stress_SampleStop(eSceneMeasureWay feMeasure);
extern Scene_Stress_Param_t* Scene_Stress_ParamPGet(void);
void Scene_Stress_CurrScoreSet(stress_t* Stress);
void Scene_Stress_CurrScoreGet(stress_t* Stress);
void Scene_Stress_CurrScoreInvalid(void);

#endif

