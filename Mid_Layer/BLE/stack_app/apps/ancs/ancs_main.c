//*****************************************************************************
//
//! @file   m_ble_profile_main.c
//!
//! @brief  Ambiq Micro's demonstration of ANCSC
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************

/**********************************************************************
**
**模块说明: ancs
**软件版本，修改日志(时间，内容),修改人:
**  初版    2018.12.18  重新调整ANCS流程，兼容v1和v2两个版本
**  
**  
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

#include "app_m_ble_profile.h"
#include "ancs_api.h"
#include "svc_lowsapp.h"
#include "BLE_Kernal.h"
#include "ancc_api.h"
#include "BLE_Stack.h"
#include "ancs_upload.h"

#if(ANCS_DETIL_TYPE != ANCS_NONE)

#if (BLE_STACK_DEBUG_ENABLE ==1)
#define Ble_Debug(x) SEGGER_RTT_printf x
#else
#define Ble_Debug(x)
#endif

/**************************************************************************************************
  Global Variables
**************************************************************************************************/
extern uint16_t *pAncsAnccHdlList;
static anccCb_t anccCb = {0};

uint32_t incall_notify_uid;  //for incoming call

//App Identifier 定义
const uint8_t QQIdentifier[] =               {"com.tencent.mqq"};           // tecent qq
const uint8_t WechatIdentifier[] =           {"com.tencent.xin"};           // tencent weixin
const uint8_t SkypeIdentifier[] =            {"com.skype.tomskype"};        // skype
const uint8_t SinaWeiboIdentifier[] =        {"com.sina.weibo"};            // sina weibo
const uint8_t MessengerIdentifier[] =        {"com.facebook.Messenger"};    // facebook
const uint8_t FacebookIdentifier[] =         {"com.facebook.Facebook"};     // facebook2
const uint8_t TwitterIdentifier[] =          {"com.atebits.Tweetie2"};      // twitter
const uint8_t WhatsappIdentifier[] =         {"net.whatsapp.WhatsApp"};     // whatsapp
const uint8_t LineIdentifier[] =             {"jp.naver.line"};             // line
const uint8_t SMSIdentifier[] =              {"com.apple.MobileSMS"};       // message
const uint8_t TimIdentifier[]      =         {"com.tencent.tim"};   //tim
const uint8_t TaobaoIdentifier[]      =      {"com.taobao.taobao4iphone"};   //taobao
const uint8_t JingDongIdentifier[]    =      {"com.360buy.jdmobile"};   //jingdong
const uint8_t DingDingIdentifier[]    =      {"com.laiwang.DingTalk"};   //Dingding
const uint8_t InstagramIdentifier[]   =      {"com.burbn.instagram"};   //Instagram
//const uint8_t CalllingIdentifier[] =         {"com.apple.Calling"};    //call     为了区分来电和未接来电，自定义
//const uint8_t MissCalllingIdentifier[] =     {"com.apple.MissCalling"}; //miss call
//const uint8_t TencentWeiboIdentifier[] =     {"com.tencent.WeiBo"};         // tecent weibo

