#ifndef UI_SCREEN_CLIMBINGMODE_H
#define UI_SCREEN_CLIMBINGMODE_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "mid_pressure.h"
#include "scene_climb.h"
#include "ui_screen_warn.h"

typedef enum 
{
	Common_Screen_SubID_ClimbingMode_Prepare,		          
	Common_Screen_SubID_ClimbingMode_Countdown,                
	Common_Screen_SubID_ClimbingMode_Setting,                 
	Common_Screen_SubID_ClimbingMode_TargetSetting,                 
    Common_Screen_SubID_ClimbingMode_TargetSetting_ClimbingDistance,                 
	Common_Screen_SubID_ClimbingMode_TargetSetting_Distance,                 
	Common_Screen_SubID_ClimbingMode_TargetSetting_Duration,                 
	Common_Screen_SubID_ClimbingMode_TargetSetting_Calorie,                 
	Common_Screen_SubID_ClimbingMode_WarnSetting,                
	Common_Screen_SubID_ClimbingMode_WarnSetting_Distance,                 
	Common_Screen_SubID_ClimbingMode_WarnSetting_Duration,                 
	Common_Screen_SubID_ClimbingMode_WarnSetting_Calorie,                 
	Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate,              
	Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate_Upperlimit,                
	Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate_Lowerlimit,                
	Common_Screen_SubID_ClimbingMode_WarnSetting_Elevation,                
	Common_Screen_SubID_ClimbingMode_WarnSetting_Elevation_Upperlimit,                
	Common_Screen_SubID_ClimbingMode_WarnSetting_Elevation_Lowerlimit,                
	Common_Screen_SubID_ClimbingMode_Datadetail,                 
	Common_Screen_SubID_ClimbingMode_Pause,                 
	Common_Screen_SubID_ClimbingMode_Continue,			
	Common_Screen_SubID_ClimbingMode_Menu,			
	Common_Screen_SubID_ClimbingMode_Abandon,			
	Common_Screen_SubID_ClimbingMode_CompleteMenu,			
	Common_Screen_SubID_ClimbingMode_History,			
	Common_Screen_SubID_ClimbingMode_Max,			
}Enum_Common_Screen_SUBID_CLIMBINGMODE;


void UI_Set_Curr_SubScreenID_Climbingmode(Enum_Common_Screen_SUBID_CLIMBINGMODE curr_id);
int UI_Get_Curr_SubScreenID_Climbingmode(void);


void UI_Screen_ClimbingModeEntry(void);
void UI_Screen_ClimbingModePrepare_Entry(void);
void UI_Screen_ClimbingModePrepare_Display(void);
void UI_Screen_ClimbingModePrepare_Exit(void);

void UI_Screen_ClimbingModePrepare_shortkeyhandle(void);
void UI_Screen_ClimbingModePrepare_holdshortkeyhandle(void);
void UI_Screen_ClimbingModePrepare_holdlongkeyhandle(void);
void UI_Screen_ClimbingModePrepare_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModePrepare_tpupslidehandle(void);
void UI_Screen_ClimbingModePrepare_tpdownslidehandle(void);
void UI_Screen_ClimbingModePrepare_tpleftslidehandle(void);
void UI_Screen_ClimbingModePrepare_tprightslidehandle(void);


void UI_Screen_ClimbingModeCountDown_Entry(void);
void UI_Screen_ClimbingModeCountDown_Display_Timerhandle(void);
void UI_Screen_ClimbingModeCountDown_Display(void);
void UI_Screen_ClimbingModeCountDown_Exit(void);

void UI_Screen_ClimbingModeCountDown_shortkeyhandle(void);
void UI_Screen_ClimbingModeCountDown_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeCountDown_holdlongkeyhandle(void);
void UI_Screen_ClimbingModeCountDown_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeCountDown_tpupslidehandle(void);
void UI_Screen_ClimbingModeCountDown_tpdownslidehandle(void);
void UI_Screen_ClimbingModeCountDown_tpleftslidehandle(void);
void UI_Screen_ClimbingModeCountDown_tprightslidehandle(void);


void UI_Screen_ClimbingModeSetting_Entry(void);
void UI_Screen_ClimbingModeSetting_Display(void);
void UI_Screen_ClimbingModeSetting_Exit(void);

