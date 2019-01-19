#ifndef     APP_TASK_H
#define     APP_TASK_H

#include "platform_common.h"

#define APP_SCHD_RTT_DEBUG	3
#if (1 == APP_SCHD_RTT_DEBUG)	// 错误等级
#define APP_SCHD_RTT_LOG(...)
#define APP_SCHD_RTT_WARN(...)
#define APP_SCHD_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == APP_SCHD_RTT_DEBUG)	// 警告等级
#define APP_SCHD_RTT_LOG(...)
#define APP_SCHD_RTT_WARN		RTT_DEBUG_WARN
#define APP_SCHD_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == APP_SCHD_RTT_DEBUG)	// 调试等级
#define APP_SCHD_RTT_LOG		RTT_DEBUG_LOG
#define APP_SCHD_RTT_WARN		RTT_DEBUG_WARN
#define APP_SCHD_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define APP_SCHD_RTT_LOG(...)
#define APP_SCHD_RTT_WARN(...)
#define APP_SCHD_RTT_ERR(...)
#endif

typedef struct
{
	uint8_t ScreenId;
}App_Schd_LcdParam_T;

typedef enum
{
	eAppSchdMsgLcd,
	eAppSchdMsgMax,
}eAppSchdMsgId;

typedef struct 
{
	eAppSchdMsgId Id;
	union
	{
		App_Schd_LcdParam_T		Lcd;
	}Param;
}App_Schd_TaskMsg_T;

extern void App_TestDataGet(uint32_t* DataBuf);
extern void App_Schd_TaskEventSet(App_Schd_TaskMsg_T* Msg, uint8_t FromISR);
extern void App_Schd_TaskCreate(void);

extern uint32_t gGPSTestBuf[22];

#endif      //APP_APP_H

