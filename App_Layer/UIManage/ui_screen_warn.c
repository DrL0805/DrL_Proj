
#include "ui_screen_warn.h"
#include "sm_timer.h"
#include "app_protocal.h"
#include "ui_screen_dateandtime.h"



#define warn_show_time  5000

Warn_display_s curr_warn_info;
int globle_warn_data = 100;


void UI_Screen_Show_Warn_Screen_Camera(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Camera);
    //UI_Screen_draw_Screen();
}

void UI_Screen_Close_Warn_Screen_Camera(void)
{
    UI_Screen_Warn_Camera_Exit();
}


void UI_Screen_Show_Warn_Screen_Call(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Call);
    //UI_Screen_draw_Screen();


}

void UI_Screen_Show_Warn_Screen_Message(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Message);
    //UI_Screen_draw_Screen();

}


void UI_Screen_Show_Warn_Screen_Alarm(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Alarm);
    //UI_Screen_draw_Screen();


}

void UI_Screen_Show_Warn_Screen_Steptarget(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Steptarget);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_Outsit(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Outsit);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_Btconnect(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Btconnect);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_Space(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Space);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_Lowpower(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Lowpower);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_Timer(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Timer);
    //UI_Screen_draw_Screen();

}


void UI_Screen_Show_Warn_Screen_Error(void)
{

    UI_Common_Shake();
    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Error);
    //UI_Screen_draw_Screen();

}


void UI_Screen_Show_Warn_Screen_RunningMode_Target_Distance(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Running_Target_Distance);
    //UI_Screen_draw_Screen();

}


void UI_Screen_Show_Warn_Screen_RunningMode_Target_Duration(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Running_Target_Duration);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_RunningMode_Target_Calorie(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Running_Target_Calorie);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_RunningMode_Warn_Distance(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Running_Warn_Distance);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_RunningMode_Warn_Duration(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Running_Warn_Duration);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_RunningMode_Warn_Calorie(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Running_Warn_Calorie);
    //UI_Screen_draw_Screen();

}


void UI_Screen_Show_Warn_Screen_RunningMode_Warn_Speed_Uplimit(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Running_Warn_Speed_Uplimit);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_RunningMode_Warn_Speed_Lowlimit(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Running_Warn_Speed_Lowlimit);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_RunningMode_Warn_Heartrate_Uplimit(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Running_Warn_Heartrate_Uplimit);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_RunningMode_Warn_Heartrate_Lowlimit(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Running_Warn_Heartrate_Lowlimit);
    //UI_Screen_draw_Screen();

}


void UI_Screen_Show_Warn_Screen_ClimbingMode_Target_ClimbingDistance(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Climbing_Target_ClimbingDistance);
    //UI_Screen_draw_Screen();

}


void UI_Screen_Show_Warn_Screen_ClimbingMode_Target_Distance(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Climbing_Target_Distance);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_ClimbingMode_Target_Duration(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Climbing_Target_Duration);
    //UI_Screen_draw_Screen();

}


void UI_Screen_Show_Warn_Screen_ClimbingMode_Target_Calorie(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Climbing_Target_Calorie);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Distance(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Climbing_Warn_Distance);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Duration(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Climbing_Warn_Duration);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Calorie(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Climbing_Warn_Calorie);
    //UI_Screen_draw_Screen();

}


void UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Heartrate_Uplimit(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Climbing_Warn_Heartrate_Uplimit);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Heartrate_Lowlimit(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Climbing_Warn_Heartrate_Lowlimit);
    //UI_Screen_draw_Screen();

}


void UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Elevation_Uplimit(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Climbing_Warn_Elevation_Uplimit);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_ClimbingMode_Warn_Elevation_Lowlimit(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Climbing_Warn_Elevation_Lowlimit);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_SwimMode_Target_Laps(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Swim_Target_Laps);
    //UI_Screen_draw_Screen();

}


void UI_Screen_Show_Warn_Screen_SwimMode_Target_Duration(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Swim_Target_Duration);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_SwimMode_Target_Calorie(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Swim_Target_Calorie);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_SwimMode_Warn_Laps(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Swim_Warn_Laps);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_SwimMode_Warn_Duration(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Swim_Warn_Duration);
    //UI_Screen_draw_Screen();

}

void UI_Screen_Show_Warn_Screen_SwimMode_Warn_Calorie(void)
{

    UI_Common_set_timer_handle(NULL);
    App_Lcd_TimerStop();
    UI_Screen_Add_Warn(Common_Screen_ID_Warn_Swim_Warn_Calorie);
    //UI_Screen_draw_Screen();

}





void UI_Screen_Warn_Set_Warn_Data(int data)
{

    globle_warn_data = data;

}

int UI_Screen_Warn_Get_Warn_Data(void)
{

    return globle_warn_data;

}

#if 1
void UI_Screen_Add_Warn(Enum_Common_Screen_SUBID_WARN warn_screen)
{

    if(curr_warn_info.curr_screen == Common_Screen_ID_Warn_None)
    {
        if(warn_screen == Common_Screen_ID_Warn_Camera)
        {
            curr_warn_info.is_camera = true;
        }
        
        if(warn_screen == Common_Screen_ID_Warn_Call)
        {
            curr_warn_info.is_call = true;
        }
        
        if(warn_screen == Common_Screen_ID_Warn_Alarm)
        {
            curr_warn_info.is_alarm = true;
        }
        
        if(warn_screen == Common_Screen_ID_Warn_Timer)
        {
            curr_warn_info.is_timer = true;
        }
        
        #if 0
        if(warn_screen == Common_Screen_ID_Warn_Message)
        {
            curr_warn_info.is_message = true;
        }
        #endif
        
        curr_warn_info.curr_screen = warn_screen;
        UI_Screen_draw_Screen();
    }
    else
    {

        
        if(warn_screen == Common_Screen_ID_Warn_Camera)
        {
            curr_warn_info.is_camera = true;
                        
        }
        else if(warn_screen == Common_Screen_ID_Warn_Call)
        {

            if(curr_warn_info.is_camera == true)
            {
                return;
            }
            curr_warn_info.is_call = true;
           
        }
        else if(warn_screen == Common_Screen_ID_Warn_Alarm)
        {
            if(curr_warn_info.is_camera == true||curr_warn_info.is_call == true)
            {
                return;
            }
            curr_warn_info.is_alarm = true;

        }
        else if(warn_screen == Common_Screen_ID_Warn_Timer)
        {
        
            if(curr_warn_info.is_camera == true||curr_warn_info.is_call == true||curr_warn_info.is_alarm == true)
            {
                return;
            }
        
            curr_warn_info.is_timer = true;
                
        }
        #if 0
        else if(warn_screen == Common_Screen_ID_Warn_Message)
        {
        
            if(curr_warn_info.is_call == true||curr_warn_info.is_alarm == true||curr_warn_info.is_timer == true)
            {
                return;
            }
            curr_warn_info.is_message = true;
            curr_warn_info.curr_screen =warn_screen;
            
        }
        #endif
        else
        {
            if(curr_warn_info.is_camera == true||curr_warn_info.is_call == true||curr_warn_info.is_alarm == true||curr_warn_info.is_timer == true)
            {
                return;
            }
        
        }
        
        curr_warn_info.curr_screen =warn_screen;
        UI_Screen_draw_Screen();
        
    }

}

