#ifndef SCENE_VARIABLE_H
#define SCENE_VARIABLE_H

#include "platform_common.h"


#define SCENE_RTT_DEBUG	3
#if (1 == SCENE_RTT_DEBUG)	// 错误等级
#define SCENE_RTT_LOG(...)
#define SCENE_RTT_WARN(...)
#define SCENE_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_RTT_DEBUG)	// 警告等级
#define SCENE_RTT_LOG(...)
#define SCENE_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_RTT_DEBUG)	// 调试等级
#define SCENE_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define SCENE_RTT_LOG(...)
#define SCENE_RTT_WARN(...)
#define SCENE_RTT_ERR(...)
#endif

#define SCENE_STORE_TIMEOUT	(28800)	// 场景数据存储超时时间，8小时
#define SCENE_WARN_CHECK_INTERVAL	(60)	// 场景警告检测间隔，如心率超标

/* 场景测量方式 */
typedef enum
{
	eSceneMeasureIM,	// instant messaging 即时测量
	eSceneMeasureBG,	// background  后台测量
	eSceneMeasureKeep,	// 保持，持续测量
}eSceneMeasureWay;

#endif



