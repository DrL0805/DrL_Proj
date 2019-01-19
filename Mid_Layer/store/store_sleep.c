#include "app_variable.h"
#include "store_sleep.h"
#include "store_algo.h"
#include "scene_sleep.h"
#include "mid_rtc.h"

StoreInfo_t			SleepStoreInfo;
StoreSleepParam_t		StoreSleepParam;
 
static void Store_Sleep_ParamInit(void)
{
	SleepStoreInfo.Status = eStoreStatusNull;			// �洢״̬				
	
	SleepStoreInfo.CatalogBeginAddr = STORE2_SLEEP_CATALOG_BEGIN_ADDR;	// �̶�ֵ��Ŀ¼�洢��ʼ��ʼ
	SleepStoreInfo.CatalogEndAddr = STORE2_SLEEP_CATALOG_END_ADDR;		// �̶�ֵ��Ŀ¼�洢������ַ��������

	SleepStoreInfo.CatalogSerialMax = STORE2_SLEEP_MAX_ALLOT_CATALOG;		// �̶�ֵ�����Ŀ¼�����ɷ���Ĵ洢�ռ����
	SleepStoreInfo.CatalogSerialMaxSave = STORE2_SLEEP_MAX_SAVE_CATALOG;	// �̶�ֵ������������Ŀ¼
	SleepStoreInfo.CatalogSerialBegin = SleepStoreInfo.CatalogSerialMax - 1;	// ��Ч�洢Ŀ¼��ʼ��ţ���Ŀ¼Cnt����Ŀ¼MaxSave����ǰĿ¼Begin��Ǳ����ǣ�Ȼ��+1
	SleepStoreInfo.CatalogSerialEnd = SleepStoreInfo.CatalogSerialMax - 1;		// ��Ч�洢Ŀ¼������ţ�ÿ�δ���Ŀ¼ʱ+1
	SleepStoreInfo.CatalogSerialCnt = 0;		// �Ѵ洢Ŀ¼������ÿ�η��Ŀ¼ʱ+1����󲻳���MaxSave

	SleepStoreInfo.DataBeginAddr = STORE2_SLEEP_DATA_BEGIN_ADDR;	// �̶�ֵ�����ݴ洢��ʼ��ʼ
	SleepStoreInfo.DataEndAddr = STORE2_SLEEP_DATA_END_ADDR;	// �̶�ֵ�����ݴ洢������ַ��������	
	SleepStoreInfo.DataCurrAddr = SleepStoreInfo.DataBeginAddr;	// ��ǰ���ݴ洢��ַ
}

// �������㷽ʽ��ʼ��
void Store_Sleep_ClearInit(void)
{
	/* �洢������ʼ�� */
	Store_Sleep_ParamInit();
	
	/* �������flash���򣬷�ֹ֮ǰ�Ĵ������ݲ���Ӱ�� */
	Mid_NandFlash_Erase(SleepStoreInfo.CatalogBeginAddr, SleepStoreInfo.DataEndAddr);
	
	StoreSleepParam.InitFlg = true;
}

// ���ݻָ���ʽ��ʼ��
void Store_Sleep_RecoverInit(void)
{
	/* �洢������ʼ�� */
	Store_Sleep_ParamInit();
	
	/* ���ݻָ� */
	Store_Algo_CatalogRecover(&SleepStoreInfo);
	
	StoreSleepParam.InitFlg = true;
}

StoreInfo_t* Store_Sleep_StoreInfoGet(void)
{
	return &SleepStoreInfo;
}

StoreSleepParam_t* Store_Sleep_ParamPGet(void)
{
	return &StoreSleepParam;
}

/*******************************************************************************
 * Brief : �洢�㷨����洢ʱ����һ��
 * Input : @CurrUtc ��ǰUTCʱ�� 
		   @Sleep 	��洢��ֵ
 * Return: @NULL
 * Call  : ÿ5min����һ��
 ***************/
void Store_Sleep_algorithm(uint32_t Sleep)
{
	if(false == StoreSleepParam.InitFlg)
		return;	
	
	/* ����ǰû����Ŀ¼���򴴽� */
	if(eStoreStatusNull == SleepStoreInfo.Status)
	{
		Store_Sleep_CatalogCreate();
	}
	
	StoreSleepParam.LogBuf[StoreSleepParam.LogCnt*STORE2_SLEEP_DATA_CLASSIFY_LEN + 0] = Sleep >> 8;
	StoreSleepParam.LogBuf[StoreSleepParam.LogCnt*STORE2_SLEEP_DATA_CLASSIFY_LEN + 1] = Sleep;	
	StoreSleepParam.LogCnt++;
	
	// RAM�������󣬴浽flash
	if(StoreSleepParam.LogCnt >= STORE2_SLEEP_LOG_MAX)
	{
		Store_Sleep_DataSave();
	}
}


