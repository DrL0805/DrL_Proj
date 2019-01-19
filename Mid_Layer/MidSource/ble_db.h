/*************************************************************************************************/
/*!
 *  \file   app_db.h
 *
 *  \brief  Application framework device database.
 *
 *          $Date: 2016-12-28 16:12:14 -0600 (Wed, 28 Dec 2016) $
 *          $Revision: 10805 $
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
#ifndef BLE_DB_H
#define BLE_DB_H

//**********************************************************************
// 函数功能: 清除配对信息，Ram和flash中都要清除
// 输入参数：
// 返回参数：
//**********************************************************************
extern uint8_t Mid_Ble_DbRecClear(void);

//**********************************************************************
// 函数功能: 初始化BLE DB相关函数回调
// 输入参数：
// 返回参数：
//**********************************************************************
extern void MId_Ble_DbFunInit(void);

#endif /* APP_DB_H */
