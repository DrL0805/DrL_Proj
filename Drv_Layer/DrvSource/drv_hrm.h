#ifndef HRM_H
#define HRM_H

#include "platform_common.h"

#define DRV_HRM_RTT_DEBUG	3
#if (1 == DRV_HRM_RTT_DEBUG)	// 错误等级
#define DRV_HRM_RTT_LOG(...)
#define DRV_HRM_RTT_WARN(...)
#define DRV_HRM_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == DRV_HRM_RTT_DEBUG)	// 警告等级
#define DRV_HRM_RTT_LOG(...)
#define DRV_HRM_RTT_WARN	RTT_DEBUG_WARN
#define DRV_HRM_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == DRV_HRM_RTT_DEBUG)	// 调试等级
#define DRV_HRM_RTT_LOG		RTT_DEBUG_LOG
#define DRV_HRM_RTT_WARN	RTT_DEBUG_WARN
#define DRV_HRM_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define DRV_HRM_RTT_LOG(...)
#define DRV_HRM_RTT_WARN(...)
#define DRV_HRM_RTT_ERR(...)
#endif

typedef enum
{
	eHrmMeasureHrdOnce,		// 心率单次测量
	eHrmMeasureHrdKeep,		// 心率持续测量
	eHrmMeasureHrvOnce,		// 压力单次测量
	eHrmMeasureHrvKeep,		// 压力持续测量
}eHrmMeasuretype;

typedef enum 
{
	OFF_TOUCH   = 0,
    ON_TOUCH    = 1,
}bsp_touch_state_s;

typedef enum
{
    HR_TOUCH,
    HR_DATA_READY,
}hrm_event;

typedef struct
{
	bool				InitFlg;
	eHrmMeasuretype		Type;	
}Drv_Hrm_Param_t;

typedef void (*hrm_event_cb)(hrm_event event);

extern void Drv_Hrm_MeasureTypeSet(eHrmMeasuretype Type);
extern void Drv_Hrm_Open(hrm_event_cb hrm_cb);
extern void Drv_Hrm_Close(void);
extern void Drv_Hrm_Start(void);
extern void Drv_Hrm_Stop(void);
extern Drv_Hrm_Param_t* Drv_Hrm_ParamPGet(void);
extern void Drv_Hrm_ReadTouchStatus(uint8 *ui8istouch);
extern void Drv_Hrm_Calculate(uint64_t ui64timestamp);
extern uint8 Drv_Hrm_SetAccelMen(int16 *fifodata, uint16 fifo_size);
extern uint8 Drv_Hrm_SetAccelRange(uint8 newrange);
extern void accelerometer_get_fifo(int16 **fifo, uint32 *fifo_size);
extern void accelerometer_start(void);
extern void accelerometer_stop(void);
extern uint8 Drv_Hrm_FactoryTest(uint16 ui16lightleak[3]);
extern uint8 Drv_Hrm_CheckHw(void);

extern void Drv_Hrm_SetCalCompleteCb(void (*cb)(uint8 hrmval));
extern void Drv_Hrv_SetCalCompleteCb(void (*cb)(float sdnn, float rmsd, float rri, uint8_t hr));
extern void Drv_Hrm_SetCalErrCb(void (*cb)(void));
extern void Drv_Hrv_SetCalErrCb(void (*cb)(void));

#endif
