#ifndef UI_SCREEN_SWIMMODE_H
#define UI_SCREEN_SWIMMODE_H

#include "ui_display_common.h"
#include "ui_display_imagesource.h"
#include "ui_display_fontsource.h"

#include "app_lcd.h"
#include "scene_swim.h"



// 主窗口句柄类型
typedef enum 
{
	Common_Screen_SubID_SwimMode_Prepare,		          
	Common_Screen_SubID_SwimMode_Countdown,                
	Common_Screen_SubID_SwimMode_Setting,                 
	Common_Screen_SubID_SwimMode_TargetSetting,                 
	Common_Screen_SubID_SwimMode_TargetSetting_Laps,                 
	Common_Screen_SubID_SwimMode_TargetSetting_Duration,                 
	Common_Screen_SubID_SwimMode_TargetSetting_Calorie,                 
	Common_Screen_SubID_SwimMode_WarnSetting,                 
	Common_Screen_SubID_SwimMode_WarnSetting_Laps,                 
	Common_Screen_SubID_SwimMode_WarnSetting_Duration,                 
	Common_Screen_SubID_SwimMode_WarnSetting_Calorie,                 
	Common_Screen_SubID_SwimMode_PoolLength,                
	Common_Screen_SubID_SwimMode_Datadetail,                 
	Common_Screen_SubID_SwimMode_Pause,                 
	Common_Screen_SubID_SwimMode_Continue,			
	Common_Screen_SubID_SwimMode_Menu,			
	Common_Screen_SubID_SwimMode_Abandon,			
	Common_Screen_SubID_SwimMode_CompleteMenu,			
	Common_Screen_SubID_SwimMode_History,			
	Common_Screen_SubID_SwimMode_Max,			// 窗口句柄数量，这个值必须准确
}Enum_Common_Screen_SUBID_SWIMMODE;



void UI_Set_Curr_SubScreenID_Swimmode(Enum_Common_Screen_SUBID_SWIMMODE curr_id);
int UI_Get_Curr_SubScreenID_Swimmode(void);


void UI_Screen_SwimModeEntry(void);
void UI_Screen_SwimModePrepare_Entry(void);
void UI_Screen_SwimModePrepare_Display(void);
void UI_Screen_SwimModePrepare_Exit(void);
void UI_Screen_SwimModePrepare_shortkeyhandle(void);
void UI_Screen_SwimModePrepare_holdshortkeyhandle(void);
void UI_Screen_SwimModePrepare_holdlongkeyhandle(void);
void UI_Screen_SwimModePrepare_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModePrepare_tpupslidehandle(void);
void UI_Screen_SwimModePrepare_tpdownslidehandle(void);
void UI_Screen_SwimModePrepare_tpleftslidehandle(void);
void UI_Screen_SwimModePrepare_tprightslidehandle(void);


void UI_Screen_SwimModeCountDown_Entry(void);
void UI_Screen_SwimModeCountDown_Display_Timerhandle(void);
void UI_Screen_SwimModeCountDown_Display(void);
void UI_Screen_SwimModeCountDown_Exit(void);
void UI_Screen_SwimModeCountDown_shortkeyhandle(void);
void UI_Screen_SwimModeCountDown_holdshortkeyhandle(void);
void UI_Screen_SwimModeCountDown_holdlongkeyhandle(void);
void UI_Screen_SwimModeCountDown_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModeCountDown_tpupslidehandle(void);
void UI_Screen_SwimModeCountDown_tpdownslidehandle(void);
void UI_Screen_SwimModeCountDown_tpleftslidehandle(void);
void UI_Screen_SwimModeCountDown_tprightslidehandle(void);


void UI_Screen_SwimModeSetting_Entry(void);
void UI_Screen_SwimModeSetting_Display(void);
void UI_Screen_SwimModeSetting_Exit(void);
void UI_Screen_SwimModeSetting_shortkeyhandle(void);
void UI_Screen_SwimModeSetting_holdshortkeyhandle(void);
void UI_Screen_SwimModeSetting_holdlongkeyhandle(void);
void UI_Screen_SwimModeSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModeSetting_tpupslidehandle(void);
void UI_Screen_SwimModeSetting_tpdownslidehandle(void);
void UI_Screen_SwimModeSetting_tpleftslidehandle(void);
void UI_Screen_SwimModeSetting_tprightslidehandle(void);


