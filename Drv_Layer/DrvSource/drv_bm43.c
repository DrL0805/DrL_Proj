
#include "sm_i2c.h"
#include "sm_sys.h"
#include "bsp_common.h"

#include "drv_bm43.h"

static bool m_bm43_initial = false;

//General Sensor Support Functions
//RAW SENSOR Reading 24bit format
#define SM_DEFAULT                  0xA0
#define SM_USERSET                  0xA1
#define SM_AZSM_DEFAULT             0xA2
#define SM_AZSM_USERSET             0xA3
#define TM_DEFAULT                  0xA4
#define TM_USERSET                  0xA5
#define TM_AZTM_DEFAULT             0xA6
#define TM_AZTM_USERSET             0xA7
#define SM_TM_AZTM_DEFAULT          0xAA
// Command List
#define Start_NOM                   0xA8
#define Start_CM                    0xA9
#define Measure                     0xAA
#define MeasureCyclic               0xAB	// ����ģʽ��������ϵ�ת���¶ȣ������ر��
#define Over2Measure                0xAC	// ��2���¶����ֵ�ŵ��Ĵ�����Ȼ�����˯��
#define Over4Measure                0xAD	// ��4���¶����ֵ�ŵ��Ĵ�����Ȼ�����˯��
#define Over8Measure                0xAE	// ��8���¶����ֵ�ŵ��Ĵ�����Ȼ�����˯��
#define Over16Measure               0xAF	// ��16���¶����ֵ�ŵ��Ĵ�����Ȼ�����˯��
#define SET_SM_Config1              0xB0
#define SET_SM_Config2              0xB1
#define STOP_CYC                    0xBF	// ֹͣ�����Ե��¶�ת��
#define NOP                         0xF0
// Not Assigned 8bit Registers
#define STATUS                      0x00
#define SENSOR_HIGH                 0x01
#define SENSOR_MIDDLE               0x02
#define SENSOR_LOW                  0x03
#define TEMP_HIGH                   0x04
#define TEMP_MIDDLE                 0x05
#define TEMP_LOW                    0x06
#define COMMAND                     0x07
#define COMMAND_DAT1                0x08
#define COMMAND_DAT2                0x09
#define READ_REGISTER               0x0A
#define READ_MEMDAT1                0x0B
#define READ_MEMDAT2                0x0C

#define delay_ms    				SMDrv_SYS_DelayMs
#define delay_us					SMDrv_SYS_DelayUs

#define  SlaveAddr 					0x00 //Change after changing slaveaddress 0x02 register[6:0]

unsigned char mcu_register[] =
{
	0x00, // STATUS 0
	0x01, // SENSOR_HIGH 1
	0x02, // SENSOR_MiDDLE 2
	0x03, // SENSOR_LOW 3
	0x04, // TEMP_HIGH 4
	0x05, // TEMP_MIDDLE 5
	0x06, // TEMP_LOW 6
	0x00, // COMMAND 7
	0x00, // COMMAND_DAT1 8
	0x00, // COMMAND_DAT2 9
	0x00, // READ_REGISTER 10
	0x00, // READ_MEMDAT1 11
	0x00, // READ_MEMDAT2 12
	0x00  // I2C_Error 13
};

//**********************************************************************
// ��������:    ��Ӳ��I2C����
// ���������    
// ���ز�����    ��
uint8 Drv_BM43_Open(void)
{
	uint8 u8ret = 0x00;

	u8ret = SMDrv_SWI2C_Open(IT_IIC_MODULE,IIC_SPEED_HIGH);

	return u8ret;
}

//**********************************************************************
// ��������:    �ر�Ӳ��I2C����
// ���������    
// ���ز�����    ��
uint8 Drv_BM43_Close(void)
{
	uint8 u8ret = 0x00;
	
	u8ret = SMDrv_SWI2C_Close(IT_IIC_MODULE);
	
	return u8ret;
}

