#ifndef	_MID_SCHEDULER_H
#define	_MID_SCHEDULER_H

#include "platform_common.h"
#include "mid_key.h"
#include "mid_uart.h"
#include "drv_touch.h"
#include "mid_magnetism.h"
#include "mid_bat.h"
#include "mid_pressure.h"
#include "mid_infrared_temp.h"
#include "drv_gps.h"

#define MID_SCHD_RTT_DEBUG	3
#if (1 == MID_SCHD_RTT_DEBUG)	// 错误等级
#define MID_SCHD_RTT_LOG(...)
#define MID_SCHD_RTT_WARN(...)
#define MID_SCHD_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MID_SCHD_RTT_DEBUG)	// 警告等级
#define MID_SCHD_RTT_LOG(...)
#define MID_SCHD_RTT_WARN		RTT_DEBUG_WARN
#define MID_SCHD_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MID_SCHD_RTT_DEBUG)	// 调试等级
#define MID_SCHD_RTT_LOG		RTT_DEBUG_LOG
#define MID_SCHD_RTT_WARN		RTT_DEBUG_WARN
#define MID_SCHD_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define MID_SCHD_RTT_LOG(...)
#define MID_SCHD_RTT_WARN(...)
#define MID_SCHD_RTT_ERR(...)
#endif

/* Key参数信息 */
typedef struct
{
	eMidKeyVal	Val;	// 键值
}Mid_Schd_KeyParam_T;

typedef struct
{
	uart_module 	Module;		// 串口模块
	uint8_t 		EventType;	// 事件类型
}Mid_Schd_UartParam_T;

/* 中间层任务调度消息类型 */
typedef enum
{
	eSchdTaskMsgKey,
//	eSchdTaskMsgAccel,
//	eSchdTaskMsgGyro,
	eSchdTaskMsgMagnetism,
	eSchdTaskMsgUart,
	eSchdTaskMsgPressure,	// 气压环温
	eSchdTaskMsgTouch,	
	eSchdTaskMsgITemp,		// 红外体温
	eSchdTaskMsgCountDown,
	eSchdTaskMsgBat,
	eSchdTaskMsgGPS,
	eSchdTaskMsgMax,
}eSchdTaskMsgId;

/* 中间层任务调度数据结构体 */
typedef struct 
{
	eSchdTaskMsgId	Id;
	union
	{
		Mid_Schd_KeyParam_T		Key;
		Mid_Schd_UartParam_T	Uart;
		TouchGIDParam_t			Touch;
		MagEvent_t				Mag;
		BatEvent_t				Bat;
		PressEvent_t			Pressure;
		ITempEvent_t			ITemp;
		GPSEvent_t				GPS;
	}Param;
}Mid_Schd_TaskMsg_T;

extern void Mid_Schd_ParamInit(void);
extern void Mid_Schd_TaskEventSet(Mid_Schd_TaskMsg_T* Msg);
extern void Mid_Schd_TaskCreate(void);

extern SemaphoreHandle_t	SPI_I2C_M0_SemaphoreHandle;

#endif
