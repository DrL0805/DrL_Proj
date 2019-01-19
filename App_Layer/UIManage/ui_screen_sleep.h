#ifndef UI_SCREEN_SLEEP_H
#define UI_SCREEN_SLEEP_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "algorithm_sleep.h"


void UI_Screen_Sleep_Entry(void);
void UI_Screen_Sleep_Display(void);
void UI_Screen_Sleep_Exit(void);

void UI_Screen_Sleep_shortkeyhandle(void);
void UI_Screen_Sleep_holdshortkeyhandle(void);
void UI_Screen_Sleep_holdlongkeyhandle(void);

void UI_Screen_Sleep_tpclickhandle(int point_x,int point_y);
void UI_Screen_Sleep_tpupslidehandle(void);
void UI_Screen_Sleep_tpdownslidehandle(void);
void UI_Screen_Sleep_tpleftslidehandle(void);
void UI_Screen_Sleep_tprightslidehandle(void);




void UI_Screen_Sleep_Detail_Display(void);
void UI_Screen_Sleep_Detail_Entry(void);
void UI_Screen_Sleep_Detail_Exit(void);

void UI_Screen_Sleep_Detail_shortkeyhandle(void);
void UI_Screen_Sleep_Detail_holdshortkeyhandle(void);
void UI_Screen_Sleep_Detail_holdlongkeyhandle(void);
void UI_Screen_Sleep_Detail_tpclickhandle(int point_x,int point_y);
void UI_Screen_Sleep_Detail_tpupslidehandle(void);
void UI_Screen_Sleep_Detail_tpdownslidehandle(void);
void UI_Screen_Sleep_Detail_tpleftslidehandle(void);
void UI_Screen_Sleep_Detail_tprightslidehandle(void);



#endif

