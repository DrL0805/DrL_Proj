/**********************************************************************
**
**ģ��˵��: BMI160����Mid��
**�޸���־��(�汾��ʱ�䣬���ݣ��޸���)
**   		V1.0   2019-1-16  ����  DrL��
				������Դ����GitHub���أ�������Ŀ��Ҫ�����˸����RAM��FLASH��ʹ�ã���
				Դ������ȥGitHub����"BMI160"
**
**********************************************************************/

#include "mid_6dof.h"
#include "sm_i2c.h"

static Mid6DofParam_t Mid6Dof;

static int8_t Mid_6Dof_I2CRead(uint8 dev_address, uint8 reg_address, uint8 *regval, uint16 length)
{
	SMDrv_SWI2C_Open(ACC_IIC_MODULE,IIC_SPEED_HIGH);
    SMDrv_SWI2C_Read(ACC_IIC_MODULE,dev_address, reg_address, regval, length);
	SMDrv_SWI2C_Close(ACC_IIC_MODULE);
	return 0;
}

static int8_t Mid_6Dof_I2CWrite(uint8 dev_address, uint8 reg_address, uint8 *regval, uint16 length)
{
	SMDrv_SWI2C_Open(ACC_IIC_MODULE,IIC_SPEED_HIGH);
	SMDrv_SWI2C_Write(ACC_IIC_MODULE,dev_address, reg_address, regval, length);
	SMDrv_SWI2C_Close(ACC_IIC_MODULE);
	return 0;
}

static void Mid_6Dof_DelayMs(uint32_t Ms)
{
	vTaskDelay(Ms);
}

/*******************************************************************************
 ** Brief : �����ʼ��
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Mid_6Dof_Init(void)
{
	/* BMI160��ʼ�� */
	Mid6Dof.Dev.id = (BMI160_I2C_ADDR << 1);
	Mid6Dof.Dev.read = Mid_6Dof_I2CRead;
	Mid6Dof.Dev.write = Mid_6Dof_I2CWrite;
	Mid6Dof.Dev.delay_ms = Mid_6Dof_DelayMs;
	drERROR_CHECK("bmi160_init", bmi160_init(&Mid6Dof.Dev));
	
	/* Ĭ�ϲ����������� */
	Mid6Dof.Dev.accel_cfg.power = BMI160_ACCEL_SUSPEND_MODE;//BMI160_ACCEL_LOWPOWER_MODE  BMI160_ACCEL_NORMAL_MODE
	Mid6Dof.Dev.accel_cfg.odr = BMI160_ACCEL_ODR_25HZ;
	Mid6Dof.Dev.accel_cfg.range = BMI160_ACCEL_RANGE_2G;
	Mid6Dof.Dev.accel_cfg.bw = BMI160_ACCEL_BW_OSR4_AVG1;	// ����ʱֻ�� AVG1 ���ܶ�ȡGsensor���ݣ�ԭ����ʱδ֪
	Mid6Dof.Dev.gyro_cfg.power = BMI160_GYRO_SUSPEND_MODE;
	Mid6Dof.Dev.gyro_cfg.odr = BMI160_GYRO_ODR_25HZ;
	Mid6Dof.Dev.gyro_cfg.range = BMI160_GYRO_RANGE_500_DPS;
	Mid6Dof.Dev.gyro_cfg.bw = BMI160_GYRO_BW_NORMAL_MODE;	
	drERROR_CHECK("bmi160_set_sens_conf", bmi160_set_sens_conf(&Mid6Dof.Dev));

	/* FIFO�������� */
	Mid6Dof.Dev.fifo = &Mid6Dof.FIFOFrame;
	
	/** ����������ʼ�� */
	memset(&Mid6Dof.Acc, 0x00, sizeof(MidAccParam_t));
	memset(&Mid6Dof.Gyr, 0x00, sizeof(MidGyrParam_t));
}

/*******************************************************************************
 ** Brief : ��ʼAcc����
 ** Input : @fODR ������
 ** Return: @NULL
 ** Call  : 
 ***************/
