#include "ui_screen_climbing.h"
#include "ui_screen_dateandtime.h"

Enum_Common_Screen_SUBID_CLIMBINGMODE curr_subscreenid_climbingmode;


//distance 
typedef enum
{
	ENUM_CMCLIMBINGDISTANCE_TARGET_100M = 0,
	ENUM_CMCLIMBINGDISTANCE_TARGET_200M,
	ENUM_CMCLIMBINGDISTANCE_TARGET_300M,
	ENUM_CMCLIMBINGDISTANCE_TARGET_500M,
	ENUM_CMCLIMBINGDISTANCE_TARGET_800M,
	ENUM_CMCLIMBINGDISTANCE_TARGET_1000M,
	ENUM_CMCLIMBINGDISTANCE_TARGET_1500M,
	ENUM_CMCLIMBINGDISTANCE_TARGET_2000M,
	ENUM_CMCLIMBINGDISTANCE_TARGET_MAX,
}enum_climbingmode_climbingdistancetarget;



char climbingmode_climbingdistancetarget_100m[] = {"100m"};
char climbingmode_climbingdistancetarget_200m[] = {"200m"};
char climbingmode_climbingdistancetarget_300m[] = {"300m"};
char climbingmode_climbingdistancetarget_500m[] = {"500m"};
char climbingmode_climbingdistancetarget_800m[] = {"800m"};
char climbingmode_climbingdistancetarget_1000m[] = {"1000m"};
char climbingmode_climbingdistancetarget_1500m[] = {"1500m"};
char climbingmode_climbingdistancetarget_2000m[] = {"2000m"};





//distance 
typedef enum
{
	ENUM_CMDISTANCE_TARGET_3KM = 0,
	ENUM_CMDISTANCE_TARGET_5KM,
	ENUM_CMDISTANCE_TARGET_10KM,
	ENUM_CMDISTANCE_TARGET_15KM,
	ENUM_CMDISTANCE_TARGET_20KM,
	ENUM_CMDISTANCE_TARGET_50KM,
	ENUM_CMDISTANCE_TARGET_80KM,
	ENUM_CMDISTANCE_TARGET_100KM,
	ENUM_CMDISTANCE_TARGET_MAX,
}enum_climbingmode_distancetarget;


char climbingmode_distancetarget_3km[] = {"3km"};
char climbingmode_distancetarget_5km[] = {"5km"};
char climbingmode_distancetarget_10km[] = {"10km"};
char climbingmode_distancetarget_15km[] = {"15km"};
char climbingmode_distancetarget_20km[] = {"20km"};
char climbingmode_distancetarget_50km[] = {"50km"};
char climbingmode_distancetarget_80km[] = {"80km"};
char climbingmode_distancetarget_100km[] = {"100km"};


//duration
typedef enum
{
	ENUM_CMDURATION_TARGET_20MIN = 0,
	ENUM_CMDURATION_TARGET_30MIN,
	ENUM_CMDURATION_TARGET_60MIN,
	ENUM_CMDURATION_TARGET_90MIN,
	ENUM_CMDURATION_TARGET_120MIN,
	ENUM_CMDURATION_TARGET_180MIN,
	ENUM_CMDURATION_TARGET_240MIN,
	ENUM_CMDURATION_TARGET_MAX,
}enum_climbingmode_durationtarget_enum;



char climbingmode_durationtarget_20min[] = {"20min"};
char climbingmode_durationtarget_30min[] = {"30min"};
char climbingmode_durationtarget_60min[] = {"60min"};
char climbingmode_durationtarget_90min[] = {"90min"};
char climbingmode_durationtarget_120min[] = {"120min"};
char climbingmode_durationtarget_180min[] = {"180min"};
char climbingmode_durationtarget_240min[] = {"240min"};


//calorie
typedef enum
{
	ENUM_CMCALORIE_TARGET_100KCAL,
	ENUM_CMCALORIE_TARGET_200KCAL,
	ENUM_CMCALORIE_TARGET_300KCAL,
	ENUM_CMCALORIE_TARGET_500KCAL,
	ENUM_CMCALORIE_TARGET_800KCAL,
	ENUM_CMCALORIE_TARGET_1000KCAL,
	ENUM_CMCALORIE_TARGET_MAX,
}enum_climbingmode_calorietarget;


char climbingmode_calorietarget_100kcal[] = {"100kcal"};
char climbingmode_calorietarget_200kcal[] = {"200kcal"};
char climbingmode_calorietarget_300kcal[] = {"300kcal"};
char climbingmode_calorietarget_500kcal[] = {"500kcal"};
char climbingmode_calorietarget_800kcal[] = {"800kcal"};
char climbingmode_calorietarget_1000kcal[] = {"1000kcal"};


typedef enum
{
	ENUM_CMDISTANCE_WARN_OFF = 0,
	ENUM_CMDISTANCE_WARN_500M,
	ENUM_CMDISTANCE_WARN_1KM,
	ENUM_CMDISTANCE_WARN_2KM,
	ENUM_CMDISTANCE_WARN_3KM,
	ENUM_CMDISTANCE_WARN_5KM,
	ENUM_CMDISTANCE_WARN_MAX,
}enum_climbingmode_distancewarn;


char climbingmode_distancewarn_500m[] = {"500m"};
char climbingmode_distancewarn_1km[] = {"1km"};
char climbingmode_distancewarn_2km[] = {"2km"};
char climbingmode_distancewarn_3km[] = {"3km"};
char climbingmode_distancewarn_5km[] = {"5km"};



typedef enum
{
	ENUM_CMDURATION_WARN_OFF = 0,
	ENUM_CMDURATION_WARN_5MIN,
	ENUM_CMDURATION_WARN_10MIN,
	ENUM_CMDURATION_WARN_15MIN,
	ENUM_CMDURATION_WARN_20MIN,
	ENUM_CMDURATION_WARN_30MIN,
	ENUM_CMDURATION_WARN_60MIN,
	ENUM_CMDURATION_WARN_90MIN,
	ENUM_CMDURATION_WARN_120MIN,
	ENUM_CMDURATION_WARN_MAX,
}enum_climbingmode_durationwarn;


char climbingmode_durationwarn_5min[] = {"5min"};
char climbingmode_durationwarn_10min[] = {"10min"};
char climbingmode_durationwarn_15min[] = {"15min"};
char climbingmode_durationwarn_20min[] = {"20min"};
char climbingmode_durationwarn_30min[] = {"30min"};
char climbingmode_durationwarn_60min[] = {"60min"};
char climbingmode_durationwarn_90min[] = {"90min"};
char climbingmode_durationwarn_120min[] = {"120min"};


typedef enum
{
	ENUM_CMCALORIE_WARN_OFF,
	ENUM_CMCALORIE_WARN_50KCAL,
	ENUM_CMCALORIE_WARN_100KCAL,
	ENUM_CMCALORIE_WARN_150KCAL,
	ENUM_CMCALORIE_WARN_200KCAL,
	ENUM_CMCALORIE_WARN_MAX,
}enum_climbingmode_caloriewarn;


char climbingmode_caloriewarn_50kcal[] = {"50kcal"};
char climbingmode_caloriewarn_100kcal[] = {"100kcal"};
char climbingmode_caloriewarn_150kcal[] = {"150kcal"};
char climbingmode_caloriewarn_200kcal[] = {"200kcal"};


void UI_Set_Curr_SubScreenID_Climbingmode(Enum_Common_Screen_SUBID_CLIMBINGMODE curr_id)
{

    curr_subscreenid_climbingmode = curr_id;

}

int UI_Get_Curr_SubScreenID_Climbingmode(void)
{

    return curr_subscreenid_climbingmode;

}


//RuningMode
void UI_Screen_ClimbingModeEntry(void)
{

    switch(curr_subscreenid_climbingmode)
    {
        case Common_Screen_SubID_ClimbingMode_Prepare:
            UI_Screen_ClimbingModePrepare_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_Countdown:
            UI_Screen_ClimbingModeCountDown_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_Setting:
            UI_Screen_ClimbingModeSetting_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_TargetSetting:
            UI_Screen_ClimbingModeTargetSetting_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_TargetSetting_ClimbingDistance:
            UI_Screen_ClimbingModeClimbingDistanceTargetSetting_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_TargetSetting_Distance:
            UI_Screen_ClimbingModeDistanceTargetSetting_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_TargetSetting_Duration:
            UI_Screen_ClimbingModeDurationTargetSetting_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_TargetSetting_Calorie:
            UI_Screen_ClimbingModeCalorieTargetSetting_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_WarnSetting:
            UI_Screen_ClimbingModeWarnSetting_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_WarnSetting_Distance:
            UI_Screen_ClimbingModeDistanceWarnSetting_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_WarnSetting_Duration:
            UI_Screen_ClimbingModeDurationWarnSetting_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_WarnSetting_Calorie:
            UI_Screen_ClimbingModeCalorieWarnSetting_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate:
            UI_Screen_ClimbingModeHrWarnSetting_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate_Upperlimit:
            UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate_Lowerlimit:
            UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_WarnSetting_Elevation:
            UI_Screen_ClimbingModeElevationWarnSetting_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_WarnSetting_Elevation_Upperlimit:
            UI_Screen_ClimbingModeElevationUpperLlimitSetting_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_WarnSetting_Elevation_Lowerlimit:
            UI_Screen_ClimbingModeElevationLowerLlimitSetting_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_Datadetail:
            UI_Screen_ClimbingModeDetail_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_Pause:
            UI_Screen_ClimbingModePause_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_Continue:
            UI_Screen_ClimbingModeContinue_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_Menu:
            UI_Screen_ClimbingModeMenu_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_Abandon:
            UI_Screen_ClimbingModeAbandon_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_CompleteMenu:
            UI_Screen_ClimbingModeCompleteMenu_Entry();
        break;
        case Common_Screen_SubID_ClimbingMode_History:
            UI_Screen_ClimbingModeHistory_Entry();
        break;
        default:
            UI_Screen_ClimbingModePrepare_Entry();
            break;
    }

}



//RuningMode
void UI_Screen_ClimbingModePrepare_Entry(void)
{
    //初始化数据等
    UI_Screen_ClimbingModePrepare_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModePrepare_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModePrepare_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModePrepare_tpupslidehandle,
                                    UI_Screen_ClimbingModePrepare_tpdownslidehandle,
                                    UI_Screen_ClimbingModePrepare_tpleftslidehandle,
                                    UI_Screen_ClimbingModePrepare_tprightslidehandle);

}

void UI_Screen_ClimbingModePrepare_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_Prepare)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    
    UI_Common_Show_ThreeIconBar(temp_ram,0,0,(uint8_t*)image_gps_24_h,(uint8_t*)image_hr_24_h,(uint8_t*)NULL);

    UI_Common_Add_Battery(temp_ram,124,17,1);
    
    UI_Common_Show_ModeListIconStringBar(temp_ram,0,59,(uint8_t*)image_sportmode_climb_24_h,(uint8_t*)image_sportmode_start_24_h,(uint8_t*)BtnSport_h,(uint8_t*)gchinesefont_sportscene_start,APP_COLOR_RED,APP_COLOR_WHITE);
    UI_Common_Show_ModeListIconStringBar(temp_ram,0,118,NULL,(uint8_t*)image_sportmode_right_24_h,NULL,(uint8_t*)gchinesefont_sportscene_setting,APP_COLOR_BLACK,APP_COLOR_WHITE);

    UI_Display_Prepare(temp_ram);
}



void UI_Screen_ClimbingModePrepare_Exit(void)
{
    //初始化数据等


}

void UI_Screen_ClimbingModePrepare_shortkeyhandle(void)
{

    //UI_Common_Shake();

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Countdown);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModePrepare_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModePrepare_holdlongkeyhandle(void)
{
}

void UI_Screen_ClimbingModePrepare_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Common_Shake();
            UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Countdown);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
            UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
            UI_Screen_draw_Screen();
        }
        break;
        default:
        break;
    }


    
}

void UI_Screen_ClimbingModePrepare_tpupslidehandle(void)
{
}

void UI_Screen_ClimbingModePrepare_tpdownslidehandle(void)
{
}

void UI_Screen_ClimbingModePrepare_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModePrepare_tprightslidehandle(void)
{


    UI_Set_Curr_ScreenID(Common_Screen_MainID_Modelist);
    UI_Screen_draw_Screen();

}

extern UI_Common_sportmode_countdown_s sportmode_countdown;

void UI_Screen_ClimbingModeCountDown_Entry(void)
{

    UI_Common_SportModeCountDownInfoDefault();
    
    UI_Screen_ClimbingModeCountDown_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeCountDown_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeCountDown_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeCountDown_tpupslidehandle,
                                    UI_Screen_ClimbingModeCountDown_tpdownslidehandle,
                                    UI_Screen_ClimbingModeCountDown_tpleftslidehandle,
                                    UI_Screen_ClimbingModeCountDown_tprightslidehandle);
}

void UI_Screen_ClimbingModeCountDown_Display_Timerhandle(void)
{
        UI_Screen_ClimbingModeCountDown_Display();
}


void  UI_Screen_ClimbingModeCountDown_Display(void)
{
    int ctime = 0;
    uint8_t* fontinfo = NULL;
    double angle = 0;
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_Countdown)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    
    
    if(sportmode_countdown.curr_time<sportmode_countdown.total_time)
    {
        ctime = (sportmode_countdown.total_time-sportmode_countdown.curr_time)/1000;
        angle = (double)sportmode_countdown.curr_time/(double)sportmode_countdown.total_time*2*PI;
        UI_Common_DispRuningModeCountDownRound(temp_ram,angle);
        sportmode_countdown.curr_time = sportmode_countdown.curr_time + sportmode_countdown.segment_time;
        UI_Common_set_timer_handle(UI_Screen_ClimbingModeCountDown_Display_Timerhandle);
        App_Lcd_TimerStart(sportmode_countdown.segment_time);
    }
    else
    {
        UI_Screen_ClimbingModeCountDown_Exit();
        
        Scene_Climb_Enable();
        //登山模式开启，关闭大休眠
        UI_Commom_Set_Allow_Lockstate2(0);
        UI_Common_Shake();
        UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Datadetail);
        UI_Screen_draw_Screen();
        
        return;
    }

    switch(ctime)
    {
        case 1:
            fontinfo = (uint8_t*)font_tgl_96_1_h;
            break;
        case 2:
            fontinfo = (uint8_t*)font_tgl_96_2_h;
            break;
        case 3:
            fontinfo = (uint8_t*)font_tgl_96_3_h;
            break;
        default:
            fontinfo = (uint8_t*)font_tgl_96_1_h;
            break;
    
    }
    
    UI_Common_AddBWsourcePic(temp_ram,74,53,(uint8_t*)fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);
    
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_ClimbingModeCountDown_Exit(void)
{
     UI_Common_set_timer_handle(NULL);
     App_Lcd_TimerStop();
}

