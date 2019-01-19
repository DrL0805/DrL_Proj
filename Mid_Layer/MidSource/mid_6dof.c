/**********************************************************************
**
**模块说明: BMI160六轴Mid层
**修改日志：(版本，时间，内容，修改人)
**   		V1.0   2019-1-16  初版  DrL，
				驱动层源码于GitHub下载，根据项目需要进行阉割（减少RAM和FLASH的使用），
				源码自行去GitHub搜索"BMI160"
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
 ** Brief : 六轴初始化
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Mid_6Dof_Init(void)
{
	/* BMI160初始化 */
	Mid6Dof.Dev.id = (BMI160_I2C_ADDR << 1);
	Mid6Dof.Dev.read = Mid_6Dof_I2CRead;
	Mid6Dof.Dev.write = Mid_6Dof_I2CWrite;
	Mid6Dof.Dev.delay_ms = Mid_6Dof_DelayMs;
	drERROR_CHECK("bmi160_init", bmi160_init(&Mid6Dof.Dev));
	
	/* 默认采样参数设置 */
	Mid6Dof.Dev.accel_cfg.power = BMI160_ACCEL_SUSPEND_MODE;//BMI160_ACCEL_LOWPOWER_MODE  BMI160_ACCEL_NORMAL_MODE
	Mid6Dof.Dev.accel_cfg.odr = BMI160_ACCEL_ODR_25HZ;
	Mid6Dof.Dev.accel_cfg.range = BMI160_ACCEL_RANGE_2G;
	Mid6Dof.Dev.accel_cfg.bw = BMI160_ACCEL_BW_OSR4_AVG1;	// 测试时只有 AVG1 才能读取Gsensor数据，原因暂时未知
	Mid6Dof.Dev.gyro_cfg.power = BMI160_GYRO_SUSPEND_MODE;
	Mid6Dof.Dev.gyro_cfg.odr = BMI160_GYRO_ODR_25HZ;
	Mid6Dof.Dev.gyro_cfg.range = BMI160_GYRO_RANGE_500_DPS;
	Mid6Dof.Dev.gyro_cfg.bw = BMI160_GYRO_BW_NORMAL_MODE;	
	drERROR_CHECK("bmi160_set_sens_conf", bmi160_set_sens_conf(&Mid6Dof.Dev));

	/* FIFO参数设置 */
	Mid6Dof.Dev.fifo = &Mid6Dof.FIFOFrame;
	
	/** 其他参数初始化 */
	memset(&Mid6Dof.Acc, 0x00, sizeof(MidAccParam_t));
	memset(&Mid6Dof.Gyr, 0x00, sizeof(MidGyrParam_t));
}

/*******************************************************************************
 ** Brief : 开始Acc采样
 ** Input : @fODR 采样率
 ** Return: @NULL
 ** Call  : 
 ***************/
