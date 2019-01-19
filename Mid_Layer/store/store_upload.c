/**********************************************************************
**
**模块说明: 存储模块上传到手机APP的函数接口
**修改日志：(版本，时间，内容，修改人)
**   		V1.0   2018-9-20  初版  DrL
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
// 函数功能: 
// 输入参数: 
// 返回参数：
static void Store_Upload_ParamInit(void)
{
	memset(&Store_Upload, 0x00, sizeof(Store_Upload_Param_t));
	Store_Upload.DataClassify = eDataClassifyMax;
}

//**********************************************************************
// 函数功能: 
// 输入参数: 
// 返回参数：
void  Store_Upload_Init(void)
{
	Store_Upload_ParamInit();
}

/*******************************************************************************
 * Brief : 
 * Input : @DataClassify 待上传的数据类型，计步、心率、睡眠。。。 
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Upload_CatalogGet(uint16_t DataClassify)
{
	Read_Info_t tRead_Info;
	uint32_t tCatalog;	
	
	// 清空之前数据，防止产生影响
	Store_Upload_ParamInit();
	
	/* 获取待上传数据的存储信息结构体 */
	switch (DataClassify)
	{
		case eDataClassifyStep:
//			Store_Step_CatalogSeal();	// 获取目录用于上传给APP前，先封存一次目录信息，把当前保存在RAM的数据也传上去
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
		case eDataClassifyRunRecord:	// 跑步目录档案
//			Store_RunRecord_StoreInfoGet(&Store_Upload.StoreInfo);
			break;
		default:
			return Ret_InvalidParam;
			break;
	}

	/* 目录为空，获取失败 */
	if(0 == Store_Upload.StoreInfo.CatalogCnt)
		return Ret_Fail;
	
	// 初始上传的参数
	Store_Upload.DataLen = 0;
	Store_Upload.CatalogNum = 0;
	Store_Upload.DataClassify = DataClassify;
	
	tRead_Info.pBuf = pvPortMalloc(STORE_MAX_MALLOC_LEN);
	
	/* 遍历目录，看那些目录还没被上传，遍历结果保存在 Store_Upload 结构体中 */ 
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
		tCatalog = Store_NextCatalogGet(&Store_Upload.StoreInfo, tCatalog);	// 下一目录
	}
	
	/* 计算所有目录的总数据长度 */
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
 * Brief : 获取场景目录信息，用于告诉APP
 * Input : @DataClassify 待上传的数据类型，计步、心率、睡眠。。。 
 * Output: @NULL
 * Return: @NULL
 * Call  : 
 ***************/
uint16_t Store_Upload_SceneCatalogGet(uint16_t DataClassify)
{
	Read_Info_t tRead_Info;
	uint32_t tCatalog;	
	
	// 清空之前数据，防止产生影响
	Store_Upload_ParamInit();
	
	/* 获取待上传数据的存储信息结构体 */
	switch (DataClassify)
	{
		case eDataClassifySleepRecord:
			Store_SleepRecord_StoreInfoGet(&Store_Upload.StoreInfo);
			break;
		case eDataClassifyRunRecord:	// 跑步目录档案
//			Store_RunRecord_StoreInfoGet(&Store_Upload.StoreInfo);
			break;
		default:
			return Ret_InvalidParam;
			break;
	}

	/* 目录为空，获取失败 */
	if(0 == Store_Upload.StoreInfo.CatalogCnt)
		return Ret_Fail;
	
	// 初始上传的参数
	Store_Upload.DataLen = 0;
	Store_Upload.CatalogNum = 0;
	Store_Upload.DataClassify = DataClassify;
	
	tRead_Info.pBuf = pvPortMalloc(STORE_MAX_MALLOC_LEN);
	
	/* 遍历目录，看那些目录还没被上传，遍历结果保存在 Store_Upload 结构体中 */ 
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
		tCatalog = Store_NextCatalogGet(&Store_Upload.StoreInfo, tCatalog);	// 下一目录
	}
	
	/* 计算所有目录的总数据长度 */
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
 * Brief : APP下发指令删除此数据类型的所有数据（APP的删除，对于硬件FLASH就是标记为已上传）
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
 * Brief : APP下发指令删除此数据类型指定UTC数据（硬件FLASH数据标记为已上传）
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
		/* 寻找对应UTC时间的目录，找到则删除（FLASH标记为已上传） */
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
	@CatalogSerial 目录序号，0~max
	@Offset	偏移地址
	@DataBuf 
	@DataLen 
 * Output: NULL
 * Return:	
 */
/*******************************************************************************
 * Brief : 向FLASH获取待上传的存储数据
 * Input : @CatalogSerial 目录序号
		   @Offset 偏移地址
		   @DataBuf 待存放数据的指针
           @DataLen 待获取的数据长度
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
// 函数功能：	获取所有配置参数
// 输入参数：	无
// 返回参数：	无
void Store_Upload_ParamGet(Store_Upload_Param_t* Store_Upload_Param)
{
	memcpy(Store_Upload_Param, &Store_Upload, sizeof(Store_Upload_Param_t));
}

#endif








