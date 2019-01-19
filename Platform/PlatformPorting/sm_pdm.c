#include "io_config.h"
#include "am_mcu_apollo.h"
#include "am_util_delay.h"
#include "sm_gpio.h"
#include "sm_pdm.h"






/*******************macro define*******************/
#define PDM_BUFF_SIZE                256
#define PDM_BUFF_BYTES               (PDM_BUFF_SIZE * 1)


/*******************variable define*******************/
volatile bool g_bPDMDataReady = true;

uint32  ui32PDMDataBuffer[PDM_BUFF_SIZE];
uint32  ui32PDMDataBufferCnt;
void *PDMHandle;

pdm_DataReady_Cb pdmDataReadyCallBack;


/*******************function define*******************/

//**********************************************************************
// 函数功能:    初始化
// 输入参数：    无
// 返回参数：    
// 0x00    :    初始化成功
// 0xff    :    初始化失败
//**********************************************************************
ret_type SMDrv_Pdm_Init(pdm_DataReady_Cb cb)
{
    ui32PDMDataBufferCnt = 0;

    pdmDataReadyCallBack = cb;

    for (int i = 0; i < PDM_BUFF_SIZE; ++i)
    {
        ui32PDMDataBuffer[i] = 0;
    }
    
    return Ret_OK;
}

//**********************************************************************
// 函数功能:    PDM总线开启
// 输入参数：    无
// 返回参数：    
// 0x00    :    初始化成功
// 0xff    :    初始化失败
//**********************************************************************
ret_type SMDrv_Pdm_Open(pdm_config_t *pdmConfig)
{	
	am_hal_pdm_gain_e 	gainval;
	am_hal_pdm_chset_e  chset;
	am_hal_gpio_pincfg_t gpioConfig = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	
	if (pdmConfig->gain <= 0)
	{
		gainval = AM_HAL_PDM_GAIN_0DB;
	}
	else if (pdmConfig->gain <= 250)
	{
		gainval = AM_HAL_PDM_GAIN_P150DB;
	}
	else
	{
		gainval = AM_HAL_PDM_GAIN_P405DB;
	}

	if (pdmConfig->chset == CHESET_RIGHT_ONLY)
	{
		chset = AM_HAL_PDM_CHANNEL_RIGHT;
	}
	else if (pdmConfig->chset == CHESET_LEFT_ONLY)
	{
		chset = AM_HAL_PDM_CHANNEL_LEFT;
	}
	else
	{
		chset = AM_HAL_PDM_CHANNEL_STEREO;
	}

	//PDM配置信息
	am_hal_pdm_config_t g_sPdmConfig =
	{
	    .eClkDivider 		= AM_HAL_PDM_MCLKDIV_1,
	    .eLeftGain 			= gainval,
	    .eRightGain 		= gainval,
	    .ui32DecimationRate = 64,
	    .bHighPassEnable 	= 0,
	    .ui32HighPassCutoff = 0xB,
	    .ePDMClkSpeed 		= AM_HAL_PDM_CLK_1_5MHZ,//AM_HAL_PDM_CLK_6MHZ,
	    .bInvertI2SBCLK 	= 0,
	    .ePDMClkSource 		= AM_HAL_PDM_INTERNAL_CLK,
	    .bPDMSampleDelay 	= 0,
	    .bDataPacking 		= 1,
	    .ePCMChannels 		= chset,
	    .bLRSwap 			= 0,
	};

    am_hal_pdm_initialize(0, &PDMHandle);
    am_hal_pdm_power_control(PDMHandle, AM_HAL_PDM_POWER_ON, false);
    am_hal_pdm_configure(PDMHandle, &g_sPdmConfig);
    am_hal_pdm_enable(PDMHandle);

    //gpio config
    //gpioConfig.eDriveStrength      = AM_HAL_GPIO_PIN_DRIVESTRENGTH_2MA;
    if (pdmConfig->clkPinNum == PDMCLK_10)
    {
    	gpioConfig.uFuncSel = AM_HAL_PIN_10_PDMCLK;
    }
    else if (pdmConfig->clkPinNum == PDMCLK_12)
    {
    	gpioConfig.uFuncSel = AM_HAL_PIN_12_PDMCLK;
    }
    else if (pdmConfig->clkPinNum == PDMCLK_14)
    {
    	gpioConfig.uFuncSel = AM_HAL_PIN_14_PDMCLK;
    }
	else if (pdmConfig->clkPinNum == PDMCLK_22)
    {
    	gpioConfig.uFuncSel = AM_HAL_PIN_22_PDMCLK;
    }
	else if (pdmConfig->clkPinNum == PDMCLK_37)
    {
    	gpioConfig.uFuncSel = AM_HAL_PIN_37_PDMCLK;
    }
    else if (pdmConfig->clkPinNum == PDMCLK_46)
    {
    	gpioConfig.uFuncSel = AM_HAL_PIN_46_PDMCLK;
    }
    else
    {
    	return Ret_InvalidParam;
    }    
    am_hal_gpio_pinconfig(pdmConfig->clkPinNum, gpioConfig);

    if (pdmConfig->dataPinNum == PDMDATA_11)
    {
    	gpioConfig.uFuncSel = AM_HAL_PIN_11_PDMDATA;
    }
    else if (pdmConfig->dataPinNum == PDMDATA_15)
    {
    	gpioConfig.uFuncSel = AM_HAL_PIN_15_PDMDATA;
    }
    else if (pdmConfig->dataPinNum == PDMDATA_29)
    {
    	gpioConfig.uFuncSel = AM_HAL_PIN_29_PDMDATA;
    }
	else if (pdmConfig->dataPinNum == PDMDATA_34)
    {
    	gpioConfig.uFuncSel = AM_HAL_PIN_34_PDMDATA;
    }
	else if (pdmConfig->dataPinNum == PDMDATA_36)
    {
    	gpioConfig.uFuncSel = AM_HAL_PIN_36_PDMDATA;
    }
    else if (pdmConfig->dataPinNum == PDMDATA_45)
    {
    	gpioConfig.uFuncSel = AM_HAL_PIN_45_PDMDATA;
    }
    else
    {
    	return Ret_InvalidParam;
    }    
    am_hal_gpio_pinconfig(pdmConfig->dataPinNum, gpioConfig);
	
    //interrupt config
    am_hal_pdm_interrupt_enable(PDMHandle, (AM_HAL_PDM_INT_DERR
                                            | AM_HAL_PDM_INT_DCMP
                                            | AM_HAL_PDM_INT_UNDFL
                                            | AM_HAL_PDM_INT_OVF));
#if AM_CMSIS_REGS
    NVIC_EnableIRQ(PDM_IRQn);
#else
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_PDM);
#endif

     am_hal_pdm_fifo_flush(PDMHandle);

    return Ret_OK;
}


