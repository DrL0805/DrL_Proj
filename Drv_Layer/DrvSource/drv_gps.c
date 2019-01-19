
#include "bsp_common.h"
#include "drv_gps.h"
#include "mid_rtc.h"		// #include "mid_rtc.h"放在下面会错误 error:  #18: expected a ")"，原因未知
#include "sm_gpio.h"
#include "sm_uart.h"
#include "mid_uart.h"
//#include "app_task.h"
#include "store_gps.h"
#include "mid_scheduler.h"


//uint8_t gps_GCD_cmd[]  = "@GCD\r\n";       	 	//冷启动
//uint8_t gps_BSSL_cmd[] = "@BSSL 0xB\r\n";  		//NMEA数据格式选择
//uint8_t gps_GSTP_cmd[] = "@GSTP\r\n";
//uint8_t gps_ABPT_cmd[] = "@ABPT 1\r\n";    		//自动备份数据，IDLE模式下发送，1到1440min,默认60min
//uint8_t gps_ABUP_cmd[] = "@ABUP 1\r\n";    		//自动备份数据，IDLE模式下使用，打开或者关闭OFF
//uint8_t gps_BUP_cmd[]  = "@BUP \r\n";       		//备份 hot启动需要的信息和其它信息。IDLE下使用
//uint8_t gps_BUPC_cmd[] = "@BUPC\r\n";      		//清清除flash中的备份信息，IDLE下使用
//uint8_t gps_CSBR_cmd[] = "@CSBR 38400\r\n";		//UART波特率设置
//uint8_t gps_FER_cmd[]  = "@FER\r\n";        		//Falsh擦除，IDLE下使用
//uint8_t gps_GALG_cmd[] = "@GALG\r\n";     		//GPS almanac data 获取，IDLE下用
//uint8_t gps_GALS_cmd[] = "@ALS\r\n";       		//GPS almanac data injection, 只能在 IDLE下用
//uint8_t gps_GEMG_cmd[] = "@GEMG\r\n";    			//
//uint8_t gps_GEMS_cmd[] = "@GEMS\r\n";      		//
//uint8_t gps_GNS_cmd[]  = "@GNS 0x01\r\n";   		//
//uint8_t gps_GPOE_cmd[] = "@GPOE x x x x x x\r\n";
//uint8_t gps_GPOS_cmd[] = "@GPOS x x x\r\n";    			//
//uint8_t gps_GPPS_cmd[] = "@GPPS \r\n";      		//
//uint8_t gps_GPTC_cmd[] = "@GPTC\r\n";   		//
//uint8_t gps_GSOP_cmd[] = "@GSOP x x x\r\n"; 
//uint8_t gps_GSP_cmd[]  = "@GSP\r\n";    			//
//uint8_t gps_GSW_cmd[]  = "@GSW\r\n";      		//
//uint8_t gps_GTCX_cmd[] = "@TCX x\r\n";   		//

//uint8_t gps_GUSE_cmd[] = "@GUSE x\r\n";    			//
//uint8_t gps_VER_cmd[]  = "@VER\r\n";      		//
//uint8_t gps_SLP_cmd[]  = "@SLP x\r\n";   		//
//uint8_t gps_WUP_cmd[]  = "@WUP\r\n"; 

//char gps_CEPA_cmd[] = "@CEPA\r\n";
//char gps_CEPE_cmd[] = "@CEPE\r\n";
//char gps_CEPW_cmd[] = "@CEPW n\r\n";


//char gps_GCD_return[] = {"\xA5\x0F\x0D[GCD] Done"};
//char gps_GSR_return[] = {"\xA5\x0F\x0D[GSR] Done"};
//char gps_BSSL_return[] = {"\xA5\x0F\x0D[BSSL] Done"};
//char gps_GSTP_return[] = {"\xA5\x0F\x0D[GSTP] Done"};
//char gps_ABPT_return[] = {"\xA5\x0F\x0D[ABPT] Done"};
//char gps_ABUP_return[] = {"\xA5\x0F\x0D[ABUP] Done"};
//char gps_BUP_return[] = {"\xA5\x0F\x0D[BUP] Done"};
//char gps_BUPC_return[] = {"\xA5\x0F\x0D[BUPC] Done"};
//char gps_CSBR_return[] = {"\xA5\x0F\x0D[CSBR] Done"};
//char gps_FER_return[] = {"\xA5\x0F\x0D[FER] Done"};
//char gps_GALG_return[] = {"\xA5\x0F\x0D[GALG] Done"};
//char gps_GALS_return[] = {"\xA5\x0F\x0D[GALS] Done"};
//char gps_GEMG_return[] = {"\xA5\x0F\x0D[GEMG] Done"};
//char gps_GEMS_return[] = {"\xA5\x0F\x0D[GEMS] Done"};
//char gps_GNS_return[] = {"\xA5\x0F\x0D[GNS] Done"};
//char gps_GPOE_return[] = {"\xA5\x0F\x0D[GPOE] Done"};
//char gps_GPOS_return[] = {"\xA5\x0F\x0D[GPOS] Done"};
//char gps_GPPS_return[] = {"\xA5\x0F\x0D[GPPS] Done"};
//char gps_GPTC_return[] = {"\xA5\x0F\x0D[GPTC] Done"};
//char gps_GSOP_return[] = {"\xA5\x0F\x0D[GSOP] Done"};
//char gps_GSP_return[] = {"\xA5\x0F\x0D[GSP] Done"};
//char gps_GSW_return[] = {"\xA5\x0F\x0D[GSW] Done"};
//char gps_GTCX_return[] = {"\xA5\x0F\x0D[GTCX] Done"};
//char gps_GTIM_return[] = {"\xA5\x0F\x0D[GTIM] Done"};
//char gps_GUSE_return[] = {"\xA5\x0F\x0D[GUSE] Done"};
//char gps_VER_return[] = {"\xA5\x0F\x0D[VER] Done"};
//char gps_SLP_return[] = {"\xA5\x0F\x0D[SLP] Done"};
//char gps_WUP_return[] = {"\xA5\x0F\x0D[WUP] Done"};


