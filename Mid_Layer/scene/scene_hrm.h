#ifndef SCENE_HRM_H
#define SCENE_HRM_H

#include "scene_variable.h"

#define SCENE_HRM_RTT_DEBUG	3
#if (1 == SCENE_HRM_RTT_DEBUG)	// ����ȼ�
#define SCENE_HRM_RTT_LOG(...)
#define SCENE_HRM_RTT_WARN(...)
#define SCENE_HRM_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_HRM_RTT_DEBUG)	// ����ȼ�
#define SCENE_HRM_RTT_LOG(...)
#define SCENE_HRM_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_HRM_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_HRM_RTT_DEBUG)	// ���Եȼ�
#define SCENE_HRM_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_HRM_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_HRM_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define SCENE_HRM_RTT_LOG(...)
#define SCENE_HRM_RTT_WARN(...)
#define SCENE_HRM_RTT_ERR(...)
#endif

#define 	SCENE_HRM_REST_ALGO_PERIOD              6	// ���ʾ�Ϣ�㷨���ڣ���λmin
#define 	SCENE_HRM_REST_HAL_CNT_MAX 		3 			//��¼���3�εĲ������
#define 	SCENE_HRM_REST_ALGO_CNT_MAX 			3 			//��Ϣ�����ж���Ҫ��¼�ĸ���
#define 	SCENE_HRM_REST_HR_UP_LIMIT 			120 		//��Ϣ��������
#define 	SCENE_HRM_REST_HR_BIAS 			80  		//��Ϣ����ƫ�����ֵ


// ��Ϣ�����㷨
typedef struct
{
	uint16 	RestPeriodCnt;						// ��Ϣ���ڼ����������жϵ�ǰ��Ϣ�����Ƿ���Ч���Լ���Ϣ����ĳ��ʱ��󣬸��¾�Ϣ����
	
	uint8 	AlgoLogCnt; 							// �㷨����ֵ����
	uint8 	AlgoLogBuf[SCENE_HRM_REST_ALGO_CNT_MAX]; 	// �㷨����ֵ����
	
	uint8 	HalLogCnt; 							// Ӳ���ɼ�����ֵ����
	uint8 	HalLogBuf[SCENE_HRM_REST_HAL_CNT_MAX];		// Ӳ���ɼ�����ֵ����
	
	uint8 	RunningFlg;							// �㷨�������б�־
	uint32 	LastStep; 							// �ϴμƲ�ֵ����һ�������Ʋ������þ�Ϣ�㷨
	uint8 	RestHr;							// ��Ϣ����ֵ
}RestHrmAlgo_t;	

typedef struct
{
	bool		InitFlg;				// ��ʼ��־
	bool		EnableFlg;				// �㷨ʹ�ܱ�־

	uint8_t		LatestHrm;		// ��������ֵ
	uint8_t 	PendCnt;		// ��̨����������

	RestHrmAlgo_t	RestAlgo;
}SceneHrmParam_t;

extern void Scene_Hrm_RestAlgo(void);

extern void Scene_Hrm_BGSampleCheck(void);
extern void Scene_Hrm_Init(void);
extern void Scene_Hrm_Enable(void);
extern void Scene_Hrm_Disable(void);
extern void Scene_Hrm_SampleComplete(void);
extern void Scene_Hrm_SampleStart(eSceneMeasureWay feMeasure);
extern void Scene_Hrm_SampleStop(eSceneMeasureWay feMeasure);
extern SceneHrmParam_t* Scene_Hrm_ParamPGet(void);
extern uint8_t Scene_Hrm_RestingHrvGet(void);

#endif

