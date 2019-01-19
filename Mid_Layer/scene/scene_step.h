#ifndef SCENE_STEP_H
#define SCENE_STEP_H

#include "platform_common.h"

#define SCENE_STEP_RTT_DEBUG	3
#if (1 == SCENE_STEP_RTT_DEBUG)	// ����ȼ�
#define SCENE_STEP_RTT_LOG(...)
#define SCENE_STEP_RTT_WARN(...)
#define SCENE_STEP_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_STEP_RTT_DEBUG)	// ����ȼ�
#define SCENE_STEP_RTT_LOG(...)
#define SCENE_STEP_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_STEP_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_STEP_RTT_DEBUG)	// ���Եȼ�
#define SCENE_STEP_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_STEP_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_STEP_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define SCENE_STEP_RTT_LOG(...)
#define SCENE_STEP_RTT_WARN(...)
#define SCENE_STEP_RTT_ERR(...)
#endif

#define SPORT_SCENE_PERIOD_MS	(40)	// �Ʋ��㷨��������

typedef struct
{
	uint32 	LastStep; // 1��ǰ�ļƲ�ֵ���뵱ǰ�Ʋ�ֵ���бȽ��Ƿ�����µļƲ�
	uint8 	SecCnt;		 // ��¼�Ʋ���������60��Ʋ�ʱ��+1
}StepDurationAlgo_t;

typedef struct
{
	bool		InitFlg;		// ��ʼ��־
	bool		EnableFlg;		// ����ʹ�ܱ�־
	
	uint32 totalStep; 			// �˶��ܲ���
	uint32 stepAim;				// �˶�Ŀ�경��
	uint16 stepComplete;		// ������ɶ�
	bool	RemindFlg;		// Ŀ��������ѱ�־ 

	uint32 Calorie;		//�˶���·���λ��ka
	uint32 sportDistance;		//���о��룬��λ��m
	uint16 sportDuaration;		//����ʱ�䣬��λ��min	

	uint8_t		SampleId;		
	uint32_t 	IntervalMs;		

	uint32_t    Step5MinCnt;	// 5min�Ʋ��ۼ�ֵ
	
	StepDurationAlgo_t	DurationAlgo;	// �Ʋ�ʱ���㷨���
}SceneStepParam_t;


extern void Scene_Step_Init(void);
extern void Scene_Step_Algorithm(int16 *xyzData, uint32_t Interval);
extern void Scene_Step_Enable(void);
extern void Scene_Step_Disable(void);
extern SceneStepParam_t* Scene_Step_ParamPGet(void);
extern void Scene_Step_Clear(void);
extern void Scene_Step_AimSet(uint32 stepAim);
extern void Scene_Step_DuarationAlgo(void);
extern uint32 Scene_Step_5minCntRead(void);


#endif



