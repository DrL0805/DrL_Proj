#include "store_swim.h"
#include "store_algo.h"
#include "store_history.h"
#include "mid_rtc.h"
#include "scene_swim.h"

StoreInfo_t			SwimStoreInfo;
StoreSwimParam_t		StoreSwimParam;

/*******************************************************************************
 * Brief : �ܲ���������
 ******************************************************************************/
 
static void Store_Swim_ParamInit(void)
{
	SwimStoreInfo.Status = eStoreStatusNull;			// �洢״̬				
	
	SwimStoreInfo.CatalogBeginAddr = STORE2_SWIM_CATALOG_BEGIN_ADDR;	// �̶�ֵ��Ŀ¼�洢��ʼ��ʼ
	SwimStoreInfo.CatalogEndAddr = STORE2_SWIM_CATALOG_END_ADDR;		// �̶�ֵ��Ŀ¼�洢������ַ��������

	SwimStoreInfo.CatalogSerialMax = STORE2_SWIM_MAX_ALLOT_CATALOG;		// �̶�ֵ�����Ŀ¼�����ɷ���Ĵ洢�ռ����
	SwimStoreInfo.CatalogSerialMaxSave = STORE2_SWIM_MAX_SAVE_CATALOG;	// �̶�ֵ������������Ŀ¼
	SwimStoreInfo.CatalogSerialBegin = SwimStoreInfo.CatalogSerialMax - 1;	// ��Ч�洢Ŀ¼��ʼ��ţ���Ŀ¼Cnt����Ŀ¼MaxSave����ǰĿ¼Begin��Ǳ����ǣ�Ȼ��+1
	SwimStoreInfo.CatalogSerialEnd = SwimStoreInfo.CatalogSerialMax - 1;		// ��Ч�洢Ŀ¼������ţ�ÿ�δ���Ŀ¼ʱ+1
	SwimStoreInfo.CatalogSerialCnt = 0;		// �Ѵ洢Ŀ¼������ÿ�η��Ŀ¼ʱ+1����󲻳���MaxSave

	SwimStoreInfo.DataBeginAddr = STORE2_SWIM_DATA_BEGIN_ADDR;	// �̶�ֵ�����ݴ洢��ʼ��ʼ
	SwimStoreInfo.DataEndAddr = STORE2_SWIM_DATA_END_ADDR;	// �̶�ֵ�����ݴ洢������ַ��������	
	SwimStoreInfo.DataCurrAddr = SwimStoreInfo.DataBeginAddr;	// ��ǰ���ݴ洢��ַ
}

// �������㷽ʽ��ʼ��
void Store_Swim_ClearInit(void)
{
	/* �洢������ʼ�� */
	Store_Swim_ParamInit();
	
	/* �������flash���򣬷�ֹ֮ǰ�Ĵ������ݲ���Ӱ�� */
	Mid_NandFlash_Erase(SwimStoreInfo.CatalogBeginAddr, SwimStoreInfo.DataEndAddr);
	
	StoreSwimParam.InitFlg = true;
}

// ���ݻָ���ʽ��ʼ��
void Store_Swim_RecoverInit(void)
{
	/* �洢������ʼ�� */
	Store_Swim_ParamInit();
	
	/* ���ݻָ� */
	Store_Algo_CatalogRecover(&SwimStoreInfo);
	
	StoreSwimParam.InitFlg = true;
}

StoreInfo_t* Store_Swim_StoreInfoGet(void)
{
	return &SwimStoreInfo;
}

StoreSwimParam_t* Store_Swim_ParamPGet(void)
{
	return &StoreSwimParam;
}

