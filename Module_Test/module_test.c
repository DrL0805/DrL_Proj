/**********************************************************************
**
**ģ��˵��: ģ����Ե�Ԫ
**����汾���޸���־(ʱ�䣬����):
**   V1.0   2018.6.22  ����  
**
**********************************************************************/
#include "platform_common.h"
#include "module_test.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"
#include "rtos.h"

#include "sm_sys.h"
#include "sm_timer.h"
#include "sm_uart.h"
#include "sm_os.h"
#include "sm_wdt.h"
#include "sm_adc.h"

#include "drv_key.h"
#include "drv_common.h"
#include "drv_extflash.h"
#include "drv_font.h"
#include "GT24L16A2Y.h"

//#include "mid_front.h"
#include "mid_extflash.h"   //for BLE MAC addr
#include "BLE_Stack.h"  //BLE stack


#if(MODULE_TEST_ENABLE == 1)
//**********************************************************************
// ��������:  ������8: ADC
// ���������
// ���ز����� 
//**********************************************************************
void AdcIsrCb(uint32 u32adcValue)
{
    uint32 volvalue;
    volvalue = (2000 * u32adcValue)/(0x01 << 14);
    RTT_DEBUG_printf(0,"Vol=%d mV\n",volvalue);
}

void Adc_test(void)
{
    static uint8 u8bInit = FALSE;
    //init uart
    if(u8bInit == FALSE)
    {
        SMDrv_ADC_Init();
        SMDrv_ADC_SetIsrPrio(3);
//        SMDrv_ADC_Enable();
        u8bInit = TRUE;
    }

    while(1)
    {
        RTT_DEBUG_printf(0,"1: open adc slot for body temp\n");
        RTT_DEBUG_printf(0,"2: StartDetect...\n");
        RTT_DEBUG_printf(0,"0: Exit...\n");
        switch(SEGGER_RTT_WaitKey())
        {
        case '1':
            SMDrv_ADC_Open(BODY_TEMP_ADC_MODULE,AdcIsrCb);
        case '2':
            SMDrv_ADC_StartDetect();
            break;
        case '0':
//            SMDrv_ADC_Disable();
//            SMDrv_ADC_Close(BODY_TEMP_ADC_MODULE);
//            SMDrv_ADC_DeInit();
            return;
        }
        SMDrv_SYS_DelayMs(1000);
    }

}

//**********************************************************************
// ��������:  ������7: wdt
// ���������
// ���ز����� 
//**********************************************************************
void WdtIsrCb(void)
{
}

void Wat_test(void)
{
    static uint8 u8bInit = FALSE;
    //init uart
    if(u8bInit == FALSE)
    {
        SMDrv_WDT_Open(255,127,WdtIsrCb);
        u8bInit = TRUE;
    }

    RTT_DEBUG_printf(0,"1: wdt normal\n");
    RTT_DEBUG_printf(0,"0: Exit...\n");
    if(SEGGER_RTT_WaitKey() == '0')
    {
        return;
    }
    RTT_DEBUG_printf(0,"wdt work\n");

    while(1)
    {
        SMDrv_WDT_ReStart();
        SMDrv_SYS_DelayMs(1000);
    }
}

//**********************************************************************
// ��������:  ������6: uart
// ���������
// ���ز����� 
//**********************************************************************
//u32RxTimeout = 1: RX
//             = 2: RX timeout
//             = 0: idle
uint32 u32RxTimeout = 0;

void uart_callback(uint32 uart_event)
{
    if(uart_event == UART_EVENT_RX_TIMEOUT)
        u32RxTimeout = 2;
    else if(uart_event == UART_EVENT_RX)
        u32RxTimeout = 1;
}

