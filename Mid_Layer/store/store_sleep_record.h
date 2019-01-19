#ifndef STORE_SLEEP_RECORD_H
#define STORE_SLEEP_RECORD_H

#include "store_variable.h"
#include "app_variable.h"

#define STORE_SLPRCD_RTT_DEBUG	2
#if (1 == STORE_SLPRCD_RTT_DEBUG)	// 错误等级
#define STORE_SLPRCD_RTT_LOG(...)
#define STORE_SLPRCD_RTT_WARN(...)
#define STORE_SLPRCD_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_SLPRCD_RTT_DEBUG)	// 警告等级
#define STORE_SLPRCD_RTT_LOG(...)
#define STORE_SLPRCD_RTT_WARN		RTT_DEBUG_WARN
#define STORE_SLPRCD_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_SLPRCD_RTT_DEBUG)	// 调试等级
#define STORE_SLPRCD_RTT_LOG		RTT_DEBUG_LOG
#define STORE_SLPRCD_RTT_WARN		RTT_DEBUG_WARN
#define STORE_SLPRCD_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_SLPRCD_RTT_LOG(...)
#define STORE_SLPRCD_RTT_WARN(...)
#define STORE_SLPRCD_RTT_ERR(...)
#endif

typedef struct
{
	uint8_t		InitFlg;
}StoreSlpRcdParam_t;

extern void Store_SlpRcd_ClearInit(void);
extern void Store_SlpRcd_RecoverInit(void);
extern StoreInfo_t* Store_SlpRcd_StoreInfoGet(void);
extern StoreSlpRcdParam_t* Store_SlpRcd_ParamPGet(void);
extern void Store_SlpRcd_RecordStore(void);
extern uint16_t Store_SlpRcd_DataRead(void);
extern uint16_t Store_SlpRcd_CatalogAllUpload(void);
extern void Store_SlpRcd_DateSimulata(void);

#endif


