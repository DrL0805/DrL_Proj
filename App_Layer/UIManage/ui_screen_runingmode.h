#ifndef UI_SCREEN_RUNINGMODE_H
#define UI_SCREEN_RUNINGMODE_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "scene_run.h"
#include "mid_pressure.h"

#include "ui_screen_warn.h"


// 主窗口句柄类型
typedef enum 
{
	Common_Screen_SubID_RuningMode_Prepare,		          
	Common_Screen_SubID_RuningMode_Countdown,                
	Common_Screen_SubID_RuningMode_Setting,                 
	Common_Screen_SubID_RuningMode_TargetSetting,                 
	Common_Screen_SubID_RuningMode_TargetSetting_Distance,                 
	Common_Screen_SubID_RuningMode_TargetSetting_Duration,                 
	Common_Screen_SubID_RuningMode_TargetSetting_Calorie,                 
	Common_Screen_SubID_RuningMode_WarnSetting,                
	Common_Screen_SubID_RuningMode_WarnSetting_Distance,                 
	Common_Screen_SubID_RuningMode_WarnSetting_Duration,                 
	Common_Screen_SubID_RuningMode_WarnSetting_Calorie,                 
	Common_Screen_SubID_RuningMode_WarnSetting_Heartrate,              
	Common_Screen_SubID_RuningMode_WarnSetting_Heartrate_Upperlimit,                
	Common_Screen_SubID_RuningMode_WarnSetting_Heartrate_Lowerlimit,                
	Common_Screen_SubID_RuningMode_WarnSetting_Speed,                
	Common_Screen_SubID_RuningMode_WarnSetting_Speed_Upperlimit,                
	Common_Screen_SubID_RuningMode_WarnSetting_Speed_Lowerlimit,                
	Common_Screen_SubID_RuningMode_Datadetail,                 
	Common_Screen_SubID_RuningMode_Pause,                 
	Common_Screen_SubID_RuningMode_Continue,			
	Common_Screen_SubID_RuningMode_Menu,			
	Common_Screen_SubID_RuningMode_Abandon,			
	Common_Screen_SubID_RuningMode_CompleteMenu,			
	Common_Screen_SubID_RuningMode_History,			
	Common_Screen_SubID_RuningMode_Max,			
}Enum_Common_Screen_SUBID_RUNINGMODE;
    


void UI_Set_Curr_SubScreenID_Runingmode(Enum_Common_Screen_SUBID_RUNINGMODE curr_id);
int UI_Get_Curr_SubScreenID_Runingmode(void);

//RuningMode
void UI_Screen_RuningModeEntry(void);


void UI_Screen_RuningModePrepare_Entry(void);
void UI_Screen_RuningModePrepare_Display(void);
void UI_Screen_RuningModePrepare_Exit(void);


void UI_Screen_RuningModePrepare_shortkeyhandle(void);
void UI_Screen_RuningModePrepare_holdshortkeyhandle(void);
void UI_Screen_RuningModePrepare_holdlongkeyhandle(void);
void UI_Screen_RuningModePrepare_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModePrepare_tpupslidehandle(void);
void UI_Screen_RuningModePrepare_tpdownslidehandle(void);
void UI_Screen_RuningModePrepare_tpleftslidehandle(void);
void UI_Screen_RuningModePrepare_tprightslidehandle(void);


void UI_Screen_RuningModeCountDown_Entry(void);
void App_DispRuningModeCountDownRound(uint8_t *lcdram,float angle);
void UI_Screen_RuningModeCountDown_Display(void);
void UI_Screen_RuningModeCountDown_Exit(void);
void UI_Screen_RuningModeCountDown_shortkeyhandle(void);
void UI_Screen_RuningModeCountDown_holdshortkeyhandle(void);
void UI_Screen_RuningModeCountDown_holdlongkeyhandle(void);
void UI_Screen_RuningModeCountDown_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeCountDown_tpupslidehandle(void);
void UI_Screen_RuningModeCountDown_tpdownslidehandle(void);
void UI_Screen_RuningModeCountDown_tpleftslidehandle(void);
void UI_Screen_RuningModeCountDown_tprightslidehandle(void);


void UI_Screen_RuningModeSetting_Entry(void);
void UI_Screen_RuningModeSetting_Display(void);
void UI_Screen_RuningModeSetting_Exit(void);
void UI_Screen_RuningModeSetting_shortkeyhandle(void);
void UI_Screen_RuningModeSetting_holdshortkeyhandle(void);
void UI_Screen_RuningModeSetting_holdlongkeyhandle(void);
void UI_Screen_RuningModeSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeSetting_tpupslidehandle(void);
void UI_Screen_RuningModeSetting_tpdownslidehandle(void);
void UI_Screen_RuningModeSetting_tpleftslidehandle(void);
void UI_Screen_RuningModeSetting_tprightslidehandle(void);


