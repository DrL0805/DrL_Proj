/**********************************************************************
**
**模块说明: ancs上传数据给后台
**软件版本，修改日志(时间，内容),修改人:
**          2018.12.17   初版，兼容V1 和V2两个版本
**
**********************************************************************/
#include "platform_common.h"
#include "platform_debugcof.h"
#include "wsf_types.h"
#include "bstream.h"
#include "wsf_msg.h"
#include "wsf_trace.h"
#include "wsf_assert.h"
#include "hci_api.h"
#include "dm_api.h"
#include "smp_api.h"
#include "att_api.h"
#include "app_cfg.h"
#include "app_api.h"
#include "app_db.h"
#include "svc_ch.h"
#include "svc_core.h"
#include "svc_dis.h"

#include "gatt_api.h"

// m_ble_profile
#include "app_m_ble_profile.h"
#include "ancs_api.h"
#include "ancc_api.h"
#include "svc_lowsapp.h"
#include "BLE_Kernal.h"

#if(ANCS_DETIL_TYPE != ANCS_NONE)

#if(BLE_STACK_DEBUG_ENABLE ==1)    
#define Ble_Debug(x) SEGGER_RTT_printf x
#else
#define Ble_Debug(x)
#endif

#define MAX_TEMP_LEN             200 //消息接收最大缓存
#define ONE_FRAME_VALID_LEN      9   //单个数据帧有效的msg内容长度

static uint32_t ios_msg_switch = 0; //消息详情/提醒开关，默认全关

#if(ANCS_VER_TYPE  == ANCS_VER_1)    //ANCS 版本1.0
static ble_recv msg_detail_cb = NULL;   //回调:返回ancs消息详情数据

typedef struct
{
    uint8_t u8MsgLen ;    //消息数据长度
    uint8_t u8MsgBuff[MAX_TEMP_LEN];  //buffer保存数据
}msg_buffer_t;

msg_buffer_t MsgData;   //buffer用于数据上传

static uint8_t send_msg_idx = 0;   //记录发送数据包序号
static uint8_t  send_flow = 0;     //记录流控
send_msg_frame_t  send_msg_frame;  //通讯协议包帧
/**********************************ANCS END********************************/

static void ancs_buffer_init(void)
{
    //init send buffer
    memset(&send_msg_frame,0,sizeof(send_msg_frame));
    //发送数据协议头不变部分不会去修改，无需每一次都设置
    send_msg_frame.frame_head = BLE_HEARD;
    send_msg_frame.version = BLE_VERSON;
    send_msg_frame.route= BLE_TO_MCU;
    send_msg_frame.interface[1] = PROT_INTERACT;
}

