
#include "ui_screen_swim.h"
#include "ui_screen_dateandtime.h"


Enum_Common_Screen_SUBID_SWIMMODE curr_subscreenid_swimmode;

//laps 
typedef enum
{
	ENUM_SMLAPS_TARGET_4 = 0,
	ENUM_SMLAPS_TARGET_8,
	ENUM_SMLAPS_TARGET_10,
	ENUM_SMLAPS_TARGET_12,
	ENUM_SMLAPS_TARGET_16,         //hmarathon21.1
	ENUM_SMLAPS_TARGET_20,          //marathon42.2
	ENUM_SMLAPS_TARGET_32,
	ENUM_SMLAPS_TARGET_40,
	ENUM_SMLAPS_TARGET_MAX,
}enum_swimmode_lapstarget;
    

char swimmode_lapstarget_4[] = {"4"};
char swimmode_lapstarget_8[] = {"8"};
char swimmode_lapstarget_10[] = {"10"};
char swimmode_lapstarget_12[] = {"12"};
char swimmode_lapstarget_16[] = {"16"};
char swimmode_lapstarget_20[] = {"20"};
char swimmode_lapstarget_32[] = {"32"};
char swimmode_lapstarget_40[] = {"40"};



//duration
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
}enum_swimmode_durationtarget;


char swimmode_durationtarget_20min[] = {"20min"};
char swimmode_durationtarget_30min[] = {"30min"};
char swimmode_durationtarget_60min[] = {"60min"};
char swimmode_durationtarget_90min[] = {"90min"};
char swimmode_durationtarget_120min[] = {"120min"};
char swimmode_durationtarget_180min[] = {"180min"};
char swimmode_durationtarget_240min[] = {"240min"};


//calorie
typedef enum
{
	ENUM_SMCALORIE_TARGET_100KCAL,
	ENUM_SMCALORIE_TARGET_200KCAL,
	ENUM_SMCALORIE_TARGET_300KCAL,
	ENUM_SMCALORIE_TARGET_500KCAL,
	ENUM_SMCALORIE_TARGET_800KCAL,
	ENUM_SMCALORIE_TARGET_1000KCAL,
	ENUM_SMCALORIE_TARGET_MAX,
}enum_swimmode_calorietarget;
    

char swimmode_durationtarget_100kcal[] = {"100kcal"};
char swimmode_durationtarget_200kcal[] = {"200kcal"};
char swimmode_durationtarget_300kcal[] = {"300kcal"};
char swimmode_durationtarget_500kcal[] = {"500kcal"};
char swimmode_durationtarget_800kcal[] = {"800kcal"};
char swimmode_durationtarget_1000kcal[] = {"1000kcal"};


typedef enum
{
	ENUM_SMLAPS_WARN_OFF = 0,
	ENUM_SMLAPS_WARN_4,
	ENUM_SMLAPS_WARN_8,
	ENUM_SMLAPS_WARN_10,
	ENUM_SMLAPS_WARN_12,
	ENUM_SMLAPS_WARN_16,
	ENUM_SMLAPS_WARN_20,
	ENUM_SMLAPS_WARN_MAX,
}enum_swimmode_lapswarn;


char swimmode_lapswarn_4[] = {"4"};
char swimmode_lapswarn_8[] = {"8"};
char swimmode_lapswarn_10[] = {"10"};
char swimmode_lapswarn_12[] = {"12"};
char swimmode_lapswarn_16[] = {"16"};
char swimmode_lapswarn_20[] = {"20"};


typedef enum
{
	ENUM_SMDURATION_WARN_OFF = 0,
	ENUM_SMDURATION_WARN_5MIN,
	ENUM_SMDURATION_WARN_10MIN,
	ENUM_SMDURATION_WARN_15MIN,
	ENUM_SMDURATION_WARN_20MIN,
	ENUM_SMDURATION_WARN_30MIN,
	ENUM_SMDURATION_WARN_60MIN,
	ENUM_SMDURATION_WARN_90MIN,
	ENUM_SMDURATION_WARN_120MIN,
	ENUM_SMDURATION_WARN_MAX,
}enum_swimmode_durationwarn;



char swimmode_durationwarn_5min[] = {"5min"};
char swimmode_durationwarn_10min[] = {"10min"};
char swimmode_durationwarn_15min[] = {"15min"};
char swimmode_durationwarn_20min[] = {"20min"};
char swimmode_durationwarn_30min[] = {"30min"};
char swimmode_durationwarn_60min[] = {"60min"};
char swimmode_durationwarn_90min[] = {"90min"};
char swimmode_durationwarn_120min[] = {"120min"};

typedef enum
{
	ENUM_SMCALORIE_WARN_OFF,
	ENUM_SMCALORIE_WARN_50KCAL,
	ENUM_SMCALORIE_WARN_100KCAL,
	ENUM_SMCALORIE_WARN_150KCAL,
	ENUM_SMCALORIE_WARN_200KCAL,
	ENUM_SMCALORIE_WARN_MAX,
}enum_swimmode_caloriewarn;

char swimmode_caloriewarn_50kcal[] = {"50kcal"};
char swimmode_caloriewarn_100kcal[] = {"100kcal"};
char swimmode_caloriewarn_150kcal[] = {"150kcal"};
char swimmode_caloriewarn_200kcal[] = {"200kcal"};

typedef enum
{
	ENUM_SMCALORIE_POOLL_25M,
	ENUM_SMCALORIE_POOLL_50M,
	ENUM_SMCALORIE_POOLL_33M,
	ENUM_SMCALORIE_POOLL_25YD,
	ENUM_SMCALORIE_POOLL_33YD,
	ENUM_SMCALORIE_POOLL_MAX,
}enum_swimmode_pooll;


char swimmode_pooll_25m[] = {"25m"};
char swimmode_pooll_50m[] = {"50m"};
char swimmode_pooll_33m[] = {"33 1/3m"};
char swimmode_pooll_25yd[] = {"25yd"};
char swimmode_pooll_33yd[] = {"33 1/3yd"};




void UI_Set_Curr_SubScreenID_Swimmode(Enum_Common_Screen_SUBID_SWIMMODE curr_id)
{

    curr_subscreenid_swimmode = curr_id;

}

int UI_Get_Curr_SubScreenID_Swimmode(void)
{

     return curr_subscreenid_swimmode;

}


//RuningMode
void UI_Screen_SwimModeEntry()
{

    switch(curr_subscreenid_swimmode)
    {
        case Common_Screen_SubID_SwimMode_Prepare:
            UI_Screen_SwimModePrepare_Entry();
        break;
        case Common_Screen_SubID_SwimMode_Countdown:
            UI_Screen_SwimModeCountDown_Entry();
        break;
        case Common_Screen_SubID_SwimMode_Setting:
            UI_Screen_SwimModeSetting_Entry();
        break;
        case Common_Screen_SubID_SwimMode_TargetSetting:
            UI_Screen_SwimModeTargetSetting_Entry();
        break;
        case Common_Screen_SubID_SwimMode_TargetSetting_Laps:
            UI_Screen_SwimModeLapsTargetSetting_Entry();
        break;
        case Common_Screen_SubID_SwimMode_TargetSetting_Duration:
            UI_Screen_SwimModeDurationTargetSetting_Entry();
        break;
        case Common_Screen_SubID_SwimMode_TargetSetting_Calorie:
            UI_Screen_SwimModeCalorieTargetSetting_Entry();
        break;
        case Common_Screen_SubID_SwimMode_WarnSetting:
            UI_Screen_SwimModeWarnSetting_Entry();
        break;
        case Common_Screen_SubID_SwimMode_WarnSetting_Laps:
            UI_Screen_SwimModeLapsWarnSetting_Entry();
        break;
        case Common_Screen_SubID_SwimMode_WarnSetting_Duration:
            UI_Screen_SwimModeDurationWarnSetting_Entry();
        break;
        case Common_Screen_SubID_SwimMode_WarnSetting_Calorie:
            UI_Screen_SwimModeCalorieWarnSetting_Entry();
        break;
        case Common_Screen_SubID_SwimMode_PoolLength:
            UI_Screen_SwimModePoolLengthSetting_Entry();
        break;
        case Common_Screen_SubID_SwimMode_Datadetail:
            UI_Screen_SwimModeDetail_Entry();
        break;
        case Common_Screen_SubID_SwimMode_Pause:
            UI_Screen_SwimModePause_Entry();
        break;
        case Common_Screen_SubID_SwimMode_Continue:
            UI_Screen_SwimModeContinue_Entry();
        break;
        case Common_Screen_SubID_SwimMode_Menu:
            UI_Screen_SwimModeMenu_Entry();
        break;
        case Common_Screen_SubID_SwimMode_Abandon:
            UI_Screen_SwimModeAbandon_Entry();
        break;
        case Common_Screen_SubID_SwimMode_CompleteMenu:
            UI_Screen_SwimModeCompleteMenu_Entry();
        break;
        case Common_Screen_SubID_SwimMode_History:
            UI_Screen_SwimModeHistory_Entry();
        break;
        default:
            UI_Screen_SwimModePrepare_Entry();
            break;
    }

}




//RuningMode
void UI_Screen_SwimModePrepare_Entry(void)
{
    //初始化数据等
    UI_Screen_SwimModePrepare_Display();

    UI_Common_set_key_handle(UI_Screen_SwimModePrepare_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SwimModePrepare_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModePrepare_tpupslidehandle,
                                    UI_Screen_SwimModePrepare_tpdownslidehandle,
                                    UI_Screen_SwimModePrepare_tpleftslidehandle,
                                    UI_Screen_SwimModePrepare_tprightslidehandle);

}

void UI_Screen_SwimModePrepare_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_Prepare)
        return;
    
    UI_Common_Clear_Screen(temp_ram);

    UI_Common_Show_ThreeIconBar(temp_ram,0,0,(uint8_t*)NULL,(uint8_t*)image_hr_24_h,(uint8_t*)NULL);

    UI_Common_Add_Battery(temp_ram,124,17,1);
    
    UI_Common_Show_ModeListIconStringBar(temp_ram,0,59,(uint8_t*)image_sportmode_swim_24_h,(uint8_t*)image_sportmode_start_24_h,(uint8_t*)BtnSport_h,(uint8_t*)gchinesefont_sportscene_start,APP_COLOR_RED,APP_COLOR_WHITE);
    UI_Common_Show_ModeListIconStringBar(temp_ram,0,118,NULL,(uint8_t*)image_sportmode_right_24_h,NULL,(uint8_t*)gchinesefont_sportscene_setting,APP_COLOR_BLACK,APP_COLOR_WHITE);

    UI_Display_Prepare(temp_ram);
}


