#ifndef __SM_SYS_H
#define __SM_SYS_H

#include "platform_common.h"

//interrupt ����ͬam_hal_interrupt.h
#ifdef AM_PART_APOLLO3
typedef enum
{
	// Hardware interrupts
	INTERRUPT_RESET              = 1,
	INTERRUPT_NMI                = 2,
	INTERRUPT_HARDFAULT          = 3,
	INTERRUPT_MPUFAULT           = 4,
	INTERRUPT_BUSFAULT           = 5,
	INTERRUPT_USAGEFAULT         = 6,
	INTERRUPT_SVCALL             = 11,
	INTERRUPT_DEBUGMON           = 12,
	INTERRUPT_PENDSV             = 14,
	INTERRUPT_SYSTICK            = 15,
	
    // Begin IRQs
	INTERRUPT_BROWNOUT           = 16,
	INTERRUPT_WATCHDOG           = 17,
	INTERRUPT_RTC                = 18,
	INTERRUPT_VCOMP              = 19,
	INTERRUPT_IOSLAVE            = 20,
	INTERRUPT_IOSACC             = 21,
	INTERRUPT_IOMASTER0          = 22,
	INTERRUPT_IOMASTER1          = 23,
	INTERRUPT_IOMASTER2          = 24,
	INTERRUPT_IOMASTER3          = 25,
	INTERRUPT_IOMASTER4          = 26,
	INTERRUPT_IOMASTER5          = 27,
	INTERRUPT_BLE                = 28,
	INTERRUPT_GPIO               = 29,
	INTERRUPT_CTIMER             = 30,
	INTERRUPT_UART0              = 31,
	INTERRUPT_UART1              = 32,
	INTERRUPT_SCARD              = 33,
	INTERRUPT_ADC                = 34,
	INTERRUPT_PDM                = 35,
	INTERRUPT_MSPI               = 36,
	INTERRUPT_RESERVED0          = 37,
	INTERRUPT_STIMER             = 38,
	INTERRUPT_STIMER_CMPR0       = 39,
	INTERRUPT_STIMER_CMPR1       = 40,
	INTERRUPT_STIMER_CMPR2       = 41,
	INTERRUPT_STIMER_CMPR3       = 42,
	INTERRUPT_STIMER_CMPR4       = 43,
	INTERRUPT_STIMER_CMPR5       = 44,
	INTERRUPT_STIMER_CMPR6       = 45,
	INTERRUPT_STIMER_CMPR7       = 46,
	INTERRUPT_CLKGEN             = 47,
	INTERRUPT_SOFTWARE0          = 48,
	INTERRUPT_SOFTWARE1          = 49,
	INTERRUPT_SOFTWARE2          = 50,
	INTERRUPT_SOFTWARE3          = 51,
}interrupt_handle;
#else
typedef enum
{
	// Hardware interrupts
	INTERRUPT_RESET              = 1,
	INTERRUPT_NMI                = 2,
	INTERRUPT_HARDFAULT          = 3,
	INTERRUPT_MPUFAULT           = 4,
	INTERRUPT_BUSFAULT           = 5,
	INTERRUPT_USAGEFAULT         = 6,

	INTERRUPT_SVCALL             = 11,
	INTERRUPT_DEBUGMON           = 12,
	INTERRUPT_PENDSV             = 14,
	INTERRUPT_SYSTICK            = 15,

    // Begin IRQs
	INTERRUPT_BROWNOUT           = 16,
	INTERRUPT_WATCHDOG           = 17,
	INTERRUPT_CLKGEN             = 18,
	INTERRUPT_VCOMP              = 19,
	INTERRUPT_IOSLAVE            = 20,
	INTERRUPT_IOSACC             = 21,
	INTERRUPT_IOMASTER0          = 22,
	INTERRUPT_IOMASTER1          = 23,
	INTERRUPT_IOMASTER2          = 24,
	INTERRUPT_IOMASTER3          = 25,
	INTERRUPT_IOMASTER4          = 26,
	INTERRUPT_IOMASTER5          = 27,
	INTERRUPT_GPIO               = 28,
	INTERRUPT_CTIMER             = 29,
	INTERRUPT_UART0              = 30,
	INTERRUPT_UART1              = 31,
	//INTERRUPT_UART             =   (AM_HAL_INTERRUPT_UART0),
	INTERRUPT_ADC                = 32,
	INTERRUPT_PDM                = 33,
	INTERRUPT_STIMER             = 34,
	INTERRUPT_STIMER_CMPR0       = 35,
	INTERRUPT_STIMER_CMPR1       = 36,
	INTERRUPT_STIMER_CMPR2       = 37,
	INTERRUPT_STIMER_CMPR3       = 38,
	INTERRUPT_STIMER_CMPR4       = 39,
	INTERRUPT_STIMER_CMPR5       = 40,
	INTERRUPT_STIMER_CMPR6       = 41,
	INTERRUPT_STIMER_CMPR7       = 42,
	INTERRUPT_FLASH              = 43,

	INTERRUPT_TICK          	 = 44,//INTERRUPT_SOFTWARE0 as tick interrupt
	INTERRUPT_SOFTWARE1          = 45,
	INTERRUPT_SOFTWARE2          = 46,
	INTERRUPT_SOFTWARE3          = 47,
}interrupt_handle;
#endif