//列表项:常用到的消息放在前面，不常用的放在后面，减少查询时间
const ancs_app_id_type ancs_app_id_list[] =
{
    //{TYPE_ANCS_MSG_INCALL,        (sizeof(CalllingIdentifier)-1),     CalllingIdentifier},     //来电    
    //{TYPE_ANCS_MSG_MISSCALL,      (sizeof(MissCalllingIdentifier)-1), MissCalllingIdentifier}, //未接来电
    {TYPE_ANCS_MSG_WECHAT,        (sizeof(WechatIdentifier)-1),       WechatIdentifier},       //微信
    {TYPE_ANCS_MSG_QQ,            (sizeof(QQIdentifier)-1),           QQIdentifier},           //QQ	
    {TYPE_ANCS_MSG_MESSAGE,       (sizeof(SMSIdentifier)-1),          SMSIdentifier},          //短信
    {TYPE_ANCS_MSG_SINA_WEIBO, 	  (sizeof(SinaWeiboIdentifier)-1),    SinaWeiboIdentifier},
    {TYPE_ANCS_MSG_SKYPE,         (sizeof(SkypeIdentifier)-1),        SkypeIdentifier},
    {TYPE_ANCS_MSG_FACEBOOK,      (sizeof(FacebookIdentifier)-1),     FacebookIdentifier},
    {TYPE_ANCS_MSG_TWITTER,       (sizeof(TwitterIdentifier)-1),      TwitterIdentifier},
    {TYPE_ANCS_MSG_WHATAPP,       (sizeof(WhatsappIdentifier)-1),     WhatsappIdentifier},
    {TYPE_ANCS_MSG_LINE,          (sizeof(LineIdentifier)-1),         LineIdentifier},
    {TYPE_ANCS_MSG_TIM,           (sizeof(TimIdentifier)-1),          TimIdentifier},
    {TYPE_ANCS_MSG_TAOBAO,        (sizeof(TaobaoIdentifier)-1),       TaobaoIdentifier},        //淘宝
    {TYPE_ANCS_MSG_JINGDONG,      (sizeof(JingDongIdentifier)-1),     JingDongIdentifier},      //京东 
    {TYPE_ANCS_MSG_DINGDING,      (sizeof(DingDingIdentifier)-1),     DingDingIdentifier},      //叮叮
    {TYPE_ANCS_MSG_INSTAGRAM,     (sizeof(InstagramIdentifier)-1),    InstagramIdentifier},     //Instagram
    //{TYPE_ANCS_MSG_CALENDAR,      (sizeof(InSmartmovtIdentifier)-1),  InSmartmovtIdentifier},   //日历信息
    //{TYPE_ANCS_MSG_TENCENT_WEIBO, (sizeof(TencentWeiboIdentifier)-1), TencentWeiboIdentifier},  //手机app先不支持，无开关
};

#define ANCS_APP_ID_NUM     (sizeof(ancs_app_id_list)/sizeof(ancs_app_id_type))

//**********************************************************************
// 函数功能: 将IOS手机下发的消息添加到list，消息类型有added/updated
// 输入参数：
// 返回参数：
// 说明:list管理数据结构是消息队列，先到的先请求，而非原厂的堆结构
//**********************************************************************
static void anccActionListPush(attr_notif_t* pElement)
{
    uint8_t u8cnt,u8Idx;

    //来电和未接来电，放在call中目的优先处理
    if((pElement->category_id == BLE_ANCS_CATEGORY_ID_INCOMING_CALL) || (pElement->category_id == BLE_ANCS_CATEGORY_ID_MISSED_CALL))
    {
        anccCb.call.isValid = TRUE;
        memcpy(&anccCb.call.call_notif,pElement,sizeof(attr_notif_t));
        return ;
    }

    //step 1: 消息为modify类型
    if(BLE_ANCS_EVENT_ID_NOTIFICATION_MODIFIED == pElement->event_id)
    {
        u8Idx = anccCb.msgInfo.u8popIdx;
        for(u8cnt = 0; u8cnt < anccCb.msgInfo.u8attCnt;u8cnt++)
        {
            //在list中有此modify消息的原消息，则将原消息清除，将此消息变为最新消息,消息数不变
            if(anccCb.msgInfo.list[u8Idx].notification_uid == pElement->notification_uid)
            {
                for(uint8_t i = u8Idx; i < anccCb.msgInfo.u8pushIdx - 1;)
                {
                    memcpy(&anccCb.msgInfo.list[i],&anccCb.msgInfo.list[i + 1],sizeof(attr_notif_t));
                    i = (i + 1) % ANCC_LIST_ELEMENTS;
                }
                memcpy(&anccCb.msgInfo.list[anccCb.msgInfo.u8pushIdx - 1],pElement,sizeof(attr_notif_t));
                return;
            }
            u8Idx = (u8Idx + 1) % ANCC_LIST_ELEMENTS;
        }
    }

    //向list中添加消息，此消息可能是add类型的，也可能是modify类型但在list中已无原始的那条消息
    //step 2: check list is full?
    if(anccCb.msgInfo.u8attCnt == ANCC_LIST_ELEMENTS)
    {
        //要记录最新来的消息，需丢弃最先来但来不及处理的消息。
        //在满的情况下，u8pushIdx和u8popIdx指向同一个位置，此时u8popIdx加一丢弃一个，这样
        //u8pushIdx位置上的数据就变为无效，确保写数据时不会盖到有效数据
        anccCb.msgInfo.u8popIdx = (anccCb.msgInfo.u8popIdx + 1) % ANCC_LIST_ELEMENTS;
    }

    //step 3: 增加一条消息
    memcpy(&anccCb.msgInfo.list[anccCb.msgInfo.u8pushIdx],pElement,sizeof(attr_notif_t));
    anccCb.msgInfo.u8pushIdx = (anccCb.msgInfo.u8pushIdx + 1) % ANCC_LIST_ELEMENTS;
    anccCb.msgInfo.u8attCnt++;
    if(anccCb.msgInfo.u8attCnt > ANCC_LIST_ELEMENTS)
    {
        anccCb.msgInfo.u8attCnt = ANCC_LIST_ELEMENTS;
    }
}

