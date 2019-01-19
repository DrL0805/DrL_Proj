

#include "ui_screen_stopwatch.h"
#include "ui_screen_dateandtime.h"

const uint8_t iamge_bw_stopwatch_h[] = {
24,24,
0x00, 0x00, 0x00, /* scanline 1 */
0x00, 0x7E, 0x00, /* scanline 2 */
0x00, 0x7E, 0x00, /* scanline 3 */
0x00, 0x00, 0x00, /* scanline 4 */
0x00, 0x7E, 0x00, /* scanline 5 */
0x01, 0xFF, 0xB0, /* scanline 6 */
0x03, 0xFF, 0xF0, /* scanline 7 */
0x07, 0xFF, 0xE0, /* scanline 8 */
0x0F, 0xE7, 0xF0, /* scanline 9 */
0x0F, 0xE7, 0xF0, /* scanline 10 */
0x1F, 0xE7, 0xF8, /* scanline 11 */
0x1F, 0xE7, 0xF8, /* scanline 12 */
0x1F, 0xE7, 0xF8, /* scanline 13 */
0x1F, 0xE7, 0xF8, /* scanline 14 */
0x1F, 0xFF, 0xF8, /* scanline 15 */
0x1F, 0xFF, 0xF8, /* scanline 16 */
0x0F, 0xFF, 0xF0, /* scanline 17 */
0x0F, 0xFF, 0xF0, /* scanline 18 */
0x07, 0xFF, 0xE0, /* scanline 19 */
0x03, 0xFF, 0xC0, /* scanline 20 */
0x01, 0xFF, 0x80, /* scanline 21 */
0x00, 0x7E, 0x00, /* scanline 22 */
0x00, 0x00, 0x00, /* scanline 23 */
0x00, 0x00, 0x00, /* scanline 24 */
};


void UI_Screen_Stopwatch_Goback()
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_Stopwatch);
    UI_Screen_draw_Screen();

}


void  UI_Screen_Stopwatch_Timerhandle(void)
{

    UI_Screen_Stopwatch_Display();

}




void UI_Screen_Stopwatch_Entry(void)
{

    SceneStopWatchParam_t* curr_info;

	curr_info = Scene_StopWatch_ParamPGet();


	
    if(curr_info->InitedFlg == FALSE)
    {
        Scene_StopWatch_Init();
    }

    if(curr_info->State == eStopWatchRuning)
    {

        //秒表 不允许进入大休眠
        UI_Commom_Set_Allow_Lockstate2(0);
        
        UI_Screen_Stopwatch_Timerhandle();
        UI_Common_set_timer_handle(UI_Screen_Stopwatch_Timerhandle);
        App_Lcd_HardTimerStart(50);
    }
    else
    {
        UI_Screen_Stopwatch_Display();
    }
    
    UI_Common_set_key_handle(UI_Screen_Stopwatch_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Stopwatch_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Stopwatch_tpupslidehandle,
                                    UI_Screen_Stopwatch_tpdownslidehandle,
                                    UI_Screen_Stopwatch_tpleftslidehandle,
                                    UI_Screen_Stopwatch_tprightslidehandle);
}