void UI_Screen_SwimModePrepare_Exit(void)
{
    //初始化数据等


}

void UI_Screen_SwimModePrepare_shortkeyhandle(void)
{

    //UI_Common_Shake();
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Countdown);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModePrepare_holdshortkeyhandle(void)
{
}

void UI_Screen_SwimModePrepare_holdlongkeyhandle(void)
{
}

void UI_Screen_SwimModePrepare_tpclickhandle(int point_x,int point_y)
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
            UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Countdown);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
            UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
            UI_Screen_draw_Screen();
        }
        break;
        default:
        break;
    }


    
}

void UI_Screen_SwimModePrepare_tpupslidehandle(void)
{


}

void UI_Screen_SwimModePrepare_tpdownslidehandle(void)
{


}

void UI_Screen_SwimModePrepare_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModePrepare_tprightslidehandle(void)
{


    UI_Set_Curr_ScreenID(Common_Screen_MainID_Modelist);
    UI_Screen_draw_Screen();

}

extern UI_Common_sportmode_countdown_s sportmode_countdown;

void UI_Screen_SwimModeCountDown_Entry(void)
{

    UI_Common_SportModeCountDownInfoDefault();
    UI_Screen_SwimModeCountDown_Display();

    UI_Common_set_key_handle(UI_Screen_SwimModeCountDown_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SwimModeCountDown_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModeCountDown_tpupslidehandle,
                                    UI_Screen_SwimModeCountDown_tpdownslidehandle,
                                    UI_Screen_SwimModeCountDown_tpleftslidehandle,
                                    UI_Screen_SwimModeCountDown_tprightslidehandle);
}

void UI_Screen_SwimModeCountDown_Display_Timerhandle(void)
{
        UI_Screen_SwimModeCountDown_Display();
}


void  UI_Screen_SwimModeCountDown_Display(void)
{
    int ctime = 0;
    uint8_t* fontinfo = NULL;
    double angle = 0;
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_Countdown)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    
    
    if(sportmode_countdown.curr_time<sportmode_countdown.total_time)
    {
        ctime = (sportmode_countdown.total_time-sportmode_countdown.curr_time)/1000;
        
        angle = (double)sportmode_countdown.curr_time/(double)sportmode_countdown.total_time*2*PI;
        
        UI_Common_DispRuningModeCountDownRound(temp_ram,angle);
        sportmode_countdown.curr_time = sportmode_countdown.curr_time + sportmode_countdown.segment_time;
        UI_Common_set_timer_handle(UI_Screen_SwimModeCountDown_Display_Timerhandle);
        App_Lcd_TimerStart(sportmode_countdown.segment_time);
    }
    else
    {
        UI_Screen_SwimModeCountDown_Exit();
        Scene_Swim_Enable();
        //模式开始，关闭大休眠
        UI_Commom_Set_Allow_Lockstate2(0);
        UI_Common_Shake();
        UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Datadetail);
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

void UI_Screen_SwimModeCountDown_Exit(void)
{
     UI_Common_set_timer_handle(NULL);
     App_Lcd_TimerStop();
}

void UI_Screen_SwimModeCountDown_shortkeyhandle(void)
{

    //UI_Screen_SwimModeCountDown_Exit();
    //UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
    //UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeCountDown_holdshortkeyhandle(void)
{
}

void UI_Screen_SwimModeCountDown_holdlongkeyhandle(void)
{
}

void UI_Screen_SwimModeCountDown_tpclickhandle(int point_x,int point_y)
{


    
}

void UI_Screen_SwimModeCountDown_tpupslidehandle(void)
{


}

void UI_Screen_SwimModeCountDown_tpdownslidehandle(void)
{
}

void UI_Screen_SwimModeCountDown_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModeCountDown_tprightslidehandle(void)
{

    UI_Screen_SwimModeCountDown_Exit();
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
    UI_Screen_draw_Screen();

}


Struct_swimmode_setting swimmode_setting_info;

void UI_Screen_SwimModeSetting_Init(void)
{


    swimmode_setting_info.target_type = Enum_swimmode_setting_target_off;
    swimmode_setting_info.target_laps = 0;
    swimmode_setting_info.target_duration = 0;
    swimmode_setting_info.target_calorie = 0;

	swimmode_setting_info.target_index = 0;
    
    swimmode_setting_info.warn_laps = 0;
    swimmode_setting_info.warn_duration = 0;
    swimmode_setting_info.warn_calorie = 0;

    swimmode_setting_info.warn_laps_index = 0;
    swimmode_setting_info.warn_duration_index = 0;
    swimmode_setting_info.warn_calorie_index = 0;

    swimmode_setting_info.pool_length = 2500;
        
}

void UI_Screen_SwimModeSetting_Getsetting(Struct_swimmode_setting *info)
{

    memcpy(info, &swimmode_setting_info, sizeof(Struct_swimmode_setting));

}



void UI_Screen_SwimModeSetting_Entry(void)
{


    UI_Screen_SwimModeSetting_Display();
    
    UI_Common_set_key_handle(UI_Screen_SwimModeSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SwimModeSetting_tpclickhandle);
    
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModeSetting_tpupslidehandle,
                                    UI_Screen_SwimModeSetting_tpdownslidehandle,
                                    UI_Screen_SwimModeSetting_tpleftslidehandle,
                                    UI_Screen_SwimModeSetting_tprightslidehandle);
    
}


void UI_Screen_SwimModeSetting_Display(void)
{

    uint8_t* fontinfo = NULL;
    int fontinfo_type = 0;
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_Setting)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    

    if(swimmode_setting_info.target_type == Enum_swimmode_setting_target_off)
    {
        fontinfo = (uint8_t*)gchinesefont_sportscene_turnoff_s;
        fontinfo_type = 0;
    }
    else if(swimmode_setting_info.target_type == Enum_swimmode_setting_target_laps)
    {
        #if 0
        typedef enum
        {
            ENUM_SMLAPS_TARGET_4 = 0,
            ENUM_SMLAPS_TARGET_8,
            ENUM_SMLAPS_TARGET_10,
            ENUM_SMLAPS_TARGET_12,
            ENUM_SMLAPS_TARGET_16,         //hmarathon21.1
            ENUM_SMLAPS_TARGET_20,          //marathon42.2
            ENUM_SMLAPS_TARGET_32,
            ENUM_SMLAPS_TARGET_40,
            ENUM_SMLAPS_TARGET_MAX,
        }app_swimmodelapstarget_enum;
        #endif
    
        switch(swimmode_setting_info.target_laps)
        {

            
            case 4:
                fontinfo = (uint8_t *)swimmode_lapstarget_4;
                fontinfo_type = 1;
            break;
            case 8:
                fontinfo = (uint8_t *)swimmode_lapstarget_8;
                fontinfo_type = 1;
            break;
            case 10:
                fontinfo = (uint8_t *)swimmode_lapstarget_10;
                fontinfo_type = 1;
            break;
            case 12:
                fontinfo = (uint8_t *)swimmode_lapstarget_12;
                fontinfo_type = 1;
            break;
            case 16:
                fontinfo = (uint8_t *)swimmode_lapstarget_16;
                fontinfo_type = 1;
            break;
            case 20:
                fontinfo = (uint8_t *)swimmode_lapstarget_20;
                fontinfo_type = 1;
            break;
            case 32:
                fontinfo = (uint8_t *)swimmode_lapstarget_32;
                fontinfo_type = 1;
            break;
            case 40:
                fontinfo = (uint8_t *)swimmode_lapstarget_40;
                fontinfo_type = 1;
            break;
            default:
            break;
        }
    }
    else if(swimmode_setting_info.target_type == Enum_swimmode_setting_target_duration)
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
        
        switch(swimmode_setting_info.target_duration)
        {

            case 20:
                fontinfo = (uint8_t *)swimmode_durationtarget_20min;
                fontinfo_type = 1;
            break;
            case 30:
                fontinfo = (uint8_t *)swimmode_durationtarget_30min;
                fontinfo_type = 1;
            break;
            case 60:
                fontinfo = (uint8_t *)swimmode_durationtarget_60min;
                fontinfo_type = 1;
            break;
            case 90:
                fontinfo = (uint8_t *)swimmode_durationtarget_90min;
                fontinfo_type = 1;
            break;
            case 120:
                fontinfo = (uint8_t *)swimmode_durationtarget_120min;
                fontinfo_type = 1;
            break;
            case 180:
                fontinfo = (uint8_t *)swimmode_durationtarget_180min;
                fontinfo_type = 1;
            break;
            case 240:
                fontinfo = (uint8_t *)swimmode_durationtarget_240min;
                fontinfo_type = 1;
            break;            
            default:
            break;


        
        }
    }
    else if(swimmode_setting_info.target_type == Enum_swimmode_setting_target_calorie)
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
        
        switch(swimmode_setting_info.target_calorie)
        {

            case 100:
                fontinfo = (uint8_t *)swimmode_durationtarget_100kcal;
                fontinfo_type = 1;
            break;
            case 200:
                fontinfo = (uint8_t *)swimmode_durationtarget_200kcal;
                fontinfo_type = 1;
            break;
            case 300:
                fontinfo = (uint8_t *)swimmode_durationtarget_300kcal;
                fontinfo_type = 1;
            break;
            case 500:
                fontinfo = (uint8_t *)swimmode_durationtarget_500kcal;
                fontinfo_type = 1;
            break;
            case 800:
                fontinfo = (uint8_t *)swimmode_durationtarget_800kcal;
                fontinfo_type = 1;
            break;
            case 1000:
                fontinfo = (uint8_t *)swimmode_durationtarget_1000kcal;
                fontinfo_type = 1;
            break;
            
            default:
            break;
        
        }
    }
    
    UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t*)gchinesefont_sportscene_target,(uint8_t*)fontinfo,NULL,fontinfo_type);
    
    UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t*)gchinesefont_sportscene_warn,(uint8_t*)NULL,NULL,0);


    switch(swimmode_setting_info.pool_length)
    {

        case 2500:
            fontinfo = (uint8_t *)swimmode_pooll_25m;
            fontinfo_type = 1;
        break;
        case 5000:
            fontinfo = (uint8_t *)swimmode_pooll_50m;
            fontinfo_type = 1;
        break;
        case 3333:
            fontinfo = (uint8_t *)swimmode_pooll_33m;
            fontinfo_type = 1;
        break;
        case 2286:
            fontinfo = (uint8_t *)swimmode_pooll_25yd;
            fontinfo_type = 1;
        break;
        case 3045:
            fontinfo = (uint8_t *)swimmode_pooll_33yd;
            fontinfo_type = 1;
        break;
        default:
        break;
    
    }
    
    UI_Common_List_RarrowDoubleline(temp_ram,0,118,(uint8_t*)gchinesefont_sportscene_Pooll,fontinfo,NULL,fontinfo_type);

    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_SwimModeSetting_Exit(void)
{
}


