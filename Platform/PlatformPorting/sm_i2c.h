#ifndef __SM_SWI2C_H
#define __SM_SWI2C_H

#include "platform_common.h"

//����iic��
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

//����ʹ��IIC��ģ������ accelerate
typedef enum
{
    HR_IIC_MODULE,    //Health Rate ����
    BAT_IIC_MODULE,   //������
	CHARGE_IIC_MODULE,//���
    MAG_IIC_MODULE,   //Magnetic Sensor �ش�
    ACC_IIC_MODULE,   //accelerate ���ټ�
    GYR_IIC_MODULE,   //gyroscope ������
    AP_IIC_MODULE,    //air pressure ��ѹ

    MAX_IIC_MODULE,   //��Ŀʹ��iic��ģ������֮��Ĳ�����δ�õ�

    TOUCH_IIC_MODULE, //������
    IT_IIC_MODULE,    //Infrared temperature ��������
    WP_IIC_MODULE,    //water temperature ˮѹ
}iic_module;

//����IIC�ٶ� 
#define IIC_SPEED_UPMAX    0
#define IIC_SPEED_HIGHEST  1    //�ٶ����,��Щ�����ٶȿɸ���400KHZ
#define IIC_SPEED_HIGH     2    //���٣� 400KHZ
#define IIC_SPEED_NORMAL   3    //���٣�
#define IIC_SPEED_LOW      4    //����

//**********************************************************************
// ��������: ��ʼ��SW iic
// ���������	
// ���ز�����
//**********************************************************************
extern void SMDrv_SWI2C_Init(void);

//**********************************************************************
// ��������: ����driver module ID SW iic
// ���������	
//    modul: driver module ID,ֵ�ο�iic_module
//    u32speed: IIC�ٶ����ã�ֵ�ο�IIC_SPEED_XXX
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_SWI2C_Open(iic_module modul,uint32 u32speed);

//**********************************************************************
// ��������: �ر�driver module ID SW IIC,��ʵ�ֵ͹���
// ���������	
//    modul: driver module ID,ֵ�ο�iic_module
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_SWI2C_Close(iic_module modul);

//**********************************************************************
// ��������: SW I2Cд����
// ���������	
//    modul: driver module ID,ֵ�ο�iic_module
//    deviceAddr��  ���豸��ַ
//    regAddr  ��  �����ƫ�Ƶ�ַ
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_SWI2C_WriteCmd(iic_module modul,uint8 deviceAddr, uint8 regAddr);

//**********************************************************************
// ��������:   SW I2Cд����
// ���������
// modul: driver module ID,ֵ�ο�iic_module
// deviceAddr��  ���豸��ַ
// regAddr  ��  �����ƫ�Ƶ�ַ
// data_Point�� ����ָ��
// length   ��  ���ݳ���
// ���ز�����   Ret_InvalidParam��Ret_OK
extern ret_type SMDrv_SWI2C_Write(iic_module modul,uint8 deviceAddr, uint8 regAddr, uint8* data_Point, uint16 length);

//**********************************************************************
// ��������:   SW I2C������
// ���������
// modul: driver module ID,ֵ�ο�iic_module
// deviceAddr��  ���豸��ַ
// regAddr  ��  �����ƫ�Ƶ�ַ
// data_Point�� ����ָ��
// length   ��  ���ݳ���
// ���ز�����   Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_SWI2C_Read(iic_module modul,uint8 deviceAddr, uint8 regAddr, uint8* data_Point, uint16 length);

//**********************************************************************
// ��������: ���������ƫ�Ƶ�ַ��SW I2C����
// ���������
// modul: driver module ID,ֵ�ο�iic_module
// deviceAddr��  ���豸��ַ
// data_Point�� ����ָ��
// length   ��  ���ݳ���
// ���ز�����   Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_SWI2C_ReadWithoutCmd(iic_module modul,uint8 deviceAddr, uint8* data_Point, uint16 length);

//**********************************************************************
// ��������: ��ʼ��HW IIC
// ���������	
// ���ز�����
//**********************************************************************
extern void SMDrv_HWI2C_Init(void);

//**********************************************************************
// ��������: ����driver module ID��Ӳ����Ӧ��iic
// ���������	
//    modul: driver module ID,ֵ�ο�iic_module
//    u32speed: IIC�ٶ����ã�ֵ�ο�IIC_SPEED_XXX
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_HWI2C_Open(iic_module modul,uint32 u32speed);

//**********************************************************************
// ��������: �ر�driver module IDӲ����Ӧ��IIC,��ʵ�ֵ͹���
// ���������	
//    modul: driver module ID,ֵ�ο�iic_module
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_HWI2C_Close(iic_module modul);

//**********************************************************************
// ��������: I2Cд����
// ���������	
//    modul: driver module ID,ֵ�ο�iic_module
//    deviceAddr��  ���豸��ַ
//    regAddr  ��  �����ƫ�Ƶ�ַ
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_HWI2C_WriteCmd(iic_module modul,uint8 deviceAddr, uint8 regAddr);

//**********************************************************************
// ��������:   I2Cд����
// ���������
// modul: driver module ID,ֵ�ο�iic_module
// deviceAddr��  ���豸��ַ
// regAddr  ��  �����ƫ�Ƶ�ַ
// data_Point�� ����ָ��
// length   ��  ���ݳ���
// ���ز�����   Ret_InvalidParam��Ret_OK
extern ret_type SMDrv_HWI2C_Write(iic_module modul,uint8 deviceAddr, uint8 regAddr, uint8* data_Point, uint16 length);

//**********************************************************************
// ��������:   I2C������
// ���������
// modul: driver module ID,ֵ�ο�iic_module
// deviceAddr��  ���豸��ַ
// regAddr  ��  �����ƫ�Ƶ�ַ
// data_Point�� ����ָ��
// length   ��  ���ݳ���
// ���ز�����   Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_HWI2C_Read(iic_module modul,uint8 deviceAddr, uint8 regAddr, uint8* data_Point, uint16 length);

//**********************************************************************
// ��������: ���������ƫ�Ƶ�ַ��I2C����
// ���������
// modul: driver module ID,ֵ�ο�iic_module
// deviceAddr��  ���豸��ַ
// data_Point�� ����ָ��
// length   ��  ���ݳ���
// ���ز�����   Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_HWI2C_ReadWithoutCmd(iic_module modul,uint8 deviceAddr, uint8* data_Point, uint16 length);

#endif

