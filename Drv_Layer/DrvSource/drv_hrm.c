/**********************************************************************
**
**模块说明: 心率计驱动接口
**软件版本，修改日志(时间，内容),修改人:
**    
**
**********************************************************************/
//#include "string.h"
#include "io_config.h"

#if (HR_EN_PIN != IO_UNKNOW)
#include "sm_i2c.h"
#include "sm_gpio.h"

// pah8011
#include "pah_driver.h"
#include "pah_verify.h"

// pah
#include "system_clock.h"
#include "pah_driver.h"
#include "pah_hrd_function.h"
#include "pah_hrv_function.h"
#include "pah_verify.h"
#include "pah_verify_8011_option.h"
#include "pah_comm.h"
#include "pah_driver_types.h"

#include "drv_hrm.h"

typedef enum
{
    bsp_status_idle                 = 0x0000,
    bsp_status_enabled              = 0x0001,
    bsp_status_disabled             = 0x0002,
    bsp_status_started              = 0x0004,
    bsp_status_stopped              = 0x0008,
    bsp_status_factorytest_started  = 0x0010,
    bsp_status_factorytest_stopped  = 0x0020,
} bsp_status_e;


/*******************variable define*******************/
static volatile bool has_interrupt_button = false;
static volatile bool has_interrupt_pah = false;
static Drv_Hrm_Param_t	Drv_Hrm = 
	{
		.Type = eHrmMeasureHrdOnce,
		.InitFlg = false,
	};

/*******************function define*******************/
void (*BspHrmCalculateCompleteCb)(uint8 HrmValue) = NULL;									// 心率测量完成回调函数
void (*BspHrvCalculateCompleteCb)(float sdnn, float rmsd, float rri, uint8_t hr) = NULL;	// 压力测量完成回调函数
	
void (*BspHrmCalculateErrCb)(void) = NULL;		// 心率测量错误回调函数
void (*BspHrvCalculateErrCb)(void) = NULL;		// 压力测量错误回调函数


//记录mid层事件回调
hrm_event_cb Hrm_Event_CB;

// IO口中断回调函数
void hrm_isr(uint32 u32PinNum)
{
    if(u32PinNum == HR_INT1_PIN)
    {
        Hrm_Event_CB(HR_DATA_READY);
		has_interrupt_pah = true;
    }
    else if(u32PinNum == HR_INT2_PIN)
    {
        Hrm_Event_CB(HR_TOUCH);
    }
    else
    {

    }
}

/*********************************************************************
 * Brief :  配置心率计测量类型
 * Input : @Type 心率计测量类型：心率、人体压力 
 * Return:	
 * Call  : 需改变心率测量类型时调用
 ************/
void Drv_Hrm_MeasureTypeSet(eHrmMeasuretype Type)
{
	/* 若测量类型未改变且已初始化，不重复配置 */
	if((Type == Drv_Hrm.Type) && Drv_Hrm.InitFlg)
		return ;
	
	Drv_Hrm.Type = Type;
	Drv_Hrm.InitFlg = false;
}

/*********************************************************************
 * Brief :  心率模块硬件使能（I2C总线初始化、GPIO口配置）     
 * Input : @hrm_cb	回调函数
 * Return:	
 * Call  : 一般先调用 Drv_Hrm_MeasureTypeSet() 函数设置心率计测量类型，
		   再调用此函数初始化测量类型
 ************/
void Drv_Hrm_Open(hrm_event_cb hrm_cb)
{
	//power on
    SMDrv_GPIO_BitClear(HR_EN_PIN);
    SMDrv_GPIO_Open(HR_EN_PIN, NULL,NULL);

    //open iic for hrm
    SMDrv_HWI2C_Open(HR_IIC_MODULE,IIC_SPEED_HIGHEST); //MODULE 0
	
    //INT1 for data ready
    SMDrv_GPIO_Open(HR_INT1_PIN, NULL,hrm_isr);
	//INT2 for touch interrupt
	SMDrv_GPIO_Open(HR_INT2_PIN, NULL,hrm_isr);
    //set gpio isr prio
    SMDrv_GPIO_SetIrqPrio(2);

    //set mid event callback
    if(hrm_cb != NULL) Hrm_Event_CB = hrm_cb;
	
	if(false == Drv_Hrm.InitFlg)
	{
		switch (Drv_Hrm.Type)
        {
        	case eHrmMeasureHrdOnce:
			case eHrmMeasureHrdKeep:
				pah8series_ppg_dri_HRD_init();
//				DRV_HRM_RTT_LOG(0, "pah8series_ppg_dri_HRD_init \n");
        		break;
        	case eHrmMeasureHrvOnce:
			case eHrmMeasureHrvKeep:	
				pah8series_ppg_dri_HRV_init();
//				DRV_HRM_RTT_LOG(0, "pah8series_ppg_dri_HRV_init \n");
        		break;
        	default:
				drERROR_CHECK("Drv_Hrm_Open", Ret_InvalidParam);
        		break;
        }
		
		Drv_Hrm.InitFlg = true;
	}
}