void UI_Screen_ClimbingModeCountDown_shortkeyhandle(void)
{

    UI_Screen_ClimbingModeCountDown_Exit();
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeCountDown_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeCountDown_holdlongkeyhandle(void)
{
}

void UI_Screen_ClimbingModeCountDown_tpclickhandle(int point_x,int point_y)
{


    
}

void UI_Screen_ClimbingModeCountDown_tpupslidehandle(void)
{


}

void UI_Screen_ClimbingModeCountDown_tpdownslidehandle(void)
{
}

void UI_Screen_ClimbingModeCountDown_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeCountDown_tprightslidehandle(void)
{

    UI_Screen_ClimbingModeCountDown_Exit();
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();


}


Struct_climbingmode_setting climbingmode_setting_info;

void UI_Screen_ClimbingModeSetting_Init(void)
{

    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_off;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;
    climbingmode_setting_info.target_index = 0;
    
    climbingmode_setting_info.warn_distance = 0;
    climbingmode_setting_info.warn_duration = 0;
    climbingmode_setting_info.warn_calorie = 0;
    
    climbingmode_setting_info.warn_distance_index = 0;
    climbingmode_setting_info.warn_duration_index = 0;
    climbingmode_setting_info.warn_calorie_index = 0;
    
    climbingmode_setting_info.heartrate_uplimit = 0;
    climbingmode_setting_info.heartrate_lowlimit = 0;
    
    climbingmode_setting_info.heartrate_uplimit_index = 0;
    climbingmode_setting_info.heartrate_lowlimit_index = 0;
    
    climbingmode_setting_info.elevation_uplimit_switch = 0;
    climbingmode_setting_info.elevation_uplimit = 0;
    climbingmode_setting_info.elevation_lowlimit_switch = 0;
    climbingmode_setting_info.elevation_lowlimit = 0;
        
        
}

void UI_Screen_ClimbingModeSetting_Getsetting(Struct_climbingmode_setting *info)
{

    memcpy(info, &climbingmode_setting_info, sizeof(Struct_climbingmode_setting));

}


void UI_Screen_ClimbingModeSetting_Entry(void)
{

    UI_Screen_ClimbingModeSetting_Display();
    
    UI_Common_set_key_handle(UI_Screen_ClimbingModeSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeSetting_tpupslidehandle,
                                    UI_Screen_ClimbingModeSetting_tpdownslidehandle,
                                    UI_Screen_ClimbingModeSetting_tpleftslidehandle,
                                    UI_Screen_ClimbingModeSetting_tprightslidehandle);
    
}


void UI_Screen_ClimbingModeSetting_Display(void)
{

    uint8_t* fontinfo = NULL;
    int font_type = 0;
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_Setting)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    

    if(climbingmode_setting_info.target_type == Enum_climbingmode_setting_target_off)
    {
        fontinfo = (uint8_t*)gchinesefont_sportscene_turnoff_s;
        font_type = 0;
    }
    else if(climbingmode_setting_info.target_type == Enum_climbingmode_setting_target_climbingdistance)
    {



     #if 0
````````typedef enum
        {
            ENUM_CMCLIMBINGDISTANCE_TARGET_100M = 0,
            ENUM_CMCLIMBINGDISTANCE_TARGET_200M,
            ENUM_CMCLIMBINGDISTANCE_TARGET_300M,
            ENUM_CMCLIMBINGDISTANCE_TARGET_500M,
            ENUM_CMCLIMBINGDISTANCE_TARGET_800M,
            ENUM_CMCLIMBINGDISTANCE_TARGET_1000M,
            ENUM_CMCLIMBINGDISTANCE_TARGET_1500M,
            ENUM_CMCLIMBINGDISTANCE_TARGET_2000M,
            ENUM_CMCLIMBINGDISTANCE_TARGET_MAX,
        }enum_climbingmode_climbingdistancetarget;
        #endif

        switch(climbingmode_setting_info.target_climbingdistance)
        {

            
            case 100:
                fontinfo = (uint8_t *)climbingmode_climbingdistancetarget_100m;
                font_type = 1;
            break;
            case 200:
                fontinfo = (uint8_t *)climbingmode_climbingdistancetarget_200m;
                font_type = 1;
            break;
            case 300:
                fontinfo = (uint8_t *)climbingmode_climbingdistancetarget_300m;
                font_type = 1;
            break;
            case 500:
                fontinfo = (uint8_t *)climbingmode_climbingdistancetarget_500m;
                font_type = 1;
            break;
            case 800:
                fontinfo = (uint8_t *)climbingmode_climbingdistancetarget_800m;
                font_type = 1;
            break;
            case 1000:
                fontinfo = (uint8_t *)climbingmode_climbingdistancetarget_1000m;
            font_type = 1;
            break;
            case 1500:
                fontinfo = (uint8_t *)climbingmode_climbingdistancetarget_1500m;
                font_type = 1;
            break;
            case 2000:
                fontinfo = (uint8_t *)climbingmode_climbingdistancetarget_2000m;
                font_type = 1;
            break;
            default:
            break;
        }

    
    }    
    else if(climbingmode_setting_info.target_type == Enum_climbingmode_setting_target_distance)
    {
#if 0
        //distance 
        typedef enum
        {
            ENUM_CMDISTANCE_TARGET_3KM = 0,
            ENUM_CMDISTANCE_TARGET_5KM,
            ENUM_CMDISTANCE_TARGET_10KM,
            ENUM_CMDISTANCE_TARGET_15KM,
            ENUM_CMDISTANCE_TARGET_20KM,
            ENUM_CMDISTANCE_TARGET_50KM,
            ENUM_CMDISTANCE_TARGET_80KM,
            ENUM_CMDISTANCE_TARGET_100KM,
            ENUM_CMDISTANCE_TARGET_MAX,
        }enum_climbingmode_distancetarget;
#endif
    
        switch(climbingmode_setting_info.target_distance)
        {

            
            case 3000:
                fontinfo = (uint8_t *)climbingmode_distancetarget_3km;
                font_type = 1;
            break;
            case 5000:
                fontinfo = (uint8_t *)climbingmode_distancetarget_5km;
                font_type = 1;
            break;
            case 10000:
                fontinfo = (uint8_t *)climbingmode_distancetarget_10km;
                font_type = 1;
            break;
            case 15000:
                fontinfo = (uint8_t *)climbingmode_distancetarget_15km;
                font_type = 1;
            break;
            case 20000:
                fontinfo = (uint8_t *)climbingmode_distancetarget_20km;
                font_type = 1;
            break;
            case 50000:
                fontinfo = (uint8_t *)climbingmode_distancetarget_50km;
                font_type = 1;
            break;
            case 80000:
                fontinfo = (uint8_t *)climbingmode_distancetarget_80km;
                font_type = 1;
            break;
            case 100000:
                fontinfo = (uint8_t *)climbingmode_distancetarget_100km;
                font_type = 1;
            break;
            default:
            break;
        }
    }
    else if(climbingmode_setting_info.target_type == Enum_climbingmode_setting_target_duration)
    {

    
        //duration
#if 0
            typedef enum
            {
                ENUM_SMDURATION_TARGET_20MIN = 0,
                ENUM_SMDURATION_TARGET_30MIN,
                ENUM_SMDURATION_TARGET_60MIN,
                ENUM_SMDURATION_TARGET_90MIN,
                ENUM_SMDURATION_TARGET_120MIN,
                ENUM_SMDURATION_TARGET_180MIN,
                ENUM_SMDURATION_TARGET_240MIN,
                ENUM_SMDURATION_TARGET_MAX,
            }app_swimmodedurationtarget_enum;
#endif
        
        switch(climbingmode_setting_info.target_duration)
        {

            case 20*60:
                fontinfo = (uint8_t *)climbingmode_durationtarget_20min;
                font_type = 1;
            break;
            case 30*60:
                fontinfo = (uint8_t *)climbingmode_durationtarget_30min;
                font_type = 1;
            break;
            case 60*60:
                fontinfo = (uint8_t *)climbingmode_durationtarget_60min;
                font_type = 1;
            break;
            case 90*60:
                fontinfo = (uint8_t *)climbingmode_durationtarget_90min;
                font_type = 1;
            break;
            case 120*60:
                fontinfo = (uint8_t *)climbingmode_durationtarget_120min;
                font_type = 1;
            break;
            case 180*60:
                fontinfo = (uint8_t *)climbingmode_durationtarget_180min;
                font_type = 1;
            break;
            case 240*60:
                fontinfo = (uint8_t *)climbingmode_durationtarget_240min;
                font_type = 1;
            break;            
            default:
            break;


        
        }
    }
    else if(climbingmode_setting_info.target_type == Enum_climbingmode_setting_target_calorie)
    {

#if 0
            typedef enum
            {
                ENUM_SMCALORIE_TARGET_100KCAL,
                ENUM_SMCALORIE_TARGET_200KCAL,
                ENUM_SMCALORIE_TARGET_300KCAL,
                ENUM_SMCALORIE_TARGET_500KCAL,
                ENUM_SMCALORIE_TARGET_800KCAL,
                ENUM_SMCALORIE_TARGET_1000KCAL,
                ENUM_SMCALORIE_TARGET_MAX,
            }app_swimmodecalorietarget_enum;
#endif
        
        switch(climbingmode_setting_info.target_calorie)
        {

            case 100:
                fontinfo = (uint8_t *)climbingmode_calorietarget_100kcal;
                font_type = 1;
            break;
            case 200:
                fontinfo = (uint8_t *)climbingmode_calorietarget_200kcal;
                font_type = 1;
            break;
            case 300:
                fontinfo = (uint8_t *)climbingmode_calorietarget_300kcal;
                font_type = 1;
            break;
            case 500:
                fontinfo = (uint8_t *)climbingmode_calorietarget_500kcal;
                font_type = 1;
            break;
            case 800:
                fontinfo = (uint8_t *)climbingmode_calorietarget_800kcal;
                font_type = 1;
            break;
            case 1000:
                fontinfo = (uint8_t *)climbingmode_calorietarget_1000kcal;
                font_type = 1;
            break;
            
            default:
            break;
        
        }
    }



    UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t*)gchinesefont_sportscene_target,(uint8_t*)fontinfo,NULL,font_type);
    UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t*)gchinesefont_sportscene_warn,NULL,NULL,0);

    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_ClimbingModeSetting_Exit(void)
{
}


void UI_Screen_ClimbingModeSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_ClimbingModeSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_TargetSetting);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        break;
        default:
        break;
    }

    
}


void UI_Screen_ClimbingModeSetting_tpupslidehandle(void)
{
}

void UI_Screen_ClimbingModeSetting_tpdownslidehandle(void)
{
}

void UI_Screen_ClimbingModeSetting_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();

}

// target 

static int memu_page = 0;

void UI_Screen_ClimbingModeTargetSetting_Entry(void)
{

    UI_Screen_ClimbingModeTargetSetting_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeTargetSetting_tpclickhandle);
    
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeTargetSetting_tpupslidehandle,
                                    UI_Screen_ClimbingModeTargetSetting_tpdownslidehandle,
                                    UI_Screen_ClimbingModeTargetSetting_tpleftslidehandle,
                                    UI_Screen_ClimbingModeTargetSetting_tprightslidehandle);
    
}

void UI_Screen_ClimbingModeTargetSetting_Display(void)
{


    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_TargetSetting)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    
    if(memu_page == 0)
    {
        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t*)gchinesefont_sportscene_target_notarget,(uint8_t*)NULL,NULL,0);
        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t*)gchinesefont_sportscene_target_Climbingdistance,(uint8_t*)NULL,NULL,0);
        UI_Common_List_RarrowDoubleline(temp_ram,0,118,(uint8_t*)gchinesefont_sportscene_target_distance,(uint8_t*)NULL,NULL,0);
    }
    else
    {
    
        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t*)gchinesefont_sportscene_target_duration,(uint8_t*)NULL,NULL,0);
        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t*)gchinesefont_sportscene_target_calorie,(uint8_t*)NULL,NULL,0);
    }
    
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_ClimbingModeTargetSetting_Exit(void)
{

    memu_page = 0;

}

void UI_Screen_ClimbingModeTargetSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeTargetSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeTargetSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_ClimbingModeTargetSetting_None(void)
{

    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_off;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;

}



void UI_Screen_ClimbingModeTargetSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(memu_page == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
            
                UI_Screen_ClimbingModeTargetSetting_Exit();
                UI_Screen_ClimbingModeTargetSetting_None();
                UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
                UI_Screen_draw_Screen();
                
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_TargetSetting_ClimbingDistance);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_TargetSetting_Distance);
                UI_Screen_draw_Screen();
            }
            break;
            default:
            break;
        }
    }
    else
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_TargetSetting_Duration);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_TargetSetting_Calorie);
                UI_Screen_draw_Screen();
            }    
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            break;
            default:
            break;
        }
    }


    
}


void UI_Screen_ClimbingModeTargetSetting_tpupslidehandle(void)
{

    if(memu_page == 0)
        memu_page = 1;
    else
        memu_page = 0;
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeTargetSetting_tpdownslidehandle(void)
{

    if(memu_page == 0)
        memu_page = 1;
    else
        memu_page = 0;
    
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeTargetSetting_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeTargetSetting_tprightslidehandle(void)
{

    UI_Screen_ClimbingModeTargetSetting_Exit();
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();

}




void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_Entry(void)
{
    int i = 0;

        
    UI_Common_ScreenCleanListInfo();

    curr_list.total_count = ENUM_CMCLIMBINGDISTANCE_TARGET_MAX;
    curr_list.total_list_page_count = (ENUM_CMCLIMBINGDISTANCE_TARGET_MAX+2)/3;

    for(i = 0;i<ENUM_CMCLIMBINGDISTANCE_TARGET_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }

    if(climbingmode_setting_info.target_type == Enum_climbingmode_setting_target_climbingdistance)
    {
        curr_list.icon_list[climbingmode_setting_info.target_index]=(uint8_t *)radiobtn_checked_h;
    }

    curr_list.string_list[ENUM_CMCLIMBINGDISTANCE_TARGET_100M]=(uint8_t *)gchinesefont_sportscene_100m;
    curr_list.string_list[ENUM_CMCLIMBINGDISTANCE_TARGET_200M]=(uint8_t *)gchinesefont_sportscene_200m;
    curr_list.string_list[ENUM_CMCLIMBINGDISTANCE_TARGET_300M]=(uint8_t *)gchinesefont_sportscene_300m;
    curr_list.string_list[ENUM_CMCLIMBINGDISTANCE_TARGET_500M]=(uint8_t *)gchinesefont_sportscene_500m;
    curr_list.string_list[ENUM_CMCLIMBINGDISTANCE_TARGET_800M]=(uint8_t *)gchinesefont_sportscene_800m;
    curr_list.string_list[ENUM_CMCLIMBINGDISTANCE_TARGET_1000M]=(uint8_t *)gchinesefont_sportscene_1000m;
    curr_list.string_list[ENUM_CMCLIMBINGDISTANCE_TARGET_1500M]=(uint8_t *)gchinesefont_sportscene_1500m;
    curr_list.string_list[ENUM_CMCLIMBINGDISTANCE_TARGET_2000M]=(uint8_t *)gchinesefont_sportscene_2000m;
    
    UI_Screen_ClimbingModeClimbingDistanceTargetSetting_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeDistanceTargetSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeClimbingDistanceTargetSetting_tpclickhandle);
    
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeClimbingDistanceTargetSetting_tpupslidehandle,
                                    UI_Screen_ClimbingModeClimbingDistanceTargetSetting_tpdownslidehandle,
                                    UI_Screen_ClimbingModeClimbingDistanceTargetSetting_tpleftslidehandle,
                                    UI_Screen_ClimbingModeClimbingDistanceTargetSetting_tprightslidehandle);


    
    
}

void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_Display(void)
{
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_TargetSetting_ClimbingDistance)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_Exit(void)
{


}

void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_100M(void)
{

    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_climbingdistance;
    climbingmode_setting_info.target_climbingdistance = 100;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;
    climbingmode_setting_info.target_index = ENUM_CMCLIMBINGDISTANCE_TARGET_100M;
    
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_200M(void)
{

    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_climbingdistance;
    climbingmode_setting_info.target_climbingdistance = 200;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMCLIMBINGDISTANCE_TARGET_200M;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_300M(void)
{

    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_climbingdistance;
    climbingmode_setting_info.target_climbingdistance = 300;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMCLIMBINGDISTANCE_TARGET_300M;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_500M(void)
{

    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_climbingdistance;
    climbingmode_setting_info.target_climbingdistance = 500;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMCLIMBINGDISTANCE_TARGET_500M;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_800M(void)
{

    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_climbingdistance;
    climbingmode_setting_info.target_climbingdistance = 800;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMCLIMBINGDISTANCE_TARGET_800M;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_1000M(void)
{

    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_climbingdistance;
    climbingmode_setting_info.target_climbingdistance = 1000;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMCLIMBINGDISTANCE_TARGET_1000M;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_1500M(void)
{

    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_climbingdistance;
    climbingmode_setting_info.target_climbingdistance = 1500;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMCLIMBINGDISTANCE_TARGET_1500M;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}


void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_2000M(void)
{

    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_climbingdistance;
    climbingmode_setting_info.target_climbingdistance = 2000;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMCLIMBINGDISTANCE_TARGET_2000M;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}


void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);



    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_ClimbingModeClimbingDistanceTargetSetting_100M();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_ClimbingModeClimbingDistanceTargetSetting_200M();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_ClimbingModeClimbingDistanceTargetSetting_300M();
            }
            break;
            default:
            break;
        }
    }
    else if(curr_list.curr_list_page == 1)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_ClimbingModeClimbingDistanceTargetSetting_500M();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                UI_Screen_ClimbingModeClimbingDistanceTargetSetting_800M();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
            
                UI_Screen_ClimbingModeClimbingDistanceTargetSetting_1000M();
            }
            break;
            default:
            break;
        }
    }
    else if(curr_list.curr_list_page == 2)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_ClimbingModeClimbingDistanceTargetSetting_1500M();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_ClimbingModeClimbingDistanceTargetSetting_2000M();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            break;
            default:
            break;
        }
    }

    
}


void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_ClimbingModeClimbingDistanceTargetSetting_Display();
    UI_Screen_Redraw_Screen();
}

void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_ClimbingModeClimbingDistanceTargetSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeClimbingDistanceTargetSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_TargetSetting);
    UI_Screen_draw_Screen();

}





void UI_Screen_ClimbingModeDistanceTargetSetting_Entry(void)
{
    int i = 0;

        
    UI_Common_ScreenCleanListInfo();

    curr_list.total_count = ENUM_CMDISTANCE_TARGET_MAX;
    curr_list.total_list_page_count = (ENUM_CMDISTANCE_TARGET_MAX+2)/3;

    for(i = 0;i<ENUM_CMDISTANCE_TARGET_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    if(climbingmode_setting_info.target_type == Enum_climbingmode_setting_target_distance)
    {
        curr_list.icon_list[climbingmode_setting_info.target_index]=(uint8_t *)radiobtn_checked_h;
    }

    curr_list.string_list[ENUM_CMDISTANCE_TARGET_3KM]=(uint8_t *)gchinesefont_sportscene_target_distance_3km;
    curr_list.string_list[ENUM_CMDISTANCE_TARGET_5KM]=(uint8_t *)gchinesefont_sportscene_target_distance_5km;
    curr_list.string_list[ENUM_CMDISTANCE_TARGET_10KM]=(uint8_t *)gchinesefont_sportscene_target_distance_10km;
    curr_list.string_list[ENUM_CMDISTANCE_TARGET_15KM]=(uint8_t *)gchinesefont_sportscene_target_distance_15km;
    curr_list.string_list[ENUM_CMDISTANCE_TARGET_20KM]=(uint8_t *)gchinesefont_sportscene_target_distance_20km;
    curr_list.string_list[ENUM_CMDISTANCE_TARGET_50KM]=(uint8_t *)gchinesefont_sportscene_target_distance_50km;
    curr_list.string_list[ENUM_CMDISTANCE_TARGET_80KM]=(uint8_t *)gchinesefont_sportscene_target_distance_80km;
    curr_list.string_list[ENUM_CMDISTANCE_TARGET_100KM]=(uint8_t *)gchinesefont_sportscene_target_distance_100km;
    
    UI_Screen_ClimbingModeDistanceTargetSetting_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeDistanceTargetSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeDistanceTargetSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeDistanceTargetSetting_tpupslidehandle,
                                    UI_Screen_ClimbingModeDistanceTargetSetting_tpdownslidehandle,
                                    UI_Screen_ClimbingModeDistanceTargetSetting_tpleftslidehandle,
                                    UI_Screen_ClimbingModeDistanceTargetSetting_tprightslidehandle);


    
    
}

