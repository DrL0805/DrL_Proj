/**********************************************************************
**
**ģ��˵��: �Խ�MCU GPIO�����ӿڣ���������Ŀԭ��ͼ������
**����汾���޸���־(ʱ�䣬����),�޸���:
**   V1.0   2018.4.10  ����  ZSL  
**   V2.0   2018.8.8   ����Apollo3 driver
**
**********************************************************************/
#define BAT_MODULE
#define KEY_MODULE
#ifdef AM_PART_APOLLO3
#define FONT_MODULE
#define FLASH_MODULE
#else
#define BLE_MODULE
#endif

#include "string.h"
#include "io_config.h"
#include "sm_gpio.h"

const am_hal_gpio_pincfg_t SM_AM_HAL_GPIO_DISABLE =
{
    .uFuncSel       = 3,
    .eDriveStrength = AM_HAL_GPIO_PIN_DRIVESTRENGTH_2MA,
    .eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_DISABLE
};

const am_hal_gpio_pincfg_t SM_AM_HAL_GPIO_OUTPUT =
{
    .uFuncSel       = 3,
    .eDriveStrength = AM_HAL_GPIO_PIN_DRIVESTRENGTH_2MA,
    .eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_PUSHPULL
};

const am_hal_gpio_pincfg_t SM_AM_HAL_GPIO_TRISTATE =
{
    .uFuncSel       = 3,
    .eDriveStrength = AM_HAL_GPIO_PIN_DRIVESTRENGTH_2MA,
    .eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_TRISTATE
};

const am_hal_gpio_pincfg_t SM_AM_HAL_GPIO_INPUT =
{
    .uFuncSel       = 3,
    .eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_DISABLE,
    .eGPInput       = 1
};

#ifdef AM_PART_APOLLO3
//**********************************************************************
// ��������:    GPIO�жϷ�����
// ���������    ��
// ���ز�����    ��
//**********************************************************************
void am_gpio_isr(void)
{
    uint64 u64PinIntStatus = 0x00;

    //step 1:Read and clear the GPIO interrupt status.
    am_hal_gpio_interrupt_status_get(true, &u64PinIntStatus);
    am_hal_gpio_interrupt_clear(u64PinIntStatus);
    
    //step 2: Call the individual pin interrupt handlers for any pin that triggered an interrupt.
    am_hal_gpio_interrupt_service(u64PinIntStatus);
}

//**********************************************************************
// ��������:  �ж�pin�Ƿ���SPI CS
// ��������� u32PinNum
// ���ز����� 
//**********************************************************************
static uint32 Smdrv_IsSpiCs(uint32 u32PinNum)
{
//����SDK CS�Ż���Ҫ���������  
#if 0
    if((u32PinNum == FONT_CS_PIN) || (u32PinNum == FLASH_CS_PIN))
        return TRUE;
#endif
    return FALSE;
}

//**********************************************************************
// ��������:    GPIO��ʼ��
// ���������    ��
// ���ز�����    ��
//**********************************************************************
void SMDrv_GPIO_Init(void)
{

}

