#ifndef SCENE_STAIRS_H
#define SCENE_STAIRS_H

#include "platform_common.h"
#include "algorithm_climbMountain.h"
#include "algorithm_climb_stairs.h"

#define SCENE_STAIRS_RTT_DEBUG	3
#if (1 == SCENE_STAIRS_RTT_DEBUG)	// 错误等级
#define SCENE_STAIRS_RTT_LOG(...)
#define SCENE_STAIRS_RTT_WARN(...)
#define SCENE_STAIRS_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_STAIRS_RTT_DEBUG)	// 警告等级
#define SCENE_STAIRS_RTT_LOG(...)
#define SCENE_STAIRS_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_STAIRS_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_STAIRS_RTT_DEBUG)	// 调试等级
#define SCENE_STAIRS_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_STAIRS_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_STAIRS_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define SCENE_STAIRS_RTT_LOG(...)
#define SCENE_STAIRS_RTT_WARN(...)
#define SCENE_STAIRS_RTT_ERR(...)
#endif

typedef struct
{
	bool		InitFlg;		// 初始标志
	bool		EnableFlg;		// 算法使能标志
	
	uint16_t	DayFloor;		// 当天爬楼梯数
}SceneStairParam_t;

extern void Scene_Stair_Algorithm(void);
extern void Scene_Stair_Init(void);
extern void Scene_Stair_Clear(void);
extern void Scene_Stair_Enable(void);
extern void Scene_Stair_Disable(void);
SceneStairParam_t* Scene_Stair_ParamPGet(void);

#endif



