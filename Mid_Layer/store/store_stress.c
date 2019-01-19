#include "app_variable.h"
#include "store_stress.h"
#include "store_algo.h"
#include "mid_rtc.h"
#include "scene_stress.h"

StoreInfo_t			StressStoreInfo;
StoreStressParam_t		StoreStressParam;

static void Store_Stress_ParamInit(void)
{
	StressStoreInfo.Status = eStoreStatusNull;			// �洢״̬				
	
	StressStoreInfo.CatalogBeginAddr = STORE2_STRESS_CATALOG_BEGIN_ADDR;	// �̶�ֵ��Ŀ¼�洢��ʼ��ʼ
	StressStoreInfo.CatalogEndAddr = STORE2_STRESS_CATALOG_END_ADDR;		// �̶�ֵ��Ŀ¼�洢������ַ��������

	StressStoreInfo.CatalogSerialMax = STORE2_STRESS_MAX_ALLOT_CATALOG;		// �̶�ֵ�����Ŀ¼�����ɷ���Ĵ洢�ռ����
	StressStoreInfo.CatalogSerialMaxSave = STORE2_STRESS_MAX_SAVE_CATALOG;	// �̶�ֵ������������Ŀ¼
	StressStoreInfo.CatalogSerialBegin = StressStoreInfo.CatalogSerialMax - 1;	// ��Ч�洢Ŀ¼��ʼ��ţ���Ŀ¼Cnt����Ŀ¼MaxSave����ǰĿ¼Begin��Ǳ����ǣ�Ȼ��+1
	StressStoreInfo.CatalogSerialEnd = StressStoreInfo.CatalogSerialMax - 1;		// ��Ч�洢Ŀ¼������ţ�ÿ�δ���Ŀ¼ʱ+1
	StressStoreInfo.CatalogSerialCnt = 0;		// �Ѵ洢Ŀ¼������ÿ�η��Ŀ¼ʱ+1����󲻳���MaxSave

	StressStoreInfo.DataBeginAddr = STORE2_STRESS_DATA_BEGIN_ADDR;	// �̶�ֵ�����ݴ洢��ʼ��ʼ
	StressStoreInfo.DataEndAddr = STORE2_STRESS_DATA_END_ADDR;	// �̶�ֵ�����ݴ洢������ַ��������	
	StressStoreInfo.DataCurrAddr = StressStoreInfo.DataBeginAddr;	// ��ǰ���ݴ洢��ַ
}

// �������㷽ʽ��ʼ��
void Store_Stress_ClearInit(void)
{
	/* �洢������ʼ�� */
	Store_Stress_ParamInit();
	
	/* �������flash���򣬷�ֹ֮ǰ�Ĵ������ݲ���Ӱ�� */
	Mid_NandFlash_Erase(StressStoreInfo.CatalogBeginAddr, StressStoreInfo.DataEndAddr);
	
	StoreStressParam.InitFlg = true;
}

// ���ݻָ���ʽ��ʼ��
void Store_Stress_RecoverInit(void)
{
	/* �洢������ʼ�� */
	Store_Stress_ParamInit();
	
	/* ���ݻָ� */
	Store_Algo_CatalogRecover(&StressStoreInfo);
	
	StoreStressParam.InitFlg = true;
}

StoreInfo_t* Store_Stress_StoreInfoGet(void)
{
	return &StressStoreInfo;
}

StoreStressParam_t* Store_Stress_ParamPGet(void)
{
	return &StoreStressParam;
}

/*******************************************************************************
 * Brief : �ܲ��洢�㷨����洢ʱ����һ��
 * Input : @CurrUtc ��ǰUTCʱ�� 
		   @Stress 	��洢��ֵ
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Store_Stress_algorithm(void)
{
	if(false == StoreStressParam.InitFlg)
		return;	
	
	Scene_Stress_Param_t* lpSceneStressParam = Scene_Stress_ParamPGet();
	
	/* ����ǰû����Ŀ¼���򴴽� */
	if(eStoreStatusNull == StressStoreInfo.Status)
	{
		Store_Stress_CatalogCreate();
	}

	StoreStressParam.LogBuf[StoreStressParam.LogCnt*STORE2_STRESS_DATA_CLASSIFY_LEN + 0] = lpSceneStressParam->CurrStress.score;
	StoreStressParam.LogBuf[StoreStressParam.LogCnt*STORE2_STRESS_DATA_CLASSIFY_LEN + 1] = lpSceneStressParam->CurrStress.score;
	
	StoreStressParam.LogCnt++;	
	
	// RAM�������󣬴浽flash
	if(StoreStressParam.LogCnt >= STORE2_STRESS_LOG_MAX)
	{
		Store_Stress_DataSave();
	}	
}