//**********************************************************************
// 函数功能:    PDM总线关闭
// 输入参数：    无
// 返回参数：    
// 0x00    :    初始化成功
// 0xff    :    初始化失败
//**********************************************************************
ret_type SMDrv_Pdm_Close(pdm_config_t *pdmConfig)
{
	am_hal_pdm_disable(PDMHandle);
	am_hal_pdm_deinitialize(&PDMHandle);
    am_hal_pdm_power_control(PDMHandle, AM_HAL_PDM_POWER_OFF, false);

    am_hal_gpio_pinconfig(pdmConfig->clkPinNum, SM_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(pdmConfig->dataPinNum, SM_AM_HAL_GPIO_DISABLE);
    return Ret_OK;
}

//**********************************************************************
// 函数功能:    PDM总线启动数据传输
// 输入参数：    无
// 返回参数：    
// 0x00    :    初始化成功
// 0xff    :    初始化失败
//**********************************************************************
ret_type SMDrv_Pdm_Start(void)
{	
	// Configure DMA and target address.
    am_hal_pdm_transfer_t sTransfer;

    if (g_bPDMDataReady == true)
    {
        g_bPDMDataReady = false;
        sTransfer.ui32TargetAddr = (uint32_t ) ui32PDMDataBuffer;
        sTransfer.ui32TotalCount = PDM_BUFF_BYTES;

        // Start the data transfer.
        am_hal_pdm_enable(PDMHandle);

         am_util_delay_ms(1);
         am_hal_pdm_fifo_flush(PDMHandle);
        am_hal_pdm_dma_start(PDMHandle, &sTransfer);
    }

	return Ret_OK;
}

//**********************************************************************
// 函数功能:    PDM总线暂停数据传输
// 输入参数：    无
// 返回参数：    
// 0x00    :    初始化成功
// 0xff    :    初始化失败
//**********************************************************************
ret_type SMDrv_Pdm_Stop(void)
{  
   am_hal_pdm_disable(PDMHandle);

    return Ret_OK;
}

//*****************************************************************************
//
// PDM interrupt handler.
//
//*****************************************************************************
void am_pdm_isr(void)
{
    uint32_t ui32Status;

    //
    // Read the interrupt status.
    //
    am_hal_pdm_interrupt_status_get(PDMHandle, &ui32Status, true);
    am_hal_pdm_interrupt_clear(PDMHandle, ui32Status);

    //
    // Once our DMA transaction completes, we will disable the PDM and send a
    // flag back down to the main routine. Disabling the PDM is only necessary
    // because this example only implemented a single buffer for storing FFT
    // data. More complex programs could use a system of multiple buffers to
    // allow the CPU to run the FFT in one buffer while the DMA pulls PCM data
    // into another buffer.
    //
    if (ui32Status & AM_HAL_PDM_INT_DCMP)
    {
        am_hal_pdm_disable(PDMHandle);
        pdmDataReadyCallBack(ui32PDMDataBuffer,PDM_BUFF_SIZE);
        g_bPDMDataReady = true;
    }
}





