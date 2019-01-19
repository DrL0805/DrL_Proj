#include "store_climb.h"
#include "store_algo.h"
#include "store_history.h"
#include "mid_rtc.h"
#include "scene_climb.h"

StoreInfo_t			ClimbStoreInfo;
StoreClimbParam_t		StoreClimbParam;

/*******************************************************************************
 * Brief : �ܲ���������
 ******************************************************************************/
 
static void Store_Climb_ParamInit(void)
{
	ClimbStoreInfo.Status = eStoreStatusNull;			// �洢״̬				
	
	ClimbStoreInfo.CatalogBeginAddr = STORE2_CLIMB_CATALOG_BEGIN_ADDR;	// �̶�ֵ��Ŀ¼�洢��ʼ��ʼ
	ClimbStoreInfo.CatalogEndAddr = STORE2_CLIMB_CATALOG_END_ADDR;		// �̶�ֵ��Ŀ¼�洢������ַ��������

	ClimbStoreInfo.CatalogSerialMax = STORE2_CLIMB_MAX_ALLOT_CATALOG;		// �̶�ֵ�����Ŀ¼�����ɷ���Ĵ洢�ռ����
	ClimbStoreInfo.CatalogSerialMaxSave = STORE2_CLIMB_MAX_SAVE_CATALOG;	// �̶�ֵ������������Ŀ¼
	ClimbStoreInfo.CatalogSerialBegin = ClimbStoreInfo.CatalogSerialMax - 1;	// ��Ч�洢Ŀ¼��ʼ��ţ���Ŀ¼Cnt����Ŀ¼MaxSave����ǰĿ¼Begin��Ǳ����ǣ�Ȼ��+1
	ClimbStoreInfo.CatalogSerialEnd = ClimbStoreInfo.CatalogSerialMax - 1;		// ��Ч�洢Ŀ¼������ţ�ÿ�δ���Ŀ¼ʱ+1
	ClimbStoreInfo.CatalogSerialCnt = 0;		// �Ѵ洢Ŀ¼������ÿ�η��Ŀ¼ʱ+1����󲻳���MaxSave

	ClimbStoreInfo.DataBeginAddr = STORE2_CLIMB_DATA_BEGIN_ADDR;	// �̶�ֵ�����ݴ洢��ʼ��ʼ
	ClimbStoreInfo.DataEndAddr = STORE2_CLIMB_DATA_END_ADDR;	// �̶�ֵ�����ݴ洢������ַ��������	
	ClimbStoreInfo.DataCurrAddr = ClimbStoreInfo.DataBeginAddr;	// ��ǰ���ݴ洢��ַ
}

// �������㷽ʽ��ʼ��
void Store_Climb_ClearInit(void)
{
	/* �洢������ʼ�� */
	Store_Climb_ParamInit();
	
	/* �������flash���򣬷�ֹ֮ǰ�Ĵ������ݲ���Ӱ�� */
	Mid_NandFlash_Erase(ClimbStoreInfo.CatalogBeginAddr, ClimbStoreInfo.DataEndAddr);
	
	StoreClimbParam.InitFlg = true;
}

// ���ݻָ���ʽ��ʼ��
void Store_Climb_RecoverInit(void)
{
	/* �洢������ʼ�� */
	Store_Climb_ParamInit();
	
	/* ���ݻָ� */
	Store_Algo_CatalogRecover(&ClimbStoreInfo);
	
	StoreClimbParam.InitFlg = true;
}

StoreInfo_t* Store_Climb_StoreInfoGet(void)
{
	return &ClimbStoreInfo;
}

StoreClimbParam_t* Store_Climb_ParamPGet(void)
{
	return &StoreClimbParam;
}

