#include "store_run.h"
#include "store_algo.h"
#include "store_history.h"
#include "mid_rtc.h"
#include "scene_run.h"

StoreInfo_t			RunStoreInfo;
StoreRunParam_t		StoreRunParam;

/*******************************************************************************
 * Brief : 跑步过程数据
 ******************************************************************************/
 
static void Store_Run_ParamInit(void)
{
	RunStoreInfo.Status = eStoreStatusNull;			// 存储状态				
	
	RunStoreInfo.CatalogBeginAddr = STORE2_RUN_CATALOG_BEGIN_ADDR;	// 固定值，目录存储开始起始
	RunStoreInfo.CatalogEndAddr = STORE2_RUN_CATALOG_END_ADDR;		// 固定值，目录存储结束地址（包括）
	RunStoreInfo.CatalogSerialMax = STORE2_RUN_MAX_ALLOT_CATALOG;		// 固定值，最大目录数，由分配的存储空间决定
	RunStoreInfo.CatalogSerialMaxSave = STORE2_RUN_MAX_SAVE_CATALOG;	// 固定值，被保存的最大目录
	RunStoreInfo.CatalogSerialBegin = RunStoreInfo.CatalogSerialMax - 1;	// 有效存储目录开始序号，若目录Cnt大于目录MaxSave，则当前目录Begin标记被覆盖，然后+1
	RunStoreInfo.CatalogSerialEnd = RunStoreInfo.CatalogSerialMax - 1;		// 有效存储目录结束序号，每次创建目录时+1
	RunStoreInfo.CatalogSerialCnt = 0;		// 已存储目录计数，每次封存目录时+1，最大不超过MaxSave

	RunStoreInfo.DataBeginAddr = STORE2_RUN_DATA_BEGIN_ADDR;	// 固定值，数据存储开始起始
	RunStoreInfo.DataEndAddr = STORE2_RUN_DATA_END_ADDR;	// 固定值，数据存储结束地址（包括）	
	RunStoreInfo.DataCurrAddr = RunStoreInfo.DataBeginAddr;	// 当前数据存储地址
}

// 数据清零方式初始化
void Store_Run_ClearInit(void)
{
	/* 存储参数初始化 */
	Store_Run_ParamInit();
	
	/* 擦除相关flash区域，防止之前的错误数据产生影响 */
	Mid_NandFlash_Erase(RunStoreInfo.CatalogBeginAddr, RunStoreInfo.DataEndAddr);
	
	StoreRunParam.InitFlg = true;
}

// 数据恢复方式初始化
void Store_Run_RecoverInit(void)
{
	/* 存储参数初始化 */
	Store_Run_ParamInit();
	
	/* 数据恢复 */
	Store_Algo_CatalogRecover(&RunStoreInfo);
	
	StoreRunParam.InitFlg = true;
}

StoreInfo_t* Store_Run_StoreInfoGet(void)
{
	return &RunStoreInfo;
}

StoreRunParam_t* Store_Run_ParamPGet(void)
{
	return &StoreRunParam;
}

