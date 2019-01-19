/**********************************************************************
**
**模块说明: 
**   
**
**********************************************************************/

#include "io_config.h"
#include "sm_gpio.h"
#include "drv_touch.h"
#include "am_util_delay.h"
#include "upgrade_it7259.h"
#include "sm_sys.h"
#include "mid_scheduler.h"

#define IT7259_ADDR			(0x8C)
#define IT7259_ADDR_READ 	(IT7259_ADDR | 0x01)

#define COMMAND_BUFFER_INDEX   					0x20 
#define QUERY_BUFFER_INDEX						0x80
#define COMMAND_RESPONSE_BUFFER_INDEX 			0xA0 
#define POINT_BUFFER_INDEX    					0xE0 
#define QUERY_SUCCESS     						0x00
#define QUERY_BUSY     							0x01 
#define QUERY_ERROR     						0x02 
#define QUERY_POINT     						0x80 

#define POINT_DATA_REPORT 		0x08	// 0x0X，X表示Finger+Point Information
#define GESTURES_REPORT			0x80
#define TOUCH_EVENT_REPORT		0x40	// 0x4X, X表示Touch Type
#define WAKEUP_REPORT			0x10


#define TAP 				0x20
#define FLICK 				0x22
#define DOUBLE_TAP 			0x23

#define UP					0x08
#define UPPER_RIGHT 		0x09
#define RIGHT 				0x0A
#define LOWER_RIGHT 		0x0B
#define DOWN			 	0x0C
#define LOWER_LEFT 			0x0D
#define LEFT 				0x0E
#define UPPER_LEFT 			0x0F

#define IIC_SCL_PIN 	(48)	
#define IIC_SDA_PIN		(49)
#define I2C_Delay()			am_util_delay_us(1)//am_util_delay_ms(1) //

#define DRV_TOUCH_VDD_ON()	am_hal_gpio_output_clear(TOUCH_EN_PIN)	// 打开TP VDD
#define DRV_TOUCH_VDD_OFF()	am_hal_gpio_output_set(TOUCH_EN_PIN)	// 关闭TP VDD
#define DRV_TOUCH_RST_CLR()	am_hal_gpio_output_clear(TOUCH_RST_PIN)	// 进入复位状态，TP不可用，
#define DRV_TOUCH_RST_SET()	am_hal_gpio_output_set(TOUCH_RST_PIN)	// 解除复位状态，TP可用

#define I2C_SCL_High(PIN)	am_hal_gpio_output_set(PIN)
#define I2C_SCL_Low(PIN) 	am_hal_gpio_output_clear(PIN)
#define I2C_SDA_High(PIN) 	am_hal_gpio_output_set(PIN) 
#define I2C_SDA_Low(PIN) 	am_hal_gpio_output_clear(PIN) 
#define I2C_SDA_Value(PIN) 	am_hal_gpio_input_read(PIN)		// 读值

DrvTouchParam_t	DrvTouch;
static TimerHandle_t 	DrvTouch_TimerHandle;


static void TOUCH_I2C_PIN_OUT(uint32_t PIN)
{
    am_hal_gpio_pincfg_t bfGpioCfg = {0};

	// 临时变量值是随机的，使用前必须清零
//	memset(&bfGpioCfg, 0x00, sizeof(am_hal_gpio_pincfg_t));
    
	bfGpioCfg.uFuncSel       = 3;
    bfGpioCfg.eDriveStrength = AM_HAL_GPIO_PIN_DRIVESTRENGTH_2MA;//AM_HAL_GPIO_PIN_DRIVESTRENGTH_2MA;
    bfGpioCfg.eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_PUSHPULL;
	 bfGpioCfg.ePullup        = AM_HAL_GPIO_PIN_PULLUP_1_5K;//AM_HAL_GPIO_PIN_PULLUP_1_5K;

    am_hal_gpio_pinconfig(PIN, bfGpioCfg);	
}

