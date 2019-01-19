/**********************************************************************
**
**模块说明: CW2015电量检测驱动接口
**软件版本，修改日志(时间，内容),修改人:
**   V1.0   2018.4.23  修改流程  ZSL  
**

**********************************************************************/
#define BAT_MODULE
#include "io_config.h"
#include "platform_debugcof.h"

#include "sm_i2c.h"
#include "sm_sys.h"
#include "sm_gpio.h"

#include "bsp_common.h"
#include "drv_bat.h"

#if(BAT_DEBUG ==1)
#define Bat_Debug(x) RTT_DEBUG_printf x
#else
#define Bat_Debug(x)
#endif

/*******************macro define*******************/
//CELLWISE Fuel Gauge IC macros and func

//Reg 0x06 bit8标示报警信号
#define    CELLWISE_ALRT_FLAG          0x80

// addr define
#define		CELLWISE_ADDR				0xC4

// const define
#define     CELLWISE_VERSION            0x6F
#define     MODE_SLEEP_MASK             (0x3<<6)
#define     MODE_SLEEP                  (0x3<<6)
#define     MODE_NORMAL                 (0x0<<6)
#define     MODE_QUICK_START            (0x3<<4)
#define     MODE_RESTART                (0xf<<0)        
#define     CONFIG_UPDATE_FLG           (0x1<<1)        
#define     ATHD                        (0x0<<3)        //ATHD = 0% 低电量中断阈值

// register macro
#define     CELLWISE_VERSION_REG        0x00 //IC版本号 默认为0x6F
#define     CELLWISE_VCELL_REG          0x02 //电池端的电压（两字节）
#define     CELLWISE_SOC_REG            0x04 //电量百分比%
#define     CELLWISE_SOC_DECIMAL_REG    0x05 //电量百分比 1/256%
#define     CELLWISE_RRT_ALRT_REG       0x06 //剩余时间、警报
#define     CELLWISE_CONFIG_REG         0x08 //低电量中断阈值设置、更新标识位
#define     CELLWISE_MODE_REG           0x0A // sleep1|0|QSTRT1|0|POR3|2|1|0
#define     CELLWISE_BATINFO_CONFIG     0x10

#define BATINFO_SIZE    64

/*******************const define*******************/
#if 1
//fix :电池原厂修改保护板后，新的profile模型
static uint8 cw_bat_modeling_info[BATINFO_SIZE] ={
0x16,0xD9,0x60,0x61,0x61,0x5E,0x5E,0x4C,
0x77,0x58,0x4B,0x52,0x55,0x48,0x40,0x38,
0x32,0x29,0x26,0x22,0x2A,0x32,0x41,0x48,
0x25,0x4B,0x0C,0xCD,0x3C,0x5C,0x95,0x9A,
0xB2,0xB1,0xA9,0xA7,0x40,0x1A,0x57,0x25,
0x0E,0x86,0x52,0x87,0x8F,0x91,0x94,0x52,
0x82,0x8C,0x92,0x96,0x5C,0xA2,0x8C,0xCB,
0x2F,0x7D,0x64,0xA5,0xB5,0x0E,0x48,0x19,
};
//fix: 2018.8.10
#else
//fix :有些机芯电量无法充电到100，原厂提供
static uint8 cw_bat_modeling_info[BATINFO_SIZE] ={
0x16,0xDC,0x62,0x5D,0x5D,0x5C,0x5A,0x54,
0x64,0x73,0x4B,0x4C,0x49,0x44,0x3E,0x3A,
0x34,0x2E,0x2F,0x32,0x3B,0x45,0x4D,0x2A,
0x0E,0x68,0x0C,0xCD,0x06,0x0D,0x5E,0x69,
0x81,0x8D,0x7D,0x78,0x47,0x1F,0x77,0x00,
0x18,0x5B,0x52,0x87,0x8F,0x91,0x94,0x52,
0x82,0x8C,0x92,0x96,0x89,0x9F,0xC2,0xCB,
0x2F,0x7D,0x64,0xA5,0xB5,0x0E,0x48,0x12,
};
//fix: 2018.7.13
#endif


static uint8 cellwiseinitflag = 0;

//**********************************************************************
// 函数功能:    寄存器写
// 输入参数：    
// 返回参数：    无
static void Bat_RegWrite(uint8 dev_address, uint8 reg_address, uint8 *regval, uint16_t length)
{
    SMDrv_SWI2C_Write(BAT_IIC_MODULE,dev_address, reg_address, regval, length);
}

