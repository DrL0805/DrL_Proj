#ifndef STORE_RUN_H
#define STORE_RUN_H

#include "store_variable.h"
#include "algorithm_running.h"

#define STORE_RUN_RTT_DEBUG	2
#if (1 == STORE_RUN_RTT_DEBUG)	// 错误等级
#define STORE_RUN_RTT_LOG(...)
#define STORE_RUN_RTT_WARN(...)
#define STORE_RUN_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_RUN_RTT_DEBUG)	// 警告等级
#define STORE_RUN_RTT_LOG(...)
#define STORE_RUN_RTT_WARN		RTT_DEBUG_WARN
#define STORE_RUN_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_RUN_RTT_DEBUG)	// 调试等级
#define STORE_RUN_RTT_LOG		RTT_DEBUG_LOG
#define STORE_RUN_RTT_WARN		RTT_DEBUG_WARN
#define STORE_RUN_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_RUN_RTT_LOG(...)
#define STORE_RUN_RTT_WARN(...)
#define STORE_RUN_RTT_ERR(...)
#endif

typedef struct
{
	bool	InitFlg;
	
	uint32_t 		LogCnt;						
	uint8_t			LogBuf[STORE2_RUN_LOG_MAX * STORE2_RUN_DATA_CLASSIFY_LEN];
	
//	runningRecord_t	AlgoRecord;	// 跑步档案信息
}StoreRunParam_t;

extern void Store_Run_ClearInit(void);
extern void Store_Run_RecoverInit(void);
extern StoreInfo_t* Store_Run_StoreInfoGet(void);
extern StoreRunParam_t* Store_Run_ParamPGet(void);
//extern void Store_Run_algorithm(uint32_t CurrUtc, runningInfo_t* RunningInfo);
extern void Store_Run_algorithm(void);
extern uint16_t Store_Run_DataRead(void);
extern void Store_Run_DateSimulata(void);
extern uint16_t Store_Run_CatalogSeal(void);

#if 1	// 外部不应用到的函数
extern uint16_t Store_Run_CatalogCreate(void);
extern void Store_Run_DataSave(void);
extern uint16_t Store_Run_CatalogAllUpload(void);
#endif

#endif




