/*******************************************************************************
 * Brief : �ܲ�����Ŀ¼����
 * Input : @CurrUtc ��ǰUTCʱ��
 * Output: @NULL
 * Return: @NULL
 * Call  :  
 ***************/
uint16_t Store_Stress_CatalogCreate(void)
{
	if(false == StoreStressParam.InitFlg)
		return Ret_NoInit;
	
	if(eStoreStatusNull != StressStoreInfo.Status)
		return Ret_DeviceBusy;	

	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	
	/* 
		Ŀ¼������ʼ����������������������Ϣ���ڵײ㺯���ͳһ����
		StressStoreInfo.Catalog.Flash.Info.DataAddr = StressStoreInfo.DataCurrAddr;
		StressStoreInfo.Catalog.Flash.Info.Mark = eCatalogMarkUsing;	
	*/
	StressStoreInfo.Catalog.User.Info.DataClassify = eDataClassifyStress;
	StressStoreInfo.Catalog.User.Info.UTC = lMidRTC->UTC;
	Store_Algo_CatalogCreate(&StressStoreInfo);

	// ����Ŀ¼��log��������
	StoreStressParam.LogCnt = 0;	
	
	return Ret_OK;
}

// �ܲ����ݴ洢
uint16_t Store_Stress_DataSave(void)
{
	/* �ܲ����ݴ洢 */
	Store_Algo_DataSave(&StressStoreInfo, StoreStressParam.LogBuf, StoreStressParam.LogCnt*STORE2_STRESS_DATA_CLASSIFY_LEN);
	
	/* ���RAM���� */
	StoreStressParam.LogCnt = 0;
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : �ܲ�����Ŀ¼���
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Stress_CatalogSeal(void)
{
	if(false == StoreStressParam.InitFlg)
		return Ret_NoInit;	
	
	if(eStoreStatusIng != StressStoreInfo.Status)
		return Ret_NoInit;	
	
	/* ���ǰ����һ��RAM������ */
	if(StoreStressParam.LogCnt)
	{
		Store_Stress_DataSave();
	}	
	
	/* Ŀ¼��� */
	Store_Algo_CatalogSeal(&StressStoreInfo, NULL, 0);

	return Ret_OK;
}

/*******************************************************************************
 * Brief : ��ȡ�ܲ����ݣ�������debug����
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Stress_DataRead(void)
{
	CatalogInfo_t		lCatalog;
	uint8_t 		lDataBuf[512];
	uint32_t 		lDataLen = 0,lDataCnt = 0;
	uint32_t	lCatalogSerial;
	
	#if 1	// ����洢��Ϣ��ӡ
	STORE_STRESS_RTT_LOG(0, "StressStoreInfo Read: \n");
	STORE_STRESS_RTT_LOG(0, "  .Status %d \n", StressStoreInfo.Status);
	STORE_STRESS_RTT_LOG(0, "  .CatalogBeginAddr 0x%X \n", StressStoreInfo.CatalogBeginAddr);
	STORE_STRESS_RTT_LOG(0, "  .CatalogEndAddr 0x%X \n", StressStoreInfo.CatalogEndAddr);
	STORE_STRESS_RTT_LOG(0, "  .CatalogSerialMax %d \n", StressStoreInfo.CatalogSerialMax);
	STORE_STRESS_RTT_LOG(0, "  .CatalogSerialMaxSave %d \n", StressStoreInfo.CatalogSerialMaxSave);
	STORE_STRESS_RTT_LOG(0, "  .CatalogSerialBegin %d \n", StressStoreInfo.CatalogSerialBegin);
	STORE_STRESS_RTT_LOG(0, "  .CatalogSerialEnd %d \n", StressStoreInfo.CatalogSerialEnd);
	STORE_STRESS_RTT_LOG(0, "  .CatalogSerialCnt %d \n", StressStoreInfo.CatalogSerialCnt);
	STORE_STRESS_RTT_LOG(0, "  .DataBeginAddr 0x%X \n", StressStoreInfo.DataBeginAddr);
	STORE_STRESS_RTT_LOG(0, "  .DataEndAddr 0x%X \n", StressStoreInfo.DataEndAddr);
	STORE_STRESS_RTT_LOG(0, "  .DataCurrAddr 0x%X \n", StressStoreInfo.DataCurrAddr);
	#endif
	
	#if 1	// Ŀ¼��ӡ
	lCatalogSerial = StressStoreInfo.CatalogSerialBegin;
	for(uint32_t k = 0;k < StressStoreInfo.CatalogSerialCnt;k++)
	{
		#if 1 /* Ŀ¼��Ϣ */
		Store_Algo_CatalogRead(&StressStoreInfo, lCatalogSerial, &lCatalog);
		STORE_STRESS_RTT_LOG(0, "Store_Algo_CatalogRead %d :\n", lCatalogSerial);
		STORE_STRESS_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
		STORE_STRESS_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
		STORE_STRESS_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
		STORE_STRESS_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
		STORE_STRESS_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
		STORE_STRESS_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
		#endif
		
		#if 1 /* Ŀ¼������Ϣ */
		Store_Algo_CatalogExtRead(&StressStoreInfo, lCatalogSerial, lDataBuf, lCatalog.User.Info.ExtDataLen);
		STORE_STRESS_RTT_LOG(0, "Store_Algo_CatalogExtRead \n");
		for(uint32_t t = 0;t < lCatalog.User.Info.ExtDataLen;t++)
		{
			if((0 == t%32) && (0 != t))
			{
				STORE_STRESS_RTT_LOG(0, "\n");
			}
			STORE_STRESS_RTT_LOG(0, "%02X ", lDataBuf[t]);
		}STORE_STRESS_RTT_LOG(0, "\n");
		#endif
		
		#if 1	/* ��ӡ���� */
		STORE_STRESS_RTT_LOG(0, "Store_Algo_DataRead \n");
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
			Store_Algo_DataRead(&StressStoreInfo, &lCatalog, lDataCnt-lDataLen, lDataBuf, lDataLen);
			for(uint32_t t = 0;t < lDataLen;t++)
			{
				if((0 == t%28) && (0 != t))
				{
					STORE_STRESS_RTT_LOG(0, "\n");
				}
				STORE_STRESS_RTT_LOG(0, "%02X ", lDataBuf[t]);
			}STORE_STRESS_RTT_LOG(0, "\n");
		}while(lDataCnt != lCatalog.Flash.Info.DataLen);
		#endif
		
		// ��һĿ¼
		lDataCnt = 0;
		lDataLen = 0;
		lCatalogSerial = Store_Algo_NextCatalogGet(&StressStoreInfo, lCatalogSerial);
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
uint16_t Store_Stress_CatalogAllUpload(void)
{
	Store_Algo_CatalogAllUpload(&StressStoreInfo);
	
	return Ret_OK;	
}

