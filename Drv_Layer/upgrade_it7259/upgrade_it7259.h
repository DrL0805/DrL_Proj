//#include "stm32f10x.h"
#include "platform_common.h"

#define MAX_BUFFER_SIZE						256

#define QUERY_COMMAND_READY					0x00
#define QUERY_COMMAND_BUSY					0x01
#define QUERY_COMMAND_ERROR					0X02

#define COMMAND_RESPONSE_SUCCESS			0x0000
#define SIGNATURE_LENGTH						16

#define FLASH_HIGH_ADDR						0xD0
#define FLASH_LOW_ADDR						0x00

#define KAL_FALSE							0
#define KAL_TRUE							1
#define NULL								0

#define max_error_count 10

#define CTP_SLAVE_ADDR		(0x8C)

#define COMMAND_BUFFER_INDEX          0x20	// 命令
#define QUERY_BUFFER_INDEX            0x80	// 获取状态
#define COMMAND_RESPONSE_BUFFER_INDEX 0xA0	// 命令响应
#define SYSTEM_COMMAND_RESPONSE_INDEX 0xC0	// 保留
#define POINT_BUFFER_INDEX            0xE0	// 触摸点坐标信息
#define COMMAND_SUCCESS        0x0000
#define COMMAND_ERROR         0x0200
#define ERROR_QUERY_TIME_OUT    0x0800

extern int Upgrade_FW_CFG(void);	// 升级固件
extern int Clear_FW_CFG(void);		// 清除固件
extern int Reset_IT7259(void);		// 软件复位TP


