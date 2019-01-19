#ifndef	_DRV_TOUCH_H
#define	_DRV_TOUCH_H

#include "platform_common.h"



#define DRV_TOUCH_RTT_DEBUG	2
#if (1 == DRV_TOUCH_RTT_DEBUG)	// ����ȼ�
#define DRV_TOUCH_RTT_LOG(...)
#define DRV_TOUCH_RTT_WARN(...)
#define DRV_TOUCH_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == DRV_TOUCH_RTT_DEBUG)	// ����ȼ�
#define DRV_TOUCH_RTT_LOG(...)
#define DRV_TOUCH_RTT_WARN		RTT_DEBUG_WARN
#define DRV_TOUCH_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == DRV_TOUCH_RTT_DEBUG)	// ���Եȼ�
#define DRV_TOUCH_RTT_LOG		RTT_DEBUG_LOG
#define DRV_TOUCH_RTT_WARN		RTT_DEBUG_WARN
#define DRV_TOUCH_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define DRV_TOUCH_RTT_LOG(...)
#define DRV_TOUCH_RTT_WARN(...)
#define DRV_TOUCH_RTT_ERR(...)
#endif

/** TP����4��״̬:
	��״̬���ģ�
		Active 1.5mA, Untouch 0.25mA, Idle 0.1mA����FAEʵ��0.1mA�����ֲ�д��25uA��, Sleep 0.1uA
	״̬�л���
		1���κ�ĩ����RESET���ͽ���Sleepģʽ�����߽���Untouchģʽ
		2����sleepģʽ�����ⴥ������Activeģʽ
		3��[Active]-(2s���޲���)->[Untouch]<-(��ָ��)->[Idle]
		*/
typedef enum
{
	eTouchStateActive,
	eTouchStateUntouch,
	eTouchStateIdle,
	eTouchStateSleep,
}TouchStateType_e;

// Flick��������
typedef enum
{
	eTouchFlickUp = 0x08,
	eTouchFlickUpperRight = 0x09,
	eTouchFlickRight = 0x0A,
	eTouchFlickLowerRight = 0x0B,
	eTouchFlickDown = 0x0C,
	eTouchFlickLowerLeft = 0x0D,
	eTouchFlickLeft = 0x0E,
	eTouchFlickUpperLeft = 0x0F,
}eTouchFlickDirection;

// ��������������
typedef enum
{
	eTouchIsrProcess,	// �����жϴ���
	
	eTouchGIDTap = 0x20,
	eTouchGIDPress = 0x21,
	eTouchGIDFlick = 0x22,
	eTouchGIDDoubleTap = 0x23,
	eTouchGIDTapAndSlide = 0x24,
	eTouchGIDDrag = 0x25,
	eTouchGIDDirection = 0x26,
	eTouchGIDTurn = 0x27,
	eTouchGIDClockwise = 0x28,
}eTouchGIDType;

typedef struct
{
	uint16_t XCoord;
	uint16_t YCoord;
}TouchGIDTapParam_t;

typedef struct
{
	eTouchFlickDirection		Direction;
	uint16_t 			XStartCoord;
	uint16_t 			YStartCoord;
	uint16_t 			XEndCoord;
	uint16_t 			YEndCoord;
}TouchGIDFlickParam_t;

// ��ͬ�������͵ľ������
typedef struct
{
	eTouchGIDType	Type;	// ��������
	union
	{
		TouchGIDTapParam_t		Tap;
		TouchGIDFlickParam_t	Flick;
	}GID;
}TouchGIDParam_t;

typedef struct
{
	uint8_t PressIngFlg;	// ������־
	
	uint8_t	IdleTimeoutCnt;		// ����������2�����TP����Idle
	TouchStateType_e	State;
	
	uint8_t	 Scale;
	uint8_t PointData[14];	// ����������Ϣ
	uint16_t XResolution;	// X�ֱ���
	uint16_t YResolution;	// Y�ֱ���
}DrvTouchParam_t;

extern uint8_t Drv_IT7259_WriteBuffer(uint8_t addr, uint8_t* pdata, int len);
extern uint8_t Drv_IT7259_ReadBuffer(uint8_t addr, uint8_t* pdata, int len);
extern uint8_t Drv_IT7259_ReadBuffer16(uint16_t addr, uint8_t* pdata, int len);
extern uint8_t Drv_IT7259_ReadBuffer32(uint32_t addr, uint8_t* pdata, int len);

extern void Drv_Touch_Init(void);
extern void Drv_Touch_IsrProcess(void);
extern void Drv_Touch_Wakeup(void);
extern void Drv_Touch_Sleep(void);
extern void Drv_Touch_Idle(void);
extern void Drv_Touch_Test(void);
extern void Drv_Touch_IdleTimeoutCheck(void);

#endif









