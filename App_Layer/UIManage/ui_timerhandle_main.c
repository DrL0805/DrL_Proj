#include "ui_timerhandle_main.h"
#include "sm_timer.h"



//void (*ui_timerhandle_callback)() = NULL;
func_timerhandle_callback ui_timerhandle_callback = NULL;


void UI_Common_set_timer_handle(func_timerhandle_callback timerhandle)
{

    ui_timerhandle_callback=timerhandle;
}

void UI_Common_do_timer_handle(void)
{

    if(ui_timerhandle_callback!=NULL)
         ui_timerhandle_callback();

}



TimerHandle_t  UI_TimerHandle[UI_Common_Timer_Max] = {0};
func_timerhandle_callback LCD_Timer_Callback[UI_Common_Timer_Max];


void UI_Common_timer_Callback(TimerHandle_t xTimer)
{
    int i = 0;
    
    RTT_DEBUG_printf(0,"UI_Common_timer_Callback %d",xTimer);
    for(i= 0;i<UI_Common_Timer_Max;i++)
    {

        if(UI_TimerHandle[i] == xTimer)
        {
            LCD_Timer_Callback[i]();
            break;
        }    
    }

}


void UI_Common_timer_Init(void)
{


    int i=0;
    char temp_timer[16]={0};
    

    for(i = 0;i<UI_Common_Timer_Max;i++)
    {
        sprintf(temp_timer,"UI_Timer%d",i);
        UI_TimerHandle[i]=xTimerCreate((const char*		)temp_timer,
									    (TickType_t			)(200/portTICK_PERIOD_MS),
							            (UBaseType_t		)pdFALSE,	// pdFALSE ，单次，pdTRUE 周期
							            (void*				)1,
							            (TimerCallbackFunction_t)UI_Common_timer_Callback); 
    }
    
    #if 0
	// 创建定时器
    sLcd_TimerHandle=xTimerCreate((const char*		)"sLcd_Timer",
									    (TickType_t			)(200/portTICK_PERIOD_MS),
							            (UBaseType_t		)pdFALSE,	// pdFALSE ，单次，pdTRUE 周期
							            (void*				)1,
							            (TimerCallbackFunction_t)sLcd_TimerCallBack); 
    
    yrLCD_TimerHandle=xTimerCreate((const char*		)"LcdLock_Timer",
									    (TickType_t			)(1000/portTICK_PERIOD_MS),
							            (UBaseType_t		)pdFALSE,	// pdFALSE ，单次，pdTRUE 周期
							            (void*				)1,
							            (TimerCallbackFunction_t)yrLCD_TimerCallBack); 								


    #endif


}

void UI_Common_timer_Start(Enum_UI_Common_Timer timer_id,uint32_t TimerMs,func_timerhandle_callback f_call_back)
{

    LCD_Timer_Callback[timer_id] =  f_call_back;
	xTimerChangePeriod(UI_TimerHandle[timer_id], pdMS_TO_TICKS(TimerMs), 3);

}


void UI_Common_timer_Stop(func_timerhandle_callback f_call_back)
{

    //Enum_UI_Common_Timer timer_id;
    int i= 0;


    for(i= 0;i<UI_Common_Timer_Max;i++)
    {

        if(LCD_Timer_Callback[i] == f_call_back)
        {
            xTimerStop(UI_TimerHandle[i],3);
            break;
        }
    }
    

}


void UI_Common_Set_Goback_Handle(uint32_t TimerMs,func_timerhandle_callback f_call_back)
{

    UI_Common_timer_Start(UI_Common_Timer_Goback,TimerMs, f_call_back);

}

void UI_Common_Cancel_Goback_Handle(void)
{

    xTimerStop(UI_TimerHandle[UI_Common_Timer_Goback],3);

}





