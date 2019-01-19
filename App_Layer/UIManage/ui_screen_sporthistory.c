
#include "ui_screen_sporthistory.h"

extern ui_common_page_info_s curr_page_info;
extern ui_common_page_info_s detail_page_info;

void UI_Screen_SportHistory_Display(void)
{

    StoreHistoryParam_t* info;
    //StoreHistoryList_t* info_detail;
    char content[32];
    int len;
    rtc_time_s rtc_time;
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    float temp_f;

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_SportHistory)
        return;

    UI_Common_Clear_Screen(temp_ram);

    info = Store_History_ParamPGet();


    if(info->ListCnt == 0)
    {
        UI_Common_AddBWsourcePic(temp_ram,72,54,(uint8_t*)image_page_outline_32_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        UI_Common_Draw_FontStr_textbox(temp_ram,8,98,160,24,(uint8_t *)gchinesefont_sportscene_nohistory,APP_COLOR_WHITE,APP_COLOR_BLACK);
    }
    else
    {

    
        if(info->ListCnt - curr_page_info.curr_page_number*3>=1)
        {

            //info_detail = Store_History_ListPGet(curr_page_info.curr_page_number*3);
                
            if(info->ListBuf[curr_page_info.curr_page_number*3].DataClassify == eDataClassifyRunNew)
            {
                //UI_Common_AddBWsourcePic(temp_ram,8,11,(uint8_t*)image_sportmode_run_24_h,APP_COLOR_BLACK,APP_COLOR_GREEN);

                UI_Common_AddPic(temp_ram,8,11,(uint8_t*)run_h);
            }
            else if(info->ListBuf[curr_page_info.curr_page_number*3].DataClassify == eDataClassifyClimbNew)
            {
                //UI_Common_AddBWsourcePic(temp_ram,8,11,(uint8_t*)image_sportmode_climb_24_h,APP_COLOR_BLACK,APP_COLOR_GREEN);

                UI_Common_AddPic(temp_ram,8,11,(uint8_t*)climb_h);
            }
            else if(info->ListBuf[curr_page_info.curr_page_number*3].DataClassify == eDataClassifySwimNew)
            {
                UI_Common_AddPic(temp_ram,8,11,(uint8_t*)swim_h);
            }

            UtcTransformTime(info->ListBuf[curr_page_info.curr_page_number*3].UTC, &rtc_time);
            sprintf(content,"%02d-%02d-%02d",rtc_time.year,rtc_time.month,rtc_time.day);
            len = strlen(content);

            UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,52,6,116,26,APP_COLOR_WHITE,content,len,26,ENUM_TEXTBOX_LEFT);

            temp_f = (float)info->ListBuf[curr_page_info.curr_page_number*3].Distance/1000;
            //memset(string_content,0,16);
            sprintf(content,"%0.2fkm",temp_f);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,52,34,160,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            
        }

        if( info->ListCnt - curr_page_info.curr_page_number*3>=2)
        {
        
            //info_detail = Store_History_ListPGet(curr_page_info.curr_page_number*3+1);
                
            if(info->ListBuf[curr_page_info.curr_page_number*3+1].DataClassify == eDataClassifyRunNew)
            {
                //UI_Common_AddBWsourcePic(temp_ram,8,11,(uint8_t*)image_sportmode_run_24_h,APP_COLOR_BLACK,APP_COLOR_GREEN);

                UI_Common_AddPic(temp_ram,8,11+59,(uint8_t*)run_h);
            }
            else if(info->ListBuf[curr_page_info.curr_page_number*3+1].DataClassify == eDataClassifyClimbNew)
            {
                //UI_Common_AddBWsourcePic(temp_ram,8,11,(uint8_t*)image_sportmode_climb_24_h,APP_COLOR_BLACK,APP_COLOR_GREEN);

                UI_Common_AddPic(temp_ram,8,11+59,(uint8_t*)climb_h);
            }
            else if(info->ListBuf[curr_page_info.curr_page_number*3+1].DataClassify == eDataClassifySwimNew)
            {
                UI_Common_AddPic(temp_ram,8,11+59,(uint8_t*)swim_h);
            }
            
            UtcTransformTime(info->ListBuf[curr_page_info.curr_page_number*3+1].UTC, &rtc_time);
            sprintf(content,"%02d-%02d-%02d",rtc_time.year,rtc_time.month,rtc_time.day);
            len = strlen(content);
            
            UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,52,6+59,116,26,APP_COLOR_WHITE,content,len,26,ENUM_TEXTBOX_LEFT);
            
            temp_f = (float)info->ListBuf[curr_page_info.curr_page_number*3+1].Distance/1000;
            //memset(string_content,0,16);
            sprintf(content,"%0.2fkm",temp_f);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,52,34+59,160,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        }
        
        if( info->ListCnt - curr_page_info.curr_page_number*3>=3)
        {

            //info_detail = Store_History_ListPGet(curr_page_info.curr_page_number*3+2);
                
            if(info->ListBuf[curr_page_info.curr_page_number*3+2].DataClassify == eDataClassifyRunNew)
            {
                //UI_Common_AddBWsourcePic(temp_ram,8,11,(uint8_t*)image_sportmode_run_24_h,APP_COLOR_BLACK,APP_COLOR_GREEN);

                UI_Common_AddPic(temp_ram,8,11+59*2,(uint8_t*)run_h);
            }
            else if(info->ListBuf[curr_page_info.curr_page_number*3+2].DataClassify == eDataClassifyClimbNew)
            {
                //UI_Common_AddBWsourcePic(temp_ram,8,11,(uint8_t*)image_sportmode_climb_24_h,APP_COLOR_BLACK,APP_COLOR_GREEN);

                UI_Common_AddPic(temp_ram,8,11+59*2,(uint8_t*)climb_h);
            }
            else if(info->ListBuf[curr_page_info.curr_page_number*3+2].DataClassify == eDataClassifySwimNew)
            {
                UI_Common_AddPic(temp_ram,8,11+59*2,(uint8_t*)swim_h);
            }
            
            UtcTransformTime(info->ListBuf[curr_page_info.curr_page_number*3+2].UTC, &rtc_time);
            sprintf(content,"%02d-%02d-%02d",rtc_time.year,rtc_time.month,rtc_time.day);
            len = strlen(content);
            
            UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,52,6+59*2,116,26,APP_COLOR_WHITE,content,len,26,ENUM_TEXTBOX_LEFT);
            
            temp_f = (float)info->ListBuf[curr_page_info.curr_page_number*3+2].Distance/1000;
            //memset(string_content,0,16);
            sprintf(content,"%0.2fkm",temp_f);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,52,34+59*2,160,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        }
            
    }
    
    UI_Display_Prepare(temp_ram);

}


