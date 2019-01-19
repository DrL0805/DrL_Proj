/**********************************************************************
**
**模块说明: 对接MCU 硬件I2C驱动接口，并根据项目原理图作配置
**软件版本，修改日志(时间，内容),修改人:
**   V1.0   2018.9.10  初版  ZSL 
**
**********************************************************************/
//在此模块中使用IIC IO口，因此需定义IIC_MODULE
#define IIC_MODULE
#include "io_config.h"

#include "am_mcu_apollo.h"
#include "sm_i2c.h"
#include "sm_gpio.h"

typedef struct
{
    uint32 u32module; //标记哪些模块已open iic
}hwiic_info_s;

static hwiic_info_s hwiic_info[IIC_MAX];

typedef struct
{
    uint32 u32iic_id;    //iic number
    uint32 u32pin_scl;   //iic clock pin
    uint32 u32pin_sda;   //iic data pin

    uint32 u32pad_scl;   //iic clock pad mode,把pin脚设置为iic clock模式
    uint32 u32pad_sda;   //iic data pad mode
}hwi2c_info_s;

#ifdef AM_PART_APOLLO3
static void *giic_Handle[IIC_MAX] = {NULL};

static uint8 iic_modul2info(iic_module modul,hwi2c_info_s *piic_info)
{
    if(piic_info == NULL)
        return FALSE;

    //配置: 只需修改此处配置
    if((modul == MAG_IIC_MODULE) || (modul == CHARGE_IIC_MODULE) || (modul == BAT_IIC_MODULE))
        piic_info->u32iic_id = IIC4;
    else if((modul == IT_IIC_MODULE)  || (modul == AP_IIC_MODULE))
        piic_info->u32iic_id = IIC1;
    else if(modul == HR_IIC_MODULE)
        piic_info->u32iic_id = IIC3;
    else if((modul == ACC_IIC_MODULE)  || (modul == GYR_IIC_MODULE))
        piic_info->u32iic_id = IIC2;
    else
        return FALSE;
    //配置 

    switch(piic_info->u32iic_id)
    {
    case IIC0:
        if((IIC0_SCL == 5) && (IIC0_SDA == 6))
        {
            piic_info->u32pin_scl = IIC0_SCL;
            piic_info->u32pin_sda = IIC0_SDA;
            piic_info->u32pad_scl = AM_HAL_PIN_5_M0SCL;
            piic_info->u32pad_sda = AM_HAL_PIN_6_M0SDAWIR3;
        }
        else
        {
            Err_Info((0,"hw iic0 pin config error:%d,%d\n",IIC0_SCL,IIC0_SDA));
            return FALSE;
        }
        break;
    case IIC1:
        if((IIC1_SCL == 8) && (IIC1_SDA == 9))
        {
            piic_info->u32pin_scl = IIC1_SCL;
            piic_info->u32pin_sda = IIC1_SDA;
            piic_info->u32pad_scl = AM_HAL_PIN_8_M1SCL;
            piic_info->u32pad_sda = AM_HAL_PIN_9_M1SDAWIR3;
        }
        else
        {
            Err_Info((0,"hw iic1 pin config error:%d,%d\n",IIC1_SCL,IIC1_SDA));
            return FALSE;
        }
        break;
    case IIC2:
        if((IIC2_SCL == 27) && (IIC2_SDA == 25))
        {
            piic_info->u32pin_scl = IIC2_SCL;
            piic_info->u32pin_sda = IIC2_SDA;
            piic_info->u32pad_scl = AM_HAL_PIN_27_M2SCL;
            piic_info->u32pad_sda = AM_HAL_PIN_25_M2SDAWIR3;
        }
        else
        {
            Err_Info((0,"hw iic2 pin config error:%d,%d\n",IIC2_SCL,IIC2_SDA));
            return FALSE;
        }
        break;
    case IIC3:
        if((IIC3_SCL == 42) && (IIC3_SDA == 43))
        {
            piic_info->u32pin_scl = IIC3_SCL;
            piic_info->u32pin_sda = IIC3_SDA;
            piic_info->u32pad_scl = AM_HAL_PIN_42_M3SCL;
            piic_info->u32pad_sda = AM_HAL_PIN_43_M3SDAWIR3;
        }
        else
        {
            Err_Info((0,"hw iic3 pin config error:%d,%d\n",IIC3_SCL,IIC3_SDA));
            return FALSE;
        }
        break;
    case IIC4:
        if((IIC4_SCL == 39) && (IIC4_SDA == 40))
        {
            piic_info->u32pin_scl = IIC4_SCL;
            piic_info->u32pin_sda = IIC4_SDA;
            piic_info->u32pad_scl = AM_HAL_PIN_39_M4SCL;
            piic_info->u32pad_sda = AM_HAL_PIN_40_M4SDAWIR3;
        }
        else
        {
            Err_Info((0,"hw iic4 pin config error:%d,%d\n",IIC4_SCL,IIC4_SDA));
            return FALSE;
        }
        break;
    case IIC5:
        if((IIC5_SCL == 48) && (IIC5_SDA == 49))
        {
            piic_info->u32pin_scl = IIC5_SCL;
            piic_info->u32pin_sda = IIC5_SDA;
            piic_info->u32pad_scl = AM_HAL_PIN_48_M5SCL;
            piic_info->u32pad_sda = AM_HAL_PIN_49_M5SDAWIR3;
        }
        else
        {
            Err_Info((0,"hw iic5 pin config error:%d,%d\n",IIC5_SCL,IIC5_SDA));
            return FALSE;
        }
        break;
    default:
        return FALSE;
    }

    return TRUE;
}



