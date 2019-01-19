#include "drv_ntc.h"
#include "io_config.h"
#include "sm_adc.h"
#include "sm_gpio.h"

/*******************const/variable define*******************/
//����ֵ,��λ:Kohm
static const uint16 ntcParaRes[] = {
   278, 263, 249, 236, 224, 213, 202, 191, 182, 172,
   164, 156, 148, 140, 134, 127, 121, 115, 109, 104, 
   99,  95,  90,  86,  82,  78,  75,  71,  68,  65, 
   62,  59,  57,  54,  52,  49,  47,  45,  43,  41,  
   40,  38,  36,  35,  33,  32,  31,  29,  28,  27,
   26,  25,  24,  23,  22,  21,  20,  19,  28,  17,
};

//�¶�ֵ
static const int16 ntcParaTemp[] = {
   -10, -9, -8,  -7,  -6,  -5,  -4,  -3,  -2,  -1,
   0,   1,   2,   3,   4,   5,   6,   7,   8,   9, 
   10,  11,  12,  13,  14,  15,  16,  17,  18,  19, 
   20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  
   30,  31,  32,  33,  34,  35,  36,  37,  38,  39,
   40,  41,  42,  43,  44,  45,  46,  47,  48,  49,
};

NTC_PARAM_T	NTC_PARAM = 
{
	.State = eNTCStateUninit,
	.TempErrFlg = false,
	.CurrTemp = 0,
	.UpLimitTemp = NTC_TMEPERATURE_UPMAX,
	.DownLimitTemp = NTC_TMEPERATURE_DOWNMAX,
	.CacheCnt = 0,
};
	
/*********************************************************************
 * Brief : ���ݵ��裬���ض�Ӧ�¶�ֵ������
 * Input : @ntcResVal  ����ֵ
 * Output: @NULL 
 * Return: �����¶����������
 * Call  : 
 ************/
static uint8 Drv_NTC_TempIndex(uint16 ntcResVal)
{
	uint8 index;
	uint8 i;

	for (i = 0; i < NTC_PARA_MAX;)
	{
		if (ntcResVal <= ntcParaRes[i])
		{
			i++;
		}
		else
		{
			break;
		}
	}
	index = i;

	if ((ntcParaRes[index] - ntcResVal) > (ntcResVal - ntcParaRes[index + 1]))
	{
		index += 1;
	}
	
	return index;
}

/*********************************************************************
 * Brief : �ɼ���ADCֵ��Ļص����������ݲɵ���ֵ������NTC����
 * Input : @u32adcValue  �ɼ�����ADCֵ
 * Output: @NULL 
 * Return: @NULL
 * Call  : @NULL
 ************/
static void Drv_NTC_IsrCb(uint32 u32adcValue)
{
    uint32 volvalue;
	float calTemp;
	float  ntctemp;
	uint32 mRT;
	int16  maxTemp,minTemp;
	uint8 	index;	
	
	 DRV_NTC_RTT_LOG(0,"u32adcValue %d \n",u32adcValue);
	
	// adcת��Ϊ��ѹֵ
	volvalue = (ADC_REF_VOL * u32adcValue) / ADC_FULL_LEVEL;	

    DRV_NTC_RTT_LOG(0,"Vol=%d mV \n",volvalue);

	// ���㵱ǰ��������ֵ
	mRT = (VDD_TOTAL * RES_TEST) / volvalue - RES_TEST;
	DRV_NTC_RTT_LOG(0,"mRT :%d\n", mRT);
	
	// �����ֵ���¶ȵĹ�ϵ���߻���
	index = Drv_NTC_TempIndex(mRT);
	if (index >= NTC_PARA_MAX)
	{
		index  = NTC_PARA_MAX - 1;
	}

	// ���浱ǰ�¶�ֵ
	NTC_PARAM.CacheLog[NTC_PARAM.CacheCnt++ & 0x0F] = ntcParaTemp[index];
	DRV_NTC_RTT_LOG(0,"ntcParaTemp :%d\n", ntcParaTemp[index]);
	
	
	if (NTC_PARAM.CacheCnt >= NTC_TEMP_CACHE_NUM)
	/* ����log�ﵽ�󣬿�ʼ�����¶�ֵ */ 
	{
		NTC_PARAM.CacheCnt = 0;

		// �ر�ADC����
		SMDrv_ADC_Close(BODY_TEMP_ADC_MODULE);
//		am_hal_gpio_output_clear(TEMP_VDD_PIN);	
		
        maxTemp       = NTC_PARAM.CacheLog[0];
        minTemp       = NTC_PARAM.CacheLog[0];
        calTemp         = 0;
		
        for(uint32_t cnt = 0; cnt < NTC_TEMP_CACHE_NUM; cnt ++)
        {
            if(maxTemp < NTC_PARAM.CacheLog[cnt])
                maxTemp   = NTC_PARAM.CacheLog[cnt];

            if(minTemp > NTC_PARAM.CacheLog[cnt])
                minTemp   = NTC_PARAM.CacheLog[cnt];

            calTemp         += NTC_PARAM.CacheLog[cnt];
        }

        ntctemp 		= (calTemp - minTemp - maxTemp) / (NTC_TEMP_CACHE_NUM - 2);
        NTC_PARAM.CurrTemp  = ntctemp * 100;

		DRV_NTC_RTT_LOG(0,"NTC_PARAM.CurrTemp :%d\n", NTC_PARAM.CurrTemp);
        
        if (NTC_PARAM.CurrTemp >= NTC_PARAM.UpLimitTemp || NTC_PARAM.CurrTemp < NTC_PARAM.DownLimitTemp)
        {
        	if (!NTC_PARAM.TempErrFlg)
        	{
//        		Mid_NTC_TempErrorCallBack();
        		NTC_PARAM.TempErrFlg = 1;
        	}
        	else
        	{
        		NTC_PARAM.TempErrFlg = 0;
        	}
        }
	}
	else
	/* ���治��������һ��ADC�ɼ� */
	{
		Drv_NTC_StartSample();
	}	
}

void Drv_NTC_Init(void)
{
	SMDrv_ADC_Init();
	SMDrv_ADC_SetIsrPrio(3);

	SMDrv_GPIO_Open(TEMP_VDD_PIN, NULL, NULL);	// TEMP_VDD
	am_hal_gpio_output_set(TEMP_VDD_PIN);
//	am_hal_gpio_output_clear(TEMP_VDD_PIN);		// ?????	// 100K���裬IO�����ߺ����Լ5uA����
}

void Drv_NTC_StartSample(void)
{
//	am_hal_gpio_output_set(TEMP_VDD_PIN);
	SMDrv_ADC_Open(BODY_TEMP_ADC_MODULE,Drv_NTC_IsrCb);	
	SMDrv_ADC_StartDetect();
}






