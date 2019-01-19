#ifndef SCENE_STOPWATCH_H
#define SCENE_STOPWATCH_H

#include "platform_common.h"

#define SCENE_STOPWATCH_RTT_DEBUG	2
#if (1 == SCENE_STOPWATCH_RTT_DEBUG)	// 错误等级
#define SCENE_STOPWATCH_RTT_LOG(...)
#define SCENE_STOPWATCH_RTT_WARN(...)
#define SCENE_STOPWATCH_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_STOPWATCH_RTT_DEBUG)	// 警告等级
#define SCENE_STOPWATCH_RTT_LOG(...)
#define SCENE_STOPWATCH_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_STOPWATCH_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_STOPWATCH_RTT_DEBUG)	// 调试等级
#define SCENE_STOPWATCH_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_STOPWATCH_RTT_WARN	RTT_DEBUG_WARN
#define SCENE_STOPWATCH_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define SCENE_STOPWATCH_RTT_LOG(...)
#define SCENE_STOPWATCH_RTT_WARN(...)
#define SCENE_STOPWATCH_RTT_ERR(...)
#endif


#define STOPWATCH_PERIOD_MS		(10)	// 秒表中断，单位ms
#define STOPWATCH_MAX_STORE		(50)	// 最大存储多少值

typedef enum
{
	eStopWatchStop,
	eStopWatchRuning,
	eStopWatchSuspend,
}StopWatchState_e;

typedef struct 
{
	uint8   hour;
	uint8   min;
	uint8   sec;
	uint32	ms;
}SceneStopWatchFormat_t;	// 秒表格式

typedef struct
{
	bool				InitedFlg;		// 初始化完成标志
	StopWatchState_e	State;
	
	uint32_t	TotalMs;							// 累积运行了多少ms
	uint32_t	MeasureCnt;							// 测量次数累加
	uint32_t	MeasurePoint[STOPWATCH_MAX_STORE];	// 测量时间点，单位ms，相对于开始计数出
}SceneStopWatchParam_t;

extern void Scene_StopWatch_Reset(void);
extern void Scene_StopWatch_Init(void);
extern void Scene_StopWatch_Start(void);
extern void Scene_StopWatch_Suspend(void);
extern void Scene_StopWatch_MeasureMark(void);
extern uint32_t Scene_StopWatch_TotalMsGet(uint8_t Methon);
SceneStopWatchParam_t* Scene_StopWatch_ParamPGet(void);
extern void Scene_StopWatch_FormatSwitch(uint32_t Ms, SceneStopWatchFormat_t* fStopWatchFormat);
extern void Scene_StopWatch_Test(void);

#endif			//	STOPWATCH_APP_H




