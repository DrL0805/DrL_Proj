/**********************************************************************
**
**模块说明: 数据上传模块，依据通信协议
**修改日志：(版本，时间，内容，修改人)
**   		V1.0   2018-12-08  初版  DrL
**
**********************************************************************/

#include "store_pdu.h"
#include "store_algo.h"
#include "store_step.h"
#include "store_run.h"
#include "store_hrd.h"
#include "store_stress.h"
#include "store_bodytemp.h"
#include "store_sleep.h"
#include "store_sleep_record.h"
#include "store_climb.h"
#include "store_swim.h"
#include "store_task.h"
#include "scene_sleep.h"

#include "ble_task.h"

StorePDUParam_t			StorePDUParam;
static TimerHandle_t 	Store_PDU_TimerHandle;

static void Store_PDUCmn_TimerCb(TimerHandle_t xTimer)
{
	Store_Task_Msg_T Store_Task_Msg;
	
	Store_Task_Msg.Id = eStoreTaskMsgPDU;
	Store_Task_EventSet(&Store_Task_Msg);
}

/*******************************************************************************
 ** Brief : 参数初始化（清零）
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
static void Store_PDU_ParamInit(void)
{
	memset(&StorePDUParam, 0x00, sizeof(StorePDUParam_t));
	StorePDUParam.DataClassify = eDataClassifyMax;
	StorePDUParam.InitFlg = true;
}

/*******************************************************************************
 ** Brief : 获取目录信息，存放在StorePDUParam结构体中，待上传给APP
 ** Input : @fDataClassify 数据类型
 ** Return: 运行结果
 ** Call  : 内部调用
 ***************/
static uint16_t Store_PDU_CatalogGet(uint16_t fDataClassify)
{
	uint32_t 			lCatalogSerial;
	CatalogInfo_t		lCatalogInfo;	
	StoreStepParam_t* 	lStoreStepParam;
	
	Store_PDU_ParamInit();	// 清空之前数据，防止产生影响
	StorePDUParam.RamData.ValidFlg = false;	// 每次请求新的目录前，先把RAM目录置为无效
	StorePDUParam.RamData.UploadFlg = false;
	
	/* 获取待上传数据的存储信息结构体 */
	switch (fDataClassify)
	{
		case eDataClassifyStep:
			StorePDUParam.RTS.SampleUnit = STORE2_STEP_SAMPLE_INFO;
			StorePDUParam.RTS.ClassifyLen = STORE2_STEP_DATA_CLASSIFY_LEN;
			StorePDUParam.RTS.EachSendLen = (PDU_DATA_UPLOAD_MAX_LEN 
				/ StorePDUParam.RTS.ClassifyLen) * StorePDUParam.RTS.ClassifyLen;	// 先除再乘是为了取整		
			StorePDUParam.pPDUStoreInfo = Store_Step_StoreInfoGet();
		
			/* RAM数据是否需要上传 */
			lStoreStepParam = Store_Step_ParamPGet();
			if(lStoreStepParam->LogCnt)
			/* 有RAM数据需要上传 */
			{
				STORE_PDU_RTT_LOG(0, "Store_PDU_CatalogGet ValidFlg = true \n");
				
				StorePDUParam.RamData.ValidFlg = true;
				StorePDUParam.RamData.DataLen = lStoreStepParam->LogCnt*STORE2_STEP_DATA_CLASSIFY_LEN;
				StorePDUParam.RamData.UTC = StorePDUParam.pPDUStoreInfo->Catalog.User.Info.UTC;
				memcpy(StorePDUParam.RamData.RAM.DataBuf, lStoreStepParam->LogBuf, StorePDUParam.RamData.DataLen);
			}
			break;
		case eDataClassifyHeartRate:
			StorePDUParam.RTS.SampleUnit = STORE2_HRD_SAMPLE_INFO;
			StorePDUParam.RTS.ClassifyLen = STORE2_HRD_DATA_CLASSIFY_LEN;
			StorePDUParam.RTS.EachSendLen = (PDU_DATA_UPLOAD_MAX_LEN 
				/ StorePDUParam.RTS.ClassifyLen) * StorePDUParam.RTS.ClassifyLen;	// 先除再乘是为了取整		
			StorePDUParam.pPDUStoreInfo = Store_Hrd_StoreInfoGet();
			break;
		case eDataClassifyBodytemp:
			StorePDUParam.RTS.SampleUnit = STORE2_BODYTEMP_SAMPLE_INFO;
			StorePDUParam.RTS.ClassifyLen = STORE2_BODYTEMP_DATA_CLASSIFY_LEN;
			StorePDUParam.RTS.EachSendLen = (PDU_DATA_UPLOAD_MAX_LEN 
				/ StorePDUParam.RTS.ClassifyLen) * StorePDUParam.RTS.ClassifyLen;	// 先除再乘是为了取整		
			StorePDUParam.pPDUStoreInfo = Store_Bodytemp_StoreInfoGet();
			break;	
		case eDataClassifySleep:
			return Ret_InvalidParam;
			break;
		case eDataClassifyRunNew:
			StorePDUParam.RTS.EachSendLen = STORE2_RUN_DATA_CLASSIFY_LEN;
			StorePDUParam.pPDUStoreInfo = Store_Run_StoreInfoGet();
			break;
		case eDataClassifyClimbNew:
			StorePDUParam.RTS.EachSendLen = STORE2_CLIMB_DATA_CLASSIFY_LEN;
			StorePDUParam.pPDUStoreInfo = Store_Climb_StoreInfoGet();
			break;
		case eDataClassifySwimNew:
			StorePDUParam.RTS.EachSendLen = 15; // STORE2_SWIM_DATA_CLASSIFY_LEN*3;
			StorePDUParam.pPDUStoreInfo = Store_Swim_StoreInfoGet();
			break;
		default:
			return Ret_InvalidParam;
			break;
	}	
	
	/* 目录为空，获取失败 */
	if((0 == StorePDUParam.pPDUStoreInfo->CatalogSerialCnt) && !StorePDUParam.RamData.ValidFlg)
		return Ret_QueueEmpty;
	
	// 初始上传的参数
	StorePDUParam.AllDataLen = 0;
	StorePDUParam.CatalogNum = 0;
	StorePDUParam.DataClassify = fDataClassify;	
	
	/* 遍历目录，看那些目录还没被上传，遍历结果保存在 StorePDUParam 结构体中 */
	lCatalogSerial = StorePDUParam.pPDUStoreInfo->CatalogSerialBegin;
	for(uint32_t i = 0;i < StorePDUParam.pPDUStoreInfo->CatalogSerialCnt;i++)
	{
		Store_Algo_CatalogRead(StorePDUParam.pPDUStoreInfo, lCatalogSerial, &lCatalogInfo);
		if(eCatalogMarkSealed == lCatalogInfo.Flash.Info.Mark)
		/* 读取目录信息，若目录MARK为未上传，则保存在 StorePDUParam 结构体中 */
		{
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].CatalogSerial = lCatalogSerial;
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].DataLen = lCatalogInfo.Flash.Info.DataLen;
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].DataAddr = lCatalogInfo.Flash.Info.DataAddr;
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].UTC = lCatalogInfo.User.Info.UTC;
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].ExtDataLen = lCatalogInfo.User.Info.ExtDataLen;
			StorePDUParam.CatalogNum++;
		}
		
		lCatalogSerial = Store_Algo_NextCatalogGet(StorePDUParam.pPDUStoreInfo, lCatalogSerial);	// 下一目录
	}
	
	/* 计算所有目录的总数据长度 */
	for(uint32_t i = 0;i < StorePDUParam.CatalogNum;i++)
	{
		StorePDUParam.AllDataLen += StorePDUParam.Catalog[i].DataLen;
	}
	
	return Ret_OK;	
}