//**********************************************************************
// 函数功能: 根据driver module ID打开硬件对应的iic
// 输入参数：	
//    modul: driver module ID,值参考iic_module
//    u32speed: IIC速度设置，值参考IIC_SPEED_XXX
// 返回参数：Ret_InvalidParam或Ret_OK
//**********************************************************************
ret_type SMDrv_HWI2C_Open(iic_module modul,uint32 u32speed)
{
    hwi2c_info_s iic_info;
    am_hal_iom_config_t IIC_Config;

    am_hal_gpio_pincfg_t gPin_config = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint32 ret;

    if(iic_modul2info(modul,&iic_info) == FALSE)
        return Ret_NoDevice;

    //此iic已打开
    if(hwiic_info[iic_info.u32iic_id].u32module != 0x00)
    {
        hwiic_info[iic_info.u32iic_id].u32module = (1 << modul); //标记模块已经open
        return Ret_OK;
    }

    //set iic config info
    memset(&IIC_Config,0x00,sizeof(am_hal_iom_config_t));
    IIC_Config.eInterfaceMode = AM_HAL_IOM_I2C_MODE;
 #if 0
    if(u32speed == IIC_SPEED_HIGHEST)
        IIC_Config.ui32ClockFreq = AM_HAL_IOM_400KHZ;
    else if(u32speed == IIC_SPEED_NORMAL)
        IIC_Config.ui32ClockFreq = AM_HAL_IOM_250KHZ;
    else if(u32speed == IIC_SPEED_LOW)
        IIC_Config.ui32ClockFreq = AM_HAL_IOM_100KHZ;
    else
        IIC_Config.ui32ClockFreq = AM_HAL_IOM_375KHZ;
 #else
    if((u32speed == IIC_SPEED_HIGHEST) || (u32speed == IIC_SPEED_HIGH))
        IIC_Config.ui32ClockFreq = AM_HAL_IOM_400KHZ;
    else
        IIC_Config.ui32ClockFreq = AM_HAL_IOM_100KHZ;
 #endif

    //open HW IIC flow:
    //step 1:config iic io pin as spi mode
    gPin_config.ePullup = AM_HAL_GPIO_PIN_PULLUP_12K;
    gPin_config.eDriveStrength = AM_HAL_GPIO_PIN_DRIVESTRENGTH_12MA;
    gPin_config.eGPOutcfg = AM_HAL_GPIO_PIN_OUTCFG_OPENDRAIN;
    gPin_config.uFuncSel = iic_info.u32pad_scl;    //clock
    gPin_config.uIOMnum = iic_info.u32iic_id;
    am_hal_gpio_pinconfig(iic_info.u32pin_scl, gPin_config);
    gPin_config.uFuncSel = iic_info.u32pad_sda;    //sda
    am_hal_gpio_pinconfig(iic_info.u32pin_sda,gPin_config);

    //step 3:init/enable iic
    //Initialize the IOM instance.
    if((ret = am_hal_iom_initialize(iic_info.u32iic_id, &giic_Handle[iic_info.u32iic_id])) != AM_HAL_STATUS_SUCCESS)
        Err_Info((0,"Error - init iic failed:%d\n",ret));

    // Enable power to the IOM instance.
    if((ret = am_hal_iom_power_ctrl(giic_Handle[iic_info.u32iic_id], AM_HAL_SYSCTRL_WAKE, false)) != AM_HAL_STATUS_SUCCESS)
        Err_Info((0,"Error - iic power wake failed:%d\n",ret));

    // Configure the IOM for Serial operation during initialization.
    if((ret = am_hal_iom_configure(giic_Handle[iic_info.u32iic_id], &IIC_Config)) != AM_HAL_STATUS_SUCCESS)
        Err_Info((0,"Error - config iic failed:%d\n",ret));

    // Enable the IOM.
    if((ret = am_hal_iom_enable(giic_Handle[iic_info.u32iic_id]) != AM_HAL_STATUS_SUCCESS) != AM_HAL_STATUS_SUCCESS)
        Err_Info((0,"Error - enable iic failed:%d\n",ret));

    hwiic_info[iic_info.u32iic_id].u32module = (1 << modul); //标记模块已经open
    return Ret_OK;
}