// target 
void UI_Screen_RuningModeTargetSetting_Entry(void);
void UI_Screen_RuningModeTargetSetting_Display(void);
void UI_Screen_RuningModeTargetSetting_Exit(void);
void UI_Screen_RuningModeTargetSetting_shortkeyhandle(void);
void UI_Screen_RuningModeTargetSetting_holdshortkeyhandle(void);
void UI_Screen_RuningModeTargetSetting_holdlongkeyhandle(void);
void UI_Screen_RuningModeTargetSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeTargetSetting_tpupslidehandle(void);
void UI_Screen_RuningModeTargetSetting_tpdownslidehandle(void);
void UI_Screen_RuningModeTargetSetting_tpleftslidehandle(void);
void UI_Screen_RuningModeTargetSetting_tprightslidehandle(void);

//warn
void UI_Screen_RuningModeWarnSetting_Entry(void);
void UI_Screen_RuningModeWarnSetting_Display(void);
void UI_Screen_RuningModeWarnSetting_Exit(void);
void UI_Screen_RuningModeWarnSetting_shortkeyhandle(void);
void UI_Screen_RuningModeWarnSetting_holdshortkeyhandle(void);
void UI_Screen_RuningModeWarnSetting_holdlongkeyhandle(void);
void UI_Screen_RuningModeWarnSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeWarnSetting_tpupslidehandle(void);
void UI_Screen_RuningModeWarnSetting_tpdownslidehandle(void);
void UI_Screen_RuningModeWarnSetting_tpleftslidehandle(void);
void UI_Screen_RuningModeWarnSetting_tprightslidehandle(void);

void UI_Screen_RuningModeDistanceTargetSetting_Entry(void);
void UI_Screen_RuningModeDistanceTargetSetting_Display(void);
void UI_Screen_RuningModeDistanceTargetSetting_Exit(void);

void UI_Screen_RuningModeDistanceTargetSetting_shortkeyhandle(void);
void UI_Screen_RuningModeDistanceTargetSetting_holdshortkeyhandle(void);
void UI_Screen_RuningModeDistanceTargetSetting_holdlongkeyhandle(void);
void UI_Screen_RuningModeDistanceTargetSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeDistanceTargetSetting_tpupslidehandle(void);
void UI_Screen_RuningModeDistanceTargetSetting_tpdownslidehandle(void);
void UI_Screen_RuningModeDistanceTargetSetting_tpleftslidehandle(void);
void UI_Screen_RuningModeDistanceTargetSetting_tprightslidehandle(void);

void UI_Screen_RuningModeDurationTargetSetting_Entry(void);
void UI_Screen_RuningModeDurationTargetSetting_Display(void);
void UI_Screen_RuningModeDurationTargetSetting_Exit(void);

void UI_Screen_RuningModeDurationTargetSetting_shortkeyhandle(void);
void UI_Screen_RuningModeDurationTargetSetting_holdshortkeyhandle(void);
void UI_Screen_RuningModeDurationTargetSetting_holdlongkeyhandle(void);
void UI_Screen_RuningModeDurationTargetSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeDurationTargetSetting_tpupslidehandle(void);
void UI_Screen_RuningModeDurationTargetSetting_tpdownslidehandle(void);
void UI_Screen_RuningModeDurationTargetSetting_tpleftslidehandle(void);
void UI_Screen_RuningModeDurationTargetSetting_tprightslidehandle(void);


void UI_Screen_RuningModeCalorieTargetSetting_Entry(void);
void UI_Screen_RuningModeCalorieTargetSetting_Display(void);
void UI_Screen_RuningModeCalorieTargetSetting_Exit(void);

void UI_Screen_RuningModeCalorieTargetSetting_shortkeyhandle(void);
void UI_Screen_RuningModeCalorieTargetSetting_holdshortkeyhandle(void);
void UI_Screen_RuningModeCalorieTargetSetting_holdlongkeyhandle(void);
void UI_Screen_RuningModeCalorieTargetSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeCalorieTargetSetting_tpupslidehandle(void);
void UI_Screen_RuningModeCalorieTargetSetting_tpdownslidehandle(void);
void UI_Screen_RuningModeCalorieTargetSetting_tpleftslidehandle(void);
void UI_Screen_RuningModeCalorieTargetSetting_tprightslidehandle(void);


void UI_Screen_RuningModeHrWarnSetting_Entry(void);
void UI_Screen_RuningModeHrWarnSetting_Display(void);
void UI_Screen_RuningModeHrWarnSetting_Exit(void);

