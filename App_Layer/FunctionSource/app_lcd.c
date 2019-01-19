
#include "app_lcd.h"
#include "sm_timer.h"
#include "ui_timerhandle_main.h"

//#include "rtos.h"
//#include "ui_display_main.h"


static QueueHandle_t 	sLcd_QueueHandle;				// 队列句柄
#define		LCD_TASK_QUEUE_LENGTH			3			// 
#define 	LCD_TASK_QUEUE_WAIT_TICK		100			// 队列阻塞时间
#define		LCD_TASK_QUEUE_SIZE				sizeof(App_Lcd_TaskMsg_T)

static TimerHandle_t 	sLcd_TimerHandle;


App_Lcd_Param_t	App_Lcd;

// LCD定时器
static void sLcd_TimerCallBack(TimerHandle_t xTimer)
{
	App_Lcd_TaskMsg_T LcdMsg;
	
	LcdMsg.Id = eAppLcdEventInside;
	App_Lcd_TaskEventSet(&LcdMsg, 1);
	
//	APP_LCD_RTT_LOG(0,"sLcd_TimerCallBack \r\n");
}


// 硬件定时器
void LCD_TimerCb(void)
{
//	SMDrv_CTimer_Stop(MOVT_CTIMER_MODULE);
	
	App_Lcd_TaskMsg_T LcdMsg;
	
	LcdMsg.Id = eAppLcdEventInside;
	App_Lcd_TaskEventSet(&LcdMsg, 1);
//	APP_LCD_RTT_LOG(0,"LCD_TimerCb \r\n");
}

// LCD屏幕刷新
void App_Lcd_ScreenRefresh(uint8_t ScreenMainId)
{
	Enum_Common_Screen_MAINID  tmp_screen_id;
	
	tmp_screen_id = UI_Get_Curr_ScreenID();
	
	if(ScreenMainId == tmp_screen_id)
	{
		UI_Show_Screen();
		Mid_Lcd_Show();		
	}
}

void App_Lcd_TimerStart(uint32_t TimerMs)
{
    // 更新定时器参数并启动
    //	xTimerStart(sLcd_TimerHandle,0);
	xTimerChangePeriod(sLcd_TimerHandle, pdMS_TO_TICKS(TimerMs), 3);
//	APP_LCD_RTT_LOG(0,"App_Lcd_TimerStart %d \n", TimerMs);
}

void App_Lcd_TimerStop(void)
{
	xTimerStop(sLcd_TimerHandle,3);
//	APP_LCD_RTT_LOG(0,"App_Lcd_TimerStop \n");
}


void App_Lcd_HardTimerStart(uint32_t TimerMs)
{
	SMDrv_CTimer_Stop(MOVT_CTIMER_MODULE);
	SMDrv_CTimer_Open(MOVT_CTIMER_MODULE, TimerMs, LCD_TimerCb);
	SMDrv_CTimer_Start(MOVT_CTIMER_MODULE);
}

void App_Lcd_HardTimerStop(void)
{
	SMDrv_CTimer_Stop(MOVT_CTIMER_MODULE);
}


void App_Lcd_Test(void)
{
	static uint16 TimerMs = 0;
	static bool Flg = false;
	
	TimerMs += 200;

	if(Flg)
	{
		Flg = false;
		SMDrv_CTimer_Stop(MOVT_CTIMER_MODULE);
	}
	else
	{
		Flg = true;
		SMDrv_CTimer_Stop(MOVT_CTIMER_MODULE);
		SMDrv_CTimer_Open(MOVT_CTIMER_MODULE, TimerMs, LCD_TimerCb);
		SMDrv_CTimer_Start(MOVT_CTIMER_MODULE);		
	}
}

static void App_Lcd_TaskProcess(void *pvParameters)
{
	App_Lcd_TaskMsg_T	Msg;

	// 创建消息队列
	sLcd_QueueHandle = xQueueCreate(LCD_TASK_QUEUE_LENGTH, LCD_TASK_QUEUE_SIZE);
	if(sLcd_QueueHandle == NULL)
	{
		APP_LCD_RTT_ERR(0,"Lcd_Queue Create Err \r\n");
	}
	
	// 创建定时器
    sLcd_TimerHandle=xTimerCreate((const char*		)"sLcd_Timer",
									    (TickType_t			)(200/portTICK_PERIOD_MS),
							            (UBaseType_t		)pdFALSE,	// pdFALSE ，单次，pdTRUE 周期
							            (void*				)1,
							            (TimerCallbackFunction_t)sLcd_TimerCallBack); 

    UI_Common_timer_Init();
    UI_Common_Init();
	
	while(1)
	{
		if(xQueueReceive(sLcd_QueueHandle, &Msg, portMAX_DELAY))
		{
			switch (Msg.Id)
            {
            	case eAppLcdEventOuter:		   // 外部事件，如key、触摸等
					UI_Show_Screen();
                    Mid_Lcd_Show();
            		break;
            	case eAppLcdEventInside:	   // 内事件，如LCD定时器等
                    UI_Common_do_timer_handle();
                    Mid_Lcd_Show();
            		break;
            	case eAppLcdEventCmd:	       //单次刷屏，计时器用
                    Mid_Lcd_Show();
            		break;
            	default:
					drERROR_CHECK("App_Lcd_TaskProcess", Ret_InvalidParam);
            		break;
            }
		}
	}
}

void App_Lcd_TaskEventSet(App_Lcd_TaskMsg_T* Msg, uint8_t FromISR)
{

	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	
	if(xPortIsInsideInterrupt() == pdTRUE)    // 判断是否在中断
	{
		if(pdPASS != xQueueSendToBackFromISR(sLcd_QueueHandle, Msg, &xHigherPriorityTaskWoken))
		{
			APP_LCD_RTT_ERR(0,"[ERR] App_Lcd_TaskEventSet \n");
		}
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	else
	{
		if(pdPASS != xQueueSendToBack(sLcd_QueueHandle, Msg, LCD_TASK_QUEUE_WAIT_TICK))
		{
			APP_LCD_RTT_ERR(0,"[ERR] App_Lcd_TaskEventSet \n");
		}
	}
    
}


void App_Lcd_TaskCreate(void)
{
    if(pdPASS != xTaskCreate(App_Lcd_TaskProcess, "LcdTask", TASK_STACKDEPTH_APP_LCD, NULL, TASK_PRIORITY_APP_LCD, NULL))
	{
		APP_LCD_RTT_ERR(0,"App_Lcd_TaskCreate Err \r\n");
	}
}










