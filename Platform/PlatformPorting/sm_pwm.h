#ifndef __SM_PWM_H
#define __SM_PWM_H

#include "platform_common.h"

#define CTIMER_PWM_ENABLE     1

//定义使用pwm的模块类型
typedef enum
{
    BL_CTIMER_PWM_MODULE    = 0x80,    //背光, backlight
    LCDEC_CTIMER_PWM_MODULE,           //LCD EXTCOMIN
}pwm_module;

typedef void (*timer_irq)(uint32 status);

//**********************************************************************
// 函数功能: 根据driver module ID打开硬件PWM
// 输入参数：	
//    modul: driver module ID,值参考pwm_module
//    u16duty: 占空比
// 返回参数：Ret_InvalidParam或Ret_OK
//**********************************************************************
extern ret_type SMDrv_PWM_Open(pwm_module modul,uint16 u16duty);

//**********************************************************************
// 函数功能: 启动PWM
// 输入参数：modul: driver module ID,值参考pwm_module
// 返回参数：Ret_InvalidParam或Ret_OK
//**********************************************************************
extern ret_type SMDrv_PWM_Start(pwm_module modul);

//**********************************************************************
// 函数功能: 停止PWM
// 输入参数: modul: driver module ID,值参考pwm_module
// 返回参数：Ret_InvalidParam或Ret_OK
//**********************************************************************
extern ret_type SMDrv_PWM_Stop(pwm_module modul);

//**********************************************************************
// 函数功能: 设置ctimer中断服务callback
// 输入参数: 
// 返回参数：
//**********************************************************************
extern ret_type SMDrv_CTimer_SetCB(timer_irq tim_cb);

#endif