void UI_Screen_SportHistory_Entry(void)
{

    StoreHistoryParam_t* info;
    info = Store_History_ParamPGet();
    
    curr_page_info.total_page_number = (info->ListCnt+2)/3;
    curr_page_info.curr_page_number = 0;
    curr_page_info.index = 0;
    
    
    UI_Screen_SportHistory_Display();
    
    UI_Common_set_key_handle(UI_Screen_SportHistory_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SportHistory_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_SportHistory_tpupslidehandle,
                                    UI_Screen_SportHistory_tpdownslidehandle,
                                    UI_Screen_SportHistory_tpleftslidehandle,
                                    UI_Screen_SportHistory_tprightslidehandle);
    
}

void UI_Screen_SportHistory_Exit(void)
{

}

void UI_Screen_SportHistory_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    
    UI_Screen_draw_Screen();

}

void UI_Screen_SportHistory_holdshortkeyhandle(void)
{
}

void UI_Screen_SportHistory_holdlongkeyhandle(void)
{
}

void UI_Screen_SportHistory_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);
    StoreHistoryParam_t* info;
    info = Store_History_ParamPGet();

    
    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            if( info->ListCnt - curr_page_info.curr_page_number*3>=1)
            {
                curr_page_info.index = curr_page_info.curr_page_number*3+0;
                UI_Set_Curr_ScreenID(Common_Screen_MainID_SportHistory_Detail);
                UI_Screen_draw_Screen();
            }
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            if( info->ListCnt - curr_page_info.curr_page_number*3>=2)
            {
                curr_page_info.index = curr_page_info.curr_page_number*3+1;
                UI_Set_Curr_ScreenID(Common_Screen_MainID_SportHistory_Detail);
                UI_Screen_draw_Screen();
            }
            
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
            if( info->ListCnt - curr_page_info.curr_page_number*3>=3)
            {
                curr_page_info.index = curr_page_info.curr_page_number*3+2;
                UI_Set_Curr_ScreenID(Common_Screen_MainID_SportHistory_Detail);
                UI_Screen_draw_Screen();
             }
        }
        break;
        default:
        break;
    }
    


}


