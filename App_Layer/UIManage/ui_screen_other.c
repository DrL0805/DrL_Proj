

#include "ui_screen_other.h"
#include "app_systerm.h"
#include "ui_screen_dateandtime.h"

#if 0
void UI_Screen_OTA_Display(void)
{
    //UI_Common_AddBWsourcePic(lcdram,64,40,(uint8_t*)iamge_warn_update_48_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
    //UI_Common_Draw_FontStr_textbox(lcdram,8,92,160,68,(uint8_t *)gchinesefont_warn_update,APP_COLOR_WHITE,APP_COLOR_BLACK);
    
}
#endif
void UI_Screen_OTA_Entry(void)
{
    //UI_Screen_OTA_Display();
    UI_Common_set_key_handle(UI_Screen_OTA_shortkeyhandle,NULL,NULL);
}

void UI_Screen_OTA_Exit(void)
{
}

void UI_Screen_OTA_shortkeyhandle(void)
{
}

void UI_Screen_OTA_holdshortkeyhandle(void)
{
    
}

void UI_Screen_OTA_holdlongkeyhandle(void)
{
}


void UI_Screen_OTA_Show(void)
{
    UI_Set_Curr_ScreenID(Common_Screen_MainID_OTA);
    UI_Screen_draw_Screen();
}



void UI_Screen_Charging_Display(void)
{
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    //Mid_Bat_ChargeStateRead(uint8 *dataTemp);

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Charging)
        return;

    UI_Common_Clear_Screen(temp_ram);
        
    UI_Common_AddPic(temp_ram,64,40,(uint8_t*)iamge_warn_battery_charge_48_h);
    UI_Common_Draw_FontStr_textbox(temp_ram,8,92,160,68,(uint8_t *)gchinesefont_warn_charging,APP_COLOR_WHITE,APP_COLOR_BLACK);
    
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_Charging_Entry(void)
{
    UI_Commom_Set_Allow_Lockstate1(1);
    UI_Commom_Set_Allow_Lockstate2(0);
    UI_Screen_Charging_Display();
    
    UI_Common_clean_key_handle();
}

void UI_Screen_Charging_Exit(void)
{

    AppSysStateType_e state =  App_Sys_StateGet();
    
    UI_Commom_Set_Allow_Lockstate1(1);
    UI_Commom_Set_Allow_Lockstate2(1);
    UI_Commom_Lockinfo_Reset();
    //RTT_DEBUG_printf(0,"UI_Screen_Charging_Exit = %d",state);
    
    if(state==eAppSysStateStore)
    {
        UI_Set_Curr_ScreenID(Common_Screen_MainID_Store);
        UI_Screen_draw_Screen();
    }
    else
    {
        UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
        UI_Screen_draw_Screen();
    }



}

void UI_Screen_Charging_shortkeyhandle(void)
{
}

void UI_Screen_Charging_holdshortkeyhandle(void)
{
    
}

void UI_Screen_Charging_holdlongkeyhandle(void)
{
}


void UI_Screen_Charging_Show(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_Charging);
    UI_Screen_draw_Screen();
}


extern void App_TestDataGet(uint32_t* DataBuf);


void UI_Screen_Test_Display(void)
{

    uint32_t info[32]={0};
    int i;
    int x,y;
    char temp_value[32];
    int len = 0;
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Test)
        return;

    UI_Common_Clear_Screen(temp_ram);

    App_TestDataGet(info);

    for(i=0;i<22;i++)
    {

        if(i%2 == 0)
        {
            x = 0;
        }
        else
        {
            x = 88;
        }

        y = 16*(i/2)+1;

        sprintf(temp_value,"%d",info[i]);
        
        len = strlen(temp_value);
        
        UI_Common_AddAsc2Str(temp_ram,x,y,(int8_t *)temp_value,len,12,APP_COLOR_BLACK,APP_COLOR_WHITE);
    
    }

    UI_Display_Prepare(temp_ram);
}

void UI_Screen_Test_Entry(void)
{
    UI_Screen_Test_Display();
    UI_Common_set_key_handle(UI_Screen_Test_shortkeyhandle,NULL,NULL);
}

void UI_Screen_Test_Exit(void)
{
}

void UI_Screen_Test_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();
}

void UI_Screen_Test_holdshortkeyhandle(void)
{
    
}

void UI_Screen_Test_holdlongkeyhandle(void)
{
}