/*******************************************************************************
 * Brief : 跑步存储算法，需存储时调用一次
 * Input : @CurrUtc 当前UTC时间 
		   @RunningInfo 需存储的值
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Store_Run_algorithm(void)
{
	if(!StoreRunParam.InitFlg) drERROR_CHECK_RETURN_NULL("Store_Run_algorithm", Ret_NoInit);

	runningInfo_t lrunningInfo;
	Scene_Run_InfoGet(&lrunningInfo);	

	#if 1
	STORE_RUN_RTT_LOG(0, "Store_Run_algorithm: Pace %d, Freq %d, Stride %d, HR %d, Longitude %d, Longitude %d \n", 
		lrunningInfo.RealTimeData.Pace, lrunningInfo.RealTimeData.Freq, lrunningInfo.RealTimeData.Stride,
		lrunningInfo.RealTimeData.HR, lrunningInfo.RealTimeData.Longitude.f, lrunningInfo.RealTimeData.Latitude.f);
	#endif

	/* 若当前没创建目录，则创建 */
	if(eStoreStatusNull == RunStoreInfo.Status)
	{
		Store_Run_CatalogCreate();
	}
	
	// 配速
	StoreRunParam.LogBuf[StoreRunParam.LogCnt*STORE2_RUN_DATA_CLASSIFY_LEN + 0] = (uint8_t)(lrunningInfo.RealTimeData.Pace >> 8);  
	StoreRunParam.LogBuf[StoreRunParam.LogCnt*STORE2_RUN_DATA_CLASSIFY_LEN + 1] = (uint8_t)(lrunningInfo.RealTimeData.Pace);
	// 步频                                                                                            
	StoreRunParam.LogBuf[StoreRunParam.LogCnt*STORE2_RUN_DATA_CLASSIFY_LEN + 2] = (uint8_t)(lrunningInfo.RealTimeData.Freq >> 8);  
	StoreRunParam.LogBuf[StoreRunParam.LogCnt*STORE2_RUN_DATA_CLASSIFY_LEN + 3] = (uint8_t)(lrunningInfo.RealTimeData.Freq);
	// 心率                                                                                            
	StoreRunParam.LogBuf[StoreRunParam.LogCnt*STORE2_RUN_DATA_CLASSIFY_LEN + 4] = (uint8_t)(lrunningInfo.RealTimeData.HR); 
	// 经度                                                                                            
	StoreRunParam.LogBuf[StoreRunParam.LogCnt*STORE2_RUN_DATA_CLASSIFY_LEN + 5] = (uint8_t)(lrunningInfo.RealTimeData.Longitude.u8[3]);
	StoreRunParam.LogBuf[StoreRunParam.LogCnt*STORE2_RUN_DATA_CLASSIFY_LEN + 6] = (uint8_t)(lrunningInfo.RealTimeData.Longitude.u8[2]);
	StoreRunParam.LogBuf[StoreRunParam.LogCnt*STORE2_RUN_DATA_CLASSIFY_LEN + 7] = (uint8_t)(lrunningInfo.RealTimeData.Longitude.u8[1]);
	StoreRunParam.LogBuf[StoreRunParam.LogCnt*STORE2_RUN_DATA_CLASSIFY_LEN + 8] = (uint8_t)(lrunningInfo.RealTimeData.Longitude.u8[0]);
	// 纬度
	StoreRunParam.LogBuf[StoreRunParam.LogCnt*STORE2_RUN_DATA_CLASSIFY_LEN + 9] =  (uint8_t)(lrunningInfo.RealTimeData.Latitude.u8[3]);
	StoreRunParam.LogBuf[StoreRunParam.LogCnt*STORE2_RUN_DATA_CLASSIFY_LEN + 10] = (uint8_t)(lrunningInfo.RealTimeData.Latitude.u8[2]);
	StoreRunParam.LogBuf[StoreRunParam.LogCnt*STORE2_RUN_DATA_CLASSIFY_LEN + 11] = (uint8_t)(lrunningInfo.RealTimeData.Latitude.u8[1]);
	StoreRunParam.LogBuf[StoreRunParam.LogCnt*STORE2_RUN_DATA_CLASSIFY_LEN + 12] = (uint8_t)(lrunningInfo.RealTimeData.Latitude.u8[0]);
	// 步幅                                                                                             
	StoreRunParam.LogBuf[StoreRunParam.LogCnt*STORE2_RUN_DATA_CLASSIFY_LEN + 13] = (uint8_t)(lrunningInfo.RealTimeData.Stride); 

	StoreRunParam.LogCnt++;
	
	// RAM缓存满后，存到flash
	if(StoreRunParam.LogCnt >= STORE2_RUN_LOG_MAX)
	{
		Store_Run_DataSave();
	}
}