void UI_Screen_SportHistory_tpupslidehandle(void)
{

    UI_Common_Next_Page();
    UI_Screen_SportHistory_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_SportHistory_tpdownslidehandle(void)
{
    UI_Common_Pre_Page();
    UI_Screen_SportHistory_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_SportHistory_tpleftslidehandle(void)
{
}

void UI_Screen_SportHistory_tprightslidehandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_Modelist);
    UI_Screen_draw_Screen();

}


void UI_Screen_SportHistoryDetail_Display(void)
{

    StoreHistoryRecord_t info;
    StoreHistoryList_t* info_detail;
    char content[32];
    int len;
    rtc_time_s rtc_time;
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    float temp_f;
    int temp_a,temp_b;
    int hour;
    int min;
    int second;

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_SportHistory_Detail)
        return;

    UI_Common_Clear_Screen(temp_ram);

    info_detail = Store_History_ListPGet(detail_page_info.index);
    Store_History_RecordGet(info_detail->CatalogSerial, &info);
    
    if(info_detail->DataClassify == eDataClassifyRunNew)
    {

        if(detail_page_info.curr_page_number == 0)
        {

            //title
            UI_Common_Draw_FontStr_textbox(temp_ram,8,8,160,16,(uint8_t *)gchinesefont_sportscene_history_running,APP_COLOR_WHITE,APP_COLOR_BLACK);

            UtcTransformTime(info.Record.Run.StartUTC, &rtc_time);
            
            sprintf(content,"%02d/%02d/%02d  %02d:%02d",rtc_time.year,rtc_time.month,rtc_time.day,rtc_time.hour,rtc_time.min);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,8,32,160,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_CENTER);

        #if 0
			MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
            sprintf(content,"%02d:%02d",lMidRTC->RTC.hour,lMidRTC->RTC.min);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,94,32,80,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        #endif

            //距离
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_distance[0]-8,59,gchinesefont_sportscene_datadetail_distance[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_distance,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            temp_f = (float)info.Record.Run.Distance/1000;
            //memset(string_content,0,16);
            sprintf(content,"%0.2fkm",temp_f);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

            //时长
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_time[0]-8,101,gchinesefont_sportscene_datadetail_time[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_time,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,105,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            hour = info.Record.Run.Duration/3600;
            min = info.Record.Run.Duration%3600/60;
            second = info.Record.Run.Duration%60;
            sprintf(content,"%02d:%02d:%02d",hour,min,second);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,101,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

            
            //活动时长
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_activitytime[0]-8,142,gchinesefont_sportscene_datadetail_activitytime[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_activitytime,APP_COLOR_WHITE,APP_COLOR_BLACK);
            //UI_Common_Draw_FontStr_textbox(lcdram,84-gchinesefont_sportscene_datadetail_minkm[0]-gchinesefont_sportscene_average[0]-8,142,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,146,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            hour = info.Record.Run.ValidDuration/3600;
            min = info.Record.Run.ValidDuration%3600/60;
            second = info.Record.Run.ValidDuration%60;
            sprintf(content,"%02d:%02d:%02d",hour,min,second);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,142,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            
            
        }
        else if(detail_page_info.curr_page_number == 1)
        {

            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_minkm[0]-8,18,gchinesefont_sportscene_datadetail_minkm[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_minkm,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_minkm[0]-gchinesefont_sportscene_average[0]-8,18,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,22,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);
            
            temp_a = info.Record.Run.PaceAVG/60;
            temp_b = info.Record.Run.PaceAVG%60; 
            sprintf(content,"%d\"%2d'",temp_a,temp_b);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,18,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            
            
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_calorie[0]-8,59,gchinesefont_sportscene_datadetail_calorie[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_calorie,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            sprintf(content,"%dkcal",info.Record.Run.Calorie);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_stridefrequency[0]-8,101,gchinesefont_sportscene_datadetail_stridefrequency[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_stridefrequency,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_stridefrequency[0]-gchinesefont_sportscene_average[0]-8,101,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,105,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            sprintf(content,"%dspm",info.Record.Run.FreqAVG);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,101,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_stride[0]-8,142,gchinesefont_sportscene_datadetail_stride[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_stride,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_stride[0]-gchinesefont_sportscene_average[0]-8,142,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,146,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            temp_f =(float)info.Record.Run.StrideAVG/100;
            sprintf(content,"%0.2fm",temp_f);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,142,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            
                
        }
        else
        {
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-8,18,gchinesefont_heartrate_detail_heartrate[0],16,(uint8_t *)gchinesefont_heartrate_detail_heartrate,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-gchinesefont_sportscene_average[0]-8,18,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,22,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            sprintf(content,"%d",info.Record.Run.HrAVG);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,18,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            

            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-8,59,gchinesefont_heartrate_detail_heartrate[0],16,(uint8_t *)gchinesefont_heartrate_detail_heartrate,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-gchinesefont_sportscene_datadetail_max[0]-8,59,gchinesefont_sportscene_datadetail_max[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_max,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            sprintf(content,"%d",info.Record.Run.HrMax);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            

        }

    
    }
    else if(info_detail->DataClassify == eDataClassifyClimbNew)
    {
        if(detail_page_info.curr_page_number == 0)
        {
            //title
            
            UtcTransformTime(info.Record.Climb.StartUTC, &rtc_time);
            
            UI_Common_Draw_FontStr_textbox(temp_ram,8,8,160,16,(uint8_t *)gchinesefont_sportscene_history_climbing,APP_COLOR_WHITE,APP_COLOR_BLACK);
            sprintf(content,"%02d/%02d/%02d  %02d:%02d",rtc_time.year,rtc_time.month,rtc_time.day,rtc_time.hour,rtc_time.min);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,8,32,160,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_CENTER);
            
            //距离
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_distance[0]-8,59,gchinesefont_sportscene_datadetail_distance[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_distance,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);


            temp_f = (float)info.Record.Climb.Distance/1000;
            //memset(string_content,0,16);
            sprintf(content,"%0.2fkm",temp_f);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);


            //时长
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_time[0]-8,101,gchinesefont_sportscene_datadetail_time[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_time,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,105,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            hour = info.Record.Climb.Duration/3600;
            min = info.Record.Climb.Duration%3600/60;
            second = info.Record.Climb.Duration%60;
            sprintf(content,"%02d:%02d:%02d",hour,min,second);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,101,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);


            //活动时长
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_activitytime[0]-8,142,gchinesefont_sportscene_datadetail_activitytime[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_activitytime,APP_COLOR_WHITE,APP_COLOR_BLACK);
            //UI_Common_Draw_FontStr_textbox(lcdram,84-gchinesefont_sportscene_datadetail_minkm[0]-gchinesefont_sportscene_average[0]-8,142,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,146,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            hour = info.Record.Climb.ValidDuration/3600;
            min = info.Record.Climb.ValidDuration%3600/60;
            second = info.Record.Climb.ValidDuration%60;
            sprintf(content,"%02d:%02d:%02d",hour,min,second);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,142,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            
            
        }
        else if(detail_page_info.curr_page_number == 1)
        {
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_goup[0]-8,18,gchinesefont_sportscene_datadetail_goup[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_goup,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,22,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            
            sprintf(content,"%dm",info.Record.Climb.UpAltitude);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,18,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

            

            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_godown[0]-8,59,gchinesefont_sportscene_datadetail_godown[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_godown,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            sprintf(content,"%dm",info.Record.Climb.DownAltitude);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

            
            
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_speed[0]-8,101,gchinesefont_sportscene_datadetail_speed[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_speed,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_speed[0]-gchinesefont_sportscene_average[0]-8,101,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,105,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);


            temp_f = info.Record.Climb.SpeedAVG/1000;
            sprintf(content,"%0.2fkm/h",temp_f);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,101,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            

            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_compass_elevation[0]-8,142,gchinesefont_compass_elevation[0],16,(uint8_t *)gchinesefont_compass_elevation,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_compass_elevation[0]-gchinesefont_sportscene_datadetail_highest[0]-8,142,gchinesefont_sportscene_datadetail_highest[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_highest,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,146,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            sprintf(content,"%dm",info.Record.Climb.HighestAltitude);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,142,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);


            
                
        }
        else
        {
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_calorie[0]-8,18,gchinesefont_sportscene_datadetail_calorie[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_calorie,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,22,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            sprintf(content,"%dkcal",info.Record.Climb.Calorie);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,18,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-8,59,gchinesefont_heartrate_detail_heartrate[0],16,(uint8_t *)gchinesefont_heartrate_detail_heartrate,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-gchinesefont_sportscene_average[0]-8,59,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,22,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            sprintf(content,"%d",info.Record.Climb.HrAVG);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            
            
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-8,101,gchinesefont_heartrate_detail_heartrate[0],16,(uint8_t *)gchinesefont_heartrate_detail_heartrate,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-gchinesefont_sportscene_datadetail_max[0]-8,101,gchinesefont_sportscene_datadetail_max[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_max,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,105,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            sprintf(content,"%d",info.Record.Climb.HrMax);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,101,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            
        }
    
    }
    else if(info_detail->DataClassify == eDataClassifySwimNew)
    {
        //首页
        if(detail_page_info.curr_page_number == 0)
        {

            UtcTransformTime(info.Record.Swim.StartUTC, &rtc_time);

            //title
            UI_Common_Draw_FontStr_textbox(temp_ram,8,8,160,16,(uint8_t *)gchinesefont_sportscene_history_swim,APP_COLOR_WHITE,APP_COLOR_BLACK);
            sprintf(content,"%02d/%02d/%02d  %02d:%02d",rtc_time.year,rtc_time.month,rtc_time.day,rtc_time.hour,rtc_time.min);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,8,32,160,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_CENTER);

            //距离
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_distance[0]-8,59,gchinesefont_sportscene_datadetail_distance[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_distance,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            temp_f = (float)info.Record.Swim.Distance/1000;
            //memset(string_content,0,16);
            sprintf(content,"%0.2fkm",temp_f);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            

            //时长
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_time[0]-8,101,gchinesefont_sportscene_datadetail_time[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_time,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,105,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            hour = info.Record.Swim.Duration/3600;
            min = info.Record.Swim.Duration%3600/60;
            second = info.Record.Swim.Duration%60;
            sprintf(content,"%02d:%02d:%02d",hour,min,second);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,101,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

            //活动时长
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_activitytime[0]-8,142,gchinesefont_sportscene_datadetail_activitytime[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_activitytime,APP_COLOR_WHITE,APP_COLOR_BLACK);
            //UI_Common_Draw_FontStr_textbox(lcdram,84-gchinesefont_sportscene_datadetail_minkm[0]-gchinesefont_sportscene_average[0]-8,142,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,146,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            hour = info.Record.Swim.ValidDuration/3600;
            min = info.Record.Swim.ValidDuration%3600/60;
            second = info.Record.Swim.ValidDuration%60;
            sprintf(content,"%02d:%02d:%02d",hour,min,second);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,142,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            
        
        }
        else if(detail_page_info.curr_page_number == 1)
        {

            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_minkm[0]-4,18,gchinesefont_sportscene_datadetail_minkm[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_minkm,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_minkm[0]-gchinesefont_sportscene_average[0]-4,18,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,22,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            temp_a = info.Record.Swim.PaceAVG/60;
            temp_b = info.Record.Swim.PaceAVG%60; 
            sprintf(content,"%d\"%2d'",temp_a,temp_b);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,18,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

            
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_strokecount[0]-4,59,gchinesefont_sportscene_strokecount[0],16,(uint8_t *)gchinesefont_sportscene_strokecount,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            sprintf(content,"%d",info.Record.Swim.Stroke);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);


            
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_strokecount[0]-4,101,gchinesefont_sportscene_strokecount[0],16,(uint8_t *)gchinesefont_sportscene_strokecount,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_strokecount[0]-gchinesefont_sportscene_average[0]-4,101,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,105,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);
            
            sprintf(content,"%d",info.Record.Swim.StrokeAVG);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,101,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_strokerate[0]-4,142,gchinesefont_sportscene_strokerate[0],16,(uint8_t *)gchinesefont_sportscene_strokerate,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_strokerate[0]-gchinesefont_sportscene_average[0]-4,142,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,146,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);


            sprintf(content,"%dspm",info.Record.Swim.StrokeRateAVG);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,142,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
                
        
        }
        else
        {

            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_swolf[0]-8,18,gchinesefont_sportscene_datadetail_swolf[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_swolf,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,22,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            sprintf(content,"%d",info.Record.Swim.SwolfAvg);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,18,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_calorie[0]-8,59,gchinesefont_sportscene_datadetail_calorie[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_calorie,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            sprintf(content,"%dkcal",info.Record.Swim.Calorie);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-8,101,gchinesefont_heartrate_detail_heartrate[0],16,(uint8_t *)gchinesefont_heartrate_detail_heartrate,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-gchinesefont_sportscene_average[0]-8,101,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,84,105,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

            
            sprintf(content,"%d",info.Record.Swim.HrAVG);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,101,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        }
        
    
    }
    
    
    UI_Display_Prepare(temp_ram);

}

void UI_Screen_SportHistoryDetail_Entry(void)
{

    detail_page_info.total_page_number = 3;
    detail_page_info.curr_page_number = 0;
    detail_page_info.index = curr_page_info.index;

    UI_Screen_SportHistoryDetail_Display();
    
    UI_Common_set_key_handle(UI_Screen_SportHistoryDetail_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SportsHistoryDetail_tpclickhandle);
    
    UI_Common_set_tp_slide_handle(UI_Screen_SportHistoryDetail_tpupslidehandle,
                                    UI_Screen_SportHistoryDetail_tpdownslidehandle,
                                    UI_Screen_SportHistoryDetail_tpleftslidehandle,
                                    UI_Screen_SportHistoryDetail_tprightslidehandle);
    
}

void UI_Screen_SportHistoryDetail_Exit(void)
{



}

void UI_Screen_SportHistoryDetail_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}

void UI_Screen_SportHistoryDetail_holdshortkeyhandle(void)
{
}

void UI_Screen_SportHistoryDetail_holdlongkeyhandle(void)
{
}

void UI_Screen_SportsHistoryDetail_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);
    
    
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
            
        }
        break;
        default:
        break;
    }
    


}

void UI_Screen_SportHistoryDetail_tpupslidehandle(void)
{
    UI_Common_Detail_Next_Page();
    UI_Screen_SportHistoryDetail_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_SportHistoryDetail_tpdownslidehandle(void)
{
    UI_Common_Detail_Pre_Page();
    UI_Screen_SportHistoryDetail_Display();
    UI_Screen_Redraw_Screen();
    
}

void UI_Screen_SportHistoryDetail_tpleftslidehandle(void)
{
}


void UI_Screen_SportHistoryDetail_tprightslidehandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_SportHistory);
    UI_Screen_draw_Screen();
}



