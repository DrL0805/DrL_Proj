#ifndef PLATFORM_DEBUG_H
#define PLATFORM_DEBUG_H

/****************************************************************************************
**                        ������Ϣ����˵��
** �������debug��Ϣ���أ� �������еĺ�:
**  PLATFORM_DEBUG_ENABLE: ����Ϊ 1: debug �汾�����Ӵ�ӡ�����ڵ��ԣ�
**                         ����Ϊ 0: relelase�汾���ͷŰ汾�����뽫��ӡȫ�ص� 
**
** ��debug�汾��: ÿһ��ģ��ᶨ��һ�����������Ƿ���Ҫ����ģ���еĴ�ӡ����
** BLE_STACK_DEBUG_ENABLE: ������������Э��ģ���ӡ��Ϣ����Ϊ1:������Ϊ0��ص�
** ����Err_Info:��ӡerror��Ϣ
**
** ��PLATFORM_DEBUG_ENABLE == 0�Ĳ��֣����뽫ȫ������Ϊ0
**   PLATFORM_DEBUG_ENABLE == 1�Ĳ��֣�Ϊdebug���ɸ��������1����0
**
** Ŀ��:�ڳ�������ʱ������λ���⣬����������ͨѶ����
** ��ӡʹ��:RTT
**
****************************************************************************************/
#define PLATFORM_DEBUG_ENABLE   1  

#if(PLATFORM_DEBUG_ENABLE == 1)   //debug version
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

//SMDrv ģ��debug ����
#define SMDRV_FLASH_DEBUG        0
#define SMDRV_ADC_DEBUG          0

//DRV ģ��debug ����
#define BAT_DEBUG                1

//MID��debug ���� 
#define MID_BLE_DEBUG            1    //����
#define MID_MAG_DEBUG            0    //mag
#define MID_PRESS_DEBUG          0    //pressure
#define MID_SPORT_DEBUG          0    //sport


//APP��debug ����
#define APP_PROTOCAL_DEBUG       0    //Э�����

//BLE STACK debug ����
#define BLE_STACK_DEBUG_ENABLE   1  
#define WSF_DEBUG_ENABLE         0  //����Э��ջ trace

#if(WSF_DEBUG_ENABLE == 1)
#define WSF_TRACE_ENABLED        1  //�˴���Ҫ�޸ģ�ֻ���޸�WSF_DEBUG_ENABLE
#define AM_DEBUG_PRINTF
#endif
#define SMOTAS_DEBUG_ENABLE      1 //OTA
#define BLE_PASSKEY_DEBUG        1

//for Error info print
#define Err_Info(x) SEGGER_RTT_printf x


#else           //release version

#define SMDRV_FLASH_DEBUG        0

#define MID_BLE_DEBUG            0
#define MID_BAT_DEBUG            0
#define MID_MAG_DEBUG            0
#define MID_PRESS_DEBUG          0 

#define APP_PROTOCAL_DEBUG       0


#define BLE_STACK_DEBUG_ENABLE   0
#define WSF_DEBUG_ENABLE         0
#define SMOTAS_DEBUG_ENABLE      0
#define BLE_PASSKEY_DEBUG        0

#define Err_Info(x) 
#endif

#define PACK_DATA 				0
#define SCENE_DATA 				0

#endif