//**********************************************************************
// ��������: ����GPIO module ID����GPIO����:����/�������Ϊ�жϣ�������
//           �������жϷ������
// ���������u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
//    config_opt:����GPIO���ԣ����ڳ����иı�GPIO����ʱʹ�ã�����GPIOģ��
//      IICʱ��SDA��һ��Ϊ���룬һ��Ϊ�����
//      == NULL: ʹ��Ĭ�ϵ��������ã� != NULL: ��ʹ�ô��������
//    g_callback:�жϷ�����callback
// ���ز���: Ret_OK��Ret_InvalidParam
//**********************************************************************
ret_type SMDrv_GPIO_Open(uint32 u32PinNum,uint32 *config_opt,gpio_cb g_callback)
{
    am_hal_gpio_pincfg_t bfGpioCfg = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint32 ret;

    if(u32PinNum >= IO_UNKNOW)
        return Ret_InvalidParam;

    //apollo3�����spi cs�ŵ������ã���spiһ������
    if(Smdrv_IsSpiCs(u32PinNum))
        return Ret_OK;

    //step 1:�������Ϊ�жϣ������жϷ������
    if(g_callback != NULL)
    {
        am_hal_gpio_interrupt_register(u32PinNum,g_callback);
    }

    //step 2:����GPIO��Ĭ�����ԣ�����ԭ��ͼ
    bfGpioCfg.uFuncSel = 3;  //IO�ڹ���ѡ��=3��GPIO
    if((u32PinNum == KEY_S0_PIN) || (u32PinNum == KEY_S1_PIN) || (u32PinNum == KEY_S2_PIN))
    {
        bfGpioCfg.eIntDir    = AM_HAL_GPIO_PIN_INTDIR_HI2LO;   //�½��ش���//AM_HAL_GPIO_PIN_INTDIR_LO2HI;//
        bfGpioCfg.eGPOutcfg  = AM_HAL_GPIO_PIN_OUTCFG_DISABLE; //����
        bfGpioCfg.eGPInput   = AM_HAL_GPIO_PIN_INPUT_ENABLE;
		bfGpioCfg.ePullup    = AM_HAL_GPIO_PIN_PULLUP_WEAK;
    }
    else if(u32PinNum == HR_INT1_PIN)
    {
        bfGpioCfg.eIntDir    = AM_HAL_GPIO_PIN_INTDIR_LO2HI;   //�����ش���
        bfGpioCfg.eGPOutcfg  = AM_HAL_GPIO_PIN_OUTCFG_DISABLE; //����
        bfGpioCfg.eGPInput   = AM_HAL_GPIO_PIN_INPUT_ENABLE;
    }
    else if ((u32PinNum == HR_INT2_PIN) || (u32PinNum == BAT_CHG_PIN))
    {
        bfGpioCfg.eIntDir    = AM_HAL_GPIO_PIN_INTDIR_LO2HI;   //�����ش���
        bfGpioCfg.eGPOutcfg  = AM_HAL_GPIO_PIN_OUTCFG_DISABLE; //����
        bfGpioCfg.eGPInput   = AM_HAL_GPIO_PIN_INPUT_ENABLE;		
		
		#if 0
        bfGpioCfg.eGPOutcfg  = AM_HAL_GPIO_PIN_OUTCFG_DISABLE; //����
        bfGpioCfg.eGPInput   = AM_HAL_GPIO_PIN_INPUT_ENABLE;
        if(u32PinNum == BAT_CHG_PIN)
        {
            bfGpioCfg.ePullup    = AM_HAL_GPIO_PIN_PULLUP_6K;
        }
		#endif
    }
	else if(u32PinNum == TOUCH_INT_PIN)
	{
        bfGpioCfg.eIntDir    = AM_HAL_GPIO_PIN_INTDIR_HI2LO;   //�½��ش���//AM_HAL_GPIO_PIN_INTDIR_LO2HI;//
        bfGpioCfg.eGPOutcfg  = AM_HAL_GPIO_PIN_OUTCFG_DISABLE; //����
        bfGpioCfg.eGPInput   = AM_HAL_GPIO_PIN_INPUT_ENABLE;
		bfGpioCfg.ePullup    = AM_HAL_GPIO_PIN_PULLUP_WEAK; //;		AM_HAL_GPIO_PIN_PULLUP_24K
	}
    else             //GPIO����Ϊ���
    {
        bfGpioCfg.eDriveStrength = AM_HAL_GPIO_PIN_DRIVESTRENGTH_2MA;
        bfGpioCfg.eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_PUSHPULL;
    }

    //step 3:����pin�������������������
    if(config_opt != NULL)
    {
        //���������������GPIO���ԵĲ�������ʹ�ô����ֵ������ʹ��Ĭ�����õ�ֵ
    }    
	
    if((ret = am_hal_gpio_pinconfig(u32PinNum, bfGpioCfg)) != AM_HAL_STATUS_SUCCESS)
    {
        Err_Info((0,"Error - open GPIO config pin %d failed:%d\n",u32PinNum,ret));
        return Ret_Fail;
    }

    //step 4:�ж�ģʽ��enable�ж�
    if(g_callback != NULL)
    {
		SMDrv_GPIO_SetIrqPrio(2);
        am_hal_gpio_interrupt_clear(AM_HAL_GPIO_BIT(u32PinNum));
        am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(u32PinNum));
    }

    return Ret_OK;
}

