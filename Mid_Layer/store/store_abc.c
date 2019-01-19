#include "store_abc.h"
#include "store_algo.h"
#include "app_variable.h"
#include "mid_rtc.h"
#include "scene_abc.h"

StoreInfo_t				ABCStoreInfo;
StoreABCParam_t			StoreABCParam;

static void Store_ABC_ParamInit(void)
{
	ABCStoreInfo.Status = eStoreStatusNull;			// 存储状态				
	
	ABCStoreInfo.CatalogBeginAddr = STORE2_ABC_CATALOG_BEGIN_ADDR;	// 固定值，目录存储开始起始
	ABCStoreInfo.CatalogEndAddr = STORE2_ABC_CATALOG_END_ADDR;		// 固定值，目录存储结束地址（包括）

	ABCStoreInfo.CatalogSerialMax = STORE2_ABC_MAX_ALLOT_CATALOG;		// 固定值，最大目录数，由分配的存储空间决定
	ABCStoreInfo.CatalogSerialMaxSave = STORE2_ABC_MAX_SAVE_CATALOG;	// 固定值，被保存的最大目录
	ABCStoreInfo.CatalogSerialBegin = ABCStoreInfo.CatalogSerialMax - 1;	// 有效存储目录开始序号，若目录Cnt大于目录MaxSave，则当前目录Begin标记被覆盖，然后+1
	ABCStoreInfo.CatalogSerialEnd = ABCStoreInfo.CatalogSerialMax - 1;		// 有效存储目录结束序号，每次创建目录时+1
	ABCStoreInfo.CatalogSerialCnt = 0;		// 已存储目录计数，每次封存目录时+1，最大不超过MaxSave

	ABCStoreInfo.DataBeginAddr = STORE2_ABC_DATA_BEGIN_ADDR;	// 固定值，数据存储开始起始
	ABCStoreInfo.DataEndAddr = STORE2_ABC_DATA_END_ADDR;	// 固定值，数据存储结束地址（包括）	
	ABCStoreInfo.DataCurrAddr = ABCStoreInfo.DataBeginAddr;	// 当前数据存储地址
}

// 数据清零方式初始化
void Store_ABC_ClearInit(void)
{
	/* 存储参数初始化 */
	Store_ABC_ParamInit();
	
	/* 擦除相关flash区域，防止之前的错误数据产生影响 */
	Mid_NandFlash_Erase(ABCStoreInfo.CatalogBeginAddr, ABCStoreInfo.DataEndAddr);
	
	StoreABCParam.InitFlg = true;
}

// 数据恢复方式初始化
void Store_ABC_RecoverInit(void)
{
	/* 存储参数初始化 */
	Store_ABC_ParamInit();
	
	/* 数据恢复 */
	Store_Algo_CatalogRecover(&ABCStoreInfo);
	
	StoreABCParam.InitFlg = true;
}

StoreInfo_t* Store_ABC_StoreInfoGet(void)
{
	return &ABCStoreInfo;
}

StoreABCParam_t* Store_ABC_ParamPGet(void)
{
	return &StoreABCParam;
}

