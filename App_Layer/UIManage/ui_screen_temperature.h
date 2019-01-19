#ifndef UI_SCREEN_TEMPERATURE_H
#define UI_SCREEN_TEMPERATURE_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "mid_infrared_temp.h"



void UI_Screen_Temperature_Entry(void);
void UI_Screen_Temperature_Display(void);
void UI_Screen_Temperature_Exit(void);

void UI_Screen_Temperature_shortkeyhandle(void);
void UI_Screen_Temperature_holdshortkeyhandle(void);
void UI_Screen_Temperature_holdlongkeyhandle(void);


void UI_Screen_Temperature_tpclickhandle(int point_x,int point_y);
void UI_Screen_Temperature_tpupslidehandle(void);
void UI_Screen_Temperature_tpdownslidehandle(void);
void UI_Screen_Temperature_tpleftslidehandle(void);
void UI_Screen_Temperature_tprightslidehandle(void);


void UI_Screen_Temperature_Detail_Display(void);
void UI_Screen_Temperature_Detail_Entry(void);
void UI_Screen_Temperature_Detail_Exit(void);


void UI_Screen_Temperature_Detail_shortkeyhandle(void);
void UI_Screen_Temperature_Detail_holdshortkeyhandle(void);
void UI_Screen_Temperature_Detail_holdlongkeyhandle(void);
void UI_Screen_Temperature_Detail_tpclickhandle(int point_x,int point_y);
void UI_Screen_Temperature_Detail_tpupslidehandle(void);
void UI_Screen_Temperature_Detail_tpdownslidehandle(void);
void UI_Screen_Temperature_Detail_tpleftslidehandle(void);
void UI_Screen_Temperature_Detail_tprightslidehandle(void);





#endif

