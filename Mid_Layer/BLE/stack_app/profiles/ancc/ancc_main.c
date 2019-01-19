//*****************************************************************************
//
//! @file   ancc_main.c
//!
//! @brief  apple notification center service client.
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
#include "platform_debugcof.h"
#include "platform_common.h"
#include "wsf_types.h"
#include "wsf_assert.h"
#include "bstream.h"
#include "app_api.h"

#if(ANCS_DETIL_TYPE != ANCS_NONE)
#include "gatt_api.h"
#include "ancs_api.h"
#include "ancc_api.h"
#include "BLE_Kernal.h"

#if(BLE_STACK_DEBUG_ENABLE ==1)    
#define Ble_Debug(x) SEGGER_RTT_printf x
#else
#define Ble_Debug(x)
#endif

/**************************************************************************************************
  Local Variables
**************************************************************************************************/
static ble_control_s m_ble_profile_cb;

/**************************************************************************************************
  ATT Client Discovery Data
**************************************************************************************************/

/*! Discovery states:  enumeration of services to be discovered */
enum
{
  ANCS_DISC_GATT_SVC,      /* GATT service */
  ANCS_DISC_ANCS_SVC,      /* discover ANCS service */
  ANCS_DISC_SVC_MAX        /* Discovery complete */
};

/*! Start of each service's handles in the the handle list */
#define ANCS_DISC_GATT_START        0
#define ANCS_DISC_ANCS_START        (ANCS_DISC_GATT_START + GATT_HDL_LIST_LEN)
#define ANCS_DISC_HDL_LIST_LEN      (ANCS_DISC_ANCS_START + ANCC_HDL_LIST_LEN)

/*! Pointers into handle list for each service's handles */
static uint16_t *pAncsGattHdlList = &m_ble_profile_cb.hdlList[ANCS_DISC_GATT_START];
uint16_t *pAncsAnccHdlList = &m_ble_profile_cb.hdlList[ANCS_DISC_ANCS_START];

/* sanity check:  make sure handle list length is <= app db handle list length */
WSF_CT_ASSERT(ANCS_DISC_HDL_LIST_LEN <= APP_DB_HDL_LIST_LEN);

/**************************************************************************************************
  ATT Client Configuration Data
**************************************************************************************************/

/*
 * Data for configuration after service discovery
 */

/* Default value for CCC notifications */
static const uint8_t m_ble_profileCccNtfVal[] = {UINT16_TO_BYTES(ATT_CLIENT_CFG_NOTIFY)}; 

/* List of characteristics to configure after service discovery */
static const attcDiscCfg_t m_ble_profileDiscCfgList[] =
{
  /* Write:  GATT service changed ccc descriptor */
  {m_ble_profileCccNtfVal, sizeof(m_ble_profileCccNtfVal), (GATT_SC_CCC_HDL_IDX + ANCS_DISC_GATT_START)},

  /* Write:  ANCS setting ccc descriptor */
  {m_ble_profileCccNtfVal, sizeof(m_ble_profileCccNtfVal), (ANCC_NOTIFICATION_SOURCE_CCC_HDL_IDX + ANCS_DISC_ANCS_START)},

  /* Write:  ANCS setting ccc descriptor */
  {m_ble_profileCccNtfVal, sizeof(m_ble_profileCccNtfVal), (ANCC_DATA_SOURCE_CCC_HDL_IDX + ANCS_DISC_ANCS_START)},
};

/* Characteristic configuration list length */
#define ANCS_DISC_CFG_LIST_LEN   (sizeof(m_ble_profileDiscCfgList) / sizeof(attcDiscCfg_t))

/* sanity check:  make sure configuration list length is <= handle list length */
WSF_CT_ASSERT(ANCS_DISC_CFG_LIST_LEN <= ANCS_DISC_HDL_LIST_LEN);


/*!
 *  Apple Notification Center Service Client (ANCC)
 */

/* UUIDs */
static const uint8_t anccAncsSvcUuid[] = {ATT_UUID_ANCS_SERVICE};       /*! ANCS Service UUID */
static const uint8_t anccNSChUuid[] = {ATT_UUID_NOTIFICATION_SOURCE};    /*! Notification Source UUID */
static const uint8_t anccCPChUuid[] = {ATT_UUID_CTRL_POINT};             /*! control point UUID*/
static const uint8_t anccDSChUuid[] = {ATT_UUID_DATA_SOURCE};            /*! data source UUID*/
/* Characteristics for discovery */

/*! Proprietary data */
static const attcDiscChar_t anccNSDat = 
{
    anccNSChUuid,
    ATTC_SET_REQUIRED | ATTC_SET_UUID_128
};