/*******************************************************************************
 ** Brief : 定时器超时处理函数
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Store_PDU_TimerHandler(void)
{
	ble_msg_t bleMsg;
	uint8_t		lSendLen;
	CatalogInfo_t lCatalogInfo;
	
//	PDU_RTT_LOG(0, "Store_PDU_TimerHandler %d \n", StorePDUParam.State);
	
	switch (StorePDUParam.State)
    {
    	case eStorePDUCatalogDataRTS:	// 发送数据
			bleMsg.id		= BLE_MSG_SEND;
			bleMsg.packet	= PROT_PACK_TRANS_DATA_UPLOAD;
			bleMsg.packet.att.flowControl = StorePDUParam.RTS.FlowCtrl++;
		
			if(StorePDUParam.RamData.UploadFlg)
			/* RAM目录 */
			{
				if((StorePDUParam.RTS.SendCnt + StorePDUParam.RTS.EachSendLen) >= StorePDUParam.RamData.DataLen)
				/* 最后一包 */
				{
					lSendLen = StorePDUParam.RamData.DataLen - StorePDUParam.RTS.SendCnt;
					xTimerStop(Store_PDU_TimerHandle,0);
					StorePDUParam.State = eStorePDUIdle;
				}
				else
				{
					lSendLen = StorePDUParam.RTS.EachSendLen;
				}
			}
			else
			/* FLASH目录 */
			{
				if((StorePDUParam.RTS.SendCnt + StorePDUParam.RTS.EachSendLen) >= 
					StorePDUParam.Catalog[StorePDUParam.RTS.CurrCatalog].DataLen)
				/* 最后一包 */
				{
					lSendLen = StorePDUParam.Catalog[StorePDUParam.RTS.CurrCatalog].DataLen - StorePDUParam.RTS.SendCnt;
					xTimerStop(Store_PDU_TimerHandle,0);
					StorePDUParam.State = eStorePDUIdle;
				}
				else
				{
					lSendLen = StorePDUParam.RTS.EachSendLen;
				}			
			}

			bleMsg.packet.att.load.content.parameter[0]	= (uint8)((StorePDUParam.RTS.SendCnt / StorePDUParam.RTS.EachSendLen) >> 8);	// 包号
			bleMsg.packet.att.load.content.parameter[1]	= (uint8)(StorePDUParam.RTS.SendCnt / StorePDUParam.RTS.EachSendLen);	
			bleMsg.packet.att.load.content.parameter[2]	= (uint8)(StorePDUParam.DataClassify >> 8);	// 数据类型
			bleMsg.packet.att.load.content.parameter[3]	= (uint8)(StorePDUParam.DataClassify);
			bleMsg.packet.att.loadLength = ( lSendLen+ 7);		// 3接口帧+2序号+2类型+16有效数据
			
			if(StorePDUParam.RamData.UploadFlg)
			/* RAM目录，从RAM读取待上传数据 */
			{
				memcpy(bleMsg.packet.att.load.content.parameter + 4, 
					StorePDUParam.RamData.RAM.DataBuf+StorePDUParam.RTS.SendCnt, lSendLen);
			}
			else
			/* FLASH目录，从FLASH读取待上传的数据 */
			{
				lCatalogInfo.Flash.Info.DataAddr = StorePDUParam.Catalog[StorePDUParam.RTS.CurrCatalog].DataAddr;
				lCatalogInfo.Flash.Info.DataLen = StorePDUParam.Catalog[StorePDUParam.RTS.CurrCatalog].DataLen;
				
				Store_Algo_DataRead(StorePDUParam.pPDUStoreInfo, &lCatalogInfo, StorePDUParam.RTS.SendCnt, 
					bleMsg.packet.att.load.content.parameter + 4, lSendLen);
			}

			Mid_Ble_SendMsg(&bleMsg);
			
			StorePDUParam.RTS.SendCnt += lSendLen;	
    		break;
    	case eStorePDUCatalogDetailRTS:		// 发送目录
			bleMsg.id = BLE_MSG_SEND;
			bleMsg.packet = PROT_SCENE_TRANS_CATA_RET;
			bleMsg.packet.att.flowControl = StorePDUParam.RTS.FlowCtrl++;
			if((StorePDUParam.RTS.SendCnt + 10) >= StorePDUParam.RTS.RecordLen)
			/* 最后一包 */
			{
				lSendLen = StorePDUParam.RTS.RecordLen - StorePDUParam.RTS.SendCnt;
				bleMsg.packet.att.load.content.parameter[0] = 0xFF;	// 最后一包包号为0xFF
				xTimerStop(Store_PDU_TimerHandle,0);
				StorePDUParam.State = eStorePDUIdle;
			}
			else
			{
				lSendLen = 10;
				bleMsg.packet.att.load.content.parameter[0] = StorePDUParam.RTS.SendCnt / 10;
			}
			bleMsg.packet.att.loadLength += ( lSendLen+ 1);	// 1字节的包号
			memcpy(bleMsg.packet.att.load.content.parameter+1, StorePDUParam.RTS.RecordBuf+StorePDUParam.RTS.SendCnt, lSendLen);
			Mid_Ble_SendMsg(&bleMsg);
			
			StorePDUParam.RTS.SendCnt += lSendLen;	
    		break;
		case eStorePDUSleepRecordRTS:	// 发送睡眠档案
			bleMsg.id = BLE_MSG_SEND;
			bleMsg.packet = PROT_SCENE_SLEEP_RECORD_INFO_NEW_ECHO;
			bleMsg.packet.att.flowControl = StorePDUParam.RTS.FlowCtrl++;
			bleMsg.packet.att.load.content.parameter[0] = StorePDUParam.RTS.SendCnt;
			bleMsg.packet.att.load.content.parameter[1] = (uint8_t)(StorePDUParam.RamData.RAM.SleepRecord.SleepData[StorePDUParam.RTS.SendCnt].State);
			bleMsg.packet.att.load.content.parameter[2] = (uint8_t)(StorePDUParam.RamData.RAM.SleepRecord.SleepData[StorePDUParam.RTS.SendCnt].Duration >> 8);
			bleMsg.packet.att.load.content.parameter[3] = (uint8_t)(StorePDUParam.RamData.RAM.SleepRecord.SleepData[StorePDUParam.RTS.SendCnt].Duration >> 0);
			if(StorePDUParam.RTS.SendCnt >= (StorePDUParam.RamData.RAM.SleepRecord.SegmentCnt-1))
			/* 最后包包号0xFF */
			{
				bleMsg.packet.att.load.content.parameter[0] = 0xFF;
				xTimerStop(Store_PDU_TimerHandle,0);
				StorePDUParam.State = eStorePDUIdle;
			}
			
			StorePDUParam.RTS.SendCnt++;
			Mid_Ble_SendMsg(&bleMsg);
			break;
    	default :
			xTimerStop(Store_PDU_TimerHandle,0);
    		break;
    }
}