//**********************************************************************
// ��������:  ���������жϴ�������
// ��������� u32PinNum: gpio num,
//   u32pol:  =1: �����أ�=0: �½���
// ���ز����� ��
//**********************************************************************
void SMDrv_GPIO_ReConfigIrq(uint32 u32PinNum,uint32 u32pol)
{
#if 0
    uint32 ui32Polarity;
    ui32Polarity = (u32pol == 1)?AM_HAL_GPIO_RISING:AM_HAL_GPIO_FALLING;
    am_hal_interrupt_disable(AM_HAL_INTERRUPT_GPIO);
    am_hal_gpio_int_disable(AM_HAL_GPIO_BIT(u32PinNum));
    am_hal_gpio_int_polarity_bit_set(u32PinNum,ui32Polarity);
    am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(u32PinNum));
    am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(u32PinNum));
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_GPIO);
#endif
}

//**********************************************************************
// ��������:  ����/�ر�pin���ж�
// ��������� u32PinNum: gpio num,
// u8Enable:  =1: enable�жϣ�=0: disable�ж�
// ���ز����� ��
//**********************************************************************
void SMDrv_GPIO_EnableInterrupt(uint32 u32PinNum,uint8 u8Enable)
{
    if(u32PinNum >= IO_UNKNOW)
        return ;

    if(Smdrv_IsSpiCs(u32PinNum))
        return ;

    if(u8Enable == TRUE)
        am_hal_gpio_interrupt_enable(AM_HAL_GPIO_BIT(u32PinNum));
    else
        am_hal_gpio_interrupt_disable(AM_HAL_GPIO_BIT(u32PinNum));
}

//**********************************************************************
// ��������:  ����GPIO�ж����ȼ�
// ��������� prio:�ж����ȼ���bit0~2λֵ��Ч
// ���ز����� ��
//**********************************************************************
void SMDrv_GPIO_SetIrqPrio(uint32 prio)
{
#if AM_CMSIS_REGS
    NVIC_SetPriority(GPIO_IRQn,prio);
#else
    am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_GPIO, AM_HAL_INTERRUPT_PRIORITY(prio));
#endif
}

//**********************************************************************
// ��������:  ��GPIO disable������ʵ�ֵ͹���
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� Ret_InvalidParam,Ret_OK
//**********************************************************************
ret_type SMDrv_GPIO_Close(uint32 u32PinNum)
{
    am_hal_gpio_pincfg_t bfGpioCfg = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    uint32 ret;

    if(u32PinNum >= IO_UNKNOW)
        return Ret_InvalidParam;

    if(Smdrv_IsSpiCs(u32PinNum))
        return Ret_OK;

    bfGpioCfg.uFuncSel       = 3,
    bfGpioCfg.eDriveStrength = AM_HAL_GPIO_PIN_DRIVESTRENGTH_2MA;
    bfGpioCfg.eGPOutcfg      = AM_HAL_GPIO_PIN_OUTCFG_DISABLE;
    if((ret = am_hal_gpio_pinconfig(u32PinNum, bfGpioCfg)) != AM_HAL_STATUS_SUCCESS)
    {
        Err_Info((0,"Error - GPIO close pin config failed:%d\n",ret));
        return Ret_Fail;
    }

    return Ret_OK;
}

//**********************************************************************
// ��������:  ����pin������ߵ�ƽ
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� Ret_InvalidParam,Ret_OK
//**********************************************************************
ret_type SMDrv_GPIO_BitSet(uint32 u32PinNum)
{
    uint32 ret;
    if(u32PinNum >= IO_UNKNOW)
        return Ret_InvalidParam;

    if(Smdrv_IsSpiCs(u32PinNum))
        return Ret_OK;

    if((ret = am_hal_gpio_state_write(u32PinNum, AM_HAL_GPIO_OUTPUT_SET)) != AM_HAL_STATUS_SUCCESS)
    {
        Err_Info((0,"Error - GPIO set failed:%d\n",ret));
        return Ret_Fail;
    }
    return Ret_OK;
}

