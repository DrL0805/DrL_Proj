#ifndef __SM_TIMER_H
#define __SM_TIMER_H

#include "platform_common.h"

//����ʹ��CTimer��ģ������
//timer 0A~3B�����жϷ�������У�����˳��:0A->0B->1A->1B->2A->2B->3A->3B (0~7)
//������ȴ����Timer��Ҫ������ǰ���
typedef enum
{
    MOVT_CTIMER_MODULE,      //������
    MULTI_CTIMER_MODULE,     //multi-timer
    SYSTICK_CTIMER_MODULE,   //ϵͳtickʱ��
    KEY_CTIMER_MODULE,       //����
    STOPWATCH_CTIMER_MODULE, //��� stop watch
    COUNTDOWN_CTIMER_MODULE, //����ʱ count down
    RTC_CTIMER_MODULE,       //RTC
    //SUBMOVT_CTIMER_MODULE,   //С����
}ctimer_module;

//**********************************************************************
// ��������: ��ʼ��counter/timer
// ���������
// ���ز�����
//**********************************************************************
extern void SMDrv_CTimer_Init(void);

//**********************************************************************
// ��������: ����driver module ID��Ӳ����Ӧ��ctimer
// ���������	
//    modul: driver module ID,ֵ�ο�ctimer_module
//    u16freq: timerƵ��
//    timer_callback:�ϲ�ע����жϻص�����
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_CTimer_Open(ctimer_module modul,uint16 u16freq,comm_cb *timer_callback);

//**********************************************************************
// ��������:  ����CTimer�ж����ȼ�
// ��������� prio:�ж����ȼ���bit0~2λֵ��Ч
// ���ز����� ��
//**********************************************************************
extern void SMDrv_CTimer_SetIsrPrio(uint32 prio);

//**********************************************************************
// �������� : ����timer�Ƚ�ֵ
// ������� ��
//    modul : driver module ID,ֵ�ο�ctimer_module
//u32cmp_cnt: �Ƚ�ֵ
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
ret_type SMDrv_CTimer_SetCmpValue(ctimer_module modul,uint32 u32cmp_cnt);

//**********************************************************************
// ��������: ����timer
// ���������modul: driver module ID,ֵ�ο�ctimer_module
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_CTimer_Start(ctimer_module modul);

//**********************************************************************
// ��������: ֹͣtimer
// �������: modul: driver module ID,ֵ�ο�ctimer_module
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_CTimer_Stop(ctimer_module modul);

//**********************************************************************
// ��������: ����timer
// ���������modul: driver module ID,ֵ�ο�ctimer_module
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_CTimer_Clear(ctimer_module modul);

//**********************************************************************
// ��������: ��ȡtimer����ֵ
// �������: modul: driver module ID,ֵ�ο�ctimer_module
// ���ز���: ����timer����ֵ 
//**********************************************************************
extern uint16 SMDrv_CTimer_ReadCount(ctimer_module modul);

//**********************************************************************
// ��������: ��ȡģ��ʹ�õ�ctimer��number
// �������: modul: driver module ID,ֵ�ο�ctimer_module
// ���ز���: ctimer��number
//**********************************************************************
extern uint32 SMDrv_CTimer_GetTimerNumber(ctimer_module modul);

//**********************************************************************
// ��������: ���ڻ�о�׶β���ctimer
// �������: 
// ���ز���: ���Խ��,ֵ������0x00��˵���ж�ʱ�����쳣
//**********************************************************************
extern uint8 SMdrv_Ctimer_Test(void);

#endif

