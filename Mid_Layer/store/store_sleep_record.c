#include "store_sleep_record.h"
#include "store_algo.h"
#include "scene_sleep.h"

StoreInfo_t					SlpRcdStoreInfo;
StoreSlpRcdParam_t			StoreSlpRcdParam;
 
static void Store_SlpRcd_ParamInit(void)
{
	SlpRcdStoreInfo.Status = eStoreStatusNull;			// �洢״̬				
	
	SlpRcdStoreInfo.CatalogBeginAddr = STORE2_SLPRCD_CATALOG_BEGIN_ADDR;	// �̶�ֵ��Ŀ¼�洢��ʼ��ʼ
	SlpRcdStoreInfo.CatalogEndAddr = STORE2_SLPRCD_CATALOG_END_ADDR;		// �̶�ֵ��Ŀ¼�洢������ַ��������

	SlpRcdStoreInfo.CatalogSerialMax = STORE2_SLPRCD_MAX_ALLOT_CATALOG;		// �̶�ֵ�����Ŀ¼�����ɷ���Ĵ洢�ռ����
	SlpRcdStoreInfo.CatalogSerialMaxSave = STORE2_SLPRCD_MAX_SAVE_CATALOG;	// �̶�ֵ������������Ŀ¼
	SlpRcdStoreInfo.CatalogSerialBegin = SlpRcdStoreInfo.CatalogSerialMax - 1;	// ��Ч�洢Ŀ¼��ʼ��ţ���Ŀ¼Cnt����Ŀ¼MaxSave����ǰĿ¼Begin��Ǳ����ǣ�Ȼ��+1
	SlpRcdStoreInfo.CatalogSerialEnd = SlpRcdStoreInfo.CatalogSerialMax - 1;		// ��Ч�洢Ŀ¼������ţ�ÿ�δ���Ŀ¼ʱ+1
	SlpRcdStoreInfo.CatalogSerialCnt = 0;		// �Ѵ洢Ŀ¼������ÿ�η��Ŀ¼ʱ+1����󲻳���MaxSave

	SlpRcdStoreInfo.DataBeginAddr = STORE2_SLPRCD_DATA_BEGIN_ADDR;	// �̶�ֵ�����ݴ洢��ʼ��ʼ
	SlpRcdStoreInfo.DataEndAddr = STORE2_SLPRCD_DATA_END_ADDR;	// �̶�ֵ�����ݴ洢������ַ��������	
	SlpRcdStoreInfo.DataCurrAddr = SlpRcdStoreInfo.DataBeginAddr;	// ��ǰ���ݴ洢��ַ
}

// �������㷽ʽ��ʼ��
void Store_SlpRcd_ClearInit(void)
{
	/* �洢������ʼ�� */
	Store_SlpRcd_ParamInit();
	
	/* �������flash���򣬷�ֹ֮ǰ�Ĵ������ݲ���Ӱ�� */
	Mid_NandFlash_Erase(SlpRcdStoreInfo.CatalogBeginAddr, SlpRcdStoreInfo.DataEndAddr);
	
	StoreSlpRcdParam.InitFlg = true;
}

// ���ݻָ���ʽ��ʼ��
void Store_SlpRcd_RecoverInit(void)
{
	/* �洢������ʼ�� */
	Store_SlpRcd_ParamInit();
	
	/* ���ݻָ� */
	Store_Algo_CatalogRecover(&SlpRcdStoreInfo);
	
	StoreSlpRcdParam.InitFlg = true;
}

StoreInfo_t* Store_SlpRcd_StoreInfoGet(void)
{
	return &SlpRcdStoreInfo;
}

StoreSlpRcdParam_t* Store_SlpRcd_ParamPGet(void)
{
	return &StoreSlpRcdParam;
}

/*******************************************************************************
 * Brief : ˯�ߵ����洢���˺����ᴴ��һ��˯�ߵ���Ŀ¼�������������FLASH��
 * Input : @NULL
 * Return: @NULL
 * Call  : ��洢˯�ߵ���ʱ����һ�Σ���ÿ���賿
 ***************/
