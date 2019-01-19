

#include "ui_screen_sleep.h"


const uint8_t image_sleep_oval_h[] = {
32,32,
0x00, 0x00, 0x00, 0x00, /* scanline 1 */
0x00, 0x00, 0x00, 0x00, /* scanline 2 */
0x00, 0x00, 0x00, 0x00, /* scanline 3 */
0x00, 0x00, 0x00, 0x00, /* scanline 4 */
0x00, 0x00, 0x00, 0x00, /* scanline 5 */
0x00, 0x00, 0x00, 0x00, /* scanline 6 */
0x00, 0x00, 0x00, 0x00, /* scanline 7 */
0x00, 0x00, 0x00, 0x00, /* scanline 8 */
0x00, 0x00, 0x00, 0x00, /* scanline 9 */
0x71, 0xE3, 0xFF, 0xE0, /* scanline 10 */
0x73, 0xF3, 0xFF, 0xF8, /* scanline 11 */
0x77, 0xFB, 0xFF, 0xFC, /* scanline 12 */
0x77, 0xFB, 0xFF, 0xFC, /* scanline 13 */
0x77, 0xFB, 0xFF, 0xFE, /* scanline 14 */
0x77, 0xFB, 0xFF, 0xFE, /* scanline 15 */
0x73, 0xF3, 0xFF, 0xFE, /* scanline 16 */
0x71, 0xE3, 0xFF, 0xFE, /* scanline 17 */
0x70, 0x03, 0xFF, 0xFE, /* scanline 18 */
0x7F, 0xFF, 0xFF, 0xFE, /* scanline 19 */
0x7F, 0xFF, 0xFF, 0xFE, /* scanline 20 */
0x7F, 0xFF, 0xFF, 0xFE, /* scanline 21 */
0x7F, 0xFF, 0xFF, 0xFE, /* scanline 22 */
0x7F, 0xFF, 0xFF, 0xFE, /* scanline 23 */
0x00, 0x00, 0x00, 0x00, /* scanline 24 */
0x00, 0x00, 0x00, 0x00, /* scanline 25 */
0x00, 0x00, 0x00, 0x00, /* scanline 26 */
0x00, 0x00, 0x00, 0x00, /* scanline 27 */
0x00, 0x00, 0x00, 0x00, /* scanline 28 */
0x00, 0x00, 0x00, 0x00, /* scanline 29 */
0x00, 0x00, 0x00, 0x00, /* scanline 30 */
0x00, 0x00, 0x00, 0x00, /* scanline 31 */
0x00, 0x00, 0x00, 0x00, /* scanline 32 */
};



