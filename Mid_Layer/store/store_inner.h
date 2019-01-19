#ifndef STORE_INNER_H
#define STORE_INNER_H


#include "store_variable.h"

// �������߰�����ظ�����������storeģ���õ����ⲿͷ�ļ������ڴ˴�����
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
#if (1 == STORE_INNER_RTT_DEBUG)	// ����ȼ�
#define STORE_INNER_RTT_LOG(...)
#define STORE_INNER_RTT_WARN(...)
#define STORE_INNER_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_INNER_RTT_DEBUG)	// ����ȼ�
#define STORE_INNER_RTT_LOG(...)
#define STORE_INNER_RTT_WARN	RTT_DEBUG_WARN
#define STORE_INNER_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_INNER_RTT_DEBUG)	// ���Եȼ�
#define STORE_INNER_RTT_LOG		RTT_DEBUG_LOG
#define STORE_INNER_RTT_WARN	RTT_DEBUG_WARN
#define STORE_INNER_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define STORE_INNER_RTT_LOG(...)
#define STORE_INNER_RTT_WARN(...)
#define STORE_INNER_RTT_ERR(...)
#endif

#endif



