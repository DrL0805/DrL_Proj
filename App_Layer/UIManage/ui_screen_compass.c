#include "ui_screen_compass.h"
#include "ui_screen_dateandtime.h"


const uint8_t image_compass_oval_h[] = {
32,32,
0x00, 0x00, 0x00, 0x00, /* scanline 1 */
0x00, 0x00, 0x00, 0x00, /* scanline 2 */
0x00, 0x00, 0x00, 0x00, /* scanline 3 */
0x00, 0x01, 0x80, 0x00, /* scanline 4 */
0x00, 0x01, 0x80, 0x00, /* scanline 5 */
0x00, 0x03, 0xC0, 0x00, /* scanline 6 */
0x00, 0x03, 0xC0, 0x00, /* scanline 7 */
0x00, 0x07, 0xE0, 0x00, /* scanline 8 */
0x00, 0x07, 0xE0, 0x00, /* scanline 9 */
0x00, 0x07, 0xE0, 0x00, /* scanline 10 */
0x00, 0x0F, 0xF0, 0x00, /* scanline 11 */
0x00, 0x0F, 0xF0, 0x00, /* scanline 12 */
0x00, 0x1F, 0xF8, 0x00, /* scanline 13 */
0x00, 0x1F, 0xF8, 0x00, /* scanline 14 */
0x00, 0x1F, 0xF8, 0x00, /* scanline 15 */
0x00, 0x3F, 0xFC, 0x00, /* scanline 16 */
0x00, 0x3F, 0xFC, 0x00, /* scanline 17 */
0x00, 0x7F, 0xFE, 0x00, /* scanline 18 */
0x00, 0x7F, 0xFE, 0x00, /* scanline 19 */
0x00, 0x7F, 0xFE, 0x00, /* scanline 20 */
0x00, 0xFF, 0xFF, 0x00, /* scanline 21 */
0x00, 0xFF, 0xFF, 0x00, /* scanline 22 */
0x01, 0xFF, 0xFF, 0x80, /* scanline 23 */
0x01, 0xFF, 0xFF, 0x80, /* scanline 24 */
0x03, 0xFE, 0x7F, 0xC0, /* scanline 25 */
0x03, 0xF0, 0x0F, 0xC0, /* scanline 26 */
0x03, 0xC0, 0x03, 0xC0, /* scanline 27 */
0x00, 0x00, 0x00, 0x00, /* scanline 28 */
0x00, 0x00, 0x00, 0x00, /* scanline 29 */
0x00, 0x00, 0x00, 0x00, /* scanline 30 */
0x00, 0x00, 0x00, 0x00, /* scanline 31 */
0x00, 0x00, 0x00, 0x00, /* scanline 32 */
};





void UI_Screen_Compass_Getpointbyangle(int x,int y,int r,double angle,int*x_n,int*y_n,int*x_e,int*y_e,int*x_s,int*y_s,int*x_w,int*y_w)
{
    double temp_angle = angle*2*PI/360;
    float temp_sin = Algorithm_sin(temp_angle);
    float temp_cos = Algorithm_cos(temp_angle);

    *x_n = x-r*temp_sin;
    *y_n = y-r*temp_cos;

    *x_s = x+r*temp_sin;
    *y_s = y+r*temp_cos;

    *x_e = x+r*temp_cos;
    *y_e = y-r*temp_sin;

    *x_w = x-r*temp_cos;
    *y_w = y+r*temp_sin;

    
}


void  UI_Screen_Compass_Timerhandle(void)
{
    
    UI_Screen_Compass_Display();
}