void UI_Screen_Sleep_Display(void)
{
    char string[16];
    int string_len;
    int hour, min;
    uint8_t* fontinfo;
    int x = 0;
    float angle_1,angle_2;

    sleep_record_t sleepRecord;
    Scene_Sleep_RecordGet(&sleepRecord);

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Sleep)
        return;

    UI_Common_Clear_Screen(temp_ram);

    
    if(sleepRecord.SleepDuration == 0)
    {
        UI_Common_Draw_Annulus_Byangle(temp_ram,87,79,64,56,PI/3,5*PI/3,APP_COLOR_PINK,FALSE);

        
        //UI_Common_AddPic(lcdram,64,56,(uint8_t*)image_sleep_oval_h);
        UI_Common_Draw_Circle(temp_ram,87,80,24,APP_COLOR_PINK);
        UI_Common_AddBWsourcePic(temp_ram,72,64,(uint8_t*)image_sleep_oval_h,APP_COLOR_PINK,APP_COLOR_BLACK);

        
        UI_Common_AddBWsourcePic(temp_ram,76,36,(uint8_t*)gchinesefont_sleep,APP_COLOR_BLACK,APP_COLOR_WHITE);

        sprintf(string,"--h --m");
        string_len = strlen(string);
        UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,8,117,160,26,APP_COLOR_WHITE,string,string_len,26,ENUM_TEXTBOX_CENTER);

        UI_Common_Draw_FontStr_textbox(temp_ram,8,150,160,16,(uint8_t *)gchinesefont_sleep_nodata,APP_COLOR_WHITE,APP_COLOR_BLACK);
    }
    else
    {

        angle_1 = sleepRecord.WakeDuration*4*PI/sleepRecord.TotalDuration/3;
        angle_2 = sleepRecord.LightDuration*4*PI/sleepRecord.TotalDuration/3+angle_1;
        
        //UI_Common_Draw_Annulus_Byangle(lcdram,87,79,64,56,PI/3,5*PI/3,APP_COLOR_PINK,FALSE);
        UI_Common_Draw_Annulus_Byangle(temp_ram,87,79,64,56,PI/3,PI/3+angle_1,APP_COLOR_CYAN,TRUE);
        UI_Common_Draw_Annulus_Byangle(temp_ram,87,79,64,56,PI/3+angle_1,PI/3+angle_2,APP_COLOR_PINK,TRUE);
        UI_Common_Draw_Annulus_Byangle(temp_ram,87,79,64,56,PI/3+angle_2,5*PI/3,APP_COLOR_BLUE,TRUE);
        UI_Common_Draw_Circle(temp_ram,87,80,24,APP_COLOR_PINK);
        UI_Common_AddBWsourcePic(temp_ram,72,64,(uint8_t*)image_sleep_oval_h,APP_COLOR_PINK,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,76,36,(uint8_t*)gchinesefont_sleep,APP_COLOR_BLACK,APP_COLOR_WHITE);

        hour = sleepRecord.SleepDuration/60;
        min = sleepRecord.SleepDuration%60;
        sprintf(string,"%02dh%02dm",hour,min);
        string_len = strlen(string);
        UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,8,117,160,26,APP_COLOR_WHITE,string,string_len,26,ENUM_TEXTBOX_CENTER);

        switch(sleepRecord.Quality)
        {
            case ALG_SLEEP_EXCELLENT:
            {
                x = 24;
                fontinfo = (uint8_t*)gchinesefont_sleep_excellent;
            }
            break;
            case ALG_SLEEP_GOOD:
            {
                x = 32;
                fontinfo = (uint8_t*)gchinesefont_sleep_good;
            }
            break;
            case ALG_SLEEP_ONLY_FAIR:
            {
                x = 32;
                fontinfo = (uint8_t*)gchinesefont_sleep_onlyfair;
            }
            break;
            case ALG_SLEEP_POOR:
            {
                x = 32;
                fontinfo = (uint8_t*)gchinesefont_sleep_Poor;
            }
            break;
            default:
            break;
        }

        UI_Common_AddBWsourcePic(temp_ram,x,150,(uint8_t*)gchinesefont_sleep_quality,APP_COLOR_BLACK,APP_COLOR_WHITE);
        UI_Common_AddBWsourcePic(temp_ram,x+80,150,(uint8_t*)fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);
        
    }

    UI_Display_Prepare(temp_ram);
    
}


void UI_Screen_Sleep_Entry(void)
{

    UI_Screen_Sleep_Display();

    UI_Common_set_key_handle(UI_Screen_Sleep_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Sleep_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Sleep_tpupslidehandle,
                                    UI_Screen_Sleep_tpdownslidehandle,
                                    UI_Screen_Sleep_tpleftslidehandle,
                                    UI_Screen_Sleep_tprightslidehandle);
}

void UI_Screen_Sleep_Exit(void)
{
}

void UI_Screen_Sleep_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);

    UI_Screen_draw_Screen();

}

void UI_Screen_Sleep_holdshortkeyhandle(void)
{
}

void UI_Screen_Sleep_holdlongkeyhandle(void)
{
}

void UI_Screen_Sleep_tpclickhandle(int point_x,int point_y)
{

    sleep_record_t sleepRecord;
    Scene_Sleep_RecordGet(&sleepRecord);

    if(sleepRecord.SleepDuration != 0)
    {
        //curr_run_screen_info.run_type = ENUM_MOVE_IN;
        UI_Common_Show_RunScreen_Prepare(ENUM_MOVE_IN);
        
        UI_Set_Curr_ScreenID(Common_Screen_MainID_Sleep_Detail);
        UI_Screen_draw_Screen();
    }

    

}