void UI_Screen_ClimbingModeDistanceTargetSetting_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_TargetSetting_Distance)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    
    UI_Common_ShowIconList(temp_ram);
    
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_ClimbingModeDistanceTargetSetting_Exit(void)
{


}

void UI_Screen_ClimbingModeDistanceTargetSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeDistanceTargetSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeDistanceTargetSetting_holdlongkeyhandle(void)
{
}


void UI_Screen_ClimbingModeDistanceTargetSetting_3KM(void)
{

    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_distance;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 3000;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;


    climbingmode_setting_info.target_index = ENUM_CMDISTANCE_TARGET_3KM;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeDistanceTargetSetting_5KM(void)
{

    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_distance;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 5000;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMDISTANCE_TARGET_5KM;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeDistanceTargetSetting_10KM(void)
{
    
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_distance;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 10000;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMDISTANCE_TARGET_10KM;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeDistanceTargetSetting_15KM(void)
{
    
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_distance;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 15000;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMDISTANCE_TARGET_15KM;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeDistanceTargetSetting_20KM(void)
{
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_distance;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 15000;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMDISTANCE_TARGET_20KM;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}


void UI_Screen_ClimbingModeDistanceTargetSetting_50KM(void)
{
    
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_distance;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 50000;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMDISTANCE_TARGET_50KM;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeDistanceTargetSetting_80KM(void)
{
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_distance;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 80000;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMDISTANCE_TARGET_80KM;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeDistanceTargetSetting_100KM(void)
{
    
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_distance;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 100000;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMDISTANCE_TARGET_100KM;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}


void UI_Screen_ClimbingModeDistanceTargetSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_ClimbingModeDistanceTargetSetting_3KM();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_ClimbingModeDistanceTargetSetting_5KM();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_ClimbingModeDistanceTargetSetting_10KM();
            }
            break;
            default:
            break;
        }
    }
    else if(curr_list.curr_list_page == 1)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_ClimbingModeDistanceTargetSetting_15KM();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                UI_Screen_ClimbingModeDistanceTargetSetting_20KM();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
            
                UI_Screen_ClimbingModeDistanceTargetSetting_50KM();
            }
            break;
            default:
            break;
        }
    }
    else if(curr_list.curr_list_page == 2)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
            
                UI_Screen_ClimbingModeDistanceTargetSetting_80KM();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {

                UI_Screen_ClimbingModeDistanceTargetSetting_100KM();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            break;
            default:
            break;
        }
    }

    


    
}


void UI_Screen_ClimbingModeDistanceTargetSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_ClimbingModeDistanceTargetSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_ClimbingModeDistanceTargetSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_ClimbingModeDistanceTargetSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_ClimbingModeDistanceTargetSetting_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeDistanceTargetSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_TargetSetting);
    UI_Screen_draw_Screen();

}





void UI_Screen_ClimbingModeDurationTargetSetting_Entry(void)
{

    int i = 0;
    
    UI_Common_ScreenCleanListInfo();

    curr_list.total_count = ENUM_CMDURATION_TARGET_MAX;
    curr_list.total_list_page_count = (ENUM_CMDURATION_TARGET_MAX+2)/3;

    for(i = 0;i<ENUM_CMDURATION_TARGET_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }

    
    if(climbingmode_setting_info.target_type == Enum_climbingmode_setting_target_duration)
    {
        curr_list.icon_list[climbingmode_setting_info.target_index]=(uint8_t *)radiobtn_checked_h;
    }

    curr_list.string_list[ENUM_CMDURATION_TARGET_20MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_20min;
    curr_list.string_list[ENUM_CMDURATION_TARGET_30MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_30min;
    curr_list.string_list[ENUM_CMDURATION_TARGET_60MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_60min;
    curr_list.string_list[ENUM_CMDURATION_TARGET_90MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_90min;
    curr_list.string_list[ENUM_CMDURATION_TARGET_120MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_120min;
    curr_list.string_list[ENUM_CMDURATION_TARGET_180MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_180min;
    curr_list.string_list[ENUM_CMDURATION_TARGET_240MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_240min;

    UI_Screen_ClimbingModeDurationTargetSetting_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeDurationTargetSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeDurationTargetSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeDurationTargetSetting_tpupslidehandle,
                                    UI_Screen_ClimbingModeDurationTargetSetting_tpdownslidehandle,
                                    UI_Screen_ClimbingModeDurationTargetSetting_tpleftslidehandle,
                                    UI_Screen_ClimbingModeDurationTargetSetting_tprightslidehandle);
    
}

void UI_Screen_ClimbingModeDurationTargetSetting_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_TargetSetting_Duration)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_ClimbingModeDurationTargetSetting_Exit(void)
{


}

void UI_Screen_ClimbingModeDurationTargetSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeDurationTargetSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeDurationTargetSetting_holdlongkeyhandle(void)
{
}


void UI_Screen_ClimbingModeDurationTargetSetting_20MIN(void)
{
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_duration;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 20*60;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMDURATION_TARGET_20MIN;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeDurationTargetSetting_30MIN(void)
{
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_duration;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 30*60;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMDURATION_TARGET_30MIN;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_ClimbingModeDurationTargetSetting_60MIN(void)
{
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_duration;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 60*60;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMDURATION_TARGET_60MIN;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_ClimbingModeDurationTargetSetting_90MIN(void)
{
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_duration;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 90*60;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMDURATION_TARGET_90MIN;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_ClimbingModeDurationTargetSetting_120MIN(void)
{
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_duration;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 120*60;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMDURATION_TARGET_120MIN;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_ClimbingModeDurationTargetSetting_180MIN(void)
{
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_duration;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 180*60;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMDURATION_TARGET_180MIN;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_ClimbingModeDurationTargetSetting_240MIN(void)
{
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_duration;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 240*60;
    climbingmode_setting_info.target_calorie = 0;

    climbingmode_setting_info.target_index = ENUM_CMDURATION_TARGET_240MIN;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_ClimbingModeDurationTargetSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            UI_Screen_ClimbingModeDurationTargetSetting_20MIN();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Screen_ClimbingModeDurationTargetSetting_30MIN();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
            UI_Screen_ClimbingModeDurationTargetSetting_60MIN();
        }
        break;
        default:
        break;
        }
    }
    else if(curr_list.curr_list_page == 1)
    {
        switch(curr_range)
        {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            UI_Screen_ClimbingModeDurationTargetSetting_90MIN();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Screen_ClimbingModeDurationTargetSetting_120MIN();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
            UI_Screen_ClimbingModeDurationTargetSetting_180MIN();
        }
        break;
        default:
        break;
        }
    }
    else if(curr_list.curr_list_page == 2)
    {
        switch(curr_range)
        {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            UI_Screen_ClimbingModeDurationTargetSetting_240MIN();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:

        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:

        break;
        default:
        break;
        }
    }
    
}



void UI_Screen_ClimbingModeDurationTargetSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_ClimbingModeDurationTargetSetting_Display();
    UI_Screen_Redraw_Screen();

}


void UI_Screen_ClimbingModeDurationTargetSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_ClimbingModeDurationTargetSetting_Display();
    UI_Screen_Redraw_Screen();

}


void UI_Screen_ClimbingModeDurationTargetSetting_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeDurationTargetSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_TargetSetting);
    UI_Screen_draw_Screen();

}



    
void UI_Screen_ClimbingModeCalorieTargetSetting_Entry(void)
{

    int i = 0;

    UI_Common_ScreenCleanListInfo();


    curr_list.total_count = ENUM_CMCALORIE_TARGET_MAX;
    curr_list.total_list_page_count = (ENUM_CMCALORIE_TARGET_MAX+2)/3;

    for(i = 0;i<ENUM_CMCALORIE_TARGET_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    if(climbingmode_setting_info.target_type == Enum_climbingmode_setting_target_calorie)
    {
        curr_list.icon_list[climbingmode_setting_info.target_index]=(uint8_t *)radiobtn_checked_h;
    }

    curr_list.string_list[ENUM_CMCALORIE_TARGET_100KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_100kcal;
    curr_list.string_list[ENUM_CMCALORIE_TARGET_200KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_200kcal;
    curr_list.string_list[ENUM_CMCALORIE_TARGET_300KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_300kcal;
    curr_list.string_list[ENUM_CMCALORIE_TARGET_500KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_500kcal;
    curr_list.string_list[ENUM_CMCALORIE_TARGET_800KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_800kcal;
    curr_list.string_list[ENUM_CMCALORIE_TARGET_1000KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_1000kcal;

    UI_Screen_ClimbingModeCalorieTargetSetting_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeCalorieTargetSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeCalorieTargetSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeCalorieTargetSetting_tpupslidehandle,
                                    UI_Screen_ClimbingModeCalorieTargetSetting_tpdownslidehandle,
                                    UI_Screen_ClimbingModeCalorieTargetSetting_tpleftslidehandle,
                                    UI_Screen_ClimbingModeCalorieTargetSetting_tprightslidehandle);
    
}

void UI_Screen_ClimbingModeCalorieTargetSetting_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_TargetSetting_Calorie)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_ClimbingModeCalorieTargetSetting_Exit(void)
{
}

void UI_Screen_ClimbingModeCalorieTargetSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeCalorieTargetSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeCalorieTargetSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_ClimbingModeCalorieTargetSetting_100KCAL(void)
{
    
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_calorie;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 100;

    climbingmode_setting_info.target_index = ENUM_CMCALORIE_TARGET_100KCAL;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeCalorieTargetSetting_200KCAL(void)
{
    
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_calorie;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 200;

    climbingmode_setting_info.target_index = ENUM_CMCALORIE_TARGET_200KCAL;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeCalorieTargetSetting_300KCAL(void)
{
    
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_calorie;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 300;

    climbingmode_setting_info.target_index = ENUM_CMCALORIE_TARGET_300KCAL;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeCalorieTargetSetting_500KCAL(void)
{
    
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_calorie;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 500;

    climbingmode_setting_info.target_index = ENUM_CMCALORIE_TARGET_500KCAL;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeCalorieTargetSetting_800KCAL(void)
{
    
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_calorie;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 800;

    climbingmode_setting_info.target_index = ENUM_CMCALORIE_TARGET_800KCAL;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeCalorieTargetSetting_1000KCAL(void)
{
    
    climbingmode_setting_info.target_type = Enum_climbingmode_setting_target_calorie;
    climbingmode_setting_info.target_climbingdistance = 0;
    climbingmode_setting_info.target_distance = 0;
    climbingmode_setting_info.target_duration = 0;
    climbingmode_setting_info.target_calorie = 1000;

    climbingmode_setting_info.target_index = ENUM_CMCALORIE_TARGET_1000KCAL;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();
}


void UI_Screen_ClimbingModeCalorieTargetSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);
    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_ClimbingModeCalorieTargetSetting_100KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_ClimbingModeCalorieTargetSetting_200KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_ClimbingModeCalorieTargetSetting_300KCAL();
            }
            break;
            default:
            break;
        }
    }
    else if(curr_list.curr_list_page == 1)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_ClimbingModeCalorieTargetSetting_500KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_ClimbingModeCalorieTargetSetting_800KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_ClimbingModeCalorieTargetSetting_1000KCAL();
            }
            break;
            default:
            break;
        }
    }

    
}

void UI_Screen_ClimbingModeCalorieTargetSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_ClimbingModeCalorieTargetSetting_Display();
    App_Lcd_TimerStart(10);

}

void UI_Screen_ClimbingModeCalorieTargetSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_ClimbingModeCalorieTargetSetting_Display();
    App_Lcd_TimerStart(10);

}

void UI_Screen_ClimbingModeCalorieTargetSetting_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeCalorieTargetSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_TargetSetting);
    UI_Screen_draw_Screen();

}






//warn
static int warn_page_number = 0;

void UI_Screen_ClimbingModeWarnSetting_Entry(void)
{

    UI_Screen_ClimbingModeWarnSetting_Display();
    
    UI_Common_set_key_handle(UI_Screen_ClimbingModeWarnSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeWarnSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeWarnSetting_tpupslidehandle,
                                    UI_Screen_ClimbingModeWarnSetting_tpdownslidehandle,
                                    UI_Screen_ClimbingModeWarnSetting_tpleftslidehandle,
                                    UI_Screen_ClimbingModeWarnSetting_tprightslidehandle);
    
}



void UI_Screen_ClimbingModeWarnSetting_Display(void)
{

    uint8_t* fontinfo = NULL;
    char* fontinfo_string = NULL;
    int fontinfo_type = 0;

    
    char info[16]={0};
    hrZoneRange_t hr_info;
    Scene_Cnm_HrZoneGet(&hr_info);
    int temp_a,temp_b;

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_WarnSetting)
        return;
    
    UI_Common_Clear_Screen(temp_ram);

    if(warn_page_number ==0)
    {        
        switch(climbingmode_setting_info.warn_distance)
        {
            case 0:
                fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                fontinfo_string = NULL;
                fontinfo_type = 0;
            break;
            case 500:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_distancewarn_500m;
                fontinfo_type = 2;
            break;
            case 1000:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_distancewarn_1km;
                fontinfo_type = 2;
            break;
            case 2000:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_distancewarn_2km;
                fontinfo_type = 2;
            break;
            case 3000:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_distancewarn_3km;
                fontinfo_type = 2;
            break;
            case 5000:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_distancewarn_5km;
                fontinfo_type = 2;
            break;
            default:
            break;
        }

        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_target_distance,(uint8_t *)fontinfo,(uint8_t *)fontinfo_string,fontinfo_type);

        switch(climbingmode_setting_info.warn_duration)
        {
            case 0:
                fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                fontinfo_string = NULL;
                fontinfo_type = 0;
            break;
            case 5*60:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_durationwarn_5min;
                fontinfo_type = 2;
            break;
            case 10*60:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_durationwarn_10min;
                fontinfo_type = 2;
            break;
            case 15*60:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_durationwarn_15min;
                fontinfo_type = 2;
            break;
            case 20*60:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_durationwarn_20min;
                fontinfo_type = 2;
            break;
            case 30*60:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_durationwarn_30min;
                fontinfo_type = 2;
            break;
            case 60*60:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_durationwarn_60min;
                fontinfo_type = 2;
            break;
            case 90*60:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_durationwarn_90min;
                fontinfo_type = 2;
            break;
            case 120*60:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_durationwarn_120min;
                fontinfo_type = 2;
            break;
            default:
            break;
        }

        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_target_duration,(uint8_t *)fontinfo,(uint8_t *)fontinfo_string,fontinfo_type);
        
        switch(climbingmode_setting_info.warn_calorie)
        {
            case 0:
                fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                fontinfo_string = NULL;
                fontinfo_type = 0;
            break;
            case 50:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_caloriewarn_50kcal;
                fontinfo_type = 2;
            break;
            case 100:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_caloriewarn_100kcal;
                fontinfo_type = 2;
            break;
            case 150:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_caloriewarn_150kcal;
                fontinfo_type = 2;
            break;
            case 200:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = climbingmode_caloriewarn_200kcal;
                fontinfo_type = 2;
            break;
            default:
            break;
        }
        UI_Common_List_RarrowDoubleline(temp_ram,0,118,(uint8_t *)gchinesefont_sportscene_target_calorie,(uint8_t *)fontinfo,(uint8_t *)fontinfo_string,fontinfo_type);
    }
    else if(warn_page_number ==1)
    {

        if(climbingmode_setting_info.elevation_lowlimit_switch == 0&&climbingmode_setting_info.elevation_uplimit_switch == 0)
        {
            fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
            UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_elevation,(uint8_t *)fontinfo,NULL,0);
        }
        else if(climbingmode_setting_info.elevation_lowlimit_switch == 0)
        {
        
            sprintf(info,"<%d",climbingmode_setting_info.elevation_uplimit);
            UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_elevation,(uint8_t *)info,NULL,1);
        }
        else if(climbingmode_setting_info.elevation_uplimit_switch == 0)
        {

            sprintf(info,">%d",climbingmode_setting_info.elevation_lowlimit);
            UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_elevation,(uint8_t *)info,NULL,1);
        
        }
        else
        {
            sprintf(info,"%d - %d",climbingmode_setting_info.elevation_lowlimit,climbingmode_setting_info.elevation_uplimit);
            UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_elevation,(uint8_t *)info,NULL,1);
        }


        if(climbingmode_setting_info.heartrate_uplimit == 0&&climbingmode_setting_info.heartrate_lowlimit == 0)
        {
            fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
            UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_warn_heartrate,(uint8_t *)fontinfo,NULL,0);
        }
        else if(climbingmode_setting_info.heartrate_uplimit == 0)
        {
            switch(climbingmode_setting_info.heartrate_lowlimit)
            {
                case 1:
                    sprintf(info,">%d",hr_info.HrZone0);
                break;
                case 2:
                    sprintf(info,">%d",hr_info.HrZone1);
                break;
                case 3:
                    sprintf(info,">%d",hr_info.HrZone2);
                break;
                case 4:
                    sprintf(info,">%d",hr_info.HrZone3);
                break;
                case 5:
                    sprintf(info,">%d",hr_info.HrZone4);
                break;
                default:
                break;
            }
            UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_warn_heartrate,(uint8_t *)info,NULL,1);
        }
        else if(climbingmode_setting_info.heartrate_lowlimit == 0)
        {
            switch(climbingmode_setting_info.heartrate_uplimit)
            {
                case 1:
                    sprintf(info,"<%d",hr_info.HrZone1);
                break;
                case 2:
                    sprintf(info,"<%d",hr_info.HrZone2);
                break;
                case 3:
                    sprintf(info,"<%d",hr_info.HrZone3);
                break;
                case 4:
                    sprintf(info,"<%d",hr_info.HrZone4);
                break;
                case 5:
                    sprintf(info,"<%d",hr_info.HrZone5);
                break;
                default:
                break;
            }
            
            UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_warn_heartrate,(uint8_t *)info,NULL,1);
        
        }
        else
        {
            switch(climbingmode_setting_info.heartrate_lowlimit)
            {
                case 1:
                    temp_a=hr_info.HrZone0;
                break;
                case 2:
                    temp_a=hr_info.HrZone1;
                break;
                case 3:
                    temp_a=hr_info.HrZone2;
                break;
                case 4:
                    temp_a=hr_info.HrZone3;
                break;
                case 5:
                    temp_a=hr_info.HrZone4;
                break;
                default:
                break;
            }

            switch(climbingmode_setting_info.heartrate_uplimit)
            {
                case 1:
                    temp_b=hr_info.HrZone1;
                break;
                case 2:
                    temp_b=hr_info.HrZone2;
                break;
                case 3:
                    temp_b=hr_info.HrZone3;
                break;
                case 4:
                    temp_b=hr_info.HrZone4;
                break;
                case 5:
                    temp_b=hr_info.HrZone5;
                break;
                default:
                break;
            }
            
            sprintf(info,"%d - %d",temp_a,temp_b);
            UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_warn_heartrate,(uint8_t *)info,NULL,1);
            
        
        }
    

    }

    UI_Display_Prepare(temp_ram);
    
}