/*******************************************************************************
 * Brief : 跑步存储算法，需存储时调用一次
 * Input : @CurrUtc 当前UTC时间 
		   @ABC 	需存储的值
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Store_ABC_algorithm(void)
{
	if(false == StoreABCParam.InitFlg)
		return;	
	
	Scene_ABC_Param_t* SceneABCParam = Scene_ABC_ParamPGet();
	ab_value_t lab_value;
	Scene_ABC_ABGet(&lab_value);
	
	if(SceneABCParam->Pressure.UpdateFlg)
	/* 气压算法更新（数据可读）才进行存储算法 */
	{
		if(eStoreStatusNull == ABCStoreInfo.Status)
		/* 若当前没创建目录，则创建 */
		{
			Store_ABC_CatalogCreate();
		}
		
		#if 1	// 打印信息
		STORE_ABC_RTT_LOG(0, "Store_ABC_algorithm \n");
		STORE_ABC_RTT_LOG(0, "pressure, seaLevel, altitude %d, %d, %d \n", lab_value.pressure, lab_value.seaLevel, lab_value.altitude);
		#endif
		
		// 气压
		StoreABCParam.LogBuf[StoreABCParam.LogCnt*STORE2_ABC_DATA_CLASSIFY_LEN + 0] = (uint8_t)(lab_value.pressure >> 24);  
		StoreABCParam.LogBuf[StoreABCParam.LogCnt*STORE2_ABC_DATA_CLASSIFY_LEN + 1] = (uint8_t)(lab_value.pressure >> 16);
		StoreABCParam.LogBuf[StoreABCParam.LogCnt*STORE2_ABC_DATA_CLASSIFY_LEN + 2] = (uint8_t)(lab_value.pressure >> 8);  
		StoreABCParam.LogBuf[StoreABCParam.LogCnt*STORE2_ABC_DATA_CLASSIFY_LEN + 3] = (uint8_t)(lab_value.pressure >> 0);
		// 海平面
		StoreABCParam.LogBuf[StoreABCParam.LogCnt*STORE2_ABC_DATA_CLASSIFY_LEN + 4] = (uint8_t)(lab_value.seaLevel >> 24);  
		StoreABCParam.LogBuf[StoreABCParam.LogCnt*STORE2_ABC_DATA_CLASSIFY_LEN + 5] = (uint8_t)(lab_value.seaLevel >> 16);
		StoreABCParam.LogBuf[StoreABCParam.LogCnt*STORE2_ABC_DATA_CLASSIFY_LEN + 6] = (uint8_t)(lab_value.seaLevel >> 8);  
		StoreABCParam.LogBuf[StoreABCParam.LogCnt*STORE2_ABC_DATA_CLASSIFY_LEN + 7] = (uint8_t)(lab_value.seaLevel >> 0);
		// 高度
		StoreABCParam.LogBuf[StoreABCParam.LogCnt*STORE2_ABC_DATA_CLASSIFY_LEN + 8] = (uint8_t)(lab_value.altitude >> 24);  
		StoreABCParam.LogBuf[StoreABCParam.LogCnt*STORE2_ABC_DATA_CLASSIFY_LEN + 9] = (uint8_t)(lab_value.altitude >> 16);
		StoreABCParam.LogBuf[StoreABCParam.LogCnt*STORE2_ABC_DATA_CLASSIFY_LEN + 10] = (uint8_t)(lab_value.altitude >> 8);  
		StoreABCParam.LogBuf[StoreABCParam.LogCnt*STORE2_ABC_DATA_CLASSIFY_LEN + 11] = (uint8_t)(lab_value.altitude >> 0);

		StoreABCParam.LogCnt++;
		
		// RAM缓存满后，存到flash
		if(StoreABCParam.LogCnt >= STORE2_ABC_LOG_MAX)
		{
			Store_ABC_DataSave();
		}		
	}
}

/*******************************************************************************
 * Brief : 跑步数据目录创建
 * Input : @CurrUtc 当前UTC时间
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_ABC_CatalogCreate(void)
{
	if(false == StoreABCParam.InitFlg)
		return Ret_NoInit;
	
	if(eStoreStatusNull != ABCStoreInfo.Status)
		return Ret_DeviceBusy;	

	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	
	/* 
		目录参数初始化，并创建。其他如下信息会在底层函数里，统一设置
		ABCStoreInfo.Catalog.Flash.Info.DataAddr = ABCStoreInfo.DataCurrAddr;
		ABCStoreInfo.Catalog.Flash.Info.Mark = eCatalogMarkUsing;	
	*/
	ABCStoreInfo.Catalog.User.Info.DataClassify = eDataClassifyABC;
	ABCStoreInfo.Catalog.User.Info.UTC = lMidRTC->UTC;
	Store_Algo_CatalogCreate(&ABCStoreInfo);

	// 创建目录后log计数清零
	StoreABCParam.LogCnt = 0;	
	
	return Ret_OK;
}

