#ifndef SCENE_CLIMB_H
#define SCENE_CLIMB_H

#include "platform_common.h"
#include "algorithm_climbMountain.h"


#define SCENE_CLIMB_RTT_DEBUG	3
#if (1 == SCENE_CLIMB_RTT_DEBUG)	// ����ȼ�
#define SCENE_CLIMB_RTT_LOG(...)
#define SCENE_CLIMB_RTT_WARN(...)
#define SCENE_CLIMB_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_CLIMB_RTT_DEBUG)	// ����ȼ�
#define SCENE_CLIMB_RTT_LOG(...)
#define SCENE_CLIMB_RTT_WARN	RTT_DEBUG_WARN
#define SCENE_CLIMB_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_CLIMB_RTT_DEBUG)	// ���Եȼ�
#define SCENE_CLIMB_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_CLIMB_RTT_WARN	RTT_DEBUG_WARN
#define SCENE_CLIMB_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define SCENE_CLIMB_RTT_LOG(...)
#define SCENE_CLIMB_RTT_WARN(...)
#define SCENE_CLIMB_RTT_ERR(...)
#endif

typedef struct
{
	bool		InitFlg;		// ��ʼ��־
	bool		EnableFlg;		// �㷨ʹ�ܱ�־
	
	uint8_t 	TargetRemindFlg;		// Ŀ�����ѱ�־��ÿ���˶���һ��Ŀ���������
	
	uint32_t	TimeCnt;		// ������ʱ
	
	uint32_t    DistanceStageRemind;	// �������Ѽ���
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



