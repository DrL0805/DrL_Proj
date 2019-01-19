#include "store_step.h"
#include "store_algo.h"
#include "scene_step.h"
#include "mid_rtc.h"

StoreInfo_t			StepStoreInfo;
StoreStepParam_t		StoreStepParam;

/*********************************************************************
 * Brief : 清空用于UI显示的计步数据，
 * Input : @NULL
 * Output: @NULL
 * Return: 
 * Call  : 初始化时 & 每天凌晨调用
 ************/
static void Store_Step_UIDataInit(void)
{
	for(uint32_t i = 0;i < 24;i++)
		StoreStepParam.UI.LogBuf[i] = 0;
	
	StoreStepParam.CumsumStep = 0;
}
 
static void Store_Step_ParamInit(void)
{
	StepStoreInfo.Status = eStoreStatusNull;			// 存储状态				
	
	StepStoreInfo.CatalogBeginAddr = STORE2_STEP_CATALOG_BEGIN_ADDR;	// 固定值，目录存储开始起始
	StepStoreInfo.CatalogEndAddr = STORE2_STEP_CATALOG_END_ADDR;		// 固定值，目录存储结束地址（包括）

	StepStoreInfo.CatalogSerialMax = STORE2_STEP_MAX_ALLOT_CATALOG;		// 固定值，最大目录数，由分配的存储空间决定
	StepStoreInfo.CatalogSerialMaxSave = STORE2_STEP_MAX_SAVE_CATALOG;	// 固定值，被保存的最大目录
	StepStoreInfo.CatalogSerialBegin = StepStoreInfo.CatalogSerialMax - 1;	// 有效存储目录开始序号，若目录Cnt大于目录MaxSave，则当前目录Begin标记被覆盖，然后+1
	StepStoreInfo.CatalogSerialEnd = StepStoreInfo.CatalogSerialMax - 1;		// 有效存储目录结束序号，每次创建目录时+1
	StepStoreInfo.CatalogSerialCnt = 0;		// 已存储目录计数，每次封存目录时+1，最大不超过MaxSave

	StepStoreInfo.DataBeginAddr = STORE2_STEP_DATA_BEGIN_ADDR;	// 固定值，数据存储开始起始
	StepStoreInfo.DataEndAddr = STORE2_STEP_DATA_END_ADDR;	// 固定值，数据存储结束地址（包括）	
	StepStoreInfo.DataCurrAddr = StepStoreInfo.DataBeginAddr;	// 当前数据存储地址
	
	#if 0	// 故意初始化一些特殊值，对FLASH边界操作进行测试 
	StepStoreInfo.DataCurrAddr = StepStoreInfo.DataEndAddr - 100;	// 用于测试FLASH循环读写
	StepStoreInfo.CatalogSerialBegin = StepStoreInfo.CatalogSerialMax - 2;
	StepStoreInfo.CatalogSerialEnd = StepStoreInfo.CatalogSerialMax - 2;		
	#endif
	
	/* 清空用于UI显示的数据 */
	Store_Step_UIDataInit();
}

// 数据清零方式初始化
void Store_Step_ClearInit(void)
{
	/* 存储参数初始化 */
	Store_Step_ParamInit();
	
	/* 擦除相关flash区域，防止之前的错误数据产生影响 */
	Mid_NandFlash_Erase(StepStoreInfo.CatalogBeginAddr, StepStoreInfo.DataEndAddr);
	
	StoreStepParam.InitFlg = true;
}

// 数据恢复方式初始化
void Store_Step_RecoverInit(void)
{
	/* 存储参数初始化 */
	Store_Step_ParamInit();
	
	/* 数据恢复 */
	Store_Algo_CatalogRecover(&StepStoreInfo);
	
	StoreStepParam.InitFlg = true;
}

StoreInfo_t* Store_Step_StoreInfoGet(void)
{
	return &StepStoreInfo;
}

StoreStepParam_t* Store_Step_ParamPGet(void)
{
	return &StoreStepParam;
}

