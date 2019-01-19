#include "store_swim.h"
#include "store_algo.h"
#include "store_history.h"
#include "mid_rtc.h"
#include "scene_swim.h"

StoreInfo_t			SwimStoreInfo;
StoreSwimParam_t		StoreSwimParam;

/*******************************************************************************
 * Brief : 跑步过程数据
 ******************************************************************************/
 
static void Store_Swim_ParamInit(void)
{
	SwimStoreInfo.Status = eStoreStatusNull;			// 存储状态				
	
	SwimStoreInfo.CatalogBeginAddr = STORE2_SWIM_CATALOG_BEGIN_ADDR;	// 固定值，目录存储开始起始
	SwimStoreInfo.CatalogEndAddr = STORE2_SWIM_CATALOG_END_ADDR;		// 固定值，目录存储结束地址（包括）

	SwimStoreInfo.CatalogSerialMax = STORE2_SWIM_MAX_ALLOT_CATALOG;		// 固定值，最大目录数，由分配的存储空间决定
	SwimStoreInfo.CatalogSerialMaxSave = STORE2_SWIM_MAX_SAVE_CATALOG;	// 固定值，被保存的最大目录
	SwimStoreInfo.CatalogSerialBegin = SwimStoreInfo.CatalogSerialMax - 1;	// 有效存储目录开始序号，若目录Cnt大于目录MaxSave，则当前目录Begin标记被覆盖，然后+1
	SwimStoreInfo.CatalogSerialEnd = SwimStoreInfo.CatalogSerialMax - 1;		// 有效存储目录结束序号，每次创建目录时+1
	SwimStoreInfo.CatalogSerialCnt = 0;		// 已存储目录计数，每次封存目录时+1，最大不超过MaxSave

	SwimStoreInfo.DataBeginAddr = STORE2_SWIM_DATA_BEGIN_ADDR;	// 固定值，数据存储开始起始
	SwimStoreInfo.DataEndAddr = STORE2_SWIM_DATA_END_ADDR;	// 固定值，数据存储结束地址（包括）	
	SwimStoreInfo.DataCurrAddr = SwimStoreInfo.DataBeginAddr;	// 当前数据存储地址
}

// 数据清零方式初始化
void Store_Swim_ClearInit(void)
{
	/* 存储参数初始化 */
	Store_Swim_ParamInit();
	
	/* 擦除相关flash区域，防止之前的错误数据产生影响 */
	Mid_NandFlash_Erase(SwimStoreInfo.CatalogBeginAddr, SwimStoreInfo.DataEndAddr);
	
	StoreSwimParam.InitFlg = true;
}

// 数据恢复方式初始化
void Store_Swim_RecoverInit(void)
{
	/* 存储参数初始化 */
	Store_Swim_ParamInit();
	
	/* 数据恢复 */
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
 * Brief : 跑步存储算法，需存储时调用一次
 * Input : @CurrUtc 当前UTC时间 
		   @SwimningInfo 需存储的值
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
	
	/* 若当前没创建目录，则创建 */
	if(eStoreStatusNull == SwimStoreInfo.Status)
	{
		Store_Swim_CatalogCreate();
	}

	// 划水速度
	StoreSwimParam.LogBuf[StoreSwimParam.LogCnt*STORE2_SWIM_DATA_CLASSIFY_LEN + 0] = (uint8_t)(lswimIndoorInfo.RealTimeData.StrokeRate >> 8);  
	StoreSwimParam.LogBuf[StoreSwimParam.LogCnt*STORE2_SWIM_DATA_CLASSIFY_LEN + 1] = (uint8_t)(lswimIndoorInfo.RealTimeData.StrokeRate);
	// //配速
	StoreSwimParam.LogBuf[StoreSwimParam.LogCnt*STORE2_SWIM_DATA_CLASSIFY_LEN + 2] = (uint8_t)(lswimIndoorInfo.LapData.LapPace >> 8);  
	StoreSwimParam.LogBuf[StoreSwimParam.LogCnt*STORE2_SWIM_DATA_CLASSIFY_LEN + 3] = (uint8_t)(lswimIndoorInfo.LapData.LapPace);
	// 心率
	StoreSwimParam.LogBuf[StoreSwimParam.LogCnt*STORE2_SWIM_DATA_CLASSIFY_LEN + 4] = (uint8_t)(lswimIndoorInfo.RealTimeData.HR); 	
	
	StoreSwimParam.LogCnt++;
	
	// RAM缓存满后，存到flash
	if(StoreSwimParam.LogCnt >= STORE2_SWIM_LOG_MAX)
	{
		Store_Swim_DataSave();
	}
}