//**********************************************************************
// 函数功能: 从list中弹出最先来的消息，并在list中清除掉，然后向ios手机请求
// 输入参数：
// 返回参数：false:list为空
//**********************************************************************
static bool_t anccActionListPop(void)
{
    //来电或未接来电，优先处理，其优先级高于其他的消息提醒
    if(anccCb.call.isValid == TRUE)
    {
        memcpy(&anccCb.active.currMsg,&anccCb.call.call_notif,sizeof(attr_notif_t));
        anccCb.call.isValid = FALSE;
        //fix: 无法拒接电话
        incall_notify_uid = anccCb.call.call_notif.notification_uid;
        //fix:2019.1.12
        return true;
    }

    //step 1: check list is empty?
    if(anccCb.msgInfo.u8attCnt == 0)
        return false;

    //step 2: pop出最先来的消息，作为当前请求的消息,list中对应删除pop出去的这条数据
    memcpy(&anccCb.active.currMsg,&anccCb.msgInfo.list[anccCb.msgInfo.u8popIdx],sizeof(attr_notif_t));
    anccCb.msgInfo.u8popIdx = (anccCb.msgInfo.u8popIdx + 1) % ANCC_LIST_ELEMENTS;
    if(anccCb.msgInfo.u8attCnt > 0)
    {
        anccCb.msgInfo.u8attCnt--;
    }
    return true;
}

//**********************************************************************
// 函数功能: 清除list中消息项，在蓝牙断开后需清除，无法在请求
// 输入参数：
// 返回参数：
//**********************************************************************
static void anccActionListClear(void)
{
   anccCb.msgInfo.u8attCnt = 0;
   anccCb.msgInfo.u8popIdx = 0;
   anccCb.msgInfo.u8pushIdx = 0;
}

//**********************************************************************
// 函数功能: 启动ANCS timer
// 输入参数：u8TimerStatus: timer状态，同时也是timer定时时间，值:ANCS_TIMER_PARSE
//           和 ANCS_TIMER_UPLOAD
// 返回参数:
// note: Start periodic ancc operation.  This function starts a timer 
// to perform periodic actions.
//**********************************************************************
void AnccActionStart(uint8_t u8TimerStatus)
{
    /* if this is first connection */
    if(anccCb.connId != DM_CONN_ID_NONE)
    {
        anccCb.timerStatus = u8TimerStatus;
        
        /* (re-)start timer */
        WsfTimerStop(&anccCb.actionTimer);
        WsfTimerStartMs(&anccCb.actionTimer, u8TimerStatus);
    }
}