void UI_Screen_SwimModeSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_SwimModeSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_SwimModeSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_TargetSetting);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
            UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_PoolLength);
            UI_Screen_draw_Screen();
        }
        break;
        default:
        break;
    }

    
}


void UI_Screen_SwimModeSetting_tpupslidehandle(void)
{
}

void UI_Screen_SwimModeSetting_tpdownslidehandle(void)
{
}

void UI_Screen_SwimModeSetting_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModeSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
    UI_Screen_draw_Screen();

}


// target 

static int targetsetting_page_number = 0;

void UI_Screen_SwimModeTargetSetting_Entry(void)
{


    UI_Screen_SwimModeTargetSetting_Display();

    UI_Common_set_key_handle(UI_Screen_SwimModeSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SwimModeTargetSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModeTargetSetting_tpupslidehandle,
                                    UI_Screen_SwimModeTargetSetting_tpdownslidehandle,
                                    UI_Screen_SwimModeTargetSetting_tpleftslidehandle,
                                    UI_Screen_SwimModeTargetSetting_tprightslidehandle);
    
}

void UI_Screen_SwimModeTargetSetting_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_TargetSetting)
        return;
    
    UI_Common_Clear_Screen(temp_ram);

    if(targetsetting_page_number == 0)
    {
        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t*)gchinesefont_sportscene_target_notarget,(uint8_t*)NULL,NULL,0);
        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t*)gchinesefont_sportscene_target_laps,(uint8_t*)NULL,NULL,0);
        UI_Common_List_RarrowDoubleline(temp_ram,0,118,(uint8_t*)gchinesefont_sportscene_target_duration,(uint8_t*)NULL,NULL,0);
    }
    else
    {
        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t*)gchinesefont_sportscene_target_calorie,(uint8_t*)NULL,NULL,0);
    }

    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_SwimModeTargetSetting_Exit(void)
{

    targetsetting_page_number =0;

}

void UI_Screen_SwimModeTargetSetting_shortkeyhandle(void)
{

    UI_Screen_SwimModeTargetSetting_Exit();

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeTargetSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_SwimModeTargetSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_SwimModeDistanceTargetSetting_None(void)
{

    swimmode_setting_info.target_type = Enum_swimmode_setting_target_off;
    swimmode_setting_info.warn_laps = 0;
    swimmode_setting_info.target_duration = 0;
    swimmode_setting_info.target_calorie = 0;

}


void UI_Screen_SwimModeTargetSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(targetsetting_page_number == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
            
                UI_Screen_SwimModeDistanceTargetSetting_None();
                UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
                UI_Screen_draw_Screen();
                
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_TargetSetting_Laps);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_TargetSetting_Duration);
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
                UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_TargetSetting_Calorie);
                UI_Screen_draw_Screen();
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


void UI_Screen_SwimModeTargetSetting_tpupslidehandle(void)
{
    if(targetsetting_page_number ==0)
    {
        targetsetting_page_number =1;
    }
    else
    {
        targetsetting_page_number =0;
    }

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_TargetSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeTargetSetting_tpdownslidehandle(void)
{
    if(targetsetting_page_number ==0)
    {
        targetsetting_page_number =1;
    }
    else
    {
        targetsetting_page_number =0;
    }

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_TargetSetting);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeTargetSetting_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModeTargetSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();

}




void UI_Screen_SwimModeLapsTargetSetting_Entry(void)
{
    int i = 0;
        
    UI_Common_ScreenCleanListInfo();

    curr_list.total_count = ENUM_SMLAPS_TARGET_MAX;
    curr_list.total_list_page_count = (ENUM_SMLAPS_TARGET_MAX+2)/3;

    for(i = 0;i<ENUM_SMLAPS_TARGET_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }

    if(swimmode_setting_info.target_type == Enum_swimmode_setting_target_laps)
    {
        curr_list.icon_list[swimmode_setting_info.target_index]=(uint8_t *)radiobtn_checked_h;
    }
    

    curr_list.string_list[ENUM_SMLAPS_TARGET_4]=(uint8_t *)gchinesefont_sportscene_4;
    curr_list.string_list[ENUM_SMLAPS_TARGET_8]=(uint8_t *)gchinesefont_sportscene_8;
    curr_list.string_list[ENUM_SMLAPS_TARGET_10]=(uint8_t *)gchinesefont_sportscene_10;
    curr_list.string_list[ENUM_SMLAPS_TARGET_12]=(uint8_t *)gchinesefont_sportscene_12;
    curr_list.string_list[ENUM_SMLAPS_TARGET_16]=(uint8_t *)gchinesefont_sportscene_16;
    curr_list.string_list[ENUM_SMLAPS_TARGET_20]=(uint8_t *)gchinesefont_sportscene_20;
    curr_list.string_list[ENUM_SMLAPS_TARGET_32]=(uint8_t *)gchinesefont_sportscene_32;
    curr_list.string_list[ENUM_SMLAPS_TARGET_40]=(uint8_t *)gchinesefont_sportscene_40;
    
    
    UI_Screen_SwimModeLapsTargetSetting_Display();

    UI_Common_set_key_handle(UI_Screen_SwimModeLapsTargetSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SwimModeLapsTargetSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModeLapsTargetSetting_tpupslidehandle,
                                    UI_Screen_SwimModeLapsTargetSetting_tpdownslidehandle,
                                    UI_Screen_SwimModeLapsTargetSetting_tpleftslidehandle,
                                    UI_Screen_SwimModeLapsTargetSetting_tprightslidehandle);


    
    
}

void UI_Screen_SwimModeLapsTargetSetting_Display(void)
{
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_TargetSetting_Laps)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
}

void UI_Screen_SwimModeLapsTargetSetting_Exit(void)
{


}

void UI_Screen_SwimModeLapsTargetSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeLapsTargetSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_SwimModeLapsTargetSetting_holdlongkeyhandle(void)
{
}




