#ifndef UI_SCREEN_BREATHTRAINING_H
#define UI_SCREEN_BREATHTRAINING_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "ui_timerhandle_main.h"


void UI_Screen_BreathTraining_DfaultInfo(void);
void UI_Screen_BreathTraining_Timerhandle(void);
void UI_Screen_BreathTraining_Display(void);
void UI_Screen_BreathTraining_Entry(void);
void UI_Screen_BreathTraining_Exit(void);

void UI_Screen_BreathTraining_shortkeyhandle(void);
void UI_Screen_BreathTraining_holdshortkeyhandle(void);
void UI_Screen_BreathTraining_holdlongkeyhandle(void);

void UI_Screen_BreathTraining_tpclickhandle(int point_x,int point_y);
void UI_Screen_BreathTraining_tpupslidehandle(void);
void UI_Screen_BreathTraining_tpdownslidehandle(void);
void UI_Screen_BreathTraining_tpleftslidehandle(void);
void UI_Screen_BreathTraining_tprightslidehandle(void);


#endif

