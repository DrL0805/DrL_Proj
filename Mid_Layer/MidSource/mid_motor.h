#ifndef	_MID_MOTOR_H
#define	_MID_MOTOR_H

#include "platform_common.h"
#include "drv_motor.h"

#define MID_MOTOR_RTT_DEBUG	2
#if (1 == MID_MOTOR_RTT_DEBUG)	// 错误等级
#define MID_MOTOR_RTT_LOG(...)
#define MID_MOTOR_RTT_WARN(...)
#define MID_MOTOR_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MID_MOTOR_RTT_DEBUG)	// 警告等级
#define MID_MOTOR_RTT_LOG(...)
#define MID_MOTOR_RTT_WARN		RTT_DEBUG_WARN
#define MID_MOTOR_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MID_MOTOR_RTT_DEBUG)	// 调试等级
#define MID_MOTOR_RTT_LOG		RTT_DEBUG_LOG
#define MID_MOTOR_RTT_WARN		RTT_DEBUG_WARN
#define MID_MOTOR_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define MID_MOTOR_RTT_LOG(...)
#define MID_MOTOR_RTT_WARN(...)
#define MID_MOTOR_RTT_ERR(...)
#endif

/*
	LED与马达震动方式做以下规定：
	1HZ闪烁或震动：开启125ms，关闭875ms
	2HZ闪烁或震动：开启125ms，关闭375ms
	4HZ闪烁或震动：开启125ms，关闭125ms
*/
#define MID_MOTOR_TICK_MS		(125)
#define MID_MOTOR_1HZ_ON_TICK	(1)
#define MID_MOTOR_1HZ_OFF_TICK	(7)

#define MID_MOTOR_2HZ_ON_TICK	(1)
#define MID_MOTOR_2HZ_OFF_TICK	(3)

#define MID_MOTOR_4HZ_ON_TICK	(1)
#define MID_MOTOR_4HZ_OFF_TICK	(1)

#define MID_MOTOR_KEEP_ON_TICK	(8)
#define MID_MOTOR_KEEP_OFF_TICK	(0)

typedef enum
{
	eMidMotorStateSleep,	// 未使用
	eMidMotorStateShakeOn,	// 处于震动模式且正在震动
	eMidMotorStateShakeOff,	// 处于震动模式且关闭震动
}eMidMotorState;

typedef enum
{
	eMidMotorShake1Hz = 1,
	eMidMotorShake2Hz = 2,
	eMidMotorShake4Hz = 4,
	eMidMotorShakeKeep,	// 长震
}eMidMotorShakeLevel;

typedef struct 
{
	uint16_t	TotalOnTick;		
	uint16_t	TotalOffTick;
	uint16_t	TotalCycleNum;		// 循环次数
	
	uint16_t	CntOnTick;		
	uint16_t	CntOffTick;
	uint16_t	CntCycleNum;
	
	eMidMotorState	State;
}Mid_Motor_Param_t;

extern void Mid_Motor_Init(void);
extern void Mid_Motor_On(void);
extern void Mid_Motor_Off(void);
extern uint16_t Mid_Motor_ShakeStart(eMidMotorShakeLevel Level, uint16_t CycleNum);
extern void Mid_Motor_ShakeStop(void);
extern void Mid_Motor_Test(void);



#endif
