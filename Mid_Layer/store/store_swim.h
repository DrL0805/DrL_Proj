#ifndef STORE_SWIM_H
#define STORE_SWIM_H

#include "store_variable.h"
#include "algorithm_swim_indoor.h"

#define STORE_SWIM_RTT_DEBUG	2
#if (1 == STORE_SWIM_RTT_DEBUG)	// 错误等级
#define STORE_SWIM_RTT_LOG(...)
#define STORE_SWIM_RTT_WARN(...)
#define STORE_SWIM_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_SWIM_RTT_DEBUG)	// 警告等级
#define STORE_SWIM_RTT_LOG(...)
#define STORE_SWIM_RTT_WARN		RTT_DEBUG_WARN
#define STORE_SWIM_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_SWIM_RTT_DEBUG)	// 调试等级
#define STORE_SWIM_RTT_LOG		RTT_DEBUG_LOG
#define STORE_SWIM_RTT_WARN		RTT_DEBUG_WARN
#define STORE_SWIM_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_SWIM_RTT_LOG(...)
#define STORE_SWIM_RTT_WARN(...)
#define STORE_SWIM_RTT_ERR(...)
#endif

typedef struct
{
	bool			InitFlg;
	
	uint32_t 		LogCnt;						
	uint8_t			LogBuf[STORE2_SWIM_LOG_MAX * STORE2_SWIM_DATA_CLASSIFY_LEN];
}StoreSwimParam_t;

extern void Store_Swim_ClearInit(void);
extern void Store_Swim_RecoverInit(void);
extern StoreInfo_t* Store_Swim_StoreInfoGet(void);
extern StoreSwimParam_t* Store_Swim_ParamPGet(void);
extern void Store_Swim_algorithm(void);
extern uint16_t Store_Swim_CatalogCreate(void);
extern uint16_t Store_Swim_DataSave(void);
extern uint16_t Store_Swim_CatalogSeal(void);
extern uint16_t Store_Swim_DataRead(void);
extern uint16_t Store_Swim_CatalogAllUpload(void);

extern void Store_Swim_DateSimulata(void);

#endif



