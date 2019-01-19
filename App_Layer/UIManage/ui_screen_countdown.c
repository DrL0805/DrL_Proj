

#include "ui_screen_countdown.h"
#include "ui_screen_dateandtime.h"


static int countdown_hour = 0;
static int countdown_min = 0;
//static int countdown_second = 0;


void UI_Screen_Countdown_Goback()
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_Countdown);
    UI_Screen_draw_Screen();

}

void  UI_Screen_Countdown_Timerhandle()
{

    UI_Screen_Countdown_Display();

    UI_Common_set_timer_handle(UI_Screen_Countdown_Timerhandle);
    App_Lcd_TimerStart(1000);

}

void UI_Screen_Countdown_Entry(void)
{


    SceneCountDownParam_t* curr_info;

	curr_info = Scene_Countdown_ParamPGet();

    if(curr_info->State == eCountDownRuning)
    {
        //计时器 不允许进入大休眠
        UI_Commom_Set_Allow_Lockstate2(0);
        UI_Screen_Countdown_Timerhandle();

    }
    else
    {
        UI_Screen_Countdown_Display();
    }


    UI_Screen_Countdown_Display();

    UI_Common_set_key_handle(UI_Screen_Countdown_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Countdown_tpclickhandle);
    
    UI_Common_set_tp_slide_handle(UI_Screen_Countdown_tpupslidehandle,
                                    UI_Screen_Countdown_tpdownslidehandle,
                                    UI_Screen_Countdown_tpleftslidehandle,
                                    UI_Screen_Countdown_tprightslidehandle);

}