void UI_Screen_RuningModeHrWarnSetting_shortkeyhandle(void);
void UI_Screen_RuningModeHrWarnSetting_holdshortkeyhandle(void);
void UI_Screen_RuningModeHrWarnSetting_holdlongkeyhandle(void);
void UI_Screen_RuningModeHrWarnSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeHrWarnSetting_tpupslidehandle(void);
void UI_Screen_RuningModeHrWarnSetting_tpdownslidehandle(void);
void UI_Screen_RuningModeHrWarnSetting_tpleftslidehandle(void);
void UI_Screen_RuningModeHrWarnSetting_tprightslidehandle(void);



void UI_Screen_RuningModeSpeedWarnSetting_Entry(void);
void UI_Screen_RuningModeSpeedWarnSetting_Display(void);
void UI_Screen_RuningModeSpeedWarnSetting_Exit(void);

void UI_Screen_RuningModeSpeedWarnSetting_shortkeyhandle(void);
void UI_Screen_RuningModeSpeedWarnSetting_holdshortkeyhandle(void);
void UI_Screen_RuningModeSpeedWarnSetting_holdlongkeyhandle(void);
void UI_Screen_RuningModeSpeedWarnSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeSpeedWarnSetting_tpupslidehandle(void);
void UI_Screen_RuningModeSpeedWarnSetting_tpdownslidehandle(void);
void UI_Screen_RuningModeSpeedWarnSetting_tpleftslidehandle(void);
void UI_Screen_RuningModeSpeedWarnSetting_tprightslidehandle(void);


void UI_Screen_RuningModeHrWarnUpperLimitSetting_Entry(void);
void UI_Screen_RuningModeHrWarnLowerLimitSetting_Entry(void);
void UI_Screen_RuningModeHrWarnLlimitSetting_Display(void);
void UI_Screen_RuningModeHrWarnLlimitSetting_Exit(void);

void UI_Screen_RuningModeHrWarnLlimitSetting_shortkeyhandle(void);
void UI_Screen_RuningModeHrWarnLlimitSetting_holdshortkeyhandle(void);
void UI_Screen_RuningModeHrWarnLlimitSetting_holdlongkeyhandle(void);


void UI_Screen_RuningModeHrWarnUpperLimitSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeHrWarnLowerLimitSetting_tpclickhandle(int point_x,int point_y);

void UI_Screen_RuningModeHrWarnLlimitSetting_tpupslidehandle(void);
void UI_Screen_RuningModeHrWarnLlimitSetting_tpdownslidehandle(void);
void UI_Screen_RuningModeHrWarnLlimitSetting_tpleftslidehandle(void);
void UI_Screen_RuningModeHrWarnLlimitSetting_tprightslidehandle(void);


void UI_Screen_RuningModeSpeedUpperLlimitSetting_Entry(void);
void UI_Screen_RuningModeSpeedLowerLlimitSetting_Entry(void);
void UI_Screen_RuningModeSpeedLlimitSetting_Display(void);
void UI_Screen_RuningModeSpeedLlimitSetting_Exit(void);

void UI_Screen_RuningModeSpeedLlimitSetting_shortkeyhandle(void);
void UI_Screen_RuningModeSpeedLlimitSetting_holdshortkeyhandle(void);
void UI_Screen_RuningModeSpeedLlimitSetting_holdlongkeyhandle(void);

void UI_Screen_RuningModeSpeedUpperLlimitSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeSpeedLowerLlimitSetting_tpclickhandle(int point_x,int point_y);

void UI_Screen_RuningModeSpeedLlimitSetting_tpupslidehandle(void);
void UI_Screen_RuningModeSpeedLlimitSetting_tpdownslidehandle(void);
void UI_Screen_RuningModeSpeedLlimitSetting_tpleftslidehandle(void);
void UI_Screen_RuningModeSpeedLlimitSetting_tprightslidehandle(void);


void UI_Screen_RuningModeDetail_Entry(void);
void UI_Screen_RuningModeDetail_Display(void);
void UI_Screen_RuningModeDetail_Exit(void);


void UI_Screen_RuningModePause_Entry(void);
void UI_Screen_RuningModePause_Display(void);
void UI_Screen_RuningModePause_Exit(void);

void UI_Screen_RuningModeContinue_Entry(void);
void UI_Screen_RuningModeContinue_Display(void);
void UI_Screen_RuningModeContinue_Exit(void);

void UI_Screen_SportModeDataDetail_Entry(void);
void UI_Screen_SportModeDataDetail_Display(void);
void UI_Screen_SportModeDataDetail_Exit(void);

