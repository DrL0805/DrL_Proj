#include "store_step.h"
#include "store_algo.h"
#include "scene_step.h"
#include "mid_rtc.h"

StoreInfo_t			StepStoreInfo;
StoreStepParam_t		StoreStepParam;

/*********************************************************************
 * Brief : �������UI��ʾ�ļƲ����ݣ�
 * Input : @NULL
 * Output: @NULL
 * Return: 
 * Call  : ��ʼ��ʱ & ÿ���賿����
 ************/
static void Store_Step_UIDataInit(void)
{
	for(uint32_t i = 0;i < 24;i++)
		StoreStepParam.UI.LogBuf[i] = 0;
	
	StoreStepParam.CumsumStep = 0;
}
 
static void Store_Step_ParamInit(void)
{
	StepStoreInfo.Status = eStoreStatusNull;			// �洢״̬				
	
	StepStoreInfo.CatalogBeginAddr = STORE2_STEP_CATALOG_BEGIN_ADDR;	// �̶�ֵ��Ŀ¼�洢��ʼ��ʼ
	StepStoreInfo.CatalogEndAddr = STORE2_STEP_CATALOG_END_ADDR;		// �̶�ֵ��Ŀ¼�洢������ַ��������

	StepStoreInfo.CatalogSerialMax = STORE2_STEP_MAX_ALLOT_CATALOG;		// �̶�ֵ�����Ŀ¼�����ɷ���Ĵ洢�ռ����
	StepStoreInfo.CatalogSerialMaxSave = STORE2_STEP_MAX_SAVE_CATALOG;	// �̶�ֵ������������Ŀ¼
	StepStoreInfo.CatalogSerialBegin = StepStoreInfo.CatalogSerialMax - 1;	// ��Ч�洢Ŀ¼��ʼ��ţ���Ŀ¼Cnt����Ŀ¼MaxSave����ǰĿ¼Begin��Ǳ����ǣ�Ȼ��+1
	StepStoreInfo.CatalogSerialEnd = StepStoreInfo.CatalogSerialMax - 1;		// ��Ч�洢Ŀ¼������ţ�ÿ�δ���Ŀ¼ʱ+1
	StepStoreInfo.CatalogSerialCnt = 0;		// �Ѵ洢Ŀ¼������ÿ�η��Ŀ¼ʱ+1����󲻳���MaxSave

	StepStoreInfo.DataBeginAddr = STORE2_STEP_DATA_BEGIN_ADDR;	// �̶�ֵ�����ݴ洢��ʼ��ʼ
	StepStoreInfo.DataEndAddr = STORE2_STEP_DATA_END_ADDR;	// �̶�ֵ�����ݴ洢������ַ��������	
	StepStoreInfo.DataCurrAddr = StepStoreInfo.DataBeginAddr;	// ��ǰ���ݴ洢��ַ
	
	#if 0	// �����ʼ��һЩ����ֵ����FLASH�߽�������в��� 
	StepStoreInfo.DataCurrAddr = StepStoreInfo.DataEndAddr - 100;	// ���ڲ���FLASHѭ����д
	StepStoreInfo.CatalogSerialBegin = StepStoreInfo.CatalogSerialMax - 2;
	StepStoreInfo.CatalogSerialEnd = StepStoreInfo.CatalogSerialMax - 2;		
	#endif
	
	/* �������UI��ʾ������ */
	Store_Step_UIDataInit();
}

// �������㷽ʽ��ʼ��
void Store_Step_ClearInit(void)
{
	/* �洢������ʼ�� */
	Store_Step_ParamInit();
	
	/* �������flash���򣬷�ֹ֮ǰ�Ĵ������ݲ���Ӱ�� */
	Mid_NandFlash_Erase(StepStoreInfo.CatalogBeginAddr, StepStoreInfo.DataEndAddr);
	
	StoreStepParam.InitFlg = true;
}

// ���ݻָ���ʽ��ʼ��
void Store_Step_RecoverInit(void)
{
	/* �洢������ʼ�� */
	Store_Step_ParamInit();
	
	/* ���ݻָ� */
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
 * Brief : �ܲ��洢�㷨����洢ʱ����һ��
 * Input : @CurrUtc ��ǰUTCʱ�� 
		   @Step 	��洢��ֵ
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Store_Step_algorithm(void)
{
	if(false == StoreStepParam.InitFlg)
		return;	
	
	uint16_t lStep5minCnt = Scene_Step_5minCntRead();
	
	/* ����ǰû����Ŀ¼���򴴽� */
	if(eStoreStatusNull == StepStoreInfo.Status)
	{
		Store_Step_CatalogCreate();
	}
	
	StoreStepParam.LogBuf[StoreStepParam.LogCnt*STORE2_STEP_DATA_CLASSIFY_LEN + 0] = lStep5minCnt >> 8;
	StoreStepParam.LogBuf[StoreStepParam.LogCnt*STORE2_STEP_DATA_CLASSIFY_LEN + 1] = lStep5minCnt;	
	StoreStepParam.LogCnt++;
	
	// RAM�������󣬴浽flash
	if(StoreStepParam.LogCnt >= STORE2_STEP_LOG_MAX)
	{
		Store_Step_CatalogSeal();
	}
}


/*******************************************************************************
 * Brief : �ܲ�����Ŀ¼����
 * Input : @CurrUtc ��ǰUTCʱ��
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
		Ŀ¼������ʼ����������������������Ϣ���ڵײ㺯���ͳһ����
		StepStoreInfo.Catalog.Flash.Info.DataAddr = StepStoreInfo.DataCurrAddr;
		StepStoreInfo.Catalog.Flash.Info.Mark = eCatalogMarkUsing;	
	*/
	StepStoreInfo.Catalog.User.Info.DataClassify = eDataClassifyStep;
	StepStoreInfo.Catalog.User.Info.UTC = lMidRTC->UTC;
	Store_Algo_CatalogCreate(&StepStoreInfo);

	// ����Ŀ¼��log��������
	StoreStepParam.LogCnt = 0;	
	
	return Ret_OK;
}