/*******************************************************************************
 ** Brief : 模块初始化
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Store_PDU_Init(void)
{
	Store_PDU_TimerHandle=xTimerCreate((const char*		)"Store_PDU_Timer",
										(TickType_t			)(20/portTICK_PERIOD_MS),
										(UBaseType_t		)pdTRUE,
										(void*				)1,
										(TimerCallbackFunction_t)Store_PDUCmn_TimerCb);	
	
	Store_PDU_ParamInit();
	
	StorePDUParam.InitFlg = true;
	StorePDUParam.State = eStorePDUIdle;
}

StorePDUParam_t* Store_PDU_ParamPGet(void)
{
	return &StorePDUParam;
}

/*******************************************************************************
 ** Brief : 请求上传目录整体信息
			根据通信协议，基础数据和运动场景数据，通信协议格式是一样的
 ** Input : @fDataClassify 数据类型：计步跑步游泳等
			@flowControl 流控
 ** Return: 
 ** Call  : 
 ***************/
uint16_t Store_PDU_CatalogInfoRTS(uint16 fDataClassify, uint8 flowControl)
{
	if(!StorePDUParam.InitFlg) drERROR_CHECK_RETURN_ERR("Store_PDU_CatalogInfoRTS", Ret_NoInit);	
	
	ble_msg_t bleMsg;
	uint16_t	lCatalogNum;
	uint32_t	lAllDataLen;

	if(Ret_OK == Store_PDU_CatalogGet(fDataClassify))
	/* 目录获取成功，返回目录信息 */
	{
		if(StorePDUParam.RamData.ValidFlg)
		/* 存在RAM目录 */
		{
			lCatalogNum = StorePDUParam.CatalogNum + 1;
			lAllDataLen = StorePDUParam.AllDataLen + StorePDUParam.RamData.DataLen;
		}		
		else
		{
			lCatalogNum = StorePDUParam.CatalogNum;
			lAllDataLen = StorePDUParam.AllDataLen;
		}
		
		bleMsg.id = BLE_MSG_SEND;
		bleMsg.packet= PROT_PACK_TRANS_CATA_TOTAL_RET;
		bleMsg.packet.att.load.content.parameter[0]	= (uint8)(fDataClassify >> 8);
		bleMsg.packet.att.load.content.parameter[1]	= (uint8)(fDataClassify);
		bleMsg.packet.att.load.content.parameter[2]	= (uint8)(lCatalogNum >> 8);
		bleMsg.packet.att.load.content.parameter[3]	= (uint8)(lCatalogNum);
		bleMsg.packet.att.load.content.parameter[4]	= (uint8)(lAllDataLen >> 24);
		bleMsg.packet.att.load.content.parameter[5]	= (uint8)(lAllDataLen >> 16);
		bleMsg.packet.att.load.content.parameter[6]	= (uint8)(lAllDataLen >> 8);
		bleMsg.packet.att.load.content.parameter[7]	= (uint8)(lAllDataLen);
		bleMsg.packet.att.flowControl = flowControl;
        Mid_Ble_SendMsg(&bleMsg);		
	}
	else
	/* 目录获取失败，返回0 */	
	{
		bleMsg.id = BLE_MSG_SEND;
		bleMsg.packet= PROT_PACK_TRANS_CATA_TOTAL_RET;
		bleMsg.packet.att.load.content.parameter[0]	= (uint8)(fDataClassify >> 8);
		bleMsg.packet.att.load.content.parameter[1]	= (uint8)(fDataClassify);
		memset(bleMsg.packet.att.load.content.parameter+2, 0x00, 6);
		bleMsg.packet.att.flowControl = flowControl;
        Mid_Ble_SendMsg(&bleMsg);		
	}
	
	return Ret_OK;	
}

/*******************************************************************************
 ** Brief : 获取基础场景数据指定序号的目录信息
 ** Input : @fDataClassify 数据类型
			@fCatalog APP请求的目录序号，非物理目录序号
			@flowControl 流控
 ** Return: 
 ** Call  : 
 ***************/