void UI_Screen_RuningModeDetail_shortkeyhandle(void);
void UI_Screen_RuningModeDetail_holdshortkeyhandle(void);
void UI_Screen_RuningModeDetail_holdlongkeyhandle(void);
void UI_Screen_RuningModeDetail_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeDetail_tpupslidehandle(void);
void UI_Screen_RuningModeDetail_tpdownslidehandle(void);
void UI_Screen_RuningModeDetail_tpleftslidehandle(void);
void UI_Screen_RuningModeDetail_tprightslidehandle(void);


void UI_Screen_RuningModePause_Timerhandle(void);
void UI_Screen_RuningModePause_Entry(void);
void UI_Screen_RuningModePause_Display(void);
void UI_Screen_RuningModePause_Exit(void);

void UI_Screen_RuningModeContinue_Timerhandle(void);
void UI_Screen_RuningModeContinue_Entry(void);
void UI_Screen_RuningModeContinue_Display(void);
void UI_Screen_RuningModeContinue_Exit(void);

void UI_Screen_RuningModeMenu_Entry(void);
void UI_Screen_RuningModeMenu_Display(void);
void UI_Screen_RuningModeMenu_Exit(void);
void UI_Screen_RuningModeMenu_shortkeyhandle(void);
void UI_Screen_RuningModeMenu_holdshortkeyhandle(void);
void UI_Screen_RuningModeMenu_holdlongkeyhandle(void);
void UI_Screen_RuningModeMenu_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeMenu_tpupslidehandle(void);
void UI_Screen_RuningModeMenu_tpdownslidehandle(void);
void UI_Screen_RuningModeMenu_tpleftslidehandle(void);
void UI_Screen_RuningModeMenu_tprightslidehandle(void);

void UI_Screen_RuningModeCompleteMenu_Entry(void);
void UI_Screen_RuningModeCompleteMenu_Display(void);
void UI_Screen_RuningModeCompleteMenu_Exit(void);
void UI_Screen_RuningModeCompleteMenu_shortkeyhandle(void);
void UI_Screen_RuningModeCompleteMenu_holdshortkeyhandle(void);
void UI_Screen_RuningModeCompleteMenu_holdlongkeyhandle(void);
void UI_Screen_RuningModeCompleteMenu_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeCompleteMenu_tpupslidehandle(void);
void UI_Screen_RuningModeCompleteMenu_tpdownslidehandle(void);
void UI_Screen_RuningModeCompleteMenu_tpleftslidehandle(void);
void UI_Screen_RuningModeCompleteMenu_tprightslidehandle(void);


void UI_Screen_RuningModeAbandon_Entry(void);
void UI_Screen_RuningModeAbandon_Display(void);
void UI_Screen_RuningModeAbandon_Exit(void);
void UI_Screen_RuningModeAbandon_shortkeyhandle(void);
void UI_Screen_RuningModeAbandon_holdshortkeyhandle(void);
void UI_Screen_RuningModeAbandon_holdlongkeyhandle(void);
void UI_Screen_RuningModeAbandon_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeAbandon_tpupslidehandle(void);
void UI_Screen_RuningModeAbandon_tpdownslidehandle(void);
void UI_Screen_RuningModeAbandon_tpleftslidehandle(void);
void UI_Screen_RuningModeAbandon_tprightslidehandle(void);



void UI_Screen_RuningModeHistory_Entry(void);
void UI_Screen_RuningModeHistory_Display(void);
void UI_Screen_RuningModeHistory_Exit(void);

void UI_Screen_RuningModeHistory_shortkeyhandle(void);
void UI_Screen_RuningModeHistory_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeHistory_tpupslidehandle(void);
void UI_Screen_RuningModeHistory_tpdownslidehandle(void);
void UI_Screen_RuningModeHistory_tpleftslidehandle(void);
void UI_Screen_RuningModeHistory_tprightslidehandle(void);



typedef enum 
{
	Enum_runningmode_setting_target_off,		          
	Enum_runningmode_setting_target_distance,                
	Enum_runningmode_setting_target_duration,                 
	Enum_runningmode_setting_target_calorie                
}Enum_runningmode_setting_target_type;


typedef struct
{
	Enum_runningmode_setting_target_type   target_type;		
	int target_distance;
	int target_duration;
	int target_calorie;
    int target_index;

	int warn_distance;
	int warn_duration;
	int warn_calorie;

	int warn_distance_index;
	int warn_duration_index;
	int warn_calorie_index;
    
    int heartrate_uplimit;
    int heartrate_lowlimit;
    
    int heartrate_uplimit_index;
    int heartrate_lowlimit_index;
    
    int speed_uplimit_switch;
    int speed_uplimit;
    int speed_lowlimit_switch;
    int speed_lowlimit;

}Struct_runningmode_setting;




