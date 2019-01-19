#include "ui_keyhandle_main.h"
#include "ui_display_common.h"





func_key_handle key_short_press_callback = NULL;
func_key_handle key_holdshort_press_callback = NULL;
func_key_handle key_holdlong_press_callback = NULL;

//void (*key_short_press_callback)(void) = NULL;
//void (*key_holdshort_press_callback)(void) = NULL;
//void (*key_holdlong_press_callback)(void) = NULL;



void UI_Common_set_key_handle(func_key_handle short_handle,func_key_handle hold_short_handle,func_key_handle holdlong_handle)
{
    key_short_press_callback = short_handle;
    key_holdshort_press_callback = hold_short_handle;
    key_holdlong_press_callback = holdlong_handle;
}

void UI_Common_do_key_handle(eMidKeyVal keyvalue)
{

        UI_Commom_Lockinfo_Reset();
        
        if(curr_run_screen_info.is_run == 1)
            return;

        switch(keyvalue)
        {
            case MID_KEY0_SHORT:
                    if(key_short_press_callback!=NULL)
                        key_short_press_callback();
                break;
            case MID_KEY0_HOLDSHORT:
                    if(key_holdshort_press_callback!=NULL)
                        key_holdshort_press_callback();
                break;
            case MID_KEY0_HOLDLONG:      
                    if(key_holdlong_press_callback!=NULL)
                        key_holdlong_press_callback();
                break;
            default:
                break;
        }
        
}

void UI_Common_clean_key_handle(void)
{
    UI_Common_set_key_handle(NULL,NULL,NULL);
}


void UI_Common_Shake(void)
{
    Mid_Motor_ShakeStart(eMidMotorShake1Hz, 1); 
}




