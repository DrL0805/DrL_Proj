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
 *  \fn     �Կɱ�����/�ɱ����ӵķ�ʽ���������㲥
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
// ��������: ���������㲥��
// ���������buf:Э������
// ���ز�����
//**********************************************************************
void BLE_Kernal_SetAdvName(uint8 *buf,uint8 u8len);

//**********************************************************************
// ��������: ���ù��ܺ���callback
// ���������fun
// ���ز�����Ret_OK:������  
//    Ret_InvalidParam: �����Ƿ�
//**********************************************************************
ret_type BLE_Kernal_SetFunc(Ble_Kernal_f *fun);

//**********************************************************************
// ��������: ����BLEЭ��ջ������app profile
// ���������
// ���ز�����
//**********************************************************************
extern void BLE_Kernal_start(void);

//**********************************************************************
// ��������: Э��ջ�¼������ýӿ�ע�ᵽЭ��ջ��
// ���������event:�¼���pMsg:��Ϣ
// ���ز�����
//**********************************************************************
extern void BLE_Kernal_Handler(wsfEventMask_t event, wsfMsgHdr_t *pMsg);

//**********************************************************************
// ��������: ��ʼ��Э��ջ����ʼ��Э��ջ������
// ���������handlerId: handle ID
// ���ز�����
//**********************************************************************
extern void BLE_Kernal_Handler_Init(wsfHandlerId_t handlerId);

#if(APOLLO_OTA_TYPE == APOLLO_OTA_VER_2)
//**********************************************************************
// ��������: ��ȡBLE������ʲô״̬��
// ���������
// ���ز�����BLE_IN_APP:BLE������APPģʽ��
//           BLE_IN_OTA:BLE������OTAģʽ��
//**********************************************************************
uint8 BLE_Stack_GetBleSatus(void);

//**********************************************************************
// ��������: ����BLE����״̬
// ���������BLE_IN_APP:BLE������APPģʽ��
//           BLE_IN_OTA:BLE������OTAģʽ��
// ���ز�����
//**********************************************************************
void BLE_Stack_SetBleSatus(uint8 u8status);
#endif

#endif

