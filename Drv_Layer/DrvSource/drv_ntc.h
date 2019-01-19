#ifndef DRV_NTC_H
#define DRV_NTC_H

#include "platform_common.h"

#define DRV_NTC_RTT_DEBUG	3
#if (1 == DRV_NTC_RTT_DEBUG)	// ����ȼ�
#define DRV_NTC_RTT_LOG(...)
#define DRV_NTC_RTT_WARN(...)
#define DRV_NTC_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == DRV_NTC_RTT_DEBUG)	// ����ȼ�
#define DRV_NTC_RTT_LOG(...)
#define DRV_NTC_RTT_WARN	RTT_DEBUG_WARN
#define DRV_NTC_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == DRV_NTC_RTT_DEBUG)	// ���Եȼ�
#define DRV_NTC_RTT_LOG		RTT_DEBUG_LOG
#define DRV_NTC_RTT_WARN	RTT_DEBUG_WARN
#define DRV_NTC_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define DRV_NTC_RTT_LOG(...)
#define DRV_NTC_RTT_WARN(...)
#define DRV_NTC_RTT_ERR(...)
#endif

// ��ѹ����
#define		VDD_TOTAL				(3300)		//mV
#define		RES_TEST				(5) 		//Kohm
#define  	NTC_TEMP_CACHE_NUM 		32			//�¶Ȼ������
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
	
	int16_t		 CurrTemp;	// ��ǰ�¶�ֵ
	int16_t		 UpLimitTemp;	// �¶����� 
	int16_t		 DownLimitTemp;	// �¶�����
	
	int16_t		 CacheLog[NTC_TEMP_CACHE_NUM];
	uint32_t     CacheCnt;
	
	
}NTC_PARAM_T;


extern void Drv_NTC_Init(void);
extern void Drv_NTC_StartSample(void);

#endif