/*******************************************************************************
 * Brief : 跑步数据目录创建
 * Input : @CurrUtc 当前UTC时间
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
		目录参数初始化，并创建。其他如下信息会在底层函数里，统一设置
		SwimStoreInfo.Catalog.Flash.Info.DataAddr = SwimStoreInfo.DataCurrAddr;
		SwimStoreInfo.Catalog.Flash.Info.Mark = eCatalogMarkUsing;	
	*/
	SwimStoreInfo.Catalog.User.Info.DataClassify = eDataClassifySwimNew;
	SwimStoreInfo.Catalog.User.Info.UTC = lMidRTC->UTC;
	Store_Algo_CatalogCreate(&SwimStoreInfo);

	// 创建目录后log计数清零
	StoreSwimParam.LogCnt = 0;	
	
	return Ret_OK;
}

// 跑步数据存储
uint16_t Store_Swim_DataSave(void)
{
	/* 跑步数据存储 */
	Store_Algo_DataSave(&SwimStoreInfo, StoreSwimParam.LogBuf, StoreSwimParam.LogCnt*STORE2_SWIM_DATA_CLASSIFY_LEN);
	
	/* 清空RAM缓存 */
	StoreSwimParam.LogCnt = 0;
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : 跑步数据目录封存
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
	
	/* 封存前保存一次RAM的数据 */
	if(StoreSwimParam.LogCnt)
	{
		Store_Swim_DataSave();
	}	
	
	/* 读取当前运动档案数据 */
	Scene_Swim_InfoGet(&lswimIndoorInfo);	
	
	#if 1	// 打印存储的目录附加信息
	STORE_SWIM_RTT_LOG(0, "Store_Swim_CatalogSeal %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d \n",
		lswimIndoorInfo.RecordData.StartUTC, lswimIndoorInfo.RecordData.StopUTC, lswimIndoorInfo.RecordData.Duration, 
		lswimIndoorInfo.RecordData.ValidDuration, lswimIndoorInfo.RecordData.Distance, lswimIndoorInfo.RecordData.Stroke, 
		lswimIndoorInfo.RecordData.Calorie, lswimIndoorInfo.RecordData.Laps, lswimIndoorInfo.RecordData.PaceAVG, 
		lswimIndoorInfo.RecordData.StrokeAVG, lswimIndoorInfo.RecordData.StrokeRateAVG, lswimIndoorInfo.RecordData.SwolfAvg, 
		lswimIndoorInfo.RecordData.HrAVG, lswimIndoorInfo.RecordData.HrMax, lswimIndoorInfo.RecordData.Style);
	#endif	
	
	/* 目录封存 */
	Store_Algo_CatalogSeal(&SwimStoreInfo, (uint8_t*)&lswimIndoorInfo.RecordData, sizeof(swimIndoorRecord_t));

	/* 增加到运动历史列表 */
	lStoreHistoryList.CatalogSerial = SwimStoreInfo.CatalogSerialEnd;
	lStoreHistoryList.DataClassify = eDataClassifySwimNew;
	lStoreHistoryList.Distance = lswimIndoorInfo.RecordData.Distance;
	lStoreHistoryList.UTC = lswimIndoorInfo.RecordData.StartUTC;
	Store_History_ListAdd(&lStoreHistoryList);		
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : 读取跑步数据，仅用于debug测试
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
	
	#if 1	// 整体存储信息打印
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
	
	#if 1	// 目录打印
	lCatalogSerial = SwimStoreInfo.CatalogSerialBegin;
	for(uint32_t k = 0;k < SwimStoreInfo.CatalogSerialCnt;k++)
	{
		#if 1 /* 目录信息 */
		Store_Algo_CatalogRead(&SwimStoreInfo, lCatalogSerial, &lCatalog);
		STORE_SWIM_RTT_LOG(0, "Store_Algo_CatalogRead %d :\n", lCatalogSerial);
		STORE_SWIM_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
		STORE_SWIM_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
		STORE_SWIM_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
		STORE_SWIM_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
		STORE_SWIM_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
		STORE_SWIM_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
		#endif
		
		#if 1 /* 目录附加信息 */
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
		
		#if 1	/* 打印数据 */
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
		
		// 下一目录
		lDataCnt = 0;
		lDataLen = 0;
		lCatalogSerial = Store_Algo_NextCatalogGet(&SwimStoreInfo, lCatalogSerial);
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
uint16_t Store_Swim_CatalogAllUpload(void)
{
	Store_Algo_CatalogAllUpload(&SwimStoreInfo);
	
	return Ret_OK;	
}



// 模拟产生假数据，用于测试
#define SWIM_DATE_SIMULATA_LEN	(80)
void Store_Swim_DateSimulata(void)
{
	STORE_SWIM_RTT_LOG(0, "Store_Swim_DateSimulata \n");
	
	#if 0
	swimIndoorInfo_t swimIndoorInfo;
	
	Store_Swim_ClearInit();
	
	for(uint32_t t = 0;t < 2;t++)
	{
		// 保存在目录附加区域的数据
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














