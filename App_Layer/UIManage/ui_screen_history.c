

#include "ui_screen_history.h"


static int curr_detail_index = 0;


void UI_Screen_History_Display(void)
{

    RemindStore_t info;
        
	//uint8_t fontdata[256];
	//font_para_t fontinfo;
    //int i = 0;

    int x =0;
    int y =0;
    //int width =0;
    //int height =0;

    
	uint16_t temp_data[256];
    uint16_t len = 0;

    int curr_index = 0;
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_History)
        return;

    UI_Common_Clear_Screen(temp_ram);
    
    App_RemindManage_DetailRemindRead(&info);

    if(info.RemindCnt == 0)
    {
        UI_Common_AddBWsourcePic(temp_ram,72,54,(uint8_t*)image_msg_outline_32_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        UI_Common_Draw_FontStr_textbox(temp_ram,8,98,160,24,(uint8_t *)gchinesefont_message_nomessage,APP_COLOR_WHITE,APP_COLOR_BLACK);
    }
    else 
    {

        if(info.RemindCnt >= 1)
        {
            
            curr_index = info.FirstPos%5;

            if(info.RemindMsg[curr_index].RemindType == PHONE_MESSAGE)
            {


                UI_Common_AddBWsourcePic(temp_ram,8,11,(uint8_t*)iamge_bw_history_sms_h,APP_COLOR_BLACK,APP_COLOR_GREEN);

                x = 52;
                y = 8;

                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.PhoneMsg.namelen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMsg.name[0]),len);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len,GB_SIZE_24X24, APP_COLOR_BLACK, APP_COLOR_WHITE);

                x = 52;
                y = 34;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.PhoneMsg.detaillen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMsg.detail[0]),len);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
                
                
            }
            else if(info.RemindMsg[curr_index].RemindType == MISS_PHONE_CALL)
            {
            
                UI_Common_AddBWsourcePic(temp_ram,8,11,(uint8_t*)iamge_bw_history_call_h,APP_COLOR_BLACK,APP_COLOR_GREEN);
                
                x = 52;
                y = 8;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.PhoneMiss.detaillen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMiss.detail[0]),len);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);
                
                x = 52;
                y = 34;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.PhoneMiss.namelen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMiss.name[0]),len);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
            
            }
            else
            {
            
                UI_Common_AddBWsourcePic(temp_ram,8,11,(uint8_t*)iamge_bw_history_app_h,APP_COLOR_BLACK,APP_COLOR_GREEN);

                
                x = 52;
                y = 8;

                #if 0
                for(i=0;i<info.RemindMsg[0].Detail.AppMsg.namelen;i++)
                {
                    
                    
                    fontinfo.dataAddr = fontdata;
                    fontinfo.sizeKind = GB_SIZE_24X24;
                    fontinfo.code.codeUnicode = info.RemindMsg[0].Detail.AppMsg.name[i];
                    memset(fontdata, 0x00, 256);
                    Mid_Font_ReadUnicode(&fontinfo);
                
                    UI_Common_AddFont_Byfontic(lcdram,x,y,fontinfo.wordSize.wordWidth,fontinfo.wordSize.wordHeight,fontdata,APP_COLOR_BLACK,APP_COLOR_WHITE);
                    x= x+fontinfo.wordSize.wordWidth;
                    
                }
                #endif
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.AppMsg.namelen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.AppMsg.name[0]),len*2);
                
                
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);

                
                x = 52;
                y = 34;

                #if 0
                for(i=0;i<info.RemindMsg[0].Detail.AppMsg.detaillen;i++)
                {
                
                    fontinfo.dataAddr = fontdata;
                    fontinfo.sizeKind = GB_SIZE_16X16;
                    fontinfo.code.codeUnicode = info.RemindMsg[0].Detail.AppMsg.detail[i];
                    memset(fontdata, 0x00, 256);
                    Mid_Font_ReadUnicode(&fontinfo);
                
                    UI_Common_AddFont_Byfontic(lcdram,x,y,fontinfo.wordSize.wordWidth,fontinfo.wordSize.wordHeight,fontdata,APP_COLOR_BLACK,APP_COLOR_WHITE);
                    x= x+fontinfo.wordSize.wordWidth;

                }
                #else
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.AppMsg.detaillen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.AppMsg.detail[0]),len*2);
                
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,16,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
                #endif

                
                
                
            }

        
        }
        
        if(info.RemindCnt >= 2)
        {

        
        curr_index = (info.FirstPos+1)%5;

        if(info.RemindMsg[curr_index].RemindType == PHONE_MESSAGE)
        {
        
            UI_Common_AddBWsourcePic(temp_ram,8,70,(uint8_t*)iamge_bw_history_sms_h,APP_COLOR_BLACK,APP_COLOR_GREEN);

            
            x = 52;
            y = 8+59;
            
            memset(temp_data, 0x00, 256);
            len = info.RemindMsg[curr_index].Detail.PhoneMsg.namelen;
            memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMsg.name[0]),len*2);
            UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len,GB_SIZE_24X24, APP_COLOR_BLACK, APP_COLOR_WHITE);
            
            x = 52;
            y = 34+59;;
            memset(temp_data, 0x00, 256);
            len = info.RemindMsg[curr_index].Detail.PhoneMsg.detaillen;
            memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMsg.detail[0]),len*2);
            UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
            
        
            
        }
        else if(info.RemindMsg[curr_index].RemindType == MISS_PHONE_CALL)
        {

            UI_Common_AddBWsourcePic(temp_ram,8,70,(uint8_t*)iamge_bw_history_call_h,APP_COLOR_BLACK,APP_COLOR_GREEN);
            x = 52;
            y = 8+59;
            memset(temp_data, 0x00, 256);
            len = info.RemindMsg[curr_index].Detail.PhoneMiss.detaillen;
            memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMiss.detail[0]),len*2);
            UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);
            
            x = 52;
            y = 34+59;
            memset(temp_data, 0x00, 256);
            len = info.RemindMsg[curr_index].Detail.PhoneMiss.namelen;
            memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMiss.name[0]),len*2);
            UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
            
        
        
        }
        else
        {
        
            UI_Common_AddBWsourcePic(temp_ram,8,70,(uint8_t*)iamge_bw_history_app_h,APP_COLOR_BLACK,APP_COLOR_GREEN);
            
            x = 52;
            y = 8+59;
            memset(temp_data, 0x00, 256);
            len = info.RemindMsg[curr_index].Detail.AppMsg.namelen;
            memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.AppMsg.name[0]),len*2);
            UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);
            
            
            x = 52;
            y = 34+59;
            memset(temp_data, 0x00, 256);
            len = info.RemindMsg[curr_index].Detail.AppMsg.detaillen;
            memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.AppMsg.detail[0]),len*2);
            UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,16,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
            
        }
        

        
        }

        if(info.RemindCnt >= 3)
        {
            UI_Common_Draw_Hline(temp_ram,4,123,168,1,APP_COLOR_WHITE,TRUE);
            UI_Common_AddBWsourcePic(temp_ram,60,146,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            UI_Common_AddBWsourcePic(temp_ram,84,146,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            UI_Common_AddBWsourcePic(temp_ram,108,146,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }

    }
    

    UI_Display_Prepare(temp_ram);

}

void UI_Screen_History_Entry(void)
{

    UI_Screen_History_Display();
    
    UI_Common_set_key_handle(UI_Screen_History_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_History_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_History_tpupslidehandle,
                                    UI_Screen_History_tpdownslidehandle,
                                    UI_Screen_History_tpleftslidehandle,
                                    UI_Screen_History_tprightslidehandle);
    
}

void UI_Screen_History_Exit(void)
{
}

void UI_Screen_History_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    
    UI_Screen_draw_Screen();

}