/*******************************************************************************
 * Brief : �ܲ��洢�㷨����洢ʱ����һ��
 * Input : @CurrUtc ��ǰUTCʱ�� 
		   @SwimningInfo ��洢��ֵ
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Store_Swim_algorithm(void)
{
	if(false == StoreSwimParam.InitFlg)
		return;	

	swimIndoorInfo_t lswimIndoorInfo;
	Scene_Swim_InfoGet(&lswimIndoorInfo);	
	
	#if 1
	STORE_SWIM_RTT_LOG(0, "Store_Swim_algorithm: %d, %d, %d \n", 
		lswimIndoorInfo.RealTimeData.StrokeRate, lswimIndoorInfo.LapData.LapPace, lswimIndoorInfo.RealTimeData.HR);
	#endif	
	
	/* ����ǰû����Ŀ¼���򴴽� */
	if(eStoreStatusNull == SwimStoreInfo.Status)
	{
		Store_Swim_CatalogCreate();
	}

	// ��ˮ�ٶ�
	StoreSwimParam.LogBuf[StoreSwimParam.LogCnt*STORE2_SWIM_DATA_CLASSIFY_LEN + 0] = (uint8_t)(lswimIndoorInfo.RealTimeData.StrokeRate >> 8);  
	StoreSwimParam.LogBuf[StoreSwimParam.LogCnt*STORE2_SWIM_DATA_CLASSIFY_LEN + 1] = (uint8_t)(lswimIndoorInfo.RealTimeData.StrokeRate);
	// //����
	StoreSwimParam.LogBuf[StoreSwimParam.LogCnt*STORE2_SWIM_DATA_CLASSIFY_LEN + 2] = (uint8_t)(lswimIndoorInfo.LapData.LapPace >> 8);  
	StoreSwimParam.LogBuf[StoreSwimParam.LogCnt*STORE2_SWIM_DATA_CLASSIFY_LEN + 3] = (uint8_t)(lswimIndoorInfo.LapData.LapPace);
	// ����
	StoreSwimParam.LogBuf[StoreSwimParam.LogCnt*STORE2_SWIM_DATA_CLASSIFY_LEN + 4] = (uint8_t)(lswimIndoorInfo.RealTimeData.HR); 	
	
	StoreSwimParam.LogCnt++;
	
	// RAM�������󣬴浽flash
	if(StoreSwimParam.LogCnt >= STORE2_SWIM_LOG_MAX)
	{
		Store_Swim_DataSave();
	}
}


/*******************************************************************************
 * Brief : �ܲ�����Ŀ¼����
 * Input : @CurrUtc ��ǰUTCʱ��
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Swim_CatalogCreate(void)
{
	if(false == StoreSwimParam.InitFlg)
		return Ret_NoInit;
	
	if(eStoreStatusNull != SwimStoreInfo.Status)
		return Ret_DeviceBusy;	

	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	
	/* 
		Ŀ¼������ʼ����������������������Ϣ���ڵײ㺯���ͳһ����
		SwimStoreInfo.Catalog.Flash.Info.DataAddr = SwimStoreInfo.DataCurrAddr;
		SwimStoreInfo.Catalog.Flash.Info.Mark = eCatalogMarkUsing;	
	*/
	SwimStoreInfo.Catalog.User.Info.DataClassify = eDataClassifySwimNew;
	SwimStoreInfo.Catalog.User.Info.UTC = lMidRTC->UTC;
	Store_Algo_CatalogCreate(&SwimStoreInfo);

	// ����Ŀ¼��log��������
	StoreSwimParam.LogCnt = 0;	
	
	return Ret_OK;
}

