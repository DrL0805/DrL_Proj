#ifndef UI_SCREEN_COUNTDOWN_H
#define UI_SCREEN_COUNTDOWN_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "scene_countdown.h"



void UI_Screen_Countdown_Timerhandle(void);
void UI_Screen_Countdown_Entry(void);
void UI_Screen_Countdown_Display(void);
void UI_Screen_Countdown_Exit(void);


void UI_Screen_Countdown_shortkeyhandle(void);
void UI_Screen_Countdown_holdshortkeyhandle(void);
void UI_Screen_Countdown_holdlongkeyhandle(void);
void UI_Screen_Countdown_tpclickhandle(int point_x,int point_y);
void UI_Screen_Countdown_tpupslidehandle(void);
void UI_Screen_Countdown_tpdownslidehandle(void);
void UI_Screen_Countdown_tpleftslidehandle(void);
void UI_Screen_Countdown_tprightslidehandle(void);


#endif