void Store_SlpRcd_RecordStore(void)
{
	if(!StoreSlpRcdParam.InitFlg) drERROR_CHECK_RETURN_NULL("Store_SlpRcd_RecordStore", Ret_NoInit);
	if(eStoreStatusNull != SlpRcdStoreInfo.Status) drERROR_CHECK_RETURN_NULL("Store_SlpRcd_RecordStore", Ret_DeviceBusy);
	
	sleep_record_t lsleepRecord;
	
	Scene_Sleep_RecordGet(&lsleepRecord);
	if(lsleepRecord.SleepDuration)
	/* ��˯�����ݲŴ洢 */
	{
		/* Ŀ¼����	*/
		SlpRcdStoreInfo.Catalog.User.Info.DataClassify = eDataClassifySlpRcd;
		SlpRcdStoreInfo.Catalog.User.Info.UTC = lsleepRecord.StartUTC;
		Store_Algo_CatalogCreate(&SlpRcdStoreInfo);

		/* Ŀ¼��棬˯�ߵ�������Ŀ¼������Ϣ��
			����Ϊ�δ���Ŀ¼������Ϣ����������������Ϊ˯�ߵ����ֽڽ��٣�����200�ֽڣ���
			��������������1page��2048�ֽڣ��ɴ�20+�Ρ�Զ�����Ƽ�nandflash�Ƽ���4�Σ����׵�ʱflash���ݳ���
		*/
		Store_Algo_CatalogSeal(&SlpRcdStoreInfo, (uint8_t*)&lsleepRecord, sizeof(sleep_record_t));	
	}
}

