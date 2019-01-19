#ifndef UI_SCREEN_FINDPHONE_H
#define UI_SCREEN_FINDPHONE_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "scene_findphone.h"



void UI_Screen_Findphone_Timerhandle(void);
void UI_Screen_Findphone_Entry(void);
void UI_Screen_Findphone_Display(void);
void UI_Screen_Findphone_Exit(void);


void UI_Screen_Findphone_shortkeyhandle(void);
void UI_Screen_Findphone_holdshortkeyhandle(void);
void UI_Screen_Findphone_holdlongkeyhandle(void);
void UI_Screen_Findphone_tpclickhandle(int point_x,int point_y);
void UI_Screen_Findphone_tpupslidehandle(void);
void UI_Screen_Findphone_tpdownslidehandle(void);
void UI_Screen_Findphone_tpleftslidehandle(void);
void UI_Screen_Findphone_tprightslidehandle(void);


#endif

