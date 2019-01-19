

#include "ui_screen_modelist.h"



void UI_Screen_Modelist_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Modelist)
        return;

    UI_Common_Clear_Screen(temp_ram);
    
    UI_Common_ShowIconList(temp_ram);
    
    UI_Display_Prepare(temp_ram);

}

void UI_Screen_Modelist_Entry(void)
{

    UI_Common_ScreenCleanListInfo();

    curr_list.curr_list_page = 0;
    curr_list.curr_list_highlight = 0;

    curr_list.icon_list[0]=(uint8_t *)run_h;
    curr_list.icon_list[1]=(uint8_t *)climb_h;
    curr_list.icon_list[2]=(uint8_t *)swim_h;
    curr_list.icon_list[3]=(uint8_t *)histo_h;
    curr_list.icon_list[4]=(uint8_t *)stopwatch_h;
    curr_list.icon_list[5]=(uint8_t *)timer_h;
    curr_list.icon_list[6]=(uint8_t *)alarm_h;
    curr_list.icon_list[7]=(uint8_t *)findhone_h;
    curr_list.icon_list[8]=(uint8_t *)settings_h;

    curr_list.string_list[0]=(uint8_t *)gchinesefont_sportscene_running;
    curr_list.string_list[1]=(uint8_t *)gchinesefont_sportscene_climbing;
    curr_list.string_list[2]=(uint8_t *)gchinesefont_sportscene_swim;
    curr_list.string_list[3]=(uint8_t *)gchinesefont_sportscene_history;
    curr_list.string_list[4]=(uint8_t *)gchinesefont_sportscene_stopwatch;
    curr_list.string_list[5]=(uint8_t *)gchinesefont_sportscene_timer;
    curr_list.string_list[6]=(uint8_t *)gchinesefont_sportscene_alarm;
    curr_list.string_list[7]=(uint8_t *)gchinesefont_sportscene_findphone;
    curr_list.string_list[8]=(uint8_t *)gchinesefont_sportscene_setting;

    curr_list.total_list_page_count = 3;
    curr_list.total_count = 9;

    UI_Screen_Modelist_Display();
    
    UI_Common_set_key_handle(UI_Screen_Modelist_shortkeyhandle,NULL,NULL);
    
    UI_Common_set_tp_click_handle(UI_Screen_Modelist_tpclickhandle);
    
    UI_Common_set_tp_slide_handle(UI_Screen_Modelist_tpupslidehandle,
                                    UI_Screen_Modelist_tpdownslidehandle,
                                    UI_Screen_Modelist_tpleftslidehandle,
                                    UI_Screen_Modelist_tprightslidehandle);

                                    
}

void UI_Screen_Modelist_Exit(void)
{


}

void UI_Screen_Modelist_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    
    UI_Screen_draw_Screen();

}

void UI_Screen_Modelist_holdshortkeyhandle(void)
{
}

void UI_Screen_Modelist_holdlongkeyhandle(void)
{
}

int UI_Screen_Modelist_Getrange_Bypoint(int point_x,int point_y)
{

    int i = 0;

    if(point_y>=0 && point_y<= 55)
    {
        i=0;
    }
    else if(point_y >55 && point_y<= 111)
    {
        i=1;
    }
    else
    {
        i=2;
    }

    return i;

}


void UI_Screen_Modelist_tpclickhandle(int point_x,int point_y)
{

    int curr_range = 0;
    
    curr_range = UI_Screen_Modelist_Getrange_Bypoint(point_x,point_y);
    curr_list.curr_list_highlight = curr_list.curr_list_page*3+curr_range;

    switch(curr_list.curr_list_highlight)
    {
        case 0:
        {
            UI_Set_Curr_ScreenID(Common_Screen_MainID_Running);
            UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
            UI_Screen_draw_Screen();
        }
        break;
        case 1:
            UI_Set_Curr_ScreenID(Common_Screen_MainID_Climbing);
            UI_Set_Curr_SubScreenID_Climbingmode(Common_Screen_SubID_ClimbingMode_Prepare);
            UI_Screen_draw_Screen();
        break;
        case 2:
            UI_Set_Curr_ScreenID(Common_Screen_MainID_Swim);
            UI_Set_Curr_SubScreenID_Swimmode(Common_Screen_SubID_SwimMode_Prepare);
            UI_Screen_draw_Screen();
        break;
        case 3:
            UI_Set_Curr_ScreenID(Common_Screen_MainID_SportHistory);
            UI_Screen_draw_Screen();
        break;
        case 4:
            UI_Set_Curr_ScreenID(Common_Screen_MainID_Stopwatch);
            UI_Screen_draw_Screen();
        break;
        case 5:
            UI_Set_Curr_ScreenID(Common_Screen_MainID_Countdown);
            UI_Screen_draw_Screen();
        break;
        case 6:
            UI_Set_Curr_ScreenID(Common_Screen_MainID_Alarm);
            UI_Screen_draw_Screen();
        break;
        case 7:
            UI_Set_Curr_ScreenID(Common_Screen_MainID_Findphone);
            UI_Screen_draw_Screen();
        break;
        case 8:
            UI_Set_Curr_ScreenID(Common_Screen_MainID_Setting);
            UI_Screen_draw_Screen();
        break;
        default:
            UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
            UI_Screen_draw_Screen();
            break;
    }

    
}

void UI_Screen_Modelist_tpupslidehandle(void)
{
    
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_Modelist_Display();
    UI_Screen_Redraw_Screen();
    
}

void UI_Screen_Modelist_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_Modelist_Display();
    UI_Screen_Redraw_Screen();
}

void UI_Screen_Modelist_tpleftslidehandle(void)
{


}

void UI_Screen_Modelist_tprightslidehandle(void)
{

}