//**********************************************************************
// 函数功能: 解析Notification Attributes
// 输入参数：
// 返回参数：
//**********************************************************************
static bool ancsAttrParse(active_notif_t* pAttr)
{
    switch(pAttr->attrId)
    {
    case BLE_ANCS_NOTIF_ATTR_ID_APP_IDENTIFIER:    //APP ID 
        #if (BLE_STACK_DEBUG_ENABLE ==1)
        Ble_Debug((0,"APP ID :"));
        for(int i = 0; i< pAttr->attrLength; i++)
        {
            Ble_Debug((0,"%c",pAttr->attrDataBuf[pAttr->parseIndex+i]));
        }
        Ble_Debug((0,"\n"));
        #endif
        if(anccCb.active.currMsg.category_id == BLE_ANCS_CATEGORY_ID_INCOMING_CALL)
            anccCb.attr.u8AppType = TYPE_ANCS_MSG_INCALL;
        else if(anccCb.active.currMsg.category_id == BLE_ANCS_CATEGORY_ID_MISSED_CALL)
            anccCb.attr.u8AppType = TYPE_ANCS_MSG_MISSCALL;
        else
        {
            for(int i = 0; i< ANCS_APP_ID_NUM; i++)
            {
                if(memcmp(ancs_app_id_list[i].str,&pAttr->attrDataBuf[pAttr->parseIndex],ancs_app_id_list[i].str_len) == 0)
                {
                    anccCb.attr.u8AppType = ancs_app_id_list[i].type;
                    break;
                }
            }
        }
        anccCb.active.attrtype |= START_GET_APP_ID;
        break;
#if(ANCS_DETIL_TYPE != ANCS_REMIND)
    case BLE_ANCS_NOTIF_ATTR_ID_TITLE:       //标题
        if(pAttr->attrLength > ATTR_TITLE_REQUEST_LEX)
        {
            Err_Info((0,"Error: title len is long than request len\n"));
            return false;
        }
        anccCb.attr.u16TtlIdx = pAttr->parseIndex;
        anccCb.attr.u16TtlLen = pAttr->attrLength;
        anccCb.active.attrtype |= GET_TITLE ;
        break;
    case BLE_ANCS_NOTIF_ATTR_ID_SUBTITLE:     //副标题
        if(pAttr->attrLength > ATTR_TITLE_REQUEST_LEX)
        {
            Err_Info((0,"Error: subtitle len is long than request len\n"));
            return false;
        }
        anccCb.attr.u16SubTtlIdx = pAttr->parseIndex;
        anccCb.attr.u16SubTtlLen = pAttr->attrLength;
        anccCb.active.attrtype |= GET_SUBTITLE ;
        break;
    case BLE_ANCS_NOTIF_ATTR_ID_MESSAGE:     //消息内容
        if(pAttr->attrLength > ATTR_MSG_REQUEST_LEX)
        {
            Err_Info((0,"Error: msg len is long than request len\n"));
            return false;
        }
        anccCb.attr.u16MsgIdx = pAttr->parseIndex;
        anccCb.attr.u16MsgLen = pAttr->attrLength;
        anccCb.active.attrtype |= GET_MSG ;
        break;
#if 0   //以下几种attribute ID应用暂未使用
    case BLE_ANCS_NOTIF_ATTR_ID_MESSAGE_SIZE:   //消息长度
    case BLE_ANCS_NOTIF_ATTR_ID_DATE:           //时间
    case BLE_ANCS_NOTIF_ATTR_ID_POSITIVE_ACTION_LABEL:  //行为
    case BLE_ANCS_NOTIF_ATTR_ID_NEGATIVE_ACTION_LABEL:  //行为
#endif
#endif
    default:
        break;
    }
    return true;
}

/*************************************************************************************************/
/*!
 *  \fn     anccAttrHandler
 *        
 *  \brief  Static routine to handle attribute receiving and processing.
 *
 *  \param  pMsg      pointer to ATT message.
 *
 *  \return None.
 */
