#ifndef SCENE_COUNTDOWN_H
#define SCENE_COUNTDOWN_H

#include "platform_common.h"

#define SCENE_COUNTDOWN_RTT_DEBUG	2
#if (1 == SCENE_COUNTDOWN_RTT_DEBUG)	// ����ȼ�
#define SCENE_COUNTDOWN_RTT_LOG(...)
#define SCENE_COUNTDOWN_RTT_WARN(...)
#define SCENE_COUNTDOWN_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_COUNTDOWN_RTT_DEBUG)	// ����ȼ�
#define SCENE_COUNTDOWN_RTT_LOG(...)
#define SCENE_COUNTDOWN_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_COUNTDOWN_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_COUNTDOWN_RTT_DEBUG)	// ���Եȼ�
#define SCENE_COUNTDOWN_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_COUNTDOWN_RTT_WARN	RTT_DEBUG_WARN
#define SCENE_COUNTDOWN_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define SCENE_COUNTDOWN_RTT_LOG(...)
#define SCENE_COUNTDOWN_RTT_WARN(...)
#define SCENE_COUNTDOWN_RTT_ERR(...)
#endif


#define COUNTDOWN_PERIOD_MS	(1000)	// ����ʱ�жϣ���λms

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
	bool				InitedFlg;		// ��ʼ����ɱ�־
//	bool				RuningFlg;		// �������б�־
	CountDownState_e	State;
	
	uint32_t	TotalSec;			// ������ʱ��
	uint32_t	RemainSec;			// ʣ��ʱ��
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