uint16_t Store_PDU_BaseCatalogDetailRTS(uint16 fDataClassify, uint16_t fCatalog, uint8 flowControl)
{
	if(!StorePDUParam.InitFlg) drERROR_CHECK_RETURN_ERR("Store_PDU_BaseCatalogDetailRTS", Ret_NoInit);
	if(fDataClassify != StorePDUParam.DataClassify) drERROR_CHECK_RETURN_ERR("Store_PDU_BaseCatalogDetailRTS", Ret_InvalidParam);
	
	ble_msg_t bleMsg;
	uint32_t lUTC, lDataLen;
	
	if(fCatalog < StorePDUParam.CatalogNum)
	{
		lUTC = StorePDUParam.Catalog[fCatalog].UTC;
		lDataLen = StorePDUParam.Catalog[fCatalog].DataLen;
	}
	else if((fCatalog == StorePDUParam.CatalogNum) && StorePDUParam.RamData.ValidFlg)
	/* fCatalog == StorePDUParam.CatalogNum，上传RAM目录信息 */
	{
		STORE_PDU_RTT_LOG(0, "Store_PDU_BaseCatalogDetailRTS ValidFlg = true \n");
		lUTC = StorePDUParam.RamData.UTC;
		lDataLen = StorePDUParam.RamData.DataLen;
	}
	else
	{
		drERROR_CHECK_RETURN_ERR("Store_PDU_BaseCatalogDetailRTS 1", (Ret_InvalidParam));
	}

	bleMsg.id = BLE_MSG_SEND;
	bleMsg.packet = PROT_PACK_TRANS_CATA_RET;
	bleMsg.packet.att.load.content.parameter[0]	= (uint8)(lUTC >> 24);
	bleMsg.packet.att.load.content.parameter[1]	= (uint8)(lUTC >> 16);
	bleMsg.packet.att.load.content.parameter[2]	= (uint8)(lUTC >> 8);
	bleMsg.packet.att.load.content.parameter[3]	= (uint8)(lUTC);
	bleMsg.packet.att.load.content.parameter[4]	= (uint8)(lDataLen >> 8);
	bleMsg.packet.att.load.content.parameter[5]	= (uint8)(lDataLen);
	bleMsg.packet.att.load.content.parameter[6]	= (uint8)((StorePDUParam.RTS.SampleUnit << 4) | (StorePDUParam.RTS.SampleUnit >> 12));
	bleMsg.packet.att.load.content.parameter[7]	= (uint8)(StorePDUParam.RTS.SampleUnit);
	bleMsg.packet.att.load.content.parameter[8]	= (uint8)(StorePDUParam.RTS.ClassifyLen);
	bleMsg.packet.att.flowControl = flowControl;
    Mid_Ble_SendMsg(&bleMsg);
	
	return Ret_OK;
}

/*******************************************************************************
 ** Brief : 获取运动场景数据指定序号的目录信息
 ** Input : @fDataClassify 数据类型
			@fCatalog APP请求的目录序号，非物理目录序号
			@flowControl 流控
 ** Return: 
 ** Call  : 
 ***************/