void UI_Screen_Countdown_Display()
{

    MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
    SceneCountDownParam_t* curr_info;
    char content[16];
    int len;
    
    int hour;
    int min;
    int second;
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    SysTimeType_e curr_type = App_Var_SysTimeTypeGet();
    ui_common_time_12hour_s curr_12hour_time = {0};
    
    UI_Common_Clear_Screen(temp_ram);

    

	curr_info = Scene_Countdown_ParamPGet();


    if(curr_info->State == eCountDownStop)
    {
        //图片
        UI_Common_AddPic(temp_ram,16,18,(uint8_t*)minus_h);
        UI_Common_AddPic(temp_ram,136,18,(uint8_t*)plus_h);
        UI_Common_AddPic(temp_ram,16,77,(uint8_t*)minus_h);
        UI_Common_AddPic(temp_ram,136,77,(uint8_t*)plus_h);
        
        UI_Common_AddBWsourcePic(temp_ram,4,122,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
        
        sprintf(content,"%2d",countdown_hour);
        len = strlen(content);
        UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,58,4,62,36,APP_COLOR_WHITE,content,len,36,ENUM_TEXTBOX_CENTER);


        sprintf(content,"%2d",countdown_min);
        len = strlen(content);
        UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,58,63,62,36,APP_COLOR_WHITE,content,len,36,ENUM_TEXTBOX_CENTER);

       //字
        UI_Common_AddBWsourcePic(temp_ram,82,44,(uint8_t*)gchinesefont_sportscene_hour,APP_COLOR_BLACK,APP_COLOR_WHITE);
        UI_Common_AddBWsourcePic(temp_ram,82,103,(uint8_t*)gchinesefont_sportscene_minute,APP_COLOR_BLACK,APP_COLOR_WHITE);
        UI_Common_Draw_FontStr_textbox(temp_ram,0,118,176,58,(uint8_t *)gchinesefont_stopwatch_start,APP_COLOR_BLACK,APP_COLOR_CYAN);
        
    
    }
    else if(curr_info->State == eCountDownRuning)
    {

        hour = curr_info->RemainSec/3600;
        min = curr_info->RemainSec%3600/60;
        second= curr_info->RemainSec%60;

        sprintf(content,"%02d:%02d:%02d",hour,min,second);
        len = strlen(content);
        UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,8,70,160,36,APP_COLOR_WHITE,content,len,36,ENUM_TEXTBOX_CENTER);


        if(curr_type == SYS_TIME_24_TYPE)
        {
            sprintf(content,"%02d:%02d",lMidRTC->RTC.hour,lMidRTC->RTC.min);
            len = strlen(content);
            UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,8,11,160,36,APP_COLOR_WHITE,content,len,26,ENUM_TEXTBOX_CENTER);
        }
        else
        {
        
            UI_Common_Get_Time_12hour(&curr_12hour_time);
            
            //14-80
            if(curr_12hour_time.is_am ==1)
            {
                sprintf(content,"%02d:%02d AM",curr_12hour_time.hour,curr_12hour_time.min);
            }
            else
            {
                sprintf(content,"%02d:%02d PM",curr_12hour_time.hour,curr_12hour_time.min);
            }
            len = strlen(content);
            UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,8,11,160,36,APP_COLOR_WHITE,content,len,26,ENUM_TEXTBOX_CENTER);
        }


        
    
        //UI_Common_AddPic(lcdram,4,63,(uint8_t*)BtnFullRed_h);
        //UI_Common_AddBWsourcePic(temp_ram,4,63,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_RED);
        //UI_Common_AddPic(lcdram,4,122,(uint8_t*)BtnFullCyan_h);
        UI_Common_AddBWsourcePic(temp_ram,4,122,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_RED);
        
        //UI_Common_Draw_FontStr_textbox(temp_ram,8,76,160,24,(uint8_t *)gchinesefont_countdown_end,APP_COLOR_BLACK,APP_COLOR_RED);
        UI_Common_Draw_FontStr_textbox(temp_ram,8,135,160,24,(uint8_t *)gchinesefont_stopwatch_pause,APP_COLOR_BLACK,APP_COLOR_RED);

    }
    else
    {

        hour = curr_info->RemainSec/3600;
        min = curr_info->RemainSec%3600/60;
        second= curr_info->RemainSec%60;
        
        sprintf(content,"%2d:%2d:%2d",hour,min,second);
        len = strlen(content);
        UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,8,70,160,36,APP_COLOR_WHITE,content,len,36,ENUM_TEXTBOX_CENTER);
        
        
        //UI_Common_AddPic(lcdram,4,63,(uint8_t*)BtnFullRed_h);
        UI_Common_AddBWsourcePic(temp_ram,4,4,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_RED);
        //UI_Common_AddPic(lcdram,4,122,(uint8_t*)BtnFullCyan_h);
        UI_Common_AddBWsourcePic(temp_ram,4,122,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
        
        UI_Common_Draw_FontStr_textbox(temp_ram,8,17,160,24,(uint8_t *)gchinesefont_stopwatch_reset,APP_COLOR_BLACK,APP_COLOR_RED);
        UI_Common_Draw_FontStr_textbox(temp_ram,8,135,160,24,(uint8_t *)gchinesefont_stopwatch_continue,APP_COLOR_BLACK,APP_COLOR_CYAN);

    }

    
    UI_Display_Prepare(temp_ram);

}


void UI_Screen_Countdown_Exit(void)
{


}


void UI_Screen_Countdown_shortkeyhandle(void)
{

        
        SceneCountDownParam_t* curr_info;

		curr_info = Scene_Countdown_ParamPGet();

        if(curr_info->State == eCountDownStop)
        {

            if(countdown_min!=0||countdown_hour!=0)
            {
                Scene_Countdown_Start();

                //计时器 不允许进入大休眠
                UI_Commom_Set_Allow_Lockstate2(0);
                
                Scene_Countdown_TimeWrite(countdown_hour*3600+countdown_min*60);
                //保存设置的值不清空
                //countdown_min = 0;
                //countdown_hour = 0;
                UI_Screen_Countdown_Timerhandle();
                UI_Screen_Redraw_Screen();
            }

        }
        else if(curr_info->State == eCountDownRuning)
        {
        
            UI_Common_set_timer_handle(NULL);
            Scene_Countdown_Suspend();
            UI_Screen_Countdown_Display();
            UI_Screen_Redraw_Screen();
        }
        else
        {
        
            UI_Screen_Countdown_Timerhandle();
            Scene_Countdown_Start();
            
        }




}

