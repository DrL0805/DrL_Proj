#include "ui_screen_heartrate.h"
#include "ui_screen_dateandtime.h"

//extern uint8_t TempLcdRam[RGB_LCD_RAM_LEN];

const uint8_t image_heart_rate_oval_h[] = {
32,32,
0x00, 0x00, 0x00, 0x00, /* scanline 1 */
0x00, 0x00, 0x00, 0x00, /* scanline 2 */
0x00, 0x00, 0x00, 0x00, /* scanline 3 */
0x00, 0x00, 0x00, 0x00, /* scanline 4 */
0x00, 0x00, 0x00, 0x00, /* scanline 5 */
0x01, 0xE0, 0x07, 0x80, /* scanline 6 */
0x07, 0xF8, 0x1F, 0xE0, /* scanline 7 */
0x0F, 0xFC, 0x3F, 0xF0, /* scanline 8 */
0x1F, 0xFE, 0x7F, 0xF8, /* scanline 9 */
0x1F, 0xFF, 0xFF, 0xF8, /* scanline 10 */
0x3F, 0xFF, 0xFF, 0xFC, /* scanline 11 */
0x3F, 0xFC, 0xFF, 0xFC, /* scanline 12 */
0x3F, 0xFC, 0xFF, 0xFC, /* scanline 13 */
0x3F, 0xFC, 0xE7, 0xFC, /* scanline 14 */
0x1F, 0x3C, 0xE7, 0xF8, /* scanline 15 */
0x1C, 0x00, 0x00, 0x38, /* scanline 16 */
0x0C, 0x00, 0x00, 0x30, /* scanline 17 */
0x07, 0xE7, 0x3C, 0xE0, /* scanline 18 */
0x03, 0xE7, 0x3F, 0xC0, /* scanline 19 */
0x01, 0xFF, 0x3F, 0x80, /* scanline 20 */
0x00, 0xFF, 0x3F, 0x00, /* scanline 21 */
0x00, 0x7F, 0x3E, 0x00, /* scanline 22 */
0x00, 0x3F, 0x3C, 0x00, /* scanline 23 */
0x00, 0x1F, 0x38, 0x00, /* scanline 24 */
0x00, 0x0F, 0xF0, 0x00, /* scanline 25 */
0x00, 0x07, 0xE0, 0x00, /* scanline 26 */
0x00, 0x03, 0xC0, 0x00, /* scanline 27 */
0x00, 0x01, 0x80, 0x00, /* scanline 28 */
0x00, 0x00, 0x00, 0x00, /* scanline 29 */
0x00, 0x00, 0x00, 0x00, /* scanline 30 */
0x00, 0x00, 0x00, 0x00, /* scanline 31 */
0x00, 0x00, 0x00, 0x00, /* scanline 32 */
};

//Mid_Hrm_Param_t* curr_heartrate_info;

bool is_heartrate_init = FALSE;
static int curr_frame = 0;



void  UI_Screen_Heartrate_Timerhandle(void)
{

    UI_Screen_Heartrate_Display();
    
}