uint16_t Store_PDU_SceneCatalogDetailRTS(uint16 fDataClassify, uint16_t fCatalog, uint8 flowControl)
{
	if(!StorePDUParam.InitFlg) drERROR_CHECK_RETURN_ERR("Store_PDU_SceneCatalogDetailRTS", Ret_NoInit);
	if(fDataClassify != StorePDUParam.DataClassify) drERROR_CHECK_RETURN_ERR("Store_PDU_SceneCatalogDetailRTS", Ret_InvalidParam);
	if(fCatalog >= StorePDUParam.CatalogNum) drERROR_CHECK_RETURN_ERR("Store_PDU_SceneCatalogDetailRTS", (Ret_InvalidParam+1));	
	
	uint8_t 		lDataBuf[STORE2_CATALOG_EXT_INFO_LEN];
	runningRecord_t			lrunningRecord;
	climbMountainRecord_t 	lclimbMountainRecord;
	swimIndoorRecord_t		lswimIndoorRecord;
//	uint32_t lPackNum;
//	ble_msg_t bleMsg;
	
	// 读取目录附加信息
	Store_Algo_CatalogExtRead(StorePDUParam.pPDUStoreInfo, StorePDUParam.Catalog[fCatalog].CatalogSerial, 
		lDataBuf, StorePDUParam.Catalog[fCatalog].ExtDataLen);
	
	#if 0	
	STORE_PDU_RTT_LOG(0, "sizeof(runningRecord_t) %d \n",sizeof(runningRecord_t));
	STORE_PDU_RTT_LOG(0, "sizeof(climbMountainRecord_t) %d \n",sizeof(climbMountainRecord_t));
	STORE_PDU_RTT_LOG(0, "sizeof(swimIndoorRecord_t) %d \n",sizeof(swimIndoorRecord_t));
	#endif
	
	#if 0	// 打印目录附加信息
	STORE_PDU_RTT_LOG(0, "Store_PDU_SceneCatalogDetailRTS: \n");
	for(uint32_t i = 0;i < StorePDUParam.Catalog[fCatalog].ExtDataLen;i++)
	{
		if((0 == i%32) && (0 != i))
		{
			STORE_PDU_RTT_LOG(0, "\n");
		}
		STORE_PDU_RTT_LOG(0, "%02X ", lDataBuf[i]);
	}STORE_PDU_RTT_LOG(0, "\n");
	#endif
	
	StorePDUParam.RTS.SendCnt = 0;
	StorePDUParam.RTS.FlowCtrl = flowControl;
	StorePDUParam.RTS.RecordLen = 0;
	StorePDUParam.State = eStorePDUCatalogDetailRTS;
	switch (fDataClassify)
    {
    	case eDataClassifyRunNew:
			/* 转换为结构体信息 */
			memcpy((uint8_t*)&lrunningRecord, lDataBuf, StorePDUParam.Catalog[fCatalog].ExtDataLen);
			
			// 通用
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(fDataClassify >> 8);	// 数据类型
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(fDataClassify);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 24);	// 起始UTC
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(StorePDUParam.Catalog[fCatalog].DataLen >> 8);	// 数据长度
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(StorePDUParam.Catalog[fCatalog].DataLen);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_RUN_SAMPLE_INFO >> 8);	// 采样间隔和单位 10秒
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_RUN_SAMPLE_INFO);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_RUN_DATA_CLASSIFY_LEN);	// 数据单元长度				
			
			// 跑步特有
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StartUTC >> 24); // 开始时间
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StartUTC >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StartUTC >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StartUTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Duration >> 24); // 持续总时间
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Duration >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Duration >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Duration);	
			memset(&StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen], 0x00, 20);	// 第1~5阶段持续时间
			StorePDUParam.RTS.RecordLen += 20;
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Distance >> 8); // 跑步总距离
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Distance);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Step >> 24); // 总步数
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Step >> 16);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Step >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Step);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Calorie >> 8); // 总卡路里
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Calorie);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StopUTC >> 24); // 结束时间
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StopUTC >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StopUTC >> 8);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StopUTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.ValidDuration >> 24); // 总有效活动时间
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.ValidDuration >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.ValidDuration >> 8);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.ValidDuration);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.PaceAVG >> 8); // 平均配速
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.PaceAVG);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.FreqAVG >> 8); // 平均步频
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.FreqAVG);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StrideAVG >> 8); // 平均步幅
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StrideAVG);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.HrAVG); // 平均心率
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.HrMax); // 最大心率			
    		break;
    	case eDataClassifyClimbNew:
			/* 转换为结构体信息 */
			memcpy((uint8_t*)&lclimbMountainRecord, lDataBuf, StorePDUParam.Catalog[fCatalog].ExtDataLen);
			
			// 通用
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(fDataClassify >> 8);	// 数据类型
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(fDataClassify);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 24);	// 起始UTC
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(StorePDUParam.Catalog[fCatalog].DataLen >> 8);	// 数据长度
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(StorePDUParam.Catalog[fCatalog].DataLen);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_CLIMB_SAMPLE_INFO >> 8);	// 采样间隔和单位 10秒
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_CLIMB_SAMPLE_INFO);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_CLIMB_DATA_CLASSIFY_LEN);	// 数据单元长度				
			
			// 登山特有
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.StartUTC >> 24); // 开始时间
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.StartUTC >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.StartUTC >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.StartUTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Duration >> 24); // 持续总时间
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Duration >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Duration >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Duration);
			memset(&StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen], 0x00, 20);	// 第1~5阶段持续时间
			StorePDUParam.RTS.RecordLen += 20;
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.UpAltitude >> 8); // 上升距离
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.UpAltitude);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.DownAltitude >> 8); // 下降距离
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.DownAltitude);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.HighestAltitude >> 8); // 最高海拔
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.HighestAltitude);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.LowestAltitude >> 8); // 最低海拔
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.LowestAltitude);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Calorie >> 8); // 总卡路里
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Calorie);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.StopUTC >> 24); // 结束时间
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.StopUTC >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.StopUTC >> 8);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.StopUTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = 0;//(uint8)(lclimbMountainRecord.ValidDuration >> 24); // 总有效活动时间
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = 0;//(uint8)(lclimbMountainRecord.ValidDuration >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = 0;//(uint8)(lclimbMountainRecord.ValidDuration >> 8);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = 0;//(uint8)(lclimbMountainRecord.ValidDuration);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Step >> 24); // 总步数
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Step >> 16);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Step >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Step);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Distance >> 8); // 登山总距离
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Distance);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.SpeedAVG >> 8); // 平均配速
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.SpeedAVG);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.HrAVG); // 平均心率
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.HrMax); // 最大心率				
    		break;
		case eDataClassifySwimNew:
			/* 转换为结构体信息 */
			memcpy((uint8_t*)&lswimIndoorRecord, lDataBuf, StorePDUParam.Catalog[fCatalog].ExtDataLen);
			
			// 通用
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(fDataClassify >> 8);	// 数据类型
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(fDataClassify);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 24);	// 起始UTC
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(StorePDUParam.Catalog[fCatalog].DataLen >> 8);	// 数据长度
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(StorePDUParam.Catalog[fCatalog].DataLen);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_SWIM_SAMPLE_INFO >> 8);	// 采样间隔和单位 10秒
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_SWIM_SAMPLE_INFO);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_SWIM_DATA_CLASSIFY_LEN);	// 数据单元长度				
			
			// 游泳特有
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StartUTC >> 24); // 开始时间
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StartUTC >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StartUTC >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StartUTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Duration >> 24); // 持续总时间
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Duration >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Duration >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Duration);	
			memset(&StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen], 0x00, 20);	// 第1~5阶段持续时间
			StorePDUParam.RTS.RecordLen += 20;
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Stroke >> 8); // 总划水次数
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Stroke);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Calorie >> 8); // 总卡路里
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Calorie);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StopUTC >> 24); // 结束时间
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StopUTC >> 16);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StopUTC >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StopUTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.ValidDuration >> 24); // 有效活动时间
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.ValidDuration >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.ValidDuration >> 8);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.ValidDuration);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Distance >> 8); // 游泳总距离
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Distance);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Laps >> 8); // 总趟数
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Laps);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.PaceAVG >> 8); // 平均速度
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.PaceAVG);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StrokeAVG >> 8); // 平均划水数
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StrokeAVG);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StrokeRateAVG >> 8); // 平均划水率
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StrokeRateAVG);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.HrAVG); 			// 平均心率
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.HrMax); 			// 最大心率	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = 0;//(uint8)(lswimIndoorRecord.Swolf >> 8); 	// SWOLOF
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = 0;//(uint8)(lswimIndoorRecord.Swolf);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Style);		// 泳姿
    		break;
    	default :
    		break;		
    }
	
	#if 1	// debug，打印即将发送的目录信息
	STORE_PDU_RTT_LOG(0, "StorePDUParam.RTS.RecordLen %d \n", StorePDUParam.RTS.RecordLen);
	for(uint32_t i = 0;i < StorePDUParam.RTS.RecordLen;i++)
	{
		if((0 == i%32) && (0 != i))
		{
			STORE_PDU_RTT_LOG(0, "\n");
		}
		STORE_PDU_RTT_LOG(0, "%02X ", StorePDUParam.RTS.RecordBuf[i]);
	}STORE_PDU_RTT_LOG(0, "\n");
	#endif	
	
	xTimerStart(Store_PDU_TimerHandle,0);
	
	return Ret_OK;	
}