void UI_Screen_ClimbingModeWarnSetting_Exit(void)
{
    warn_page_number = 0;


}


void UI_Screen_ClimbingModeWarnSetting_shortkeyhandle(void)
{
    UI_Screen_ClimbingModeWarnSetting_Exit();
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeWarnSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeWarnSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_ClimbingModeWarnSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    

    if(warn_page_number == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Distance);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Duration);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Calorie);
                UI_Screen_draw_Screen();
            }
            break;
            default:
            break;
        }
    }
    else
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Elevation);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            break;
            default:
            break;
        }
        
    }


}



void UI_Screen_ClimbingModeWarnSetting_tpupslidehandle(void)
{

    if(warn_page_number == 0)
        warn_page_number = 1;
    else if(warn_page_number == 1)
        warn_page_number = 0;
    
    UI_Screen_draw_Screen();

    
}

void UI_Screen_ClimbingModeWarnSetting_tpdownslidehandle(void)
{

    if(warn_page_number == 0)
        warn_page_number = 1;
    else if(warn_page_number == 1)
        warn_page_number = 0;
    
    UI_Screen_draw_Screen();

    
}



void UI_Screen_ClimbingModeWarnSetting_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeWarnSetting_tprightslidehandle(void)
{
    UI_Screen_ClimbingModeWarnSetting_Exit();
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Setting);
    UI_Screen_draw_Screen();

}




void UI_Screen_ClimbingModeDistanceWarnSetting_Entry(void)
{
    int i = 0;

        
    UI_Common_ScreenCleanListInfo();

    curr_list.total_count = ENUM_CMDISTANCE_WARN_MAX;
    curr_list.total_list_page_count = (ENUM_CMDISTANCE_WARN_MAX+2)/3;

    for(i = 0;i<ENUM_CMDISTANCE_WARN_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    curr_list.icon_list[climbingmode_setting_info.warn_distance_index]=(uint8_t *)radiobtn_checked_h;

    curr_list.string_list[ENUM_CMDISTANCE_WARN_OFF]=(uint8_t *)gchinesefont_sportscene_turnoff;
    curr_list.string_list[ENUM_CMDISTANCE_WARN_500M]=(uint8_t *)gchinesefont_sportscene_warn_distance_500m;
    curr_list.string_list[ENUM_CMDISTANCE_WARN_1KM]=(uint8_t *)gchinesefont_sportscene_warn_distance_1km;
    curr_list.string_list[ENUM_CMDISTANCE_WARN_2KM]=(uint8_t *)gchinesefont_sportscene_warn_distance_2km;
    curr_list.string_list[ENUM_CMDISTANCE_WARN_3KM]=(uint8_t *)gchinesefont_sportscene_warn_distance_3km;
    curr_list.string_list[ENUM_CMDISTANCE_WARN_5KM]=(uint8_t *)gchinesefont_sportscene_warn_distance_5km;
    
    UI_Screen_ClimbingModeDistanceWarnSetting_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeDistanceWarnSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeDistanceWarnSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeDistanceWarnSetting_tpupslidehandle,
                                    UI_Screen_ClimbingModeDistanceWarnSetting_tpdownslidehandle,
                                    UI_Screen_ClimbingModeDistanceWarnSetting_tpleftslidehandle,
                                    UI_Screen_ClimbingModeDistanceWarnSetting_tprightslidehandle);


    
    
}

void UI_Screen_ClimbingModeDistanceWarnSetting_Display(void)
{
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_WarnSetting_Distance)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_ClimbingModeDistanceWarnSetting_Exit(void)
{


}

void UI_Screen_ClimbingModeDistanceWarnSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeDistanceWarnSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeDistanceWarnSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_ClimbingModeDistanceWarnSetting_Off(void)
{

    climbingmode_setting_info.warn_distance = 0;
    climbingmode_setting_info.warn_distance_index = ENUM_CMDISTANCE_WARN_OFF;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}


void UI_Screen_ClimbingModeDistanceWarnSetting_500M(void)
{

    climbingmode_setting_info.warn_distance = 500;
    climbingmode_setting_info.warn_distance_index = ENUM_CMDISTANCE_WARN_500M;
    
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeDistanceWarnSetting_1KM(void)
{

    climbingmode_setting_info.warn_distance = 1000;
    climbingmode_setting_info.warn_distance_index = ENUM_CMDISTANCE_WARN_1KM;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeDistanceWarnSetting_2KM(void)
{

    climbingmode_setting_info.warn_distance = 2000;
    climbingmode_setting_info.warn_distance_index = ENUM_CMDISTANCE_WARN_2KM;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeDistanceWarnSetting_3KM(void)
{

    climbingmode_setting_info.warn_distance = 3000;
    climbingmode_setting_info.warn_distance_index = ENUM_CMDISTANCE_WARN_3KM;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeDistanceWarnSetting_5KM(void)
{

    climbingmode_setting_info.warn_distance = 5000;
    climbingmode_setting_info.warn_distance_index = ENUM_CMDISTANCE_WARN_5KM;
    
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeDistanceWarnSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_ClimbingModeDistanceWarnSetting_Off();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_ClimbingModeDistanceWarnSetting_500M();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_ClimbingModeDistanceWarnSetting_1KM();
            }
            break;
            default:
            break;
        }
    }
    else if(curr_list.curr_list_page == 1)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_ClimbingModeDistanceWarnSetting_2KM();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                UI_Screen_ClimbingModeDistanceWarnSetting_3KM();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
            
                UI_Screen_ClimbingModeDistanceWarnSetting_5KM();
            }
            break;
            default:
            break;
        }
    }

    
}


void UI_Screen_ClimbingModeDistanceWarnSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_ClimbingModeDistanceWarnSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_ClimbingModeDistanceWarnSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_ClimbingModeDistanceWarnSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_ClimbingModeDistanceWarnSetting_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeDistanceWarnSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();

}


    


void UI_Screen_ClimbingModeDurationWarnSetting_Entry(void)
{
    int i = 0;

        
    UI_Common_ScreenCleanListInfo();

    curr_list.total_count = ENUM_CMDURATION_WARN_MAX;
    curr_list.total_list_page_count = (ENUM_CMDURATION_WARN_MAX+2)/3;

    for(i = 0;i<ENUM_CMDURATION_WARN_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    curr_list.icon_list[climbingmode_setting_info.warn_duration_index]=(uint8_t *)radiobtn_checked_h;

    curr_list.string_list[ENUM_CMDURATION_WARN_OFF]=(uint8_t *)gchinesefont_sportscene_turnoff;
    curr_list.string_list[ENUM_CMDURATION_WARN_5MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_5min;
    curr_list.string_list[ENUM_CMDURATION_WARN_10MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_10min;
    curr_list.string_list[ENUM_CMDURATION_WARN_15MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_15min;
    curr_list.string_list[ENUM_CMDURATION_WARN_20MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_20min;
    curr_list.string_list[ENUM_CMDURATION_WARN_30MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_30min;
    curr_list.string_list[ENUM_CMDURATION_WARN_60MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_60min;
    curr_list.string_list[ENUM_CMDURATION_WARN_90MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_90min;
    curr_list.string_list[ENUM_CMDURATION_WARN_120MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_120min;
    
    UI_Screen_ClimbingModeDurationWarnSetting_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeDurationWarnSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeDurationWarnSetting_tpclickhandle);
    
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeDurationWarnSetting_tpupslidehandle,
                                    UI_Screen_ClimbingModeDurationWarnSetting_tpdownslidehandle,
                                    UI_Screen_ClimbingModeDurationWarnSetting_tpleftslidehandle,
                                    UI_Screen_ClimbingModeDurationWarnSetting_tprightslidehandle);


    
    
}

void UI_Screen_ClimbingModeDurationWarnSetting_Display(void)
{
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_WarnSetting_Duration)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_ClimbingModeDurationWarnSetting_Exit(void)
{


}

void UI_Screen_ClimbingModeDurationWarnSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeDurationWarnSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeDurationWarnSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_ClimbingModeDurationWarnSetting_Off(void)
{

    climbingmode_setting_info.warn_duration = 0;
    climbingmode_setting_info.warn_duration_index = ENUM_CMDURATION_WARN_OFF;
    
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}


void UI_Screen_ClimbingModeDurationWarnSetting_5MIN(void)
{

    climbingmode_setting_info.warn_duration = 5*60;
    climbingmode_setting_info.warn_duration_index = ENUM_CMDURATION_WARN_5MIN;
    
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_ClimbingModeDurationWarnSetting_10MIN(void)
{

    climbingmode_setting_info.warn_duration = 10*60;
    climbingmode_setting_info.warn_duration_index = ENUM_CMDURATION_WARN_10MIN;
    
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_ClimbingModeDurationWarnSetting_15MIN(void)
{

    climbingmode_setting_info.warn_duration = 15*60;
    climbingmode_setting_info.warn_duration_index = ENUM_CMDURATION_WARN_15MIN;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_ClimbingModeDurationWarnSetting_20MIN(void)
{

    climbingmode_setting_info.warn_duration = 20*60;
    climbingmode_setting_info.warn_duration_index = ENUM_CMDURATION_WARN_20MIN;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}




void UI_Screen_ClimbingModeDurationWarnSetting_30MIN(void)
{

    climbingmode_setting_info.warn_duration = 30*60;
    climbingmode_setting_info.warn_duration_index = ENUM_CMDURATION_WARN_30MIN;

    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_ClimbingModeDurationWarnSetting_60MIN(void)
{

    climbingmode_setting_info.warn_duration = 60*60;
    climbingmode_setting_info.warn_duration_index = ENUM_CMDURATION_WARN_60MIN;
    
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_ClimbingModeDurationWarnSetting_90MIN(void)
{

    climbingmode_setting_info.warn_duration = 90*60;
    climbingmode_setting_info.warn_duration_index = ENUM_CMDURATION_WARN_90MIN;
    
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_ClimbingModeDurationWarnSetting_120MIN(void)
{

    climbingmode_setting_info.warn_duration = 120*60;
    climbingmode_setting_info.warn_duration_index = ENUM_CMDURATION_WARN_120MIN;
    
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}


void UI_Screen_ClimbingModeDurationWarnSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_ClimbingModeDurationWarnSetting_Off();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_ClimbingModeDurationWarnSetting_5MIN();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_ClimbingModeDurationWarnSetting_10MIN();
            }
            break;
            default:
            break;
        }
    }
    else if(curr_list.curr_list_page == 1)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_ClimbingModeDurationWarnSetting_15MIN();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                UI_Screen_ClimbingModeDurationWarnSetting_20MIN();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
            
                UI_Screen_ClimbingModeDurationWarnSetting_30MIN();
            }
            break;
            default:
            break;
        }
    }
    else if(curr_list.curr_list_page == 2)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_ClimbingModeDurationWarnSetting_60MIN();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                UI_Screen_ClimbingModeDurationWarnSetting_90MIN();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
            
                UI_Screen_ClimbingModeDurationWarnSetting_120MIN();
            }
            break;
            default:
            break;
        }
    }

    
}


void UI_Screen_ClimbingModeDurationWarnSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_ClimbingModeDurationWarnSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_ClimbingModeDurationWarnSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_ClimbingModeDurationWarnSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_ClimbingModeDurationWarnSetting_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeDurationWarnSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();

}




    
    
void UI_Screen_ClimbingModeCalorieWarnSetting_Entry(void)
{

    int i = 0;

    UI_Common_ScreenCleanListInfo();


    curr_list.total_count = ENUM_CMCALORIE_WARN_MAX;
    curr_list.total_list_page_count = ENUM_CMCALORIE_WARN_MAX/3+1;

    for(i = 0;i<ENUM_CMCALORIE_WARN_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    curr_list.icon_list[climbingmode_setting_info.warn_calorie_index]=(uint8_t *)radiobtn_checked_h;

    curr_list.string_list[ENUM_CMCALORIE_WARN_OFF]=(uint8_t *)gchinesefont_sportscene_turnoff;
    curr_list.string_list[ENUM_CMCALORIE_WARN_50KCAL]=(uint8_t *)gchinesefont_sportscene_warn_calorie_50kcal;
    curr_list.string_list[ENUM_CMCALORIE_WARN_100KCAL]=(uint8_t *)gchinesefont_sportscene_warn_calorie_100kcal;
    curr_list.string_list[ENUM_CMCALORIE_WARN_150KCAL]=(uint8_t *)gchinesefont_sportscene_warn_calorie_150kcal;
    curr_list.string_list[ENUM_CMCALORIE_WARN_200KCAL]=(uint8_t *)gchinesefont_sportscene_warn_calorie_200kcal;

    UI_Screen_ClimbingModeCalorieWarnSetting_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeCalorieWarnSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeCalorieWarnSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeCalorieWarnSetting_tpupslidehandle,
                                    UI_Screen_ClimbingModeCalorieWarnSetting_tpdownslidehandle,
                                    UI_Screen_ClimbingModeCalorieWarnSetting_tpleftslidehandle,
                                    UI_Screen_ClimbingModeCalorieWarnSetting_tprightslidehandle);
    
}

void UI_Screen_ClimbingModeCalorieWarnSetting_Display(void)
{
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_WarnSetting_Calorie)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_ClimbingModeCalorieWarnSetting_Exit(void)
{
}

void UI_Screen_ClimbingModeCalorieWarnSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeCalorieWarnSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeCalorieWarnSetting_holdlongkeyhandle(void)
{
}


void UI_Screen_ClimbingModeCalorieWarnSetting_Off(void)
{
    
    climbingmode_setting_info.warn_calorie = 0;
    climbingmode_setting_info.warn_calorie_index = ENUM_CMCALORIE_WARN_OFF;
    
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}


void UI_Screen_ClimbingModeCalorieWarnSetting_50KCAL(void)
{
    
    climbingmode_setting_info.warn_calorie = 50;
    climbingmode_setting_info.warn_calorie_index = ENUM_CMCALORIE_WARN_50KCAL;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeCalorieWarnSetting_100KCAL(void)
{
    
    climbingmode_setting_info.warn_calorie = 100;
    climbingmode_setting_info.warn_calorie_index = ENUM_CMCALORIE_WARN_100KCAL;
    
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeCalorieWarnSetting_150KCAL(void)
{
    
    climbingmode_setting_info.warn_calorie = 150;
    climbingmode_setting_info.warn_calorie_index = ENUM_CMCALORIE_WARN_150KCAL;
    
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_ClimbingModeCalorieWarnSetting_200KCAL(void)
{
    
    climbingmode_setting_info.warn_calorie = 200;
    climbingmode_setting_info.warn_calorie_index = ENUM_CMCALORIE_WARN_200KCAL;
    
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();
}


void UI_Screen_ClimbingModeCalorieWarnSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);
    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_ClimbingModeCalorieWarnSetting_Off();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_ClimbingModeCalorieWarnSetting_50KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_ClimbingModeCalorieWarnSetting_100KCAL();
            }
            break;
            default:
            break;
        }
    }
    else if(curr_list.curr_list_page == 1)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_ClimbingModeCalorieWarnSetting_150KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_ClimbingModeCalorieWarnSetting_200KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            
            break;
            default:
            break;
        }
    }

    
}

void UI_Screen_ClimbingModeCalorieWarnSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_ClimbingModeCalorieWarnSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_ClimbingModeCalorieWarnSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_ClimbingModeCalorieWarnSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_ClimbingModeCalorieWarnSetting_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeCalorieWarnSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();

}







void UI_Screen_ClimbingModeHrWarnSetting_Entry(void)
{

    UI_Screen_ClimbingModeHrWarnSetting_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeHrWarnSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeHrWarnSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeHrWarnSetting_tpupslidehandle,
                                    UI_Screen_ClimbingModeHrWarnSetting_tpdownslidehandle,
                                    UI_Screen_ClimbingModeHrWarnSetting_tpleftslidehandle,
                                    UI_Screen_ClimbingModeHrWarnSetting_tprightslidehandle);
    
}

void UI_Screen_ClimbingModeHrWarnSetting_Display(void)
{

    uint8_t* fontinfo = NULL;
    char info[16]={0};
    hrZoneRange_t hr_info;
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    
    Scene_Cnm_HrZoneGet(&hr_info);

    if(climbingmode_setting_info.heartrate_uplimit == 0)
    {        
        fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_warn_heartrate_upperlimit,fontinfo,NULL,0);
    }
    else
    {
        switch(climbingmode_setting_info.heartrate_uplimit)
        {
            case 1:
                sprintf(info,"%d",hr_info.HrZone1);
            break;
            case 2:
                sprintf(info,"%d",hr_info.HrZone2);
            break;
            case 3:
                sprintf(info,"%d",hr_info.HrZone3);
            break;
            case 4:
                sprintf(info,"%d",hr_info.HrZone4);
            break;
            case 5:
                sprintf(info,"%d",hr_info.HrZone5);
            break;
            default:
            break;
        }

        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_warn_heartrate_upperlimit,(uint8_t *)info,NULL,1);
    }



    
    if(climbingmode_setting_info.heartrate_lowlimit == 0)
    {        
        fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_warn_heartrate_lowerlimit,(uint8_t *)fontinfo,NULL,0);
    }
    else
    {
        switch(climbingmode_setting_info.heartrate_lowlimit)
        {
            case 1:
                sprintf(info,"%d",hr_info.HrZone0);
            break;
            case 2:
                sprintf(info,"%d",hr_info.HrZone1);
            break;
            case 3:
                sprintf(info,"%d",hr_info.HrZone2);
            break;
            case 4:
                sprintf(info,"%d",hr_info.HrZone3);
            break;
            case 5:
                sprintf(info,"%d",hr_info.HrZone4);
            break;
            default:
            break;
        }

        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_warn_heartrate_lowerlimit,(uint8_t *)info,NULL,1);
        
    }
    UI_Display_Prepare(temp_ram);

}



void UI_Screen_ClimbingModeHrWarnSetting_Exit(void)
{

}

void UI_Screen_ClimbingModeHrWarnSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeHrWarnSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeHrWarnSetting_holdlongkeyhandle(void)
{
}


void UI_Screen_ClimbingModeHrWarnSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate_Upperlimit);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate_Lowerlimit);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        
        break;
        default:
        break;
    }


    
}


void UI_Screen_ClimbingModeHrWarnSetting_tpupslidehandle(void)
{

}

void UI_Screen_ClimbingModeHrWarnSetting_tpdownslidehandle(void)
{
}

void UI_Screen_ClimbingModeHrWarnSetting_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeHrWarnSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();

}

//心率上限/下限设置列表
typedef enum
{
	ENUM_CMHRWARN_OFF = 0,
	ENUM_CMHRWARN_RANGE1,
	ENUM_CMHRWARN_RANGE2,
	ENUM_CMHRWARN_RANGE3,
	ENUM_CMHRWARN_RANGE4,
	ENUM_CMHRWARN_RANGE5,
	ENUM_CMHRWARN_MAX,
}app_climbingmodehrwarn_enum;



void UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Entry(void)
{

    int i = 0;
    //char content[10][16]= {0};
    hrZoneRange_t hr_info;
    
    Scene_Cnm_HrZoneGet(&hr_info);
    
    UI_Common_ScreenCleanListInfo();

    curr_list.curr_list_page = 0;
    curr_list.curr_list_highlight = 0;

    curr_list.total_count = ENUM_CMHRWARN_MAX;
    curr_list.total_list_page_count = (ENUM_CMHRWARN_MAX+2)/3;

    for(i = 0;i<ENUM_CMHRWARN_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    curr_list.icon_list[climbingmode_setting_info.heartrate_uplimit_index]=(uint8_t *)radiobtn_checked_h;

    curr_list.string_list[ENUM_CMHRWARN_OFF]=(uint8_t *)gchinesefont_sportscene_turnoff;
    curr_list.string_list[ENUM_CMHRWARN_RANGE1]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range1;
    curr_list.string_list[ENUM_CMHRWARN_RANGE2]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range2;
    curr_list.string_list[ENUM_CMHRWARN_RANGE3]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range3;
    curr_list.string_list[ENUM_CMHRWARN_RANGE4]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range4;
    curr_list.string_list[ENUM_CMHRWARN_RANGE5]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range5;

    sprintf(curr_list.line2_content[1],"%d-%d",hr_info.HrZone0,hr_info.HrZone1);
    sprintf(curr_list.line2_content[2],"%d-%d",hr_info.HrZone1,hr_info.HrZone2);
    sprintf(curr_list.line2_content[3],"%d-%d",hr_info.HrZone2,hr_info.HrZone3);
    sprintf(curr_list.line2_content[4],"%d-%d",hr_info.HrZone3,hr_info.HrZone4);
    sprintf(curr_list.line2_content[5],"%d-%d",hr_info.HrZone4,hr_info.HrZone5);
    

    UI_Screen_ClimbingModeHrWarnLlimitSetting_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeHrWarnLlimitSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeHrWarnUpperLimitSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeHrWarnLlimitSetting_tpupslidehandle,
                                    UI_Screen_ClimbingModeHrWarnLlimitSetting_tpdownslidehandle,
                                    UI_Screen_ClimbingModeHrWarnLlimitSetting_tpleftslidehandle,
                                    UI_Screen_ClimbingModeHrWarnLlimitSetting_tprightslidehandle);
    
}

void UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Entry(void)
{

    int i = 0;
    //char content[10][16]= {0};
    
    hrZoneRange_t hr_info;
    
    Scene_Cnm_HrZoneGet(&hr_info);

    UI_Common_ScreenCleanListInfo();

    curr_list.curr_list_page = 0;
    curr_list.curr_list_highlight = 0;

    curr_list.total_count = ENUM_CMHRWARN_MAX;
    curr_list.total_list_page_count = (ENUM_CMHRWARN_MAX+2)/3;
    
    for(i = 0;i<ENUM_CMHRWARN_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    curr_list.icon_list[climbingmode_setting_info.heartrate_lowlimit_index]=(uint8_t *)radiobtn_checked_h;

    curr_list.string_list[ENUM_CMHRWARN_OFF]=(uint8_t *)gchinesefont_sportscene_turnoff;
    curr_list.string_list[ENUM_CMHRWARN_RANGE1]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range1;
    curr_list.string_list[ENUM_CMHRWARN_RANGE2]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range2;
    curr_list.string_list[ENUM_CMHRWARN_RANGE3]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range3;
    curr_list.string_list[ENUM_CMHRWARN_RANGE4]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range4;
    curr_list.string_list[ENUM_CMHRWARN_RANGE5]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range5;
    
    
    sprintf(curr_list.line2_content[1],"%d-%d",hr_info.HrZone0,hr_info.HrZone1);
    sprintf(curr_list.line2_content[2],"%d-%d",hr_info.HrZone1,hr_info.HrZone2);
    sprintf(curr_list.line2_content[3],"%d-%d",hr_info.HrZone2,hr_info.HrZone3);
    sprintf(curr_list.line2_content[4],"%d-%d",hr_info.HrZone3,hr_info.HrZone4);
    sprintf(curr_list.line2_content[5],"%d-%d",hr_info.HrZone4,hr_info.HrZone5);

        
    UI_Screen_ClimbingModeHrWarnLlimitSetting_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeHrWarnLlimitSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeHrWarnLowerLimitSetting_tpclickhandle);

    
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeHrWarnLlimitSetting_tpupslidehandle,
                                    UI_Screen_ClimbingModeHrWarnLlimitSetting_tpdownslidehandle,
                                    UI_Screen_ClimbingModeHrWarnLlimitSetting_tpleftslidehandle,
                                    UI_Screen_ClimbingModeHrWarnLlimitSetting_tprightslidehandle);
    
}

void UI_Screen_ClimbingModeHrWarnLlimitSetting_Display(void)
{
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if((UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate_Lowerlimit)&&(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate_Upperlimit))
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
}

void UI_Screen_ClimbingModeHrWarnLlimitSetting_Exit(void)
{
}

void UI_Screen_ClimbingModeHrWarnLlimitSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();

}


void UI_Screen_ClimbingModeHrWarnLlimitSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeHrWarnLlimitSetting_holdlongkeyhandle(void)
{
}


void UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Off(void)
{
    
    climbingmode_setting_info.heartrate_uplimit = 0;
    climbingmode_setting_info.heartrate_uplimit_index = ENUM_CMHRWARN_OFF;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate);
    UI_Screen_draw_Screen();
}


void UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Range1(void)
{

    climbingmode_setting_info.heartrate_uplimit = 1;
    climbingmode_setting_info.heartrate_uplimit_index = ENUM_CMHRWARN_RANGE1;
    
    if(climbingmode_setting_info.heartrate_lowlimit!=0&&climbingmode_setting_info.heartrate_lowlimit>climbingmode_setting_info.heartrate_uplimit)
    {

        climbingmode_setting_info.heartrate_uplimit = 0;
        climbingmode_setting_info.heartrate_uplimit_index = ENUM_CMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate);

        UI_Screen_draw_Screen();
    }
}

void UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Range2(void)
{

    climbingmode_setting_info.heartrate_uplimit = 2;
    climbingmode_setting_info.heartrate_uplimit_index = ENUM_CMHRWARN_RANGE2;

    if(climbingmode_setting_info.heartrate_lowlimit!=0&&climbingmode_setting_info.heartrate_lowlimit>climbingmode_setting_info.heartrate_uplimit)
    {

        climbingmode_setting_info.heartrate_uplimit = 0;
        climbingmode_setting_info.heartrate_uplimit_index = ENUM_CMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {

        UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }

}

void UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Range3(void)
{

    climbingmode_setting_info.heartrate_uplimit = 3;
    climbingmode_setting_info.heartrate_uplimit_index = ENUM_CMHRWARN_RANGE3;

    if(climbingmode_setting_info.heartrate_lowlimit!=0&&climbingmode_setting_info.heartrate_lowlimit>climbingmode_setting_info.heartrate_uplimit)
    {
        climbingmode_setting_info.heartrate_uplimit = 0;
        climbingmode_setting_info.heartrate_uplimit_index = ENUM_CMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
}

void UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Range4(void)
{

    climbingmode_setting_info.heartrate_uplimit = 4;
    climbingmode_setting_info.heartrate_uplimit_index = ENUM_CMHRWARN_RANGE4;

    if(climbingmode_setting_info.heartrate_lowlimit!=0&&climbingmode_setting_info.heartrate_lowlimit>climbingmode_setting_info.heartrate_uplimit)
    {
        climbingmode_setting_info.heartrate_uplimit = 0;
        climbingmode_setting_info.heartrate_uplimit_index = ENUM_CMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
}

void UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Range5(void)
{

    climbingmode_setting_info.heartrate_uplimit = 5;
    climbingmode_setting_info.heartrate_uplimit_index = ENUM_CMHRWARN_RANGE5;
    
    if(climbingmode_setting_info.heartrate_lowlimit!=0&&climbingmode_setting_info.heartrate_lowlimit>climbingmode_setting_info.heartrate_uplimit)
    {
        climbingmode_setting_info.heartrate_uplimit = 0;
        climbingmode_setting_info.heartrate_uplimit_index = ENUM_CMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
}


void UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Off(void)
{
    
    climbingmode_setting_info.heartrate_lowlimit = 0;
    climbingmode_setting_info.heartrate_lowlimit_index = ENUM_CMHRWARN_OFF;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate);
    UI_Screen_draw_Screen();
}



void UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Range1(void)
{



    climbingmode_setting_info.heartrate_lowlimit = 1;
    climbingmode_setting_info.heartrate_lowlimit_index = ENUM_CMHRWARN_RANGE1;

    if(climbingmode_setting_info.heartrate_uplimit!=0&&climbingmode_setting_info.heartrate_lowlimit>climbingmode_setting_info.heartrate_uplimit)
    {

        climbingmode_setting_info.heartrate_lowlimit = 0;
        climbingmode_setting_info.heartrate_lowlimit_index = ENUM_CMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
}

void UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Range2(void)
{

    climbingmode_setting_info.heartrate_lowlimit = 2;
    climbingmode_setting_info.heartrate_lowlimit_index = ENUM_CMHRWARN_RANGE2;
    

    if(climbingmode_setting_info.heartrate_uplimit!=0&&climbingmode_setting_info.heartrate_lowlimit>climbingmode_setting_info.heartrate_uplimit)
    {
        climbingmode_setting_info.heartrate_lowlimit = 0;
        climbingmode_setting_info.heartrate_lowlimit_index = ENUM_CMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
}

void UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Range3(void)
{

    climbingmode_setting_info.heartrate_lowlimit = 3;
    climbingmode_setting_info.heartrate_lowlimit_index = ENUM_CMHRWARN_RANGE3;
    
    if(climbingmode_setting_info.heartrate_uplimit!=0&&climbingmode_setting_info.heartrate_lowlimit>climbingmode_setting_info.heartrate_uplimit)
    {
    
        climbingmode_setting_info.heartrate_lowlimit = 0;
        climbingmode_setting_info.heartrate_lowlimit_index = ENUM_CMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {

        UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
}

void UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Range4(void)
{

    climbingmode_setting_info.heartrate_lowlimit = 4;
    climbingmode_setting_info.heartrate_lowlimit_index = ENUM_CMHRWARN_RANGE4;

    if(climbingmode_setting_info.heartrate_uplimit!=0&&climbingmode_setting_info.heartrate_lowlimit>climbingmode_setting_info.heartrate_uplimit)
    {
        climbingmode_setting_info.heartrate_lowlimit = 0;
        climbingmode_setting_info.heartrate_lowlimit_index = ENUM_CMHRWARN_OFF;
    
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {

        UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
}

void UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Range5(void)
{
    climbingmode_setting_info.heartrate_lowlimit = 5;
    climbingmode_setting_info.heartrate_lowlimit_index = ENUM_CMHRWARN_RANGE5;

    if(climbingmode_setting_info.heartrate_uplimit!=0&&climbingmode_setting_info.heartrate_lowlimit>climbingmode_setting_info.heartrate_uplimit)
    {

        climbingmode_setting_info.heartrate_lowlimit = 0;
        climbingmode_setting_info.heartrate_lowlimit_index = ENUM_CMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
}

void UI_Screen_ClimbingModeHrWarnUpperLimitSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Off();
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Range1();
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Range2();
            break;
            default:
            break;
        }
    }
    else
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Range3();
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Range4();
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            UI_Screen_ClimbingModeHrWarnUpperLimitSetting_Range5();
            break;
            default:
            break;
        }
    }


    
}



void UI_Screen_ClimbingModeHrWarnLowerLimitSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Off();
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Range1();
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Range2();
            break;
            default:
            break;
        }
    }
    else
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Range3();
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Range4();
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            UI_Screen_ClimbingModeHrWarnLowerLimitSetting_Range5();
            break;
            default:
            break;
        }
    }


    
}


void UI_Screen_ClimbingModeHrWarnLlimitSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_ClimbingModeHrWarnLlimitSetting_Display();
    App_Lcd_TimerStart(10);

}

void UI_Screen_ClimbingModeHrWarnLlimitSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_ClimbingModeHrWarnLlimitSetting_Display();
    App_Lcd_TimerStart(10);

}

void UI_Screen_ClimbingModeHrWarnLlimitSetting_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeHrWarnLlimitSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();

}




void UI_Screen_ClimbingModeElevationWarnSetting_Entry(void)
{

    UI_Screen_ClimbingModeElevationWarnSetting_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeElevationWarnSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeElevationWarnSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeElevationWarnSetting_tpupslidehandle,
                                    UI_Screen_ClimbingModeElevationWarnSetting_tpdownslidehandle,
                                    UI_Screen_ClimbingModeElevationWarnSetting_tpleftslidehandle,
                                    UI_Screen_ClimbingModeElevationWarnSetting_tprightslidehandle);
    
}

