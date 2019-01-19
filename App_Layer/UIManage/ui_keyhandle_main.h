#ifndef UI_KEYHANDLE_MAIN_H
#define UI_KEYHANDLE_MAIN_H
#include "mid_key.h"




typedef void (*func_key_handle)(void);



void UI_Common_set_key_handle(func_key_handle short_handle,func_key_handle hold_short_handle,func_key_handle holdlong_handle);
//void UI_Common_set_key_handle(void *short_handle,void *hold_short_handle,void *holdlong_handle);
void UI_Common_do_key_handle(eMidKeyVal keyvalue);
void UI_Common_clean_key_handle(void);


void UI_Common_Shake(void);
extern void UI_Commom_Lockinfo_Reset(void);
#endif