void UI_Screen_Delete_Warn(void)
{

    curr_warn_info.is_camera = false;
    curr_warn_info.is_call = false;
    curr_warn_info.is_alarm = false;
    curr_warn_info.is_timer = false;
    //curr_warn_info.is_message = false;

    curr_warn_info.curr_screen = Common_Screen_ID_Warn_None;
    UI_Screen_draw_Screen();
}

#else

void  UI_Screen_Add_Warn(Enum_Common_Screen_SUBID_WARN warn_screen)
{

    Enum_Common_Screen_SUBID_WARN pre_screen;

    if(curr_warn_info.curr_screen == Common_Screen_ID_Warn_None)
    {
        curr_warn_info.curr_screen = warn_screen;
        
        if(warn_screen == Common_Screen_ID_Warn_Camera)
        {
            curr_warn_info.is_camera = true;
        }
        
        if(warn_screen == Common_Screen_ID_Warn_Call)
        {
            curr_warn_info.is_call = true;
        }
        
        if(warn_screen == Common_Screen_ID_Warn_Alarm)
        {
            curr_warn_info.is_alarm = true;
        }
        
        if(warn_screen == Common_Screen_ID_Warn_Timer)
        {
            curr_warn_info.is_timer = true;
        }
        
        if(warn_screen == Common_Screen_ID_Warn_Message)
        {
            curr_warn_info.is_message = true;
        }
        
    }
    else
    {
    
    
        if(curr_warn_info.is_camera == true)
        {
            return;
        }
        
        if(warn_screen == Common_Screen_ID_Warn_Camera)
        {
            curr_warn_info.is_camera = true;
            curr_warn_info.curr_screen =warn_screen;
            
            curr_warn_info.is_call = false;
            curr_warn_info.is_alarm = false;
            curr_warn_info.is_timer = false;
            curr_warn_info.is_message = false;
            
			for(;curr_warn_info.warn_total != 0; curr_warn_info.warn_total--)
            {
                curr_warn_info.wait_screen[curr_warn_info.warn_total-1] = Common_Screen_ID_Warn_None;
            }
            
        }
        else if(warn_screen == Common_Screen_ID_Warn_Call)
        {
            curr_warn_info.is_call = true;
            pre_screen = curr_warn_info.curr_screen;
            curr_warn_info.curr_screen =warn_screen;
            UI_Screen_Add_Warn(pre_screen);
           
        }
        else if(warn_screen == Common_Screen_ID_Warn_Alarm)
        {
            
            curr_warn_info.is_alarm = true;
            
            if(curr_warn_info.is_call==false)
            {
                pre_screen = curr_warn_info.curr_screen;
                curr_warn_info.curr_screen =warn_screen;
                UI_Screen_Add_Warn(pre_screen);
            }
            else
            {
            
            }
            
        }
        else if(warn_screen == Common_Screen_ID_Warn_Timer)
        {
            
            curr_warn_info.is_timer = true;
            
            if(curr_warn_info.is_call==false&&curr_warn_info.is_alarm==false)
            {
                pre_screen = curr_warn_info.curr_screen;
                curr_warn_info.curr_screen =warn_screen;
                UI_Screen_Add_Warn(pre_screen);
            }
            else
            {
            
            }
        }
        else if(warn_screen == Common_Screen_ID_Warn_Message)
        {
            
            curr_warn_info.is_message = true;
            
            if(curr_warn_info.is_call==false&&curr_warn_info.is_alarm==false&&curr_warn_info.is_timer==false)
            {
                pre_screen = curr_warn_info.curr_screen;
                curr_warn_info.curr_screen =warn_screen;
                UI_Screen_Add_Warn(pre_screen);
            }
            else
            {
            
            }
        }
        else
        {

            if(curr_warn_info.warn_total < WARN_WAIT_SCREEN_MAX)
            {
                curr_warn_info.wait_screen[curr_warn_info.warn_total] =warn_screen;
                curr_warn_info.warn_total++;
            }
        
        }
        
    
    }
    

}

void UI_Screen_Delete_Warn(void)
{

    if(curr_warn_info.curr_screen == Common_Screen_ID_Warn_Camera)
    {
        curr_warn_info.curr_screen = Common_Screen_ID_Warn_None;
        curr_warn_info.is_camera = false;
    }
    else if(curr_warn_info.curr_screen == Common_Screen_ID_Warn_Call)
    {
        curr_warn_info.curr_screen = Common_Screen_ID_Warn_None;
        curr_warn_info.is_call = false;
    }
    else if(curr_warn_info.curr_screen == Common_Screen_ID_Warn_Alarm)
    {
        curr_warn_info.curr_screen = Common_Screen_ID_Warn_None;
        curr_warn_info.is_alarm = false;
    }
    else if(curr_warn_info.curr_screen == Common_Screen_ID_Warn_Timer)
    {
        curr_warn_info.curr_screen = Common_Screen_ID_Warn_None;
        curr_warn_info.is_timer = false;
    }
    else if(curr_warn_info.curr_screen == Common_Screen_ID_Warn_Message)
    {
        curr_warn_info.curr_screen = Common_Screen_ID_Warn_None;
        curr_warn_info.is_message = false;
    }
    else
    {
        curr_warn_info.curr_screen = Common_Screen_ID_Warn_None;
    }
    

    if(curr_warn_info.is_alarm == true)
    {
        curr_warn_info.curr_screen = Common_Screen_ID_Warn_Alarm;
    }
    else if(curr_warn_info.is_timer == true)
    {
        curr_warn_info.curr_screen = Common_Screen_ID_Warn_Timer;
    }
    else if(curr_warn_info.is_message == true)
    {
        curr_warn_info.curr_screen = Common_Screen_ID_Warn_Message;
    }
    else if(curr_warn_info.warn_total!=0)
    {
        curr_warn_info.curr_screen = curr_warn_info.wait_screen[curr_warn_info.warn_total-1];
        curr_warn_info.wait_screen[curr_warn_info.warn_total-1] = Common_Screen_ID_Warn_None;
        curr_warn_info.warn_total--;
    
    }

    
    UI_Screen_draw_Screen();
    
}
#endif


void UI_Screen_Delete_All_Warn(void)
{

    curr_warn_info.is_camera = false;
    curr_warn_info.is_call = false;
    curr_warn_info.is_alarm = false;
    curr_warn_info.is_timer = false;
    //curr_warn_info.is_message = false;

    curr_warn_info.curr_screen = Common_Screen_ID_Warn_None;
    
    UI_Screen_draw_Screen();
    
}



Enum_Common_Screen_SUBID_WARN UI_Screen_Get_Warn_Screenid(void)
{
    return curr_warn_info.curr_screen;
}


