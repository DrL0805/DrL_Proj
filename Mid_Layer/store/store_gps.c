#include "app_variable.h"
#include "store_gps.h"
#include "store_algo.h"
#include "scene_step.h"
#include "mid_rtc.h"

StoreInfo_t			GPSStoreInfo;
StoreGPSParam_t		StoreGPSParam;

static void Store_GPS_ParamInit(void)
{
	GPSStoreInfo.Status = eStoreStatusNull;			// �洢״̬				
	
	GPSStoreInfo.CatalogBeginAddr = STORE2_GPS_CATALOG_BEGIN_ADDR;	// �̶�ֵ��Ŀ¼�洢��ʼ��ʼ
	GPSStoreInfo.CatalogEndAddr = STORE2_GPS_CATALOG_END_ADDR;		// �̶�ֵ��Ŀ¼�洢������ַ��������

	GPSStoreInfo.CatalogSerialMax = STORE2_GPS_MAX_ALLOT_CATALOG;		// �̶�ֵ�����Ŀ¼�����ɷ���Ĵ洢�ռ����
	GPSStoreInfo.CatalogSerialMaxSave = STORE2_GPS_MAX_SAVE_CATALOG;	// �̶�ֵ������������Ŀ¼
	GPSStoreInfo.CatalogSerialBegin = GPSStoreInfo.CatalogSerialMax - 1;	// ��Ч�洢Ŀ¼��ʼ��ţ���Ŀ¼Cnt����Ŀ¼MaxSave����ǰĿ¼Begin��Ǳ����ǣ�Ȼ��+1
	GPSStoreInfo.CatalogSerialEnd = GPSStoreInfo.CatalogSerialMax - 1;		// ��Ч�洢Ŀ¼������ţ�ÿ�δ���Ŀ¼ʱ+1
	GPSStoreInfo.CatalogSerialCnt = 0;		// �Ѵ洢Ŀ¼������ÿ�η��Ŀ¼ʱ+1����󲻳���MaxSave

	GPSStoreInfo.DataBeginAddr = STORE2_GPS_DATA_BEGIN_ADDR;	// �̶�ֵ�����ݴ洢��ʼ��ʼ
	GPSStoreInfo.DataEndAddr = STORE2_GPS_DATA_END_ADDR;	// �̶�ֵ�����ݴ洢������ַ��������	
	GPSStoreInfo.DataCurrAddr = GPSStoreInfo.DataBeginAddr;	// ��ǰ���ݴ洢��ַ
}

// �������㷽ʽ��ʼ��
void Store_GPS_ClearInit(void)
{
	/* �洢������ʼ�� */
	Store_GPS_ParamInit();
	
	/* �������flash���򣬷�ֹ֮ǰ�Ĵ������ݲ���Ӱ�� */
	Mid_NandFlash_Erase(GPSStoreInfo.CatalogBeginAddr, GPSStoreInfo.DataEndAddr);
	
	StoreGPSParam.InitFlg = true;
}

// ���ݻָ���ʽ��ʼ��
void Store_GPS_RecoverInit(void)
{
	/* �洢������ʼ�� */
	Store_GPS_ParamInit();
	
	/* ���ݻָ� */
	Store_Algo_CatalogRecover(&GPSStoreInfo);
	
	StoreGPSParam.InitFlg = true;
}

StoreInfo_t* Store_GPS_StoreInfoGet(void)
{
	return &GPSStoreInfo;
}

StoreGPSParam_t* Store_GPS_ParamPGet(void)
{
	return &StoreGPSParam;
}

/*******************************************************************************
 * Brief : �ܲ��洢�㷨����洢ʱ����һ��
 * Input : @CurrUtc ��ǰUTCʱ�� 
		   @GPS 	��洢��ֵ
 * Return: @NULL
 * Call  : 
 ***************/
