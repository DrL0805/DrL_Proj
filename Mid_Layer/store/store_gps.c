#include "app_variable.h"
#include "store_gps.h"
#include "store_algo.h"
#include "scene_step.h"
#include "mid_rtc.h"

StoreInfo_t			GPSStoreInfo;
StoreGPSParam_t		StoreGPSParam;

static void Store_GPS_ParamInit(void)
{
	GPSStoreInfo.Status = eStoreStatusNull;			// 存储状态				
	
	GPSStoreInfo.CatalogBeginAddr = STORE2_GPS_CATALOG_BEGIN_ADDR;	// 固定值，目录存储开始起始
	GPSStoreInfo.CatalogEndAddr = STORE2_GPS_CATALOG_END_ADDR;		// 固定值，目录存储结束地址（包括）

	GPSStoreInfo.CatalogSerialMax = STORE2_GPS_MAX_ALLOT_CATALOG;		// 固定值，最大目录数，由分配的存储空间决定
	GPSStoreInfo.CatalogSerialMaxSave = STORE2_GPS_MAX_SAVE_CATALOG;	// 固定值，被保存的最大目录
	GPSStoreInfo.CatalogSerialBegin = GPSStoreInfo.CatalogSerialMax - 1;	// 有效存储目录开始序号，若目录Cnt大于目录MaxSave，则当前目录Begin标记被覆盖，然后+1
	GPSStoreInfo.CatalogSerialEnd = GPSStoreInfo.CatalogSerialMax - 1;		// 有效存储目录结束序号，每次创建目录时+1
	GPSStoreInfo.CatalogSerialCnt = 0;		// 已存储目录计数，每次封存目录时+1，最大不超过MaxSave

	GPSStoreInfo.DataBeginAddr = STORE2_GPS_DATA_BEGIN_ADDR;	// 固定值，数据存储开始起始
	GPSStoreInfo.DataEndAddr = STORE2_GPS_DATA_END_ADDR;	// 固定值，数据存储结束地址（包括）	
	GPSStoreInfo.DataCurrAddr = GPSStoreInfo.DataBeginAddr;	// 当前数据存储地址
}

// 数据清零方式初始化
void Store_GPS_ClearInit(void)
{
	/* 存储参数初始化 */
	Store_GPS_ParamInit();
	
	/* 擦除相关flash区域，防止之前的错误数据产生影响 */
	Mid_NandFlash_Erase(GPSStoreInfo.CatalogBeginAddr, GPSStoreInfo.DataEndAddr);
	
	StoreGPSParam.InitFlg = true;
}

// 数据恢复方式初始化
void Store_GPS_RecoverInit(void)
{
	/* 存储参数初始化 */
	Store_GPS_ParamInit();
	
	/* 数据恢复 */
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
 * Brief : 跑步存储算法，需存储时调用一次
 * Input : @CurrUtc 当前UTC时间 
		   @GPS 	需存储的值
 * Return: @NULL
 * Call  : 
 ***************/
void Store_GPS_algorithm(void)
{
	if(false == StoreGPSParam.InitFlg)
		return;	
	
	int16 		LongitudeBias;	// 精度差值
	int16 		LatitudeBias;	// 纬度差值
	int8		AltitudeBias;	// 海拔差值
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
	
	/* 若当前没创建目录，则创建 */
	if(eStoreStatusNull == GPSStoreInfo.Status)
	{
		Store_GPS_CatalogCreate();
	}
	
	if(1)	// GPS定位成功
	{
		if(StoreGPSParam.Algo.NewCatalogFlg)
		/* 首次定位成功，保存GPS的首次定位数据 */
		{
			StoreGPSParam.Algo.NewCatalogFlg = false;
			StoreGPSParam.Algo.BeginLongitude = 0;
			StoreGPSParam.Algo.BeginLatitude = 0;
			StoreGPSParam.Algo.BeginAltitude = 0;
			StoreGPSParam.Algo.GPSValidUTC = lMidRTC->UTC;
		}
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 1] = LongitudeBias >> 8;	// 经度差值
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 2] = LongitudeBias;	
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 3] = LatitudeBias >> 8;	// 纬度差值	
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 4] = LatitudeBias;
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 5] = AltitudeBias;			// 海拔差值
		
		
		StoreGPSParam.Algo.LastLongitude = 0;
		StoreGPSParam.Algo.LastLatitude = 0;
		StoreGPSParam.Algo.LastAltitude = 0;
		StoreGPSParam.Algo.LastStep = 0;
	}
	else
	{
		
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 1] = LongitudeBias >> 8;	// 经度差值
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 2] = LongitudeBias;	
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 3] = LatitudeBias >> 8;	// 纬度差值	
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 4] = LatitudeBias;
		StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 5] = AltitudeBias;			// 海拔差值	
	}
	
	StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 0] = 2;					// 时间累加
	StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 6] = 0;					// 心率
	StoreGPSParam.LogBuf[StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN + 7] = lpSceneStepParam->totalStep - StoreGPSParam.Algo.LastStep; // 步数差值	

	StoreGPSParam.LogCnt++;
	
	// RAM缓存满后，存到flash
	if(StoreGPSParam.LogCnt >= STORE2_GPS_LOG_MAX)
	{
		Store_GPS_DataSave();
	}
}