//**********************************************************************
// ��������:  ����pin������͵�ƽ
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� Ret_InvalidParam,Ret_OK
//**********************************************************************
ret_type SMDrv_GPIO_BitClear(uint32 u32PinNum)
{
    uint32 ret;
    if(u32PinNum >= IO_UNKNOW)
        return Ret_InvalidParam;

    if(Smdrv_IsSpiCs(u32PinNum))
        return Ret_OK;

    if((ret = am_hal_gpio_state_write(u32PinNum, AM_HAL_GPIO_OUTPUT_CLEAR)) != AM_HAL_STATUS_SUCCESS)
    {
        Err_Info((0,"Error - GPIO clear failed:%d\n",ret));
        return Ret_Fail;
    }
    return Ret_OK;
}

//**********************************************************************
// ��������:  ��pin�������ƽ��ת
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� Ret_InvalidParam,Ret_OK
//**********************************************************************
ret_type SMDrv_GPIO_BitToggle(uint32 u32PinNum)
{
    uint32 ret;
    if(u32PinNum >= IO_UNKNOW)
        return Ret_InvalidParam;

    if(Smdrv_IsSpiCs(u32PinNum))
        return Ret_OK;

    if((ret = am_hal_gpio_state_write(u32PinNum, AM_HAL_GPIO_OUTPUT_TOGGLE)) != AM_HAL_STATUS_SUCCESS)
    {
        Err_Info((0,"Error - GPIO toggle failed:%d\n",ret));
        return Ret_Fail;
    }
    return Ret_OK;
}

//**********************************************************************
// ��������:  �������ȡ�Ĵ����л�ȡpin�ŵ�ƽֵ
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� 0xFFFFFFFF:������������ֵΪ��ȡ����ֵ
//**********************************************************************
uint32 SMDrv_GPIO_InBitRead(uint32 u32PinNum)
{
    uint32_t u32State;
    uint32 ret;

    if(u32PinNum >= IO_UNKNOW)
        return 0xFFFFFFFF;

    if(Smdrv_IsSpiCs(u32PinNum))
        return 0xFFFFFFFF;

    if((ret = am_hal_gpio_state_read(u32PinNum,AM_HAL_GPIO_INPUT_READ, &u32State)) != AM_HAL_STATUS_SUCCESS)
        Err_Info((0,"Error - GPIO read in failed:%d\n",ret));
    return u32State;
}

//**********************************************************************
// ��������:  ����������Ĵ����л�ȡpin�ŵ�ƽֵ
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� 0xFFFFFFFF:������������ֵΪ��ȡ����ֵ
//**********************************************************************
uint32 SMDrv_GPIO_OutBitRead(uint32 u32PinNum)
{
    uint32_t u32State;    
    uint32 ret;

    if(u32PinNum >= IO_UNKNOW)
        return 0xFFFFFFFF;

    if(Smdrv_IsSpiCs(u32PinNum))
        return 0xFFFFFFFF;

    if((ret = am_hal_gpio_state_read(u32PinNum,AM_HAL_GPIO_OUTPUT_READ, &u32State)) != AM_HAL_STATUS_SUCCESS)
        Err_Info((0,"Error - GPIO read out failed:%d\n",ret));
    return u32State;
}

#else

typedef struct
{
   uint32  pin;           //gpio pin��
   gpio_cb gpio_callback; //gpio�жϻص�����
}gpio_irq_s;

//����GPIO�ж���
#define GPIO_INT_MAX 10

//��¼ע���GPIO�жϵ�pin��callback���Լ�����
static gpio_irq_s gpio_int[GPIO_INT_MAX];
uint8 u8IntCount =0;

//**********************************************************************
// ��������:    GPIO�жϷ�����
// ���������    ��
// ���ز�����    ��
//**********************************************************************
void am_gpio_isr(void)
{
    uint64 int_pin_value;
    uint32 gpio_id; 

    int_pin_value = am_hal_gpio_int_status_get(true);
    am_hal_gpio_int_clear(0xFFFFFFFFFFFFFFFF);

    for(gpio_id = 0; gpio_id < u8IntCount; gpio_id++)
    {
        if(AM_HAL_GPIO_BIT(gpio_int[gpio_id].pin) & int_pin_value)
        {
            if(gpio_int[gpio_id].gpio_callback != NULL)
            {
                gpio_int[gpio_id].gpio_callback(gpio_int[gpio_id].pin);
            }
        }
    }
}

