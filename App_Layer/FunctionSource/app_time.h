#ifndef	__APP_TIME_H
#define __APP_TIME_H

#include "platform_common.h"
#include "mid_rtc.h"

#define APP_TIME_RTT_DEBUG	3
#if (1 == APP_TIME_RTT_DEBUG)	// 错误等级
#define APP_TIME_RTT_LOG(...)
#define APP_TIME_RTT_WARN(...)
#define APP_TIME_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == APP_TIME_RTT_DEBUG)	// 警告等级
#define APP_TIME_RTT_LOG(...)
#define APP_TIME_RTT_WARN		RTT_DEBUG_WARN
#define APP_TIME_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == APP_TIME_RTT_DEBUG)	// 调试等级
#define APP_TIME_RTT_LOG		RTT_DEBUG_LOG
#define APP_TIME_RTT_WARN		RTT_DEBUG_WARN
#define APP_TIME_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define APP_TIME_RTT_LOG(...)
#define APP_TIME_RTT_WARN(...)
#define APP_TIME_RTT_ERR(...)
#endif

typedef struct
{
	uint8_t Flg;
}AppTimeParam_t;


typedef struct
{
	eMidRTCMsg	Msg;
}AppTimeRTCParam_t;

/* 中间层任务调度消息类型 */
typedef enum
{
	eTimeTaskMsgRTC,
	eTimeTaskMsgMax,
}AppTimeTaskMsgId_e;

/* 中间层任务调度数据结构体 */
typedef struct
{
	AppTimeTaskMsgId_e Id;
	union
	{
		AppTimeRTCParam_t	RTC;
	}Param;
}AppTimeTaskMsg_t;

uint16_t App_Time_NotDisturdTimeCheck(void);
void App_Time_TaskEventSet(AppTimeTaskMsg_t* Msg);
void App_Time_TaskCreate(void);


extern void UI_Commom_Lockinfo_Timehandle(void);


#endif