void Uart_test(void)
{
    static uint8 u8bInit = FALSE;
    uint16 u16LenWritten,u16ReadLen;
    uint8 u8Buffer[128];
    uint32 u32RcvTime=0;
    uint32 u32TxBufSize,u32RxBufSize;

    //init uart
    if(u8bInit == FALSE)
    {
        SMDrv_UART_Open(BASE_UART_MODULE,uart_callback);
        SMDrv_UART_EnableIrq(BASE_UART_MODULE, UART_EVENT_RX|UART_EVENT_RX_TIMEOUT,TRUE);
        u8bInit = TRUE;
    }

    //get TX/RX fifo buffer size
    u32TxBufSize = SMDrv_UART_GetTxBuffSize(BASE_UART_MODULE);
    u32RxBufSize = SMDrv_UART_GetRxBuffSize(BASE_UART_MODULE);
    while(1)
    {
        //���ճ�ʱ��˵�������Ѿ�������ɣ����Զ�ȡ����
        if(u32RxTimeout == 2)
        {
            SMDrv_UART_ReadBytes(BASE_UART_MODULE,u8Buffer,u32RxBufSize,&u16ReadLen);

            //�����������ֵ���С�ڻ�������С
            if(u16ReadLen > u32TxBufSize)
                u16ReadLen = u32TxBufSize;
            SMDrv_UART_WriteBytes(BASE_UART_MODULE,u8Buffer,u16ReadLen,&u16LenWritten);
            u32RxTimeout = 0,u32RcvTime=0;
        }

        //�����жϣ���1/2 fifo�����ж�Ϊ�������յ���������16�ı���ʱ��ֻ��rx�жϣ�������
        //rx timeout�жϣ��ڴ�����³�����Զ�ȡ���ݣ�Ҳ���Լӳ�ʱ�жϣ�Ȼ����һ�ζ�ȡ����
        if(u32RxTimeout == 1)
        {
            if(u32RcvTime == 0)
                u32RcvTime = SMOS_GetTickCount();
            else
            {
                if(SMOS_GetTickCount() - u32RcvTime > 20)
                {
                    SMDrv_UART_ReadBytes(BASE_UART_MODULE,u8Buffer,u32RxBufSize,&u16ReadLen);
                    //RTT_DEBUG_printf(0,"read len:%d\n",u16ReadLen);

                    //�����������ֵ���С�ڻ�������С
                    if(u16ReadLen > u32TxBufSize)
                        u16ReadLen = u32TxBufSize;
                    SMDrv_UART_WriteBytes(BASE_UART_MODULE,u8Buffer,u16ReadLen,&u16LenWritten);
                    //RTT_DEBUG_printf(0,"write len:%d\n",u16LenWritten);
                    u32RxTimeout = 0,u32RcvTime=0;
                }
            }
        }
        SMDrv_SYS_DelayMs(100);
    }
}

//**********************************************************************
// ��������:  ������5: font
// ���������
// ���ز����� 
//**********************************************************************
void Font_test(void)
{
    static uint8 u8bInit = FALSE;
    uint8 i;
    uint8 DZ_Data[16];
    uint8  A_8X16_compare1[16] = 
    {
    	0x00,0x80,0x70,0x08,0x70,0x80,0x00,0x00,0x3c,0x03,0x02,0x02,0x02,0x03,0x3c,0x00
    };
 
    if(u8bInit == FALSE)
    {
        Drv_Font_Open();
        Drv_Font_SendCmd(FONT_SLEEP_CMD);
        Drv_Font_Close();
        u8bInit = TRUE;
    }
    while(1)
    {
        RTT_DEBUG_printf(0,"1: font Test.\n");
        RTT_DEBUG_printf(0,"0: Exit...\n");
        switch(SEGGER_RTT_WaitKey())
        {
        case '1':
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
            break;
        case '0':
            return;
        default:
            break;
        }
    }
}

//**********************************************************************
// ��������:  ������4: flash
// ���������
// ���ز����� 
//**********************************************************************
static uint16 IdleWait(uint16 WaitTick)
{
	uint16 waitCnt, ret;
	ret 	= 0;
	waitCnt = 0;
	while(Drv_Extflash_CheckState())
	{
		waitCnt++;
		if(waitCnt > WaitTick)
		{
			ret = 0xff;
			break;
		}
		vTaskDelay(10);		// ticks
		// ��ֹ�������������ʱ����ر�
		Drv_Extflash_SendCmd(FLASH_WAKEUP_CMD);
	}
	return ret;
}

void Flash_test(void)
{
    static uint8 u8bInit = FALSE;
	uint8  dataTemp[16], i, u8len =16;
	uint16 ret = 0;
    
    if(u8bInit == FALSE)
    {
        Drv_Extflash_Open();
        Drv_Extflash_SendCmd(FLASH_SLEEP_CMD);
        Drv_Extflash_Close();
        u8bInit = TRUE;
    }
    while(1)
    {
        RTT_DEBUG_printf(0,"1: flash Test.\n");
        RTT_DEBUG_printf(0,"0: Exit...\n");
        switch(SEGGER_RTT_WaitKey())
        {
        case '1':
            #if 1
            Drv_Extflash_Open();
            Drv_Extflash_SendCmd(FLASH_WAKEUP_CMD);
            Drv_Extflash_Erase4K(0x0000);
            IdleWait(60);

            RTT_DEBUG_printf(0,"write data:\n");
            for(i = 0; i < u8len; i++)
            {
                dataTemp[i] = i;
                RTT_DEBUG_printf(0,"0x%x,",i);
            }
            RTT_DEBUG_printf(0,"\n");
            Drv_Extflash_Write(dataTemp, 0x0000, u8len);
            ret |= IdleWait(20);
            memset(dataTemp,0x00,u8len);
            Drv_Extflash_Read(dataTemp, 0x0000, u8len);
            RTT_DEBUG_printf(0,"read data:\n");
            for(i = 0; i < u8len; i++)
            {
                RTT_DEBUG_printf(0,"0x%x,",dataTemp[i]);
            }
            RTT_DEBUG_printf(0,"\n");

            Drv_Extflash_SendCmd(FLASH_SLEEP_CMD);

            Drv_Extflash_Close();
            #else            
            uint8 u8MacAddr[6];
            extflash_para_t extflash;
            
            extflash.dataAddr = u8MacAddr;
            extflash.Cb = NULL;
            extflash.length = 6;
            extflash.dataAddr = u8MacAddr;
            Mid_ExtFlash_ReadBleInfo(EXTFLASH_EVENT_READ_MAC,&extflash);
            RTT_DEBUG_printf(0,"MAC:\n");
            for(i = 0; i < 6; i++)
            {
                RTT_DEBUG_printf(0,"0x%x,",u8MacAddr[i]);
            }
            RTT_DEBUG_printf(0,"\n");
            #endif
            break;
        case '0':
            return;
        default:
                break;
        }
    }
}

