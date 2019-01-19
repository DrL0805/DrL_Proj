#include "ui_screen_pressure.h"
#include "ui_screen_dateandtime.h"


const uint8_t image_stress_oval_h[] = {
32,32,
0x00, 0x00, 0x00, 0x00, /* scanline 1 */
0x00, 0x00, 0x00, 0x00, /* scanline 2 */
0x00, 0x00, 0x00, 0x00, /* scanline 3 */
0x00, 0x00, 0x00, 0x00, /* scanline 4 */
0x00, 0x00, 0x00, 0x00, /* scanline 5 */
0x00, 0x00, 0x00, 0x00, /* scanline 6 */
0x00, 0x00, 0x00, 0x00, /* scanline 7 */
0x00, 0x00, 0x00, 0x00, /* scanline 8 */
0x02, 0x00, 0x00, 0x40, /* scanline 9 */
0x07, 0x00, 0x00, 0xE0, /* scanline 10 */
0x03, 0x80, 0x01, 0xC0, /* scanline 11 */
0x01, 0xC0, 0x03, 0x80, /* scanline 12 */
0x01, 0xC0, 0x03, 0x80, /* scanline 13 */
0x03, 0x80, 0x01, 0xC0, /* scanline 14 */
0x07, 0x00, 0x00, 0xE0, /* scanline 15 */
0x02, 0x00, 0x00, 0x40, /* scanline 16 */
0x00, 0x00, 0x00, 0x00, /* scanline 17 */
0x00, 0x00, 0x00, 0x00, /* scanline 18 */
0x00, 0x00, 0x00, 0x00, /* scanline 19 */
0x00, 0x00, 0x00, 0x00, /* scanline 20 */
0x00, 0x00, 0x00, 0x00, /* scanline 21 */
0x00, 0x00, 0x00, 0x00, /* scanline 22 */
0x00, 0x3F, 0xFC, 0x00, /* scanline 23 */
0x00, 0x7F, 0xFE, 0x00, /* scanline 24 */
0x00, 0x60, 0x06, 0x00, /* scanline 25 */
0x00, 0x7F, 0xFE, 0x00, /* scanline 26 */
0x00, 0x3F, 0xFC, 0x00, /* scanline 27 */
0x00, 0x00, 0x00, 0x00, /* scanline 28 */
0x00, 0x00, 0x00, 0x00, /* scanline 29 */
0x00, 0x00, 0x00, 0x00, /* scanline 30 */
0x00, 0x00, 0x00, 0x00, /* scanline 31 */
0x00, 0x00, 0x00, 0x00, /* scanline 32 */
};



#if 0
void UI_Screen_Pressure_Display(uint8_t *lcdram)
{

    UI_Common_AddBWsourcePic(lcdram,0,0,(uint8_t*)bg_circle_hollow_h,APP_COLOR_BLACK,APP_COLOR_YELLOW);
    //UI_Common_Draw_Annulus_Byangle(lcdram,87,80,65,60,min_progress_angle,max_progress_angle,APP_COLOR_YELLOW,FALSE);
    //UI_Common_Draw_Annulus_Byangle(lcdram,87,80,65,60,min_progress_angle,PI/2,APP_COLOR_YELLOW,TRUE);
    UI_Common_AddPic(lcdram,64,56,(uint8_t*)image_stress_oval_h);
    UI_Common_AddBWsourcePic(lcdram,76,36,(uint8_t*)gchinesefont_pressure,APP_COLOR_BLACK,APP_COLOR_WHITE);

}
#endif

bool is_pressure_init = FALSE;

static int curr_frame = 0;

void  UI_Screen_Pressure_Timerhandle(void)
{    
    UI_Screen_Pressure_Display();
}

