#ifndef RTOS_H
#define RTOS_H

/* FreeRTOS includes */
#include "os.h"

/* Mid_Ble */
#define TASK_PRIORITY_MID_BLE		TASK_PRIORITY_REALTIME
#define TASK_STACKDEPTH_MID_BLE		(1024)					// 单位Word，即4Byte

/* Mid_Schd */
#define TASK_PRIORITY_MID_SCHD		TASK_PRIORITY_HIGH	
#define TASK_STACKDEPTH_MID_SCHD	(1024)					// 单位Word，即4Byte

/* Mod_Algo */
#define TASK_PRIORITY_MOD_ALGO		TASK_PRIORITY_MIDDLE
#define TASK_STACKDEPTH_MOD_ALGO	(1024)					// 单位Word，即4Byte

/* Mod_Time */
#define TASK_PRIORITY_MOD_TIME		TASK_PRIORITY_MIDDLE
#define TASK_STACKDEPTH_MOD_TIME	(1024)					// 单位Word，即4Byte

/* App_Schd */
#define TASK_PRIORITY_APP_SCHD		TASK_PRIORITY_MIDDLE_LOW
#define TASK_STACKDEPTH_APP_SCHD	(1024)					// 单位Word，即4Byte

/* Mod_Flash */
#define TASK_PRIORITY_MOD_FLASH		TASK_PRIORITY_LOW
#define TASK_STACKDEPTH_MOD_FLASH	(1024)					// 单位Word，即4Byte

/* App_Lcd */
#define TASK_PRIORITY_APP_LCD		TASK_PRIORITY_LOW
#define TASK_STACKDEPTH_APP_LCD		(1024)					// 单位Word，即4Byte

#define	APP_1SEC_TICK				configTICK_RATE_HZ

#endif // RTOS_H

