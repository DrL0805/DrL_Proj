

#include "ui_screen_setting.h"

static int page_number = 0;


 
void UI_Screen_Setting_Entry(void)
{


    
    UI_Screen_Setting_Display();
    
    UI_Common_set_key_handle(UI_Screen_Setting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Setting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Setting_tpupslidehandle,
                                    UI_Screen_Setting_tpdownslidehandle,
                                    UI_Screen_Setting_tpleftslidehandle,
                                    UI_Screen_Setting_tprightslidehandle);
    
    
}


void UI_Screen_Setting_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Setting)
        return;

    UI_Common_Clear_Screen(temp_ram);

    
    if(page_number == 0)
    {
        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t*)gchinesefont_warn_watchface,NULL,NULL,0);
        
        UI_Common_AddBWsourcePic(temp_ram,8,76,(uint8_t*)gchinesefont_warn_donotdisturb,APP_COLOR_BLACK,APP_COLOR_WHITE);
        #if 1
        if(gtSysCfg.notDisturbSwitch == 0)
        {

            UI_Common_AddPic(temp_ram,120,76,(uint8_t *)image_switcher_off_24_h);
        }
        else
        {
            UI_Common_AddPic(temp_ram,120,76,(uint8_t *)image_switcher_on_24_h);
        }
        #endif

        UI_Common_AddBWsourcePic(temp_ram,8,135,(uint8_t*)gchinesefont_warn_bluetooth,APP_COLOR_BLACK,APP_COLOR_WHITE);
        #if 1
        if(geBleState == BLE_SLEEP)
        {
            //UI_Common_AddBWsourcePic(temp_ram,120,135,(uint8_t *)image_switcher_off_24_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            UI_Common_AddPic(temp_ram,120,135,(uint8_t *)image_switcher_off_24_h);
        }
        else
        {
            UI_Common_AddPic(temp_ram,120,135,(uint8_t *)image_switcher_on_24_h);
        }
        #endif

        
    }
    else
    {
        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t*)gchinesefont_warn_brightness,NULL,NULL,0);
        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t*)gchinesefont_warn_asregards,NULL,NULL,0);
    
    }
    
    UI_Display_Prepare(temp_ram);

}


void UI_Screen_Setting_Exit(void)
{

    page_number = 0;

}


void UI_Screen_Setting_shortkeyhandle(void)
{
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}

void UI_Screen_Setting_holdshortkeyhandle(void)
{

}

void UI_Screen_Setting_holdlongkeyhandle(void)
{
}



void UI_Screen_Setting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    //gtSysCfg.notDisturbSwitch


    if(page_number==0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                if(gtSysCfg.notDisturbSwitch == SWITCH_OFF)
                {
                    gtSysCfg.notDisturbSwitch =SWITCH_ON;
                }
                else
                {
                    gtSysCfg.notDisturbSwitch =SWITCH_OFF;
                }
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {

                if(geBleState!=BLE_SLEEP)
                {
                    App_Protocal_BleStateSet(BLE_SLEEP);
                }
                else
                {
                    App_Protocal_BleStateSet(BLE_BROADCAST);
                }
                
                UI_Screen_draw_Screen();

            }
            break;
            default:
            break;
        }
    }
    else
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                
                UI_Set_Curr_ScreenID(Common_Screen_MainID_Setting_Brightness);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                UI_Set_Curr_ScreenID(Common_Screen_MainID_Setting_Infomation);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            break;
            default:
            break;
        }
        
    }


}

void UI_Screen_Setting_tpupslidehandle(void)
{

    if(page_number == 0)
    {
        page_number = 1;
        UI_Screen_draw_Screen();
    }

}

void UI_Screen_Setting_tpdownslidehandle(void)
{
    if(page_number == 1)
    {
        page_number = 0;
        UI_Screen_draw_Screen();
    }
}

void UI_Screen_Setting_tpleftslidehandle(void)
{
}

void UI_Screen_Setting_tprightslidehandle(void)
{

        UI_Set_Curr_ScreenID(Common_Screen_MainID_Modelist);
        UI_Screen_draw_Screen();
        
}


