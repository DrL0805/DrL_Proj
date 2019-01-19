#ifndef UI_TPHANDLE_MAIN_H
#define UI_TPHANDLE_MAIN_H

#include "drv_touch.h"

typedef void (*func_tphandle_click_callback)(int point_x,int point_y);
typedef void (*func_tphandle_slide_callback)(void);

void UI_Common_set_tp_click_handle(func_tphandle_click_callback func_tp_click);
void UI_Common_set_tp_slide_handle(func_tphandle_slide_callback func_up_slide,func_tphandle_slide_callback func_down_slide,func_tphandle_slide_callback func_left_slide,func_tphandle_slide_callback func_right_slide);

void UI_Common_do_tp_click_handle(int32 point_x,int32 point_y);
void UI_Common_do_tp_slide_handle(eTouchFlickDirection tp_slide);


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


typedef enum 
{
	Enum_Common_ListScreen_Tprange_0,
	Enum_Common_ListScreen_Tprange_1,
	Enum_Common_ListScreen_Tprange_2,
	Enum_Common_ListScreen_Tprange_3,
	Enum_Common_ListScreen_Tprange_4,
	Enum_Common_ListScreen_Tprange_5,
	Enum_Common_ListScreen_Tprange_MAX,
}Enum_Common_ListScreen_Tprange;

Enum_Common_ListScreen_Tprange UI_Common_List_Get_Tprange_Bypoint(int32 point_x,int32 point_y);


void UI_Common_clean_tp_handle(void);

extern void UI_Commom_Lockinfo_Reset(void);


#endif