//**********************************************************************
// ��������:    GPIO��ʼ��
// ���������    ��
// ���ز�����    ��
//**********************************************************************
void SMDrv_GPIO_Init(void)
{
     memset(gpio_int,0x00,sizeof(gpio_int));
     u8IntCount =0;
}

//**********************************************************************
// ��������: ����GPIO module ID����GPIO����:����/�������Ϊ�жϣ�������
//           �������жϷ������
// ���������u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
//    config_opt:����GPIO���ԣ����ڳ����иı�GPIO����ʱʹ�ã�����GPIOģ��
//      IICʱ��SDA��һ��Ϊ���룬һ��Ϊ�����
//      == NULL: ʹ��Ĭ�ϵ��������ã� != NULL: ��ʹ�ô��������
//    g_callback:�жϷ�����callback
// ���ز���: Ret_OK��Ret_InvalidParam
//**********************************************************************
ret_type SMDrv_GPIO_Open(uint32 u32PinNum,uint32 *config_opt,gpio_cb g_callback)
{
    uint32 u32Pin,bgpio_irq = 0;
    uint32 gpio_conf = AM_HAL_PIN_OUTPUT, gpio_pol = AM_HAL_GPIO_FALLING;

    if(u32PinNum >= IO_UNKNOW)
        return Ret_InvalidParam; 

    //step 1:�������Ϊ�жϣ������жϷ�����򣬲���ȡ��ӦGPIOֵ
    if(u8IntCount < GPIO_INT_MAX)
    {
        if(g_callback != NULL)
        {
            for(u32Pin = 0; u32Pin < GPIO_INT_MAX; u32Pin++)
            {
                //Ҫע����ж�gpio�Ѿ�ע���
                if(gpio_int[u32Pin].pin == u32PinNum)
                    break;
                if(gpio_int[u32Pin].gpio_callback == NULL)
                    break;
            }
            //ע����ж�GPIO������Ԥ�����ֵ
            if(u32Pin >= GPIO_INT_MAX)
                return Ret_InvalidParam; 

            //û��ע�����������ע��callback
            //if((u32Pin < GPIO_INT_MAX) && (gpio_int[u32Pin].gpio_callback != g_callback))
            if(gpio_int[u32Pin].gpio_callback != g_callback)
            {
                //���û��ע�������u8IntCount +=1
                if(gpio_int[u32Pin].gpio_callback == NULL)
                    u8IntCount++;
                gpio_int[u32Pin].gpio_callback = g_callback;
                gpio_int[u32Pin].pin = u32PinNum;
            }
        }
    }

    //step 2:����GPIO��Ĭ�����ԣ�����ԭ��ͼ
    if((u32PinNum == KEY_S0_PIN) || (u32PinNum == KEY_S1_PIN) ||(u32PinNum == KEY_S2_PIN))
    {
        bgpio_irq = 1;
        gpio_pol = AM_HAL_GPIO_FALLING;    //�½��ش���
        gpio_conf = AM_HAL_PIN_INPUT | AM_HAL_GPIO_PULL24K;
    }
    else if((u32PinNum == HR_INT1_PIN) ||(u32PinNum == BLE_RDY_PIN))
    {
        bgpio_irq = 1;
        gpio_pol = AM_HAL_GPIO_RISING;    //�����ش���
        gpio_conf = AM_HAL_PIN_INPUT;
        
    }else if ((u32PinNum == HR_INT2_PIN) || (u32PinNum == BAT_CHG_PIN) || (u32PinNum == BAT_PG_PIN))
    {
        gpio_conf = AM_HAL_PIN_INPUT;
        if(u32PinNum == BAT_CHG_PIN)
        {
            gpio_conf |= AM_HAL_GPIO_PULL6K;
        }
    }
    else
    {
        gpio_conf = AM_HAL_PIN_OUTPUT;   //GPIO����Ϊ���
    }
            
    //step 3:����pin�������������������
    if(config_opt != NULL)
    {
        //���������������GPIO���ԵĲ�������ʹ�ô����ֵ������ʹ��Ĭ�����õ�ֵ
        gpio_conf = *config_opt;
    }
    am_hal_gpio_pin_config(u32PinNum, gpio_conf);

    //step 4:�ж�ģʽ����GPIO������Ϊ�ж�
    if(bgpio_irq == 1)
    {
        //am_hal_gpio_int_set(AM_HAL_GPIO_BIT(u32PinNum));
        if(u32PinNum != HR_INT2_PIN)
        {
            am_hal_gpio_int_polarity_bit_set(u32PinNum,gpio_pol);  
            am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(u32PinNum));
            if(u32PinNum != BLE_RDY_PIN) //BLE EM9304 open��ʱ���ݲ���Ҫenable
            {
                am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(u32PinNum));
            }
        }
    }

    return Ret_OK;
}