//**********************************************************************
// 函数功能: 定时发送消息详情
// 输入参数:
// 返回参数：none
// 说明:  两种方式将消息详情发送给app: 1.用循环方式将消息数据逐个发送给app
//   2.用timer隔一段时间发送消息详情数据。
//   当消息详情数据很大的时候，用循环的方式会出错，因此采用timer的方式
//**********************************************************************
void ancsAttr_UpLoad_Timeout(void)
{    
    uint8_t u8FrameValidLen;   //记录每帧中实际有效长度
    uint8_t u8OrderIndex;      //记录消息序号在协议中的下标

    Ble_Debug((0,"ancs_send_msg_detail_timeout\n")); 
    //新协议: 新的消息详情协议中每帧数据中多2 bytes MSG id
#if(ANCS_DETIL_TYPE == ANCS_DETIL_NEW)
    u8FrameValidLen = ONE_FRAME_VALID_LEN - 2;
    u8OrderIndex = 3;
#else 
    u8FrameValidLen = ONE_FRAME_VALID_LEN;
    u8OrderIndex = 1;
#endif
    //新协议: 2018.9.27

    if(MsgData.u8MsgLen > u8FrameValidLen)
    {
        //新协议: 新的消息详情协议中每帧数据中多2 bytes MSG id
        #if(ANCS_DETIL_TYPE == ANCS_DETIL_NEW)
        send_msg_frame.par_lenth = u8FrameValidLen + 7;  // 内容长度 7 + idx 1  + type 1 + 消息ID 2 + 接口 3
        #else
        send_msg_frame.par_lenth = u8FrameValidLen + 5;  // 内容长度 9 + idx 1  + type 1 + 接口 3
        #endif
        //新协议: 2018.9.27
        send_msg_frame.buf[u8OrderIndex] = send_msg_idx;
        memcpy(&send_msg_frame.buf[u8OrderIndex + 1],&MsgData.u8MsgBuff[send_msg_idx*u8FrameValidLen],u8FrameValidLen);
        send_msg_frame.buf[11] = BLE_Stack_CheckSum((uint8_t *)&send_msg_frame,send_msg_frame.par_lenth + 5);

        if(msg_detail_cb != NULL)
        {
            (msg_detail_cb)((uint8_t *)&send_msg_frame,send_msg_frame.par_lenth + 6);
        }
        MsgData.u8MsgLen -= u8FrameValidLen;
        send_msg_idx++;
        //启动timer，每隔50ms上传一包数据
        AnccActionStart(ANCS_TIMER_UPLOAD);
    }
    else 
    {
        send_msg_frame.buf[u8OrderIndex] = 0xff;
        memcpy(&send_msg_frame.buf[u8OrderIndex + 1],&MsgData.u8MsgBuff[send_msg_idx*u8FrameValidLen],MsgData.u8MsgLen);
        //新协议: 新的消息详情协议中每帧数据中多2 bytes MSG id
        #if(ANCS_DETIL_TYPE == ANCS_DETIL_NEW)
        send_msg_frame.par_lenth = MsgData.u8MsgLen + 7; //内容长度 + idx 1 + type 1 + 消息ID 2 + 接口 3
        send_msg_frame.buf[MsgData.u8MsgLen + 4] = BLE_Stack_CheckSum((uint8_t *)&send_msg_frame,send_msg_frame.par_lenth + 5);
        #else
        send_msg_frame.par_lenth = MsgData.u8MsgLen + 5; //内容长度 + idx 1 + type 1 + 接口 3
        send_msg_frame.buf[MsgData.u8MsgLen + 2] = BLE_Stack_CheckSum((uint8_t *)&send_msg_frame,send_msg_frame.par_lenth + 5);
        #endif
        //新协议: 2018.9.27

        MsgData.u8MsgLen = 0;
        if(msg_detail_cb != NULL)
        {
            (msg_detail_cb)((uint8_t *)&send_msg_frame,send_msg_frame.par_lenth + 6);
        }

        AncsActionNext();
    }
}