//char gps_CEPA_return[] = {"\xA5\x0F\x0D[CEPA] Done"};
//char gps_CEPE_return[] = {"\xA5\x0F\x0D[CEPE] Done"};
//char gps_CEPW_R_return[] = {"\xA5\x0F\x0D[CEPW] Ready"};
//char gps_CEPW_D_return[] = {"\xA5\x0F\x0D[CEPW] Done"};

#define GPS_EN_PIN      46    	// GPS整体电源，低电平供电
#define GPS_1_8_EN_PIN	44		// GPS 1.8V 供电，高电平供电
#define GPS_0_7_EN_PIN	10		// GPS 0.7V 供电，高电平供电

#define UART_TX_BUF_SIZE 256 /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE 256 /**< UART RX buffer size. */

#define GPS_PWR_ON()			am_hal_gpio_output_clear(GPS_EN_PIN)
#define GPS_PWR_OFF()			am_hal_gpio_output_set(GPS_EN_PIN)
#define GPS_PWR_1_8V_ON()		am_hal_gpio_output_set(GPS_1_8_EN_PIN)
#define GPS_PWR_1_8V_OFF()		am_hal_gpio_output_clear(GPS_1_8_EN_PIN)
#define GPS_PWR_0_7V_ON()		am_hal_gpio_output_set(GPS_0_7_EN_PIN)
#define GPS_PWR_0_7V_OFF()		am_hal_gpio_output_clear(GPS_0_7_EN_PIN)

TimerHandle_t 	GPS_TimerHandle;
DrvGPSParam_t	DrvGPSParam;

DRV_GPS_PART_T	GPS_PART;
DRV_GPS_GSV_T	GPS_GSV;
DRV_GPS_RMC_T	GPS_RMC;

/*******************************************************************************
 ** Brief : 
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
static void Drv_GPS_TimerCb(TimerHandle_t xTimer)
{
	DRV_GPS_RTT_LOG(0, "Drv_GPS_TimerCb \n");
	
	Mid_Schd_TaskMsg_T Msg;
	
	Msg.Id = eSchdTaskMsgGPS;
	Msg.Param.GPS.Id = DrvGPSParam.Operate.Id;
	switch (DrvGPSParam.Operate.Step)
    {
    	case eGPSColdStartProcessPwrOn:	// 上电延时2000ms到后，开始发送指令
			DrvGPSParam.Operate.Step = eGPSColdStartProcessCmdGCD;
			Mid_Schd_TaskEventSet(&Msg);
    		break;
		case eGPSHotStartProcessPwrOn:	// 上电延时2000ms到后，开始发送指令
			DrvGPSParam.Operate.Step = eGPSHotStartProcessCmdGTIM;
			Mid_Schd_TaskEventSet(&Msg);
    		break;
    	default :
    		break;
    }
}

/*******************************************************************************
 ** Brief : GPS串口数据回调，收到GPS串口数据后，发送事件解析GPS数据
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
static void Drv_GPS_UartCb(uint32 uart_event)
{
//	RTT_DEBUG_printf(0,"Drv_GPS_UartCb %d \n", uart_event);
	
	#if 1	// 不区分类型，只要串口有数据回调，均发送事件
	Mid_Schd_TaskMsg_T Msg;
	
	Msg.Id = eSchdTaskMsgUart;
	Msg.Param.Uart.Module = GPS_UART_MODULE;
	Msg.Param.Uart.EventType = UART_EVENT_RX_TIMEOUT;
	Mid_Schd_TaskEventSet(&Msg);	
	#endif
	
	#if 0
	Mid_Schd_TaskMsg_T Msg;
	
    if(uart_event == UART_EVENT_RX_TIMEOUT)
	{
		Msg.Id = eSchdTaskMsgUart;
		Msg.Param.Uart.Module = GPS_UART_MODULE;
		Msg.Param.Uart.EventType = UART_EVENT_RX_TIMEOUT;
        Mid_Schd_TaskEventSet(&Msg);
	}else if(uart_event == UART_EVENT_RX)
	{
		Msg.Id = eSchdTaskMsgUart;
		Msg.Param.Uart.Module = GPS_UART_MODULE;
		Msg.Param.Uart.EventType = UART_EVENT_RX_TIMEOUT;
        Mid_Schd_TaskEventSet(&Msg);		
	}
	#endif
}

/*******************************************************************************
 ** Brief : 通过串口向GPS发送命令
 ** Input : @Cmd 命令数组 
			@CmdLen 命令长度
 ** Return: @NULL
 ** Call  : 
 ***************/
static void Drv_GPS_SendCmd(char *Cmd, uint8_t CmdLen)
{
	Mid_Uart_Send(1, (uint8_t*)Cmd, CmdLen);	
}