//**********************************************************************
// ��������:    �Ĵ���д
// ���������    
// ���ز�����    ��
static void BM43_RegWrite(uint8 dev_addr, uint8 reg_addr, uint8 *regval, uint16 length)
{
    SMDrv_SWI2C_Write(IT_IIC_MODULE,dev_addr, reg_addr, regval, length);
}

//**********************************************************************
// ��������:    �Ĵ�����
// ���������
// ���ز�����
static void BM43_RegRead(uint8 dev_addr, uint8 reg_addr, uint8 *regval, uint16 length)
{
    SMDrv_SWI2C_Read(IT_IIC_MODULE,dev_addr, reg_addr, regval, length);
}

//**********************************************************************
// ��������:    ���豸��ǰ״̬������������ mcu_register
// ���������
// ���ز�����
static uint32_t read_status(void) //read status
{  
	BM43_RegRead(SlaveAddr, STATUS, &mcu_register[STATUS], 1);
	
	return 0;
}

//**********************************************************************
// ��������:    ����豸��ǰ״̬
// ���������
// ���ز�����
static uint32_t check_busy(void) //check if flash writing is finished or not
{
	int i = 0;
	while(1)
	{
		if(0x00 == read_status())
        {
            if((mcu_register[STATUS]&0x10) == 0)
                return 0x00;
        }
		if (++i > 150)	// 30ms��ʱ
			break;
		else
			delay_us(200);
	}
	
	return 0xff;
}

//************************************************************************************************************
// ��������:   	��������
// ��������:    cmd		->	������
// ����ֵ  :	�������    
uint32_t command_only(unsigned char cmd) //See command list listed above
{
	uint8 ui8Regtemp[1] = {0x00};
//	uint8 RetVal = 0xFF;
	
	BM43_RegWrite(SlaveAddr, cmd, ui8Regtemp, 1);
	
	return check_busy();	
}

//************************************************************************************************************
// ��������:   	���ʹ�����������
// ��������:    cmd			->	������
//				cmddat1		->	����1
//				cmddat2		->	����2
// ����ֵ  :	�������   
uint32_t command_data(unsigned char cmd, unsigned char cmddat1, unsigned char cmddat2)
{
    uint8_t    buf[2];
//    uint32_t 	RetVal = 0xFF;
    
    buf[0] = cmddat1;
    buf[1] = cmddat2;

	BM43_RegWrite(SlaveAddr, cmd, buf, 2);
	
	return check_busy();	
}

//************************************************************************************************************
// ��������:   	���Ĵ�����ַд����
// ��������:    address		->	�Ĵ�����ַ
//				dat1		->	����1
//				dat2		->	����2
// ����ֵ  :	�������
uint32_t write_mem_register(unsigned char address, unsigned char dat1, unsigned char dat2) //register write
{
    uint8_t     buf[3];
    uint32_t     ret;
    
    buf[0] = address + 0x40;
    buf[1] = dat1;
    buf[2] = dat2;
    
    BM43_RegWrite(SlaveAddr, buf[0], &buf[1], 2);	// �ο��ڹ����򣬲�ȷ���Ƿ���ã�
    
	ret = check_busy();
    if(0 != ret)
    {
        return ret;
    }
    
	mcu_register[COMMAND] = address;
	mcu_register[COMMAND_DAT1] = dat1;
	mcu_register[COMMAND_DAT2] = dat2;
	
	return ret;
}

//************************************************************************************************************
// ��������:   	���Ĵ������ݣ����������� mcu_register
// ��������:    address		->	�Ĵ�����ַ
// ����ֵ  :	�������     
uint32_t read_mem_register(unsigned char address) //read register
{
    uint32_t     ret;

    return ret;
}