//**********************************************************************
// 函数功能: 上传ancs消息数据给后台
// 输入参数：
// 返回参数：
//**********************************************************************
void ancsAttr_UpLoad(anccCb_t *anccCb)
{
#if(ANCS_DETIL_TYPE != ANCS_REMIND)
    uint8_t u8MsgIdx = 0,u8Remaining,attrId;  //u8MsgIdx既是u8MsgBuffer操作下表，又作为数据长度
    uint8_t *pu8Buf;   //主要便于打印信息
#endif
    uint32_t u32MsgBit = BIT(anccCb->attr.u8AppType);

    //后台不支持的消息，或消息开关关闭，不上传数据
    if((anccCb->attr.u8AppType == TYPE_ANCS_MSG_TYPE_INVALID) || ((ios_msg_switch & u32MsgBit) == 0x00))
    {
        Ble_Debug((0,"do not upload msg, u8AppType = %d\n", anccCb->attr.u8AppType));
        return;
    }

#if(ANCS_DETIL_TYPE == ANCS_REMIND)    //消息提醒
    Ble_Debug((0,"New Msg type:%d\n",anccCb->attr.u8AppType));

    //封装协议信息
    send_msg_frame.par_lenth = 0x07;
    send_msg_frame.flow = send_flow++;
    send_msg_frame.interface[0] = CALL;
    send_msg_frame.interface[2] = PROT_NEW_MSG;
    send_msg_frame.buf[0] = BYTE3(u32MsgBit);
    send_msg_frame.buf[1] = BYTE2(u32MsgBit);
    send_msg_frame.buf[2] = BYTE1(u32MsgBit);
    send_msg_frame.buf[3] = BYTE0(u32MsgBit);
    send_msg_frame.buf[4] = BLE_Stack_CheckSum((uint8_t *)&send_msg_frame,send_msg_frame.par_lenth + 5);

    if(msg_detail_cb != NULL)
    {
        (msg_detail_cb)((uint8_t *)&send_msg_frame,send_msg_frame.par_lenth + 6);
    }

    AncsActionNext(); //处理下一条消息

#else                               //消息详情

#if(ANCS_DETIL_TYPE == ANCS_DETIL_NEW)
    uint16_t u16MsgId;

    //设置消息信息
    u16MsgId = (anccCb->attr.u32Uid & 0xFFFF);
    Ble_Debug((0,"Msg type:%d UID :%d\n",anccCb->attr.u8AppType,u16MsgId));
#endif
    //copy title data
    if(anccCb->attr.u16TtlLen > 0)
    {
        u8Remaining = (anccCb->attr.u16TtlLen > TITLE_MAX_LEN) ? TITLE_MAX_LEN : anccCb->attr.u16TtlLen;        
        pu8Buf = &MsgData.u8MsgBuff[u8MsgIdx];
        memcpy(pu8Buf,&anccCb->active.attrDataBuf[anccCb->attr.u16TtlIdx],u8Remaining);
        u8MsgIdx += u8Remaining;
        MsgData.u8MsgBuff[u8MsgIdx++] = '\0';
        Ble_Debug((0,"TITLE :%s LEN :%d\n",pu8Buf,u8Remaining));
    }
    else
    {
        //消息本身不带title时，用应用名为默认title
        if(anccCb->attr.u8AppType == TYPE_ANCS_MSG_QQ)
            pu8Buf = "QQ";
        else if(anccCb->attr.u8AppType == TYPE_ANCS_MSG_SINA_WEIBO)
            pu8Buf = "WEIBO";
        else if(anccCb->attr.u8AppType == TYPE_ANCS_MSG_SKYPE)
            pu8Buf = "Skype";
        else if(anccCb->attr.u8AppType == TYPE_ANCS_MSG_FACEBOOK)
            pu8Buf = "Facebook";
        else if(anccCb->attr.u8AppType == TYPE_ANCS_MSG_TWITTER)
            pu8Buf = "Twitter";
        else if(anccCb->attr.u8AppType == TYPE_ANCS_MSG_WHATAPP)
            pu8Buf = "WhatApp";
        else if(anccCb->attr.u8AppType == TYPE_ANCS_MSG_LINE)
            pu8Buf = "Line";
        else if(anccCb->attr.u8AppType == TYPE_ANCS_MSG_TIM)
            pu8Buf = "Tim";
        else if(anccCb->attr.u8AppType == TYPE_ANCS_MSG_TAOBAO)
            pu8Buf = "TaoBao";
        else if(anccCb->attr.u8AppType == TYPE_ANCS_MSG_JINGDONG)
            pu8Buf = "JD";
        else if(anccCb->attr.u8AppType == TYPE_ANCS_MSG_DINGDING)
            pu8Buf = "DingDing";
        else if(anccCb->attr.u8AppType == TYPE_ANCS_MSG_INSTAGRAM)
            pu8Buf = "Instagram";

        if(pu8Buf != NULL)
        {
            u8Remaining = sizeof(pu8Buf)-1;
            memcpy(&MsgData.u8MsgBuff[u8MsgIdx],pu8Buf,u8Remaining);
            u8MsgIdx += u8Remaining;
        }
    }

    //copy subtitle data
    if(anccCb->attr.u16SubTtlLen > 0)
    {
        u8Remaining = (anccCb->attr.u16SubTtlLen > SUBTITLE_MAX_LEN) ? SUBTITLE_MAX_LEN : anccCb->attr.u16SubTtlLen;
        pu8Buf = &MsgData.u8MsgBuff[u8MsgIdx];
        memcpy(pu8Buf,&anccCb->active.attrDataBuf[anccCb->attr.u16SubTtlIdx],u8Remaining);
        u8MsgIdx += u8Remaining;
        MsgData.u8MsgBuff[u8MsgIdx++] = '\0';
        Ble_Debug((0,"SUBTITLE :%s LEN :%d\n",pu8Buf,u8Remaining));
    }

    //msg 数据不全的情况下
    if((anccCb->active.attrtype & GET_MSG) != GET_MSG)
    {
        if(anccCb->active.bufIndex - anccCb->active.parseIndex > 3)
        {
            attrId = anccCb->active.attrDataBuf[anccCb->active.parseIndex]; //未接收全的attribute时:anccCb.active.parseIndex是attr id位置            
            BYTES_TO_UINT16(anccCb->active.attrLength, &(anccCb->active.attrDataBuf[anccCb->active.parseIndex + 1]));
            if(attrId == BLE_ANCS_NOTIF_ATTR_ID_MESSAGE)
            {
                u8Remaining = anccCb->active.bufIndex - anccCb->active.parseIndex - 3;
                anccCb->attr.u16MsgIdx = anccCb->active.parseIndex + 3;
                anccCb->attr.u16MsgLen = (u8Remaining > anccCb->active.attrLength) ? anccCb->active.attrLength : u8Remaining;
            }
        }
    }
    
    //copy msg data:已接收全的情况
    if(anccCb->attr.u16MsgLen > 0)
    {
        u8Remaining = MAX_TEMP_LEN - u8MsgIdx;  //u8MsgBuffer剩余空间大小
        pu8Buf = &MsgData.u8MsgBuff[u8MsgIdx];
        if(u8Remaining > anccCb->attr.u16MsgLen)
        {
            memcpy(pu8Buf,&anccCb->active.attrDataBuf[anccCb->attr.u16MsgIdx],anccCb->attr.u16MsgLen);
            u8MsgIdx += anccCb->attr.u16MsgLen;
            MsgData.u8MsgBuff[u8MsgIdx++] = '\0';
        }
        else
        {
            memcpy(pu8Buf,&anccCb->active.attrDataBuf[anccCb->attr.u16MsgIdx],u8Remaining);
            MsgData.u8MsgBuff[MAX_TEMP_LEN -1] = '\0';
            u8MsgIdx = MAX_TEMP_LEN;
        }
        Ble_Debug((0,"MSG :%s LEN :%d\n",pu8Buf,u8MsgIdx));

        MsgData.u8MsgLen = u8MsgIdx;        
        send_msg_idx = 0;     //新包序号从0开始

        //封装协议信息
        send_msg_frame.flow = send_flow++;
        send_msg_frame.interface[0] = ECHO;
        send_msg_frame.interface[2] = (ANCS_DETIL_TYPE == ANCS_DETIL_NEW) ? PROT_MSG_DETAIL_NEW : PROT_MSG_DETAIL;
        send_msg_frame.buf[0] = anccCb->attr.u8AppType;
#if(ANCS_DETIL_TYPE == ANCS_DETIL_NEW)
        send_msg_frame.buf[1] = BYTE1(u16MsgId);
        send_msg_frame.buf[2] = BYTE0(u16MsgId);
#endif
        //启动timer上传数据
        AnccActionStart(ANCS_TIMER_UPLOAD);
    }
    else
    {   
        AncsActionNext(); //处理下一条消息
    }
#endif
}

