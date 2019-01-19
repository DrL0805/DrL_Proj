#include "ui_display_main.h"
#include "ui_screen_store.h"
#include "ui_screen_dateandtime.h"
#include "ui_screen_step.h"
#include "ui_screen_heartrate.h"
#include "ui_screen_pressure.h"
#include "ui_screen_temperature.h"
#include "ui_screen_sleep.h"
#include "ui_screen_compass.h"
#include "ui_screen_history.h"
#include "ui_screen_modelist.h"
#include "ui_screen_breathtraining.h"
#include "ui_screen_stopwatch.h"



static uint8_t MainRam[RGB_LCD_RAM_LEN]={0x00}; 
static uint8_t TempLcdRam[RGB_LCD_RAM_LEN]={0x00};
//过场动画专用
static uint8_t TempLcdRam_old[RGB_LCD_RAM_LEN]={0x00};
extern uint8_t TempLcdRam_run[RGB_LCD_RAM_LEN];
//主屏幕id 
static Enum_Common_Screen_MAINID globle_screen_id = Common_Screen_MainID_Min;


func_callback_handle ui_screen_go_callback;


typedef struct 
{

    uint8_t* display_ram_main;      //此ram存放数据全部为组好显示数据的最终数�?
    uint8_t* display_ram_temp;      //组好包之前的显示数据
    uint8_t* display_ram_old;       //屏幕切换动效专用，保存上一屏显示数�?
    uint8_t* display_ram_run;       //屏幕切换动效专用，存放组好的显示数据

}globle_display_ram_t;


globle_display_ram_t display_ram_info;


void UI_Display_Ram_Init(void)
{

    display_ram_info.display_ram_main = MainRam;
    display_ram_info.display_ram_temp = TempLcdRam;
    //过场动画使用
    display_ram_info.display_ram_old = TempLcdRam_old;
    display_ram_info.display_ram_run = TempLcdRam_run;
   
}

uint8_t* UI_Display_Get_MainRam(void)
{
    return display_ram_info.display_ram_main;
}

uint8_t* UI_Display_Get_Tempram(void)
{
    return display_ram_info.display_ram_temp;
}

uint8_t* UI_Display_Get_Runoldram(void)
{
    return display_ram_info.display_ram_old;
}
uint8_t* UI_Display_Get_Runram(void)
{
    return display_ram_info.display_ram_run;
}

void UI_Display_Prepare(uint8_t *tempram)
{

    uint8_t *lcd_ram = UI_Display_Get_MainRam();
    
    memcpy(lcd_ram, tempram, RGB_LCD_RAM_LEN);
    
}



void UI_Set_Curr_ScreenID(Enum_Common_Screen_MAINID curr_id)
{

    globle_screen_id = curr_id;

}

Enum_Common_Screen_MAINID UI_Get_Curr_ScreenID(void)
{
    return globle_screen_id;
}


void UI_Set_Go_back_handle(func_callback_handle fuc)
{

    ui_screen_go_callback = fuc;
}

void* UI_Get_Go_back_handle(void)
{

    return ui_screen_go_callback;
}


void UI_Do_Go_back_handle(void)
{
    ui_screen_go_callback();
    UI_Set_Go_back_handle(NULL);
}


void UI_Show_Screen(void)
{


    Enum_Common_Screen_SUBID_WARN curr_screen_id = UI_Screen_Get_Warn_Screenid();
	
    if(curr_screen_id != Common_Screen_ID_Warn_None)
    {
        UI_Commom_Lockinfo_Reset();
        UI_Show_Screen_Warn();
    }
    else
    {
        UI_Show_Screen_Common();
    }

}


