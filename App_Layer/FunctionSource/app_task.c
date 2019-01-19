#include "app_task.h"
#include "app_systerm.h"

#include "mid_interface.h"
#include "scene_interface.h"
#include "store_interface.h"
#include "app_remind_manage.h"

#include "scene_task.h"

#include "app_time.h"

#include "app_lcd.h"

static QueueHandle_t 	AppSchd_QueueHandle;				// 队列句柄
#define		APP_SCHD_TASK_QUEUE_LENGTH			5			// 
#define 	APP_SCHD_TASK_QUEUE_WAIT_TICK		100			// 队列阻塞时间
#define		APP_SCHD_TASK_QUEUE_SIZE			sizeof(App_Schd_TaskMsg_T)

uint32_t gGPSTestBuf[22];
void App_TestDataGet(uint32_t* DataBuf)
{
//	static uint32_t lCnt = 0;
//	
//	lCnt++;
//	
//	/* 最多显示22个数据 */
//	for(uint32_t i = 0;i < 22;i++)
//	{
//		DataBuf[i] = i*1000 + lCnt;
//	}
	
	for(uint32_t i = 0;i < 22;i++)
	{
		DataBuf[i] = gGPSTestBuf[i];
	}
}

static void App_Schd_TaskProcess(void *pvParameters)
{
	App_Schd_TaskMsg_T	Msg;
	
	AppSchd_QueueHandle = xQueueCreate(APP_SCHD_TASK_QUEUE_LENGTH, APP_SCHD_TASK_QUEUE_SIZE);
	if(AppSchd_QueueHandle == NULL)
	{
		APP_SCHD_RTT_ERR(0,"Schd Queue Create Err \r\n");
	}
	
	App_Sys_Init();				// 系统初始化

	while(1)
	{
		if(xQueueReceive(AppSchd_QueueHandle, &Msg, portMAX_DELAY))
		{
			switch(Msg.Id)
			{
				case eAppSchdMsgLcd:
//					APP_SCHD_RTT_ERR(0,"eAppSchdMsgLcd %d \n", Msg.Param.Lcd.ScreenId);
					App_Lcd_ScreenRefresh(Msg.Param.Lcd.ScreenId);
					break;
				default:
					drERROR_CHECK("App_Schd_TaskProcess", Ret_InvalidParam);
					break;
			}
		}
	}
}

//**********************************************************************
// 函数功能:	
// 输入参数：
// 返回参数：
void App_Schd_TaskEventSet(App_Schd_TaskMsg_T* Msg, uint8_t FromISR)
{
	 portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	
	/* 若中断函数中调用，需判断是否需要进行任务调度 */
	if(xPortIsInsideInterrupt() == pdTRUE)    // ???????
	{
		if(pdPASS != xQueueSendToBackFromISR(AppSchd_QueueHandle, Msg, &xHigherPriorityTaskWoken))
		{
			APP_SCHD_RTT_ERR(0,"App_Schd_TaskEventSet Err \r\n");
		}
		
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	else
	{
		if(pdPASS != xQueueSendToBack(AppSchd_QueueHandle, Msg, APP_SCHD_TASK_QUEUE_WAIT_TICK))
		{
			APP_SCHD_RTT_ERR(0,"App_Schd_TaskEventSet Err \r\n");
		}		
	}	
}

void App_Schd_TaskCreate(void)
{
    xTaskCreate(App_Schd_TaskProcess, "AppSchdTask", TASK_STACKDEPTH_APP_SCHD, NULL, TASK_PRIORITY_APP_SCHD, NULL);
}												