void UI_Screen_Sleep_tpupslidehandle(void)
{

    //curr_run_screen_info.run_type = ENUM_ROUND_UP;
    UI_Common_Show_RunScreen_Prepare(ENUM_ROUND_UP);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Compass);
    UI_Screen_draw_Screen();


}

void UI_Screen_Sleep_tpdownslidehandle(void)
{

    //curr_run_screen_info.run_type = ENUM_ROUND_DOWN;
    UI_Common_Show_RunScreen_Prepare(ENUM_ROUND_DOWN);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Temperature);
    UI_Screen_draw_Screen();

}

void UI_Screen_Sleep_tpleftslidehandle(void)
{
}

void UI_Screen_Sleep_tprightslidehandle(void)
{
}



#if 0
typedef struct
{
	uint8_t StartHour;		 /* 开始时间：时 , 睡眠开始结束时间RTC格式 */
	uint8_t StartMin;		 /* 开始时间：分 */
	uint8_t StopHour;		 /* 结束时间：时 */
	uint8_t StopMin;		 /* 结束时间：分 */
	uint32_t StartUTC;		 /* 睡眠开始UTC , 睡眠开始结束时间UTC格式 */
	uint32_t StopUTC;		 /* 睡眠结束UTC */
	uint16_t SleepDuration;  /* *m 总睡眠时长，不包括清醒时间 */
	sleep_quality_e Quality; /* 睡眠质量 */

	uint16_t TotalDuration; /* *m 总睡眠时长：包括清醒时长，等于下面四个时长的总和 */
	uint16_t WakeDuration;  /* *m 清醒时长 */
	uint16_t LightDuration; /* *m 浅睡时长 */
	uint16_t DeepDuration;  /* *m 深睡时长 */
	uint16_t RemDuration;   /* *m 快速眼动时长 */

	uint8_t SegmentCnt;							  /* 从开始时间到结束时间有几个详细时间段 */
	sleep_segment_t SleepData[SLEEP_SEGMENT_MAX]; /* 每段具体时长和状态 */
} sleep_record_t;
#endif

#define  DM_COMMON_HEIGHT   48
#define  DM_WAKEDURATION_HEIGHT   56

