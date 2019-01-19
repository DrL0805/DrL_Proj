#ifndef UI_SCREEN_WARN_H
#define UI_SCREEN_WARN_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "ui_screen_runingmode.h"
#include "ui_screen_climbing.h"
#include "ui_screen_swim.h"
#include "app_remind_manage.h"


#define WARN_SHOW_TIME     5
#define WARN_WAIT_SCREEN_MAX   10


// 报警窗口类型
typedef enum 
{
	Common_Screen_ID_Warn_None,
        
	Common_Screen_ID_Warn_Camera,
	Common_Screen_ID_Warn_Call,
	Common_Screen_ID_Warn_Alarm,
	Common_Screen_ID_Warn_Timer, 
	Common_Screen_ID_Warn_Message,
	Common_Screen_ID_Warn_Steptarget,
	Common_Screen_ID_Warn_Outsit,
	Common_Screen_ID_Warn_Btbreak,
	Common_Screen_ID_Warn_Btconnect,
	Common_Screen_ID_Warn_Space,
	Common_Screen_ID_Warn_Lowpower,
	Common_Screen_ID_Warn_Error,
	Common_Screen_ID_Warn_Running_Target_Distance,
	Common_Screen_ID_Warn_Running_Target_Duration,        
	Common_Screen_ID_Warn_Running_Target_Calorie,           
	Common_Screen_ID_Warn_Running_Warn_Distance,
	Common_Screen_ID_Warn_Running_Warn_Duration,        
	Common_Screen_ID_Warn_Running_Warn_Calorie,           
	Common_Screen_ID_Warn_Running_Warn_Speed_Uplimit,           
	Common_Screen_ID_Warn_Running_Warn_Speed_Lowlimit,           
	Common_Screen_ID_Warn_Running_Warn_Heartrate_Uplimit,           
	Common_Screen_ID_Warn_Running_Warn_Heartrate_Lowlimit,           
	Common_Screen_ID_Warn_Swim_Target_Laps,        
	Common_Screen_ID_Warn_Swim_Target_Duration,        
	Common_Screen_ID_Warn_Swim_Target_Calorie,           
	Common_Screen_ID_Warn_Swim_Warn_Laps,        
	Common_Screen_ID_Warn_Swim_Warn_Duration,        
	Common_Screen_ID_Warn_Swim_Warn_Calorie,           
	Common_Screen_ID_Warn_Climbing_Target_ClimbingDistance,        
	Common_Screen_ID_Warn_Climbing_Target_Distance,        
	Common_Screen_ID_Warn_Climbing_Target_Duration,        
	Common_Screen_ID_Warn_Climbing_Target_Calorie,          
	Common_Screen_ID_Warn_Climbing_Warn_Distance,        
	Common_Screen_ID_Warn_Climbing_Warn_Duration,        
	Common_Screen_ID_Warn_Climbing_Warn_Calorie,          
	Common_Screen_ID_Warn_Climbing_Warn_Heartrate_Uplimit,           
	Common_Screen_ID_Warn_Climbing_Warn_Heartrate_Lowlimit,           
	Common_Screen_ID_Warn_Climbing_Warn_Elevation_Uplimit,           
	Common_Screen_ID_Warn_Climbing_Warn_Elevation_Lowlimit,           
	Common_Screen_ID_Warn_Max,
	
}Enum_Common_Screen_SUBID_WARN;



