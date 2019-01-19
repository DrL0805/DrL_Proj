#ifndef STORE_UPLOAD_H
#define STORE_UPLOAD_H

#if 0

#include "store_variable.h"

#define STORE_UPLOAD_RTT_DEBUG	3
#if (1 == STORE_UPLOAD_RTT_DEBUG)	// ����ȼ�
#define STORE_UPLOAD_RTT_LOG(...)
#define STORE_UPLOAD_RTT_WARN(...)
#define STORE_UPLOAD_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_UPLOAD_RTT_DEBUG)	// ����ȼ�
#define STORE_UPLOAD_RTT_LOG(...)
#define STORE_UPLOAD_RTT_WARN		RTT_DEBUG_WARN
#define STORE_UPLOAD_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_UPLOAD_RTT_DEBUG)	// ���Եȼ�
#define STORE_UPLOAD_RTT_LOG		RTT_DEBUG_LOG
#define STORE_UPLOAD_RTT_WARN		RTT_DEBUG_WARN
#define STORE_UPLOAD_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define STORE_UPLOAD_RTT_LOG(...)
#define STORE_UPLOAD_RTT_WARN(...)
#define STORE_UPLOAD_RTT_ERR(...)
#endif

typedef struct
{
	uint16_t 	Catalog;	// ��Ŀ¼����������
	uint32_t	DataLen;	// ��Ŀ¼���ݳ���
	uint32_t 	UTC;		// ��Ŀ¼��UTC
}Upload_Catalog_t;

typedef struct
{
	uint16_t			DataClassify;	// ���ݷ���
	uint16_t			CatalogNum;		// ������Ŀ¼��
	uint32_t			DataLen;		// ����Ŀ¼�洢�������ܳ��ȣ����ڸ���APP
	
	Store_Info_t 			StoreInfo;								// �洢��Ϣ�ṹ��
	Upload_Catalog_t		Catalog[STORE_MAX_SAVE_CATALOG_NUM];	// ���ϴ���Ŀ¼��Ϣ
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

