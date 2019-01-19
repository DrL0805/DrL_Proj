#ifndef UI_DISPALY_COMMON_H
#define UI_DISPALY_COMMON_H

#include <string.h>
//#include "wsf_types.h"
#include "platform_common.h"
#include "drv_rgb_lcd.h"
#include "algorithm_usual.h"
#include "app_ascii_source.h"

#include <stdlib.h>
#include <stdio.h>

#include "ui_display_fontsource.h"
#include "ui_display_imagesource.h"
#include "ui_display_main.h"

#include "ui_tphandle_main.h"
#include "mid_rtc.h"
#include "app_lcd.h"

#include "scene_interface.h"
#include "scene_run.h"
#include "store_interface.h"
#include "app_remind_manage.h"
#include "drv_font.h"

#include "scene_common.h"

#include "mid_interface.h"
#include "scene_interface.h"
#include "store_interface.h"

#include "ui_keyhandle_main.h"


#define APP_COLOR_BLACK     0X00    //黑
#define APP_COLOR_BLUE      0X01    //蓝
#define APP_COLOR_GREEN     0X02    //绿
#define APP_COLOR_CYAN      0X03    //青
#define APP_COLOR_RED       0X04    //红
#define APP_COLOR_PINK      0X05    //粉
#define APP_COLOR_YELLOW    0X06    //黄
#define APP_COLOR_WHITE     0X07    //白

//translucent
#define APP_COLOR_TRANSLUCENT     0XFF    //透明

#define LCD_WIDTH           176
#define LCD_HEIGHT          176

//环形进度条参数
#define ANNULUS_PROGRESS_MINANGLE       PI/3
#define ANNULUS_PROGRESS_MAXANGLE       5*PI/3
#define ANNULUS_PROGRESS_CENTERX        87
#define ANNULUS_PROGRESS_CENTERY        79
#define ANNULUS_PROGRESS_LR             64
#define ANNULUS_PROGRESS_SR             56



typedef struct
{
    uint8 offset_x;
    uint8 offset_y;
    uint8 width;
    uint8 height;
} ui_common_pic_info_s;

typedef enum 
{
    ENUM_TEXTBOX_LEFT  = 0,
    ENUM_TEXTBOX_CENTER,
    ENUM_TEXTBOX_RIGHT,
}enum_textbox_display_type;



uint8_t UI_Common_GetPixelValue(uint8_t* picinfo,uint8_t info_x,uint8_t info_y);
uint8_t UI_Common_GetBWPixelValue(uint8_t* picinfo,uint8_t info_x,uint8_t info_y,uint8_t bg_color,uint8_t image_color);
void UI_Common_SetPixelValue(uint8_t *lcdram,uint8_t info_x,uint8_t info_y, uint8_t PixelValue);
void UI_Common_AddFullPic(uint8_t *lcdram,uint8_t pic_x,uint8_t pic_y,uint8_t* picinfo);
void UI_Common_AddPic(uint8_t *lcdram,uint8_t pic_x,uint8_t pic_y,uint8_t* picinfo);
void UI_Common_AddBWsourcePic(uint8_t *lcdram,int pic_x,int pic_y,uint8_t* picinfo,int8_t bg_color,int8_t image_color);
uint8_t UI_Common_GetFontPixelValue(uint8_t* fontinfo,uint8_t info_x,uint8_t info_y,uint8_t bg_color,uint8_t font_color);
void UI_Common_AddAsc2Font(uint8_t *lcdram,uint8_t pic_x,uint8_t pic_y,uint8_t* fontinfo,uint8_t bg_color,uint8_t font_color);
void UI_Common_AddAsc2Str(uint8_t *lcdram,uint8_t pic_x,uint8_t pic_y,int8_t* string,int strlen,int font_size,uint8_t bg_color,uint8_t font_color);
//图片信息加入到显示区域
void UI_Common_GetAsc2Str_info(int8_t* string,int strlen,int font_size,int *str_width,int *str_height);
void UI_Common_Draw_Annulus(uint8_t *lcdram,float x,float y,float Lr,float Sr,uint8_t color,bool is_solid);
void UI_Common_Draw_Circle(uint8_t *lcdram,float x,float y,float Lr,uint8_t color);
//void UI_Common_Draw_Annulus_Byangle(uint8_t *lcdram,int x,int y,int Lr,int Sr,float s_angle,float e_angle,uint8_t color,bool is_solid);
void UI_Common_Draw_Hline(uint8_t *lcdram,int x,int y,int len,int breadth,uint8_t color,bool is_solid);
void UI_Common_Draw_Vline(uint8_t *lcdram,int x,int y,int len,int breadth,uint8_t color,bool is_solid);
uint8_t*  UI_Common_GetNumberImageInfo(int number,int type);
void UI_Common_Draw_Annulus_Progress(uint8_t *lcdram,int x,int y,int Lr,int Sr,uint8_t bg_color,uint8_t progress_color,int percent);

void UI_Common_Draw_NumberImage_textbox(uint8_t *lcdram,int box_x,int box_y,int box_w,int box_h,int type,uint8_t image_color,int number);
void UI_Common_Draw_AscStr_textbox(uint8_t *lcdram,int box_x,int box_y,int box_w,int box_h,int font_size,uint8_t font_color,char* string,int strlen,enum_textbox_display_type display_type);
void UI_Common_Draw_FontStr_textbox(uint8_t *lcdram,int box_x,int box_y,int box_w,int box_h,uint8_t *fontinfo,uint8_t font_color,uint8_t bg_color);
uint8_t*  UI_Common_GetweekfontInfo(int day);


