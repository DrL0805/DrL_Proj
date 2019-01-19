#ifndef STORE_GPS_H
#define STORE_GPS_H

#include "store_variable.h"

#define STORE_GPS_RTT_DEBUG	2
#if (1 == STORE_GPS_RTT_DEBUG)	// ����ȼ�
#define STORE_GPS_RTT_LOG(...)
#define STORE_GPS_RTT_WARN(...)
#define STORE_GPS_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_GPS_RTT_DEBUG)	// ����ȼ�
#define STORE_GPS_RTT_LOG(...)
#define STORE_GPS_RTT_WARN		RTT_DEBUG_WARN
#define STORE_GPS_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_GPS_RTT_DEBUG)	// ���Եȼ�
#define STORE_GPS_RTT_LOG		RTT_DEBUG_LOG
#define STORE_GPS_RTT_WARN		RTT_DEBUG_WARN
#define STORE_GPS_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define STORE_GPS_RTT_LOG(...)
#define STORE_GPS_RTT_WARN(...)
#define STORE_GPS_RTT_ERR(...)
#endif

// GPS�洢�㷨
typedef struct
{
	uint8_t			NewCatalogFlg;	// ��Ŀ¼������־
	
	uint32_t 		BeginUTC;		// ������ʼʱ��
	uint32_t 		GPSValidUTC;	// GPS��λ�ɹ�ʱ��
	uint32_t		BeginLongitude;
	uint32_t		BeginLatitude;
	uint32_t		BeginAltitude;
	
	uint32_t		LastLongitude;
	uint32_t		LastLatitude;
	uint32_t		LastAltitude;
	uint32_t 		LastStep;	
}StoreGPSAlgo_t;

typedef struct
{
	uint8_t			InitFlg;
	
	uint32_t 		LogCnt;						
	uint8_t			LogBuf[STORE2_GPS_LOG_MAX * STORE2_GPS_DATA_CLASSIFY_LEN];
	
	StoreGPSAlgo_t	Algo;
}StoreGPSParam_t;

extern void Store_GPS_ClearInit(void);
extern void Store_GPS_RecoverInit(void);
extern StoreInfo_t* Store_GPS_StoreInfoGet(void);
extern StoreGPSParam_t* Store_GPS_ParamPGet(void);
extern void Store_GPS_algorithm(void);
extern uint16_t Store_GPS_CatalogCreate(void);
extern uint16_t Store_GPS_DataSave(void);
extern uint16_t Store_GPS_CatalogSeal(void);
extern uint16_t Store_GPS_DataRead(void);
extern uint16_t Store_GPS_CatalogAllUpload(void);
extern void Store_GPS_RamDataClear(void);
extern void Store_GPS_DateSimulata(void);

#endif