// �ܲ����ݴ洢
uint16_t Store_Swim_DataSave(void)
{
	/* �ܲ����ݴ洢 */
	Store_Algo_DataSave(&SwimStoreInfo, StoreSwimParam.LogBuf, StoreSwimParam.LogCnt*STORE2_SWIM_DATA_CLASSIFY_LEN);
	
	/* ���RAM���� */
	StoreSwimParam.LogCnt = 0;
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : �ܲ�����Ŀ¼���
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Swim_CatalogSeal(void)
{
	if(false == StoreSwimParam.InitFlg)
		return Ret_NoInit;	
	
	if(eStoreStatusIng != SwimStoreInfo.Status)
		return Ret_NoInit;	

	swimIndoorInfo_t lswimIndoorInfo;
	StoreHistoryList_t lStoreHistoryList;
	
	/* ���ǰ����һ��RAM������ */
	if(StoreSwimParam.LogCnt)
	{
		Store_Swim_DataSave();
	}	
	
	/* ��ȡ��ǰ�˶��������� */
	Scene_Swim_InfoGet(&lswimIndoorInfo);	
	
	#if 1	// ��ӡ�洢��Ŀ¼������Ϣ
	STORE_SWIM_RTT_LOG(0, "Store_Swim_CatalogSeal %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d \n",
		lswimIndoorInfo.RecordData.StartUTC, lswimIndoorInfo.RecordData.StopUTC, lswimIndoorInfo.RecordData.Duration, 
		lswimIndoorInfo.RecordData.ValidDuration, lswimIndoorInfo.RecordData.Distance, lswimIndoorInfo.RecordData.Stroke, 
		lswimIndoorInfo.RecordData.Calorie, lswimIndoorInfo.RecordData.Laps, lswimIndoorInfo.RecordData.PaceAVG, 
		lswimIndoorInfo.RecordData.StrokeAVG, lswimIndoorInfo.RecordData.StrokeRateAVG, lswimIndoorInfo.RecordData.SwolfAvg, 
		lswimIndoorInfo.RecordData.HrAVG, lswimIndoorInfo.RecordData.HrMax, lswimIndoorInfo.RecordData.Style);
	#endif	
	
	/* Ŀ¼��� */
	Store_Algo_CatalogSeal(&SwimStoreInfo, (uint8_t*)&lswimIndoorInfo.RecordData, sizeof(swimIndoorRecord_t));

	/* ���ӵ��˶���ʷ�б� */
	lStoreHistoryList.CatalogSerial = SwimStoreInfo.CatalogSerialEnd;
	lStoreHistoryList.DataClassify = eDataClassifySwimNew;
	lStoreHistoryList.Distance = lswimIndoorInfo.RecordData.Distance;
	lStoreHistoryList.UTC = lswimIndoorInfo.RecordData.StartUTC;
	Store_History_ListAdd(&lStoreHistoryList);		
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : ��ȡ�ܲ����ݣ�������debug����
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Swim_DataRead(void)
{
	CatalogInfo_t		lCatalog;
	uint8_t 		lDataBuf[512];
	uint32_t 		lDataLen = 0,lDataCnt = 0;
	uint32_t	lCatalogSerial;
	
	#if 1	// ����洢��Ϣ��ӡ
	STORE_SWIM_RTT_LOG(0, "SwimStoreInfo Read: \n");
	STORE_SWIM_RTT_LOG(0, "  .Status %d \n", SwimStoreInfo.Status);
	STORE_SWIM_RTT_LOG(0, "  .CatalogBeginAddr 0x%X \n", SwimStoreInfo.CatalogBeginAddr);
	STORE_SWIM_RTT_LOG(0, "  .CatalogEndAddr 0x%X \n", SwimStoreInfo.CatalogEndAddr);
	STORE_SWIM_RTT_LOG(0, "  .CatalogSerialMax %d \n", SwimStoreInfo.CatalogSerialMax);
	STORE_SWIM_RTT_LOG(0, "  .CatalogSerialMaxSave %d \n", SwimStoreInfo.CatalogSerialMaxSave);
	STORE_SWIM_RTT_LOG(0, "  .CatalogSerialBegin %d \n", SwimStoreInfo.CatalogSerialBegin);
	STORE_SWIM_RTT_LOG(0, "  .CatalogSerialEnd %d \n", SwimStoreInfo.CatalogSerialEnd);
	STORE_SWIM_RTT_LOG(0, "  .CatalogSerialCnt %d \n", SwimStoreInfo.CatalogSerialCnt);
	STORE_SWIM_RTT_LOG(0, "  .DataBeginAddr 0x%X \n", SwimStoreInfo.DataBeginAddr);
	STORE_SWIM_RTT_LOG(0, "  .DataEndAddr 0x%X \n", SwimStoreInfo.DataEndAddr);
	STORE_SWIM_RTT_LOG(0, "  .DataCurrAddr 0x%X \n", SwimStoreInfo.DataCurrAddr);
	#endif
	
	#if 1	// Ŀ¼��ӡ
	lCatalogSerial = SwimStoreInfo.CatalogSerialBegin;
	for(uint32_t k = 0;k < SwimStoreInfo.CatalogSerialCnt;k++)
	{
		#if 1 /* Ŀ¼��Ϣ */
		Store_Algo_CatalogRead(&SwimStoreInfo, lCatalogSerial, &lCatalog);
		STORE_SWIM_RTT_LOG(0, "Store_Algo_CatalogRead %d :\n", lCatalogSerial);
		STORE_SWIM_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
		STORE_SWIM_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
		STORE_SWIM_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
		STORE_SWIM_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
		STORE_SWIM_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
		STORE_SWIM_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
		#endif
		
		#if 1 /* Ŀ¼������Ϣ */
		Store_Algo_CatalogExtRead(&SwimStoreInfo, lCatalogSerial, lDataBuf, lCatalog.User.Info.ExtDataLen);
		STORE_SWIM_RTT_LOG(0, "Store_Algo_CatalogExtRead \n");
		for(uint32_t t = 0;t < lCatalog.User.Info.ExtDataLen;t++)
		{
			if((0 == t%32) && (0 != t))
			{
				STORE_SWIM_RTT_LOG(0, "\n");
			}
			STORE_SWIM_RTT_LOG(0, "%02X ", lDataBuf[t]);
		}STORE_SWIM_RTT_LOG(0, "\n");
		#endif
		
		#if 1	/* ��ӡ���� */
		STORE_SWIM_RTT_LOG(0, "Store_Algo_DataRead \n");
		do
		{
			if((lDataCnt+200) <= lCatalog.Flash.Info.DataLen)	// 5*40
			{
				lDataLen = 200;
				lDataCnt += 200;
			}
			else
			{
				lDataLen = lCatalog.Flash.Info.DataLen - lDataCnt;
				lDataCnt = lCatalog.Flash.Info.DataLen;
			}
			Store_Algo_DataRead(&SwimStoreInfo, &lCatalog, lDataCnt-lDataLen, lDataBuf, lDataLen);
			for(uint32_t t = 0;t < lDataLen;t++)
			{
				if((0 == t%20) && (0 != t))
				{
					STORE_SWIM_RTT_LOG(0, "\n");
				}
				STORE_SWIM_RTT_LOG(0, "%02X ", lDataBuf[t]);
			}STORE_SWIM_RTT_LOG(0, "\n");
		}while(lDataCnt != lCatalog.Flash.Info.DataLen);
		#endif
		
		// ��һĿ¼
		lDataCnt = 0;
		lDataLen = 0;
		lCatalogSerial = Store_Algo_NextCatalogGet(&SwimStoreInfo, lCatalogSerial);
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
uint16_t Store_Swim_CatalogAllUpload(void)
{
	Store_Algo_CatalogAllUpload(&SwimStoreInfo);
	
	return Ret_OK;	
}



// ģ����������ݣ����ڲ���
#define SWIM_DATE_SIMULATA_LEN	(80)
void Store_Swim_DateSimulata(void)
{
	STORE_SWIM_RTT_LOG(0, "Store_Swim_DateSimulata \n");
	
	#if 0
	swimIndoorInfo_t swimIndoorInfo;
	
	Store_Swim_ClearInit();
	
	for(uint32_t t = 0;t < 2;t++)
	{
		// ������Ŀ¼�������������
		memset((uint8_t*)&StoreSwimParam.AlgoRecord, 0x66+t, sizeof(swimIndoorRecord_t));
		
		Store_Swim_CatalogCreate();
		for(uint32_t i = 0; i < SWIM_DATE_SIMULATA_LEN*(t+1);i++)
		{
			memset((uint8_t *)&swimIndoorInfo, i, sizeof(swimIndoorInfo_t));
			Store_Swim_algorithm(i, swimIndoorInfo);
		}
		Store_Swim_CatalogSeal();	
	}

	#endif
}