void UI_Screen_History_holdshortkeyhandle(void)
{
}

void UI_Screen_History_holdlongkeyhandle(void)
{
}

void UI_Screen_History_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    RemindStore_t info;

    
    App_RemindManage_DetailRemindRead(&info);
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);
    
    RTT_DEBUG_printf(0,"UI_Screen_History_tpclickhandle=%d---%d",curr_range,info.RemindCnt);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {

            if(info.RemindCnt >= 1)
            {
                curr_detail_index = 0;

                UI_Set_Curr_ScreenID(Common_Screen_MainID_History_Detail);
                UI_Screen_draw_Screen();
            }

        
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            if(info.RemindCnt >= 2)
            {
                curr_detail_index = 1;

                UI_Set_Curr_ScreenID(Common_Screen_MainID_History_Detail);
                UI_Screen_draw_Screen();
            }
        
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {

            if(info.RemindCnt >= 3)
            {
            
                UI_Set_Curr_ScreenID(Common_Screen_MainID_History_List);
                UI_Screen_draw_Screen();
            }
        
        }
        break;
        default:
        break;
    }


}



void UI_Screen_History_tpupslidehandle(void)
{

    //curr_run_screen_info.run_type = ENUM_ROUND_UP;
    UI_Common_Show_RunScreen_Prepare(ENUM_ROUND_UP);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();


}