void UI_Screen_RuningModeDistanceWarnSetting_Entry(void);
void UI_Screen_RuningModeDistanceWarnSetting_Display(void);
void UI_Screen_RuningModeDistanceWarnSetting_Exit(void);


void UI_Screen_RuningModeDistanceWarnSetting_shortkeyhandle(void);
void UI_Screen_RuningModeDistanceWarnSetting_holdshortkeyhandle(void);
void UI_Screen_RuningModeDistanceWarnSetting_holdlongkeyhandle(void);


void UI_Screen_RuningModeDistanceWarnSetting_Off(void);
void UI_Screen_RuningModeDistanceWarnSetting_500M(void);
void UI_Screen_RuningModeDistanceWarnSetting_1KM(void);
void UI_Screen_RuningModeDistanceWarnSetting_2KM(void);
void UI_Screen_RuningModeDistanceWarnSetting_3KM(void);
void UI_Screen_RuningModeDistanceWarnSetting_5KM(void);


void UI_Screen_RuningModeDistanceWarnSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeDistanceWarnSetting_tpupslidehandle(void);
void UI_Screen_RuningModeDistanceWarnSetting_tpdownslidehandle(void);
void UI_Screen_RuningModeDistanceWarnSetting_tpleftslidehandle(void);
void UI_Screen_RuningModeDistanceWarnSetting_tprightslidehandle(void);



void UI_Screen_RuningModeDurationWarnSetting_Entry(void);
void UI_Screen_RuningModeDurationWarnSetting_Display(void);
void UI_Screen_RuningModeDurationWarnSetting_Exit(void);

void UI_Screen_RuningModeDurationWarnSetting_shortkeyhandle(void);
void UI_Screen_RuningModeDurationWarnSetting_holdshortkeyhandle(void);
void UI_Screen_RuningModeDurationWarnSetting_holdlongkeyhandle(void);


void UI_Screen_RuningModeDurationWarnSetting_Off(void);
void UI_Screen_RuningModeDurationWarnSetting_5MIN(void);
void UI_Screen_RuningModeDurationWarnSetting_10MIN(void);
void UI_Screen_RuningModeDurationWarnSetting_15MIN(void);
void UI_Screen_RuningModeDurationWarnSetting_20MIN(void);
void UI_Screen_RuningModeDurationWarnSetting_30MIN(void);
void UI_Screen_RuningModeDurationWarnSetting_60MIN(void);
void UI_Screen_RuningModeDurationWarnSetting_90MIN(void);
void UI_Screen_RuningModeDurationWarnSetting_120MIN(void);


void UI_Screen_RuningModeDurationWarnSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeDurationWarnSetting_tpupslidehandle(void);
void UI_Screen_RuningModeDurationWarnSetting_tpdownslidehandle(void);
void UI_Screen_RuningModeDurationWarnSetting_tpleftslidehandle(void);
void UI_Screen_RuningModeDurationWarnSetting_tprightslidehandle(void);


void UI_Screen_RuningModeCalorieWarnSetting_Entry(void);
void UI_Screen_RuningModeCalorieWarnSetting_Display(void);
void UI_Screen_RuningModeCalorieWarnSetting_Exit(void);

void UI_Screen_RuningModeCalorieWarnSetting_shortkeyhandle(void);
void UI_Screen_RuningModeCalorieWarnSetting_holdshortkeyhandle(void);
void UI_Screen_RuningModeCalorieWarnSetting_holdlongkeyhandle(void);


void UI_Screen_RuningModeCalorieWarnSetting_Off(void);
void UI_Screen_RuningModeCalorieWarnSetting_50KCAL(void);
void UI_Screen_RuningModeCalorieWarnSetting_100KCAL(void);
void UI_Screen_RuningModeCalorieWarnSetting_150KCAL(void);
void UI_Screen_RuningModeCalorieWarnSetting_200KCAL(void);

void UI_Screen_RuningModeCalorieWarnSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_RuningModeCalorieWarnSetting_tpupslidehandle(void);
void UI_Screen_RuningModeCalorieWarnSetting_tpdownslidehandle(void);
void UI_Screen_RuningModeCalorieWarnSetting_tpleftslidehandle(void);
void UI_Screen_RuningModeCalorieWarnSetting_tprightslidehandle(void);

void UI_Screen_RuningModeSetting_Getsetting(Struct_runningmode_setting *info);

void UI_Screen_RuningModeSetting_Init(void);
#endif

