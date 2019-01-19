

#include "ui_screen_dateandtime.h"
#include "app_systerm.h"

static int is_show_state_bar =0;


//心率显示
void UI_Display_HeartRate(uint8_t *lcdram,uint8_t info_x,uint8_t info_y,uint8_t size)
{
    char content[16];
    int len= 0;

    Mid_Hrm_Param_t* curr_heartrate_info;
    curr_heartrate_info = Mid_Hrm_ParamPGet();

    UI_Common_AddBWsourcePic(lcdram,SCREEN_DATEANDTIME_HEART_RATE_X,SCREEN_DATEANDTIME_HEART_RATE_Y,(uint8_t*)bw_image_heartrate_24_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
    if(curr_heartrate_info->LastHeartRate == HRM_INVALID_VALUE)
    {
        sprintf(content,"--");
    }
    else
    {
        sprintf(content,"%d",curr_heartrate_info->LastHeartRate);
    }

    len = strlen(content);
    UI_Common_AddAsc2Str(lcdram,SCREEN_DATEANDTIME_HEART_RATE_X+30,SCREEN_DATEANDTIME_HEART_RATE_Y,(int8_t*)content,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
}


//时间显示 time_type   时间格式      (12/24小时)          size 时间bar高度  不同位置 高度不同
void UI_Display_Time(uint8_t *lcdram,uint8_t info_x,uint8_t info_y,uint8_t time_type,uint8_t size)
{
    int x=0;
    //uint8_t font_color = APP_COLOR_WHITE;
    uint8_t *fontinfo;
    int a;
    char str_content[16];
    int len;
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
    SysTimeType_e curr_type = App_Var_SysTimeTypeGet();

    ui_common_time_12hour_s curr_12hour_time = {0};

    if(curr_type == SYS_TIME_24_TYPE)
    {
        x = SCREEN_DATEANDTIME_TIME_X;
        a = lMidRTC->RTC.hour/10;
        fontinfo = UI_Common_GetNumberImageInfo(a,1);
        UI_Common_AddBWsourcePic(lcdram,x,SCREEN_DATEANDTIME_TIME_Y,fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);
        x = x+fontinfo[0];
        a = lMidRTC->RTC.hour%10;
        fontinfo = UI_Common_GetNumberImageInfo(a,1);
        UI_Common_AddBWsourcePic(lcdram,x,SCREEN_DATEANDTIME_TIME_Y,fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);
        x = x+fontinfo[0];
        UI_Common_AddBWsourcePic(lcdram,x,SCREEN_DATEANDTIME_TIME_Y,(uint8_t *)font_tgl_48_colon_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        x = x+font_tgl_48_colon_h[0];
        a = lMidRTC->RTC.min/10;
        fontinfo = UI_Common_GetNumberImageInfo(a,1);
        UI_Common_AddBWsourcePic(lcdram,x,SCREEN_DATEANDTIME_TIME_Y,fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);
        x = x+fontinfo[0];
        a = lMidRTC->RTC.min%10;
        fontinfo = UI_Common_GetNumberImageInfo(a,1);
        UI_Common_AddBWsourcePic(lcdram,x,SCREEN_DATEANDTIME_TIME_Y,fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);

        //UI_Common_AddBWsourcePic(lcdram,14,80,(uint8_t*)bw_image_AM_h,APP_COLOR_BLACK,APP_COLOR_WHITE);

        
    }
    else
    {

        UI_Common_Get_Time_12hour(&curr_12hour_time);

        //14-80
        if(curr_12hour_time.is_am ==1)
        {

            UI_Common_AddAsc2Str(lcdram, 12, 80,"AM",2,12,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }
        else
        {
            UI_Common_AddAsc2Str(lcdram, 12, 80,"PM",2,12,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }

        x = SCREEN_DATEANDTIME_TIME_X;
        a = curr_12hour_time.hour/10;
        fontinfo = UI_Common_GetNumberImageInfo(a,1);
        UI_Common_AddBWsourcePic(lcdram,x,SCREEN_DATEANDTIME_TIME_Y,fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);
        x = x+fontinfo[0];
        a = curr_12hour_time.hour%10;
        fontinfo = UI_Common_GetNumberImageInfo(a,1);
        UI_Common_AddBWsourcePic(lcdram,x,SCREEN_DATEANDTIME_TIME_Y,fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);
        x = x+fontinfo[0];
        UI_Common_AddBWsourcePic(lcdram,x,SCREEN_DATEANDTIME_TIME_Y,(uint8_t *)font_tgl_48_colon_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        x = x+font_tgl_48_colon_h[0];
        a = curr_12hour_time.min/10;
        fontinfo = UI_Common_GetNumberImageInfo(a,1);
        UI_Common_AddBWsourcePic(lcdram,x,SCREEN_DATEANDTIME_TIME_Y,fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);
        x = x+fontinfo[0];
        a = curr_12hour_time.min%10;
        fontinfo = UI_Common_GetNumberImageInfo(a,1);
        UI_Common_AddBWsourcePic(lcdram,x,SCREEN_DATEANDTIME_TIME_Y,fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);
        

    
    }

    
    fontinfo= UI_Common_GetweekfontInfo(lMidRTC->RTC.week);
    UI_Common_AddBWsourcePic(lcdram,90,44,(uint8_t*)fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);

    
    sprintf(str_content,"%02d/%02d",lMidRTC->RTC.month,lMidRTC->RTC.day);
    len = strlen(str_content);
    UI_Common_Draw_AscStr_textbox(lcdram,56,44,32,12,12,APP_COLOR_WHITE,str_content,len,ENUM_TEXTBOX_CENTER);


    
}


//未读信息显示
void UI_Display_UnreadMsg(uint8_t *lcdram,uint8_t info_x,uint8_t info_y,uint8_t size)
{

    UI_Common_AddPic(lcdram,SCREEN_DATEANDTIME_UNRMSG_X,SCREEN_DATEANDTIME_UNRMSG_Y,(uint8_t*)image_call_msg_outline_16_h);

}

uint8_t*  UI_Common_GetWeatherimageInfo(SceneWeahterStatus_e weatherstatus)
{

    uint8_t* imageinfo = NULL;

        switch(weatherstatus)
        {
            case WEATHER_TENDENCY_SUNNY:
                imageinfo = (uint8_t*)image_weather_0000_sunny_24_h;
                break;
            case WEATHER_TENDENCY_CLOUDY:
                imageinfo = (uint8_t*)image_weather_0001_cloudy_24_h;
                break;
            case WEATHER_TENDENCY_OVERCAST:
                imageinfo = (uint8_t*)image_weather_0002_overcast_24_h;
                break;
            case WEATHER_TENDENCY_HAZE:
                imageinfo = (uint8_t*)iamge_weather_0003_haze_24_h;
                break;
            case WEATHER_TENDENCY_ICERAIN:
                imageinfo = (uint8_t*)image_weather_0004_icerain_24_h;
                break;
            case WEATHER_TENDENCY_FOGGY:
                imageinfo = (uint8_t*)image_weather_0005_foggy_24_h;
                break;
            case WEATHER_TENDENCY_LIGHT_RAIN:
                imageinfo = (uint8_t*)image_weather_0100_light_rain_24_h;
                break;
            case WEATHER_TENDENCY_MODERATE_RAIN:
                imageinfo = (uint8_t*)image_weather_0101_moderate_rain_24_h;
                break;
            case WEATHER_TENDENCY_HEAVY_RAIN:
                imageinfo = (uint8_t*)image_weather_0102_heavy_rain_24_h;
                break;
            case WEATHER_TENDENCY_RAINSTORM:
                imageinfo = (uint8_t*)image_weather_0103_rainstorm_24_h;
                break;
            case WEATHER_TENDENCY_BIG_RAINSTORM:
                imageinfo = (uint8_t*)image_weather_0104_big_rainstorm_24_h;
                break;
            case WEATHER_TENDENCY_SUPER_RAINSTORM:
                imageinfo = (uint8_t*)image_weather_0105_super_rainstorm_24_h;
                break;
            case WEATHER_TENDENCY_SNOW_SHOWER:
                imageinfo = (uint8_t*)image_weather_0200_snow_shower_24_h;
                break;
            case WEATHER_TENDENCY_LIGHT_SNOW:
                imageinfo = (uint8_t*)image_weather_0201_light_snow_24_h;
                break;
            case WEATHER_TENDENCY_MODERATE_SNOW:
                imageinfo = (uint8_t*)image_weather_0202_moderate_snow_24_h;
                break;
            case WEATHER_TENDENCY_HEAVY_SNOW:
                imageinfo = (uint8_t*)image_weather_0203_heavy_snow_24_h;
                break;
            case WEATHER_TENDENCY_BLIZZARD:
                imageinfo = (uint8_t*)image_weather_0204_blizzard_24_h;
                break;
            case WEATHER_TENDENCY_DUST:
                imageinfo = (uint8_t*)image_weather_0300_dust_24_h;
                break;
            case WEATHER_TENDENCY_DUSTBLOW:
                imageinfo = (uint8_t*)image_weather_0301_dustblow_24_h;
                break;
            case WEATHER_TENDENCY_SANDSTORM:
                imageinfo = (uint8_t*)image_weather_0302_sandstorm_24_h;
                break;
            case WEATHER_TENDENCY_STRONG_SANDSTORM:
                imageinfo = (uint8_t*)image_weather_0303_strong_sandstorm_24_h;
                break;
            case WEATHER_TENDENCY_SHOWER:
                imageinfo = (uint8_t*)image_weather_0400_shower_24_h;
                break;
            case WEATHER_TENDENCY_THUNDER_RAIN:
                imageinfo = (uint8_t*)image_weather_0401_thunder_rain_24_h;
                break;
            case WEATHER_TENDENCY_SLEETY:
                imageinfo = (uint8_t*)image_weather_0402_sleety_24_h;
                break;
            case WEATHER_TENDENCY_HAIL:
                imageinfo = (uint8_t*)image_weather_0403_hail_24_h;
                break;
            default:
                imageinfo = (uint8_t*)image_weather_0000_sunny_24_h;
                break;
        }
        
    
    return imageinfo;
    
}



//时间显示 time_type   时间格式      (12/24小时)          size 时间bar高度  不同位置 高度不同
void UI_Display_Weather(uint8_t *lcdram,uint8_t info_x,uint8_t info_y,uint8_t size)
{
    SceneWeahterParam_t curr_weather;
    uint8_t *imageinfo;
    char str_content[16];
    int len;
    int offset_x,offset_y;

    Scene_Weather_TendencyGet(&curr_weather);
    imageinfo=UI_Common_GetWeatherimageInfo(curr_weather.Status);
    UI_Common_AddPic(lcdram,SCREEN_DATEANDTIME_WEATHER_X,SCREEN_DATEANDTIME_WEATHER_Y,imageinfo);

    if(curr_weather.CurTemperature==SCENE_WEATHER_INVALID_TEMP)
    {
        sprintf(str_content,"--");
        len= strlen(str_content);
        UI_Common_GetAsc2Str_info((int8_t*)str_content,len,16,&offset_x,&offset_y);
        UI_Common_AddAsc2Str(lcdram,84,126,(int8_t*)str_content,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
    }
    else
    {
        sprintf(str_content,"%d",curr_weather.CurTemperature);
        len= strlen(str_content);
        UI_Common_GetAsc2Str_info((int8_t*)str_content,len,16,&offset_x,&offset_y);
        UI_Common_AddAsc2Str(lcdram,84,126,(int8_t*)str_content,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
        UI_Common_AddBWsourcePic(lcdram,84+offset_x+2,126,(uint8_t*)gchinesefont_degree,APP_COLOR_BLACK,APP_COLOR_WHITE);
    }
    
}


//时间显示 time_type   时间格式      (12/24小时)          size 时间bar高度  不同位置 高度不同
void UI_Display_Stepinfo(uint8_t *lcdram,uint8_t info_x,uint8_t info_y,uint8_t size)
{
//    stepSportInfo_s curr_step_info;
	SceneStepParam_t* tpSceneStep;
    float end_engle = 0;
    char str_content[16];
    int len;

//    Mid_SportScene_SportInfoRead(&curr_step_info);
	tpSceneStep = Scene_Step_ParamPGet();

    end_engle= 2*PI*tpSceneStep->stepComplete/100;
    //背景图
    UI_Common_Draw_Annulus(lcdram,87,87,87,79,APP_COLOR_RED,FALSE);
    UI_Common_Draw_Annulus_Byangle(lcdram,87,87,87,79,0,end_engle,APP_COLOR_RED,TRUE);

    sprintf(str_content,"%d",tpSceneStep->totalStep);
    len= strlen(str_content);
    UI_Common_Draw_AscStr_textbox(lcdram,60,146,56,16,16,APP_COLOR_WHITE,str_content,len,ENUM_TEXTBOX_CENTER);
}



void UI_Display_StateBar(uint8_t *lcdram,int bar_x,int bar_y,int height)
{
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
    uint8_t *fontinfo;
    char str_content[16];
    int len;

    is_show_state_bar = 0;
    
    UI_Common_Draw_Hline(lcdram,bar_x,bar_y,176,24,APP_COLOR_BLACK,TRUE);

    sprintf(str_content,"%2d/%2d",lMidRTC->RTC.month,lMidRTC->RTC.day);
    len = strlen(str_content);
    UI_Common_Draw_AscStr_textbox(lcdram,4,4,44,16,16,APP_COLOR_WHITE,str_content,len,ENUM_TEXTBOX_LEFT);

    fontinfo= UI_Common_GetweekfontInfo(lMidRTC->RTC.week);
    UI_Common_AddBWsourcePic(lcdram,4+44,6,(uint8_t*)fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);

    UI_Common_Add_Battery(lcdram,176-24,0,1);
    

    if(App_Var_BleStateGet()==BLE_CONNECT)
    {
        UI_Common_AddBWsourcePic(lcdram,176-24-16,4,(uint8_t*)iamge_bw_bt_connected_16_h,APP_COLOR_BLACK,APP_COLOR_BLUE);
    }  
    else if(App_Var_BleStateGet()==BLE_BROADCAST)
    {
        UI_Common_AddBWsourcePic(lcdram,176-24-16,4,(uint8_t*)iamge_bw_bt_16_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
    }
    else
    {
    }

        
    if(App_Var_NoDisturbSwitchGet()==SWITCH_ON)
    {
        UI_Common_AddBWsourcePic(lcdram,176-24-16-16,4,(uint8_t*)iamge_bw_donotdisturb_16_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
    }
    else
    {
    }


    if(UI_Screen_Alarm_Get_State()!=0)
    {
        UI_Common_AddBWsourcePic(lcdram,176-24-16-16-16,4,(uint8_t*)iamge_bw_alarm_16_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
    }
    else
    {
    }

    
    

}



void UI_Screen_DateAndTime_Timerhandle(void)
{

    UI_Screen_DateAndTime_Display();

}

void UI_Screen_DateAndTime_Display()
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();


    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_DateAndTime)
        return;

    UI_Common_Clear_Screen(temp_ram);

    UI_Common_set_timer_handle(UI_Screen_DateAndTime_Timerhandle);
    App_Lcd_TimerStart(1000);

    UI_Display_Stepinfo(temp_ram,0,0,0);

    //心率
    UI_Display_HeartRate(temp_ram,0,0,0);
    //时间
    UI_Display_Time(temp_ram,0,0,0,0);
    //未读信息
    //UI_Display_UnreadMsg(temp_ram,0,0,0);
    //天气
    UI_Display_Weather(temp_ram,0,0,0);

    if(NULL!=UI_Get_Go_back_handle())
    {
        UI_Common_Draw_Vline(temp_ram,174,0,176,2,APP_COLOR_CYAN,true);
    }

    if(is_show_state_bar == 1)
    {
        UI_Display_StateBar(temp_ram,0,0,24);
    }
    

    UI_Display_Prepare(temp_ram);
    
}


void UI_Screen_DateAndTime_Entry()
{


    UI_Screen_DateAndTime_Display();

    UI_Common_set_key_handle(UI_Screen_DateAndTime_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_DateAndTime_tpclickhandle);
    
    UI_Common_set_tp_slide_handle(UI_Screen_DateAndTime_tpupslidehandle,
                                    UI_Screen_DateAndTime_tpdownslidehandle,
                                    UI_Screen_DateAndTime_tpleftslidehandle,
                                    UI_Screen_DateAndTime_tprightslidehandle);
    
}

void UI_Screen_DateAndTime_Exit(void)
{
    is_show_state_bar = 0;
    
    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
}

void UI_Screen_DateAndTime_shortkeyhandle(void)
{

    UI_Screen_DateAndTime_Exit();
    if(NULL!=UI_Get_Go_back_handle())
    {
        UI_Do_Go_back_handle();
    }
    else
    {
        UI_Set_Curr_ScreenID(Common_Screen_MainID_Modelist);
        UI_Screen_draw_Screen();
    }


}

void UI_Screen_DateAndTime_holdshortkeyhandle(void)
{
}

void UI_Screen_DateAndTime_holdlongkeyhandle(void)
{
}


void UI_Screen_DateAndTime_tpclickhandle(int point_x,int point_y)
{

    //判断点的范围
    is_show_state_bar = 1;

}

void UI_Screen_DateAndTime_tpupslidehandle(void)
{

    UI_Screen_DateAndTime_Exit();
    
    //curr_run_screen_info.run_type = ENUM_ROUND_UP;
    UI_Common_Show_RunScreen_Prepare(ENUM_ROUND_UP);

    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Step);
    UI_Screen_draw_Screen();


}

void UI_Screen_DateAndTime_tpdownslidehandle(void)
{

    UI_Screen_DateAndTime_Exit();
    
    //curr_run_screen_info.run_type = ENUM_ROUND_DOWN;
    UI_Common_Show_RunScreen_Prepare(ENUM_ROUND_DOWN);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_History);
    UI_Screen_draw_Screen();

}

void UI_Screen_DateAndTime_tpleftslidehandle(void)
{


}


void UI_Screen_DateAndTime_tprightslidehandle(void)
{
}


typedef struct 
{

	uint8   state;
	uint8   is_allow_state1;
	uint8   is_allow_state2;
	uint8   count;
	uint8   threshold;  //暂时闲置
    
}ui_common_lock_info_s;



ui_common_lock_info_s lock_info = {0};


void UI_Commom_Lockinfo_Init(void)
{

    lock_info.state = 0;
    lock_info.is_allow_state1 = 1;
    lock_info.is_allow_state2 = 1;
    lock_info.count = 0;
    lock_info.threshold = 0;
     
}


//1 允许 0.不允许
void UI_Commom_Set_Allow_Lockstate1(uint8 state)
{

    lock_info.is_allow_state1 = state;
    
}

//1 允许 0.不允许
void UI_Commom_Set_Allow_Lockstate2(uint8 state)
{

    lock_info.is_allow_state2 = state;
    
}

void UI_Commom_Lockinfo_Timehandle(void)
{
    
    //RTT_DEBUG_printf(0,"UI_Commom_Lockinfo_Timehandle = %d-%d",lock_info.state,lock_info.count);
    lock_info.count++;

    if(lock_info.is_allow_state1 == 0)
        lock_info.count = 0;

    if(lock_info.state == 0)
    {
        
        if(lock_info.count >= 10&&lock_info.is_allow_state1 == 1)
        {
            lock_info.state = 1;

            UI_Common_Close_Blacklight();
        
        }

    
    }
    else if(lock_info.state == 1)
    {
        //lock_info.count++;

        if(lock_info.count >= 30&&lock_info.is_allow_state2 == 1)
        {

            lock_info.state = 2;
            //App_Lcd_TimerStop();
            App_Lcd_HardTimerStop();
            Drv_Touch_Sleep();
            UI_Set_Curr_ScreenID(Common_Screen_MainID_Lock);
            //RTT_DEBUG_printf(0,"Common_Screen_MainID_Lock");
            //UI_Screen_draw_Screen();
            UI_Screen_Delete_Warn();
        }
         
    }
    else
    {
    
    }

    

}

void UI_Commom_Lockinfo_Reset(void)
{
    //RTT_DEBUG_printf(0,"UI_Commom_Lockinfo_Reset = %d",lock_info.state);
    
    lock_info.count = 0;

    if(lock_info.state == 1)
    {
        lock_info.state = 0;
        UI_Common_Open_Blacklight();
        //RTT_DEBUG_printf(0,"lock_info.count1");
    }
    else if(lock_info.state == 2)
    {
        lock_info.state = 0;
        UI_Common_Open_Blacklight();
        Drv_Touch_Wakeup();
        //RTT_DEBUG_printf(0,"lock_info.count2");
    }
}

int UI_Commom_get_Lockinfo_State(void)
{

    return lock_info.state;
    
}


void UI_Screen_Lock_Timerhandle(void)
{

    UI_Screen_Lock_Display();
    UI_Common_set_timer_handle(UI_Screen_Lock_Timerhandle);
    App_Lcd_TimerStart(1000);
    
}


void UI_Screen_Lock_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Lock)
    {
        UI_Screen_Lock_Exit();
        return;
    }

    //清屏
    UI_Common_Clear_Screen(temp_ram);
    
    UI_Display_Time(temp_ram,0,0,0,0);
    //未读信息
    //UI_Display_UnreadMsg(temp_ram,0,0,0);
    
    //显示准备
    UI_Display_Prepare(temp_ram);
    
}


void UI_Screen_Lock_Entry()
{
	//RTT_DEBUG_printf(0, "UI_Screen_Lock_Entry \n");
    //显示
    UI_Screen_Lock_Display();
    //time 自带刷屏
    UI_Screen_Lock_Timerhandle();
    //操作
    UI_Common_set_key_handle(UI_Screen_Lock_shortkeyhandle,NULL,NULL);
    UI_Common_clean_tp_handle();
    
    
}

void UI_Screen_Lock_Exit(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();

}

void UI_Screen_Lock_shortkeyhandle(void)
{

    UI_Screen_Lock_Exit();
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}

void UI_Screen_Lock_holdshortkeyhandle(void)
{
}

void UI_Screen_Lock_holdlongkeyhandle(void)
{
}


