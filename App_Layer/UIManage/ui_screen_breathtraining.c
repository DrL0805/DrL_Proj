#include "ui_screen_breathtraining.h"
#include "ui_screen_dateandtime.h"

//extern uint8_t TempLcdRam[RGB_LCD_RAM_LEN];

const uint8_t image_btraining_h[] = {
48,48,
0x00, 0x00, 0x5D, 0xBA, 0x00, 0x00, /* scanline 1 */
0x00, 0x02, 0xFF, 0xFF, 0x40, 0x00, /* scanline 2 */
0x00, 0x01, 0xFF, 0xFF, 0x80, 0x00, /* scanline 3 */
0x00, 0x27, 0xFF, 0xFF, 0xE4, 0x00, /* scanline 4 */
0x00, 0x7F, 0xFF, 0xFF, 0xFE, 0x00, /* scanline 5 */
0x00, 0xBF, 0xFF, 0xFF, 0xFD, 0x00, /* scanline 6 */
0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, /* scanline 7 */
0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, /* scanline 8 */
0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, /* scanline 9 */
0x0B, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, /* scanline 10 */
0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, /* scanline 11 */
0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, /* scanline 12 */
0x0F, 0xFF, 0xFE, 0x7F, 0xFF, 0xF0, /* scanline 13 */
0x1F, 0xFF, 0xFC, 0x3F, 0xFF, 0xF8, /* scanline 14 */
0x5F, 0xFF, 0xF8, 0x1F, 0xFF, 0xFA, /* scanline 15 */
0x3F, 0xFF, 0xF8, 0x1F, 0xFF, 0xFC, /* scanline 16 */
0x7F, 0xFD, 0xF0, 0x0F, 0xBF, 0xFE, /* scanline 17 */
0xFF, 0xF8, 0x30, 0x0C, 0x1F, 0xFF, /* scanline 18 */
0x7F, 0xF8, 0x30, 0x0C, 0x1F, 0xFE, /* scanline 19 */
0xFF, 0xF8, 0x20, 0x04, 0x1F, 0xFF, /* scanline 20 */
0xFF, 0xF8, 0x20, 0x04, 0x1F, 0xFF, /* scanline 21 */
0xFF, 0xF8, 0x20, 0x04, 0x1F, 0xFF, /* scanline 22 */
0x7F, 0xF8, 0x20, 0x04, 0x1F, 0xFE, /* scanline 23 */
0xFF, 0xFF, 0x20, 0x04, 0xFF, 0xFF, /* scanline 24 */
0xFF, 0x81, 0xE0, 0x07, 0x81, 0xFF, /* scanline 25 */
0x7F, 0x00, 0x60, 0x06, 0x00, 0xFE, /* scanline 26 */
0xFF, 0x80, 0x30, 0x0C, 0x01, 0xFF, /* scanline 27 */
0xFF, 0x80, 0x30, 0x0C, 0x01, 0xFF, /* scanline 28 */
0xFF, 0x80, 0x10, 0x08, 0x01, 0xFF, /* scanline 29 */
0x7F, 0xC0, 0x18, 0x18, 0x03, 0xFE, /* scanline 30 */
0xFF, 0xE0, 0x08, 0x10, 0x07, 0xFF, /* scanline 31 */
0x7F, 0xF0, 0x0C, 0x30, 0x0F, 0xFE, /* scanline 32 */
0x3F, 0xFC, 0x06, 0x60, 0x3F, 0xFC, /* scanline 33 */
0x5F, 0xFF, 0x03, 0xC0, 0xFF, 0xFA, /* scanline 34 */
0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, /* scanline 35 */
0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, /* scanline 36 */
0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, /* scanline 37 */
0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, /* scanline 38 */
0x0B, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, /* scanline 39 */
0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, /* scanline 40 */
0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, /* scanline 41 */
0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, /* scanline 42 */
0x00, 0xBF, 0xFF, 0xFF, 0xFD, 0x00, /* scanline 43 */
0x00, 0x7F, 0xFF, 0xFF, 0xFE, 0x00, /* scanline 44 */
0x00, 0x27, 0xFF, 0xFF, 0xE4, 0x00, /* scanline 45 */
0x00, 0x01, 0xFF, 0xFF, 0x80, 0x00, /* scanline 46 */
0x00, 0x02, 0xFF, 0xFF, 0x40, 0x00, /* scanline 47 */
0x00, 0x00, 0x5D, 0xBA, 0x00, 0x00, /* scanline 48 */
};

