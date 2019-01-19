#ifndef SCENE_STOPWATCH_H
#define SCENE_STOPWATCH_H

#include "platform_common.h"

#define SCENE_STOPWATCH_RTT_DEBUG	2
#if (1 == SCENE_STOPWATCH_RTT_DEBUG)	// ����ȼ�
#define SCENE_STOPWATCH_RTT_LOG(...)
#define SCENE_STOPWATCH_RTT_WARN(...)
#define SCENE_STOPWATCH_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_STOPWATCH_RTT_DEBUG)	// ����ȼ�
#define SCENE_STOPWATCH_RTT_LOG(...)
#define SCENE_STOPWATCH_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_STOPWATCH_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_STOPWATCH_RTT_DEBUG)	// ���Եȼ�
#define SCENE_STOPWATCH_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_STOPWATCH_RTT_WARN	RTT_DEBUG_WARN
#define SCENE_STOPWATCH_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define SCENE_STOPWATCH_RTT_LOG(...)
#define SCENE_STOPWATCH_RTT_WARN(...)
#define SCENE_STOPWATCH_RTT_ERR(...)
#endif


#define STOPWATCH_PERIOD_MS		(10)	// ����жϣ���λms
#define STOPWATCH_MAX_STORE		(50)	// ���洢����ֵ

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
}SceneStopWatchFormat_t;	// ����ʽ

typedef struct
{
	bool				InitedFlg;		// ��ʼ����ɱ�־
	StopWatchState_e	State;
	
	uint32_t	TotalMs;							// �ۻ������˶���ms
	uint32_t	MeasureCnt;							// ���������ۼ�
	uint32_t	MeasurePoint[STOPWATCH_MAX_STORE];	// ����ʱ��㣬��λms������ڿ�ʼ������
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