void UI_Screen_ClimbingModeSetting_shortkeyhandle(void);
void UI_Screen_ClimbingModeSetting_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeSetting_holdlongkeyhandle(void);
void UI_Screen_ClimbingModeSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeSetting_tpupslidehandle(void);
void UI_Screen_ClimbingModeSetting_tpdownslidehandle(void);
void UI_Screen_ClimbingModeSetting_tpleftslidehandle(void);
void UI_Screen_ClimbingModeSetting_tprightslidehandle(void);


void UI_Screen_ClimbingModeHrWarnSetting_Entry(void);
void UI_Screen_ClimbingModeHrWarnSetting_Display(void);
void UI_Screen_ClimbingModeHrWarnSetting_Exit(void);

void UI_Screen_ClimbingModeHrWarnSetting_shortkeyhandle(void);
void UI_Screen_ClimbingModeHrWarnSetting_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeHrWarnSetting_holdlongkeyhandle(void);
void UI_Screen_ClimbingModeHrWarnSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeHrWarnSetting_tpupslidehandle(void);
void UI_Screen_ClimbingModeHrWarnSetting_tpdownslidehandle(void);
void UI_Screen_ClimbingModeHrWarnSetting_tpleftslidehandle(void);
void UI_Screen_ClimbingModeHrWarnSetting_tprightslidehandle(void);


void UI_Screen_ClimbingModeDetail_Timerhandle(void);
void UI_Screen_ClimbingModeDetail_Entry(void);
void UI_Screen_ClimbingModeDetail_Display(void);
void UI_Screen_ClimbingModeDetail_Exit(void);

void UI_Screen_ClimbingModeDetail_shortkeyhandle(void);
void UI_Screen_ClimbingModeDetail_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeDetail_holdlongkeyhandle(void);
void UI_Screen_ClimbingModeDetail_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeDetail_tpupslidehandle(void);
void UI_Screen_ClimbingModeDetail_tpdownslidehandle(void);
void UI_Screen_ClimbingModeDetail_tpleftslidehandle(void);
void UI_Screen_ClimbingModeDetail_tprightslidehandle(void);


void UI_Screen_ClimbingModePause_Timerhandle(void);
void UI_Screen_ClimbingModePause_Entry(void);
void UI_ScreenClimbingModePause_Display(void);
void UI_Screen_ClimbingModePause_Exit(void);

void UI_Screen_ClimbingModeContinue_Timerhandle(void);
void UI_Screen_ClimbingModeContinue_Entry(void);
void UI_Screen_ClimbingModeContinue_Display(void);
void UI_Screen_ClimbingModeContinue_Exit(void);


void UI_Screen_ClimbingModeMenu_Entry(void);
void UI_Screen_ClimbingModeMenu_Display(void);
void UI_Screen_ClimbingModeMenu_Exit(void);
void UI_Screen_ClimbingModeMenu_shortkeyhandle(void);
void UI_Screen_ClimbingModeMenu_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeMenu_holdlongkeyhandle(void);
void UI_Screen_ClimbingModeMenu_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeMenu_tpupslidehandle(void);
void UI_Screen_ClimbingModeMenu_tpdownslidehandle(void);
void UI_Screen_ClimbingModeMenu_tpleftslidehandle(void);
void UI_Screen_ClimbingModeMenu_tprightslidehandle(void);


void UI_Screen_ClimbingModeCompleteMenu_Entry(void);
void UI_Screen_ClimbingModeCompleteMenu_Display(void);
void UI_Screen_ClimbingModeCompleteMenu_Exit(void);

void UI_Screen_ClimbingModeCompleteMenu_shortkeyhandle(void);
void UI_Screen_ClimbingModeCompleteMenu_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeCompleteMenu_holdlongkeyhandle(void);
void UI_Screen_ClimbingModeCompleteMenu_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeCompleteMenu_tpupslidehandle(void);
void UI_Screen_ClimbingModeCompleteMenu_tpdownslidehandle(void);
void UI_Screen_ClimbingModeCompleteMenu_tpleftslidehandle(void);
void UI_Screen_ClimbingModeCompleteMenu_tprightslidehandle(void);


