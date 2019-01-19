#ifndef UI_SCREEN_HEARTRATE_H
#define UI_SCREEN_HEARTRATE_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "mid_hrm.h"
#include "scene_hrm.h"



void UI_Screen_Heartrate_Entry(void);
void UI_Screen_Heartrate_Display(void);
void UI_Screen_Heartrate_Exit(void);

void UI_Screen_Heartrate_shortkeyhandle(void);
void UI_Screen_Heartrate_holdshortkeyhandle(void);
void UI_Screen_Heartrate_holdlongkeyhandle(void);

void UI_Screen_Heartrate_tpclickhandle(int point_x,int point_y);
void UI_Screen_Heartrate_tpupslidehandle(void);
void UI_Screen_Heartrate_tpdownslidehandle(void);
void UI_Screen_Heartrate_tpleftslidehandle(void);
void UI_Screen_Heartrate_tprightslidehandle(void);


void UI_Screen_Heartrate_Detail_Display(void);
void UI_Screen_Heartrate_Detail_Entry(void);
void UI_Screen_Heartrate_Detail_Exit(void);

void UI_Screen_Heartrate_Detail_shortkeyhandle(void);
void UI_Screen_Heartrate_Detail_holdshortkeyhandle(void);
void UI_Screen_Heartrate_Detail_holdlongkeyhandle(void);

void UI_Screen_Heartrate_Detail_tpclickhandle(int point_x,int point_y);
void UI_Screen_Heartrate_Detail_tpupslidehandle(void);
void UI_Screen_Heartrate_Detail_tpdownslidehandle(void);
void UI_Screen_Heartrate_Detail_tpleftslidehandle(void);
void UI_Screen_Heartrate_Detail_tprightslidehandle(void);


#endif

