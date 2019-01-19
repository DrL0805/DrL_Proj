#ifndef STORE_HISTORY_H
#define STORE_HISTORY_H

#include "store_variable.h"
#include "app_variable.h"
#include "algorithm_running.h"
#include "algorithm_swim_indoor.h"
#include "algorithm_climbMountain.h"

#define STORE_HISTORY_RTT_DEBUG	2
#if (1 == STORE_HISTORY_RTT_DEBUG)	// ����ȼ�
#define STORE_HISTORY_RTT_LOG(...)
#define STORE_HISTORY_RTT_WARN(...)
#define STORE_HISTORY_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_HISTORY_RTT_DEBUG)	// ����ȼ�
#define STORE_HISTORY_RTT_LOG(...)
#define STORE_HISTORY_RTT_WARN		RTT_DEBUG_WARN
#define STORE_HISTORY_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_HISTORY_RTT_DEBUG)	// ���Եȼ�
#define STORE_HISTORY_RTT_LOG		RTT_DEBUG_LOG
#define STORE_HISTORY_RTT_WARN		RTT_DEBUG_WARN
#define STORE_HISTORY_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define STORE_HISTORY_RTT_LOG(...)
#define STORE_HISTORY_RTT_WARN(...)
#define STORE_HISTORY_RTT_ERR(...)
#endif

#define STORE_HISTORY_LIST_MAX	(30)

typedef struct
{
	eDataClassifyCode	DataClassify;	// �����������ͣ��ܲ�����ɽ����Ӿ
	union
	{
		runningRecord_t			Run;
		climbMountainRecord_t	Climb;
		swimIndoorRecord_t		Swim;
	}Record;
}StoreHistoryRecord_t;

// �˶���ʷ��Ϣ�����ݹ���飬����UI��ʾ
typedef struct
{
	eDataClassifyCode	DataClassify;	// �����������ͣ��ܲ�����ɽ����Ӿ
	uint32_t 			CatalogSerial;	// ����Ŀ¼���
	uint32_t			UTC;			// �˶�ʱ��
	uint32_t			Distance;		// �˶�����
}StoreHistoryList_t;

typedef struct
{
	bool					InitFlg;
	
	uint8_t					ListCnt;	// ��¼��ʷ��Ϣ�м���
	uint8_t					ListPos;	// ��ǰ�洢λ�ã�����ѭ���洢��ȡֵ 0~(STORE_HISTORY_LIST_MAX-1)
	StoreHistoryList_t		ListBuf[STORE_HISTORY_LIST_MAX];
}StoreHistoryParam_t;

extern void Store_History_Init(void);
extern void Store_History_ListAdd(StoreHistoryList_t* fStoreHistoryList);
extern StoreHistoryList_t* Store_History_ListPGet(uint8_t fSerial);
extern void Store_History_RecordGet(uint8_t fSerial, StoreHistoryRecord_t* fStoreHistoryRecord);
extern StoreHistoryParam_t* Store_History_ParamPGet(void);
extern void Store_History_Test(void);

#endif


















