#ifndef SCENE_TASK_H
#define SCENE_TASK_H

#include "platform_common.h"
#include "scene_countdown.h"
#include "scene_findphone.h"

#define MOD_ALGO_RTT_DEBUG	3
#if (1 == MOD_ALGO_RTT_DEBUG)	// 错误等级
#define MOD_ALGO_RTT_LOG(...)
#define MOD_ALGO_RTT_WARN(...)
#define MOD_ALGO_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MOD_ALGO_RTT_DEBUG)	// 警告等级
#define MOD_ALGO_RTT_LOG(...)
#define MOD_ALGO_RTT_WARN		RTT_DEBUG_WARN
#define MOD_ALGO_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MOD_ALGO_RTT_DEBUG)	// 调试等级
#define MOD_ALGO_RTT_LOG		RTT_DEBUG_LOG
#define MOD_ALGO_RTT_WARN		RTT_DEBUG_WARN
#define MOD_ALGO_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define MOD_ALGO_RTT_LOG(...)
#define MOD_ALGO_RTT_WARN(...)
#define MOD_ALGO_RTT_ERR(...)
#endif

typedef struct
{
	uint8_t	Event;		// 心率事件类型：eMidHrmEventType
	float	sdnn;
	float	rmsd;
	float	rri;
	uint8_t hr;
}SceneTaskHrmParm_t;

typedef enum
{
//	eAlgoTaskMsgAccel,
//	eAlgoTaskMsgGyro,
	eAlgoTaskMsgMagnetism,
	eAlgoTaskMsgGPS,
	eAlgoTaskMsgHrm,
	eAlgoTaskMsgPressure,	// 气压环温
	eSceneTaskMsgCountdown,
	eSceneTaskMsgFindphone,
	eAlgoTaskMsg6Dof,		// 六轴，包括Acc和Gyr
	eAlgoTaskMsgMax,
}SceneTaskMsgId_e;

typedef struct
{
	uint8_t Flg;
}SceneTaskParam_t;

typedef struct
{
	SceneTaskMsgId_e Id;
	union
	{
		SceneTaskHrmParm_t	Hrm;
		CountDownEvent_t	Countdown;
		FindphoneEvent_t		Findphone;
	}Param;
}SceneTaskMsg_t;

void Scene_Task_TaskEventSet(SceneTaskMsg_t* Msg);
void Scene_Task_TaskCreate(void);
#endif










