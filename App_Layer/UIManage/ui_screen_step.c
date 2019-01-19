

#include "ui_screen_step.h"


const uint8_t image_floor_24_h[] = {
24,24,
0x00, 0x00, 0x00, /* scanline 1 */
0x00, 0x00, 0x00, /* scanline 2 */
0x00, 0x00, 0x00, /* scanline 3 */
0x00, 0x00, 0x00, /* scanline 4 */
0x00, 0x00, 0x00, /* scanline 5 */
0x00, 0x01, 0xFC, /* scanline 6 */
0x00, 0x01, 0xFC, /* scanline 7 */
0x00, 0x01, 0xFC, /* scanline 8 */
0x00, 0x01, 0xC0, /* scanline 9 */
0x00, 0x1F, 0xC0, /* scanline 10 */
0x00, 0x1F, 0xC0, /* scanline 11 */
0x00, 0x1F, 0xC0, /* scanline 12 */
0x00, 0x1C, 0x00, /* scanline 13 */
0x01, 0xFC, 0x00, /* scanline 14 */
0x01, 0xFC, 0x00, /* scanline 15 */
0x01, 0xFC, 0x00, /* scanline 16 */
0x01, 0xC0, 0x00, /* scanline 17 */
0x1F, 0xC0, 0x00, /* scanline 18 */
0x1F, 0xC0, 0x00, /* scanline 19 */
0x1F, 0xC0, 0x00, /* scanline 20 */
0x00, 0x00, 0x00, /* scanline 21 */
0x00, 0x00, 0x00, /* scanline 22 */
0x00, 0x00, 0x00, /* scanline 23 */
0x00, 0x00, 0x00, /* scanline 24 */
};

const uint8_t image_calorie_24_h[] = {
24,24,
0x00, 0x00, 0x00, /* scanline 1 */
0x00, 0x00, 0x00, /* scanline 2 */
0x00, 0x10, 0x00, /* scanline 3 */
0x00, 0x30, 0x00, /* scanline 4 */
0x00, 0x70, 0x00, /* scanline 5 */
0x00, 0xF8, 0x00, /* scanline 6 */
0x00, 0xFC, 0x00, /* scanline 7 */
0x01, 0xFE, 0x00, /* scanline 8 */
0x01, 0xFF, 0x80, /* scanline 9 */
0x01, 0xFF, 0xC0, /* scanline 10 */
0x01, 0xFF, 0xE0, /* scanline 11 */
0x04, 0xFF, 0xE0, /* scanline 12 */
0x0E, 0xFF, 0xF0, /* scanline 13 */
0x0F, 0xFB, 0xF0, /* scanline 14 */
0x0F, 0xF3, 0xF0, /* scanline 15 */
0x0F, 0xE1, 0xF0, /* scanline 16 */
0x0F, 0xE1, 0xF0, /* scanline 17 */
0x07, 0xC0, 0xE0, /* scanline 18 */
0x07, 0xC0, 0xE0, /* scanline 19 */
0x03, 0xC1, 0xC0, /* scanline 20 */
0x01, 0xE1, 0x80, /* scanline 21 */
0x00, 0x60, 0x00, /* scanline 22 */
0x00, 0x00, 0x00, /* scanline 23 */
0x00, 0x00, 0x00, /* scanline 24 */
};

