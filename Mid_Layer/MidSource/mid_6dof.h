#ifndef	MID_6DOF_H
#define	MID_6DOF_H

#include "platform_common.h"
#include "bmi160.h"

#define MID_6DOF_RTT_DEBUG		3
#if (1 == MID_6DOF_RTT_DEBUG)	// 错误等级
#define MID_6DOF_RTT_LOG(...)
#define MID_6DOF_RTT_WARN(...)
#define MID_6DOF_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MID_6DOF_RTT_DEBUG)	// 警告等级
#define MID_6DOF_RTT_LOG(...)
#define MID_6DOF_RTT_WARN		RTT_DEBUG_WARN
#define MID_6DOF_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MID_6DOF_RTT_DEBUG)	// 调试等级
#define MID_6DOF_RTT_LOG		RTT_DEBUG_LOG
#define MID_6DOF_RTT_WARN		RTT_DEBUG_WARN
#define MID_6DOF_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define MID_6DOF_RTT_LOG(...)
#define MID_6DOF_RTT_WARN(...)
#define MID_6DOF_RTT_ERR(...)
#endif

/** Header模式读取25组数据，需要177字节；加速度+角速度25Hz数据约350字节（不使用BMI160_FIFO_TIME） */
#define MID_6DOF_FIFO_LEN	(450)	// 

typedef struct
{
	uint16_t SamplePeriod;	// 采样周期，单位ms
	uint8_t ODRFlg;			// 正在采样（数据可读）标志
	
	/** 各采样率应用层计数，当计数值为0时，关闭对应硬件 */
	uint8_t ODR1HzCnt;
	uint8_t ODR25HzCnt;
}MidAccParam_t;

typedef struct
{
	uint16_t SamplePeriod;	// 采样周期，单位ms
	uint8_t ODRFlg;			// 正在采样（数据可读）标志
	
	/** 各采样率应用层计数，当计数值为0时，关闭对应硬件 */
	uint8_t ODR25HzCnt;
}MidGyrParam_t;

typedef struct
{
	bool						InitFlg;
	
	struct bmi160_dev			Dev;			// 硬件驱动相关结构体
	struct bmi160_fifo_frame	FIFOFrame;		// 硬件驱动FIFO相关结构体
//	uint8_t 					FIFOBuf[MID_6DOF_FIFO_LEN];	// 25Hz采样，1秒缓存25*6=150字节数据
	
	MidAccParam_t				Acc;
	MidGyrParam_t				Gyr;
}Mid6DofParam_t;

extern void Mid_6Dof_Init(void);
extern void Mid_6Dof_AccStart(uint8_t fODR);
extern void Mid_6Dof_AccStop(uint8_t fODR);
extern void Mid_6Dof_GyrStart(uint8_t fODR);
extern void Mid_6Dof_GyrStop(uint8_t fODR);
extern uint16_t Mid_6Dof_FIFORead(struct bmi160_sensor_data* fAccData, uint8_t* fAccLen, struct bmi160_sensor_data* fGyrData, uint8_t* fGyrLen);
extern Mid6DofParam_t* Mid_6Dof_ParamPGet(void);
extern void Mid_6Dof_Test(void);

#endif