/*******************************************************************************
 ** Brief : GPS唤醒
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
static void Drv_GPS_Wakeup(void)
{
	SMDrv_UART_Open(GPS_UART_MODULE,Drv_GPS_UartCb);	// 打开UART产生4mA+功耗
	
	GPS_PWR_ON();
	GPS_PWR_1_8V_ON();
	GPS_PWR_0_7V_ON();			// 给GPS供电产生970uA功耗
	
//	vTaskDelay(3000);		// 延时确保上电稳定，至少大于2000ms
}

/*******************************************************************************
 ** Brief : GPS休眠，进入低功耗状态
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
static void Drv_GPS_Sleep(void)
{
	GPS_PWR_OFF();	
	GPS_PWR_1_8V_OFF();
	GPS_PWR_0_7V_OFF();	
	
	SMDrv_UART_Close(GPS_UART_MODULE);	// 初始化完后关闭串口，节省功耗
}

/*******************************************************************************
 * Brief : 冷启动流程
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ***************/
static void DRV_GPS_ColdStartProcess(void)
{
	char gps_GCD_cmd[]  = "@GCD\r\n";       	 	//冷启动

	switch (DrvGPSParam.Operate.Step)
    {
    	case eGPSColdStartProcessPwrOn:
			DRV_GPS_RTT_LOG(0, "eGPSColdStartProcessPwrOn \n");
			Drv_GPS_Wakeup();
			xTimerChangePeriod(GPS_TimerHandle, pdMS_TO_TICKS(2000), 3);	// 打开GPS电源后，等待2000ms，让GPS从FLASH读取数据到RAM
    		break;
    	case eGPSColdStartProcessCmdGCD:
			DRV_GPS_RTT_LOG(0, "eGPSIdleProcessCmdBUP \n");
			Drv_GPS_SendCmd(gps_GCD_cmd, (sizeof(gps_GCD_cmd)-1));		
    		break;
    	default :
			drERROR_CHECK("DRV_GPS_ColdStartProcess", Ret_InvalidParam);
    		break;
    }
}

/*******************************************************************************
 * Brief : GPS热启动处理过程，完全按照官方流程
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void DRV_GPS_HotStartProcess(void)
{
//	char gps_GSR_cmd[]  = "@GSR\r\n";
//	char gps_GTIM_cmd[] = "@GTIM 2013 02 01 13 30 30\r\n";	// 2013/2/1 13:30:30
//	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
//	rtc_time_s	lZeroZoneRTC;	// 零（伦敦）时区RTC

//	switch (DrvGPSParam.Operate.Step)
//    {
//    	case eGPSHotStartProcessPwrOn: /* 打开GPS电源 */
//			DRV_GPS_RTT_LOG(0, "eGPSHotStartProcessPwrOn \n");
//			GPS_PWR_ON();
//			vTaskDelay(2);
//			
//			GPS_PWR_1_8V_ON();
//			vTaskDelay(2);
//			
//			GPS_PWR_0_7V_ON();
			Drv_GPS_Wakeup();
	
//			xTimerChangePeriod(GPS_TimerHandle, pdMS_TO_TICKS(2000), 3);	// 打开GPS电源后，等待2000ms，让GPS从FLASH读取数据到RAM				
//    		break;
//    	case eGPSHotStartProcessCmdGTIM: /* @GTIM， 设置当前UTC时间，发送UTC热启动才有效 */
//			DRV_GPS_RTT_LOG(0, "eGPSHotStartProcessCmdGTIM \n");
////			TimeZoneTransform(&lMidRTC->RTC, &lZeroZoneRTC);
//			sprintf(gps_GTIM_cmd+8, "%02d",lZeroZoneRTC.year);
//			sprintf(gps_GTIM_cmd+11,"%02d",lZeroZoneRTC.month);
//			sprintf(gps_GTIM_cmd+14,"%02d",lZeroZoneRTC.day);
//			sprintf(gps_GTIM_cmd+17,"%02d",lZeroZoneRTC.hour);
//			sprintf(gps_GTIM_cmd+20,"%02d",lZeroZoneRTC.min);
//			sprintf(gps_GTIM_cmd+23,"%02d",lZeroZoneRTC.sec);		
//			for(uint32_t i = 0;i < 5;i++)
//				gps_GTIM_cmd[10+i*3] = ' ';	// 补空格
//			gps_GTIM_cmd[25] = '\r';		// 补充 \r符号
//	
//			#if 1	// debug
//			DRV_GPS_RTT_LOG(0, "gps_GTIM_cmd %s", gps_GTIM_cmd);
//			#endif
//			Drv_GPS_SendCmd(gps_GTIM_cmd, (sizeof(gps_GTIM_cmd)-1));
//    		break;
//		case eGPSHotStartProcessCmdGSR: /* @GSR，时间精确位置其次的热启动方式 */
//			DRV_GPS_RTT_LOG(0, "eGPSHotStartProcessCmdGSR \n");
//			Drv_GPS_SendCmd(gps_GSR_cmd, (sizeof(gps_GSR_cmd)-1));
//			DrvGPSParam.State = eGPSStateHotStart;
//    		break;
//    	default :
//			DRV_GPS_RTT_LOG(0, "[ERR] DRV_GPS_HotStartProcess \n");
//    		break;
//    }
}