/*******************************************************************************
 * Brief : ��ȡ���ݣ�������debug����
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_SlpRcd_DataRead(void)
{
	CatalogInfo_t		lCatalog;
	uint8_t 		lDataBuf[512];
	uint32_t 		lDataLen = 0,lDataCnt = 0;
	uint32_t	lCatalogSerial;
	
	#if 1	// ����洢��Ϣ��ӡ
	STORE_SLPRCD_RTT_LOG(0, "SlpRcdStoreInfo Read: \n");
	STORE_SLPRCD_RTT_LOG(0, "  .Status %d \n", SlpRcdStoreInfo.Status);
	STORE_SLPRCD_RTT_LOG(0, "  .CatalogBeginAddr 0x%X \n", SlpRcdStoreInfo.CatalogBeginAddr);
	STORE_SLPRCD_RTT_LOG(0, "  .CatalogEndAddr 0x%X \n", SlpRcdStoreInfo.CatalogEndAddr);
	STORE_SLPRCD_RTT_LOG(0, "  .CatalogSerialMax %d \n", SlpRcdStoreInfo.CatalogSerialMax);
	STORE_SLPRCD_RTT_LOG(0, "  .CatalogSerialMaxSave %d \n", SlpRcdStoreInfo.CatalogSerialMaxSave);
	STORE_SLPRCD_RTT_LOG(0, "  .CatalogSerialBegin %d \n", SlpRcdStoreInfo.CatalogSerialBegin);
	STORE_SLPRCD_RTT_LOG(0, "  .CatalogSerialEnd %d \n", SlpRcdStoreInfo.CatalogSerialEnd);
	STORE_SLPRCD_RTT_LOG(0, "  .CatalogSerialCnt %d \n", SlpRcdStoreInfo.CatalogSerialCnt);
	STORE_SLPRCD_RTT_LOG(0, "  .DataBeginAddr 0x%X \n", SlpRcdStoreInfo.DataBeginAddr);
	STORE_SLPRCD_RTT_LOG(0, "  .DataEndAddr 0x%X \n", SlpRcdStoreInfo.DataEndAddr);
	STORE_SLPRCD_RTT_LOG(0, "  .DataCurrAddr 0x%X \n", SlpRcdStoreInfo.DataCurrAddr);
	#endif
	
	#if 1	// Ŀ¼��ӡ
	lCatalogSerial = SlpRcdStoreInfo.CatalogSerialBegin;
	for(uint32_t k = 0;k < SlpRcdStoreInfo.CatalogSerialCnt;k++)
	{
		#if 1 /* Ŀ¼��Ϣ */
		Store_Algo_CatalogRead(&SlpRcdStoreInfo, lCatalogSerial, &lCatalog);
		STORE_SLPRCD_RTT_LOG(0, "Store_Algo_CatalogRead %d :\n", lCatalogSerial);
		STORE_SLPRCD_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
		STORE_SLPRCD_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
		STORE_SLPRCD_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
		STORE_SLPRCD_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
		STORE_SLPRCD_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
		STORE_SLPRCD_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
		#endif
		
		#if 1 /* Ŀ¼������Ϣ�� */
			
			#if 0	/* Ŀ¼������Ϣ����ӡԭʼ���� */
			Store_Algo_CatalogExtRead(&SlpRcdStoreInfo, lCatalogSerial, lDataBuf, lCatalog.User.Info.ExtDataLen);
			STORE_SLPRCD_RTT_LOG(0, "Store_Algo_CatalogExtRead %d \n", lCatalog.User.Info.ExtDataLen);
			for(uint32_t t = 0;t < lCatalog.User.Info.ExtDataLen;t++)
			{
				if((0 == t%32) && (0 != t))
				{
					STORE_SLPRCD_RTT_LOG(0, "\n");
					vTaskDelay(5);
				}
				STORE_SLPRCD_RTT_LOG(0, "%02X ", lDataBuf[t]);
			}STORE_SLPRCD_RTT_LOG(0, "\n");
			#endif
			
			#if 1	/* Ŀ¼������Ϣ��ת��Ϊ˯����Ϣ�ṹ�� */
			sleep_record_t lsleepRecord;
			Store_Algo_CatalogExtRead(&SlpRcdStoreInfo, lCatalogSerial, (uint8_t*)&lsleepRecord, lCatalog.User.Info.ExtDataLen);
			STORE_SLPRCD_RTT_LOG(0, "	record: %d %d %d %d %d %d %d %d \n", 
				lsleepRecord.StartHour, lsleepRecord.StartMin, lsleepRecord.StopHour, lsleepRecord.StopMin,
				lsleepRecord.StartUTC, lsleepRecord.StopUTC, lsleepRecord.SleepDuration, lsleepRecord.Quality);
			STORE_SLPRCD_RTT_LOG(0, "	record: %d %d %d %d %d %d \n", 
				lsleepRecord.TotalDuration, lsleepRecord.WakeDuration, lsleepRecord.LightDuration, lsleepRecord.DeepDuration,
				lsleepRecord.RemDuration, lsleepRecord.SegmentCnt);
			for(uint32_t i = 0;i < lsleepRecord.SegmentCnt;i++)
			{
				STORE_SLPRCD_RTT_LOG(0, "		%d Segment : %d %d \n", 
				i, lsleepRecord.SleepData[i].State, lsleepRecord.SleepData[i].Duration);
			}
			#endif
			
		#endif
			
		// ��һĿ¼
		lDataCnt = 0;
		lDataLen = 0;
		lCatalogSerial = Store_Algo_NextCatalogGet(&SlpRcdStoreInfo, lCatalogSerial);
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
uint16_t Store_SlpRcd_CatalogAllUpload(void)
{
	Store_Algo_CatalogAllUpload(&SlpRcdStoreInfo);
	
	return Ret_OK;	
}


// ģ����������ݣ����ڲ���
void Store_SlpRcd_DateSimulata(void)
{
	STORE_SLPRCD_RTT_LOG(0, "Store_SlpRcd_DateSimulata \n");
	
	#if 1
	Store_SlpRcd_RecordStore();
	Store_SlpRcd_RecordStore();
	#endif
}







