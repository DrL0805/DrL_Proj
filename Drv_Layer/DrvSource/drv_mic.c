#include "string.h"
#include "io_config.h"
#include "sm_gpio.h"
#include "sm_pdm.h"
#include "drv_mic.h"


/*******************macro define*******************/
#define MIC_BUFF_SIZE                256


/*******************const define*******************/



/*******************variable define*******************/
uint32 midMicDataBuf[MIC_BUFF_SIZE];

static uint8 micFuncState;

/*******************function define*******************/

//**********************************************************************
// 函数功能:  MIC初始化
// 输入参数： 无
// 返回参数：    
// 0x00    :  初始化成功
// 0xff    :  初始化失败
//**********************************************************************
void Drv_Mic_DataCache(uint32 *buf, uint32 len)
{
	uint32 rxCnt, cacheLen;

	cacheLen = len;
	if (cacheLen > MIC_BUFF_SIZE)
	{
		cacheLen = MIC_BUFF_SIZE;
	}

	for (rxCnt = 0; rxCnt < cacheLen; rxCnt ++)
	{
		midMicDataBuf[rxCnt] = *buf++;
	}
}

//**********************************************************************
// 函数功能:  MIC初始化
// 输入参数： 无
// 返回参数：    
// 0x00    :  初始化成功
// 0xff    :  初始化失败
//**********************************************************************
uint8 Drv_Mic_Init(void)
{
	micFuncState = 0;

	for (int i = 0; i < MIC_BUFF_SIZE; i++)
	{
		midMicDataBuf[i] = 0;
	}
	SMDrv_Pdm_Init(Drv_Mic_DataCache);

	return 0;
}

//**********************************************************************
// 函数功能:  MIC采集启动
// 输入参数： 无
// 返回参数：    
// 0x00    :  操作成功
// 0xff    :  操作失败
//**********************************************************************
uint8 Drv_Mic_Sample(void)
{
	pdm_config_t pdmConfig =
	{
		.clkPinNum		= PDM_CLK,
		.dataPinNum		= PDM_DATA,
		.gain			= 0,
		.chset			= CHESET_LEFT_ONLY, //CHESET_RIGHT_ONLY,
	};

	if (!micFuncState)
	{
		SMDrv_Pdm_Open(&pdmConfig);
		micFuncState = 1;
	}
	
	SMDrv_Pdm_Start();

	return 0;
}

//**********************************************************************
// 函数功能:  MIC关闭
// 输入参数： 无
// 返回参数：    
// 0x00    :  操作成功
// 0xff    :  操作失败
//**********************************************************************
uint8 Drv_Mic_Close(void)
{
	pdm_config_t pdmConfig =
	{
		.clkPinNum		= PDM_CLK,
		.dataPinNum		= PDM_DATA,
		.gain			= 0,
		.chset			= CHESET_NONE,
	};

	SMDrv_Pdm_Stop();
	SMDrv_Pdm_Close(&pdmConfig);

	micFuncState = 0;
	return 0;
}

//**********************************************************************
// 函数功能:  MIC采集停止
// 输入参数： 无
// 返回参数：    
// 0x00    :  操作成功
// 0xff    :  操作失败
//**********************************************************************
uint8 Drv_Mic_Stop(void)
{
	SMDrv_Pdm_Stop();

	return 0;
}

//**********************************************************************
// 函数功能:  MIC采集数据获取
// 输入参数： 
// micBuf  :  缓存buf
// readLen :  读取的数据长度
// 返回参数：    
// 0x00    :  操作成功
// 0xff    :  操作失败
//**********************************************************************
uint8 Drv_Mic_DataRead(uint32 *micBuf, uint32 readLen)
{
	uint32 rCnt,rCacheLen;

	rCacheLen = readLen;

	if (rCacheLen > MIC_BUFF_SIZE)
	{
		rCacheLen = MIC_BUFF_SIZE;
	}

	for (rCnt = 0; rCnt < rCacheLen; rCnt++)
	{
		*micBuf ++ = midMicDataBuf[rCnt];
	}

	return 0;
}




