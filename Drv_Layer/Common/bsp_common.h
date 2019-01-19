#ifndef     BSP_COMMON_H
#define     BSP_COMMON_H

#include "platform_common.h"


//多传感器芯片管理
typedef struct
{
    uint8     accelstate;
    uint8     gyrostate;
    uint8     magstate;    
}MultiSensor_s;

typedef enum 
{
   uinit            = 0x00,
   sleep            = 0x01,
   poweron          = 0x02,
   powerdown        = 0x03,  
}MultiSensorState_s;


//共享总线管理
typedef struct  
{
    uint8     ExtFlash;
    uint8     NandFlash;
    uint8     WordStack;
}ShareBusSpi_s;

typedef struct  
{
    uint8     Accels;
    uint8     Gyros;
    uint8     Mags;
    uint8     Pressure;
    uint8     Hrm;
}ShareBusI2c_s;

typedef enum 
{
   BusUninit          = 0x00,
   BusActive          = 0x01,
   BusIlde            = 0x02,  
}ShareBusState_s;


//管理九轴初始化状态
extern MultiSensor_s multisensor;

//共享总线管理
extern ShareBusSpi_s sharebusspi;    
extern ShareBusI2c_s sharebusi2c;  


//#ifndef		UART_HANDLE_T
//#define		UART_HANDLE_T
//// uart isr handle
//typedef	enum
//{
//	UART0_IDLE = 0,
//	UART0_GPS_OCCUPY,
//	UART0_WITHOUT_FLOW_CONTROL,
//	UART1_IDLE,
//	UART1_BLE_DOWNLOAD,
//	UART1_BLE_OCCUPY,
//	UART1_WITHOUT_FLOW_CONTROL
//}uart_occupy_t;

//#endif

extern bool drCMN_ArrayCmp(uint8_t *str1, uint8_t *str2, uint8_t len);
extern uint32_t drCMN_CyclePosNext(uint32_t fPosNum, uint32_t fCurrPos, int32_t fShift);

#endif


