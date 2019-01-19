/**********************************************************************
**
**ģ��˵��: �洢ģ���ϴ����ֻ�APP�ĺ����ӿ�
**�޸���־��(�汾��ʱ�䣬���ݣ��޸���)
**   		V1.0   2018-9-20  ����  DrL
**
**********************************************************************/

#if 0

#include "store_upload.h"
#include "store_inner.h"
#include "store_step.h"
#include "store_run.h"
#include "store_hrd.h"
#include "store_stress.h"
#include "store_bodytemp.h"
#include "store_sleep.h"
#include "store_climb.h"
#include "store_swim.h"
#include "store_sleep_record.h"

Store_Upload_Param_t	Store_Upload;

//**********************************************************************
// ��������: 
// �������: 
// ���ز�����
static void Store_Upload_ParamInit(void)
{
	memset(&Store_Upload, 0x00, sizeof(Store_Upload_Param_t));
	Store_Upload.DataClassify = eDataClassifyMax;
}

//**********************************************************************
// ��������: 
// �������: 
// ���ز�����
void  Store_Upload_Init(void)
{
	Store_Upload_ParamInit();
}

/*******************************************************************************
 * Brief : 
 * Input : @DataClassify ���ϴ����������ͣ��Ʋ������ʡ�˯�ߡ����� 
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Upload_CatalogGet(uint16_t DataClassify)
{
	Read_Info_t tRead_Info;
	uint32_t tCatalog;	
	
	// ���֮ǰ���ݣ���ֹ����Ӱ��
	Store_Upload_ParamInit();
	
	/* ��ȡ���ϴ����ݵĴ洢��Ϣ�ṹ�� */
	switch (DataClassify)
	{
		case eDataClassifyStep:
//			Store_Step_CatalogSeal();	// ��ȡĿ¼�����ϴ���APPǰ���ȷ��һ��Ŀ¼��Ϣ���ѵ�ǰ������RAM������Ҳ����ȥ
//			Store_Step_StoreInfoGet(&Store_Upload.StoreInfo);
			break;
		case eDataClassifyHeartRate:
//			Store_Hrd_CatalogSeal();
//			Store_Hrd_StoreInfoGet(&Store_Upload.StoreInfo);
			break;
		case eDataClassifyRunNew:
//			Store_Run_StoreInfoGet(&Store_Upload.StoreInfo);
			break;
		case eDataClassifyStress:
//			Store_Stress_CatalogSeal();
//			Store_Stress_StoreInfoGet(&Store_Upload.StoreInfo);
			break;
		case eDataClassifyBodytemp:
//			Store_Bodytemp_CatalogSeal();
//			Store_Bodytemp_StoreInfoGet(&Store_Upload.StoreInfo);
			break;
		case eDataClassifySleep:
//			Store_Sleep_StoreInfoGet(&Store_Upload.StoreInfo);
			break;
		case eDataClassifyClimbNew:
//			Store_Climb_StoreInfoGet(&Store_Upload.StoreInfo);
			break;
		case eDataClassifySwimNew:
//			Store_Swim_StoreInfoGet(&Store_Upload.StoreInfo);
			break;
		case eDataClassifySleepRecord:
//			Store_SleepRecord_StoreInfoGet(&Store_Upload.StoreInfo);
			break;
		case eDataClassifyRunRecord:	// �ܲ�Ŀ¼����
//			Store_RunRecord_StoreInfoGet(&Store_Upload.StoreInfo);
			break;
		default:
			return Ret_InvalidParam;
			break;
	}

	/* Ŀ¼Ϊ�գ���ȡʧ�� */
	if(0 == Store_Upload.StoreInfo.CatalogCnt)
		return Ret_Fail;
	
	// ��ʼ�ϴ��Ĳ���
	Store_Upload.DataLen = 0;
	Store_Upload.CatalogNum = 0;
	Store_Upload.DataClassify = DataClassify;
	
	tRead_Info.pBuf = pvPortMalloc(STORE_MAX_MALLOC_LEN);
	
	/* ����Ŀ¼������ЩĿ¼��û���ϴ���������������� Store_Upload �ṹ���� */ 
	tCatalog = Store_Upload.StoreInfo.CatalogBegin;
	for(uint32_t i = 0;i < Store_Upload.StoreInfo.CatalogCnt;i++)
	{
		Store_DataRead(&Store_Upload.StoreInfo, &tRead_Info, tCatalog);
		if(STORE_CATALOG_SEALED == tRead_Info.Catalog.Info.State)
		{
			Store_Upload.Catalog[Store_Upload.CatalogNum].Catalog = tCatalog;
			Store_Upload.Catalog[Store_Upload.CatalogNum].DataLen = tRead_Info.Catalog.Info.dataLength;
			Store_Upload.Catalog[Store_Upload.CatalogNum].UTC = tRead_Info.Catalog.Info.utc;
			Store_Upload.CatalogNum++;
		}
		tCatalog = Store_NextCatalogGet(&Store_Upload.StoreInfo, tCatalog);	// ��һĿ¼
	}
	
	/* ��������Ŀ¼�������ݳ��� */
	for(uint32_t i = 0;i < Store_Upload.CatalogNum;i++)
	{
		Store_Upload.DataLen += Store_Upload.Catalog[i].DataLen;
	}
	
	vPortFree(tRead_Info.pBuf);	
	
	#if 0	// debug
	STORE_UPLOAD_RTT_LOG(0, "Store_Upload_CatalogGet 0x%04X \n", Store_Upload.DataClassify);
	STORE_UPLOAD_RTT_LOG(0, "CatalogNum %d \n", Store_Upload.CatalogNum);
	STORE_UPLOAD_RTT_LOG(0, "DataLen %d \n", Store_Upload.DataLen);
	for(uint32_t i = 0;i < Store_Upload.CatalogNum;i++)
	{
		STORE_UPLOAD_RTT_LOG(0, "Store_Upload.Catalog[%d].Catalog %d \n", i, Store_Upload.Catalog[i].Catalog);
		STORE_UPLOAD_RTT_LOG(0, "Store_Upload.Catalog[%d].DataLen %d \n", i, Store_Upload.Catalog[i].DataLen);
		STORE_UPLOAD_RTT_LOG(0, "Store_Upload.Catalog[%d].UTC %d \n", i, Store_Upload.Catalog[i].UTC);	
	}
	#endif
	
	return Ret_OK;	
}