/*******************************************************************************
 * Brief : GPS关闭过程，完全按照官方流程
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ***************/
static void DRV_GPS_IdleProcess(void)
{
	char gps_GSTP_cmd[] = "@GSTP\r\n";	
	char gps_BUP_cmd[]  = "@BUP \r\n";       		//备份 hot启动需要的信息和其它信息。IDLE下使用

	switch (DrvGPSParam.Operate.Step)
    {
    	case eGPSIdleProcessCmdGSTP:		/* @GSTP， 停止GPS，进入IDLE模式*/
			DRV_GPS_RTT_LOG(0, "eGPSIdleProcessCmdGSTP \n");
			Drv_GPS_SendCmd(gps_GSTP_cmd, (sizeof(gps_GSTP_cmd)-1));
    		break;
    	case eGPSIdleProcessCmdBUP: 		/* @BUP，位置信息存入FLASH，后续热启动需要 */
			DRV_GPS_RTT_LOG(0, "eGPSIdleProcessCmdBUP \n");
			Drv_GPS_SendCmd(gps_BUP_cmd, (sizeof(gps_BUP_cmd)-1));	
    		break;
		case eGPSIdleProcessPwrOff: 		/* 断电 */ 
			DRV_GPS_RTT_LOG(0, "eGPSIdleProcessPwrOff \n");
			DrvGPSParam.State = eGPSStateIdle;
			Drv_GPS_Sleep();
    		break;
    	default :
			DRV_GPS_RTT_LOG(0, "[ERR] DRV_GPS_IdleProcess \n");
    		break;
    }
}

/*******************************************************************************
 ** Brief : GPS初始化
 ** Input : @NULL
 ** Return: @NULL
 ** Call  : 
 ***************/
void Drv_GPS_Init(void)
{
	SMDrv_UART_Open(GPS_UART_MODULE,Drv_GPS_UartCb);	// 打开UART产生4mA+功耗
	SMDrv_UART_SetIsrPrio(GPS_UART_MODULE, 3);
	SMDrv_UART_EnableIrq(GPS_UART_MODULE, UART_EVENT_RX|UART_EVENT_RX_TIMEOUT,TRUE);	
	SMDrv_UART_Close(GPS_UART_MODULE);	// 初始化完后关闭串口，节省功耗
	
	SMDrv_GPIO_Open(GPS_0_7_EN_PIN, NULL, NULL);
	SMDrv_GPIO_Open(GPS_1_8_EN_PIN, NULL, NULL);
	SMDrv_GPIO_Open(GPS_EN_PIN, NULL, NULL);
	
	/*
		开启定时器：	xTimerChangePeriod(GPS_TimerHandle, pdMS_TO_TICKS(TimerMs), 3);
		停止定时器：	xTimerStop(GPS_TimerHandle,3);
	*/
    GPS_TimerHandle=xTimerCreate((const char*		)"GPS_Timer",
								(TickType_t			)(100/portTICK_PERIOD_MS),
								(UBaseType_t		)pdFALSE,	// pdFALSE ，单次，pdTRUE 周期
								(void*				)1,
								(TimerCallbackFunction_t)Drv_GPS_TimerCb);
	DrvGPSParam.InitFlg = true;
	DrvGPSParam.SearchingCnt = 0;
	DrvGPSParam.State = eGPSStateIdle;
	
	Drv_GPS_Sleep();
}


void Drv_GPS_ColdStart(void)
{		
	/* 参数初始化 */
	for(uint32_t i = 0;i < GPS_GSV_SV_MAX;i++)
	{
		GPS_GSV.SatelliteInfo[i].ID = 0;
		GPS_GSV.SatelliteInfo[i].Elevation = 0;
		GPS_GSV.SatelliteInfo[i].Azimuth = 0;
		GPS_GSV.SatelliteInfo[i].SNR = 0;
	}
	GPS_RMC.Lon = 0;	
	GPS_RMC.Lat = 0;
	DrvGPSParam.SearchingCnt = 0;
	DrvGPSParam.State = eGPSStateColdStart;

	DrvGPSParam.Operate.Id = eGPSEventColdStart;
	DrvGPSParam.Operate.Step = eGPSColdStartProcessPwrOn;
	DrvGPSParam.Operate.Result = GPSProcessResultSuc;
	DRV_GPS_ColdStartProcess();	
}

/*******************************************************************************
 * Brief : GPS热启动
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Drv_GPS_HotStart(void)
{
	/* 参数初始化 */
	for(uint32_t i = 0;i < GPS_GSV_SV_MAX;i++)
	{
		GPS_GSV.SatelliteInfo[i].ID = 0;
		GPS_GSV.SatelliteInfo[i].Elevation = 0;
		GPS_GSV.SatelliteInfo[i].Azimuth = 0;
		GPS_GSV.SatelliteInfo[i].SNR = 0;
	}
	GPS_RMC.Lon = 0;	
	GPS_RMC.Lat = 0;
	DrvGPSParam.SearchingCnt = 0;

	DrvGPSParam.Operate.Id = eGPSEventHotStart;
	DrvGPSParam.Operate.Step = eGPSHotStartProcessPwrOn;
	DrvGPSParam.Operate.Result = GPSProcessResultSuc;
	DRV_GPS_HotStartProcess();	
}