void UI_Screen_ClimbingModeElevationWarnSetting_Display(void)
{

    uint8_t* fontinfo = NULL;
    char info[16]={0};
    hrZoneRange_t hr_info;
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_WarnSetting_Elevation)
        return;
    
    UI_Common_Clear_Screen(temp_ram);

    
    Scene_Cnm_HrZoneGet(&hr_info);

    if(climbingmode_setting_info.elevation_uplimit_switch == 0)
    {        
        fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_warn_heartrate_upperlimit,(uint8_t *)fontinfo,NULL,0);
    }
    else
    {
    
        sprintf(info,"%d",climbingmode_setting_info.elevation_uplimit);
        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_warn_heartrate_upperlimit,(uint8_t *)info,NULL,1);
    }

    
    if(climbingmode_setting_info.elevation_lowlimit_switch == 0)
    {        
        fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_warn_heartrate_lowerlimit,(uint8_t *)fontinfo,NULL,0);
    }
    else
    {
        sprintf(info,"%d",climbingmode_setting_info.elevation_lowlimit);
        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_warn_heartrate_lowerlimit,(uint8_t *)info,NULL,1);
    }

    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_ClimbingModeElevationWarnSetting_Exit(void)
{

}

void UI_Screen_ClimbingModeElevationWarnSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeElevationWarnSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeElevationWarnSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_ClimbingModeElevationWarnSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Elevation_Upperlimit);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Elevation_Lowerlimit);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        
        break;
        default:
        break;
    }


    
}


void UI_Screen_ClimbingModeElevationWarnSetting_tpupslidehandle(void)
{

}

void UI_Screen_ClimbingModeElevationWarnSetting_tpdownslidehandle(void)
{
}

void UI_Screen_ClimbingModeElevationWarnSetting_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeElevationWarnSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting);
    UI_Screen_draw_Screen();

}



typedef struct 
{
    int temp_switch;
    int temp_curr_page;
    int temp_value1;
    int temp_value1_step;
    int temp_value1_min;
    int temp_value1_max;
    int temp_value2;
    int temp_value2_step;
    int temp_value2_min;
    int temp_value2_max;
    bool isloop;
}app_sportmode_elevationwarn_s;

app_sportmode_elevationwarn_s sportmode_elevationwarn_info = {0x00};

void UI_Screen_ClimbingModeElevationUpperLlimitSetting_Init(void)
{

    sportmode_elevationwarn_info.temp_switch = climbingmode_setting_info.elevation_uplimit_switch;
    sportmode_elevationwarn_info.temp_curr_page = 0;
    
    sportmode_elevationwarn_info.temp_value1  = climbingmode_setting_info.elevation_uplimit/100;
    sportmode_elevationwarn_info.temp_value1_step = 1;
    sportmode_elevationwarn_info.temp_value1_min  = 0;
    sportmode_elevationwarn_info.temp_value1_max = 99;
    
    sportmode_elevationwarn_info.temp_value2  = climbingmode_setting_info.elevation_uplimit%100;
    sportmode_elevationwarn_info.temp_value2_step = 1;
    sportmode_elevationwarn_info.temp_value2_min  = 0;
    sportmode_elevationwarn_info.temp_value2_max = 99;
    
    sportmode_elevationwarn_info.isloop  =TRUE;
    
}

void UI_Screen_ClimbingModeElevationUpperLlimitSetting_Save(void)
{


    climbingmode_setting_info.elevation_uplimit_switch = sportmode_elevationwarn_info.temp_switch;
    climbingmode_setting_info.elevation_uplimit = sportmode_elevationwarn_info.temp_value1*100 +sportmode_elevationwarn_info.temp_value2;

}

void UI_Screen_ClimbingModeElevationUpperLlimitSetting_Entry(void)
{   

    UI_Screen_ClimbingModeElevationUpperLlimitSetting_Init();

    UI_Screen_ClimbingModeElevationLlimitSetting_Display();
    
    UI_Common_set_key_handle(UI_Screen_ClimbingModeElevationLlimitSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeElevationUpperLlimitSetting_tpclickhandle);
    
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeElevationLlimitSetting_tpupslidehandle,
                                    UI_Screen_ClimbingModeElevationLlimitSetting_tpdownslidehandle,
                                    UI_Screen_ClimbingModeElevationLlimitSetting_tpleftslidehandle,
                                    UI_Screen_ClimbingModeElevationLlimitSetting_tprightslidehandle);
    
}

void UI_Screen_ClimbingModeElevationLowerLlimitSetting_Init(void)
{

    sportmode_elevationwarn_info.temp_switch = climbingmode_setting_info.elevation_lowlimit_switch;
    sportmode_elevationwarn_info.temp_curr_page = 0;
    
    sportmode_elevationwarn_info.temp_value1  = climbingmode_setting_info.elevation_lowlimit/100;
    sportmode_elevationwarn_info.temp_value1_step = 1;
    sportmode_elevationwarn_info.temp_value1_min  = 0;
    sportmode_elevationwarn_info.temp_value1_max = 99;
    
    sportmode_elevationwarn_info.temp_value2  = climbingmode_setting_info.elevation_lowlimit%100;
    sportmode_elevationwarn_info.temp_value2_step = 1;
    sportmode_elevationwarn_info.temp_value2_min  = 0;
    sportmode_elevationwarn_info.temp_value2_max = 99;
    
    sportmode_elevationwarn_info.isloop  =TRUE;

}

void UI_Screen_ClimbingModeElevationLowerLlimitSetting_Save(void)
{


    climbingmode_setting_info.elevation_lowlimit_switch = sportmode_elevationwarn_info.temp_switch;
    climbingmode_setting_info.elevation_lowlimit = sportmode_elevationwarn_info.temp_value1*100 +sportmode_elevationwarn_info.temp_value2;

}



void UI_Screen_ClimbingModeElevationLowerLlimitSetting_Entry(void)
{


    UI_Screen_ClimbingModeElevationLowerLlimitSetting_Init();

    UI_Screen_ClimbingModeElevationLlimitSetting_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeElevationLlimitSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeElevationLowerLlimitSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeElevationLlimitSetting_tpupslidehandle,
                                    UI_Screen_ClimbingModeElevationLlimitSetting_tpdownslidehandle,
                                    UI_Screen_ClimbingModeElevationLlimitSetting_tpleftslidehandle,
                                    UI_Screen_ClimbingModeElevationLlimitSetting_tprightslidehandle);
    
}

void UI_Screen_ClimbingModeElevationLlimitSetting_Display(void)
{

    char content[8];
    int len;

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if((UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_WarnSetting_Elevation_Lowerlimit)&&(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_WarnSetting_Elevation_Upperlimit))
        return;
    
    UI_Common_Clear_Screen(temp_ram);

    if(sportmode_elevationwarn_info.temp_curr_page == 0)
    {
    
        if(sportmode_elevationwarn_info.temp_switch == 0)
        {
        
            UI_Common_AddBWsourcePic(temp_ram,64,76,(uint8_t*)iamge_bw_ullimit_off_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }
        else
        {

            sprintf(content,"%02d",sportmode_elevationwarn_info.temp_value1);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,80,4,16,16,16,APP_COLOR_CYAN,content,len,ENUM_TEXTBOX_RIGHT);
            
            sprintf(content,"%02dm",sportmode_elevationwarn_info.temp_value2);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,96,4,16,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            
            
            //line
            UI_Common_Draw_Hline(temp_ram,0,24,176,1,APP_COLOR_WHITE,TRUE);

            //arrow
            UI_Common_AddBWsourcePic(temp_ram,76,32,(uint8_t*)iamge_bw_ullimit_arrow_up_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            UI_Common_AddBWsourcePic(temp_ram,76,144,(uint8_t*)iamge_bw_ullimit_arrow_down_h,APP_COLOR_BLACK,APP_COLOR_WHITE);

            //switch
            UI_Common_AddBWsourcePic(temp_ram,4,76,(uint8_t*)iamge_bw_ullimit_on_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
            //frame
            UI_Common_AddBWsourcePic(temp_ram,55,68,(uint8_t*)iamge_bw_ullimit_frame_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            //frame
            UI_Common_AddBWsourcePic(temp_ram,124,68,(uint8_t*)iamge_bw_ullimit_frame_h,APP_COLOR_BLACK,APP_COLOR_WHITE);


            sprintf(content,"%2d",sportmode_elevationwarn_info.temp_value1);
            UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,64,75,48,48,APP_COLOR_CYAN,content,2,48,ENUM_TEXTBOX_CENTER);
            
            sprintf(content,"%2d",sportmode_elevationwarn_info.temp_value2);
            UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,138,82,36,36,APP_COLOR_WHITE,content,2,36,ENUM_TEXTBOX_CENTER);
        
        }

        
    
    }
    else
    {

            sprintf(content,"%02d",sportmode_elevationwarn_info.temp_value1);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,64,4,16,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_RIGHT);
            
            sprintf(content,"%02d",sportmode_elevationwarn_info.temp_value2);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,80,4,16,16,16,APP_COLOR_CYAN,content,len,ENUM_TEXTBOX_LEFT);

            sprintf(content,"m");
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,98,4,16,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            
            //line
            UI_Common_Draw_Hline(temp_ram,0,24,176,1,APP_COLOR_WHITE,TRUE);

            //arrow
            UI_Common_AddBWsourcePic(temp_ram,76,32,(uint8_t*)iamge_bw_ullimit_arrow_up_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            UI_Common_AddBWsourcePic(temp_ram,76,144,(uint8_t*)iamge_bw_ullimit_arrow_down_h,APP_COLOR_BLACK,APP_COLOR_WHITE);

            
            //frame
            UI_Common_AddBWsourcePic_withoffsetx(temp_ram,0,68,(uint8_t*)iamge_bw_ullimit_frame_h,APP_COLOR_BLACK,APP_COLOR_WHITE,12);
            //frame
            UI_Common_AddBWsourcePic(temp_ram,55,68,(uint8_t*)iamge_bw_ullimit_frame_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            //OK
            UI_Common_AddBWsourcePic(temp_ram,124,76,(uint8_t*)iamge_bw_ullimit_ok_h,APP_COLOR_BLACK,APP_COLOR_CYAN);


            sprintf(content,"%2d",sportmode_elevationwarn_info.temp_value1);
            UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,2,82,36,36,APP_COLOR_CYAN,content,2,36,ENUM_TEXTBOX_CENTER);
            sprintf(content,"%2d",sportmode_elevationwarn_info.temp_value2);
            UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,64,75,48,48,APP_COLOR_CYAN,content,2,48,ENUM_TEXTBOX_CENTER);
            
     }

    UI_Display_Prepare(temp_ram);

}

void UI_Screen_ClimbingModeElevationLlimitSetting_Exit(void)
{


}

void UI_Screen_ClimbingModeElevationLlimitSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeElevationLlimitSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeElevationLlimitSetting_holdlongkeyhandle(void)
{
}



typedef enum 
{
	Enum_Climbing_Limitsetting_Invalid,		
	Enum_Climbing_Limitsetting_Button0,
	Enum_Climbing_Limitsetting_Button1,    
	Enum_Climbing_Limitsetting_Button2,       
	Enum_Climbing_Limitsetting_Button3,
	Enum_Climbing_Limitsetting_Button4,
	Enum_Climbing_Limitsetting_Max,		
}Enum_Climbing_Limitsetting_Button;


    
Enum_Climbing_Limitsetting_Button UI_Screen_ClimbingMode_Limitsetting_Get_Button_Bypoint(int point_x,int point_y)
{

    Enum_Climbing_Limitsetting_Button temp_button = Enum_Climbing_Limitsetting_Invalid;

   if(point_y>=28 && point_y<= 60)
    {
        if(point_x>=64 && point_x<= 112)
        {
            temp_button=Enum_Climbing_Limitsetting_Button1;
        }
    }
    else if(point_y >=76 && point_y<= 124)
    {
        if(point_x>=4 && point_x<= 52)
        {
            temp_button = Enum_Climbing_Limitsetting_Button2;
        }
        else if(point_x>=64 && point_x<= 112)
        {
            temp_button = Enum_Climbing_Limitsetting_Button0;
        }
        else if(point_x>=124 && point_x<= 172)
        {
            temp_button = Enum_Climbing_Limitsetting_Button4;
        }

    }
    else if(point_y>=140 && point_y<= 172)
    {

        if(point_x>=64 && point_x<= 112)
        {
            temp_button=Enum_Climbing_Limitsetting_Button3;
        }
    }

   return temp_button;

}

void UI_Screen_ClimbingModeElevationUpperLlimitSetting_Button0(void)
{

    
    if(sportmode_elevationwarn_info.temp_curr_page == 0)
    {
        if(sportmode_elevationwarn_info.temp_switch == 0)
        {
            sportmode_elevationwarn_info.temp_switch = 1;
            
            UI_Screen_ClimbingModeElevationLlimitSetting_Display();
            UI_Screen_Redraw_Screen();
        
        }
      
    }

}

void UI_Screen_ClimbingModeElevationUpperLlimitSetting_Button1(void)
{
        
        if(sportmode_elevationwarn_info.temp_curr_page == 0)
        {
            if(sportmode_elevationwarn_info.temp_switch == 1)
            {
                sportmode_elevationwarn_info.temp_value1 = sportmode_elevationwarn_info.temp_value1 + sportmode_elevationwarn_info.temp_value1_step;

                if(sportmode_elevationwarn_info.temp_value1 > sportmode_elevationwarn_info.temp_value1_max)
                {
                    if(sportmode_elevationwarn_info.isloop == 1)
                    {
                        sportmode_elevationwarn_info.temp_value1 = sportmode_elevationwarn_info.temp_value1_min;
                    }
                    else
                    {
                        sportmode_elevationwarn_info.temp_value1 = sportmode_elevationwarn_info.temp_value1_max;
                    
}
                }
             }
            
        }
        else if(sportmode_elevationwarn_info.temp_curr_page == 1)
        {

            sportmode_elevationwarn_info.temp_value2 = sportmode_elevationwarn_info.temp_value2 + sportmode_elevationwarn_info.temp_value2_step;
            
            if(sportmode_elevationwarn_info.temp_value2 > sportmode_elevationwarn_info.temp_value2_max)
            {
                if(sportmode_elevationwarn_info.isloop == 1)
                {
                    sportmode_elevationwarn_info.temp_value2 = sportmode_elevationwarn_info.temp_value2_min;
                }
                else
                {
                    sportmode_elevationwarn_info.temp_value2 = sportmode_elevationwarn_info.temp_value2_max;
                
}
            }
            
        }
        
        UI_Screen_ClimbingModeElevationLlimitSetting_Display();
        UI_Screen_Redraw_Screen();
        
}

void UI_Screen_ClimbingModeElevationUpperLlimitSetting_Button2(void)
{
    
    if(sportmode_elevationwarn_info.temp_curr_page == 0)
    {
        if(sportmode_elevationwarn_info.temp_switch == 1)
        {
            sportmode_elevationwarn_info.temp_switch = 0;
    
            UI_Screen_ClimbingModeElevationLlimitSetting_Display();
            UI_Screen_Redraw_Screen();
        
        }
    }

}

void UI_Screen_ClimbingModeElevationUpperLlimitSetting_Button3(void)
{

    
    if(sportmode_elevationwarn_info.temp_curr_page == 0)
    {
        if(sportmode_elevationwarn_info.temp_switch == 1)
        {
            sportmode_elevationwarn_info.temp_value1 = sportmode_elevationwarn_info.temp_value1 - sportmode_elevationwarn_info.temp_value1_step;
    
            if(sportmode_elevationwarn_info.temp_value1 < sportmode_elevationwarn_info.temp_value1_min)
            {
                if(sportmode_elevationwarn_info.isloop == 1)
                {
                    sportmode_elevationwarn_info.temp_value1 = sportmode_elevationwarn_info.temp_value1_max;
                }
                else
                {
                    sportmode_elevationwarn_info.temp_value1 = sportmode_elevationwarn_info.temp_value1_min;
                
}
            }
    
         }
        
    }
    else if(sportmode_elevationwarn_info.temp_curr_page == 1)
    {
    
        sportmode_elevationwarn_info.temp_value2 = sportmode_elevationwarn_info.temp_value2 - sportmode_elevationwarn_info.temp_value2_step;
        
        if(sportmode_elevationwarn_info.temp_value2 < sportmode_elevationwarn_info.temp_value2_min)
        {
            if(sportmode_elevationwarn_info.isloop == 1)
            {
                sportmode_elevationwarn_info.temp_value2 = sportmode_elevationwarn_info.temp_value2_max;
            }
            else
            {
                sportmode_elevationwarn_info.temp_value2 = sportmode_elevationwarn_info.temp_value2_min;
            
}
        }
        
        
    }

    UI_Screen_ClimbingModeElevationLlimitSetting_Display();
    UI_Screen_Redraw_Screen();
    

}