void Mid_6Dof_AccStart(uint8_t fODR)
{
	MID_6DOF_RTT_LOG(0,"Mid_6Dof_AccStart %d \n", fODR);
	
	uint8_t lResetFlg = false;	// �������ô�����������־
	
	Mid6Dof.Acc.ODRFlg = false;		// �������ù����У���ֹ��ȡ����������
	Mid6Dof.Dev.accel_cfg.power = BMI160_ACCEL_LOWPOWER_MODE;
	
	switch(fODR)
	/** ����Ӧ�ã���ʱֻ��1Hz��25Hz���ֲ����ʣ�Ĭ��25Hz */
	{
		case BMI160_ACCEL_ODR_1_56HZ:
			Mid6Dof.Acc.ODR1HzCnt++;
			if((1 == Mid6Dof.Acc.ODR1HzCnt) && (0 == Mid6Dof.Acc.ODR25HzCnt))
			/** ���ظ������ж� */
			{
				lResetFlg = true;
				Mid6Dof.Dev.accel_cfg.odr = BMI160_ACCEL_ODR_1_56HZ;
				Mid6Dof.Acc.SamplePeriod = 1000;
				MID_6DOF_RTT_LOG(0,"Mid_6Dof_AccStart_1Hz \n");
			}
			break;
		case BMI160_ACCEL_ODR_25HZ:
			Mid6Dof.Acc.ODR25HzCnt++;
			if(1 == Mid6Dof.Acc.ODR25HzCnt)
			/** ���ظ������ж� */
			{
				lResetFlg = true;
				Mid6Dof.Dev.accel_cfg.odr = BMI160_ACCEL_ODR_25HZ;
				Mid6Dof.Acc.SamplePeriod = 40;
				MID_6DOF_RTT_LOG(0,"Mid_6Dof_AccStart_25Hz \n");	
			}			
			break;
		default:
			drERROR_CHECK("Mid_6Dof_AccStart", Ret_InvalidParam);
			break;
	}
	
	if(lResetFlg)
	{
		drERROR_CHECK("bmi160_set_fifo_config", 
			bmi160_set_fifo_config(BMI160_FIFO_ACCEL | BMI160_FIFO_HEADER, BMI160_ENABLE, &Mid6Dof.Dev));
		drERROR_CHECK("bmi160_set_sens_conf", bmi160_set_sens_conf(&Mid6Dof.Dev));
	}
	
	if(Mid6Dof.Acc.ODR1HzCnt+Mid6Dof.Acc.ODR25HzCnt)
	{
		Mid6Dof.Acc.ODRFlg = true;
	}
}

/*******************************************************************************
 ** Brief : �ر�Acc����
 ** Input : @fODR ������
 ** Return: @NULL
 ** Call  : 
 ***************/
void Mid_6Dof_AccStop(uint8_t fODR)
{
	MID_6DOF_RTT_LOG(0,"Mid_6Dof_AccStop %d \n", fODR);

	Mid6Dof.Acc.ODRFlg = false;		// �������ù����У���ֹ��ȡ����������
	
	switch(fODR)
	/** ����Ӧ�ã���ʱֻ��1Hz��25Hz���ֲ����ʣ�Ĭ��25Hz */
	{
		case BMI160_ACCEL_ODR_1_56HZ:
			if(Mid6Dof.Acc.ODR1HzCnt)
			{
				Mid6Dof.Acc.ODR1HzCnt--;
			}

			/** �ж��Ƿ���Ҫ���Ͳ����ʻ��߹ر�Ӳ�� */	
			if((0 == Mid6Dof.Acc.ODR25HzCnt) && (0 == Mid6Dof.Acc.ODR1HzCnt))
			/** �ر�Ӳ�� */
			{
				Mid6Dof.Dev.accel_cfg.power = BMI160_ACCEL_SUSPEND_MODE;
				drERROR_CHECK("bmi160_set_fifo_config", 
					bmi160_set_fifo_config(BMI160_FIFO_ACCEL, BMI160_DISABLE, &Mid6Dof.Dev));
				drERROR_CHECK("bmi160_set_sens_conf0", bmi160_set_sens_conf(&Mid6Dof.Dev));
				
				MID_6DOF_RTT_LOG(0,"Mid_6Dof_AccStop_SUSPEND \n");
			}
			break;
		case BMI160_ACCEL_ODR_25HZ:
			if(Mid6Dof.Acc.ODR25HzCnt)
			{
				Mid6Dof.Acc.ODR25HzCnt--;
			}
			
			/** �ж��Ƿ���Ҫ���Ͳ����ʻ��߹ر�Ӳ�� */	
			if((0 == Mid6Dof.Acc.ODR25HzCnt) && (Mid6Dof.Acc.ODR1HzCnt))
			/** ������תΪ1Hz */
			{
				Mid6Dof.Acc.SamplePeriod = 1000;
				Mid6Dof.Dev.accel_cfg.odr = BMI160_ACCEL_ODR_1_56HZ;
				Mid6Dof.Dev.accel_cfg.power = BMI160_ACCEL_LOWPOWER_MODE;
				drERROR_CHECK("bmi160_set_sens_conf1", bmi160_set_sens_conf(&Mid6Dof.Dev));

				MID_6DOF_RTT_LOG(0,"Mid_6Dof_AccStop_1Hz \n");
			}
			else if((0 == Mid6Dof.Acc.ODR25HzCnt) && (0 == Mid6Dof.Acc.ODR1HzCnt))
			/** �ر�Ӳ�� */
			{
				Mid6Dof.Dev.accel_cfg.power = BMI160_ACCEL_SUSPEND_MODE;
				drERROR_CHECK("bmi160_set_fifo_config", 
					bmi160_set_fifo_config(BMI160_FIFO_ACCEL, BMI160_DISABLE, &Mid6Dof.Dev));
				drERROR_CHECK("bmi160_set_sens_conf2", bmi160_set_sens_conf(&Mid6Dof.Dev));

				MID_6DOF_RTT_LOG(0,"Mid_6Dof_AccStop_SUSPEND \n");
			}
			break;			
		default:
			drERROR_CHECK("Mid_6Dof_AccStop", Ret_InvalidParam);
			break;
	}

	if(Mid6Dof.Acc.ODR1HzCnt+Mid6Dof.Acc.ODR25HzCnt)
	{
		Mid6Dof.Acc.ODRFlg = true;
	}
	
	if((false == Mid6Dof.Acc.ODRFlg) && (false == Mid6Dof.Gyr.ODRFlg))
	/** ���Ӳ���ɼ�ȫ���رգ������FIFO���� */
	{
		bmi160_set_fifo_flush(&Mid6Dof.Dev);
	}	
}