static void TOUCH_I2C_PIN_IN(uint32_t PIN)
{
    am_hal_gpio_pincfg_t bfGpioCfg = {0};

	// 临时变量值是随机的，使用前必须清零
//	memset(&bfGpioCfg, 0x00, sizeof(am_hal_gpio_pincfg_t));
	
    bfGpioCfg.uFuncSel       = 3;
    bfGpioCfg.eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_DISABLE;
    bfGpioCfg.eGPInput       = AM_HAL_GPIO_PIN_INPUT_ENABLE;
    bfGpioCfg.ePullup        = AM_HAL_GPIO_PIN_PULLUP_1_5K;//AM_HAL_GPIO_PIN_PULLUP_6K;//
    am_hal_gpio_pinconfig(PIN, bfGpioCfg);	
}

static void I2C_PinConfig(void)
{
	SMDrv_GPIO_Open(TOUCH_EN_PIN, NULL, NULL);
	SMDrv_GPIO_Open(TOUCH_RST_PIN, NULL, NULL);
	DRV_TOUCH_VDD_OFF();		// 初始化默认关掉TP
	DRV_TOUCH_RST_CLR();		// reset	TP复位脚拉高后功耗1.9mA，复位脚拉低不产生功耗	
	
	TOUCH_I2C_PIN_OUT(IIC_SCL_PIN);
	TOUCH_I2C_PIN_OUT(IIC_SDA_PIN);
	I2C_SCL_High(IIC_SCL_PIN);
	I2C_SDA_High(IIC_SDA_PIN);
}

static void I2C_Start(void)
{
    TOUCH_I2C_PIN_OUT(IIC_SDA_PIN);
    I2C_SCL_High(IIC_SCL_PIN);
    I2C_Delay();
    I2C_SDA_High(IIC_SDA_PIN);
    I2C_Delay();
    I2C_SDA_Low(IIC_SDA_PIN);
    I2C_Delay();
    I2C_SCL_Low(IIC_SCL_PIN);
    I2C_Delay();
}

static void I2C_Stop(void)
{
    I2C_SCL_Low(IIC_SCL_PIN);
    TOUCH_I2C_PIN_OUT(IIC_SDA_PIN);
    I2C_SDA_Low(IIC_SDA_PIN);
    I2C_Delay();
    I2C_SCL_High(IIC_SCL_PIN);
    I2C_Delay();
    I2C_SDA_High(IIC_SDA_PIN);
    I2C_Delay();
}

static void I2C_NoACK(void)
{
    I2C_SDA_High(IIC_SDA_PIN);
    I2C_Delay();
    I2C_SCL_High(IIC_SCL_PIN);
    I2C_Delay();
    I2C_SCL_Low(IIC_SCL_PIN);
}

static void I2C_ACK(void)
{
    I2C_SDA_Low(IIC_SDA_PIN);
    I2C_Delay();
    I2C_SCL_High(IIC_SCL_PIN);
    I2C_Delay();
    I2C_SCL_Low(IIC_SCL_PIN);
}

static unsigned char I2C_ReadByte(void)
{
    unsigned char i;
    unsigned char Data = 0;
    TOUCH_I2C_PIN_IN(IIC_SDA_PIN);
    I2C_Delay();
    for (i = 0; i < 8; i++)
    {
        I2C_SCL_Low(IIC_SCL_PIN);
        I2C_Delay();
        I2C_SCL_High(IIC_SCL_PIN);
        I2C_Delay();
        if (I2C_SDA_Value(IIC_SDA_PIN) == 1)
        {
            Data = (Data << 1) + 0x01;
        }
        else
        {
            Data = (Data << 1) + 0x00;
        }
    }
    I2C_SCL_Low(IIC_SCL_PIN);
    TOUCH_I2C_PIN_OUT(IIC_SDA_PIN);
    I2C_Delay();
    return (Data);
}