/*******************************************************************************
 * Brief : 跑步存储算法，需存储时调用一次
 * Input : @CurrUtc 当前UTC时间 
		   @Step 	需存储的值
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Store_Step_algorithm(void)
{
	if(false == StoreStepParam.InitFlg)
		return;	
	
	uint16_t lStep5minCnt = Scene_Step_5minCntRead();
	
	/* 若当前没创建目录，则创建 */
	if(eStoreStatusNull == StepStoreInfo.Status)
	{
		Store_Step_CatalogCreate();
	}
	
	StoreStepParam.LogBuf[StoreStepParam.LogCnt*STORE2_STEP_DATA_CLASSIFY_LEN + 0] = lStep5minCnt >> 8;
	StoreStepParam.LogBuf[StoreStepParam.LogCnt*STORE2_STEP_DATA_CLASSIFY_LEN + 1] = lStep5minCnt;	
	StoreStepParam.LogCnt++;
	
	// RAM缓存满后，存到flash
	if(StoreStepParam.LogCnt >= STORE2_STEP_LOG_MAX)
	{
		Store_Step_CatalogSeal();
	}
}


/*******************************************************************************
 * Brief : 跑步数据目录创建
 * Input : @CurrUtc 当前UTC时间
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Step_CatalogCreate(void)
{
	if(false == StoreStepParam.InitFlg)
		return Ret_NoInit;
	
	if(eStoreStatusNull != StepStoreInfo.Status)
		return Ret_DeviceBusy;	
	
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();

	/* 
		目录参数初始化，并创建。其他如下信息会在底层函数里，统一设置
		StepStoreInfo.Catalog.Flash.Info.DataAddr = StepStoreInfo.DataCurrAddr;
		StepStoreInfo.Catalog.Flash.Info.Mark = eCatalogMarkUsing;	
	*/
	StepStoreInfo.Catalog.User.Info.DataClassify = eDataClassifyStep;
	StepStoreInfo.Catalog.User.Info.UTC = lMidRTC->UTC;
	Store_Algo_CatalogCreate(&StepStoreInfo);

	// 创建目录后log计数清零
	StoreStepParam.LogCnt = 0;	
	
	return Ret_OK;
}

