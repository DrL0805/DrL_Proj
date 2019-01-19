

#include "ui_screen_temperature.h"


const uint8_t image_temperature_oval_h[] = {
32,32,
0x00, 0x00, 0x00, 0x00, /* scanline 1 */
0x00, 0x03, 0x80, 0x00, /* scanline 2 */
0x00, 0x07, 0xC0, 0x00, /* scanline 3 */
0x00, 0x0C, 0x60, 0x00, /* scanline 4 */
0x00, 0x19, 0x30, 0x00, /* scanline 5 */
0x00, 0x1B, 0xB7, 0xC0, /* scanline 6 */
0x00, 0x1B, 0xB7, 0xC0, /* scanline 7 */
0x00, 0x1B, 0xB0, 0x00, /* scanline 8 */
0x00, 0x1B, 0xB7, 0x80, /* scanline 9 */
0x00, 0x1B, 0xB7, 0x80, /* scanline 10 */
0x00, 0x1B, 0xB0, 0x00, /* scanline 11 */
0x00, 0x1B, 0xB7, 0xC0, /* scanline 12 */
0x00, 0x1B, 0xB7, 0xC0, /* scanline 13 */
0x00, 0x1B, 0xB0, 0x00, /* scanline 14 */
0x00, 0x1B, 0xB7, 0x00, /* scanline 15 */
0x00, 0x1B, 0xB7, 0x00, /* scanline 16 */
0x00, 0x1B, 0xB0, 0x00, /* scanline 17 */
0x00, 0x1B, 0xB7, 0xC0, /* scanline 18 */
0x00, 0x1B, 0xB7, 0xC0, /* scanline 19 */
0x00, 0x1B, 0xB0, 0x00, /* scanline 20 */
0x00, 0x33, 0x98, 0x00, /* scanline 21 */
0x00, 0x37, 0xD8, 0x00, /* scanline 22 */
0x00, 0x67, 0xCC, 0x00, /* scanline 23 */
0x00, 0x6F, 0xEC, 0x00, /* scanline 24 */
0x00, 0x67, 0xCC, 0x00, /* scanline 25 */
0x00, 0x37, 0xD8, 0x00, /* scanline 26 */
0x00, 0x31, 0x18, 0x00, /* scanline 27 */
0x00, 0x1C, 0x70, 0x00, /* scanline 28 */
0x00, 0x0F, 0xE0, 0x00, /* scanline 29 */
0x00, 0x03, 0x80, 0x00, /* scanline 30 */
0x00, 0x00, 0x00, 0x00, /* scanline 31 */
0x00, 0x00, 0x00, 0x00, /* scanline 32 */
};


bool is_check_start = FALSE;
static int curr_frame = 0;



void  UI_Screen_Temperature_Timerhandle(void)
{
    
    UI_Screen_Temperature_Display();
}