void UI_Screen_Compass_Display(void)
{

    int x_n,y_n;
    int x_e,y_e;
    int x_s,y_s;
    int x_w,y_w;
    calState_e state;
    uint16_t curr_angle;
    ab_value_t curr_ab_value;
    char content[16];
    int len;
    int temp_value;

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Compass)
        return;

    UI_Common_Clear_Screen(temp_ram);

    Scene_ABC_ABGet(&curr_ab_value);

    state = Scene_ABC_CompassAngleGet(&curr_angle);
    
    
    if(state == COMPASS_CAL_DONE)
    {
    
        UI_Screen_Compass_Getpointbyangle(87,79,60,curr_angle,&x_n,&y_n,&x_e,&y_e,&x_s,&y_s,&x_w,&y_w);
        
        //UI_Common_Draw_FontStr_textbox(lcdram,4,42,168,86,APP_COLOR_WHITE,(uint8_t *)gchinesefont_compass_prompt);

        UI_Common_Draw_Annulus_Byangle(temp_ram,87,79,64,56,PI/3,5*PI/3,APP_COLOR_YELLOW,TRUE);

        if(y_n<=100)
        {
            UI_Common_AddBWsourcePic(temp_ram,x_n-16,y_n-16,(uint8_t*)image_compass_north_h,APP_COLOR_WHITE,APP_COLOR_BLACK);
        }

        if(y_e<=100)
        {
            UI_Common_AddBWsourcePic(temp_ram,x_e-16,y_e-16,(uint8_t*)image_compass_east_h,APP_COLOR_WHITE,APP_COLOR_BLACK);
        }
        
        if(y_s<=100)
        {
            UI_Common_AddBWsourcePic(temp_ram,x_s-16,y_s-16,(uint8_t*)image_compass_south_h,APP_COLOR_WHITE,APP_COLOR_BLACK);
        }
        
        if(y_w<=100)
        {
            UI_Common_AddBWsourcePic(temp_ram,x_w-16,y_w-16,(uint8_t*)image_compass_west_h,APP_COLOR_WHITE,APP_COLOR_BLACK);
        }
        
        //UI_Common_AddPic(lcdram,64,56,(uint8_t*)image_compass_oval_h);

        UI_Common_Draw_Circle(temp_ram,87,80,24,APP_COLOR_YELLOW);
        UI_Common_AddBWsourcePic(temp_ram,72,64,(uint8_t*)image_compass_oval_h,APP_COLOR_YELLOW,APP_COLOR_BLACK);
        
        UI_Common_AddBWsourcePic(temp_ram,4,137,(uint8_t*)gchinesefont_compass_elevation,APP_COLOR_BLACK,APP_COLOR_WHITE);
        UI_Common_AddBWsourcePic(temp_ram,140,137,(uint8_t*)gchinesefont_compass_kpa,APP_COLOR_BLACK,APP_COLOR_WHITE);

        temp_value = curr_angle;
        sprintf(content,"%dD",temp_value);
        len =  strlen(content);
        UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,50,117,76,26,APP_COLOR_WHITE,content,len,26,ENUM_TEXTBOX_CENTER);

        
        temp_value = curr_ab_value.altitude/100;
        sprintf(content,"%dm",temp_value);
        len =  strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,4,155,80,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        
        temp_value = curr_ab_value.pressure/100;
        sprintf(content,"%dhPa",temp_value);
        len =  strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,88+4,155,80,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_RIGHT);

    }
    else if(state == COMPASS_CAL_NONE)
    {
        Scene_ABC_CompassCalibrationStart();

        UI_Common_AddPic(temp_ram,69,30,(uint8_t *)image_compass_watch_h);
        UI_Common_Draw_Annulus(temp_ram,88,67,48,46,APP_COLOR_WHITE,TRUE);
        UI_Common_AddBWsourcePic(temp_ram,37,65,(uint8_t*)image_compass_arrow_up_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        UI_Common_AddBWsourcePic(temp_ram,130,65,(uint8_t*)image_compass_arrow_down_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        
        UI_Common_Draw_FontStr_textbox(temp_ram,4,115,168,86,(uint8_t *)gchinesefont_compass_prompt,APP_COLOR_WHITE,APP_COLOR_BLACK);
        
    }
    else if(state == COMPASS_CAL_ING)
    {

        UI_Common_AddPic(temp_ram,69,30,(uint8_t *)image_compass_watch_h);
        UI_Common_Draw_Annulus(temp_ram,88,67,48,46,APP_COLOR_WHITE,TRUE);
        UI_Common_AddBWsourcePic(temp_ram,37,65,(uint8_t*)image_compass_arrow_up_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        UI_Common_AddBWsourcePic(temp_ram,130,65,(uint8_t*)image_compass_arrow_down_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        
        UI_Common_Draw_FontStr_textbox(temp_ram,4,115,168,86,(uint8_t *)gchinesefont_compass_prompt,APP_COLOR_WHITE,APP_COLOR_BLACK);
        
    }
    else if(state == COMPASS_CAL_FAIL)
    {

        UI_Common_AddPic(temp_ram,69,30,(uint8_t *)image_compass_watch_h);
        UI_Common_Draw_Annulus(temp_ram,88,67,48,46,APP_COLOR_WHITE,TRUE);
        UI_Common_AddBWsourcePic(temp_ram,37,65,(uint8_t*)image_compass_arrow_up_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        UI_Common_AddBWsourcePic(temp_ram,130,65,(uint8_t*)image_compass_arrow_down_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        
        UI_Common_Draw_FontStr_textbox(temp_ram,4,115,168,86,(uint8_t *)gchinesefont_compass_prompt,APP_COLOR_WHITE,APP_COLOR_BLACK);
        
    }

    
    UI_Common_set_timer_handle(UI_Screen_Compass_Timerhandle);
    App_Lcd_TimerStart(200);
    

    UI_Display_Prepare(temp_ram);
    
}


void UI_Screen_Compass_Entry(void)
{
    //Scene_ABC_CompassStart();
    
    Scene_ABC_CompassEnable();
    UI_Commom_Set_Allow_Lockstate2(0);
    UI_Screen_Compass_Display();
    
    UI_Common_set_key_handle(UI_Screen_Compass_shortkeyhandle,NULL,NULL);
    UI_Common_set_tp_click_handle(UI_Screen_Compass_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Compass_tpupslidehandle,
                                    UI_Screen_Compass_tpdownslidehandle,
                                    UI_Screen_Compass_tpleftslidehandle,
                                    UI_Screen_Compass_tprightslidehandle);

}

void UI_Screen_Compass_Exit(void)
{

    UI_Commom_Set_Allow_Lockstate2(1);
    curr_run_screen_info.is_run = 0;
    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    Scene_ABC_CompassDisable();

}

void UI_Screen_Compass_shortkeyhandle(void)
{

    UI_Screen_Compass_Exit();
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);

    UI_Screen_draw_Screen();

}

void UI_Screen_Compass_holdshortkeyhandle(void)
{
}

void UI_Screen_Compass_holdlongkeyhandle(void)
{
}

void UI_Screen_Compass_tpclickhandle(int point_x,int point_y)
{

    UI_Screen_Compass_Exit();
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Altitude_Detail);
    UI_Screen_draw_Screen();
    
}

void UI_Screen_Compass_tpupslidehandle(void)
{

    UI_Screen_Compass_Exit();
    //curr_run_screen_info.run_type = ENUM_ROUND_UP;
    UI_Common_Show_RunScreen_Prepare(ENUM_ROUND_UP);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_History);
    UI_Screen_draw_Screen();


}

void UI_Screen_Compass_tpdownslidehandle(void)
{
    UI_Screen_Compass_Exit();
    //curr_run_screen_info.run_type = ENUM_ROUND_DOWN;
    UI_Common_Show_RunScreen_Prepare(ENUM_ROUND_DOWN);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Sleep);
    UI_Screen_draw_Screen();

}

void UI_Screen_Compass_tpleftslidehandle(void)
{
}

void UI_Screen_Compass_tprightslidehandle(void)
{
}



void UI_Screen_Altitude_Detail_Display(void)
{


    int32_t data[135] = {80 ,76  ,98  ,98  ,57  ,65  ,69  ,300  ,71  ,71  ,63  ,62  ,63  ,59  ,62  ,64  ,64  ,63  ,62  ,63  ,63  ,63  ,62  ,60  ,62  ,58  ,60  ,62  ,59  ,60  ,62  ,59  ,62  ,62  ,61  ,61  ,
        58  ,69  ,59  ,64  ,81  ,61  ,63  ,85  ,64  ,57  ,59  ,60  ,59  ,60  ,59  ,60  ,56  ,56  ,59  ,58  ,56  ,56  ,56  ,57  ,57  ,58  ,56  ,59  ,55  ,57  ,55  ,57  ,57  ,57  ,55  ,
        55  ,56  ,55  ,55  ,55  ,53  ,56  ,54  ,56  ,55  ,57  ,56  ,84  ,58  ,60  ,53  ,55  ,61  ,58  ,63  ,63  ,58  ,72  ,58  ,57  ,63  ,57  ,68  ,56  ,56  ,63  ,57  ,60  ,62  ,60  ,66  ,59  ,57  ,
        53  ,61  ,52  ,73  ,57  ,58  ,56  ,57  ,55  ,56  ,57  ,58  ,56  ,57  ,55  ,56,58  ,56  ,57  ,55  ,56,58  ,56  ,57  ,55  ,56};

    int32_t max_value = 0;
    int max_value_pos = 0;
    int32_t min_value = 0;
    int min_value_pos = 0;
    int standard_value=0;
    int32_t result= 0;
    float segment;
    int i;
    int diagram_start_x,diagram_start_y;
    int curr_height=0;
    
    char content[32];
    int len;

    int32_t curr_data = 0;

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Altitude_Detail)
        return;

    UI_Common_Clear_Screen(temp_ram);
    
    Store_ABC_UIAltitudeGet(data,135);

    UI_Common_AddBWsourcePic(temp_ram,8,6,(uint8_t*)gchinesefont_compass_elevation,APP_COLOR_BLACK,APP_COLOR_WHITE);

    curr_data =data[0]/100;
    sprintf(content,"%dm",curr_data);
    len = strlen(content);
    UI_Common_Draw_AscStr_textbox(temp_ram,88,6,80,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_RIGHT);
    
    diagram_start_x = 0;
    diagram_start_y = 145;

    //底部标线
    UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y,135,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+15,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+15+30,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+15+30*2,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+15+30*3,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+15+30*4,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);

    max_value = data[0];
    min_value = data[0];

    for(i= 0;i<135;i++)
    {
        if(data[i] > max_value)
        {
            max_value = data[i];
            max_value_pos = i;
        }

        if(data[i] < min_value)
        {
            min_value = data[i];
            min_value_pos = i;
        }
    }

    

    result = max_value-min_value;
    
    RTT_DEBUG_printf(0,"%d\n%d\n%d\n",max_value,min_value,result);

    
    if(result<=100)
    {

        standard_value = (120 - result)/2;
        RTT_DEBUG_printf(0,"abc");
        
        for(i=1;i<=135;i++)
        {

            curr_height = data[135-i] - min_value + standard_value;
            UI_Common_SetPixelValue(temp_ram,diagram_start_x+i-1,diagram_start_y- curr_height, APP_COLOR_YELLOW);
            UI_Common_Draw_Vline(temp_ram,diagram_start_x+i-1,diagram_start_y- curr_height,curr_height,1,APP_COLOR_YELLOW,TRUE);
        }


        curr_height = data[max_value_pos] - min_value + standard_value;
        if(max_value_pos!=134)
        {
            UI_Common_Draw_Vline(temp_ram,diagram_start_x+135-max_value_pos-2,diagram_start_y- curr_height-1,3,3,APP_COLOR_RED,TRUE);
        }
        else
        {
            UI_Common_Draw_Vline(temp_ram,diagram_start_x+135-max_value_pos-1,diagram_start_y- curr_height-1,3,3,APP_COLOR_RED,TRUE);
        }

        
        curr_height = data[min_value_pos] - min_value + standard_value;
        if(min_value_pos!=134)
        {
            UI_Common_Draw_Vline(temp_ram,diagram_start_x+135-min_value_pos-2,diagram_start_y- curr_height-1,3,3,APP_COLOR_RED,TRUE);
        }
        else
        {
            UI_Common_Draw_Vline(temp_ram,diagram_start_x+135-min_value_pos-1,diagram_start_y- curr_height-1,3,3,APP_COLOR_RED,TRUE);
        }


        
        min_value = min_value - standard_value+10;
        max_value = min_value + 100;
        UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y- 10,135,1,APP_COLOR_BLACK,TRUE);
        curr_data =min_value/100;
        sprintf(content,"%d",curr_data);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+135+8,diagram_start_y- 10 -6,20,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y- -10-100,135,1,APP_COLOR_WHITE,false);
        curr_data =max_value/100;
        sprintf(content,"%d",curr_data);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+135+8,diagram_start_y- 10 -100 -6,20,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

            
    }
    else
    {

        segment = (float)100/result;

        for(i=1;i<=135;i++)
        {

            curr_height = (data[135-i] - min_value)*segment+10;
            UI_Common_SetPixelValue(temp_ram,diagram_start_x+i-1,diagram_start_y- curr_height, APP_COLOR_YELLOW);
            UI_Common_Draw_Vline(temp_ram,diagram_start_x+i-1,diagram_start_y- curr_height,curr_height,1,APP_COLOR_YELLOW,TRUE);
        }

    
        UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y- 10,135,1,APP_COLOR_BLACK,TRUE);
        curr_data =min_value/100;
        sprintf(content,"%d",curr_data);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+135+8,diagram_start_y- 10 -6,20,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y-10-100,135,1,APP_COLOR_WHITE,false);
        curr_data =max_value/100;
        sprintf(content,"%d",max_value);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+135+8,diagram_start_y- 10 -100 -6,20,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        curr_height = (data[max_value_pos] - min_value)*segment+10;
        
        if(max_value_pos!=134)
        {
            UI_Common_Draw_Vline(temp_ram,diagram_start_x+135-max_value_pos-2,diagram_start_y- curr_height-1,3,3,APP_COLOR_RED,TRUE);
        }
        else
        {
            UI_Common_Draw_Vline(temp_ram,diagram_start_x+135-max_value_pos-1,diagram_start_y- curr_height-1,3,3,APP_COLOR_RED,TRUE);
        }

        
        curr_height = (data[min_value_pos] - min_value)*segment+10;
        if(min_value_pos!=134)
        {
            UI_Common_Draw_Vline(temp_ram,diagram_start_x+135-min_value_pos-2,diagram_start_y- curr_height-1,3,3,APP_COLOR_RED,TRUE);
        }
        else
        {
            UI_Common_Draw_Vline(temp_ram,diagram_start_x+135-min_value_pos-1,diagram_start_y- curr_height-1,3,3,APP_COLOR_RED,TRUE);
        }
        
    }

    //UI_Common_Draw_AscStr_textbox(temp_ram,15,diagram_start_y+6,120,12,12,APP_COLOR_WHITE,"4Hours",6,ENUM_TEXTBOX_CENTER);
    UI_Common_AddBWsourcePic(temp_ram,35,diagram_start_y+6,(uint8_t*)gchinesefont_detail_4Hours,APP_COLOR_BLACK,APP_COLOR_WHITE);

    UI_Display_Prepare(temp_ram);

}