typedef struct 
{
    int is_init;
    int curr_list_page;
    int curr_list_highlight;
    int total_count;
    int total_list_page_count;
    uint8_t *icon_list[20];
    uint8_t *string_list[20];
    char line2_content[20][16];
}UI_Common_list_s;

extern UI_Common_list_s curr_list;


void UI_Common_ScreenCleanListInfo(void);
void UI_Common_ShowIconList(uint8_t *lcdram);

typedef enum 
{
    ENUM_ROUND_NON  = 0,
    ENUM_ROUND_UP,
    ENUM_ROUND_DOWN,
    ENUM_ROUND_LEFT,
    ENUM_ROUND_RIGHT,
    ENUM_MOVE_IN,
    ENUM_MOVE_OUT,
    ENUM_ROUND_MAX,
}enum_run_screen_type;

typedef struct 
{
	enum_run_screen_type  run_type;
    
	uint8 *ram_new;
	uint8 *ram_old;
	uint8 *ram_temp;
    int segment_size;
    int curr_segment_count;
    int duration_per_frame;
    bool is_run;

    bool is_ready;
}struct_run_screen_info;


extern struct_run_screen_info curr_run_screen_info;

//extern uint8_t TempLcdRam[RGB_LCD_RAM_LEN];
void UI_Common_Show_RunScreen_Prepare(enum_run_screen_type run_type);

void UI_Common_Show_RunScreen_timehandle(void);
void UI_Common_Show_RunScreen(enum_run_screen_type runDiret,uint8 *ram_new,uint8 *ram_old,uint8 *ram_temp);
void UI_Common_Show_RunScreen_Internal(enum_run_screen_type runDiret, uint8 runPixel, uint8 runTime);
void UI_Common_Draw_NumberImage_textbox_Bystringinfo(uint8_t *lcdram,int box_x,int box_y,int box_w,int box_h,uint8_t image_color,char *string,int len,int number_size,enum_textbox_display_type display_type);


void UI_Common_Show_PlayPause(uint8_t *lcdram,int type);
void UI_Common_Show_SportModeDataDetailBG(uint8_t *lcdram,int type_line0,int type_line1,int type_line2);


void UI_Common_Show_ThreeIconBar(uint8_t *lcdram,int x,int y,uint8_t* icon0,uint8_t* icon1,uint8_t*icon2);
void UI_Common_Show_ModeListIconStringBar(uint8_t *lcdram,int x,int y,uint8_t* l_icon,uint8_t* r_icon,uint8_t* bg_image,uint8_t* stringinfo,uint8_t bg_color,uint8_t image_color);


void UI_Common_Show_ModeMenuHeadBar(uint8_t *lcdram,int x,int y,char* data1,int data1_len,char* data2,int data2_len);

//倒计时 
typedef struct 
{
    int segment_time;   //定时器时间
    int curr_time;
    int total_time;
}UI_Common_sportmode_countdown_s;


void UI_Common_SportModeCountDownInfoDefault(void);
void UI_Common_DispRuningModeCountDownRound(uint8_t *lcdram,double angle);

void UI_Common_List_RarrowDoubleline(uint8_t *lcdram,int x,int y,uint8_t *line0_info0,uint8_t* line1_info0,uint8_t* line1_info1,int line1_type);

uint8_t* UI_Common_GetNumberImageInfo_Bychar(char data,int *width, int *height,int number_size);

void UI_Common_Drawtextbox_byfontic(uint8_t *lcdram, int text_x, int text_y,int text_width,int text_height, uint16* string, int strlen, Wordstock_size_s font_size_type, uint8_t bg_color, uint8_t font_color);


uint8_t UI_Common_GetFontPixelValue_Byfontic(uint8_t* fontinfo,uint8_t info_x,uint8_t info_y,int width,int height,uint8_t bg_color,uint8_t font_color);

void UI_Common_AddFont_Byfontic(uint8_t *lcdram,uint8_t x,uint8_t y,int width,int height,uint8_t* fontinfo,uint8_t bg_color,uint8_t font_color);

void UI_Common_AddBWsourcePic_withoffsetx(uint8_t *lcdram,uint8_t pic_x,uint8_t pic_y,uint8_t* picinfo,uint8_t bg_color,uint8_t image_color,int offset);



void UI_Common_Add_Battery(uint8_t *lcdram,uint8_t x,uint8_t y,int type);


void UI_Common_Show_SportModeDataDetail_CommonData(uint8_t *lcdram,int x,int y,int width,int height,const uint8_t *title,char* data,int datalen,uint8_t font_color);

void UI_Common_Draw_Annulus_Byangle(uint8_t *lcdram,int x,int y,int Lr,int Sr,double s_angle,double e_angle,uint8_t color,bool is_solid);


extern void UI_Screen_draw_Screen(void);
extern void UI_Screen_Redraw_Screen(void);

void UI_Common_Clear_Screen(uint8_t *lcdram);


typedef struct 
{

	uint8 curr_page_number;
	uint8 total_page_number;

	uint8 index;
    
}ui_common_page_info_s;




typedef struct 
{
    uint8  			is_am;
    uint8  			hour;
    uint8  			min;
    uint8  			sec;
}ui_common_time_12hour_s;



void UI_Common_Get_Time_12hour(ui_common_time_12hour_s *timeTemp);
void UI_Common_Show_SportModeDataDetail_HrData(uint8_t *lcdram,int x,int y,int width,int height,uint8_t *title,char* data,int datalen,uint8_t font_color,hrZone_e hrZone);


void UI_Common_Next_Page(void);
void UI_Common_Pre_Page(void);
void UI_Common_Detail_Next_Page(void);
void UI_Common_Detail_Pre_Page(void);


#endif