/*******************************************************************************
 * Brief : GPS关闭
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Drv_GPS_Idle(void)
{
	DrvGPSParam.SearchingCnt = 0;
	
	DrvGPSParam.Operate.Id = eGPSEventIdle;
	DrvGPSParam.Operate.Step = eGPSIdleProcessCmdGSTP;
	DrvGPSParam.Operate.Result = GPSProcessResultSuc;
	DRV_GPS_IdleProcess();
}

/*******************************************************************************
 * Brief : 对串口收到的GPS原始数据进行解析
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Drv_GPS_UartParse(uint8_t* fDataBuf, uint32_t fDataLen)
{
	static uint8_t lGPsBuf[256];
	static uint8_t lGPSLen = 0;
	static uint8_t lGPSDataType = 0;	// GPS数据类型，1 GPS数据，2指令返回
	
	for(uint32_t i = 0;i < fDataLen;i++)
	{
		if('$' == fDataBuf[i])	// 首字符 $，为GPS数据
		{
			lGPSLen = 0;
			memset(lGPsBuf, 0x00, 256);			// 每次清空buf，防止对下次产生影响
			lGPsBuf[lGPSLen++] = fDataBuf[i];
			lGPSDataType = 1;
		}
		else if('[' == fDataBuf[i])	// 首字符 [，为返回的指令
		{
			lGPSLen = 0;
			memset(lGPsBuf, 0x00, 256);			// 每次清空buf，防止对下次产生影响
			lGPsBuf[lGPSLen++] = fDataBuf[i];
			lGPSDataType = 2;
		}
		else	// 过程数据
		{
			lGPsBuf[lGPSLen++] = fDataBuf[i];
			if(('\r' == lGPsBuf[lGPSLen-2]) && ('\n' == lGPsBuf[lGPSLen-1]))	// 尾字符 \r\n
			{
				if(1 == lGPSDataType)
				{
					lGPSDataType = 0;
//					if((('G' == lGPsBuf[3]) && ('S' == lGPsBuf[4]) && ('V' == lGPsBuf[5])) ||
//						(('V' == lGPsBuf[3]) && ('T' == lGPsBuf[4]) && ('G' == lGPsBuf[5])) ||
//						(('R' == lGPsBuf[3]) && ('M' == lGPsBuf[4]) && ('C' == lGPsBuf[5])))
					{
						for(uint32_t j = 0;j < lGPSLen;j++)
						{
							DRV_GPS_RTT_LOG(0,"%c", lGPsBuf[j]);
						}//DRV_GPS_RTT_LOG(0,"\n");
						Drv_GPS_InfoParse((char *)lGPsBuf);
					}
				}
				else if(2 == lGPSDataType)
				{
					lGPSDataType = 0;
					#if 1
					for(uint32_t j = 0;j < lGPSLen;j++)
					{
						DRV_GPS_RTT_LOG(0,"%c", lGPsBuf[j]);
					}
					#endif
					
					/* 根据当前操作步骤，判断操作是否成功 */
//					char gps_GSR_return[] = {"[GSR] Done\r\n"};
					char gps_GTIM_return[] = {"[GTIM] Done\r\n"};
					char gps_GSTP_return[] = {"[GSTP] Done\r\n"};
					char gps_BUP_return[] = {"[BUP] Done\r\n"};
					switch (DrvGPSParam.Operate.Step)
					{
						case eGPSHotStartProcessCmdGTIM:
							if(drCMN_ArrayCmp((uint8_t*)gps_GTIM_return, lGPsBuf, (sizeof(gps_GTIM_return)-1)))
							{
								DrvGPSParam.Operate.Result = GPSProcessResultSuc;
							}
							else
							{
								DrvGPSParam.Operate.Result = GPSProcessResultFai;
								DRV_GPS_RTT_WARN(0, "[WARN] @GTIM ResultFai \n");
							}
							
							DrvGPSParam.Operate.Step = eGPSHotStartProcessCmdGSR;
							DRV_GPS_HotStartProcess();
							break;
						case eGPSIdleProcessCmdGSTP:
							if(drCMN_ArrayCmp((uint8_t*)gps_GSTP_return, lGPsBuf, (sizeof(gps_GSTP_return)-1)))
							{
								DrvGPSParam.Operate.Result = GPSProcessResultSuc;
							}
							else
							{
								DrvGPSParam.Operate.Result = GPSProcessResultFai;
								DRV_GPS_RTT_WARN(0, "[WARN] @GSTP ResultFai \n");
							}
							
							DrvGPSParam.Operate.Step = eGPSIdleProcessCmdBUP;
							DRV_GPS_IdleProcess();							
							break;
						case eGPSIdleProcessCmdBUP:
							if(drCMN_ArrayCmp((uint8_t*)gps_BUP_return, lGPsBuf, (sizeof(gps_BUP_return)-1)))
							{
								DrvGPSParam.Operate.Result = GPSProcessResultSuc;
							}
							else
							{
								DrvGPSParam.Operate.Result = GPSProcessResultFai;
								DRV_GPS_RTT_WARN(0, "[WARN] @BUP ResultFai \n");
							}
							
							DrvGPSParam.Operate.Step = eGPSIdleProcessPwrOff;
							DRV_GPS_IdleProcess();							
							break;
						default :
							break;
					}
				}
			}
		}
	}	
}

