#ifndef MID_HRM_H
#define MID_HRM_H

#include "platform_common.h"
#include "drv_hrm.h"

#define MID_HRM_RTT_DEBUG	2
#if (1 == MID_HRM_RTT_DEBUG)	// 错误等级
#define MID_HRM_RTT_LOG(...)
#define MID_HRM_RTT_WARN(...)
#define MID_HRM_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MID_HRM_RTT_DEBUG)	// 警告等级
#define MID_HRM_RTT_LOG(...)
#define MID_HRM_RTT_WARN	RTT_DEBUG_WARN
#define MID_HRM_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MID_HRM_RTT_DEBUG)	// 调试等级
#define MID_HRM_RTT_LOG		RTT_DEBUG_LOG
#define MID_HRM_RTT_WARN	RTT_DEBUG_WARN
#define MID_HRM_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define MID_HRM_RTT_LOG(...)
#define MID_HRM_RTT_WARN(...)
#define MID_HRM_RTT_ERR(...)
#endif

#define HRM_INVALID_VALUE	0		// 无效心率值
#define HRM_UNWEAR_TIMEOUT	3		// 未佩戴检测超时时间

typedef enum
{
	eMidHrmEventCalculate,
	eMidHrmEventHrmComplete,		// 心率计算完成
	eMidHrmEventHrvComplete,		// 压力计算完成
	eMidHrmEventHrdErr,				// 心率计算错误
	eMidHrmEventHrvErr,				// 压力计算错误
	eMidHrmEventUnwear,				// 未佩戴
	eMidHrmEventTimeout,			// 算法超时
}eMidHrmEventType;

// 心率当前状态
typedef enum
{
	eMidHrmStateIdle,		// 空闲
	eMidHrmStateMeasuring,	// 测量中
//	eMidHrmStateUnwear,		// 未佩戴
//	eMidHrmStateDone,		// 测量完成
}eMidHrmStateType;

typedef struct
{
	bool				InitFlg;
	bool				HrUpdateFlg;		// 心率测量值更新标志，每次开始测量时复位
	eMidHrmStateType	State;				// 心率计状态
	eHrmMeasuretype		MeasureType;		// 测量类型：心率、压力
	
	uint8_t		UnwearCnt;			// 未佩戴检测计数
	uint8_t		TimeoutCnt;			// 算法超时计数

	uint8_t		CurrHeartRate;		// 当前更新的心率值，0xFF表示无效
	uint8_t		LastHeartRate;		// 上次有效的心率值
}Mid_Hrm_Param_t;

extern void Mid_Hrm_AccelMenSet(int16 *fifodata);
extern void Mid_Hrm_Start(eHrmMeasuretype Type);
extern void Mid_Hrm_Stop(void);
extern void Mid_Hrm_Calculate(void);
extern void Mid_Hrm_UnwearCheck(void);
extern void Mid_Hrm_TimeoutCheck(void);
extern void Mid_Hrm_Init(void);
extern void Mid_Hrm_TouchStatusRead(uint8 *ui8istouch);
extern Mid_Hrm_Param_t* Mid_Hrm_ParamPGet(void);
extern uint16 Mid_Hrm_FactoryTestRead(uint16 ui16lightleak[3]);
extern uint8 Mid_Hrm_FactoryTest(void);
extern void Mid_Hrm_Test(void);

#endif





