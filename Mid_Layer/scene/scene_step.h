#ifndef SCENE_STEP_H
#define SCENE_STEP_H

#include "platform_common.h"

#define SCENE_STEP_RTT_DEBUG	3
#if (1 == SCENE_STEP_RTT_DEBUG)	// 错误等级
#define SCENE_STEP_RTT_LOG(...)
#define SCENE_STEP_RTT_WARN(...)
#define SCENE_STEP_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_STEP_RTT_DEBUG)	// 警告等级
#define SCENE_STEP_RTT_LOG(...)
#define SCENE_STEP_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_STEP_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_STEP_RTT_DEBUG)	// 调试等级
#define SCENE_STEP_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_STEP_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_STEP_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define SCENE_STEP_RTT_LOG(...)
#define SCENE_STEP_RTT_WARN(...)
#define SCENE_STEP_RTT_ERR(...)
#endif

#define SPORT_SCENE_PERIOD_MS	(40)	// 计步算法调用周期

typedef struct
{
	uint32 	LastStep; // 1秒前的计步值，与当前计步值进行比较是否产生新的计步
	uint8 	SecCnt;		 // 记录计步秒数，满60秒计步时长+1
}StepDurationAlgo_t;

typedef struct
{
	bool		InitFlg;		// 初始标志
	bool		EnableFlg;		// 场景使能标志
	
	uint32 totalStep; 			// 运动总步数
	uint32 stepAim;				// 运动目标步数
	uint16 stepComplete;		// 运行完成度
	bool	RemindFlg;		// 目标完成提醒标志 

	uint32 Calorie;		//运动卡路里，单位：ka
	uint32 sportDistance;		//运行距离，单位：m
	uint16 sportDuaration;		//运行时间，单位：min	

	uint8_t		SampleId;		
	uint32_t 	IntervalMs;		

	uint32_t    Step5MinCnt;	// 5min计步累加值
	
	StepDurationAlgo_t	DurationAlgo;	// 计步时长算法相关
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



