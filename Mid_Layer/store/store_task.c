
#include "store_task.h"
#include "store_upload.h"
#include "store_common.h"
#include "store_pdu.h"

static QueueHandle_t 	STORE_Task_QueueHandle;				// 队列句柄
#define		STORE_TASK_QUEUE_LENGTH			3			// 
#define 	STORE_TASK_QUEUE_WAIT_TICK		100			// 队列阻塞时间
#define		STORE_TASK_QUEUE_SIZE			sizeof(Store_Task_Msg_T)


// ***********************************************************************
//	以下是任务调度代码
// ***********************************************************************
static void Store_Task_Process(void *pvParameters)
{
	Store_Task_Msg_T	Msg;

	// 创建消息队列
	STORE_Task_QueueHandle = xQueueCreate(STORE_TASK_QUEUE_LENGTH, STORE_TASK_QUEUE_SIZE);
	if(STORE_Task_QueueHandle == NULL)
	{
		STORE_TASK_RTT_ERR(0,"PDU_Queue Create Err \r\n");
	}
	
	while(1)
	{
		if(xQueueReceive(STORE_Task_QueueHandle, &Msg, portMAX_DELAY))
		{
			/* 
				StoreTask原则：
				读Flash即时读，写Flash放入Task慢慢写
			*/
			switch (Msg.Id)
            {
            	case eStoreTaskMsgCmn:
					Store_Cmn_EventProcess(&Msg.Param.StoreCmn);
					break;
				case eStoreTaskMsgPDU:
					Store_PDU_TimerHandler();
					break;
            	default :
					drERROR_CHECK("Store_Task_Process", Ret_InvalidParam);
            		break;
            }
		}
	}
}

void Store_Task_EventSet(Store_Task_Msg_T* Msg)
{
	 portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	
	if(xPortIsInsideInterrupt() == pdTRUE)    // 判断是否在中断
	{
		if(pdPASS != xQueueSendToBackFromISR(STORE_Task_QueueHandle, Msg, &xHigherPriorityTaskWoken))
		{
			STORE_TASK_RTT_ERR(0,"Mod_PDU_TaskEventSet Err \r\n");
		}
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	else
	{
		if(pdPASS != xQueueSendToBack(STORE_Task_QueueHandle, Msg, STORE_TASK_QUEUE_WAIT_TICK))
		{
			STORE_TASK_RTT_ERR(0,"Mod_PDU_TaskEventSet Err \r\n");
		}
	}
}

void Store_Task_Create(void)
{
    if(pdPASS != xTaskCreate(Store_Task_Process, "PDUTask", TASK_STACKDEPTH_MOD_FLASH, NULL, TASK_PRIORITY_MOD_FLASH, NULL))
	{
		STORE_TASK_RTT_ERR(0,"Mod_PDU_TaskCreate Err \r\n");
	}
}