//**********************************************************************
// 函数功能: ancs消息取消
// 输入参数：
// 返回参数：
//**********************************************************************
void ancsAttr_Cancle(attr_notif_t* pAttr)
{
    uint32_t u32MsgBit = 0x00;
    uint8_t u8Idex = 0;
#if(ANCS_DETIL_TYPE == ANCS_DETIL_NEW)
    uint8_t u16MsgId = (pAttr->notification_uid & 0xffff);
#endif

#if(ANCS_DETIL_TYPE == ANCS_DETIL)
    //只支持取消来电和未接来电，如H001
    if((pAttr->category_id != BLE_ANCS_CATEGORY_ID_INCOMING_CALL) && \
       (pAttr->category_id != BLE_ANCS_CATEGORY_ID_MISSED_CALL))
        return ;
#endif

    //消息类型只能知道来电和未接来电，其他通过UID区分
    if(pAttr->category_id == BLE_ANCS_CATEGORY_ID_INCOMING_CALL)
        u32MsgBit = BIT(TYPE_ANCS_MSG_INCALL);
    else if(pAttr->category_id == BLE_ANCS_CATEGORY_ID_MISSED_CALL)
        u32MsgBit = BIT(TYPE_ANCS_MSG_MISSCALL);

    //封装协议信息
    send_msg_frame.par_lenth = (ANCS_DETIL_TYPE == ANCS_DETIL_NEW) ? 0x09 : 0x07;
    send_msg_frame.flow = send_flow++;
    send_msg_frame.interface[0] = CALL;
    send_msg_frame.interface[2] = (ANCS_DETIL_TYPE == ANCS_DETIL_NEW) ? PROT_CANCEL_MSG_NEW : PROT_CANCEL_MSG;;
    send_msg_frame.buf[u8Idex++] = BYTE3(u32MsgBit);
    send_msg_frame.buf[u8Idex++] = BYTE2(u32MsgBit);
    send_msg_frame.buf[u8Idex++] = BYTE1(u32MsgBit);
    send_msg_frame.buf[u8Idex++] = BYTE0(u32MsgBit);
#if(ANCS_DETIL_TYPE == ANCS_DETIL_NEW)
    send_msg_frame.buf[u8Idex++] = BYTE1(u16MsgId);
    send_msg_frame.buf[u8Idex++] = BYTE0(u16MsgId);
#endif
    send_msg_frame.buf[u8Idex++] = BLE_Stack_CheckSum((uint8_t *)&send_msg_frame,send_msg_frame.par_lenth + 5);

    if(msg_detail_cb != NULL)
    {
        (msg_detail_cb)((uint8_t *)&send_msg_frame,send_msg_frame.par_lenth + 6);
    }
}

