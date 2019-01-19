#ifndef STORE_ALGO_H
#define STORE_ALGO_H

#include "store_variable.h"

#define STORE_ALGO_RTT_DEBUG	3
#if (1 == STORE_ALGO_RTT_DEBUG)	// 错误等级
#define STORE_ALGO_RTT_LOG(...)
#define STORE_ALGO_RTT_WARN(...)
#define STORE_ALGO_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_ALGO_RTT_DEBUG)	// 警告等级
#define STORE_ALGO_RTT_LOG(...)
#define STORE_ALGO_RTT_WARN	RTT_DEBUG_WARN
#define STORE_ALGO_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_ALGO_RTT_DEBUG)	// 调试等级
#define STORE_ALGO_RTT_LOG		RTT_DEBUG_LOG
#define STORE_ALGO_RTT_WARN		RTT_DEBUG_WARN
#define STORE_ALGO_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_ALGO_RTT_LOG(...)
#define STORE_ALGO_RTT_WARN(...)
#define STORE_ALGO_RTT_ERR(...)
#endif


extern uint32_t Store_Algo_NextCatalogGet(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial);
extern uint32_t Store_Algo_LastCatalogGet(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial);
extern uint32_t Store_Algo_CatalogAddrGet(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial);
extern uint16_t Store_Algo_CatalogMark(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial, CatalogMart_e Mark);
extern uint16_t Store_Algo_CatalogCreate(StoreInfo_t* fStoreInfo);
extern uint16_t Store_Algo_DataSave(StoreInfo_t* fStoreInfo, uint8_t* DataBuf, uint32_t DataLen);
extern uint16_t Store_Algo_CatalogSeal(StoreInfo_t* fStoreInfo, uint8_t* ExtDataBuf, uint32_t ExtDataLen);
extern uint16_t Store_Algo_CatalogRecover(StoreInfo_t* fStoreInfo);
extern uint16_t Store_Algo_CatalogRead(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial, CatalogInfo_t* CatalogInfo);
extern uint16_t Store_Algo_CatalogExtRead(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial, uint8_t* DataBuf, uint32_t DataLen);
extern uint16_t Store_Algo_DataRead(StoreInfo_t* fStoreInfo, CatalogInfo_t* fCatalogInfo, uint32_t Offset, uint8_t* DataBuf, uint32_t DataLen);
extern uint16_t Store_Algo_CatalogUpload(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial);
extern uint16_t Store_Algo_CatalogAllUpload(StoreInfo_t* fStoreInfo);
extern uint16_t Store_Algo_CatalogClear(StoreInfo_t* fStoreInfo);
#endif