/*******************************************************************************
 * Brief : ��ȡ����UI��ʾ�����ݣ�����144���㣩
 * Input : @buf ָ�룬����������ǰ
		   @Len ��δʹ��
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
#define STRESS_UI_DATA_LEN	(144)	// ����UI��ʾ�����ݸ���
void Store_Stress_UIDataGet(uint8_t* Buf, uint32_t Len)
{
	uint32_t tReadLen = 0;	// �Ѷ�ȡ�����ݳ���
	uint32_t tCatalog;
	CatalogInfo_t fCatalogInfo;
	uint8_t* lDataBuf;
	uint32_t lDataLen;
	
	memset(Buf, 0x00, STRESS_UI_DATA_LEN*sizeof(Buf[0]));	// ��ʼ��BufĬ��ֵ 
	
	lDataBuf = pvPortMalloc(STORE_MAX_MALLOC_LEN);	// ��ȡ�ڴ�	
	
	/* ��ȡδ����flash������ */ 
	if(eStoreStatusIng == StressStoreInfo.Status)
	{
		for(uint32_t i = StoreStressParam.LogCnt;i > 0;i--)
		{
			Buf[tReadLen++] = StoreStressParam.LogBuf[STORE2_STRESS_DATA_CLASSIFY_LEN*(i-1)];	// ����ֵ����
			if(tReadLen >= STRESS_UI_DATA_LEN)
				goto Done;
		}
	}
	
	/* ��ȡ�Ѵ���flash������ */ 
	if(eStoreStatusIng == StressStoreInfo.Status)
	{
		tCatalog = Store_Algo_NextCatalogGet(&StressStoreInfo, StressStoreInfo.CatalogSerialEnd);
	}
	else
	{
		tCatalog = StressStoreInfo.CatalogSerialBegin;
	}
	for(uint32_t i = 0;i < StressStoreInfo.CatalogSerialCnt;i++)
	{
		/* ��ȡĿ¼��Ϣ */ 
		Store_Algo_CatalogRead(&StressStoreInfo, tCatalog, &fCatalogInfo);		
		
		/* ��ȡFLASH���ݣ�����ȡSTORE_MAX_MALLOC_LEN�ֽڡ����������Ҳ���ᳬ����ֵ */ 
		if(fCatalogInfo.Flash.Info.DataLen >= STORE_MAX_MALLOC_LEN)
			lDataLen = STORE_MAX_MALLOC_LEN;
		else
			lDataLen = fCatalogInfo.Flash.Info.DataLen;
		Store_Algo_DataRead(&StressStoreInfo, &fCatalogInfo, 0, lDataBuf, lDataLen);

		for(uint32_t j = lDataLen / STORE2_STRESS_DATA_CLASSIFY_LEN;j > 0;j--)
		{
			Buf[tReadLen++] = lDataBuf[STORE2_STRESS_DATA_CLASSIFY_LEN*(j-1)];	// ����ֵ����
			if(tReadLen >= STRESS_UI_DATA_LEN)
				goto Done;
		}
		
		// ��һĿ¼
		tCatalog = Store_Algo_LastCatalogGet(&StressStoreInfo, StressStoreInfo.CatalogSerialEnd);
	}
	
	#if 1	// debug
	STORE_STRESS_RTT_LOG(0, "Store_Stress_UIDataGet: \n");
	for(uint32_t i = 0;i < STRESS_UI_DATA_LEN;i++)
	{
		if((0 == i%32) && (0 != i))
		{
			STORE_STRESS_RTT_LOG(0, "\n");
		}
		STORE_STRESS_RTT_LOG(0, "%d ", Buf[i]);
	}STORE_STRESS_RTT_LOG(0, "\n");	
	#endif	
	
	vPortFree(lDataBuf);
	