/*******************************************************************************
 * Brief : ��ȡ����Ŀ¼��Ϣ�����ڸ���APP
 * Input : @DataClassify ���ϴ����������ͣ��Ʋ������ʡ�˯�ߡ����� 
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Upload_SceneCatalogGet(uint16_t DataClassify)
{
	Read_Info_t tRead_Info;
	uint32_t tCatalog;	
	
	// ���֮ǰ���ݣ���ֹ����Ӱ��
	Store_Upload_ParamInit();
	
	/* ��ȡ���ϴ����ݵĴ洢��Ϣ�ṹ�� */
	switch (DataClassify)
	{
		case eDataClassifySleepRecord:
			Store_SleepRecord_StoreInfoGet(&Store_Upload.StoreInfo);
			break;
		case eDataClassifyRunRecord:	// �ܲ�Ŀ¼����
//			Store_RunRecord_StoreInfoGet(&Store_Upload.StoreInfo);
			break;
		default:
			return Ret_InvalidParam;
			break;
	}

	/* Ŀ¼Ϊ�գ���ȡʧ�� */
	if(0 == Store_Upload.StoreInfo.CatalogCnt)
		return Ret_Fail;
	
	// ��ʼ�ϴ��Ĳ���
	Store_Upload.DataLen = 0;
	Store_Upload.CatalogNum = 0;
	Store_Upload.DataClassify = DataClassify;
	
	tRead_Info.pBuf = pvPortMalloc(STORE_MAX_MALLOC_LEN);
	
	/* ����Ŀ¼������ЩĿ¼��û���ϴ���������������� Store_Upload �ṹ���� */ 
	tCatalog = Store_Upload.StoreInfo.CatalogBegin;
	for(uint32_t i = 0;i < Store_Upload.StoreInfo.CatalogCnt;i++)
	{
		Store_DataRead(&Store_Upload.StoreInfo, &tRead_Info, tCatalog);
		if(STORE_CATALOG_SEALED == tRead_Info.Catalog.Info.State)
		{
			Store_Upload.Catalog[Store_Upload.CatalogNum].Catalog = tCatalog;
			Store_Upload.Catalog[Store_Upload.CatalogNum].DataLen = tRead_Info.Catalog.Info.RecordDataLen;	//tRead_Info.Catalog.Info.dataLength;
			Store_Upload.Catalog[Store_Upload.CatalogNum].UTC = tRead_Info.Catalog.Info.utc;
			Store_Upload.CatalogNum++;
		}
		tCatalog = Store_NextCatalogGet(&Store_Upload.StoreInfo, tCatalog);	// ��һĿ¼
	}
	
	/* ��������Ŀ¼�������ݳ��� */
	for(uint32_t i = 0;i < Store_Upload.CatalogNum;i++)
	{
		Store_Upload.DataLen += Store_Upload.Catalog[i].DataLen;
	}
	
	vPortFree(tRead_Info.pBuf);	
	
	#if 0	// debug
	STORE_UPLOAD_RTT_LOG(0, "Store_Upload_CatalogGet 0x%04X \n", Store_Upload.DataClassify);
	STORE_UPLOAD_RTT_LOG(0, "CatalogNum %d \n", Store_Upload.CatalogNum);
	STORE_UPLOAD_RTT_LOG(0, "DataLen %d \n", Store_Upload.DataLen);
	for(uint32_t i = 0;i < Store_Upload.CatalogNum;i++)
	{
		STORE_UPLOAD_RTT_LOG(0, "Store_Upload.Catalog[%d].Catalog %d \n", i, Store_Upload.Catalog[i].Catalog);
		STORE_UPLOAD_RTT_LOG(0, "Store_Upload.Catalog[%d].DataLen %d \n", i, Store_Upload.Catalog[i].DataLen);
		STORE_UPLOAD_RTT_LOG(0, "Store_Upload.Catalog[%d].UTC %d \n", i, Store_Upload.Catalog[i].UTC);	
	}
	#endif
	
	return Ret_OK;	
}


