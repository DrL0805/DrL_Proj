/**********************************************************************
**
**模块说明: BLE 协议栈提供给APP的服务接口定义
**软件版本，修改日志(时间，内容),修改人:
**   V1.0   2018.5.1  初版  ZSL  
**  fix 1:  2018.5.27 手动关闭后，会自动开广播，并自动连上的问题  
**  fix 2:  2018.5.31 开机后进仓储，蓝牙开广播，后power off引起的问题
**  fix 3:  2018.6.5  修改广播参数定义方式
**  fix 4:  2018.6.12 修改在OTA中频繁消息提醒，导致升级失败
**  fix 5:  2018.6.26 电量低于10%，自动进入走针模式，除指针走时外所有功能关闭，实际手表的蓝牙未关闭
**  add:    2018.9.27 增加新协议消息详情处理
**
**********************************************************************/
#include "platform_common.h"
#include "platform_debugcof.h"
#include "platform_feature.h"
#include "sm_sys.h"

#include "wsf_types.h"
#include "bstream.h"
#include "wsf_msg.h"
#include "wsf_trace.h"
#include "hci_api.h"
#include "dm_api.h"
#include "att_api.h"
#include "smp_api.h"
#include "app_api.h"
#include "app_db.h"
#include "app_main.h"
#include "svc_ch.h"
#include "svc_core.h"
#include "svc_dis.h"

#include "svc_lowsapp.h"
#include "gatt_api.h"
// ancs
#include "ancc_api.h"
#include "ancs_api.h"
#include "app_m_ble_profile.h"
#include "amotas_api.h"

#ifdef AM_PART_APOLLO3
#include "hci_drv_apollo3.h"
#include "hci_drv_apollo.h"
#else
#include "hci_em9304.h"
#include "drv_em9304.h"
#endif

#include "BLE_Stack.h"
#include "radio_task.h"
#include "BLE_Kernal.h"


#if(BLE_STACK_DEBUG_ENABLE ==1)
#define Ble_Debug(x) SEGGER_RTT_printf x
#else
#define Ble_Debug(x)
#endif

#define BLE_STACK_BOOT   0
#define BLE_STACK_ON     1

static uint8_t u8BtStatus = BT_ADV_OFF;      //记录蓝牙连接状态,开机在仓储状态下为非广播
static uint8 u8StackStatus = BLE_STACK_BOOT; //蓝牙开机时视为在boot状态，在power on动作之后才是ON

ble_echo pBleStatus_Echo = NULL;

/**************************************************************************************************
  Configurable Parameters
**************************************************************************************************/

/*! configurable parameters for advertising */
static appAdvCfg_t m_ble_profileAdvCfg =
{
    {    0,     0,     0},                  /*! Advertising durations in ms */   //默认60000
    {  800,     0,     0}                   /*! Advertising intervals in 0.625 ms units */
};

/*! configurable parameters for security */
static const appSecCfg_t m_ble_profileSecCfg =
{
#if(BLE_PASSKEY_PAIRNG_ENABLE == 1)
    DM_AUTH_MITM_FLAG |                     /*! Authentication and bonding flags */
#endif
    DM_AUTH_BOND_FLAG,                      /*! Authentication and bonding flags */
    0,                                      /*! Initiator key distribution flags */
    DM_KEY_DIST_LTK,                        /*! Responder key distribution flags */
    FALSE,                                  /*! TRUE if Out-of-band pairing data is present */
    FALSE                                   /*! TRUE to initiate security upon connection */
};

/*! configurable parameters for ANCS connection parameter update */
static appUpdateCfg_t m_ble_profileUpdateCfg =
{
    3000,                                   /*! Connection idle period in ms before attempting
                                              connection parameter update; set to zero to disable */
    20,                                     /*! *1.25ms = 300ms */
    50,                                     /*! *1.25ms = 400ms*/
    3,                                      /*! Connection latency */
    600,                                    /*! Supervision timeout in 10ms units */
    5                                       /*! Number of update attempts before giving up */
};

/*! SMP security parameter configuration */
/* Configuration structure */
static const smpCfg_t m_ble_profileSmpCfg =
{
    3000,                                   /*! 'Repeated attempts' timeout in msec */
#if(BLE_PASSKEY_PAIRNG_ENABLE == 1)
    SMP_IO_DISP_ONLY,
#else
    SMP_IO_NO_IN_NO_OUT,                    /*! I/O Capability */
#endif
    7,                                      /*! Minimum encryption key length */
    16,                                     /*! Maximum encryption key length */
    3,                                      /*! Attempts to trigger 'repeated attempts' timeout */
    0                                       /*! Device authentication requirements */
};