// �ܲ����ݴ洢
uint16_t Store_Step_DataSave(void)
{
	/* �ܲ����ݴ洢 */
	Store_Algo_DataSave(&StepStoreInfo, StoreStepParam.LogBuf, StoreStepParam.LogCnt*STORE2_STEP_DATA_CLASSIFY_LEN);
	
	/* ���RAM���� */
	StoreStepParam.LogCnt = 0;
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : �ܲ�����Ŀ¼���
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
	
	/* ���ǰ����һ��RAM������ */
	if(StoreStepParam.LogCnt)
	{
		Store_Step_DataSave();
	}	
	
	/* Ŀ¼��� */
	Store_Algo_CatalogSeal(&StepStoreInfo, NULL, 0);

	return Ret_OK;
}

/*******************************************************************************
 * Brief : ��ȡ�ܲ����ݣ�������debug����
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
	
	#if 1	// ����洢��Ϣ��ӡ
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
	
	#if 1	// Ŀ¼��ӡ
	lCatalogSerial = StepStoreInfo.CatalogSerialBegin;
	for(uint32_t k = 0;k < StepStoreInfo.CatalogSerialCnt;k++)
	{
		#if 1 /* Ŀ¼��Ϣ */
		Store_Algo_CatalogRead(&StepStoreInfo, lCatalogSerial, &lCatalog);
		STORE_STEP_RTT_LOG(0, "Store_Algo_CatalogRead %d :\n", lCatalogSerial);
		STORE_STEP_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
		STORE_STEP_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
		STORE_STEP_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
		STORE_STEP_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
		STORE_STEP_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
		STORE_STEP_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
		#endif
		
		#if 1 /* Ŀ¼������Ϣ */
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
		
		#if 1	/* ��ӡ���� */
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
		
		// ��һĿ¼
		lDataCnt = 0;
		lDataLen = 0;
		lCatalogSerial = Store_Algo_NextCatalogGet(&StepStoreInfo, lCatalogSerial);
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
uint16_t Store_Step_CatalogAllUpload(void)
{
	Store_Algo_CatalogAllUpload(&StepStoreInfo);
	
	return Ret_OK;	
}

/*******************************************************************************
 * Brief : ����洢�洢��RAM�е�����
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
 * Brief : ��������UI��ʾ�ļƲ�����
 * Input : @tRTCTime ��ǰRTCʱ��
		   @TotalStep �����ܲ���
 * Output: @NULL
 * Return: @NULL
 * Call  : ÿСʱ����һ��
 ***************/
void Store_Step_UIDataUpdate(void)
{
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
	
	if(0 == lMidRTC->RTC.hour)	
	/* ÿ��������UI�Ʋ����� */ 
	{
		Store_Step_UIDataInit();
	}
	else
	{
		/* ��(TotalStep < tStep)˵�����ݳ����Ʋ���Ϊ0*/
		if(lpSceneStepParam->totalStep < StoreStepParam.CumsumStep)
		{
			StoreStepParam.UI.LogBuf[(lMidRTC->RTC.hour-1)] = 0;
			drERROR_CHECK("Store_Step_UIDataUpdate", Ret_InvalidParam); 
		}
		else
		{
			StoreStepParam.UI.LogBuf[(lMidRTC->RTC.hour-1)] = lpSceneStepParam->totalStep - StoreStepParam.CumsumStep;
		}
		
		StoreStepParam.CumsumStep = lpSceneStepParam->totalStep;	// �����ۼӼƲ�ֵ
	}
}


/*******************************************************************************
 * Brief : ��ȡ����UI��ʾ�����ݣ�����24Сʱ��
 * Input : @buf ָ�� 
 * Output: @Len ��δʹ�ã�ǿ�ƻ�ȡ����24Сʱ����
 * Return: @NULL
 * Call  : 
 ***************/
void Store_Step_UIDataGet(uint16_t* Buf, uint32_t Len)
{
	SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	
	memcpy(Buf, StoreStepParam.UI.LogBuf, 24*sizeof(Buf[0]));
	
	// ��ǰСʱ�ڵļƲ�ֵ
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

// ģ����������ݣ����ڲ���
#define STEP_DATE_SIMULATA_LEN	(189)
void Store_Step_DateSimulata(void)
{
	STORE_STEP_RTT_LOG(0, "Store_Step_DateSimulata \n");
	
	#if 0	// ����β���ݶ�д����
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
	
	#if 1 // ������Ⱦ���ݣ�Ȼ��ָ����ݣ�Ȼ���ڶ�д����
	
		#if 0	// ��Ⱦ���ݣ�д�����ݣ����ǲ�����
		Store_Step_ClearInit();
		
		// д����������
		for(uint32_t lTmp = 0;lTmp < 2;lTmp++)
		{
			Store_Step_CatalogCreate();
			for(uint32_t i = 0; i < STEP_DATE_SIMULATA_LEN + lTmp;i++)
			{
				Store_Step_algorithm();
			}
			Store_Step_CatalogSeal();	
		}		
		
		// д�����ݣ��������Ŀ¼
		Store_Step_CatalogCreate();
		for(uint32_t i = 0; i < STEP_DATE_SIMULATA_LEN;i++)
		{
			Store_Step_algorithm();
		}
		#endif
	
	
		#if 0	// ���±����д���������ݣ��ٶ�ȡ����
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


