#ifndef STORE_HISTORY_H
#define STORE_HISTORY_H

#include "store_variable.h"
#include "app_variable.h"
#include "algorithm_running.h"
#include "algorithm_swim_indoor.h"
#include "algorithm_climbMountain.h"

#define STORE_HISTORY_RTT_DEBUG	2
#if (1 == STORE_HISTORY_RTT_DEBUG)	// 错误等级
#define STORE_HISTORY_RTT_LOG(...)
#define STORE_HISTORY_RTT_WARN(...)
#define STORE_HISTORY_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_HISTORY_RTT_DEBUG)	// 警告等级
#define STORE_HISTORY_RTT_LOG(...)
#define STORE_HISTORY_RTT_WARN		RTT_DEBUG_WARN
#define STORE_HISTORY_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_HISTORY_RTT_DEBUG)	// 调试等级
#define STORE_HISTORY_RTT_LOG		RTT_DEBUG_LOG
#define STORE_HISTORY_RTT_WARN		RTT_DEBUG_WARN
#define STORE_HISTORY_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_HISTORY_RTT_LOG(...)
#define STORE_HISTORY_RTT_WARN(...)
#define STORE_HISTORY_RTT_ERR(...)
#endif

#define STORE_HISTORY_LIST_MAX	(30)

typedef struct
{
	eDataClassifyCode	DataClassify;	// 场景数据类型：跑步、登山、游泳
	union
	{
		runningRecord_t			Run;
		climbMountainRecord_t	Climb;
		swimIndoorRecord_t		Swim;
	}Record;
}StoreHistoryRecord_t;

// 运动历史信息，根据规格书，用于UI显示
typedef struct
{
	eDataClassifyCode	DataClassify;	// 场景数据类型：跑步、登山、游泳
	uint32_t 			CatalogSerial;	// 物理目录序号
	uint32_t			UTC;			// 运动时间
	uint32_t			Distance;		// 运动距离
}StoreHistoryList_t;

typedef struct
{
	bool					InitFlg;
	
	uint8_t					ListCnt;	// 记录历史消息有几条
	uint8_t					ListPos;	// 当前存储位置，用于循环存储，取值 0~(STORE_HISTORY_LIST_MAX-1)
	StoreHistoryList_t		ListBuf[STORE_HISTORY_LIST_MAX];
}StoreHistoryParam_t;

extern void Store_History_Init(void);
extern void Store_History_ListAdd(StoreHistoryList_t* fStoreHistoryList);
extern StoreHistoryList_t* Store_History_ListPGet(uint8_t fSerial);
extern void Store_History_RecordGet(uint8_t fSerial, StoreHistoryRecord_t* fStoreHistoryRecord);
extern StoreHistoryParam_t* Store_History_ParamPGet(void);
extern void Store_History_Test(void);

#endif


















