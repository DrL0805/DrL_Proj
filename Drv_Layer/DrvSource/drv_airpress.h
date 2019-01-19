#ifndef AIR_PRESSURE_H
#define AIR_PRESSURE_H

#include "platform_common.h"

//oversampling rate 过采样率：一次有效数据需采样几次进行计算
typedef enum
{
    eAirpressOSR_1 		= 0x00,	// 1times, 3.6ms 
    eAirpressOSR_2 		= 0x01,	// 2times, 5.2ms
    eAirpressOSR_4 		= 0x02,	// 4times, 8.4ms
    eAirpressOSR_8 		= 0x03,	// 8times, 14.8ms
    eAirpressOSR_16 	= 0x04,	// 16times, 27.6ms
    eAirpressOSR_32 	= 0x05,	// 32times, 53.2ms
	eAirpressOSR_64 	= 0x06,	// 64times, 104.4ms
    eAirpressOSR_128 	= 0x07,	// 128times, 206.8ms
	eAirpressOSR_MAX,
}AirpressOSR_e;

// measurement rate 测量率：持续测量时每秒几次
typedef enum
{
    eAirpressMR_1 	= 0x00, // 1 measurement pr. sec.
    eAirpressMR_2 	= 0x10,	// 2 measurement pr. sec.
    eAirpressMR_4 	= 0x20,	// 3 measurement pr. sec.
    eAirpressMR_8 	= 0x30,	// 4 measurement pr. sec.
    eAirpressMR_16 	= 0x40,	// 5 measurement pr. sec.
    eAirpressMR_32 	= 0x50,	// 6 measurement pr. sec.
	eAirpressMR_64 	= 0x60,	// 7 measurement pr. sec.
    eAirpressMR_128 	= 0x70,	// 8 measurement pr. sec.
	eAirpressMR_MAX,
}AirpressMR_e;

//control reg status
typedef enum
{
    COEF_RDY  	= 0x80,		// 系数完成
    SENSOR_RDY  = 0x40,		// 传感器初始化完成
    TMP_RDY  	= 0x20,		// 温度新数据可读
    RPS_RDY 	= 0x10,		// 气压新数据可读
}AirPressSensorState;

// measurement mode and type
typedef enum
{
    STANDBY  		= 0x00,		// 待机模式
    PRS_MEAS  		= 0x01,		// 气压测量
    TMP_MEAS  		= 0x02,		// 温度测量
    BG_PRS_MEAS 	= 0x05,		// 周期性气压测量
	BG_TMP_MEAS 	= 0x06,		// 周期性温度测量
	BG_ALL_MEAS		= 0x07,		// 周期性气压和温度测量
}AirPressMode;

extern uint8 Drv_AirPress_EnableIO(void);
extern uint8 Drv_AirPress_DisableIO(void);

extern uint8 Drv_AirPress_Init(void);
extern void Drv_AirPress_Calibrate(void);	// 传感器自校准，未使用
extern uint8 Drv_AirPress_TempSingleCvt(void);	// 开启一次温度采集
extern uint8 Drv_AirPress_PressSingleCvt(void);	// 开启一次气压采集
extern uint8 Drv_AirPress_TemPressContinuousCvt(void);	// 启动气压温度持续采集
extern uint8 Drv_AirPress_ReadPress(int32 *Press);	// 读取压力值，单位Pa
extern uint8 Drv_AirPress_ReadTemp(int16 *Temp);	// 读取温度值，℃*100
extern uint8 Drv_AirPress_SetAltitudeCmps(int32 LocalAvgPress);	// 设置海拔高度计算值的补偿量，未使用
extern uint8 Drv_AirPress_SelfTest(void);
extern uint8 Drv_AirPress_Standby(void);	// 设置传感器standby　mode
extern uint8 Drv_AirPress_PressCvtParaConfig(AirpressOSR_e fAirpressOSR, AirpressMR_e fAirpressMR);	// 气压采集参数配置
extern uint8 Drv_AirPress_TempCvtParaConfig(AirpressOSR_e fAirpressOSR, AirpressMR_e fAirpressMR);	// 温度采集参数配置
extern void Drv_AirPress_SoftReset(void);


#endif