void UI_Screen_SwimModeLapsTargetSetting_4(void)
{

    swimmode_setting_info.target_type = Enum_swimmode_setting_target_laps;
    swimmode_setting_info.target_laps = 4;
    swimmode_setting_info.target_duration = 0;
    swimmode_setting_info.target_calorie = 0;

    swimmode_setting_info.target_index = ENUM_SMLAPS_TARGET_4;
    
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeLapsTargetSetting_8(void)
{

    swimmode_setting_info.target_type = Enum_swimmode_setting_target_laps;
    swimmode_setting_info.target_laps = 8;
    swimmode_setting_info.target_duration = 0;
    swimmode_setting_info.target_calorie = 0;

    swimmode_setting_info.target_index = ENUM_SMLAPS_TARGET_8;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeLapsTargetSetting_10(void)
{
    
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_laps;
    swimmode_setting_info.target_laps = 10;
    swimmode_setting_info.target_duration = 0;
    swimmode_setting_info.target_calorie = 0;

    swimmode_setting_info.target_index = ENUM_SMLAPS_TARGET_10;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeLapsTargetSetting_12(void)
{
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_laps;
    swimmode_setting_info.target_laps = 12;
    swimmode_setting_info.target_duration = 0;
    swimmode_setting_info.target_calorie = 0;

    swimmode_setting_info.target_index = ENUM_SMLAPS_TARGET_12;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeLapsTargetSetting_16(void)
{
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_laps;
    swimmode_setting_info.target_laps = 16;
    swimmode_setting_info.target_duration = 0;
    swimmode_setting_info.target_calorie = 0;

    swimmode_setting_info.target_index = ENUM_SMLAPS_TARGET_16;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeLapsTargetSetting_20(void)
{
    
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_laps;
    swimmode_setting_info.target_laps = 20;
    swimmode_setting_info.target_duration = 0;
    swimmode_setting_info.target_calorie = 0;

    swimmode_setting_info.target_index = ENUM_SMLAPS_TARGET_20;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeLapsTargetSetting_32(void)
{
    
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_laps;
    swimmode_setting_info.target_laps = 32;
    swimmode_setting_info.target_duration = 0;
    swimmode_setting_info.target_calorie = 0;

    swimmode_setting_info.target_index = ENUM_SMLAPS_TARGET_32;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeLapsTargetSetting_40(void)
{
    
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_laps;
    swimmode_setting_info.target_laps = 40;
    swimmode_setting_info.target_duration = 0;
    swimmode_setting_info.target_calorie = 0;

    swimmode_setting_info.target_index = ENUM_SMLAPS_TARGET_40;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}


void UI_Screen_SwimModeLapsTargetSetting_tpclickhandle(int point_x,int point_y)
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
                UI_Screen_SwimModeLapsTargetSetting_4();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_SwimModeLapsTargetSetting_8();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_SwimModeLapsTargetSetting_10();
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
                UI_Screen_SwimModeLapsTargetSetting_12();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                UI_Screen_SwimModeLapsTargetSetting_16();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
            
                UI_Screen_SwimModeLapsTargetSetting_20();
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
            
                UI_Screen_SwimModeLapsTargetSetting_32();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                        
                UI_Screen_SwimModeLapsTargetSetting_40();
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


void UI_Screen_SwimModeLapsTargetSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_SwimModeLapsTargetSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_SwimModeLapsTargetSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_SwimModeLapsTargetSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_SwimModeLapsTargetSetting_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModeLapsTargetSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_TargetSetting);
    UI_Screen_draw_Screen();

}


void UI_Screen_SwimModeDurationTargetSetting_Entry(void)
{

    int i = 0;

    
    UI_Common_ScreenCleanListInfo();

    curr_list.total_count = ENUM_SMDURATION_TARGET_MAX;
    curr_list.total_list_page_count = (ENUM_SMDURATION_TARGET_MAX+2)/3;

    for(i = 0;i<ENUM_SMDURATION_TARGET_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    if(swimmode_setting_info.target_type == Enum_swimmode_setting_target_duration)
    {
        curr_list.icon_list[swimmode_setting_info.target_index]=(uint8_t *)radiobtn_checked_h;
    }

    curr_list.string_list[ENUM_SMDURATION_TARGET_20MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_20min;
    curr_list.string_list[ENUM_SMDURATION_TARGET_30MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_30min;
    curr_list.string_list[ENUM_SMDURATION_TARGET_60MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_60min;
    curr_list.string_list[ENUM_SMDURATION_TARGET_90MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_90min;
    curr_list.string_list[ENUM_SMDURATION_TARGET_120MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_120min;
    curr_list.string_list[ENUM_SMDURATION_TARGET_180MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_180min;
    curr_list.string_list[ENUM_SMDURATION_TARGET_240MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_240min;

    UI_Screen_SwimModeDurationTargetSetting_Display();

    UI_Common_set_key_handle(UI_Screen_SwimModeDurationTargetSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SwimModeDurationTargetSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModeDurationTargetSetting_tpupslidehandle,
                                    UI_Screen_SwimModeDurationTargetSetting_tpdownslidehandle,
                                    UI_Screen_SwimModeDurationTargetSetting_tpleftslidehandle,
                                    UI_Screen_SwimModeDurationTargetSetting_tprightslidehandle);
    
}

void UI_Screen_SwimModeDurationTargetSetting_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_TargetSetting_Duration)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_SwimModeDurationTargetSetting_Exit(void)
{


}

void UI_Screen_SwimModeDurationTargetSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeDurationTargetSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_SwimModeDurationTargetSetting_holdlongkeyhandle(void)
{
}


void UI_Screen_SwimModeDurationTargetSetting_20MIN(void)
{
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_duration;
    swimmode_setting_info.target_laps = 0;
    swimmode_setting_info.target_duration = 20;
    swimmode_setting_info.target_calorie = 0;

    swimmode_setting_info.target_index = ENUM_SMDURATION_TARGET_20MIN;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeDurationTargetSetting_30MIN(void)
{
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_duration;
    swimmode_setting_info.target_laps = 0;
    swimmode_setting_info.target_duration = 30;
    swimmode_setting_info.target_calorie = 0;

    swimmode_setting_info.target_index = ENUM_SMDURATION_TARGET_30MIN;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_SwimModeDurationTargetSetting_60MIN(void)
{
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_duration;
    swimmode_setting_info.target_laps = 0;
    swimmode_setting_info.target_duration = 60;
    swimmode_setting_info.target_calorie = 0;

    swimmode_setting_info.target_index = ENUM_SMDURATION_TARGET_60MIN;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_SwimModeDurationTargetSetting_90MIN(void)
{
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_duration;
    swimmode_setting_info.target_laps = 0;
    swimmode_setting_info.target_duration = 90;
    swimmode_setting_info.target_calorie = 0;

    swimmode_setting_info.target_index = ENUM_SMDURATION_TARGET_90MIN;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_SwimModeDurationTargetSetting_120MIN(void)
{
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_duration;
    swimmode_setting_info.target_laps = 0;
    swimmode_setting_info.target_duration = 120;
    swimmode_setting_info.target_calorie = 0;

    swimmode_setting_info.target_index = ENUM_SMDURATION_TARGET_120MIN;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_SwimModeDurationTargetSetting_180MIN(void)
{
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_duration;
    swimmode_setting_info.target_laps = 0;
    swimmode_setting_info.target_duration = 180;
    swimmode_setting_info.target_calorie = 0;

    swimmode_setting_info.target_index = ENUM_SMDURATION_TARGET_180MIN;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_SwimModeDurationTargetSetting_240MIN(void)
{
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_duration;
    swimmode_setting_info.target_laps = 0;
    swimmode_setting_info.target_duration = 240;
    swimmode_setting_info.target_calorie = 0;

    swimmode_setting_info.target_index = ENUM_SMDURATION_TARGET_240MIN;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_SwimModeDurationTargetSetting_tpclickhandle(int point_x,int point_y)
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
            UI_Screen_SwimModeDurationTargetSetting_20MIN();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Screen_SwimModeDurationTargetSetting_30MIN();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
            UI_Screen_SwimModeDurationTargetSetting_60MIN();
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
            UI_Screen_SwimModeDurationTargetSetting_90MIN();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Screen_SwimModeDurationTargetSetting_120MIN();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
            UI_Screen_SwimModeDurationTargetSetting_180MIN();
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
            UI_Screen_SwimModeDurationTargetSetting_240MIN();
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


void UI_Screen_SwimModeDurationTargetSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_SwimModeDurationTargetSetting_Display();
    UI_Screen_Redraw_Screen();

}


void UI_Screen_SwimModeDurationTargetSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_SwimModeDurationTargetSetting_Display();
    UI_Screen_Redraw_Screen();

}


void UI_Screen_SwimModeDurationTargetSetting_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModeDurationTargetSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_TargetSetting);
    UI_Screen_draw_Screen();

}


    
void UI_Screen_SwimModeCalorieTargetSetting_Entry(void)
{

    int i = 0;



    UI_Common_ScreenCleanListInfo();

    curr_list.total_count = ENUM_SMCALORIE_TARGET_MAX;
    curr_list.total_list_page_count = (ENUM_SMCALORIE_TARGET_MAX+2)/3;

    for(i = 0;i<ENUM_SMCALORIE_TARGET_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    if(swimmode_setting_info.target_type == Enum_swimmode_setting_target_calorie)
    {
        curr_list.icon_list[swimmode_setting_info.target_index]=(uint8_t *)radiobtn_checked_h;
    }

    curr_list.string_list[ENUM_SMCALORIE_TARGET_100KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_100kcal;
    curr_list.string_list[ENUM_SMCALORIE_TARGET_200KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_200kcal;
    curr_list.string_list[ENUM_SMCALORIE_TARGET_300KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_300kcal;
    curr_list.string_list[ENUM_SMCALORIE_TARGET_500KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_500kcal;
    curr_list.string_list[ENUM_SMCALORIE_TARGET_800KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_800kcal;
    curr_list.string_list[ENUM_SMCALORIE_TARGET_1000KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_1000kcal;

    UI_Screen_SwimModeCalorieTargetSetting_Display();

    UI_Common_set_key_handle(UI_Screen_SwimModeCalorieTargetSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SwimModeCalorieTargetSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModeCalorieTargetSetting_tpupslidehandle,
                                    UI_Screen_SwimModeCalorieTargetSetting_tpdownslidehandle,
                                    UI_Screen_SwimModeCalorieTargetSetting_tpleftslidehandle,
                                    UI_Screen_SwimModeCalorieTargetSetting_tprightslidehandle);
    
}

void UI_Screen_SwimModeCalorieTargetSetting_Display(void)
{
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_TargetSetting_Calorie)
        return;
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_SwimModeCalorieTargetSetting_Exit(void)
{
}

void UI_Screen_SwimModeCalorieTargetSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeCalorieTargetSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_SwimModeCalorieTargetSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_SwimModeCalorieTargetSetting_100KCAL(void)
{
    
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_calorie;
    swimmode_setting_info.target_laps = 0;
    swimmode_setting_info.target_duration = 0;
    swimmode_setting_info.target_calorie = 100;

    swimmode_setting_info.target_index = ENUM_SMCALORIE_TARGET_100KCAL;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeCalorieTargetSetting_200KCAL(void)
{
    
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_calorie;
    swimmode_setting_info.target_laps = 0;
    swimmode_setting_info.target_duration = 0;
    swimmode_setting_info.target_calorie = 200;

    swimmode_setting_info.target_index = ENUM_SMCALORIE_TARGET_200KCAL;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeCalorieTargetSetting_300KCAL(void)
{
    
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_calorie;
    swimmode_setting_info.target_laps = 0;
    swimmode_setting_info.target_duration = 0;
    swimmode_setting_info.target_calorie = 300;

    swimmode_setting_info.target_index = ENUM_SMCALORIE_TARGET_300KCAL;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeCalorieTargetSetting_500KCAL(void)
{
    
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_calorie;
    swimmode_setting_info.target_laps = 0;
    swimmode_setting_info.target_duration = 0;
    swimmode_setting_info.target_calorie = 500;

    swimmode_setting_info.target_index = ENUM_SMCALORIE_TARGET_500KCAL;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeCalorieTargetSetting_800KCAL(void)
{
    
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_calorie;
    swimmode_setting_info.target_laps = 0;
    swimmode_setting_info.target_duration = 0;
    swimmode_setting_info.target_calorie = 800;

    swimmode_setting_info.target_index = ENUM_SMCALORIE_TARGET_800KCAL;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeCalorieTargetSetting_1000KCAL(void)
{
    
    swimmode_setting_info.target_type = Enum_swimmode_setting_target_calorie;
    swimmode_setting_info.target_laps = 0;
    swimmode_setting_info.target_duration = 0;
    swimmode_setting_info.target_calorie = 1000;

    swimmode_setting_info.target_index = ENUM_SMCALORIE_TARGET_1000KCAL;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}


void UI_Screen_SwimModeCalorieTargetSetting_tpclickhandle(int point_x,int point_y)
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
                UI_Screen_SwimModeCalorieTargetSetting_100KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_SwimModeCalorieTargetSetting_200KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_SwimModeCalorieTargetSetting_300KCAL();
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
                UI_Screen_SwimModeCalorieTargetSetting_500KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_SwimModeCalorieTargetSetting_800KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_SwimModeCalorieTargetSetting_1000KCAL();
            }
            break;
            default:
            break;
        }
    }

    
}

void UI_Screen_SwimModeCalorieTargetSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_SwimModeCalorieTargetSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_SwimModeCalorieTargetSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_SwimModeCalorieTargetSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_SwimModeCalorieTargetSetting_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModeCalorieTargetSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_TargetSetting);
    UI_Screen_draw_Screen();

}


void UI_Screen_SwimModeWarnSetting_Entry(void)
{

    UI_Screen_SwimModeWarnSetting_Display();
    
    UI_Common_set_key_handle(UI_Screen_SwimModeWarnSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SwimModeWarnSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModeWarnSetting_tpupslidehandle,
                                    UI_Screen_SwimModeWarnSetting_tpdownslidehandle,
                                    UI_Screen_SwimModeWarnSetting_tpleftslidehandle,
                                    UI_Screen_SwimModeWarnSetting_tprightslidehandle);
    
}


void UI_Screen_SwimModeWarnSetting_Display(void)
{


        uint8_t* fontinfo = NULL;
        char* fontinfo_string = NULL;
        int fontinfo_type = 0;
        

        uint8_t *temp_ram = UI_Display_Get_Tempram();
        
        if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_WarnSetting)
            return;
        UI_Common_Clear_Screen(temp_ram);

        switch(swimmode_setting_info.warn_laps)
        {
            case 0:
                fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                fontinfo_string = NULL;
                fontinfo_type = 0;
            break;
            case 4:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_lapswarn_4;
                fontinfo_type = 2;
            break;
            case 8:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_lapswarn_8;
                fontinfo_type = 2;
            break;
            case 10:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_lapswarn_10;
                fontinfo_type = 2;
            break;
            case 12:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_lapswarn_12;
                fontinfo_type = 2;
            break;
            case 16:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_lapswarn_16;
                fontinfo_type = 2;
            break;
            case 20:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_lapswarn_20;
                fontinfo_type = 2;
            break;
            default:
            break;
        }

        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_target_laps,(uint8_t *)fontinfo,(uint8_t *)fontinfo_string,fontinfo_type);

        switch(swimmode_setting_info.warn_duration)
        {
            case 0:
                fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                fontinfo_string = NULL;
                fontinfo_type = 0;
            break;
            case 5:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_durationwarn_5min;
                fontinfo_type = 2;
            break;
            case 10:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_durationwarn_10min;
                fontinfo_type = 2;
            break;
            case 15:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_durationwarn_15min;
                fontinfo_type = 2;
            break;
            case 20:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_durationwarn_20min;
                fontinfo_type = 2;
            break;
            case 30:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_durationwarn_30min;
                fontinfo_type = 2;
            break;
            case 60:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_durationwarn_60min;
                fontinfo_type = 2;
            break;
            case 90:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_durationwarn_90min;
                fontinfo_type = 2;
            break;
            case 120:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_durationwarn_120min;
                fontinfo_type = 2;
            break;
            default:
            break;
        }
        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_target_duration,(uint8_t *)fontinfo,(uint8_t *)fontinfo_string,fontinfo_type);
        switch(swimmode_setting_info.warn_calorie)
        {
            case 0:
                fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                fontinfo_string =   NULL;
                fontinfo_type = 0;
            break;
            case 50:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_caloriewarn_50kcal;
                fontinfo_type = 2;
            break;
            case 100:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_caloriewarn_100kcal;
                fontinfo_type = 2;
            break;
            case 150:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_caloriewarn_150kcal;
                fontinfo_type = 2;
                fontinfo = (uint8_t *)gchinesefont_sportscene_warn_calorie_150kcal_s;
            break;
            case 200:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = swimmode_caloriewarn_200kcal;
                fontinfo_type = 2;
            break;
            default:
            break;
        }
        UI_Common_List_RarrowDoubleline(temp_ram,0,118,(uint8_t *)gchinesefont_sportscene_target_calorie,(uint8_t *)fontinfo,(uint8_t *)fontinfo_string,fontinfo_type);
        
        UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_SwimModeWarnSetting_Exit(void)
{


}


void UI_Screen_SwimModeWarnSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeWarnSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_SwimModeWarnSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_SwimModeWarnSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting_Laps);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting_Duration);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting_Calorie);
                UI_Screen_draw_Screen();
            }
            break;
            default:
            break;
        }
    


}


void UI_Screen_SwimModeWarnSetting_tpupslidehandle(void)
{


    
}


void UI_Screen_SwimModeWarnSetting_tpdownslidehandle(void)
{


}


void UI_Screen_SwimModeWarnSetting_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModeWarnSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();

}



void UI_Screen_SwimModeLapsWarnSetting_Entry(void)
{
    int i = 0;
        
    UI_Common_ScreenCleanListInfo();

    curr_list.total_count = ENUM_SMLAPS_WARN_MAX;
    curr_list.total_list_page_count = (ENUM_SMLAPS_WARN_MAX+2)/3;

    for(i = 0;i<ENUM_SMLAPS_WARN_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    curr_list.icon_list[swimmode_setting_info.warn_laps_index]=(uint8_t *)radiobtn_checked_h;

    curr_list.string_list[ENUM_SMLAPS_WARN_OFF]=(uint8_t *)gchinesefont_sportscene_turnoff;
    curr_list.string_list[ENUM_SMLAPS_WARN_4]=(uint8_t *)gchinesefont_sportscene_4;
    curr_list.string_list[ENUM_SMLAPS_WARN_8]=(uint8_t *)gchinesefont_sportscene_8;
    curr_list.string_list[ENUM_SMLAPS_WARN_10]=(uint8_t *)gchinesefont_sportscene_10;
    curr_list.string_list[ENUM_SMLAPS_WARN_12]=(uint8_t *)gchinesefont_sportscene_12;
    curr_list.string_list[ENUM_SMLAPS_WARN_16]=(uint8_t *)gchinesefont_sportscene_16;
    curr_list.string_list[ENUM_SMLAPS_WARN_20]=(uint8_t *)gchinesefont_sportscene_20;
    
    UI_Screen_SwimModeLapsWarnSetting_Display();

    UI_Common_set_key_handle(UI_Screen_SwimModeLapsWarnSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SwimModeLapsWarnSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModeLapsWarnSetting_tpupslidehandle,
                                    UI_Screen_SwimModeLapsWarnSetting_tpdownslidehandle,
                                    UI_Screen_SwimModeLapsWarnSetting_tpleftslidehandle,
                                    UI_Screen_SwimModeLapsWarnSetting_tprightslidehandle);


    
    
}

void UI_Screen_SwimModeLapsWarnSetting_Display(void)
{
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_WarnSetting_Laps)
        return;
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_SwimModeLapsWarnSetting_Exit(void)
{


}

void UI_Screen_SwimModeLapsWarnSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeLapsWarnSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_SwimModeLapsWarnSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_SwimModeLapsWarnSetting_Off(void)
{

    swimmode_setting_info.warn_laps = 0;
    swimmode_setting_info.warn_laps_index = ENUM_SMLAPS_WARN_OFF;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}


void UI_Screen_SwimModeLapsWarnSetting_4(void)
{

    swimmode_setting_info.warn_laps = 4;
    swimmode_setting_info.warn_laps_index = ENUM_SMLAPS_WARN_4;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeLapsWarnSetting_8(void)
{

    swimmode_setting_info.warn_laps = 8;
    swimmode_setting_info.warn_laps_index = ENUM_SMLAPS_WARN_8;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeLapsWarnSetting_10(void)
{

    swimmode_setting_info.warn_laps = 10;
    swimmode_setting_info.warn_laps_index = ENUM_SMLAPS_WARN_10;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeLapsWarnSetting_12(void)
{

    swimmode_setting_info.warn_laps = 12;
    swimmode_setting_info.warn_laps_index = ENUM_SMLAPS_WARN_12;
    
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeLapsWarnSetting_16(void)
{

    swimmode_setting_info.warn_laps = 16;
    swimmode_setting_info.warn_laps_index = ENUM_SMLAPS_WARN_16;
    
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeLapsWarnSetting_20(void)
{

    swimmode_setting_info.warn_laps = 20;
    swimmode_setting_info.warn_laps_index = ENUM_SMLAPS_WARN_20;
    
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeLapsWarnSetting_tpclickhandle(int point_x,int point_y)
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
                UI_Screen_SwimModeLapsWarnSetting_Off();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_SwimModeLapsWarnSetting_4();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_SwimModeLapsWarnSetting_8();
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
                UI_Screen_SwimModeLapsWarnSetting_10();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                UI_Screen_SwimModeLapsWarnSetting_12();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
            
                UI_Screen_SwimModeLapsWarnSetting_16();
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
                UI_Screen_SwimModeLapsWarnSetting_20();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
            
            }
            break;
            default:
            break;
        }
    }
    
}


void UI_Screen_SwimModeLapsWarnSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_SwimModeLapsWarnSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_SwimModeLapsWarnSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_SwimModeLapsWarnSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_SwimModeLapsWarnSetting_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModeLapsWarnSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();

}



void UI_Screen_SwimModeDurationWarnSetting_Entry(void)
{
    int i = 0;
    
    UI_Common_ScreenCleanListInfo();

    curr_list.total_count = ENUM_SMDURATION_WARN_MAX;
    curr_list.total_list_page_count = (ENUM_SMDURATION_WARN_MAX+2)/3;

    for(i = 0;i<ENUM_SMDURATION_WARN_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    curr_list.icon_list[swimmode_setting_info.warn_duration_index]=(uint8_t *)radiobtn_checked_h;

    curr_list.string_list[ENUM_SMDURATION_WARN_OFF]=(uint8_t *)gchinesefont_sportscene_turnoff;
    curr_list.string_list[ENUM_SMDURATION_WARN_5MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_5min;
    curr_list.string_list[ENUM_SMDURATION_WARN_10MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_10min;
    curr_list.string_list[ENUM_SMDURATION_WARN_15MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_15min;
    curr_list.string_list[ENUM_SMDURATION_WARN_20MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_20min;
    curr_list.string_list[ENUM_SMDURATION_WARN_30MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_30min;
    curr_list.string_list[ENUM_SMDURATION_WARN_60MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_60min;
    curr_list.string_list[ENUM_SMDURATION_WARN_90MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_90min;
    curr_list.string_list[ENUM_SMDURATION_WARN_120MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_120min;
    
    UI_Screen_SwimModeDurationWarnSetting_Display();

    UI_Common_set_key_handle(UI_Screen_SwimModeDurationWarnSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SwimModeDurationWarnSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModeDurationWarnSetting_tpupslidehandle,
                                    UI_Screen_SwimModeDurationWarnSetting_tpdownslidehandle,
                                    UI_Screen_SwimModeDurationWarnSetting_tpleftslidehandle,
                                    UI_Screen_SwimModeDurationWarnSetting_tprightslidehandle);


    
    
}

void UI_Screen_SwimModeDurationWarnSetting_Display(void)
{
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_WarnSetting_Duration)
        return;
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_SwimModeDurationWarnSetting_Exit(void)
{


}

void UI_Screen_SwimModeDurationWarnSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeDurationWarnSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_SwimModeDurationWarnSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_SwimModeDurationWarnSetting_Off(void)
{

    swimmode_setting_info.warn_duration = 0;
    swimmode_setting_info.warn_duration_index = ENUM_SMDURATION_WARN_OFF;
    
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}


void UI_Screen_SwimModeDurationWarnSetting_5MIN(void)
{

    swimmode_setting_info.warn_duration = 5;
    swimmode_setting_info.warn_duration_index = ENUM_SMDURATION_WARN_5MIN;
    
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_SwimModeDurationWarnSetting_10MIN(void)
{

    swimmode_setting_info.warn_duration = 10;
    swimmode_setting_info.warn_duration_index = ENUM_SMDURATION_WARN_10MIN;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_SwimModeDurationWarnSetting_15MIN(void)
{

    swimmode_setting_info.warn_duration = 15;
    swimmode_setting_info.warn_duration_index = ENUM_SMDURATION_WARN_15MIN;
    
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_SwimModeDurationWarnSetting_20MIN(void)
{

    swimmode_setting_info.warn_duration = 20;
    swimmode_setting_info.warn_duration_index = ENUM_SMDURATION_WARN_20MIN;
    
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}




void UI_Screen_SwimModeDurationWarnSetting_30MIN(void)
{

    swimmode_setting_info.warn_duration = 30;
    swimmode_setting_info.warn_duration_index = ENUM_SMDURATION_WARN_30MIN;
    
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_SwimModeDurationWarnSetting_60MIN(void)
{

    swimmode_setting_info.warn_duration = 60;

    swimmode_setting_info.warn_duration_index = ENUM_SMDURATION_WARN_60MIN;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_SwimModeDurationWarnSetting_90MIN(void)
{

    swimmode_setting_info.warn_duration = 90;
    swimmode_setting_info.warn_duration_index = ENUM_SMDURATION_WARN_90MIN;
    
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_SwimModeDurationWarnSetting_120MIN(void)
{

    swimmode_setting_info.warn_duration = 120;
    swimmode_setting_info.warn_duration_index = ENUM_SMDURATION_WARN_120MIN;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}




void UI_Screen_SwimModeDurationWarnSetting_tpclickhandle(int point_x,int point_y)
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
                UI_Screen_SwimModeDurationWarnSetting_Off();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_SwimModeDurationWarnSetting_5MIN();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_SwimModeDurationWarnSetting_10MIN();
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
                UI_Screen_SwimModeDurationWarnSetting_15MIN();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                UI_Screen_SwimModeDurationWarnSetting_20MIN();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
            
                UI_Screen_SwimModeDurationWarnSetting_30MIN();
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
                UI_Screen_SwimModeDurationWarnSetting_60MIN();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                UI_Screen_SwimModeDurationWarnSetting_90MIN();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
            
                UI_Screen_SwimModeDurationWarnSetting_120MIN();
            }
            break;
            default:
            break;
        }
    }

    
}


void UI_Screen_SwimModeDurationWarnSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_SwimModeDurationWarnSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_SwimModeDurationWarnSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_SwimModeDurationWarnSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_SwimModeDurationWarnSetting_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModeDurationWarnSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();

}



    
void UI_Screen_SwimModeCalorieWarnSetting_Entry(void)
{

    int i = 0;

    UI_Common_ScreenCleanListInfo();


    curr_list.total_count = ENUM_SMCALORIE_WARN_MAX;
    curr_list.total_list_page_count = ENUM_SMCALORIE_WARN_MAX/3+1;

    for(i = 0;i<ENUM_SMCALORIE_WARN_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    curr_list.icon_list[swimmode_setting_info.warn_calorie_index]=(uint8_t *)radiobtn_checked_h;

    curr_list.string_list[ENUM_SMCALORIE_WARN_OFF]=(uint8_t *)gchinesefont_sportscene_turnoff;
    curr_list.string_list[ENUM_SMCALORIE_WARN_50KCAL]=(uint8_t *)gchinesefont_sportscene_warn_calorie_50kcal;
    curr_list.string_list[ENUM_SMCALORIE_WARN_100KCAL]=(uint8_t *)gchinesefont_sportscene_warn_calorie_100kcal;
    curr_list.string_list[ENUM_SMCALORIE_WARN_150KCAL]=(uint8_t *)gchinesefont_sportscene_warn_calorie_150kcal;
    curr_list.string_list[ENUM_SMCALORIE_WARN_200KCAL]=(uint8_t *)gchinesefont_sportscene_warn_calorie_200kcal;

    UI_Screen_SwimModeCalorieWarnSetting_Display();

    UI_Common_set_key_handle(UI_Screen_SwimModeCalorieWarnSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SwimModeCalorieWarnSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModeCalorieWarnSetting_tpupslidehandle,
                                    UI_Screen_SwimModeCalorieWarnSetting_tpdownslidehandle,
                                    UI_Screen_SwimModeCalorieWarnSetting_tpleftslidehandle,
                                    UI_Screen_SwimModeCalorieWarnSetting_tprightslidehandle);
    
}

void UI_Screen_SwimModeCalorieWarnSetting_Display(void)
{
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_WarnSetting_Calorie)
        return;
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
}

void UI_Screen_SwimModeCalorieWarnSetting_Exit(void)
{
}

void UI_Screen_SwimModeCalorieWarnSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeCalorieWarnSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_SwimModeCalorieWarnSetting_holdlongkeyhandle(void)
{
}


void UI_Screen_SwimModeCalorieWarnSetting_Off(void)
{
    
    swimmode_setting_info.warn_calorie = 0;
    swimmode_setting_info.warn_calorie_index = ENUM_SMCALORIE_WARN_OFF;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}


void UI_Screen_SwimModeCalorieWarnSetting_50KCAL(void)
{
    
    swimmode_setting_info.warn_calorie = 50;
    swimmode_setting_info.warn_calorie_index = ENUM_SMCALORIE_WARN_50KCAL;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeCalorieWarnSetting_100KCAL(void)
{
    
    swimmode_setting_info.warn_calorie = 100;
    swimmode_setting_info.warn_calorie_index = ENUM_SMCALORIE_WARN_100KCAL;
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeCalorieWarnSetting_150KCAL(void)
{
    
    swimmode_setting_info.warn_calorie = 150;
    swimmode_setting_info.warn_calorie_index = ENUM_SMCALORIE_WARN_150KCAL;
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModeCalorieWarnSetting_200KCAL(void)
{
    
    swimmode_setting_info.warn_calorie = 200;
    swimmode_setting_info.warn_calorie_index = ENUM_SMCALORIE_WARN_200KCAL;
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_draw_Screen();
}


void UI_Screen_SwimModeCalorieWarnSetting_tpclickhandle(int point_x,int point_y)
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
                UI_Screen_SwimModeCalorieWarnSetting_Off();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_SwimModeCalorieWarnSetting_50KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_SwimModeCalorieWarnSetting_100KCAL();
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
                UI_Screen_SwimModeCalorieWarnSetting_150KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_SwimModeCalorieWarnSetting_200KCAL();
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

void UI_Screen_SwimModeCalorieWarnSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_SwimModeCalorieWarnSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_SwimModeCalorieWarnSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_SwimModeCalorieWarnSetting_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_SwimModeCalorieWarnSetting_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModeCalorieWarnSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_WarnSetting);
    UI_Screen_Redraw_Screen();

}


    
    
void UI_Screen_SwimModePoolLengthSetting_Entry(void)
{

    int i = 0;

    UI_Common_ScreenCleanListInfo();


    curr_list.total_count = ENUM_SMCALORIE_POOLL_MAX;
    curr_list.total_list_page_count = (ENUM_SMCALORIE_POOLL_MAX+2)/3;

    for(i = 0;i<ENUM_SMCALORIE_POOLL_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    curr_list.icon_list[swimmode_setting_info.pool_length_index]=(uint8_t *)radiobtn_checked_h;

    curr_list.string_list[ENUM_SMCALORIE_POOLL_25M]=(uint8_t *)gchinesefont_sportscene_25M;
    curr_list.string_list[ENUM_SMCALORIE_POOLL_50M]=(uint8_t *)gchinesefont_sportscene_50M;
    curr_list.string_list[ENUM_SMCALORIE_POOLL_33M]=(uint8_t *)gchinesefont_sportscene_333M;
    curr_list.string_list[ENUM_SMCALORIE_POOLL_25YD]=(uint8_t *)gchinesefont_sportscene_25YD;
    curr_list.string_list[ENUM_SMCALORIE_POOLL_33YD]=(uint8_t *)gchinesefont_sportscene_333YD;

    UI_Screen_SwimModePoolLengthSetting_Display();

    UI_Common_set_key_handle(UI_Screen_SwimModePoolLengthSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SwimModePoolLengthSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModePoolLengthSetting_tpupslidehandle,
                                    UI_Screen_SwimModePoolLengthSetting_tpdownslidehandle,
                                    UI_Screen_SwimModePoolLengthSetting_tpleftslidehandle,
                                    UI_Screen_SwimModePoolLengthSetting_tprightslidehandle);
    
}

void UI_Screen_SwimModePoolLengthSetting_Display(void)
{
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_PoolLength)
        return;
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
}

void UI_Screen_SwimModePoolLengthSetting_Exit(void)
{
}

void UI_Screen_SwimModePoolLengthSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModePoolLengthSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_SwimModePoolLengthSetting_holdlongkeyhandle(void)
{
}




void UI_Screen_SwimModePoolLengthSetting_25(void)
{
    
    swimmode_setting_info.pool_length = 2500;
    swimmode_setting_info.pool_length_index = ENUM_SMCALORIE_POOLL_25M;
    
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModePoolLengthSetting_50(void)
{
    
    swimmode_setting_info.pool_length = 5000;
    swimmode_setting_info.pool_length_index = ENUM_SMCALORIE_POOLL_50M;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModePoolLengthSetting_333(void)
{
    
    swimmode_setting_info.pool_length = 3333;
    swimmode_setting_info.pool_length_index = ENUM_SMCALORIE_POOLL_33M;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModePoolLengthSetting_25yd(void)
{
    
    swimmode_setting_info.pool_length = 2286;
    swimmode_setting_info.pool_length_index = ENUM_SMCALORIE_POOLL_25YD;
    
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_SwimModePoolLengthSetting_333yd(void)
{
    
    swimmode_setting_info.pool_length = 3045;
    swimmode_setting_info.pool_length_index = ENUM_SMCALORIE_POOLL_33YD;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();
}



void UI_Screen_SwimModePoolLengthSetting_tpclickhandle(int point_x,int point_y)
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
                UI_Screen_SwimModePoolLengthSetting_25();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_SwimModePoolLengthSetting_50();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_SwimModePoolLengthSetting_333();
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
                UI_Screen_SwimModePoolLengthSetting_25yd();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_SwimModePoolLengthSetting_333yd();
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

void UI_Screen_SwimModePoolLengthSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_SwimModePoolLengthSetting_Display();
    //App_Lcd_TimerStart(10);
    UI_Screen_Redraw_Screen();
}

void UI_Screen_SwimModePoolLengthSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page = curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_SwimModePoolLengthSetting_Display();
    //App_Lcd_TimerStart(10);
    UI_Screen_Redraw_Screen();
}

void UI_Screen_SwimModePoolLengthSetting_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModePoolLengthSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Setting);
    UI_Screen_draw_Screen();

}



//page 1 page 2

static int detail_page = 0;


void UI_Screen_SwimModeDetail_Goback()
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Datadetail);
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Swim);
    UI_Screen_draw_Screen();

}


void  UI_Screen_SwimModeDetail_Timerhandle(void)
{

    UI_Screen_SwimModeDetail_Display();

    UI_Common_set_timer_handle(UI_Screen_SwimModeDetail_Timerhandle);
    App_Lcd_TimerStart(1000);

}


void UI_Screen_SwimModeDetail_Entry(void)
{   
    
    
    UI_Screen_SwimModeDetail_Timerhandle();

    UI_Common_set_key_handle(UI_Screen_SwimModeDetail_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SwimModeDetail_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModeDetail_tpupslidehandle,
                                    UI_Screen_SwimModeDetail_tpdownslidehandle,
                                    UI_Screen_SwimModeDetail_tpleftslidehandle,
                                    UI_Screen_SwimModeDetail_tprightslidehandle);
    
    
}

void UI_Screen_SwimModeDetail_Display(void)
{

    swimIndoorInfo_t curr_info;
    int temp_h,temp_m,temp_s;
    char string_content[16];
    int string_len;
    float temp_f;
    int temp_a,temp_b;
    uint8_t *fontinfo;
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
    MID_PRESS_PARA_T* curr_press_info;
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    static int page_control = 0;

    SysTimeType_e curr_type = App_Var_SysTimeTypeGet();
    ui_common_time_12hour_s curr_12hour_time = {0};
    
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_Datadetail)
        return;
    UI_Common_Clear_Screen(temp_ram);

    page_control ++;

    if(page_control>=10000)
        page_control =0;

    if(page_control%5==0)
    {
        if(detail_page == 0)
            detail_page =1;
        else
            detail_page =0;
    }

    

    Scene_Swim_InfoGet(&curr_info);

    if(detail_page==0)
    {
    
        UI_Common_Show_SportModeDataDetailBG(temp_ram,1,1,1);
        //(uint8_t *lcdram,int x,int y,int width,int height,uint8_t *title,char* data,int datalen,uint8_t font_color)

        temp_h = curr_info.RecordData.Duration/3600;
        temp_m = curr_info.RecordData.Duration%3600/60;
        temp_s = curr_info.RecordData.Duration%60;

        sprintf(string_content,"%02d:%02d:%02d",temp_h,temp_m,temp_s);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,0,87,58,gchinesefont_sportscene_datadetail_timing,string_content,string_len,APP_COLOR_WHITE);
        
        sprintf(string_content,"%d",curr_info.RecordData.Distance);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,88,0,87,58,gchinesefont_sportscene_datadetail_distance,string_content,string_len,APP_COLOR_WHITE);

        temp_a = curr_info.RecordData.Laps;
        sprintf(string_content,"%d",curr_info.RecordData.Laps);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,59,87,58,gchinesefont_sportscene_laps,string_content,string_len,APP_COLOR_WHITE);

        //temp_a = curr_info.RecordData.PaceAVG;
        
        temp_a = curr_info.RecordData.PaceAVG/60;
        temp_b = curr_info.RecordData.PaceAVG%60; 
        sprintf(string_content,"%d'%2d\"",temp_a,temp_b);
        //sprintf(string_content,"%d",temp_a);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,88,59,87,58,gchinesefont_sportscene_datadetail_minkm,string_content,string_len,APP_COLOR_WHITE);

        temp_a = curr_info.RecordData.StrokeAVG;
        sprintf(string_content,"%d",temp_a);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,118,87,58,gchinesefont_sportscene_strokecount,string_content,string_len,APP_COLOR_WHITE);

        temp_a = curr_info.RealTimeData.StrokeRate;
        sprintf(string_content,"%d",temp_a);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,88,118,87,58,gchinesefont_sportscene_strokerate,string_content,string_len,APP_COLOR_WHITE);
        
    }
    else
    {
        UI_Common_Show_SportModeDataDetailBG(temp_ram,0,1,0);
        //(uint8_t *lcdram,int x,int y,int width,int height,uint8_t *title,char* data,int datalen,uint8_t font_color)
        
        sprintf(string_content,"%d",curr_info.RecordData.Calorie);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,0,176,58,gchinesefont_sportscene_datadetail_calorie,string_content,string_len,APP_COLOR_WHITE);
    

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
            
            UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,59,87,58,gchinesefont_sportscene_datadetail_currenttime,string_content,string_len,APP_COLOR_WHITE);
        }
        
		
        curr_press_info = Mid_Press_ParamPGet();
        temp_f = (float)curr_press_info->LastTemp/100;
        sprintf(string_content,"%0.1fC",temp_f);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,89,59,87,58,gchinesefont_sportscene_watertemp,string_content,string_len,APP_COLOR_WHITE);



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
        
        if(curr_info.RealTimeData.HR == 0)
        {
            sprintf(string_content,"--");
        }
        else
        {
            
            sprintf(string_content,"%d",curr_info.RealTimeData.HR);
        }
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_HrData(temp_ram,0,118,176,58,fontinfo,string_content,string_len,APP_COLOR_WHITE,curr_info.HrZone);

    }

    UI_Display_Prepare(temp_ram);
    
}



void UI_Screen_SwimModeDetail_Exit(void)
{
    detail_page = 0;
}


void UI_Screen_SwimModeDetail_shortkeyhandle(void)
{

    UI_Screen_SwimModeDetail_Exit();
    UI_Common_Shake();
    Scene_Swim_Pause();
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Pause);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeDetail_holdshortkeyhandle(void)
{
}

void UI_Screen_SwimModeDetail_holdlongkeyhandle(void)
{
}

void UI_Screen_SwimModeDetail_tpclickhandle(int point_x,int point_y)
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
    
}


void UI_Screen_SwimModeDetail_tpupslidehandle(void)
{
    #if 0

        if(detail_page == 0)
            detail_page =1;
        else
            detail_page =0;
        
        UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Datadetail);
        UI_Screen_draw_Screen();
    #endif

}

void UI_Screen_SwimModeDetail_tpdownslidehandle(void)
{
    #if 0
        if(detail_page == 0)
            detail_page =1;
        else
            detail_page =0;
        
        UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Datadetail);
        UI_Screen_draw_Screen();
    #endif
}

void UI_Screen_SwimModeDetail_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModeDetail_tprightslidehandle(void)
{

    #if 0
        UI_Set_Go_back_handle(UI_Screen_SwimModeDetail_Goback);

        UI_Screen_SwimModeDetail_Exit();
        UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
        UI_Screen_draw_Screen();
    #endif

}

void UI_Screen_SwimModePause_Timerhandle(void)
{

        UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Menu);
        UI_Screen_draw_Screen();

}

void UI_Screen_SwimModePause_Entry(void)
{   

    UI_Screen_SwimModePause_Display();

    UI_Common_set_timer_handle(UI_Screen_SwimModePause_Timerhandle);
    App_Lcd_TimerStart(500);

    UI_Common_clean_tp_handle();
    UI_Common_clean_key_handle();
    
}

void UI_Screen_SwimModePause_Display(void)
{
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_Datadetail)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_Show_PlayPause(temp_ram,1);
    UI_Display_Prepare(temp_ram);
}

void UI_Screen_SwimModePause_Exit(void)
{

}


void UI_Screen_SwimModeContinue_Timerhandle(void)
{

        UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Datadetail);
        UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeContinue_Entry(void)
{   

    UI_Screen_SwimModeContinue_Display();
    UI_Common_set_timer_handle(UI_Screen_SwimModeContinue_Timerhandle);
    App_Lcd_TimerStart(500);

    UI_Common_clean_tp_handle();
    UI_Common_clean_key_handle();
    
    
}

void UI_Screen_SwimModeContinue_Display(void)
{
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_Datadetail)
        return;
    UI_Common_Clear_Screen(temp_ram);
    UI_Common_Show_PlayPause(temp_ram,0);
    UI_Display_Prepare(temp_ram);
}

void UI_Screen_SwimModeContinue_Exit(void)
{


}


//static int menu_page = 0;


void UI_Screen_SwimModeMenu_Entry(void)
{   

    UI_Screen_SwimModeMenu_Display();

    UI_Common_set_key_handle(UI_Screen_SwimModeMenu_shortkeyhandle,UI_Screen_SwimModeMenu_holdshortkeyhandle,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SwimModeMenu_tpclickhandle);
    
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModeMenu_tpupslidehandle,
                                    UI_Screen_SwimModeMenu_tpdownslidehandle,
                                    UI_Screen_SwimModeMenu_tpleftslidehandle,
                                    UI_Screen_SwimModeMenu_tprightslidehandle);
}

void UI_Screen_SwimModeMenu_Display(void)
{
    swimIndoorInfo_t curr_info;
    char string_distance[16];
    int len_distance;
    char string_duration[16];
    int len_duration;
    int temp_h,temp_m,temp_s;
    float temp_f;

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_Menu)
        return;
    UI_Common_Clear_Screen(temp_ram);


    #if 0
    if(menu_page == 0)
    {
        Scene_Swim_InfoGet(&curr_info);

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
    
        Scene_Swim_InfoGet(&curr_info);
        
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

        UI_Common_Draw_FontStr_textbox(temp_ram,8,84,160,24,(uint8_t *)gchinesefont_sportscene_remind1,APP_COLOR_CYAN,APP_COLOR_BLACK);
        UI_Common_Draw_FontStr_textbox(temp_ram,8,84+24+12,160,24,(uint8_t *)gchinesefont_sportscene_remind2,APP_COLOR_CYAN,APP_COLOR_BLACK);
        
    #endif

    UI_Display_Prepare(temp_ram);

}

void UI_Screen_SwimModeMenu_Exit(void)
{

    //menu_page = 0;

}

void UI_Screen_SwimModeMenu_shortkeyhandle(void)
{

    UI_Screen_SwimModeMenu_Exit();
    UI_Common_Shake();
    Scene_Swim_Continue();
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Continue);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeMenu_holdshortkeyhandle(void)
{

    UI_Screen_SwimModeMenu_Exit();
    UI_Common_Shake();
    Scene_Swim_Disable();
    //模式开始，开启大休眠
    UI_Commom_Set_Allow_Lockstate2(1);
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_History);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeMenu_holdlongkeyhandle(void)
{
}

void UI_Screen_SwimModeMenu_tpclickhandle(int point_x,int point_y)
{

    #if 0
    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);
    

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        if(menu_page == 1)
        {
            UI_Screen_SwimModeMenu_Exit();
            UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Abandon);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        if(menu_page == 1)
        {
            UI_Screen_SwimModeMenu_Exit();
            UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
            UI_Screen_draw_Screen();
        }
        else if(menu_page == 0)
        {
            UI_Screen_SwimModeMenu_Exit();
            UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Continue);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        if(menu_page == 0)
        {
            UI_Screen_SwimModeMenu_Exit();
            UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_CompleteMenu);
            UI_Screen_draw_Screen();
        }
        
        break;
        default:
        break;
    }
    #endif
    
}


void UI_Screen_SwimModeMenu_tpupslidehandle(void)
{
    #if 0
    if(menu_page == 0)
        menu_page =1;
    else
        menu_page =0;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Menu);
    UI_Screen_draw_Screen();
    #endif

}

void UI_Screen_SwimModeMenu_tpdownslidehandle(void)
{
    #if 0
    if(menu_page == 0)
        menu_page =1;
    else
        menu_page =0;
    
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Menu);
    UI_Screen_draw_Screen();
    #endif
}

