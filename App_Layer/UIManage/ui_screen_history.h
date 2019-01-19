#ifndef UI_SCREEN_HISTORY_H
#define UI_SCREEN_HISTORY_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "app_remind_manage.h"


void UI_Screen_History_Entry(void);
void UI_Screen_History_Display(void);
void UI_Screen_History_Exit(void);

void UI_Screen_History_shortkeyhandle(void);
void UI_Screen_History_holdshortkeyhandle(void);
void UI_Screen_History_holdlongkeyhandle(void);

void UI_Screen_History_tpclickhandle(int point_x,int point_y);
void UI_Screen_History_tpupslidehandle(void);
void UI_Screen_History_tpdownslidehandle(void);
void UI_Screen_History_tpleftslidehandle(void);
void UI_Screen_History_tprightslidehandle(void);



void UI_Screen_History_List_Display(void);
void UI_Screen_History_List_Entry(void);
void UI_Screen_History_List_Exit(void);

void UI_Screen_History_List_shortkeyhandle(void);
void UI_Screen_History_List_holdshortkeyhandle(void);
void UI_Screen_History_List_holdlongkeyhandle(void);

void UI_Screen_History_List_tpclickhandle(int point_x,int point_y);
void UI_Screen_History_List_tpupslidehandle(void);
void UI_Screen_History_List_tpdownslidehandle(void);
void UI_Screen_History_List_tpleftslidehandle(void);
void UI_Screen_History_List_tprightslidehandle(void);




void UI_Screen_History_Detail_Display(void);
void UI_Screen_History_Detail_Entry(void);
void UI_Screen_History_Detail_Exit(void);


void UI_Screen_History_Detail_shortkeyhandle(void);
void UI_Screen_History_Detail_holdshortkeyhandle(void);
void UI_Screen_History_Detail_holdlongkeyhandle(void);
void UI_Screen_History_Detail_tpclickhandle(int point_x,int point_y);
void UI_Screen_History_Detail_tpupslidehandle(void);
void UI_Screen_History_Detail_tpdownslidehandle(void);
void UI_Screen_History_Detail_tpleftslidehandle(void);
void UI_Screen_History_Detail_tprightslidehandle(void);

#endif