// 跑步数据存储
uint16_t Store_ABC_DataSave(void)
{
	/* 跑步数据存储 */
	Store_Algo_DataSave(&ABCStoreInfo, StoreABCParam.LogBuf, StoreABCParam.LogCnt*STORE2_ABC_DATA_CLASSIFY_LEN);
	
	/* 清空RAM缓存 */
	StoreABCParam.LogCnt = 0;
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : 跑步数据目录封存
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_ABC_CatalogSeal(void)
{
	if(false == StoreABCParam.InitFlg)
		return Ret_NoInit;	
	
	if(eStoreStatusIng != ABCStoreInfo.Status)
		return Ret_NoInit;	
	
	/* 封存前保存一次RAM的数据 */
	if(StoreABCParam.LogCnt)
	{
		Store_ABC_DataSave();
	}	
	
	/* 目录封存 */
	Store_Algo_CatalogSeal(&ABCStoreInfo, NULL, 0);

	return Ret_OK;
}

/*******************************************************************************
 * Brief : 读取跑步数据，仅用于debug测试
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_ABC_DataRead(void)
{
	CatalogInfo_t		lCatalog;
	uint8_t 		lDataBuf[512];
	uint32_t 		lDataLen = 0,lDataCnt = 0;
	uint32_t	lCatalogSerial;
	
	#if 1	// 整体存储信息打印
	STORE_ABC_RTT_LOG(0, "ABCStoreInfo Read: \n");
	STORE_ABC_RTT_LOG(0, "  .Status %d \n", ABCStoreInfo.Status);
	STORE_ABC_RTT_LOG(0, "  .CatalogBeginAddr 0x%X \n", ABCStoreInfo.CatalogBeginAddr);
	STORE_ABC_RTT_LOG(0, "  .CatalogEndAddr 0x%X \n", ABCStoreInfo.CatalogEndAddr);
	STORE_ABC_RTT_LOG(0, "  .CatalogSerialMax %d \n", ABCStoreInfo.CatalogSerialMax);
	STORE_ABC_RTT_LOG(0, "  .CatalogSerialMaxSave %d \n", ABCStoreInfo.CatalogSerialMaxSave);
	STORE_ABC_RTT_LOG(0, "  .CatalogSerialBegin %d \n", ABCStoreInfo.CatalogSerialBegin);
	STORE_ABC_RTT_LOG(0, "  .CatalogSerialEnd %d \n", ABCStoreInfo.CatalogSerialEnd);
	STORE_ABC_RTT_LOG(0, "  .CatalogSerialCnt %d \n", ABCStoreInfo.CatalogSerialCnt);
	STORE_ABC_RTT_LOG(0, "  .DataBeginAddr 0x%X \n", ABCStoreInfo.DataBeginAddr);
	STORE_ABC_RTT_LOG(0, "  .DataEndAddr 0x%X \n", ABCStoreInfo.DataEndAddr);
	STORE_ABC_RTT_LOG(0, "  .DataCurrAddr 0x%X \n", ABCStoreInfo.DataCurrAddr);
	#endif
	
	#if 1	// 目录打印
	lCatalogSerial = ABCStoreInfo.CatalogSerialBegin;
	for(uint32_t k = 0;k < ABCStoreInfo.CatalogSerialCnt;k++)
	{
		#if 1 /* 目录信息 */
		Store_Algo_CatalogRead(&ABCStoreInfo, lCatalogSerial, &lCatalog);
		STORE_ABC_RTT_LOG(0, "Store_Algo_CatalogRead %d :\n", lCatalogSerial);
		STORE_ABC_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
		STORE_ABC_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
		STORE_ABC_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
		STORE_ABC_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
		STORE_ABC_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
		STORE_ABC_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
		#endif
		
		#if 1 /* 目录附加信息 */
		Store_Algo_CatalogExtRead(&ABCStoreInfo, lCatalogSerial, lDataBuf, lCatalog.User.Info.ExtDataLen);
		STORE_ABC_RTT_LOG(0, "Store_Algo_CatalogExtRead \n");
		for(uint32_t t = 0;t < lCatalog.User.Info.ExtDataLen;t++)
		{
			if((0 == t%32) && (0 != t))
			{
				STORE_ABC_RTT_LOG(0, "\n");
				vTaskDelay(10);
			}
			STORE_ABC_RTT_LOG(0, "%02X ", lDataBuf[t]);
		}STORE_ABC_RTT_LOG(0, "\n");
		#endif
		
		#if 1	/* 打印数据 */
		STORE_ABC_RTT_LOG(0, "Store_Algo_DataRead \n");
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
			Store_Algo_DataRead(&ABCStoreInfo, &lCatalog, lDataCnt-lDataLen, lDataBuf, lDataLen);
			for(uint32_t t = 0;t < lDataLen;t++)
			{
				if((0 == t%28) && (0 != t))
				{
					STORE_ABC_RTT_LOG(0, "\n");
					vTaskDelay(10);
				}
				STORE_ABC_RTT_LOG(0, "%02X ", lDataBuf[t]);
			}STORE_ABC_RTT_LOG(0, "\n");
		}while(lDataCnt != lCatalog.Flash.Info.DataLen);
		#endif
		
		// 下一目录
		lDataCnt = 0;
		lDataLen = 0;
		lCatalogSerial = Store_Algo_NextCatalogGet(&ABCStoreInfo, lCatalogSerial);
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
uint16_t Store_ABC_CatalogAllUpload(void)
{
	Store_Algo_CatalogAllUpload(&ABCStoreInfo);
	
	return Ret_OK;	
}