void UI_Screen_Altitude_Detail_Entry(void)
{
    UI_Screen_Altitude_Detail_Display();
    
    UI_Common_set_key_handle(UI_Screen_Altitude_Detail_shortkeyhandle,NULL,NULL);
    UI_Common_set_tp_click_handle(UI_Screen_Altitude_Detail_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Altitude_Detail_tpupslidehandle,
                                    UI_Screen_Altitude_Detail_tpdownslidehandle,
                                    UI_Screen_Altitude_Detail_tpleftslidehandle,
                                    UI_Screen_Altitude_Detail_tprightslidehandle);

}

void UI_Screen_Altitude_Detail_Exit()
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    Scene_ABC_CompassDisable();

}

void UI_Screen_Altitude_Detail_shortkeyhandle()
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}



void UI_Screen_Altitude_Detail_holdshortkeyhandle(void)
{
}

void UI_Screen_Altitude_Detail_holdlongkeyhandle(void)
{
}

void UI_Screen_Altitude_Detail_tpclickhandle(int point_x,int point_y)
{
}

void UI_Screen_Altitude_Detail_tpupslidehandle(void)
{
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Airpressure_Detail);
    UI_Screen_draw_Screen();
}

void UI_Screen_Altitude_Detail_tpdownslidehandle(void)
{
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Airpressure_Detail);
    UI_Screen_draw_Screen();
}

