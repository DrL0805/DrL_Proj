#ifndef UI_DISPALY_MAIN_H
#define UI_DISPALY_MAIN_H

#include "ui_display_common.h"
#include "mid_key.h"
#include "ui_screen_warn.h"
#include "mid_interface.h"
#include "mid_lcd.h"
#include "ui_screen_store.h"
#include "ui_display_poweron.h"
#include "ui_screen_step.h"
#include "ui_screen_heartrate.h"
#include "ui_screen_pressure.h"
#include "ui_screen_temperature.h"
#include "ui_screen_sleep.h"
#include "ui_screen_compass.h"
#include "ui_screen_history.h"
#include "ui_screen_modelist.h"
#include "ui_screen_breathtraining.h"
#include "ui_screen_runingmode.h"
#include "ui_screen_climbing.h"
#include "ui_screen_swim.h"
#include "ui_screen_sporthistory.h"
#include "ui_screen_stopwatch.h"
#include "ui_screen_countdown.h"
#include "ui_screen_alarm.h"
#include "ui_screen_findphone.h"
#include "ui_screen_setting.h"
#include "ui_screen_other.h"




extern void UI_Show_Screen(void);

// 主窗口句柄类型
typedef enum 
{
	Common_Screen_MainID_Min,		          // 无效值
	Common_Screen_MainID_Store,		          // 仓储	
	Common_Screen_MainID_Poweron,             // 开机
	Common_Screen_MainID_DateAndTime,         // 时间
	Common_Screen_MainID_Step,
	Common_Screen_MainID_Step_Detail,
	Common_Screen_MainID_Heartrate,
	Common_Screen_MainID_Heartrate_Detail,
	Common_Screen_MainID_Pressure,
	Common_Screen_MainID_Pressure_Detail,
	Common_Screen_MainID_Temperature,
	Common_Screen_MainID_Temperature_Detail,
	Common_Screen_MainID_Sleep,
	Common_Screen_MainID_Sleep_Detail,
	Common_Screen_MainID_Compass,              //ABC
	Common_Screen_MainID_Altitude_Detail,              //ABC
	Common_Screen_MainID_Airpressure_Detail,              //ABC
	Common_Screen_MainID_History,
	Common_Screen_MainID_History_List,
	Common_Screen_MainID_History_Detail,
	Common_Screen_MainID_Modelist,
	Common_Screen_MainID_BreathTraining,
	Common_Screen_MainID_Running,		
	Common_Screen_MainID_Climbing,          
	Common_Screen_MainID_Swim,        
	Common_Screen_MainID_SportHistory,
	Common_Screen_MainID_SportHistory_Detail,
	Common_Screen_MainID_Stopwatch,
	Common_Screen_MainID_Stopwatch_Detail,
	Common_Screen_MainID_Countdown,
	Common_Screen_MainID_Alarm,
	Common_Screen_MainID_Findphone,
	Common_Screen_MainID_Setting,           
	Common_Screen_MainID_Setting_Brightness ,           
	Common_Screen_MainID_Setting_Infomation,           
	Common_Screen_MainID_OTA,           
	Common_Screen_MainID_Charging,           
	Common_Screen_MainID_Lock,           
	Common_Screen_MainID_Reset,           
	Common_Screen_MainID_Test,           
	Common_Screen_MainID_Test_App,           
	Common_Screen_MainID_Max,			// 窗口句柄数量，这个值必须准确
}Enum_Common_Screen_MAINID;
    
typedef void (*func_callback_handle)(void);

void UI_Set_Curr_ScreenID(Enum_Common_Screen_MAINID curr_id);
Enum_Common_Screen_MAINID UI_Get_Curr_ScreenID(void);


void UI_Set_Go_back_handle(func_callback_handle go_back_handle);
void* UI_Get_Go_back_handle(void);
void UI_Do_Go_back_handle(void);



void UI_Show_Screen(void);
void UI_Show_Screen_Common(void);
void UI_Show_Screen_Warn(void);


extern void UI_Commom_Lockinfo_Reset(void);
extern int UI_Commom_get_Lockinfo_State(void);



extern void UI_Common_Value_Init(void);
extern eLcdBLGrade UI_Common_Get_Blacklight_value(void);
extern void UI_Common_Set_Blacklight_value(eLcdBLGrade value);
extern void UI_Common_Open_Blacklight(void);
extern void UI_Common_Close_Blacklight(void);
extern void UI_Common_Init(void)
;


//显示数据
uint8_t * UI_Display_Get_Mainram(void);
//组合数据使用
uint8_t * UI_Display_Get_Tempram(void);
//过场动画使用，保存上一屏数据
uint8_t * UI_Display_Get_Runoldram(void);
//过场动画组合数据组合使用  --通过 tempram和runoldran组合获得
uint8_t * UI_Display_Get_Runram(void);

//将临时ram数据，cpy到显示专用ram中
void UI_Display_Prepare(uint8_t *tempram);

#endif