static unsigned short I2C_WriteByte(unsigned char Data)
{
    unsigned char i;
    TOUCH_I2C_PIN_OUT(IIC_SDA_PIN);
    for (i = 0; i < 8; i++)
    {
        if ((Data & 0x80) == 0x80)
        {
            I2C_SDA_High(IIC_SDA_PIN);
        }
        else
        {
            I2C_SDA_Low(IIC_SDA_PIN);
        }
        I2C_Delay();
        I2C_SCL_High(IIC_SCL_PIN);
        I2C_Delay();
        I2C_SCL_Low(IIC_SCL_PIN);
        Data <<= 0x01;
    }

    //      Wait "ACK" Signal
    TOUCH_I2C_PIN_IN(IIC_SDA_PIN);
    I2C_Delay();
    I2C_SCL_High(IIC_SCL_PIN);
    I2C_Delay();

	i = 0xff;
    while(1)
    {
        if(I2C_SDA_Value(IIC_SDA_PIN) == 1)
        {
            if ((--i) == 0)
            {
                TOUCH_I2C_PIN_OUT(IIC_SDA_PIN);
                I2C_SDA_High(IIC_SDA_PIN);
                I2C_Delay();
                return Ret_NoDevice;	//  //no ack indicate
            }
        }
        else
        {
            break;
        }
    }
    I2C_SCL_Low(IIC_SCL_PIN);
    TOUCH_I2C_PIN_OUT(IIC_SDA_PIN);
    I2C_SDA_High(IIC_SDA_PIN);
    I2C_Delay();
    return Ret_OK;   // Write OK
}

static unsigned short I2C_WriteBytes(unsigned char* dataAddr, unsigned short length)
{
    unsigned short i;
    unsigned short ret = Ret_OK;
    for(i = 0; i < length; i++)
    {
        ret = I2C_WriteByte(dataAddr[i]);
        if(ret != Ret_OK)
        {
            break;
        }
    }
    return ret;
}

static void I2C_ReadBytes(unsigned char *dataAddr, unsigned short length)
{
    unsigned short i;
    for(i = 0; i < length; i++)
    {
        dataAddr[i] = I2C_ReadByte();
        if(i < (length - 1))
        {
            I2C_ACK();
        }
        else
        {
            I2C_NoACK();
        }
    }
}


 uint8_t Drv_IT7259_WriteBuffer(uint8_t addr, uint8_t* pdata, int len) 
{
	uint8_t RetVal = Ret_OK;
	
	I2C_Start(); 
	
	RetVal |= I2C_WriteByte(IT7259_ADDR);	// 设备地址
	
	RetVal |= I2C_WriteByte(addr);		// 寄存器地址
	
	RetVal |= I2C_WriteBytes(pdata, len);
	
	I2C_Stop(); 
	
	return RetVal;
}

 uint8_t Drv_IT7259_ReadBuffer(uint8_t addr, uint8_t* pdata, int len) 
{
	uint8_t RetVal = Ret_OK;
	
	I2C_Start(); 
	
	RetVal |= I2C_WriteByte(IT7259_ADDR);	// 设备地址
	RetVal |= I2C_WriteByte(addr);			// 寄存器地址
	
	I2C_Start(); 
	
	RetVal |= I2C_WriteByte(IT7259_ADDR_READ);	// 读地址
	
	I2C_ReadBytes(pdata, len);
	
	I2C_Stop();
	
	return RetVal;
}

 uint8_t Drv_IT7259_ReadBuffer16(uint16_t addr, uint8_t* pdata, int len) 
{
	uint8_t RetVal = Ret_OK;
	
	I2C_Start(); 
	
	RetVal |= I2C_WriteByte(IT7259_ADDR);	// 设备地址
	RetVal |= I2C_WriteByte(addr >> 8);			// 寄存器地址
	RetVal |= I2C_WriteByte(addr);			// 寄存器地址
	
	I2C_Start(); 
	
	RetVal |= I2C_WriteByte(IT7259_ADDR_READ);	// 读地址
	
	I2C_ReadBytes(pdata, len);
	
	I2C_Stop();
	
	return RetVal;
}


 uint8_t Drv_IT7259_ReadBuffer32(uint32_t addr, uint8_t* pdata, int len) 
{
	uint8_t RetVal = Ret_OK;
	
	I2C_Start(); 
	
	RetVal |= I2C_WriteByte(IT7259_ADDR);	// 设备地址
	RetVal |= I2C_WriteByte(addr >> 24);			// 寄存器地址
	RetVal |= I2C_WriteByte(addr >> 16);			// 寄存器地址
	RetVal |= I2C_WriteByte(addr >> 8);			// 寄存器地址
	RetVal |= I2C_WriteByte(addr);			// 寄存器地址
	
	I2C_Start(); 
	
	RetVal |= I2C_WriteByte(IT7259_ADDR_READ);	// 读地址
	
	I2C_ReadBytes(pdata, len);
	
	I2C_Stop();
	
	return RetVal;
}