void UI_Screen_SwimModeDetail_Timerhandle(void);
void UI_Screen_SwimModeDetail_Entry(void);
void UI_Screen_SwimModeDetail_Display(void);
void UI_Screen_SwimModeDetail_Exit(void);
void UI_Screen_SwimModeDetail_shortkeyhandle(void);
void UI_Screen_SwimModeDetail_holdshortkeyhandle(void);
void UI_Screen_SwimModeDetail_holdlongkeyhandle(void);
void UI_Screen_SwimModeDetail_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModeDetail_tpupslidehandle(void);
void UI_Screen_SwimModeDetail_tpdownslidehandle(void);
void UI_Screen_SwimModeDetail_tpleftslidehandle(void);
void UI_Screen_SwimModeDetail_tprightslidehandle(void);


void UI_Screen_SwimModePause_Timerhandle(void);
void UI_Screen_SwimModePause_Entry(void);
void UI_Screen_SwimModePause_Display(void);
void UI_Screen_SwimModePause_Exit(void);


void UI_Screen_SwimModeContinue_Timerhandle(void);
void UI_Screen_SwimModeContinue_Entry(void);
void UI_Screen_SwimModeContinue_Display(void);
void UI_Screen_SwimModeContinue_Exit(void);

void UI_Screen_SwimModeMenu_Entry(void);
void UI_Screen_SwimModeMenu_Display(void);
void UI_Screen_SwimModeMenu_Exit(void);
void UI_Screen_SwimModeMenu_shortkeyhandle(void);
void UI_Screen_SwimModeMenu_holdshortkeyhandle(void);
void UI_Screen_SwimModeMenu_holdlongkeyhandle(void);
void UI_Screen_SwimModeMenu_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModeMenu_tpupslidehandle(void);
void UI_Screen_SwimModeMenu_tpdownslidehandle(void);
void UI_Screen_SwimModeMenu_tpleftslidehandle(void);
void UI_Screen_SwimModeMenu_tprightslidehandle(void);


void UI_Screen_SwimModeCompleteMenu_Entry(void);
void UI_Screen_SwimModeCompleteMenu_Display(void);
void UI_Screen_SwimModeCompleteMenu_Exit(void);
void UI_Screen_SwimModeCompleteMenu_shortkeyhandle(void);
void UI_Screen_SwimModeCompleteMenu_holdshortkeyhandle(void);
void UI_Screen_SwimModeCompleteMenu_holdlongkeyhandle(void);
void UI_Screen_SwimModeCompleteMenu_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModeCompleteMenu_tpupslidehandle(void);
void UI_Screen_SwimModeCompleteMenu_tpdownslidehandle(void);
void UI_Screen_SwimModeCompleteMenu_tpleftslidehandle(void);
void UI_Screen_SwimModeCompleteMenu_tprightslidehandle(void);


void UI_Screen_SwimModeAbandon_Entry(void);
void UI_Screen_SwimModeAbandon_Display(void);
void UI_Screen_SwimModeAbandon_Exit(void);
void UI_Screen_SwimModeAbandon_shortkeyhandle(void);
void UI_Screen_SwimModeAbandon_holdshortkeyhandle(void);
void UI_Screen_SwimModeAbandon_holdlongkeyhandlevoid(void);
void UI_Screen_SwimModeAbandon_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModeAbandon_tpupslidehandle(void);
void UI_Screen_SwimModeAbandon_tpdownslidehandle(void);
void UI_Screen_SwimModeAbandon_tpleftslidehandle(void);
void UI_Screen_SwimModeAbandon_tprightslidehandle(void);



void UI_Screen_SwimModeHistory_Entry(void);
void UI_Screen_SwimModeHistory_Display(void);
void UI_Screen_SwimModeHistory_Exit(void);
void UI_Screen_SwimModeHistory_shortkeyhandle(void);
void UI_Screen_SwimModeHistory_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModeHistory_tpupslidehandle(void);
void UI_Screen_SwimModeHistory_tpdownslidehandle(void);
void UI_Screen_SwimModeHistory_tpleftslidehandle(void);
void UI_Screen_SwimModeHistory_tprightslidehandle(void);