void UI_Screen_Altitude_Detail_tpleftslidehandle(void)
{
}

void UI_Screen_Altitude_Detail_tprightslidehandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_Compass);
    UI_Screen_draw_Screen();

}




void UI_Screen_Airpressure_Detail_Display(void)
{

    int32_t data[144] = {   99624   ,99627   ,99629   ,99632   ,99633   ,99634   ,99634   ,99633   ,99632   ,99631   ,99631   ,99630   ,99630   ,99630   ,99630   ,99631   ,99632   ,99633   ,99634   ,99634   ,
        99634   ,99633   ,99634   ,99635   ,99637   ,99639   ,99641   ,99643   ,99644   ,99645   ,99646   ,99647   ,99647   ,99648   ,99648   ,99648   ,99649   ,99650   ,99652   ,99655   ,99656   ,99657   ,
        99658   ,99659   ,99661   ,99662   ,99663   ,99664   ,99665   ,99666   ,99668   ,99669   ,99671   ,99673   ,99675   ,99677   ,99679   ,99680   ,99681   ,99682   ,99682   ,99683   ,99683   ,99682   ,
        99682   ,99681   ,99680   ,99680   ,99680   ,99680   ,99679   ,99679   ,99678   ,99678   ,99679   ,99680   ,99681   ,99681   ,99681   ,99681   ,99681   ,99681   ,99681   ,99682   ,99684   ,99687   ,
        99688   ,99689   ,99690   ,99689   ,99688   ,99686   ,99685   ,99685   ,99685   ,99686   ,99686   ,99686   ,99685   ,99684   ,99684   ,99684   ,99685   ,99685   ,99686   ,99686   ,99686   ,99686   ,
        99686   ,99686   ,99686   ,99685   ,99685   ,99684   ,99684   ,99682   ,99681   ,99680   ,99679   ,99680   ,99681   ,99681   ,99681   ,99680   ,99681   ,99681   ,99680   ,99679   ,99676   ,
        99673   ,99672   ,99671   ,99670   ,99669   ,99668   ,99667   ,99667   ,99667   ,99667   ,99668   ,99669   ,99669   ,99669   ,99669   ,
        };

    int32_t max_value = 0;
    int max_value_pos = 0;
    int32_t min_value = 0;
    int min_value_pos = 0;
    int i;
    
    int32_t result= 0;
    int diagram_start_x,diagram_start_y;
    int curr_height=0;

    float curr_data;

    char content[16];
    int len;

    int ratio = 0;

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Airpressure_Detail)
        return;

    UI_Common_Clear_Screen(temp_ram);


    Store_ABC_UIPressureGet(data,144);

    UI_Common_AddBWsourcePic(temp_ram,8,6,(uint8_t*)gchinesefont_compass_kpa,APP_COLOR_BLACK,APP_COLOR_WHITE);

    curr_data =(float)data[0]/100;
    sprintf(content,"%0.1fhPa",curr_data);
    len = strlen(content);
    UI_Common_Draw_AscStr_textbox(temp_ram,88,6,80,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_RIGHT);
    
    
    diagram_start_x = 0;
    diagram_start_y = 145;

    //标线 40
    UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y,144,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+36-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+36*2-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+36*3-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);
    UI_Common_Draw_Vline(temp_ram,diagram_start_x+36*4-1,diagram_start_y+1,2,1,APP_COLOR_WHITE,true);


    max_value = data[0];
    min_value = data[0];

    for(i= 0;i<144;i++)
    {
        data[i] = data[i];
    
        if(data[i]>max_value)
        {
            max_value = data[i];
            max_value_pos = i;
        }

        if(data[i]<min_value)
        {
            min_value = data[i];
            min_value_pos = i;
        }
    }

    min_value = min_value/100*100;

    result = max_value - min_value;

    ratio = result/120+1;

    sprintf(content,"%d",min_value/100);
    len=strlen(content);
    UI_Common_Draw_AscStr_textbox(temp_ram,diagram_start_x+144,diagram_start_y-6,20,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

    for(i=1;i<=144;i++)
    {
        curr_height = (data[144-i]+1)/ratio - min_value;

        UI_Common_SetPixelValue(temp_ram,diagram_start_x+i-1,diagram_start_y-curr_height-1, APP_COLOR_WHITE);
        UI_Common_SetPixelValue(temp_ram,diagram_start_x+i-1,diagram_start_y-curr_height, APP_COLOR_GREEN);
        UI_Common_Draw_Vline(temp_ram,diagram_start_x+i-1,diagram_start_y-curr_height,curr_height,1,APP_COLOR_GREEN,TRUE);
    }


    curr_height = (data[max_value_pos]+1)/ratio - min_value;
    if(max_value_pos!=143)
    {
        UI_Common_Draw_Vline(temp_ram,diagram_start_x+144-max_value_pos-2,diagram_start_y- curr_height-1,3,3,APP_COLOR_RED,TRUE);
    }
    else
    {
        UI_Common_Draw_Vline(temp_ram,diagram_start_x+144-max_value_pos-1,diagram_start_y- curr_height-1,3,3,APP_COLOR_RED,TRUE);
    }

    curr_height = (data[min_value_pos]+1)/ratio - min_value;
    if(max_value_pos!=143)
    {
        UI_Common_Draw_Vline(temp_ram,diagram_start_x+144-min_value_pos-2,diagram_start_y- curr_height-1,3,3,APP_COLOR_RED,TRUE);
    }
    else
    {
        UI_Common_Draw_Vline(temp_ram,diagram_start_x+144-min_value_pos-1,diagram_start_y- curr_height-1,3,3,APP_COLOR_RED,TRUE);
    }
        
    //UI_Common_Draw_AscStr_textbox(lcdram,diagram_start_x+144+2,diagram_start_y-6,20,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

    //标线1 120
    UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y- 50,144,1,APP_COLOR_WHITE,false);
    //UI_Common_Draw_AscStr_textbox(lcdram,diagram_start_x+144+8,diagram_start_y- 50 -6,20,12,12,APP_COLOR_WHITE,"50",2,ENUM_TEXTBOX_LEFT);

    //标线1 180
    UI_Common_Draw_Hline(temp_ram,diagram_start_x,diagram_start_y- 100,144,1,APP_COLOR_WHITE,false);
    //UI_Common_Draw_AscStr_textbox(lcdram,diagram_start_x+144+8,diagram_start_y- 75 -6,20,12,12,APP_COLOR_WHITE,"75",2,ENUM_TEXTBOX_LEFT);
    
    
    //UI_Common_Draw_AscStr_textbox(temp_ram,15,diagram_start_y+10,144,12,12,APP_COLOR_WHITE,"24Hours",7,ENUM_TEXTBOX_CENTER);
    UI_Common_AddBWsourcePic(temp_ram,32,diagram_start_y+10,(uint8_t*)gchinesefont_detail_24Hours,APP_COLOR_BLACK,APP_COLOR_WHITE);
    
    UI_Display_Prepare(temp_ram);

}


