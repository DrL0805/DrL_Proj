#ifndef UI_SCREEN_STOPWATCH_H
#define UI_SCREEN_STOPWATCH_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "scene_stopwatch.h"


void UI_Screen_Stopwatch_Timerhandle(void);
void UI_Screen_Stopwatch_Entry(void);
void UI_Screen_Stopwatch_Display(void);
void UI_Screen_Stopwatch_Exit(void);

void UI_Screen_Stopwatch_shortkeyhandle(void);
void UI_Screen_Stopwatch_holdshortkeyhandle(void);
void UI_Screen_Stopwatch_holdlongkeyhandle(void);
void UI_Screen_Stopwatch_tpclickhandle(int point_x,int point_y);
void UI_Screen_Stopwatch_tpupslidehandle(void);
void UI_Screen_Stopwatch_tpdownslidehandle(void);
void UI_Screen_Stopwatch_tpleftslidehandle(void);
void UI_Screen_Stopwatch_tprightslidehandle(void);


void UI_Screen_Stopwatch_Detail_Entry(void);
void UI_Screen_Stopwatch_Detail_Display(void);
void UI_Screen_Stopwatch_Detail_Exit(void);

void UI_Screen_Stopwatch_Detail_shortkeyhandle(void);
void UI_Screen_Stopwatch_Detail_tpclickhandle(int point_x,int point_y);
void UI_Screen_Stopwatch_Detail_tpupslidehandle(void);
void UI_Screen_Stopwatch_Detail_tpdownslidehandle(void);
void UI_Screen_Stopwatch_Detail_tpleftslidehandle(void);
void UI_Screen_Stopwatch_Detail_tprightslidehandle(void);


#endif

