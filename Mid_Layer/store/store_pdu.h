#ifndef STORE_PDU_H
#define STORE_PDU_H

#include "store_variable.h"

#define STORE_PDU_RTT_DEBUG	3
#if (1 == STORE_PDU_RTT_DEBUG)	// ����ȼ�
#define STORE_PDU_RTT_LOG(...)
#define STORE_PDU_RTT_WARN(...)
#define STORE_PDU_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_PDU_RTT_DEBUG)	// ����ȼ�
#define STORE_PDU_RTT_LOG(...)
#define STORE_PDU_RTT_WARN		RTT_DEBUG_WARN
#define STORE_PDU_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_PDU_RTT_DEBUG)	// ���Եȼ�
#define STORE_PDU_RTT_LOG		RTT_DEBUG_LOG
#define STORE_PDU_RTT_WARN		RTT_DEBUG_WARN
#define STORE_PDU_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define STORE_PDU_RTT_LOG(...)
#define STORE_PDU_RTT_WARN(...)
#define STORE_PDU_RTT_ERR(...)
#endif

typedef enum
{
	eStorePDUIdle,				// ����
	eStorePDUCatalogDetailRTS,	// ���ڷ���Ŀ¼ϸ�ڣ����˶�����������Ŀ¼ϸ��
	eStorePDUCatalogDataRTS,	// ���ڷ���Ŀ¼����
	eStorePDUSleepRecordRTS,	// ���ڷ���˯�ߵ�����Ϣ
}StorePDUState_e;

/* ��ȡĿ¼������Ϣ����ֱ�ӱ��� CatalogInfo_t �ṹ�壬��Ϊ�˽�ԼRAM */
typedef struct
{
	uint32_t CatalogSerial;	// ��Ŀ¼����������
	uint32_t DataLen;	// ��Ŀ¼��Ӧ���������ݳ���
	uint32_t DataAddr;	// ��Ŀ¼��Ӧ��������ַ
	
	uint32_t UTC;			// ��Ŀ¼��UTC
	uint16_t ExtDataLen;	// ��Ŀ¼������Ϣ����
}PDUCatalog_t;

typedef struct
{
	uint8_t		FlowCtrl;		// ����
	uint8_t 	EachSendLen;	// ÿ�η������ݳ���
	uint8_t		RecordBuf[100];	// ��Ŵ����͵ĳ�����������
	uint8_t		ClassifyLen;	// ����������С���ݵ�λ����
	uint16_t	SampleUnit;		// ���������͵Ĳ�����λ
	uint32_t	RecordLen;		// �����������ݳ���
	uint32_t	SendCnt;		// �ѷ��ͼ���/����˯�ߵ���ʱ��ʾ�ѷ��ʹ���
	uint32_t 	CurrCatalog;	// ���ڷ������ݵ�Ŀ¼ 0~(STORE2_MAX_SAVE_CATALOG_NUM-1), ֵΪ0xFFFFʱ��ʾ�ϴ���RAMĿ¼
}PDURTSInfo_t;	// ������Ϣ�ṹ��

/* 
	˵����
	��Щ����app�����ϴ�ʱ��ϣ���Ѳ��������ݶ����ϴ�����Ʋ�
	������H002����nandflash�����ƣ�ÿpageһ�β�������д��������ޣ��Ƽ�4�Σ�ʵ�ⳬ��32�κ�س�����
	����H002�Ĵ洢�߼��ǣ��������ݺ��Ȼ�����RAM���ﵽһ���������ٴ浽FLASH
	��˲ų����²ߣ�����һ��ram����app��������ʱ�����Ѳ�����ram���ݷ��������Ҫ���ϴ���APP��
	ע��1���˶����������ò����˽ṹ�壬��Ϊ�˶��������ݱ��뱣���������ϴ���
		2��˯�ߵ��������ϴ�Ҳʹ�õ����RAM
*/
typedef struct
{
	uint8_t			ValidFlg;		// RAMĿ¼��Ч��־
	uint8_t			UploadFlg;		// RAMĿ¼���������ϴ���־
//	uint8_t			DateBuf[1024];
	uint16_t 		DataLen;
	uint32_t 		UTC;
	union
	{
		uint8_t 		DataBuf[1024];	
		sleep_record_t	SleepRecord;
	}RAM;
}PDURamData_t;

typedef struct
{
	uint8_t				InitFlg;
	uint16_t			DataClassify;	// ���ݷ���
	uint16_t			CatalogNum;		// ������Ŀ¼��
	uint32_t			AllDataLen;		// ����Ŀ¼�洢�������ܳ��ȣ����ڸ���APP	
	StoreInfo_t*		pPDUStoreInfo;	// ���ϴ����ݵĴ洢��Ϣ�ṹ��ָ��
	StorePDUState_e		State;
	
	PDURamData_t		RamData;
	PDUCatalog_t		Catalog[STORE2_MAX_SAVE_CATALOG_NUM];	// Ŀ¼��Ϣ
	PDURTSInfo_t		RTS;
}StorePDUParam_t;

extern void Store_PDU_TimerHandler(void);
extern void Store_PDU_Init(void);
extern StorePDUParam_t* Store_PDU_ParamPGet(void);
extern uint16_t Store_PDU_CatalogInfoRTS(uint16 fDataClassify, uint8 flowControl);
extern uint16_t Store_PDU_BaseCatalogDetailRTS(uint16 fDataClassify, uint16_t fCatalog, uint8 flowControl);
extern uint16_t Store_PDU_SceneCatalogDetailRTS(uint16 fDataClassify, uint16_t fCatalog, uint8 flowControl);
extern uint16_t Store_PDU_CatalogDataRTS(uint16 fDataClassify, uint32 fUTC, uint16 fPackSerial, uint8 flowControl);
extern uint16_t Store_PDU_DeleteAll(uint8 flowControl);
extern uint16_t Store_PDU_ClassifyDelete(uint16 fDataClassify, uint8 flowControl);
extern uint16_t Store_PDU_UTCCatalogDelete(uint16 fDataClassify, uint32 UTC, uint8 flowControl);

extern uint16_t Store_PDU_SleepRecordCatalogRTS(uint8 flowControl);
extern uint16_t Store_PDU_SleepRecordDataRTS(uint16_t fCatalog, uint8 flowControl);
extern uint16_t Store_PDU_SleepRecordDelete(uint32 UTC, uint8 flowControl);

#endif




















