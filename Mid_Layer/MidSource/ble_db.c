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
    uint32_t u32KeyNum;   //��¼�ж��ٸ��豸����豸���
    appDbRec_t appdb[APP_DB_NUM_RECS];
}Ble_PassKey;

static Ble_PassKey passkey;

#if 0
//**********************************************************************
// ��������: ��������Ϣ��Ram��flash�ж�Ҫ���
// ���������
// ���ز�����
//**********************************************************************
uint8_t Mid_Ble_DbRecClear(void)
{
    //step 1:�ж��Ƿ��������Ϣ
    if((*(uint32_t*)(passkey.appdb[0].peerAddr) == 0xFFFFFFFF) && (*(uint32_t*)(passkey.appdb[1].peerAddr) == 0xFFFFFFFF) && \
       (*(uint32_t*)(passkey.appdb[2].peerAddr) == 0xFFFFFFFF))
    {
        return TRUE;
    }

    //step 2:����flash�б�����ж���Ϣ
    memset(&passkey,0xFF,sizeof(Ble_PassKey));
    Store_Part_Write(eStorePart2KB,0,(uint8*)&passkey,sizeof(Ble_PassKey));

    //step 3: ���ram�������Ϣ
    AppDbClear();
    return TRUE;
}
#endif

//**********************************************************************
// ��������:Copy Record list from NVM into the active record list, if any
// ���������
// ���ز�����
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
            //fix :ȷ����������load db��ram�з���dis״̬��init
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
// ��������: ����record list
// ���������
// ���ز�����
//**********************************************************************
int32_t Mid_Ble_SaveNewRecInNvm(appDbHdl_t hdl)
{
    uint8_t u8ident = 0; //��¼record��Ϣ�Ƿ��Ѵ���
    uint8_t i;  

    //step 1: �ж��µ���Ϣ��flash���Ƿ����
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

    //step 2: ���µ������Ϣ����flash������
    //case 1: ��������ӵ��豸�Ѵ��ڣ����������
    //case 2: ����豸��Եĸ���С��3����ֱ�Ӹ�������
    //case 3: ����豸��Եĸ���С��3���򸲸�������Ե��Ǹ�
    if(u8ident == 0)
    {
        //���record��Ϣ�Ѵ��ڣ�ֻ��update����;�����¼u32KeyNum��record��Ҫupdate
        passkey.u32KeyNum++; 
    }
    if(i >= APP_DB_NUM_RECS)
    {
        i = (passkey.u32KeyNum - 1) % 3;
    }
    Db_Debug((0,"update %d id target flash info\n",i));
    memcpy((uint8_t *)&passkey.appdb[i], (uint8_t *)hdl, sizeof(appDbRec_t));
    //fix :���ios�ֻ�������״̬�º����豸���ֱ�����(��ota��wdt)���ֻ�app�Ͽ���������������Ϣ����
    //discStatus����ancs����״̬�����ܱ��浱ǰ��ֵ(����ʱ��ӡ��ֵ��3)���������ҷ��ַ�������
    passkey.appdb[i].discStatus = 0x00;
    //fix :2018.12.25

    //step 3:���µ�����д��flash��
    Store_Part_Write(eStorePart2KB,0,(uint8*)&passkey,sizeof(Ble_PassKey));
    return 0;
}

//**********************************************************************
// ��������: ��ʼ��BLE DB��غ����ص�
// ���������
// ���ز�����
//**********************************************************************
void MId_Ble_DbFunInit(void)
{
    ble_db_info_f fun;
    fun.ReadRecInfo = Mid_Ble_CopyRecListInNvm;
    fun.StoreRecInfo = Mid_Ble_SaveNewRecInNvm;
    AppDbSetFun(&fun);
}