void Mid_6Dof_GyrStart(uint8_t fODR)
{
	MID_6DOF_RTT_LOG(0,"Mid_6Dof_GyrStart %d \n", fODR);

	Mid6Dof.Gyr.ODRFlg = false;	// �������ù����У���ֹ��ȡ����������
	Mid6Dof.Dev.gyro_cfg.power = BMI160_GYRO_NORMAL_MODE;
	switch(fODR)
	{
		case BMI160_GYRO_ODR_25HZ:
			Mid6Dof.Gyr.ODR25HzCnt++;
			if(1 == Mid6Dof.Gyr.ODR25HzCnt)
			/** ���ظ������ж� */	
			{
				Mid6Dof.Dev.gyro_cfg.odr = BMI160_GYRO_ODR_25HZ;
				Mid6Dof.Gyr.SamplePeriod = 40;
				drERROR_CHECK("bmi160_set_fifo_config", 
					bmi160_set_fifo_config(BMI160_FIFO_GYRO | BMI160_FIFO_HEADER, BMI160_ENABLE, &Mid6Dof.Dev));
				drERROR_CHECK("bmi160_set_sens_conf", bmi160_set_sens_conf(&Mid6Dof.Dev));			
			}
			break;
		default:
			drERROR_CHECK("Mid_6Dof_GyrStart", Ret_InvalidParam);
			break;
	}
	
	if(Mid6Dof.Gyr.ODR25HzCnt)
	{
		Mid6Dof.Gyr.ODRFlg = true;
	}
}

void Mid_6Dof_GyrStop(uint8_t fODR)
{
	MID_6DOF_RTT_LOG(0,"Mid_6Dof_GyrStop %d \n", fODR);
	
	Mid6Dof.Gyr.ODRFlg = false;		// �������ù����У���ֹ��ȡ����������
	switch(fODR)
	{
		case BMI160_GYRO_ODR_25HZ:
			if(Mid6Dof.Gyr.ODR25HzCnt)
			{
				Mid6Dof.Gyr.ODR25HzCnt--;
			}

			if(0 == Mid6Dof.Gyr.ODR25HzCnt)
			/** �ر�Ӳ�� */	
			{
//				Mid6Dof.Dev.accel_cfg.power = BMI160_ACCEL_SUSPEND_MODE;		// �ر�Gry��FIFOҲҪ��Acc��Ϊsuspendģʽ����Ȼ�����Լ10uA������
				Mid6Dof.Dev.gyro_cfg.power = BMI160_GYRO_SUSPEND_MODE;				
				drERROR_CHECK("bmi160_set_fifo_config", 
					bmi160_set_fifo_config(BMI160_FIFO_GYRO, BMI160_DISABLE, &Mid6Dof.Dev));
				drERROR_CHECK("bmi160_set_sens_conf0", bmi160_set_sens_conf(&Mid6Dof.Dev));				
			}
			break;
		default:
			drERROR_CHECK("Mid_6Dof_GyrStart", Ret_InvalidParam);
			break;
	}	

	if(Mid6Dof.Gyr.ODR25HzCnt)
	{
		Mid6Dof.Gyr.ODRFlg = true;
	}
	
	if((false == Mid6Dof.Acc.ODRFlg) && (false == Mid6Dof.Gyr.ODRFlg))
	/** ���Ӳ���ɼ�ȫ���رգ������FIFO���� */
	{
		bmi160_set_fifo_flush(&Mid6Dof.Dev);
	}
}