void UI_Show_Screen_Common(void)
{

    uint8_t *lcd_ram = UI_Display_Get_MainRam();
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    UI_Common_Clear_Screen(temp_ram);
    
    switch(globle_screen_id)
    {
        case Common_Screen_MainID_Store:
            UI_Screen_Store_Entry();
        break;
        case Common_Screen_MainID_Poweron:
            UI_Screen_Poweron_Entry();
        break;
        case Common_Screen_MainID_DateAndTime:
            UI_Screen_DateAndTime_Entry();
        break;
        case Common_Screen_MainID_Step:
            UI_Screen_Step_Entry();
        break;
        case Common_Screen_MainID_Step_Detail:
            UI_Screen_Step_Detail_Entry();
        break;
        case Common_Screen_MainID_Heartrate:
            UI_Screen_Heartrate_Entry();
        break;
        case Common_Screen_MainID_Heartrate_Detail:
            UI_Screen_Heartrate_Detail_Entry();
        break;
        case Common_Screen_MainID_Pressure:
            UI_Screen_Pressure_Entry();
        break;
        case Common_Screen_MainID_Pressure_Detail:
            UI_Screen_Pressure_Detail_Entry();
        break;
        case Common_Screen_MainID_Temperature:
            UI_Screen_Temperature_Entry();
        break;
        case Common_Screen_MainID_Temperature_Detail:
            UI_Screen_Temperature_Detail_Entry();
        break;
        case Common_Screen_MainID_Sleep:
            UI_Screen_Sleep_Entry();
        break;
        case Common_Screen_MainID_Sleep_Detail:
            UI_Screen_Sleep_Detail_Entry();
        break;
        case Common_Screen_MainID_Compass:
            UI_Screen_Compass_Entry();
        break;
        case Common_Screen_MainID_Altitude_Detail:
            UI_Screen_Altitude_Detail_Entry();
        break;
        case Common_Screen_MainID_Airpressure_Detail:
            UI_Screen_Airpressure_Detail_Entry();
        break;
        case Common_Screen_MainID_History:
            UI_Screen_History_Entry();
        break;
        case Common_Screen_MainID_History_List:
            UI_Screen_History_List_Entry();
        break;
        case Common_Screen_MainID_History_Detail:
            UI_Screen_History_Detail_Entry();
        break;
        case Common_Screen_MainID_Modelist:
            UI_Screen_Modelist_Entry();
        break;
        case Common_Screen_MainID_BreathTraining:
            UI_Screen_BreathTraining_Entry();
        break;
        case Common_Screen_MainID_Running:
            UI_Screen_RuningModeEntry();
        break;
        case Common_Screen_MainID_Climbing:
            UI_Screen_ClimbingModeEntry();
        break;
        case Common_Screen_MainID_Swim:
            UI_Screen_SwimModeEntry();
        break;
        case Common_Screen_MainID_SportHistory:
            UI_Screen_SportHistory_Entry();
        break;
        case Common_Screen_MainID_SportHistory_Detail:
            UI_Screen_SportHistoryDetail_Entry();
        break;
        case Common_Screen_MainID_Stopwatch:
            UI_Screen_Stopwatch_Entry();
        break;
        case Common_Screen_MainID_Stopwatch_Detail:
            UI_Screen_Stopwatch_Detail_Entry();
        break;
        case Common_Screen_MainID_Countdown:
            UI_Screen_Countdown_Entry();
        break;
        case Common_Screen_MainID_Alarm:
            UI_Screen_Alarm_Entry();
        break;
        case Common_Screen_MainID_Findphone:
            UI_Screen_Findphone_Entry();
        break;
        case Common_Screen_MainID_Setting:
            UI_Screen_Setting_Entry();
        break;
        case Common_Screen_MainID_Setting_Brightness:
            UI_Screen_Setting_Brightness_Entry();
        break;
        case Common_Screen_MainID_Setting_Infomation:
            UI_Screen_Setting_Infomation_Entry();
        break;
        case Common_Screen_MainID_OTA:
            UI_Screen_OTA_Entry();
        break;
        case Common_Screen_MainID_Charging:
            UI_Screen_Charging_Entry();
        break;
        case Common_Screen_MainID_Lock:
            UI_Screen_Lock_Entry();
        break;
        case Common_Screen_MainID_Reset:
            UI_Screen_Reset_Entry();
        break;
        case Common_Screen_MainID_Test:
            UI_Screen_Test_Entry();
        break;
        case Common_Screen_MainID_Test_App:
            UI_Screen_Test_App_Entry();
        break;
        default:
            UI_Screen_DateAndTime_Display();
            break;
    }



    if(curr_run_screen_info.run_type == ENUM_ROUND_NON)
    {
        curr_run_screen_info.is_ready = 1;
                
    }
    else
    {
        UI_Common_Show_RunScreen(curr_run_screen_info.run_type,temp_ram,TempLcdRam_old,TempLcdRam_run);
    }

}