void UI_Screen_Stopwatch_Display(void)
{

    char content[16];
    int len;
    
    int min;
    int second;
    int ms;
    
    SceneStopWatchParam_t* curr_info;

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Stopwatch)
        return;

    UI_Common_Clear_Screen(temp_ram);


	curr_info = Scene_StopWatch_ParamPGet();

    if(curr_info->State == eStopWatchStop)
    {

        if(curr_info->MeasureCnt == 0)
        {
            UI_Common_AddBWsourcePic(temp_ram,76,16,(uint8_t*)iamge_bw_stopwatch_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }
        else
        {
            sprintf(content,"%d",curr_info->MeasureCnt);
            len = strlen(content);
            UI_Common_AddAsc2Str(temp_ram,72,8,(int8_t*)content,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
            UI_Common_AddBWsourcePic(temp_ram,88,8,(uint8_t*)gchinesefont_stopwatch_time,APP_COLOR_BLACK,APP_COLOR_WHITE);
            min = 0;
            second=0;
            ms= 0;
            sprintf(content,"%2d:%2d.%2d",min,second,ms);
            len = strlen(content);
            UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,8,30,160,20,APP_COLOR_WHITE,content,len,20,ENUM_TEXTBOX_CENTER);
        }

        min = curr_info->TotalMs/1000/60;
        second= curr_info->TotalMs/1000%60;
        ms= curr_info->TotalMs/10%100;
        sprintf(content,"%2d:%2d.%2d",min,second,ms);
        len = strlen(content);
        UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,8,70,160,36,APP_COLOR_WHITE,content,len,36,ENUM_TEXTBOX_CENTER);
        
        //UI_Common_AddPic(lcdram,4,122,(uint8_t*)BtnFullCyan_h);
        UI_Common_AddBWsourcePic(temp_ram,4,122,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
        
        UI_Common_Draw_FontStr_textbox(temp_ram,0,118,176,58,(uint8_t *)gchinesefont_stopwatch_start,APP_COLOR_BLACK,APP_COLOR_CYAN);
    
    }
    else if(curr_info->State == eStopWatchRuning)
    {

        if(curr_info->MeasureCnt == 0)
        {
            UI_Common_AddBWsourcePic(temp_ram,76,16,(uint8_t*)iamge_bw_stopwatch_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }
        else
        {
            sprintf(content,"%d",curr_info->MeasureCnt);
            len = strlen(content);
            UI_Common_AddAsc2Str(temp_ram,72,8,(int8_t*)content,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
            UI_Common_AddBWsourcePic(temp_ram,88,8,(uint8_t*)gchinesefont_stopwatch_time,APP_COLOR_BLACK,APP_COLOR_WHITE);
            min = curr_info->MeasurePoint[curr_info->MeasureCnt-1]/1000/60;
            second= curr_info->MeasurePoint[curr_info->MeasureCnt-1]/1000%60;
            ms= curr_info->MeasurePoint[curr_info->MeasureCnt-1]/10%100;
            sprintf(content,"%2d:%2d.%2d",min,second,ms);
            len = strlen(content);
            UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,8,30,160,20,APP_COLOR_WHITE,content,len,20,ENUM_TEXTBOX_CENTER);
        } 

        min = curr_info->TotalMs/1000/60;
        second= curr_info->TotalMs/1000%60;
        ms= curr_info->TotalMs/10%100;
        sprintf(content,"%2d:%2d.%2d",min,second,ms);
        len = strlen(content);
        UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,8,70,160,36,APP_COLOR_WHITE,content,len,36,ENUM_TEXTBOX_CENTER);

    
        //UI_Common_AddPic(lcdram,4,122,(uint8_t*)BtnHalfCyan_h);
        //UI_Common_AddPic(lcdram,92,122,(uint8_t*)BtnHalfCyan_h);

        UI_Common_AddBWsourcePic(temp_ram,4,122,(uint8_t*)iamge_bw_BtnHalf_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
        UI_Common_AddBWsourcePic(temp_ram,92,122,(uint8_t*)iamge_bw_BtnHalf_h,APP_COLOR_BLACK,APP_COLOR_YELLOW);

        
        UI_Common_Draw_FontStr_textbox(temp_ram,8,135,72,24,(uint8_t *)gchinesefont_stopwatch_metering,APP_COLOR_BLACK,APP_COLOR_CYAN);
        UI_Common_Draw_FontStr_textbox(temp_ram,96,135,72,24,(uint8_t *)gchinesefont_stopwatch_pause,APP_COLOR_BLACK,APP_COLOR_YELLOW);
    
    }
    else
    {
    
        //UI_Common_AddPic(lcdram,4,4,(uint8_t*)BtnFullCyan_h);
        UI_Common_AddBWsourcePic(temp_ram,4,4,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
        
        UI_Common_Draw_FontStr_textbox(temp_ram,8,17,160,24,(uint8_t *)gchinesefont_stopwatch_examine,APP_COLOR_BLACK,APP_COLOR_CYAN);

        min = curr_info->TotalMs/1000/60;
        second= curr_info->TotalMs/1000%60;
        ms= curr_info->TotalMs/10%100;
        sprintf(content,"%2d:%2d.%2d",min,second,ms);
        len = strlen(content);
        UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,8,70,160,36,APP_COLOR_WHITE,content,len,36,ENUM_TEXTBOX_CENTER);

        //UI_Common_AddPic(lcdram,4,122,(uint8_t*)BtnHalfRed_h);
        //UI_Common_AddPic(lcdram,92,122,(uint8_t*)BtnHalfCyan_h);
        
        UI_Common_AddBWsourcePic(temp_ram,4,122,(uint8_t*)iamge_bw_BtnHalf_h,APP_COLOR_BLACK,APP_COLOR_RED);
        UI_Common_AddBWsourcePic(temp_ram,92,122,(uint8_t*)iamge_bw_BtnHalf_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
        
        
        UI_Common_Draw_FontStr_textbox(temp_ram,8,135,72,24,(uint8_t *)gchinesefont_stopwatch_reset,APP_COLOR_BLACK,APP_COLOR_RED);
        UI_Common_Draw_FontStr_textbox(temp_ram,96,135,72,24,(uint8_t *)gchinesefont_stopwatch_continue,APP_COLOR_BLACK,APP_COLOR_CYAN);
    
    }

    
    UI_Display_Prepare(temp_ram);

}


void UI_Screen_Stopwatch_Exit(void)
{

    //退出后，允许进入大休眠
    UI_Commom_Set_Allow_Lockstate2(1);

}


void UI_Screen_Stopwatch_shortkeyhandle(void)
{

        SceneStopWatchParam_t* curr_info;
        curr_info = Scene_StopWatch_ParamPGet();

        if(curr_info->State == eStopWatchStop)
        {
            Scene_StopWatch_Start();
            //秒表 不允许进入大休眠
            UI_Commom_Set_Allow_Lockstate2(0);
            
            //硬件计时，定时执�?
            UI_Screen_Stopwatch_Timerhandle();
            UI_Common_set_timer_handle(UI_Screen_Stopwatch_Timerhandle);
            App_Lcd_HardTimerStart(60);
        }
        else if(curr_info->State == eStopWatchRuning)
        {
        
            UI_Common_set_timer_handle(NULL);
            App_Lcd_HardTimerStop();
            
            Scene_StopWatch_Suspend();
            UI_Screen_draw_Screen();
            
        }
        else
        {
        
            Scene_StopWatch_Start();
            UI_Screen_Stopwatch_Timerhandle();
            UI_Common_set_timer_handle(UI_Screen_Stopwatch_Timerhandle);
            App_Lcd_HardTimerStart(60);
            
        }


}

void UI_Screen_Stopwatch_holdshortkeyhandle(void)
{




}

void UI_Screen_Stopwatch_holdlongkeyhandle(void)
{
}



void UI_Screen_Stopwatch_tpclickhandle(int point_x,int point_y)
{

    SceneStopWatchParam_t* curr_info;
    Enum_Common_ListScreen_Tprange curr_range;
//    uint32_t result;

	curr_info = Scene_StopWatch_ParamPGet();
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(curr_info->State == eStopWatchStop)
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
                Scene_StopWatch_Start();
                //秒表 不允许进入大休眠
                UI_Commom_Set_Allow_Lockstate2(0);
                //硬件计时，定时执�?
                UI_Screen_Stopwatch_Timerhandle();
                UI_Common_set_timer_handle(UI_Screen_Stopwatch_Timerhandle);
                App_Lcd_HardTimerStart(60);
            }
            break;
            default:
            break;
        }
    }
    else if(curr_info->State == eStopWatchRuning)
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
            {
                Scene_StopWatch_MeasureMark();
            }
            break;
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Common_set_timer_handle(NULL);
                App_Lcd_HardTimerStop();
                
                Scene_StopWatch_Suspend();
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
                //UI_Common_set_timer_handle(NULL);
                //App_Lcd_HardTimerStop();
                UI_Set_Curr_ScreenID(Common_Screen_MainID_Stopwatch_Detail);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
        
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            {
                //UI_Common_set_timer_handle(NULL);
                //App_Lcd_HardTimerStop();

                //重置后，允许进入大休眠
                UI_Commom_Set_Allow_Lockstate2(1);
                
                Scene_StopWatch_Reset();
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_5:
            {
            
                Scene_StopWatch_Start();
                UI_Screen_Stopwatch_Timerhandle();
                UI_Common_set_timer_handle(UI_Screen_Stopwatch_Timerhandle);
                App_Lcd_HardTimerStart(60);
                
            }
            break;
            default:
            break;
        }
    }


}

