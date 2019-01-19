#ifndef UI_SCREEN_OTHER_H
#define UI_SCREEN_OTHER_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "ui_keyhandle_main.h"


void UI_Screen_OTA_Entry(void);
void UI_Screen_OTA_Display(void);
void UI_Screen_OTA_Exit(void);

void UI_Screen_OTA_shortkeyhandle(void);
void UI_Screen_OTA_holdshortkeyhandle(void);
void UI_Screen_OTA_holdlongkeyhandle(void);

void UI_Screen_OTA_Show(void);

void UI_Screen_Charging_Display(void);
void UI_Screen_Charging_Entry(void);
void UI_Screen_Charging_Exit(void);

void UI_Screen_Charging_shortkeyhandle(void);
void UI_Screen_Charging_holdshortkeyhandle(void);
void UI_Screen_Charging_holdlongkeyhandle(void);


void UI_Screen_Charging_Show(void);


void UI_Screen_Test_Display(void);
void UI_Screen_Test_Entry(void);
void UI_Screen_Test_Exit(void);
void UI_Screen_Test_shortkeyhandle(void);
void UI_Screen_Test_holdshortkeyhandle(void);
void UI_Screen_Test_holdlongkeyhandle(void);


void UI_Screen_Test_App_Entry(void);
void UI_Screen_Test_App_Exit(void);
void UI_Screen_Test_App_shortkeyhandle(void);
void UI_Screen_Test_App_holdshortkeyhandle(void);
void UI_Screen_Test_App_holdlongkeyhandle(void);
void UI_Screen_Test_App_Show(void);



void UI_Screen_Reset_Display(void);
void UI_Screen_Reset_Entry(void);
void UI_Screen_Reset_Exit(void);
void UI_Screen_Reset_Show(void);

#endif