/*******************************************************************************
 * Brief : GPS事件处理
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Drv_GPS_EventProcess(GPSEvent_t* Event_t)
{
	switch(Event_t->Id)
	{
		case eGPSEventColdStart:
			DRV_GPS_ColdStartProcess();
			break;
		case eGPSEventHotStart:
			DRV_GPS_HotStartProcess();
			break;
		case eGPSEventIdle:
			DRV_GPS_IdleProcess();
			break;
		default:
			break;	
	}
}

/*******************************************************************************
 * Brief : GPS测试
 * Input : @fExtEvent 事件类型
 * Return: @NULL
 * Call  : 
 ***************/
#include "app_systerm.h"
void Drv_GPS_Test(uint8_t fExtEvent)
{
//	if(eAppSysStateNormal == App_Sys_StateGet())
	{
		switch (fExtEvent)
		{
			case 1:	// 按键短按
				switch(DrvGPSParam.State)
				{
					case eGPSStateIdle:
						Drv_GPS_ColdStart();
						break;
					case eGPSStateColdStart:
					case eGPSStateHotStart:
						Drv_GPS_Idle();
						break;
					default:
						DRV_GPS_RTT_LOG(0, "[ERR] Drv_GPS_Test \n");
						break;
				}
				break;
			case 2:	// 3秒长按
				switch(DrvGPSParam.State)
				{
					case eGPSStateIdle:
						Drv_GPS_HotStart();
						break;
					case eGPSStateColdStart:
					case eGPSStateHotStart:
						Drv_GPS_Idle();
						break;
					default:
						DRV_GPS_RTT_LOG(0, "[ERR] Drv_GPS_Test \n");
						break;
				}				
				break;
			default :
				break;
		}
	}
}

/**********************************************************************
**
**模块说明: GPS数据解析模块，当收到GPS原始串口数据后，调用此模块，解析提取出想
			要的GPS数据
**修改日志：
**
**********************************************************************/

/*******************************************************************************
 * Brief : 对 GPS 收到的原始字符串数据进行拆解，存入 GPS_PART 结构体中
 * Input : @GPSBuffer GPS收到的原始数据
 * Return: Ret_OK 解析成功，否则失败
 * Call  : 
 ***************/
static uint16_t Drv_GPS_BufferPart(char* GPSBuffer)
{
	char *subString;
	char *subStringNext;	
	
	// 清空结构体内容
	memset(&GPS_PART,0x00,sizeof(DRV_GPS_PART_T));
//	GPS_PART.PartCnt = 0;
	
	subString = GPSBuffer;
	
	// 前面数据以","结束
	while((subStringNext = strstr(subString, ",")) != NULL)
	{
		GPS_PART.PartDataLen[GPS_PART.PartCnt] = subStringNext - subString;
		
		memcpy(&GPS_PART.PartData[GPS_PART.PartCnt], subString, GPS_PART.PartDataLen[GPS_PART.PartCnt]);
		
		subString = ++subStringNext;
		GPS_PART.PartCnt++;
		
		if(GPS_PART.PartCnt >= GPS_PART_NUM)
		{
			DRV_GPS_RTT_WARN(0,"[WARN] GPS_PART.PartCnt >= GPS_PART_NUM \n");
			return Ret_Fail;
		}
	}
	
	// 最后一个数据以"*"结束。之后是异或校验和，暂不处理
	if ((subStringNext = strstr(subString, "*")) != NULL)
	{
		GPS_PART.PartDataLen[GPS_PART.PartCnt] = subStringNext - subString;
		
		memcpy(&GPS_PART.PartData[GPS_PART.PartCnt], subString, GPS_PART.PartDataLen[GPS_PART.PartCnt]);	
		
		subString = ++subStringNext;
		GPS_PART.PartCnt++;	

		GPS_PART.ParseSucFlg = true;
		
		#if 0	// log GPS 数据解析结果
		for(uint32_t i = 0;i < GPS_PART.PartCnt;i++)
		{
			DRV_GPS_RTT_LOG(0,"[%d]",i);
			for(uint32_t j = 0;j < GPS_PART.PartDataLen[i];j++)
			{
				DRV_GPS_RTT_LOG(0,"%c",GPS_PART.PartData[i][j]);
			}
		}
		DRV_GPS_RTT_LOG(0,"\n");
		#endif
		
		return Ret_OK;
	}

	DRV_GPS_RTT_WARN(0,"[WARN] Drv_GPS_BufferPart \n");

	return Ret_Fail;
}

/*******************************************************************************
 * Brief : 获取当前 GPS 消息类型
 * Input : @GpsPart 解析后的GPS数据数组（半成品）
 * Return: @NULL
 * Call  : 
 ***************/
static GPS_MSG_TYPE_M Drv_GPS_MsgType(DRV_GPS_PART_T *GpsPart)
{
	if(strstr(&GpsPart->PartData[0][0], "GGA") != NULL)
		return GPS_MSG_GGA;
	
	if(strstr(&GpsPart->PartData[0][0], "GLL") != NULL)
		return GPS_MSG_GLL;	
	
	if(strstr(&GpsPart->PartData[0][0], "GSA") != NULL)
		return GPS_MSG_GSA;	
	
	if(strstr(&GpsPart->PartData[0][0], "GSV") != NULL)
		return GPS_MSG_GSV;	
	
	if(strstr(&GpsPart->PartData[0][0], "RMC") != NULL)
		return GPS_MSG_RMC;	
	
	if(strstr(&GpsPart->PartData[0][0], "VTG") != NULL)
		return GPS_MSG_VTG;	
	
	if(strstr(&GpsPart->PartData[0][0], "ZDA") != NULL)
		return GPS_MSG_ZDA;	
	
//	if(strstr(&GpsPart->PartData[0][0], "TXT") != NULL)
//		return GPS_MSG_TXT;	
	
	return GPS_MSG_NULL;
}