//**********************************************************************
// ��������:  ���������жϴ�������
// ��������� u32PinNum: gpio num,
//   u32pol:  =1: �����أ�=0: �½���
// ���ز����� ��
//**********************************************************************
void SMDrv_GPIO_ReConfigIrq(uint32 u32PinNum,uint32 u32pol)
{
    uint32 ui32Polarity;

    ui32Polarity = (u32pol == 1)?AM_HAL_GPIO_RISING:AM_HAL_GPIO_FALLING;
    am_hal_interrupt_disable(AM_HAL_INTERRUPT_GPIO);
    am_hal_gpio_int_disable(AM_HAL_GPIO_BIT(u32PinNum));
    am_hal_gpio_int_polarity_bit_set(u32PinNum,ui32Polarity);
    am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(u32PinNum));
    am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(u32PinNum));
    am_hal_interrupt_enable(AM_HAL_INTERRUPT_GPIO);
}

//**********************************************************************
// ��������:  ����/�ر�pin���ж�
// ��������� u32PinNum: gpio num,
// u8Enable:  =1: enable�жϣ�=0: disable�ж�
// ���ز����� ��
//**********************************************************************
void SMDrv_GPIO_EnableInterrupt(uint32 u32PinNum,uint8 u8Enable)
{
    if(u8Enable == TRUE)
        am_hal_gpio_int_enable(AM_HAL_GPIO_BIT(u32PinNum));
    else
        am_hal_gpio_int_disable(AM_HAL_GPIO_BIT(u32PinNum));
}

//**********************************************************************
// ��������:  ����GPIO�ж����ȼ�
// ��������� prio:�ж����ȼ���bit0~2λֵ��Ч
// ���ز����� ��
//**********************************************************************
void SMDrv_GPIO_SetIrqPrio(uint32 prio)
{
    am_hal_interrupt_priority_set(AM_HAL_INTERRUPT_GPIO, AM_HAL_INTERRUPT_PRIORITY(prio));
}

//**********************************************************************
// ��������:  ����GPIOΪ����ģʽ����uart��iic��spi��pdm��
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
//            u32config: gpio pad
// ���ز����� ��
//**********************************************************************
void SMDrv_GPIO_SetIOPad(uint32 u32PinNum,uint32 u32config)
{
    am_hal_gpio_pin_config(u32PinNum, u32config);
}

//**********************************************************************
// ��������:  ��GPIO disable������ʵ�ֵ͹���
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� Ret_InvalidParam,Ret_OK
//**********************************************************************
ret_type SMDrv_GPIO_Close(uint32 u32PinNum)
{
    uint32 u32Pin;

    if(u32PinNum >= IO_UNKNOW)
        return Ret_InvalidParam;

    for(u32Pin = 0; u32Pin < GPIO_INT_MAX; u32Pin++)
    {
        //�ж�gpio�Ѿ�ע���,�����callback����pin���Ǳ���ԭ����ֵ
        if(gpio_int[u32Pin].pin == u32PinNum)
        {
            gpio_int[u32Pin].gpio_callback = NULL;
            u8IntCount--;

            am_hal_gpio_int_disable(AM_HAL_GPIO_BIT(u32PinNum)); //disable �ж�
            am_hal_gpio_int_clear(AM_HAL_GPIO_BIT(u32PinNum));
            break;
        }
    }

    am_hal_gpio_pin_config(u32PinNum, AM_HAL_PIN_DISABLE);
    return Ret_OK;
}

