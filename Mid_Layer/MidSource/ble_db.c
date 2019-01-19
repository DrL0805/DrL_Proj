/*************************************************************************************************/
/*!
 *  \file   app_db.c
 *
 *  \brief  Application framework device database example, using simple RAM-based storage.
 *
 *          $Date: 2017-03-21 16:17:43 -0500 (Tue, 21 Mar 2017) $
 *          $Revision: 11622 $
 *
 *  Copyright (c) 2011-2017 ARM Ltd., all rights reserved.
 *  ARM Ltd. confidential and proprietary.
 *
 *  IMPORTANT.  Your use of this file is governed by a Software License Agreement
 *  ("Agreement") that must be accepted in order to download or otherwise receive a
 *  copy of this file.  You may not use or copy this file for any purpose other than
 *  as described in the Agreement.  If you do not agree to all of the terms of the
 *  Agreement do not use this file and delete all copies in your possession or control;
 *  if you do not have a copy of the Agreement, you must contact ARM Ltd. prior
 *  to any use, copying or further distribution of this software.
 */
/*************************************************************************************************/
#include "platform_common.h"
#include "platform_debugcof.h"
#include "platform_feature.h"

#include "app_db.h"
#include "ble_db.h"

#include "store_common.h"  //for BLE paring info
#include "store_part.h"

#if(MID_BLE_DEBUG == 1)
#define Db_Debug(x) SEGGER_RTT_printf x
#else
#define Db_Debug(x)
#endif

typedef struct 
{
    uint32_t u32KeyNum;   //记录有多少个设备与此设备配对
    appDbRec_t appdb[APP_DB_NUM_RECS];
}Ble_PassKey;

static Ble_PassKey passkey;

#if 0
//**********************************************************************
// 函数功能: 清除配对信息，Ram和flash中都要清除
// 输入参数：
// 返回参数：
//**********************************************************************
uint8_t Mid_Ble_DbRecClear(void)
{
    //step 1:判断是否有配对信息
    if((*(uint32_t*)(passkey.appdb[0].peerAddr) == 0xFFFFFFFF) && (*(uint32_t*)(passkey.appdb[1].peerAddr) == 0xFFFFFFFF) && \
       (*(uint32_t*)(passkey.appdb[2].peerAddr) == 0xFFFFFFFF))
    {
        return TRUE;
    }

    //step 2:擦除flash中保存的判断信息
    memset(&passkey,0xFF,sizeof(Ble_PassKey));
    Store_Part_Write(eStorePart2KB,0,(uint8*)&passkey,sizeof(Ble_PassKey));

    //step 3: 清除ram中配对信息
    AppDbClear();
    return TRUE;
}
#endif

//**********************************************************************
// 函数功能:Copy Record list from NVM into the active record list, if any
// 输入参数：
// 返回参数：
//**********************************************************************
void Mid_Ble_CopyRecListInNvm(appDbRec_t *pRecord)
{
    uint8_t i; 

    //step 1: read paring info
    Store_Part_Read(eStorePart2KB,0,(uint8*)&passkey,sizeof(Ble_PassKey));

    //step 2: Copy Record list from NVM into the active record list, if any
    for(i=0;i<APP_DB_NUM_RECS;i++)
    {
        if(((*(uint32_t*)(passkey.appdb[i].peerAddr) != 0xFFFFFFFF))&&(*(uint32_t*)(passkey.appdb[i].peerAddr) != 0x00000000))
        {
            //fix :确保开机起来load db后ram中发现dis状态是init
            if(passkey.appdb[i].discStatus != 0x00)
            {
                passkey.appdb[i].discStatus = 0x00;
            }
            //fix :2018.12.25
            //valid record in NVM
            memcpy(pRecord, &passkey.appdb[i], sizeof(appDbRec_t));
            
            //pRecord->inUse = FALSE;
            //pRecord->valid = TRUE;
            pRecord++;
        }
        else
        {
            break;  //break the for loop
        }
    }

    //step 3: get passkey nums
    if((passkey.u32KeyNum == 0xffffffff) || (i == 0))
        passkey.u32KeyNum = 0;

    Db_Debug((0,"passkey.u32KeyNum: %d\n",passkey.u32KeyNum));
}

//**********************************************************************
// 函数功能: 更新record list
// 输入参数：
// 返回参数：
//**********************************************************************
int32_t Mid_Ble_SaveNewRecInNvm(appDbHdl_t hdl)
{
    uint8_t u8ident = 0; //记录record信息是否已存在
    uint8_t i;  

    //step 1: 判断新的信息在flash中是否存在
    for(i = 0; i < APP_DB_NUM_RECS; i++)
    {
        if((*(uint32_t*)(passkey.appdb[i].peerAddr) != 0xFFFFFFFF))
        {
            if(BdaCmp(((appDbRec_t*)hdl)->peerAddr, passkey.appdb[i].peerAddr))
            {
                Db_Debug((0,"NVM save: record is identical, update the record.\n"));
                u8ident = 1;
                break;
            }
            //Db_Debug((0,"NVM save: target flash not empty, check next record.\n"));
        }
        else
        {
            Db_Debug((0,"NVM save: target flash is empty\n"));
            break;
        }
    }

    //step 2: 用新的配对信息更新flash中数据
    //case 1: 如果此连接的设备已存在，则更新数据
    //case 2: 与此设备配对的个数小于3，则直接更新数据
    //case 3: 与此设备配对的个数小于3，则覆盖最先配对的那个
    if(u8ident == 0)
    {
        //如果record信息已存在，只需update数据;否则记录u32KeyNum和record都要update
        passkey.u32KeyNum++; 
    }
    if(i >= APP_DB_NUM_RECS)
    {
        i = (passkey.u32KeyNum - 1) % 3;
    }
    Db_Debug((0,"update %d id target flash info\n",i));
    memcpy((uint8_t *)&passkey.appdb[i], (uint8_t *)hdl, sizeof(appDbRec_t));
    //fix :解决ios手机在连接状态下忽略设备后，手表重启(如ota，wdt)，手机app断开，后重连，无消息提醒
    //discStatus发现ancs服务状态，不能保存当前的值(测试时打印的值是3)，否则会打乱发现服务流程
    passkey.appdb[i].discStatus = 0x00;
    //fix :2018.12.25

    //step 3:更新的数据写到flash中
    Store_Part_Write(eStorePart2KB,0,(uint8*)&passkey,sizeof(Ble_PassKey));
    return 0;
}

//**********************************************************************
// 函数功能: 初始化BLE DB相关函数回调
// 输入参数：
// 返回参数：
//**********************************************************************
void MId_Ble_DbFunInit(void)
{
    ble_db_info_f fun;
    fun.ReadRecInfo = Mid_Ble_CopyRecListInNvm;
    fun.StoreRecInfo = Mid_Ble_SaveNewRecInNvm;
    AppDbSetFun(&fun);
}