/*******************************************************************************
 * Brief : GPS GSV 数据解析，不要的参数可注释掉，提高运行效率
 * Input : @GpsPart 解析后的GPS数据数组（半成品）
 * Return: @NULL
 * Call  : 
 ***************/
static void Drv_GPS_GSVInfoParse(DRV_GPS_PART_T *GpsPart)
{
	uint8_t lStatementSerial;	// 语句编号
	uint8_t lSatelliteNum;		// 本语句卫星数
	
	lStatementSerial = (uint8_t)(atoi(&GpsPart->PartData[2][0]));	// 当前语句编号
	if(1 == lStatementSerial)	// 如果当前语句编号为1，清空已存储的卫星信息
	{
//		DRV_GPS_RTT_LOG(0, "GPS CLEAR 1 \n");
		
		for(uint32_t i = 0;i < GPS_GSV_SV_MAX;i++)
		{
			GPS_GSV.SatelliteInfo[i].ID = 0;
			GPS_GSV.SatelliteInfo[i].Elevation = 0;
			GPS_GSV.SatelliteInfo[i].Azimuth = 0;
			GPS_GSV.SatelliteInfo[i].SNR = 0;
		}		
	}

	// 可见卫星数
	if(0 != GpsPart->PartDataLen[3])
	{
		GPS_GSV.SatelliteNum = (uint8_t)(atoi(&GpsPart->PartData[3][0]));
	}
	
	/* 解析卫星信息 */ 
	// 本条语句有多少卫星
	if(4*lStatementSerial > GPS_GSV.SatelliteNum)
	{
		lSatelliteNum = 4*lStatementSerial - GPS_GSV.SatelliteNum;
	}
	else
	{
		lSatelliteNum = 4;
	}
	for(uint32_t i = 0;i < lSatelliteNum;i++)
	{
		GPS_GSV.SatelliteInfo[(lStatementSerial-1)*4 + i].ID = ((uint8_t)(atoi(&GpsPart->PartData[i*4+4][0])));
		GPS_GSV.SatelliteInfo[(lStatementSerial-1)*4 + i].Elevation = (uint16_t)(atoi(&GpsPart->PartData[i*4+5][0]));
		GPS_GSV.SatelliteInfo[(lStatementSerial-1)*4 + i].Azimuth = (uint8_t)((atoi)(&GpsPart->PartData[i*4+6][0]));
		GPS_GSV.SatelliteInfo[(lStatementSerial-1)*4 + i].SNR = ((uint8_t)(atoi)(&GpsPart->PartData[i*4+7][0]));
	}
	
//	for(uint32_t i = 0;i<12;i++)
//	{
//		DRV_GPS_RTT_LOG(0,"GPS_GSV... %d \n",(atoi(&GpsPart->PartData[i+4][0])));
//	}
	
	#if 0	 // log GPS 数据解析结果
	for(uint32_t i = 0;i < GPS_PART.PartCnt;i++)
	{
		DRV_GPS_RTT_LOG(0,"[%d]: ",i);
		for(uint32_t j = 0;j < GPS_PART.PartDataLen[i];j++)
		{
			DRV_GPS_RTT_LOG(0,"%c",GPS_PART.PartData[i][j]);
		}
		DRV_GPS_RTT_LOG(0,"\n");
	}
	#endif
}

/*******************************************************************************
 * Brief : GPS RMC 数据解析，不要的参数可注释掉，提高运行效率
 * Input : @GpsPart 解析后的GPS数据数组（半成品）
 * Return: @NULL
 * Call  : 
 ***************/
