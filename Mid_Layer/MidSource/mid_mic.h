#ifndef MID_MIC_H
#define MID_MIC_H

#include "platform_common.h"

// 事件定义
typedef enum
{
	MIC_SAMPLE  	= 0,
	MIC_CLOSE,
}MIC_INTERFACE_E;

// 事件定义
typedef struct 
{
	uint16			id;							// 事件ID
}mic_event_s;

uint8 Mid_Mic_Init(void);
void Mid_Mic_Samle(void);
void Mid_Mic_Close(void);
void Mid_Mic_DataRead(uint32 *micBuf, uint32 readLen);
uint16 Mid_Mic_EventProcess(mic_event_s* msg);

#endif