//**********************************************************************
// ��������:  ������3: Ctimer
// ���������
// ���ز����� 
//**********************************************************************
void Timer2A_Isr(void)
{
    static uint8 u8loop = 0;

    if(u8loop == 0)
    {
       Drv_Common_GreenLedOn();
       u8loop = 1;
    }
    else
    {
        Drv_Common_GreenLedOff();
        u8loop =0;
    }
}

void Timer2B_Isr(void)
{
    static uint32 u32cnt=0;
    
    RTT_DEBUG_printf(0,"timer2B u32cnt=%d\n",u32cnt);
    u32cnt++;
}

void Ctimer_test(void)
{
    static uint8 u8bInit = FALSE,u8bOpenA = FALSE,u8bOpenB = FALSE;

    if(u8bInit == FALSE)
    {
        SMDrv_CTimer_SetIsrPrio(1);
        Drv_Common_Init();
        u8bInit = TRUE;
    }
    while(1)
    {
        RTT_DEBUG_printf(0,"1: start timer2A.\n");
        RTT_DEBUG_printf(0,"2: stop timer2A.\n");      
        RTT_DEBUG_printf(0,"3: start timer2B.\n");
        RTT_DEBUG_printf(0,"4: stop timer2B.\n");
        RTT_DEBUG_printf(0,"0: Exit...\n");
        switch(SEGGER_RTT_WaitKey())
        {
        case '1':
            if(u8bOpenA == FALSE)
            {
                SMDrv_CTimer_Open(STOPWATCH_CTIMER_MODULE,7,Timer2A_Isr);
                u8bOpenA = TRUE;
            }
            SMDrv_CTimer_Start(STOPWATCH_CTIMER_MODULE);
            break;
        case '2':
            SMDrv_CTimer_Stop(STOPWATCH_CTIMER_MODULE);
            break;
         case '3':
            if(u8bOpenB == FALSE)
            {
                SMDrv_CTimer_Open(COUNTDOWN_CTIMER_MODULE,7,Timer2B_Isr);
                u8bOpenB = TRUE;
            }
            SMDrv_CTimer_Start(COUNTDOWN_CTIMER_MODULE);
            break;
        case '4':
            SMDrv_CTimer_Stop(COUNTDOWN_CTIMER_MODULE);
            break;
        case '0':
            if(u8bOpenA == TRUE)
                SMDrv_CTimer_Stop(STOPWATCH_CTIMER_MODULE);
            
            if(u8bOpenB == TRUE)
                SMDrv_CTimer_Stop(COUNTDOWN_CTIMER_MODULE);
  
            u8bOpenA = FALSE;
            u8bOpenB = FALSE;
            return;
        default:
            break;
        }
    }
}

//**********************************************************************
// ��������:  ������2: ����
// ���������
// ���ز����� 
//**********************************************************************
static void Ble_CB(const uint8 *buf,uint16 len)
{
    uint16  i;

    RTT_DEBUG_printf(0,"BLE Recv:\n");
    for(i = 0; i < len; i++)
    {
        RTT_DEBUG_printf(0,"0x%x,",buf[i]);
    }
    RTT_DEBUG_printf(0,"\n");
    BLE_Stack_Send((uint8 *)buf,len);
}