void UI_Screen_Setting_Infomation_Entry(void)
{


    
    UI_Screen_Setting_Infomation_Display();
    
    UI_Common_set_key_handle(UI_Screen_Setting_Infomation_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Setting_Infomation_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Setting_Infomation_tpupslidehandle,
                                    UI_Screen_Setting_Infomation_tpdownslidehandle,
                                    UI_Screen_Setting_Infomation_tpleftslidehandle,
                                    UI_Screen_Setting_Infomation_tprightslidehandle);
    
    
}


void UI_Screen_Setting_Infomation_Display(void)
{
   // uint32 VersionRead(void)
    uint8 u8MacAddr[6];
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    char info[32] = {0};
    uint8 sw[3] = {0};
    uint32 curr_sw = VersionRead();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Setting_Infomation)
        return;

    UI_Common_Clear_Screen(temp_ram);

    
    sw[0]=(curr_sw>>16&0x000000ff);
    sw[1]=(curr_sw>>8&0x000000ff);
    sw[2]=(curr_sw&0x000000ff);
        
    sprintf(info,"V%d.%d.%d",sw[0],sw[1],sw[2]);
    //UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t*)gchinesefont_setting_infomation_sw,info,1);

    UI_Common_AddBWsourcePic(temp_ram,0+8,0+8,(uint8_t*)gchinesefont_setting_infomation_sw,APP_COLOR_BLACK,APP_COLOR_WHITE);
    UI_Common_AddAsc2Str(temp_ram,0+8,0+34,(int8_t*)info,strlen(info),16,APP_COLOR_BLACK,APP_COLOR_WHITE);

    BLE_Stack_GetMac(u8MacAddr);
    sprintf(info,"%02x:%02x:%02x:%02x:%02x:%02x",u8MacAddr[0],u8MacAddr[1],u8MacAddr[2],u8MacAddr[3],u8MacAddr[4],u8MacAddr[5]);
    //UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t*)gchinesefont_setting_infomation_bt,info,1);
    UI_Common_AddBWsourcePic(temp_ram,0+8,59+8,(uint8_t*)gchinesefont_setting_infomation_bt,APP_COLOR_BLACK,APP_COLOR_WHITE);
    UI_Common_AddAsc2Str(temp_ram,0+8,59+34,(int8_t*)info,strlen(info),16,APP_COLOR_BLACK,APP_COLOR_WHITE);

    
    UI_Display_Prepare(temp_ram);
}



void UI_Screen_Setting_Infomation_Exit(void)
{


}


void UI_Screen_Setting_Infomation_shortkeyhandle(void)
{
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();


}

void UI_Screen_Setting_Infomation_holdshortkeyhandle(void)
{

}

void UI_Screen_Setting_Infomation_holdlongkeyhandle(void)
{
}



void UI_Screen_Setting_Infomation_tpclickhandle(int point_x,int point_y)
{


}

void UI_Screen_Setting_Infomation_tpupslidehandle(void)
{


}

void UI_Screen_Setting_Infomation_tpdownslidehandle(void)
{
}

void UI_Screen_Setting_Infomation_tpleftslidehandle(void)
{
}

void UI_Screen_Setting_Infomation_tprightslidehandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_Setting);
    UI_Screen_draw_Screen();
        
}



void UI_Screen_Setting_Brightness_Entry(void)
{


    UI_Screen_Setting_Brightness_Display();

    
    UI_Common_set_key_handle(UI_Screen_Setting_Brightness_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Setting_Brightness_tpclickhandle);
    
    UI_Common_set_tp_slide_handle(UI_Screen_Setting_Brightness_tpupslidehandle,
                                    UI_Screen_Setting_Brightness_tpdownslidehandle,
                                    UI_Screen_Setting_Brightness_tpleftslidehandle,
                                    UI_Screen_Setting_Brightness_tprightslidehandle);
    
    
}





