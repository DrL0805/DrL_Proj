#ifndef SCENE_COUNTDOWN_H
#define SCENE_COUNTDOWN_H

#include "platform_common.h"

#define SCENE_COUNTDOWN_RTT_DEBUG	2
#if (1 == SCENE_COUNTDOWN_RTT_DEBUG)	// 错误等级
#define SCENE_COUNTDOWN_RTT_LOG(...)
#define SCENE_COUNTDOWN_RTT_WARN(...)
#define SCENE_COUNTDOWN_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_COUNTDOWN_RTT_DEBUG)	// 警告等级
#define SCENE_COUNTDOWN_RTT_LOG(...)
#define SCENE_COUNTDOWN_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_COUNTDOWN_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_COUNTDOWN_RTT_DEBUG)	// 调试等级
#define SCENE_COUNTDOWN_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_COUNTDOWN_RTT_WARN	RTT_DEBUG_WARN
#define SCENE_COUNTDOWN_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define SCENE_COUNTDOWN_RTT_LOG(...)
#define SCENE_COUNTDOWN_RTT_WARN(...)
#define SCENE_COUNTDOWN_RTT_ERR(...)
#endif


#define COUNTDOWN_PERIOD_MS	(1000)	// 倒计时中断，单位ms

typedef enum
{
	eCountDownStop,
	eCountDownRuning,
	eCountDownSuspend,
}CountDownState_e;

typedef struct 
{
    uint32_t 	hour;
    uint32_t 	min;
    uint32_t 	sec;
}SceneCountDownFormat_t;

typedef struct
{
	bool				InitedFlg;		// 初始化完成标志
//	bool				RuningFlg;		// 正在运行标志
	CountDownState_e	State;
	
	uint32_t	TotalSec;			// 设置总时间
	uint32_t	RemainSec;			// 剩余时间
}SceneCountDownParam_t;

extern void Scene_Countdown_Reset(void);
extern void Scene_Countdown_Init(void);
extern void Scene_Countdown_Start(void);
extern void Scene_Countdown_Suspend(void);
extern uint32_t Scene_Countdown_RemainRead(void);
extern void Scene_Countdown_TimeWrite(uint32_t Sec);
extern SceneCountDownParam_t* Scene_Countdown_ParamPGet(void);
extern void Scene_Countdown_Test(void);

typedef enum 
{
	eCountDownEventTimeOut,
}CountDownEventId_e;

typedef struct
{
	CountDownEventId_e		Id;
	uint8_t 				Param;
}CountDownEvent_t;


#endif