/*******************************************************************************
 ** Brief : 请求上传场景指定目录数据
			基础场景数据和运动场景数据公用一个上传函数
 ** Input : @fDataClassify 数据类型
			@fUTC UTC，用于确定上传哪个目录
			@fPackSerial 包序号，从这个包号开始上传
			@flowControl 流控
 ** Return: 
 ** Call  : 
 ***************/
uint16_t Store_PDU_CatalogDataRTS(uint16 fDataClassify, uint32 fUTC, uint16 fPackSerial, uint8 flowControl)
{
	ble_msg_t bleMsg;
	uint32_t lCatalog;
	
	if(fDataClassify != StorePDUParam.DataClassify)
	/* 返回无效数据类型 */
	{
		bleMsg.id			= BLE_MSG_SEND;
		bleMsg.packet	= PROT_PACK_TRANS_DATA_RET;
		bleMsg.packet.att.load.content.parameter[0]	= 1;
		bleMsg.packet.att.flowControl				= flowControl;
        Mid_Ble_SendMsg(&bleMsg);		
		return Ret_Fail;
	}
	
	/* 查找目录，若找到，开始发送 */
	// 先查找RAM目录
	if(StorePDUParam.RamData.ValidFlg && (StorePDUParam.RamData.UTC == fUTC))
	{
		STORE_PDU_RTT_LOG(0, "Store_PDU_CatalogDataRTS ValidFlg = true \n");
		
		StorePDUParam.RTS.SendCnt = fPackSerial*StorePDUParam.RTS.EachSendLen;
		StorePDUParam.RTS.FlowCtrl = flowControl;

		if(StorePDUParam.RTS.SendCnt < StorePDUParam.RamData.DataLen)
		/* 参数有效，返回成功，并开始上传数据 */
		{
			bleMsg.id		= BLE_MSG_SEND;
			bleMsg.packet	= PROT_PACK_TRANS_DATA_RET;
			bleMsg.packet.att.load.content.parameter[0]	= 0;
			bleMsg.packet.att.flowControl				= flowControl;
			Mid_Ble_SendMsg(&bleMsg);
			
			xTimerStart(Store_PDU_TimerHandle,0);
			StorePDUParam.State = eStorePDUCatalogDataRTS;
			StorePDUParam.RamData.UploadFlg = true;			// 上传RAM目录置位
			return Ret_OK;					
		}
		else
		/* 返回无效包序号 */
		{
			bleMsg.id			= BLE_MSG_SEND;
			bleMsg.packet	= PROT_PACK_TRANS_DATA_RET;
			bleMsg.packet.att.load.content.parameter[0]	= 3;
			bleMsg.packet.att.flowControl				= flowControl;
			Mid_Ble_SendMsg(&bleMsg);
			return Ret_Fail;				
		}		
	}
	
	// 再查找存于FLASH的目录
	for(lCatalog = 0;lCatalog < StorePDUParam.CatalogNum;lCatalog++)
	{
		if(fUTC == StorePDUParam.Catalog[lCatalog].UTC)
		{
			StorePDUParam.RTS.SendCnt = fPackSerial*StorePDUParam.RTS.EachSendLen;
			StorePDUParam.RTS.FlowCtrl = flowControl;
			StorePDUParam.RTS.CurrCatalog = lCatalog;
			
			if(StorePDUParam.RTS.SendCnt < StorePDUParam.Catalog[lCatalog].DataLen)
			/* 参数有效，返回成功，并开始上传数据 */
			{
				bleMsg.id		= BLE_MSG_SEND;
				bleMsg.packet	= PROT_PACK_TRANS_DATA_RET;
				bleMsg.packet.att.load.content.parameter[0]	= 0;
				bleMsg.packet.att.flowControl				= flowControl;
				Mid_Ble_SendMsg(&bleMsg);
				
				xTimerStart(Store_PDU_TimerHandle,0);
				StorePDUParam.State = eStorePDUCatalogDataRTS;
				StorePDUParam.RamData.UploadFlg = false;			// 上传RAM目录清除
				return Ret_OK;					
			}
			else
			/* 返回无效包序号 */
			{
				bleMsg.id			= BLE_MSG_SEND;
				bleMsg.packet	= PROT_PACK_TRANS_DATA_RET;
				bleMsg.packet.att.load.content.parameter[0]	= 3;
				bleMsg.packet.att.flowControl				= flowControl;
				Mid_Ble_SendMsg(&bleMsg);
				return Ret_Fail;				
			}
		}	
	}
	
	/* 找不到对应UTC的目录，返回错误 */
	bleMsg.id			= BLE_MSG_SEND;
	bleMsg.packet	= PROT_PACK_TRANS_DATA_RET;
	bleMsg.packet.att.load.content.parameter[0]	= 2;
	bleMsg.packet.att.flowControl = flowControl;
	Mid_Ble_SendMsg(&bleMsg);
	
	return Ret_OK;	
}

// 删除所有场景数据
uint16_t Store_PDU_DeleteAll(uint8 flowControl)
{
	drERROR_CHECK("Store_PDU_DeleteAll", Ret_Fail);	// 检测app是否会使用此指令
	
	ble_msg_t bleMsg;
	
	/* 删除操作 */
//	Store_Step_CatalogAllUpload();	
//	Store_Hrd_CatalogAllUpload();	
//  ...	
	
	/* 返回删除成功指令 */
	bleMsg.id			= BLE_MSG_SEND;
	bleMsg.packet	= PROT_SCENE_TRANS_DELETE_ALL_RET;
	bleMsg.packet.att.load.content.parameter[0]	= 2;	// 不允许删除
	bleMsg.packet.att.flowControl = flowControl;
    Mid_Ble_SendMsg(&bleMsg);
	
	return Ret_OK;
}