void Store_GPS_algorithm(void)
{
	if(false == StoreGPSParam.InitFlg)
		return;	
	
	int16 		LongitudeBias;	// ���Ȳ�ֵ
	int16 		LatitudeBias;	// γ�Ȳ�ֵ
	int8		AltitudeBias;	// ���β�ֵ
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
	
	/* ����ǰû����Ŀ¼���򴴽� */
	if(eStoreStatusNull == GPSStoreInfo.Status)
	{
		Store_GPS_CatalogCreate();
	}
	
	if(1)	// GPS��λ�ɹ�
	{
		if(StoreGPSParam.Algo.NewCatalogFlg)
		/* �״ζ�λ�ɹ�������GPS���״ζ�λ���� */
		{
			StoreGPSParam.Algo.NewCatalogFlg = false;
			StoreGPSParam.Algo.BeginLongitude = 0;
			StoreGPSParam.Algo.BeginLatitude = 0;
			StoreGPSParam.Algo.BeginAltitude = 0;
			StoreGPSParam.Algo.GPSValidUTC = lMidRTC->UTC;
		}
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 1] = LongitudeBias >> 8;	// ���Ȳ�ֵ
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 2] = LongitudeBias;	
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 3] = LatitudeBias >> 8;	// γ�Ȳ�ֵ	
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 4] = LatitudeBias;
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 5] = AltitudeBias;			// ���β�ֵ
		
		
		StoreGPSParam.Algo.LastLongitude = 0;
		StoreGPSParam.Algo.LastLatitude = 0;
		StoreGPSParam.Algo.LastAltitude = 0;
		StoreGPSParam.Algo.LastStep = 0;
	}
	else
	{
		
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 1] = LongitudeBias >> 8;	// ���Ȳ�ֵ
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 2] = LongitudeBias;	
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 3] = LatitudeBias >> 8;	// γ�Ȳ�ֵ	
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 4] = LatitudeBias;
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 5] = AltitudeBias;			// ���β�ֵ	
	}
	
	StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 0] = 2;					// ʱ���ۼ�
	StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 6] = 0;					// ����
	StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 7] = lpSceneStepParam->totalStep - StoreGPSParam.Algo.LastStep; // ������ֵ	

	StoreGPSParam.LogCnt++;
	
	// RAM�������󣬴浽flash
	if(StoreGPSParam.LogCnt >= STORE2_GPS_LOG_MAX)
	{
		Store_GPS_DataSave();
	}
}


/*******************************************************************************
 * Brief : �ܲ�����Ŀ¼����
 * Input : @CurrUtc ��ǰUTCʱ��
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_GPS_CatalogCreate(void)
{
	if(false == StoreGPSParam.InitFlg)
		return Ret_NoInit;
	
	if(eStoreStatusNull != GPSStoreInfo.Status)
		return Ret_DeviceBusy;	
	
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();

	/* 
		Ŀ¼������ʼ����������������������Ϣ���ڵײ㺯���ͳһ����
		GPSStoreInfo.Catalog.Flash.Info.DataAddr = GPSStoreInfo.DataCurrAddr;
		GPSStoreInfo.Catalog.Flash.Info.Mark = eCatalogMarkUsing;	
	*/
	GPSStoreInfo.Catalog.User.Info.DataClassify = eDataClassifyGPS;
	GPSStoreInfo.Catalog.User.Info.UTC = lMidRTC->UTC;
	Store_Algo_CatalogCreate(&GPSStoreInfo);

	// ����Ŀ¼��log��������
	StoreGPSParam.LogCnt = 0;
	StoreGPSParam.Algo.NewCatalogFlg = true;
	StoreGPSParam.Algo.BeginUTC = lMidRTC->UTC;
	
	return Ret_OK;
}