//**********************************************************************
// 函数功能: 打印收发数据
// 输入参数：
// 返回参数：
//**********************************************************************
static void ble_printdata(uint8_t *buf)
{
#if(BLE_STACK_DEBUG_ENABLE ==1)
    uint8_t	i;

    for(i = 0; i < buf[MSG_LEN] + 6; i++)
    {
        Ble_Debug((0,"0x%x,",buf[i]));
    }
    Ble_Debug((0,"\n"));
#endif
}

//**********************************************************************
// 函数功能: 判断蓝牙是否在关闭状态
// 输入参数:
// 返回参数：1: 关闭广播或掉电
//**********************************************************************
static uint8 Ble_IsOff(void)
{
    if((u8BtStatus == BT_ADV_OFF) || (u8BtStatus == BT_POWEROFF))
    {
        return 1;
    }
    return 0;
}

static void Ble_PowerOnOff(uint8_t u8status)
{
    //避免重复操作
    if(((u8BtStatus == BT_ADV_ON) && (u8status == BT_POWERON)) || \
       ((u8BtStatus == BT_POWEROFF) && (u8status == BT_POWEROFF)))
        return;

    if(u8status == BT_POWERON)     //开蓝牙
    {
        Ble_Debug((0,"BT_POWERON \n"));
        SMDrv_SYS_DelayMs(100);
        HciDrvRadioBoot(0);
        #ifndef AM_PART_APOLLO3
        Drv_EM9304_EnableInterrupt();
        #endif
        DmDevReset();
        //fix 2:开机后进仓储，蓝牙开广播，后power off引起的问题
        u8StackStatus = BLE_STACK_ON;
        //fix 2018.5.31

        //fix 6: 电量低于10%，自动进入走针模式，除指针走时外所有功能关闭，实际手表的蓝牙未关闭
        //在power on之后蓝牙处于广播状态
        u8BtStatus = BT_ADV_ON;
        //fix :2018.6.26
    }
    else                           //关蓝牙
    {
        Ble_Debug((0,"BT_POWEROFF \n"));
        SMDrv_SYS_DelayMs(100);
        HciDrvRadioShutdown();
        u8BtStatus = BT_POWEROFF;
    }
}

static void Ble_SetStatus(uint8_t u8status)
{
    if(u8status == BT_ADV_ON)     //开蓝牙
    {
        Ble_Debug((0,"BT_ADV_ON \n"));
        BLE_Kernal_AdvSetup();
    }
    else                           //关蓝牙
    {
        Ble_Debug((0,"BT_ADV_OFF \n"));
        dmConnId_t  connId;
        if ((connId = AppConnIsOpen()) != DM_CONN_ID_NONE) /*connected */
        {
            AppConnClose(connId);
        }

        AppAdvStop();
    }
    u8BtStatus = u8status;
}

//**********************************************************************
// 函数功能: 设置蓝牙连接间隔
// 输入参数：buf:协议数据
// 返回参数：
//**********************************************************************
static void BLE_SetConnInterval(uint8_t u8Interval)
{
    hciConnSpec_t ConnSpec;
    dmConnId_t  connId;

    /* do update */    
    ConnSpec.minCeLen = 0;
    ConnSpec.maxCeLen = 0xffff;
    ConnSpec.connLatency = m_ble_profileUpdateCfg.connLatency;
    ConnSpec.supTimeout = m_ble_profileUpdateCfg.supTimeout;

    if ((u8Interval == 0) || (u8Interval == 2))
    {
        m_ble_profileUpdateCfg.connIntervalMin = 10;  /*! *1.25ms = 12.5 ms */
        m_ble_profileUpdateCfg.connIntervalMax = 40;  /*! *1.25ms = 50ms*/
    } 
    else
    {
        m_ble_profileUpdateCfg.connIntervalMin = 80;   /*! *1.25ms = 300ms*/
        m_ble_profileUpdateCfg.connIntervalMax = 160;  /*! *1.25ms = 400ms*/
    }
    ConnSpec.connIntervalMin = m_ble_profileUpdateCfg.connIntervalMin;   
    ConnSpec.connIntervalMax = m_ble_profileUpdateCfg.connIntervalMax;

    /*更新pAppUpdateCfg结构体指针参数*/
    pAppUpdateCfg = (appUpdateCfg_t *) &m_ble_profileUpdateCfg;
    if ((connId = AppConnIsOpen()) != DM_CONN_ID_NONE) /*connected */
    {
        DmConnUpdate(connId, &ConnSpec);
    }
}

