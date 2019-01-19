#ifndef STORE_SLEEP_H
#define STORE_SLEEP_H

#include "store_variable.h"

#define STORE_SLEEP_RTT_DEBUG	2
#if (1 == STORE_SLEEP_RTT_DEBUG)	// 错误等级
#define STORE_SLEEP_RTT_LOG(...)
#define STORE_SLEEP_RTT_WARN(...)
#define STORE_SLEEP_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_SLEEP_RTT_DEBUG)	// 警告等级
#define STORE_SLEEP_RTT_LOG(...)
#define STORE_SLEEP_RTT_WARN		RTT_DEBUG_WARN
#define STORE_SLEEP_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_SLEEP_RTT_DEBUG)	// 调试等级
#define STORE_SLEEP_RTT_LOG		RTT_DEBUG_LOG
#define STORE_SLEEP_RTT_WARN		RTT_DEBUG_WARN
#define STORE_SLEEP_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_SLEEP_RTT_LOG(...)
#define STORE_SLEEP_RTT_WARN(...)
#define STORE_SLEEP_RTT_ERR(...)
#endif

typedef struct
{
	uint8_t			InitFlg;

	uint32_t 		LogCnt;						
	uint8_t			LogBuf[STORE2_SLEEP_LOG_MAX * STORE2_SLEEP_DATA_CLASSIFY_LEN];	
}StoreSleepParam_t;


extern void Store_Sleep_ClearInit(void);
extern void Store_Sleep_RecoverInit(void);
extern StoreInfo_t* Store_Sleep_StoreInfoGet(void);
extern StoreSleepParam_t* Store_Sleep_ParamPGet(void);
extern void Store_Sleep_algorithm(uint32_t Sleep);
extern uint16_t Store_Sleep_CatalogCreate(void);
extern uint16_t Store_Sleep_DataSave(void);
extern uint16_t Store_Sleep_CatalogSeal(void);
extern uint16_t Store_Sleep_DataRead(void);
extern uint16_t Store_Sleep_CatalogAllUpload(void);
extern void Store_Sleep_RamDataClear(void);
extern void Store_Sleep_DateSimulata(void);










#endif