typedef enum 
{
	Warn_Common_Type_Min,		
	Warn_Common_Type_Running_Target_Distance,        
	Warn_Common_Type_Running_Target_Duration,        
	Warn_Common_Type_Running_Target_Calorie,           
	Warn_Common_Type_Running_Warn_Distance,        
	Warn_Common_Type_Running_Warn_Duration,        
	Warn_Common_Type_Running_Warn_Calorie,           
	Warn_Common_Type_Running_Warn_Speed_Uplimit,           
	Warn_Common_Type_Running_Warn_Speed_Lowlimit,           
	Warn_Common_Type_Running_Warn_Heartrate_Uplimit,           
	Warn_Common_Type_Running_Warn_Heartrate_Lowlimit,           
	Warn_Common_Type_Swim_Target_Laps,        
	Warn_Common_Type_Swim_Target_Duration,        
	Warn_Common_Type_Swim_Target_Calorie,           
	Warn_Common_Type_Swim_Warn_Laps,        
	Warn_Common_Type_Swim_Warn_Duration,        
	Warn_Common_Type_Swim_Warn_Calorie,           
	Warn_Common_Type_Climbing_Target_ClimbingDistance,        
	Warn_Common_Type_Climbing_Target_Distance,        
	Warn_Common_Type_Climbing_Target_Duration,        
	Warn_Common_Type_Climbing_Target_Calorie,           
	Warn_Common_Type_Climbing_Warn_Distance,        
	Warn_Common_Type_Climbing_Warn_Duration,        
	Warn_Common_Type_Climbing_Warn_Calorie,           
	Warn_Common_Type_Climbing_Warn_Heartrate_Uplimit,           
	Warn_Common_Type_Climbing_Warn_Heartrate_Lowlimit,     
	Warn_Common_Type_Climbing_Warn_Elevation_Uplimit,           
	Warn_Common_Type_Climbing_Warn_Elevation_Lowlimit,           
	Warn_Common_Type_Max,		
}Enum_Warn_Common_Type;
    


typedef struct 
{
    
    uint8_t round_color;
    uint8_t* title;
    char content[16];
    
    uint8_t* info;
    char info_content[16];
    
}Warn_Common_info_s;


typedef struct 
{
    
    int warn_total;
    Enum_Common_Screen_SUBID_WARN curr_warn_type;
    //Enum_Common_Screen_SUBID_WARN wait_screen[WARN_WAIT_SCREEN_MAX];
    Enum_Common_Screen_SUBID_WARN curr_screen;

    //bool is_message;
    
    bool is_camera;
    bool is_call;
    bool is_alarm;
    bool is_timer;
    
}Warn_display_s;




void UI_Screen_Warn_Set_Warn_Data(int data);
int UI_Screen_Warn_Get_Warn_Data(void);


void UI_Screen_Add_Warn(Enum_Common_Screen_SUBID_WARN warn_screen);
void UI_Screen_Delete_Warn(void);
void UI_Screen_Delete_All_Warn(void);

Enum_Common_Screen_SUBID_WARN UI_Screen_Get_Warn_Screenid(void);


void UI_Screen_Warn_Call_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Call_Display(uint8_t *lcdram);
void UI_Screen_Warn_Call_Exit(void);

void UI_Screen_Warn_Call_shortkeyhandle(void);
void UI_Screen_Warn_Call_holdshortkeyhandle(void);
void UI_Screen_Warn_Call_holdlongkeyhandle(void);
void UI_Screen_Warn_Call_tpclickhandle(int point_x,int point_y);
void UI_Screen_Warn_Call_tpupslidehandle(void);
void UI_Screen_Warn_Call_tpdownslidehandle(void);
void UI_Screen_Warn_Call_tpleftslidehandle(void);
void UI_Screen_Warn_Call_tprightslidehandle(void);



void UI_Screen_Warn_Alarm_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Alarm_Display(uint8_t *lcdram);
void UI_Screen_Warn_Alarm_Exit(void);

void UI_Screen_Warn_Alarm_shortkeyhandle(void);
void UI_Screen_Warn_Alarm_holdshortkeyhandle(void);
void UI_Screen_Warn_Alarm_holdlongkeyhandle(void);
void UI_Screen_Warn_Alarm_tpclickhandle(int point_x,int point_y);
void UI_Screen_Warn_Alarm_tpupslidehandle(void);
void UI_Screen_Warn_Alarm_tpdownslidehandle(void);
void UI_Screen_Warn_Alarm_tpleftslidehandle(void);
void UI_Screen_Warn_Alarm_tprightslidehandle(void);