typedef enum 
{
	Enum_swimmode_setting_target_off,		          
	Enum_swimmode_setting_target_laps,                
	Enum_swimmode_setting_target_duration,                 
	Enum_swimmode_setting_target_calorie                
}Enum_swimmode_setting_target_type;



typedef struct
{

	Enum_swimmode_setting_target_type   target_type;		
	int target_laps;
	int target_duration;
	int target_calorie;
    
	int target_index;
    
	int warn_laps;
	int warn_duration;
	int warn_calorie;

	int warn_laps_index;
	int warn_duration_index;
	int warn_calorie_index;

    int pool_length;
    int pool_length_index;
    

}Struct_swimmode_setting;






void UI_Screen_SwimModeSetting_Init(void);
void UI_Screen_SwimModeSetting_Getsetting(Struct_swimmode_setting *info);


void UI_Screen_SwimModeSetting_Entry(void);
void UI_Screen_SwimModeSetting_Display(void);
void UI_Screen_SwimModeSetting_Exit(void);

void UI_Screen_SwimModeSetting_shortkeyhandle(void);
void UI_Screen_SwimModeSetting_holdshortkeyhandle(void);
void UI_Screen_SwimModeSetting_holdlongkeyhandle(void);

void UI_Screen_SwimModeSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModeSetting_tpupslidehandle(void);
void UI_Screen_SwimModeSetting_tpdownslidehandle(void);
void UI_Screen_SwimModeSetting_tpleftslidehandle(void);
void UI_Screen_SwimModeSetting_tprightslidehandle(void);




void UI_Screen_SwimModeTargetSetting_Entry(void);
void UI_Screen_SwimModeTargetSetting_Display(void);
void UI_Screen_SwimModeTargetSetting_Exit(void);

void UI_Screen_SwimModeTargetSetting_shortkeyhandle(void);
void UI_Screen_SwimModeTargetSetting_holdshortkeyhandle(void);
void UI_Screen_SwimModeTargetSetting_holdlongkeyhandle(void);
void UI_Screen_DistanceTargetSetting_None(void);

void UI_Screen_SwimModeTargetSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModeTargetSetting_tpupslidehandle(void);
void UI_Screen_SwimModeTargetSetting_tpdownslidehandle(void);
void UI_Screen_SwimModeTargetSetting_tpleftslidehandle(void);
void UI_Screen_SwimModeTargetSetting_tprightslidehandle(void);


void UI_Screen_SwimModeLapsTargetSetting_Entry(void);
void UI_Screen_SwimModeLapsTargetSetting_Display(void);
void UI_Screen_SwimModeLapsTargetSetting_Exit(void);

void UI_Screen_SwimModeLapsTargetSetting_shortkeyhandle(void);
void UI_Screen_SwimModeLapsTargetSetting_holdshortkeyhandle(void);
void UI_Screen_SwimModeLapsTargetSetting_holdlongkeyhandle(void);

void UI_Screen_SwimModeLapsTargetSetting_4(void);
void UI_Screen_SwimModeLapsTargetSetting_8(void);
void UI_Screen_SwimModeLapsTargetSetting_10(void);
void UI_Screen_SwimModeLapsTargetSetting_12(void);
void UI_Screen_SwimModeLapsTargetSetting_16(void);
void UI_Screen_SwimModeLapsTargetSetting_20(void);
void UI_Screen_SwimModeLapsTargetSetting_32(void);
void UI_Screen_SwimModeLapsTargetSetting_40(void);

void UI_Screen_SwimModeLapsTargetSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModeLapsTargetSetting_tpupslidehandle(void);
void UI_Screen_SwimModeLapsTargetSetting_tpdownslidehandle(void);
void UI_Screen_SwimModeLapsTargetSetting_tpleftslidehandle(void);
void UI_Screen_SwimModeLapsTargetSetting_tprightslidehandle(void);


void UI_Screen_SwimModeDurationTargetSetting_Entry(void);
void UI_Screen_SwimModeDurationTargetSetting_Display(void);
void UI_Screen_SwimModeDurationTargetSetting_Exit(void);


void UI_Screen_SwimModeDurationTargetSetting_shortkeyhandle(void);
void UI_Screen_SwimModeDurationTargetSetting_holdshortkeyhandle(void);
void UI_Screen_SwimModeDurationTargetSetting_holdlongkeyhandle(void);