// �ܲ����ݴ洢
uint16_t Store_GPS_DataSave(void)
{
	/* �ܲ����ݴ洢 */
	Store_Algo_DataSave(&GPSStoreInfo, StoreGPSParam.LogBuf, StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN);
	
	/* ���RAM���� */
	StoreGPSParam.LogCnt = 0;
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : �ܲ�����Ŀ¼���
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_GPS_CatalogSeal(void)
{
	if(false == StoreGPSParam.InitFlg)
		return Ret_NoInit;	
	
	if(eStoreStatusIng != GPSStoreInfo.Status)
		return Ret_NoInit;	
	
	/* ���ǰ����һ��RAM������ */
	if(StoreGPSParam.LogCnt)
	{
		Store_GPS_DataSave();
	}	
	
	/* Ŀ¼��� */
	Store_Algo_CatalogSeal(&GPSStoreInfo, NULL, 0);

	return Ret_OK;
}

/*******************************************************************************
 * Brief : ��ȡ�ܲ����ݣ�������debug����
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_GPS_DataRead(void)
{
	CatalogInfo_t		lCatalog;
	uint8_t 		lDataBuf[512];
	uint32_t 		lDataLen = 0,lDataCnt = 0;
	uint32_t	lCatalogSerial;
	
	#if 1	// ����洢��Ϣ��ӡ
	STORE_GPS_RTT_LOG(0, "GPSStoreInfo Read: \n");
	STORE_GPS_RTT_LOG(0, "  .Status %d \n", GPSStoreInfo.Status);
	STORE_GPS_RTT_LOG(0, "  .CatalogBeginAddr 0x%X \n", GPSStoreInfo.CatalogBeginAddr);
	STORE_GPS_RTT_LOG(0, "  .CatalogEndAddr 0x%X \n", GPSStoreInfo.CatalogEndAddr);
	STORE_GPS_RTT_LOG(0, "  .CatalogSerialMax %d \n", GPSStoreInfo.CatalogSerialMax);
	STORE_GPS_RTT_LOG(0, "  .CatalogSerialMaxSave %d \n", GPSStoreInfo.CatalogSerialMaxSave);
	STORE_GPS_RTT_LOG(0, "  .CatalogSerialBegin %d \n", GPSStoreInfo.CatalogSerialBegin);
	STORE_GPS_RTT_LOG(0, "  .CatalogSerialEnd %d \n", GPSStoreInfo.CatalogSerialEnd);
	STORE_GPS_RTT_LOG(0, "  .CatalogSerialCnt %d \n", GPSStoreInfo.CatalogSerialCnt);
	STORE_GPS_RTT_LOG(0, "  .DataBeginAddr 0x%X \n", GPSStoreInfo.DataBeginAddr);
	STORE_GPS_RTT_LOG(0, "  .DataEndAddr 0x%X \n", GPSStoreInfo.DataEndAddr);
	STORE_GPS_RTT_LOG(0, "  .DataCurrAddr 0x%X \n", GPSStoreInfo.DataCurrAddr);
	#endif
	
	#if 1	// Ŀ¼��ӡ
	lCatalogSerial = GPSStoreInfo.CatalogSerialBegin;
	for(uint32_t k = 0;k < GPSStoreInfo.CatalogSerialCnt;k++)
	{
		#if 1 /* Ŀ¼��Ϣ */
		Store_Algo_CatalogRead(&GPSStoreInfo, lCatalogSerial, &lCatalog);
		STORE_GPS_RTT_LOG(0, "Store_Algo_CatalogRead %d :\n", lCatalogSerial);
		STORE_GPS_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
		STORE_GPS_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
		STORE_GPS_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
		STORE_GPS_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
		STORE_GPS_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
		STORE_GPS_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
		#endif
		
		#if 1 /* Ŀ¼������Ϣ */
		Store_Algo_CatalogExtRead(&GPSStoreInfo, lCatalogSerial, lDataBuf, lCatalog.User.Info.ExtDataLen);
		STORE_GPS_RTT_LOG(0, "Store_Algo_CatalogExtRead \n");
		for(uint32_t t = 0;t < lCatalog.User.Info.ExtDataLen;t++)
		{
			if((0 == t%32) && (0 != t))
			{
				STORE_GPS_RTT_LOG(0, "\n");
				vTaskDelay(5);
			}
			STORE_GPS_RTT_LOG(0, "%02X ", lDataBuf[t]);
		}STORE_GPS_RTT_LOG(0, "\n");
		#endif
		
		#if 1	/* ��ӡ���� */
		STORE_GPS_RTT_LOG(0, "Store_Algo_DataRead \n");
		do
		{
			if((lDataCnt+280) <= lCatalog.Flash.Info.DataLen)	// 14*20
			{
				lDataLen = 280;
				lDataCnt += 280;
			}
			else
			{
				lDataLen = lCatalog.Flash.Info.DataLen - lDataCnt;
				lDataCnt = lCatalog.Flash.Info.DataLen;
			}
			Store_Algo_DataRead(&GPSStoreInfo, &lCatalog, lDataCnt-lDataLen, lDataBuf, lDataLen);
			for(uint32_t t = 0;t < lDataLen;t++)
			{
				if((0 == t%28) && (0 != t))
				{
					STORE_GPS_RTT_LOG(0, "\n");
				}
				STORE_GPS_RTT_LOG(0, "%02X ", lDataBuf[t]);
			}STORE_GPS_RTT_LOG(0, "\n");
		}while(lDataCnt != lCatalog.Flash.Info.DataLen);
		#endif
		
		// ��һĿ¼
		lDataCnt = 0;
		lDataLen = 0;
		lCatalogSerial = Store_Algo_NextCatalogGet(&GPSStoreInfo, lCatalogSerial);
	}
	#endif

	return Ret_OK;	
}