const uint8_t image_distance_24_h[] = {
24,24,
0x00, 0x00, 0x00, /* scanline 1 */
0x00, 0x00, 0x00, /* scanline 2 */
0x00, 0x00, 0x00, /* scanline 3 */
0x00, 0x00, 0x00, /* scanline 4 */
0x00, 0x00, 0x00, /* scanline 5 */
0x00, 0x00, 0x00, /* scanline 6 */
0x3F, 0xFF, 0xFC, /* scanline 7 */
0x7F, 0xFF, 0xFE, /* scanline 8 */
0x66, 0x66, 0x66, /* scanline 9 */
0x66, 0x66, 0x66, /* scanline 10 */
0x66, 0x66, 0x66, /* scanline 11 */
0x66, 0x66, 0x66, /* scanline 12 */
0x60, 0x00, 0x06, /* scanline 13 */
0x60, 0x00, 0x06, /* scanline 14 */
0x60, 0x00, 0x06, /* scanline 15 */
0x60, 0x00, 0x06, /* scanline 16 */
0x7F, 0xFF, 0xFE, /* scanline 17 */
0x3F, 0xFF, 0xFC, /* scanline 18 */
0x00, 0x00, 0x00, /* scanline 19 */
0x00, 0x00, 0x00, /* scanline 20 */
0x00, 0x00, 0x00, /* scanline 21 */
0x00, 0x00, 0x00, /* scanline 22 */
0x00, 0x00, 0x00, /* scanline 23 */
0x00, 0x00, 0x00, /* scanline 24 */
};


void  UI_Screen_Step_Timerhandle(void)
{

    UI_Screen_Step_Display();
    UI_Common_set_timer_handle(UI_Screen_Step_Timerhandle);
    App_Lcd_TimerStart(5000);
}



void UI_Screen_Step_Display(void)
{
    //int value = 50;
    char str_content[16];
    int len=0;
	SceneStepParam_t* tpSceneStep;
    float temp_f;
    SceneStairParam_t* stairinfo;
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Step)
        return;

    UI_Common_Clear_Screen(temp_ram);


    UI_Common_set_timer_handle(UI_Screen_Step_Timerhandle);
    App_Lcd_TimerStart(5000);


	tpSceneStep = Scene_Step_ParamPGet();
    UI_Common_Draw_Annulus_Progress(temp_ram,ANNULUS_PROGRESS_CENTERX,ANNULUS_PROGRESS_CENTERY,ANNULUS_PROGRESS_LR,ANNULUS_PROGRESS_SR,APP_COLOR_CYAN,APP_COLOR_CYAN,tpSceneStep->stepComplete);
    
    UI_Common_AddBWsourcePic(temp_ram,20,120,(uint8_t*)image_distance_24_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
    UI_Common_AddBWsourcePic(temp_ram,76,120,(uint8_t*)image_calorie_24_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
    UI_Common_AddBWsourcePic(temp_ram,132,120,(uint8_t*)image_floor_24_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
    
    UI_Common_Draw_NumberImage_textbox(temp_ram,58,42,60,26,0,APP_COLOR_CYAN,tpSceneStep->totalStep);
    //UI_Common_Draw_NumberImage_textbox(lcdram,58,42,60,26,0,APP_COLOR_CYAN,55555);
    sprintf(str_content, "%d%% %d", tpSceneStep->stepComplete, tpSceneStep->stepAim);
    len=strlen(str_content);
    UI_Common_Draw_AscStr_textbox(temp_ram,40,76,96,16,16,APP_COLOR_WHITE,str_content,len,ENUM_TEXTBOX_CENTER);
    memset(str_content,0,len);
    sprintf(str_content, "%dmin", tpSceneStep->sportDuaration);
    len=strlen(str_content);
    UI_Common_Draw_AscStr_textbox(temp_ram,40,96,96,16,16,APP_COLOR_WHITE,str_content,len,ENUM_TEXTBOX_CENTER);
    memset(str_content,0,len);
    
    temp_f = (float)tpSceneStep->sportDistance/1000;
    sprintf(str_content, "%.2f", temp_f);	// DrL
    len=strlen(str_content);
    UI_Common_Draw_AscStr_textbox(temp_ram,4,148,56,16,16,APP_COLOR_WHITE,str_content,len,ENUM_TEXTBOX_CENTER);
    memset(str_content,0,len);
    sprintf(str_content, "%d", tpSceneStep->Calorie);
    len=strlen(str_content);
    UI_Common_Draw_AscStr_textbox(temp_ram,60,148,56,16,16,APP_COLOR_WHITE,str_content,len,ENUM_TEXTBOX_CENTER);

    
    stairinfo = Scene_Stair_ParamPGet();
    
    memset(str_content,0,len);
    sprintf(str_content, "%d", stairinfo->DayFloor);
    len=strlen(str_content);
    UI_Common_Draw_AscStr_textbox(temp_ram,116,148,56,16,16,APP_COLOR_WHITE,str_content,len,ENUM_TEXTBOX_CENTER);
    

    UI_Display_Prepare(temp_ram);

}


void UI_Screen_Step_Entry(void)
{


    UI_Screen_Step_Display();
    UI_Common_set_key_handle(UI_Screen_Step_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Step_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Step_tpupslidehandle,
                                    UI_Screen_Step_tpdownslidehandle,
                                    UI_Screen_Step_tpleftslidehandle,
                                    UI_Screen_Step_tprightslidehandle);

    
}

void UI_Screen_Step_Exit(void)
{

   // memset(curr_step_info,0x00,sizeof(stepSportInfo_s));

}

void UI_Screen_Step_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}

void UI_Screen_Step_holdshortkeyhandle(void)
{
}

void UI_Screen_Step_holdlongkeyhandle(void)
{
}


void UI_Screen_Step_tpclickhandle(int point_x,int point_y)
{
    //curr_run_screen_info.run_type = ENUM_MOVE_IN;
    UI_Common_Show_RunScreen_Prepare(ENUM_MOVE_IN);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Step_Detail);
    UI_Screen_draw_Screen();

}