void UI_Screen_SwimModeMenu_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModeMenu_tprightslidehandle(void)
{
    #if 0
    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
    UI_Screen_draw_Screen();
    #endif

}


void UI_Screen_SwimModeCompleteMenu_Entry(void)
{   

    //menu_page = 0;
    UI_Screen_SwimModeCompleteMenu_Display();

    UI_Common_set_key_handle(UI_Screen_SwimModeCompleteMenu_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SwimModeCompleteMenu_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModeCompleteMenu_tpupslidehandle,
                                    UI_Screen_SwimModeCompleteMenu_tpdownslidehandle,
                                    UI_Screen_SwimModeCompleteMenu_tpleftslidehandle,
                                    UI_Screen_SwimModeCompleteMenu_tprightslidehandle);
}

void UI_Screen_SwimModeCompleteMenu_Display(void)
{

    #if 0
    swimIndoorInfo_t curr_info;
    char string_distance[16];
    int len_distance;
    char string_duration[16];
    int len_duration;
    int temp_h,temp_m,temp_s;
    #endif

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_CompleteMenu)
        return;
    UI_Common_Clear_Screen(temp_ram);

    #if 0 
    Scene_Swim_InfoGet(&curr_info);

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
    UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_datadetail_datadetail,NULL,NULL,0);
    UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_datadetail_exit,NULL,NULL,0);
    #endif
    
    UI_Display_Prepare(temp_ram);

}


