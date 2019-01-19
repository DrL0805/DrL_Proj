/**********************************************************************
**
**模块说明: 字库驱动接口
**软件版本，修改日志(时间，内容),修改人:
**   V1.0   2018.4.19  修改流程  ZSL  
**
**********************************************************************/
#define FONT_MODULE
#include "io_config.h"

#if(FONT_CS_PIN != IO_UNKNOW)
#include "sm_gpio.h"
#include "sm_spi.h"

#include "HFMA2Ylib.h"
#include "drv_font.h"

//spi max buffer length
#define SPI_BUFFER_MAX_SIZE 		(4095)

/*******************variable define*******************/
static const uint8  A_8X16_compare[16] = 
{
	0x00,0x80,0x70,0x08,0x70,0x80,0x00,0x00,0x3c,0x03,0x02,0x02,0x02,0x03,0x3c,0x00
};

//**********************************************************************
// 函数功能: 使能字库片选
// 输入参数：	
// 返回参数：无
//**********************************************************************
static void FontCs_Enable(void)
{
    SMDrv_GPIO_BitClear(FONT_CS_PIN);
}

//**********************************************************************
// 函数功能: 禁止片选
// 输入参数：	
// 返回参数：无
//**********************************************************************
static void FontCs_Disable(void)
{
    SMDrv_GPIO_BitSet(FONT_CS_PIN);
}

//**********************************************************************
// 函数功能:	flash写数据
// 输入参数：	
// *data   :    数据指针
// lenght  ：   数据长度
// 返回参数：	无
//**********************************************************************
static void FlashWriteData(uint8 *data, uint16 lenght)
{
    uint16 i;
    uint16 cnt;
    uint16 num;
    uint16 lenght_temp;
	
    //spi write at most 4095 bytes one time
    if(lenght > SPI_BUFFER_MAX_SIZE)
    {
        num 		= lenght / SPI_BUFFER_MAX_SIZE;
        cnt 		= 0;
        lenght_temp = lenght % SPI_BUFFER_MAX_SIZE;

        for(i = 0;i < num; i ++)
        {
            cnt = i * SPI_BUFFER_MAX_SIZE;
            SMDrv_SPI_WriteBytes(FONT_SPI_MODULE,&data[cnt],SPI_BUFFER_MAX_SIZE);		
        }

        cnt 		= i * SPI_BUFFER_MAX_SIZE;
        SMDrv_SPI_WriteBytes(FONT_SPI_MODULE,&data[cnt],lenght_temp);			
    }
    else
    {
        SMDrv_SPI_WriteBytes(FONT_SPI_MODULE,data,lenght);
    }
}

//**********************************************************************
// 函数功能:	flash读数据
// 输入参数：	
// *pData  ：	数据指针
// length  ： 	读的字节数
// 返回参数：	无
//**********************************************************************
static void FlashReadData(uint8 *data, uint32_t lenght)
{
    uint16 i;
    uint16 cnt;
    uint16 num;
    uint16 lenght_temp;
	
    //spi write at most 4095 bytes one time
    if(lenght > SPI_BUFFER_MAX_SIZE)
    {
        num 		= lenght / SPI_BUFFER_MAX_SIZE;
        cnt 		= 0;
        lenght_temp = lenght % SPI_BUFFER_MAX_SIZE;

        for(i = 0;i < num; i ++)
        {
            cnt = i * SPI_BUFFER_MAX_SIZE;
            SMDrv_SPI_ReadBytes(FONT_SPI_MODULE,&data[cnt],SPI_BUFFER_MAX_SIZE);		
        }

        cnt = i * SPI_BUFFER_MAX_SIZE;
        SMDrv_SPI_ReadBytes(FONT_SPI_MODULE,&data[cnt],lenght_temp);
    }
    else
    {
        SMDrv_SPI_ReadBytes(FONT_SPI_MODULE,data,lenght);
    }	
}
#endif