/*! Proprietary data descriptor */  //notification source
static const attcDiscChar_t anccNSdatCcc = 
{
    attCliChCfgUuid,
    ATTC_SET_REQUIRED | ATTC_SET_DESCRIPTOR
};
// control point
static const attcDiscChar_t anccCtrlPoint = 
{
    anccCPChUuid,
    ATTC_SET_REQUIRED | ATTC_SET_UUID_128
};

// data source
static const attcDiscChar_t anccDataSrc = 
{
    anccDSChUuid,
    ATTC_SET_REQUIRED | ATTC_SET_UUID_128
};
/*! Proprietary data descriptor */  //data source
static const attcDiscChar_t anccDataSrcCcc = 
{
    attCliChCfgUuid,
    ATTC_SET_REQUIRED | ATTC_SET_DESCRIPTOR
};

/*! List of characteristics to be discovered; order matches handle index enumeration  */
static const attcDiscChar_t *anccSvcDiscCharList[] =
{
    &anccNSDat,                    /*! Proprietary data */
    &anccNSdatCcc,                 /*! Proprietary data descriptor */
    &anccCtrlPoint,                /*! Control point */
    &anccDataSrc,                  /*! data source */
    &anccDataSrcCcc                /*! data source descriptor */
};

/* sanity check:  make sure handle list length matches characteristic list length */
WSF_CT_ASSERT(ANCC_HDL_LIST_LEN == ((sizeof(anccSvcDiscCharList) / sizeof(attcDiscChar_t *))));

//fix 1:ANCS服务发现，解决手机只开蓝牙，不开应用APP，也可以支持ANCS功能
static ble_echo pAncs_CB = NULL;
static uint8_t u8DiscStatus = 0x00;
//fix 

/*************************************************************************************************/
/*!
 *  \fn     AnccSvcDiscover
 *        
 *  \brief  Perform service and characteristic discovery for ancs service. 
 *          Parameter pHdlList must point to an array of length ANCC_HDL_LIST_LEN. 
 *          If discovery is successful the handles of discovered characteristics and
 *          descriptors will be set in pHdlList.
 *
 *  \param  connId    Connection identifier.
 *  \param  pHdlList  Characteristic handle list.
 *
 *  \return None.
 */
/*************************************************************************************************/
void AnccSvcDiscover(dmConnId_t connId, uint16_t *pHdlList)
{
    AppDiscFindService(connId, ATT_128_UUID_LEN, (uint8_t *) anccAncsSvcUuid,
                     ANCC_HDL_LIST_LEN, (attcDiscChar_t **) anccSvcDiscCharList, pHdlList);
}

/*************************************************************************************************/
/*!
 *  \fn     AnccGetNotificationAttribute
 *        
 *  \brief  Send a command to the apple notification center service control point.
 *
 *  \param  pHdlList  Characteristic handle list.
 *  \param  notiUid   NotificationUid.
 *
 *  \return None.
 */
/*************************************************************************************************/
void AnccGetNotificationAttribute(dmConnId_t connId,uint16_t *pHdlList, uint32_t notiUid)
{
    // An example to get notification attributes
#if(ANCS_DETIL_TYPE == ANCS_REMIND)
    uint8_t buf[6];   // retrieve the complete attribute list
#else
    uint8_t buf[15];   // retrieve the complete attribute list
#endif
    
    if (pHdlList[ANCC_CONTROL_POINT_HDL_IDX] != ATT_HANDLE_NONE)
    {
        buf[0] = BLE_ANCS_COMMAND_ID_GET_NOTIF_ATTRIBUTES;  // put command
        uint8_t * p = &buf[1];
        UINT32_TO_BSTREAM(p, notiUid);    // encode notification uid

        // encode attribute IDs
        buf[5] = BLE_ANCS_NOTIF_ATTR_ID_APP_IDENTIFIER;
#if(ANCS_DETIL_TYPE != ANCS_REMIND)   //只有消息提醒的时候，不需要title，subtitile和msg
        buf[6] = BLE_ANCS_NOTIF_ATTR_ID_TITLE;
        // 2 byte length
        buf[7] = ATTR_TITLE_REQUEST_LEX;
        buf[8] = ATTR_TITLE_REQUEST_LEX >> 8;
        
        buf[9] = BLE_ANCS_NOTIF_ATTR_ID_SUBTITLE;
        buf[10] = ATTR_TITLE_REQUEST_LEX;
        buf[11] = ATTR_TITLE_REQUEST_LEX >> 8;       //title 和subtitle最大请求数据128
        
        buf[12] = BLE_ANCS_NOTIF_ATTR_ID_MESSAGE;
        buf[13] = ATTR_MSG_REQUEST_LEX;
        buf[14] = ATTR_MSG_REQUEST_LEX >> 8;       //消息内容最大请求150，总共406 byte(除app id)
#if 0  //时间和行为，未使用到，暂不请求
        buf[15] = BLE_ANCS_NOTIF_ATTR_ID_MESSAGE_SIZE;
        buf[16] = BLE_ANCS_NOTIF_ATTR_ID_DATE;
        buf[17] = BLE_ANCS_NOTIF_ATTR_ID_POSITIVE_ACTION_LABEL;
        buf[18] = BLE_ANCS_NOTIF_ATTR_ID_NEGATIVE_ACTION_LABEL;
#endif
#endif
        AttcWriteReq(connId, pHdlList[ANCC_CONTROL_POINT_HDL_IDX], sizeof(buf), buf);
    }
}