/*******************************************************************************
 * Brief : 跑步数据目录创建
 * Input : @CurrUtc 当前UTC时间
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Run_CatalogCreate(void)
{
	if(false == StoreRunParam.InitFlg)
		return Ret_NoInit;
	
	if(eStoreStatusNull != RunStoreInfo.Status)
		return Ret_DeviceBusy;	

	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	
	/* 
		目录参数初始化，并创建。其他如下信息会在底层函数里，统一设置
		RunStoreInfo.Catalog.Flash.Info.DataAddr = RunStoreInfo.DataCurrAddr;
		RunStoreInfo.Catalog.Flash.Info.Mark = eCatalogMarkUsing;	
	*/
	RunStoreInfo.Catalog.User.Info.DataClassify = eDataClassifyRunNew;
	RunStoreInfo.Catalog.User.Info.UTC = lMidRTC->UTC;
	Store_Algo_CatalogCreate(&RunStoreInfo);

	// 创建目录后log计数清零
	StoreRunParam.LogCnt = 0;	
	
	return Ret_OK;
}

// 跑步数据存储
void Store_Run_DataSave(void)
{
	/* 跑步数据存储 */
	Store_Algo_DataSave(&RunStoreInfo, StoreRunParam.LogBuf, StoreRunParam.LogCnt*STORE2_RUN_DATA_CLASSIFY_LEN);
	
	/* 清空RAM缓存 */
	StoreRunParam.LogCnt = 0;
}