void UI_Screen_ClimbingModeAbandon_Entry(void);
void UI_Screen_ClimbingModeAbandon_Display(void);
void UI_Screen_ClimbingModeAbandon_Exit(void);

void UI_Screen_ClimbingModeAbandon_shortkeyhandle(void);
void UI_Screen_ClimbingModeAbandon_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeAbandon_holdlongkeyhandle(void);
void UI_Screen_ClimbingModeAbandon_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeAbandon_tpupslidehandle(void);
void UI_Screen_ClimbingModeAbandon_tpdownslidehandle(void);
void UI_Screen_ClimbingModeAbandon_tpleftslidehandle(void);
void UI_Screen_ClimbingModeAbandon_tprightslidehandle(void);



void UI_Screen_ClimbingModeHistory_Entry(void);
void UI_Screen_ClimbingModeHistory_Display(void);
void UI_Screen_ClimbingModeHistory_Exit(void);

void UI_Screen_ClimbingModeHistory_shortkeyhandle(void);
void UI_Screen_ClimbingModeHistory_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeHistory_tpupslidehandle(void);
void UI_Screen_ClimbingModeHistory_tpdownslidehandle(void);
void UI_Screen_ClimbingModeHistory_tpleftslidehandle(void);
void UI_Screen_ClimbingModeHistory_tprightslidehandle(void);


typedef enum 
{
	Enum_climbingmode_setting_target_off,		          
	Enum_climbingmode_setting_target_climbingdistance,                
	Enum_climbingmode_setting_target_distance,                
	Enum_climbingmode_setting_target_duration,                 
	Enum_climbingmode_setting_target_calorie                
}Enum_climbingmode_setting_target_type;


typedef struct
{

	Enum_climbingmode_setting_target_type   target_type;		
	int target_climbingdistance;
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
    
	int elevation_uplimit_switch;
	int elevation_uplimit;
	int elevation_lowlimit_switch;
	int elevation_lowlimit;

}Struct_climbingmode_setting;



void UI_Screen_ClimbingModeTargetSetting_Entry(void);
void UI_Screen_ClimbingModeTargetSetting_Display(void);
void UI_Screen_ClimbingModeTargetSetting_Exit(void);

void UI_Screen_ClimbingModeTargetSetting_shortkeyhandle(void);
void UI_Screen_ClimbingModeTargetSetting_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeTargetSetting_holdlongkeyhandle(void);

void UI_Screen_ClimbingModeTargetSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeTargetSetting_tpupslidehandle(void);
void UI_Screen_ClimbingModeTargetSetting_tpdownslidehandle(void);
void UI_Screen_ClimbingModeTargetSetting_tpleftslidehandle(void);
void UI_Screen_ClimbingModeTargetSetting_tprightslidehandle(void);


void UI_Screen_ClimbingModeWarnSetting_Entry(void);
void UI_Screen_ClimbingModeWarnSetting_Display(void);
void UI_Screen_ClimbingModeWarnSetting_Exit(void);

void UI_Screen_ClimbingModeWarnSetting_shortkeyhandle(void);
void UI_Screen_ClimbingModeWarnSetting_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeWarnSetting_holdlongkeyhandle(void);
void UI_Screen_ClimbingModeWarnSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeWarnSetting_tpupslidehandle(void);
void UI_Screen_ClimbingModeWarnSetting_tpdownslidehandle(void);
void UI_Screen_ClimbingModeWarnSetting_tpleftslidehandle(void);
void UI_Screen_ClimbingModeWarnSetting_tprightslidehandle(void);



void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_Entry(void);
void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_Display(void);
void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_Exit(void);

void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_shortkeyhandle(void);
void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_holdlongkeyhandle(void);


void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_100M(void);
void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_200M(void);
void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_300M(void);
void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_500M(void);
void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_800M(void);
void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_1000M(void);
void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_1500M(void);
void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_2000M(void);


void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_tpupslidehandle(void);
void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_tpdownslidehandle(void);
void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_tpleftslidehandle(void);
void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_tprightslidehandle(void);


void UI_Screen_ClimbingModeDurationTargetSetting_Entry(void);
void UI_Screen_ClimbingModeDurationTargetSetting_Display(void);
void UI_Screen_ClimbingModeDurationTargetSetting_Exit(void);