void UI_Screen_SwimModeDurationTargetSetting_20MIN(void);
void UI_Screen_SwimModeDurationTargetSetting_30MIN(void);
void UI_Screen_SwimModeDurationTargetSetting_60MIN(void);
void UI_Screen_SwimModeDurationTargetSetting_90MIN(void);
void UI_Screen_SwimModeDurationTargetSetting_120MIN(void);
void UI_Screen_SwimModeDurationTargetSetting_180MIN(void);
void UI_Screen_SwimModeDurationTargetSetting_240MIN(void);


void UI_Screen_SwimModeDurationTargetSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModeDurationTargetSetting_tpupslidehandle(void);
void UI_Screen_SwimModeDurationTargetSetting_tpdownslidehandle(void);
void UI_Screen_SwimModeDurationTargetSetting_tpleftslidehandle(void);
void UI_Screen_SwimModeDurationTargetSetting_tprightslidehandle(void);


void UI_Screen_SwimModeCalorieTargetSetting_Entry(void);
void UI_Screen_SwimModeCalorieTargetSetting_Display(void);
void UI_Screen_SwimModeCalorieTargetSetting_Exit(void);


void UI_Screen_SwimModeCalorieTargetSetting_shortkeyhandle(void);
void UI_Screen_SwimModeCalorieTargetSetting_holdshortkeyhandle(void);
void UI_Screen_SwimModeCalorieTargetSetting_holdlongkeyhandle(void);


void UI_Screen_SwimModeCalorieTargetSetting_100KCAL(void);
void UI_Screen_SwimModeCalorieTargetSetting_200KCAL(void);
void UI_Screen_SwimModeCalorieTargetSetting_300KCAL(void);
void UI_Screen_SwimModeCalorieTargetSetting_500KCAL(void);
void UI_Screen_SwimModeCalorieTargetSetting_800KCAL(void);
void UI_Screen_SwimModeCalorieTargetSetting_1000KCAL(void);


void UI_Screen_SwimModeCalorieTargetSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModeCalorieTargetSetting_tpupslidehandle(void);
void UI_Screen_SwimModeCalorieTargetSetting_tpdownslidehandle(void);
void UI_Screen_SwimModeCalorieTargetSetting_tpleftslidehandle(void);
void UI_Screen_SwimModeCalorieTargetSetting_tprightslidehandle(void);



void UI_Screen_SwimModeWarnSetting_Entry(void);
void UI_Screen_SwimModeWarnSetting_Display(void);
void UI_Screen_SwimModeWarnSetting_Exit(void);

void UI_Screen_SwimModeWarnSetting_shortkeyhandle(void);
void UI_Screen_SwimModeWarnSetting_holdshortkeyhandle(void);
void UI_Screen_SwimModeWarnSetting_holdlongkeyhandle(void);

void UI_Screen_SwimModeWarnSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModeWarnSetting_tpupslidehandle(void);
void UI_Screen_SwimModeWarnSetting_tpdownslidehandle(void);
void UI_Screen_SwimModeWarnSetting_tpleftslidehandle(void);
void UI_Screen_SwimModeWarnSetting_tprightslidehandle(void);


void UI_Screen_SwimModeLapsWarnSetting_Entry(void);
void UI_Screen_SwimModeLapsWarnSetting_Display(void);
void UI_Screen_SwimModeLapsWarnSetting_Exit(void);

void UI_Screen_SwimModeLapsWarnSetting_shortkeyhandle(void);
void UI_Screen_SwimModeLapsWarnSetting_holdshortkeyhandle(void);
void UI_Screen_SwimModeLapsWarnSetting_holdlongkeyhandle(void);
void UI_Screen_SwimModeLapsWarnSetting_Off(void);


void UI_Screen_SwimModeLapsWarnSetting_4(void);
void UI_Screen_SwimModeLapsWarnSetting_8(void);
void UI_Screen_SwimModeLapsWarnSetting_10(void);
void UI_Screen_SwimModeLapsWarnSetting_12(void);
void UI_Screen_SwimModeLapsWarnSetting_16(void);
void UI_Screen_SwimModeLapsWarnSetting_20(void);

void UI_Screen_SwimModeLapsWarnSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModeLapsWarnSetting_tpupslidehandle(void);
void UI_Screen_SwimModeLapsWarnSetting_tpdownslidehandle(void);
void UI_Screen_SwimModeLapsWarnSetting_tpleftslidehandle(void);
void UI_Screen_SwimModeLapsWarnSetting_tprightslidehandle(void);


