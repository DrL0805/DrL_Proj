/**********************************************************************
**
**模块说明: 充电驱动接口
**软件版本，修改日志(时间，内容),修改人:
**   V1.0   2018.9.29  兼容CW6304和CE3150B  ZSL  
**
**********************************************************************/
#define BAT_MODULE
#include "io_config.h"
#include "platform_debugcof.h"

#include "sm_i2c.h"
#include "sm_sys.h"
#include "sm_gpio.h"
#include "drv_charger.h"

#if(BAT_DEBUG ==1)
#define Bat_Debug(x) RTT_DEBUG_printf x
#else
#define Bat_Debug(x)
#endif

/*******************macro define*******************/
#if(CHARGER_CHIP == CHARGER_CW6304)
// addr define
#define	CHARGER_ADDR				0x12

//充电配置寄存器 0x01
//Charger termination voltage充电截止电压
#define CHARG_TERM_VOL_4_2V         (0x0<<6)
#define CHARG_TERM_VOL_4_25V        (0x1<<6)
#define CHARG_TERM_VOL_4_3V         (0x2<<6)
#define CHARG_TERM_VOL_4_35V        (0x3<<6)

//Charger termination current充电截止电流
#define CHARG_TERM_CURRENT_10       (0x1<<5) //10% Constant current
#define CHARG_TERM_CURRENT_5        (0x0<<5) //5% Constant current

//Constant current setting恒流充电电流设置
#define CHARG_CONST_CURRENT_100     (0x12<<0)   //100mA恒流充电

//安全寄存器 0x02
//Low battery alarm threshold低电报警阔值(V)
#define CHARG_LOW_ALARM_3_3V         (0x5<<0)
#define CHARG_LOW_ALARM_3_5V         (0x7<<0)

//中断寄存器:0x03,0x04(中断类型:bit位为1:边沿触发，为0电平触发)
#define CHARG_CHG_OUT                (0x1<<7)  //charge out
#define CHARG_TIMER_EXPIRE           (0x1<<6)  //Charging timer expire
#define CHARG_CHG_IN                 (0x1<<5)  //charge in
#define CHARG_BAT_FULL               (0x1<<4)  //Battery full

//register define
#define SYS_CONFIG_REG          0x00 //System配置
#define CHARGE_CONFIG_REG       0x01 //充电配置
#define SAFETY_CONFIG_REG       0x02 //安全
#define INTERRUPT_REG           0x03 //中断
#define INTERRUPT_TYPE_REG      0x04 //中断类型
#endif

ChargeCheckCb Bat_ChgCheckCb = NULL;

#if(CHARGER_CHIP == CHARGER_CW6304)
//**********************************************************************
// 函数功能:    寄存器写
// 输入参数：    
//**********************************************************************
static void Charge_RegWrite(uint8 dev_address, uint8 reg_address, uint8 *regval, uint16_t length)
{
    SMDrv_SWI2C_Write(CHARGE_IIC_MODULE,dev_address, reg_address, regval, length);
}

//**********************************************************************
// 函数功能:    寄存器读
// 输入参数：    无
// 返回参数：    无
//**********************************************************************
static void Charge_RegRead(uint8 dev_address, uint8 reg_address, uint8 *regval, uint16_t length)
{
    SMDrv_SWI2C_Read(CHARGE_IIC_MODULE,dev_address, reg_address, regval, length);
}
#endif

//**********************************************************************
// 函数功能:  充电初始化
// 输入参数： chg_cb:充电相关事件回调函数
// 返回参数：    
//**********************************************************************
ret_type Drv_Charge_Open(ChargeCheckCb chg_cb)
{
#if(CHARGER_CHIP == CHARGER_CW6304)
    uint8 u8RegValue;

    SMDrv_SWI2C_Open(CHARGE_IIC_MODULE,IIC_SPEED_HIGH);
    //step 1: get sys config，if reg value is not right,then update
    Charge_RegRead(CHARGER_ADDR, SYS_CONFIG_REG, &u8RegValue, 1);
    Bat_Debug((0,"sys config(0x00) value = 0x%02x\n",u8RegValue));
    if((u8RegValue & 0xE0) != 0xE0)
    {
        //Enable NTC check,charging and charging timer
        u8RegValue = 0xE0;
        Charge_RegWrite(CHARGER_ADDR, SYS_CONFIG_REG,&u8RegValue,1); 
    }

    //step 2:set charger config(reg:0x01)
    //充电截止电压为4.35V，充电截止电流为10%，以100mA充电
    u8RegValue = (CHARG_TERM_VOL_4_35V | CHARG_TERM_CURRENT_5 | CHARG_CONST_CURRENT_100);
    Charge_RegWrite(CHARGER_ADDR, CHARGE_CONFIG_REG,&u8RegValue,1);
    Charge_RegRead(CHARGER_ADDR, CHARGE_CONFIG_REG, &u8RegValue, 1);
    Bat_Debug((0,"charge config(0x01) value = 0x%02x\n",u8RegValue));

    //step 3:set low alarm config(reg:0x02)
    u8RegValue = CHARG_LOW_ALARM_3_5V;     //3.5V低电报警
    Charge_RegWrite(CHARGER_ADDR, SAFETY_CONFIG_REG,&u8RegValue,1);

    //step 4:set Interrupt type(reg:0x04) as Edge trigger
    u8RegValue = 0xFF;
    Charge_RegWrite(CHARGER_ADDR, INTERRUPT_TYPE_REG,&u8RegValue,1);

    //step 5:clear Interrupt(reg:0x03)
    u8RegValue = 0x00;
    Charge_RegWrite(CHARGER_ADDR, INTERRUPT_REG,&u8RegValue,1);
    SMDrv_SWI2C_Close(CHARGE_IIC_MODULE); 
#endif

    //电池充电检测IO配置
    SMDrv_GPIO_Open(BAT_CHG_PIN,NULL,NULL);
#if(CHARGER_CHIP == CHARGER_CE3150B)
    SMDrv_GPIO_Open(BAT_PG_PIN,NULL,NULL);
#endif

    if(chg_cb != NULL)
    {
        Bat_ChgCheckCb = chg_cb;
    }
    return Ret_OK;
}