void UI_Screen_Temperature_Display(void)
{
    //static int i=0;
    Mid_IT_Param_t* curr_temperature_info;
    float progress_angle =PI/3;
    float curr_angle[12] = {0,PI/6,2*PI/6,3*PI/6,4*PI/6,5*PI/6,PI,5*PI/6,4*PI/6,3*PI/6,2*PI/6,PI/6};
    //int temp_value = 0;
    //int offset_x = 0;
    //int string_width = 0;
    //int x =8;
    char string[16];
    int string_len;
    float curr_temp;

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Temperature)
        return;

    UI_Common_Clear_Screen(temp_ram);
    
	curr_temperature_info = Mid_IT_ParamPGet();

    if(curr_temperature_info->UpdateFlg==FALSE||is_check_start==FALSE)
    {
    
        UI_Common_set_timer_handle(UI_Screen_Temperature_Timerhandle);
        App_Lcd_TimerStart(200);

        UI_Common_Draw_Annulus_Byangle(temp_ram,87,79,64,56,PI/3,5*PI/3,APP_COLOR_GREEN,FALSE);
        UI_Common_Draw_Annulus_Byangle(temp_ram,87,79,64,56,PI/3+curr_angle[curr_frame],PI/3+curr_angle[curr_frame]+progress_angle,APP_COLOR_GREEN,TRUE);
        //UI_Common_AddPic(lcdram,64,56,(uint8_t*)image_temperature_oval_h);
        UI_Common_Draw_Circle(temp_ram,87,80,24,APP_COLOR_GREEN);
        UI_Common_AddBWsourcePic(temp_ram,72,64,(uint8_t*)image_temperature_oval_h,APP_COLOR_GREEN,APP_COLOR_BLACK);
        
        UI_Common_AddBWsourcePic(temp_ram,76,36,(uint8_t*)gchinesefont_temperature,APP_COLOR_BLACK,APP_COLOR_WHITE);
        UI_Common_Draw_FontStr_textbox(temp_ram,8,120,160,48,(uint8_t *)gchinesefont_temperature_prompt,APP_COLOR_WHITE,APP_COLOR_BLACK);
        curr_frame++;
        if(curr_frame>=12)
        {
            curr_frame =0;
        }
    }
    else 
    {
        
        curr_frame=0;
        UI_Common_Draw_Annulus_Byangle(temp_ram,88,80,64,56,PI/3,5*PI/3,APP_COLOR_GREEN,TRUE);
        UI_Common_Draw_Circle(temp_ram,87,80,24,APP_COLOR_GREEN);
        UI_Common_AddBWsourcePic(temp_ram,72,64,(uint8_t*)image_temperature_oval_h,APP_COLOR_GREEN,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,76,36,(uint8_t*)gchinesefont_temperature,APP_COLOR_BLACK,APP_COLOR_WHITE);

        curr_temp = curr_temperature_info->CurrTemp/10;
        sprintf(string,"%0.1fC",curr_temp);
        string_len = strlen(string);
        UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,8,117,160,26,APP_COLOR_WHITE,string,string_len,26,ENUM_TEXTBOX_CENTER);
         #if 0
            if(curr_temperature_info.CurrTemp<0)
            {
                string_width = string_width+font_tgl_32_hyphen_h[0];
                temp_value = 0-curr_temperature_info.CurrTemp;
            }
            else
            {
                temp_value = curr_temperature_info.CurrTemp;
            }
            
            if(temp_value>=10)
                string_width = string_width+12*2;
            else
                string_width = string_width+12*1;

                string_width = string_width+font_tgl_32_celsius_h[0];

            offset_x= (160-string_width)/2;

            x=x+offset_x;

            if(curr_temperature_info.CurrTemp<0)
            {
                UI_Common_AddBWsourcePic(lcdram,x,117,(uint8_t*)font_tgl_32_hyphen_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
                x=x+font_tgl_32_hyphen_h[0];
            }

            if(temp_value>=10)
            {
                UI_Common_Draw_NumberImage_textbox(lcdram,x,117,24,26,0,APP_COLOR_WHITE,temp_value);
                x=x+24;
            }
            else
            {
                UI_Common_Draw_NumberImage_textbox(lcdram,x,117,12,26,0,APP_COLOR_WHITE,temp_value);
                x=x+24;
            }
                UI_Common_AddBWsourcePic(lcdram,x,117,(uint8_t*)font_tgl_32_celsius_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            #endif
       }

    UI_Display_Prepare(temp_ram);
    
}



void UI_Screen_Temperature_Entry(void)
{

    is_check_start = FALSE;
    curr_frame = 0;
    
    UI_Screen_Temperature_Display();
    
    UI_Common_set_key_handle(UI_Screen_Temperature_shortkeyhandle,UI_Screen_Temperature_holdshortkeyhandle,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Temperature_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Temperature_tpupslidehandle,
                                    UI_Screen_Temperature_tpdownslidehandle,
                                    UI_Screen_Temperature_tpleftslidehandle,
                                    UI_Screen_Temperature_tprightslidehandle);
}

void UI_Screen_Temperature_Exit(void)
{
    is_check_start = FALSE;
    App_Lcd_TimerStop();
    UI_Common_set_timer_handle(NULL);
    
}

void UI_Screen_Temperature_shortkeyhandle(void)
{

    UI_Screen_Temperature_Exit();
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}

void UI_Screen_Temperature_holdshortkeyhandle(void)
{
    is_check_start = TRUE;
    Mid_IT_ConverStart();
}

void UI_Screen_Temperature_holdlongkeyhandle(void)
{
}

void UI_Screen_Temperature_tpclickhandle(int point_x,int point_y)
{
    UI_Screen_Temperature_Exit();
    
    //curr_run_screen_info.run_type = ENUM_MOVE_IN;
    UI_Common_Show_RunScreen_Prepare(ENUM_MOVE_IN);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Temperature_Detail);
    UI_Screen_draw_Screen();
    

}

void UI_Screen_Temperature_tpupslidehandle(void)
{
    UI_Screen_Temperature_Exit();
    //curr_run_screen_info.run_type = ENUM_ROUND_UP;
    UI_Common_Show_RunScreen_Prepare(ENUM_ROUND_UP);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Sleep);
    UI_Screen_draw_Screen();


}

void UI_Screen_Temperature_tpdownslidehandle(void)
{

    UI_Screen_Temperature_Exit();
    
    //curr_run_screen_info.run_type = ENUM_ROUND_DOWN;
    UI_Common_Show_RunScreen_Prepare(ENUM_ROUND_DOWN);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Pressure);
    UI_Screen_draw_Screen();

}

void UI_Screen_Temperature_tpleftslidehandle(void)
{
}

void UI_Screen_Temperature_tprightslidehandle(void)
{
}


