#ifndef STORE_INNER_H
#define STORE_INNER_H


#include "store_variable.h"

// 避免乱七八糟的重复包含，所有store模块用到的外部头文件，都在此处包含
#include "app_variable.h"
#include "mid_nandflash.h"
//#include "scene_run.h"
//#include "scene_stress.h"
#include "scene_interface.h"
#include "mid_rtc.h"
#include "mid_alarm.h"
#include "ble_task.h"
#include "bsp_common.h"

#define STORE_INNER_RTT_DEBUG	3
#if (1 == STORE_INNER_RTT_DEBUG)	// 错误等级
#define STORE_INNER_RTT_LOG(...)
#define STORE_INNER_RTT_WARN(...)
#define STORE_INNER_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_INNER_RTT_DEBUG)	// 警告等级
#define STORE_INNER_RTT_LOG(...)
#define STORE_INNER_RTT_WARN	RTT_DEBUG_WARN
#define STORE_INNER_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_INNER_RTT_DEBUG)	// 调试等级
#define STORE_INNER_RTT_LOG		RTT_DEBUG_LOG
#define STORE_INNER_RTT_WARN	RTT_DEBUG_WARN
#define STORE_INNER_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_INNER_RTT_LOG(...)
#define STORE_INNER_RTT_WARN(...)
#define STORE_INNER_RTT_ERR(...)
#endif

#endif



