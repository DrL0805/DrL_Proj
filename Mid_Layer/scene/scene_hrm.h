#ifndef SCENE_HRM_H
#define SCENE_HRM_H

#include "scene_variable.h"

#define SCENE_HRM_RTT_DEBUG	3
#if (1 == SCENE_HRM_RTT_DEBUG)	// 错误等级
#define SCENE_HRM_RTT_LOG(...)
#define SCENE_HRM_RTT_WARN(...)
#define SCENE_HRM_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_HRM_RTT_DEBUG)	// 警告等级
#define SCENE_HRM_RTT_LOG(...)
#define SCENE_HRM_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_HRM_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_HRM_RTT_DEBUG)	// 调试等级
#define SCENE_HRM_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_HRM_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_HRM_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define SCENE_HRM_RTT_LOG(...)
#define SCENE_HRM_RTT_WARN(...)
#define SCENE_HRM_RTT_ERR(...)
#endif

#define 	SCENE_HRM_REST_ALGO_PERIOD              6	// 心率静息算法周期，单位min
#define 	SCENE_HRM_REST_HAL_CNT_MAX 		3 			//记录最近3次的测量结果
#define 	SCENE_HRM_REST_ALGO_CNT_MAX 			3 			//静息心率判断需要记录的个数
#define 	SCENE_HRM_REST_HR_UP_LIMIT 			120 		//静息心率上限
#define 	SCENE_HRM_REST_HR_BIAS 			80  		//静息心率偏差最大值


// 静息心率算法
typedef struct
{
	uint16 	RestPeriodCnt;						// 静息周期计数，用于判断当前静息心率是否有效，以及静息超过某段时间后，更新静息心率
	
	uint8 	AlgoLogCnt; 							// 算法心率值计数
	uint8 	AlgoLogBuf[SCENE_HRM_REST_ALGO_CNT_MAX]; 	// 算法心率值缓存
	
	uint8 	HalLogCnt; 							// 硬件采集心率值计数
	uint8 	HalLogBuf[SCENE_HRM_REST_HAL_CNT_MAX];		// 硬件采集心率值缓存
	
	uint8 	RunningFlg;							// 算法正在运行标志
	uint32 	LastStep; 							// 上次计步值数，一旦产生计步，重置静息算法
	uint8 	RestHr;							// 静息心率值
}RestHrmAlgo_t;	

typedef struct
{
	bool		InitFlg;				// 初始标志
	bool		EnableFlg;				// 算法使能标志

	uint8_t		LatestHrm;		// 最新心率值
	uint8_t 	PendCnt;		// 后台待测量计数

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