void UI_Screen_SwimModeCompleteMenu_Exit(void)
{


}
void UI_Screen_SwimModeCompleteMenu_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeCompleteMenu_holdshortkeyhandle(void)
{
}

void UI_Screen_SwimModeCompleteMenu_holdlongkeyhandle(void)
{
}

void UI_Screen_SwimModeCompleteMenu_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_History);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
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


void UI_Screen_SwimModeCompleteMenu_tpupslidehandle(void)
{
}

void UI_Screen_SwimModeCompleteMenu_tpdownslidehandle(void)
{
}

void UI_Screen_SwimModeCompleteMenu_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModeCompleteMenu_tprightslidehandle(void)
{

}

void UI_Screen_SwimModeAbandon_Entry(void)
{   

    UI_Screen_SwimModeAbandon_Display();

    UI_Common_set_key_handle(UI_Screen_SwimModeAbandon_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_SwimModeAbandon_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModeAbandon_tpupslidehandle,
                                    UI_Screen_SwimModeAbandon_tpdownslidehandle,
                                    UI_Screen_SwimModeAbandon_tpleftslidehandle,
                                    UI_Screen_SwimModeAbandon_tprightslidehandle);
}

void UI_Screen_SwimModeAbandon_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_CompleteMenu)
        return;
    UI_Common_Clear_Screen(temp_ram);
    
    UI_Common_AddBWsourcePic(temp_ram,4,63,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
    //UI_Common_AddPic(lcdram,4,122,(uint8_t*)BtnFullRed_h);
    UI_Common_AddBWsourcePic(temp_ram,4,122,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_RED);
    

    UI_Common_Draw_FontStr_textbox(temp_ram,0,0,176,58,(uint8_t *)gchinesefont_sportscene_abandon_confirm,APP_COLOR_WHITE,APP_COLOR_BLACK);
    UI_Common_Draw_FontStr_textbox(temp_ram,0,59,176,58,(uint8_t *)gchinesefont_sportscene_abandon_confirm_no,APP_COLOR_BLACK,APP_COLOR_CYAN);
    UI_Common_Draw_FontStr_textbox(temp_ram,0,118,176,58,(uint8_t *)gchinesefont_sportscene_abandon_confirm_yes,APP_COLOR_BLACK,APP_COLOR_RED);

    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_SwimModeAbandon_Exit(void)
{


}

void UI_Screen_SwimModeAbandon_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_SwimModeAbandon_holdshortkeyhandle(void)
{
}

void UI_Screen_SwimModeAbandon_holdlongkeyhandle(void)
{
}

void UI_Screen_SwimModeAbandon_tpclickhandle(int point_x,int point_y)
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
            UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Menu);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
        
            UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
            UI_Screen_draw_Screen();
        }
        
        break;
        default:
        break;
    }
        
    
}


