#ifndef SCENE_SWIM_H
#define SCENE_SWIM_H

#include "scene_variable.h"
#include "algorithm_swim_indoor.h"

#define SCENE_SWIM_RTT_DEBUG	3
#if (1 == SCENE_SWIM_RTT_DEBUG)	// ����ȼ�
#define SCENE_SWIM_RTT_LOG(...)
#define SCENE_SWIM_RTT_WARN(...)
#define SCENE_SWIM_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_SWIM_RTT_DEBUG)	// ����ȼ�
#define SCENE_SWIM_RTT_LOG(...)
#define SCENE_SWIM_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_SWIM_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_SWIM_RTT_DEBUG)	// ���Եȼ�
#define SCENE_SWIM_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_SWIM_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_SWIM_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define SCENE_SWIM_RTT_LOG(...)
#define SCENE_SWIM_RTT_WARN(...)
#define SCENE_SWIM_RTT_ERR(...)
#endif

typedef enum
{
	eSceneSwimAlgoGsenser,
	eSceneSwimAlgoHr,
}SceneSwimAlgoType_e;

typedef struct
{
	uint8_t		InitFlg;		// ��ʼ��־
	uint8_t		EnableFlg;		// �㷨ʹ�ܱ�־
	
	uint8_t 	TargetRemindFlg;		// Ŀ�����ѱ�־��ÿ���˶���һ��Ŀ���������
	
	uint32_t	TimeCnt;		// ������ʱ
	
	uint32_t    LapsStageRemind;	// �������Ѽ���
	uint32_t	DurationStageRemind;
	uint32_t	CaloriaStageRemind;	
}SceneSwimParam_t;

extern void Scene_Swim_Init(void);
extern void Scene_Swim_Algorithm(int16 *AccData, SceneSwimAlgoType_e feSceneSwimAlgoType);
extern void Scene_Swim_Enable(void);
extern void Scene_Swim_Disable(void);
extern void Scene_Swim_Pause(void);
extern void Scene_Swim_Continue(void);
extern SceneSwimParam_t* Scene_Swim_ParamPGet(void);
extern void Scene_Swim_InfoGet(swimIndoorInfo_t *info);
extern void Scene_Swim_Test(uint8_t fEvent);

#endif