void UI_Screen_ClimbingModeElevationUpperLlimitSetting_Button4(void)
{

    int32 temp_value;


    if(sportmode_elevationwarn_info.temp_curr_page == 1)
    {
        if(sportmode_elevationwarn_info.temp_value1!=0||sportmode_elevationwarn_info.temp_value2!=0)
        {

            temp_value = sportmode_elevationwarn_info.temp_value1*100+sportmode_elevationwarn_info.temp_value2;
            
            if(climbingmode_setting_info.elevation_lowlimit_switch==1&&climbingmode_setting_info.elevation_lowlimit>=temp_value)
            {
                UI_Screen_Show_Warn_Screen_Error();
            }
            else
            {
                UI_Screen_ClimbingModeElevationUpperLlimitSetting_Save();
                UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Elevation);
                UI_Screen_draw_Screen();
            }
        }
    }
}

void UI_Screen_ClimbingModeElevationUpperLlimitSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Climbing_Limitsetting_Button button;
    button = UI_Screen_ClimbingMode_Limitsetting_Get_Button_Bypoint(point_x,point_y);

    if(button == Enum_Climbing_Limitsetting_Invalid)
        return;

    switch(button)
    {
        case Enum_Climbing_Limitsetting_Button0:
            UI_Screen_ClimbingModeElevationUpperLlimitSetting_Button0();
        break;
        case Enum_Climbing_Limitsetting_Button1:
            UI_Screen_ClimbingModeElevationUpperLlimitSetting_Button1();
        break;
        case Enum_Climbing_Limitsetting_Button2:
            UI_Screen_ClimbingModeElevationUpperLlimitSetting_Button2();
        break;
        case Enum_Climbing_Limitsetting_Button3:
            UI_Screen_ClimbingModeElevationUpperLlimitSetting_Button3();
        break;
        case Enum_Climbing_Limitsetting_Button4:
            UI_Screen_ClimbingModeElevationUpperLlimitSetting_Button4();
        break;
        default:
        break;
    }

}





void UI_Screen_ClimbingModeElevationLowerLlimitSetting_Button0(void)
{
    if(sportmode_elevationwarn_info.temp_curr_page == 0)
    {
        if(sportmode_elevationwarn_info.temp_switch == 0)
        {
            sportmode_elevationwarn_info.temp_switch = 1;

            UI_Screen_ClimbingModeElevationLlimitSetting_Display();
            UI_Screen_Redraw_Screen();
        
        }
      
    }

}

void UI_Screen_ClimbingModeElevationLowerLlimitSetting_Button1(void)
{
        
        if(sportmode_elevationwarn_info.temp_curr_page == 0)
        {
            if(sportmode_elevationwarn_info.temp_switch == 1)
            {
                sportmode_elevationwarn_info.temp_value1 = sportmode_elevationwarn_info.temp_value1 + sportmode_elevationwarn_info.temp_value1_step;

                if(sportmode_elevationwarn_info.temp_value1 > sportmode_elevationwarn_info.temp_value1_max)
                {
                    if(sportmode_elevationwarn_info.isloop == 1)
                    {
                        sportmode_elevationwarn_info.temp_value1 = sportmode_elevationwarn_info.temp_value1_min;
                    }
                    else
                    {
                        sportmode_elevationwarn_info.temp_value1 = sportmode_elevationwarn_info.temp_value1_max;
                    
}
                }
             }
            
        }
        else if(sportmode_elevationwarn_info.temp_curr_page == 1)
        {

            sportmode_elevationwarn_info.temp_value2 = sportmode_elevationwarn_info.temp_value2 + sportmode_elevationwarn_info.temp_value2_step;
            
            if(sportmode_elevationwarn_info.temp_value2 > sportmode_elevationwarn_info.temp_value2_max)
            {
                if(sportmode_elevationwarn_info.isloop == 1)
                {
                    sportmode_elevationwarn_info.temp_value2 = sportmode_elevationwarn_info.temp_value2_min;
                }
                else
                {
                    sportmode_elevationwarn_info.temp_value2 = sportmode_elevationwarn_info.temp_value2_max;
                
}
            }
            
        }
        
        UI_Screen_ClimbingModeElevationLlimitSetting_Display();
        UI_Screen_Redraw_Screen();
        
}

void UI_Screen_ClimbingModeElevationLowerLlimitSetting_Button2(void)
{

    if(sportmode_elevationwarn_info.temp_curr_page == 0)
    {
        if(sportmode_elevationwarn_info.temp_switch == 1)
        {
            sportmode_elevationwarn_info.temp_switch = 0;
    
            UI_Screen_ClimbingModeElevationLlimitSetting_Display();
            UI_Screen_Redraw_Screen();
        
        }
    }

}

void UI_Screen_ClimbingModeElevationLowerLlimitSetting_Button3(void)
{
    
    if(sportmode_elevationwarn_info.temp_curr_page == 0)
    {
        if(sportmode_elevationwarn_info.temp_switch == 1)
        {
            sportmode_elevationwarn_info.temp_value1 = sportmode_elevationwarn_info.temp_value1 - sportmode_elevationwarn_info.temp_value1_step;
    
            if(sportmode_elevationwarn_info.temp_value1 < sportmode_elevationwarn_info.temp_value1_min)
            {
                if(sportmode_elevationwarn_info.isloop == 1)
                {
                    sportmode_elevationwarn_info.temp_value1 = sportmode_elevationwarn_info.temp_value1_max;
                }
                else
                {
                    sportmode_elevationwarn_info.temp_value1 = sportmode_elevationwarn_info.temp_value1_min;
                
                }
            }
    
         }
        
    }
    else if(sportmode_elevationwarn_info.temp_curr_page == 1)
    {
        sportmode_elevationwarn_info.temp_value2 = sportmode_elevationwarn_info.temp_value2 - sportmode_elevationwarn_info.temp_value2_step;
        
        if(sportmode_elevationwarn_info.temp_value2 < sportmode_elevationwarn_info.temp_value2_min)
        {
            if(sportmode_elevationwarn_info.isloop == 1)
            {
                sportmode_elevationwarn_info.temp_value2 = sportmode_elevationwarn_info.temp_value2_max;
            }
            else
            {
                sportmode_elevationwarn_info.temp_value2 = sportmode_elevationwarn_info.temp_value2_min;
            
            }
        }
        
        
    }

    UI_Screen_ClimbingModeElevationLlimitSetting_Display();
    UI_Screen_Redraw_Screen();
    
}

void UI_Screen_ClimbingModeElevationLowerLlimitSetting_Button4(void)
{

    int32 temp_value;

    if(sportmode_elevationwarn_info.temp_curr_page == 1)
    {
        if(sportmode_elevationwarn_info.temp_value1!=0||sportmode_elevationwarn_info.temp_value2!=0)
        {

            temp_value = sportmode_elevationwarn_info.temp_value1*100+sportmode_elevationwarn_info.temp_value2;
            
            if(climbingmode_setting_info.elevation_uplimit_switch==1&&climbingmode_setting_info.elevation_uplimit<=temp_value)
            {
                UI_Screen_Show_Warn_Screen_Error();
            }
            else
            {
                UI_Screen_ClimbingModeElevationLowerLlimitSetting_Save();
                UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Elevation);
                UI_Screen_draw_Screen();
            }
         }
    }

        
}


void UI_Screen_ClimbingModeElevationLowerLlimitSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Climbing_Limitsetting_Button button;
    button = UI_Screen_ClimbingMode_Limitsetting_Get_Button_Bypoint(point_x,point_y);

    RTT_DEBUG_printf(0,"button = %d",button);

    if(button == Enum_Climbing_Limitsetting_Invalid)
        return;

    switch(button)
    {
        case Enum_Climbing_Limitsetting_Button0:
            UI_Screen_ClimbingModeElevationLowerLlimitSetting_Button0();
        break;
        case Enum_Climbing_Limitsetting_Button1:
            UI_Screen_ClimbingModeElevationLowerLlimitSetting_Button1();
        break;
        case Enum_Climbing_Limitsetting_Button2:
            UI_Screen_ClimbingModeElevationLowerLlimitSetting_Button2();
        break;
        case Enum_Climbing_Limitsetting_Button3:
            UI_Screen_ClimbingModeElevationLowerLlimitSetting_Button3();
        break;
        case Enum_Climbing_Limitsetting_Button4:
            UI_Screen_ClimbingModeElevationLowerLlimitSetting_Button4();
        break;
        default:
        break;
    }

}


void UI_Screen_ClimbingModeElevationLlimitSetting_tpupslidehandle(void)
{
}

void UI_Screen_ClimbingModeElevationLlimitSetting_tpdownslidehandle(void)
{
}

void UI_Screen_ClimbingModeElevationLlimitSetting_tpleftslidehandle(void)
{
    if(sportmode_elevationwarn_info.temp_curr_page == 0 && sportmode_elevationwarn_info.temp_switch ==1)
    {
        sportmode_elevationwarn_info.temp_curr_page = 1;
        UI_Screen_ClimbingModeElevationLlimitSetting_Display();
        UI_Screen_Redraw_Screen();
    }

}

void UI_Screen_ClimbingModeElevationLlimitSetting_tprightslidehandle(void)
{

    if(sportmode_elevationwarn_info.temp_curr_page == 0)
    {
        climbingmode_setting_info.elevation_uplimit_switch = sportmode_elevationwarn_info.temp_switch;
        UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_WarnSetting_Elevation);
        UI_Screen_draw_Screen();
    }
    else
    {
        sportmode_elevationwarn_info.temp_curr_page = 0;
        UI_Screen_ClimbingModeElevationLlimitSetting_Display();
        UI_Screen_Redraw_Screen();
    }

    

}

//page 1 page 2

static int detail_page = 0;

void UI_Screen_ClimbingModeDetail_Goback()
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Datadetail);
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Climbing);
    UI_Screen_draw_Screen();

}


void  UI_Screen_ClimbingModeDetail_Timerhandle(void)
{

    UI_Screen_ClimbingModeDetail_Display();

    UI_Common_set_timer_handle(UI_Screen_ClimbingModeDetail_Timerhandle);
    App_Lcd_TimerStart(1000);

}


void UI_Screen_ClimbingModeDetail_Entry(void)
{   
    
    //Scene_Climb_Enable();
    
    UI_Screen_ClimbingModeDetail_Timerhandle();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeDetail_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeDetail_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeDetail_tpupslidehandle,
                                    UI_Screen_ClimbingModeDetail_tpdownslidehandle,
                                    UI_Screen_ClimbingModeDetail_tpleftslidehandle,
                                    UI_Screen_ClimbingModeDetail_tprightslidehandle);
    
    
}

void UI_Screen_ClimbingModeDetail_Display(void)
{

    climbMountainInfo_t curr_info;
    int temp_h,temp_m,temp_s;
    char string_content[16];
    int string_len;
    float temp_f;
    int temp_a;//temp_b;
    uint8_t *fontinfo;
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();

    MID_PRESS_PARA_T* curr_press_info;
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    SysTimeType_e curr_type = App_Var_SysTimeTypeGet();
    ui_common_time_12hour_s curr_12hour_time = {0};

    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_Datadetail)
        return;
    
    UI_Common_Clear_Screen(temp_ram);

    Scene_Climb_InfoGet(&curr_info);

    if(detail_page==0)
    {
    
        UI_Common_Show_SportModeDataDetailBG(temp_ram,0,1,0);
        //(uint8_t *lcdram,int x,int y,int width,int height,uint8_t *title,char* data,int datalen,uint8_t font_color)

        temp_h = curr_info.RecordData.Duration/3600;
        temp_m = curr_info.RecordData.Duration%3600/60;
        temp_s = curr_info.RecordData.Duration%60;

        sprintf(string_content,"%2d:%02d:%02d",temp_h,temp_m,temp_s);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,0,176,58,gchinesefont_sportscene_datadetail_timing,string_content,string_len,APP_COLOR_WHITE);
        
        temp_a = (float)curr_info.RealTimeData.Altitude;
        sprintf(string_content,"%d",temp_a);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,59,87,58,gchinesefont_compass_elevation,string_content,string_len,APP_COLOR_WHITE);


        temp_a = curr_info.RealTimeData.Speed;
        sprintf(string_content,"%d",temp_a);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,88,59,87,58,gchinesefont_sportscene_verticalspeed,string_content,string_len,APP_COLOR_WHITE);

        switch(curr_info.HrZone)
        {
            case HR_ZONE_0:
                fontinfo = (uint8_t *)gchinesefont_sportscene_datadetail_nothing;
                break;
            case HR_ZONE_1:
                fontinfo = (uint8_t *)gchinesefont_sportscene_datadetail_warmup;
            break;
            case HR_ZONE_2:
                fontinfo = (uint8_t *)gchinesefont_sportscene_datadetail_fatburning;
            break;
            case HR_ZONE_3:
                fontinfo = (uint8_t *)gchinesefont_sportscene_datadetail_aerobicendurance;
            break;
            case HR_ZONE_4:
                fontinfo = (uint8_t *)gchinesefont_sportscene_datadetail_physicalstrengthen;
            break;
            case HR_ZONE_5:
                fontinfo = (uint8_t *)gchinesefont_sportscene_datadetail_anaerobicendurance;
            break;
            default:
                fontinfo = (uint8_t *)gchinesefont_sportscene_datadetail_nothing;
                break;
            
        }

        if(curr_info.RealTimeData.Hr == 0)
        {
            sprintf(string_content,"--");
        }
        else
        {
            
            sprintf(string_content,"%d",curr_info.RealTimeData.Hr);
        }

        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_HrData(temp_ram,0,118,176,58,fontinfo,string_content,string_len,APP_COLOR_WHITE,curr_info.HrZone);
        
    }
    else
    {
        UI_Common_Show_SportModeDataDetailBG(temp_ram,0,1,0);
        //(uint8_t *lcdram,int x,int y,int width,int height,uint8_t *title,char* data,int datalen,uint8_t font_color)
        
        sprintf(string_content,"%d",curr_info.RecordData.Distance);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,0,176,58,gchinesefont_sportscene_datadetail_distance,string_content,string_len,APP_COLOR_WHITE);

        if(curr_type == SYS_TIME_24_TYPE)
        {
            sprintf(string_content,"%d:%2d",lMidRTC->RTC.hour,lMidRTC->RTC.min);
            string_len = strlen(string_content);
            UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,59,87,58,gchinesefont_sportscene_datadetail_currenttime,string_content,string_len,APP_COLOR_WHITE);
        }
        else
        {
        
            UI_Common_Get_Time_12hour(&curr_12hour_time);
            
            //14-80
            if(curr_12hour_time.is_am ==1)
            {
                sprintf(string_content,"%d:%02d AM",curr_12hour_time.hour,curr_12hour_time.min);
            }
            else
            {
                sprintf(string_content,"%d:%02d PM",curr_12hour_time.hour,curr_12hour_time.min);
            }
            string_len = strlen(string_content);
            UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,59,87,58,gchinesefont_sportscene_datadetail_currenttime,string_content,string_len,APP_COLOR_WHITE);
        }

        

		curr_press_info = Mid_Press_ParamPGet();
        temp_f = (float)curr_press_info->LastTemp/100;
        sprintf(string_content,"%0.1fC",temp_f);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,89,59,87,58,gchinesefont_sportscene_datadetail_temperature,string_content,string_len,APP_COLOR_WHITE);


        sprintf(string_content,"%d",curr_info.RecordData.Calorie);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,118,176,58,gchinesefont_sportscene_datadetail_calorie,string_content,string_len,APP_COLOR_WHITE);

    }
    
    UI_Display_Prepare(temp_ram);

}



void UI_Screen_ClimbingModeDetail_Exit(void)
{
    detail_page = 0;
}


void UI_Screen_ClimbingModeDetail_shortkeyhandle(void)
{

    UI_Common_Shake();
    Scene_Climb_Pause();
    UI_Screen_ClimbingModeDetail_Exit();
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Pause);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeDetail_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeDetail_holdlongkeyhandle(void)
{
}

void UI_Screen_ClimbingModeDetail_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        break;
        default:
        break;
    }

    
    #if 0
    UI_Screen_ClimbingModeDetail_Exit();
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Pause);
    UI_Screen_draw_Screen();
    #endif
    
    
}


void UI_Screen_ClimbingModeDetail_tpupslidehandle(void)
{

    if(detail_page == 0)
        detail_page =1;
    else
        detail_page =0;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Datadetail);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeDetail_tpdownslidehandle(void)
{

    if(detail_page == 0)
        detail_page =1;
    else
        detail_page =0;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Datadetail);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeDetail_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeDetail_tprightslidehandle(void)
{

    UI_Set_Go_back_handle(UI_Screen_ClimbingModeDetail_Goback);

    UI_Screen_ClimbingModeDetail_Exit();

    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();
}


void UI_Screen_ClimbingModePause_Timerhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Menu);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModePause_Entry(void)
{   

    UI_ScreenClimbingModePause_Display();

    UI_Common_set_timer_handle(UI_Screen_ClimbingModePause_Timerhandle);
    App_Lcd_TimerStart(500);
    
    UI_Common_clean_tp_handle();
    UI_Common_clean_key_handle();
}

void UI_ScreenClimbingModePause_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_Pause)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_Show_PlayPause(temp_ram,1);
    UI_Display_Prepare(temp_ram);

}

void UI_Screen_ClimbingModePause_Exit(void)
{

}