//**********************************************************************
// 函数功能: 来电通知反馈
// 输入参数：buf:协议数据
// 返回参数：
//**********************************************************************
static void BLE_InCallResp(uint8_t *buf)
{
    if(buf[INTER_TYPE] == CALL)  // 拒接/接听来电
    {
        Ble_Ancs_DoCall(buf[PARAM_IDX]);
    }
}

//**********************************************************************
// 函数功能: 数据传输
// 输入参数：buf:协议数据
// 返回参数：
//**********************************************************************
static void BLE_PacktTransport(uint8_t *buf)
{
    uint8_t trans_data_len = buf[MSG_LEN] - 3;

    switch (buf[INTER_TYPE])
    {
    case SET: //01 f0 01
        if (trans_data_len <= 20)
        {
            lowsapp_send_data(&buf[PARAM_IDX],trans_data_len,SEND_CHANNEL_DATA);
        }
        break;
    default:
        break;
    }
}

//**********************************************************************
// 函数功能: 解析MCU发给BLE的协议数据
// 输入参数：buf:协议数据
// 返回参数：
//**********************************************************************
static void BLE_AnalysisData(uint8 *buf)
{
    if(buf[INTER_IDX] == PROT_INTERACT)   // 0x03: 交互控制
    {
        if(buf[INTER_IDX + 1] == PROT_INCALL_RESP)  // /* 03 03 */  
        {
            BLE_InCallResp(buf);
        }
    }
    else if((buf[INTER_IDX] == PORT_PACK_TRANS) && (buf[INTER_IDX + 1] == PORT_PACK_TRANS_CH1)) /* f0 01   数据传输，数据通道*/
    {
        BLE_PacktTransport(buf);
    }
    else
        ;
}

void Ble_Handler_Init(wsfHandlerId_t handlerId)
{
    pAppAdvCfg = (appAdvCfg_t *) &m_ble_profileAdvCfg;
    pAppSecCfg = (appSecCfg_t *) &m_ble_profileSecCfg;
    pAppUpdateCfg = (appUpdateCfg_t *) &m_ble_profileUpdateCfg;
    pSmpCfg = (smpCfg_t *) &m_ble_profileSmpCfg;

#if(ANCS_DETIL_TYPE != ANCS_NONE)   //支持ANCS
    Ble_Ancs_HandlerInit(handlerId);
    Ble_Ancs_Start();
#endif
}

