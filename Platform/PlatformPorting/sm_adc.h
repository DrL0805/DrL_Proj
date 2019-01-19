#ifndef __SM_ADC_H
#define __SM_ADC_H

#include "platform_common.h"

#define		ADC_REF_VOL				(2000)//参考电压(mv)，由ＡＤＣ配置决定
#define		ADC_FULL_LEVEL			(16383)//满量程ＡＤ值，0x3fff,14bits

//定义使用adc的模块类型
//说明:软件中用到的module放在MAX_ADC_MODULE前，没用的放在后面
typedef enum
{
    BAT_ADC_MODULE,       //BAT Adc
    BODY_TEMP_ADC_MODULE, //体温，热敏
    MAX_ADC_MODULE,
}adc_module;

typedef void (*adc_cb)(uint32 u32adcValue);

//**********************************************************************
// 函数功能: 初始化ADC
// 输入参数：
// 返回参数：
//**********************************************************************
extern void SMDrv_ADC_Init(void);

//*****************************************************************************
//函数功能：打开一个ADC通道,并启动
// 输入参数：module：module id,同时也是slot ID,因此值需小于8，最多支持8个slot
// 			adc_callback: callback函调函数
// 返回：	无
//*****************************************************************************
extern ret_type SMDrv_ADC_Open(adc_module module,adc_cb adc_callback);

//*****************************************************************************
//函数功能：关闭一个打开的ADC通道
// 输入参数：module：
// 返回：	无
//*****************************************************************************
extern ret_type SMDrv_ADC_Close(adc_module module);

//**********************************************************************
// 函数功能: 启动ADC转换
// 输入参数：无
// 返回参数：	
//**********************************************************************
extern void SMDrv_ADC_StartDetect(void);

//**********************************************************************
// 函数功能:  设置ADC中断优先级,并启动ADC中断
// 输入参数:
//     prio:中断优先级，bit0~2位值有效
// 返回参数： 无
//**********************************************************************
extern ret_type SMDrv_ADC_SetIsrPrio(uint32 prio);

#endif