void UI_Screen_History_tpdownslidehandle(void)
{

    //curr_run_screen_info.run_type = ENUM_ROUND_UP;
    UI_Common_Show_RunScreen_Prepare(ENUM_ROUND_DOWN);
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Compass);
    UI_Screen_draw_Screen();

}

void UI_Screen_History_tpleftslidehandle(void)
{
}

void UI_Screen_History_tprightslidehandle(void)
{



}



static int history_list_page = 0;

void UI_Screen_History_List_Display(void)
{


    RemindStore_t info;
        
    
	//uint8_t fontdata[256];
	//font_para_t fontinfo;
    //int i = 0;

    int x =0;
    int y =0;
    //int width =0;
    //int height =0;

    
	uint16_t  temp_data[256];
    uint16_t len = 0;

    int curr_index = 0;

    
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_History_List)
        return;

    UI_Common_Clear_Screen(temp_ram);

    
    App_RemindManage_DetailRemindRead(&info);

    if(history_list_page ==0)
    {
        if(info.RemindCnt >= 1)
        {
            
            curr_index = info.FirstPos%5;

            if(info.RemindMsg[curr_index].RemindType == PHONE_MESSAGE)
            {


                UI_Common_AddBWsourcePic(temp_ram,8,11,(uint8_t*)iamge_bw_history_sms_h,APP_COLOR_BLACK,APP_COLOR_GREEN);

                x = 52;
                y = 8;

                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.PhoneMsg.namelen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMsg.name[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len,GB_SIZE_24X24, APP_COLOR_BLACK, APP_COLOR_WHITE);

                x = 52;
                y = 34;

                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.PhoneMsg.detaillen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMsg.detail[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
                
            }
            else if(info.RemindMsg[curr_index].RemindType == MISS_PHONE_CALL)
            {
            
                UI_Common_AddBWsourcePic(temp_ram,8,11,(uint8_t*)iamge_bw_history_call_h,APP_COLOR_BLACK,APP_COLOR_GREEN);
                
                x = 52;
                y = 8;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.PhoneMiss.detaillen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMiss.detail[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);
                
                x = 52;
                y = 34;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.PhoneMiss.namelen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMiss.name[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);


            
            }
            else
            {
            
                UI_Common_AddBWsourcePic(temp_ram,8,11,(uint8_t*)iamge_bw_history_app_h,APP_COLOR_BLACK,APP_COLOR_GREEN);

                
                x = 52;
                y = 8;

                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.AppMsg.namelen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.AppMsg.name[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);

                
                x = 52;
                y = 34;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.AppMsg.detaillen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.AppMsg.detail[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,16,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
                
                
            }

        
        }
        
        if(info.RemindCnt >= 2)
        {

        
        curr_index = (info.FirstPos+1)%5;

        if(info.RemindMsg[curr_index].RemindType == PHONE_MESSAGE)
        {
        
            UI_Common_AddBWsourcePic(temp_ram,8,70,(uint8_t*)iamge_bw_history_sms_h,APP_COLOR_BLACK,APP_COLOR_GREEN);
            
            x = 52;
            y = 8+59;
            memset(temp_data, 0x00, 256);
            len = info.RemindMsg[curr_index].Detail.PhoneMsg.namelen;
            memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMsg.name[0]),len*2);
            UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len,GB_SIZE_24X24, APP_COLOR_BLACK, APP_COLOR_WHITE);
            
            x = 52;
            y = 34+59;
            memset(temp_data, 0x00, 256);
            len = info.RemindMsg[curr_index].Detail.PhoneMsg.detaillen;
            memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMsg.detail[0]),len*2);
            UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
            
        
            
        }
        else if(info.RemindMsg[curr_index].RemindType == MISS_PHONE_CALL)
        {

            UI_Common_AddBWsourcePic(temp_ram,8,70,(uint8_t*)iamge_bw_history_call_h,APP_COLOR_BLACK,APP_COLOR_GREEN);
            
            x = 52;
            y = 8+59;
            memset(temp_data, 0x00, 256);
            len = info.RemindMsg[curr_index].Detail.PhoneMiss.detaillen;
            memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMiss.detail[0]),len*2);
            UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);
            
            x = 52;
            y = 34+59;
            memset(temp_data, 0x00, 256);
            len = info.RemindMsg[curr_index].Detail.PhoneMiss.namelen;
            memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMiss.name[0]),len*2);
            UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
            
        
        
        }
        else
        {
        
            UI_Common_AddBWsourcePic(temp_ram,8,70,(uint8_t*)iamge_bw_history_app_h,APP_COLOR_BLACK,APP_COLOR_GREEN);
            
            x = 52;
            y = 8+59;
            memset(temp_data, 0x00, 256);
            len = info.RemindMsg[curr_index].Detail.AppMsg.namelen;
            memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.AppMsg.name[0]),len*2);
            UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);
            
            x = 52;
            y = 34+59;
            memset(temp_data, 0x00, 256);
            len = info.RemindMsg[curr_index].Detail.AppMsg.detaillen;
            memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.AppMsg.detail[0]),len*2);
            UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,16,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
            
            
        }
        
        }

        if(info.RemindCnt >= 3)
        {
        
        
            curr_index = (info.FirstPos+2)%5;
            
            if(info.RemindMsg[curr_index].RemindType == PHONE_MESSAGE)
            {
            
                UI_Common_AddBWsourcePic(temp_ram,8,129,(uint8_t*)iamge_bw_history_sms_h,APP_COLOR_BLACK,APP_COLOR_GREEN);
                x = 52;
                y = 8+59*2;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.PhoneMsg.namelen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMsg.name[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len,GB_SIZE_24X24, APP_COLOR_BLACK, APP_COLOR_WHITE);
                
                x = 52;
                y = 34+59*2;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.PhoneMsg.detaillen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMsg.detail[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
                
            
                
            }
            else if(info.RemindMsg[curr_index].RemindType == MISS_PHONE_CALL)
            {
            
                UI_Common_AddBWsourcePic(temp_ram,8,129,(uint8_t*)iamge_bw_history_call_h,APP_COLOR_BLACK,APP_COLOR_GREEN);
                
                x = 52;
                y = 8+59*2;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.PhoneMiss.detaillen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMiss.detail[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);
                
                x = 52;
                y = 34+59*2;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.PhoneMiss.namelen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMiss.name[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
                
                
            
            
            }
            else
            {
            
                UI_Common_AddBWsourcePic(temp_ram,8,129,(uint8_t*)iamge_bw_history_app_h,APP_COLOR_BLACK,APP_COLOR_GREEN);
                
                x = 52;
                y = 8+59*2;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.AppMsg.namelen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.AppMsg.name[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);
                
                x = 52;
                y = 34+59*2;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.AppMsg.detaillen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.AppMsg.detail[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,16,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
                
                
            }
            
        
        
        }
        

    }
    else if(history_list_page ==1)
    {

    
        if(info.RemindCnt >= 3)
        {
        
        
                curr_index = (info.FirstPos+3)%5;
            
                if(info.RemindMsg[curr_index].RemindType == PHONE_MESSAGE)
                {
            
            
                    UI_Common_AddBWsourcePic(temp_ram,8,11,(uint8_t*)iamge_bw_history_sms_h,APP_COLOR_BLACK,APP_COLOR_GREEN);
            
                    x = 52;
                    y = 8;
            
                    memset(temp_data, 0x00, 256);
                    len = info.RemindMsg[curr_index].Detail.PhoneMsg.namelen;
                    memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMsg.name[0]),len*2);
                    UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len,GB_SIZE_24X24, APP_COLOR_BLACK, APP_COLOR_WHITE);
            
                    x = 52;
                    y = 34;
            
                    memset(temp_data, 0x00, 256);
                    len = info.RemindMsg[curr_index].Detail.PhoneMsg.detaillen;
                    memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMsg.detail[0]),len*2);
                    UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
                    
                }
                else if(info.RemindMsg[curr_index].RemindType == MISS_PHONE_CALL)
                {
                
                    UI_Common_AddBWsourcePic(temp_ram,8,11,(uint8_t*)iamge_bw_history_call_h,APP_COLOR_BLACK,APP_COLOR_GREEN);
                    
                    x = 52;
                    y = 8;
                    memset(temp_data, 0x00, 256);
                    len = info.RemindMsg[curr_index].Detail.PhoneMiss.detaillen;
                    memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMiss.detail[0]),len*2);
                    UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);
                    
                    x = 52;
                    y = 34;
                    memset(temp_data, 0x00, 256);
                    len = info.RemindMsg[curr_index].Detail.PhoneMiss.namelen;
                    memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMiss.name[0]),len*2);
                    UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
            
            
                
                }
                else
                {
                
                    UI_Common_AddBWsourcePic(temp_ram,8,11,(uint8_t*)iamge_bw_history_app_h,APP_COLOR_BLACK,APP_COLOR_GREEN);
            
                    
                    x = 52;
                    y = 8;
            
                    memset(temp_data, 0x00, 256);
                    len = info.RemindMsg[curr_index].Detail.AppMsg.namelen;
                    memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.AppMsg.name[0]),len*2);
                    UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);
            
                    
                    x = 52;
                    y = 34;
                    memset(temp_data, 0x00, 256);
                    len = info.RemindMsg[curr_index].Detail.AppMsg.detaillen;
                    memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.AppMsg.detail[0]),len*2);
                    UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,16,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
                    
                    
                }
            
            
            }
            
        
        


        if(info.RemindCnt >= 4)
        {
        
        
            curr_index = (info.FirstPos+4)%5;
            
            if(info.RemindMsg[curr_index].RemindType == PHONE_MESSAGE)
            {
            
                UI_Common_AddBWsourcePic(temp_ram,8,70,(uint8_t*)iamge_bw_history_sms_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
                
                x = 52;
                y = 8+59;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.PhoneMsg.namelen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMsg.name[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len,GB_SIZE_24X24, APP_COLOR_BLACK, APP_COLOR_WHITE);
                
                x = 52;
                y = 34+59;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.PhoneMsg.detaillen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMsg.detail[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
                
            
                
            }
            else if(info.RemindMsg[curr_index].RemindType == MISS_PHONE_CALL)
            {
            
                UI_Common_AddBWsourcePic(temp_ram,8,70,(uint8_t*)iamge_bw_history_call_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
                
                x = 52;
                y = 8+59;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.PhoneMiss.detaillen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMiss.detail[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);
                
                x = 52;
                y = 34+59;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.PhoneMiss.namelen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMiss.name[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
                
            
            
            }
            else
            {
            
                UI_Common_AddBWsourcePic(temp_ram,8,70,(uint8_t*)iamge_bw_history_app_h,APP_COLOR_BLACK,APP_COLOR_GREEN);
                
                x = 52;
                y = 8+59;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.AppMsg.namelen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.AppMsg.name[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);
                
                x = 52;
                y = 34+59;
                memset(temp_data, 0x00, 256);
                len = info.RemindMsg[curr_index].Detail.AppMsg.detaillen;
                memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.AppMsg.detail[0]),len*2);
                UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,16,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
                
                
            }
            
        
            UI_Common_AddBWsourcePic(temp_ram,16,130,(uint8_t*)gchinesefont_history_prompt,APP_COLOR_BLACK,APP_COLOR_WHITE);

            
        }
        
    
    }
    
    UI_Display_Prepare(temp_ram);

}


