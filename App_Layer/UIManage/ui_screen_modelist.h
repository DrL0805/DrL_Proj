#ifndef UI_SCREEN_MODELIST_H
#define UI_SCREEN_MODELIST_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "ui_screen_runingmode.h"
#include "ui_screen_climbing.h"


void UI_Screen_Modelist_Entry(void);
void UI_Screen_Modelist_Display(void);
void UI_Screen_Modelist_Exit(void);

void UI_Screen_Modelist_shortkeyhandle(void);
void UI_Screen_Modelist_holdshortkeyhandle(void);
void UI_Screen_Modelist_holdlongkeyhandle(void);

void UI_Screen_Modelist_tpclickhandle(int point_x,int point_y);
void UI_Screen_Modelist_tpupslidehandle(void);
void UI_Screen_Modelist_tpdownslidehandle(void);
void UI_Screen_Modelist_tpleftslidehandle(void);
void UI_Screen_Modelist_tprightslidehandle(void);

#endif