// 删除指定场景数据
uint16_t Store_PDU_ClassifyDelete(uint16 fDataClassify, uint8 flowControl)
{
	drERROR_CHECK("Store_PDU_ClassifyDelete", Ret_Fail);	// 检测app是否会使用此指令
	
	ble_msg_t bleMsg;
	
	bleMsg.id			= BLE_MSG_SEND;
	bleMsg.packet	= PROT_SCENE_TRANS_DELETE_CLASS_RET;
	bleMsg.packet.att.load.content.parameter[0]	= (uint8)(fDataClassify >> 8);
	bleMsg.packet.att.load.content.parameter[1]	= (uint8)(fDataClassify);
	bleMsg.packet.att.load.content.parameter[2]	= 1;	/* 删除失败 */
	bleMsg.packet.att.flowControl		= flowControl;
    
	if(fDataClassify == StorePDUParam.DataClassify)
	/* 仅允许删除当前待上传的数据类型 */
	{
		Store_Algo_CatalogAllUpload(StorePDUParam.pPDUStoreInfo);
		bleMsg.packet.att.load.content.parameter[2]	= 0;	/* 删除成功 */		
	}
	
	Mid_Ble_SendMsg(&bleMsg);	
	
	return Ret_OK;
}

// APP下发指令删除此数据类型指定UTC数据（硬件FLASH数据标记为已上传）
uint16_t Store_PDU_UTCCatalogDelete(uint16 fDataClassify, uint32 UTC, uint8 flowControl)
{
	ble_msg_t bleMsg;

	bleMsg.id			= BLE_MSG_SEND;
	bleMsg.packet	= PROT_SCENE_TRANS_DELETE_CATALOG_RET;
	bleMsg.packet.att.load.content.parameter[0]	= (uint8)(fDataClassify >> 8);
	bleMsg.packet.att.load.content.parameter[1]	= (uint8)(fDataClassify);
	bleMsg.packet.att.load.content.parameter[2]	= (uint8)(UTC >> 24);
	bleMsg.packet.att.load.content.parameter[3]	= (uint8)(UTC >> 16);
	bleMsg.packet.att.load.content.parameter[4]	= (uint8)(UTC >> 8);
	bleMsg.packet.att.load.content.parameter[5]	= (uint8)(UTC);
	bleMsg.packet.att.load.content.parameter[6]	= 1;
	bleMsg.packet.att.flowControl		= flowControl;
	
	/* 删除RAM数据 */
	if(UTC == StorePDUParam.RamData.UTC)
	{
		switch (fDataClassify)
        {
        	case eDataClassifyStep:
				bleMsg.packet.att.load.content.parameter[6]	= 0;
				Store_Step_RamDataClear();	// 清除计步ram数据
        		break;
        	default :
        		break;
        }
	}
	
	if(fDataClassify == StorePDUParam.DataClassify)
	/* 仅允许删除当前待上传的数据类型 */
	{
		/* 查找指定UTC是否存在 */
		for(uint32_t i = 0;i < StorePDUParam.CatalogNum;i++)
		{
			if(StorePDUParam.Catalog[i].UTC == UTC)
			{
				bleMsg.packet.att.load.content.parameter[6]	= 0;	// 找到则返回删除成功
				Store_Algo_CatalogUpload(StorePDUParam.pPDUStoreInfo, StorePDUParam.Catalog[i].CatalogSerial);
				break;
			}
		}
	}
	
    Mid_Ble_SendMsg(&bleMsg);	
	
	return Ret_OK;
}





/*******************************************************************************
 ** Brief : 请求上传最近睡眠记录条目
 ** Input : @flowControl 流控
 ** Return: 
 ** Call  : 
 ***************/
uint16_t Store_PDU_SleepRecordCatalogRTS(uint8 flowControl)
{
	if(!StorePDUParam.InitFlg) drERROR_CHECK_RETURN_ERR("Store_PDU_SleepRecordCatalogRTS", Ret_NoInit);	
	
	ble_msg_t bleMsg;
	uint16_t		lCatalogNum;
	uint32_t 			lCatalogSerial;
	CatalogInfo_t		lCatalogInfo;	
	sleep_record_t 		lsleepRecord;
	
	Scene_Sleep_RecordGet(&lsleepRecord);
	
	Store_PDU_ParamInit();									// 清空之前数据，防止产生影响
	StorePDUParam.RamData.ValidFlg = false;					
	StorePDUParam.RamData.UploadFlg = false;
	StorePDUParam.pPDUStoreInfo = Store_SlpRcd_StoreInfoGet();
	StorePDUParam.CatalogNum = 0;
	StorePDUParam.DataClassify = eDataClassifySlpRcd;
	
	/* 遍历目录，看那些目录还没被上传，遍历结果保存在 StorePDUParam 结构体中 */
	lCatalogSerial = StorePDUParam.pPDUStoreInfo->CatalogSerialBegin;
	for(uint32_t i = 0;i < StorePDUParam.pPDUStoreInfo->CatalogSerialCnt;i++)
	{
		Store_Algo_CatalogRead(StorePDUParam.pPDUStoreInfo, lCatalogSerial, &lCatalogInfo);
		if(eCatalogMarkSealed == lCatalogInfo.Flash.Info.Mark)
		/* 读取目录信息，若目录MARK为未上传，则保存在 StorePDUParam 结构体中 */
		{
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].CatalogSerial = lCatalogSerial;
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].DataLen = lCatalogInfo.Flash.Info.DataLen;
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].DataAddr = lCatalogInfo.Flash.Info.DataAddr;
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].UTC = lCatalogInfo.User.Info.UTC;
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].ExtDataLen = lCatalogInfo.User.Info.ExtDataLen;
			StorePDUParam.CatalogNum++;
		}
		
		lCatalogSerial = Store_Algo_NextCatalogGet(StorePDUParam.pPDUStoreInfo, lCatalogSerial);	// 下一目录
	}
	
	lCatalogNum = StorePDUParam.CatalogNum;
	if(lsleepRecord.SleepDuration)
	/* 本地睡眠时长非零，说明存在RAM目录 */
	{
		StorePDUParam.RamData.ValidFlg = true;
		lCatalogNum++;
	}

	bleMsg.id = BLE_MSG_SEND;
	bleMsg.packet = PROT_SCENE_SLEEP_RECORD_CONTENT_RET;
	bleMsg.packet.att.load.content.parameter[0]	= (uint8)(lCatalogNum);
	bleMsg.packet.att.flowControl = flowControl;
	Mid_Ble_SendMsg(&bleMsg);
	
	return Ret_OK;	
}