//************************************************************************************************************
// ��������:   	����ɵ��¶�ֵ * 10
// ��������:    temperature		->	�ɵ����¶�ֵ * 10
// ����ֵ  :	��       
//************************************************************************************************************
static void calculate (int32_t *temperature)    
{      
	float TemperatureValue = 0.0;
	float SensorValue = 0.0;
	float Ambient = 0.0;
	float Delta_T = 0.0;	
	float Object;  
	
	//TemperatureValue = make32(mcu_register[TEMP_HIGH], mcu_register[TEMP_MIDDLE], mcu_register[TEMP_LOW]);
	
	TemperatureValue = (float)(mcu_register[TEMP_HIGH]*65536)+(float)(mcu_register[TEMP_MIDDLE]*256)+(float)mcu_register[TEMP_LOW];
		
	//SensorValue = make32(mcu_register[SENSOR_HIGH], mcu_register[SENSOR_MIDDLE], mcu_register[SENSOR_LOW]);
	
	SensorValue = (float)((float)mcu_register[SENSOR_HIGH]*(float)65536)+(float)((float)mcu_register[SENSOR_MIDDLE]*(float)256)+(float)mcu_register[SENSOR_LOW];
	
	Ambient = (TemperatureValue / (float)pow(2, 24))*(float)125.0 - (float)40.0;
	Delta_T = (float)1000*(SensorValue / (float)pow(2, 24) -(float) 0.5);
	Object = Ambient + Delta_T;  

	*temperature = (Object*(float)10);     
}

//************************************************************************************************************
// ��������:   	�����¶�ת��
// ��������:    ��
// ����ֵ  :	��       
//************************************************************************************************************
void bm43_conversion_start(void)
{
	command_only(Start_NOM);
	command_only(Over2Measure);
}

//************************************************************************************************************
// ��������:   	ֹͣ�¶�ת��
// ��������:    ��
// ����ֵ  :	��       
//************************************************************************************************************
void bm43_conversion_stop(void)
{
	command_only(STOP_CYC);
}

//************************************************************************************************************
// ��������:   	��ȡת������¶�ֵ
// ��������:    ��
// ����ֵ  :	�ɵ����¶� * 10 (�����ǰ�¶�29.8�棬������298)       
//************************************************************************************************************
int32_t bm43_calculate_temp(void)
{
	int32_t 	temperature = 0;
	BM43_RegRead(SlaveAddr, STATUS, &mcu_register[STATUS], 7);
	calculate(&temperature);
	
	return temperature;
}

//************************************************************************************************************
// ��������:   	��ʼ�������¶ȴ�����������һ������
// ��������:    ��
// ����ֵ  :	�������       
//************************************************************************************************************
uint32_t Drv_BM43_init(void)
{
  	int32_t temperature = 0;
		
    if (m_bm43_initial)
    {
        return 0;
    }

    // Ӳ��I2C��ʼ��
	Drv_BM43_Open();

	// �����������ʲô��
	read_mem_register(0x02);

    command_only(Start_NOM);
	command_only(Over2Measure);
	// ע���ж��¶�����
	// �ȴ�������� 
	delay_ms(100);

	BM43_RegRead(SlaveAddr, STATUS, &mcu_register[STATUS], 7);
	calculate(&temperature);

	Drv_BM43_Close();
	
	m_bm43_initial = true;
	
    return 0;
}


uint8_t Drv_BM43_SelfTest(void)
{
//	uint8 ui8Regtemp[1] = {0x00};
	uint8 RetVal = 0;
	int32_t temperature = 0;
	
	// ��Ӳ��I2C
	Drv_BM43_Open();
	
	// �������ģʽ
	RetVal = command_only(Start_NOM);

	// �ɼ�����ȡƽ��ֵ���������
	RetVal = command_only(Over2Measure);

	// ��ʱ�ȴ��������
	delay_ms(50);
	
	// ��ȡ�������
	BM43_RegRead(SlaveAddr, STATUS, &mcu_register[STATUS], 7);
	
	// �����¶�ֵ��ע�⸺�ţ���λ�棬һ��С���㣬
	// ��23.9���϶ȣ�temperature = 239
	calculate(&temperature);

	// Ӳ������
	Drv_BM43_Close();
	
	//����������
	RTT_DEBUG_printf(0,"BM43 Test: %d \n",temperature);
	
	return RetVal;
}






