#ifndef SCENE_GESTURE_H
#define SCENE_GESTURE_H

#include "platform_common.h"
#include "algorithm_gesture.h"

#define SCENE_GESTURE_RTT_DEBUG	3
#if (1 == SCENE_GESTURE_RTT_DEBUG)	// 错误等级
#define SCENE_GESTURE_RTT_LOG(...)
#define SCENE_GESTURE_RTT_WARN(...)
#define SCENE_GESTURE_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_GESTURE_RTT_DEBUG)	// 警告等级
#define SCENE_GESTURE_RTT_LOG(...)
#define SCENE_GESTURE_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_GESTURE_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_GESTURE_RTT_DEBUG)	// 调试等级
#define SCENE_GESTURE_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_GESTURE_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_GESTURE_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define SCENE_GESTURE_RTT_LOG(...)
#define SCENE_GESTURE_RTT_WARN(...)
#define SCENE_GESTURE_RTT_ERR(...)
#endif


#define GESTURE_SCENE_PERIOD_MS	(200)	

typedef struct
{
	bool		InitFlg;
	bool		EnableFlg;		
	uint8_t		SampleId;
	uint32_t 	IntervalMs;		
}Scene_Gesture_Param_t;

extern void Scene_Gesture_algorithm(int16 *xyzData, uint32_t Interval);
extern void Scene_Gesture_Init(void);	
extern void Scene_Gesture_Enable(void);
extern void Scene_Gesture_Disable(void);

#endif



