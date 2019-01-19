#ifndef UI_SCREEN_SPORTHISTORY_H
#define UI_SCREEN_SPORTHISTORY_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"


void UI_Screen_SportHistory_Entry(void);
void UI_Screen_SportHistory_Display(void);
void UI_Screen_SportHistory_Exit(void);

void UI_Screen_SportHistory_shortkeyhandle(void);
void UI_Screen_SportHistory_holdshortkeyhandle(void);
void UI_Screen_SportHistory_holdlongkeyhandlevoid(void);

void UI_Screen_SportHistory_tpclickhandle(int point_x,int point_y);
void UI_Screen_SportHistory_tpupslidehandle(void);
void UI_Screen_SportHistory_tpdownslidehandle(void);
void UI_Screen_SportHistory_tpleftslidehandle(void);
void UI_Screen_SportHistory_tprightslidehandle(void);


void UI_Screen_SportHistoryDetail_Display(void);


void UI_Screen_SportHistoryDetail_Entry(void);
void UI_Screen_SportHistoryDetail_Exit(void);
void UI_Screen_SportHistoryDetail_shortkeyhandle(void);
void UI_Screen_SportHistoryDetail_holdshortkeyhandle(void);
void UI_Screen_SportHistoryDetail_holdlongkeyhandle(void);
void UI_Screen_SportsHistoryDetail_tpclickhandle(int point_x,int point_y);
void UI_Screen_SportHistoryDetail_tpupslidehandle(void);
void UI_Screen_SportHistoryDetail_tpdownslidehandle(void);
void UI_Screen_SportHistoryDetail_tpleftslidehandle(void);
void UI_Screen_SportHistoryDetail_tprightslidehandle(void);





#endif