void Mid_6Dof_AccStart(uint8_t fODR)
{
	MID_6DOF_RTT_LOG(0,"Mid_6Dof_AccStart %d \n", fODR);
	
	uint8_t lResetFlg = false;	// 重新配置传感器参数标志
	
	Mid6Dof.Acc.ODRFlg = false;		// 参数配置过程中，禁止读取传感器数据
	Mid6Dof.Dev.accel_cfg.power = BMI160_ACCEL_LOWPOWER_MODE;
	
	switch(fODR)
	/** 根据应用，暂时只有1Hz和25Hz两种采样率，默认25Hz */
	{
		case BMI160_ACCEL_ODR_1_56HZ:
			Mid6Dof.Acc.ODR1HzCnt++;
			if((1 == Mid6Dof.Acc.ODR1HzCnt) && (0 == Mid6Dof.Acc.ODR25HzCnt))
			/** 不重复配置判断 */
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
			/** 不重复配置判断 */
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
 ** Brief : 关闭Acc采样
 ** Input : @fODR 采样率
 ** Return: @NULL
 ** Call  : 
 ***************/
void Mid_6Dof_AccStop(uint8_t fODR)
{
	MID_6DOF_RTT_LOG(0,"Mid_6Dof_AccStop %d \n", fODR);

	Mid6Dof.Acc.ODRFlg = false;		// 参数配置过程中，禁止读取传感器数据
	
	switch(fODR)
	/** 根据应用，暂时只有1Hz和25Hz两种采样率，默认25Hz */
	{
		case BMI160_ACCEL_ODR_1_56HZ:
			if(Mid6Dof.Acc.ODR1HzCnt)
			{
				Mid6Dof.Acc.ODR1HzCnt--;
			}

			/** 判断是否需要降低采样率或者关闭硬件 */	
			if((0 == Mid6Dof.Acc.ODR25HzCnt) && (0 == Mid6Dof.Acc.ODR1HzCnt))
			/** 关闭硬件 */
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
			
			/** 判断是否需要降低采样率或者关闭硬件 */	
			if((0 == Mid6Dof.Acc.ODR25HzCnt) && (Mid6Dof.Acc.ODR1HzCnt))
			/** 采样率转为1Hz */
			{
				Mid6Dof.Acc.SamplePeriod = 1000;
				Mid6Dof.Dev.accel_cfg.odr = BMI160_ACCEL_ODR_1_56HZ;
				Mid6Dof.Dev.accel_cfg.power = BMI160_ACCEL_LOWPOWER_MODE;
				drERROR_CHECK("bmi160_set_sens_conf1", bmi160_set_sens_conf(&Mid6Dof.Dev));

				MID_6DOF_RTT_LOG(0,"Mid_6Dof_AccStop_1Hz \n");
			}
			else if((0 == Mid6Dof.Acc.ODR25HzCnt) && (0 == Mid6Dof.Acc.ODR1HzCnt))
			/** 关闭硬件 */
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
	/** 如果硬件采集全部关闭，则清空FIFO数据 */
	{
		bmi160_set_fifo_flush(&Mid6Dof.Dev);
	}	
}

void Mid_6Dof_GyrStart(uint8_t fODR)
{
	MID_6DOF_RTT_LOG(0,"Mid_6Dof_GyrStart %d \n", fODR);

	Mid6Dof.Gyr.ODRFlg = false;	// 参数配置过程中，禁止读取传感器数据
	Mid6Dof.Dev.gyro_cfg.power = BMI160_GYRO_NORMAL_MODE;
	switch(fODR)
	{
		case BMI160_GYRO_ODR_25HZ:
			Mid6Dof.Gyr.ODR25HzCnt++;
			if(1 == Mid6Dof.Gyr.ODR25HzCnt)
			/** 不重复配置判断 */	
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
	
	Mid6Dof.Gyr.ODRFlg = false;		// 参数配置过程中，禁止读取传感器数据
	switch(fODR)
	{
		case BMI160_GYRO_ODR_25HZ:
			if(Mid6Dof.Gyr.ODR25HzCnt)
			{
				Mid6Dof.Gyr.ODR25HzCnt--;
			}

			if(0 == Mid6Dof.Gyr.ODR25HzCnt)
			/** 关闭硬件 */	
			{
//				Mid6Dof.Dev.accel_cfg.power = BMI160_ACCEL_SUSPEND_MODE;		// 关闭Gry的FIFO也要把Acc置为suspend模式，不然会产生约10uA电流。
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
	/** 如果硬件采集全部关闭，则清空FIFO数据 */
	{
		bmi160_set_fifo_flush(&Mid6Dof.Dev);
	}
}

uint16_t Mid_6Dof_FIFORead(struct bmi160_sensor_data* fAccData, uint8_t* fAccLen, struct bmi160_sensor_data* fGyrData, uint8_t* fGyrLen)
{
	if((false == Mid6Dof.Acc.ODRFlg) && (false == Mid6Dof.Gyr.ODRFlg))
		return Ret_Fail;

	int8_t rslt = Ret_OK;
	uint8_t lFIFOBuf[MID_6DOF_FIFO_LEN];	// 临时存储读取的FIFO数据
	
	Mid6Dof.FIFOFrame.data = lFIFOBuf;
	Mid6Dof.FIFOFrame.length = MID_6DOF_FIFO_LEN;

	/** FIFO读之前先配置为NORMAL模式，否则快速读不可用 */
	Mid6Dof.Dev.accel_cfg.power = BMI160_ACCEL_NORMAL_MODE;
	bmi160_set_power_mode(&Mid6Dof.Dev);

	/** 读取FIFO原始数据 */
//	rslt |= bmi160_get_fifo_data(&Mid6Dof.Dev);
	drERROR_CHECK("bmi160_set_sens_conf", bmi160_get_fifo_data(&Mid6Dof.Dev));
//	MID_6DOF_RTT_LOG(0,"bmi160_get_fifo_data %d \n",Mid6Dof.Dev.fifo->length);

	/** 转换Acc数据 */
//	rslt |= bmi160_extract_accel(fAccData, fAccLen, &Mid6Dof.Dev);
	drERROR_CHECK("bmi160_extract_accel", bmi160_extract_accel(fAccData, fAccLen, &Mid6Dof.Dev));
	#if 0	// 打印读取并转换完成的FIFO数据
	MID_6DOF_RTT_LOG(0,"fAccLen %d \n",*fAccLen);
	for (uint32_t i = 0; i < *fAccLen; i++) 
	{
		MID_6DOF_RTT_LOG(0, "[%d] %d %d %d \n", i, fAccData[i].x, fAccData[i].y, fAccData[i].z);
	}
	#endif

	/** 转换Gyr数据 */
//	rslt |= bmi160_extract_gyro(fGyrData, fGyrLen, &Mid6Dof.Dev);
	drERROR_CHECK("bmi160_extract_accel", bmi160_extract_gyro(fGyrData, fGyrLen, &Mid6Dof.Dev));
	#if 0	// 打印读取并转换完成的FIFO数据
	MID_6DOF_RTT_LOG(0,"fGyrLen %d \n",*fGyrLen);
	for (uint32_t i = 0; i < *fGyrLen; i++) 
	{
		MID_6DOF_RTT_LOG(0, "[%d] %d %d %d \n", i, fGyrData[i].x, fGyrData[i].y, fGyrData[i].z);
	}
	#endif

	/* 读完后再配置回low power模式，节约功耗 */
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
	#if 0	// 加速度
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
	
	#if 1	// 角速度
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
		/** 经测试，只要打开Gyr的FIFO采集，Acc也会产生FIFO数据，
			但仅打开AccFIFO，不会产生Gyr数据。
			原因暂时未知，猜测是Gyr配置为normal模式导致的
		*/
		Mid_6Dof_GyrStart(BMI160_GYRO_ODR_25HZ);	
		Mid_6Dof_AccStart(BMI160_ACCEL_ODR_25HZ);
	}
	#endif
}