/*******************************************************************************
 * Brief : 跑步数据目录创建
 * Input : @CurrUtc 当前UTC时间
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
		目录参数初始化，并创建。其他如下信息会在底层函数里，统一设置
		GPSStoreInfo.Catalog.Flash.Info.DataAddr = GPSStoreInfo.DataCurrAddr;
		GPSStoreInfo.Catalog.Flash.Info.Mark = eCatalogMarkUsing;	
	*/
	GPSStoreInfo.Catalog.User.Info.DataClassify = eDataClassifyGPS;
	GPSStoreInfo.Catalog.User.Info.UTC = lMidRTC->UTC;
	Store_Algo_CatalogCreate(&GPSStoreInfo);

	// 创建目录后log计数清零
	StoreGPSParam.LogCnt = 0;
	StoreGPSParam.Algo.NewCatalogFlg = true;
	StoreGPSParam.Algo.BeginUTC = lMidRTC->UTC;
	
	return Ret_OK;
}

// 跑步数据存储
uint16_t Store_GPS_DataSave(void)
{
	/* 跑步数据存储 */
	Store_Algo_DataSave(&GPSStoreInfo, StoreGPSParam.LogBuf, StoreGPSParam.LogCnt*STORE2_GPS_DATA_CLASSIFY_LEN);
	
	/* 清空RAM缓存 */
	StoreGPSParam.LogCnt = 0;
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : 跑步数据目录封存
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
	
	/* 封存前保存一次RAM的数据 */
	if(StoreGPSParam.LogCnt)
	{
		Store_GPS_DataSave();
	}	
	
	/* 目录封存 */
	Store_Algo_CatalogSeal(&GPSStoreInfo, NULL, 0);

	return Ret_OK;
}

/*******************************************************************************
 * Brief : 读取跑步数据，仅用于debug测试
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
	
	#if 1	// 整体存储信息打印
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
	
	#if 1	// 目录打印
	lCatalogSerial = GPSStoreInfo.CatalogSerialBegin;
	for(uint32_t k = 0;k < GPSStoreInfo.CatalogSerialCnt;k++)
	{
		#if 1 /* 目录信息 */
		Store_Algo_CatalogRead(&GPSStoreInfo, lCatalogSerial, &lCatalog);
		STORE_GPS_RTT_LOG(0, "Store_Algo_CatalogRead %d :\n", lCatalogSerial);
		STORE_GPS_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
		STORE_GPS_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
		STORE_GPS_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
		STORE_GPS_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
		STORE_GPS_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
		STORE_GPS_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
		#endif
		
		#if 1 /* 目录附加信息 */
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
		
		#if 1	/* 打印数据 */
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
		
		// 下一目录
		lDataCnt = 0;
		lDataLen = 0;
		lCatalogSerial = Store_Algo_NextCatalogGet(&GPSStoreInfo, lCatalogSerial);
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
uint16_t Store_GPS_CatalogAllUpload(void)
{
	Store_Algo_CatalogAllUpload(&GPSStoreInfo);
	
	return Ret_OK;	
}

/*******************************************************************************
 * Brief : 清除存储存储在RAM中的数据
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Store_GPS_RamDataClear(void)
{
	StoreGPSParam.LogCnt = 0;
	
	Store_Algo_CatalogClear(&GPSStoreInfo);
}


// 模拟产生假数据，用于测试
#define GPS_DATE_SIMULATA_LEN	(189)
void Store_GPS_DateSimulata(void)
{
	STORE_GPS_RTT_LOG(0, "Store_GPS_DateSimulata \n");
	
	#if 0	// 跨首尾数据读写测试
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
	
	#if 1 // 故意污染数据，然后恢复数据，然后在读写测试
	
		#if 0	// 污染数据：写入数据，但是不保存
		Store_GPS_ClearInit();
		
		// 写入正常数据
		for(uint32_t lTmp = 0;lTmp < 2;lTmp++)
		{
			Store_GPS_CatalogCreate();
			for(uint32_t i = 0; i < GPS_DATE_SIMULATA_LEN + lTmp;i++)
			{
				Store_GPS_algorithm();
			}
			Store_GPS_CatalogSeal();	
		}		
		
		// 写入数据，但不封存目录
		Store_GPS_CatalogCreate();
		for(uint32_t i = 0; i < GPS_DATE_SIMULATA_LEN;i++)
		{
			Store_GPS_algorithm();
		}
		#endif
	
	
		#if 0	// 重新编译后，写入正常数据，再读取数据
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
