//**********************************************************************
// 函数功能: 关闭driver module ID硬件对应的IIC,以实现低功耗
// 输入参数：	
//    modul: driver module ID,值参考iic_module
// 返回参数：Ret_InvalidParam或Ret_OK
//**********************************************************************
ret_type SMDrv_HWI2C_Close(iic_module modul)
{
    hwi2c_info_s iic_info;
    am_hal_gpio_pincfg_t pin_config = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint32 ret;

    if(iic_modul2info(modul,&iic_info) == FALSE)
        return Ret_NoDevice;

    hwiic_info[iic_info.u32iic_id].u32module &= (~(1 << modul)); //清除模块使用iic口标记
    //有几个模块同时使用此iic
    if(hwiic_info[iic_info.u32iic_id].u32module != 0x00)
        return Ret_OK;

    //step 1:config iic io pin as gpio mode
    pin_config.uFuncSel       = 3;
    pin_config.eDriveStrength = AM_HAL_GPIO_PIN_DRIVESTRENGTH_2MA;
    pin_config.eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_PUSHPULL;
    am_hal_gpio_pinconfig(iic_info.u32pin_scl, pin_config);
    am_hal_gpio_pinconfig(iic_info.u32pin_sda,pin_config);
    SMDrv_GPIO_BitSet(iic_info.u32pin_scl);
    SMDrv_GPIO_BitSet(iic_info.u32pin_sda);

    //step 2:disable iic power control
    if((ret = am_hal_iom_disable(giic_Handle[iic_info.u32iic_id])) != AM_HAL_STATUS_SUCCESS)
        Err_Info((0,"Error - disable iic failed:%d\n",ret));
    if((ret = am_hal_iom_power_ctrl(giic_Handle[iic_info.u32iic_id], AM_HAL_SYSCTRL_DEEPSLEEP, false)) != AM_HAL_STATUS_SUCCESS)
        Err_Info((0,"Error - iic power sleep ctrl failed:%d\n",ret));
    if((ret = am_hal_iom_uninitialize(giic_Handle[iic_info.u32iic_id])) != AM_HAL_STATUS_SUCCESS)
        Err_Info((0,"Error - iic deinit failed:%d\n",ret));

    return Ret_OK;
}

