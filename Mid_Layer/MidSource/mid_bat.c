/**********************************************************************
**
**模块说明: mid层Bat接口
**软件版本，修改日志(时间，内容),修改人:
**   V1.0   2018.4.25  修改流程  ZSL 
**   V1.1   2018.9.1   增加充电管理
**
**********************************************************************/
#include "drv_bat.h"
#include "drv_charger.h"
#include "mid_bat.h"
#include "mid_scheduler.h"

#if(BAT_DEBUG ==1)
#define Bat_Debug(x) SEGGER_RTT_printf x
#else
#define Bat_Debug(x)
#endif

//#define APP_BAT_FULL   4300
//#define APP_BAT_LOW    3600

//定义:充电满时最低电量值,防止无法充电到100，不产生充满事件
#define BAT_FULL_SOC    95

static uint8  batChangeState; 
static uint8  batSoc        = 100;              //电池电量：%

/*******************function define*******************/
static midbat_cb pBatMsg_Cb = NULL;

//fix : 充电满，不显示100%,有些手表一直充不到100%
#if(BAT_CHARGE_PATH_MANAGE == 0)
static uint8 u8MaxSocValue = 100;      //标识充满电后，拔掉充电线时电量值
#endif
static uint8 u8DispSoc = 100;          //记录显示电量
static uint8 u8IsChargeFull = FALSE;   //标识是否充电满


void Mid_Bat_Cb(uint8 bat_msg)
{
	Mid_Schd_TaskMsg_T Msg;
	
	Msg.Id = eSchdTaskMsgBat;
	Msg.Param.Bat.Id = eBatEventStatusChange;
	Msg.Param.Bat.BatStatus = (BatStatusType_e)(bat_msg);
	Mid_Schd_TaskEventSet(&Msg);	
}
//**********************************************************************
// 函数功能:  回调函数，当充电状态检测完成，对数据进行处理。
//      这里包括两个操作，一、保存电池充电状态，二、提供注册函数接口，给上层进行处理
// 输入参数： state：电池充电状态
// 返回参数： 无
//**********************************************************************
void Mid_Bat_ChargeState_IOIsr(bat_charge_envet evnet)
{
    //fix: 充满事件是u8IsChargeFull设为TRUE，拔出充电线时设为FALSE
    // incharge事件不设置，原因:在不带路径管理的情况下，复充点也会有此事件
    // 但为了充满后显示一直为100，所以incharge事件时不改变u8IsChargeFull
    if(evnet == BAT_FULL_CHARGE)
    {
        if(batSoc > BAT_FULL_SOC)
        {
            u8IsChargeFull = TRUE;
            batChangeState = MID_BAT_FULL_CHARGE;
        }
        else
        {
            return ; //误判充满
        }
    }
    else if(evnet == BAT_OFF_CHARGE)
    {
#if(BAT_CHARGE_PATH_MANAGE == 0)
        //fix : 充电满，不显示100%,有些手表一直充不到100%
        if(u8IsChargeFull == TRUE)
        {
            //拔掉充电线后记录当前值为u8MaxSocValue,考虑在值变化点拔线，在拔线后电量显示非100的情况
            //因此记录的最大值比当前读取的值小1，以避免此情况
            u8MaxSocValue = batSoc - 1;
            Bat_Debug((0,"Off Charge u8MaxSocValue=%d\n",u8MaxSocValue));
        }
        //fix : 2018.7.13
#endif
        u8IsChargeFull = FALSE;
        batChangeState = MID_BAT_OFF_CHARGE;
    }
    else if(evnet == BAT_IN_CHARGING)
        batChangeState = MID_BAT_IN_CHARGING;
    else
        ;
	
    if(pBatMsg_Cb != NULL)
    {
        (pBatMsg_Cb)(batChangeState);
    }
}

//**********************************************************************
// 函数功能:  电池电量测量初始化
//     电池电量测量初始化，完成基本的初始化，包括初始化ADC模块，
///    以及注册回调函数1，把ADC采集到的数据读取出来，进行处理.
//          注册回调函数2，把电池的充电状态上传
//     此函数执行完还未开始采集数据。因为要等电量稳定时，再开
//     启电池电量的数据采集
// 输入参数： 无
// 返回参数： 无
// 调用：初始化时调用一次
//**********************************************************************
void Mid_Bat_Init(void)
{
    //step 1: open Bat
	Drv_Bat_Open(); //初始化电量计
//	Drv_Bat_GoSleep(); //暂定电量计一直开启，不暂停有约10uA功耗
    Drv_Bat_DisableIO();

    //step 2: open charger
    Drv_Charge_Open(Mid_Bat_ChargeState_IOIsr);  //初始化充电器
	pBatMsg_Cb	= Mid_Bat_Cb;
}

//**********************************************************************
// 函数功能:  获取电池电量(百分比)，及对应的等级
// 输入参数： *u8Soc: 用于获取电量
// 返回参数： 电池类型
//**********************************************************************
uint8 Mid_Bat_SocRead(uint8 *pu8Soc)
{
    uint8 u8Soc = batSoc;
    uint8 u8type = CHARGING_CELL;

    if(pu8Soc == NULL)
        return u8type;

    //在充电满的情况下，电量值保持100 
    if((u8IsChargeFull == TRUE) && (u8Soc < 100))
    {
        u8Soc = 100;
    }

    //fix:防止在使用过程中出现电量显示变大的情况；在没电后充电，显示为0
    if((batChangeState == MID_BAT_OFF_CHARGE) && (u8Soc != 0))
    {
        u8Soc = (batSoc > u8DispSoc) ? u8DispSoc : batSoc;
    }
    //fix

    *pu8Soc = u8Soc;
    u8DispSoc = u8Soc;
    //Bat_Debug((0,"SocRead pu8Soc=%d,u8DispSoc=%d,batSoc=%d\n",*pu8Soc,u8DispSoc,batSoc));
    return u8type;
}