//**********************************************************************
// 函数功能:    寄存器读
// 输入参数：    无
// 返回参数：    无
static void Bat_RegRead(uint8 dev_address, uint8 reg_address, uint8 *regval, uint16_t length)
{
    SMDrv_SWI2C_Read(BAT_IIC_MODULE,dev_address, reg_address, regval, length);
}

//**********************************************************************
// 函数功能: 检测低电报警信号，如果是低电则清除低电报警标志
// 输入参数：
// 返回参数：TRUE:系统处于电池低电，FALSE:未处于低电状态
// 说    明:当电量小于CW2015设置的阈值时，low报警就会触发，CW2015 IC将
//      ALRT flag置1， 同时拉低ALRT脚同时主控IC，ALRT脚会一直持续低，直到
//      host通过IIC写数据将ALRT flag清0.
//**********************************************************************
uint8 Drv_Bat_LowAlert(void)
{
    uint8 u8AlrtFlag;

    if (SMDrv_GPIO_InBitRead(BAT_ALRT_PIN) == 0)
    {
        SMDrv_SWI2C_Open(BAT_IIC_MODULE,IIC_SPEED_HIGH);
        Bat_RegRead(CELLWISE_ADDR, CELLWISE_RRT_ALRT_REG, &u8AlrtFlag, 1);
        if((u8AlrtFlag & CELLWISE_ALRT_FLAG) == CELLWISE_ALRT_FLAG)
        {
            Bat_Debug((0,"ALRT =0x%x\n",u8AlrtFlag));
            u8AlrtFlag &= ~CELLWISE_ALRT_FLAG; 
            Bat_RegWrite(CELLWISE_ADDR, CELLWISE_RRT_ALRT_REG, &u8AlrtFlag, 1);
        }
        SMDrv_SWI2C_Close(BAT_IIC_MODULE); 
        return TRUE;
    }
    return FALSE;
}

//**********************************************************************
// 函数功能：    在0x10寄存器写入电池建模信息
// 输入参数：    无
// 返回参数：    
// 0x00    :    初始化成功
// 0xff    :    初始化失败
uint8 Drv_Bat_ModelUpdate(void)
{
    uint8 ui8loop;
    uint8 reg_val;
    
    Bat_RegRead(CELLWISE_ADDR, CELLWISE_MODE_REG, &reg_val, 1);
    if((reg_val & MODE_SLEEP_MASK) == MODE_SLEEP)
    {
        Bat_Debug((0,"cw chip is in sleep mode\n"));
    }
    
    /* update new battery info */
    Bat_RegWrite(CELLWISE_ADDR, CELLWISE_BATINFO_CONFIG, cw_bat_modeling_info, BATINFO_SIZE);
    
    /* readback & check */
    for(ui8loop=0; ui8loop<BATINFO_SIZE; ui8loop++)
    {
        Bat_RegRead(CELLWISE_ADDR, CELLWISE_BATINFO_CONFIG+ui8loop, &reg_val, 1);
        if( reg_val != cw_bat_modeling_info[ui8loop] )
        {
            Bat_Debug((0,"cw model check error!!!\n"));
            return 0xFF;
        }            
    }
    
    /* set cw2015/cw2013 to use new battery info */
    Bat_RegRead(CELLWISE_ADDR, CELLWISE_CONFIG_REG, &reg_val, 1);
    reg_val |= CONFIG_UPDATE_FLG;   /* set UPDATE_FLAG */
	reg_val &= 0x07;                /* clear ATHD低电量中断阈值 */
	reg_val |= ATHD;                /* set ATHD */
    Bat_RegWrite(CELLWISE_ADDR, CELLWISE_CONFIG_REG, &reg_val, 1);
    
    /* reset */
    reg_val = MODE_RESTART;
    Bat_RegWrite(CELLWISE_ADDR, CELLWISE_MODE_REG, &reg_val, 1);
    SMDrv_SYS_DelayUs(100);
    reg_val = MODE_NORMAL;
    Bat_RegWrite(CELLWISE_ADDR, CELLWISE_MODE_REG, &reg_val, 1);
    
    return 0x00;    
}