//**********************************************************************
//函数功能：心率模块硬件关闭（I2C总线关闭、GPIO关闭），电源启动会造成系统电压
//          下跌，硬件关闭暂不关闭电源，但需要关闭心率算法，才能降低功耗    
//输入参数：无   
//返回参数：
// 0x00   :  操作成功
// 0xFF   :  操作失败
//**********************************************************************
void Drv_Hrm_Close(void)
{
    //power off
	//am_hal_gpio_out_bit_set(HR_EN_PIN);
    SMDrv_HWI2C_Close(HR_IIC_MODULE);

	//INT1
    SMDrv_GPIO_Close(HR_INT1_PIN);    
	//INT2    
    SMDrv_GPIO_Close(HR_INT2_PIN);
}

//**********************************************************************
//函数功能： 启动心率测量：心率模块配置、状态设置    
//输入参数： 无    
//返回参数：
// 0x00   :  操作成功
// 0x01   :  操作失败
//**********************************************************************
void Drv_Hrm_Start(void)
{
	if(false == Drv_Hrm.InitFlg) drERROR_CHECK("Drv_Hrm_Start", Ret_NoInit);  
	
	switch (Drv_Hrm.Type)
	{
		case eHrmMeasureHrdOnce:
		case eHrmMeasureHrdKeep:
			pah8series_ppg_HRD_start();
//			DRV_HRM_RTT_LOG(0, "pah8series_ppg_HRD_start \n");
			break;
		case eHrmMeasureHrvOnce:
		case eHrmMeasureHrvKeep:
			pah8series_ppg_HRV_start();
//			DRV_HRM_RTT_LOG(0, "pah8series_ppg_HRV_start \n");
			break;
		default:
			drERROR_CHECK("Drv_Hrm_Start", Ret_InvalidParam);
			break;
	}
}

//**********************************************************************
//函数功能： 关闭心率测量：关闭心率算法、设置空闲状态  
//输入参数： 无    
//返回参数：
// 0x00   :  操作成功
// 0xFF   :  操作失败
//**********************************************************************
void Drv_Hrm_Stop(void)
{    	
	if(false == Drv_Hrm.InitFlg) drERROR_CHECK("Drv_Hrm_Stop", Ret_NoInit); 	
	
	switch (Drv_Hrm.Type)
	{
		case eHrmMeasureHrdOnce:
		case eHrmMeasureHrdKeep:
			pah8series_ppg_HRD_stop();
//			DRV_HRM_RTT_LOG(0, "pah8series_ppg_HRD_stop \n");
			break;
		case eHrmMeasureHrvOnce:
		case eHrmMeasureHrvKeep:
			pah8series_ppg_HRV_stop();
//			DRV_HRM_RTT_LOG(0, "pah8series_ppg_HRV_stop \n");
			break;
		default:
			drERROR_CHECK("Drv_Hrm_Stop", Ret_InvalidParam);
			break;
	}	
}

Drv_Hrm_Param_t* Drv_Hrm_ParamPGet(void)
{
	return &Drv_Hrm;
}

//**********************************************************************
//函数功能： 工厂测试 
//输入参数： 无    
//返回参数：
// 0x00   :  操作成功
// 0xFF   :  操作失败
//**********************************************************************
uint8 Drv_Hrm_FactoryTest(uint16 ui16lightleak[3])
{
    pah_verify_adc_data_s adc_data;
    pah_ret  ret = pah_err_unknown;

    ret = pah_verify_init();
    if (PAH_FAILED(ret))
        return 0xff;

    ret = pah_verify_light_leak_read_adc_data(&adc_data);
    
    if (PAH_FAILED(ret))
        return 0xff;

    ui16lightleak[0] = adc_data.ch_adc_data[0].value;
	ui16lightleak[1] = adc_data.ch_adc_data[2].value;
	ui16lightleak[2] = adc_data.ch_adc_data[3].value;

    if (ui16lightleak[0] > PAH_LIGHT_LEAK_CH_T_MAX)
    {
       return 0xff;
    }
    if (ui16lightleak[1] > PAH_LIGHT_LEAK_CH_B_MAX)
    {
       return 0xff;
    }
    if (ui16lightleak[2] > PAH_LIGHT_LEAK_CH_C_MAX)
    {
       return 0xff;
    }
    return 0x00;
}

//**********************************************************************
//函数功能： 检测HR硬件
//输入参数： 无    
//返回参数：
// 0x00   :  操作成功
// 0xFF   :  操作失败
//**********************************************************************
uint8 Drv_Hrm_CheckHw(void)
{
    pah_ret ret = pah_err_unknown;

    ret = pah_verify_init();
    return (ret == pah_success) ? 0x00 : 0xFF;
}