/* 宋体 [未指定字号]*/
/* 字串 呼气   32x16  */
const unsigned char gchinesefont_breathtraining_exhale[] = { 
32, 16, 
0x00,0x08,0x10,0x00,0x00,0x3C,0x10,0x00,0x7B,0xE0,0x3F,0xFC,0x48,0x20,0x20,0x00,
0x49,0x24,0x4F,0xF0,0x48,0xA4,0x80,0x00,0x48,0xA8,0x3F,0xF0,0x48,0x20,0x00,0x10,
0x4B,0xFE,0x00,0x10,0x48,0x20,0x00,0x10,0x78,0x20,0x00,0x10,0x48,0x20,0x00,0x10,
0x00,0x20,0x00,0x0A,0x00,0x20,0x00,0x0A,0x00,0xA0,0x00,0x06,0x00,0x40,0x00,0x02,
};
/* 宋体 [未指定字号]*/
/* 字串 吸气   32x16  */
const unsigned char gchinesefont_breathtraining_inhale[] = { 
32, 16, 
0x00,0x00,0x10,0x00,0x07,0xF8,0x10,0x00,0x79,0x08,0x3F,0xFC,0x49,0x10,0x20,0x00,
0x49,0x10,0x4F,0xF0,0x49,0x20,0x80,0x00,0x49,0x3C,0x3F,0xF0,0x49,0x04,0x00,0x10,
0x49,0x04,0x00,0x10,0x4A,0x88,0x00,0x10,0x7A,0x88,0x00,0x10,0x4A,0x50,0x00,0x10,
0x04,0x20,0x00,0x0A,0x04,0x50,0x00,0x0A,0x08,0x88,0x00,0x06,0x03,0x06,0x00,0x02,
};
/* 宋体 [未指定字号]*/
/* 字串 屏息   32x16  */
const unsigned char gchinesefont_breathtraining_breathless[] = { 
32, 16, 
0x00,0x00,0x01,0x00,0x3F,0xF8,0x02,0x00,0x20,0x08,0x1F,0xF0,0x20,0x08,0x10,0x10,
0x3F,0xF8,0x1F,0xF0,0x24,0x10,0x10,0x10,0x22,0x20,0x1F,0xF0,0x2F,0xF8,0x10,0x10,
0x22,0x20,0x1F,0xF0,0x22,0x20,0x10,0x10,0x3F,0xFC,0x01,0x00,0x22,0x20,0x08,0x84,
0x42,0x20,0x48,0x92,0x44,0x20,0x48,0x12,0x84,0x20,0x87,0xF0,0x08,0x20,0x00,0x00,
};



//breath training
typedef enum
{
    BTRAINING_READY = 0,    //expiration 呼气
    BTRAINING_IN,        //inhale  吸气
    BTRAINING_IN_HOLD,   //吸气后屏息
    BTRAINING_EX,    //expiration 呼气
    BTRAINING_EX_HOLD,   //呼气后屏息
    BTRAINING_MAX,
}app_breathtraining_state;


typedef struct 
{
    app_breathtraining_state state;
    int curr_time;
    int total_time;
    int segment_time;
    int defaultlr;
    int increaselr;
    float centerx;
    float centery;
    
    uint8 bg_clolr_l;
    uint8 bg_clolr_m;
    uint8 bg_clolr_u;
    
}app_breathtraining_info_s;

app_breathtraining_info_s curr_btraining_info;


void UI_Screen_BreathTraining_DfaultInfo(void)
{

    curr_btraining_info.state = BTRAINING_READY;
    curr_btraining_info.curr_time = 0;
    curr_btraining_info.total_time = 1240; //8轮训练 第8轮无吸气后屏息
    curr_btraining_info.segment_time = 40; 
    curr_btraining_info.defaultlr = 16;    //最小圆半径
    curr_btraining_info.increaselr = 1;   //每次增加半径
    curr_btraining_info.centerx = 88; 
    curr_btraining_info.centery = 80; 

    curr_btraining_info.bg_clolr_l = APP_COLOR_BLUE;  
    curr_btraining_info.bg_clolr_m = APP_COLOR_CYAN; 
    curr_btraining_info.bg_clolr_u = APP_COLOR_BLACK; 
    
    
}