//**********************************************************************
// 函数功能:    电量计初始化
// 输入参数：    无
// 返回参数：    
//**********************************************************************
ret_type Drv_Bat_Open(void)
{
    uint8 ui8loop;
    uint8 i;
    uint8 reg_val = MODE_NORMAL;
    uint8 percentdata[2];

    SMDrv_SWI2C_Open(BAT_IIC_MODULE,IIC_SPEED_HIGH);
    SMDrv_GPIO_Open(BAT_ALRT_PIN,NULL,NULL);

    if(cellwiseinitflag == 0)
    {
        cellwiseinitflag = 1;
        /* wake up cw2015/13 from sleep mode */
        Bat_RegWrite(CELLWISE_ADDR, CELLWISE_MODE_REG, &reg_val, 1);
        /* check ATHD if not right */
        Bat_RegRead(CELLWISE_ADDR, CELLWISE_CONFIG_REG, &reg_val, 1);
        Bat_Debug((0,"read CELLWISE_CONFIG_REG =0x%x\n",reg_val));
        if((reg_val & 0xf8) != ATHD)
        {
            //"the new ATHD need set"
            reg_val &= 0x07;    /* clear ATHD */
            reg_val |= ATHD;    /* set ATHD */
            Bat_Debug((0,"write CELLWISE_CONFIG_REG =0x%x\n",reg_val));
            Bat_RegWrite(CELLWISE_ADDR, CELLWISE_CONFIG_REG, &reg_val, 1);
        }
        /* check config_update_flag if not right */
        Bat_RegRead(CELLWISE_ADDR, CELLWISE_CONFIG_REG, &reg_val, 1);
        if(!(reg_val & CONFIG_UPDATE_FLG))
        {
            Drv_Bat_ModelUpdate();
        }
        else
        {
            for(ui8loop=0; ui8loop<BATINFO_SIZE; ui8loop++)
            {
                Bat_RegRead(CELLWISE_ADDR, CELLWISE_BATINFO_CONFIG+ui8loop, &reg_val, 1);
                if( reg_val != cw_bat_modeling_info[ui8loop] )
                {
                    //Bat_Debug((0,"cw model check error!!!\n"));
                    break;
                }            
            }
            if(ui8loop != BATINFO_SIZE)
            {
                //"update flag for new battery info need set"
                Drv_Bat_ModelUpdate();
            }
        }

        /* check SOC if not eqaul 255 */
        for (i = 0; i < 50; i++) 
        {
            SMDrv_SYS_DelayMs(10);//delay 100ms  
            Bat_RegRead(CELLWISE_ADDR, CELLWISE_SOC_REG, percentdata, 2);
            if (percentdata[0] <= 100)
            {
                break;  
            } 
        }
    }

    return Ret_OK;
}

//**********************************************************************
// 函数功能:   电量计自检
// 输入参数：   无
// 返回参数：    
//**********************************************************************
ret_type Drv_Bat_SelfTest(void)
{
   uint8  data;

    // Selftest
    Bat_RegRead(CELLWISE_ADDR, CELLWISE_VERSION_REG,&data, 1);
    if(data < CELLWISE_VERSION)
    {
        Bat_Debug((0,"CellWise test failed\n"));
        cellwiseinitflag = 0;
        return Ret_Fail;
    }
    return Ret_OK;
}

//**********************************************************************
// 函数功能: 读取电量剩余百分比，数据单位为%
// 输入参数：p_i8percentData:获取电量整数值
// 返回参数：
// 说    明:reg 0x04读取电量整数部分，0x05 reg是小数部分(软件暂不需要)
//**********************************************************************
ret_type Drv_Bat_ReadLevel(uint8 *p_i8percentData)
{
    if(p_i8percentData == NULL)
        return Ret_InvalidParam;

    Bat_RegRead(CELLWISE_ADDR, CELLWISE_SOC_REG, p_i8percentData, 1);
    if(*p_i8percentData > 100)
        *p_i8percentData = 100;
    return Ret_OK;
}

#if(BAT_DEBUG ==1)
//**********************************************************************
// 函数功能: 读取电池电压，数据单位为305uV
// 输入参数：    
// p_i8voltageData ：数据单位为mV
// 返回参数：
//**********************************************************************
ret_type Drv_Bat_ReadVoltage(uint16 *p_ui16voltageData)
{
    uint8 voltagedata[2];
    if(p_ui16voltageData == NULL)
        return Ret_InvalidParam;

    Bat_RegRead(CELLWISE_ADDR, CELLWISE_VCELL_REG, voltagedata, 2);
    *p_ui16voltageData = (uint16)((((uint16)voltagedata[0]<<8) + voltagedata[1])*305/1000);
    return Ret_OK;
}
#endif

