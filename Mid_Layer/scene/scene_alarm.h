#ifndef	SCENE_ALARM_H
#define	SCENE_ALARM_H

#include "platform_common.h"
//#include "app_variable.h"

#define SCENE_ALARM_RTT_DEBUG	2
#if (1 == SCENE_ALARM_RTT_DEBUG)	// 错误等级
#define SCENE_ALARM_RTT_LOG(...)
#define SCENE_ALARM_RTT_WARN(...)
#define SCENE_ALARM_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_ALARM_RTT_DEBUG)	// 警告等级
#define SCENE_ALARM_RTT_LOG(...)
#define SCENE_ALARM_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_ALARM_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_ALARM_RTT_DEBUG)	// 调试等级
#define SCENE_ALARM_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_ALARM_RTT_WARN	RTT_DEBUG_WARN
#define SCENE_ALARM_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define SCENE_ALARM_RTT_LOG(...)
#define SCENE_ALARM_RTT_WARN(...)
#define SCENE_ALARM_RTT_ERR(...)
#endif

#define	ALARM_SNOOZE_DURATION_MIN	(1)	// 闹钟贪睡时长，单位min
#define SCENE_ALARM_MAX_ALARM_NUM	(3)		// 最大闹钟数量

// 闹钟参数结构体，依据通信协议
typedef struct 
{
	uint8 hour;
	uint8 min;
	uint8 ReptMap;			// 重复位图 bit0~bit6: sun~sat, bit7: 重复开关
	uint8 alarmswitch;	    // 闹钟事件开关 1: alarm open, 0: alarm close
	uint8 RingSwitch;		// 贪睡开关，0关 1开
	uint8 RingDurtion;		// 贪睡时长min
	uint8 AlertLevel;		// 闹钟提醒等级
}alarm_clock_t;

typedef struct
{
	uint8_t 			RingSwitch;		// 闹钟贪睡功能开关，1 当前正在处于贪睡模式
	uint8_t 			RingCnt;		// 贪睡次数，最多5次
	uint8_t 			accTimer;		// 贪睡时间累积，每10分钟一次
	uint8_t		 		curRingAlarmId;	// 当前闹钟句柄（通过获取这个值来判断哪个闹钟响了）
	
	alarm_clock_t	Clock[SCENE_ALARM_MAX_ALARM_NUM];	// 闹钟组数
}SceneAlarmParam_t;

uint8 Scene_Alarm_Check(void);
void Scene_Alarm_Write(alarm_clock_t *configinfo, uint8_t group);
void Scene_Alarm_Read(alarm_clock_t *configinfo, uint8_t group);
uint8 Scene_Alarm_ValidNumRead(void);
void Scene_Alarm_CurrAlarmGet(alarm_clock_t *alarm_clock);	
void Scene_Alarm_Stop(void);
void Scene_Alarm_Delay(void);
SceneAlarmParam_t* Scene_Alarm_ParamPGet(void);
void Scene_Alarm_Test(void);

#endif			//	ALARM_APP_H





