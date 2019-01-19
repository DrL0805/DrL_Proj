#ifndef __SM_SPI_H
#define __SM_SPI_H

#include "platform_common.h"

//����ʹ��spi��ģ������
typedef enum
{
    BLE_SPI_MODULE,    //ʹ��SPIͨѶ��BLE����    
    FONT_SPI_MODULE,   //�ֿ�
    FLASH_SPI_MODULE,  //SPI FLASH
    MAX_SPI_MODULE,    
}spi_module;

//**********************************************************************
// ��������: ��ʼ��SPI
// ���������	
// ���ز�����
//**********************************************************************
extern void SMDrv_SPI_Init(void);

//**********************************************************************
// ��������: ����driver module ID��Ӳ����Ӧ��SPI
// ���������	
//    modul: driver module ID
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_SPI_Open(spi_module modul);

//**********************************************************************
// ��������: �ر�driver module IDӲ����Ӧ��SPI
// ���������	
//    modul: driver module ID
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_SPI_Close(spi_module modul);

//**********************************************************************
// ��������: ����driver module ID��Ӳ����Ӧ��SPI
// ���������	
//    modul: driver module ID,ֵ�ο�spi_module
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_SPI_Wake(spi_module modul);

//**********************************************************************
// ��������: ��driver module IDӲ����Ӧ��SPI����sleepģʽ
// �������:
//    modul: driver module ID,ֵ�ο�spi_module
// ���ز�����Ret_InvalidParam��Ret_OK
//**********************************************************************
extern ret_type SMDrv_SPI_Sleep(spi_module modul);

//**********************************************************************
// ��������: ����driver module��ȡspi module ID
// ���������	
//    modul: driver module ID,ֵ�ο�spi_module
// ���ز�����spi Module ID
//**********************************************************************
extern uint32 SMDrv_SPI_GetModuleId(spi_module modul);

//**********************************************************************
// ��������: ��driver module ID��Ӧ��SPIд1 ���ֽ�
// ���������	
//    modul: driver module ID
// ���ز�����
//**********************************************************************
extern void SMDrv_SPI_WriteByte(spi_module modul,uint8 u8ch);

//**********************************************************************
// ��������: ��driver module ID��Ӧ��SPIд����ֽ�
// ���������	
//    modul: driver module ID
// ���ز�����
//**********************************************************************
extern void SMDrv_SPI_WriteBytes(spi_module modul,uint8 *pData, uint16 length);

//**********************************************************************
// ��������: ��driver module ID��Ӧ��SPI������ֽ�
// ���������	
//    modul: driver module ID
// ���ز�����
//**********************************************************************
extern void SMDrv_SPI_ReadBytes(spi_module modul,uint8* pData, uint16 length);

#endif

