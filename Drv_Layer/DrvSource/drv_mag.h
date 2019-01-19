#ifndef MAGNETISM_H
#define MAGNETISM_H

#include "platform_common.h"

// magnetism work mode
typedef enum 
{
	MAG_STANDBY_MODE 		= 0x00,
	MAG_CONTINUOUS_MODE		= 0x01,
	MAG_SELFTEST_MODE 		= 0x02,
}bsp_mag_mode;

//Full Scale range   
typedef enum 
{
	MAG_SCALE_RANGE_2GS   	= 0x00,
	MAG_SCALE_RANGE_8GS   	= 0x01,
	MAG_SCALE_RANGE_12GS   	= 0x02,
	MAG_SCALE_RANGE_20GS  	= 0x03,
}bsp_mag_scalerange;

//Output Data Rate  
typedef enum 
{
	MAG_DATA_RATE_10HZ   	= 0x00,
	MAG_DATA_RATE_50HZ   	= 0x01,
	MAG_DATA_RATE_100HZ   	= 0x02,
	MAG_DATA_RATE_200HZ  	= 0x03,
}bsp_mag_datarate;

//Over  sample Rate 
typedef enum 
{
	MAG_OVER_SAMPLE_RATE_512   	= 0x00,
	MAG_OVER_SAMPLE_RATE_256   	= 0x01,
	MAG_OVER_SAMPLE_RATE_128   	= 0x02,
	MAG_OVER_SAMPLE_RATE_64  	= 0x03,
}bsp_mag_osr;

//**********************************************************************
// ��������:    �شŴ�������ʼ��
// ���������    ��
// ���ز�����    
// 0x00    :    ��ʼ���ɹ�
// 0xff    :    ��ʼ��ʧ��
//**********************************************************************
extern uint8 Drv_Mag_Open(void);
//**********************************************************************
// ��������:    �شŴ�����Ӳ���ر�
// ���������    ��
// ���ز�����    
// 0x00    :    ���óɹ�
// 0xff    :    ����ʧ��
//**********************************************************************
extern uint8 Drv_Mag_Close(void);

//**********************************************************************
// ��������:    �شŴ����������ʼ���������
// ���������    
// sampleRate    ������
//               Valid Values for uint16 sampleRate are:
//               MAG_DATA_RATE_10HZ
//               MAG_DATA_RATE_50HZ
//               MAG_DATA_RATE_100HZ
//               MAG_DATA_RATE_200HZ
// scaleRange    ��������
//               fullscale selection 
//               Valid Values for uint8 scaleRange are:
//               MAG_SCALE_RANGE_2GS
//               MAG_SCALE_RANGE_8GS
//               MAG_SCALE_RANGE_12GS
//               MAG_SCALE_RANGE_20GS
// ���ز�����    
// 0x00    :    ��ʼ���ɹ�
// 0xff    :    ��ʼ��ʧ��
//**********************************************************************
extern uint8 Drv_Mag_Set(bsp_mag_datarate sampleRate, bsp_mag_scalerange scaleRange);

//**********************************************************************
// ��������:  ��ȡ�شŴ�����3�����ݣ�������Ϊ����������ʽ
// ���������    
// axisData ����������ָ��
// ���ز�����    
// 0x00    :    �����ɹ�
// 0xff    :    ����ʧ��
//**********************************************************************
extern uint8 Drv_Mag_Read(int16 xyzData[3]);

//**********************************************************************
// ��������:    �شŴ���������
// ���������   ��
// ���ز�����    
// 0x00    :    �����ɹ�
// 0xff    :    ����ʧ��
//**********************************************************************
extern uint8 Drv_Mag_WakeUp(void);

//**********************************************************************
// ��������:    ���õشŴ���������˯��״̬
// ���������   ��
// ���ز�����    
// 0x00    :    �����ɹ�
// 0xff    :    ����ʧ��
//**********************************************************************
extern uint8 Drv_Mag_GotoSleep(void);

//**********************************************************************
// ��������:    �شŴ������Լ�
// ���������    ��
// ���ز�����    
// 0x00    :    �Լ�ɹ�
// 0x01    :    �Լ�ʧ��
//**********************************************************************
extern uint8 Drv_Mag_SelfTest(void);

#endif

