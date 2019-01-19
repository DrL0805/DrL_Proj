#include "ui_screen_store.h"
#include "ui_screen_dateandtime.h"

uint8 is_show_barrery = 1;

void UI_Screen_Store_Timehandle(void)
{
    if(is_show_barrery == 1)
    {
        is_show_barrery =0;
        UI_Screen_draw_Screen();
    }

}


void UI_Screen_Store_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();


    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Store)
        return;

    UI_Common_Clear_Screen(temp_ram);

    if(is_show_barrery ==1)
    {
        UI_Common_Add_Battery(temp_ram, 76,76,0);
        UI_Common_timer_Start(UI_Common_Timer_4,1000,UI_Screen_Store_Timehandle);
    }
    else
    {
    }

    UI_Display_Prepare(temp_ram);
    
    
}


void UI_Screen_Store_Entry(void)
{

    UI_Commom_Set_Allow_Lockstate1(0);
    
    UI_Screen_Store_Display();
    
    UI_Common_set_key_handle(UI_Screen_Store_shortkeyhandle,UI_Screen_Store_holdshortkeyhandle,NULL);
    UI_Common_clean_tp_handle();
    
}

void UI_Screen_Store_Exit(void)
{
}

void UI_Screen_Store_shortkeyhandle(void)
{

    if(is_show_barrery == 0)
    {
        is_show_barrery = 1;

        UI_Screen_draw_Screen();
    }


}

void UI_Screen_Store_holdshortkeyhandle(void)
{

    UI_Commom_Set_Allow_Lockstate1(1);
    App_Sys_StartingUp();
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Poweron);
    UI_Screen_draw_Screen();
    
}

void UI_Screen_Store_holdlongkeyhandle(void)
{
}



