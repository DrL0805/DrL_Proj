#ifndef DRV_CHARGER_H
#define DRV_CHARGER_H

#include "platform_common.h"

typedef enum 
{
    BAT_OFF_CHARGE 		= 0x00,
    BAT_IN_CHARGING,
    BAT_FULL_CHARGE,
}bat_charge_envet;

typedef	void (*ChargeCheckCb)(bat_charge_envet evnet);

//**********************************************************************
// 函数功能:  充电初始化
// 输入参数： chg_cb:充电相关事件回调函数
// 返回参数：    
//**********************************************************************
extern ret_type Drv_Charge_Open(ChargeCheckCb chg_cb);

//**********************************************************************
// 函数功能:	电池充电状态检测
// 输入参数：	无
// 返回参数：	无
//**********************************************************************
extern void Drv_Charge_CheckStatus(void);

//**********************************************************************
// 函数功能:  充电自检
// 输入参数： 无
// 返回参数：    
//**********************************************************************
extern ret_type Drv_Charge_SelfTest(void);

#endif