//**********************************************************************
// 函数功能: I2C写命令
// 输入参数：	
//    modul: driver module ID,值参考iic_module
//    deviceAddr：  从设备地址
//    regAddr  ：  命令或偏移地址
// 返回参数：Ret_InvalidParam或Ret_OK
//**********************************************************************
ret_type SMDrv_HWI2C_WriteCmd(iic_module modul,uint8 deviceAddr, uint8 regAddr)
{
    hwi2c_info_s iic_info;
    am_hal_iom_transfer_t Transaction;
    uint32 u32Ret;

    if(iic_modul2info(modul,&iic_info) == FALSE)
        return Ret_NoDevice;

    if(hwiic_info[iic_info.u32iic_id].u32module == 0x00)
    {
        Err_Info((0,"modul :%d iic is not open\n",modul));
        return Ret_Fail;
    }

    // Create the transaction.
    memset(&Transaction,0x00,sizeof(am_hal_iom_transfer_t));    
    Transaction.uPeerInfo.ui32I2CDevAddr = deviceAddr >> 1;
    Transaction.eDirection      = AM_HAL_IOM_TX;
#if 1
    Transaction.ui32NumBytes    = 1;
    Transaction.pui32TxBuffer   = (uint32_t *)&regAddr;
#else
    Transaction.ui32InstrLen    = 1;
    Transaction.ui32Instr       = (uint32_t)regAddr;
#endif

    // Execute the transction over IOM.
    if ((u32Ret = am_hal_iom_blocking_transfer(giic_Handle[iic_info.u32iic_id], &Transaction)) != AM_HAL_STATUS_SUCCESS)
        Err_Info((0,"Error - iic Write CMD failed:%d.\n",u32Ret));

    return Ret_OK;
}

//**********************************************************************
// 函数功能:   I2C写操作
// 输入参数：
// modul: driver module ID,值参考iic_module
// deviceAddr：  从设备地址
// regAddr  ：  命令或偏移地址
// data_Point： 数据指针
// length   ：  数据长度
// 返回参数：   Ret_InvalidParam或Ret_OK
ret_type SMDrv_HWI2C_Write(iic_module modul,uint8 deviceAddr, uint8 regAddr, uint8 *Buffer, uint16 length)
{
    hwi2c_info_s iic_info;
    am_hal_iom_transfer_t Transaction;
    uint32 ret;

    if(iic_modul2info(modul,&iic_info) == FALSE)
        return Ret_NoDevice;

    if(hwiic_info[iic_info.u32iic_id].u32module == 0x00)
    {
        Err_Info((0,"modul :%d iic is not open\n",modul));
        return Ret_Fail;
    }

    // Create the transaction.
    memset(&Transaction,0x00,sizeof(am_hal_iom_transfer_t));
    Transaction.uPeerInfo.ui32I2CDevAddr = deviceAddr >> 1;
    Transaction.eDirection      = AM_HAL_IOM_TX;
    Transaction.ui32InstrLen    = 1;
    Transaction.ui32Instr       = (uint32_t)regAddr;
    Transaction.ui32NumBytes    = length;
    Transaction.pui32TxBuffer   = (uint32_t *)Buffer;

    // Execute the transction over IOM.
    if((ret = am_hal_iom_blocking_transfer(giic_Handle[iic_info.u32iic_id], &Transaction)) != AM_HAL_STATUS_SUCCESS)
        Err_Info((0,"Error - iic Write bytes failed=%d\n",ret));

    return Ret_OK;
}

//**********************************************************************
// 函数功能:   I2C读操作
// 输入参数：
// modul: driver module ID,值参考iic_module
// deviceAddr：  从设备地址
// regAddr  ：  命令或偏移地址
// data_Point： 数据指针
// length   ：  数据长度
// 返回参数：   Ret_InvalidParam或Ret_OK
//**********************************************************************
ret_type SMDrv_HWI2C_Read(iic_module modul,uint8 deviceAddr, uint8 regAddr, uint8* Buffer, uint16 length)
{
    hwi2c_info_s iic_info;
    am_hal_iom_transfer_t Transaction;
    uint32 ret;

    if(iic_modul2info(modul,&iic_info) == FALSE)
        return Ret_NoDevice;

    if(hwiic_info[iic_info.u32iic_id].u32module == 0x00)
    {
        Err_Info((0,"modul :%d iic is not open\n",modul));
        return Ret_Fail;
    }

    // Create the transaction.
    memset(&Transaction,0x00,sizeof(am_hal_iom_transfer_t));
    Transaction.uPeerInfo.ui32I2CDevAddr = deviceAddr  >> 1;
    Transaction.eDirection      = AM_HAL_IOM_RX;
    Transaction.ui32InstrLen    = 1;
    Transaction.ui32Instr       = (uint32_t)regAddr;
    Transaction.ui32NumBytes    = length;    
    Transaction.pui32RxBuffer   = (uint32_t *)Buffer;

    // Execute the transction over IOM.
    if((ret = am_hal_iom_blocking_transfer(giic_Handle[iic_info.u32iic_id], &Transaction)) != AM_HAL_STATUS_SUCCESS)
        Err_Info((0,"Error - iic read failed:%d\n",ret));

    return Ret_OK;
}