/*********************************************************************
 * Brief : 获取最新气压数据，用于UI显示。
			根据UI显示：24小时数据，取点144个（10分钟一次）
			每隔5个取1个点，所以取24 * 60 / 2 = 720
 * Input : @Buf 存储数据的buf
		   @Len 想要获取的数据长度，暂未使用此参数
 * Output: @NULL 
 * Return: 处理结果
 * Call  : 
 ************/
#define PRESSURE_UI_DATA_LEN		(144)	// 用于UI显示的数据个数
#define PRESSURE_UI_DATA_INTERVAL	(5)		// 数据间隔（每多少个数据取一个用于UI显示）
void Store_ABC_UIPressureGet(int32_t* Buf, uint32_t Len3)
{
	uint32_t lIntervalCnt = 0;
	uint32_t tReadLen = 0;	// 已读取的数据长度
	uint32_t tCatalog;
	CatalogInfo_t fCatalogInfo;
	uint8_t* lDataBuf;
	uint32_t lDataLen;	
	uint32_t lDataOffset;
	
	memset(Buf, 0x00, PRESSURE_UI_DATA_LEN*sizeof(Buf[0]));	// 初始化Buf默认值
	
	lDataBuf = pvPortMalloc(STORE_MAX_MALLOC_LEN);	

	/* 读取未存入flash的数据 */ 
	if(eStoreStatusIng == ABCStoreInfo.Status)
	{
		for(uint32_t i = StoreABCParam.LogCnt;i > 0;i--)
		{
			if(++lIntervalCnt == PRESSURE_UI_DATA_INTERVAL)
			{
				lIntervalCnt = 0;
				Buf[tReadLen++] = (int32_t)((StoreABCParam.LogBuf[STORE2_ABC_DATA_CLASSIFY_LEN*(i-1)+0] << 24) |
											(StoreABCParam.LogBuf[STORE2_ABC_DATA_CLASSIFY_LEN*(i-1)+1] << 16) |
											(StoreABCParam.LogBuf[STORE2_ABC_DATA_CLASSIFY_LEN*(i-1)+2] << 8 ) |
											(StoreABCParam.LogBuf[STORE2_ABC_DATA_CLASSIFY_LEN*(i-1)+3] << 0 ));	// 最新值在先
				if(tReadLen >= PRESSURE_UI_DATA_LEN)
					goto Done;
			}
		}
	}
	
	/* 读取已存入flash的数据 */ 
	if(eStoreStatusIng == ABCStoreInfo.Status)
	{
		tCatalog = Store_Algo_NextCatalogGet(&ABCStoreInfo, ABCStoreInfo.CatalogSerialEnd);
	}
	else
	{
		tCatalog = ABCStoreInfo.CatalogSerialBegin;
	}
	for(uint32_t i = 0;i < ABCStoreInfo.CatalogSerialCnt;i++)
	{
		/* 读取目录信息 */ 
		Store_Algo_CatalogRead(&ABCStoreInfo, tCatalog, &fCatalogInfo);
		
		/* 若目录指向数据区域长度太大，得多次读取 */
		lDataOffset = fCatalogInfo.Flash.Info.DataLen;	// 最新数据在前，所以从后面开始读
		for(uint32_t k = 0;k < 
			((fCatalogInfo.Flash.Info.DataLen + STORE2_ABC_LOG_MAX_LEN - 1) / STORE2_ABC_LOG_MAX_LEN)	// 进位除法
			;k++)
		{
			if(lDataOffset <= STORE2_ABC_LOG_MAX_LEN)
			/* 最后一次 */
			{
				lDataLen = lDataOffset;
			}
			else
			{
				lDataLen = STORE2_ABC_LOG_MAX_LEN;
			}
			lDataOffset -= lDataLen;
			Store_Algo_DataRead(&ABCStoreInfo, &fCatalogInfo, lDataOffset, lDataBuf, lDataLen);			
			#if 0	// debug
			STORE_ABC_RTT_LOG(0, "lDataOffset lDataLen %d %d \n", lDataOffset, lDataLen);
			for(uint32_t i = 0;i < lDataLen;i++)
			{
				if((0 == i%32) && (0 != i))
				{
					STORE_ABC_RTT_LOG(0, "\n");
				}
				STORE_ABC_RTT_LOG(0, "%02X ", lDataBuf[i]);
			}STORE_ABC_RTT_LOG(0, "\n");
			#endif			
			for(uint32_t j = lDataLen / STORE2_ABC_DATA_CLASSIFY_LEN;j > 0;j--)
			{
				if(++lIntervalCnt == PRESSURE_UI_DATA_INTERVAL)
				{
					lIntervalCnt = 0;
					Buf[tReadLen++] = (int32_t)((lDataBuf[STORE2_ABC_DATA_CLASSIFY_LEN*(j-1)+0] << 24) |
												(lDataBuf[STORE2_ABC_DATA_CLASSIFY_LEN*(j-1)+1] << 16) |
												(lDataBuf[STORE2_ABC_DATA_CLASSIFY_LEN*(j-1)+2] << 8 ) |
												(lDataBuf[STORE2_ABC_DATA_CLASSIFY_LEN*(j-1)+3] << 0 ));	// 最新值在先
					if(tReadLen >= PRESSURE_UI_DATA_LEN)
						goto Done;
				}
			}
		}			

		// 上一目录
		tCatalog = Store_Algo_LastCatalogGet(&ABCStoreInfo, ABCStoreInfo.CatalogSerialEnd);
	}
	
	vPortFree(lDataBuf);
	
	#if 1 // debug 打印获取到的数据
	STORE_ABC_RTT_LOG(0, "Store_ABC_UIPressureGet: \n");
	for(uint32_t i = 0;i < PRESSURE_UI_DATA_LEN;i++)
	{
		if((0 == i%10) && (0 != i))
		{
			STORE_ABC_RTT_LOG(0, "\n");
			vTaskDelay(1);
		}
		STORE_ABC_RTT_LOG(0, "%08X ", Buf[i]);
	}STORE_ABC_RTT_LOG(0, "\n");
	#endif		
	
Done:
	vPortFree(lDataBuf);
	
	#if 1 // debug 打印获取到的数据
	STORE_ABC_RTT_LOG(0, "Store_ABC_UIPressureGet: \n");
	for(uint32_t i = 0;i < PRESSURE_UI_DATA_LEN;i++)
	{
		if((0 == i%10) && (0 != i))
		{
			STORE_ABC_RTT_LOG(0, "\n");
			vTaskDelay(1);
		}
		STORE_ABC_RTT_LOG(0, "%08X ", Buf[i]);
	}STORE_ABC_RTT_LOG(0, "\n");
	#endif		
}