void UI_Screen_Pressure_Display(void)
{
    //char str_content[16];
    //int len;
    //static int i=0;
    float progress_angle =PI/3;
    float curr_angle[12] = {0,PI/6,2*PI/6,3*PI/6,4*PI/6,5*PI/6,PI,5*PI/6,4*PI/6,3*PI/6,2*PI/6,PI/6};
    Scene_Stress_Param_t* Scene_Stress_info;
    uint8_t* fontinfo;
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    static int curr_remind = 0;

    
    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Pressure)
        return;

    UI_Common_Clear_Screen(temp_ram);
    
    Scene_Stress_info = Scene_Stress_ParamPGet();

    if(is_pressure_init == FALSE||Scene_Stress_info->UpdateFlg == FALSE)
    {

            UI_Common_set_timer_handle(UI_Screen_Pressure_Timerhandle);
            App_Lcd_TimerStart(200);
            UI_Common_Draw_Annulus_Byangle(temp_ram,87,79,64,56,PI/3,5*PI/3,APP_COLOR_YELLOW,FALSE);
            UI_Common_Draw_Annulus_Byangle(temp_ram,87,79,64,56,PI/3+curr_angle[curr_frame],PI/3+curr_angle[curr_frame]+progress_angle,APP_COLOR_YELLOW,TRUE);
            curr_frame++;
            if(curr_frame>=12)
            {
                curr_remind++;
                curr_frame =0;
            }
            if((is_pressure_init==FALSE)&&(curr_frame>=10))
            {
                curr_remind =0;
                is_pressure_init = TRUE;
                //不允许进入休眠状态
                UI_Commom_Set_Allow_Lockstate1(0);
				Scene_Stress_SampleStart(eSceneMeasureIM);
            }
            //UI_Common_AddPic(lcdram,64,56,(uint8_t*)image_stress_oval_h);
            UI_Common_Draw_Circle(temp_ram,87,80,24,APP_COLOR_YELLOW);
            UI_Common_AddBWsourcePic(temp_ram,72,64,(uint8_t*)image_stress_oval_h,APP_COLOR_YELLOW,APP_COLOR_BLACK);
            UI_Common_AddBWsourcePic(temp_ram,76,36,(uint8_t*)gchinesefont_pressure,APP_COLOR_BLACK,APP_COLOR_WHITE);
            
            UI_Common_AddBWsourcePic(temp_ram,75,117,(uint8_t*)font_tgl_32_hyphen_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            UI_Common_AddBWsourcePic(temp_ram,88,117,(uint8_t*)font_tgl_32_hyphen_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            

            UI_Common_AddBWsourcePic(temp_ram,75,117,(uint8_t*)font_tgl_32_hyphen_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            UI_Common_AddBWsourcePic(temp_ram,88,117,(uint8_t*)font_tgl_32_hyphen_h,APP_COLOR_BLACK,APP_COLOR_WHITE);

            //gchinesefont_wearingremind
            if(curr_remind%2==0)
            {
                UI_Common_Draw_FontStr_textbox(temp_ram,8,150,160,16,(uint8_t *)gchinesefont_testing,APP_COLOR_WHITE,APP_COLOR_BLACK);
            }
            else
            {
                UI_Common_Draw_FontStr_textbox(temp_ram,8,150,160,16,(uint8_t *)gchinesefont_wearingremind,APP_COLOR_WHITE,APP_COLOR_BLACK);
            }
        
    }
    else
    {
            
            if(Scene_Stress_info->CurrStress.score== STRESS_INVALID_SCORE)
            {
                //压力检测失败 震动一次
                UI_Common_Shake();
            
                UI_Common_Draw_Annulus_Byangle(temp_ram,87,79,64,56,PI/3,5*PI/3,APP_COLOR_YELLOW,FALSE);
                UI_Common_AddBWsourcePic(temp_ram,76,36,(uint8_t*)gchinesefont_pressure,APP_COLOR_BLACK,APP_COLOR_WHITE);
                UI_Common_Draw_Circle(temp_ram,87,80,24,APP_COLOR_YELLOW);
                UI_Common_AddBWsourcePic(temp_ram,72,64,(uint8_t*)image_stress_oval_h,APP_COLOR_YELLOW,APP_COLOR_BLACK);
                UI_Common_AddBWsourcePic(temp_ram,75,117,(uint8_t*)font_tgl_32_hyphen_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
                UI_Common_AddBWsourcePic(temp_ram,88,117,(uint8_t*)font_tgl_32_hyphen_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
                //gchinesefont_wearingremind
                UI_Common_Draw_FontStr_textbox(temp_ram,8,150,160,16,(uint8_t *)gchinesefont_wearingremind2,APP_COLOR_WHITE,APP_COLOR_BLACK);
                
            }
            else
            {

                UI_Common_Draw_Annulus_Byangle(temp_ram,87,79,64,56,PI/3,5*PI/3,APP_COLOR_YELLOW,TRUE);
                UI_Common_Draw_Circle(temp_ram,87,80,24,APP_COLOR_YELLOW);
                UI_Common_AddBWsourcePic(temp_ram,72,64,(uint8_t*)image_stress_oval_h,APP_COLOR_YELLOW,APP_COLOR_BLACK);
                UI_Common_AddBWsourcePic(temp_ram,76,36,(uint8_t*)gchinesefont_pressure,APP_COLOR_BLACK,APP_COLOR_WHITE);

                if(Scene_Stress_info->CurrStress.score == 0)
                {
                    //sprintf(str_content,"--");
                    //len=strlen(str_content);
                    //UI_Common_Draw_AscStr_textbox(temp_ram,8,117,160,16,16,APP_COLOR_WHITE,str_content,len,ENUM_TEXTBOX_CENTER);
                    
                    UI_Common_AddBWsourcePic(temp_ram,75,117,(uint8_t*)font_tgl_32_hyphen_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
                    UI_Common_AddBWsourcePic(temp_ram,88,117,(uint8_t*)font_tgl_32_hyphen_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
                    
                
                }
                else
                {
                    UI_Common_Draw_NumberImage_textbox(temp_ram,8,117,160,26,0,APP_COLOR_WHITE,Scene_Stress_info->CurrStress.score);
                }

                switch(Scene_Stress_info->CurrStress.level)
                {
                    case 0:
                        fontinfo = (uint8_t *)gchinesefont_moderate;
                        break;                
                    case 1:
                        fontinfo = (uint8_t *)gchinesefont_low;
                        break;                
                    case 2:
                        fontinfo = (uint8_t *)gchinesefont_middle;
                        break;                
                    case 3:
                        fontinfo = (uint8_t *)gchinesefont_high;
                        break;                
                    default:
                        fontinfo = (uint8_t *)gchinesefont_low;
                        break;                
                }
                
                UI_Common_Draw_FontStr_textbox(temp_ram,8,150,160,16,(uint8_t *)fontinfo,APP_COLOR_WHITE,APP_COLOR_BLACK);
            }

            //有结果后，解除不允许进入休眠状态
            UI_Commom_Set_Allow_Lockstate1(1);

            UI_Common_set_timer_handle(NULL);
            
    }

    UI_Display_Prepare(temp_ram);

}


void UI_Screen_Pressure_Entry(void)
{

    is_pressure_init = FALSE;
    
    UI_Screen_Pressure_Display();
    UI_Common_set_key_handle(UI_Screen_Pressure_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Pressure_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Pressure_tpupslidehandle,
                                    UI_Screen_Pressure_tpdownslidehandle,
                                    UI_Screen_Pressure_tpleftslidehandle,
                                    UI_Screen_Pressure_tprightslidehandle);
    
    
}

void UI_Screen_Pressure_Exit(void)
{

    curr_frame =0;
    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();

    if(is_pressure_init == TRUE)
    {
        Scene_Stress_SampleStop(eSceneMeasureIM);
        is_pressure_init = FALSE;
        //有结果后，解除不允许进入休眠状态
        UI_Commom_Set_Allow_Lockstate1(1);
    }
}

void UI_Screen_Pressure_shortkeyhandle(void)
{
    UI_Screen_Pressure_Exit();
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);

    UI_Screen_draw_Screen();

}

void UI_Screen_Pressure_holdshortkeyhandle(void)
{
}

void UI_Screen_Pressure_holdlongkeyhandle(void)
{
}

void UI_Screen_Pressure_tpclickhandle(int point_x,int point_y)
{

    //判断点的范围
    UI_Screen_Pressure_Exit();
    //curr_run_screen_info.run_type = ENUM_MOVE_IN;
    UI_Common_Show_RunScreen_Prepare(ENUM_MOVE_IN);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Pressure_Detail);
    UI_Screen_draw_Screen();
    

}

void UI_Screen_Pressure_tpupslidehandle(void)
{
    UI_Screen_Pressure_Exit();
    //curr_run_screen_info.run_type = ENUM_ROUND_UP;
    UI_Common_Show_RunScreen_Prepare(ENUM_ROUND_UP);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Temperature);
    UI_Screen_draw_Screen();


}

void UI_Screen_Pressure_tpdownslidehandle(void)
{
    UI_Screen_Pressure_Exit();
    //curr_run_screen_info.run_type = ENUM_ROUND_DOWN;
    UI_Common_Show_RunScreen_Prepare(ENUM_ROUND_DOWN);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Heartrate);
    UI_Screen_draw_Screen();

}

void UI_Screen_Pressure_tpleftslidehandle(void)
{
}

void UI_Screen_Pressure_tprightslidehandle(void)
{
}



void UI_Screen_Pressure_Detail_Display(void)
{
    uint8 data[144] = {80 ,76  ,98  ,98  ,67  ,65  ,69  ,71  ,71  ,71  ,63  ,62  ,63  ,59  ,62  ,64  ,64  ,63  ,62  ,63  ,63  ,63  ,62  ,60  ,62  ,58  ,60  ,62  ,59  ,60  ,62  ,59  ,62  ,62  ,61  ,61  ,
        58  ,69  ,59  ,64  ,81  ,61  ,63  ,85  ,64  ,57  ,59  ,60  ,59  ,60  ,59  ,60  ,56  ,56  ,59  ,58  ,56  ,56  ,56  ,57  ,57  ,58  ,56  ,59  ,55  ,57  ,55  ,57  ,57  ,57  ,55  ,
        55  ,56  ,55  ,55  ,55  ,53  ,56  ,54  ,56  ,55  ,57  ,56  ,84  ,58  ,60  ,53  ,55  ,61  ,58  ,63  ,63  ,58  ,72  ,58  ,57  ,63  ,57  ,68  ,56  ,56  ,63  ,57  ,60  ,62  ,60  ,66  ,59  ,57  ,
        53  ,61  ,52  ,73  ,57  ,58  ,56  ,57  ,55  ,56  ,57  ,58  ,56  ,57  ,55  ,56,58  ,56  ,57  ,55  ,56,58  ,56  ,57  ,55  ,80 ,76  ,98  ,98  ,67  ,65  ,69  ,71  ,71 };

    int curr_data;
    int i;//j;

    int diagram_start_x,diagram_start_y;
    char content[16];
    int len;
    uint8_t *temp_ram = UI_Display_Get_Tempram();


    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Pressure_Detail)
        return;

    UI_Common_Clear_Screen(temp_ram);

    

    Store_Stress_UIDataGet(data,144);

    UI_Common_AddBWsourcePic(temp_ram,8,6,(uint8_t*)gchinesefont_pressure_detail_pressure,APP_COLOR_BLACK,APP_COLOR_WHITE);


    if(data[0] == 0)
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
    diagram_start_y = 140;

    //标线 40
    UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y,144,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+36-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+36*2-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+36*3-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+36*4-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    
    UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+144+8,diagram_start_y-6,20,12,12,APP_COLOR_WHITE,"0",1,ENUM_TEXTBOX_LEFT);
    
    for(i=1;i<=144;i++)
    {
    
        curr_data = data[144-i];
        UI_Common_SetPixelValue(temp_ram,diagram_start_x+i-1,diagram_start_y-curr_data, APP_COLOR_RED);
        UI_Common_Draw_Vline(temp_ram,diagram_start_x+i-1,diagram_start_y-curr_data,curr_data,1,APP_COLOR_RED,TRUE);
        
    }

    //标线1 60
    UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y- 25,135,1,APP_COLOR_WHITE,false);
    UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+144+8,diagram_start_y- 25 -6,20,12,12,APP_COLOR_WHITE,"25",2,ENUM_TEXTBOX_LEFT);

    //标线1 120
    UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y- 50,135,1,APP_COLOR_WHITE,false);
    UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+144+8,diagram_start_y- 50 -6,20,12,12,APP_COLOR_WHITE,"50",2,ENUM_TEXTBOX_LEFT);

    //标线1 180
    UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y- 75,135,1,APP_COLOR_WHITE,false);
    UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+144+8,diagram_start_y- 75 -6,20,12,12,APP_COLOR_WHITE,"75",2,ENUM_TEXTBOX_LEFT);
    
    //UI_Common_Draw_AscStr_textbox(temp_ram,15,diagram_start_y+10,120,12,12,APP_COLOR_WHITE,"24Hours",7,ENUM_TEXTBOX_CENTER);

    UI_Common_AddBWsourcePic(temp_ram,32,diagram_start_y+10,(uint8_t*)gchinesefont_detail_24Hours,APP_COLOR_BLACK,APP_COLOR_WHITE);
    
    UI_Display_Prepare(temp_ram);
    
}