void UI_Screen_Setting_Brightness_Draw_Progressbar(uint8_t *lcdram,int x, int y, int len, int height,uint8_t color,int curr_percent)
{

     int progress_len = len*curr_percent/100;

     UI_Common_Draw_Hline(lcdram,x,y,len,height,color,FALSE);
     UI_Common_Draw_Hline(lcdram,x,y,progress_len,height,color,TRUE);

}




void UI_Screen_Setting_Brightness_Display(void)
{

    int curr_percent = 0;
    char content[16];
    int len;

    eLcdBLGrade curr_value = UI_Common_Get_Blacklight_value();

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Setting_Brightness)
        return;

    UI_Common_Clear_Screen(temp_ram);
    

    switch(curr_value)
    {
        case eLcdBLGrade_0:
            curr_percent =0;
            break;
        case eLcdBLGrade_1:
            curr_percent =20;
            break;
        case eLcdBLGrade_2:
            curr_percent =40;
            break;
        case eLcdBLGrade_3:
            curr_percent =60;
            break;
        case eLcdBLGrade_4:
            curr_percent =80;
            break;
        case eLcdBLGrade_5:
            curr_percent =100;
            break;
        default:
            curr_percent =0;
            break;
    }

    sprintf(content,"%d",curr_percent);
    len = strlen(content);
    UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,8,30,160,24,APP_COLOR_WHITE,content,len,26,ENUM_TEXTBOX_CENTER);

    UI_Screen_Setting_Brightness_Draw_Progressbar(temp_ram,8, 80,160, 17,APP_COLOR_WHITE,curr_percent);
    
    UI_Common_AddBWsourcePic(temp_ram,4,122,(uint8_t*)iamge_bw_BtnHalf_h,APP_COLOR_BLACK,APP_COLOR_YELLOW);
    UI_Common_AddBWsourcePic(temp_ram,92,122,(uint8_t*)iamge_bw_BtnHalf_h,APP_COLOR_BLACK,APP_COLOR_CYAN);

    UI_Common_AddBWsourcePic(temp_ram,32,135,(uint8_t*)iamge_bw_minus_h,APP_COLOR_YELLOW,APP_COLOR_BLACK);
    UI_Common_AddBWsourcePic(temp_ram,120,135,(uint8_t*)iamge_bw_plus_h,APP_COLOR_CYAN,APP_COLOR_BLACK);

    
    UI_Display_Prepare(temp_ram);
    
}


void UI_Screen_Setting_Brightness_Exit(void)
{
}


void UI_Screen_Setting_Brightness_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}

void UI_Screen_Setting_Brightness_holdshortkeyhandle(void)
{
}

void UI_Screen_Setting_Brightness_holdlongkeyhandle(void)
{
}



void UI_Screen_Setting_Brightness_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    eLcdBLGrade curr_value = UI_Common_Get_Blacklight_value();


    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        
        break;
        case Enum_Common_ListScreen_Tprange_4:
        {
            if(curr_value != eLcdBLGrade_1)
            {
                curr_value=curr_value-10;
                UI_Common_Set_Blacklight_value(curr_value);
                UI_Screen_Setting_Brightness_Display();
                UI_Screen_Redraw_Screen();
            }
        
        }
        break;
        case Enum_Common_ListScreen_Tprange_5:
        {
            if(curr_value != eLcdBLGrade_5)
            {
                curr_value = curr_value + 10;
                UI_Common_Set_Blacklight_value(curr_value);
                UI_Screen_Setting_Brightness_Display();
                UI_Screen_Redraw_Screen();
            }
        
        }
        break;
        default:
        break;
    }


}


void UI_Screen_Setting_Brightness_tpupslidehandle(void)
{
}

void UI_Screen_Setting_Brightness_tpdownslidehandle(void)
{
}

void UI_Screen_Setting_Brightness_tpleftslidehandle(void)
{
}

void UI_Screen_Setting_Brightness_tprightslidehandle(void)
{

        UI_Set_Curr_ScreenID(Common_Screen_MainID_Setting);
        UI_Screen_draw_Screen();
        
}