void UI_Screen_History_List_Entry(void)
{

    UI_Screen_History_List_Display();
    
    UI_Common_set_key_handle(UI_Screen_History_List_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_History_List_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_History_List_tpupslidehandle,
                                    UI_Screen_History_List_tpdownslidehandle,
                                    UI_Screen_History_List_tpleftslidehandle,
                                    UI_Screen_History_List_tprightslidehandle);
    
}

void UI_Screen_History_List_Exit(void)
{

    history_list_page =0;


}

void UI_Screen_History_List_shortkeyhandle(void)
{

    UI_Screen_History_List_Exit();
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    
    UI_Screen_draw_Screen();

}

void UI_Screen_History_List_holdshortkeyhandle(void)
{
}

void UI_Screen_History_List_holdlongkeyhandle(void)
{
}

void UI_Screen_History_List_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    RemindStore_t info;

    
    App_RemindManage_DetailRemindRead(&info);

    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    
    RTT_DEBUG_printf(0,"UI_Screen_History_List_tpclickhandle=%d---%d",curr_range,info.RemindCnt);

    if(history_list_page ==0)
    {
        
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {

                if(info.RemindCnt >= 1)
                {
                    curr_detail_index = 0;
                    UI_Screen_History_List_Exit();
                    UI_Set_Curr_ScreenID(Common_Screen_MainID_History_Detail);
                    UI_Screen_draw_Screen();
                }

            
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                if(info.RemindCnt >= 2)
                {
                    curr_detail_index = 1;
                    UI_Screen_History_List_Exit();
                    UI_Set_Curr_ScreenID(Common_Screen_MainID_History_Detail);
                    UI_Screen_draw_Screen();
                }
            
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {

                if(info.RemindCnt >= 3)
                {
                
                    curr_detail_index = 2;
                    UI_Screen_History_List_Exit();
                    UI_Set_Curr_ScreenID(Common_Screen_MainID_History_Detail);
                    UI_Screen_draw_Screen();
                }
            
            }
            break;
            default:
            break;
        }
    }
    else if(history_list_page ==1)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {

                if(info.RemindCnt >= 4)
                {
                    curr_detail_index = 3;
                    UI_Screen_History_List_Exit();
                    UI_Set_Curr_ScreenID(Common_Screen_MainID_History_Detail);
                    UI_Screen_draw_Screen();
                }

            
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                if(info.RemindCnt >= 5)
                {
                    curr_detail_index = 4;
                    UI_Screen_History_List_Exit();
                    UI_Set_Curr_ScreenID(Common_Screen_MainID_History_Detail);
                    UI_Screen_draw_Screen();
                }
            
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


void UI_Screen_History_List_tpupslidehandle(void)
{

    RemindStore_t info;
    App_RemindManage_DetailRemindRead(&info);

    if(info.RemindCnt<=3)
    {
    }
    else
    {
        if(history_list_page == 0)
        {
            history_list_page =1;
        }
        else
        {
            history_list_page =0;
        }
        
        UI_Set_Curr_ScreenID(Common_Screen_MainID_History_List);
        UI_Screen_draw_Screen();
    }


}

void UI_Screen_History_List_tpdownslidehandle(void)
{

    RemindStore_t info;
    App_RemindManage_DetailRemindRead(&info);

    if(info.RemindCnt<=3)
    {
    }
    else
    {
        if(history_list_page == 0)
        {
            history_list_page =1;
        }
        else
        {
            history_list_page =0;
        }
        UI_Set_Curr_ScreenID(Common_Screen_MainID_History_List);
        UI_Screen_draw_Screen();
    }


}


void UI_Screen_History_List_tpleftslidehandle(void)
{
}

void UI_Screen_History_List_tprightslidehandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_History);
    
    UI_Screen_draw_Screen();

}




