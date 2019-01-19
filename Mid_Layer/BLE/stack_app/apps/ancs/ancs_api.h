//*****************************************************************************
//
//! @file   ancs_aph.h
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

#ifndef ANCS_API_H
#define ANCS_API_H

#include "wsf_os.h"
#include "stdint.h"
#include "stdbool.h"
#include "lowsapp_main.h"
#include "BLE_Stack.h"
#include "BLE_Kernal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************************************
  Macros
**************************************************************************************************/

typedef enum
{   
    START_GET_ATTR,
    START_GET_APP_ID,
    GET_TITLE,
    GET_SUBTITLE,
    GET_MSG,
    POSITIVE_ACTION,
    NEGATIVE_ACTION,
    MSG_OP_END
}GET_MSG_OP_STATE;

#if(ANCS_DETIL_TYPE == ANCS_REMIND)
#define ATTR_FULL START_GET_APP_ID
#elif((ANCS_DETIL_TYPE == ANCS_DETIL) || (ANCS_DETIL_TYPE == ANCS_DETIL_NEW))
#define ATTR_FULL (START_GET_APP_ID | GET_TITLE | GET_SUBTITLE | GET_MSG)
#endif

typedef void (*ancs_msg_type_handler)(const uint8_t *buf,uint8_t len,uint8_t type, uint32_t u32MsgId);
typedef void (*ancs_msg_detail_handler)(const uint8_t *buf,uint8_t len,GET_MSG_OP_STATE get_msg_op_state,uint32_t u32MsgId);

//#define CHECK_VALID_BIT(bitmap, bit)            ( (((bitmap) & (bit)) == (bit)) ? true : false )
//#define SET_VALID_BIT(bitmap, bit, bit_mask)    (bitmap) |= ((bit) & (bit_mask))

//**********************************************************************
// ��������: ����ܽӣ��ܽӵ�ǰ����
// ���������
// ���ز�����
//**********************************************************************
extern void Ble_Ancs_DoCall(uint8_t u8Operate);

/**************************************************************************************************
  Function Declarations
**************************************************************************************************/

//**********************************************************************
// ��������: Start the application.ע��ص����������񣬸�λЭ��ջ
// ���������
// ���ز�����
//**********************************************************************
extern void Ble_Ancs_Start(void);

//**********************************************************************
// ��������: Application handler init function called during system initialization.
// ���������handlerID  WSF handler ID.
// ���ز�����
//**********************************************************************
extern void Ble_Ancs_HandlerInit(wsfHandlerId_t handlerId);

//**********************************************************************
// ��������: WSF event handler for application.
// ���������event   WSF event mask.
//           pMsg    WSF message.
// ���ز�����
//**********************************************************************
extern void Ble_Ancs_Handler(wsfEventMask_t event, wsfMsgHdr_t *pMsg);

//**********************************************************************
// ��������: ����check ANCS���ֻص������ڽ���ֻ�ֻ������������Ӧ��APP��
//           Ҳ����֧��ANCS����
// ���������pfun:callback
// ���ز�����
//**********************************************************************
extern void Ble_Ancs_Check_Cb(ble_echo pfun);

//**********************************************************************
// ��������: �����ANCS��ص��¼�
// ���������pMsg:ָ����Ϣ
// ���ز�����
//**********************************************************************
extern void Ble_Ancs_HandleProcMsg(m_ble_profile_msg_t *pMsg);

#ifdef __cplusplus
};
#endif

#endif /* ANCS_API_H */
