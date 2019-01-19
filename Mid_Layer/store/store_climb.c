#include "store_climb.h"
#include "store_algo.h"
#include "store_history.h"
#include "mid_rtc.h"
#include "scene_climb.h"

StoreInfo_t			ClimbStoreInfo;
StoreClimbParam_t		StoreClimbParam;

/*******************************************************************************
 * Brief : 跑步过程数据
 ******************************************************************************/
 
static void Store_Climb_ParamInit(void)
{
	ClimbStoreInfo.Status = eStoreStatusNull;			// 存储状态				
	
	ClimbStoreInfo.CatalogBeginAddr = STORE2_CLIMB_CATALOG_BEGIN_ADDR;	// 固定值，目录存储开始起始
	ClimbStoreInfo.CatalogEndAddr = STORE2_CLIMB_CATALOG_END_ADDR;		// 固定值，目录存储结束地址（包括）

	ClimbStoreInfo.CatalogSerialMax = STORE2_CLIMB_MAX_ALLOT_CATALOG;		// 固定值，最大目录数，由分配的存储空间决定
	ClimbStoreInfo.CatalogSerialMaxSave = STORE2_CLIMB_MAX_SAVE_CATALOG;	// 固定值，被保存的最大目录
	ClimbStoreInfo.CatalogSerialBegin = ClimbStoreInfo.CatalogSerialMax - 1;	// 有效存储目录开始序号，若目录Cnt大于目录MaxSave，则当前目录Begin标记被覆盖，然后+1
	ClimbStoreInfo.CatalogSerialEnd = ClimbStoreInfo.CatalogSerialMax - 1;		// 有效存储目录结束序号，每次创建目录时+1
	ClimbStoreInfo.CatalogSerialCnt = 0;		// 已存储目录计数，每次封存目录时+1，最大不超过MaxSave

	ClimbStoreInfo.DataBeginAddr = STORE2_CLIMB_DATA_BEGIN_ADDR;	// 固定值，数据存储开始起始
	ClimbStoreInfo.DataEndAddr = STORE2_CLIMB_DATA_END_ADDR;	// 固定值，数据存储结束地址（包括）	
	ClimbStoreInfo.DataCurrAddr = ClimbStoreInfo.DataBeginAddr;	// 当前数据存储地址
}

// 数据清零方式初始化
void Store_Climb_ClearInit(void)
{
	/* 存储参数初始化 */
	Store_Climb_ParamInit();
	
	/* 擦除相关flash区域，防止之前的错误数据产生影响 */
	Mid_NandFlash_Erase(ClimbStoreInfo.CatalogBeginAddr, ClimbStoreInfo.DataEndAddr);
	
	StoreClimbParam.InitFlg = true;
}

// 数据恢复方式初始化
void Store_Climb_RecoverInit(void)
{
	/* 存储参数初始化 */
	Store_Climb_ParamInit();
	
	/* 数据恢复 */
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
 * Brief : 跑步存储算法，需存储时调用一次
 * Input : @CurrUtc 当前UTC时间 
		   @ClimbningInfo 需存储的值
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
	
	/* 若当前没创建目录，则创建 */
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

	// 海拔
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 0] = (uint8_t)(lclimbMountainInfo.RealTimeData.Altitude >> 8);  
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 1] = (uint8_t)(lclimbMountainInfo.RealTimeData.Altitude);
	// 爬山速度
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 2] = (uint8_t)(lclimbMountainInfo.RealTimeData.Speed >> 8);  
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 3] = (uint8_t)(lclimbMountainInfo.RealTimeData.Speed);
	// 心率
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 4] = (uint8_t)(lclimbMountainInfo.RealTimeData.Hr); 
	// 经度
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 5] = (uint8_t)(lclimbMountainInfo.RealTimeData.Longitude.u8[3]);
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 6] = (uint8_t)(lclimbMountainInfo.RealTimeData.Longitude.u8[2]);
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 7] = (uint8_t)(lclimbMountainInfo.RealTimeData.Longitude.u8[1]);
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 8] = (uint8_t)(lclimbMountainInfo.RealTimeData.Longitude.u8[0]);
	// 纬度
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 9] =  (uint8_t)(lclimbMountainInfo.RealTimeData.Latitude.u8[3]);
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 10] = (uint8_t)(lclimbMountainInfo.RealTimeData.Latitude.u8[2]);
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 11] = (uint8_t)(lclimbMountainInfo.RealTimeData.Latitude.u8[1]);
	StoreClimbParam.LogBuf[StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN + 12] = (uint8_t)(lclimbMountainInfo.RealTimeData.Latitude.u8[0]); 		

	StoreClimbParam.LogCnt++;
	
	// RAM缓存满后，存到flash
	if(StoreClimbParam.LogCnt >= STORE2_CLIMB_LOG_MAX)
	{
		Store_Climb_DataSave();
	}
}


