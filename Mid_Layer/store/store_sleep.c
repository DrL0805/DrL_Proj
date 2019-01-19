#include "app_variable.h"
#include "store_sleep.h"
#include "store_algo.h"
#include "scene_sleep.h"
#include "mid_rtc.h"

StoreInfo_t			SleepStoreInfo;
StoreSleepParam_t		StoreSleepParam;
 
static void Store_Sleep_ParamInit(void)
{
	SleepStoreInfo.Status = eStoreStatusNull;			// 存储状态				
	
	SleepStoreInfo.CatalogBeginAddr = STORE2_SLEEP_CATALOG_BEGIN_ADDR;	// 固定值，目录存储开始起始
	SleepStoreInfo.CatalogEndAddr = STORE2_SLEEP_CATALOG_END_ADDR;		// 固定值，目录存储结束地址（包括）

	SleepStoreInfo.CatalogSerialMax = STORE2_SLEEP_MAX_ALLOT_CATALOG;		// 固定值，最大目录数，由分配的存储空间决定
	SleepStoreInfo.CatalogSerialMaxSave = STORE2_SLEEP_MAX_SAVE_CATALOG;	// 固定值，被保存的最大目录
	SleepStoreInfo.CatalogSerialBegin = SleepStoreInfo.CatalogSerialMax - 1;	// 有效存储目录开始序号，若目录Cnt大于目录MaxSave，则当前目录Begin标记被覆盖，然后+1
	SleepStoreInfo.CatalogSerialEnd = SleepStoreInfo.CatalogSerialMax - 1;		// 有效存储目录结束序号，每次创建目录时+1
	SleepStoreInfo.CatalogSerialCnt = 0;		// 已存储目录计数，每次封存目录时+1，最大不超过MaxSave

	SleepStoreInfo.DataBeginAddr = STORE2_SLEEP_DATA_BEGIN_ADDR;	// 固定值，数据存储开始起始
	SleepStoreInfo.DataEndAddr = STORE2_SLEEP_DATA_END_ADDR;	// 固定值，数据存储结束地址（包括）	
	SleepStoreInfo.DataCurrAddr = SleepStoreInfo.DataBeginAddr;	// 当前数据存储地址
}

// 数据清零方式初始化
void Store_Sleep_ClearInit(void)
{
	/* 存储参数初始化 */
	Store_Sleep_ParamInit();
	
	/* 擦除相关flash区域，防止之前的错误数据产生影响 */
	Mid_NandFlash_Erase(SleepStoreInfo.CatalogBeginAddr, SleepStoreInfo.DataEndAddr);
	
	StoreSleepParam.InitFlg = true;
}

// 数据恢复方式初始化
void Store_Sleep_RecoverInit(void)
{
	/* 存储参数初始化 */
	Store_Sleep_ParamInit();
	
	/* 数据恢复 */
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
 * Brief : 存储算法，需存储时调用一次
 * Input : @CurrUtc 当前UTC时间 
		   @Sleep 	需存储的值
 * Return: @NULL
 * Call  : 每5min调用一次
 ***************/
void Store_Sleep_algorithm(uint32_t Sleep)
{
	if(false == StoreSleepParam.InitFlg)
		return;	
	
	/* 若当前没创建目录，则创建 */
	if(eStoreStatusNull == SleepStoreInfo.Status)
	{
		Store_Sleep_CatalogCreate();
	}
	
	StoreSleepParam.LogBuf[StoreSleepParam.LogCnt*STORE2_SLEEP_DATA_CLASSIFY_LEN + 0] = Sleep >> 8;
	StoreSleepParam.LogBuf[StoreSleepParam.LogCnt*STORE2_SLEEP_DATA_CLASSIFY_LEN + 1] = Sleep;	
	StoreSleepParam.LogCnt++;
	
	// RAM缓存满后，存到flash
	if(StoreSleepParam.LogCnt >= STORE2_SLEEP_LOG_MAX)
	{
		Store_Sleep_DataSave();
	}
}


/*******************************************************************************
 * Brief : 目录创建
 * Input : @CurrUtc 当前UTC时间
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
		目录参数初始化，并创建。其他如下信息会在底层函数里，统一设置
		SleepStoreInfo.Catalog.Flash.Info.DataAddr = SleepStoreInfo.DataCurrAddr;
		SleepStoreInfo.Catalog.Flash.Info.Mark = eCatalogMarkUsing;	
	*/
	SleepStoreInfo.Catalog.User.Info.DataClassify = eDataClassifySleep;
	SleepStoreInfo.Catalog.User.Info.UTC = lMidRTC->UTC;
	Store_Algo_CatalogCreate(&SleepStoreInfo);

	// 创建目录后log计数清零
	StoreSleepParam.LogCnt = 0;	
	
	return Ret_OK;
}

