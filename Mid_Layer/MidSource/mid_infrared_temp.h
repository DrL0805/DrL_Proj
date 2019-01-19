#ifndef MID_INFRARED_TEMP_H
#define	MID_INFRARED_TEMP_H

#include "platform_common.h"

#define MID_IT_RTT_DEBUG	3
#if (1 == MID_IT_RTT_DEBUG)	// 错误等级
#define MID_IT_RTT_LOG(...)
#define MID_IT_RTT_WARN(...)
#define MID_IT_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MID_IT_RTT_DEBUG)	// 警告等级
#define MID_IT_RTT_LOG(...)
#define MID_IT_RTT_WARN		RTT_DEBUG_WARN
#define MID_IT_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MID_IT_RTT_DEBUG)	// 调试等级
#define MID_IT_RTT_LOG		RTT_DEBUG_LOG
#define MID_IT_RTT_WARN		RTT_DEBUG_WARN
#define MID_IT_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define MID_IT_RTT_LOG(...)
#define MID_IT_RTT_WARN(...)
#define MID_IT_RTT_ERR(...)
#endif

typedef struct
{
	bool				InitFlg;
	bool				UpdateFlg;

	int32_t 			CurrTemp;
}Mid_IT_Param_t;

extern void Mid_IT_Init(void);
extern void Mid_IT_ConverStart(void);
extern void Mid_IT_ConverStop(void);
extern void Mid_IT_TempCal(void);
extern Mid_IT_Param_t* Mid_IT_ParamPGet(void);
extern void Mid_IT_Test(void);

typedef enum 
{
	eITempEventStartSample,
	eITempEventStopSample,
	eITempEventDataUpdate,
}ITempEventId_e;

typedef struct
{
	ITempEventId_e	Id;
	uint8_t 		Param;
}ITempEvent_t;















#endif			//BAT_APP_H