static void BLE_Test(void)
{
    uint8 newblestate;

    while(1)
    {
        RTT_DEBUG_printf(0,"\n1: Transmiter,with BLE tool...\n");
        RTT_DEBUG_printf(0,"2: ADV On...\n");
        RTT_DEBUG_printf(0,"3: ADV Off...\n");
        RTT_DEBUG_printf(0,"4: Power On...\n");
        RTT_DEBUG_printf(0,"5: Power Off...\n");
        RTT_DEBUG_printf(0,"6: Set ADV Name...\n");
        RTT_DEBUG_printf(0,"0: Exit...\n");
        switch(SEGGER_RTT_WaitKey())
        {
        case '1':
            BLE_Stack_SetRecvCallBack(Ble_CB);
            SMDrv_SYS_DelayMs(50);
            break;
        case '2':
            newblestate = BT_ADV_ON;
            BLE_Stack_Interact(BLE_STATUS_SET,&newblestate,0);
            break;
        case '3':
            newblestate = BT_ADV_OFF;
            BLE_Stack_Interact(BLE_STATUS_SET,&newblestate,0);
            break;
        case '4':
            newblestate = BT_POWERON;
            BLE_Stack_Interact(BLE_POWERONOFF,&newblestate,0);
            break;
        case '5':
            newblestate = BT_POWEROFF;
            BLE_Stack_Interact(BLE_POWERONOFF,&newblestate,0);
            break;
        case '6':
            BLE_Stack_Interact(BLE_AVD_NAME_SET,"ble_test",8);
            break;
        case '0':
            newblestate = BT_ADV_OFF;
            BLE_Stack_Interact(BLE_STATUS_SET,&newblestate,0);
            SMDrv_SYS_DelayMs(50);
            newblestate = BT_POWEROFF;
            BLE_Stack_Interact(BLE_POWERONOFF,&newblestate,0);
            return;
        default:
            break;
        }
    }
}

//**********************************************************************
// ��������:  ������1: ���������
// ���������
// ���ز����� 
//**********************************************************************
static void Key_CB(key_num_t keynum,key_event event_type)
{
    RTT_DEBUG_printf(0,"Key S%d:",keynum);
    if(event_type == KEY_HOLDSHORT_EVENT)
        RTT_DEBUG_printf(0,"short hold\n");
    else if(event_type == KEY_HOLDLONG_EVENT)
        RTT_DEBUG_printf(0,"long hold\n");
    else
        RTT_DEBUG_printf(0,"press...\n");
}

static void Key_Moto_Test(void)
{
    static uint8 u8bInit = FALSE;

    if(u8bInit == FALSE)
    {
        Drv_Key_Init();
        Drv_Common_Init();
        u8bInit = TRUE;
    }
    while(1)
    {
        RTT_DEBUG_printf(0,"1: Key Test.\n");
        RTT_DEBUG_printf(0,"2: Moto Test.\n");
        RTT_DEBUG_printf(0,"0: Exit...\n");
        switch(SEGGER_RTT_WaitKey())
        {
        case '1':
            Drv_Key_SetCallBack(Key_CB);
            break;
        case '2':
            //Drv_Common_MotoOn();
            Drv_Common_GreenLedOn();
            SMDrv_SYS_DelayMs(1500);
            //Drv_Common_MotoOff();
            Drv_Common_GreenLedOff();
            SMDrv_SYS_DelayMs(500);
            break;
        case '0':
            Drv_Key_SetCallBack(NULL);
            Drv_Common_MotoOff();
            return;
        default:
            break;
        }
    }
}

//**********************************************************************
// ��������:  ģ����������
// ���������
// ���ز����� 
//**********************************************************************
void Module_Test_Main(void *pvParameters)
{
    int32 s32Key;
    SMDrv_SYS_DelayMs(500);
    while(1)
    {
        RTT_DEBUG_printf(0,"Goto H003 Module Test:\n");
        RTT_DEBUG_printf(0,"a: Key,Moto Test...\n");
        RTT_DEBUG_printf(0,"b: BLE Test...\n");
        RTT_DEBUG_printf(0,"c: Ctimer Test...\n");
        RTT_DEBUG_printf(0,"d: flash Test...\n");
        RTT_DEBUG_printf(0,"e: font Test...\n");
        RTT_DEBUG_printf(0,"f: uart Test...\n");
        RTT_DEBUG_printf(0,"h: wdt Test...\n");
        RTT_DEBUG_printf(0,"g: adc Test...\n");

        s32Key = SEGGER_RTT_WaitKey();
        //RTT_DEBUG_printf(0,"s32Key=%c\n",s32Key);
        switch(s32Key)
        {
        case 'a':
            Key_Moto_Test();
            break;
        case 'b':
            BLE_Test();
            break;
        case 'c':
            Ctimer_test();
        case 'd':
            Flash_test();
            break;
        case 'e':
            Font_test();
        case 'f':
            Uart_test();
            break;
        case 'h':
            Wat_test();
            break;
        case 'g':
            Adc_test();
            break;
        }
        SMDrv_SYS_DelayMs(50);
    }
}
#endif
