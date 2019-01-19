#ifndef STORE_PART_H
#define STORE_PART_H

#include "store_variable.h"

#define STORE_PART_RTT_DEBUG	2
#if (1 == STORE_PART_RTT_DEBUG)	// 错误等级
#define STORE_PART_RTT_LOG(...)
#define STORE_PART_RTT_WARN(...)
#define STORE_PART_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_PART_RTT_DEBUG)	// 警告等级
#define STORE_PART_RTT_LOG(...)
#define STORE_PART_RTT_WARN		RTT_DEBUG_WARN
#define STORE_PART_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_PART_RTT_DEBUG)	// 调试等级
#define STORE_PART_RTT_LOG		RTT_DEBUG_LOG
#define STORE_PART_RTT_WARN		RTT_DEBUG_WARN
#define STORE_PART_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_PART_RTT_LOG(...)
#define STORE_PART_RTT_WARN(...)
#define STORE_PART_RTT_ERR(...)
#endif

/*
	store_part使用情况，当外部使用part模块存储数据时，需在此说明，防止共用。
	
	256B，共320part：
	序号	管理者		用途
	0~9		DrL			系统信息
	 :0		DrL			系统配置开关，如提醒开关、久坐开关、系统语言等
	 :1		DrL			时间信息，系统时间、世界时间、勿扰时间、久坐时间、城市代号等
	 :2	    DrL			闹钟信息
	 :3		DrL			人体信息，身高体重年龄等
	 :4-9	DrL			保留
	10		ZSL			蓝牙广播信息
	
	512B，共80part：
	序号	使用者		用途
	
	1KB，共40part：
	序号	使用者		用途
	
	2KB，共20part：
	序号	使用者		用途
	0-4 	ZSL			蓝牙配对码，最多5个
	5		DrL			系统复位信息（WDT/OTA复位前需要保存的信息）
*/


typedef enum
{
	eStorePart256B,
	eStorePart512B,
	eStorePart1KB,
	eStorePart2KB
}StorePartType_e;

typedef struct
{
	bool	InitFlg;
}StorePartParam_t;

extern void Store_Part_Init(void);
extern void Store_Part_Write(StorePartType_e PartType, uint32_t Part, uint8_t* DataBuf, uint32_t DataLen);
extern void Store_Part_Read(StorePartType_e PartType, uint32_t Part, uint8_t* DataBuf, uint32_t DataLen);
extern void Store_Part_Test(void);



#endif