void UI_Screen_Countdown_holdshortkeyhandle(void)
{

}

void UI_Screen_Countdown_holdlongkeyhandle(void)
{
}



void UI_Screen_Countdown_tpclickhandle(int point_x,int point_y)
{

    SceneCountDownParam_t* curr_info;
    Enum_Common_ListScreen_Tprange curr_range;

	curr_info = Scene_Countdown_ParamPGet();
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(curr_info->State == eCountDownStop)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            {
                if(countdown_hour>0)
                {
                    countdown_hour = countdown_hour -1;
                }
                else
                {
                    countdown_hour = 23;
                }
                UI_Screen_Countdown_Display();
                UI_Screen_Redraw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_1:
            {
                if(countdown_hour<23)
                {
                    countdown_hour = countdown_hour +1;
                }
                else
                {
                    countdown_hour = 0;
                }
                UI_Screen_Countdown_Display();
                App_Lcd_TimerStart(10);
                
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            {
                if(countdown_min>0)
                {
                    countdown_min = countdown_min -1;
                }
                else
                {
                    countdown_min = 59;
                }
                
                UI_Screen_Countdown_Display();
                UI_Screen_Redraw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                if(countdown_min<59)
                {
                    countdown_min = countdown_min +1;
                }
                else
                {
                    countdown_min = 0;
                }
                
                UI_Screen_Countdown_Display();
                UI_Screen_Redraw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                if(countdown_min!=0||countdown_hour!=0)
                {
                    Scene_Countdown_Start();
                    //计时器 不允许进入大休眠
                    UI_Commom_Set_Allow_Lockstate2(0);
                    Scene_Countdown_TimeWrite(countdown_min*60+countdown_hour*3600);
                    //保存设置的值不清空
                    //countdown_min = 0;
                    //countdown_hour = 0;
                    UI_Screen_Countdown_Timerhandle();
                    UI_Screen_Redraw_Screen();
                    
                }
                
            }
            break;
            default:
            break;
        }
        
    }
    else if(curr_info->State == eCountDownRuning)
    {
    
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
        
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Common_set_timer_handle(NULL);
                Scene_Countdown_Suspend();
                UI_Screen_Countdown_Display();
                UI_Screen_Redraw_Screen();
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
                //退出后，允许进入大休眠
                UI_Commom_Set_Allow_Lockstate2(1);
                UI_Common_set_timer_handle(NULL);
                Scene_Countdown_Reset();
                UI_Screen_Countdown_Display();
                UI_Screen_Redraw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                Scene_Countdown_Start();
                UI_Screen_Countdown_Timerhandle();
                UI_Screen_Redraw_Screen();
            }
            break;
            default:
            break;
        }
    }


}

void UI_Screen_Countdown_tpupslidehandle(void)
{
}

void UI_Screen_Countdown_tpdownslidehandle(void)
{

}

void UI_Screen_Countdown_tpleftslidehandle(void)
{
}

void UI_Screen_Countdown_tprightslidehandle(void)
{
        SceneCountDownParam_t* curr_info;

		curr_info = Scene_Countdown_ParamPGet();
        
        if(curr_info->State == eCountDownStop)
        {
            //退出后，允许进入大休眠
            UI_Commom_Set_Allow_Lockstate2(1);
        
            UI_Set_Curr_ScreenID(Common_Screen_MainID_Modelist);
            UI_Screen_draw_Screen();
        }
        else
        {

            UI_Set_Go_back_handle(UI_Screen_Countdown_Goback);
            //退出后，允许进入大休眠
            UI_Commom_Set_Allow_Lockstate2(1);
            UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
            UI_Screen_draw_Screen();
        }

}