//**********************************************************************
// 函数功能: 协议栈事件处理，该接口注册到协议栈内
// 输入参数：event:事件，pMsg:消息
// 返回参数：
//**********************************************************************
void BLE_App_Handler(wsfEventMask_t event, wsfMsgHdr_t *pMsg)
{
    uint8 u8reason;

    if (pMsg == NULL)
        return ;

#if(ANCS_DETIL_TYPE != ANCS_NONE)    //支持ANCS
    //ANCS消息处理,在OTA模式下不解析ANCS
    if(BLE_Stack_GetMode() != BLE_MODE_OTA)
    {
        Ble_Ancs_HandleProcMsg((m_ble_profile_msg_t *)pMsg);
    }
#endif

    //Err_Info((0,"event=%d-0x%x\n",event,event));
    //step 2: 处理客制化事件
    switch(pMsg->event)
    {
    case DM_RESET_CMPL_IND:
        //fix 2:开机后进仓储，蓝牙开广播，后power off引起的问题
        //在开机过程先不做广播，等按键做power on后在开启广播
        if(u8StackStatus != BLE_STACK_BOOT)
        {
            //复位事件:开启广播
            BLE_Kernal_AdvSetup();
        }
        //fix 2018.5.31
        break;
    case DM_CONN_CLOSE_IND:
        //step a: get BLE conn close reason value
        u8reason = ((hciDisconnectCmplEvt_t*)pMsg)->reason;
        Err_Info((0,"Warning: Connection Closed due to: 0x%0x,u8BtStatus=%d\n",u8reason,u8BtStatus));

        //step b:check need resart adv or not,and echo status to mcu
        //fix 1:手动关闭后，会自动开广播，并自动连上的问题
        //在conn close事件发生，并且广播关闭的情况下，就不做重启广播的动作
        if(Ble_IsOff() == 0)
        {
            //restart advertising
            BLE_Kernal_AdvSetup();

            //在没有MCU设置关蓝牙的状态下，蓝牙断开后处于广播状态
            //并将蓝牙断开事件，主动告知MCU
            //fix 3:在机芯和app未连接的状态下，将一些异常的连接状态值反馈给固件app
            // 导致在屏幕上显示异常的断开。
            //解法:只有在上一个连接状态为已连接的时候，才反馈断开事件信息
            if(u8BtStatus == BT_CONNECTED)
            {
                u8BtStatus = BT_ADV_ON;
                if(pBleStatus_Echo != NULL)
                {
                    (pBleStatus_Echo)(BLE_CONN_STATUS_ECHO,u8BtStatus,u8reason);
                }
            }
            //fix 3: 2018.5.31
        }
        //fix 1: 2018.5.27
        break;
    case DM_CONN_OPEN_IND:    //蓝牙连接上事件:echo to MCU
        u8BtStatus = BT_CONNECTED;
        if(pBleStatus_Echo != NULL)
        {
            (pBleStatus_Echo)(BLE_CONN_STATUS_ECHO,u8BtStatus,0x00);
        }
        break;
    case DM_SEC_PAIR_CMPL_IND:    //Pairing completed successfully
        Ble_Debug((0,">>> Pairing completed successfully <<<"));
#if(BLE_PASSKEY_PAIRNG_ENABLE == 1)
        if(pBleStatus_Echo != NULL)
        {
            (pBleStatus_Echo)(BLE_PAIRING_AUTH_STATUS,0x00,0);
        }
#endif
        Ble_Debug((0,"------MTU SIZE = %d-------\n", AttGetMtu(((m_ble_profile_msg_t *)pMsg)->hdr.param)));
        break;
    case DM_SEC_PAIR_FAIL_IND:
        Ble_Debug((0,">>> Pairing failed <<<"));
#if(BLE_PASSKEY_PAIRNG_ENABLE == 1)
        if(pBleStatus_Echo != NULL)
        {
            (pBleStatus_Echo)(BLE_PAIRING_AUTH_STATUS,0x01,0);
        }
#endif
        break;
    case DM_SEC_ENCRYPT_IND:
        Ble_Debug((0,">>> Connection encrypted <<<"));
        break;
    case DM_SEC_ENCRYPT_FAIL_IND:
        Ble_Debug((0,">>> Encryption failed <<<"));
        break;
    default:
        break;
    }
}

//**********************************************************************
// 函数功能: 处理配对码相关的事件
// 输入参数：
// 返回参数：
//**********************************************************************
void Ble_PassKey(uint8_t event,uint32_t u32opt)
{
    switch(event)
    {
    case PASSKEY_DISPLAY:   //display passkey
        Ble_Debug((0,">>> Passkey: %d <<<", u32opt));
#if(BLE_PASSKEY_PAIRNG_ENABLE == 1)
        if(pBleStatus_Echo != NULL)
        {
            (pBleStatus_Echo)(BLE_PAIRING_PASSKEY_ECHO,u32opt,0);
        }
#endif
        break;
    case PASSKEY_PROMPT:        /*! Prompt user to enter passkey */
    case CONFIRMVALUE_DISPLAY:  //display Confirm Value
        break;
    }
}