//**********************************************************************
// ��������:  ����pin������ߵ�ƽ
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� Ret_InvalidParam,Ret_OK
//**********************************************************************
ret_type SMDrv_GPIO_BitSet(uint32 u32PinNum)
{
#if 0    //�ڼ�for�ж��ж�pin������IOģ��iic/spiʱ��Ӱ���ٶ�
    uint32 u32Pin;

    if(u32PinNum >= IO_UNKNOW)
        return Ret_InvalidParam;

    //��Ϊ�ж�ʹ��GPIO�������ֶ���������ߵ͵�ƽ
    for(u32Pin = 0; u32Pin < GPIO_INT_MAX; u32Pin++)
    {
        if((gpio_int[u32Pin].pin == u32PinNum) && (gpio_int[u32Pin].gpio_callback != NULL))
            return Ret_OK;
    }        
#endif

    am_hal_gpio_out_bit_set(u32PinNum);
    return Ret_OK;
}

//**********************************************************************
// ��������:  ����pin������͵�ƽ
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� Ret_InvalidParam,Ret_OK
//**********************************************************************
ret_type SMDrv_GPIO_BitClear(uint32 u32PinNum)
{
#if 0    //�ڼ�for�ж��ж�pin������IOģ��iic/spiʱ��Ӱ���ٶ�
    uint32 u32Pin;

    if(u32PinNum >= IO_UNKNOW)
        return Ret_InvalidParam;

    //��Ϊ�ж�ʹ��GPIO�������ֶ���������ߵ͵�ƽ
    for(u32Pin = 0; u32Pin < GPIO_INT_MAX; u32Pin++)
    {
        if((gpio_int[u32Pin].pin == u32PinNum) && (gpio_int[u32Pin].gpio_callback != NULL))
            return Ret_OK;
    }
#endif

    am_hal_gpio_out_bit_clear(u32PinNum);
    return Ret_OK;
}

//**********************************************************************
// ��������:  ��pin�������ƽ��ת
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� Ret_InvalidParam,Ret_OK
//**********************************************************************
ret_type SMDrv_GPIO_BitToggle(uint32 u32PinNum)
{
#if 0    //�ڼ�for�ж��ж�pin������IOģ��iic/spiʱ��Ӱ���ٶ�
    uint32 u32Pin;

    if(u32PinNum >= IO_UNKNOW)
        return Ret_InvalidParam;

    //�ж�GPIO�������ֶ���������ߵ͵�ƽ
    for(u32Pin = 0; u32Pin < GPIO_INT_MAX; u32Pin++)
    {
        if((gpio_int[u32Pin].pin == u32PinNum) && (gpio_int[u32Pin].gpio_callback != NULL))
            return Ret_OK;
    }
#endif

    am_hal_gpio_out_bit_toggle(u32PinNum);
    return Ret_OK;
}

//**********************************************************************
// ��������:  �������ȡ�Ĵ����л�ȡpin�ŵ�ƽֵ
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� 0xFFFFFFFF:������������ֵΪ��ȡ����ֵ
//**********************************************************************
uint32 SMDrv_GPIO_InBitRead(uint32 u32PinNum)
{
    if(u32PinNum >= IO_UNKNOW)
        return 0xFFFFFFFF;

    return am_hal_gpio_input_bit_read(u32PinNum);
}

//**********************************************************************
// ��������:  ����������Ĵ����л�ȡpin�ŵ�ƽֵ
// ��������� u32PinNum: gpio num, ֵ�ο�io_config.h��IO����
// ���ز����� 0xFFFFFFFF:������������ֵΪ��ȡ����ֵ
//**********************************************************************
uint32 SMDrv_GPIO_OutBitRead(uint32 u32PinNum)
{
    if(u32PinNum >= IO_UNKNOW)
        return 0xFFFFFFFF;

    return am_hal_gpio_out_bit_read(u32PinNum);
}
#endif

