#include "store_bodytemp.h"
#include "store_algo.h"
#include "app_variable.h"
#include "mid_rtc.h"

StoreInfo_t					BodytempStoreInfo;
StoreBodytempParam_t		StoreBodytempParam;

static void Store_Bodytemp_ParamInit(void)
{
	BodytempStoreInfo.Status = eStoreStatusNull;			// 存储状态				
	
	BodytempStoreInfo.CatalogBeginAddr = STORE2_BODYTEMP_CATALOG_BEGIN_ADDR;	// 固定值，目录存储开始起始
	BodytempStoreInfo.CatalogEndAddr = STORE2_BODYTEMP_CATALOG_END_ADDR;		// 固定值，目录存储结束地址（包括）

	BodytempStoreInfo.CatalogSerialMax = STORE2_BODYTEMP_MAX_ALLOT_CATALOG;		// 固定值，最大目录数，由分配的存储空间决定
	BodytempStoreInfo.CatalogSerialMaxSave = STORE2_BODYTEMP_MAX_SAVE_CATALOG;	// 固定值，被保存的最大目录
	BodytempStoreInfo.CatalogSerialBegin = BodytempStoreInfo.CatalogSerialMax - 1;	// 有效存储目录开始序号，若目录Cnt大于目录MaxSave，则当前目录Begin标记被覆盖，然后+1
	BodytempStoreInfo.CatalogSerialEnd = BodytempStoreInfo.CatalogSerialMax - 1;		// 有效存储目录结束序号，每次创建目录时+1
	BodytempStoreInfo.CatalogSerialCnt = 0;		// 已存储目录计数，每次封存目录时+1，最大不超过MaxSave

	BodytempStoreInfo.DataBeginAddr = STORE2_BODYTEMP_DATA_BEGIN_ADDR;	// 固定值，数据存储开始起始
	BodytempStoreInfo.DataEndAddr = STORE2_BODYTEMP_DATA_END_ADDR;	// 固定值，数据存储结束地址（包括）	
	BodytempStoreInfo.DataCurrAddr = BodytempStoreInfo.DataBeginAddr;	// 当前数据存储地址
}

// 数据清零方式初始化
void Store_Bodytemp_ClearInit(void)
{
	/* 存储参数初始化 */
	Store_Bodytemp_ParamInit();
	
	/* 擦除相关flash区域，防止之前的错误数据产生影响 */
	Mid_NandFlash_Erase(BodytempStoreInfo.CatalogBeginAddr, BodytempStoreInfo.DataEndAddr);
	
	StoreBodytempParam.InitFlg = true;
}

// 数据恢复方式初始化
void Store_Bodytemp_RecoverInit(void)
{
	/* 存储参数初始化 */
	Store_Bodytemp_ParamInit();
	
	/* 数据恢复 */
	Store_Algo_CatalogRecover(&BodytempStoreInfo);
	
	StoreBodytempParam.InitFlg = true;
}

StoreInfo_t* Store_Bodytemp_StoreInfoGet(void)
{
	return &BodytempStoreInfo;
}

StoreBodytempParam_t* Store_Bodytemp_ParamPGet(void)
{
	return &StoreBodytempParam;
}

/*******************************************************************************
 * Brief : 跑步存储算法，需存储时调用一次
 * Input : @CurrUtc 当前UTC时间 
		   @Bodytemp 	需存储的值
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Store_Bodytemp_algorithm(void)
{
	if(false == StoreBodytempParam.InitFlg)
		return;	
	
	int16_t lBodytemp = 39;
	
	/* 若当前没创建目录，则创建 */
	if(eStoreStatusNull == BodytempStoreInfo.Status)
	{
		Store_Bodytemp_CatalogCreate();
	}
	
	StoreBodytempParam.LogBuf[StoreBodytempParam.LogCnt*STORE2_BODYTEMP_DATA_CLASSIFY_LEN + 0] = (uint8_t)(lBodytemp >> 8);
	StoreBodytempParam.LogBuf[StoreBodytempParam.LogCnt*STORE2_BODYTEMP_DATA_CLASSIFY_LEN + 1] = (uint8_t)(lBodytemp);
	
	StoreBodytempParam.LogCnt++;	
	
	// RAM缓存满后，存到flash
	if(StoreBodytempParam.LogCnt >= STORE2_BODYTEMP_LOG_MAX)
	{
		Store_Bodytemp_DataSave();
	}	
}

