#ifndef UI_SCREEN_STORE_H
#define UI_SCREEN_STORE_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"


 void UI_Screen_Store_Entry(void);
 void UI_Screen_Store_Display(void);
 void UI_Screen_Store_Exit(void);

 void UI_Screen_Store_shortkeyhandle(void);
 void UI_Screen_Store_holdshortkeyhandle(void);
 void UI_Screen_Store_holdlongkeyhandle(void);

 extern void App_Sys_StartingUp(void);

#endif

