#ifndef	__STORE_TASK_H
#define __STORE_TASK_H

#include "store_variable.h"
#include "store_common.h"

#define STORE_TASK_RTT_DEBUG	3
#if (1 == STORE_TASK_RTT_DEBUG)	// ����ȼ�
#define STORE_TASK_RTT_LOG(...)
#define STORE_TASK_RTT_WARN(...)
#define STORE_TASK_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_TASK_RTT_DEBUG)	// ����ȼ�
#define STORE_TASK_RTT_LOG(...)
#define STORE_TASK_RTT_WARN		RTT_DEBUG_WARN
#define STORE_TASK_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_TASK_RTT_DEBUG)	// ���Եȼ�
#define STORE_TASK_RTT_LOG		RTT_DEBUG_LOG
#define STORE_TASK_RTT_WARN		RTT_DEBUG_WARN
#define STORE_TASK_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define STORE_TASK_RTT_LOG(...)
#define STORE_TASK_RTT_WARN(...)
#define STORE_TASK_RTT_ERR(...)
#endif

typedef enum
{
	eStoreTaskMsgCmn,	// �洢��flash�����ݸ���
	eStoreTaskMsgPDU,
	eStoreTaskMsgMax,
}StoreTaskMsgId_e;

typedef struct
{
	StoreTaskMsgId_e Id;
	union
	{
		StoreCmnEvent_t		StoreCmn;
	}Param;		
}Store_Task_Msg_T;

void Store_Task_EventSet(Store_Task_Msg_T* Msg);
void Store_Task_Create(void);
#endif