void UI_Screen_SwimModeDurationWarnSetting_Entry(void);
void UI_Screen_SwimModeDurationWarnSetting_Display(void);
void UI_Screen_SwimModeDurationWarnSetting_Exit(void);

void UI_Screen_SwimModeDurationWarnSetting_shortkeyhandle(void);
void UI_Screen_SwimModeDurationWarnSetting_holdshortkeyhandle(void);
void UI_Screen_SwimModeDurationWarnSetting_holdlongkeyhandle(void);
void UI_Screen_SwimModeDurationWarnSetting_Off(void);


void UI_Screen_SwimModeDurationWarnSetting_5MIN(void);
void UI_Screen_SwimModeDurationWarnSetting_10MIN(void);
void UI_Screen_SwimModeDurationWarnSetting_15MIN(void);
void UI_Screen_SwimModeDurationWarnSetting_20MIN(void);
void UI_Screen_SwimModeDurationWarnSetting_30MIN(void);
void UI_Screen_SwimModeDurationWarnSetting_60MIN(void);
void UI_Screen_SwimModeDurationWarnSetting_90MIN(void);
void UI_Screen_SwimModeDurationWarnSetting_120MIN(void);

void UI_Screen_SwimModeDurationWarnSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModeDurationWarnSetting_tpupslidehandle(void);
void UI_Screen_SwimModeDurationWarnSetting_tpdownslidehandle(void);
void UI_Screen_SwimModeDurationWarnSetting_tpleftslidehandle(void);
void UI_Screen_SwimModeDurationWarnSetting_tprightslidehandle(void);

void UI_Screen_SwimModeCalorieWarnSetting_Entry(void);
void UI_Screen_SwimModeCalorieWarnSetting_Display(void);
void UI_Screen_SwimModeCalorieWarnSetting_Exit(void);

void UI_Screen_SwimModeCalorieWarnSetting_shortkeyhandle(void);
void UI_Screen_SwimModeCalorieWarnSetting_holdshortkeyhandle(void);
void UI_Screen_SwimModeCalorieWarnSetting_holdlongkeyhandle(void);


void UI_Screen_SwimModeCalorieWarnSetting_Off(void);
void UI_Screen_SwimModeCalorieWarnSetting_50KCAL(void);
void UI_Screen_SwimModeCalorieWarnSetting_100KCAL(void);
void UI_Screen_SwimModeCalorieWarnSetting_150KCAL(void);
void UI_Screen_SwimModeCalorieWarnSetting_200KCAL(void);

void UI_Screen_SwimModeCalorieWarnSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModeCalorieWarnSetting_tpupslidehandle(void);
void UI_Screen_SwimModeCalorieWarnSetting_tpdownslidehandle(void);
void UI_Screen_SwimModeCalorieWarnSetting_tpleftslidehandle(void);
void UI_Screen_SwimModeCalorieWarnSetting_tprightslidehandle(void);

    
void UI_Screen_SwimModePoolLengthSetting_Entry(void);
void UI_Screen_SwimModePoolLengthSetting_Display(void);
void UI_Screen_SwimModePoolLengthSetting_Exit(void);

void UI_Screen_SwimModePoolLengthSetting_shortkeyhandle(void);
void UI_Screen_SwimModePoolLengthSetting_holdshortkeyhandle(void);
void UI_Screen_SwimModePoolLengthSetting_holdlongkeyhandle(void);



void UI_Screen_SwimModePoolLengthSetting_25(void);
void UI_Screen_SwimModePoolLengthSetting_50(void);
void UI_Screen_SwimModePoolLengthSetting_333(void);
void UI_Screen_SwimModePoolLengthSetting_25yd(void);
void UI_Screen_SwimModePoolLengthSetting_333yd(void);

void UI_Screen_SwimModePoolLengthSetting_tpclickhandle(int point_x,int point_y);
void UI_Screen_SwimModePoolLengthSetting_tpupslidehandle(void);
void UI_Screen_SwimModePoolLengthSetting_tpdownslidehandle(void);
void UI_Screen_SwimModePoolLengthSetting_tpleftslidehandle(void);
void UI_Screen_SwimModePoolLengthSetting_tprightslidehandle(void);



#endif

