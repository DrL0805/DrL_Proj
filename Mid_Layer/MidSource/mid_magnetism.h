#ifndef MID_MAGNETISM_H
#define MID_MAGNETISM_H

#include "platform_common.h"
#include "drv_mag.h"

#define MID_MAG_RTT_DEBUG		2
#if (1 == MID_MAG_RTT_DEBUG)	// 错误等级
#define MID_MAG_RTT_LOG(...)
#define MID_MAG_RTT_WARN(...)
#define MID_MAG_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MID_MAG_RTT_DEBUG)	// 警告等级
#define MID_MAG_RTT_LOG(...)
#define MID_MAG_RTT_WARN		RTT_DEBUG_WARN
#define MID_MAG_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MID_MAG_RTT_DEBUG)	// 调试等级
#define MID_MAG_RTT_LOG		RTT_DEBUG_LOG
#define MID_MAG_RTT_WARN		RTT_DEBUG_WARN
#define MID_MAG_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define MID_MAG_RTT_LOG(...)
#define MID_MAG_RTT_WARN(...)
#define MID_MAG_RTT_ERR(...)
#endif

// 采样范围
typedef enum
{
	eMidMagSampleRange2GS,
	eMidMagSampleRange8GS,
	eMidMagSampleRange12GS,
	eMidMagSampleRange20GS,
}eMidMagSampleRange;

// 采样率
typedef enum
{
	eMidMagSampleRate1HZ   = 1,		// 1000ms
	eMidMagSampleRate2HZ   = 2,		// 500ms
	eMidMagSampleRate25HZ  = 25,		// 40ms
	eMidMagSampleRate50HZ  = 50,		// 20ms
	eMidMagSampleRate100HZ = 100,		// 10ms
	eMidMagSampleRate200HZ = 200,		// 5ms	
}eMidMagSampleRate;

typedef enum
{
	MID_MAG_UNINIT,		// 未初始化的
	MID_MAG_INITED,		// 已初始化
	MID_MAG_SAMPLING,	// 采样中，
	MID_MAG_SAMPLED,	// 采样过，采样数据可读取，但不一定实时
}MID_MAG_STATE_E;

typedef struct
{
	uint32_t 					MTiemrId;		
	
	bool						InitedFlg;		// 已初始化标志
	bool						SamplingFlg;	// 正在采样标志
	
	int16_t 					LatestData[3];		// 保存最新采到的数据
	eMidMagSampleRate			SampleRate;			// 硬件采样率
	eMidMagSampleRange			SampleRange;		// 硬件采样范围
	uint32_t    				SamplePeriod;		// 采样定时周期，单位ms
}MID_MAG_PARA_T;

extern void Mid_Magnetism_Init(void);
extern void Mid_Mag_ParamSet(eMidMagSampleRate Rate, eMidMagSampleRange Range);
extern MID_MAG_PARA_T* Mid_Mag_ParamPGet(void);
extern uint16 Mid_Magnetism_SelfTest(void);
extern void Mid_Mag_Test(void);

extern void Mid_Mag_StartSample(void);
extern void Mid_Mag_StopSample(void);
extern void Mid_Mag_DataUpdate(void);

typedef enum 
{
	eMagEventStartSample,
	eMagEventStopSample,
	eMagEventDataUpdate,
}MagEventId_e;

typedef struct
{
	MagEventId_e	Id;
	uint8_t 		Param;
}MagEvent_t;

#endif		// MAGNETISM_APP_H