void UI_Screen_Warn_Camera_Entry(uint8_t *lcdram)
{


    UI_Commom_Set_Allow_Lockstate1(0);

    UI_Screen_Warn_Camera_Display(lcdram);

    UI_Common_set_key_handle(UI_Screen_Warn_Camera_shortkeyhandle,UI_Screen_Warn_Camera_holdshortkeyhandle,UI_Screen_Warn_Camera_holdlongkeyhandle);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Camera_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Camera_tpupslidehandle,
                                    UI_Screen_Warn_Camera_tpdownslidehandle,
                                    UI_Screen_Warn_Camera_tpleftslidehandle,
                                    UI_Screen_Warn_Camera_tprightslidehandle);

    

}

void UI_Screen_Warn_Camera_Display(uint8_t *lcdram)
{

    UI_Common_AddBWsourcePic(lcdram,64,40,(uint8_t*)iamge_warn_camera_48_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
    UI_Common_Draw_FontStr_textbox(lcdram,8,92,160,68,(uint8_t *)gchinesefont_warn_camera,APP_COLOR_WHITE,APP_COLOR_BLACK);
    
}


void UI_Screen_Warn_Camera_Exit(void)
{

    UI_Commom_Set_Allow_Lockstate1(1);
    RTT_DEBUG_printf(0,"UI_Screen_Warn_Camera_Exit");
    UI_Screen_Delete_Warn();

}


void UI_Screen_Warn_Camera_shortkeyhandle(void)
{
    App_Protocal_TakePhoto();
}

void UI_Screen_Warn_Camera_holdshortkeyhandle(void)
{
}

void UI_Screen_Warn_Camera_holdlongkeyhandle(void)
{
}

void UI_Screen_Warn_Camera_tpclickhandle(int point_x,int point_y)
{
}

void UI_Screen_Warn_Camera_tpupslidehandle(void)
{

}

void UI_Screen_Warn_Camera_tpdownslidehandle(void)
{
}

void UI_Screen_Warn_Camera_tpleftslidehandle(void)
{
}

void UI_Screen_Warn_Camera_tprightslidehandle(void)
{
    //UI_Screen_Close_Warn_Screen_Camera();
}


void UI_Screen_Warn_Call_Reject(void)
{

    App_Protocal_PhoneCallRet(gePhoneSystem, ePhoneCallReject);

}

void UI_Screen_Warn_Call_Answer(void)
{

    App_Protocal_PhoneCallRet(gePhoneSystem, ePhoneCallAnswer);
}

void UI_Screen_Warn_Call_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Call_Display(lcdram);

    UI_Common_Set_Goback_Handle(10*1000,UI_Screen_Delete_Warn);
	
    UI_Common_set_key_handle(UI_Screen_Warn_Call_shortkeyhandle,UI_Screen_Warn_Call_holdshortkeyhandle,UI_Screen_Warn_Call_holdlongkeyhandle);
	
    UI_Common_set_tp_click_handle(UI_Screen_Warn_Call_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Call_tpupslidehandle,
                                    UI_Screen_Warn_Call_tpdownslidehandle,
                                    UI_Screen_Warn_Call_tpleftslidehandle,
                                    UI_Screen_Warn_Call_tprightslidehandle);

}

void UI_Screen_Warn_Call_Display(uint8_t *lcdram)
{

    RemindMsg_t info;

	uint16_t temp_data[256];
    uint16_t len = 0;

    int i = 0;
    
    App_RemindManage_CurrCallRead(&info);
        
    //UI_Common_AddPic(lcdram,4,4,(uint8_t*)BtnFullCyan_h);
    //UI_Common_AddPic(lcdram,4,122,(uint8_t*)BtnFullRed_h);

    UI_Common_AddBWsourcePic(lcdram,2,70,(uint8_t*)iamge_bw_history_call_h,APP_COLOR_BLACK,APP_COLOR_WHITE);


    memset(temp_data, 0x00, 256);
    len = info.Detail.PhoneCall.namelen;
    //memcpy(temp_data,&(info.Detail.PhoneCall.name[0]),len);
    //temp_data = &(info.Detail.PhoneCall.name[0]);

    for(i= 0;i<len;i++)
    {
        temp_data[i] = info.Detail.PhoneCall.name[i];
    }
    
    UI_Common_Drawtextbox_byfontic(lcdram, 40, 76,120,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);

    UI_Common_AddBWsourcePic(lcdram,4,4,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
    UI_Common_AddBWsourcePic(lcdram,4,122,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_RED);

    UI_Common_Draw_FontStr_textbox(lcdram,0,0,176,58,(uint8_t *)gchinesefont_warn_answer,APP_COLOR_BLACK,APP_COLOR_CYAN);
    UI_Common_Draw_FontStr_textbox(lcdram,0,118,176,58,(uint8_t *)gchinesefont_warn_reject,APP_COLOR_BLACK,APP_COLOR_RED);


    //UI_Common_set_timer_handle(UI_Screen_Warn_Call_Exit);
    //App_Lcd_TimerStart(10000);

}


void UI_Screen_Warn_Call_Exit(void)
{

    UI_Common_Cancel_Goback_Handle();
    UI_Screen_Delete_Warn();

}


void UI_Screen_Warn_Call_shortkeyhandle(void)
{

}

void UI_Screen_Warn_Call_holdshortkeyhandle(void)
{
}

void UI_Screen_Warn_Call_holdlongkeyhandle(void)
{
}

void UI_Screen_Warn_Call_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            //App_Lcd_TimerStop();
            UI_Screen_Warn_Call_Answer();
            UI_Screen_Warn_Call_Exit();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
            UI_Screen_Warn_Call_Reject();
            UI_Screen_Warn_Call_Exit();
        }
        break;
        default:
        break;
    }


}

void UI_Screen_Warn_Call_tpupslidehandle(void)
{
}

void UI_Screen_Warn_Call_tpdownslidehandle(void)
{
}

void UI_Screen_Warn_Call_tpleftslidehandle(void)
{
}

void UI_Screen_Warn_Call_tprightslidehandle(void)
{

    UI_Screen_Warn_Call_Exit();
    
}


const uint8_t image_bw_alarm_active_24_h[] = {
24,24,
0x00, 0x00, 0x00, /* scanline 1 */
0x00, 0x00, 0x00, /* scanline 2 */
0x00, 0x18, 0x00, /* scanline 3 */
0x06, 0x18, 0x60, /* scanline 4 */
0x0E, 0x7E, 0x70, /* scanline 5 */
0x1C, 0xFF, 0x38, /* scanline 6 */
0x19, 0xFF, 0x98, /* scanline 7 */
0x39, 0xFF, 0x9C, /* scanline 8 */
0x33, 0xFF, 0xCC, /* scanline 9 */
0x33, 0xFF, 0xCC, /* scanline 10 */
0x33, 0xFF, 0xCC, /* scanline 11 */
0x03, 0xFF, 0xC0, /* scanline 12 */
0x03, 0xFF, 0xC0, /* scanline 13 */
0x03, 0xFF, 0xC0, /* scanline 14 */
0x03, 0xFF, 0xC0, /* scanline 15 */
0x03, 0xFF, 0xC0, /* scanline 16 */
0x07, 0xFF, 0xE0, /* scanline 17 */
0x0F, 0xFF, 0xF0, /* scanline 18 */
0x0F, 0xFF, 0xF0, /* scanline 19 */
0x00, 0x00, 0x00, /* scanline 20 */
0x00, 0x3C, 0x00, /* scanline 21 */
0x00, 0x18, 0x00, /* scanline 22 */
0x00, 0x00, 0x00, /* scanline 23 */
0x00, 0x00, 0x00, /* scanline 24 */
};