/*******************************************************************************
 * Brief : Ŀ¼����
 * Input : @CurrUtc ��ǰUTCʱ��
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Sleep_CatalogCreate(void)
{
	if(false == StoreSleepParam.InitFlg)
		return Ret_NoInit;
	
	if(eStoreStatusNull != SleepStoreInfo.Status)
		return Ret_DeviceBusy;	

	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	
	/* 
		Ŀ¼������ʼ����������������������Ϣ���ڵײ㺯���ͳһ����
		SleepStoreInfo.Catalog.Flash.Info.DataAddr = SleepStoreInfo.DataCurrAddr;
		SleepStoreInfo.Catalog.Flash.Info.Mark = eCatalogMarkUsing;	
	*/
	SleepStoreInfo.Catalog.User.Info.DataClassify = eDataClassifySleep;
	SleepStoreInfo.Catalog.User.Info.UTC = lMidRTC->UTC;
	Store_Algo_CatalogCreate(&SleepStoreInfo);

	// ����Ŀ¼��log��������
	StoreSleepParam.LogCnt = 0;	
	
	return Ret_OK;
}

// ���ݴ洢
uint16_t Store_Sleep_DataSave(void)
{
	/* �ܲ����ݴ洢 */
	Store_Algo_DataSave(&SleepStoreInfo, StoreSleepParam.LogBuf, StoreSleepParam.LogCnt*STORE2_SLEEP_DATA_CLASSIFY_LEN);
	
	/* ���RAM���� */
	StoreSleepParam.LogCnt = 0;
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : Ŀ¼���
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Sleep_CatalogSeal(void)
{
	if(false == StoreSleepParam.InitFlg)
		return Ret_NoInit;	
	
	if(eStoreStatusIng != SleepStoreInfo.Status)
		return Ret_NoInit;	
	
	sleep_record_t lsleepRecord;
	
	/* ���ǰ����һ��RAM������ */
	if(StoreSleepParam.LogCnt)
	{
		Store_Sleep_DataSave();
	}
	
	/* ��ȡ��ǰ˯�ߵ�����Ϣ */
	Scene_Sleep_RecordGet(&lsleepRecord);	
	
	/* Ŀ¼��� */
	Store_Algo_CatalogSeal(&SleepStoreInfo, (uint8_t*)&lsleepRecord, sizeof(sleep_record_t));

	return Ret_OK;
}

/*******************************************************************************
 * Brief : ��ȡ���ݣ�������debug����
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Sleep_DataRead(void)
{
	CatalogInfo_t		lCatalog;
	uint8_t 		lDataBuf[512];
	uint32_t 		lDataLen = 0,lDataCnt = 0;
	uint32_t	lCatalogSerial;
	
	#if 1	// ����洢��Ϣ��ӡ
	STORE_SLEEP_RTT_LOG(0, "SleepStoreInfo Read: \n");
	STORE_SLEEP_RTT_LOG(0, "  .Status %d \n", SleepStoreInfo.Status);
	STORE_SLEEP_RTT_LOG(0, "  .CatalogBeginAddr 0x%X \n", SleepStoreInfo.CatalogBeginAddr);
	STORE_SLEEP_RTT_LOG(0, "  .CatalogEndAddr 0x%X \n", SleepStoreInfo.CatalogEndAddr);
	STORE_SLEEP_RTT_LOG(0, "  .CatalogSerialMax %d \n", SleepStoreInfo.CatalogSerialMax);
	STORE_SLEEP_RTT_LOG(0, "  .CatalogSerialMaxSave %d \n", SleepStoreInfo.CatalogSerialMaxSave);
	STORE_SLEEP_RTT_LOG(0, "  .CatalogSerialBegin %d \n", SleepStoreInfo.CatalogSerialBegin);
	STORE_SLEEP_RTT_LOG(0, "  .CatalogSerialEnd %d \n", SleepStoreInfo.CatalogSerialEnd);
	STORE_SLEEP_RTT_LOG(0, "  .CatalogSerialCnt %d \n", SleepStoreInfo.CatalogSerialCnt);
	STORE_SLEEP_RTT_LOG(0, "  .DataBeginAddr 0x%X \n", SleepStoreInfo.DataBeginAddr);
	STORE_SLEEP_RTT_LOG(0, "  .DataEndAddr 0x%X \n", SleepStoreInfo.DataEndAddr);
	STORE_SLEEP_RTT_LOG(0, "  .DataCurrAddr 0x%X \n", SleepStoreInfo.DataCurrAddr);
	#endif
	
	#if 1	// Ŀ¼��ӡ
	lCatalogSerial = SleepStoreInfo.CatalogSerialBegin;
	for(uint32_t k = 0;k < SleepStoreInfo.CatalogSerialCnt;k++)
	{
		#if 1 /* Ŀ¼��Ϣ */
		Store_Algo_CatalogRead(&SleepStoreInfo, lCatalogSerial, &lCatalog);
		STORE_SLEEP_RTT_LOG(0, "Store_Algo_CatalogRead %d :\n", lCatalogSerial);
		STORE_SLEEP_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
		STORE_SLEEP_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
		STORE_SLEEP_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
		STORE_SLEEP_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
		STORE_SLEEP_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
		STORE_SLEEP_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
		#endif
		
		#if 1 /* Ŀ¼������Ϣ�� */
			
			#if 0	/* Ŀ¼������Ϣ����ӡԭʼ���� */
			Store_Algo_CatalogExtRead(&SleepStoreInfo, lCatalogSerial, lDataBuf, lCatalog.User.Info.ExtDataLen);
			STORE_SLEEP_RTT_LOG(0, "Store_Algo_CatalogExtRead %d \n", lCatalog.User.Info.ExtDataLen);
			for(uint32_t t = 0;t < lCatalog.User.Info.ExtDataLen;t++)
			{
				if((0 == t%32) && (0 != t))
				{
					STORE_SLEEP_RTT_LOG(0, "\n");
					vTaskDelay(5);
				}
				STORE_SLEEP_RTT_LOG(0, "%02X ", lDataBuf[t]);
			}STORE_SLEEP_RTT_LOG(0, "\n");
			#endif
			
			#if 1	/* Ŀ¼������Ϣ��ת��Ϊ˯����Ϣ�ṹ�� */
			sleep_record_t lsleepRecord;
			Store_Algo_CatalogExtRead(&SleepStoreInfo, lCatalogSerial, (uint8_t*)&lsleepRecord, lCatalog.User.Info.ExtDataLen);
			STORE_SLEEP_RTT_LOG(0, "	record: %d %d %d %d %d %d %d %d \n", 
				lsleepRecord.StartHour, lsleepRecord.StartMin, lsleepRecord.StopHour, lsleepRecord.StopMin,
				lsleepRecord.StartUTC, lsleepRecord.StopUTC, lsleepRecord.SleepDuration, lsleepRecord.Quality);
			STORE_SLEEP_RTT_LOG(0, "	record: %d %d %d %d %d %d \n", 
				lsleepRecord.TotalDuration, lsleepRecord.WakeDuration, lsleepRecord.LightDuration, lsleepRecord.DeepDuration,
				lsleepRecord.RemDuration, lsleepRecord.SegmentCnt);
			for(uint32_t i = 0;i < lsleepRecord.SegmentCnt;i++)
			{
				STORE_SLEEP_RTT_LOG(0, "		%d Segment : %d %d \n", 
				i, lsleepRecord.SleepData[i].State, lsleepRecord.SleepData[i].Duration);
			}
			#endif
			
		#endif
		
		#if 0	/* ��ӡ���� */
		STORE_SLEEP_RTT_LOG(0, "Store_Algo_DataRead \n");
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
			Store_Algo_DataRead(&SleepStoreInfo, &lCatalog, lDataCnt-lDataLen, lDataBuf, lDataLen);
			for(uint32_t t = 0;t < lDataLen;t++)
			{
				if((0 == t%28) && (0 != t))
				{
					STORE_SLEEP_RTT_LOG(0, "\n");
				}
				STORE_SLEEP_RTT_LOG(0, "%02X ", lDataBuf[t]);
			}STORE_SLEEP_RTT_LOG(0, "\n");
		}while(lDataCnt != lCatalog.Flash.Info.DataLen);
		#endif
		
		// ��һĿ¼
		lDataCnt = 0;
		lDataLen = 0;
		lCatalogSerial = Store_Algo_NextCatalogGet(&SleepStoreInfo, lCatalogSerial);
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
uint16_t Store_Sleep_CatalogAllUpload(void)
{
	Store_Algo_CatalogAllUpload(&SleepStoreInfo);
	
	return Ret_OK;	
}

/*******************************************************************************
 * Brief : ����洢�洢��RAM�е�����
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Store_Sleep_RamDataClear(void)
{
	StoreSleepParam.LogCnt = 0;
	
	Store_Algo_CatalogClear(&SleepStoreInfo);
}

// ģ����������ݣ����ڲ���
#define SLEEP_DATE_SIMULATA_LEN	(189)
void Store_Sleep_DateSimulata(void)
{
	STORE_SLEEP_RTT_LOG(0, "Store_Sleep_DateSimulata \n");
	
	#if 0

	#endif
}
















