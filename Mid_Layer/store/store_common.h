#ifndef STORE_COMMON_H
#define STORE_COMMON_H

#include "store_variable.h"

#define STORE_CMN_RTT_DEBUG	3
#if (1 == STORE_CMN_RTT_DEBUG)	// 错误等级
#define STORE_CMN_RTT_LOG(...)
#define STORE_CMN_RTT_WARN(...)
#define STORE_CMN_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_CMN_RTT_DEBUG)	// 警告等级
#define STORE_CMN_RTT_LOG(...)
#define STORE_CMN_RTT_WARN		RTT_DEBUG_WARN
#define STORE_CMN_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_CMN_RTT_DEBUG)	// 调试等级
#define STORE_CMN_RTT_LOG		RTT_DEBUG_LOG
#define STORE_CMN_RTT_WARN	RTT_DEBUG_WARN
#define STORE_CMN_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_CMN_RTT_LOG(...)
#define STORE_CMN_RTT_WARN(...)
#define STORE_CMN_RTT_ERR(...)
#endif

extern void Store_Cmn_InfoRead(uint32_t LogAddr, uint8_t* pBuf, uint32_t Len);
extern void Store_Cmn_SysInfoReadUpdate(void);
extern void Store_Cmn_SysInfoWriteUpdate(void);
extern void Store_Cmn_FactoryInfoReadUpdate(void);
extern void Store_Cmn_FactoryInfoWriteUpdate(void);
extern void Store_Cmn_TimeInfoReadUpdate(void);
extern void Store_Cmn_TimeInfoWriteUpdate(void);
extern void Store_Cmn_AlarmInfoReadUpdate(void);
extern void Store_Cmn_AlarmInfoWriteUpdate(void);
extern void Store_Cmn_BodyInfoReadUpdate(void);
extern void Store_Cmn_BodyInfoWriteUpdate(void);
extern void Store_Cmn_MacWrite(uint8_t* Buf, uint32_t Len);
extern void Store_Cmn_MacRead(uint8_t* Buf, uint32_t Len);
extern void Store_Cmn_SnWrite(uint8_t* Buf, uint32_t Len);
extern void Store_Cmn_SnRead(uint8_t* Buf, uint32_t Len);

typedef enum 
{
	eStoreCmnEventSysInfoWrite,
	eStoreCmnEventTimeInfoWrite,
	eStoreCmnEventAlarmInfoWrite,
	eStoreCmnEvenBodyInfoWrite
}StoreCmnEventId_e;

typedef struct
{
	StoreCmnEventId_e	Id;
	uint8_t 			Param;
}StoreCmnEvent_t;

extern void Store_Cmn_EventProcess(StoreCmnEvent_t* Event_t);

#endif



