#ifndef	_MID_MOTOR_H
#define	_MID_MOTOR_H

#include "platform_common.h"
#include "drv_motor.h"

#define MID_MOTOR_RTT_DEBUG	2
#if (1 == MID_MOTOR_RTT_DEBUG)	// ����ȼ�
#define MID_MOTOR_RTT_LOG(...)
#define MID_MOTOR_RTT_WARN(...)
#define MID_MOTOR_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MID_MOTOR_RTT_DEBUG)	// ����ȼ�
#define MID_MOTOR_RTT_LOG(...)
#define MID_MOTOR_RTT_WARN		RTT_DEBUG_WARN
#define MID_MOTOR_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MID_MOTOR_RTT_DEBUG)	// ���Եȼ�
#define MID_MOTOR_RTT_LOG		RTT_DEBUG_LOG
#define MID_MOTOR_RTT_WARN		RTT_DEBUG_WARN
#define MID_MOTOR_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define MID_MOTOR_RTT_LOG(...)
#define MID_MOTOR_RTT_WARN(...)
#define MID_MOTOR_RTT_ERR(...)
#endif

/*
	LED������𶯷�ʽ�����¹涨��
	1HZ��˸���𶯣�����125ms���ر�875ms
	2HZ��˸���𶯣�����125ms���ر�375ms
	4HZ��˸���𶯣�����125ms���ر�125ms
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
	eMidMotorStateSleep,	// δʹ��
	eMidMotorStateShakeOn,	// ������ģʽ��������
	eMidMotorStateShakeOff,	// ������ģʽ�ҹر���
}eMidMotorState;

typedef enum
{
	eMidMotorShake1Hz = 1,
	eMidMotorShake2Hz = 2,
	eMidMotorShake4Hz = 4,
	eMidMotorShakeKeep,	// ����
}eMidMotorShakeLevel;

typedef struct 
{
	uint16_t	TotalOnTick;		
	uint16_t	TotalOffTick;
	uint16_t	TotalCycleNum;		// ѭ������
	
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