void UI_Show_Screen_Warn(void)
{

    Enum_Common_Screen_SUBID_WARN curr_screen_id = UI_Screen_Get_Warn_Screenid();

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    UI_Common_Clear_Screen(temp_ram);
    

    switch(curr_screen_id)
    {
    
        case Common_Screen_ID_Warn_Camera:
            UI_Screen_Warn_Camera_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Call:
            UI_Screen_Warn_Call_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Alarm:
            UI_Screen_Warn_Alarm_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Timer:
            UI_Screen_Warn_Timer_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Message:
            UI_Screen_Warn_Message_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Steptarget:
            UI_Screen_Warn_Steptarget_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Outsit:
            UI_Screen_Warn_Outsit_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Btbreak:
            UI_Screen_Warn_Btbreak_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Btconnect:
            UI_Screen_Warn_Btbreak_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Space:
            UI_Screen_Warn_Nospace_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Lowpower:
            UI_Screen_Warn_Lowpower_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Error:
            UI_Screen_Warn_SettingError_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Running_Target_Distance:
            UI_Screen_Warn_Common_Running_Target_Distance_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Running_Target_Duration:
            UI_Screen_Warn_Common_Running_Target_Duration_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Running_Target_Calorie:
            UI_Screen_Warn_Common_Running_Warn_Calorie_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Running_Warn_Distance:
            UI_Screen_Warn_Common_Running_Warn_Distance_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Running_Warn_Duration:
            UI_Screen_Warn_Common_Running_Warn_Duration_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Running_Warn_Calorie:
            UI_Screen_Warn_Common_Running_Target_Calorie_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Running_Warn_Speed_Uplimit:
            UI_Screen_Warn_Common_Running_Warn_Speed_Uplimit_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Running_Warn_Speed_Lowlimit:
            UI_Screen_Warn_Common_Running_Warn_Speed_Lowlimit_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Running_Warn_Heartrate_Uplimit:
            UI_Screen_Warn_Common_Running_Warn_Heartrate_Uplimit_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Running_Warn_Heartrate_Lowlimit:
            UI_Screen_Warn_Common_Running_Warn_Heartrate_Lowlimit_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Swim_Target_Laps:
            UI_Screen_Warn_Common_Swim_Target_Laps_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Swim_Target_Duration:
            UI_Screen_Warn_Common_Swim_Target_Duration_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Swim_Target_Calorie:
            UI_Screen_Warn_Common_Swim_Target_Calorie_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Swim_Warn_Laps:
            UI_Screen_Warn_Common_Swim_Warn_Laps_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Swim_Warn_Duration:
            UI_Screen_Warn_Common_Swim_Warn_Duration_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Swim_Warn_Calorie:
            UI_Screen_Warn_Common_Swim_Warn_Calorie_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Climbing_Target_ClimbingDistance:
            UI_Screen_Warn_Common_Climbing_Target_ClimbingDistance_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Climbing_Target_Distance:
            UI_Screen_Warn_Common_Climbing_Target_Distance_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Climbing_Target_Duration:
            UI_Screen_Warn_Common_Climbing_Target_Duration_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Climbing_Target_Calorie:
            UI_Screen_Warn_Common_Climbing_Target_Calorie_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Climbing_Warn_Distance:
            UI_Screen_Warn_Common_Climbing_Warn_Distance_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Climbing_Warn_Duration:
            UI_Screen_Warn_Common_Climbing_Warn_Duration_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Climbing_Warn_Calorie:
            UI_Screen_Warn_Common_Climbing_Warn_Calorie_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Climbing_Warn_Heartrate_Uplimit:
            UI_Screen_Warn_Common_Climbing_Warn_Heartrate_Uplimit_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Climbing_Warn_Heartrate_Lowlimit:
            UI_Screen_Warn_Common_Climbing_Warn_Heartrate_Lowlimit_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Climbing_Warn_Elevation_Uplimit:
            UI_Screen_Warn_Common_Climbing_Warn_Elevation_Uplimit_Entry(temp_ram);
        break;
        case Common_Screen_ID_Warn_Climbing_Warn_Elevation_Lowlimit:
            UI_Screen_Warn_Common_Climbing_Warn_Elevation_Lowlimit_Entry(temp_ram);
        break;
        default:
            break;
    }

    
    UI_Display_Prepare(temp_ram);

}