/*******************************************************************************
 * Brief : 跑步数据目录创建
 * Input : @CurrUtc 当前UTC时间
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Bodytemp_CatalogCreate(void)
{
	if(false == StoreBodytempParam.InitFlg)
		return Ret_NoInit;
	
	if(eStoreStatusNull != BodytempStoreInfo.Status)
		return Ret_DeviceBusy;	

	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	
	/* 
		目录参数初始化，并创建。其他如下信息会在底层函数里，统一设置
		BodytempStoreInfo.Catalog.Flash.Info.DataAddr = BodytempStoreInfo.DataCurrAddr;
		BodytempStoreInfo.Catalog.Flash.Info.Mark = eCatalogMarkUsing;	
	*/
	BodytempStoreInfo.Catalog.User.Info.DataClassify = eDataClassifyBodytemp;
	BodytempStoreInfo.Catalog.User.Info.UTC = lMidRTC->UTC;
	Store_Algo_CatalogCreate(&BodytempStoreInfo);

	// 创建目录后log计数清零
	StoreBodytempParam.LogCnt = 0;	
	
	return Ret_OK;
}

// 跑步数据存储
uint16_t Store_Bodytemp_DataSave(void)
{
	/* 跑步数据存储 */
	Store_Algo_DataSave(&BodytempStoreInfo, StoreBodytempParam.LogBuf, StoreBodytempParam.LogCnt*STORE2_BODYTEMP_DATA_CLASSIFY_LEN);
	
	/* 清空RAM缓存 */
	StoreBodytempParam.LogCnt = 0;
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : 跑步数据目录封存
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Bodytemp_CatalogSeal(void)
{
	if(false == StoreBodytempParam.InitFlg)
		return Ret_NoInit;	
	
	if(eStoreStatusIng != BodytempStoreInfo.Status)
		return Ret_NoInit;	
	
	/* 封存前保存一次RAM的数据 */
	if(StoreBodytempParam.LogCnt)
	{
		Store_Bodytemp_DataSave();
	}	
	
	/* 目录封存 */
	Store_Algo_CatalogSeal(&BodytempStoreInfo, NULL, 0);

	return Ret_OK;
}

/*******************************************************************************
 * Brief : 读取跑步数据，仅用于debug测试
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Bodytemp_DataRead(void)
{
	CatalogInfo_t		lCatalog;
	uint8_t 		lDataBuf[512];
	uint32_t 		lDataLen = 0,lDataCnt = 0;
	uint32_t	lCatalogSerial;
	
	#if 1	// 整体存储信息打印
	STORE_BODYTEMP_RTT_LOG(0, "BodytempStoreInfo Read: \n");
	STORE_BODYTEMP_RTT_LOG(0, "  .Status %d \n", BodytempStoreInfo.Status);
	STORE_BODYTEMP_RTT_LOG(0, "  .CatalogBeginAddr 0x%X \n", BodytempStoreInfo.CatalogBeginAddr);
	STORE_BODYTEMP_RTT_LOG(0, "  .CatalogEndAddr 0x%X \n", BodytempStoreInfo.CatalogEndAddr);
	STORE_BODYTEMP_RTT_LOG(0, "  .CatalogSerialMax %d \n", BodytempStoreInfo.CatalogSerialMax);
	STORE_BODYTEMP_RTT_LOG(0, "  .CatalogSerialMaxSave %d \n", BodytempStoreInfo.CatalogSerialMaxSave);
	STORE_BODYTEMP_RTT_LOG(0, "  .CatalogSerialBegin %d \n", BodytempStoreInfo.CatalogSerialBegin);
	STORE_BODYTEMP_RTT_LOG(0, "  .CatalogSerialEnd %d \n", BodytempStoreInfo.CatalogSerialEnd);
	STORE_BODYTEMP_RTT_LOG(0, "  .CatalogSerialCnt %d \n", BodytempStoreInfo.CatalogSerialCnt);
	STORE_BODYTEMP_RTT_LOG(0, "  .DataBeginAddr 0x%X \n", BodytempStoreInfo.DataBeginAddr);
	STORE_BODYTEMP_RTT_LOG(0, "  .DataEndAddr 0x%X \n", BodytempStoreInfo.DataEndAddr);
	STORE_BODYTEMP_RTT_LOG(0, "  .DataCurrAddr 0x%X \n", BodytempStoreInfo.DataCurrAddr);
	#endif
	
	#if 1	// 目录打印
	lCatalogSerial = BodytempStoreInfo.CatalogSerialBegin;
	for(uint32_t k = 0;k < BodytempStoreInfo.CatalogSerialCnt;k++)
	{
		#if 1 /* 目录信息 */
		Store_Algo_CatalogRead(&BodytempStoreInfo, lCatalogSerial, &lCatalog);
		STORE_BODYTEMP_RTT_LOG(0, "Store_Algo_CatalogRead %d :\n", lCatalogSerial);
		STORE_BODYTEMP_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
		STORE_BODYTEMP_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
		STORE_BODYTEMP_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
		STORE_BODYTEMP_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
		STORE_BODYTEMP_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
		STORE_BODYTEMP_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
		#endif
		
		#if 1 /* 目录附加信息 */
		Store_Algo_CatalogExtRead(&BodytempStoreInfo, lCatalogSerial, lDataBuf, lCatalog.User.Info.ExtDataLen);
		STORE_BODYTEMP_RTT_LOG(0, "Store_Algo_CatalogExtRead \n");
		for(uint32_t t = 0;t < lCatalog.User.Info.ExtDataLen;t++)
		{
			if((0 == t%32) && (0 != t))
			{
				STORE_BODYTEMP_RTT_LOG(0, "\n");
			}
			STORE_BODYTEMP_RTT_LOG(0, "%02X ", lDataBuf[t]);
		}STORE_BODYTEMP_RTT_LOG(0, "\n");
		#endif
		
		#if 1	/* 打印数据 */
		STORE_BODYTEMP_RTT_LOG(0, "Store_Algo_DataRead \n");
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
			Store_Algo_DataRead(&BodytempStoreInfo, &lCatalog, lDataCnt-lDataLen, lDataBuf, lDataLen);
			for(uint32_t t = 0;t < lDataLen;t++)
			{
				if((0 == t%28) && (0 != t))
				{
					STORE_BODYTEMP_RTT_LOG(0, "\n");
				}
				STORE_BODYTEMP_RTT_LOG(0, "%02X ", lDataBuf[t]);
			}STORE_BODYTEMP_RTT_LOG(0, "\n");
		}while(lDataCnt != lCatalog.Flash.Info.DataLen);
		#endif
		
		// 下一目录
		lDataCnt = 0;
		lDataLen = 0;
		lCatalogSerial = Store_Algo_NextCatalogGet(&BodytempStoreInfo, lCatalogSerial);
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
uint16_t Store_Bodytemp_CatalogAllUpload(void)
{
	Store_Algo_CatalogAllUpload(&BodytempStoreInfo);
	
	return Ret_OK;	
}

