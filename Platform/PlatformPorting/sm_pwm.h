#ifndef __SM_PWM_H
#define __SM_PWM_H

#include "platform_common.h"

#define CTIMER_PWM_ENABLE     1

//����ʹ��pwm��ģ������
typedef enum
{
    BL_CTIMER_PWM_MODULE    = 0x80,    //����, backlight
    LCDEC_CTIMER_PWM_MODULE,           //LCD EXTCOMIN
}pwm_module;

typedef void (*timer_irq)(uint32 status);

//**********************************************************************
// ��������: ����driver module ID��Ӳ��PWM
// ���������	
//    modul: driver module ID,ֵ�ο�pwm_module
//    u16duty: ռ�ձ�
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_PWM_Open(pwm_module modul,uint16 u16duty);

//**********************************************************************
// ��������: ����PWM
// ���������modul: driver module ID,ֵ�ο�pwm_module
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_PWM_Start(pwm_module modul);

//**********************************************************************
// ��������: ֹͣPWM
// �������: modul: driver module ID,ֵ�ο�pwm_module
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_PWM_Stop(pwm_module modul);

//**********************************************************************
// ��������: ����ctimer�жϷ���callback
// �������: 
// ���ز�����
//**********************************************************************
extern ret_type SMDrv_CTimer_SetCB(timer_irq tim_cb);

#endif

