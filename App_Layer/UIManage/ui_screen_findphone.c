
#include "ui_screen_findphone.h"


bool is_finding = 0;
//static int quit_count = 0;


void  UI_Screen_Findphone_Timerhandle(void)
{


    UI_Screen_Findphone_Display();
    UI_Common_set_timer_handle(UI_Screen_Findphone_Timerhandle);
    App_Lcd_TimerStart(500);

}

void UI_Screen_Findphone_Entry(void)
{
    if(geBleState == BLE_CONNECT)
    {
        is_finding = 1;
        Scene_Findphone_Start();
    }

    UI_Screen_Findphone_Timerhandle();

    UI_Common_set_key_handle(UI_Screen_Findphone_shortkeyhandle,NULL,NULL);
    
    UI_Common_set_tp_click_handle(UI_Screen_Findphone_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Findphone_tpupslidehandle,
                                    UI_Screen_Findphone_tpdownslidehandle,
                                    UI_Screen_Findphone_tpleftslidehandle,
                                    UI_Screen_Findphone_tprightslidehandle);

}


void UI_Screen_Findphone_Display(void)
{

    static int i = 0;

    
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Findphone)
        return;

    UI_Common_Clear_Screen(temp_ram);
    
    
    RTT_DEBUG_printf(0,"geBleState = %d",geBleState);
    
    if(geBleState != BLE_CONNECT)
    {

            if(is_finding == 1)
            {
                is_finding = 0;
                Scene_Findphone_Stop();
                App_Lcd_TimerStop();
                UI_Common_set_timer_handle(NULL);
            }

            UI_Common_AddBWsourcePic(temp_ram,64,40,(uint8_t*)image_warn_bt_48_h,APP_COLOR_BLACK,APP_COLOR_RED);
            UI_Common_Draw_FontStr_textbox(temp_ram,8,92,160,68,(uint8_t *)gchinesefont_warn_BTbreak,APP_COLOR_WHITE,APP_COLOR_BLACK);
        
    }
    else
    {

            if(is_finding == 0)
            {
                is_finding = 1;
                Scene_Findphone_Start();
            }
            
            UI_Common_AddBWsourcePic(temp_ram,60,38,(uint8_t*)image_findphone_phone_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        
            
            if(i>=1)
            {
                UI_Common_AddBWsourcePic(temp_ram,48,58,(uint8_t*)image_findphone_l_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
                UI_Common_AddBWsourcePic(temp_ram,124,58,(uint8_t*)image_findphone_l_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
            }

            if(i>=2)
            {
                UI_Common_AddBWsourcePic(temp_ram,36,66,(uint8_t*)image_findphone_m_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
                UI_Common_AddBWsourcePic(temp_ram,136,66,(uint8_t*)image_findphone_m_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
            }

            if(i>=3)
            {
                UI_Common_AddBWsourcePic(temp_ram,24,74,(uint8_t*)image_findphone_s_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
                UI_Common_AddBWsourcePic(temp_ram,148,74,(uint8_t*)image_findphone_s_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
            }

            if(i>=3)
            {
                i = 0;
            }
            else
            {
                i++;
            }

            //UI_Common_AddPic(lcdram,4,122,(uint8_t*)BtnFullRed_h);
            //UI_Common_AddBWsourcePic(temp_ram,4,122,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_RED);
            //UI_Common_Draw_FontStr_textbox(temp_ram,0,118,176,58,(uint8_t *)gchinesefont_finephone_stop,APP_COLOR_BLACK,APP_COLOR_RED);
            
    }
    
    UI_Display_Prepare(temp_ram);

}


void UI_Screen_Findphone_Exit(void)
{

    is_finding = 0;
    Scene_Findphone_Stop();
    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();

}


void UI_Screen_Findphone_shortkeyhandle(void)
{
    UI_Screen_Findphone_Exit();
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();
        

}

void UI_Screen_Findphone_holdshortkeyhandle(void)
{

}

void UI_Screen_Findphone_holdlongkeyhandle(void)
{
}



void UI_Screen_Findphone_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
            #if 0
                if(is_finding == 0)
                {
                    is_finding = 1;
                    Scene_Findphone_Start();
                    UI_Common_set_timer_handle(UI_Screen_Findphone_Timerhandle);
                    App_Lcd_TimerStart(10);
                }
                else
                {
                    quit_count =0;
                    is_finding = 0;
                    Scene_Findphone_Stop();
                    App_Lcd_TimerStop();
                    UI_Common_set_timer_handle(NULL);
                    UI_Screen_Findphone_Display();
                    UI_Screen_Redraw_Screen();
                }
            #endif
        }
        break;
        default:
        break;
    }


}

void UI_Screen_Findphone_tpupslidehandle(void)
{
}

void UI_Screen_Findphone_tpdownslidehandle(void)
{

}

void UI_Screen_Findphone_tpleftslidehandle(void)
{
}

void UI_Screen_Findphone_tprightslidehandle(void)
{
    UI_Screen_Findphone_Exit();
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Modelist);
    UI_Screen_draw_Screen();

}