/*******************************************************************************
 ** Brief : 请求上传睡眠档案数据
 ** Input : @fCatalog 目录序号 从0开始
			@flowControl 流控
 ** Return: 
 ** Call  : 
 ***************/
uint16_t Store_PDU_SleepRecordDataRTS(uint16_t fCatalog, uint8 flowControl)
{
	if(!StorePDUParam.InitFlg) drERROR_CHECK_RETURN_ERR("Store_PDU_SleepRecordDataRTS", Ret_NoInit);
	if(eDataClassifySlpRcd != StorePDUParam.DataClassify) drERROR_CHECK_RETURN_ERR("Store_PDU_SleepRecordDataRTS", Ret_InvalidParam);	
	
	ble_msg_t bleMsg;
	
	StorePDUParam.RTS.FlowCtrl = flowControl;
	
	if(fCatalog < StorePDUParam.CatalogNum)
	/* 从FLASH获取睡眠档案 */
	{
		Store_Algo_CatalogExtRead(StorePDUParam.pPDUStoreInfo, StorePDUParam.Catalog[fCatalog].CatalogSerial, (uint8_t*)&StorePDUParam.RamData.RAM.SleepRecord, sizeof(sleep_record_t));
	}
	else if((fCatalog == StorePDUParam.CatalogNum) && StorePDUParam.RamData.ValidFlg)
	/* fCatalog == StorePDUParam.CatalogNum，上传RAM目录信息 */
	{
		Scene_Sleep_RecordGet(&StorePDUParam.RamData.RAM.SleepRecord);
	}
	else
	{
		drERROR_CHECK_RETURN_ERR("Store_PDU_SleepRecordDataRTS_1", (Ret_InvalidParam));
	}
	
	/* 获取条目的睡眠记录信息1 RET（H002所用新睡眠） */
	bleMsg.id = BLE_MSG_SEND;
	bleMsg.packet = PROT_SCENE_SLEEP_RECORD_INFO_NEW_RET;
	bleMsg.packet.att.load.content.parameter[0]	= (uint8)(StorePDUParam.RamData.RAM.SleepRecord.StartUTC >> 24);
	bleMsg.packet.att.load.content.parameter[1]	= (uint8)(StorePDUParam.RamData.RAM.SleepRecord.StartUTC >> 16);
	bleMsg.packet.att.load.content.parameter[2]	= (uint8)(StorePDUParam.RamData.RAM.SleepRecord.StartUTC >> 8);
	bleMsg.packet.att.load.content.parameter[3]	= (uint8)(StorePDUParam.RamData.RAM.SleepRecord.StartUTC >> 0);
	bleMsg.packet.att.load.content.parameter[4]	= (uint8)(StorePDUParam.RamData.RAM.SleepRecord.StopUTC >> 24);
	bleMsg.packet.att.load.content.parameter[5]	= (uint8)(StorePDUParam.RamData.RAM.SleepRecord.StopUTC >> 16);
	bleMsg.packet.att.load.content.parameter[6]	= (uint8)(StorePDUParam.RamData.RAM.SleepRecord.StopUTC >> 8);
	bleMsg.packet.att.load.content.parameter[7]	= (uint8)(StorePDUParam.RamData.RAM.SleepRecord.StopUTC >> 0);
	bleMsg.packet.att.load.content.parameter[8]	= (uint8)(StorePDUParam.RamData.RAM.SleepRecord.SleepDuration >> 8);
	bleMsg.packet.att.load.content.parameter[9]	= (uint8)(StorePDUParam.RamData.RAM.SleepRecord.SleepDuration >> 0);
	bleMsg.packet.att.load.content.parameter[10]= (uint8)(StorePDUParam.RamData.RAM.SleepRecord.Quality);
	bleMsg.packet.att.flowControl = StorePDUParam.RTS.FlowCtrl++;
    Mid_Ble_SendMsg(&bleMsg);
	
	if(StorePDUParam.RamData.RAM.SleepRecord.SegmentCnt)
	/* 有睡眠分段信息，则上传 */
	{
		xTimerStart(Store_PDU_TimerHandle,0);
		StorePDUParam.State = eStorePDUSleepRecordRTS;
		StorePDUParam.RTS.SendCnt = 0;
	}
	
	return Ret_OK;
}

/*******************************************************************************
 ** Brief : 删除睡眠档案信息
 ** Input : @UTC 睡眠UTC
			@flowControl 流控
 ** Return: 
 ** Call  : 
 ***************/
uint16_t Store_PDU_SleepRecordDelete(uint32 UTC, uint8 flowControl)
{
	if(eDataClassifySlpRcd != StorePDUParam.DataClassify) drERROR_CHECK_RETURN_ERR("Store_PDU_SleepRecordDataRTS", Ret_InvalidParam);	
			
	ble_msg_t bleMsg;

	bleMsg.id			= BLE_MSG_SEND;
	bleMsg.packet	= PROT_SCENE_SLEEP_RECORD_DEL_ECHO;
	bleMsg.packet.att.load.content.parameter[0]	= (uint8)(UTC >> 24);
	bleMsg.packet.att.load.content.parameter[1]	= (uint8)(UTC >> 16);
	bleMsg.packet.att.load.content.parameter[2]	= (uint8)(UTC >> 8);
	bleMsg.packet.att.load.content.parameter[3]	= (uint8)(UTC);
	bleMsg.packet.att.load.content.parameter[4]	= 1;
	bleMsg.packet.att.flowControl		= flowControl;
	
	/* RAM目录 */
	if(StorePDUParam.RamData.RAM.SleepRecord.StartUTC == UTC)
	{
		bleMsg.packet.att.load.content.parameter[4]	= 0;
	}
	
	/* 查找指定UTC是否存在 */
	for(uint32_t i = 0;i < StorePDUParam.CatalogNum;i++)
	{
		if(StorePDUParam.Catalog[i].UTC == UTC)
		{
			bleMsg.packet.att.load.content.parameter[4]	= 0;	// 找到则返回删除成功
			Store_Algo_CatalogUpload(StorePDUParam.pPDUStoreInfo, StorePDUParam.Catalog[i].CatalogSerial);
			break;
		}
	}
	
    Mid_Ble_SendMsg(&bleMsg);	
	
	return Ret_OK;
}











