#ifndef STORE_CLIMB_H
#define STORE_CLIMB_H

#include "store_variable.h"
#include "algorithm_climbMountain.h"

#define STORE_CLIMB_RTT_DEBUG	2
#if (1 == STORE_CLIMB_RTT_DEBUG)	// 错误等级
#define STORE_CLIMB_RTT_LOG(...)
#define STORE_CLIMB_RTT_WARN(...)
#define STORE_CLIMB_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_CLIMB_RTT_DEBUG)	// 警告等级
#define STORE_CLIMB_RTT_LOG(...)
#define STORE_CLIMB_RTT_WARN		RTT_DEBUG_WARN
#define STORE_CLIMB_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_CLIMB_RTT_DEBUG)	// 调试等级
#define STORE_CLIMB_RTT_LOG		RTT_DEBUG_LOG
#define STORE_CLIMB_RTT_WARN		RTT_DEBUG_WARN
#define STORE_CLIMB_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_CLIMB_RTT_LOG(...)
#define STORE_CLIMB_RTT_WARN(...)
#define STORE_CLIMB_RTT_ERR(...)
#endif

typedef struct
{
	bool	InitFlg;
	
	uint32_t 		LogCnt;						
	uint8_t			LogBuf[STORE2_CLIMB_LOG_MAX * STORE2_CLIMB_DATA_CLASSIFY_LEN];
	
//	climbMountainRecord_t	AlgoRecord;	// 跑步档案信息
}StoreClimbParam_t;

extern void Store_Climb_ClearInit(void);
extern void Store_Climb_RecoverInit(void);
extern StoreInfo_t* Store_Climb_StoreInfoGet(void);
extern StoreClimbParam_t* Store_Climb_ParamPGet(void);
extern void Store_Climb_algorithm(void);
extern uint16_t Store_Climb_CatalogCreate(void);
extern uint16_t Store_Climb_DataSave(void);
extern uint16_t Store_Climb_CatalogSeal(void);
extern uint16_t Store_Climb_DataRead(void);
extern uint16_t Store_Climb_CatalogAllUpload(void);

extern void Store_Climb_DateSimulata(void);

#endif