//**********************************************************************
// 函数功能:	字库硬件初始化
// 输入参数：	无
// 返回参数：	
// 0x00    :    初始化成功
// 0x02    :    参数错误
//**********************************************************************
uint8 Drv_Font_Open(void)
{
#if(FONT_CS_PIN != IO_UNKNOW)
    ret_type u8ret;
    uint32 u32font_conf = GPIO_PIN_OUTPUT; //default set pin as output

    //set flash cs pin as high, and open it
    if((u8ret = SMDrv_GPIO_BitSet(FONT_CS_PIN)) != Ret_OK)
        return u8ret;
    if((u8ret = SMDrv_GPIO_Open(FONT_CS_PIN,&u32font_conf,NULL)) != Ret_OK)
        return u8ret;
    
    //open spi
    if((u8ret = SMDrv_SPI_Open(FONT_SPI_MODULE)) != Ret_OK)
        return u8ret;

#endif
	return Ret_OK;
}

//**********************************************************************
// 函数功能:	字库硬件待机低功耗配置
// 输入参数：	无
// 返回参数：	
// 0x00    :    设置成功
// 0x02    :    参数错误
//**********************************************************************
uint8 Drv_Font_Close(void)
{
#if(FONT_CS_PIN != IO_UNKNOW)
    ret_type u8ret;

    if((u8ret = SMDrv_SPI_Close(FONT_SPI_MODULE)) != Ret_OK)
        return u8ret;

    #if 0
    //flash cs pin config
    if((u8ret = SMDrv_GPIO_BitSet(FONT_CS_PIN)) != Ret_OK)
        return u8ret;
    #endif
#endif
    return Ret_OK;
}

//**********************************************************************
// 函数功能:	根据汉字编码读取汉字数据流
// 输入参数：	
// GB 	   : 	汉字编码
// pdata   :  	汉字数据流指针
// 返回参数：	
// 0x00    :    操作成功
// 0xff    :    操作失败
//**********************************************************************
uint8 Drv_Font_ReadGB2313(uint16 GB, uint8 gb_size,uint8 *pdata)
{
#if(FONT_CS_PIN != IO_UNKNOW)
    switch(gb_size)
    {
		case GB_SIZE_16X16://GB_SIZE_16X16
			hzbmp16(SEL_GB, GB, 0, 16,pdata);
			break;
		case GB_SIZE_24X24://GB_SIZE_24X24
			hzbmp24(SEL_GB, GB, 0, 24,pdata);
			break;
		default:
			break;
    }
#endif
    return Ret_OK;
}

//**********************************************************************
// 函数功能:	UNICODE汉字编码转GB编码
// 输入参数：	
// unicode : 	unicode编码
// 返回参数：	GB编码
//**********************************************************************
uint16 Drv_Font_Unicode2GB(uint16 unicode)
{
	uint16_t Ret_Val;
	
	Drv_Font_SendCmd(FONT_WAKEUP_CMD);
    Ret_Val = U2G(unicode);
	Drv_Font_SendCmd(FONT_SLEEP_CMD);

	return Ret_Val;
}

//**********************************************************************
// 函数功能:	根据ASCII码读取字母数据流
// 输入参数：	
// ascii   : 	字母ASCII码
// ascii_size： 字母ASCII码点阵格式
// pdata   :  	字母据流指针
// 返回参数：	
// 0x00    :    操作成功
// 0xff    :    操作失败
//**********************************************************************
uint8 Drv_Font_ReadASCII(uint8 ascii, uint8 ascii_size, uint8 *pdata)
{
#if(FONT_CS_PIN != IO_UNKNOW)
    ASCII_GetData(ascii,ascii_size,pdata);	
#endif
    return Ret_OK;
}

//**********************************************************************
// 函数功能:	根据UI码读取UI数据流
// 输入参数：	
// ascii   : 	字母ASCII码
// ascii_size： 字母ASCII码点阵格式
// pdata   :  	字母据流指针
// 返回参数：	
// 0x00    :    操作成功
// 0xff    :    操作失败
//**********************************************************************
uint8 Drv_Font_ReadUI(uint8 uisequence, uint8 *pdata)
{
#if(FONT_CS_PIN != IO_UNKNOW)
    zz_zf(uisequence,KCD_UI_32,pdata);	
#endif
    return Ret_OK;
}

