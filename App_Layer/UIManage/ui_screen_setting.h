#ifndef UI_SCREEN_SETTING_H
#define UI_SCREEN_SETTING_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "app_protocal.h"



void UI_Screen_Setting_Entry(void);
void UI_Screen_Setting_Display(void);
void UI_Screen_Setting_Exit(void);

void UI_Screen_Setting_shortkeyhandle(void);
void UI_Screen_Setting_holdshortkeyhandle(void);
void UI_Screen_Setting_holdlongkeyhandle(void);
void UI_Screen_Setting_tpclickhandle(int point_x,int point_y);
void UI_Screen_Setting_tpupslidehandle(void);
void UI_Screen_Setting_tpdownslidehandle(void);
void UI_Screen_Setting_tpleftslidehandle(void);
void UI_Screen_Setting_tprightslidehandle(void);



void UI_Screen_Setting_Infomation_Entry(void);
void UI_Screen_Setting_Infomation_Display(void);
void UI_Screen_Setting_Infomation_Exit(void);

void UI_Screen_Setting_Infomation_shortkeyhandle(void);
void UI_Screen_Setting_Infomation_holdshortkeyhandle(void);
void UI_Screen_Setting_Infomation_holdlongkeyhandle(void);
void UI_Screen_Setting_Infomation_tpclickhandle(int point_x,int point_y);
void UI_Screen_Setting_Infomation_tpupslidehandle(void);
void UI_Screen_Setting_Infomation_tpdownslidehandle(void);
void UI_Screen_Setting_Infomation_tpleftslidehandle(void);
void UI_Screen_Setting_Infomation_tprightslidehandle(void);


void UI_Screen_Setting_Brightness_Entry(void);
void UI_Screen_Setting_Brightness_Display(void);
void UI_Screen_Setting_Brightness_Exit(void);

void UI_Screen_Setting_Brightness_shortkeyhandle(void);
void UI_Screen_Setting_Brightness_holdshortkeyhandle(void);
void UI_Screen_Setting_Brightness_holdlongkeyhandle(void);
void UI_Screen_Setting_Brightness_tpclickhandle(int point_x,int point_y);
void UI_Screen_Setting_Brightness_tpupslidehandle(void);
void UI_Screen_Setting_Brightness_tpdownslidehandle(void);
void UI_Screen_Setting_Brightness_tpleftslidehandle(void);
void UI_Screen_Setting_Brightness_tprightslidehandle(void);


#endif