static uint16_t Drv_IT7259_CheckBusy(void)
{
	uint8_t query, RetVal;
	uint16_t i=0;

	do
	{
		SMDrv_SYS_DelayMs(5);		// 延时等待TP命令处理完
		RetVal = Drv_IT7259_ReadBuffer(QUERY_BUFFER_INDEX, &query, 1);
		i++;
		if(i>500)
			return Ret_DeviceBusy;
	}while((query & QUERY_BUSY) || (Ret_OK != RetVal));
	
	return Ret_OK;
}

// 检测触摸屏ID
static uint8_t Drv_IT7259_IdCapSensor(void)
{
	uint8_t RetVal;
	uint8_t Cmd = 0;
	uint8_t data[10];
	
	RetVal = Drv_IT7259_CheckBusy();
	if( Ret_OK != RetVal)	return RetVal;
	
	RetVal = Drv_IT7259_WriteBuffer(COMMAND_BUFFER_INDEX, &Cmd, 1);
	if( Ret_OK != RetVal)	return RetVal;
	
	RetVal = Drv_IT7259_CheckBusy();
	if( Ret_OK != RetVal)	return RetVal;

	Drv_IT7259_ReadBuffer(COMMAND_RESPONSE_BUFFER_INDEX, data, 10);
	if( Ret_OK != RetVal)	return RetVal;
	
	if(data[1] != 'I' || data[2] != 'T' || data[3] != 'E' || data[4] != '7' || data[5] != '2'  || data[6] != '5'  /* || data[7] != '9' */)
		return Ret_Fail;

	return Ret_OK;
}

// 获取触摸屏分辨率
static uint8_t Drv_IT7259_2DResolutionsGet(uint16_t *pwXResolution, uint16_t *pwYResolution, uint8_t *pucStep)
{
	uint8_t RetVal= Ret_OK;
	uint8_t cmd[2] = {0x01, 0x02};
	uint8_t data[14];
	
	RetVal = Drv_IT7259_CheckBusy();
	if( Ret_OK != RetVal)	return RetVal;
	RetVal = Drv_IT7259_WriteBuffer(COMMAND_BUFFER_INDEX, cmd, 2);
	if( Ret_OK != RetVal)	return RetVal;	

	RetVal = Drv_IT7259_CheckBusy();
	if( Ret_OK != RetVal)	return RetVal;
	RetVal = Drv_IT7259_ReadBuffer(COMMAND_RESPONSE_BUFFER_INDEX, data, 14);
	if( Ret_OK != RetVal)	return RetVal;
	
	if(pwXResolution != NULL)
		*pwXResolution = data[2] + (data[3] << 8);

	if(pwYResolution != NULL)
		*pwYResolution = data[4] + (data[5] << 8);

	if(pucStep != NULL)
		*pucStep = data[6];
	
	return Ret_OK;	
}