void UI_Screen_Step_tpupslidehandle()
{

    //curr_run_screen_info.run_type = ENUM_ROUND_UP;
    UI_Common_Show_RunScreen_Prepare(ENUM_ROUND_UP);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Heartrate);
    UI_Screen_draw_Screen();


}

void UI_Screen_Step_tpdownslidehandle()
{

    //curr_run_screen_info.run_type = ENUM_ROUND_DOWN;
    UI_Common_Show_RunScreen_Prepare(ENUM_ROUND_DOWN);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}

void UI_Screen_Step_tpleftslidehandle(void)
{
}

void UI_Screen_Step_tprightslidehandle(void)
{
}


void UI_Screen_Step_Detail_Display(void)
{
    int curr_height;
    int i;

    int diagram_start_x,diagram_start_y;
    char content[16];
    int len;
    int total_step = 0;
    int max_data = 0;
	uint16_t data[24]; // = {0,500,1555,20,4210,3,300,2560,1000,905,4750,3680,4400,1456,2569,3598,205,2230,312,80,30,1400,12,32};
    uint8_t *temp_ram = UI_Display_Get_Tempram();


    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Step_Detail)
        return;

    UI_Common_Clear_Screen(temp_ram);
    
    
	/* 获取最�?4小时计步�?*/
	Store_Step_UIDataGet(data, 0);
	
    for(i= 0;i<24;i++)
    {
        total_step = total_step+data[i];
        if(data[i]>max_data)
            max_data =data[i];
    }

    UI_Common_AddBWsourcePic(temp_ram,8,6,(uint8_t*)gchinesefont_step_detail_step,APP_COLOR_BLACK,APP_COLOR_WHITE);

    sprintf(content,"%d",total_step);
    len = strlen(content);
    UI_Common_Draw_AscStr_textbox(temp_ram,88,6,80,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_RIGHT);

    diagram_start_x = 0;
    diagram_start_y = 150;

    //标线 40
    UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y,120,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+0+20-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+0+20*2-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+0+20*3-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+0+20*4-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+0+20*5-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+0+20*6-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    
    UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+120+8,diagram_start_y-6,20,12,12,APP_COLOR_WHITE,"0",1,ENUM_TEXTBOX_LEFT);


    if(max_data > 5000)
    {

        for(i=1;i<=24;i++)
        {
            if(data[24-i]<12000)
            {
                curr_height = (data[24-i]+99)/100;
            }
            else
            {

                curr_height = 120;
            }
            //UI_Common_SetPixelValue(lcdram,diagram_start_x-i*5,diagram_start_y-curr_height, APP_COLOR_RED);
            UI_Common_Draw_Vline(temp_ram,diagram_start_x+(i-1)*5,diagram_start_y-curr_height,curr_height,4,APP_COLOR_CYAN,TRUE);
        }
        //标线1 60
        UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y- 50,120,1,APP_COLOR_WHITE,false);
        UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+120+8,diagram_start_y- 50 -6,20,12,12,APP_COLOR_WHITE,"5000",4,ENUM_TEXTBOX_LEFT);

        //标线1 120
        UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y- 100,120,1,APP_COLOR_WHITE,false);
        UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+120+8,diagram_start_y- 100 -6,20,12,12,APP_COLOR_WHITE,"10000",5,ENUM_TEXTBOX_LEFT);
        
    }
    else 
    {
        for(i=1;i<=24;i++)
        {
            curr_height = (data[24-i]+49)/50;
            //UI_Common_SetPixelValue(lcdram,diagram_start_x-i*5,diagram_start_y-curr_height, APP_COLOR_RED);
            UI_Common_Draw_Vline(temp_ram,diagram_start_x+(i-1)*5,diagram_start_y-curr_height,curr_height,4,APP_COLOR_CYAN,TRUE);
        }
        //标线1 60
        UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y- 50,120,1,APP_COLOR_WHITE,false);
        UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+(i-1)*5,diagram_start_y- 50 -6,20,12,12,APP_COLOR_WHITE,"2500",4,ENUM_TEXTBOX_LEFT);
        
        //标线1 120
        UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y- 100,120,1,APP_COLOR_WHITE,false);
        UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+(i-1)*5,diagram_start_y- 100 -6,20,12,12,APP_COLOR_WHITE,"5000",4,ENUM_TEXTBOX_LEFT);
    
    }

    //UI_Common_Draw_AscStr_textbox(temp_ram,15,diagram_start_y+10,120,12,12,APP_COLOR_WHITE,"24Hours",6,ENUM_TEXTBOX_CENTER);
    
    UI_Common_AddBWsourcePic(temp_ram,55,diagram_start_y+10,(uint8_t*)gchinesefont_detail_today,APP_COLOR_BLACK,APP_COLOR_WHITE);

    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_Step_Detail_Entry(void)
{


    UI_Screen_Step_Detail_Display();
    UI_Common_set_key_handle(UI_Screen_Step_Detail_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Step_Detail_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Step_Detail_tpupslidehandle,
                                    UI_Screen_Step_Detail_tpdownslidehandle,
                                    UI_Screen_Step_Detail_tpleftslidehandle,
                                    UI_Screen_Step_Detail_tprightslidehandle);

    
}

void UI_Screen_Step_Detail_Exit()
{

   // memset(curr_step_info,0x00,sizeof(stepSportInfo_s));

}

void UI_Screen_Step_Detail_shortkeyhandle()
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    
    UI_Screen_draw_Screen();

}

void UI_Screen_Step_Detail_holdshortkeyhandle(void)
{
}

void UI_Screen_Step_Detail_holdlongkeyhandle(void)
{
}


void UI_Screen_Step_Detail_tpclickhandle(int point_x,int point_y)
{

    //判断点的范围

}

void UI_Screen_Step_Detail_tpupslidehandle(void)
{



}

void UI_Screen_Step_Detail_tpdownslidehandle(void)
{


}

void UI_Screen_Step_Detail_tpleftslidehandle(void)
{
}

void UI_Screen_Step_Detail_tprightslidehandle(void)
{
    //curr_run_screen_info.run_type = ENUM_MOVE_OUT;
    UI_Common_Show_RunScreen_Prepare(ENUM_MOVE_OUT);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Step);
    UI_Screen_draw_Screen();

}