extern void App_RemindManage_GetCancelMsgId(uint16 *pu16MsgId);


void UI_Screen_Test_Display_App(void)
{

    #if 0
    uint16 info;
    int i;

    char temp_value[32];
    int len = 0;

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Test_App)
        return;

    UI_Common_Clear_Screen(temp_ram);

    
    App_RemindManage_GetCancelMsgId(&info);


    //sprintf(temp_value,"%d",info);
    sprintf(temp_value,"0123456789");
    len = strlen(temp_value);
    UI_Common_AddAsc2Str(temp_ram,0,0,(int8_t *)temp_value,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
    UI_Common_AddAsc2Str(temp_ram,0,17,(int8_t *)temp_value,len,12,APP_COLOR_BLACK,APP_COLOR_WHITE);

    sprintf(temp_value,"ABCDEFG abcdefg");
    len = strlen(temp_value);
    
    UI_Common_AddAsc2Str(temp_ram,0,30,(int8_t *)temp_value,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
    UI_Common_AddAsc2Str(temp_ram,0,48,(int8_t *)temp_value,len,12,APP_COLOR_BLACK,APP_COLOR_WHITE);

    sprintf(temp_value,"HIJKLMN hijklmn");
    len = strlen(temp_value);
    
    UI_Common_AddAsc2Str(temp_ram,0,60,(int8_t *)temp_value,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
    UI_Common_AddAsc2Str(temp_ram,0,79,(int8_t *)temp_value,len,12,APP_COLOR_BLACK,APP_COLOR_WHITE);

    sprintf(temp_value,"OPQ RST opq ret");
    len = strlen(temp_value);
    
    UI_Common_AddAsc2Str(temp_ram,0,90,(int8_t *)temp_value,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
    UI_Common_AddAsc2Str(temp_ram,0,109,(int8_t *)temp_value,len,12,APP_COLOR_BLACK,APP_COLOR_WHITE);


    sprintf(temp_value,"UVW XYZ uvw xyz");
    len = strlen(temp_value);
    
    UI_Common_AddAsc2Str(temp_ram,0,120,(int8_t *)temp_value,len,16,APP_COLOR_BLACK,APP_COLOR_WHITE);
    UI_Common_AddAsc2Str(temp_ram,0,139,(int8_t *)temp_value,len,12,APP_COLOR_BLACK,APP_COLOR_WHITE);
    
    
    //UI_Common_AddBWsourcePic(temp_ram,0,0,(uint8_t*)gchinesefont_detail_test,APP_COLOR_BLACK,APP_COLOR_WHITE);
    //UI_Common_AddBWsourcePic(temp_ram,0,64,(uint8_t*)gchinesefont_detail_test3,APP_COLOR_BLACK,APP_COLOR_WHITE);
    //UI_Common_AddBWsourcePic(temp_ram,0,80,(uint8_t*)gchinesefont_detail_test1,APP_COLOR_BLACK,APP_COLOR_WHITE);

    
    UI_Display_Prepare(temp_ram);

    #endif
    
}



void UI_Screen_Test_App_Entry(void)
{
    UI_Screen_Test_Display_App();
    UI_Common_set_key_handle(UI_Screen_Test_App_shortkeyhandle,NULL,NULL);
}

void UI_Screen_Test_App_Exit(void)
{
}

void UI_Screen_Test_App_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();
}

void UI_Screen_Test_App_holdshortkeyhandle(void)
{
    
}

void UI_Screen_Test_App_holdlongkeyhandle(void)
{
}

void UI_Screen_Test_App_Show(void)
{
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Test_App);
    UI_Screen_draw_Screen();
}


void UI_Screen_Reset_Display(void)
{
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Reset)
        return;

    UI_Common_Clear_Screen(temp_ram);
    UI_Common_AddBWsourcePic(temp_ram,64,40,(uint8_t*)image_reset_48_h,APP_COLOR_BLACK,APP_COLOR_RED);
    UI_Display_Prepare(temp_ram);
}

void UI_Screen_Reset_Entry(void)
{

    UI_Screen_Reset_Display();
    
    UI_Common_clean_key_handle();
    UI_Common_clean_tp_handle();
    
    
}

void UI_Screen_Reset_Exit(void)
{
}

void UI_Screen_Reset_Show(void)
{
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Reset);
    UI_Screen_draw_Screen();
}