//**********************************************************************
// 函数功能:  启动一次电量检测
// 输入参数： 无 
// 返回参数： 无
// 调用：每分钟调用检测一次电量值
//**********************************************************************
void Mid_Bat_BatCheck(void)
{
    //fix :解决无电的时候开始充电，电量显示100
    static uint8 u8CurSoc = 0xFF;  //初始化为无效值
    //fix :2018.9.20
    uint8 u8BatSoc;
#if(BAT_DEBUG ==1)
    uint16 batVoltage = 4300;    //电压
#endif

    Drv_Bat_EnableIO();
    //step 1: Get Soc and Vol
    Drv_Bat_ReadLevel(&u8BatSoc);
#if( BAT_DEBUG ==1 )
    Drv_Bat_ReadVoltage(&batVoltage);
    Bat_Debug((0,"u8Soc=%d,batVoltage=%d mV\n",u8BatSoc,batVoltage));
#endif

    if(u8CurSoc != u8BatSoc)
    {
        batSoc = u8BatSoc;        
        u8CurSoc = u8BatSoc;
#if(BAT_CHARGE_PATH_MANAGE == 0)
        //fix: 有充满事件发生，但电量小于100时，显示电量值为100
        // 以防止有些电池无法充电到100显示的问题
        if(u8MaxSocValue < 100)
        {
            // ftemp = (100.0 * socTemp) / u8MaxSocValue; 浮点算法
            batSoc = (uint8)(((10000 / u8MaxSocValue) * u8BatSoc) / 100);
            if(batSoc > 100)
                batSoc = 100;
        }
#endif
        //Bat_Debug((0,"batSoc=%d,u8SocTemp=%d mV\n",batSoc,u8SocTemp));
    }

    //step 2: 不带路径管理的情况下:充电过程中调整u8MaxSocValue值
#if(BAT_CHARGE_PATH_MANAGE == 0)
    //fix :u8MaxSocValue小于100时，在充电过程中逐步调整此值到100
    if((batChangeState == MID_BAT_IN_CHARGING) && (u8MaxSocValue < 100))
    {
        //充电过程，越接近充满，充1%用时会越长
        if(((u8DispSoc >= 90) && (u8BatSoc >= u8DispSoc)) || \
           ((u8DispSoc >= 70) && (u8BatSoc >= (u8DispSoc + 2))) || \
           (u8BatSoc >= (u8DispSoc + 4)))
        {
            Bat_Debug((0,"Update u8MaxSocValue %d to 100\n",u8MaxSocValue));
            u8MaxSocValue = 100;
        }
    }
    //fix :2018.7.13
#endif

    //step 3: 在使用过程中检测低电
    if((batChangeState == MID_BAT_OFF_CHARGE) && (batSoc < 10))
    {
        //低电提醒，只作一次提醒
        if((pBatMsg_Cb != NULL) && (batChangeState != MID_BAT_LOW_LEVEL))
        {
             batChangeState = MID_BAT_LOW_LEVEL;
            (pBatMsg_Cb)(MID_BAT_LOW_LEVEL);
        }
    }

    Drv_Bat_DisableIO();
}

//**********************************************************************
// 函数功能:  电量计唤醒
// 输入参数： 无 
// 返回参数： 无
//**********************************************************************
void Mid_Bat_WakeUp(void)
{
    Drv_Bat_EnableIO();
    Drv_Bat_WakeUp();
    Drv_Bat_DisableIO();
}

//**********************************************************************
// 函数功能:  读取电池的充电状态  
// 输入参数： dataTemp：传入变量，保存电池的充电状态
// 返回参数： 无
//**********************************************************************
void Mid_Bat_ChargeStateRead(uint8 *dataTemp)
{
	*dataTemp = batChangeState;
}

//**********************************************************************
// 函数功能:  启动一次充电检测
// 输入参数： 无 
// 返回参数： 无
// 调用：每秒检测一次
//**********************************************************************
void Mid_Bat_ChargCheck(void)
{
    //step 1: 对电池的充电状态进行一次检测
    Drv_Charge_CheckStatus();
    
    //step 2:检测电池低电报警，放在此处原因:充电检测都定时的，电量检测时长时短
    if(batSoc < 5)
    {
        if(Drv_Bat_LowAlert() == TRUE)
        {
            batChangeState = MID_BAT_LOW_ALERT;
            if(pBatMsg_Cb != NULL)
            {
                (pBatMsg_Cb)(batChangeState);
            }
        }
    }
}

//**********************************************************************
// 函数功能:  电池检测 
// 输入参数： 无
// 返回参数： 电池检测结果
//**********************************************************************
uint16 Mid_Bat_SelfTest(void)
{
    uint16 result = 0;

    Drv_Bat_EnableIO();
    // Drv_Bat_WakeUp();
	
    if(Drv_Bat_SelfTest() != Ret_OK)
    {
        result |= 0x00ff;
    }
    
     // Drv_Bat_GoSleep();
    Drv_Bat_DisableIO();

    return result;
}

void Mid_Bat_Test(void)
{
	Mid_Schd_TaskMsg_T Msg;
	
	Msg.Id = eSchdTaskMsgBat;
	Msg.Param.Bat.Id = eBatEventBatCheck;
	Mid_Schd_TaskEventSet(&Msg);
}