/*******************************************************************************
 ** Brief : 检测是否有新触摸产生
			0xC0 0b11000000，新触摸坐标产生
			0x80 0b10000000，触摸释放（手册没写，实测得出的结果：任何手势操作都会有一个释放中断）
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
static uint8_t Drv_IT7259_NewPointCheck(void)
{
	uint8_t query, RetVal = Ret_OK;
	
	RetVal = Drv_IT7259_ReadBuffer(QUERY_BUFFER_INDEX, &query, 1);
	if( Ret_OK != RetVal)	return RetVal;	
	
//	DRV_TOUCH_RTT_LOG(0,"Drv_IT7259_NewPointCheck 0x%02X \n", query);
	
	if((0x80 == query) && DrvTouch.PressIngFlg)	// 长按释放
	{
		DrvTouch.PressIngFlg = false;
		xTimerStop(DrvTouch_TimerHandle,0);
	}
	
	if (query & QUERY_POINT)  
		return 1;	
	else
		return 0;
}

// 获取触摸屏点阵信息
static uint8_t Drv_IT7259PointDataRead(uint8_t* DataBuf)
{
	uint8_t RetVal = Ret_OK;
	
	RetVal = Drv_IT7259_ReadBuffer(POINT_BUFFER_INDEX, DataBuf, 14);
	
	return RetVal;
}

// 触摸中断回调函数
static void Drv_Touch_Isr(uint32 u32PinNum)
{
	Mid_Schd_TaskMsg_T Msg;
	
	Msg.Id = eSchdTaskMsgTouch;
	Msg.Param.Touch.Type = eTouchIsrProcess;
	
	Mid_Schd_TaskEventSet(&Msg);
}

static void DrvTouch_TimerCallBack(TimerHandle_t xTimer)
{
	Mid_Schd_TaskMsg_T Msg;
	
	Msg.Id = eSchdTaskMsgTouch;
	Msg.Param.Touch.Type = eTouchGIDPress;
	Msg.Param.Touch.GID.Tap.XCoord = (DrvTouch.PointData[2] + (DrvTouch.PointData[3] << 8));
	Msg.Param.Touch.GID.Tap.YCoord = (DrvTouch.PointData[4] + (DrvTouch.PointData[5] << 8));
	
	Mid_Schd_TaskEventSet(&Msg);		
}



void Drv_Touch_Init(void)
{
	I2C_PinConfig();
	SMDrv_GPIO_Open(TOUCH_INT_PIN,NULL,Drv_Touch_Isr);
	
	DrvTouch_TimerHandle=xTimerCreate((const char*		)"DrvTouch_Timer",
									    (TickType_t			)(200/portTICK_PERIOD_MS),
							            (UBaseType_t		)pdTRUE,
							            (void*				)1,
							            (TimerCallbackFunction_t)DrvTouch_TimerCallBack); 	
	DrvTouch.PressIngFlg = false;

	#if 0	// 固件升级
	Drv_Touch_Wakeup();	
	SMDrv_SYS_DelayMs(100);	
	Upgrade_FW_CFG();	// 固件升级
	#endif
	Drv_Touch_Wakeup();	
	SMDrv_SYS_DelayMs(100);	
	
	if(Ret_OK != Drv_IT7259_IdCapSensor())
	{
		DRV_TOUCH_RTT_ERR(0,"Drv_IT7259_IdCapSensor Err \n");
	}
	SMDrv_SYS_DelayMs(10);	
	if(Ret_OK != Drv_IT7259_2DResolutionsGet(&DrvTouch.XResolution, &DrvTouch.YResolution, &DrvTouch.Scale))
	{
		DRV_TOUCH_RTT_ERR(0,"Drv_IT7259_2DResolutionsGet Err \n");
	}
	
	DRV_TOUCH_RTT_LOG(0,"Resolution(%d, %d) \n", DrvTouch.XResolution, DrvTouch.YResolution);
	
	Drv_Touch_Sleep();
}

void Drv_Touch_IsrProcess(void)
{
	DRV_TOUCH_RTT_LOG(0,"Drv_Touch_Isr \n");
	
	Mid_Schd_TaskMsg_T Msg;
	bool	ValidGIDFlg = false;

	if(Drv_IT7259_NewPointCheck())
	{
		if(Ret_OK == Drv_IT7259PointDataRead(DrvTouch.PointData))
		{
			#if 0 // 报点，打印(X ,Y)坐标
			uint16_t lXPoint, lYPoint;
			if(DrvTouch.PointData[0] & POINT_DATA_REPORT)														
			{
				lXPoint = (uint16)(DrvTouch.PointData[2] | ((DrvTouch.PointData[3]&0x0F) << 8));
				lYPoint = (uint16)(DrvTouch.PointData[4] | ((DrvTouch.PointData[3]&0xF0) << 4));
				
				DRV_TOUCH_RTT_LOG(0,"POINT_DATA_REPORT (%d, %d) \n", lXPoint, lYPoint);
			}
			#endif
			
			if(DrvTouch.PointData[0] & WAKEUP_REPORT)
			{
				DRV_TOUCH_RTT_LOG(0,"WAKEUP_REPORT \n");
				DrvTouch.State = eTouchStateActive;
				DrvTouch.IdleTimeoutCnt = 0;
			}
			
			if(DrvTouch.PointData[0] & GESTURES_REPORT)	// 手势													
			{
				switch(DrvTouch.PointData[1])
				{
					case eTouchGIDTap:	// Tap点击
						DRV_TOUCH_RTT_LOG(0,"GID Tap (%d, %d) \n", 
							DrvTouch.PointData[2] + (DrvTouch.PointData[3] << 8), DrvTouch.PointData[4] + (DrvTouch.PointData[5] << 8));
						Msg.Param.Touch.Type = eTouchGIDTap;
						Msg.Param.Touch.GID.Tap.XCoord = (DrvTouch.PointData[2] + (DrvTouch.PointData[3] << 8));
						Msg.Param.Touch.GID.Tap.YCoord = (DrvTouch.PointData[4] + (DrvTouch.PointData[5] << 8));
						ValidGIDFlg = true;
						break;
					case eTouchGIDPress:	// Press 长按
						DRV_TOUCH_RTT_LOG(0,"GID Press (%d, %d) \n", 
							DrvTouch.PointData[2] + (DrvTouch.PointData[3] << 8), DrvTouch.PointData[4] + (DrvTouch.PointData[5] << 8));
						Msg.Param.Touch.Type = eTouchGIDPress;
						Msg.Param.Touch.GID.Tap.XCoord = (DrvTouch.PointData[2] + (DrvTouch.PointData[3] << 8));
						Msg.Param.Touch.GID.Tap.YCoord = (DrvTouch.PointData[4] + (DrvTouch.PointData[5] << 8));
						ValidGIDFlg = true;
					
						DrvTouch.PressIngFlg = true;
						xTimerStart(DrvTouch_TimerHandle,3);	// 开启长按定时器，没检测到释放前，则一直发送长按事件
						break;
					case eTouchGIDFlick:	// Flick 滑动方向与规格书不符合
//						DRV_TOUCH_RTT_LOG(0,"GID Flick X(%d -> %d), Y(%d -> %d), Direction %02X \n", 
//							DrvTouch.PointData[2] + (DrvTouch.PointData[3] << 8), DrvTouch.PointData[6] + (DrvTouch.PointData[7] << 8),
//							DrvTouch.PointData[4] + (DrvTouch.PointData[5] << 8), DrvTouch.PointData[8] + (DrvTouch.PointData[9] << 8),
//							DrvTouch.PointData[10]);
						Msg.Param.Touch.Type = eTouchGIDFlick;
						Msg.Param.Touch.GID.Flick.Direction = (eTouchFlickDirection)(DrvTouch.PointData[10]);
						Msg.Param.Touch.GID.Flick.XStartCoord = (DrvTouch.PointData[2] + (DrvTouch.PointData[3] << 8));//  * 0.7364;
						Msg.Param.Touch.GID.Flick.YStartCoord = (DrvTouch.PointData[4] + (DrvTouch.PointData[5] << 8));//  * 0.7364;
						Msg.Param.Touch.GID.Flick.XEndCoord = (DrvTouch.PointData[6] + (DrvTouch.PointData[7] << 8));//  * 0.7364;
						Msg.Param.Touch.GID.Flick.YEndCoord = (DrvTouch.PointData[8] + (DrvTouch.PointData[9] << 8));//  * 0.7364;
						ValidGIDFlg = true;
						break;
					case eTouchGIDDoubleTap:	// Double-Tap 两次必须触摸同一个点才双击
//						DRV_TOUCH_RTT_LOG(0,"GID Double-Tap (%d, %d) \n", 
//							DrvTouch.PointData[2] + (DrvTouch.PointData[3] << 8), DrvTouch.PointData[4] + (DrvTouch.PointData[5] << 8));
						Msg.Param.Touch.Type = eTouchGIDTap;	// h002无双击，按单击处理
						Msg.Param.Touch.GID.Tap.XCoord = (DrvTouch.PointData[2] + (DrvTouch.PointData[3] << 8));
						Msg.Param.Touch.GID.Tap.YCoord = (DrvTouch.PointData[4] + (DrvTouch.PointData[5] << 8));
						ValidGIDFlg = true;					
						break;
					default:
						DRV_TOUCH_RTT_LOG(0,"GID Other %d \n", DrvTouch.PointData[1]);
						break;
				}
				
				/* 如果为有效触控，向上层发送触控消息 */
				if(ValidGIDFlg)
				{
					Msg.Id = eSchdTaskMsgTouch;
					Mid_Schd_TaskEventSet(&Msg);				
				}
			}
		}
	}
}