//**********************************************************************
// 函数功能：向font字库芯片发送命令
// 输入参数：
//    ft_cmd = FONT_WAKEUP_CMD: 唤醒指令
//    ft_cmd = FONT_SLEEP_CMD:  睡眠指令
// 返回参数：	0x00:操作成功
//              0x02:参数错误
//**********************************************************************
uint8 Drv_Font_SendCmd(font_cmd ft_cmd)
{
#if(FONT_CS_PIN != IO_UNKNOW)
    uint8 u8Cmd;
        
    FontCs_Enable();
    if(ft_cmd == FONT_WAKEUP_CMD)
        u8Cmd = 0xAB;
    else if(ft_cmd == FONT_SLEEP_CMD)
        u8Cmd = 0xB9;
    else
        return Ret_InvalidParam;
    SMDrv_SPI_WriteByte(FONT_SPI_MODULE,u8Cmd);
    FontCs_Disable();
#endif
    return Ret_OK;
}

//**********************************************************************
// 函数功能:	字库芯片自检
// 输入参数：	无
// 返回参数：	
// 0x00    :    自检通过
// 0x01    :    自检失败
//**********************************************************************
uint8 Drv_Font_SelfTest(void)
{
	#if 0
    uint8 i;
    uint8 DZ_Data[16];
    uint8  A_8X16_compare1[16] = 
    {
    	0x00,0x80,0x70,0x08,0x70,0x80,0x00,0x00,0x3c,0x03,0x02,0x02,0x02,0x03,0x3c,0x00
    }; 
	
	Drv_Font_Open();
	Drv_Font_SendCmd(FONT_SLEEP_CMD);
	Drv_Font_Close();

	Drv_Font_Open();
	RTT_DEBUG_printf(0,"0\n");
	Drv_Font_SendCmd(FONT_WAKEUP_CMD);
	RTT_DEBUG_printf(0,"1\n");
	Drv_Font_ReadASCII(0x41, ASCII_8X16,DZ_Data);
	RTT_DEBUG_printf(0,"2\n");
	for(i = 0; i < 16; i++)
	{
		if(DZ_Data[i] != A_8X16_compare1[i])
			break;
	}
	if(i>=16)
		RTT_DEBUG_printf(0,"OK: font\n");
	else
		RTT_DEBUG_printf(0,"Error: font read 'A'\n");
	Drv_Font_SendCmd(FONT_SLEEP_CMD);
	Drv_Font_Close();	
	#endif
	
	#if 0	// 字库flash擦写读测试
	uint8_t tWriteBuf[10], tReadBuf[10];
	
	for(uint32_t i = 0;i < 10;i++)
		tWriteBuf[i] = i+30;
	
	Drv_Font_Open();
	Drv_Font_SendCmd(FONT_WAKEUP_CMD);
	Drv_Font_Erase(0x1F0000);						
	Drv_Font_PageProgram(0x1F0000, 10, tWriteBuf);
	r_dat_bat(0x1F0000, 10 , tReadBuf);
	Drv_Font_SendCmd(FONT_SLEEP_CMD);	
	Drv_Font_Close();	
	
	RTT_DEBUG_printf(0, "Drv_Font_SelfTest: ");
	for(uint32_t i = 0;i < 10;i++)
	{
		RTT_DEBUG_printf(0, "%02X ", tWriteBuf[i]);
	}RTT_DEBUG_printf(0, "\n");	
	for(uint32_t i = 0;i < 10;i++)
	{
		RTT_DEBUG_printf(0, "%02X ", tReadBuf[i]);
	}RTT_DEBUG_printf(0, "\n");	
	#endif
	
	
	
    uint8 result = Ret_OK;
    uint8 i;
    uint8 DZ_Data[16];
	
	Drv_Font_Open();
	Drv_Font_SendCmd(FONT_WAKEUP_CMD);

    Drv_Font_ReadASCII(0x41, ASCII_8X16,DZ_Data);
    for(i = 0; i < 16; i++)
    {
        if(DZ_Data[i] != A_8X16_compare[i])
            result = Ret_Fail;
    }
	
	Drv_Font_SendCmd(FONT_SLEEP_CMD);	
	Drv_Font_Close();		
	
    return result;
}