void UI_Screen_Pressure_Detail_Entry(void)
{

    UI_Screen_Pressure_Detail_Display();

    UI_Common_set_key_handle(UI_Screen_Pressure_Detail_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Pressure_Detail_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Pressure_Detail_tpupslidehandle,
                                    UI_Screen_Pressure_Detail_tpdownslidehandle,
                                    UI_Screen_Pressure_Detail_tpleftslidehandle,
                                    UI_Screen_Pressure_Detail_tprightslidehandle);
    
}

void UI_Screen_Pressure_Detail_Exit(void)
{


}

void UI_Screen_Pressure_Detail_shortkeyhandle(void)
{
    UI_Screen_Pressure_Detail_Exit();
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}

void UI_Screen_Pressure_Detail_holdshortkeyhandle(void)
{
}

void UI_Screen_Pressure_Detail_holdlongkeyhandle(void)
{
}

void UI_Screen_Pressure_Detail_tpclickhandle(int point_x,int point_y)
{

    //判断点的范围

}

void UI_Screen_Pressure_Detail_tpupslidehandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_BreathTraining);
    
    UI_Screen_draw_Screen();

}

void UI_Screen_Pressure_Detail_tpdownslidehandle(void)
{

}

void UI_Screen_Pressure_Detail_tpleftslidehandle(void)
{
}

void UI_Screen_Pressure_Detail_tprightslidehandle(void)
{
    //curr_run_screen_info.run_type = ENUM_MOVE_OUT;
    UI_Common_Show_RunScreen_Prepare(ENUM_MOVE_OUT);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Pressure);
    UI_Screen_draw_Screen();

}