/*******************************************************************************
 * Brief : 跑步数据目录封存
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Run_CatalogSeal(void)
{
	runningInfo_t lrunningInfo;
	StoreHistoryList_t lStoreHistoryList;
	
	if(false == StoreRunParam.InitFlg)
		return Ret_NoInit;	
	
	if(eStoreStatusIng != RunStoreInfo.Status)
		return Ret_NoInit;	
	
	/* 封存前保存一次RAM的数据 */
	if(StoreRunParam.LogCnt)
	{
		Store_Run_DataSave();
	}
	
	/* 读取当前运动档案数据 */
	Scene_Run_InfoGet(&lrunningInfo);
	
	#if 0	// 打印存储的目录附加信息
	{
		STORE_RUN_RTT_LOG(0, "Store_Run_CatalogSeal %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d \n",
			lrunningInfo.RecordData.StartUTC, lrunningInfo.RecordData.StopUTC, lrunningInfo.RecordData.Duration,
			lrunningInfo.RecordData.ValidDuration, lrunningInfo.RecordData.Step, lrunningInfo.RecordData.Distance,
			lrunningInfo.RecordData.Calorie, lrunningInfo.RecordData.PaceAVG, lrunningInfo.RecordData.FreqAVG,
			lrunningInfo.RecordData.StrideAVG, lrunningInfo.RecordData.HrAVG, lrunningInfo.RecordData.HrMax);
	}
	#endif
	
	/* 目录封存 */
	Store_Algo_CatalogSeal(&RunStoreInfo, (uint8_t*)&lrunningInfo.RecordData, sizeof(runningRecord_t));
	
	/* 增加到运动历史列表 */
	lStoreHistoryList.CatalogSerial = RunStoreInfo.CatalogSerialEnd;
	lStoreHistoryList.DataClassify = eDataClassifyRunNew;
	lStoreHistoryList.Distance = lrunningInfo.RecordData.Distance;
	lStoreHistoryList.UTC = lrunningInfo.RecordData.StartUTC;
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
uint16_t Store_Run_DataRead(void)
{
	CatalogInfo_t		lCatalog;
	uint8_t 		lDataBuf[512];
	uint32_t 		lDataLen = 0,lDataCnt = 0;
	uint32_t	lCatalogSerial;
	
	#if 1	// 整体存储信息打印
	STORE_RUN_RTT_LOG(0, "RunStoreInfo Read: \n");
	STORE_RUN_RTT_LOG(0, "  .Status %d \n", RunStoreInfo.Status);
	STORE_RUN_RTT_LOG(0, "  .CatalogBeginAddr 0x%X \n", RunStoreInfo.CatalogBeginAddr);
	STORE_RUN_RTT_LOG(0, "  .CatalogEndAddr 0x%X \n", RunStoreInfo.CatalogEndAddr);
	STORE_RUN_RTT_LOG(0, "  .CatalogSerialMax %d \n", RunStoreInfo.CatalogSerialMax);
	STORE_RUN_RTT_LOG(0, "  .CatalogSerialMaxSave %d \n", RunStoreInfo.CatalogSerialMaxSave);
	STORE_RUN_RTT_LOG(0, "  .CatalogSerialBegin %d \n", RunStoreInfo.CatalogSerialBegin);
	STORE_RUN_RTT_LOG(0, "  .CatalogSerialEnd %d \n", RunStoreInfo.CatalogSerialEnd);
	STORE_RUN_RTT_LOG(0, "  .CatalogSerialCnt %d \n", RunStoreInfo.CatalogSerialCnt);
	STORE_RUN_RTT_LOG(0, "  .DataBeginAddr 0x%X \n", RunStoreInfo.DataBeginAddr);
	STORE_RUN_RTT_LOG(0, "  .DataEndAddr 0x%X \n", RunStoreInfo.DataEndAddr);
	STORE_RUN_RTT_LOG(0, "  .DataCurrAddr 0x%X \n", RunStoreInfo.DataCurrAddr);
	#endif
	
	#if 1	// 目录打印
	lCatalogSerial = RunStoreInfo.CatalogSerialBegin;
	for(uint32_t k = 0;k < RunStoreInfo.CatalogSerialCnt;k++)
	{
		#if 1 /* 目录信息 */
		Store_Algo_CatalogRead(&RunStoreInfo, lCatalogSerial, &lCatalog);
		STORE_RUN_RTT_LOG(0, "Store_Algo_CatalogRead %d :\n", lCatalogSerial);
		STORE_RUN_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
		STORE_RUN_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
		STORE_RUN_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
		STORE_RUN_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
		STORE_RUN_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
		STORE_RUN_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
		#endif
		
		#if 1 /* 目录附加信息 */
		Store_Algo_CatalogExtRead(&RunStoreInfo, lCatalogSerial, lDataBuf, lCatalog.User.Info.ExtDataLen);
		STORE_RUN_RTT_LOG(0, "Store_Algo_CatalogExtRead \n");
		for(uint32_t t = 0;t < lCatalog.User.Info.ExtDataLen;t++)
		{
			if((0 == t%32) && (0 != t))
			{
				STORE_RUN_RTT_LOG(0, "\n");
			}
			STORE_RUN_RTT_LOG(0, "%02X ", lDataBuf[t]);
		}STORE_RUN_RTT_LOG(0, "\n");
		#endif
		
		#if 1	/* 打印数据 */
		STORE_RUN_RTT_LOG(0, "Store_Algo_DataRead \n");
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
			Store_Algo_DataRead(&RunStoreInfo, &lCatalog, lDataCnt-lDataLen, lDataBuf, lDataLen);
			for(uint32_t t = 0;t < lDataLen;t++)
			{
				if((0 == t%28) && (0 != t))
				{
					STORE_RUN_RTT_LOG(0, "\n");
				}
				STORE_RUN_RTT_LOG(0, "%02X ", lDataBuf[t]);
			}STORE_RUN_RTT_LOG(0, "\n");
		}while(lDataCnt != lCatalog.Flash.Info.DataLen);
		#endif
		
		// 下一目录
		lDataCnt = 0;
		lDataLen = 0;
		lCatalogSerial = Store_Algo_NextCatalogGet(&RunStoreInfo, lCatalogSerial);
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
uint16_t Store_Run_CatalogAllUpload(void)
{
	Store_Algo_CatalogAllUpload(&RunStoreInfo);
	
	return Ret_OK;	
}



// 模拟产生假数据，用于测试
#define RUN_DATE_SIMULATA_LEN	(189)
void Store_Run_DateSimulata(void)
{
	STORE_RUN_RTT_LOG(0, "Store_Run_DateSimulata \n");
	
	#if 0
	runningInfo_t runningInfo;
	
	Store_Run_ClearInit();
	
	for(uint32_t t = 0;t < 2;t++)
	{
		// 保存在目录附加区域的数据
//		memset((uint8_t*)&StoreRunParam.AlgoRecord, 0x66+t, sizeof(runningRecord_t));
		
		Store_Run_CatalogCreate();
		for(uint32_t i = 0; i < RUN_DATE_SIMULATA_LEN;i++)
		{
			memset((uint8_t *)&runningInfo, i+t, sizeof(runningInfo_t));
			Store_Run_algorithm(i, &runningInfo);
		}
		Store_Run_CatalogSeal();
	}

	#endif
}










