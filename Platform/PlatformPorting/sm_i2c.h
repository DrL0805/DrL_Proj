#ifndef __SM_SWI2C_H
#define __SM_SWI2C_H

#include "platform_common.h"

//定义iic口
enum
{
    IIC0=0,
    IIC1,
    IIC2,
    IIC3,
    IIC4,
    IIC5,
    IIC_MAX,
};

//定义使用IIC的模块类型 accelerate
typedef enum
{
    HR_IIC_MODULE,    //Health Rate 心率
    BAT_IIC_MODULE,   //电量计
	CHARGE_IIC_MODULE,//充电
    MAG_IIC_MODULE,   //Magnetic Sensor 地磁
    ACC_IIC_MODULE,   //accelerate 加速计
    GYR_IIC_MODULE,   //gyroscope 陀螺仪
    AP_IIC_MODULE,    //air pressure 气压

    MAX_IIC_MODULE,   //项目使用iic的模块数，之后的部分是未用的

    TOUCH_IIC_MODULE, //触摸屏
    IT_IIC_MODULE,    //Infrared temperature 红外体温
    WP_IIC_MODULE,    //water temperature 水压
}iic_module;

//定义IIC速度 
#define IIC_SPEED_UPMAX    0
#define IIC_SPEED_HIGHEST  1    //速度最高,有些外设速度可高于400KHZ
#define IIC_SPEED_HIGH     2    //高速， 400KHZ
#define IIC_SPEED_NORMAL   3    //中速，
#define IIC_SPEED_LOW      4    //低速

//**********************************************************************
// 函数功能: 初始化SW iic
// 输入参数：	
// 返回参数：
//**********************************************************************
extern void SMDrv_SWI2C_Init(void);

//**********************************************************************
// 函数功能: 根据driver module ID SW iic
// 输入参数：	
//    modul: driver module ID,值参考iic_module
//    u32speed: IIC速度设置，值参考IIC_SPEED_XXX
// 返回参数：Ret_InvalidParam或Ret_OK
//**********************************************************************
extern ret_type SMDrv_SWI2C_Open(iic_module modul,uint32 u32speed);

//**********************************************************************
// 函数功能: 关闭driver module ID SW IIC,以实现低功耗
// 输入参数：	
//    modul: driver module ID,值参考iic_module
// 返回参数：Ret_InvalidParam或Ret_OK
//**********************************************************************
extern ret_type SMDrv_SWI2C_Close(iic_module modul);

//**********************************************************************
// 函数功能: SW I2C写命令
// 输入参数：	
//    modul: driver module ID,值参考iic_module
//    deviceAddr：  从设备地址
//    regAddr  ：  命令或偏移地址
// 返回参数：Ret_InvalidParam或Ret_OK
//**********************************************************************
extern ret_type SMDrv_SWI2C_WriteCmd(iic_module modul,uint8 deviceAddr, uint8 regAddr);

//**********************************************************************
// 函数功能:   SW I2C写操作
// 输入参数：
// modul: driver module ID,值参考iic_module
// deviceAddr：  从设备地址
// regAddr  ：  命令或偏移地址
// data_Point： 数据指针
// length   ：  数据长度
// 返回参数：   Ret_InvalidParam或Ret_OK
extern ret_type SMDrv_SWI2C_Write(iic_module modul,uint8 deviceAddr, uint8 regAddr, uint8* data_Point, uint16 length);

//**********************************************************************
// 函数功能:   SW I2C读操作
// 输入参数：
// modul: driver module ID,值参考iic_module
// deviceAddr：  从设备地址
// regAddr  ：  命令或偏移地址
// data_Point： 数据指针
// length   ：  数据长度
// 返回参数：   Ret_InvalidParam或Ret_OK
//**********************************************************************
extern ret_type SMDrv_SWI2C_Read(iic_module modul,uint8 deviceAddr, uint8 regAddr, uint8* data_Point, uint16 length);

//**********************************************************************
// 函数功能: 不带命令或偏移地址读SW I2C操作
// 输入参数：
// modul: driver module ID,值参考iic_module
// deviceAddr：  从设备地址
// data_Point： 数据指针
// length   ：  数据长度
// 返回参数：   Ret_InvalidParam或Ret_OK
//**********************************************************************
extern ret_type SMDrv_SWI2C_ReadWithoutCmd(iic_module modul,uint8 deviceAddr, uint8* data_Point, uint16 length);

//**********************************************************************
// 函数功能: 初始化HW IIC
// 输入参数：	
// 返回参数：
//**********************************************************************
extern void SMDrv_HWI2C_Init(void);

//**********************************************************************
// 函数功能: 根据driver module ID打开硬件对应的iic
// 输入参数：	
//    modul: driver module ID,值参考iic_module
//    u32speed: IIC速度设置，值参考IIC_SPEED_XXX
// 返回参数：Ret_InvalidParam或Ret_OK
//**********************************************************************
extern ret_type SMDrv_HWI2C_Open(iic_module modul,uint32 u32speed);

//**********************************************************************
// 函数功能: 关闭driver module ID硬件对应的IIC,以实现低功耗
// 输入参数：	
//    modul: driver module ID,值参考iic_module
// 返回参数：Ret_InvalidParam或Ret_OK
//**********************************************************************
extern ret_type SMDrv_HWI2C_Close(iic_module modul);

//**********************************************************************
// 函数功能: I2C写命令
// 输入参数：	
//    modul: driver module ID,值参考iic_module
//    deviceAddr：  从设备地址
//    regAddr  ：  命令或偏移地址
// 返回参数：Ret_InvalidParam或Ret_OK
//**********************************************************************
extern ret_type SMDrv_HWI2C_WriteCmd(iic_module modul,uint8 deviceAddr, uint8 regAddr);

//**********************************************************************
// 函数功能:   I2C写操作
// 输入参数：
// modul: driver module ID,值参考iic_module
// deviceAddr：  从设备地址
// regAddr  ：  命令或偏移地址
// data_Point： 数据指针
// length   ：  数据长度
// 返回参数：   Ret_InvalidParam或Ret_OK
extern ret_type SMDrv_HWI2C_Write(iic_module modul,uint8 deviceAddr, uint8 regAddr, uint8* data_Point, uint16 length);

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
extern ret_type SMDrv_HWI2C_Read(iic_module modul,uint8 deviceAddr, uint8 regAddr, uint8* data_Point, uint16 length);

//**********************************************************************
// 函数功能: 不带命令或偏移地址读I2C操作
// 输入参数：
// modul: driver module ID,值参考iic_module
// deviceAddr：  从设备地址
// data_Point： 数据指针
// length   ：  数据长度
// 返回参数：   Ret_InvalidParam或Ret_OK
//**********************************************************************
extern ret_type SMDrv_HWI2C_ReadWithoutCmd(iic_module modul,uint8 deviceAddr, uint8* data_Point, uint16 length);

#endif

