#ifndef UI_DISPALY_DATEANDTIME_H
#define UI_DISPALY_DATEANDTIME_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"
#include "app_lcd.h"

#include "scene_weather.h"
#include "mid_hrm.h"

#include "task.h"


#define SCREEN_DATEANDTIME_HEART_RATE_X  60
#define SCREEN_DATEANDTIME_HEART_RATE_Y  16

#define SCREEN_DATEANDTIME_TIME_X  34
#define SCREEN_DATEANDTIME_TIME_Y  64

#define SCREEN_DATEANDTIME_UNRMSG_X  148
#define SCREEN_DATEANDTIME_UNRMSG_Y  80

#define SCREEN_DATEANDTIME_WEATHER_X  56
#define SCREEN_DATEANDTIME_WEATHER_Y  122


void UI_Screen_DateAndTime_Entry(void);
void UI_Screen_DateAndTime_Display(void);
void UI_Screen_DateAndTime_Exit(void);

void UI_Screen_DateAndTime_shortkeyhandle(void);
void UI_Screen_DateAndTime_holdshortkeyhandle(void);
void UI_Screen_DateAndTime_holdlongkeyhandle(void);

void UI_Screen_DateAndTime_tpclickhandle(int point_x,int point_y);
void UI_Screen_DateAndTime_tpupslidehandle(void);
void UI_Screen_DateAndTime_tpdownslidehandle(void);
void UI_Screen_DateAndTime_tpleftslidehandle(void);
void UI_Screen_DateAndTime_tprightslidehandle(void);


void UI_Commom_Lockinfo_Init(void);
void UI_Commom_Lockinfo_Timehandle(void);
void UI_Commom_Lockinfo_Reset(void);
int UI_Commom_get_Lockinfo_State(void);
void UI_Screen_Lock_Display(void);
void UI_Screen_Lock_Entry(void);
void UI_Screen_Lock_Exit(void);


void UI_Screen_Lock_shortkeyhandle(void);
void UI_Screen_Lock_holdshortkeyhandle(void);
void UI_Screen_Lock_holdlongkeyhandle(void);


//1 允许 0.不允许
void UI_Commom_Set_Allow_Lockstate1(uint8 state);
//1 允许 0.不允许
void UI_Commom_Set_Allow_Lockstate2(uint8 state);

#endif