//**********************************************************************
// 函数功能: 不带命令或偏移地址读I2C操作
// 输入参数：
// modul: driver module ID,值参考iic_module
// deviceAddr：  从设备地址
// data_Point： 数据指针
// length   ：  数据长度
// 返回参数：   Ret_InvalidParam或Ret_OK
//**********************************************************************
ret_type SMDrv_HWI2C_ReadWithoutCmd(iic_module modul,uint8 deviceAddr, uint8* Buffer, uint16 length)
{
    hwi2c_info_s iic_info;
    am_hal_iom_transfer_t Transaction;
    uint32 ret;

    if(iic_modul2info(modul,&iic_info) == FALSE)
        return Ret_NoDevice;

    if(hwiic_info[iic_info.u32iic_id].u32module == 0x00)
    {
        Err_Info((0,"modul :%d iic is not open\n",modul));
        return Ret_Fail;
    }

    // Create the transaction.
    memset(&Transaction,0x00,sizeof(am_hal_iom_transfer_t));
    Transaction.uPeerInfo.ui32I2CDevAddr = deviceAddr >> 1;
    Transaction.eDirection      = AM_HAL_IOM_RX;
    Transaction.ui32InstrLen    = 0;
    Transaction.ui32Instr       = 0;   //no reg addr or cmd
    Transaction.ui32NumBytes    = length;
    Transaction.pui32TxBuffer   = (uint32_t *)Buffer;

    // Execute the transction over IOM.
    if((ret = am_hal_iom_blocking_transfer(giic_Handle[iic_info.u32iic_id], &Transaction)) != AM_HAL_STATUS_SUCCESS)
        Err_Info((0,"Error - iic read bytes without cmd failed=%d\n",ret));

    return Ret_OK;
}

#else