void UI_Screen_Stopwatch_tpupslidehandle(void)
{
}

void UI_Screen_Stopwatch_tpdownslidehandle(void)
{


}

void UI_Screen_Stopwatch_tpleftslidehandle(void)
{
}

void UI_Screen_Stopwatch_tprightslidehandle(void)
{


        SceneStopWatchParam_t* curr_info;
	    curr_info = Scene_StopWatch_ParamPGet();
        
        if(curr_info->State == eStopWatchStop)
        {
            UI_Screen_Stopwatch_Exit();
            UI_Set_Curr_ScreenID(Common_Screen_MainID_Modelist);
            UI_Screen_draw_Screen();
        }
        else
        {
            UI_Screen_Stopwatch_Exit();
            UI_Set_Go_back_handle(UI_Screen_Stopwatch_Goback);
            UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
            UI_Screen_draw_Screen();
        }

}


extern ui_common_page_info_s detail_page_info;

void UI_Screen_Stopwatch_Detail_Entry(void)
{

    detail_page_info.curr_page_number = 0;
    
    UI_Screen_Stopwatch_Detail_Display();
    UI_Common_set_key_handle(UI_Screen_Stopwatch_Detail_shortkeyhandle,NULL,NULL);
    
    UI_Common_set_tp_click_handle(UI_Screen_Stopwatch_Detail_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Stopwatch_Detail_tpupslidehandle,
                                    UI_Screen_Stopwatch_Detail_tpdownslidehandle,
                                    UI_Screen_Stopwatch_Detail_tpleftslidehandle,
                                    UI_Screen_Stopwatch_Detail_tprightslidehandle);
    
}