//**********************************************************************
// 函数功能:    读取剩余时间，数据单位为：1分钟
// 输入参数：    
// p_i8voltageData ：数据单位为mV
// 返回参数：    
//**********************************************************************
ret_type Drv_Bat_ReadRemainTime(uint16 *p_i16timeData)
{
    uint8 timedata[2];
    if(p_i16timeData == NULL)
        return Ret_InvalidParam;
    
    Bat_RegRead(CELLWISE_ADDR, CELLWISE_RRT_ALRT_REG, timedata, 2);
    timedata[0] &= ~(0x01<<7); 
    *p_i16timeData = ((uint16)timedata[0]<<8) + timedata[1];

    return Ret_OK;
}

//**********************************************************************
// 函数功能:    设置电量计进入睡眠状态
// 输入参数：   无
// 返回参数：    
//**********************************************************************
ret_type Drv_Bat_GoSleep(void)
{
    uint8 ui8Regtemp[1] = {0x00};

    cellwiseinitflag = 0;

    Bat_RegRead(CELLWISE_ADDR, CELLWISE_MODE_REG, ui8Regtemp, 1);
    ui8Regtemp[0] |= 3<<6; 
    Bat_RegWrite(CELLWISE_ADDR, CELLWISE_MODE_REG, ui8Regtemp, 1);
    return Ret_OK;
}

//**********************************************************************
// 函数功能:    电量计唤醒
// 输入参数：   无
// 返回参数：    
//**********************************************************************
ret_type Drv_Bat_WakeUp(void)
{
    uint8 ui8loop;
    uint8 reg_val = MODE_NORMAL;
    
    if(cellwiseinitflag == 0)
    {
        cellwiseinitflag = 1;
        /* wake up cw2015/13 from sleep mode */
        Bat_RegWrite(CELLWISE_ADDR, CELLWISE_MODE_REG, &reg_val, 1);
        /* check ATHD if not right */
        Bat_RegRead(CELLWISE_ADDR, CELLWISE_CONFIG_REG, &reg_val, 1);
        if((reg_val & 0xf8) != ATHD)
        {
            //"the new ATHD need set"
            reg_val &= 0x07;    /* clear ATHD */
            reg_val |= ATHD;    /* set ATHD */
            Bat_RegWrite(CELLWISE_ADDR, CELLWISE_CONFIG_REG, &reg_val, 1);
        }
        /* check config_update_flag if not right */
        Bat_RegRead(CELLWISE_ADDR, CELLWISE_CONFIG_REG, &reg_val, 1);
        if(!(reg_val & CONFIG_UPDATE_FLG))
        {
            Drv_Bat_ModelUpdate();
        }
        else
        {
            for(ui8loop=0; ui8loop<BATINFO_SIZE; ui8loop++)
            {
                Bat_RegRead(CELLWISE_ADDR, CELLWISE_BATINFO_CONFIG+ui8loop, &reg_val, 1);
                if( reg_val != cw_bat_modeling_info[ui8loop] )
                {
                    Bat_Debug((0,"cw model check error!!!\n"));
                    break;
                }
            }
            if(ui8loop != BATINFO_SIZE)
            {
                //"update flag for new battery info need set"
                Drv_Bat_ModelUpdate();
            }
        }
    }

    return Ret_OK;
}

//**********************************************************************
// 函数功能:    使能模块使用的IO功能
// 输入参数：    无
// 返回参数：    
// 0x00    :    设置成功
// 0x01    :    设置失败
//**********************************************************************
ret_type Drv_Bat_EnableIO(void)
{
    return SMDrv_SWI2C_Open(BAT_IIC_MODULE,IIC_SPEED_HIGH);
}

//**********************************************************************
// 函数功能:    关闭模块使用的IO功能，实现低功耗
// 输入参数：    无
// 返回参数：    
// 0x00    :    设置成功
// 0x01    :    设置失败
//**********************************************************************
ret_type Drv_Bat_DisableIO(void)
{
    return SMDrv_SWI2C_Close(BAT_IIC_MODULE); 
}