void UI_Screen_Sleep_Detail_Display(void)
{
    char content[16];
    int len;
    sleep_record_t curr_info;
    int diagram_start_x,diagram_start_y;
    int curr_segment_len = 0;
    int x;
    int i= 0;
    int hour,min;
    int remainder = 0;

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Sleep_Detail)
        return;

    UI_Common_Clear_Screen(temp_ram);
        
    Scene_Sleep_RecordGet(&curr_info);

    sprintf(content,"%02d:%02d-%02d:%02d",curr_info.StartHour,curr_info.StartMin,curr_info.StopHour,curr_info.StopMin);
    len = strlen(content);
    UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,0,12,176,20,APP_COLOR_WHITE,content,len,20,ENUM_TEXTBOX_CENTER);


    diagram_start_x = 8+160;
    diagram_start_y = 104;
    x = 8;


    UI_Common_Draw_Hline(temp_ram,diagram_start_x-160,diagram_start_y,160,1,APP_COLOR_WHITE,TRUE);
    

    for(i = 0;i<curr_info.SegmentCnt;i++)
    {

        curr_segment_len = (curr_info.SleepData[i].Duration*160+remainder)/curr_info.TotalDuration;
        remainder = curr_info.SleepData[i].Duration*160%curr_info.TotalDuration;
        
        if(curr_info.SleepData[i].State ==ALG_SLEEP_WAKE)
        {
            UI_Common_Draw_Hline(temp_ram,x,diagram_start_y-DM_WAKEDURATION_HEIGHT,curr_segment_len,DM_WAKEDURATION_HEIGHT,APP_COLOR_CYAN,TRUE);
        }
        else if(curr_info.SleepData[i].State ==ALG_SLEEP_LIGHT)
        {
            UI_Common_Draw_Hline(temp_ram,x,diagram_start_y-DM_COMMON_HEIGHT,curr_segment_len,DM_COMMON_HEIGHT,APP_COLOR_PINK,TRUE);
        }
        else 
        {
            UI_Common_Draw_Hline(temp_ram,x,diagram_start_y-DM_COMMON_HEIGHT,curr_segment_len,DM_COMMON_HEIGHT,APP_COLOR_BLUE,TRUE);
        }
        x= x+curr_segment_len;
    
    }

    
    UI_Common_Draw_Hline(temp_ram,16,116,8,8,APP_COLOR_CYAN,TRUE);
    UI_Common_Draw_Hline(temp_ram,16,136,8,8,APP_COLOR_PINK,TRUE);
    UI_Common_Draw_Hline(temp_ram,16,156,8,8,APP_COLOR_BLUE,TRUE);

    
    UI_Common_AddBWsourcePic(temp_ram,48,112,(uint8_t*)gchinesefont_sleep_detail_wakeup,APP_COLOR_BLACK,APP_COLOR_WHITE);
    UI_Common_AddBWsourcePic(temp_ram,48,132,(uint8_t*)gchinesefont_sleep_detail_lightsleep,APP_COLOR_BLACK,APP_COLOR_WHITE);
    UI_Common_AddBWsourcePic(temp_ram,48,152,(uint8_t*)gchinesefont_sleep_detail_deepsleep,APP_COLOR_BLACK,APP_COLOR_WHITE);


    hour = curr_info.WakeDuration/60;
    min = curr_info.WakeDuration%60;
    sprintf(content,"%02dh%02dm",hour,min);
    len = strlen(content);
    UI_Common_Draw_AscStr_textbox(temp_ram,104,112,80,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);


    hour = curr_info.LightDuration/60;
    min = curr_info.LightDuration%60;
    sprintf(content,"%02dh%02dm",hour,min);
    len = strlen(content);
    UI_Common_Draw_AscStr_textbox(temp_ram,104,132,80,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

    hour = curr_info.DeepDuration/60;
    min = curr_info.DeepDuration%60;
    sprintf(content,"%02dh%02dm",hour,min);
    len = strlen(content);
    UI_Common_Draw_AscStr_textbox(temp_ram,104,152,80,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);


    UI_Display_Prepare(temp_ram);
    
}


void UI_Screen_Sleep_Detail_Entry(void)
{

    UI_Screen_Sleep_Detail_Display();
    
    UI_Common_set_key_handle(UI_Screen_Sleep_Detail_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Sleep_Detail_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Sleep_Detail_tpupslidehandle,
                                    UI_Screen_Sleep_Detail_tpdownslidehandle,
                                    UI_Screen_Sleep_Detail_tpleftslidehandle,
                                    UI_Screen_Sleep_Detail_tprightslidehandle);
}

void UI_Screen_Sleep_Detail_Exit(void)
{
}

void UI_Screen_Sleep_Detail_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);

    UI_Screen_draw_Screen();

}

void UI_Screen_Sleep_Detail_holdshortkeyhandle(void)
{
}

void UI_Screen_Sleep_Detail_holdlongkeyhandle(void)
{
}

void UI_Screen_Sleep_Detail_tpclickhandle(int point_x,int point_y)
{

    //判断点的范围

}

void UI_Screen_Sleep_Detail_tpupslidehandle(void)
{


}

void UI_Screen_Sleep_Detail_tpdownslidehandle(void)
{


}

void UI_Screen_Sleep_Detail_tpleftslidehandle(void)
{
}

void UI_Screen_Sleep_Detail_tprightslidehandle(void)
{
    //curr_run_screen_info.run_type = ENUM_MOVE_OUT;
    UI_Common_Show_RunScreen_Prepare(ENUM_MOVE_OUT);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Sleep);
    UI_Screen_draw_Screen();

}



