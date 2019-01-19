#ifndef UI_SCREEN_ALARM_H
#define UI_SCREEN_ALARM_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "scene_alarm.h"


void UI_Screen_Alarm_Entry(void);
void UI_Screen_Alarm_Display(void);
void UI_Screen_Alarm_Exit(void);

void UI_Screen_Alarm_shortkeyhandle(void);
void UI_Screen_Alarm_holdshortkeyhandle(void);
void UI_Screen_Alarm_holdlongkeyhandle(void);

void UI_Screen_Alarm_tpclickhandle(int point_x,int point_y);
void UI_Screen_Alarm_tpupslidehandle(void);
void UI_Screen_Alarm_tpdownslidehandle(void);
void UI_Screen_Alarm_tpleftslidehandle(void);
void UI_Screen_Alarm_tprightslidehandle(void);

int UI_Screen_Alarm_Get_State(void);


#endif