Done:
	#if 1	// debug
	STORE_STRESS_RTT_LOG(0, "Store_Stress_UIDataGet: \n");
	for(uint32_t i = 0;i < STRESS_UI_DATA_LEN;i++)
	{
		if((0 == i%32) && (0 != i))
		{
			STORE_STRESS_RTT_LOG(0, "\n");
		}
		STORE_STRESS_RTT_LOG(0, "%d ", Buf[i]);
	}STORE_STRESS_RTT_LOG(0, "\n");	
	#endif	
	
	vPortFree(lDataBuf);
}

// ģ����������ݣ����ڲ���
#define STRESS_DATE_SIMULATA_LEN	(189)
void Store_Stress_DateSimulata(void)
{
	STORE_STRESS_RTT_LOG(0, "Store_Stress_DateSimulata \n");
	
	#if 0
	stress_t lStress;
	
	Store_Stress_ClearInit();
	
	for(uint32_t t = 0;t < 2;t++)
	{
		Store_Stress_CatalogCreate();
		for(uint32_t i = 0; i < STRESS_DATE_SIMULATA_LEN;i++)
		{
			memset(&lStress, i, sizeof(stress_t));
			Store_Stress_algorithm();
		}
		Store_Stress_CatalogSeal();	
	}

	#endif
	
	#if 0
	stress_t lStress;
	uint8 UIData[144] = {80 ,76  ,98  ,98  ,67  ,65  ,69  ,71  ,71  ,71  ,63  ,62  ,63  ,59  ,62  ,64  ,64  ,63  ,62  ,63  ,63  ,63  ,62  ,60  ,62  ,58  ,60  ,62  ,59  ,60  ,62  ,59  ,62  ,62  ,61  ,61  ,
	58  ,69  ,59  ,64  ,81  ,61  ,63  ,85  ,64  ,57  ,59  ,60  ,59  ,60  ,59  ,60  ,56  ,56  ,59  ,58  ,56  ,56  ,56  ,57  ,57  ,58  ,56  ,59  ,55  ,57  ,55  ,57  ,57  ,57  ,55  ,
	55  ,56  ,55  ,55  ,55  ,53  ,56  ,54  ,56  ,55  ,57  ,56  ,84  ,58  ,60  ,53  ,55  ,61  ,58  ,63  ,63  ,58  ,72  ,58  ,57  ,63  ,57  ,68  ,56  ,56  ,63  ,57  ,60  ,62  ,60  ,66  ,59  ,57  ,
	53  ,61  ,52  ,73  ,57  ,58  ,56  ,57  ,55  ,56  ,57  ,58  ,56  ,57  ,55  ,56,58  ,56  ,57  ,55  ,56,58  ,56  ,57  ,55  ,80 ,76  ,98  ,98  ,67  ,65  ,69  ,71  ,71 };
	uint32 lUTC = 1542078756;	// 1542078756 ����ʱ�� 2018/11/13 11:12:36
	
	Store_Stress_ClearInit();
		
	Store_Stress_CatalogCreate();
	for(uint32_t i = 0; i < 144;i++)
	{
		lStress.score = UIData[i];
//		Store_Stress_algorithm();
		lUTC += 600;	// 10min
	}
	Store_Stress_CatalogSeal();
	#endif
}

















