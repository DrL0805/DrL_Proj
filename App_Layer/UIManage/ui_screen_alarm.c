

#include "ui_screen_alarm.h"




static int page_number = 0;


int UI_Screen_Alarm_Get_State(void)
{

    uint8 total_count = Scene_Alarm_ValidNumRead();
    alarm_clock_t curr_info;
    int state = 0;
    int i;
    
    for(i = 0;i<total_count;i++)
    {
        Scene_Alarm_Read(&curr_info, i);
        state = state+curr_info.alarmswitch;
    }

    return state;
    
}



void UI_Screen_Alarm_Display(void)
{


    uint8 total_count = Scene_Alarm_ValidNumRead();
    alarm_clock_t curr_info;
    char content[16];
    int len;
    int image_w=0,image_h=0;
    int x = 8;
    int i;
    int offset_x = 0;    
    uint8_t* fontinfo;
    

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Alarm)
        return;

    UI_Common_Clear_Screen(temp_ram);

    
    if(total_count == 0)
    {
        UI_Common_AddBWsourcePic(temp_ram,72,54,(uint8_t*)image_alarm_outline_32_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        UI_Common_Draw_FontStr_textbox(temp_ram,8,98,160,24,(uint8_t *)gchinesefont_alarm_noalarm,APP_COLOR_WHITE,APP_COLOR_BLACK);
    }
    else
    {


        if(page_number == 0)
        {
        
            if(total_count>=1)
            {
                
                Scene_Alarm_Read(&curr_info, 0);
                
                sprintf(content,"%02d:%02d",curr_info.hour,curr_info.min);
                len = strlen(content);
                offset_x = 0;
                for(i=0;i<len;i++)
                {
                    fontinfo = UI_Common_GetNumberImageInfo_Bychar(content[i],&image_w,&image_h,26);
                    UI_Common_AddBWsourcePic(temp_ram,x+offset_x,17,(uint8_t*)fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);
                    offset_x = offset_x+fontinfo[0];
                }

                if(curr_info.alarmswitch == 0)
                {
                    UI_Common_AddPic(temp_ram,120,17,(uint8_t *)image_switcher_off_24_h);
                }
                else
                {
                    UI_Common_AddPic(temp_ram,120,17,(uint8_t *)image_switcher_on_24_h);
                }
            
            }

            
            if(total_count>=2)
            {
                
                Scene_Alarm_Read(&curr_info, 1);
                
                sprintf(content,"%02d:%02d",curr_info.hour,curr_info.min);
                len = strlen(content);
                offset_x = 0;
                for(i=0;i<len;i++)
                {
                    fontinfo = UI_Common_GetNumberImageInfo_Bychar(content[i],&image_w,&image_h,26);
                    UI_Common_AddBWsourcePic(temp_ram,x+offset_x,76,(uint8_t*)fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);
                    offset_x = offset_x+fontinfo[0];
                }
            
                if(curr_info.alarmswitch == 0)
                {
                    UI_Common_AddPic(temp_ram,120,76,(uint8_t *)image_switcher_off_24_h);
                }
                else
                {
                    UI_Common_AddPic(temp_ram,120,76,(uint8_t *)image_switcher_on_24_h);
                }
            
            }

            
            if(total_count>=3)
            {
                
                Scene_Alarm_Read(&curr_info, 2);
                
                sprintf(content,"%02d:%02d",curr_info.hour,curr_info.min);
                len = strlen(content);
                offset_x = 0;
                for(i=0;i<len;i++)
                {
                    fontinfo = UI_Common_GetNumberImageInfo_Bychar(content[i],&image_w,&image_h,26);
                    UI_Common_AddBWsourcePic(temp_ram,x+offset_x,135,(uint8_t*)fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);
                    offset_x = offset_x+fontinfo[0];
                }
            
                if(curr_info.alarmswitch == 0)
                {
                    UI_Common_AddPic(temp_ram,120,135,(uint8_t *)image_switcher_off_24_h);
                }
                else
                {
                    UI_Common_AddPic(temp_ram,120,135,(uint8_t *)image_switcher_on_24_h);
                }
            
            }
        
        }
#if 0
        else if(page_number == 1)
        {
            
            if(total_count>=4)
            {
                
                Scene_Alarm_Read(&curr_info, eMidAlarmGroup3);
            
                
                sprintf(content,"%02d:%02d",curr_info.hour,curr_info.min);
                len = strlen(content);
                offset_x = 0;
                for(i=0;i<len;i++)
                {
                    fontinfo = UI_Common_GetNumberImageInfo_Bychar(content[i],&image_w,&image_h,26);
                    UI_Common_AddBWsourcePic(temp_ram,x+offset_x,17,(uint8_t*)fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);
                    offset_x = offset_x+fontinfo[0];
                }
            
                if(curr_info.alarmswitch == 0)
                {
                    UI_Common_AddPic(temp_ram,120,17,(uint8_t *)image_switcher_off_24_h);
                }
                else
                {
                    UI_Common_AddPic(temp_ram,120,17,(uint8_t *)image_switcher_on_24_h);
                }
            
            }
            
            if(total_count>=5)
            {
                
                Scene_Alarm_Read(&curr_info, eMidAlarmGroup4);
            
                
                sprintf(content,"%02d:%02d",curr_info.hour,curr_info.min);
                len = strlen(content);
                offset_x = 0;
                for(i=0;i<len;i++)
                {
                    fontinfo = UI_Common_GetNumberImageInfo_Bychar(content[i],&image_w,&image_h,26);
                    UI_Common_AddBWsourcePic(temp_ram,x+offset_x,76,(uint8_t*)fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);
                    offset_x = offset_x+fontinfo[0];
                }
            
                if(curr_info.alarmswitch == 0)
                {
                    UI_Common_AddPic(temp_ram,120,76,(uint8_t *)image_switcher_off_24_h);
                }
                else
                {
                    UI_Common_AddPic(temp_ram,120,76,(uint8_t *)image_switcher_on_24_h);
                }
            
            }

        
        }

    #endif
    }


    UI_Display_Prepare(temp_ram);

}