/*************************************************************************************************/
static bool ancsAttrHandler(attEvt_t * pMsg)
{
    uint16_t bytesRemaining = 0;
    uint8_t commandId = 0xff;

    switch(anccCb.active.attrState)
    {
    case NOTI_ATTR_NEW_NOTIFICATION:
        // new notification
        commandId = pMsg->pValue[0];
        if(commandId == BLE_ANCS_COMMAND_ID_GET_NOTIF_ATTRIBUTES)
        {
            BYTES_TO_UINT32(anccCb.attr.u32Uid, &(pMsg->pValue[1]));
        }
        else
        {
            Err_Info((0,"Error:NOTI_ATTR_NEW_NOTIFICATION command id is fail\n"));
            return false;
        }

        //接收消息uid和请求的不一致
        if(anccCb.active.currMsg.notification_uid != anccCb.attr.u32Uid)
        {
            Err_Info((0,"Error:notiUid is different from requeted UID\n"));
            return false;
        }

        anccCb.active.parseIndex = 5;
        anccCb.active.attrState = NOTI_ATTR_NEW_ATTRIBUTE;
        anccCb.active.attrId = 0xff;
        anccCb.active.attrtype =0;   //清除接收attr id类型，否则只会解析appid

        anccCb.attr.u8AppType = TYPE_ANCS_MSG_TYPE_INVALID;
        anccCb.attr.u16TtlLen = 0;
        anccCb.attr.u16SubTtlLen = 0;
        anccCb.attr.u16MsgLen = 0;

        bytesRemaining = (pMsg->valueLen > ANCC_ATTRI_BUFFER_SIZE_BYTES) ? ANCC_ATTRI_BUFFER_SIZE_BYTES : pMsg->valueLen;
        // copy data
        memcpy(anccCb.active.attrDataBuf,pMsg->pValue,bytesRemaining);
        anccCb.active.bufIndex = bytesRemaining; //bufIndex此时位置上是无效数据。
        // no break here by intention

    case NOTI_ATTR_NEW_ATTRIBUTE:
        // new attribute
        // check consistency of the attribute
        if(anccCb.active.bufIndex - anccCb.active.parseIndex < 3) // 1 byte attribute id + 2 bytes attribute length
        {
            // attribute header not received completely
            anccCb.active.attrState = NOTI_ATTR_RECEIVING_ATTRIBUTE;
            //启动接收超时
            AnccActionStart(ANCS_TIMER_PARSE);
            Err_Info((0,"warming :consistency of the attribute is fail\n"));
            return false;
        }

        anccCb.active.attrId = anccCb.active.attrDataBuf[anccCb.active.parseIndex];
        BYTES_TO_UINT16(anccCb.active.attrLength, &(anccCb.active.attrDataBuf[anccCb.active.parseIndex + 1]));
        if(anccCb.active.attrLength > (anccCb.active.bufIndex - anccCb.active.parseIndex - 3)) // 1 byte attribute id + 2 bytes attribute length
        {
            // attribute body not received completely
            anccCb.active.attrState = NOTI_ATTR_RECEIVING_ATTRIBUTE;
            //启动接收超时
            AnccActionStart(ANCS_TIMER_PARSE);
            Err_Info((0,"Error:attribute body not received completely\n"));
            return false;
        }

        // parse attribute
        anccCb.active.parseIndex += 3; // 1 byte attribute id + 2 bytes attribute length
        if(ancsAttrParse(&anccCb.active) == false)
        {
            Err_Info((0,"Error: msg data is error\n"));
            anccCb.active.attrState = NOTI_ATTR_NEW_NOTIFICATION;
            return false;
        }

        //各attribute数据解析完成
        if((anccCb.active.attrtype & ATTR_FULL) == ATTR_FULL)
        {
            //notification reception done
            anccCb.active.attrState = NOTI_ATTR_NEW_NOTIFICATION;

            // notification received execute
            ancsAttr_UpLoad(&anccCb);
            return false;
        }

        //解析下一个attribute
        anccCb.active.parseIndex += anccCb.active.attrLength;
        return true; // continue parsing
        // no need to break;
    case NOTI_ATTR_RECEIVING_ATTRIBUTE:
        // notification continuing
        bytesRemaining = ANCC_ATTRI_BUFFER_SIZE_BYTES - anccCb.active.bufIndex;  //attrDataBuf剩余空间大小
        bytesRemaining = (bytesRemaining > pMsg->valueLen) ? pMsg->valueLen : bytesRemaining; //取小者
        // copy data
        memcpy(&anccCb.active.attrDataBuf[anccCb.active.bufIndex],pMsg->pValue,bytesRemaining);
        anccCb.active.bufIndex += bytesRemaining;
        anccCb.active.attrState = NOTI_ATTR_NEW_ATTRIBUTE;
        return true;  
    }
    return false;
}