void UI_Screen_Warn_Alarm_Goback(void)
{

    Scene_Alarm_Delay();
    UI_Screen_Delete_Warn();
    
}



void UI_Screen_Warn_Alarm_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Alarm_Display(lcdram);

    UI_Common_Set_Goback_Handle(10*1000,UI_Screen_Warn_Alarm_Goback);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Alarm_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Alarm_tpupslidehandle,
                                    UI_Screen_Warn_Alarm_tpdownslidehandle,
                                    UI_Screen_Warn_Alarm_tpleftslidehandle,
                                    UI_Screen_Warn_Alarm_tprightslidehandle);

                                    
}

void UI_Screen_Warn_Alarm_Display(uint8_t *lcdram)
{

    //alarm_clock_t info;
    char content[16];
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
    SysTimeType_e curr_type = App_Var_SysTimeTypeGet();

    ui_common_time_12hour_s curr_12hour_time = {0};
    
    //Scene_Alarm_CurrAlarmGet(&info);   

    // UI_Common_AddPic(lcdram,4,4,(uint8_t*)BtnFullCyan_h);
    UI_Common_AddBWsourcePic(lcdram,4,4,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
    
    //UI_Common_AddPic(lcdram,4,122,(uint8_t*)BtnFullYellow_h);
    UI_Common_AddBWsourcePic(lcdram,4,122,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_YELLOW);
    
    UI_Common_AddBWsourcePic(lcdram,4,122,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_YELLOW);
    
    UI_Common_AddBWsourcePic(lcdram,14,76,(uint8_t *)image_bw_alarm_active_24_h,APP_COLOR_BLACK,APP_COLOR_WHITE);

    if(curr_type == SYS_TIME_24_TYPE)
    {
        sprintf(content,"%02d:%02d",lMidRTC->RTC.hour,lMidRTC->RTC.min);
        UI_Common_Draw_NumberImage_textbox_Bystringinfo(lcdram,52,76,116,24,APP_COLOR_WHITE,content,strlen(content),26,ENUM_TEXTBOX_CENTER);
    }
    else
    {

        UI_Common_Get_Time_12hour(&curr_12hour_time);
        
        //14-80
        if(curr_12hour_time.is_am ==1)
        {

            sprintf(content,"%02d:%02d AM",curr_12hour_time.hour,curr_12hour_time.min);
        }
        else
        {
            sprintf(content,"%02d:%02d PM",curr_12hour_time.hour,curr_12hour_time.min);
        }
        
        UI_Common_Draw_NumberImage_textbox_Bystringinfo(lcdram,52,76,116,24,APP_COLOR_WHITE,content,strlen(content),26,ENUM_TEXTBOX_CENTER);
    }

    UI_Common_Draw_FontStr_textbox(lcdram,0,0,176,58,(uint8_t *)gchinesefont_warn_later,APP_COLOR_BLACK,APP_COLOR_CYAN);
    UI_Common_Draw_FontStr_textbox(lcdram,0,118,176,58,(uint8_t *)gchinesefont_warn_stop,APP_COLOR_BLACK,APP_COLOR_YELLOW);
    
}


void UI_Screen_Warn_Alarm_Exit(void)
{

    UI_Common_Cancel_Goback_Handle();
    UI_Screen_Delete_Warn();
    
}


void UI_Screen_Warn_Alarm_shortkeyhandle(void)
{

}

void UI_Screen_Warn_Alarm_holdshortkeyhandle(void)
{
}

void UI_Screen_Warn_Alarm_holdlongkeyhandle(void)
{
}

void UI_Screen_Warn_Alarm_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            Scene_Alarm_Delay();
            UI_Screen_Warn_Alarm_Exit();
            //UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
            Scene_Alarm_Stop();
            UI_Screen_Warn_Alarm_Exit();
            //UI_Screen_draw_Screen();
        }
        break;
        default:
        break;
    }

}

void UI_Screen_Warn_Alarm_tpupslidehandle(void)
{
}

void UI_Screen_Warn_Alarm_tpdownslidehandle(void)
{
}

void UI_Screen_Warn_Alarm_tpleftslidehandle(void)
{
}

void UI_Screen_Warn_Alarm_tprightslidehandle(void)
{

    Scene_Alarm_Delay();
    UI_Screen_Warn_Alarm_Exit();

}





void UI_Screen_Warn_Common_shortkeyhandle(void)
{
    UI_Common_Cancel_Goback_Handle();
    UI_Screen_Delete_Warn();
}

void UI_Screen_Warn_Common_holdshortkeyhandle(void)
{
}

void UI_Screen_Warn_Common_holdlongkeyhandle(void)
{
}

void UI_Screen_Warn_Common_tpclickhandle(int point_x,int point_y)
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

void UI_Screen_Warn_Common_tpupslidehandle(void)
{
}

void UI_Screen_Warn_Common_tpdownslidehandle(void)
{
}

void UI_Screen_Warn_Common_tpleftslidehandle(void)
{
}

void UI_Screen_Warn_Common_tprightslidehandle(void)
{

    UI_Common_Cancel_Goback_Handle();
    UI_Screen_Delete_Warn();

}




void UI_Screen_Warn_Timer_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Timer_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);
    
}

void UI_Screen_Warn_Timer_Display(uint8_t *lcdram)
{

    UI_Common_AddBWsourcePic(lcdram,64,40,(uint8_t*)image_warn_timer_48_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
    UI_Common_Draw_FontStr_textbox(lcdram,8,92,160,68,(uint8_t *)gchinesefont_warn_timer,APP_COLOR_WHITE,APP_COLOR_BLACK);

}


void UI_Screen_Warn_Timer_Exit(void)
{
    UI_Common_Cancel_Goback_Handle();
    UI_Screen_Delete_Warn();
}





void UI_Screen_Warn_Message_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Message_Display(lcdram);

    UI_Common_set_key_handle(UI_Screen_Warn_Message_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Message_tpclickhandle);
    
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Message_tpupslidehandle,
                                    UI_Screen_Warn_Message_tpdownslidehandle,
                                    UI_Screen_Warn_Message_tpleftslidehandle,
                                    UI_Screen_Warn_Message_tprightslidehandle);	

}