void UI_Screen_Warn_Timer_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Timer_Display(uint8_t *lcdram);
void UI_Screen_Warn_Timer_Exit(void);


void UI_Screen_Warn_Message_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Message_Display(uint8_t *lcdram);
void UI_Screen_Warn_Message_Exit(void);
void UI_Screen_Warn_Message_shortkeyhandle(void);
void UI_Screen_Warn_Message_holdshortkeyhandle(void);
void UI_Screen_Warn_Message_holdlongkeyhandle(void);
void UI_Screen_Warn_Message_tpclickhandle(int point_x,int point_y);
void UI_Screen_Warn_Message_tpupslidehandle(void);
void UI_Screen_Warn_Message_tpdownslidehandle(void);
void UI_Screen_Warn_Message_tpleftslidehandle(void);
void UI_Screen_Warn_Message_tprightslidehandle(void);





void UI_Screen_Warn_Steptarget_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Steptarget_Display(uint8_t *lcdram);
void UI_Screen_Warn_Steptarget_Exit(void);


void UI_Screen_Warn_Outsit_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Outsit_Display(uint8_t *lcdram);
void UI_Screen_Warn_Outsit_Exit(void);


void UI_Screen_Warn_Btbreak_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Btbreak_Display(uint8_t *lcdram);
void UI_Screen_Warn_Btbreak_Exit(void);


void UI_Screen_Warn_Nospace_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Nospace_Display(uint8_t *lcdram);
void UI_Screen_Warn_Nospace_Exit(void);


void UI_Screen_Warn_Lowpower_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Lowpower_Display(uint8_t *lcdram);
void UI_Screen_Warn_Lowpower_Exit(void);


void UI_Screen_Warn_Camera_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Camera_Display(uint8_t *lcdram);
void UI_Screen_Warn_Camera_Exit(void);

void UI_Screen_Warn_Camera_shortkeyhandle(void);
void UI_Screen_Warn_Camera_holdshortkeyhandle(void);
void UI_Screen_Warn_Camera_holdlongkeyhandle(void);
void UI_Screen_Warn_Camera_tpclickhandle(int point_x,int point_y);
void UI_Screen_Warn_Camera_tpupslidehandle(void);
void UI_Screen_Warn_Camera_tpdownslidehandle(void);
void UI_Screen_Warn_Camera_tpleftslidehandle(void);
void UI_Screen_Warn_Camera_tprightslidehandle(void);



void UI_Screen_Warn_SettingError_Entry(uint8_t *lcdram);
void UI_Screen_Warn_SettingError_Display(uint8_t *lcdram);
void UI_Screen_Warn_SettingError_Exit(void);





void UI_Screen_Warn_Common_Init(Enum_Warn_Common_Type type);


void UI_Screen_Warn_Common_Running_Target_Distance_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Running_Target_Duration_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Running_Target_Calorie_Entry(uint8_t *lcdram);


void UI_Screen_Warn_Common_Running_Warn_Distance_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Running_Warn_Duration_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Running_Warn_Calorie_Entry(uint8_t *lcdram);


void UI_Screen_Warn_Common_Running_Warn_Speed_Uplimit_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Running_Warn_Speed_Lowlimit_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Running_Warn_Heartrate_Uplimit_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Running_Warn_Heartrate_Lowlimit_Entry(uint8_t *lcdram);


void UI_Screen_Warn_Common_Swim_Target_Laps_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Swim_Target_Duration_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Swim_Target_Calorie_Entry(uint8_t *lcdram);


void UI_Screen_Warn_Common_Swim_Warn_Laps_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Swim_Warn_Duration_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Swim_Warn_Calorie_Entry(uint8_t *lcdram);



