#ifndef	_DRV_TOUCH_H
#define	_DRV_TOUCH_H

#include "platform_common.h"



#define DRV_TOUCH_RTT_DEBUG	2
#if (1 == DRV_TOUCH_RTT_DEBUG)	// 错误等级
#define DRV_TOUCH_RTT_LOG(...)
#define DRV_TOUCH_RTT_WARN(...)
#define DRV_TOUCH_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == DRV_TOUCH_RTT_DEBUG)	// 警告等级
#define DRV_TOUCH_RTT_LOG(...)
#define DRV_TOUCH_RTT_WARN		RTT_DEBUG_WARN
#define DRV_TOUCH_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == DRV_TOUCH_RTT_DEBUG)	// 调试等级
#define DRV_TOUCH_RTT_LOG		RTT_DEBUG_LOG
#define DRV_TOUCH_RTT_WARN		RTT_DEBUG_WARN
#define DRV_TOUCH_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define DRV_TOUCH_RTT_LOG(...)
#define DRV_TOUCH_RTT_WARN(...)
#define DRV_TOUCH_RTT_ERR(...)
#endif

/** TP具有4个状态:
	各状态功耗：
		Active 1.5mA, Untouch 0.25mA, Idle 0.1mA（跟FAE实测0.1mA，但手册写的25uA）, Sleep 0.1uA
	状态切换：
		1、任何末试下RESET拉低进入Sleep模式，拉高进入Untouch模式
		2、非sleep模式下任意触摸进入Active模式
		3、[Active]-(2s无无操作)->[Untouch]<-(发指令)->[Idle]
		*/
typedef enum
{
	eTouchStateActive,
	eTouchStateUntouch,
	eTouchStateIdle,
	eTouchStateSleep,
}TouchStateType_e;

// Flick手势类型
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

// 触摸屏手势类型
typedef enum
{
	eTouchIsrProcess,	// 触摸中断处理
	
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

// 不同手势类型的具体参数
typedef struct
{
	eTouchGIDType	Type;	// 手势类型
	union
	{
		TouchGIDTapParam_t		Tap;
		TouchGIDFlickParam_t	Flick;
	}GID;
}TouchGIDParam_t;

typedef struct
{
	uint8_t PressIngFlg;	// 长按标志
	
	uint8_t	IdleTimeoutCnt;		// 计数，触摸2秒后让TP进入Idle
	TouchStateType_e	State;
	
	uint8_t	 Scale;
	uint8_t PointData[14];	// 触摸点阵信息
	uint16_t XResolution;	// X分辨率
	uint16_t YResolution;	// Y分辨率
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









