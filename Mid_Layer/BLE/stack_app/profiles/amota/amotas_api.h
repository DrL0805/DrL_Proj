//*****************************************************************************
//
//  amotas_api.h
//! @file
//!
//! @brief Brief description of the header. No need to get fancy here.
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2018, Ambiq Micro
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
// Third party software included in this distribution is subject to the
// additional license terms as defined in the /docs/licenses directory.
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
// This is part of revision 1.2.12 of the AmbiqSuite Development Package.
//
//*****************************************************************************
#ifndef AMOTAS_API_H
#define AMOTAS_API_H

#include "wsf_timer.h"
#include "att_api.h"

#include "BLE_Stack.h"

#ifdef __cplusplus
extern "C"
{
#endif
//*****************************************************************************
//
// Macro definitions
//
//*****************************************************************************
#define AMOTA_PACKET_SIZE           (512 + 16)    // Bytes
#define AMOTA_LENGTH_SIZE_IN_PKT    2
#define AMOTA_CMD_SIZE_IN_PKT       1
#define AMOTA_CRC_SIZE_IN_PKT       4
#define AMOTA_HEADER_SIZE_IN_PKT    AMOTA_LENGTH_SIZE_IN_PKT + AMOTA_CMD_SIZE_IN_PKT

#define AMOTA_FW_HEADER_SIZE        44

#define AMOTA_FW_STORAGE_INTERNAL   0
#define AMOTA_FW_STORAGE_EXTERNAL   1

//定义升级数据类型
#define OTA_DATA_CORE      0    //BLE CORE数据类型
#define OTA_DATA_APP       1    //APP数据类型
#define OTA_DATA_UPDATE    2    //场景升级数据类型


/*! Configurable parameters */
typedef struct
{
    //! Short description of each member should go here.
    uint32_t reserved;
}
AmotasCfg_t;

typedef struct
{
    uint8_t u8Language;    //UI显示文字语言
    uint8_t u8AvdName[11]; //蓝牙广播名
    uint8_t u8MacAddr[6];  //蓝牙mac地址
}ble_otainfo_t;

typedef struct
{
    uint32_t u32FwLen;
    uint32_t u32FwCrc;
}ble_updateinfo_t;

typedef struct
{
    uint8_t u8IsOTA;       //OTA标识
    uint8_t u8IsUpdate;    //更新标识，更新场景或主题
    union
    {
        ble_otainfo_t ota;
        ble_updateinfo_t update;
    }info;
}ble_otaflag_t;

//*****************************************************************************
//
// External variable definitions
//
//*****************************************************************************


//*****************************************************************************
//
// External function definitions.
//
//*****************************************************************************

//*****************************************************************************
//
// function definitions
//
//*****************************************************************************

//set callback for notify OTA to app
void amotas_set_callback(ble_echo pfun);

void amotas_init(wsfHandlerId_t handlerId, AmotasCfg_t *pCfg);

void amotas_proc_msg(wsfMsgHdr_t *pMsg);

uint8_t amotas_write_cback(dmConnId_t connId, uint16_t handle, uint8_t operation,
                       uint16_t offset, uint16_t len, uint8_t *pValue, attsAttr_t *pAttr);

void amotas_start(dmConnId_t connId, uint8_t resetTimerEvt, uint8_t disconnectTimerEvt, uint8_t amotaCccIdx);

void amotas_stop(dmConnId_t connId);

extern void amotas_conn_close(dmConnId_t connId);

//**********************************************************************
// 函数功能: 保存OTA flag到内部flash
// 输入参数：u8flagtype:标识类型: OTA_DATA_APP,OTA_DATA_UPDATE
//           potaflag: 指针指向要保存的ota flag数据
// 返回参数：0:成功，1失败
//**********************************************************************
extern uint8 amotas_storeflag(uint8 u8flagtype, ble_otaflag_t *potaflag);

//**********************************************************************
// 函数功能: 清除升级flag，并重写回内部flash
// 输入参数：u8flagtype: 升级类型,OTA_DATA_APP,OTA_DATA_UPDATE
// 返回参数：0:成功，1失败
//**********************************************************************
extern uint8 amotas_clearflag(uint8 u8flagtype);

#ifdef __cplusplus
}
#endif

#endif // AMOTAS_API_H