void UI_Common_Clear_DisplayRam(uint8_t *ram)
{
    memset(ram,0x00, RGB_LCD_RAM_LEN);
}


void UI_Screen_draw_Screen(void)
{
    App_Lcd_TaskMsg_T   LcdMsg;
    LcdMsg.Id = eAppLcdEventOuter;
    App_Lcd_TaskEventSet(&LcdMsg, 0);
}

void UI_Screen_Redraw_Screen(void)
{

    App_Lcd_TaskMsg_T   LcdMsg;
    LcdMsg.Id = eAppLcdEventCmd;
    App_Lcd_TaskEventSet(&LcdMsg, 0);
}

void UI_Screen_Redraw_Screen_Bytimer(void)
{

    App_Lcd_TaskMsg_T   LcdMsg;
    LcdMsg.Id = eAppLcdEventInside;
    App_Lcd_TaskEventSet(&LcdMsg, 0);
}

void UI_Common_Clear_Screen(uint8_t *lcdram)
{
    UI_Common_Clear_DisplayRam(lcdram);
    
}


//初始化管�?

typedef struct 
{
	eLcdBLGrade bl_level;
        
}globle_setting_t;


globle_setting_t globle_setting_info;


void UI_Common_Value_Init(void)
{

    globle_setting_info.bl_level = eLcdBLGrade_3;
    //初始�?
    UI_Screen_RuningModeSetting_Init();
    UI_Screen_ClimbingModeSetting_Init();
    UI_Screen_SwimModeSetting_Init();
    
}

eLcdBLGrade UI_Common_Get_Blacklight_value(void)
{
    return globle_setting_info.bl_level;
    
}

void UI_Common_Set_Blacklight_value(eLcdBLGrade value)
{
    globle_setting_info.bl_level = value;
    
    //RTT_DEBUG_printf(0,"UI_Common_Set_Blacklight_value -- %d", globle_setting_info.bl_level);
    Mid_Lcd_BLDutySet(globle_setting_info.bl_level);
}

void UI_Common_Close_Blacklight(void)
{
    Mid_Lcd_BLDutySet(eLcdBLGrade_0);
}


void UI_Common_Open_Blacklight(void)
{
    Mid_Lcd_BLDutySet(globle_setting_info.bl_level);
}


void UI_Common_Init(void)
{

    UI_Display_Ram_Init();
    UI_Common_Value_Init();
    UI_Commom_Lockinfo_Init();
    
    UI_Screen_ClimbingModeElevationUpperLlimitSetting_Init();
    UI_Screen_ClimbingModeElevationLowerLlimitSetting_Init();
    
    //仓储模式
	UI_Set_Curr_ScreenID(Common_Screen_MainID_Store);	
	UI_Show_Screen();
	Mid_Lcd_Show();

}







