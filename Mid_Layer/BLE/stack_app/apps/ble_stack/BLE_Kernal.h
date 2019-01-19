#ifndef __BLE_KERNAL__H
#define __BLE_KERNAL__H

#include "app_cfg.h"

#define BLE_IN_APP    0
#define BLE_IN_OTA    1

#ifndef ANCS_CONN_MAX
#define ANCS_CONN_MAX                  1
#endif

/*! WSF message event starting value */
#define ANCS_MSG_START               0xA0

/*! WSF message event enumeration */
enum
{
    ANCC_ACTION_TIMER_IND = ANCS_MSG_START,     /*! ANCC action timer expired */
    AMOTA_RESET_TIMER_IND,                      /*! AMOTA reset timer expired */ 
    AMOTA_DISCONNECT_TIMER_IND,                 /*! AMOTA disconnect timer expired */
    APP_SEND_ANCS_MSG_TIMEOUT_IND,
};

/*! application control block */
typedef struct
{
  /* m_ble_profile tracking variables */
  uint16_t          hdlList[APP_DB_HDL_LIST_LEN];
  wsfHandlerId_t    handlerId;
  uint8_t           discState;
  uint16_t          connInterval;     /* connection interval */
}ble_control_s;

/*! Application message type */
typedef union
{
    wsfMsgHdr_t     hdr;
    dmEvt_t         dm;
    attsCccEvt_t    ccc;
    attEvt_t        att;
} m_ble_profile_msg_t;

typedef struct
{
    void (*Ble_HandlerInit)(wsfHandlerId_t handlerId);
    void (*Ble_Handler)(wsfEventMask_t event, wsfMsgHdr_t *pMsg);
}Ble_Kernal_f;

/*************************************************************************************************/
/*!
 *  \fn     以可被查找/可被连接的方式开启蓝牙广播
 *
 *  \brief  Set up advertising and other procedures that need to be performed after
 *          device reset.
 *
 *  \param  pMsg    Pointer to message.
 *
 *  \return None.
 */
/*************************************************************************************************/
void BLE_Kernal_AdvSetup(void);

//**********************************************************************
// 函数功能: 设置蓝牙广播名
// 输入参数：buf:协议数据
// 返回参数：
//**********************************************************************
void BLE_Kernal_SetAdvName(uint8 *buf,uint8 u8len);

//**********************************************************************
// 函数功能: 设置功能函数callback
// 输入参数：fun
// 返回参数：Ret_OK:正常，  
//    Ret_InvalidParam: 参数非法
//**********************************************************************
ret_type BLE_Kernal_SetFunc(Ble_Kernal_f *fun);

//**********************************************************************
// 函数功能: 启动BLE协议栈，创建app profile
// 输入参数：
// 返回参数：
//**********************************************************************
extern void BLE_Kernal_start(void);

//**********************************************************************
// 函数功能: 协议栈事件处理，该接口注册到协议栈内
// 输入参数：event:事件，pMsg:消息
// 返回参数：
//**********************************************************************
extern void BLE_Kernal_Handler(wsfEventMask_t event, wsfMsgHdr_t *pMsg);

//**********************************************************************
// 函数功能: 初始化协议栈，初始化协议栈参数等
// 输入参数：handlerId: handle ID
// 返回参数：
//**********************************************************************
extern void BLE_Kernal_Handler_Init(wsfHandlerId_t handlerId);

#if(APOLLO_OTA_TYPE == APOLLO_OTA_VER_2)
//**********************************************************************
// 函数功能: 获取BLE运行在什么状态下
// 输入参数：
// 返回参数：BLE_IN_APP:BLE运行在APP模式下
//           BLE_IN_OTA:BLE运作在OTA模式下
//**********************************************************************
uint8 BLE_Stack_GetBleSatus(void);

//**********************************************************************
// 函数功能: 设置BLE运行状态
// 输入参数：BLE_IN_APP:BLE运行在APP模式下
//           BLE_IN_OTA:BLE运作在OTA模式下
// 返回参数：
//**********************************************************************
void BLE_Stack_SetBleSatus(uint8 u8status);
#endif

#endif

