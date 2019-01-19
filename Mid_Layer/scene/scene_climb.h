#ifndef SCENE_CLIMB_H
#define SCENE_CLIMB_H

#include "platform_common.h"
#include "algorithm_climbMountain.h"


#define SCENE_CLIMB_RTT_DEBUG	3
#if (1 == SCENE_CLIMB_RTT_DEBUG)	// 错误等级
#define SCENE_CLIMB_RTT_LOG(...)
#define SCENE_CLIMB_RTT_WARN(...)
#define SCENE_CLIMB_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_CLIMB_RTT_DEBUG)	// 警告等级
#define SCENE_CLIMB_RTT_LOG(...)
#define SCENE_CLIMB_RTT_WARN	RTT_DEBUG_WARN
#define SCENE_CLIMB_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_CLIMB_RTT_DEBUG)	// 调试等级
#define SCENE_CLIMB_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_CLIMB_RTT_WARN	RTT_DEBUG_WARN
#define SCENE_CLIMB_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define SCENE_CLIMB_RTT_LOG(...)
#define SCENE_CLIMB_RTT_WARN(...)
#define SCENE_CLIMB_RTT_ERR(...)
#endif

typedef struct
{
	bool		InitFlg;		// 初始标志
	bool		EnableFlg;		// 算法使能标志
	
	uint8_t 	TargetRemindFlg;		// 目标提醒标志，每次运动仅一次目标完成提醒
	
	uint32_t	TimeCnt;		// 场景计时
	
	uint32_t    DistanceStageRemind;	// 过程提醒计数
	uint32_t	DurationStageRemind;
	uint32_t	CaloriaStageRemind;	
}SceneClimbParam_t;

extern void Scene_Climb_Init(void);
extern void Scene_Climb_Algorithm(void);
extern void Scene_Climb_Enable(void);
extern void Scene_Climb_Disable(void);
extern void Scene_Climb_Pause(void);
extern void Scene_Climb_Continue(void);
extern SceneClimbParam_t* Scene_Climb_ParamPGet(void);
extern void Scene_Climb_InfoGet(climbMountainInfo_t *info);
extern void Scene_Climb_Test(uint8_t fEvent);

#endif