// 跑步数据存储
uint16_t Store_Step_DataSave(void)
{
	/* 跑步数据存储 */
	Store_Algo_DataSave(&StepStoreInfo, StoreStepParam.LogBuf, StoreStepParam.LogCnt*STORE2_STEP_DATA_CLASSIFY_LEN);
	
	/* 清空RAM缓存 */
	StoreStepParam.LogCnt = 0;
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : 跑步数据目录封存
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Step_CatalogSeal(void)
{
	if(false == StoreStepParam.InitFlg)
		return Ret_NoInit;	
	
	if(eStoreStatusIng != StepStoreInfo.Status)
		return Ret_NoInit;	
	
	/* 封存前保存一次RAM的数据 */
	if(StoreStepParam.LogCnt)
	{
		Store_Step_DataSave();
	}	
	
	/* 目录封存 */
	Store_Algo_CatalogSeal(&StepStoreInfo, NULL, 0);

	return Ret_OK;
}

/*******************************************************************************
 * Brief : 读取跑步数据，仅用于debug测试
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Step_DataRead(void)
{
	CatalogInfo_t		lCatalog;
	uint8_t 		lDataBuf[512];
	uint32_t 		lDataLen = 0,lDataCnt = 0;
	uint32_t	lCatalogSerial;
	
	#if 1	// 整体存储信息打印
	STORE_STEP_RTT_LOG(0, "StepStoreInfo Read: \n");
	STORE_STEP_RTT_LOG(0, "  .Status %d \n", StepStoreInfo.Status);
	STORE_STEP_RTT_LOG(0, "  .CatalogBeginAddr 0x%X \n", StepStoreInfo.CatalogBeginAddr);
	STORE_STEP_RTT_LOG(0, "  .CatalogEndAddr 0x%X \n", StepStoreInfo.CatalogEndAddr);
	STORE_STEP_RTT_LOG(0, "  .CatalogSerialMax %d \n", StepStoreInfo.CatalogSerialMax);
	STORE_STEP_RTT_LOG(0, "  .CatalogSerialMaxSave %d \n", StepStoreInfo.CatalogSerialMaxSave);
	STORE_STEP_RTT_LOG(0, "  .CatalogSerialBegin %d \n", StepStoreInfo.CatalogSerialBegin);
	STORE_STEP_RTT_LOG(0, "  .CatalogSerialEnd %d \n", StepStoreInfo.CatalogSerialEnd);
	STORE_STEP_RTT_LOG(0, "  .CatalogSerialCnt %d \n", StepStoreInfo.CatalogSerialCnt);
	STORE_STEP_RTT_LOG(0, "  .DataBeginAddr 0x%X \n", StepStoreInfo.DataBeginAddr);
	STORE_STEP_RTT_LOG(0, "  .DataEndAddr 0x%X \n", StepStoreInfo.DataEndAddr);
	STORE_STEP_RTT_LOG(0, "  .DataCurrAddr 0x%X \n", StepStoreInfo.DataCurrAddr);
	#endif
	
	#if 1	// 目录打印
	lCatalogSerial = StepStoreInfo.CatalogSerialBegin;
	for(uint32_t k = 0;k < StepStoreInfo.CatalogSerialCnt;k++)
	{
		#if 1 /* 目录信息 */
		Store_Algo_CatalogRead(&StepStoreInfo, lCatalogSerial, &lCatalog);
		STORE_STEP_RTT_LOG(0, "Store_Algo_CatalogRead %d :\n", lCatalogSerial);
		STORE_STEP_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
		STORE_STEP_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
		STORE_STEP_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
		STORE_STEP_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
		STORE_STEP_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
		STORE_STEP_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
		#endif
		
		#if 1 /* 目录附加信息 */
		Store_Algo_CatalogExtRead(&StepStoreInfo, lCatalogSerial, lDataBuf, lCatalog.User.Info.ExtDataLen);
		STORE_STEP_RTT_LOG(0, "Store_Algo_CatalogExtRead \n");
		for(uint32_t t = 0;t < lCatalog.User.Info.ExtDataLen;t++)
		{
			if((0 == t%32) && (0 != t))
			{
				STORE_STEP_RTT_LOG(0, "\n");
				vTaskDelay(5);
			}
			STORE_STEP_RTT_LOG(0, "%02X ", lDataBuf[t]);
		}STORE_STEP_RTT_LOG(0, "\n");
		#endif
		
		#if 1	/* 打印数据 */
		STORE_STEP_RTT_LOG(0, "Store_Algo_DataRead \n");
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
			Store_Algo_DataRead(&StepStoreInfo, &lCatalog, lDataCnt-lDataLen, lDataBuf, lDataLen);
			for(uint32_t t = 0;t < lDataLen;t++)
			{
				if((0 == t%28) && (0 != t))
				{
					STORE_STEP_RTT_LOG(0, "\n");
				}
				STORE_STEP_RTT_LOG(0, "%02X ", lDataBuf[t]);
			}STORE_STEP_RTT_LOG(0, "\n");
		}while(lDataCnt != lCatalog.Flash.Info.DataLen);
		#endif
		
		// 下一目录
		lDataCnt = 0;
		lDataLen = 0;
		lCatalogSerial = Store_Algo_NextCatalogGet(&StepStoreInfo, lCatalogSerial);
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
uint16_t Store_Step_CatalogAllUpload(void)
{
	Store_Algo_CatalogAllUpload(&StepStoreInfo);
	
	return Ret_OK;	
}

/*******************************************************************************
 * Brief : 清除存储存储在RAM中的数据
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Store_Step_RamDataClear(void)
{
	StoreStepParam.LogCnt = 0;
	
	Store_Algo_CatalogClear(&StepStoreInfo);
}

/*******************************************************************************
 * Brief : 更新用于UI显示的计步数据
 * Input : @tRTCTime 当前RTC时间
		   @TotalStep 当天总步数
 * Output: @NULL
 * Return: @NULL
 * Call  : 每小时调用一次
 ***************/