//**********************************************************************
// 函数功能: MCU与BLE之间数据交互
// 输入参数：type:交互类型
//    param: 数据参数
//    option:可选参数，如广播名长度
// 返回参数：
//**********************************************************************
ret_type BLE_Stack_Interact(Ble_Interact_Type type,uint8 *param,uint8 option)
{
    if(BLE_Stack_GetMode() == BLE_MODE_NOINIT)
        return Ret_Fail;
    if(type == BLE_STATUS_SET)        //开关蓝牙广播
    {
        //if BLE is in OTA, then stop to set BLE on/off

        Ble_Debug((0,"u8BtStatus =%d,swtich=%d\n",u8BtStatus,param[0]));
        //set BLE on/off
        if(((u8BtStatus == BT_ADV_ON) || (u8BtStatus == BT_CONNECTED)) && (param[0] == BT_ADV_OFF))
        {
            Ble_SetStatus(BT_ADV_OFF);
        }
        else if((u8BtStatus == BT_ADV_OFF) && (param[0] == BT_ADV_ON))
        {
            Ble_SetStatus(BT_ADV_ON);
        }
        else
            ;
    }
    else if(type == BLE_POWERONOFF)
    {
        if((param[0] != BT_POWERON) && (param[0] != BT_POWEROFF))
            return Ret_InvalidParam;
        
        Ble_PowerOnOff(param[0]);
    }
    else if(type == BLE_STATUS_GET)            //获取蓝牙状态
    {
        *param = u8BtStatus;
    }
    else if(type == BLE_AVD_NAME_SET)      //设置广播名
    {
        BLE_Kernal_SetAdvName(param,option);
    }
    else if(type == BLE_LINKINTV_SET)      //设置连接间隔
    {
        BLE_SetConnInterval(param[0]);
    }
    else
        ;
    return Ret_OK;
}

//**********************************************************************
// 函数功能: 设置蓝牙Echo动作callback
// 输入参数：pfun:callback
// 返回参数：ret_type
//**********************************************************************
ret_type BLE_Stack_SetEcho_CallBack(ble_echo pfun)
{
    if(pfun == NULL) 
        return Ret_InvalidParam;

    //step 1: set ble status echo callback
    pBleStatus_Echo = pfun;

    //step 2: set call back for ota
    amotas_set_callback(pfun);

    //step 3: set call back for ancs
    Ble_Ancs_Check_Cb(pfun);
    return Ret_OK;
}

//**********************************************************************
// 函数功能: 应用层发送数据到ble的接口，ble模块根据opid执行相应动作
// 输入参数：buf/len: 发送数据的buffer和长度
// 返回参数：Ret_OK:正常，  
//    Ret_InvalidParam: 参数非法
//**********************************************************************
ret_type BLE_Stack_Send(uint8 *buf,uint8 len)
{
    if(buf == NULL)
    {
        return Ret_InvalidParam;
    }
 
    if((buf[HEARD_IDX] != BLE_HEARD) || (buf[VERSON_IDX] != BLE_VERSON) || ((buf[MSG_LEN] + 6) != len))
    {
        ble_printdata(buf);  //print error data
        return Ret_Fail;  //数据不正确
    }

    if (buf[ROL_IDX] == MCU_TO_BLE)
    {
        BLE_AnalysisData(buf); //解析MCU发给BLE的协议数据
    }
    else if (buf[ROL_IDX] == MCU_TO_APP)//直接传输，命令通道
    {
        uint8_t cmd_len = buf[MSG_LEN] + 6;

        if(cmd_len != len)
        {
            len = (cmd_len > 20) ? 20 : cmd_len;
        }

        lowsapp_send_data(buf,len,SEND_CHANNEL_CMD);
    }
    else
    {
         ;
    }
    return Ret_OK;
}

//**********************************************************************
// 函数功能: 检查ble发送是否空闲，空闲返回true
// 输入参数：无
// 返回参数：1:空闲，可发送；  0: 发送忙
//**********************************************************************
uint8 BLE_Stack_CheckSendStatus(void)
{
	return lowsapp_send_idle_check();
}

static void Ble_Init_Func(void)
{
    Ble_Kernal_f blefun;

    blefun.Ble_HandlerInit = Ble_Handler_Init;
    blefun.Ble_Handler = BLE_App_Handler;

    BLE_Kernal_SetFunc(&blefun);
}

//**********************************************************************
// 函数功能: 初始化并创建BLE协议栈消息事件处理任务
// 输入参数：无
// 返回参数：无
//**********************************************************************
void BLE_Stack_Init(void)
{
    //ble is in normal mode,after board setup
    BLE_Stack_SetMode(BLE_MODE_NORMAL);

    //set ble kernal function callback first
    Ble_Init_Func();
    //设置UI Action回调
    AppSetPasskeyDispCb(Ble_PassKey);

    // Run setup functions.
    RadioTaskSetup();

    // Create the functional tasks
    RadioCreateTask();
}