/*************************************************************************************************/
/*!
 *  \fn     AnccConnOpen
 *        
 *  \brief  Update the key parameters for control variables when connection open.
 *
 *  \param  connId      Connection identifier.
 *  \param  hdlList     Characteristic handle list.
 *
 *  \return None.
 */
/*************************************************************************************************/
static void AncsConnOpen(dmConnId_t connId, uint16_t* hdlList)
{
    anccCb.connId = connId;
    anccCb.hdlList = hdlList;
}

/*************************************************************************************************/
/*!
 *  \fn     AnccConnClose
 *        
 *  \brief  Clear the key parameters for control variables when connection close.
 *
 *  \param  None.
 *
 *  \return None.
 */
/*************************************************************************************************/
static void AncsConnClose(void)
{
    anccCb.connId = DM_CONN_ID_NONE;
}

/*************************************************************************************************/
/*!
 *  \fn     AnccActionHandler
 *        
 *  \brief  Routine to handle ancc related actions.
 *
 *  \param  actionTimerEvt  WsfTimer event indication.
 *
 *  \return None.
 */
/*************************************************************************************************/
static void AncsActionHandler(void)
{
#if(ANCS_VER_TYPE  == ANCS_VER_1)
    //step 1: 定时上传数据
    if(anccCb.timerStatus == ANCS_TIMER_UPLOAD)
    {
        ancsAttr_UpLoad_Timeout();
        return;
    }
#endif

    //step 2: 上一条消息还没有接收全，且超时也没有接收到剩余的数据，则尝试上传数据
    if(anccCb.active.attrtype != 0x00)
    {
        ancsAttr_UpLoad(&anccCb);
        return ;
    }

    //step 3: 从list中pop attribute信息，并向IOS手机请求；无信息则stop timer
    if(anccActionListPop())
    {
        AnccGetNotificationAttribute(anccCb.connId,anccCb.hdlList, anccCb.active.currMsg.notification_uid);
        //AnccActionStart(ANCS_TIMER_PARSE);    //无需再启动timer
    }
    else   //list empty
    {
        /* stop timer */
        WsfTimerStop(&anccCb.actionTimer);
    }
}

//**********************************************************************
// 函数功能: 启动timer，处理下一条消息
// 输入参数：
// 返回参数：
//**********************************************************************
void AncsActionNext(void)
{
    //上传完一条消息数据，启动timer，请求下一条消息
    AnccActionStart(ANCS_TIMER_PARSE);
    //清除接收attr id类型，否则只会解析appid
    anccCb.active.attrtype = 0x00;
    anccCb.attr.u8AppType = TYPE_ANCS_MSG_TYPE_INVALID;    //消息类型先设为无效
}

/*************************************************************************************************/
/*!
 *  \fn     AnccNtfValueUpdate
 *        
 *  \brief  Routine to handle any ancc related notify.
 *
 *  \param  pHdlList  Characteristic handle list.
 *  \param  actionTimerEvt  WsfTimer event indication.
 *  \param  pMsg      pointer to ATT message.
 *
 *  \return None.
 */