void UI_Screen_ClimbingModeContinue_Timerhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Datadetail);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeContinue_Entry(void)
{   

    UI_Screen_ClimbingModeContinue_Display();
    UI_Common_set_timer_handle(UI_Screen_ClimbingModeContinue_Timerhandle);
    App_Lcd_TimerStart(500);

    UI_Common_clean_tp_handle();
    UI_Common_clean_key_handle();
    
}

void UI_Screen_ClimbingModeContinue_Display(void)
{
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_Continue)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_Show_PlayPause(temp_ram,0);
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_ClimbingModeContinue_Exit(void)
{


}


static int menu_page = 0;


void UI_Screen_ClimbingModeMenu_Entry(void)
{   

    UI_Screen_ClimbingModeMenu_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeMenu_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeMenu_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeMenu_tpupslidehandle,
                                    UI_Screen_ClimbingModeMenu_tpdownslidehandle,
                                    UI_Screen_ClimbingModeMenu_tpleftslidehandle,
                                    UI_Screen_ClimbingModeMenu_tprightslidehandle);
}

void UI_Screen_ClimbingModeMenu_Display(void)
{
    climbMountainInfo_t curr_info;
    char string_distance[16];
    int len_distance;
    char string_duration[16];
    int len_duration;
    int temp_h,temp_m,temp_s;
    float temp_f;
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_Menu)
        return;
    
    UI_Common_Clear_Screen(temp_ram);

    #if 0
    if(menu_page == 0)
    {
        Scene_Climb_InfoGet(&curr_info);

        temp_f = (float)curr_info.RecordData.Distance/1000;
        //memset(string_content,0,16);
        sprintf(string_distance,"%0.2f",temp_f);
        len_distance = strlen(string_distance);

        
        temp_h = curr_info.RecordData.Duration/3600;
        temp_m = curr_info.RecordData.Duration%3600/60;
        temp_s = curr_info.RecordData.Duration%60;
        
        sprintf(string_duration,"%2d:%2d:%2d",temp_h,temp_m,temp_s);
        len_duration = strlen(string_duration);

        UI_Common_Show_ModeMenuHeadBar(lcdram,0,0,string_distance,len_distance,string_duration,len_duration);

        UI_Common_List_RarrowDoubleline(lcdram,0,59,(uint8_t *)gchinesefont_sportscene_datadetail_continue,NULL,0);
        UI_Common_List_RarrowDoubleline(lcdram,0,118,(uint8_t *)gchinesefont_sportscene_datadetail_complete,NULL,0);
    }
    else
    {
        UI_Common_List_RarrowDoubleline(lcdram,0,0,(uint8_t *)gchinesefont_sportscene_datadetail_abandon,NULL,0);
        UI_Common_List_RarrowDoubleline(lcdram,0,59,(uint8_t *)gchinesefont_sportscene_datadetail_keeponrunning,NULL,0);
    }
    #else

        Scene_Climb_InfoGet(&curr_info);
        
        temp_f = (float)curr_info.RecordData.Distance/1000;
        //memset(string_content,0,16);
        sprintf(string_distance,"%0.2f",temp_f);
        len_distance = strlen(string_distance);
        
        
        temp_h = curr_info.RecordData.Duration/3600;
        temp_m = curr_info.RecordData.Duration%3600/60;
        temp_s = curr_info.RecordData.Duration%60;
        
        sprintf(string_duration,"%2d:%2d:%2d",temp_h,temp_m,temp_s);
        len_duration = strlen(string_duration);

        UI_Common_Show_ModeMenuHeadBar(temp_ram,0,0,string_distance,len_distance,string_duration,len_duration);


        UI_Common_Draw_Hline(temp_ram,4,59,168,1,APP_COLOR_WHITE,TRUE);
        
        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_datadetail_continue,NULL,NULL,0);
        UI_Common_List_RarrowDoubleline(temp_ram,0,118,(uint8_t *)gchinesefont_sportscene_datadetail_complete,NULL,NULL,0);
    
    #endif
    
    UI_Display_Prepare(temp_ram);

}

void UI_Screen_ClimbingModeMenu_Exit(void)
{

    menu_page = 0;

}

void UI_Screen_ClimbingModeMenu_shortkeyhandle(void)
{

    UI_Screen_ClimbingModeMenu_Exit();

    UI_Common_Shake();

    Scene_Climb_Continue();
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Continue);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeMenu_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeMenu_holdlongkeyhandle(void)
{
}

void UI_Screen_ClimbingModeMenu_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        if(menu_page == 1)
        {
            UI_Screen_ClimbingModeMenu_Exit();
            UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Abandon);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        if(menu_page == 1)
        {
            UI_Screen_ClimbingModeMenu_Exit();
            UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
            UI_Screen_draw_Screen();
        }
        else if(menu_page == 0)
        {
            UI_Screen_ClimbingModeMenu_Exit();
            UI_Common_Shake();
            Scene_Climb_Continue();
            UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Continue);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        if(menu_page == 0)
        {
            UI_Screen_ClimbingModeMenu_Exit();
            UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_CompleteMenu);
            UI_Screen_draw_Screen();
        }
        
        break;
        default:
        break;
    }
        
    
}


void UI_Screen_ClimbingModeMenu_tpupslidehandle(void)
{

#if 0
    if(menu_page == 0)
        menu_page =1;
    else
        menu_page =0;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Menu);
    UI_Screen_draw_Screen();
#endif
}

void UI_Screen_ClimbingModeMenu_tpdownslidehandle(void)
{
#if 0
    if(menu_page == 0)
        menu_page =1;
    else
        menu_page =0;
    
    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Menu);
    UI_Screen_draw_Screen();
#endif
}

void UI_Screen_ClimbingModeMenu_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeMenu_tprightslidehandle(void)
{

    //UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
    //UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeCompleteMenu_Entry(void)
{   

    menu_page = 0;
    UI_Screen_ClimbingModeCompleteMenu_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeCompleteMenu_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeCompleteMenu_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeCompleteMenu_tpupslidehandle,
                                    UI_Screen_ClimbingModeCompleteMenu_tpdownslidehandle,
                                    UI_Screen_ClimbingModeCompleteMenu_tpleftslidehandle,
                                    UI_Screen_ClimbingModeCompleteMenu_tprightslidehandle);
}

void UI_Screen_ClimbingModeCompleteMenu_Display(void)
{

    #if 0
    climbMountainInfo_t curr_info;
    char string_distance[16];
    int len_distance;
    char string_duration[16];
    int len_duration;
    int temp_h,temp_m,temp_s;
    float temp_f;
    #endif

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_CompleteMenu)
        return;
    
    UI_Common_Clear_Screen(temp_ram);

    #if 0
    Scene_Climb_InfoGet(&curr_info);

    temp_f = (float)curr_info.RecordData.Distance/1000;
    //memset(string_content,0,16);
    sprintf(string_distance,"%0.2f",temp_f);
    len_distance = strlen(string_distance);

    
    temp_h = curr_info.RecordData.Duration/3600;
    temp_m = curr_info.RecordData.Duration%3600/60;
    temp_s = curr_info.RecordData.Duration%60;
    
    sprintf(string_duration,"%2d:%2d:%2d",temp_h,temp_m,temp_s);
    len_duration = strlen(string_duration);

    UI_Common_Show_ModeMenuHeadBar(lcdram,0,0,string_distance,len_distance,string_duration,len_duration);

    UI_Common_List_RarrowDoubleline(lcdram,0,59,(uint8_t *)gchinesefont_sportscene_datadetail_datadetail,NULL,0);
    UI_Common_List_RarrowDoubleline(lcdram,0,118,(uint8_t *)gchinesefont_sportscene_datadetail_exit,NULL,0);
    #else

    UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_save,NULL,NULL,0);
    UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_abandon_confirm_yes,NULL,NULL,0);
    #endif

    UI_Display_Prepare(temp_ram);
    
}


void UI_Screen_ClimbingModeCompleteMenu_Exit(void)
{


}
void UI_Screen_ClimbingModeCompleteMenu_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Menu);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeCompleteMenu_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeCompleteMenu_holdlongkeyhandle(void)
{
}

void UI_Screen_ClimbingModeCompleteMenu_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            UI_Common_Shake();

            Scene_Climb_Disable();
            //模式结束，开启大休眠
            UI_Commom_Set_Allow_Lockstate2(1);
            
            UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_History);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Abandon);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        break;
        default:
        break;
    }

    
    
}


void UI_Screen_ClimbingModeCompleteMenu_tpupslidehandle(void)
{
}

void UI_Screen_ClimbingModeCompleteMenu_tpdownslidehandle(void)
{
}

void UI_Screen_ClimbingModeCompleteMenu_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeCompleteMenu_tprightslidehandle(void)
{

}

void UI_Screen_ClimbingModeAbandon_Entry(void)
{   

    UI_Screen_ClimbingModeAbandon_Display();

    UI_Common_set_key_handle(UI_Screen_ClimbingModeAbandon_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeAbandon_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeAbandon_tpupslidehandle,
                                    UI_Screen_ClimbingModeAbandon_tpdownslidehandle,
                                    UI_Screen_ClimbingModeAbandon_tpleftslidehandle,
                                    UI_Screen_ClimbingModeAbandon_tprightslidehandle);
}

void UI_Screen_ClimbingModeAbandon_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_Abandon)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    //UI_Common_AddPic(lcdram,4,63,(uint8_t*)BtnFullCyan_h);
    UI_Common_AddBWsourcePic(temp_ram,4,63,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
    UI_Common_AddBWsourcePic(temp_ram,4,122,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_RED);

    UI_Common_Draw_FontStr_textbox(temp_ram,0,0,176,58,(uint8_t *)gchinesefont_sportscene_abandon_confirm,APP_COLOR_WHITE,APP_COLOR_BLACK);
    UI_Common_Draw_FontStr_textbox(temp_ram,0,59,176,58,(uint8_t *)gchinesefont_sportscene_abandon_confirm_no,APP_COLOR_BLACK,APP_COLOR_CYAN);
    UI_Common_Draw_FontStr_textbox(temp_ram,0,118,176,58,(uint8_t *)gchinesefont_sportscene_abandon_confirm_yes,APP_COLOR_BLACK,APP_COLOR_RED);

    UI_Display_Prepare(temp_ram);
}

void UI_Screen_ClimbingModeAbandon_Exit(void)
{


}

void UI_Screen_ClimbingModeAbandon_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Menu);
    UI_Screen_draw_Screen();

}

void UI_Screen_ClimbingModeAbandon_holdshortkeyhandle(void)
{
}

void UI_Screen_ClimbingModeAbandon_holdlongkeyhandle(void)
{
}

void UI_Screen_ClimbingModeAbandon_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Menu);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {

            UI_Set_Go_back_handle(NULL);
            Scene_Climb_Disable();
            //模式结束，开启大休眠
            UI_Commom_Set_Allow_Lockstate2(1);
            
            UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
            UI_Screen_draw_Screen();
        }
        
        break;
        default:
        break;
    }
        
    
}


void UI_Screen_ClimbingModeAbandon_tpupslidehandle(void)
{


}

void UI_Screen_ClimbingModeAbandon_tpdownslidehandle(void)
{


}

void UI_Screen_ClimbingModeAbandon_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeAbandon_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Menu);
    UI_Screen_draw_Screen();
}

static int page_number = 0;

void UI_Screen_ClimbingModeHistory_Entry(void)
{


        
    UI_Screen_ClimbingModeHistory_Display();
    
    UI_Common_set_key_handle(UI_Screen_ClimbingModeHistory_shortkeyhandle,NULL,NULL);
    
    UI_Common_set_tp_click_handle(UI_Screen_ClimbingModeHistory_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_ClimbingModeHistory_tpupslidehandle,
                                    UI_Screen_ClimbingModeHistory_tpdownslidehandle,
                                    UI_Screen_ClimbingModeHistory_tpleftslidehandle,
                                    UI_Screen_ClimbingModeHistory_tprightslidehandle);
    
}


void UI_Screen_ClimbingModeHistory_Display(void)
{

    char content[32];
    int len;
    
    int hour;
    int min;
    int second;

    //int width;
    //int height;
    //int total_width = 0;
    
    float temp_f;
    
    rtc_time_s rtc_time;
    //int temp_value;
    
    climbMountainInfo_t curr_info;
    

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Climbingmode()!=Common_Screen_SubID_ClimbingMode_History)
        return;
    
    UI_Common_Clear_Screen(temp_ram);


    Scene_Climb_InfoGet(&curr_info);

    //首页
    if(page_number == 0)
    {
        //title
        
        UtcTransformTime(curr_info.RecordData.StartUTC, &rtc_time);
        
        UI_Common_Draw_FontStr_textbox(temp_ram,8,8,160,16,(uint8_t *)gchinesefont_sportscene_history_climbing,APP_COLOR_WHITE,APP_COLOR_BLACK);
        sprintf(content,"%02d/%02d/%02d  %02d:%02d",rtc_time.year,rtc_time.month,rtc_time.day,rtc_time.hour,rtc_time.min);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,8,32,160,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_CENTER);
        
        //距离
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_distance[0]-8,59,gchinesefont_sportscene_datadetail_distance[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_distance,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);


        temp_f = (float)curr_info.RecordData.Distance/1000;
        //memset(string_content,0,16);
        sprintf(content,"%0.2fkm",temp_f);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);


        //时长
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_time[0]-8,101,gchinesefont_sportscene_datadetail_time[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_time,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,105,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        hour = curr_info.RecordData.Duration/3600;
        min = curr_info.RecordData.Duration%3600/60;
        second = curr_info.RecordData.Duration%60;
        sprintf(content,"%02d:%02d:%02d",hour,min,second);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,101,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);


        //活动时长
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_activitytime[0]-8,142,gchinesefont_sportscene_datadetail_activitytime[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_activitytime,APP_COLOR_WHITE,APP_COLOR_BLACK);
        //UI_Common_Draw_FontStr_textbox(lcdram,84-gchinesefont_sportscene_datadetail_minkm[0]-gchinesefont_sportscene_average[0]-8,142,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,146,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        hour = curr_info.RecordData.ValidDuration/3600;
        min = curr_info.RecordData.ValidDuration%3600/60;
        second = curr_info.RecordData.ValidDuration%60;
        sprintf(content,"%02d:%02d:%02d",hour,min,second);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,142,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        
        
    }
    else if(page_number == 1)
    {
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_goup[0]-8,18,gchinesefont_sportscene_datadetail_goup[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_goup,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,22,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        
        sprintf(content,"%dm",curr_info.RecordData.UpAltitude);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,18,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        

        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_godown[0]-8,59,gchinesefont_sportscene_datadetail_godown[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_godown,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        sprintf(content,"%dm",curr_info.RecordData.DownAltitude);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        
        
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_speed[0]-8,101,gchinesefont_sportscene_datadetail_speed[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_speed,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_speed[0]-gchinesefont_sportscene_average[0]-8,101,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,105,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);


        temp_f = curr_info.RecordData.SpeedAVG/1000;
        sprintf(content,"%0.2fkm/h",temp_f);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,101,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        

        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_compass_elevation[0]-8,142,gchinesefont_compass_elevation[0],16,(uint8_t *)gchinesefont_compass_elevation,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_compass_elevation[0]-gchinesefont_sportscene_datadetail_highest[0]-8,142,gchinesefont_sportscene_datadetail_highest[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_highest,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,146,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        sprintf(content,"%dm",curr_info.RecordData.HighestAltitude);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,142,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);


        
            
    }
    else
    {
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_calorie[0]-8,18,gchinesefont_sportscene_datadetail_calorie[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_calorie,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,22,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        sprintf(content,"%dkcal",curr_info.RecordData.Calorie);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,18,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-8,59,gchinesefont_heartrate_detail_heartrate[0],16,(uint8_t *)gchinesefont_heartrate_detail_heartrate,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-gchinesefont_sportscene_average[0]-8,59,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        sprintf(content,"%d",curr_info.RecordData.HrAVG);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        
        
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-8,101,gchinesefont_heartrate_detail_heartrate[0],16,(uint8_t *)gchinesefont_heartrate_detail_heartrate,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-gchinesefont_sportscene_datadetail_max[0]-8,101,gchinesefont_sportscene_datadetail_max[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_max,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,105,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        sprintf(content,"%d",curr_info.RecordData.HrMax);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,101,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        
    }
    
    
    UI_Display_Prepare(temp_ram);

}


void UI_Screen_ClimbingModeHistory_Exit(void)
{

    page_number = 0;

}


void UI_Screen_ClimbingModeHistory_shortkeyhandle()
{
    UI_Set_Go_back_handle(NULL);
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();
}


void UI_Screen_ClimbingModeHistory_tpclickhandle(int point_x,int point_y)
{
    
}

void UI_Screen_ClimbingModeHistory_tpupslidehandle(void)
{
    int total_page;

    total_page = 3;
    
    if(page_number < total_page-1)
    {
        page_number++;
        UI_Screen_draw_Screen();
    }
    else
    {
    }


}

void UI_Screen_ClimbingModeHistory_tpdownslidehandle(void)
{

    if(page_number>0)
    {
        page_number--;
        UI_Screen_draw_Screen();
    }
    else
    {
        
    }
    

}

void UI_Screen_ClimbingModeHistory_tpleftslidehandle(void)
{
}

void UI_Screen_ClimbingModeHistory_tprightslidehandle(void)
{
    UI_Set_Go_back_handle(NULL);
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();
}










