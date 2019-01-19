#include "store_sleep_record.h"
#include "store_algo.h"
#include "scene_sleep.h"

StoreInfo_t					SlpRcdStoreInfo;
StoreSlpRcdParam_t			StoreSlpRcdParam;
 
static void Store_SlpRcd_ParamInit(void)
{
	SlpRcdStoreInfo.Status = eStoreStatusNull;			// 存储状态				
	
	SlpRcdStoreInfo.CatalogBeginAddr = STORE2_SLPRCD_CATALOG_BEGIN_ADDR;	// 固定值，目录存储开始起始
	SlpRcdStoreInfo.CatalogEndAddr = STORE2_SLPRCD_CATALOG_END_ADDR;		// 固定值，目录存储结束地址（包括）

	SlpRcdStoreInfo.CatalogSerialMax = STORE2_SLPRCD_MAX_ALLOT_CATALOG;		// 固定值，最大目录数，由分配的存储空间决定
	SlpRcdStoreInfo.CatalogSerialMaxSave = STORE2_SLPRCD_MAX_SAVE_CATALOG;	// 固定值，被保存的最大目录
	SlpRcdStoreInfo.CatalogSerialBegin = SlpRcdStoreInfo.CatalogSerialMax - 1;	// 有效存储目录开始序号，若目录Cnt大于目录MaxSave，则当前目录Begin标记被覆盖，然后+1
	SlpRcdStoreInfo.CatalogSerialEnd = SlpRcdStoreInfo.CatalogSerialMax - 1;		// 有效存储目录结束序号，每次创建目录时+1
	SlpRcdStoreInfo.CatalogSerialCnt = 0;		// 已存储目录计数，每次封存目录时+1，最大不超过MaxSave

	SlpRcdStoreInfo.DataBeginAddr = STORE2_SLPRCD_DATA_BEGIN_ADDR;	// 固定值，数据存储开始起始
	SlpRcdStoreInfo.DataEndAddr = STORE2_SLPRCD_DATA_END_ADDR;	// 固定值，数据存储结束地址（包括）	
	SlpRcdStoreInfo.DataCurrAddr = SlpRcdStoreInfo.DataBeginAddr;	// 当前数据存储地址
}

// 数据清零方式初始化
void Store_SlpRcd_ClearInit(void)
{
	/* 存储参数初始化 */
	Store_SlpRcd_ParamInit();
	
	/* 擦除相关flash区域，防止之前的错误数据产生影响 */
	Mid_NandFlash_Erase(SlpRcdStoreInfo.CatalogBeginAddr, SlpRcdStoreInfo.DataEndAddr);
	
	StoreSlpRcdParam.InitFlg = true;
}

// 数据恢复方式初始化
void Store_SlpRcd_RecoverInit(void)
{
	/* 存储参数初始化 */
	Store_SlpRcd_ParamInit();
	
	/* 数据恢复 */
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
 * Brief : 睡眠档案存储，此函数会创建一个睡眠档案目录，并立即封存在FLASH中
 * Input : @NULL
 * Return: @NULL
 * Call  : 需存储睡眠档案时调用一次，如每天凌晨
 ***************/
void Store_SlpRcd_RecordStore(void)
{
	if(!StoreSlpRcdParam.InitFlg) drERROR_CHECK_RETURN_NULL("Store_SlpRcd_RecordStore", Ret_NoInit);
	if(eStoreStatusNull != SlpRcdStoreInfo.Status) drERROR_CHECK_RETURN_NULL("Store_SlpRcd_RecordStore", Ret_DeviceBusy);
	
	sleep_record_t lsleepRecord;
	
	Scene_Sleep_RecordGet(&lsleepRecord);
	if(lsleepRecord.SleepDuration)
	/* 有睡眠数据才存储 */
	{
		/* 目录创建	*/
		SlpRcdStoreInfo.Catalog.User.Info.DataClassify = eDataClassifySlpRcd;
		SlpRcdStoreInfo.Catalog.User.Info.UTC = lsleepRecord.StartUTC;
		Store_Algo_CatalogCreate(&SlpRcdStoreInfo);

		/* 目录封存，睡眠档案存与目录附加信息中
			解释为何存在目录附加信息而不是数据区？因为睡眠档案字节较少（不到200字节），
			若存在数据区，1page有2048字节，可存20+次。远超过推荐nandflash推荐的4次，容易到时flash数据出错
		*/
		Store_Algo_CatalogSeal(&SlpRcdStoreInfo, (uint8_t*)&lsleepRecord, sizeof(sleep_record_t));	
	}
}

/*******************************************************************************
 * Brief : 读取数据，仅用于debug测试
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
	
	#if 1	// 整体存储信息打印
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
	
	#if 1	// 目录打印
	lCatalogSerial = SlpRcdStoreInfo.CatalogSerialBegin;
	for(uint32_t k = 0;k < SlpRcdStoreInfo.CatalogSerialCnt;k++)
	{
		#if 1 /* 目录信息 */
		Store_Algo_CatalogRead(&SlpRcdStoreInfo, lCatalogSerial, &lCatalog);
		STORE_SLPRCD_RTT_LOG(0, "Store_Algo_CatalogRead %d :\n", lCatalogSerial);
		STORE_SLPRCD_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
		STORE_SLPRCD_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
		STORE_SLPRCD_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
		STORE_SLPRCD_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
		STORE_SLPRCD_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
		STORE_SLPRCD_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
		#endif
		
		#if 1 /* 目录附加信息， */
			
			#if 0	/* 目录附加信息，打印原始数据 */
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
			
			#if 1	/* 目录附加信息，转换为睡眠信息结构体 */
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
			
		// 下一目录
		lDataCnt = 0;
		lDataLen = 0;
		lCatalogSerial = Store_Algo_NextCatalogGet(&SlpRcdStoreInfo, lCatalogSerial);
	}
	#endif

	return Ret_OK;	
}

/*******************************************************************************
 * Brief : 所有目录数据标记为已上传（即app的删除操作）
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


// 模拟产生假数据，用于测试
void Store_SlpRcd_DateSimulata(void)
{
	STORE_SLPRCD_RTT_LOG(0, "Store_SlpRcd_DateSimulata \n");
	
	#if 1
	Store_SlpRcd_RecordStore();
	Store_SlpRcd_RecordStore();
	#endif
}