void UI_Screen_Airpressure_Detail_Entry(void)
{
    UI_Screen_Airpressure_Detail_Display();
    
    UI_Common_set_key_handle(UI_Screen_Airpressure_Detail_shortkeyhandle,NULL,NULL);
    UI_Common_set_tp_click_handle(UI_Screen_Airpressure_Detail_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Airpressure_Detail_tpupslidehandle,
                                    UI_Screen_Airpressure_Detail_tpdownslidehandle,
                                    UI_Screen_Airpressure_Detail_tpleftslidehandle,
                                    UI_Screen_Airpressure_Detail_tprightslidehandle);

}

void UI_Screen_Airpressure_Detail_Exit(void)
{
    curr_run_screen_info.is_run = 0;
    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    Scene_ABC_CompassDisable();

}

void UI_Screen_Airpressure_Detail_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);

    UI_Screen_draw_Screen();

}

void UI_Screen_Airpressure_Detail_holdshortkeyhandle(void)
{
}

void UI_Screen_Airpressure_Detail_holdlongkeyhandle(void)
{
}

void UI_Screen_Airpressure_Detail_tpclickhandle(int point_x,int point_y)
{
}

void UI_Screen_Airpressure_Detail_tpupslidehandle(void)
{
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Altitude_Detail);
    UI_Screen_draw_Screen();
}

void UI_Screen_Airpressure_Detail_tpdownslidehandle(void)
{
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Altitude_Detail);
    UI_Screen_draw_Screen();

}

void UI_Screen_Airpressure_Detail_tpleftslidehandle(void)
{

}

void UI_Screen_Airpressure_Detail_tprightslidehandle(void)
{
    //curr_run_screen_info.run_type = ENUM_MOVE_OUT;
    UI_Common_Show_RunScreen_Prepare(ENUM_MOVE_OUT);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Compass);
    UI_Screen_draw_Screen();

}