/*******************************************************************************
 * Brief : �ܲ��洢�㷨����洢ʱ����һ��
 * Input : @CurrUtc ��ǰUTCʱ�� 
		   @ClimbningInfo ��洢��ֵ
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Store_Climb_algorithm(void)
{
	if(false == StoreClimbParam.InitFlg)
		return;	

	climbMountainInfo_t lclimbMountainInfo;
	Scene_Climb_InfoGet(&lclimbMountainInfo);		
	
	/* ����ǰû����Ŀ¼���򴴽� */
	if(eStoreStatusNull == ClimbStoreInfo.Status)
	{
		Store_Climb_CatalogCreate();
	}
	
	#if 1
	{
		STORE_CLIMB_RTT_LOG(0, "Store_Climb_algorithm: %d, %d, %d, %d, %d \n",
			lclimbMountainInfo.RealTimeData.Altitude, lclimbMountainInfo.RealTimeData.Speed, lclimbMountainInfo.RealTimeData.Hr,
			(uint32_t)(lclimbMountainInfo.RealTimeData.Longitude.f), (uint32_t)(lclimbMountainInfo.RealTimeData.Latitude.f));
	}
	#endif	

	// ����
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 0] = (uint8_t)(lclimbMountainInfo.RealTimeData.Altitude >> 8);  
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 1] = (uint8_t)(lclimbMountainInfo.RealTimeData.Altitude);
	// ��ɽ�ٶ�
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 2] = (uint8_t)(lclimbMountainInfo.RealTimeData.Speed >> 8);  
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 3] = (uint8_t)(lclimbMountainInfo.RealTimeData.Speed);
	// ����
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 4] = (uint8_t)(lclimbMountainInfo.RealTimeData.Hr); 
	// ����
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 5] = (uint8_t)(lclimbMountainInfo.RealTimeData.Longitude.u8[3]);
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 6] = (uint8_t)(lclimbMountainInfo.RealTimeData.Longitude.u8[2]);
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 7] = (uint8_t)(lclimbMountainInfo.RealTimeData.Longitude.u8[1]);
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 8] = (uint8_t)(lclimbMountainInfo.RealTimeData.Longitude.u8[0]);
	// γ��
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 9] =  (uint8_t)(lclimbMountainInfo.RealTimeData.Latitude.u8[3]);
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 10] = (uint8_t)(lclimbMountainInfo.RealTimeData.Latitude.u8[2]);
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 11] = (uint8_t)(lclimbMountainInfo.RealTimeData.Latitude.u8[1]);
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 12] = (uint8_t)(lclimbMountainInfo.RealTimeData.Latitude.u8[0]); 		

	StoreClimbParam.LogCnt++;
	
	// RAM�������󣬴浽flash
	if(StoreClimbParam.LogCnt >= STORE2_CLIMB_LOG_MAX)
	{
		Store_Climb_DataSave();
	}
}


/*******************************************************************************
 * Brief : �ܲ�����Ŀ¼����
 * Input : @CurrUtc ��ǰUTCʱ��
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Climb_CatalogCreate(void)
{
	if(false == StoreClimbParam.InitFlg)
		return Ret_NoInit;
	
	if(eStoreStatusNull != ClimbStoreInfo.Status)
		return Ret_DeviceBusy;	

	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	
	/* 
		Ŀ¼������ʼ����������������������Ϣ���ڵײ㺯���ͳһ����
		ClimbStoreInfo.Catalog.Flash.Info.DataAddr = ClimbStoreInfo.DataCurrAddr;
		ClimbStoreInfo.Catalog.Flash.Info.Mark = eCatalogMarkUsing;	
	*/
	ClimbStoreInfo.Catalog.User.Info.DataClassify = eDataClassifyClimbNew;
	ClimbStoreInfo.Catalog.User.Info.UTC = lMidRTC->UTC;
	Store_Algo_CatalogCreate(&ClimbStoreInfo);

	// ����Ŀ¼��log��������
	StoreClimbParam.LogCnt = 0;	
	
	return Ret_OK;
}