void UI_Screen_Warn_Message_Display(uint8_t *lcdram)
{

    RemindMsg_t info;
    int y;
    int x;
    
	uint16_t  temp_data[256];
    uint16_t len = 0;

    char content[16];
    

    App_RemindManage_CurrDetailRead(&info);
    

    if(info.RemindType == PHONE_MESSAGE)
    {
    
        UI_Common_AddBWsourcePic(lcdram,8,8,(uint8_t*)iamge_bw_history_sms_h,APP_COLOR_BLACK,APP_COLOR_GREEN);

        x = 50;
        y = 4;
        memset(temp_data, 0x00, 256);
        len = info.Detail.PhoneMsg.namelen;
        memcpy(temp_data,&(info.Detail.PhoneMsg.name[0]),len*2);
        UI_Common_Drawtextbox_byfontic(lcdram, x, y,116,24,temp_data,len,GB_SIZE_24X24, APP_COLOR_BLACK, APP_COLOR_WHITE);

        x = 50;
        y = 32;

        sprintf(content,"%2d:%2d",info.RTC.hour,info.RTC.min);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(lcdram,x,y,117,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        x = 8;
        y = 52;
        memset(temp_data, 0x00, 256);
        len = info.Detail.PhoneMsg.detaillen;
        memcpy(temp_data,&(info.Detail.PhoneMsg.detail[0]),len*2);
        UI_Common_Drawtextbox_byfontic(lcdram, x, y,160,116,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
        
    }
    else if(info.RemindType == MISS_PHONE_CALL)
    {
    
        UI_Common_AddBWsourcePic(lcdram,8,8,(uint8_t*)iamge_bw_history_call_h,APP_COLOR_BLACK,APP_COLOR_GREEN);

        x = 50;
        y = 4;
        memset(temp_data, 0x00, 256);
        len = info.Detail.PhoneMiss.detaillen;
        memcpy(temp_data,&(info.Detail.PhoneMiss.detail[0]),len*2);
        UI_Common_Drawtextbox_byfontic(lcdram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);

        x = 50;
        y = 32;

        sprintf(content,"%2d:%2d",info.RTC.hour,info.RTC.min);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(lcdram,x,y,117,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        
        
        x = 8;
        y = 52;
        memset(temp_data, 0x00, 256);
        len = info.Detail.PhoneMiss.namelen;
        memcpy(temp_data,&(info.Detail.PhoneMiss.name[0]),len*2);
        UI_Common_Drawtextbox_byfontic(lcdram, x, y,160,116,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);

        
    
    
    }
    else
    {
    
        UI_Common_AddBWsourcePic(lcdram,8,8,(uint8_t*)iamge_bw_history_app_h,APP_COLOR_BLACK,APP_COLOR_GREEN);
        
        x = 50;
        y = 4;
        memset(temp_data, 0x00, 256);
        len = info.Detail.AppMsg.namelen;
        memcpy(temp_data,&(info.Detail.AppMsg.name[0]),len*2);
        UI_Common_Drawtextbox_byfontic(lcdram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);

        
        x = 50;
        y = 32;

        sprintf(content,"%2d:%2d",info.RTC.hour,info.RTC.min);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(lcdram,x,y,117,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        
        x = 8;
        y = 52;
        memset(temp_data, 0x00, 256);
        len = info.Detail.AppMsg.detaillen;
        memcpy(temp_data,&(info.Detail.AppMsg.detail[0]),len*2);
        UI_Common_Drawtextbox_byfontic(lcdram, x, y,160,116,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
        
        
    }



}


void UI_Screen_Warn_Message_Exit(void)
{
    UI_Screen_Delete_Warn();
}


void UI_Screen_Warn_Message_shortkeyhandle(void)
{


    UI_Screen_Warn_Message_Exit();
    //UI_Screen_Delete_All_Warn();
    //App_RemindManage_DeleteAllMsg();
    
}

void UI_Screen_Warn_Message_holdshortkeyhandle(void)
{
}

void UI_Screen_Warn_Message_holdlongkeyhandle(void)
{
}

void UI_Screen_Warn_Message_tpclickhandle(int point_x,int point_y)
{

}

void UI_Screen_Warn_Message_tpupslidehandle(void)
{
}

void UI_Screen_Warn_Message_tpdownslidehandle(void)
{
}

void UI_Screen_Warn_Message_tpleftslidehandle(void)
{
}

void UI_Screen_Warn_Message_tprightslidehandle(void)
{

#if 0
    RemindMsg_t info;
    
    RemindStore_t m_info;
    
    App_RemindManage_CurrDetailRead(&info);
    App_RemindManage_DeleteMsg(info.u16MsgID);
    
    App_RemindManage_DetailRemindRead(&m_info);

    if(m_info.RemindCnt == 0)
    {
        UI_Screen_Warn_Message_Exit();
    }
    else
    {
        UI_Screen_draw_Screen();
    }
#endif

    UI_Screen_Warn_Message_Exit();
    
}



void UI_Screen_Warn_Steptarget_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Steptarget_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Steptarget_Display(uint8_t *lcdram)
{

    UI_Common_AddBWsourcePic(lcdram,64,40,(uint8_t*)image_warn_target_48_h,APP_COLOR_BLACK,APP_COLOR_YELLOW);
    UI_Common_Draw_FontStr_textbox(lcdram,8,92,160,68,(uint8_t *)gchinesefont_warn_target,APP_COLOR_WHITE,APP_COLOR_BLACK);
    
}


void UI_Screen_Warn_Steptarget_Exit(void)
{
    UI_Screen_Delete_Warn();
}


void UI_Screen_Warn_Outsit_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Outsit_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Outsit_Display(uint8_t *lcdram)
{
    UI_Common_AddBWsourcePic(lcdram,64,40,(uint8_t*)image_warn_walk_48_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
    UI_Common_Draw_FontStr_textbox(lcdram,8,92,160,68,(uint8_t *)gchinesefont_warn_walk,APP_COLOR_WHITE,APP_COLOR_BLACK);
}


void UI_Screen_Warn_Outsit_Exit(void)
{
    UI_Screen_Delete_Warn();
}


void UI_Screen_Warn_Btbreak_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Btbreak_Display(lcdram);

    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);
}

void UI_Screen_Warn_Btbreak_Display(uint8_t *lcdram)
{
    UI_Common_AddBWsourcePic(lcdram,64,40,(uint8_t*)image_warn_bt_48_h,APP_COLOR_BLACK,APP_COLOR_RED);
    UI_Common_Draw_FontStr_textbox(lcdram,8,92,160,68,(uint8_t *)gchinesefont_warn_BTbreak,APP_COLOR_WHITE,APP_COLOR_BLACK);
}


void UI_Screen_Warn_Btbreak_Exit(void)
{
    UI_Screen_Delete_Warn();
}

void UI_Screen_Warn_Nospace_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Nospace_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Nospace_Display(uint8_t *lcdram)
{
    UI_Common_AddBWsourcePic(lcdram,64,40,(uint8_t*)image_warn_space_48_h,APP_COLOR_BLACK,APP_COLOR_YELLOW);
    UI_Common_Draw_FontStr_textbox(lcdram,8,92,160,68,(uint8_t *)gchinesefont_warn_space,APP_COLOR_WHITE,APP_COLOR_BLACK);
}


void UI_Screen_Warn_Nospace_Exit(void)
{
    UI_Screen_Delete_Warn();
}

void UI_Screen_Warn_Lowpower_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Lowpower_Display(lcdram);

    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Lowpower_Display(uint8_t *lcdram)
{

    UI_Common_AddBWsourcePic(lcdram,64,40,(uint8_t*)image_warn_battery_empty_48_h,APP_COLOR_BLACK,APP_COLOR_RED);
    UI_Common_Draw_FontStr_textbox(lcdram,8,92,160,68,(uint8_t *)gchinesefont_warn_lowbattery,APP_COLOR_WHITE,APP_COLOR_BLACK);
    
}


void UI_Screen_Warn_Lowpower_Exit(void)
{
    UI_Screen_Delete_Warn();
}



void UI_Screen_Warn_SettingError_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_SettingError_Display(lcdram);

    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);
}

void UI_Screen_Warn_SettingError_Display(uint8_t *lcdram)
{

    UI_Common_AddBWsourcePic(lcdram,64,40,(uint8_t*)iamge_warn_alert_48_h,APP_COLOR_BLACK,APP_COLOR_RED);
    UI_Common_Draw_FontStr_textbox(lcdram,8,92,160,68,(uint8_t *)gchinesefont_setting_error,APP_COLOR_WHITE,APP_COLOR_BLACK);
    
}



void UI_Screen_Warn_SettingError_Exit(void)
{
    UI_Screen_Delete_Warn();
}


Warn_Common_info_s Warn_Common_info;


void UI_Screen_Warn_Common_Init(Enum_Warn_Common_Type type)
{
    int value = UI_Screen_Warn_Get_Warn_Data();
    
    Struct_runningmode_setting running_info;
    Struct_swimmode_setting swim_info;
    Struct_climbingmode_setting climbing_info;

    UI_Screen_RuningModeSetting_Getsetting(&running_info);
    UI_Screen_SwimModeSetting_Getsetting(&swim_info);
    UI_Screen_ClimbingModeSetting_Getsetting(&climbing_info);
    
    memset(&Warn_Common_info,0X00,sizeof(Warn_Common_info_s));

    switch(type)
    {

        case Warn_Common_Type_Running_Target_Distance:
            Warn_Common_info.round_color = APP_COLOR_YELLOW;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_distance;
            Warn_Common_info.info = (uint8_t *)gchinesefont_warn_targetcomplete;
            sprintf(Warn_Common_info.content,"%0.1f",(float)running_info.target_distance/1000);
            break;
        case Warn_Common_Type_Running_Target_Duration:
            Warn_Common_info.round_color = APP_COLOR_YELLOW;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_duration;
            Warn_Common_info.info = (uint8_t *)gchinesefont_warn_targetcomplete;
            sprintf(Warn_Common_info.content,"%d",running_info.target_duration);
            break;
        case Warn_Common_Type_Running_Target_Calorie:
            Warn_Common_info.round_color = APP_COLOR_YELLOW;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_calorie;
            Warn_Common_info.info = (uint8_t *)gchinesefont_warn_targetcomplete;
            sprintf(Warn_Common_info.content,"%d",running_info.target_calorie);
            break;
        case Warn_Common_Type_Running_Warn_Distance:
            Warn_Common_info.round_color = APP_COLOR_GREEN;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_distance;

            switch(running_info.warn_distance)
            {
                case 0:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                break;
                case 500:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_distance_500m_s;
                break;
                case 1000:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_distance_1km_s;
                break;
                case 2000:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_distance_2km_s;
                break;
                case 3000:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_distance_3km_s;
                break;
                case 5000:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_distance_5km_s;
                break;
                default:
                break;
            }
            sprintf(Warn_Common_info.content,"%0.1f",(float)value/1000);
            break;
        case Warn_Common_Type_Running_Warn_Duration:
            Warn_Common_info.round_color = APP_COLOR_GREEN;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_duration;

            switch(running_info.warn_duration)
            {
                case 0:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                break;
                case 5:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_5min_s;
                break;
                case 10:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_10min_s;
                break;
                case 15:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_15min_s;
                break;
                case 20:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_20min_s;
                break;
                case 30:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_30min_s;
                break;
                case 60:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_60min_s;
                break;
                case 90:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_90min_s;
                break;
                case 120:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_120min_s;
                break;
                default:
                break;
            }

            sprintf(Warn_Common_info.content,"%d",value);
            break;
        case Warn_Common_Type_Running_Warn_Calorie:
            Warn_Common_info.round_color = APP_COLOR_GREEN;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_calorie;

            switch(running_info.warn_calorie)
            {
                case 0:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                break;
                case 50:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_calorie_50kcal_s;
                break;
                case 100:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_calorie_100kcal_s;
                break;
                case 150:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_calorie_150kcal_s;
                break;
                case 200:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_calorie_200kcal_s;
                break;
                default:
                break;
            }
            sprintf(Warn_Common_info.content,"%d",value);
            break;
        case Warn_Common_Type_Running_Warn_Speed_Uplimit:
            Warn_Common_info.round_color = APP_COLOR_RED;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_warn_minkm;
            Warn_Common_info.info = NULL;
            sprintf(Warn_Common_info.info_content,"%02d'%02d\"",running_info.speed_uplimit/60,running_info.speed_uplimit%60);
            
            sprintf(Warn_Common_info.content,"%02d'%02d\"",value/60,value%60);
            break;
        case Warn_Common_Type_Running_Warn_Speed_Lowlimit:
            Warn_Common_info.round_color = APP_COLOR_CYAN;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_warn_minkm;
            Warn_Common_info.info = NULL;
            sprintf(Warn_Common_info.info_content,"%02d'%02d\"",running_info.speed_lowlimit/60,running_info.speed_lowlimit%60);
            
            sprintf(Warn_Common_info.content,"%02d'%02d\"",value/60,value%60);
            break;
        case Warn_Common_Type_Running_Warn_Heartrate_Uplimit:
            Warn_Common_info.round_color = APP_COLOR_RED;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_warn_heartrate;

            Warn_Common_info.info = NULL;
            sprintf(Warn_Common_info.info_content,"%d",running_info.heartrate_uplimit);

            sprintf(Warn_Common_info.content,"%d",value);
            break;
        case Warn_Common_Type_Running_Warn_Heartrate_Lowlimit:
            Warn_Common_info.round_color = APP_COLOR_CYAN;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_warn_heartrate;

            Warn_Common_info.info = NULL;
            sprintf(Warn_Common_info.info_content,"%d",running_info.heartrate_lowlimit);

            sprintf(Warn_Common_info.content,"%d",value);
            break;
            
        case Warn_Common_Type_Swim_Target_Laps:
            Warn_Common_info.round_color = APP_COLOR_YELLOW;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_laps;
            Warn_Common_info.info = (uint8_t *)gchinesefont_warn_targetcomplete;
            sprintf(Warn_Common_info.content,"%d",swim_info.target_laps);
            break;
        case Warn_Common_Type_Swim_Target_Duration:
            Warn_Common_info.round_color = APP_COLOR_YELLOW;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_duration;
            Warn_Common_info.info = (uint8_t *)gchinesefont_warn_targetcomplete;
            sprintf(Warn_Common_info.content,"%d",swim_info.target_duration);
            break;
        case Warn_Common_Type_Swim_Target_Calorie:
            Warn_Common_info.round_color = APP_COLOR_YELLOW;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_calorie;
            Warn_Common_info.info = (uint8_t *)gchinesefont_warn_targetcomplete;
            sprintf(Warn_Common_info.content,"%d",swim_info.target_calorie);
            break;
        case Warn_Common_Type_Swim_Warn_Laps:
            Warn_Common_info.round_color = APP_COLOR_GREEN;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_laps;

            switch(swim_info.warn_laps)
            {
                case 0:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                break;
                case 4:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_distance_500m_s;
                break;
                case 8:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_distance_1km_s;
                break;
                case 10:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_distance_2km_s;
                break;
                case 12:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_distance_3km_s;
                break;
                case 16:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_distance_5km_s;
                break;
                case 20:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_distance_5km_s;
                break;
                default:
                break;
            }
            
            sprintf(Warn_Common_info.content,"%d",value);
            break;
        case Warn_Common_Type_Swim_Warn_Duration:
            Warn_Common_info.round_color = APP_COLOR_GREEN;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_duration;
            
            switch(swim_info.warn_duration)
            {
                case 0:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                break;
                case 5:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_5min_s;
                break;
                case 10:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_10min_s;
                break;
                case 15:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_15min_s;
                break;
                case 20:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_20min_s;
                break;
                case 30:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_30min_s;
                break;
                case 60:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_60min_s;
                break;
                case 90:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_90min_s;
                break;
                case 120:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_120min_s;
                break;
                default:
                break;
            }
            sprintf(Warn_Common_info.content,"%d",value);
            break;
        case Warn_Common_Type_Swim_Warn_Calorie:
            Warn_Common_info.round_color = APP_COLOR_GREEN;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_calorie;

            switch(swim_info.warn_calorie)
            {
                case 0:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                break;
                case 50:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_calorie_50kcal_s;
                break;
                case 100:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_calorie_100kcal_s;
                break;
                case 150:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_calorie_150kcal_s;
                break;
                case 200:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_calorie_200kcal_s;
                break;
                default:
                break;
            }
            sprintf(Warn_Common_info.content,"%d",value);
            break;
        case Warn_Common_Type_Climbing_Target_ClimbingDistance:
            Warn_Common_info.round_color = APP_COLOR_YELLOW;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_Climbingdistance;
            Warn_Common_info.info = (uint8_t *)gchinesefont_warn_targetcomplete;
            sprintf(Warn_Common_info.content,"%d",climbing_info.target_climbingdistance);
            break;
        case Warn_Common_Type_Climbing_Target_Distance:
            Warn_Common_info.round_color = APP_COLOR_YELLOW;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_distance;
            Warn_Common_info.info = (uint8_t *)gchinesefont_warn_targetcomplete;
            sprintf(Warn_Common_info.content,"%d",climbing_info.target_distance);
            break;
        case Warn_Common_Type_Climbing_Target_Duration:
            Warn_Common_info.round_color = APP_COLOR_YELLOW;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_duration;
            Warn_Common_info.info = (uint8_t *)gchinesefont_warn_targetcomplete;
            sprintf(Warn_Common_info.content,"%d",climbing_info.target_duration);
            break;
        case Warn_Common_Type_Climbing_Target_Calorie:
            Warn_Common_info.round_color = APP_COLOR_YELLOW;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_calorie;
            Warn_Common_info.info = (uint8_t *)gchinesefont_warn_targetcomplete;
            sprintf(Warn_Common_info.content,"%d",climbing_info.target_calorie);
            break;
        case Warn_Common_Type_Climbing_Warn_Distance:
            Warn_Common_info.round_color = APP_COLOR_GREEN;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_Climbingdistance;

            switch(climbing_info.warn_distance)
            {
                case 0:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                break;
                case 500:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_distance_500m_s;
                break;
                case 1000:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_distance_1km_s;
                break;
                case 2000:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_distance_2km_s;
                break;
                case 3000:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_distance_3km_s;
                break;
                case 5000:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_distance_5km_s;
                break;
                default:
                break;
            }
            sprintf(Warn_Common_info.content,"%0.1f",(float)value/1000);
            break;
        case Warn_Common_Type_Climbing_Warn_Duration:
            Warn_Common_info.round_color = APP_COLOR_GREEN;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_duration;
            Warn_Common_info.info = (uint8_t *)gchinesefont_warn_targetcomplete;
            
            switch(climbing_info.warn_duration)
            {
                case 0:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                break;
                case 5:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_5min_s;
                break;
                case 10:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_10min_s;
                break;
                case 15:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_15min_s;
                break;
                case 20:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_20min_s;
                break;
                case 30:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_30min_s;
                break;
                case 60:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_60min_s;
                break;
                case 90:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_90min_s;
                break;
                case 120:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_duration_120min_s;
                break;
                default:
                break;
            }
            sprintf(Warn_Common_info.content,"%d",value);
            break;
        case Warn_Common_Type_Climbing_Warn_Calorie:
            Warn_Common_info.round_color = APP_COLOR_GREEN;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_target_calorie;
            
            switch(climbing_info.warn_calorie)
            {
                case 0:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                break;
                case 50:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_calorie_50kcal_s;
                break;
                case 100:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_calorie_100kcal_s;
                break;
                case 150:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_calorie_150kcal_s;
                break;
                case 200:
                    Warn_Common_info.info = (uint8_t *)gchinesefont_sportscene_warn_calorie_200kcal_s;
                break;
                default:
                break;
            }
            
            sprintf(Warn_Common_info.content,"%d",value);
            break;
        case Warn_Common_Type_Climbing_Warn_Heartrate_Uplimit:
            Warn_Common_info.round_color = APP_COLOR_RED;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_warn_heartrate;

            Warn_Common_info.info = NULL;
            sprintf(Warn_Common_info.info_content,"%d",climbing_info.heartrate_uplimit);

            sprintf(Warn_Common_info.content,"%d",value);
            break;
        case Warn_Common_Type_Climbing_Warn_Heartrate_Lowlimit:
            Warn_Common_info.round_color = APP_COLOR_CYAN;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_warn_heartrate;

            Warn_Common_info.info = NULL;
            sprintf(Warn_Common_info.info_content,"%d",climbing_info.heartrate_lowlimit);

            sprintf(Warn_Common_info.content,"%d",value);
            break;
        case Warn_Common_Type_Climbing_Warn_Elevation_Uplimit:
            Warn_Common_info.round_color = APP_COLOR_RED;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_elevation;

            Warn_Common_info.info = NULL;
            sprintf(Warn_Common_info.info_content,"%d",climbing_info.elevation_uplimit);

            sprintf(Warn_Common_info.content,"%d",value);
            break;
        case Warn_Common_Type_Climbing_Warn_Elevation_Lowlimit:
            Warn_Common_info.round_color = APP_COLOR_CYAN;
            Warn_Common_info.title = (uint8_t *)gchinesefont_sportscene_elevation;

            Warn_Common_info.info = NULL;
            sprintf(Warn_Common_info.info_content,"%d",climbing_info.elevation_lowlimit);

            sprintf(Warn_Common_info.content,"%d",value);
            break;
            
        default:
            break;

    
    }



}





void UI_Screen_Warn_Common_Running_Target_Distance_Entry(uint8_t *lcdram)
{


    UI_Screen_Warn_Common_Init(Warn_Common_Type_Running_Target_Distance);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Running_Target_Duration_Entry(uint8_t *lcdram)
{


    UI_Screen_Warn_Common_Init(Warn_Common_Type_Running_Target_Duration);
    UI_Screen_Warn_Common_Display(lcdram);

    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Running_Target_Calorie_Entry(uint8_t *lcdram)
{


    UI_Screen_Warn_Common_Init(Warn_Common_Type_Running_Target_Calorie);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}


void UI_Screen_Warn_Common_Running_Warn_Distance_Entry(uint8_t *lcdram)
{


    UI_Screen_Warn_Common_Init(Warn_Common_Type_Running_Warn_Distance);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Running_Warn_Duration_Entry(uint8_t *lcdram)
{


    UI_Screen_Warn_Common_Init(Warn_Common_Type_Running_Warn_Duration);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Running_Warn_Calorie_Entry(uint8_t *lcdram)
{


    UI_Screen_Warn_Common_Init(Warn_Common_Type_Running_Warn_Calorie);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}



void UI_Screen_Warn_Common_Running_Warn_Speed_Uplimit_Entry(uint8_t *lcdram)
{


    UI_Screen_Warn_Common_Init(Warn_Common_Type_Running_Warn_Speed_Uplimit);
    UI_Screen_Warn_Common_Display(lcdram);

    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}



void UI_Screen_Warn_Common_Running_Warn_Speed_Lowlimit_Entry(uint8_t *lcdram)
{


    UI_Screen_Warn_Common_Init(Warn_Common_Type_Running_Warn_Speed_Lowlimit);
    UI_Screen_Warn_Common_Display(lcdram);

    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}


void UI_Screen_Warn_Common_Running_Warn_Heartrate_Uplimit_Entry(uint8_t *lcdram)
{


    UI_Screen_Warn_Common_Init(Warn_Common_Type_Running_Warn_Heartrate_Uplimit);
    UI_Screen_Warn_Common_Display(lcdram);

    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Running_Warn_Heartrate_Lowlimit_Entry(uint8_t *lcdram)
{


    UI_Screen_Warn_Common_Init(Warn_Common_Type_Running_Warn_Heartrate_Lowlimit);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Swim_Target_Laps_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Swim_Target_Laps);
    UI_Screen_Warn_Common_Display(lcdram);

    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Swim_Target_Duration_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Swim_Target_Duration);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Swim_Target_Calorie_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Swim_Target_Calorie);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}



void UI_Screen_Warn_Common_Swim_Warn_Laps_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Swim_Warn_Laps);
    UI_Screen_Warn_Common_Display(lcdram);

    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Swim_Warn_Duration_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Swim_Warn_Duration);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Swim_Warn_Calorie_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Swim_Warn_Calorie);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Climbing_Target_ClimbingDistance_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Climbing_Target_ClimbingDistance);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Climbing_Target_Distance_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Climbing_Target_Distance);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Climbing_Target_Duration_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Climbing_Target_Duration);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Climbing_Target_Calorie_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Climbing_Target_Calorie);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}


