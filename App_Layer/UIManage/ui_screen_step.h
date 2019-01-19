#ifndef UI_SCREEN_STEP_H
#define UI_SCREEN_STEP_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "scene_stairs.h"

void UI_Screen_Step_Entry(void);
void UI_Screen_Step_Display(void);
void UI_Screen_Step_Exit(void);

void UI_Screen_Step_shortkeyhandle(void);
void UI_Screen_Step_holdshortkeyhandle(void);
void UI_Screen_Step_holdlongkeyhandle(void);

void UI_Screen_Step_tpclickhandle(int point_x,int point_y);
void UI_Screen_Step_tpupslidehandle(void);
void UI_Screen_Step_tpdownslidehandle(void);
void UI_Screen_Step_tpleftslidehandle(void);
void UI_Screen_Step_tprightslidehandle(void);




void UI_Screen_Step_Detail_Display(void);
void UI_Screen_Step_Detail_Entry(void);
void UI_Screen_Step_Detail_Exit(void);


void UI_Screen_Step_Detail_shortkeyhandle(void);
void UI_Screen_Step_Detail_holdshortkeyhandle(void);
void UI_Screen_Step_Detail_holdlongkeyhandle(void);
void UI_Screen_Step_Detail_tpclickhandle(int point_x,int point_y);
void UI_Screen_Step_Detail_tpupslidehandle(void);
void UI_Screen_Step_Detail_tpdownslidehandle(void);
void UI_Screen_Step_Detail_tpleftslidehandle(void);
void UI_Screen_Step_Detail_tprightslidehandle(void);

#endif