#if(READ_NP_APP_ATTR == 1)
/*************************************************************************************************/
/*!
 *  \fn     AncsGetAppAttribute
 *        
 *  \brief  Send a command to the apple notification center service control point.
 *
 *  \param  pHdlList  Connection identifier.
 *  \param  pAppId    Attribute handle.
 *
 *  \return None.
 */
/*************************************************************************************************/
void AncsGetAppAttribute(dmConnId_t connId,uint16_t *pHdlList, uint8_t *pAppId)
{
    // An example to get app attributes
    uint8_t buf[64];   // to hold the command, size of app identifier is unknown
    uint8_t count = 0;
    if (pHdlList[ANCC_CONTROL_POINT_HDL_IDX] != ATT_HANDLE_NONE)
    {
        buf[0] = BLE_ANCS_COMMAND_ID_GET_APP_ATTRIBUTES;    // put command

        while (pAppId[count++] != 0);   // NULL terminated string
        if(count > (64 - 2))
        {
            // app identifier is too long
        }
        else
        {
            memcpy(&buf[1], pAppId, count);
        }

        buf[count + 1] = 0; // app attribute id
        AttcWriteReq(connId, pHdlList[ANCC_CONTROL_POINT_HDL_IDX], (count + 2), buf);
    }
}
#endif

/*************************************************************************************************/
/*!
 *  \fn     AncsPerformNotiAction
 *        
 *  \brief  Send a command to the apple notification center service control point.
 *
 *  \param  pHdlList  Characteristic handle list.
 *  \param  actionId  Notification action identifier.
 *  \param  notiUid   NotificationUid.
 *
 *  \return None.
 */
/*************************************************************************************************/
void AncsPerformNotiAction(dmConnId_t connId,uint16_t *pHdlList, uint32_t notiUid, ancc_notif_action_id_values_t actionId)
{
    // An example to performs notification action
    uint8_t buf[6];   //to hold the command, size of app identifier is unknown
    if (pHdlList[ANCC_CONTROL_POINT_HDL_IDX] != ATT_HANDLE_NONE)
    {
        buf[0] = BLE_ANCS_COMMAND_ID_GET_PERFORM_NOTIF_ACTION;    // put command
        uint8_t * p = &buf[1];
        UINT32_TO_BSTREAM(p, notiUid);      // encode notification uid
        buf[5] = actionId;                  //action id
        AttcWriteReq(connId, pHdlList[ANCC_CONTROL_POINT_HDL_IDX], sizeof(buf), buf);
    }
}

/*************************************************************************************************/
/*!
 *  \fn     anccDiscCback
 *
 *  \brief  Discovery callback.
 *
 *  \param  connId    Connection identifier.
 *  \param  status    Service or configuration status.
 *
 *  \return None.
 */