// �ܲ����ݴ洢
uint16_t Store_Climb_DataSave(void)
{
	/* �ܲ����ݴ洢 */
	Store_Algo_DataSave(&ClimbStoreInfo, StoreClimbParam.LogBuf, StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN);
	
	/* ���RAM���� */
	StoreClimbParam.LogCnt = 0;
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : �ܲ�����Ŀ¼���
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Climb_CatalogSeal(void)
{
	climbMountainInfo_t lclimbMountainInfo;
	StoreHistoryList_t lStoreHistoryList;	
	
	if(false == StoreClimbParam.InitFlg)
		return Ret_NoInit;	
	
	if(eStoreStatusIng != ClimbStoreInfo.Status)
		return Ret_NoInit;	
	
	/* ���ǰ����һ��RAM������ */
	if(StoreClimbParam.LogCnt)
	{
		Store_Climb_DataSave();
	}	
	
	/* ��ȡ��ǰ�˶��������� */
	Scene_Climb_InfoGet(&lclimbMountainInfo);
	
	#if 1
	STORE_CLIMB_RTT_LOG(0, "Store_Climb_CatalogSeal %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d \n",
		lclimbMountainInfo.RecordData.StartUTC, lclimbMountainInfo.RecordData.StopUTC, lclimbMountainInfo.RecordData.Duration,
		lclimbMountainInfo.RecordData.Step, lclimbMountainInfo.RecordData.Distance, lclimbMountainInfo.RecordData.UpAltitude,
		lclimbMountainInfo.RecordData.DownAltitude, lclimbMountainInfo.RecordData.HighestAltitude, lclimbMountainInfo.RecordData.LowestAltitude,
		lclimbMountainInfo.RecordData.SpeedAVG, lclimbMountainInfo.RecordData.Calorie, lclimbMountainInfo.RecordData.HrAVG,
		lclimbMountainInfo.RecordData.HrMax);
	#endif	
	
	/* Ŀ¼��� */
	Store_Algo_CatalogSeal(&ClimbStoreInfo, (uint8_t*)&lclimbMountainInfo.RecordData, sizeof(climbMountainRecord_t));

	/* ���ӵ��˶���ʷ�б� */
	lStoreHistoryList.CatalogSerial = ClimbStoreInfo.CatalogSerialEnd;
	lStoreHistoryList.DataClassify = eDataClassifyClimbNew;
	lStoreHistoryList.Distance = lclimbMountainInfo.RecordData.Distance;
	lStoreHistoryList.UTC = lclimbMountainInfo.RecordData.StartUTC;
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
uint16_t Store_Climb_DataRead(void)
{
	CatalogInfo_t		lCatalog;
	uint8_t 		lDataBuf[512];
	uint32_t 		lDataLen = 0,lDataCnt = 0;
	uint32_t	lCatalogSerial;
	
	#if 1	// ����洢��Ϣ��ӡ
	STORE_CLIMB_RTT_LOG(0, "ClimbStoreInfo Read: \n");
	STORE_CLIMB_RTT_LOG(0, "  .Status %d \n", ClimbStoreInfo.Status);
	STORE_CLIMB_RTT_LOG(0, "  .CatalogBeginAddr 0x%X \n", ClimbStoreInfo.CatalogBeginAddr);
	STORE_CLIMB_RTT_LOG(0, "  .CatalogEndAddr 0x%X \n", ClimbStoreInfo.CatalogEndAddr);
	STORE_CLIMB_RTT_LOG(0, "  .CatalogSerialMax %d \n", ClimbStoreInfo.CatalogSerialMax);
	STORE_CLIMB_RTT_LOG(0, "  .CatalogSerialMaxSave %d \n", ClimbStoreInfo.CatalogSerialMaxSave);
	STORE_CLIMB_RTT_LOG(0, "  .CatalogSerialBegin %d \n", ClimbStoreInfo.CatalogSerialBegin);
	STORE_CLIMB_RTT_LOG(0, "  .CatalogSerialEnd %d \n", ClimbStoreInfo.CatalogSerialEnd);
	STORE_CLIMB_RTT_LOG(0, "  .CatalogSerialCnt %d \n", ClimbStoreInfo.CatalogSerialCnt);
	STORE_CLIMB_RTT_LOG(0, "  .DataBeginAddr 0x%X \n", ClimbStoreInfo.DataBeginAddr);
	STORE_CLIMB_RTT_LOG(0, "  .DataEndAddr 0x%X \n", ClimbStoreInfo.DataEndAddr);
	STORE_CLIMB_RTT_LOG(0, "  .DataCurrAddr 0x%X \n", ClimbStoreInfo.DataCurrAddr);
	#endif
	
	#if 1	// Ŀ¼��ӡ
	lCatalogSerial = ClimbStoreInfo.CatalogSerialBegin;
	for(uint32_t k = 0;k < ClimbStoreInfo.CatalogSerialCnt;k++)
	{
		#if 1 /* Ŀ¼��Ϣ */
		Store_Algo_CatalogRead(&ClimbStoreInfo, lCatalogSerial, &lCatalog);
		STORE_CLIMB_RTT_LOG(0, "Store_Algo_CatalogRead %d :\n", lCatalogSerial);
		STORE_CLIMB_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
		STORE_CLIMB_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
		STORE_CLIMB_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
		STORE_CLIMB_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
		STORE_CLIMB_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
		STORE_CLIMB_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
		#endif
		
		#if 1 /* Ŀ¼������Ϣ */
		Store_Algo_CatalogExtRead(&ClimbStoreInfo, lCatalogSerial, lDataBuf, lCatalog.User.Info.ExtDataLen);
		STORE_CLIMB_RTT_LOG(0, "Store_Algo_CatalogExtRead \n");
		for(uint32_t t = 0;t < lCatalog.User.Info.ExtDataLen;t++)
		{
			if((0 == t%32) && (0 != t))
			{
				STORE_CLIMB_RTT_LOG(0, "\n");
			}
			STORE_CLIMB_RTT_LOG(0, "%02X ", lDataBuf[t]);
		}STORE_CLIMB_RTT_LOG(0, "\n");
		#endif
		
		#if 1	/* ��ӡ���� */
		STORE_CLIMB_RTT_LOG(0, "Store_Algo_DataRead \n");
		do
		{
			if((lDataCnt+260) <= lCatalog.Flash.Info.DataLen)	// 13*20
			{
				lDataLen = 260;
				lDataCnt += 260;
			}
			else
			{
				lDataLen = lCatalog.Flash.Info.DataLen - lDataCnt;
				lDataCnt = lCatalog.Flash.Info.DataLen;
			}
			Store_Algo_DataRead(&ClimbStoreInfo, &lCatalog, lDataCnt-lDataLen, lDataBuf, lDataLen);
			for(uint32_t t = 0;t < lDataLen;t++)
			{
				if((0 == t%26) && (0 != t))
				{
					STORE_CLIMB_RTT_LOG(0, "\n");
				}
				STORE_CLIMB_RTT_LOG(0, "%02X ", lDataBuf[t]);
			}STORE_CLIMB_RTT_LOG(0, "\n");
		}while(lDataCnt != lCatalog.Flash.Info.DataLen);
		#endif
		
		// ��һĿ¼
		lDataCnt = 0;
		lDataLen = 0;
		lCatalogSerial = Store_Algo_NextCatalogGet(&ClimbStoreInfo, lCatalogSerial);
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
uint16_t Store_Climb_CatalogAllUpload(void)
{
	Store_Algo_CatalogAllUpload(&ClimbStoreInfo);
	
	return Ret_OK;	
}



// ģ����������ݣ����ڲ���
#define CLIMB_DATE_SIMULATA_LEN	(119)
void Store_Climb_DateSimulata(void)
{
	STORE_CLIMB_RTT_LOG(0, "Store_Climb_DateSimulata \n");
	
	#if 1
	climbMountainInfo_t climbMountainInfo;
	
	Store_Climb_ClearInit();
	
	for(uint32_t t = 0;t < 2;t++)
	{
		// ������Ŀ¼�������������
//		memset((uint8_t*)&StoreClimbParam.AlgoRecord, 0x66+t, sizeof(climbMountainRecord_t));
		
		Store_Climb_CatalogCreate();
		for(uint32_t i = 0; i < CLIMB_DATE_SIMULATA_LEN*(t+1);i++)
		{
			memset((uint8_t *)&climbMountainInfo, i, sizeof(climbMountainInfo_t));
//			Store_Climb_algorithm(i, climbMountainInfo);
		}
		Store_Climb_CatalogSeal();	
	}

	#endif
}