//**********************************************************************
// 函数功能:	字库芯片初始化，并控制其进入休眠模式
// 输入参数：	无
// 返回参数：	00H初始化成功，其他值初始化失败
//**********************************************************************
uint8 Drv_Font_Init(void)
{		
	#if 1
    uint8 result = Ret_OK;
#if(FONT_CS_PIN != IO_UNKNOW)
	result= Drv_Font_Open();
	if(Ret_OK != result) return result;
	
	result= Drv_Font_SendCmd(FONT_SLEEP_CMD);
	if(Ret_OK != result) return result;
	
	result= Drv_Font_Close();
	if(Ret_OK != result) return result;
#endif
    return result;
	#endif
}






// **********************************************************************
// 字库flash读写函数 ****************************************************
// **********************************************************************


/*********************************************************************
 * Brief : 检测字库芯片状态
 * Input : NULL
 * Output: NULL
 * Return: NULL
 ************/
static void Drv_Font_checkStatus(void)
{
	uint8_t tWriteBuf[1] = {0x05};
	uint8_t tReadBuf[1];
	
	FontCs_Enable();
	SMDrv_SPI_WriteBytes(FONT_SPI_MODULE,tWriteBuf, 1);
	while(1)
	{
		 SMDrv_SPI_ReadBytes(FONT_SPI_MODULE, tReadBuf, 1);
	 	 if((tReadBuf[0] & 0x01)==0x00)
			break;
	}
	FontCs_Disable();
}

/*********************************************************************
 * Brief : 写使能
 * Input : NULL
 * Output: NULL
 * Return: NULL
 ************/
static void Drv_Font_WriteEnable(void)
{
	uint8_t tWriteBuf[1] = {0x06};
	
	FontCs_Enable();
	SMDrv_SPI_WriteBytes(FONT_SPI_MODULE,tWriteBuf, 1);
	FontCs_Disable();
}

/*********************************************************************
 * Brief : 读字库数据
 * Input : NULL
 * Output: NULL
 * Return: NULL
 ************/
void r_dat_bat(unsigned long TAB_addr,unsigned int Num,unsigned char *p_arr)
{
    uint8 data[4];
    data[3] = (uint8)TAB_addr;
    data[2] = (uint8)(TAB_addr >> 8);
    data[1] = (uint8)(TAB_addr >> 16);
    data[0] = 0x03;

    FontCs_Enable();
    FlashWriteData(data, 4);
    FlashReadData(p_arr,Num);
    FontCs_Disable();
}

/*********************************************************************
 * Brief : 写数据到字库
 * Input : NULL
 * Output: NULL
 * Return: NULL
 ************/
void Drv_Font_PageProgram(unsigned long address,unsigned int number,unsigned char *p)
{
    uint8 data[4];
    data[3] = (uint8)address;
    data[2] = (uint8)(address >> 8);
    data[1] = (uint8)(address >> 16);
    data[0] = 0x02;

	Drv_Font_WriteEnable();
    FontCs_Enable();
    FlashWriteData(data, 4);
	FlashWriteData(p, number);
    FontCs_Disable();
	Drv_Font_checkStatus();	
}

/*********************************************************************
 * Brief : 块擦除
 * Input : NULL
 * Output: NULL
 * Return: NULL
 ************/
void Drv_Font_Erase(unsigned long address)
{
    uint8 data[4];
    data[3] = (uint8)address;
    data[2] = (uint8)(address >> 8);
    data[1] = (uint8)(address >> 16);
    data[0] = 0x20;

	Drv_Font_WriteEnable();
    FontCs_Enable();
    FlashWriteData(data, 4);
    FontCs_Disable();
	Drv_Font_checkStatus();
}