static uint8 iic_modul2info(iic_module modul,hwi2c_info_s *piic_info)
{
    if(piic_info == NULL)
        return FALSE;

    //配置: 只需修改此处配置
    if(modul == MAG_IIC_MODULE)
        piic_info->u32iic_id = IIC0;
    else if((modul == BAT_IIC_MODULE)  || (modul == AP_IIC_MODULE))
        piic_info->u32iic_id = IIC1;
    else if(modul == HR_IIC_MODULE)
        piic_info->u32iic_id = IIC4;
    else if((modul == ACC_IIC_MODULE)  || (modul == GYR_IIC_MODULE))
        piic_info->u32iic_id = IIC5;
    else
        return FALSE;
    //配置 

    switch(piic_info->u32iic_id)
    {
    case IIC0:
        if((IIC0_SCL == 5) && (IIC0_SDA == 6))
        {
            piic_info->u32pin_scl = IIC0_SCL;
            piic_info->u32pin_sda = IIC0_SDA;
            piic_info->u32pad_scl = AM_HAL_PIN_5_M0SCL;
            piic_info->u32pad_sda = AM_HAL_PIN_6_M0SDA;
        }
        else
        {
            Err_Info((0,"hw iic0 pin config error:%d,%d\n",IIC0_SCL,IIC0_SDA));
            return FALSE;
        }
        break;
    case IIC1:
        if((IIC1_SCL == 8) && (IIC1_SDA == 9))
        {
            piic_info->u32pin_scl = IIC1_SCL;
            piic_info->u32pin_sda = IIC1_SDA;
            piic_info->u32pad_scl = AM_HAL_PIN_8_M1SCL;
            piic_info->u32pad_sda = AM_HAL_PIN_9_M1SDA;
        }
        else
        {
            Err_Info((0,"hw iic1 pin config error:%d,%d\n",IIC1_SCL,IIC1_SDA));
            return FALSE;
        }
        break;
    case IIC2:
        if((IIC2_SCL == 27) && (IIC2_SDA == 25))
        {
            piic_info->u32pin_scl = IIC2_SCL;
            piic_info->u32pin_sda = IIC2_SDA;
            piic_info->u32pad_scl = AM_HAL_PIN_27_M2SCL;
            piic_info->u32pad_sda = AM_HAL_PIN_25_M2SDA;
        }
        else
        {
            Err_Info((0,"hw iic2 pin config error:%d,%d\n",IIC2_SCL,IIC2_SDA));
            return FALSE;
        }
        break;
    case IIC3:
        if((IIC3_SCL == 42) && (IIC3_SDA == 43))
        {
            piic_info->u32pin_scl = IIC3_SCL;
            piic_info->u32pin_sda = IIC3_SDA;
            piic_info->u32pad_scl = AM_HAL_PIN_42_M3SCL;
            piic_info->u32pad_sda = AM_HAL_PIN_43_M3SDA;
        }
        else
        {
            Err_Info((0,"hw iic3 pin config error:%d,%d\n",IIC3_SCL,IIC3_SDA));
            return FALSE;
        }
        break;
    case IIC4:
        if((IIC4_SCL == 39) && (IIC4_SDA == 40))
        {
            piic_info->u32pin_scl = IIC4_SCL;
            piic_info->u32pin_sda = IIC4_SDA;
            piic_info->u32pad_scl = AM_HAL_PIN_39_M4SCL;
            piic_info->u32pad_sda = AM_HAL_PIN_40_M4SDA;
        }
        else
        {
            Err_Info((0,"hw iic4 pin config error:%d,%d\n",IIC4_SCL,IIC4_SDA));
            return FALSE;
        }
        break;
    case IIC5:
        if((IIC5_SCL == 48) && (IIC5_SDA == 49))
        {
            piic_info->u32pin_scl = IIC5_SCL;
            piic_info->u32pin_sda = IIC5_SDA;
            piic_info->u32pad_scl = AM_HAL_PIN_48_M5SCL;
            piic_info->u32pad_sda = AM_HAL_PIN_49_M5SDA;
        }
        else
        {
            Err_Info((0,"hw iic5 pin config error:%d,%d\n",IIC5_SCL,IIC5_SDA));
            return FALSE;
        }
        break;
    default:
        return FALSE;
    }

    return TRUE;
}

//**********************************************************************
// 函数功能: 根据driver module ID打开硬件对应的iic
// 输入参数：	
//    modul: driver module ID,值参考iic_module
//    u32speed: IIC速度设置，值参考IIC_SPEED_XXX
// 返回参数：Ret_InvalidParam或Ret_OK
//**********************************************************************
ret_type SMDrv_HWI2C_Open(iic_module modul,uint32 u32speed)
{
    hwi2c_info_s iic_info;
    am_hal_iom_config_t IIC_Config;

    if(iic_modul2info(modul,&iic_info) == FALSE)
        return Ret_InvalidParam;

    //此iic已打开
    if(hwiic_info[iic_info.u32iic_id].u32module != 0x00)
    {
        hwiic_info[iic_info.u32iic_id].u32module = (1 << modul); //标记模块已经open
        return Ret_OK;
    }

    //open SPI flow:
    //step 1:enable iic power control and set iom as iic mode
    memset(&IIC_Config,0x00,sizeof(am_hal_iom_config_t));
    IIC_Config.ui32InterfaceMode = AM_HAL_IOM_I2CMODE;
    IIC_Config.ui8WriteThreshold = 12;
    IIC_Config.ui8ReadThreshold = 120;
    if(u32speed == IIC_SPEED_HIGHEST)
        IIC_Config.ui32ClockFrequency = AM_HAL_IOM_400KHZ;
    else if(u32speed == IIC_SPEED_NORMAL)
        IIC_Config.ui32ClockFrequency = AM_HAL_IOM_250KHZ;
    else if(u32speed == IIC_SPEED_LOW)
        IIC_Config.ui32ClockFrequency = AM_HAL_IOM_100KHZ;
    else
        IIC_Config.ui32ClockFrequency = AM_HAL_IOM_375KHZ;

    am_hal_iom_pwrctrl_enable(iic_info.u32iic_id);
    am_hal_iom_config(iic_info.u32iic_id, &IIC_Config);

    //step 2:config iic io pin as spi mode
    // Set pins high to prevent bus dips.
    SMDrv_GPIO_BitSet(iic_info.u32pin_scl);
    SMDrv_GPIO_BitSet(iic_info.u32pin_sda);
    SMDrv_GPIO_SetIOPad(iic_info.u32pin_scl, iic_info.u32pad_scl | AM_HAL_GPIO_PULLUP);
    SMDrv_GPIO_SetIOPad(iic_info.u32pin_sda, iic_info.u32pad_sda | AM_HAL_GPIO_PULLUP);
    //step 3:enable iic
    am_hal_iom_enable(iic_info.u32iic_id);

    hwiic_info[iic_info.u32iic_id].u32module = (1 << modul); //标记模块已经open
    return Ret_OK;
}

