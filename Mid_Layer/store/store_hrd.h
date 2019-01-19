#ifndef STORE_HRD_H
#define STORE_HRD_H

#include "store_variable.h"

#define STORE_HRD_RTT_DEBUG	2
#if (1 == STORE_HRD_RTT_DEBUG)	// 错误等级
#define STORE_HRD_RTT_LOG(...)
#define STORE_HRD_RTT_WARN(...)
#define STORE_HRD_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_HRD_RTT_DEBUG)	// 警告等级
#define STORE_HRD_RTT_LOG(...)
#define STORE_HRD_RTT_WARN		RTT_DEBUG_WARN
#define STORE_HRD_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_HRD_RTT_DEBUG)	// 调试等级
#define STORE_HRD_RTT_LOG		RTT_DEBUG_LOG
#define STORE_HRD_RTT_WARN		RTT_DEBUG_WARN
#define STORE_HRD_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_HRD_RTT_LOG(...)
#define STORE_HRD_RTT_WARN(...)
#define STORE_HRD_RTT_ERR(...)
#endif

typedef struct
{
	bool			InitFlg;
	
	uint32_t 		LogCnt;						
	uint8_t			LogBuf[STORE2_HRD_LOG_MAX * STORE2_HRD_DATA_CLASSIFY_LEN];
}StoreHrdParam_t;

extern void Store_Hrd_ClearInit(void);
extern void Store_Hrd_RecoverInit(void);
extern StoreInfo_t* Store_Hrd_StoreInfoGet(void);
extern StoreHrdParam_t* Store_Hrd_ParamPGet(void);
extern void Store_Hrd_algorithm(void);
extern uint16_t Store_Hrd_CatalogCreate(void);
extern uint16_t Store_Hrd_DataSave(void);
extern uint16_t Store_Hrd_CatalogSeal(void);
extern uint16_t Store_Hrd_DataRead(void);
extern uint16_t Store_Hrd_CatalogAllUpload(void);
extern void Store_Hrd_UIDataGet(uint8_t* Buf, uint32_t Len);
extern void Store_Hrd_DateSimulata(void);


#endif