typedef enum
{
    MCU_EXTERNAL_RESET,
    MCU_POWERON_RESET,
    MCU_BROWNOUT_RESET,
    MCU_POR_RESET,
    MCU_POI_RESET,
    MCU_DEBUGGER_RESET,
    MCU_WDT_RESET,
    MCU_BOUNSUP_RESET,
    MCU_BOCORE_RESET,
    MCU_BOMEM_RESET,
    MCU_BOBLE_RESET,
    MCU_WDT_MAX  =0xFF,
}Rest_Type;

//**********************************************************************
// ��������: ��ʼ��ambiqϵͳʱ�ӣ���Ƶ48M�������ⲿ����������
//           ��ʹ�ܵ͹��ĵ�·
// ���������	��
// ���ز�����	
//**********************************************************************
extern void SMDrv_SYS_ClockInit(void);

#ifdef AM_PART_APOLLO3
//**********************************************************************
// ��������: ʹ��/��ֹMCU burst mode��
// ���������bEnableBurst=TRUE:ʹ��burst mode����Ƶ���ܵ�96MHz
//           =FALSE:��ֹburst mode����Ƶ48MHz
// ���ز���:
// ʹ��˵��:Ϊ�˽��͹��ģ��ڴ������㣬cpu copy����ʱ����Ϊburst mode��
//          ��ͨ������½�ֹburst mode
// ע:��ģʽApollo/Apollo2��֧�֣�Apollo3֧��
//**********************************************************************
extern void SMDrv_SYS_EnableBurstMode(uint8 bEnableBurst);
#endif

//**********************************************************************
// ��������: ��ȡChip ID
// ���������
// ���ز�����Chip ID	
//**********************************************************************
extern uint32 SMDrv_SYS_GetChipID(void);

//**********************************************************************
// ��������: ʹ��NVIC�ж�
// �����������
// ���ز�����	
//**********************************************************************
extern void SMDrv_SYS_EnableIsr(interrupt_handle ui32Interrupt);

//**********************************************************************
// ��������: ��ֹNVIC�ж�
// �����������
// ���ز�����	
//**********************************************************************
extern void SMDrv_SYS_DisableIsr(interrupt_handle ui32Interrupt);

//**********************************************************************
// ��������: Set a pending interrupt bit in the NVIC
// �����������
// ���ز�����	
//**********************************************************************
extern void SMDrv_SYS_SetIsrPend(interrupt_handle ui32Interrupt);

//**********************************************************************
// ��������: Clear a pending interrupt bit in the NVIC without servicing it
// �����������
// ���ز�����	
//**********************************************************************
extern void SMDrv_SYS_ClearIsrPend(interrupt_handle ui32Interrupt);

//**********************************************************************
// ��������: �����ж����ȼ�
// �����������
// ���ز�����	
//**********************************************************************
extern void SMDrv_SYS_SetIsrPrio(interrupt_handle ui32Interrupt,uint32 u32isrprio);

//**********************************************************************
// ��������: ʹ���ж�����
// �����������
// ���ز�����	
//**********************************************************************
extern void SMDrv_SYS_EnableMasterIsr(void);

//**********************************************************************
// ��������: ��ֹ�ж�����
// �����������
// ���ز�����	
//**********************************************************************
extern void SMDrv_SYS_DisableMasterIsr(void);

//**********************************************************************
// ��������: POR Reset
// �����������
// ���ز�����	
//**********************************************************************
extern void SMDrv_SYS_PowerOnReset(void);

//**********************************************************************
// ��������: POI reset
// ���������
// ���ز�����	
//**********************************************************************
extern void SMDrv_SYS_Rest_POI(void);

//**********************************************************************
// ��������:	ϵͳ���ߴ���������������
// ���������	��
// ���ز�����	
//**********************************************************************
extern void SMDrv_SYS_Sleep(void);

//**********************************************************************
// ��������: ��ʱn ms
// ���������u32nms:��ʱms��
// ���ز�����	
//**********************************************************************
extern void SMDrv_SYS_DelayMs(uint32 u32nms);

//**********************************************************************
// ��������: ��ʱn us
// ���������u32nus:��ʱus��
// ���ز�����	
//**********************************************************************
extern void SMDrv_SYS_DelayUs(uint32 u32nus);

//**********************************************************************
// ��������: д�Ĵ���
// ���������u32reg:�Ĵ�����ַ��u32value:Ҫд��ֵ
// ���ز�����	
//**********************************************************************
extern void SMDrv_SYS_WriteReg(uint32 u32reg, uint32 u32value);

//**********************************************************************
// ��������: ��ȡMCU Rest type������λԭ��
// ���������
// ���ز�����	
//**********************************************************************
extern Rest_Type SMDrv_SYS_GetRestType(void);

//**********************************************************************
// ��������:	����ϵͳ����ʱ�ӣ�systick��,32HZ, 31.25ms/tick
//**********************************************************************
extern void SMDrv_SYSTick_ClockInit(void);

#endif