uint16_t Mid_6Dof_FIFORead(struct bmi160_sensor_data* fAccData, uint8_t* fAccLen, struct bmi160_sensor_data* fGyrData, uint8_t* fGyrLen)
{
	if((false == Mid6Dof.Acc.ODRFlg) && (false == Mid6Dof.Gyr.ODRFlg))
		return Ret_Fail;

	int8_t rslt = Ret_OK;
	uint8_t lFIFOBuf[MID_6DOF_FIFO_LEN];	// ��ʱ�洢��ȡ��FIFO����
	
	Mid6Dof.FIFOFrame.data = lFIFOBuf;
	Mid6Dof.FIFOFrame.length = MID_6DOF_FIFO_LEN;

	/** FIFO��֮ǰ������ΪNORMALģʽ��������ٶ������� */
	Mid6Dof.Dev.accel_cfg.power = BMI160_ACCEL_NORMAL_MODE;
	bmi160_set_power_mode(&Mid6Dof.Dev);

	/** ��ȡFIFOԭʼ���� */
//	rslt |= bmi160_get_fifo_data(&Mid6Dof.Dev);
	drERROR_CHECK("bmi160_set_sens_conf", bmi160_get_fifo_data(&Mid6Dof.Dev));
//	MID_6DOF_RTT_LOG(0,"bmi160_get_fifo_data %d \n",Mid6Dof.Dev.fifo->length);

	/** ת��Acc���� */
//	rslt |= bmi160_extract_accel(fAccData, fAccLen, &Mid6Dof.Dev);
	drERROR_CHECK("bmi160_extract_accel", bmi160_extract_accel(fAccData, fAccLen, &Mid6Dof.Dev));
	#if 0	// ��ӡ��ȡ��ת����ɵ�FIFO����
	MID_6DOF_RTT_LOG(0,"fAccLen %d \n",*fAccLen);
	for (uint32_t i = 0; i < *fAccLen; i++) 
	{
		MID_6DOF_RTT_LOG(0, "[%d] %d %d %d \n", i, fAccData[i].x, fAccData[i].y, fAccData[i].z);
	}
	#endif

	/** ת��Gyr���� */
//	rslt |= bmi160_extract_gyro(fGyrData, fGyrLen, &Mid6Dof.Dev);
	drERROR_CHECK("bmi160_extract_accel", bmi160_extract_gyro(fGyrData, fGyrLen, &Mid6Dof.Dev));
	#if 0	// ��ӡ��ȡ��ת����ɵ�FIFO����
	MID_6DOF_RTT_LOG(0,"fGyrLen %d \n",*fGyrLen);
	for (uint32_t i = 0; i < *fGyrLen; i++) 
	{
		MID_6DOF_RTT_LOG(0, "[%d] %d %d %d \n", i, fGyrData[i].x, fGyrData[i].y, fGyrData[i].z);
	}
	#endif

	/* ����������û�low powerģʽ����Լ���� */
	Mid6Dof.Dev.accel_cfg.power = BMI160_ACCEL_LOWPOWER_MODE;
	rslt |= bmi160_set_power_mode(&Mid6Dof.Dev);	
	
	drERROR_CHECK("Mid_6Dof_FIFORead", rslt);

	return rslt;
}

Mid6DofParam_t* Mid_6Dof_ParamPGet(void)
{
	return &Mid6Dof;
}

void Mid_6Dof_Test(void)
{
	#if 0	// ���ٶ�
	static uint8_t lAccStartFlg = false;
	
	if(lAccStartFlg)
	{
		lAccStartFlg = false;
		Mid_6Dof_AccStop(BMI160_ACCEL_ODR_25HZ);
	}
	else
	{
		lAccStartFlg = true;
		Mid_6Dof_AccStart(BMI160_ACCEL_ODR_25HZ);
	}
	#endif
	
	#if 1	// ���ٶ�
	static uint8_t lGyrStartFlg = false;
	
	if(lGyrStartFlg)
	{
		lGyrStartFlg = false;
		Mid_6Dof_GyrStop(BMI160_GYRO_ODR_25HZ);	
		Mid_6Dof_AccStop(BMI160_ACCEL_ODR_25HZ);
	}
	else
	{
		lGyrStartFlg = true;
		/** �����ԣ�ֻҪ��Gyr��FIFO�ɼ���AccҲ�����FIFO���ݣ�
			������AccFIFO���������Gyr���ݡ�
			ԭ����ʱδ֪���²���Gyr����Ϊnormalģʽ���µ�
		*/
		Mid_6Dof_GyrStart(BMI160_GYRO_ODR_25HZ);	
		Mid_6Dof_AccStart(BMI160_ACCEL_ODR_25HZ);
	}
	#endif
}