// 触摸复位（打开触摸）
void Drv_Touch_Wakeup(void)
{
	DRV_TOUCH_VDD_ON();
	vTaskDelay(1);
	
	DRV_TOUCH_RST_CLR();		// 复位等待TP初始化成功
	vTaskDelay(1);
	DRV_TOUCH_RST_SET();	

	DrvTouch.State = eTouchStateActive;
}

// 关闭触摸功能
void Drv_Touch_Sleep(void)
{
	DRV_TOUCH_RST_CLR();	// TP进入复位状态
	
	DRV_TOUCH_VDD_OFF();	// 切断TP电源
	
	DrvTouch.State = eTouchStateSleep;
}

// 发指令让TP进入IDLE模式
void Drv_Touch_Idle(void)
{
//	DRV_TOUCH_RTT_LOG(0, "Drv_Touch_Idle \n");
	
	uint8_t cmd[3] = {0x04, 0x00, 0x01};
	uint8_t data[14] = {1,2,3,4,5,6,7,8,9};

	if( Ret_OK != Drv_IT7259_CheckBusy()) 
		drERROR_CHECK_RETURN_NULL("Drv_Touch_Idle", 1);
	if( Ret_OK != Drv_IT7259_WriteBuffer(COMMAND_BUFFER_INDEX, cmd, 3))	
		drERROR_CHECK_RETURN_NULL("Drv_Touch_Idle", 2);
	
	DrvTouch.State = eTouchStateIdle;
	
	#if 0
	/** 根据规格书发送Idle指令成功后，会收到0x0000的response。
		但是实测下面这两条获取response的指令会超时，猜测TP进入休眠后不返回response
		但实测发送上面两条指令后，TP确定进入了休眠，功耗明显降低
	*/
	if( Ret_OK != Drv_IT7259_CheckBusy())
		drERROR_CHECK("Drv_Touch_Idle", 3);
	if( Ret_OK != Drv_IT7259_ReadBuffer(COMMAND_RESPONSE_BUFFER_INDEX, data, 14)) 
		drERROR_CHECK("Drv_Touch_Idle", 4);
	
	#if 1
	DRV_TOUCH_RTT_LOG(0, "Drv_Touch_Idle: ");
	for(uint32_t i = 0;i < 14;i++)
	{
		DRV_TOUCH_RTT_LOG(0, "%02X ", data[i]);
	}DRV_TOUCH_RTT_LOG(0, "\n");	
	#endif
	
	#endif
}

void Drv_Touch_Test(void)
{
	DRV_TOUCH_RTT_LOG(0, "Drv_Touch_Test \n");
	
	Drv_Touch_Idle();
}

/*******************************************************************************
 ** Brief : TP空闲超时检测，，当空闲超时时，发指令让TP进入Idle
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 500ms 秒调用一次
 ***************/
void Drv_Touch_IdleTimeoutCheck(void)
{
	if(eTouchStateActive == DrvTouch.State)
	{
		if(++DrvTouch.IdleTimeoutCnt > 2)	// 1秒后TP进入Idle
		{
			Drv_Touch_Idle();
		}
	}
}