#if(CHARGER_CHIP == CHARGER_CW6304)
//**********************************************************************
// 函数功能: 识别拔插抖动情况下插入/拔除事件
// 输入参数：
// 返回参数：
// 说    明:充电器插入和拔出是接触问题可能会导致bit7和bit5同时出现置高的情况。
//这时需要将BIT7和BIT5的中断触发类型改为电平触发来区分充电器的插入和拔出。
//区分完成后还是要将触发类型改成边沿触发，否则IRQ会一直维持低电平
//**********************************************************************
static uint8 Charge_CheckDetect(void)
{
    uint8 u8RegValue = 0x00, u8iqr = CHARG_CHG_OUT;

    //step 1:CHARG_CHG_OUT和CHARG_CHG_IN设置为电平触发，其他还是边沿触发
    u8RegValue = 0x5F;
    Charge_RegWrite(CHARGER_ADDR, INTERRUPT_TYPE_REG,&u8RegValue,1);

    //step 2:clear all interrupts
    u8RegValue = 0x00;
    Charge_RegWrite(CHARGER_ADDR, INTERRUPT_REG,&u8RegValue,1);

    //step 3:wait interrupt happen
    while(SMDrv_GPIO_InBitRead(BAT_CHG_PIN) == 1);

    //step 4:读取中断状态，并做判断
    Charge_RegRead(CHARGER_ADDR, INTERRUPT_REG, &u8RegValue, 1);
    Bat_Debug((0,"reRead interrupt = 0x%02x\n",u8RegValue));
    u8iqr = ((u8RegValue & CHARG_CHG_IN) != 0x00) ? CHARG_CHG_IN : CHARG_CHG_OUT;

    //step 5:全部中断设置为边沿触发
    u8RegValue = 0xFF;
    Charge_RegWrite(CHARGER_ADDR, INTERRUPT_TYPE_REG,&u8RegValue,1);
    return u8iqr;
}

//**********************************************************************
// 函数功能:	电池充电状态检测
// 输入参数：	无
// 返回参数：	无
//**********************************************************************
void Drv_Charge_CheckStatus(void)
{
#if(BAT_CHG_PIN != IO_UNKNOW)
    static bat_charge_envet oldBatChargeStatusOld = BAT_OFF_CHARGE;
    bat_charge_envet BatChargeStatus;
    uint8  u8RegValue = 0x00;

    if (SMDrv_GPIO_InBitRead(BAT_CHG_PIN) == 0)
    {
        SMDrv_SWI2C_Open(CHARGE_IIC_MODULE,IIC_SPEED_HIGH);

        //step 1:read interrupt status
        Charge_RegRead(CHARGER_ADDR, INTERRUPT_REG, &u8RegValue, 1);
        Bat_Debug((0,"interrupt = 0x%02x\n",u8RegValue));

        //step 2:check interrupt
        //case 1: 拔插抖动时识别插入和拔除
        if(((u8RegValue & CHARG_CHG_OUT) != 0x00) && ((u8RegValue & CHARG_CHG_IN) != 0x00))
        {
            if(Charge_CheckDetect() == CHARG_CHG_IN)
            {
                BatChargeStatus = BAT_IN_CHARGING;   //in charging event
                Bat_Debug((0,"BAT_IN_CHARGING\n"));
            }
            else
            {
                 Bat_Debug((0,"BAT_OFF_CHARGE\n"));
                 BatChargeStatus = BAT_OFF_CHARGE;    //off charging event
            }
        }
        //case 2:充满及充电超时，都视为电池充满；电池焊接不良，会有误报充满的情况
        else if(((u8RegValue & CHARG_BAT_FULL) != 0x00) || ((u8RegValue & CHARG_TIMER_EXPIRE) != 0x00))
        {
            Bat_Debug((0,"BAT_FULL_CHARGE\n"));
            BatChargeStatus = BAT_FULL_CHARGE;    //charge full event
        }
        //case 3: 充电拔出事件
        else if((u8RegValue & CHARG_CHG_OUT) != 0x00)
        {
            Bat_Debug((0,"BAT_OFF_CHARGE\n"));
            BatChargeStatus = BAT_OFF_CHARGE;    //off charging event
        }
        //case 4:充电插入事件
        else if((u8RegValue & CHARG_CHG_IN) != 0x00)
        {
            Bat_Debug((0,"BAT_IN_CHARGING\n"));
            BatChargeStatus = BAT_IN_CHARGING;   //in charging event
        }
        //case 5:其他事件不作处理
        else
            ;    //do not care others

        //step 3:clear all interrupts
        u8RegValue = 0x00;
        Charge_RegWrite(CHARGER_ADDR, INTERRUPT_REG,&u8RegValue,1);
        SMDrv_SWI2C_Close(CHARGE_IIC_MODULE); 
    }
	else 
	{
		return;
	}

    //update charge status, and notify status to app
	if((oldBatChargeStatusOld != BatChargeStatus) && (Bat_ChgCheckCb != NULL))
	{
		oldBatChargeStatusOld = BatChargeStatus;
//        RTT_DEBUG_printf(0,"oldBatChargeStatusOld=%d,BatChargeStatus =%d\n",oldBatChargeStatusOld, BatChargeStatus);
		(Bat_ChgCheckCb)(BatChargeStatus);
	}
#endif
}