void UI_Screen_Temperature_Detail_Display(void)
{


    int16_t data[144] = {0};

    //float curr_data;
    int i =1;//j;
    //int max_data =0;
    //120 +18(标尺) + 4（gap）=142 x =（ 176-142）/2
    int diagram_start_x,diagram_start_y;
    //char content[16];
    //int len;
    int curr_height;
    int low_value = 320;
    int height_value = 420;
    int line_len = 1;
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Temperature_Detail)
        return;

    UI_Common_Clear_Screen(temp_ram);

    Store_Bodytemp_UIDataGet(data,144);

    UI_Common_AddBWsourcePic(temp_ram,8,6,(uint8_t*)gchinesefont_temperature_shelltemperature,APP_COLOR_BLACK,APP_COLOR_WHITE);

    #if 0
    curr_data = (float)data[0]/10;
    sprintf(content,"%0.1f",curr_data);
    len = strlen(content);
    UI_Common_Draw_AscStr_textbox(lcdram,88,6,80,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_RIGHT);
    #endif

    diagram_start_x = 0;
    diagram_start_y = 145;


    UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y,144,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+36-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+36*2-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+36*3-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+36*4-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    
    // UI_Common_Draw_AscStr_textbox(lcdram,diagram_start_x+144+8,diagram_start_y-6,20,12,12,APP_COLOR_WHITE,"0",1,ENUM_TEXTBOX_LEFT);
    
    for(i=1;i<=144;i++)
    {

        if(data[144-i]<=low_value)
        {
            curr_height = 0;
        }
        else if(data[144-i]>=height_value)
        {
            curr_height =100;
        }
        else
        {
            curr_height = data[144-i]-low_value;
        }


        if(i == 1)
        {

            if(data[144-i] <=data[144-i-1])
            {
                line_len = 1;
            }
            else
            {

                line_len = data[144-i] - data[144-i-1];
            }
        
        }
        else if(i == 144)
        {
            if(data[144-i] <=data[144-i+1])
            {
                line_len = 1;
            }
            else
            {
                line_len = data[144-i-1] - data[144-i+1];
            }
        }
        else
        {

            if(data[144-i-1] <= data[144-i+1])
            {
                if(data[144-i] <= data[144-i-1])
                {
                    line_len = 1;
                }
                else
                {

                    line_len = data[144-i] - data[144-i-1];
                }
            }
            else
            {


                if(data[144-i] <= data[144-i+1])
                {
                    line_len = 1;
                }
                else
                {

                    line_len = data[144-i] - data[144-i+1];
                }

            }

        
        }


        
        UI_Common_SetPixelValue(temp_ram,diagram_start_x+i-1,diagram_start_y-curr_height, APP_COLOR_GREEN);
        UI_Common_SetPixelValue(temp_ram,diagram_start_x+i-1,diagram_start_y-curr_height-1, APP_COLOR_GREEN);
        UI_Common_Draw_Vline(temp_ram,diagram_start_x+i-1,diagram_start_y-curr_height,line_len,1,APP_COLOR_GREEN,TRUE);
        
    }
    
    //UI_Common_Draw_AscStr_textbox(temp_ram,15,diagram_start_y+10,120,12,12,APP_COLOR_WHITE,"24Hours",7,ENUM_TEXTBOX_CENTER);
    UI_Common_AddBWsourcePic(temp_ram,35,diagram_start_y+10,(uint8_t*)gchinesefont_detail_24Hours,APP_COLOR_BLACK,APP_COLOR_WHITE);
    
    UI_Display_Prepare(temp_ram);


}


void UI_Screen_Temperature_Detail_Entry(void)
{

    UI_Screen_Temperature_Detail_Display();
    
    UI_Common_set_key_handle(UI_Screen_Temperature_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Temperature_Detail_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Temperature_Detail_tpupslidehandle,
                                    UI_Screen_Temperature_Detail_tpdownslidehandle,
                                    UI_Screen_Temperature_Detail_tpleftslidehandle,
                                    UI_Screen_Temperature_Detail_tprightslidehandle);
}

void UI_Screen_Temperature_Detail_Exit(void)
{


}

void UI_Screen_Temperature_Detail_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}

void UI_Screen_Temperature_Detail_holdshortkeyhandle(void)
{
    is_check_start = TRUE;
    Mid_IT_ConverStart();
}

void UI_Screen_Temperature_Detail_holdlongkeyhandle(void)
{
}

void UI_Screen_Temperature_Detail_tpclickhandle(int point_x,int point_y)
{

    //判断点的范围

}

void UI_Screen_Temperature_Detail_tpupslidehandle(void)
{


}

void UI_Screen_Temperature_Detail_tpdownslidehandle(void)
{


}

void UI_Screen_Temperature_Detail_tpleftslidehandle(void)
{
}

void UI_Screen_Temperature_Detail_tprightslidehandle(void)
{

    //curr_run_screen_info.run_type = ENUM_MOVE_OUT;
    UI_Common_Show_RunScreen_Prepare(ENUM_MOVE_OUT);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Temperature);
    UI_Screen_draw_Screen();


}



