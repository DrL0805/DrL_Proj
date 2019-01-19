#ifndef SCENE_RUN_H
#define SCENE_RUN_H

#include "platform_common.h"
#include "algorithm_running.h"


#define SCENE_RUN_RTT_DEBUG	3
#if (1 == SCENE_RUN_RTT_DEBUG)	// ����ȼ�
#define SCENE_RUN_RTT_LOG(...)
#define SCENE_RUN_RTT_WARN(...)
#define SCENE_RUN_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_RUN_RTT_DEBUG)	// ����ȼ�
#define SCENE_RUN_RTT_LOG(...)
#define SCENE_RUN_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_RUN_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_RUN_RTT_DEBUG)	// ���Եȼ�
#define SCENE_RUN_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_RUN_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_RUN_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define SCENE_RUN_RTT_LOG(...)
#define SCENE_RUN_RTT_WARN(...)
#define SCENE_RUN_RTT_ERR(...)
#endif

typedef struct
{
	uint8_t		InitFlg;		// ��ʼ��־
	uint8_t		EnableFlg;		// �㷨ʹ�ܱ�־
	
	uint8_t 	TargetRemindFlg;		// Ŀ�����ѱ�־��ÿ���˶���һ��Ŀ���������
	
	uint32_t	TimeCnt;		// ������ʱ
	
	uint32_t    DistanceStageRemind;	// �������Ѽ���
	uint32_t	DurationStageRemind;
	uint32_t	CaloriaStageRemind;
	
}SceneRunParam_t;

extern void Scene_Run_Init(void);
extern void Scene_Run_Algorithm(void);
extern void Scene_Run_Enable(void);
extern void Scene_Run_Disable(void);
extern void Scene_Run_Pause(void);
extern void Scene_Run_Continue(void);
extern SceneRunParam_t* Scene_Run_ParamPGet(void);
extern void Scene_Run_InfoGet(runningInfo_t *info);
extern void Scene_Run_Test(uint8_t fEvent);


#endif