void UI_Screen_Heartrate_Display(void)
{
    char str_content[16];
    int len;
    int rhr_value= Scene_Hrm_RestingHrvGet();
    //static int i=0;
    float progress_angle =PI/3;
    float curr_angle[12] = {0,PI/6,2*PI/6,3*PI/6,4*PI/6,5*PI/6,PI,5*PI/6,4*PI/6,3*PI/6,2*PI/6,PI/6};
    Mid_Hrm_Param_t*curr_heartrate_info = Mid_Hrm_ParamPGet();

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    static int curr_remind = 0;


    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Heartrate)
        return;

    UI_Common_Clear_Screen(temp_ram);
    

    if(is_heartrate_init==FALSE||curr_heartrate_info->HrUpdateFlg==FALSE)
    {

        UI_Common_set_timer_handle(UI_Screen_Heartrate_Timerhandle);
        App_Lcd_TimerStart(200);
        UI_Common_Draw_Annulus_Byangle(temp_ram,87,79,64,56,PI/3,5*PI/3,APP_COLOR_RED,FALSE);
        UI_Common_Draw_Annulus_Byangle(temp_ram,87,79,64,56,PI/3+curr_angle[curr_frame],PI/3+curr_angle[curr_frame]+progress_angle,APP_COLOR_RED,TRUE);
        curr_frame++;
        if(curr_frame>=12)
        {
            curr_remind++;
            curr_frame = 0;
        }
        if((is_heartrate_init==FALSE)&&(curr_frame>=10))
        {
            is_heartrate_init = TRUE;
            
             curr_remind =0;
             //不允许进入休眠状态
             UI_Commom_Set_Allow_Lockstate1(0);
             //开启心率ic
             Scene_Hrm_SampleStart(eSceneMeasureIM);
        }
        UI_Common_AddBWsourcePic(temp_ram,76,36,(uint8_t*)gchinesefont_heartrate,APP_COLOR_BLACK,APP_COLOR_WHITE);
        
        UI_Common_Draw_Circle(temp_ram,87,80,24,APP_COLOR_RED);
        UI_Common_AddBWsourcePic(temp_ram,72,64,(uint8_t*)image_heart_rate_oval_h,APP_COLOR_RED,APP_COLOR_BLACK);
        
        //gchinesefont_wearingremind
        if(curr_remind%2==0)
        {
            UI_Common_Draw_FontStr_textbox(temp_ram,8,122,160,16,(uint8_t *)gchinesefont_testing,APP_COLOR_WHITE,APP_COLOR_BLACK);
        }
        else
        {
            UI_Common_Draw_FontStr_textbox(temp_ram,8,122,160,16,(uint8_t *)gchinesefont_wearingremind,APP_COLOR_WHITE,APP_COLOR_BLACK);
        }
        
        sprintf(str_content,"RHR--");
        len=strlen(str_content);
        UI_Common_Draw_AscStr_textbox(temp_ram,9,150,158,16,16,APP_COLOR_WHITE,str_content,len,ENUM_TEXTBOX_CENTER);


        
    }
    else
    {
            curr_frame =0;
            //RTT_DEBUG_printf(0, "UI_Screen_Heartrate_Display %d",curr_heartrate_info.CurrHeartRate);
            if(curr_heartrate_info->CurrHeartRate == HRM_INVALID_VALUE)
            {

                //心率检测失败 震动一次
                UI_Common_Shake();
            
                UI_Common_Draw_Annulus_Byangle(temp_ram,87,79,64,56,PI/3,5*PI/3,APP_COLOR_RED,FALSE);
                UI_Common_AddBWsourcePic(temp_ram,76,36,(uint8_t*)gchinesefont_heartrate,APP_COLOR_BLACK,APP_COLOR_WHITE);
                
                UI_Common_Draw_Circle(temp_ram,87,80,24,APP_COLOR_RED);
                UI_Common_AddBWsourcePic(temp_ram,72,64,(uint8_t*)image_heart_rate_oval_h,APP_COLOR_RED,APP_COLOR_BLACK);
                //gchinesefont_wearingremind
                UI_Common_Draw_FontStr_textbox(temp_ram,8,122,160,16,(uint8_t *)gchinesefont_wearingremind2,APP_COLOR_WHITE,APP_COLOR_BLACK);
                if(rhr_value == 0xff)
                {
                    sprintf(str_content,"RHR--");
                    len=strlen(str_content);
                    UI_Common_Draw_AscStr_textbox(temp_ram,9,150,158,16,16,APP_COLOR_WHITE,str_content,len,ENUM_TEXTBOX_CENTER);
                }
                else
                {
                    sprintf(str_content,"RHR %d",rhr_value);
                    len=strlen(str_content);
                    UI_Common_Draw_AscStr_textbox(temp_ram,9,150,158,16,16,APP_COLOR_WHITE,str_content,len,ENUM_TEXTBOX_CENTER);
                }
                
            }
            else
            {

                UI_Common_Draw_Annulus_Byangle(temp_ram,87,79,64,56,PI/3,5*PI/3,APP_COLOR_RED,TRUE);
                UI_Common_Draw_Circle(temp_ram,87,80,24,APP_COLOR_RED);
                UI_Common_AddBWsourcePic(temp_ram,72,64,(uint8_t*)image_heart_rate_oval_h,APP_COLOR_RED,APP_COLOR_BLACK);
                
                UI_Common_AddBWsourcePic(temp_ram,76,36,(uint8_t*)gchinesefont_heartrate,APP_COLOR_BLACK,APP_COLOR_WHITE);
                
                UI_Common_Draw_NumberImage_textbox(temp_ram,8,117,160,26,0,APP_COLOR_WHITE,curr_heartrate_info->CurrHeartRate);
                
                if(rhr_value == 0xff)
                {
                    sprintf(str_content,"RHR--");
                    len=strlen(str_content);
                    UI_Common_Draw_AscStr_textbox(temp_ram,9,150,158,16,16,APP_COLOR_WHITE,str_content,len,ENUM_TEXTBOX_CENTER);
                }
                else
                {
                    sprintf(str_content,"RHR %d",rhr_value);
                    len=strlen(str_content);
                    UI_Common_Draw_AscStr_textbox(temp_ram,9,150,158,16,16,APP_COLOR_WHITE,str_content,len,ENUM_TEXTBOX_CENTER);
                }
            }

            //有结果后，解除不允许进入休眠状态
            UI_Commom_Set_Allow_Lockstate1(1);
            
            UI_Common_set_timer_handle(NULL);
            
    }

    UI_Display_Prepare(temp_ram);

}