#elif(ANCS_VER_TYPE  == ANCS_VER_2)         //ANCS 版本1.0
static Ancs_Msg_Cb AncsMsg_Cb = NULL;

//**********************************************************************
// 函数功能: 上传ancs消息数据给后台
// 输入参数：
// 返回参数：
//**********************************************************************
void ancsAttr_UpLoad(anccCb_t *anccCb)
{
    ancs_msg_info_t info;
    uint8_t u8MsgBuffer[MAX_TEMP_LEN];
    uint8_t u8MsgIdx = 0,u8Remaining,attrId;  //u8MsgIdx既是u8MsgBuffer操作下表，又作为数据长度
    uint8_t *pu8Buf = NULL;   //主要便于打印信息

    //后台不支持的消息，或消息开关关闭，不上传数据
    if((anccCb->attr.u8AppType == TYPE_ANCS_MSG_TYPE_INVALID) || ((ios_msg_switch & BIT(anccCb->attr.u8AppType)) == 0x00))
    {
        Ble_Debug((0,"do not upload msg, u8AppType = %d\n", anccCb->attr.u8AppType));
        return;
    }

    //设置消息信息
    info.u8MsgType = anccCb->attr.u8AppType;
    info.u16MsgId = (anccCb->attr.u32Uid & 0xFFFF);
    info.u8ProType = PROT_MSG_DETAIL_NEW;
    Ble_Debug((0,"Msg type:%d UID :%d\n",info.u8MsgType,info.u16MsgId));

#if(ANCS_DETIL_TYPE == ANCS_REMIND)
    if(AncsMsg_Cb != NULL)
    {
        (AncsMsg_Cb)(&info,NULL,0);  //消息提醒时，无内容
    }
#else     //消息详情
    //copy title data
    if(anccCb->attr.u16TtlLen > 0)
    {
        u8Remaining = (anccCb->attr.u16TtlLen > TITLE_MAX_LEN) ? TITLE_MAX_LEN : anccCb->attr.u16TtlLen;        
        pu8Buf = &u8MsgBuffer[u8MsgIdx];
        memcpy(pu8Buf,&anccCb->active.attrDataBuf[anccCb->attr.u16TtlIdx],u8Remaining);
        u8MsgIdx += u8Remaining;
        u8MsgBuffer[u8MsgIdx++] = '\0';
        Ble_Debug((0,"TITLE :%s LEN :%d\n",pu8Buf,u8Remaining));
    }
    else
    {
        //消息本身不带title时，用应用名为默认title
        if(info.u8MsgType == TYPE_ANCS_MSG_QQ)
            pu8Buf = "QQ";
        else if(info.u8MsgType == TYPE_ANCS_MSG_SINA_WEIBO)
            pu8Buf = "Weibo";
        else if(info.u8MsgType == TYPE_ANCS_MSG_SKYPE)
            pu8Buf = "Skype";
        else if(info.u8MsgType == TYPE_ANCS_MSG_FACEBOOK)
            pu8Buf = "Facebook";
        else if(info.u8MsgType == TYPE_ANCS_MSG_TWITTER)
            pu8Buf = "Twitter";
        else if(info.u8MsgType == TYPE_ANCS_MSG_WHATAPP)
            pu8Buf = "WhatApp";
        else if(info.u8MsgType == TYPE_ANCS_MSG_LINE)
            pu8Buf = "Line";
        else if(info.u8MsgType == TYPE_ANCS_MSG_TIM)
            pu8Buf = "Tim";
        else if(info.u8MsgType == TYPE_ANCS_MSG_TAOBAO)
            pu8Buf = "TaoBao";
        else if(info.u8MsgType == TYPE_ANCS_MSG_JINGDONG)
            pu8Buf = "JD";
        else if(info.u8MsgType == TYPE_ANCS_MSG_DINGDING)
            pu8Buf = "DingDing";
        else if(info.u8MsgType == TYPE_ANCS_MSG_INSTAGRAM)
            pu8Buf = "Instagram";

        if(pu8Buf != NULL)
        {
            u8Remaining = sizeof(pu8Buf)-1;
            memcpy(&u8MsgBuffer[u8MsgIdx],pu8Buf,u8Remaining);
            u8MsgIdx += u8Remaining;
        }
    }

    //copy subtitle data
    if(anccCb->attr.u16SubTtlLen > 0)
    {
        u8Remaining = (anccCb->attr.u16SubTtlLen > SUBTITLE_MAX_LEN) ? SUBTITLE_MAX_LEN : anccCb->attr.u16SubTtlLen;
        pu8Buf = &u8MsgBuffer[u8MsgIdx];
        memcpy(pu8Buf,&anccCb->active.attrDataBuf[anccCb->attr.u16SubTtlIdx],u8Remaining);
        u8MsgIdx += u8Remaining;
        u8MsgBuffer[u8MsgIdx++] = '\0';
        Ble_Debug((0,"SUBTITLE :%s LEN :%d\n",pu8Buf,u8Remaining));
    }

    //msg 数据不全的情况下
    if((anccCb->active.attrtype & GET_MSG) != GET_MSG)
    {
        if(anccCb->active.bufIndex - anccCb->active.parseIndex > 3)
        {
            attrId = anccCb->active.attrDataBuf[anccCb->active.parseIndex]; //未接收全的attribute时:anccCb.active.parseIndex是attr id位置            
            BYTES_TO_UINT16(anccCb->active.attrLength, &(anccCb->active.attrDataBuf[anccCb->active.parseIndex + 1]));
            if(attrId == BLE_ANCS_NOTIF_ATTR_ID_MESSAGE)
            {
                u8Remaining = anccCb->active.bufIndex - anccCb->active.parseIndex - 3;
                anccCb->attr.u16MsgIdx = anccCb->active.parseIndex + 3;
                anccCb->attr.u16MsgLen = (u8Remaining > anccCb->active.attrLength) ? anccCb->active.attrLength : u8Remaining;
            }
        }
    }

    //copy msg data:已接收全的情况
    if(anccCb->attr.u16MsgLen > 0)
    {
        u8Remaining = MAX_TEMP_LEN - u8MsgIdx;  //u8MsgBuffer剩余空间大小
        pu8Buf = &u8MsgBuffer[u8MsgIdx];
        if(u8Remaining > anccCb->attr.u16MsgLen)
        {
            memcpy(pu8Buf,&anccCb->active.attrDataBuf[anccCb->attr.u16MsgIdx],anccCb->attr.u16MsgLen);
            u8MsgIdx += anccCb->attr.u16MsgLen;
            u8MsgBuffer[u8MsgIdx++] = '\0';
        }
        else
        {
            memcpy(pu8Buf,&anccCb->active.attrDataBuf[anccCb->attr.u16MsgIdx],u8Remaining);
            u8MsgBuffer[MAX_TEMP_LEN -1] = '\0';
            u8MsgIdx = MAX_TEMP_LEN;
        }
        Ble_Debug((0,"MSG :%s LEN :%d\n",pu8Buf,anccCb->attr.u16MsgLen));
        
        if(AncsMsg_Cb != NULL)
        {
            (AncsMsg_Cb)(&info,u8MsgBuffer,u8MsgIdx);  //消息详情
        }
    }
#endif

    AncsActionNext(); //处理下一条消息
}