void UI_Screen_Warn_Common_Climbing_Warn_Distance_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Climbing_Warn_Distance);
    UI_Screen_Warn_Common_Display(lcdram);

    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Climbing_Warn_Duration_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Climbing_Warn_Duration);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Climbing_Warn_Calorie_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Climbing_Warn_Calorie);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}


void UI_Screen_Warn_Common_Climbing_Warn_Elevation_Uplimit_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Climbing_Warn_Elevation_Uplimit);
    UI_Screen_Warn_Common_Display(lcdram);

    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Climbing_Warn_Elevation_Lowlimit_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Climbing_Warn_Elevation_Lowlimit);
    UI_Screen_Warn_Common_Display(lcdram);

    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Climbing_Warn_Heartrate_Uplimit_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Climbing_Warn_Heartrate_Uplimit);
    UI_Screen_Warn_Common_Display(lcdram);
    
    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}

void UI_Screen_Warn_Common_Climbing_Warn_Heartrate_Lowlimit_Entry(uint8_t *lcdram)
{

    UI_Screen_Warn_Common_Init(Warn_Common_Type_Climbing_Warn_Heartrate_Lowlimit);
    UI_Screen_Warn_Common_Display(lcdram);

    UI_Common_Set_Goback_Handle(warn_show_time,UI_Screen_Delete_Warn);

    UI_Common_set_key_handle(UI_Screen_Warn_Common_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_Warn_Common_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_Warn_Common_tpupslidehandle,
                                    UI_Screen_Warn_Common_tpdownslidehandle,
                                    UI_Screen_Warn_Common_tpleftslidehandle,
                                    UI_Screen_Warn_Common_tprightslidehandle);

}