void UI_Screen_Heartrate_Entry(void)
{

    curr_frame =0;
    
    UI_Screen_Heartrate_Display();

    UI_Common_set_key_handle(UI_Screen_Heartrate_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Heartrate_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Heartrate_tpupslidehandle,
                                    UI_Screen_Heartrate_tpdownslidehandle,
                                    UI_Screen_Heartrate_tpleftslidehandle,
                                    UI_Screen_Heartrate_tprightslidehandle);
    
}

void UI_Screen_Heartrate_Exit(void)
{

    //curr_run_screen_info.is_run = 0;
    curr_frame =0;
    App_Lcd_TimerStop();
    UI_Common_set_timer_handle(NULL);
    
    if(is_heartrate_init == TRUE)
    {
        is_heartrate_init = FALSE;
        //有结果后，解除不允许进入休眠状态
        UI_Commom_Set_Allow_Lockstate1(1);
        Scene_Hrm_SampleStop(eSceneMeasureIM);
    }
}

void UI_Screen_Heartrate_shortkeyhandle(void)
{
    UI_Screen_Heartrate_Exit();
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}

void UI_Screen_Heartrate_holdshortkeyhandle(void)
{
}

void UI_Screen_Heartrate_holdlongkeyhandle(void)
{
}

void UI_Screen_Heartrate_tpclickhandle(int point_x,int point_y)
{

    UI_Screen_Heartrate_Exit();
    
    //curr_run_screen_info.run_type = ENUM_MOVE_IN;
    UI_Common_Show_RunScreen_Prepare(ENUM_MOVE_IN);
    
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Heartrate_Detail);
    UI_Screen_draw_Screen();

}

void UI_Screen_Heartrate_tpupslidehandle(void)
{

    UI_Screen_Heartrate_Exit();

    //curr_run_screen_info.run_type = ENUM_ROUND_UP;
    UI_Common_Show_RunScreen_Prepare(ENUM_ROUND_UP);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Pressure);
    UI_Screen_draw_Screen();


}

void UI_Screen_Heartrate_tpdownslidehandle(void)
{
    UI_Screen_Heartrate_Exit();
    
    //curr_run_screen_info.run_type = ENUM_ROUND_DOWN;
    UI_Common_Show_RunScreen_Prepare(ENUM_ROUND_DOWN);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Step);
    UI_Screen_draw_Screen();

}

void UI_Screen_Heartrate_tpleftslidehandle(void)
{


}

void UI_Screen_Heartrate_tprightslidehandle(void)
{

}