/*************************************************************************************************/
static void anccDiscCback(dmConnId_t connId, uint8_t status)
{
    switch(status)
    {
    case APP_DISC_INIT:
        /* set handle list when initialization requested */
        AppDiscSetHdlList(connId, ANCS_DISC_HDL_LIST_LEN, m_ble_profile_cb.hdlList);
        break;
    case APP_DISC_SEC_REQUIRED:
        //fix: 解决手表绑定信息丢失，ancs功能不起作用
        /* request security */
        //AppSlaveSecurityReq(connId);  //此处不能做，会打乱app连接过程流程，导致app不能正常使用
        //fix: 2018.12.11
        break;
    case APP_DISC_START:
        /* initialize discovery state */
        m_ble_profile_cb.discState = ANCS_DISC_GATT_SVC;

        /* discover GATT service */
        GattDiscover(connId, pAncsGattHdlList);
        u8DiscStatus = 0x00;
        break;
    case APP_DISC_FAILED:
        u8DiscStatus = 0x01;
        Ble_Debug((0,"!!!!!Disc Failed. discState = %d!!!!!\n", m_ble_profile_cb.discState));
    case APP_DISC_CMPL:
        //expecting only m_ble_profile service to be discovered
        m_ble_profile_cb.discState++;
        if (m_ble_profile_cb.discState == ANCS_DISC_ANCS_SVC)
        {
            /* discover ANCS service */
            AnccSvcDiscover(connId, pAncsAnccHdlList);
            Ble_Debug((0,"Discovering ANCS.\n"));
        }
        else
        {
            /* discovery complete */
            AppDiscComplete(connId, APP_DISC_CMPL);
            Ble_Debug((0,"Finished ANCS discovering.\n"));

            /* start configuration */
            Ble_Debug((0,"Disc CFG start.\n"));
            AppDiscConfigure(connId, APP_DISC_CFG_START, ANCS_DISC_CFG_LIST_LEN,
                         (attcDiscCfg_t *) m_ble_profileDiscCfgList, ANCS_DISC_HDL_LIST_LEN, m_ble_profile_cb.hdlList);

            //fix 1:ANCS服务发现，解决手机只开蓝牙，不开应用APP，也可以支持ANCS功能
            // IOS手机不会发生APP_DISC_FAILED事件，Android手机会有此事件
            if((pAncs_CB != NULL) && (u8DiscStatus != 0x01))
            {
                (pAncs_CB)(BLE_ANCS_DISCOVERING,0,0);
                u8DiscStatus = 0x00;
            }
            //fix: 2018.6.8
        }
        break;
    case APP_DISC_CFG_START:
        /* start configuration */
        AppDiscConfigure(connId, APP_DISC_CFG_START, ANCS_DISC_CFG_LIST_LEN,
                       (attcDiscCfg_t *) m_ble_profileDiscCfgList, ANCS_DISC_HDL_LIST_LEN, m_ble_profile_cb.hdlList);
        break;
    case APP_DISC_CFG_CMPL:
        AppDiscComplete(connId, status);
        Ble_Debug((0,"Finished Disc CFG."));
        break;
    case APP_DISC_CFG_CONN_START:
        /* start connection setup configuration */
        AppDiscConfigure(connId, APP_DISC_CFG_CONN_START, ANCS_DISC_CFG_LIST_LEN,
                       (attcDiscCfg_t *) m_ble_profileDiscCfgList, ANCS_DISC_HDL_LIST_LEN, m_ble_profile_cb.hdlList);
        break;
    default:
        break;
    }
}

/*************************************************************************************************/
/*!
 *  \fn     AnccValueUpdate
 *
 *  \brief  Process a received ATT read response, notification, or indication.
 *
 *  \param  pMsg    Pointer to ATT callback event message.
 *
 *  \return None.
 */
/*************************************************************************************************/
void AnccValueUpdate(attEvt_t *pMsg)
{
    /* iOS notification */
    if ((pMsg->handle == pAncsAnccHdlList[ANCC_NOTIFICATION_SOURCE_HDL_IDX]) ||
        (pMsg->handle == pAncsAnccHdlList[ANCC_DATA_SOURCE_HDL_IDX]) ||
        (pMsg->handle == pAncsAnccHdlList[ANCC_CONTROL_POINT_HDL_IDX]))
    {
        AnccNtfValueUpdate(pAncsAnccHdlList, pMsg);
    }
    else
    {
        Ble_Debug((0,"Data received from other other handle\n"));
    }

    /* GATT */
    if (GattValueUpdate(pAncsGattHdlList, pMsg) == ATT_SUCCESS)
    {
        return;
    }
}

//**********************************************************************
// 函数功能: Start the application.注册回调，创建服务，复位协议栈
// 输入参数：
// 返回参数：
//**********************************************************************
void Ble_Ancs_Start(void)
{
    /* Register for app framework discovery callbacks */
    AppDiscRegister(anccDiscCback);
}

//**********************************************************************
// 函数功能: 设置check ANCS发现回调，用于解决手机只开蓝牙，不开应用APP，
//           也可以支持ANCS功能
// 输入参数：pfun:callback
// 返回参数：
//**********************************************************************
void Ble_Ancs_Check_Cb(ble_echo pfun)
{
    if(pfun == NULL)
        return ;
    pAncs_CB = pfun;
}
#endif