// 数据存储
uint16_t Store_Sleep_DataSave(void)
{
	/* 跑步数据存储 */
	Store_Algo_DataSave(&SleepStoreInfo, StoreSleepParam.LogBuf, StoreSleepParam.LogCnt*STORE2_SLEEP_DATA_CLASSIFY_LEN);
	
	/* 清空RAM缓存 */
	StoreSleepParam.LogCnt = 0;
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : 目录封存
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
	
	/* 封存前保存一次RAM的数据 */
	if(StoreSleepParam.LogCnt)
	{
		Store_Sleep_DataSave();
	}
	
	/* 读取当前睡眠档案信息 */
	Scene_Sleep_RecordGet(&lsleepRecord);	
	
	/* 目录封存 */
	Store_Algo_CatalogSeal(&SleepStoreInfo, (uint8_t*)&lsleepRecord, sizeof(sleep_record_t));

	return Ret_OK;
}

/*******************************************************************************
 * Brief : 读取数据，仅用于debug测试
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
	
	#if 1	// 整体存储信息打印
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
	
	#if 1	// 目录打印
	lCatalogSerial = SleepStoreInfo.CatalogSerialBegin;
	for(uint32_t k = 0;k < SleepStoreInfo.CatalogSerialCnt;k++)
	{
		#if 1 /* 目录信息 */
		Store_Algo_CatalogRead(&SleepStoreInfo, lCatalogSerial, &lCatalog);
		STORE_SLEEP_RTT_LOG(0, "Store_Algo_CatalogRead %d :\n", lCatalogSerial);
		STORE_SLEEP_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
		STORE_SLEEP_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
		STORE_SLEEP_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
		STORE_SLEEP_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
		STORE_SLEEP_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
		STORE_SLEEP_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
		#endif
		
		#if 1 /* 目录附加信息， */
			
			#if 0	/* 目录附加信息，打印原始数据 */
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
			
			#if 1	/* 目录附加信息，转换为睡眠信息结构体 */
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
		
		#if 0	/* 打印数据 */
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
		
		// 下一目录
		lDataCnt = 0;
		lDataLen = 0;
		lCatalogSerial = Store_Algo_NextCatalogGet(&SleepStoreInfo, lCatalogSerial);
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
uint16_t Store_Sleep_CatalogAllUpload(void)
{
	Store_Algo_CatalogAllUpload(&SleepStoreInfo);
	
	return Ret_OK;	
}

/*******************************************************************************
 * Brief : 清除存储存储在RAM中的数据
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Store_Sleep_RamDataClear(void)
{
	StoreSleepParam.LogCnt = 0;
	
	Store_Algo_CatalogClear(&SleepStoreInfo);
}

// 模拟产生假数据，用于测试
#define SLEEP_DATE_SIMULATA_LEN	(189)
void Store_Sleep_DateSimulata(void)
{
	STORE_SLEEP_RTT_LOG(0, "Store_Sleep_DateSimulata \n");
	
	#if 0

	#endif
}
