// 0 为最新数据
void UI_Screen_Heartrate_Detail_Display(void)
{

    uint8 data[135] = {80 ,76  ,98  ,98  ,67  ,65  ,69  ,71  ,71  ,71  ,63  ,62  ,63  ,59  ,62  ,64  ,64  ,63  ,62  ,63  ,63  ,63  ,62  ,60  ,62  ,58  ,60  ,62  ,59  ,60  ,62  ,59  ,62  ,62  ,61  ,61  ,
        58  ,69  ,59  ,64  ,81  ,61  ,63  ,85  ,64  ,57  ,59  ,60  ,59  ,60  ,59  ,60  ,56  ,56  ,59  ,58  ,56  ,56  ,56  ,57  ,57  ,58  ,56  ,59  ,55  ,57  ,55  ,57  ,57  ,57  ,55  ,
        55  ,56  ,55  ,55  ,55  ,53  ,56  ,54  ,56  ,55  ,57  ,56  ,84  ,58  ,60  ,53  ,55  ,61  ,58  ,63  ,63  ,58  ,72  ,58  ,57  ,63  ,57  ,68  ,56  ,56  ,63  ,57  ,60  ,62  ,60  ,66  ,59  ,57  ,
        53  ,61  ,52  ,73  ,57  ,58  ,56  ,57  ,55  ,56  ,57  ,58  ,56  ,57  ,55  ,56,58  ,56  ,57  ,55  ,56,58  ,56  ,57  ,55  ,56};

    int curr_data;
    int i;
    //int max_data =0;
    //120 +18(标尺) + 4（gap）=142 x =（ 176-142）/2
    int diagram_start_x,diagram_start_y;
    char content[16];
    int len;
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Heartrate_Detail)
        return;

    UI_Common_Clear_Screen(temp_ram);

    Store_Hrd_UIDataGet(data,135);
    
    
    UI_Common_AddBWsourcePic(temp_ram,8,6,(uint8_t*)gchinesefont_heartrate_detail_heartrate,APP_COLOR_BLACK,APP_COLOR_WHITE);

    if(data[0] == HRM_INVALID_VALUE)
    {
        sprintf(content,"--");
    }
    else
    {
        sprintf(content,"%d",data[0]);
    }
    len = strlen(content);
    UI_Common_Draw_AscStr_textbox(temp_ram,88,6,80,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_RIGHT);

    diagram_start_x = 0;
    diagram_start_y = 145;

    //标线 40
    UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y,135,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+15,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+15+30,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+15+30*2,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+15+30*3,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+15+30*4,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    
    UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+135+8,diagram_start_y-6,20,12,12,APP_COLOR_WHITE,"0",1,ENUM_TEXTBOX_LEFT);
    
    for(i=1;i<=135;i++)
    {

        curr_data = data[135-i];
        UI_Common_SetPixelValue(temp_ram,diagram_start_x+i-1,diagram_start_y-(curr_data+1)/2, APP_COLOR_RED);
        UI_Common_Draw_Vline(temp_ram,diagram_start_x+i-1,diagram_start_y-(curr_data+1)/2,(curr_data+1)/2,1,APP_COLOR_RED,TRUE);

    }
    
    //标线1 60
    UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y- 60/2,135,1,APP_COLOR_WHITE,false);
    UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+135+8,diagram_start_y- 60/2 -6,20,12,12,APP_COLOR_WHITE,"60",2,ENUM_TEXTBOX_LEFT);

    //标线1 120
    UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y- 120/2,135,1,APP_COLOR_WHITE,false);
    UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+135+8,diagram_start_y- 120/2 -6,20,12,12,APP_COLOR_WHITE,"120",3,ENUM_TEXTBOX_LEFT);

    //标线1 180
    UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y- 180/2,135,1,APP_COLOR_WHITE,false);
    UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+135+8,diagram_start_y- 180/2 -6,20,12,12,APP_COLOR_WHITE,"180",3,ENUM_TEXTBOX_LEFT);

    
    //UI_Common_Draw_AscStr_textbox(temp_ram,15,diagram_start_y+6,120,12,12,APP_COLOR_WHITE,"4Hours",6,ENUM_TEXTBOX_CENTER);

    UI_Common_AddBWsourcePic(temp_ram,35,diagram_start_y+6,(uint8_t*)gchinesefont_detail_4Hours,APP_COLOR_BLACK,APP_COLOR_WHITE);

    UI_Display_Prepare(temp_ram);

}


void UI_Screen_Heartrate_Detail_Entry(void)
{

    UI_Screen_Heartrate_Detail_Display();

    UI_Common_set_key_handle(UI_Screen_Heartrate_Detail_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Heartrate_Detail_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Heartrate_Detail_tpupslidehandle,
                                    UI_Screen_Heartrate_Detail_tpdownslidehandle,
                                    UI_Screen_Heartrate_Detail_tpleftslidehandle,
                                    UI_Screen_Heartrate_Detail_tprightslidehandle);
    
}

void UI_Screen_Heartrate_Detail_Exit(void)
{


}

void UI_Screen_Heartrate_Detail_shortkeyhandle(void)
{
    UI_Screen_Heartrate_Detail_Exit();
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}

void UI_Screen_Heartrate_Detail_holdshortkeyhandle(void)
{
}

void UI_Screen_Heartrate_Detail_holdlongkeyhandle(void)
{
}

void UI_Screen_Heartrate_Detail_tpclickhandle(int point_x,int point_y)
{

    //判断点的范围

}

void UI_Screen_Heartrate_Detail_tpupslidehandle(void)
{



}

void UI_Screen_Heartrate_Detail_tpdownslidehandle(void)
{

}

void UI_Screen_Heartrate_Detail_tpleftslidehandle(void)
{
}

void UI_Screen_Heartrate_Detail_tprightslidehandle(void)
{

    UI_Screen_Heartrate_Detail_Exit();
    //curr_run_screen_info.run_type = ENUM_MOVE_OUT;
    UI_Common_Show_RunScreen_Prepare(ENUM_MOVE_OUT);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Heartrate);
    UI_Screen_draw_Screen();

}




