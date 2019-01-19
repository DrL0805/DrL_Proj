#ifndef SCENE_FINDPHONE_H
#define SCENE_FINDPHONE_H

#include "platform_common.h"

#define SCENE_FINDPHONE_RTT_DEBUG	2
#if (1 == SCENE_FINDPHONE_RTT_DEBUG)	// 错误等级
#define SCENE_FINDPHONE_RTT_LOG(...)
#define SCENE_FINDPHONE_RTT_WARN(...)
#define SCENE_FINDPHONE_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_FINDPHONE_RTT_DEBUG)	// 警告等级
#define SCENE_FINDPHONE_RTT_LOG(...)
#define SCENE_FINDPHONE_RTT_WARN	RTT_DEBUG_WARN
#define SCENE_FINDPHONE_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_FINDPHONE_RTT_DEBUG)	// 调试等级
#define SCENE_FINDPHONE_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_FINDPHONE_RTT_WARN	RTT_DEBUG_WARN
#define SCENE_FINDPHONE_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define SCENE_FINDPHONE_RTT_LOG(...)
#define SCENE_FINDPHONE_RTT_WARN(...)
#define SCENE_FINDPHONE_RTT_ERR(...)
#endif

typedef struct
{
	bool		InitFlg;		// 初始标志
	bool		EnableFlg;		// 算法使能标志

}Scene_Findphone_Param_t;

extern void Scene_Findphone_Init(void);
extern void Scene_Findphone_Start(void);
extern void Scene_Findphone_Stop(void);
extern void Scene_Findphone_Test(void);

typedef enum 
{
	eFindphoneEventTimerCb,
}eFindphoneEventId;

typedef struct
{
	eFindphoneEventId	Id;
	uint8_t 		Param;
}FindphoneEvent_t;


#endif