/*********************************************************************
 * Brief : 获取最新海拔数据，用于UI显示。
			根据UI显示：4小时数据，取点135个（美观需要）（2分钟一次）
 * Input : @Buf 存储数据的buf
	       @Len 想要获取的数据长度，暂未使用此参数
 * Output: @NULL 
 * Return: 处理结果
 * Call  : 
 ************/
#define ALTITUDE_UI_DATA_LEN	(135)	// 用于UI显示的数据个数
//#define ALTITUDE_EACH_READ_LEN	()		// 每次读取数据长度，必须小于 STORE_MAX_MALLOC_LEN 且是 STORE2_ABC_DATA_CLASSIFY_LEN 的整数倍
void Store_ABC_UIAltitudeGet(int32_t* Buf, uint32_t Len)
{
	uint32_t tReadLen = 0;	// 已读取的数据长度
	uint32_t tCatalog;
	CatalogInfo_t fCatalogInfo;
	uint8_t* lDataBuf;
	uint32_t lDataLen;
	uint32_t lDataOffset;
	
	memset(Buf, 0x00, ALTITUDE_UI_DATA_LEN*sizeof(Buf[0]));	// 初始化Buf默认值
	
	lDataBuf = pvPortMalloc(STORE_MAX_MALLOC_LEN);
	
	/* 读取未存入flash的数据 */ 
	if(eStoreStatusIng == ABCStoreInfo.Status)
	{
		for(uint32_t i = StoreABCParam.LogCnt;i > 0;i--)
		{
			Buf[tReadLen++] = (int32_t)((StoreABCParam.LogBuf[STORE2_ABC_DATA_CLASSIFY_LEN*(i-1)+8] << 24) |
										(StoreABCParam.LogBuf[STORE2_ABC_DATA_CLASSIFY_LEN*(i-1)+9] << 16) |
										(StoreABCParam.LogBuf[STORE2_ABC_DATA_CLASSIFY_LEN*(i-1)+10] << 8 ) |
										(StoreABCParam.LogBuf[STORE2_ABC_DATA_CLASSIFY_LEN*(i-1)+11] << 0 ));	// 最新值在先				
			if(tReadLen >= ALTITUDE_UI_DATA_LEN)
				goto Done;			
		}
	}
	
	/* 读取已存入flash的数据 */ 
	if(eStoreStatusIng == ABCStoreInfo.Status)
	{
		tCatalog = Store_Algo_NextCatalogGet(&ABCStoreInfo, ABCStoreInfo.CatalogSerialEnd);
	}
	else
	{
		tCatalog = ABCStoreInfo.CatalogSerialBegin;
	}
	for(uint32_t i = 0;i < ABCStoreInfo.CatalogSerialCnt;i++)
	{
		/* 读取目录信息 */ 
		Store_Algo_CatalogRead(&ABCStoreInfo, tCatalog, &fCatalogInfo);
		
		/* 若目录指向数据区域长度太大，得多次读取 */
		lDataOffset = fCatalogInfo.Flash.Info.DataLen;	// 最新数据在前，所以从后面开始读
		for(uint32_t k = 0;k < 
			((fCatalogInfo.Flash.Info.DataLen + STORE2_ABC_LOG_MAX_LEN - 1) / STORE2_ABC_LOG_MAX_LEN)	// 进位除法
			;k++)
		{
			if(lDataOffset <= STORE2_ABC_LOG_MAX_LEN)
			/* 最后一次 */
			{
				lDataLen = lDataOffset;
			}
			else
			{
				lDataLen = STORE2_ABC_LOG_MAX_LEN;
			}
			lDataOffset -= lDataLen;
			Store_Algo_DataRead(&ABCStoreInfo, &fCatalogInfo, lDataOffset, lDataBuf, lDataLen);	
			#if 0	// debug
			STORE_ABC_RTT_LOG(0, "lDataOffset lDataLen %d %d \n", lDataOffset, lDataLen);
			for(uint32_t i = 0;i < lDataLen;i++)
			{
				if((0 == i%32) && (0 != i))
				{
					STORE_ABC_RTT_LOG(0, "\n");
				}
				STORE_ABC_RTT_LOG(0, "%02X ", lDataBuf[i]);
			}STORE_ABC_RTT_LOG(0, "\n");
			#endif
			for(uint32_t j = lDataLen / STORE2_ABC_DATA_CLASSIFY_LEN;j > 0;j--)
			{
				Buf[tReadLen++] = (int32_t)((lDataBuf[STORE2_ABC_DATA_CLASSIFY_LEN*(j-1)+8] << 24) |
											(lDataBuf[STORE2_ABC_DATA_CLASSIFY_LEN*(j-1)+9] << 16) |
											(lDataBuf[STORE2_ABC_DATA_CLASSIFY_LEN*(j-1)+10] << 8 ) |
											(lDataBuf[STORE2_ABC_DATA_CLASSIFY_LEN*(j-1)+11] << 0 ));	// 最新值在先		
				if(tReadLen >= ALTITUDE_UI_DATA_LEN)
					goto Done;		
			}
		}
		
		// 上一目录
		tCatalog = Store_Algo_LastCatalogGet(&ABCStoreInfo, ABCStoreInfo.CatalogSerialEnd);
	}
	
	vPortFree(lDataBuf);
	
	#if 1 // debug 打印获取到的数据
	STORE_ABC_RTT_LOG(0, "Store_ABC_UIAltitudeGet: \n");
	for(uint32_t i = 0;i < ALTITUDE_UI_DATA_LEN;i++)
	{
		if((0 == i%10) && (0 != i))
		{
			STORE_ABC_RTT_LOG(0, "\n");
			vTaskDelay(1);
		}
		STORE_ABC_RTT_LOG(0, "%08X ", Buf[i]);
	}STORE_ABC_RTT_LOG(0, "\n");
	#endif
	
Done:
	vPortFree(lDataBuf);
	
	#if 1 // debug 打印获取到的数据
	STORE_ABC_RTT_LOG(0, "Store_ABC_UIAltitudeGet: \n");
	for(uint32_t i = 0;i < ALTITUDE_UI_DATA_LEN;i++)
	{
		if((0 == i%10) && (0 != i))
		{
			STORE_ABC_RTT_LOG(0, "\n");
			vTaskDelay(1);
		}
		STORE_ABC_RTT_LOG(0, "%08X ", Buf[i]);
	}STORE_ABC_RTT_LOG(0, "\n");
	#endif	
}