/*************************************************************************************************/
void AnccNtfValueUpdate(uint16_t *pHdlList, attEvt_t * pMsg)
{
    attr_notif_t ancs_notif;

    //notification received
    if (pMsg->handle == pHdlList[ANCC_NOTIFICATION_SOURCE_HDL_IDX])
    {
        //step 1:消息已存在，或过时的消息，则不加入anccCb.anccList处理
        if(pMsg->pValue[1] & (0x1 << BLE_ANCS_EVENT_FLAG_PREEXISTING))
        {
            //Ble_Debug((0,"* pre_existing nitification\n"));
            return;
        }

        //step 2: process notificiation source (brief)
        ancs_notif.event_id = pMsg->pValue[0];
        ancs_notif.event_flags = pMsg->pValue[1];
        ancs_notif.category_id = pMsg->pValue[2];
        ancs_notif.category_count = pMsg->pValue[3];
        BYTES_TO_UINT32(ancs_notif.notification_uid, &pMsg->pValue[4]);

        //step 3:消息属性是removed
        if(BLE_ANCS_EVENT_ID_NOTIFICATION_REMOVED == ancs_notif.event_id) 
        {
            //消息删除，处理完直接退出            
            Ble_Debug((0,"Nofity removed, event_id = %d\n", ancs_notif.event_id));
            Ble_Debug((0,"Nofity removed, category_id = %d\n", ancs_notif.category_id));
            Ble_Debug((0,"Nofity removed, notification_uid = %d\n", ancs_notif.notification_uid));
            ancsAttr_Cancle(&ancs_notif);
            return ;
        }

        //step 4:消息属性是add或modified，加入消息list
        anccActionListPush(&ancs_notif);

        //step 5:如果list中只有1条消息或有电话信息时，需启动timer,消息多时，解析完一条在请求下一条
        if((anccCb.msgInfo.u8attCnt == 1) || ((anccCb.msgInfo.u8attCnt == 0) && (anccCb.call.isValid == TRUE)))
        {
            // actions to be done with timer delays to avoid generating heavy traffic
            AnccActionStart(ANCS_TIMER_PARSE);
        }
    }
    else if(pMsg->handle == pHdlList[ANCC_DATA_SOURCE_HDL_IDX])
    {
        if(anccCb.active.currMsg.event_flags & (0x1 << BLE_ANCS_EVENT_FLAG_PREEXISTING))
        {
            Ble_Debug((0,"* pre_existing nitification \n"));
            return;
        }

        // process notificiation/app attributes
        while(ancsAttrHandler(pMsg));
    }
}

//**********************************************************************
// 函数功能: 处理和ANCS相关的事件
// 输入参数：pMsg:指向消息
// 返回参数：
//**********************************************************************
void Ble_Ancs_HandleProcMsg(m_ble_profile_msg_t *pMsg)
{
    switch(pMsg->hdr.event)
    {
    case ANCC_ACTION_TIMER_IND:
        AncsActionHandler();
        break;
    case ATTC_READ_RSP:
    case ATTC_HANDLE_VALUE_NTF:
    case ATTC_HANDLE_VALUE_IND:
        Ble_Debug((0,"-------ATTC_HANDLE_VALUE_NTF/IND-------\n"));
        AnccValueUpdate((attEvt_t *) pMsg);
        break;
    case ATTC_WRITE_RSP:    // write respose after Control point operation. 
        Ble_Debug((0,"------ATTC_WRITE_RSP--------\n"));
        break;
    case DM_CONN_OPEN_IND:
        /* set bondable here to enable bond/pair after disconnect */
        AncsConnOpen(pMsg->hdr.param, pAncsAnccHdlList);
        break;
    case DM_CONN_CLOSE_IND:
        AncsConnClose();
        anccActionListClear();
        anccCb.timerStatus = ANCS_TIMER_PARSE;
        break;
    default:
        break;
    }
}

//**********************************************************************
// 函数功能: 来电拒接，拒接当前来电
// 输入参数：
// 返回参数：
//**********************************************************************
void Ble_Ancs_DoCall(uint8_t u8Operate)
{
    if(u8Operate == 0)    //来电拒接
    {
        AncsPerformNotiAction(anccCb.connId,anccCb.hdlList, incall_notify_uid, BLE_ANCS_NOTIF_ACTION_ID_NEGATIVE);
    }
    else if(u8Operate == 1)    //来电接听
    {
        AncsPerformNotiAction(anccCb.connId,anccCb.hdlList, incall_notify_uid, BLE_ANCS_NOTIF_ACTION_ID_POSITIVE);
    }
}

//**********************************************************************
// 函数功能: Application handler init function called during system initialization.
// 输入参数：handlerID  WSF handler ID.App handler id for timer operation.
// 返回参数：
//**********************************************************************
void Ble_Ancs_HandlerInit(wsfHandlerId_t handlerId)
{
    /* Initialize application framework */    
    memset(&anccCb.msgInfo, 0, sizeof(ancc_notif_t));
    anccCb.call.isValid = FALSE;
    /* initialize control block */  //ANCS timer  
    anccCb.actionTimer.handlerId = handlerId;
    anccCb.actionTimer.msg.event = ANCC_ACTION_TIMER_IND;
    anccCb.timerStatus = ANCS_TIMER_PARSE;
}
#endif