/*******************************************************************************
 * Brief : APP�·�ָ��ɾ�����������͵��������ݣ�APP��ɾ��������Ӳ��FLASH���Ǳ��Ϊ���ϴ���
 * Input : @NULL
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
void Store_Upload_CatalogAllDelete(void)
{
	Store_CatalogAllUpload(&Store_Upload.StoreInfo);
}

/*******************************************************************************
 * Brief : APP�·�ָ��ɾ������������ָ��UTC���ݣ�Ӳ��FLASH���ݱ��Ϊ���ϴ���
 * Input : @UTC 
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Upload_CatalogUTCDelete(uint32_t UTC)
{
	for(uint32_t i = 0;i < Store_Upload.CatalogNum;i++)
	{
		if(UTC == Store_Upload.Catalog[i].UTC)
		/* Ѱ�Ҷ�ӦUTCʱ���Ŀ¼���ҵ���ɾ����FLASH���Ϊ���ϴ��� */
		{
			Store_CatalogUpload(&Store_Upload.StoreInfo, Store_Upload.Catalog[i].Catalog);
			break;
		}
	}
	
	return Ret_OK;
}

/*********************************************************************
 * Brief :
 * Input :
	@CatalogSerial Ŀ¼��ţ�0~max
	@Offset	ƫ�Ƶ�ַ
	@DataBuf 
	@DataLen 
 * Output: NULL
 * Return:	
 */
/*******************************************************************************
 * Brief : ��FLASH��ȡ���ϴ��Ĵ洢����
 * Input : @CatalogSerial Ŀ¼���
		   @Offset ƫ�Ƶ�ַ
		   @DataBuf ��������ݵ�ָ��
           @DataLen ����ȡ�����ݳ���
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Upload_DataGet(uint16_t CatalogSerial, uint16_t Offset, uint8_t* DataBuf, uint32_t DataLen)
{
	Read_Info_t tRead_Info;
	
	tRead_Info.pBuf = pvPortMalloc(STORE_MAX_MALLOC_LEN);
	
	Store_DataRead(&Store_Upload.StoreInfo, &tRead_Info, Store_Upload.Catalog[CatalogSerial].Catalog);
	memcpy(DataBuf, tRead_Info.pBuf + Offset, DataLen);
	
	vPortFree(tRead_Info.pBuf);	
	
	return Ret_OK;
}

//**********************************************************************
// �������ܣ�	��ȡ�������ò���
// ���������	��
// ���ز�����	��
void Store_Upload_ParamGet(Store_Upload_Param_t* Store_Upload_Param)
{
	memcpy(Store_Upload_Param, &Store_Upload, sizeof(Store_Upload_Param_t));
}

#endif