void UI_Screen_ClimbingModeDurationTargetSetting_shortkeyhandle(void);
void UI_Screen_ClimbingModeDurationTargetSetting_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeDurationTargetSetting_holdlongkeyhandle(void);

void UI_Screen_ClimbingModeDurationTargetSetting_20MIN(void);
void UI_Screen_ClimbingModeDurationTargetSetting_30MIN(void);
void UI_Screen_ClimbingModeDurationTargetSetting_60MIN(void);
void UI_Screen_ClimbingModeDurationTargetSetting_90MIN(void);
void UI_Screen_ClimbingModeDurationTargetSetting_120MIN(void);
void UI_Screen_ClimbingModeDurationTargetSetting_180MIN(void);
void UI_Screen_ClimbingModeDurationTargetSetting_240MIN(void);


void UI_Screen_ClimbingModeDurationTargetSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeDurationTargetSetting_tpupslidehandle(void);
void UI_Screen_ClimbingModeDurationTargetSetting_tpdownslidehandle(void);
void UI_Screen_ClimbingModeDurationTargetSetting_tpleftslidehandle(void);
void UI_Screen_ClimbingModeDurationTargetSetting_tprightslidehandle(void);

void UI_Screen_ClimbingModeCalorieTargetSetting_Entry(void);
void UI_Screen_ClimbingModeCalorieTargetSetting_Display(void);
void UI_Screen_ClimbingModeCalorieTargetSetting_Exit(void);

void UI_Screen_ClimbingModeCalorieTargetSetting_shortkeyhandle(void);
void UI_Screen_ClimbingModeCalorieTargetSetting_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeCalorieTargetSetting_holdlongkeyhandle(void);


void UI_Screen_ClimbingModeCalorieTargetSetting_100KCAL(void);
void UI_Screen_ClimbingModeCalorieTargetSetting_200KCAL(void);
void UI_Screen_ClimbingModeCalorieTargetSetting_300KCAL(void);
void UI_Screen_ClimbingModeCalorieTargetSetting_500KCAL(void);
void UI_Screen_ClimbingModeCalorieTargetSetting_800KCAL(void);
void UI_Screen_ClimbingModeCalorieTargetSetting_1000KCAL(void);

void UI_Screen_ClimbingModeCalorieTargetSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeCalorieTargetSetting_tpupslidehandle(void);
void UI_Screen_ClimbingModeCalorieTargetSetting_tpdownslidehandle(void);
void UI_Screen_ClimbingModeCalorieTargetSetting_tpleftslidehandle(void);
void UI_Screen_ClimbingModeCalorieTargetSetting_tprightslidehandle(void);


void UI_Screen_ClimbingModeDistanceTargetSetting_Entry(void);
void UI_Screen_ClimbingModeDistanceTargetSetting_Display(void);
void UI_Screen_ClimbingModeDistanceTargetSetting_Exit(void);

void UI_Screen_ClimbingModeDistanceTargetSetting_shortkeyhandle(void);
void UI_Screen_ClimbingModeDistanceTargetSetting_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeDistanceTargetSetting_holdlongkeyhandle(void);

void UI_Screen_ClimbingModeDistanceTargetSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeDistanceTargetSetting_tpupslidehandle(void);
void UI_Screen_ClimbingModeDistanceTargetSetting_tpdownslidehandle(void);
void UI_Screen_ClimbingModeDistanceTargetSetting_tpleftslidehandle(void);
void UI_Screen_ClimbingModeDistanceTargetSetting_tprightslidehandle(void);

void UI_Screen_ClimbingModeDistanceWarnSetting_Entry(void);
void UI_Screen_ClimbingModeDistanceWarnSetting_Display(void);
void UI_Screen_ClimbingModeDistanceWarnSetting_Exit(void);

void UI_Screen_ClimbingModeDistanceWarnSetting_shortkeyhandle(void);
void UI_Screen_ClimbingModeDistanceWarnSetting_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeDistanceWarnSetting_holdlongkeyhandle(void);

void UI_Screen_ClimbingModeDistanceWarnSetting_Off(void);
void UI_Screen_ClimbingModeDistanceWarnSetting_500M(void);
void UI_Screen_ClimbingModeDistanceWarnSetting_1KM(void);
void UI_Screen_ClimbingModeDistanceWarnSetting_2KM(void);
void UI_Screen_ClimbingModeDistanceWarnSetting_3KM(void);
void UI_Screen_ClimbingModeDistanceWarnSetting_5KM(void);

void UI_Screen_ClimbingModeDistanceWarnSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeDistanceWarnSetting_tpupslidehandle(void);
void UI_Screen_ClimbingModeDistanceWarnSetting_tpdownslidehandle(void);
void UI_Screen_ClimbingModeDistanceWarnSetting_tpleftslidehandle(void);
void UI_Screen_ClimbingModeDistanceWarnSetting_tprightslidehandle(void);


void UI_Screen_ClimbingModeDurationWarnSetting_Entry(void);
void UI_Screen_ClimbingModeDurationWarnSetting_Display(void);
void UI_Screen_ClimbingModeDurationWarnSetting_Exit(void);

void UI_Screen_ClimbingModeDurationWarnSetting_shortkeyhandle(void);
void UI_Screen_ClimbingModeDurationWarnSetting_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeDurationWarnSetting_holdlongkeyhandle(void);

void UI_Screen_ClimbingModeDurationWarnSetting_Off(void);
void UI_Screen_ClimbingModeDurationWarnSetting_5MIN(void);
void UI_Screen_ClimbingModeDurationWarnSetting_10MIN(void);
void UI_Screen_ClimbingModeDurationWarnSetting_15MIN(void);
void UI_Screen_ClimbingModeDurationWarnSetting_20MIN(void);
void UI_Screen_ClimbingModeDurationWarnSetting_30MIN(void);
void UI_Screen_ClimbingModeDurationWarnSetting_60MIN(void);
void UI_Screen_ClimbingModeDurationWarnSetting_90MIN(void);
void UI_Screen_ClimbingModeDurationWarnSetting_120MIN(void);


void UI_Screen_ClimbingModeDurationWarnSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeDurationWarnSetting_tpupslidehandle(void);
void UI_Screen_ClimbingModeDurationWarnSetting_tpdownslidehandle(void);
void UI_Screen_ClimbingModeDurationWarnSetting_tpleftslidehandle(void);
void UI_Screen_ClimbingModeDurationWarnSetting_tprightslidehandle(void);



void UI_Screen_ClimbingModeCalorieWarnSetting_Entry(void);
void UI_Screen_ClimbingModeCalorieWarnSetting_Display(void);
void UI_Screen_ClimbingModeCalorieWarnSetting_Exit(void);

void UI_Screen_ClimbingModeCalorieWarnSetting_shortkeyhandle(void);
void UI_Screen_ClimbingModeCalorieWarnSetting_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeCalorieWarnSetting_holdlongkeyhandle(void);

void UI_Screen_ClimbingModeCalorieWarnSetting_Off(void);
void UI_Screen_ClimbingModeCalorieWarnSetting_50KCAL(void);
void UI_Screen_ClimbingModeCalorieWarnSetting_100KCAL(void);
void UI_Screen_ClimbingModeCalorieWarnSetting_150KCAL(void);
void UI_Screen_ClimbingModeCalorieWarnSetting_200KCAL(void);


void UI_Screen_ClimbingModeCalorieWarnSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeCalorieWarnSetting_tpupslidehandle(void);
void UI_Screen_ClimbingModeCalorieWarnSetting_tpdownslidehandle(void);
void UI_Screen_ClimbingModeCalorieWarnSetting_tpleftslidehandle(void);
void UI_Screen_ClimbingModeCalorieWarnSetting_tprightslidehandle(void);




void UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Entry(void);
void UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Entry(void);
void UI_Screen_ClimbingModeHrWarnLlimitSetting_Display(void);
void UI_Screen_ClimbingModeHrWarnLlimitSetting_Exit(void);

void UI_Screen_ClimbingModeHrWarnLlimitSetting_shortkeyhandle(void);
void UI_Screen_ClimbingModeHrWarnLlimitSetting_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeHrWarnLlimitSetting_holdlongkeyhandle(void);

void UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Off(void);
void UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Range1(void);
void UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Range2(void);
void UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Range3(void);
void UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Range4(void);
void UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Range5(void);

void UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Off(void);
void UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Range1(void);
void UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Range2(void);
void UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Range3(void);
void UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Range4(void);
void UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Range5(void);


void UI_Screen_ClimbingModeHrWarnUpperLimitSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeHrWarnLowerLimitSetting_tpclickhandle(int point_x,int point_y);

void UI_Screen_ClimbingModeHrWarnLlimitSetting_tpupslidehandle(void);
void UI_Screen_ClimbingModeHrWarnLlimitSetting_tpdownslidehandle(void);
void UI_Screen_ClimbingModeHrWarnLlimitSetting_tpleftslidehandle(void);
void UI_Screen_ClimbingModeHrWarnLlimitSetting_tprightslidehandle(void);




void UI_Screen_ClimbingModeElevationWarnSetting_Entry(void);
void UI_Screen_ClimbingModeElevationWarnSetting_Display(void);
void UI_Screen_ClimbingModeElevationWarnSetting_Exit(void);


void UI_Screen_ClimbingModeElevationWarnSetting_shortkeyhandle(void);
void UI_Screen_ClimbingModeElevationWarnSetting_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeElevationWarnSetting_holdlongkeyhandle(void);

void UI_Screen_ClimbingModeElevationWarnSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_ClimbingModeElevationWarnSetting_tpupslidehandle(void);
void UI_Screen_ClimbingModeElevationWarnSetting_tpdownslidehandle(void);
void UI_Screen_ClimbingModeElevationWarnSetting_tpleftslidehandle(void);
void UI_Screen_ClimbingModeElevationWarnSetting_tprightslidehandle(void);


void UI_Screen_ClimbingModeElevationUpperLlimitSetting_Init(void);
void UI_Screen_ClimbingModeElevationUpperLlimitSetting_Save(void);
void UI_Screen_ClimbingModeElevationUpperLlimitSetting_Entry(void);


void UI_Screen_ClimbingModeElevationLowerLlimitSetting_Init(void);
void UI_Screen_ClimbingModeElevationLowerLlimitSetting_Save(void);
void UI_Screen_ClimbingModeElevationLowerLlimitSetting_Entry(void);


void UI_Screen_ClimbingModeElevationLlimitSetting_Display(void);
void UI_Screen_ClimbingModeElevationLlimitSetting_Exit(void);


void UI_Screen_ClimbingModeElevationLlimitSetting_shortkeyhandle(void);
void UI_Screen_ClimbingModeElevationLlimitSetting_holdshortkeyhandle(void);
void UI_Screen_ClimbingModeElevationLlimitSetting_holdlongkeyhandle(void);


void UI_Screen_ClimbingModeElevationUpperLlimitSetting_Button0(void);
void UI_Screen_ClimbingModeElevationUpperLlimitSetting_Button1(void);
void UI_Screen_ClimbingModeElevationUpperLlimitSetting_Button2(void);
void UI_Screen_ClimbingModeElevationUpperLlimitSetting_Button3(void);
void UI_Screen_ClimbingModeElevationUpperLlimitSetting_Button4(void);
void UI_Screen_ClimbingModeElevationUpperLlimitSetting_tpclickhandle(int point_x,int point_y);

void UI_Screen_ClimbingModeElevationLowerLlimitSetting_Button0(void);
void UI_Screen_ClimbingModeElevationLowerLlimitSetting_Button1(void);
void UI_Screen_ClimbingModeElevationLowerLlimitSetting_Button2(void);
void UI_Screen_ClimbingModeElevationLowerLlimitSetting_Button3(void);
void UI_Screen_ClimbingModeElevationLowerLlimitSetting_Button4(void);
void UI_Screen_ClimbingModeElevationLowerLlimitSetting_tpclickhandle(int point_x,int point_y);

void UI_Screen_ClimbingModeElevationLlimitSetting_tpupslidehandle(void);
void UI_Screen_ClimbingModeElevationLlimitSetting_tpdownslidehandle(void);
void UI_Screen_ClimbingModeElevationLlimitSetting_tpleftslidehandle(void);
void UI_Screen_ClimbingModeElevationLlimitSetting_tprightslidehandle(void);

void UI_Screen_ClimbingModeSetting_Getsetting(Struct_climbingmode_setting *info);
void UI_Screen_ClimbingModeSetting_Init(void);


 #endif