/*******************************************************************************
 * Brief : 跑步数据目录创建
 * Input : @CurrUtc 当前UTC时间
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
		目录参数初始化，并创建。其他如下信息会在底层函数里，统一设置
		ClimbStoreInfo.Catalog.Flash.Info.DataAddr = ClimbStoreInfo.DataCurrAddr;
		ClimbStoreInfo.Catalog.Flash.Info.Mark = eCatalogMarkUsing;	
	*/
	ClimbStoreInfo.Catalog.User.Info.DataClassify = eDataClassifyClimbNew;
	ClimbStoreInfo.Catalog.User.Info.UTC = lMidRTC->UTC;
	Store_Algo_CatalogCreate(&ClimbStoreInfo);

	// 创建目录后log计数清零
	StoreClimbParam.LogCnt = 0;	
	
	return Ret_OK;
}

// 跑步数据存储
uint16_t Store_Climb_DataSave(void)
{
	/* 跑步数据存储 */
	Store_Algo_DataSave(&ClimbStoreInfo, StoreClimbParam.LogBuf, StoreClimbParam.LogCnt*STORE2_CLIMB_DATA_CLASSIFY_LEN);
	
	/* 清空RAM缓存 */
	StoreClimbParam.LogCnt = 0;
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : 跑步数据目录封存
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
	
	/* 封存前保存一次RAM的数据 */
	if(StoreClimbParam.LogCnt)
	{
		Store_Climb_DataSave();
	}	
	
	/* 读取当前运动档案数据 */
	Scene_Climb_InfoGet(&lclimbMountainInfo);
	
	#if 1
	STORE_CLIMB_RTT_LOG(0, "Store_Climb_CatalogSeal %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d \n",
		lclimbMountainInfo.RecordData.StartUTC, lclimbMountainInfo.RecordData.StopUTC, lclimbMountainInfo.RecordData.Duration,
		lclimbMountainInfo.RecordData.Step, lclimbMountainInfo.RecordData.Distance, lclimbMountainInfo.RecordData.UpAltitude,
		lclimbMountainInfo.RecordData.DownAltitude, lclimbMountainInfo.RecordData.HighestAltitude, lclimbMountainInfo.RecordData.LowestAltitude,
		lclimbMountainInfo.RecordData.SpeedAVG, lclimbMountainInfo.RecordData.Calorie, lclimbMountainInfo.RecordData.HrAVG,
		lclimbMountainInfo.RecordData.HrMax);
	#endif	
	
	/* 目录封存 */
	Store_Algo_CatalogSeal(&ClimbStoreInfo, (uint8_t*)&lclimbMountainInfo.RecordData, sizeof(climbMountainRecord_t));

	/* 增加到运动历史列表 */
	lStoreHistoryList.CatalogSerial = ClimbStoreInfo.CatalogSerialEnd;
	lStoreHistoryList.DataClassify = eDataClassifyClimbNew;
	lStoreHistoryList.Distance = lclimbMountainInfo.RecordData.Distance;
	lStoreHistoryList.UTC = lclimbMountainInfo.RecordData.StartUTC;
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
uint16_t Store_Climb_DataRead(void)
{
	CatalogInfo_t		lCatalog;
	uint8_t 		lDataBuf[512];
	uint32_t 		lDataLen = 0,lDataCnt = 0;
	uint32_t	lCatalogSerial;
	
	#if 1	// 整体存储信息打印
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
	
	#if 1	// 目录打印
	lCatalogSerial = ClimbStoreInfo.CatalogSerialBegin;
	for(uint32_t k = 0;k < ClimbStoreInfo.CatalogSerialCnt;k++)
	{
		#if 1 /* 目录信息 */
		Store_Algo_CatalogRead(&ClimbStoreInfo, lCatalogSerial, &lCatalog);
		STORE_CLIMB_RTT_LOG(0, "Store_Algo_CatalogRead %d :\n", lCatalogSerial);
		STORE_CLIMB_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
		STORE_CLIMB_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
		STORE_CLIMB_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
		STORE_CLIMB_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
		STORE_CLIMB_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
		STORE_CLIMB_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
		#endif
		
		#if 1 /* 目录附加信息 */
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
		
		#if 1	/* 打印数据 */
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
		
		// 下一目录
		lDataCnt = 0;
		lDataLen = 0;
		lCatalogSerial = Store_Algo_NextCatalogGet(&ClimbStoreInfo, lCatalogSerial);
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
uint16_t Store_Climb_CatalogAllUpload(void)
{
	Store_Algo_CatalogAllUpload(&ClimbStoreInfo);
	
	return Ret_OK;	
}



// 模拟产生假数据，用于测试
#define CLIMB_DATE_SIMULATA_LEN	(119)
void Store_Climb_DateSimulata(void)
{
	STORE_CLIMB_RTT_LOG(0, "Store_Climb_DateSimulata \n");
	
	#if 1
	climbMountainInfo_t climbMountainInfo;
	
	Store_Climb_ClearInit();
	
	for(uint32_t t = 0;t < 2;t++)
	{
		// 保存在目录附加区域的数据
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
