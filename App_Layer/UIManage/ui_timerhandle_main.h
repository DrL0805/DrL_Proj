#ifndef UI_TIMERHANDLE_MAIN_H
#define UI_TIMERHANDLE_MAIN_H

#include "ui_display_common.h"

typedef void (*func_timerhandle_callback)(void);

void UI_Common_set_timer_handle(func_timerhandle_callback timerhandle);
void UI_Common_do_timer_handle(void);


typedef enum 
{
	UI_Common_Timer_0,        //1s 1次标准计时timer 控制界面时间显示刷新
	UI_Common_Timer_1,        
	UI_Common_Timer_2,        
	UI_Common_Timer_Goback,            //返回专用timer，用于弹出报警框后，返回原本界面
	UI_Common_Timer_4,                 //仓储界面，显示电量1s后黑屏
	UI_Common_Timer_Max,		
}Enum_UI_Common_Timer;



void UI_Common_timer_Callback(TimerHandle_t xTimer);
void UI_Common_timer_Init(void);
void UI_Common_timer_Start(Enum_UI_Common_Timer timer_id,uint32_t TimerMs,func_timerhandle_callback f_call_back);
void UI_Common_timer_Stop(func_timerhandle_callback f_call_back);


void UI_Common_Set_Goback_Handle(uint32_t TimerMs,func_timerhandle_callback f_call_back);
void UI_Common_Cancel_Goback_Handle(void);


#endif

