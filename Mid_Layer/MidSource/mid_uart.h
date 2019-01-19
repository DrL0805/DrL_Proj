#ifndef         MID_UART_H
#define         MID_UART_H

#include "sm_uart.h"


extern void Mid_Uart_Init(void);
extern void Mid_Uart_Send(uart_module modul, uint8_t* u8Buffer, uint16_t u16ReadLen);

#endif			//UART_APP_H
