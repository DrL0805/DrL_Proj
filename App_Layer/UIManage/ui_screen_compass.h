#ifndef UI_SCREEN_COMPASS_H
#define UI_SCREEN_COMPASS_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "scene_abc.h"

void UI_Screen_Compass_Entry(void);
void UI_Screen_Compass_Display(void);
void UI_Screen_Compass_Exit(void);

void UI_Screen_Compass_shortkeyhandle(void);
void UI_Screen_Compass_holdshortkeyhandle(void);
void UI_Screen_Compass_holdlongkeyhandle(void);

void UI_Screen_Compass_tpclickhandle(int point_x,int point_y);
void UI_Screen_Compass_tpupslidehandle(void);
void UI_Screen_Compass_tpdownslidehandle(void);
void UI_Screen_Compass_tpleftslidehandle(void);
void UI_Screen_Compass_tprightslidehandle(void);

void UI_Screen_Altitude_Detail_Display(void);
void UI_Screen_Altitude_Detail_Entry(void);
void UI_Screen_Altitude_Detail_Exit(void);

void UI_Screen_Altitude_Detail_shortkeyhandle(void);
void UI_Screen_Altitude_Detail_holdshortkeyhandle(void);
void UI_Screen_Altitude_Detail_holdlongkeyhandle(void);
void UI_Screen_Altitude_Detail_tpclickhandle(int point_x,int point_y);
void UI_Screen_Altitude_Detail_tpupslidehandle(void);
void UI_Screen_Altitude_Detail_tpdownslidehandle(void);
void UI_Screen_Altitude_Detail_tpleftslidehandle(void);
void UI_Screen_Altitude_Detail_tprightslidehandle(void);


void UI_Screen_Airpressure_Detail_Display(void);
void UI_Screen_Airpressure_Detail_Entry(void);
void UI_Screen_Airpressure_Detail_Exit(void);

void UI_Screen_Airpressure_Detail_shortkeyhandle(void);
void UI_Screen_Airpressure_Detail_holdshortkeyhandle(void);
void UI_Screen_Airpressure_Detail_holdlongkeyhandle(void);
void UI_Screen_Airpressure_Detail_tpclickhandle(int point_x,int point_y);
void UI_Screen_Airpressure_Detail_tpupslidehandle(void);
void UI_Screen_Airpressure_Detail_tpdownslidehandle(void);
void UI_Screen_Airpressure_Detail_tpleftslidehandle(void);
void UI_Screen_Airpressure_Detail_tprightslidehandle(void);


#endif