//**********************************************************************
// 函数功能: ancs消息取消
// 输入参数：
// 返回参数：
//**********************************************************************
void ancsAttr_Cancle(attr_notif_t* pAttr)
{
    ancs_msg_info_t info;

    //取消消息时只有来电有消息类型，其他的不可知，设为other，此时关键是UID
    info.u8MsgType = (pAttr->category_id == BLE_ANCS_CATEGORY_ID_INCOMING_CALL) ? TYPE_ANCS_MSG_INCALL : TYPE_ANCS_MSG_OTHER1;
    info.u16MsgId = (pAttr->notification_uid & 0xFFFF);
    info.u8ProType = PROT_CANCEL_MSG_NEW;
    
    if(AncsMsg_Cb != NULL)
    {
        (AncsMsg_Cb)(&info,NULL,0);  //取消消息时，无内容
    }
}

//**********************************************************************
// 函数功能: 设置ANCS数据回调函数，此种情况下不在通过协议包方式上传ANCS数据
// 输入参数：
// 返回参数：
//**********************************************************************
ret_type BLE_Stack_SetAncsCallBack(Ancs_Msg_Cb ancs_handler)
{
    if(ancs_handler == NULL)
    {
        return Ret_InvalidParam;   //param is invalid
    }
    AncsMsg_Cb = ancs_handler;
    return Ret_OK;
}
#endif

//**********************************************************************
// 函数功能: 设置消息详情开关
// 输入参数：u32MsgDetailOn: 消息详情开关
// 返回参数：
//**********************************************************************
void BLE_Stack_SetAncsMsgSwitch(uint32 u32MsgDetailOn)
{
    ios_msg_switch = u32MsgDetailOn;
    Ble_Debug((0,"ios_msg_switch =0x%x\n",ios_msg_switch));
}

//**********************************************************************
// 函数功能: 设置接收数据回调函数，蓝牙接收到的数据都通过此回调返回给app处理
// 输入参数：recv_data_handler:数据接收callback，
// 返回参数：
//    Ret_OK:正常，  
//    Ret_InvalidParam: 参数非法
//**********************************************************************
ret_type BLE_Stack_SetRecvCallBack(ble_recv recv_data_handler)
{
    if(recv_data_handler == NULL)
    {
        return Ret_InvalidParam;   //param is invalid
    }

#if(ANCS_VER_TYPE  == ANCS_VER_1)
    ancs_buffer_init();
    msg_detail_cb = recv_data_handler;
#endif
    lowsapp_transfer_data_init(recv_data_handler);
    return Ret_OK;
}

#endif