void UI_Screen_Alarm_Entry(void)
{


    UI_Screen_Alarm_Display();
    
    UI_Common_set_key_handle(UI_Screen_Alarm_shortkeyhandle,NULL,NULL);

    
    UI_Common_set_tp_click_handle(UI_Screen_Alarm_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Alarm_tpupslidehandle,
                                    UI_Screen_Alarm_tpdownslidehandle,
                                    UI_Screen_Alarm_tpleftslidehandle,
                                    UI_Screen_Alarm_tprightslidehandle);
    
}

void UI_Screen_Alarm_Exit(void)
{

    page_number = 0;

}

void UI_Screen_Alarm_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    
    UI_Screen_draw_Screen();

}

void UI_Screen_Alarm_holdshortkeyhandle(void)
{
}

void UI_Screen_Alarm_holdlongkeyhandle(void)
{
}

void UI_Screen_Alarm_tpclickhandle(int point_x,int point_y)
{
        uint8 total_count = Scene_Alarm_ValidNumRead();
        Enum_Common_ListScreen_Tprange curr_range;
        alarm_clock_t curr_info;
        
        curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);
        
        if(total_count == 0)
            return;

        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                if(page_number ==0)
                {
                    Scene_Alarm_Read(&curr_info, 0);
                    
                    if(curr_info.alarmswitch == 0)
                    curr_info.alarmswitch =1;
                    else
                    curr_info.alarmswitch =0;
                    
                    RTT_DEBUG_printf(0,"switch = %d",curr_info.alarmswitch);
                    
                    Scene_Alarm_Write(&curr_info, 0);
                    
                    UI_Screen_draw_Screen();
                }
                
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                if(page_number ==0&&total_count>=2)
                {
                    Scene_Alarm_Read(&curr_info, 1);
                    if(curr_info.alarmswitch == 0)
                    curr_info.alarmswitch =1;
                    else
                    curr_info.alarmswitch =0;
                    Scene_Alarm_Write(&curr_info, 1);
                    
                    UI_Screen_draw_Screen();
                }
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                if(page_number ==0&&total_count>=3)
                {
                    Scene_Alarm_Read(&curr_info, 2);
                    if(curr_info.alarmswitch == 0)
                    curr_info.alarmswitch =1;
                    else
                    curr_info.alarmswitch =0;
                    
                    Scene_Alarm_Write(&curr_info, 2);
                    
                    UI_Screen_draw_Screen();
                }
            }
            break;
            default:
            break;
        }


}

void UI_Screen_Alarm_tpupslidehandle(void)
{

    uint8 total_count = Scene_Alarm_ValidNumRead();

    if(total_count>3)
    {
        if(page_number == 0)
        {
            page_number = 1;
            
            UI_Screen_draw_Screen();
        }
    }


}

void UI_Screen_Alarm_tpdownslidehandle(void)
{
    
    if(page_number == 1)
    {
        page_number = 0;
        
        UI_Screen_draw_Screen();
    }
    


}

void UI_Screen_Alarm_tpleftslidehandle(void)
{
}

void UI_Screen_Alarm_tprightslidehandle(void)
{

    UI_Screen_Alarm_Exit();

    UI_Set_Curr_ScreenID(Common_Screen_MainID_Modelist);
    UI_Screen_draw_Screen();

}

