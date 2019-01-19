#include "ui_tphandle_main.h"
#include "ui_display_common.h"


void (*ui_tphandle_click_callback)(int point_x,int point_y) = NULL;

func_tphandle_click_callback ui_tphandle_click_callback;

//void (*ui_tphandle_slide_up_callback)() = NULL;
//void (*ui_tphandle_slide_down_callback)() = NULL;
//void (*ui_tphandle_slide_left_callback)() = NULL;
//void (*ui_tphandle_slide_right_callback)() = NULL;

func_tphandle_slide_callback ui_tphandle_slide_up_callback;
func_tphandle_slide_callback ui_tphandle_slide_down_callback;
func_tphandle_slide_callback ui_tphandle_slide_left_callback;
func_tphandle_slide_callback ui_tphandle_slide_right_callback;

void UI_Common_set_tp_click_handle(func_tphandle_click_callback func_tp_click)
{

    ui_tphandle_click_callback = func_tp_click;

}
void UI_Common_set_tp_slide_handle(func_tphandle_slide_callback func_up_slide,func_tphandle_slide_callback func_down_slide,func_tphandle_slide_callback func_left_slide,func_tphandle_slide_callback func_right_slide)
{
    ui_tphandle_slide_up_callback = func_up_slide;
    ui_tphandle_slide_down_callback = func_down_slide;
    ui_tphandle_slide_left_callback = func_left_slide;
    ui_tphandle_slide_right_callback = func_right_slide;

}

void UI_Common_do_tp_click_handle(int32 point_x,int32 point_y)
{
    UI_Commom_Lockinfo_Reset();
//    RTT_DEBUG_printf(0,"UI_Common_do_tp_click_handle = %d \n",curr_run_screen_info.is_run);
    if(curr_run_screen_info.is_run == 1||curr_run_screen_info.is_ready == 0)
        return;
    if(ui_tphandle_click_callback!=NULL)
        ui_tphandle_click_callback(point_x,point_y);


}
void UI_Common_do_tp_slide_handle(eTouchFlickDirection tp_slide)
{

    UI_Commom_Lockinfo_Reset();
//    RTT_DEBUG_printf(0,"UI_Common_do_tp_slide_handle = %d \n",curr_run_screen_info.is_run);
    if(curr_run_screen_info.is_run == 1||curr_run_screen_info.is_ready == 0)
        return;
//    RTT_DEBUG_printf(0, "UI_Common_do_tp_slide_handle %d",tp_slide);

    switch(tp_slide)
    {
        case eTouchFlickUp:
            if(ui_tphandle_slide_up_callback!=NULL)
                ui_tphandle_slide_up_callback();
        break;
        case eTouchFlickDown:
            if(ui_tphandle_slide_down_callback!=NULL)
                ui_tphandle_slide_down_callback();
        break;
        case eTouchFlickLeft:
            if(ui_tphandle_slide_left_callback!=NULL)
                ui_tphandle_slide_left_callback();
        break;
        case eTouchFlickRight:
            if(ui_tphandle_slide_right_callback!=NULL)
                ui_tphandle_slide_right_callback();
        break;
        default:
        break;

    }

}


/*

      0     |     1
------------------------
            |
      2     |     3
            |
------------------------
            |
      5     |     6

*/


Enum_Common_ListScreen_Tprange UI_Common_List_Get_Tprange_Bypoint(int32 point_x,int32 point_y)
{
	
    Enum_Common_ListScreen_Tprange temp_range = Enum_Common_ListScreen_Tprange_MAX;
	
    if(point_y>=0 && point_y<= 55)
    {
        if(point_x>=0 && point_x<= 87)
        {
            temp_range=Enum_Common_ListScreen_Tprange_0;
        }
        else
        {
            temp_range=Enum_Common_ListScreen_Tprange_1;
        }
    }
    else if(point_y >55 && point_y<= 111)
    {
        if(point_x>=0 && point_x<= 87)
        {
            temp_range=Enum_Common_ListScreen_Tprange_2;
        }
        else
        {
            temp_range=Enum_Common_ListScreen_Tprange_3;
        }
    }
    else
    {

        if(point_x>=0 && point_x<= 87)
        {
            temp_range=Enum_Common_ListScreen_Tprange_4;
        }
        else
        {
           temp_range=Enum_Common_ListScreen_Tprange_5;
        }
    }

    return temp_range;

}


void UI_Common_clean_tp_handle(void)
{
    UI_Common_set_tp_click_handle(NULL);
    UI_Common_set_tp_slide_handle(NULL,NULL,NULL,NULL);
    
}