static void Drv_GPS_RMCInfoParse(DRV_GPS_PART_T *GpsPart)
{
//	static uint32 lCnt = 0;
//	DRV_GPS_RTT_LOG(0,"lCnt %d \n",lCnt++);
	char lStr[10];
	
	#if 1 // UTC 
	if(0 != GpsPart->PartDataLen[1])
	{
		GPS_RMC.UTC = atof(&GpsPart->PartData[1][0]);
	}
	#endif
	
	#if 1 // 位置有效标志
	if(0 != GpsPart->PartDataLen[2])
	{
		GPS_RMC.Status = GpsPart->PartData[2][0];
		
		if('V' == GPS_RMC.Status)
		{
			DrvGPSParam.SearchingCnt++;
		}
	}
	#endif
	
	#if 1 // 纬度，前2字节表示度
	if(0 != GpsPart->PartDataLen[3])
	{
//		GPS_RMC.Lat = atof(&GpsPart->PartData[3][0]);
		memset(lStr, 0x00, 10);
		memcpy(lStr, &GpsPart->PartData[3][0], 2);	// 前2字节表示度
		GPS_RMC.Lat = atoi(lStr);
		GPS_RMC.Lat += (atof(&GpsPart->PartData[3][2]) / 60);	// 后面字节表示分
	}
	#endif
	
	#if 1 // 纬度方向
	if(0 != GpsPart->PartDataLen[4])
	{
		GPS_RMC.uLat = GpsPart->PartData[4][0];	
	}
	#endif
	
	#if 1 // 经度，前3字节表示度
	if(0 != GpsPart->PartDataLen[5])
	{
//		GPS_RMC.Lon = atof(&GpsPart->PartData[5][0]);
		memset(lStr, 0x00, 10);
		memcpy(lStr, &GpsPart->PartData[5][0], 3);	// 前3字节表示度
		GPS_RMC.Lon = atoi(lStr);
		GPS_RMC.Lon += (atof(&GpsPart->PartData[5][3]) / 60);	// 后面字节表示分			
	}
	#endif
	
	#if 1 // 经度方向
	if(0 != GpsPart->PartDataLen[6])
	{
		GPS_RMC.uLon = GpsPart->PartData[6][0];
	}
	#endif
	
	#if 0 // 对地速度
	if(0 != GpsPart->PartDataLen[7])
	{
		GPS_RMC.Spd = atof(&GpsPart->PartData[7][0]);
	}
	#endif
	
	#if 0	// 对地真航向，单位度
	if(0 != GpsPart->PartDataLen[8])
	{
		GPS_RMC.Cog = atof(&GpsPart->PartData[8][0]);
	}	
	#endif 
	
	#if 0	// 日期（dd 为日， mm 为月， yy 为年）
	if(0 != GpsPart->PartDataLen[9])
	{
		GPS_RMC.Date = atoi(&GpsPart->PartData[9][0]);
	}	
	#endif
	
	#if 0	// 磁偏角，单位为度。 固定为空
	if(0 != GpsPart->PartDataLen[10])
	{
		GPS_RMC.Mv = atof(&GpsPart->PartData[10][0]);
	}	
	#endif
	
	#if 0	// 磁偏角方向： E-东， W-西。 固定为空
	if(0 != GpsPart->PartDataLen[11])
	{
		GPS_RMC.MvE = GpsPart->PartData[11][0];
	}
	#endif
	
	#if 0	// 定位模式标志,A自动
	if(0 != GpsPart->PartDataLen[12])
	{
		GPS_RMC.Mode = GpsPart->PartData[12][0];
	}
	#endif	
	
	#if 0
//	DRV_GPS_RTT_LOG(0,"Drv_GPS_RMCInfoParse \n");
	DRV_GPS_RTT_LOG(0,"GPS_RMC.UTC %d \n",(uint32_t)(GPS_RMC.UTC));
	DRV_GPS_RTT_LOG(0,"GPS_RMC.Status %c \n",GPS_RMC.Status);
	DRV_GPS_RTT_LOG(0,".Lat %d \n",(uint32_t)GPS_RMC.Lat);
	DRV_GPS_RTT_LOG(0,".uLat %c \n",GPS_RMC.uLat);
	DRV_GPS_RTT_LOG(0,".Lon %d \n",(uint32_t)GPS_RMC.Lon);
	DRV_GPS_RTT_LOG(0,".uLon %c \n",GPS_RMC.uLon);
//	DRV_GPS_RTT_LOG(0,".Spd %d \n",(uint32_t)GPS_RMC.Spd);
//	DRV_GPS_RTT_LOG(0,".Cog %d \n",(uint32_t)GPS_RMC.Cog);
//	DRV_GPS_RTT_LOG(0,".Date %d \n",GPS_RMC.Date);
//	DRV_GPS_RTT_LOG(0,".Mv %d \n",(uint32_t)GPS_RMC.Mv);
//	DRV_GPS_RTT_LOG(0,".MvE %c \n",GPS_RMC.MvE);
//	DRV_GPS_RTT_LOG(0,".Mode %c \n",GPS_RMC.Mode);
	#endif
}

/*******************************************************************************
 * Brief : GPS 数据解析
 * Input : @GPSBuffer
 * Return: @NULL
 * Call  : 
 ***************/
void Drv_GPS_InfoParse(char* GPSBuffer)
{
	static uint32_t lTimeoutCnt = 0;
	
	// 先把原始字符串数据拆解后存入 GPS_PART 结构体中
	if(Ret_OK != Drv_GPS_BufferPart(GPSBuffer))	return;
	
	// 判断 GPS 消息类型并进行解析
	switch (Drv_GPS_MsgType(&GPS_PART))
    {
//    	case GPS_MSG_GGA: break;
//    	case GPS_MSG_GLL: break;
//		case GPS_MSG_GNS: break;
//		case GPS_MSG_GSA: break;
		case GPS_MSG_GSV: 
			Drv_GPS_GSVInfoParse(&GPS_PART);
			lTimeoutCnt = 0;
			break;
		case GPS_MSG_RMC: 
			Drv_GPS_RMCInfoParse(&GPS_PART);
			if((++lTimeoutCnt) >= 3)	// 超时清空GPS数据
			{
//				DRV_GPS_RTT_LOG(0, "GPS CLEAR 0 \n");
				
				for(uint32_t i = 0;i < GPS_GSV_SV_MAX;i++)
				{
					GPS_GSV.SatelliteInfo[i].ID = 0;
					GPS_GSV.SatelliteInfo[i].Elevation = 0;
					GPS_GSV.SatelliteInfo[i].Azimuth = 0;
					GPS_GSV.SatelliteInfo[i].SNR = 0;
				}
			}
			break;
//		case GPS_MSG_VTG: break;
//		case GPS_MSG_ZDA: break;
    	default:
//			Drv_GPS_GSVInfoParse(&GPS_PART);
    		break;
    }
}


































