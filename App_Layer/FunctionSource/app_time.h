#ifndef	__APP_TIME_H
#define __APP_TIME_H

#include "platform_common.h"
#include "mid_rtc.h"

#define APP_TIME_RTT_DEBUG	3
#if (1 == APP_TIME_RTT_DEBUG)	// ����ȼ�
#define APP_TIME_RTT_LOG(...)
#define APP_TIME_RTT_WARN(...)
#define APP_TIME_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == APP_TIME_RTT_DEBUG)	// ����ȼ�
#define APP_TIME_RTT_LOG(...)
#define APP_TIME_RTT_WARN		RTT_DEBUG_WARN
#define APP_TIME_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == APP_TIME_RTT_DEBUG)	// ���Եȼ�
#define APP_TIME_RTT_LOG		RTT_DEBUG_LOG
#define APP_TIME_RTT_WARN		RTT_DEBUG_WARN
#define APP_TIME_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
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

/* �м�����������Ϣ���� */
typedef enum
{
	eTimeTaskMsgRTC,
	eTimeTaskMsgMax,
}AppTimeTaskMsgId_e;

/* �м������������ݽṹ�� */
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