/*******************************************************************************
 * Brief : 获取用于UI显示的数据（最新144个点）
 * Input : @buf 指针，最新数据在前
		   @Len 暂未使用
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
#define BODYTEMP_UI_DATA_LEN		(144)	// 用于UI显示的数据个数
#define BODYTEMP_UI_DATA_INTERVAL	(5)	// 数据间隔（每多少个数据取一个用于UI显示）
void Store_Bodytemp_UIDataGet(int16_t* Buf, uint32_t Len)
{
	uint32_t lIntervalCnt = 0;
	uint32_t tReadLen = 0;	// 已读取的数据长度
	uint32_t tCatalog;
	CatalogInfo_t fCatalogInfo;
	uint8_t* lDataBuf;
	uint32_t lDataLen;	
	
	memset(Buf, 0x00, BODYTEMP_UI_DATA_LEN*sizeof(Buf[0]));	// 初始化Buf默认值

	lDataBuf = pvPortMalloc(STORE_MAX_MALLOC_LEN);
	
	/* 读取未存入flash的数据 */ 
	if(eStoreStatusIng == BodytempStoreInfo.Status)
	{
		for(uint32_t i = StoreBodytempParam.LogCnt;i > 0;i--)
		{
			if(++lIntervalCnt == BODYTEMP_UI_DATA_INTERVAL)
			{
				lIntervalCnt = 0;
				
				Buf[tReadLen++] = (uint16_t)((StoreBodytempParam.LogBuf[STORE2_BODYTEMP_DATA_CLASSIFY_LEN*(i-1)] << 8) + 
								StoreBodytempParam.LogBuf[STORE2_BODYTEMP_DATA_CLASSIFY_LEN*(i-1)+1]);	// 最新值在先
				if(tReadLen >= BODYTEMP_UI_DATA_LEN)
					goto Done;			
			}

		}
	}
	
	/* 读取已存入flash的数据 */ 
	if(eStoreStatusIng == BodytempStoreInfo.Status)
	{
		tCatalog = Store_Algo_NextCatalogGet(&BodytempStoreInfo, BodytempStoreInfo.CatalogSerialEnd);
	}
	else
	{
		tCatalog = BodytempStoreInfo.CatalogSerialBegin;
	}
	for(uint32_t i = 0;i < BodytempStoreInfo.CatalogSerialCnt;i++)
	{
		/* 读取目录信息 */ 
		Store_Algo_CatalogRead(&BodytempStoreInfo, tCatalog, &fCatalogInfo);
		
		/* 读取FLASH数据，最大读取STORE_MAX_MALLOC_LEN字节。正常情况下也不会超过此值 */ 
		if(fCatalogInfo.Flash.Info.DataLen >= STORE_MAX_MALLOC_LEN)
			lDataLen = STORE_MAX_MALLOC_LEN;
		else
			lDataLen = fCatalogInfo.Flash.Info.DataLen;
		Store_Algo_DataRead(&BodytempStoreInfo, &fCatalogInfo, 0, lDataBuf, lDataLen);		

		for(uint32_t j = lDataLen / STORE2_BODYTEMP_DATA_CLASSIFY_LEN;j > 0;j--)
		{
			if(++lIntervalCnt == BODYTEMP_UI_DATA_INTERVAL)
			{
				lIntervalCnt = 0;
				Buf[tReadLen++] = (uint16_t)((lDataBuf[STORE2_BODYTEMP_DATA_CLASSIFY_LEN*(j-1)] << 8) + 
							lDataBuf[STORE2_BODYTEMP_DATA_CLASSIFY_LEN*(j-1)+1]);	// 最新值在先
				if(tReadLen >= BODYTEMP_UI_DATA_LEN)
					goto Done;
			}
		}
		
		// 上一目录
		tCatalog = Store_Algo_LastCatalogGet(&BodytempStoreInfo, BodytempStoreInfo.CatalogSerialEnd);
	}
	
	vPortFree(lDataBuf);
	