void Store_Step_UIDataUpdate(void)
{
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
	
	if(0 == lMidRTC->RTC.hour)	
	/* 每天零点清空UI计步数据 */ 
	{
		Store_Step_UIDataInit();
	}
	else
	{
		/* 若(TotalStep < tStep)说明数据出错，计步设为0*/
		if(lpSceneStepParam->totalStep < StoreStepParam.CumsumStep)
		{
			StoreStepParam.UI.LogBuf[(lMidRTC->RTC.hour-1)] = 0;
			drERROR_CHECK("Store_Step_UIDataUpdate", Ret_InvalidParam); 
		}
		else
		{
			StoreStepParam.UI.LogBuf[(lMidRTC->RTC.hour-1)] = lpSceneStepParam->totalStep - StoreStepParam.CumsumStep;
		}
		
		StoreStepParam.CumsumStep = lpSceneStepParam->totalStep;	// 今天累加计步值
	}
}


/*******************************************************************************
 * Brief : 获取用于UI显示的数据（最新24小时）
 * Input : @buf 指针 
 * Output: @Len 暂未使用，强制获取最新24小时数据
 * Return: @NULL
 * Call  : 
 ***************/
void Store_Step_UIDataGet(uint16_t* Buf, uint32_t Len)
{
	SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	
	memcpy(Buf, StoreStepParam.UI.LogBuf, 24*sizeof(Buf[0]));
	
	// 当前小时内的计步值
	Buf[lMidRTC->RTC.hour] = lpSceneStepParam->totalStep - StoreStepParam.CumsumStep;	
	
	#if 1	// debug
	STORE_STEP_RTT_LOG(0, "Store_Step_UIDataGet: \n");
	for(uint32_t i = 0;i < 24;i++)
	{
		if((0 == i%32) && (0 != i))
		{
			STORE_STEP_RTT_LOG(0, "\n");
		}
		STORE_STEP_RTT_LOG(0, "%d ", Buf[i]);
	}STORE_STEP_RTT_LOG(0, "\n");	
	#endif	
}

// 模拟产生假数据，用于测试
#define STEP_DATE_SIMULATA_LEN	(189)
void Store_Step_DateSimulata(void)
{
	STORE_STEP_RTT_LOG(0, "Store_Step_DateSimulata \n");
	
	#if 0	// 跨首尾数据读写测试
	Store_Step_ClearInit();
	
	for(uint32_t lTmp = 0;lTmp < 2;lTmp++)
	{
		Store_Step_CatalogCreate();
		for(uint32_t i = 0; i < STEP_DATE_SIMULATA_LEN + lTmp;i++)
		{
			Store_Step_algorithm();
		}
		Store_Step_CatalogSeal();	
	}

	#endif
	
	#if 1 // 故意污染数据，然后恢复数据，然后在读写测试
	
		#if 0	// 污染数据：写入数据，但是不保存
		Store_Step_ClearInit();
		
		// 写入正常数据
		for(uint32_t lTmp = 0;lTmp < 2;lTmp++)
		{
			Store_Step_CatalogCreate();
			for(uint32_t i = 0; i < STEP_DATE_SIMULATA_LEN + lTmp;i++)
			{
				Store_Step_algorithm();
			}
			Store_Step_CatalogSeal();	
		}		
		
		// 写入数据，但不封存目录
		Store_Step_CatalogCreate();
		for(uint32_t i = 0; i < STEP_DATE_SIMULATA_LEN;i++)
		{
			Store_Step_algorithm();
		}
		#endif
	
	
		#if 0	// 重新编译后，写入正常数据，再读取数据
		for(uint32_t lTmp = 0;lTmp < 2;lTmp++)
		{
			Store_Step_CatalogCreate();
			for(uint32_t i = 0; i < STEP_DATE_SIMULATA_LEN + lTmp;i++)
			{
				Store_Step_algorithm();
			}
			Store_Step_CatalogSeal();	
		}
		#endif	
	
	#endif
}