void UI_Screen_SwimModeAbandon_tpupslidehandle(void)
{


}

void UI_Screen_SwimModeAbandon_tpdownslidehandle(void)
{


}

void UI_Screen_SwimModeAbandon_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModeAbandon_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Menu);
    UI_Screen_draw_Screen();
}


static int page_number = 0;

void UI_Screen_SwimModeHistory_Entry(void)
{

    
    UI_Screen_SwimModeHistory_Display();
    UI_Common_set_key_handle(UI_Screen_SwimModeHistory_shortkeyhandle,NULL,NULL);
    
    UI_Common_set_tp_click_handle(UI_Screen_SwimModeHistory_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_SwimModeHistory_tpupslidehandle,
                                    UI_Screen_SwimModeHistory_tpdownslidehandle,
                                    UI_Screen_SwimModeHistory_tpleftslidehandle,
                                    UI_Screen_SwimModeHistory_tprightslidehandle);
    
}


void UI_Screen_SwimModeHistory_Display(void)
{

    char content[32];
    int len;
    
    int hour;
    int min;
    int second;

    rtc_time_s rtc_time;

    swimIndoorInfo_t curr_info;
    int temp_a,temp_b;
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Swimmode()!=Common_Screen_SubID_SwimMode_History)
        return;
    UI_Common_Clear_Screen(temp_ram);


    Scene_Swim_InfoGet(&curr_info);

    //首页
    if(page_number == 0)
    {

        UtcTransformTime(curr_info.RecordData.StartUTC, &rtc_time);

        //title
        UI_Common_Draw_FontStr_textbox(temp_ram,8,8,160,16,(uint8_t *)gchinesefont_sportscene_history_swim,APP_COLOR_WHITE,APP_COLOR_BLACK);
        sprintf(content,"%02d/%02d/%02d  %02d:%02d",rtc_time.year,rtc_time.month,rtc_time.day,rtc_time.hour,rtc_time.min);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,8,32,160,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_CENTER);

        //距离
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_distance[0]-8,59,gchinesefont_sportscene_datadetail_distance[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_distance,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        //temp_f = (float)curr_info.RecordData.Distance/1000;
        //memset(string_content,0,16);
        sprintf(content,"%dm",curr_info.RecordData.Distance);
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

        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_minkm[0]-4,18,gchinesefont_sportscene_datadetail_minkm[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_minkm,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_minkm[0]-gchinesefont_sportscene_average[0]-4,18,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,22,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        temp_a = curr_info.RecordData.PaceAVG/60;
        temp_b = curr_info.RecordData.PaceAVG%60; 
        sprintf(content,"%d'%2d\"",temp_a,temp_b);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,18,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_strokecount[0]-4,59,gchinesefont_sportscene_strokecount[0],16,(uint8_t *)gchinesefont_sportscene_strokecount,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        sprintf(content,"%d",curr_info.RecordData.Stroke);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);


        
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_strokecount[0]-4,101,gchinesefont_sportscene_strokecount[0],16,(uint8_t *)gchinesefont_sportscene_strokecount,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_strokecount[0]-gchinesefont_sportscene_average[0]-4,101,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,105,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);
        
        sprintf(content,"%d",curr_info.RecordData.StrokeAVG);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,101,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_strokerate[0]-4,142,gchinesefont_sportscene_strokerate[0],16,(uint8_t *)gchinesefont_sportscene_strokerate,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_strokerate[0]-gchinesefont_sportscene_average[0]-4,142,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,146,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);


        sprintf(content,"%dspm",curr_info.RecordData.StrokeRateAVG);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,142,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            
    
    }
    else
    {

        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_swolf[0]-8,18,gchinesefont_sportscene_datadetail_swolf[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_swolf,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,22,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        sprintf(content,"%d",curr_info.RecordData.SwolfAvg);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,18,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_calorie[0]-8,59,gchinesefont_sportscene_datadetail_calorie[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_calorie,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        sprintf(content,"%dkcal",curr_info.RecordData.Calorie);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-8,101,gchinesefont_heartrate_detail_heartrate[0],16,(uint8_t *)gchinesefont_heartrate_detail_heartrate,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-gchinesefont_sportscene_average[0]-8,101,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,105,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        
        sprintf(content,"%d",curr_info.RecordData.HrAVG);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,101,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

    }
    
    
    UI_Display_Prepare(temp_ram);

}


void UI_Screen_SwimModeHistory_Exit(void)
{

    page_number = 0;

}


void UI_Screen_SwimModeHistory_shortkeyhandle(void)
{
    UI_Screen_SwimModeHistory_Exit();
    UI_Set_Go_back_handle(NULL);
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}


void UI_Screen_SwimModeHistory_tpclickhandle(int point_x,int point_y)
{
    
}

void UI_Screen_SwimModeHistory_tpupslidehandle(void)
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

void UI_Screen_SwimModeHistory_tpdownslidehandle(void)
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

void UI_Screen_SwimModeHistory_tpleftslidehandle(void)
{
}

void UI_Screen_SwimModeHistory_tprightslidehandle(void)
{

    UI_Screen_SwimModeHistory_Exit();
    UI_Set_Go_back_handle(NULL);
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}














