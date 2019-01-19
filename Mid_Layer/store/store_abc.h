#ifndef STORE_ABC_H
#define STORE_ABC_H

#include "store_variable.h"
#include "algorithm_abc.h"

#define STORE_ABC_RTT_DEBUG	2
#if (1 == STORE_ABC_RTT_DEBUG)	// 错误等级
#define STORE_ABC_RTT_LOG(...)
#define STORE_ABC_RTT_WARN(...)
#define STORE_ABC_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_ABC_RTT_DEBUG)	// 警告等级
#define STORE_ABC_RTT_LOG(...)
#define STORE_ABC_RTT_WARN		RTT_DEBUG_WARN
#define STORE_ABC_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_ABC_RTT_DEBUG)	// 调试等级
#define STORE_ABC_RTT_LOG		RTT_DEBUG_LOG
#define STORE_ABC_RTT_WARN		RTT_DEBUG_WARN
#define STORE_ABC_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_ABC_RTT_LOG(...)
#define STORE_ABC_RTT_WARN(...)
#define STORE_ABC_RTT_ERR(...)
#endif


typedef struct
{
	bool			InitFlg;
	
	uint32_t 		LogCnt;						
	uint8_t			LogBuf[STORE2_ABC_LOG_MAX * STORE2_ABC_DATA_CLASSIFY_LEN];
}StoreABCParam_t;

extern void Store_ABC_ClearInit(void);
extern void Store_ABC_RecoverInit(void);
extern StoreInfo_t* Store_ABC_StoreInfoGet(void);
extern StoreABCParam_t* Store_ABC_ParamPGet(void);
extern void Store_ABC_algorithm(void);
extern uint16_t Store_ABC_CatalogCreate(void);
extern uint16_t Store_ABC_DataSave(void);
extern uint16_t Store_ABC_CatalogSeal(void);
extern uint16_t Store_ABC_DataRead(void);
extern uint16_t Store_ABC_CatalogAllUpload(void);
extern void Store_ABC_UIPressureGet(int32_t* Buf, uint32_t Len);
extern void Store_ABC_UIAltitudeGet(int32_t* Buf, uint32_t Len);
extern void Store_ABC_DateSimulata(void);

#endif