Done:
	vPortFree(lDataBuf);
}

// 模拟产生假数据，用于测试
#define BODYTEMP_DATE_SIMULATA_LEN	(189)
void Store_Bodytemp_DateSimulata(void)
{
	STORE_BODYTEMP_RTT_LOG(0, "Store_Bodytemp_DateSimulata \n");
	
	#if 0
	int16_t lBodytemp;
	
	Store_Bodytemp_ClearInit();
	
	for(uint32_t t = 0;t < 2;t++)
	{
		Store_Bodytemp_CatalogCreate();
		for(uint32_t i = 0; i < BODYTEMP_DATE_SIMULATA_LEN;i++)
		{
			lBodytemp = i;
			Store_Bodytemp_algorithm();
		}
		Store_Bodytemp_CatalogSeal();	
	}
	#endif
	
	#if 0
	uint16 UIData[144] = { 351 ,367  ,370  ,387  ,399  ,356  ,333  ,365  ,331  ,328  ,389  ,397  ,354  ,355  ,370  ,380  ,355  ,365  ,362  ,363  ,363  ,363  ,362  ,360  ,362  ,358  ,360  ,362  ,359  ,360  ,362  ,359  ,362  ,362  ,361  ,361  ,
	 358  ,369  ,359  ,364  ,381  ,361  ,363  ,385  ,364  ,357  ,359  ,360  ,359  ,360  ,359  ,360  ,356  ,356  ,359  ,358  ,356  ,356  ,356  ,357  ,357  ,358  ,356  ,359  ,355  ,357  ,355  ,357  ,357  ,357  ,355  ,
	 355  ,356  ,355  ,355  ,355  ,353  ,356  ,354  ,356  ,355  ,357  ,356  ,384  ,358  ,360  ,353  ,355  ,361  ,358  ,363  ,363  ,358  ,372  ,358  ,357  ,363  ,357  ,368  ,356  ,356  ,363  ,357  ,360  ,362  ,360  ,366  ,359  ,357  ,
	 353  ,361  ,352  ,373  ,357  ,358  ,356  ,357  ,355  ,356  ,357  ,358  ,356  ,357  ,355  ,356  ,358  ,356  ,357  ,355  ,356  ,358  ,356  ,357  ,355  ,356,  357  ,355  ,356,  357  ,355  ,356,  357  ,355  ,356};
	uint32 lUTC = 1542078756;	// 1542078756 北京时间 2018/11/13 11:12:36

	Store_Bodytemp_ClearInit();
	
	Store_Bodytemp_CatalogCreate();
	for(uint32_t i = 0; i < 144;i++)
	{
		Store_Bodytemp_algorithm();
//		Store_Bodytemp_algorithm();
		lUTC += 120;	// 2min一个包
	}
	Store_Bodytemp_CatalogSeal();			
	
	#endif
}













