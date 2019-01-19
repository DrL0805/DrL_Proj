#ifndef SCENE_SWIM_H
#define SCENE_SWIM_H

#include "scene_variable.h"
#include "algorithm_swim_indoor.h"

#define SCENE_SWIM_RTT_DEBUG	3
#if (1 == SCENE_SWIM_RTT_DEBUG)	// 错误等级
#define SCENE_SWIM_RTT_LOG(...)
#define SCENE_SWIM_RTT_WARN(...)
#define SCENE_SWIM_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_SWIM_RTT_DEBUG)	// 警告等级
#define SCENE_SWIM_RTT_LOG(...)
#define SCENE_SWIM_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_SWIM_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_SWIM_RTT_DEBUG)	// 调试等级
#define SCENE_SWIM_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_SWIM_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_SWIM_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define SCENE_SWIM_RTT_LOG(...)
#define SCENE_SWIM_RTT_WARN(...)
#define SCENE_SWIM_RTT_ERR(...)
#endif

typedef enum
{
	eSceneSwimAlgoGsenser,
	eSceneSwimAlgoHr,
}SceneSwimAlgoType_e;

typedef struct
{
	uint8_t		InitFlg;		// 初始标志
	uint8_t		EnableFlg;		// 算法使能标志
	
	uint8_t 	TargetRemindFlg;		// 目标提醒标志，每次运动仅一次目标完成提醒
	
	uint32_t	TimeCnt;		// 场景计时
	
	uint32_t    LapsStageRemind;	// 过程提醒计数
	uint32_t	DurationStageRemind;
	uint32_t	CaloriaStageRemind;	
}SceneSwimParam_t;

extern void Scene_Swim_Init(void);
extern void Scene_Swim_Algorithm(int16 *AccData, SceneSwimAlgoType_e feSceneSwimAlgoType);
extern void Scene_Swim_Enable(void);
extern void Scene_Swim_Disable(void);
extern void Scene_Swim_Pause(void);
extern void Scene_Swim_Continue(void);
extern SceneSwimParam_t* Scene_Swim_ParamPGet(void);
extern void Scene_Swim_InfoGet(swimIndoorInfo_t *info);
extern void Scene_Swim_Test(uint8_t fEvent);

#endif