#elif(CHARGER_CHIP == CHARGER_CE3150B)
//**********************************************************************
// 函数功能:	电池充电状态检测
// 输入参数：	无
// 返回参数：	无
//**********************************************************************
void Drv_Charge_CheckStatus(void)
{
#if((BAT_PG_PIN != IO_UNKNOW) && (BAT_CHG_PIN != IO_UNKNOW))
    static bat_charge_envet oldBatChargeStatusOld = BAT_OFF_CHARGE;
    static uint32 u32ChkFullTime =0;  //标记检测到充满状态的次数 
    bat_charge_envet BatChargeStatus;

    if (SMDrv_GPIO_InBitRead(BAT_PG_PIN))
    {
        //fix: 不断拔插充电线测试，在拔掉前CHG脚有概率出现抖动，误判断为充满
        //解法: task调动检测20次(30s)，连续为充满，才判断为充满
        //增加:充电电量小于BAT_FULL_SOC时，不会产生充满事件
        BatChargeStatus = BAT_IN_CHARGING;          //in charging
        //RTT_DEBUG_printf(0,"BAT_CHG_PIN =%d,u8BatSoc=%d\n",am_hal_gpio_input_bit_read(BAT_CHG_PIN),u8BatSoc);
        if(SMDrv_GPIO_InBitRead(BAT_CHG_PIN) == 1)
        {
            if((u32ChkFullTime++) >= 20)
            {
                BatChargeStatus = BAT_FULL_CHARGE;  //charge full event
            }
        }
        else
        {
            u32ChkFullTime = 0;
        }
        //fix :2018.7.13
    }
    else										//off charging event
    {
        u32ChkFullTime = 0;
        BatChargeStatus = BAT_OFF_CHARGE;
    }

    //oldBatChargeStatusOld初始化为BAT_OFF_CHARGE，无需加firstData判断
	if((oldBatChargeStatusOld != BatChargeStatus) && (Bat_ChgCheckCb != NULL))
	{
		oldBatChargeStatusOld = BatChargeStatus;
        RTT_DEBUG_printf(0,"BatChargeStatus =%d\n",BatChargeStatus);
		(Bat_ChgCheckCb)(BatChargeStatus);
	}
#endif
}
#else

#endif

//**********************************************************************
// 函数功能:  充电自检
// 输入参数： 无
// 返回参数：    
//**********************************************************************
ret_type Drv_Charge_SelfTest(void)
{
#if(CHARGER_CHIP == CHARGER_CW6304)
    uint8  u8RegValue;
    SMDrv_SWI2C_Open(CHARGE_IIC_MODULE,IIC_SPEED_HIGH);

    u8RegValue = (CHARG_TERM_VOL_4_3V | CHARG_TERM_CURRENT_10 | CHARG_CONST_CURRENT_100);
    Charge_RegWrite(CHARGER_ADDR, CHARGE_CONFIG_REG,&u8RegValue,1);
    SMDrv_SYS_DelayMs(1);
    u8RegValue = 0x00;
    Charge_RegRead(CHARGER_ADDR, CHARGE_CONFIG_REG, &u8RegValue, 1);
    Bat_Debug((0,"charger config(0x01) value = 0x%02x\n",u8RegValue));
    SMDrv_SWI2C_Close(CHARGE_IIC_MODULE); 
    if(u8RegValue != (CHARG_TERM_VOL_4_3V | CHARG_TERM_CURRENT_10 | CHARG_CONST_CURRENT_100))
    {
        return Ret_Fail;
    }
#endif
    return Ret_OK;
}

