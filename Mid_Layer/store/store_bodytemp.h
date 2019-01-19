#ifndef STORE_BODYTEMP_H
#define STORE_BODYTEMP_H

#define STORE_BODYTEMP_RTT_DEBUG	2
#if (1 == STORE_BODYTEMP_RTT_DEBUG)	// 错误等级
#define STORE_BODYTEMP_RTT_LOG(...)
#define STORE_BODYTEMP_RTT_WARN(...)
#define STORE_BODYTEMP_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_BODYTEMP_RTT_DEBUG)	// 警告等级
#define STORE_BODYTEMP_RTT_LOG(...)
#define STORE_BODYTEMP_RTT_WARN		RTT_DEBUG_WARN
#define STORE_BODYTEMP_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_BODYTEMP_RTT_DEBUG)	// 调试等级
#define STORE_BODYTEMP_RTT_LOG		RTT_DEBUG_LOG
#define STORE_BODYTEMP_RTT_WARN		RTT_DEBUG_WARN
#define STORE_BODYTEMP_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_BODYTEMP_RTT_LOG(...)
#define STORE_BODYTEMP_RTT_WARN(...)
#define STORE_BODYTEMP_RTT_ERR(...)
#endif

#include "store_variable.h"

typedef struct
{
	bool			InitFlg;
	
	uint32_t 		LogCnt;						
	uint8_t			LogBuf[STORE2_BODYTEMP_LOG_MAX * STORE2_BODYTEMP_DATA_CLASSIFY_LEN];
}StoreBodytempParam_t;

extern void Store_Bodytemp_ClearInit(void);
extern void Store_Bodytemp_RecoverInit(void);
extern StoreInfo_t* Store_Bodytemp_StoreInfoGet(void);
extern StoreBodytempParam_t* Store_Bodytemp_ParamPGet(void);
extern void Store_Bodytemp_algorithm(void);
extern uint16_t Store_Bodytemp_CatalogCreate(void);
extern uint16_t Store_Bodytemp_DataSave(void);
extern uint16_t Store_Bodytemp_CatalogSeal(void);
extern uint16_t Store_Bodytemp_DataRead(void);
extern uint16_t Store_Bodytemp_CatalogAllUpload(void);
extern void Store_Bodytemp_UIDataGet(int16_t* Buf, uint32_t Len);
extern void Store_Bodytemp_DateSimulata(void);

#endif