//**********************************************************************
//函数功能： 读取心率模块有效触摸状态
//输入参数： 
//ui8istouch： 触摸状态指针    
//返回参数：
// 0x00   :  操作成功
// 0xFF   :  操作失败
//**********************************************************************
void Drv_Hrm_ReadTouchStatus(uint8 *ui8istouch)
{
	if(false == Drv_Hrm.InitFlg) drERROR_CHECK("Drv_Hrm_ReadTouchStatus", Ret_NoInit); 	
	
	bool TouchFlg = false;
	
	pah_read_touch_flag(&TouchFlg);
	
//    if (pah_is_touched())		
//	if(SMDrv_GPIO_InBitRead(HR_INT2_PIN))
	if (TouchFlg)
    {
        *ui8istouch = ON_TOUCH;
    }
    else
    {
        *ui8istouch = OFF_TOUCH;
    }
}

//**********************************************************************
//函数功能： 心率计算
//输入参数： 
//ui64timestamp： 曝光时间调整量   
//返回参数：
// 0x00   :  操作成功
// 0xFF   :  操作失败
//**********************************************************************
void Drv_Hrm_Calculate(uint64_t ui64timestamp)
{
	if(false == Drv_Hrm.InitFlg) drERROR_CHECK("Drv_Hrm_Calculate", Ret_NoInit);
	
	switch (Drv_Hrm.Type)
	{
		case eHrmMeasureHrdOnce:
		case eHrmMeasureHrdKeep:	
			pah8series_ppg_dri_HRD_task(&has_interrupt_pah ,&has_interrupt_button ,&ui64timestamp);
			hrd_alg_task();
			break;
		case eHrmMeasureHrvOnce:
		case eHrmMeasureHrvKeep:	
			pah8series_ppg_dri_HRV_task(&has_interrupt_pah,&has_interrupt_button ,&ui64timestamp);
			hrv_alg_task();	
			break;
		default:
			drERROR_CHECK("Drv_Hrm_Calculate", Ret_InvalidParam);
			break;
	}
}


// 设置心率计算完成回调函数
 void Drv_Hrm_SetCalCompleteCb(void (*cb)(uint8 hrmval))
{
    BspHrmCalculateCompleteCb = cb; 
}

// 设置压力计算完成回调函数
void Drv_Hrv_SetCalCompleteCb(void (*cb)(float sdnn, float rmsd, float rri, uint8_t hr))
{
    BspHrvCalculateCompleteCb = cb; 
}

// 设置心率计算错误回调函数
 void Drv_Hrm_SetCalErrCb(void (*cb)(void))
{
    BspHrmCalculateErrCb = cb; 
}

// 设置压力计算错误回调函数
 void Drv_Hrv_SetCalErrCb(void (*cb)(void))
{
    BspHrvCalculateErrCb = cb; 
}

//*******************************accelermeter*************************************//
//动态测量需要加入重力数据
#define SAMPLE_NUM_PER_CH   80
#define AXIS_SIZE           3

static int16 mems_data[SAMPLE_NUM_PER_CH * 3];

static uint16 memscnt = 0;

//**********************************************************************
//函数功能： 存储心率算法重力数据
//输入参数：     
//fifodata： 重力数据指针
//fifo_size：重力数据长度   
//返回参数：     
// 0x00   :  操作成功
// 0xFF   :  操作失败 
//**********************************************************************
uint8 Drv_Hrm_SetAccelMen(int16 *fifodata, uint16 fifo_size)
{   
    uint16 i;

    if((memscnt + fifo_size) >= (SAMPLE_NUM_PER_CH * 3))
        return 0xff;
    
    for(i = 0; i < fifo_size; i++)
    {
        mems_data[memscnt++] = fifodata[i];
    }	
	return 0x00;
}

//**********************************************************************
//函数功能： 设置重力计量程
//输入参数： 量程值：0:2G, 1:4G, 2:8G, 3:16G
//返回参数： 无
//**********************************************************************
uint8 Drv_Hrm_SetAccelRange(uint8 newrange)
{
    return 0;
}

//**********************************************************************
//函数功能： 获取心率算法重力数据
//输入参数：     
//fifodata： 重力数据指针
//fifo_size：重力数据长度（每轴的数据长度）   
//返回参数： 无
//**********************************************************************
void accelerometer_get_fifo(int16 **fifo, uint32 *fifo_size)
{
    *fifo = mems_data;
    *fifo_size = memscnt / AXIS_SIZE;
    memscnt = 0;
}

//**********************************************************************
//函数功能： 启动重力计，数据缓存清零
//输入参数： 无
//返回参数： 无
//**********************************************************************
void accelerometer_start(void)
{
    // TODO
    // accel start
    memscnt = 0;    
}

//**********************************************************************
//函数功能： 关闭重力计，数据缓存清零
//输入参数： 无
//返回参数： 无
//**********************************************************************
void accelerometer_stop(void)
{
    // TODO
    //accel stop
    memscnt = 0;
}
#endif