void UI_Screen_History_Detail_Display(void)
{

    RemindStore_t info;

    int curr_index = 0;
	uint16_t  temp_data[256];
    uint16_t len = 0;

    char content[16];

    
    int x =0;
    int y =0;
    //int width =0;
    //int height =0;

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_History_Detail)
        return;

    UI_Common_Clear_Screen(temp_ram);
    
    
    App_RemindManage_DetailRemindRead(&info);

    curr_index = (info.FirstPos+curr_detail_index)%5;

    if(info.RemindMsg[curr_index].RemindType == PHONE_MESSAGE)
    {
    
        UI_Common_AddBWsourcePic(temp_ram,8,8,(uint8_t*)iamge_bw_history_sms_h,APP_COLOR_BLACK,APP_COLOR_GREEN);

        x = 50;
        y = 4;
        memset(temp_data, 0x00, 256);
        len = info.RemindMsg[curr_index].Detail.PhoneMsg.namelen;
        memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMsg.name[0]),len*2);
        UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len,GB_SIZE_24X24, APP_COLOR_BLACK, APP_COLOR_WHITE);

        x = 50;
        y = 32;

        sprintf(content,"%2d:%2d",info.RemindMsg[curr_index].RTC.hour,info.RemindMsg[curr_index].RTC.min);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,x,y,117,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        x = 8;
        y = 52;
        memset(temp_data, 0x00, 256);
        len = info.RemindMsg[curr_index].Detail.PhoneMsg.detaillen;
        memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMsg.detail[0]),len*2);
        UI_Common_Drawtextbox_byfontic(temp_ram, x, y,160,116,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
    
        
    }
		
    else if(info.RemindMsg[curr_index].RemindType == MISS_PHONE_CALL)
    {
    
        UI_Common_AddBWsourcePic(temp_ram,8,8,(uint8_t*)iamge_bw_history_call_h,APP_COLOR_BLACK,APP_COLOR_GREEN);

        x = 50;
        y = 4;
        memset(temp_data, 0x00, 256);
        len = info.RemindMsg[curr_index].Detail.PhoneMiss.detaillen;
        memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMiss.detail[0]),len*2);
        UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);

        x = 50;
        y = 32;

        sprintf(content,"%2d:%2d",info.RemindMsg[curr_index].RTC.hour,info.RemindMsg[curr_index].RTC.min);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,x,y,117,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        
        
        x = 8;
        y = 52;
        memset(temp_data, 0x00, 256);
        len = info.RemindMsg[curr_index].Detail.PhoneMiss.namelen;
        memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.PhoneMiss.name[0]),len*2);
        UI_Common_Drawtextbox_byfontic(temp_ram, x, y,160,116,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);

        
    
    
    }
    else
    {
    
        UI_Common_AddBWsourcePic(temp_ram,8,8,(uint8_t*)iamge_bw_history_app_h,APP_COLOR_BLACK,APP_COLOR_GREEN);
        
        x = 50;
        y = 4;
        memset(temp_data, 0x00, 256);
        len = info.RemindMsg[curr_index].Detail.AppMsg.namelen;
        memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.AppMsg.name[0]),len*2);
        UI_Common_Drawtextbox_byfontic(temp_ram, x, y,116,24,temp_data,len, GB_SIZE_24X24,APP_COLOR_BLACK, APP_COLOR_WHITE);

        
        x = 50;
        y = 32;

        sprintf(content,"%2d:%2d",info.RemindMsg[curr_index].RTC.hour,info.RemindMsg[curr_index].RTC.min);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,x,y,117,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        
        x = 8;
        y = 52;
        memset(temp_data, 0x00, 256);
        len = info.RemindMsg[curr_index].Detail.AppMsg.detaillen;
        memcpy(temp_data,&(info.RemindMsg[curr_index].Detail.AppMsg.detail[0]),len*2);
        UI_Common_Drawtextbox_byfontic(temp_ram, x, y,160,116,temp_data,len, GB_SIZE_16X16,APP_COLOR_BLACK, APP_COLOR_WHITE);
        
        
    }
    
    UI_Display_Prepare(temp_ram);

}

void UI_Screen_History_Detail_Entry(void)
{

    UI_Screen_History_Detail_Display();
    
    UI_Common_set_key_handle(UI_Screen_History_Detail_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_History_Detail_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_History_Detail_tpupslidehandle,
                                    UI_Screen_History_Detail_tpdownslidehandle,
                                    UI_Screen_History_Detail_tpleftslidehandle,
                                    UI_Screen_History_Detail_tprightslidehandle);
    
}

void UI_Screen_History_Detail_Exit(void)
{



}

void UI_Screen_History_Detail_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    
    UI_Screen_draw_Screen();

}

void UI_Screen_History_Detail_holdshortkeyhandle(void)
{
}

void UI_Screen_History_Detail_holdlongkeyhandle(void)
{
}

void UI_Screen_History_Detail_tpclickhandle(int point_x,int point_y)
{

    //判断点的范围

}

void UI_Screen_History_Detail_tpupslidehandle(void)
{

}

void UI_Screen_History_Detail_tpdownslidehandle(void)
{

}


void UI_Screen_History_Detail_tpleftslidehandle(void)
{
}

void UI_Screen_History_Detail_tprightslidehandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_History);
    
    UI_Screen_draw_Screen();
}