void UI_Screen_Warn_Common_Climbing_Target_ClimbingDistance_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Climbing_Target_Distance_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Climbing_Target_Duration_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Climbing_Target_Calorie_Entry(uint8_t *lcdram);


void UI_Screen_Warn_Common_Climbing_Warn_ClimbingDistance_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Climbing_Warn_Distance_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Climbing_Warn_Duration_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Climbing_Warn_Calorie_Entry(uint8_t *lcdram);



void UI_Screen_Warn_Common_Climbing_Warn_Elevation_Uplimit_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Climbing_Warn_Elevation_Lowlimit_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Climbing_Warn_Heartrate_Uplimit_Entry(uint8_t *lcdram);
void UI_Screen_Warn_Common_Climbing_Warn_Heartrate_Lowlimit_Entry(uint8_t *lcdram);


void UI_Screen_Warn_Common_Display(uint8_t *lcdram);
void UI_Screen_Warn_Common_Exit(void);



void UI_Screen_Show_Warn_Screen_Camera(void);
void UI_Screen_Close_Warn_Screen_Camera(void);


void UI_Screen_Show_Warn_Screen_Call(void);
void UI_Screen_Show_Warn_Screen_Alarm(void);


void UI_Screen_Show_Warn_Screen_Steptarget(void);
void UI_Screen_Show_Warn_Screen_Outsit(void);
void UI_Screen_Show_Warn_Screen_Btconnect(void);
void UI_Screen_Show_Warn_Screen_Space(void);
void UI_Screen_Show_Warn_Screen_Lowpower(void);
void UI_Screen_Show_Warn_Screen_Timer(void);
void UI_Screen_Show_Warn_Screen_Message(void);
void UI_Screen_Show_Warn_Screen_Error(void);


void UI_Screen_Show_Warn_Screen_RunningMode_Target_Distance(void);
void UI_Screen_Show_Warn_Screen_RunningMode_Target_Duration(void);
void UI_Screen_Show_Warn_Screen_RunningMode_Target_Calorie(void);
void UI_Screen_Show_Warn_Screen_RunningMode_Warn_Distance(void);
void UI_Screen_Show_Warn_Screen_RunningMode_Warn_Duration(void);
void UI_Screen_Show_Warn_Screen_RunningMode_Warn_Calorie(void);
void UI_Screen_Show_Warn_Screen_RunningMode_Warn_Speed_Uplimit(void);
void UI_Screen_Show_Warn_Screen_RunningMode_Warn_Speed_Lowlimit(void);
void UI_Screen_Show_Warn_Screen_RunningMode_Warn_Heartrate_Uplimit(void);
void UI_Screen_Show_Warn_Screen_RunningMode_Warn_Heartrate_Lowlimit(void);

void UI_Screen_Show_Warn_Screen_ClimbingMode_Target_ClimbingDistance(void);
void UI_Screen_Show_Warn_Screen_ClimbingMode_Target_Distance(void);
void UI_Screen_Show_Warn_Screen_ClimbingMode_Target_Duration(void);
void UI_Screen_Show_Warn_Screen_ClimbingMode_Target_Calorie(void);
void UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Distance(void);
void UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Duration(void);
void UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Calorie(void);
void UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Heartrate_Uplimit(void);
void UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Heartrate_Lowlimit(void);
void UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Elevation_Uplimit(void);
void UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Elevation_Lowlimit(void);

void UI_Screen_Show_Warn_Screen_SwimMode_Target_Laps(void);
void UI_Screen_Show_Warn_Screen_SwimMode_Target_Duration(void);
void UI_Screen_Show_Warn_Screen_SwimMode_Target_Calorie(void);
void UI_Screen_Show_Warn_Screen_SwimMode_Warn_Laps(void);
void UI_Screen_Show_Warn_Screen_SwimMode_Warn_Duration(void);
void UI_Screen_Show_Warn_Screen_SwimMode_Warn_Calorie(void);



#endif





