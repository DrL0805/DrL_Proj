#ifndef UI_SCREEN_PRESSURE_H
#define UI_SCREEN_PRESSURE_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "scene_stress.h"




void UI_Screen_Pressure_Entry(void);
void UI_Screen_Pressure_Display(void);
void UI_Screen_Pressure_Exit(void);

void UI_Screen_Pressure_shortkeyhandle(void);
void UI_Screen_Pressure_holdshortkeyhandle(void);
void UI_Screen_Pressure_holdlongkeyhandle(void);


void UI_Screen_Pressure_tpclickhandle(int point_x,int point_y);
void UI_Screen_Pressure_tpupslidehandle(void);
void UI_Screen_Pressure_tpdownslidehandle(void);
void UI_Screen_Pressure_tpleftslidehandle(void);
void UI_Screen_Pressure_tprightslidehandle(void);





void UI_Screen_Pressure_Detail_Display(void);
void UI_Screen_Pressure_Detail_Entry(void);
void UI_Screen_Pressure_Detail_Exit(void);

void UI_Screen_Pressure_Detail_shortkeyhandle(void);
void UI_Screen_Pressure_Detail_holdshortkeyhandle(void);
void UI_Screen_Pressure_Detail_holdlongkeyhandle(void);
void UI_Screen_Pressure_Detail_tpclickhandle(int point_x,int point_y);
void UI_Screen_Pressure_Detail_tpupslidehandle(void);
void UI_Screen_Pressure_Detail_tpdownslidehandle(void);
void UI_Screen_Pressure_Detail_tpleftslidehandle(void);
void UI_Screen_Pressure_Detail_tprightslidehandle(void);



#endif