// 模拟产生假数据，用于测试
#define ABC_DATE_SIMULATA_LEN	(189)
void Store_ABC_DateSimulata(void)
{
	STORE_ABC_RTT_LOG(0, "Store_ABC_DateSimulata \n");
	
	#if 0
	ab_value_t lab_value;
	
	Store_ABC_ClearInit();
	
	for(uint32_t t = 0;t < 2;t++)
	{
		Store_ABC_CatalogCreate();
		for(uint32_t i = 0; i < ABC_DATE_SIMULATA_LEN;i++)
		{
			memset(&lab_value, i, sizeof(ab_value_t));
			Store_ABC_algorithm(i, lab_value);
		}
		Store_ABC_CatalogSeal();	
	}

	#endif
	
	#if 0
    int32_t AltitudeData[135] = {80 ,76  ,98  ,98  ,57  ,65  ,69  ,71  ,71  ,71  ,63  ,62  ,63  ,59  ,62  ,64  ,64  ,63  ,62  ,63  ,63  ,63  ,62  ,60  ,62  ,58  ,60  ,62  ,59  ,60  ,62  ,59  ,62  ,62  ,61  ,61  ,
        58  ,69  ,59  ,64  ,81  ,61  ,63  ,85  ,64  ,57  ,59  ,60  ,59  ,60  ,59  ,60  ,56  ,56  ,59  ,58  ,56  ,56  ,56  ,57  ,57  ,58  ,56  ,59  ,55  ,57  ,55  ,57  ,57  ,57  ,55  ,
        55  ,56  ,55  ,55  ,55  ,53  ,56  ,54  ,56  ,55  ,57  ,56  ,84  ,58  ,60  ,53  ,55  ,61  ,58  ,63  ,63  ,58  ,72  ,58  ,57  ,63  ,57  ,68  ,56  ,56  ,63  ,57  ,60  ,62  ,60  ,66  ,59  ,57  ,
        53  ,61  ,52  ,73  ,57  ,58  ,56  ,57  ,55  ,56  ,57  ,58  ,56  ,57  ,55  ,56,58  ,56  ,57  ,55  ,56,58  ,56  ,57  ,55  ,56};
		
    int32_t AirpressureData[144] = {   99624   ,99627   ,99629   ,99632   ,99633   ,99634   ,99634   ,99633   ,99632   ,99631   ,99631   ,99630   ,99630   ,99630   ,99630   ,99631   ,99632   ,99633   ,99634   ,99634   ,
        99634   ,99633   ,99634   ,99635   ,99637   ,99639   ,99641   ,99643   ,99644   ,99645   ,99646   ,99647   ,99647   ,99648   ,99648   ,99648   ,99649   ,99650   ,99652   ,99655   ,99656   ,99657   ,
        99658   ,99659   ,99661   ,99662   ,99663   ,99664   ,99665   ,99666   ,99668   ,99669   ,99671   ,99673   ,99675   ,99677   ,99679   ,99680   ,99681   ,99682   ,99682   ,99683   ,99683   ,99682   ,
        99682   ,99681   ,99680   ,99680   ,99680   ,99680   ,99679   ,99679   ,99678   ,99678   ,99679   ,99680   ,99681   ,99681   ,99681   ,99681   ,99681   ,99681   ,99681   ,99682   ,99684   ,99687   ,
        99688   ,99689   ,99690   ,99689   ,99688   ,99686   ,99685   ,99685   ,99685   ,99686   ,99686   ,99686   ,99685   ,99684   ,99684   ,99684   ,99685   ,99685   ,99686   ,99686   ,99686   ,99686   ,
        99686   ,99686   ,99686   ,99685   ,99685   ,99684   ,99684   ,99682   ,99681   ,99680   ,99679   ,99680   ,99681   ,99681   ,99681   ,99680   ,99681   ,99681   ,99680   ,99679   ,99676   ,
        99673   ,99672   ,99671   ,99670   ,99669   ,99668   ,99667   ,99667   ,99667   ,99667   ,99668   ,99669   ,99669   ,99669   ,99669   ,
        };
	
	ab_value_t lab_value;
	uint32 lUTC = 1542078756;	// 1542078756 北京时间 2018/11/13 11:12:36
	
	Store_ABC_ClearInit();
	
	Store_ABC_CatalogCreate();
	for(uint32_t i = 0; i < 135;i++)
	{
		lab_value.altitude = AltitudeData[i];
		lab_value.pressure = AirpressureData[i];
		Store_ABC_algorithm(lUTC, lab_value);
		lUTC += 120;	// 2min
	}
	Store_ABC_CatalogSeal();		
		
	#endif
}


















