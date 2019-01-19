#ifndef DRV_NTC_H
#define DRV_NTC_H

#include "platform_common.h"

#define DRV_NTC_RTT_DEBUG	3
#if (1 == DRV_NTC_RTT_DEBUG)	// 错误等级
#define DRV_NTC_RTT_LOG(...)
#define DRV_NTC_RTT_WARN(...)
#define DRV_NTC_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == DRV_NTC_RTT_DEBUG)	// 警告等级
#define DRV_NTC_RTT_LOG(...)
#define DRV_NTC_RTT_WARN	RTT_DEBUG_WARN
#define DRV_NTC_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == DRV_NTC_RTT_DEBUG)	// 调试等级
#define DRV_NTC_RTT_LOG		RTT_DEBUG_LOG
#define DRV_NTC_RTT_WARN	RTT_DEBUG_WARN
#define DRV_NTC_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define DRV_NTC_RTT_LOG(...)
#define DRV_NTC_RTT_WARN(...)
#define DRV_NTC_RTT_ERR(...)
#endif

// 分压电阻
#define		VDD_TOTAL				(3300)		//mV
#define		RES_TEST				(5) 		//Kohm
#define  	NTC_TEMP_CACHE_NUM 		32			//温度缓存个数
#define 	NTC_TMEPERATURE_UPMAX     4500
#define 	NTC_TMEPERATURE_DOWNMAX   3500
#define 	NTC_PARA_MAX 			  60

typedef enum
{
	eNTCStateUninit,
	eNTCStateInited,
}eNTCStateType;

typedef struct
{
	eNTCStateType	State;
	bool			TempErrFlg;	
	
	int16_t		 CurrTemp;	// 当前温度值
	int16_t		 UpLimitTemp;	// 温度上限 
	int16_t		 DownLimitTemp;	// 温度下限
	
	int16_t		 CacheLog[NTC_TEMP_CACHE_NUM];
	uint32_t     CacheCnt;
	
	
}NTC_PARAM_T;


extern void Drv_NTC_Init(void);
extern void Drv_NTC_StartSample(void);

#endif