//**********************************************************************
// 函数功能: 关闭driver module ID硬件对应的IIC,以实现低功耗
// 输入参数：	
//    modul: driver module ID,值参考iic_module
// 返回参数：Ret_InvalidParam或Ret_OK
//**********************************************************************
ret_type SMDrv_HWI2C_Close(iic_module modul)
{
    hwi2c_info_s iic_info;
    am_hal_iom_config_t SPI_Config;

    if(iic_modul2info(modul,&iic_info) == FALSE)
        return Ret_InvalidParam;

    hwiic_info[iic_info.u32iic_id].u32module &= (~(1 << modul)); //清除模块使用iic口标记
    //有几个模块同时使用此iic
    if(hwiic_info[iic_info.u32iic_id].u32module != 0x00)
        return Ret_OK;

    //step 1:disable iic power control
    am_hal_iom_disable(iic_info.u32iic_id);
    am_hal_iom_pwrctrl_disable(iic_info.u32iic_id);

    //step 2:config iic io pin as gpio mode
    SMDrv_GPIO_SetIOPad(iic_info.u32pin_scl, AM_HAL_PIN_OUTPUT);
    SMDrv_GPIO_SetIOPad(iic_info.u32pin_sda, AM_HAL_PIN_OUTPUT);
    if(SPI_Config.bSPOL == 1)  //空闲的时候为high
    {
        SMDrv_GPIO_BitSet(iic_info.u32pin_scl);
        SMDrv_GPIO_BitSet(iic_info.u32pin_sda);
    }
        
    return Ret_OK;
}

//**********************************************************************
// 函数功能: I2C写命令
// 输入参数：	
//    modul: driver module ID,值参考iic_module
//    deviceAddr：  从设备地址
//    regAddr  ：  命令或偏移地址
// 返回参数：Ret_InvalidParam或Ret_OK
//**********************************************************************
ret_type SMDrv_HWI2C_WriteCmd(iic_module modul,uint8 deviceAddr, uint8 regAddr)
{
    hwi2c_info_s iic_info;
    am_hal_iom_status_e ret;

    if(iic_modul2info(modul,&iic_info) == FALSE)
        return Ret_InvalidParam;

    if(hwiic_info[iic_info.u32iic_id].u32module == 0x00)
    {
        Err_Info((0,"modul :%d iic is not open\n",modul));
        return Ret_Fail;
    }

    //fix :swiic时把iic addr左移一位，最低bit为w/r,硬件iic通过接口区分w/r
    deviceAddr >>= 1;
    //fix :2018.9.12
    if((ret = am_hal_iom_i2c_write(iic_info.u32iic_id, deviceAddr, (uint32_t *)&regAddr, 1, AM_HAL_IOM_RAW)) != AM_HAL_IOM_SUCCESS)
        Err_Info((0,"Error - iic Write byte failed=%d\n",ret));
    
    return Ret_OK;
}

