#ifndef __SM_UART_H
#define __SM_UART_H

#include "platform_common.h"

//����ʹ��UART��ģ������
typedef enum
{
    BASE_UART_MODULE,   //����ͨѶ�ã�����ԣ���о�о�
    GPS_UART_MODULE,    //GPS
    BLE_UART_MODULE,    //ʹ��UARTͨѶ��BLE����
}uart_module;

//����driver��ͨ�õ�uart�ж�����
#define UART_EVENT_NONE       0X00        //���ж�
#define UART_EVENT_TX         0x01        //�����ж�
#define UART_EVENT_RX         0x02        //�����ж�
#define UART_EVENT_RX_TIMEOUT 0x04        //���ճ�ʱ�ж�

typedef void (*uart_cb)(uint32 uart_event);

//**********************************************************************
// ��������: ��ʼ��UART
// ���������	
// ���ز�����
//**********************************************************************
extern void SMDrv_UART_Init(void);

//**********************************************************************
// ��������: ����driver module ID��Ӳ����Ӧ��UART
// ���������	
//    modul: driver module ID,ֵ�ο�uart_module
//    ptype_info:Ҫ���õ�uart�ж����ͣ�FIFO����, �������жϣ�������ΪNULL
//    ut_callback:�ϲ�ע����жϻص�����
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_UART_Open(uart_module modul,uart_cb ut_callback);

//**********************************************************************
// ��������: �ر�driver module IDӲ����Ӧ��UART,��ʵ�ֵ͹���
// ���������	
//    modul: driver module ID,ֵ�ο�uart_module
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_UART_Close(uart_module modul);

//**********************************************************************
// ��������:  ����GPIO�ж����ȼ�,������uart�ж�
// �������:
//     modul: driver module ID,ֵ�ο�uart_module
//     prio:�ж����ȼ���bit0~2λֵ��Ч
// ���ز����� ��
//**********************************************************************
extern ret_type SMDrv_UART_SetIsrPrio(uart_module modul,uint32 prio);

//**********************************************************************
// ��������: ʹ��/ʧ��UARTĳ�����͵��ж�
// �������:
//     modul: driver module ID,ֵ�ο�uart_module
//     irq_type:�ж�����
//     benable: ʹ��/ʧ��UARTĳ�����ж�  =1--ʹ�ܣ� =0--ʧ��
// ���ز����� ��
//**********************************************************************
extern ret_type SMDrv_UART_EnableIrq(uart_module modul,uint32 irq_type,uint8 benable);

//**********************************************************************
// ��������: ��driver module ID��Ӧ��UARTд��n���ֽ�
// ���������	
//    modul: driver module ID
//    pData: Ҫ����������
//    len: Ҫ���������ݵĳ���
// ���ز�����
//    pu16LenWritten: ʵ�ʷ��͵ĳ���
//**********************************************************************
extern ret_type SMDrv_UART_WriteBytes(uart_module modul,uint8 *pData,uint16 len,uint16 *pu16LenWritten);

//**********************************************************************
// ��������: ��driver module ID��Ӧ��UARTдn���ֽ�
// ���������	
//    modul: driver module ID
//    pBuffer: Ҫ��ȡ�����ݻ���buffer
//    len: Ҫ��ȡ�����ݵĳ���
// ���ز�����
//    pu16LenWritten: ʵ�ʶ�ȡ�����ݳ���
//**********************************************************************
extern ret_type SMDrv_UART_ReadBytes(uart_module modul,uint8 *pBuffer,uint16 len,uint16 *pu16ReadLen);

//**********************************************************************
// ��������: ��ȡmoduleʹ��UART���ͻ�������С
// ���������	
//    modul: driver module ID
// ���ز��������ͻ�������С
//**********************************************************************
extern uint32 SMDrv_UART_GetTxBuffSize(uart_module modul);

//**********************************************************************
// ��������: ��ȡmoduleʹ��UART���ջ�������С
// ���������	
//    modul: driver module ID
// ���ز��������ջ�������С
//**********************************************************************
extern uint32 SMDrv_UART_GetRxBuffSize(uart_module modul);

#endif