void UI_Screen_Stopwatch_Detail_Display(void)
{

    char content[16];
    int len;
    
    int min;
    int second;
    int ms;


    int width;
    int height;
    int total_width = 0;
    int x;

    int temp_value;
    
    SceneStopWatchParam_t* curr_info;
	curr_info = Scene_StopWatch_ParamPGet();

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Stopwatch_Detail)
        return;

    UI_Common_Clear_Screen(temp_ram);

    detail_page_info.total_page_number = curr_info->MeasureCnt/4+1;

    //首页
    if(detail_page_info.curr_page_number == 0)
    {

        //title
        min = curr_info->TotalMs/1000/60;
        second= curr_info->TotalMs/1000%60;
        ms= curr_info->TotalMs/10%100;
        sprintf(content,"%02d:%02d.%02d",min,second,ms);
        len = strlen(content);
        //UI_Common_Draw_NumberImage_textbox_Bystringinfo(lcdram,8,70,160,36,APP_COLOR_WHITE,content,len,36);
        UI_Common_Draw_AscStr_textbox(temp_ram,8,8,160,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_CENTER);
        
        sprintf(content,"%d",curr_info->MeasureCnt);
        len = strlen(content);
        UI_Common_GetAsc2Str_info((int8_t*)content,len,12,&width,&height);
        total_width = total_width + width;
        total_width = total_width + gchinesefont_stopwatch_detail_have_12[0] + gchinesefont_stopwatch_detail_time_12[0];
        x = (160-total_width)/2+8;
        UI_Common_AddBWsourcePic(temp_ram,x-2,32,(uint8_t*)gchinesefont_stopwatch_detail_have_12,APP_COLOR_BLACK,APP_COLOR_WHITE);
        x = x+gchinesefont_stopwatch_detail_have_12[0];
        UI_Common_AddAsc2Str(temp_ram,x,30,(int8_t*)content,len,12,APP_COLOR_BLACK,APP_COLOR_WHITE);
        x = x+width;
        UI_Common_AddBWsourcePic(temp_ram,x+2,32,(uint8_t*)gchinesefont_stopwatch_detail_time_12,APP_COLOR_BLACK,APP_COLOR_WHITE);

        total_width = 0;
    }
    else
    {
        //数据
        temp_value = curr_info->MeasureCnt - detail_page_info.curr_page_number*4+1;
        if(temp_value>0)
        {
            sprintf(content,"%d",temp_value);
            len = strlen(content);
            UI_Common_GetAsc2Str_info((int8_t*)content,len,16,&width,&height);
            total_width = total_width + width;
            total_width = total_width + gchinesefont_stopwatch_detail_first_16[0] + gchinesefont_stopwatch_detail_time_16[0];
            x = 76-total_width;
            UI_Common_AddBWsourcePic(temp_ram,x,18,(uint8_t*)gchinesefont_stopwatch_detail_first_16,APP_COLOR_BLACK,APP_COLOR_WHITE);
            x = x+gchinesefont_stopwatch_detail_first_16[0];
            UI_Common_AddAsc2Str(temp_ram,x,18,(int8_t*)content,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
            x = x+width;
            UI_Common_AddBWsourcePic(temp_ram,x,18,(uint8_t*)gchinesefont_stopwatch_detail_time_16,APP_COLOR_BLACK,APP_COLOR_WHITE);
            total_width = 0;
        
            UI_Common_AddBWsourcePic(temp_ram,84,22,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
            
            min = curr_info->MeasurePoint[temp_value-1]/1000/60;
            second= curr_info->MeasurePoint[temp_value-1]/1000%60;
            ms= curr_info->MeasurePoint[temp_value-1]/10%100;
            sprintf(content,"%02d:%02d.%02d",min,second,ms);
            len = strlen(content);
            UI_Common_AddAsc2Str(temp_ram,100,18,(int8_t*)content,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }
    
    }

    //数据
    temp_value = curr_info->MeasureCnt-detail_page_info.curr_page_number*4;
    if(temp_value>0)
    {
        sprintf(content,"%d",temp_value);
        len = strlen(content);
        UI_Common_GetAsc2Str_info((int8_t*)content,len,16,&width,&height);
        total_width = total_width + width;
        total_width = total_width + gchinesefont_stopwatch_detail_first_16[0] + gchinesefont_stopwatch_detail_time_16[0];
        
        x = 76-total_width;
        UI_Common_AddBWsourcePic(temp_ram,x,59,(uint8_t*)gchinesefont_stopwatch_detail_first_16,APP_COLOR_BLACK,APP_COLOR_WHITE);
        x = x+gchinesefont_stopwatch_detail_first_16[0];
        UI_Common_AddAsc2Str(temp_ram,x,59,(int8_t*)content,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
        x = x+width;
        UI_Common_AddBWsourcePic(temp_ram,x,59,(uint8_t*)gchinesefont_stopwatch_detail_time_16,APP_COLOR_BLACK,APP_COLOR_WHITE);
        total_width = 0;
            
        UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
        
        min = curr_info->MeasurePoint[temp_value-1]/1000/60;
        second= curr_info->MeasurePoint[temp_value-1]/1000%60;
        ms= curr_info->MeasurePoint[temp_value-1]/10%100;
        sprintf(content,"%02d:%02d.%02d",min,second,ms);
        len = strlen(content);
        UI_Common_AddAsc2Str(temp_ram,100,59,(int8_t*)content,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
    }

    //数据
    temp_value = curr_info->MeasureCnt-detail_page_info.curr_page_number*4 - 1;
    if(temp_value>0)
    {
        sprintf(content,"%d",temp_value);
        len = strlen(content);
        UI_Common_GetAsc2Str_info((int8_t*)content,len,16,&width,&height);
        total_width = total_width + width;
        total_width = total_width + gchinesefont_stopwatch_detail_first_16[0] + gchinesefont_stopwatch_detail_time_16[0];
        
        x = 76-total_width;
        UI_Common_AddBWsourcePic(temp_ram,x,101,(uint8_t*)gchinesefont_stopwatch_detail_first_16,APP_COLOR_BLACK,APP_COLOR_WHITE);
        x = x+gchinesefont_stopwatch_detail_first_16[0];
        UI_Common_AddAsc2Str(temp_ram,x,101,(int8_t*)content,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
        x = x+width;
        UI_Common_AddBWsourcePic(temp_ram,x,101,(uint8_t*)gchinesefont_stopwatch_detail_time_16,APP_COLOR_BLACK,APP_COLOR_WHITE);
        total_width = 0;
        
        UI_Common_AddBWsourcePic(temp_ram,84,105,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
        
        min = curr_info->MeasurePoint[temp_value-1]/1000/60;
        second= curr_info->MeasurePoint[temp_value-1]/1000%60;
        ms= curr_info->MeasurePoint[temp_value-1]/10%100;
        sprintf(content,"%02d:%02d.%02d",min,second,ms);
        len = strlen(content);
        UI_Common_AddAsc2Str(temp_ram,100,101,(int8_t*)content,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
    }


    //数据
    temp_value = curr_info->MeasureCnt-detail_page_info.curr_page_number*4-2;
    if(temp_value>0)
    {
        sprintf(content,"%d",temp_value);
        len = strlen(content);
        UI_Common_GetAsc2Str_info((int8_t*)content,len,16,&width,&height);
        total_width = total_width + width;
        total_width = total_width + gchinesefont_stopwatch_detail_first_16[0] + gchinesefont_stopwatch_detail_time_16[0];
        x = 76-total_width;
        UI_Common_AddBWsourcePic(temp_ram,x,142,(uint8_t*)gchinesefont_stopwatch_detail_first_16,APP_COLOR_BLACK,APP_COLOR_WHITE);
        x = x+gchinesefont_stopwatch_detail_first_16[0];
        UI_Common_AddAsc2Str(temp_ram,x,142,(int8_t*)content,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
        x = x+width;
        UI_Common_AddBWsourcePic(temp_ram,x,142,(uint8_t*)gchinesefont_stopwatch_detail_time_16,APP_COLOR_BLACK,APP_COLOR_WHITE);
        total_width = 0;
    
        UI_Common_AddBWsourcePic(temp_ram,84,146,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
        
        //title
        min = curr_info->MeasurePoint[temp_value-1]/1000/60;
        second= curr_info->MeasurePoint[temp_value-1]/1000%60;
        ms= curr_info->MeasurePoint[temp_value-1]/10%100;
        sprintf(content,"%02d:%02d.%02d",min,second,ms);
        len = strlen(content);
        UI_Common_AddAsc2Str(temp_ram,100,142,(int8_t*)content,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
        
    }
    
    
    UI_Display_Prepare(temp_ram);

}


void UI_Screen_Stopwatch_Detail_Exit(void)
{
    

}


void UI_Screen_Stopwatch_Detail_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_Stopwatch);
    UI_Screen_draw_Screen();

}


void UI_Screen_Stopwatch_Detail_tpclickhandle(int point_x,int point_y)
{
    
}



void UI_Screen_Stopwatch_Detail_tpupslidehandle(void)
{

    UI_Common_Detail_Next_Page();
    UI_Screen_Stopwatch_Detail_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_Stopwatch_Detail_tpdownslidehandle(void)
{

    UI_Common_Detail_Pre_Page();
    UI_Screen_Stopwatch_Detail_Display();
    UI_Screen_Redraw_Screen();
    
}

void UI_Screen_Stopwatch_Detail_tpleftslidehandle(void)
{
}

void UI_Screen_Stopwatch_Detail_tprightslidehandle(void)
{


    UI_Set_Curr_ScreenID(Common_Screen_MainID_Stopwatch);
    UI_Screen_draw_Screen();


}