void UI_Screen_Warn_Common_Display(uint8_t *lcdram)
{

    int len = strlen(Warn_Common_info.content);
    
    UI_Common_Shake();

    UI_Common_Draw_Annulus(lcdram,87,87,87,83,Warn_Common_info.round_color,TRUE);
    UI_Common_Draw_FontStr_textbox(lcdram,24,24,128,24,(uint8_t *)Warn_Common_info.title,APP_COLOR_WHITE,APP_COLOR_BLACK);

    if(len!=0)
    {
        UI_Common_Draw_NumberImage_textbox_Bystringinfo(lcdram,8, 70, 168, 36,APP_COLOR_WHITE,Warn_Common_info.content,len,36,ENUM_TEXTBOX_CENTER);
    }
    
    if(Warn_Common_info.info!=NULL)
    {
        UI_Common_Draw_FontStr_textbox(lcdram,24,128,128,16,(uint8_t *)Warn_Common_info.info,APP_COLOR_WHITE,APP_COLOR_BLACK);
    }
    else
    {
       UI_Common_Draw_AscStr_textbox(lcdram,24,128,128,16,16,APP_COLOR_WHITE,Warn_Common_info.info_content,strlen(Warn_Common_info.info_content),ENUM_TEXTBOX_CENTER);
    }

    
}



void UI_Screen_Warn_Common_Exit(void)
{
    UI_Screen_Delete_Warn();
}





