#include "mid_uart.h"
#include "mid_interface.h"


static void uart_callback(uint32 uart_event)
{
	Mid_Schd_TaskMsg_T Msg;
	
	MID_SCHD_RTT_LOG(0,"uart_callback %d \n", uart_event);
	
    if((uart_event == UART_EVENT_RX_TIMEOUT) || (uart_event == UART_EVENT_RX))
	{
		Msg.Id = eSchdTaskMsgUart;
		Msg.Param.Uart.Module = BASE_UART_MODULE;
		Msg.Param.Uart.EventType = UART_EVENT_RX_TIMEOUT;
        Mid_Schd_TaskEventSet(&Msg);
	}
	
    if(uart_event == UART_EVENT_RX)
	{
//		Msg.Id = eSchdTaskMsgUart;
//		Msg.Param.Uart.Module = GPS_UART_MODULE;
//		Msg.Param.Uart.EventType = UART_EVENT_RX;
//        Mid_Schd_TaskEventSet(&Msg);		
	}
}

void Mid_Uart_Init(void)
{
	SMDrv_UART_Init();
	
	SMDrv_UART_Open(BASE_UART_MODULE,uart_callback);
	SMDrv_UART_SetIsrPrio(BASE_UART_MODULE, 3);
	SMDrv_UART_EnableIrq(BASE_UART_MODULE, UART_EVENT_RX|UART_EVENT_RX_TIMEOUT,TRUE);	
}

void Mid_Uart_Send(uart_module modul, uint8_t* u8Buffer, uint16_t u16ReadLen)
{
	uint16_t 	u16LenWritten;
	
	SMDrv_UART_WriteBytes(modul,u8Buffer,u16ReadLen,&u16LenWritten);
}