/*******************************************************************************
 * Brief : ����Ŀ¼���ݱ��Ϊ���ϴ�����app��ɾ��������
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_GPS_CatalogAllUpload(void)
{
	Store_Algo_CatalogAllUpload(&GPSStoreInfo);
	
	return Ret_OK;	
}

/*******************************************************************************
 * Brief : ����洢�洢��RAM�е�����
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Store_GPS_RamDataClear(void)
{
	StoreGPSParam.LogCnt = 0;
	
	Store_Algo_CatalogClear(&GPSStoreInfo);
}


// ģ����������ݣ����ڲ���
#define GPS_DATE_SIMULATA_LEN	(189)
void Store_GPS_DateSimulata(void)
{
	STORE_GPS_RTT_LOG(0, "Store_GPS_DateSimulata \n");
	
	#if 0	// ����β���ݶ�д����
	Store_GPS_ClearInit();
	
	for(uint32_t lTmp = 0;lTmp < 2;lTmp++)
	{
		Store_GPS_CatalogCreate();
		for(uint32_t i = 0; i < GPS_DATE_SIMULATA_LEN + lTmp;i++)
		{
			Store_GPS_algorithm();
		}
		Store_GPS_CatalogSeal();	
	}

	#endif
	
	#if 1 // ������Ⱦ���ݣ�Ȼ��ָ����ݣ�Ȼ���ڶ�д����
	
		#if 0	// ��Ⱦ���ݣ�д�����ݣ����ǲ�����
		Store_GPS_ClearInit();
		
		// д����������
		for(uint32_t lTmp = 0;lTmp < 2;lTmp++)
		{
			Store_GPS_CatalogCreate();
			for(uint32_t i = 0; i < GPS_DATE_SIMULATA_LEN + lTmp;i++)
			{
				Store_GPS_algorithm();
			}
			Store_GPS_CatalogSeal();	
		}		
		
		// д�����ݣ��������Ŀ¼
		Store_GPS_CatalogCreate();
		for(uint32_t i = 0; i < GPS_DATE_SIMULATA_LEN;i++)
		{
			Store_GPS_algorithm();
		}
		#endif
	
	
		#if 0	// ���±����д���������ݣ��ٶ�ȡ����
		for(uint32_t lTmp = 0;lTmp < 2;lTmp++)
		{
			Store_GPS_CatalogCreate();
			for(uint32_t i = 0; i < GPS_DATE_SIMULATA_LEN + lTmp;i++)
			{
				Store_GPS_algorithm();
			}
			Store_GPS_CatalogSeal();	
		}
		#endif	
	
	#endif
}
