void  UI_Screen_BreathTraining_Timerhandle(void)
{
    //static int i = 0;

    UI_Common_set_timer_handle(UI_Screen_BreathTraining_Timerhandle);

    if(curr_btraining_info.curr_time%curr_btraining_info.segment_time == 0)
    {
        curr_btraining_info.state++;

        if(curr_btraining_info.state == BTRAINING_MAX)
        {
            curr_btraining_info.state = BTRAINING_IN;        
        }
    }
    
    if(curr_btraining_info.curr_time<curr_btraining_info.total_time)
    {
        UI_Screen_BreathTraining_Display();
        curr_btraining_info.curr_time++;
    }
    else
    {

    
        //结束训练后，重新开始允许进入休眠状态
        UI_Commom_Set_Allow_Lockstate1(1);
    
        curr_btraining_info.curr_time=0;
        curr_btraining_info.state = BTRAINING_READY;
        
        UI_Common_set_timer_handle(NULL);
        App_Lcd_HardTimerStop();
        
        UI_Screen_draw_Screen();
    }

}




void UI_Screen_BreathTraining_Display(void)
{

    int timecount = 0;
    int c_countdown = 1;
    uint8_t* fontinfo = NULL;

    int len = 0;
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_BreathTraining)
        return;

    UI_Common_Clear_Screen(temp_ram);

    if(curr_btraining_info.state == BTRAINING_READY)
    {
        UI_Common_AddBWsourcePic(temp_ram,64,56,(uint8_t*)image_btraining_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
        UI_Common_AddBWsourcePic(temp_ram,40,116,(uint8_t*)gchinesefont_breathingtraining,APP_COLOR_BLACK,APP_COLOR_WHITE);
        UI_Common_AddBWsourcePic(temp_ram,52,152,(uint8_t*)gchinesefont_clickscreen,APP_COLOR_BLACK,APP_COLOR_CYAN);
    }
    else
    {
        timecount = curr_btraining_info.curr_time%40; //4-3-2-1
        c_countdown = c_countdown+(curr_btraining_info.segment_time - timecount-1)/10;
        fontinfo =UI_Common_GetNumberImageInfo(c_countdown,0);
        
        if(curr_btraining_info.state == BTRAINING_IN) //吸气
        {
            //UI_Common_Draw_Circle(lcdram,curr_btraining_info.centerx,curr_btraining_info.centery,curr_btraining_info.defaultlr+curr_btraining_info.increaselr*timecount,APP_COLOR_WHITE);
            UI_Common_Draw_Circle(temp_ram,curr_btraining_info.centerx,curr_btraining_info.centery,curr_btraining_info.defaultlr+4*2+curr_btraining_info.increaselr*timecount,curr_btraining_info.bg_clolr_l);
            UI_Common_Draw_Circle(temp_ram,curr_btraining_info.centerx,curr_btraining_info.centery,curr_btraining_info.defaultlr+4+curr_btraining_info.increaselr*timecount/2,curr_btraining_info.bg_clolr_m);
            
            UI_Common_AddBWsourcePic(temp_ram,76,152,(uint8_t*)gchinesefont_breathtraining_inhale,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }
        else if(curr_btraining_info.state == BTRAINING_IN_HOLD)//屏息
        {
            //UI_Common_Draw_Circle(lcdram,curr_btraining_info.centerx,curr_btraining_info.centery,curr_btraining_info.defaultlr+curr_btraining_info.increaselr*(curr_btraining_info.segment_time-1),APP_COLOR_WHITE);

            UI_Common_Draw_Circle(temp_ram,curr_btraining_info.centerx,curr_btraining_info.centery,curr_btraining_info.defaultlr+4*2+curr_btraining_info.increaselr*(curr_btraining_info.segment_time-1),curr_btraining_info.bg_clolr_l);
            UI_Common_Draw_Circle(temp_ram,curr_btraining_info.centerx,curr_btraining_info.centery,curr_btraining_info.defaultlr+4+curr_btraining_info.increaselr*(curr_btraining_info.segment_time-1)/2,curr_btraining_info.bg_clolr_m);
            UI_Common_AddBWsourcePic(temp_ram,76,152,(uint8_t*)gchinesefont_breathtraining_breathless,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }
        else if(curr_btraining_info.state == BTRAINING_EX)
        {
            //UI_Common_Draw_Circle(lcdram,curr_btraining_info.centerx,curr_btraining_info.centery,curr_btraining_info.defaultlr+curr_btraining_info.increaselr*(curr_btraining_info.segment_time-timecount-1),APP_COLOR_WHITE);
            
            UI_Common_Draw_Circle(temp_ram,curr_btraining_info.centerx,curr_btraining_info.centery,curr_btraining_info.defaultlr+4*2+curr_btraining_info.increaselr*(curr_btraining_info.segment_time-timecount-1),curr_btraining_info.bg_clolr_l);
            UI_Common_Draw_Circle(temp_ram,curr_btraining_info.centerx,curr_btraining_info.centery,curr_btraining_info.defaultlr+4+curr_btraining_info.increaselr*(curr_btraining_info.segment_time-timecount-1)/2,curr_btraining_info.bg_clolr_m);
            UI_Common_AddBWsourcePic(temp_ram,76,152,(uint8_t*)gchinesefont_breathtraining_exhale,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }
        else if(curr_btraining_info.state == BTRAINING_EX_HOLD)
        {
            //UI_Common_Draw_Circle(lcdram,curr_btraining_info.centerx,curr_btraining_info.centery,curr_btraining_info.defaultlr,APP_COLOR_WHITE);

            UI_Common_Draw_Circle(temp_ram,curr_btraining_info.centerx,curr_btraining_info.centery,curr_btraining_info.defaultlr+4*2,curr_btraining_info.bg_clolr_l);
            UI_Common_Draw_Circle(temp_ram,curr_btraining_info.centerx,curr_btraining_info.centery,curr_btraining_info.defaultlr+4,curr_btraining_info.bg_clolr_m);
            UI_Common_AddBWsourcePic(temp_ram,76,152,(uint8_t*)gchinesefont_breathtraining_breathless,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }

        
        UI_Common_Draw_Circle(temp_ram,curr_btraining_info.centerx,curr_btraining_info.centery,curr_btraining_info.defaultlr,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,81,67,(uint8_t*)fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);

        len = curr_btraining_info.curr_time*176/curr_btraining_info.total_time;
        UI_Common_Draw_Hline(temp_ram,0,173,len,4,APP_COLOR_CYAN,1);
        
    }

    UI_Display_Prepare(temp_ram);

}



void UI_Screen_BreathTraining_Entry(void)
{

    UI_Screen_BreathTraining_DfaultInfo();

    UI_Screen_BreathTraining_Display();
    
    UI_Common_set_key_handle(UI_Screen_BreathTraining_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_BreathTraining_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_BreathTraining_tpupslidehandle,
                                    UI_Screen_BreathTraining_tpdownslidehandle,
                                    UI_Screen_BreathTraining_tpleftslidehandle,
                                    UI_Screen_BreathTraining_tprightslidehandle);
    
}

void UI_Screen_BreathTraining_Exit(void)
{
    //退出呼吸训练后，充值允许进入休眠状态
    UI_Commom_Set_Allow_Lockstate1(1);

    UI_Screen_BreathTraining_DfaultInfo();
    UI_Common_set_timer_handle(NULL);
    App_Lcd_HardTimerStop();
    
}

void UI_Screen_BreathTraining_shortkeyhandle(void)
{
    UI_Screen_BreathTraining_Exit();
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}

void UI_Screen_BreathTraining_holdshortkeyhandle(void)
{
}

void UI_Screen_BreathTraining_holdlongkeyhandle(void)
{
}


void UI_Screen_BreathTraining_tpclickhandle(int point_x,int point_y)
{

    //开始训练后，不进入休眠状态
    UI_Commom_Set_Allow_Lockstate1(0);

    UI_Screen_BreathTraining_Timerhandle();
    UI_Common_set_timer_handle(UI_Screen_BreathTraining_Timerhandle);
    App_Lcd_HardTimerStart(curr_btraining_info.increaselr*100);
    
}

void UI_Screen_BreathTraining_tpupslidehandle(void)
{
}

void UI_Screen_BreathTraining_tpdownslidehandle(void)
{
    UI_Screen_BreathTraining_Exit();

    UI_Set_Curr_ScreenID(Common_Screen_MainID_Pressure_Detail);
    UI_Screen_draw_Screen();
}

void UI_Screen_BreathTraining_tpleftslidehandle(void)
{
}

void UI_Screen_BreathTraining_tprightslidehandle(void)
{
     UI_Screen_BreathTraining_Exit();
     //curr_run_screen_info.run_type = ENUM_MOVE_OUT;
     UI_Common_Show_RunScreen_Prepare(ENUM_MOVE_OUT);
     
     UI_Set_Curr_ScreenID(Common_Screen_MainID_Pressure);
     UI_Screen_draw_Screen();

}





