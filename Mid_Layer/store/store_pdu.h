#ifndef STORE_PDU_H
#define STORE_PDU_H

#include "store_variable.h"

#define STORE_PDU_RTT_DEBUG	3
#if (1 == STORE_PDU_RTT_DEBUG)	// 错误等级
#define STORE_PDU_RTT_LOG(...)
#define STORE_PDU_RTT_WARN(...)
#define STORE_PDU_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_PDU_RTT_DEBUG)	// 警告等级
#define STORE_PDU_RTT_LOG(...)
#define STORE_PDU_RTT_WARN		RTT_DEBUG_WARN
#define STORE_PDU_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_PDU_RTT_DEBUG)	// 调试等级
#define STORE_PDU_RTT_LOG		RTT_DEBUG_LOG
#define STORE_PDU_RTT_WARN		RTT_DEBUG_WARN
#define STORE_PDU_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_PDU_RTT_LOG(...)
#define STORE_PDU_RTT_WARN(...)
#define STORE_PDU_RTT_ERR(...)
#endif

typedef enum
{
	eStorePDUIdle,				// 空闲
	eStorePDUCatalogDetailRTS,	// 正在发送目录细节，仅运动场景数据有目录细节
	eStorePDUCatalogDataRTS,	// 正在发送目录数据
	eStorePDUSleepRecordRTS,	// 正在发送睡眠档案信息
}StorePDUState_e;

/* 读取目录有用信息，不直接保存 CatalogInfo_t 结构体，是为了节约RAM */
typedef struct
{
	uint32_t CatalogSerial;	// 此目录真正物理编号
	uint32_t DataLen;	// 此目录对应数据区数据长度
	uint32_t DataAddr;	// 此目录对应数据区地址
	
	uint32_t UTC;			// 此目录的UTC
	uint16_t ExtDataLen;	// 此目录附加信息长度
}PDUCatalog_t;

typedef struct
{
	uint8_t		FlowCtrl;		// 流控
	uint8_t 	EachSendLen;	// 每次发送数据长度
	uint8_t		RecordBuf[100];	// 存放待发送的场景档案数据
	uint8_t		ClassifyLen;	// 数据类型最小数据单位长度
	uint16_t	SampleUnit;		// 此数据类型的采样单位
	uint32_t	RecordLen;		// 场景档案数据长度
	uint32_t	SendCnt;		// 已发送计数/发送睡眠档案时表示已发送次数
	uint32_t 	CurrCatalog;	// 正在发送数据的目录 0~(STORE2_MAX_SAVE_CATALOG_NUM-1), 值为0xFFFF时表示上传的RAM目录
}PDURTSInfo_t;	// 发送信息结构体

/* 
	说明：
	有些数据app请求上传时，希望已产生的数据都能上传，如计步
	但由于H002所有nandflash的限制，每page一次擦除允许写入次数有限（推荐4次，实测超过32次后必出错）。
	所以H002的存储逻辑是，产生数据后先缓存在RAM，达到一定数量后再存到FLASH
	因此才出此下策：开辟一块ram，当app请求数据时，把已产生的ram数据放在这里，需要则上传给APP。
	注：1）运动场景数据用不到此结构体，因为运动场景数据必须保存后才允许上传。
		2）睡眠档案数据上传也使用的这块RAM
*/
typedef struct
{
	uint8_t			ValidFlg;		// RAM目录有效标志
	uint8_t			UploadFlg;		// RAM目录数据正在上传标志
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
	uint16_t			DataClassify;	// 数据分类
	uint16_t			CatalogNum;		// 读到的目录数
	uint32_t			AllDataLen;		// 所有目录存储的数据总长度，用于告诉APP	
	StoreInfo_t*		pPDUStoreInfo;	// 待上传数据的存储信息结构体指针
	StorePDUState_e		State;
	
	PDURamData_t		RamData;
	PDUCatalog_t		Catalog[STORE2_MAX_SAVE_CATALOG_NUM];	// 目录信息
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




















