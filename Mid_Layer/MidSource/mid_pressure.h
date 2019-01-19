#ifndef MID_PRESSURE_H
#define MID_PRESSURE_H

#define 	AIRPRESSURE

#include "platform_common.h"
#include "drv_airpress.h"

#define MID_PRESS_RTT_DEBUG	2
#if (1 == MID_PRESS_RTT_DEBUG)	// 错误等级
#define MID_PRESS_RTT_LOG(...)
#define MID_PRESS_RTT_WARN(...)
#define MID_PRESS_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MID_PRESS_RTT_DEBUG)	// 警告等级
#define MID_PRESS_RTT_LOG(...)
#define MID_PRESS_RTT_WARN		RTT_DEBUG_WARN
#define MID_PRESS_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MID_PRESS_RTT_DEBUG)	// 调试等级
#define MID_PRESS_RTT_LOG		RTT_DEBUG_LOG
#define MID_PRESS_RTT_WARN		RTT_DEBUG_WARN
#define MID_PRESS_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define MID_PRESS_RTT_LOG(...)
#define MID_PRESS_RTT_WARN(...)
#define MID_PRESS_RTT_ERR(...)
#endif

typedef enum
{
	eMidPressSampleTemp,		// 采集温度
	eMidPressSamplePress,		// 采集气压
	eMidPressSampleTempPress,	// 温度气压持续采集
	eMidPressSampleMax,
}eMidPressSampleType;

typedef struct
{
	uint8_t						InitedFlg;			// 已初始化标志
	uint8_t						TempUpdateFlg;		// 温度采集成功标志
	uint8_t						PressUpdateFlg;		// 气压采集成功标志
	uint8_t						ContinuousCvtFlg;	// 持续采样标志
	
	AirpressOSR_e 				Osr;		// 过采样率
	AirpressMR_e				Mr;			// 持续测量时每秒测量次数
	eMidPressSampleType			SampleType;	// 采样类型

	int16						LastTemp;	// 保存最新温度值
	int32						LastPress;
}MID_PRESS_PARA_T;

extern void Mid_Press_ParamSet(AirpressOSR_e Osr, eMidPressSampleType SampleType);
extern void Mid_Press_PressStart(void);
extern void Mid_Press_TempUpdate(void);
extern void Mid_Press_PressUpdate(void);
extern MID_PRESS_PARA_T* Mid_Press_ParamPGet(void);

extern uint16_t Mid_Press_Init(void);
extern uint16 Mid_Press_SelfTest(void);
extern void Mid_Press_ContinuousCvtCheck(void);
extern void Mid_Press_Test(void);

typedef enum 
{
	ePressEventStartSample,
	ePressEventDataUpdate,
}PressEventId_e;

typedef struct
{
	PressEventId_e	Id;
	uint8_t 		Param;
}PressEvent_t;

#endif

