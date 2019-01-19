#ifndef __SM_GPIO_H
#define __SM_GPIO_H

#include "am_mcu_apollo.h"
#include "platform_common.h"

#ifdef AM_PART_APOLLO3
#define GPIO_PIN_DISABLE  0x00   //��ֹ���͹�����
#define GPIO_PIN_INPUT    0x01     //����
#define GPIO_PIN_OUTPUT   0x02    //���
#define GPIO_PIN_OD       0x04 	//��©
#define GPIO_PIN_3STATE   0x08    //����̬

#else
//��������1��2������������ϣ���GPIO_PIN_INPUT|AM_HAL_GPIO_PULL1_5K
//��������1
#define GPIO_PIN_DISABLE  AM_HAL_PIN_DISABLE   //��ֹ���͹�����
#define GPIO_PIN_INPUT    AM_HAL_PIN_INPUT     //����
#define GPIO_PIN_OUTPUT   AM_HAL_PIN_OUTPUT    //���
#define GPIO_PIN_OD       AM_HAL_PIN_OPENDRAIN //��©
#define GPIO_PIN_3STATE   AM_HAL_PIN_3STATE    //����̬

//��������2
#define GPIO_PIN_POWER    AM_HAL_GPIO_POWER
#define GPIO_PIN_HIGH_DRV AM_HAL_GPIO_HIGH_DRIVE
#define GPIO_PIN_LOW_DRV  AM_HAL_GPIO_LOW_DRIVE
#define GPIO_PIN_PULLUP   AM_HAL_GPIO_PULLUP     //����
#define GPIO_PIN_PULL1_5K AM_HAL_GPIO_PULL1_5K   //����
#define GPIO_PIN_PULL6K   AM_HAL_GPIO_PULL6K     //����6K
#define GPIO_PIN_PULL12K  AM_HAL_GPIO_PULL12K    //����12K
#define GPIO_PIN_PULL24K  AM_HAL_GPIO_PULL24K    //����24K
#endif

typedef void (*gpio_cb)(uint32 u32PinNum);

//**********************************************************************
// ��������:    GPIO��ʼ��
// ���������    ��
// ���ز�����    ��
//**********************************************************************
extern void SMDrv_GPIO_Init(void);

//**********************************************************************
// ��������: ����GPIO module ID����GPIO����:����/�������Ϊ�жϣ�������
//           �������жϷ������
// ���������u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
//    config_opt:����GPIO���ԣ����ڳ����иı�GPIO����ʱʹ�ã�����GPIOģ��
//      IICʱ��SDA��һ��Ϊ���룬һ��Ϊ�����
//      == NULL: ʹ��Ĭ�ϵ��������ã� != NULL: ��ʹ�ô��������,ֵ�ο�GPIO_PIN_xxx
//    g_callback:�жϷ�����callback
// ���ز���: Ret_OK��Ret_InvalidParam
//**********************************************************************
extern ret_type SMDrv_GPIO_Open(uint32 u32PinNum,uint32 *config_opt,gpio_cb g_callback);

//**********************************************************************
// ��������:  ���������жϴ�������
// ��������� u32PinNum: gpio num,
//   u32pol:  =1: �����أ�=0: �½���
// ���ز����� ��
//**********************************************************************
extern void SMDrv_GPIO_ReConfigIrq(uint32 u32PinNum,uint32 u32pol);

//**********************************************************************
// ��������:  ����/�ر�pin���ж�
// ��������� u32PinNum: gpio num,
// u8Enable:  =1: enable�жϣ�=0: disable�ж�
// ���ز����� ��
//**********************************************************************
extern void SMDrv_GPIO_EnableInterrupt(uint32 u32PinNum,uint8 u8Enable);

//**********************************************************************
// ��������:  ����GPIO�ж����ȼ�
// ��������� prio:�ж����ȼ���bit0~2λֵ��Ч
// ���ز����� ��
//**********************************************************************
extern void SMDrv_GPIO_SetIrqPrio(uint32 prio);

//**********************************************************************
// ��������:  ����GPIOΪ����ģʽ����uart��iic��spi��pdm��
// ��������� u32pin:   gpio num, 
//            u32config: gpio pad
// ���ز����� ��
//**********************************************************************
extern void SMDrv_GPIO_SetIOPad(uint32 u32pin,uint32 u32config);

//**********************************************************************
// ��������:  ��GPIO disable������ʵ�ֵ͹���
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� Ret_InvalidParam,Ret_OK
//**********************************************************************
extern ret_type SMDrv_GPIO_Close(uint32 u32PinNum);

//**********************************************************************
// ��������:  ����pin������ߵ�ƽ
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� Ret_InvalidParam,Ret_OK
//**********************************************************************
extern ret_type SMDrv_GPIO_BitSet(uint32 u32PinNum);

//**********************************************************************
// ��������:  ����pin������͵�ƽ
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� Ret_InvalidParam,Ret_OK
//**********************************************************************
extern ret_type SMDrv_GPIO_BitClear(uint32 u32PinNum);

//**********************************************************************
// ��������:  ��pin�������ƽ��ת
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� Ret_InvalidParam,Ret_OK
//**********************************************************************
extern ret_type SMDrv_GPIO_BitToggle(uint32 u32PinNum);

//**********************************************************************
// ��������:  �������ȡ�Ĵ����л�ȡpin�ŵ�ƽֵ
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� 0xFFFFFFFF:������������ֵΪ��ȡ����ֵ
//**********************************************************************
extern uint32 SMDrv_GPIO_InBitRead(uint32 u32PinNum);

//**********************************************************************
// ��������:  ����������Ĵ����л�ȡpin�ŵ�ƽֵ
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� 0xFFFFFFFF:������������ֵΪ��ȡ����ֵ
//**********************************************************************
extern uint32 SMDrv_GPIO_OutBitRead(uint32 u32PinNum);

extern const am_hal_gpio_pincfg_t SM_AM_HAL_GPIO_DISABLE;
extern const am_hal_gpio_pincfg_t SM_AM_HAL_GPIO_OUTPUT;
extern const am_hal_gpio_pincfg_t SM_AM_HAL_GPIO_TRISTATE;
extern const am_hal_gpio_pincfg_t SM_AM_HAL_GPIO_INPUT;

#endif
