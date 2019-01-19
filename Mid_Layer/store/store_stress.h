#ifndef STORE_STRESS_H
#define STORE_STRESS_H

#include "store_variable.h"
#include "algorithm_stress.h"

#define STORE_STRESS_RTT_DEBUG	2
#if (1 == STORE_STRESS_RTT_DEBUG)	// 错误等级
#define STORE_STRESS_RTT_LOG(...)
#define STORE_STRESS_RTT_WARN(...)
#define STORE_STRESS_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_STRESS_RTT_DEBUG)	// 警告等级
#define STORE_STRESS_RTT_LOG(...)
#define STORE_STRESS_RTT_WARN		RTT_DEBUG_WARN
#define STORE_STRESS_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_STRESS_RTT_DEBUG)	// 调试等级
#define STORE_STRESS_RTT_LOG		RTT_DEBUG_LOG
#define STORE_STRESS_RTT_WARN		RTT_DEBUG_WARN
#define STORE_STRESS_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_STRESS_RTT_LOG(...)
#define STORE_STRESS_RTT_WARN(...)
#define STORE_STRESS_RTT_ERR(...)
#endif

typedef struct
{
	bool			InitFlg;
	
	uint32_t 		LogCnt;						
	uint8_t			LogBuf[STORE2_STRESS_LOG_MAX * STORE2_STRESS_DATA_CLASSIFY_LEN];
}StoreStressParam_t;

extern void Store_Stress_ClearInit(void);
extern void Store_Stress_RecoverInit(void);
extern StoreInfo_t* Store_Stress_StoreInfoGet(void);
extern StoreStressParam_t* Store_Stress_ParamPGet(void);
extern void Store_Stress_algorithm(void);
extern uint16_t Store_Stress_CatalogCreate(void);
extern uint16_t Store_Stress_DataSave(void);
extern uint16_t Store_Stress_CatalogSeal(void);
extern uint16_t Store_Stress_DataRead(void);
extern uint16_t Store_Stress_CatalogAllUpload(void);
extern void Store_Stress_UIDataGet(uint8_t* Buf, uint32_t Len);
extern void Store_Stress_DateSimulata(void);


#endif