//**********************************************************************
// 函数功能:   I2C写操作
// 输入参数：
// modul: driver module ID,值参考iic_module
// deviceAddr：  从设备地址
// regAddr  ：  命令或偏移地址
// data_Point： 数据指针
// length   ：  数据长度
// 返回参数：   Ret_InvalidParam或Ret_OK
ret_type SMDrv_HWI2C_Write(iic_module modul,uint8 deviceAddr, uint8 regAddr, uint8* Buffer, uint16 length)
{
    hwi2c_info_s iic_info;
    am_hal_iom_status_e ret;

    if(iic_modul2info(modul,&iic_info) == FALSE)
        return Ret_InvalidParam;

    if(hwiic_info[iic_info.u32iic_id].u32module == 0x00)
    {
        Err_Info((0,"modul :%d iic is not open\n",modul));
        return Ret_Fail;
    }

    //fix :swiic时把iic addr左移一位，最低bit为w/r,硬件iic通过接口区分w/r
    deviceAddr >>= 1;
    //fix :2018.9.12
    if((ret = am_hal_iom_i2c_write(iic_info.u32iic_id, deviceAddr, (uint32_t *)Buffer, length, AM_HAL_IOM_OFFSET(regAddr))) != AM_HAL_IOM_SUCCESS)
        Err_Info((0,"Error - iic Write bytes failed=%d\n",ret));

    return Ret_OK;
}

//**********************************************************************
// 函数功能:   I2C读操作
// 输入参数：
// modul: driver module ID,值参考iic_module
// deviceAddr：  从设备地址
// regAddr  ：  命令或偏移地址
// data_Point： 数据指针
// length   ：  数据长度
// 返回参数：   Ret_InvalidParam或Ret_OK
//**********************************************************************
ret_type SMDrv_HWI2C_Read(iic_module modul,uint8 deviceAddr, uint8 regAddr, uint8* Buffer, uint16 length)
{
    hwi2c_info_s iic_info;
    am_hal_iom_status_e ret;

    if(iic_modul2info(modul,&iic_info) == FALSE)
        return Ret_InvalidParam;

    if(hwiic_info[iic_info.u32iic_id].u32module == 0x00)
    {
        Err_Info((0,"modul :%d iic is not open\n",modul));
        return Ret_Fail;
    }

    //fix :swiic时把iic addr左移一位，最低bit为w/r,硬件iic通过接口区分w/r
    deviceAddr >>= 1;
    //fix :2018.9.12
    if((ret = am_hal_iom_i2c_read(iic_info.u32iic_id, deviceAddr, (uint32_t *)Buffer, length, AM_HAL_IOM_OFFSET(regAddr))) != AM_HAL_IOM_SUCCESS)
        Err_Info((0,"Error - iic read bytes failed=%d\n",ret));

    return Ret_OK;
}

//**********************************************************************
// 函数功能: 不带命令或偏移地址读I2C操作
// 输入参数：
// modul: driver module ID,值参考iic_module
// deviceAddr：  从设备地址
// data_Point： 数据指针
// length   ：  数据长度
// 返回参数：   Ret_InvalidParam或Ret_OK
//**********************************************************************
ret_type SMDrv_HWI2C_ReadWithoutCmd(iic_module modul,uint8 deviceAddr, uint8* Buffer, uint16 length)
{
    hwi2c_info_s iic_info;
    am_hal_iom_status_e ret;

    if(iic_modul2info(modul,&iic_info) == FALSE)
        return Ret_InvalidParam;

    if(hwiic_info[iic_info.u32iic_id].u32module == 0x00)
    {
        Err_Info((0,"modul :%d iic is not open\n",modul));
        return Ret_Fail;
    }

    //fix :swiic时把iic addr左移一位，最低bit为w/r,硬件iic通过接口区分w/r
    deviceAddr >>= 1;
    //fix :2018.9.12
    if((ret = am_hal_iom_i2c_read(iic_info.u32iic_id, deviceAddr, (uint32_t *)Buffer, length, AM_HAL_IOM_RAW)) != AM_HAL_IOM_SUCCESS)
        Err_Info((0,"Error - iic read bytes without cmd failed=%d\n",ret));
    
    return Ret_OK;
}

#endif

//**********************************************************************
// 函数功能: 初始化HW IIC
// 输入参数：	
// 返回参数：
//**********************************************************************
void SMDrv_HWI2C_Init(void)
{
    memset(hwiic_info,0x00,sizeof(hwiic_info));
}

