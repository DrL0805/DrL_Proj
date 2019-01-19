#ifndef SCENE_SLEEP_H
#define SCENE_SLEEP_H

#include "platform_common.h"
#include "algorithm_sleep.h"

#define SCENE_SLEEP_RTT_DEBUG	3
#if (1 == SCENE_SLEEP_RTT_DEBUG)	// 错误等级
#define SCENE_SLEEP_RTT_LOG(...)
#define SCENE_SLEEP_RTT_WARN(...)
#define SCENE_SLEEP_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_SLEEP_RTT_DEBUG)	// 警告等级
#define SCENE_SLEEP_RTT_LOG(...)
#define SCENE_SLEEP_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_SLEEP_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_SLEEP_RTT_DEBUG)	// 调试等级
#define SCENE_SLEEP_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_SLEEP_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_SLEEP_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define SCENE_SLEEP_RTT_LOG(...)
#define SCENE_SLEEP_RTT_WARN(...)
#define SCENE_SLEEP_RTT_ERR(...)
#endif

#define SLEEP_SCENE_PERIOD_MS	(1000)	// 睡眠算法调用周期

typedef struct
{
	bool		InitFlg;
	bool		EnableFlg;		
	uint8_t		SampleId;
	uint32_t 	IntervalMs;		
}SceneSleepParam_t;

extern void Scene_Sleep_algorithm(int16 *xyzData, uint32_t Interval);
extern void Scene_Sleep_Init(void);
extern void Scene_Sleep_Clear(void);
extern void Scene_Sleep_RecordGet(sleep_record_t *sleepRecord);
extern void Scene_Sleep_Enable(void);
extern void Scene_Sleep_Disable(void);

#endif



