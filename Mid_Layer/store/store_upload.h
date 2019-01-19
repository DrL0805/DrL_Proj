#ifndef STORE_UPLOAD_H
#define STORE_UPLOAD_H

#if 0

#include "store_variable.h"

#define STORE_UPLOAD_RTT_DEBUG	3
#if (1 == STORE_UPLOAD_RTT_DEBUG)	// 错误等级
#define STORE_UPLOAD_RTT_LOG(...)
#define STORE_UPLOAD_RTT_WARN(...)
#define STORE_UPLOAD_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_UPLOAD_RTT_DEBUG)	// 警告等级
#define STORE_UPLOAD_RTT_LOG(...)
#define STORE_UPLOAD_RTT_WARN		RTT_DEBUG_WARN
#define STORE_UPLOAD_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_UPLOAD_RTT_DEBUG)	// 调试等级
#define STORE_UPLOAD_RTT_LOG		RTT_DEBUG_LOG
#define STORE_UPLOAD_RTT_WARN		RTT_DEBUG_WARN
#define STORE_UPLOAD_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_UPLOAD_RTT_LOG(...)
#define STORE_UPLOAD_RTT_WARN(...)
#define STORE_UPLOAD_RTT_ERR(...)
#endif

typedef struct
{
	uint16_t 	Catalog;	// 此目录真正物理编号
	uint32_t	DataLen;	// 此目录数据长度
	uint32_t 	UTC;		// 此目录的UTC
}Upload_Catalog_t;

typedef struct
{
	uint16_t			DataClassify;	// 数据分类
	uint16_t			CatalogNum;		// 读到的目录数
	uint32_t			DataLen;		// 所有目录存储的数据总长度，用于告诉APP
	
	Store_Info_t 			StoreInfo;								// 存储信息结构体
	Upload_Catalog_t		Catalog[STORE_MAX_SAVE_CATALOG_NUM];	// 待上传的目录信息
}Store_Upload_Param_t;

extern void Store_Upload_Init(void);
extern uint16_t Store_Upload_CatalogGet(uint16_t DataClassify);
extern uint16_t Store_Upload_SceneCatalogGet(uint16_t DataClassify);
extern void Store_Upload_CatalogAllDelete(void);
extern uint16_t Store_Upload_CatalogUTCDelete(uint32_t UTC);
extern uint16_t Store_Upload_DataGet(uint16_t CatalogSerial, uint16_t Offset, uint8_t* DataBuf, uint32_t DataLen);
extern void Store_Upload_ParamGet(Store_Upload_Param_t* Store_Upload_Param);

#endif

#endif

