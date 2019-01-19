/**********************************************************************
**
**ģ��˵��: �����ϴ�ģ�飬����ͨ��Э��
**�޸���־��(�汾��ʱ�䣬���ݣ��޸���)
**   		V1.0   2018-12-08  ����  DrL
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
 ** Brief : ������ʼ�������㣩
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
 ** Brief : ��ȡĿ¼��Ϣ�������StorePDUParam�ṹ���У����ϴ���APP
 ** Input : @fDataClassify ��������
 ** Return: ���н��
 ** Call  : �ڲ�����
 ***************/
static uint16_t Store_PDU_CatalogGet(uint16_t fDataClassify)
{
	uint32_t 			lCatalogSerial;
	CatalogInfo_t		lCatalogInfo;	
	StoreStepParam_t* 	lStoreStepParam;
	
	Store_PDU_ParamInit();	// ���֮ǰ���ݣ���ֹ����Ӱ��
	StorePDUParam.RamData.ValidFlg = false;	// ÿ�������µ�Ŀ¼ǰ���Ȱ�RAMĿ¼��Ϊ��Ч
	StorePDUParam.RamData.UploadFlg = false;
	
	/* ��ȡ���ϴ����ݵĴ洢��Ϣ�ṹ�� */
	switch (fDataClassify)
	{
		case eDataClassifyStep:
			StorePDUParam.RTS.SampleUnit = STORE2_STEP_SAMPLE_INFO;
			StorePDUParam.RTS.ClassifyLen = STORE2_STEP_DATA_CLASSIFY_LEN;
			StorePDUParam.RTS.EachSendLen = (PDU_DATA_UPLOAD_MAX_LEN 
				/ StorePDUParam.RTS.ClassifyLen) * StorePDUParam.RTS.ClassifyLen;	// �ȳ��ٳ���Ϊ��ȡ��		
			StorePDUParam.pPDUStoreInfo = Store_Step_StoreInfoGet();
		
			/* RAM�����Ƿ���Ҫ�ϴ� */
			lStoreStepParam = Store_Step_ParamPGet();
			if(lStoreStepParam->LogCnt)
			/* ��RAM������Ҫ�ϴ� */
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
				/ StorePDUParam.RTS.ClassifyLen) * StorePDUParam.RTS.ClassifyLen;	// �ȳ��ٳ���Ϊ��ȡ��		
			StorePDUParam.pPDUStoreInfo = Store_Hrd_StoreInfoGet();
			break;
		case eDataClassifyBodytemp:
			StorePDUParam.RTS.SampleUnit = STORE2_BODYTEMP_SAMPLE_INFO;
			StorePDUParam.RTS.ClassifyLen = STORE2_BODYTEMP_DATA_CLASSIFY_LEN;
			StorePDUParam.RTS.EachSendLen = (PDU_DATA_UPLOAD_MAX_LEN 
				/ StorePDUParam.RTS.ClassifyLen) * StorePDUParam.RTS.ClassifyLen;	// �ȳ��ٳ���Ϊ��ȡ��		
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
	
	/* Ŀ¼Ϊ�գ���ȡʧ�� */
	if((0 == StorePDUParam.pPDUStoreInfo->CatalogSerialCnt) && !StorePDUParam.RamData.ValidFlg)
		return Ret_QueueEmpty;
	
	// ��ʼ�ϴ��Ĳ���
	StorePDUParam.AllDataLen = 0;
	StorePDUParam.CatalogNum = 0;
	StorePDUParam.DataClassify = fDataClassify;	
	
	/* ����Ŀ¼������ЩĿ¼��û���ϴ���������������� StorePDUParam �ṹ���� */
	lCatalogSerial = StorePDUParam.pPDUStoreInfo->CatalogSerialBegin;
	for(uint32_t i = 0;i < StorePDUParam.pPDUStoreInfo->CatalogSerialCnt;i++)
	{
		Store_Algo_CatalogRead(StorePDUParam.pPDUStoreInfo, lCatalogSerial, &lCatalogInfo);
		if(eCatalogMarkSealed == lCatalogInfo.Flash.Info.Mark)
		/* ��ȡĿ¼��Ϣ����Ŀ¼MARKΪδ�ϴ����򱣴��� StorePDUParam �ṹ���� */
		{
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].CatalogSerial = lCatalogSerial;
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].DataLen = lCatalogInfo.Flash.Info.DataLen;
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].DataAddr = lCatalogInfo.Flash.Info.DataAddr;
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].UTC = lCatalogInfo.User.Info.UTC;
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].ExtDataLen = lCatalogInfo.User.Info.ExtDataLen;
			StorePDUParam.CatalogNum++;
		}
		
		lCatalogSerial = Store_Algo_NextCatalogGet(StorePDUParam.pPDUStoreInfo, lCatalogSerial);	// ��һĿ¼
	}
	
	/* ��������Ŀ¼�������ݳ��� */
	for(uint32_t i = 0;i < StorePDUParam.CatalogNum;i++)
	{
		StorePDUParam.AllDataLen += StorePDUParam.Catalog[i].DataLen;
	}
	
	return Ret_OK;	
}

/*******************************************************************************
 ** Brief : ��ʱ����ʱ������
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
    	case eStorePDUCatalogDataRTS:	// ��������
			bleMsg.id		= BLE_MSG_SEND;
			bleMsg.packet	= PROT_PACK_TRANS_DATA_UPLOAD;
			bleMsg.packet.att.flowControl = StorePDUParam.RTS.FlowCtrl++;
		
			if(StorePDUParam.RamData.UploadFlg)
			/* RAMĿ¼ */
			{
				if((StorePDUParam.RTS.SendCnt + StorePDUParam.RTS.EachSendLen) >= StorePDUParam.RamData.DataLen)
				/* ���һ�� */
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
			/* FLASHĿ¼ */
			{
				if((StorePDUParam.RTS.SendCnt + StorePDUParam.RTS.EachSendLen) >= 
					StorePDUParam.Catalog[StorePDUParam.RTS.CurrCatalog].DataLen)
				/* ���һ�� */
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

			bleMsg.packet.att.load.content.parameter[0]	= (uint8)((StorePDUParam.RTS.SendCnt / StorePDUParam.RTS.EachSendLen) >> 8);	// ����
			bleMsg.packet.att.load.content.parameter[1]	= (uint8)(StorePDUParam.RTS.SendCnt / StorePDUParam.RTS.EachSendLen);	
			bleMsg.packet.att.load.content.parameter[2]	= (uint8)(StorePDUParam.DataClassify >> 8);	// ��������
			bleMsg.packet.att.load.content.parameter[3]	= (uint8)(StorePDUParam.DataClassify);
			bleMsg.packet.att.loadLength = ( lSendLen+ 7);		// 3�ӿ�֡+2���+2����+16��Ч����
			
			if(StorePDUParam.RamData.UploadFlg)
			/* RAMĿ¼����RAM��ȡ���ϴ����� */
			{
				memcpy(bleMsg.packet.att.load.content.parameter + 4, 
					StorePDUParam.RamData.RAM.DataBuf+StorePDUParam.RTS.SendCnt, lSendLen);
			}
			else
			/* FLASHĿ¼����FLASH��ȡ���ϴ������� */
			{
				lCatalogInfo.Flash.Info.DataAddr = StorePDUParam.Catalog[StorePDUParam.RTS.CurrCatalog].DataAddr;
				lCatalogInfo.Flash.Info.DataLen = StorePDUParam.Catalog[StorePDUParam.RTS.CurrCatalog].DataLen;
				
				Store_Algo_DataRead(StorePDUParam.pPDUStoreInfo, &lCatalogInfo, StorePDUParam.RTS.SendCnt, 
					bleMsg.packet.att.load.content.parameter + 4, lSendLen);
			}

			Mid_Ble_SendMsg(&bleMsg);
			
			StorePDUParam.RTS.SendCnt += lSendLen;	
    		break;
    	case eStorePDUCatalogDetailRTS:		// ����Ŀ¼
			bleMsg.id = BLE_MSG_SEND;
			bleMsg.packet = PROT_SCENE_TRANS_CATA_RET;
			bleMsg.packet.att.flowControl = StorePDUParam.RTS.FlowCtrl++;
			if((StorePDUParam.RTS.SendCnt + 10) >= StorePDUParam.RTS.RecordLen)
			/* ���һ�� */
			{
				lSendLen = StorePDUParam.RTS.RecordLen - StorePDUParam.RTS.SendCnt;
				bleMsg.packet.att.load.content.parameter[0] = 0xFF;	// ���һ������Ϊ0xFF
				xTimerStop(Store_PDU_TimerHandle,0);
				StorePDUParam.State = eStorePDUIdle;
			}
			else
			{
				lSendLen = 10;
				bleMsg.packet.att.load.content.parameter[0] = StorePDUParam.RTS.SendCnt / 10;
			}
			bleMsg.packet.att.loadLength += ( lSendLen+ 1);	// 1�ֽڵİ���
			memcpy(bleMsg.packet.att.load.content.parameter+1, StorePDUParam.RTS.RecordBuf+StorePDUParam.RTS.SendCnt, lSendLen);
			Mid_Ble_SendMsg(&bleMsg);
			
			StorePDUParam.RTS.SendCnt += lSendLen;	
    		break;
		case eStorePDUSleepRecordRTS:	// ����˯�ߵ���
			bleMsg.id = BLE_MSG_SEND;
			bleMsg.packet = PROT_SCENE_SLEEP_RECORD_INFO_NEW_ECHO;
			bleMsg.packet.att.flowControl = StorePDUParam.RTS.FlowCtrl++;
			bleMsg.packet.att.load.content.parameter[0] = StorePDUParam.RTS.SendCnt;
			bleMsg.packet.att.load.content.parameter[1] = (uint8_t)(StorePDUParam.RamData.RAM.SleepRecord.SleepData[StorePDUParam.RTS.SendCnt].State);
			bleMsg.packet.att.load.content.parameter[2] = (uint8_t)(StorePDUParam.RamData.RAM.SleepRecord.SleepData[StorePDUParam.RTS.SendCnt].Duration >> 8);
			bleMsg.packet.att.load.content.parameter[3] = (uint8_t)(StorePDUParam.RamData.RAM.SleepRecord.SleepData[StorePDUParam.RTS.SendCnt].Duration >> 0);
			if(StorePDUParam.RTS.SendCnt >= (StorePDUParam.RamData.RAM.SleepRecord.SegmentCnt-1))
			/* ��������0xFF */
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
 ** Brief : ģ���ʼ��
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
 ** Brief : �����ϴ�Ŀ¼������Ϣ
			����ͨ��Э�飬�������ݺ��˶��������ݣ�ͨ��Э���ʽ��һ����
 ** Input : @fDataClassify �������ͣ��Ʋ��ܲ���Ӿ��
			@flowControl ����
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
	/* Ŀ¼��ȡ�ɹ�������Ŀ¼��Ϣ */
	{
		if(StorePDUParam.RamData.ValidFlg)
		/* ����RAMĿ¼ */
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
	/* Ŀ¼��ȡʧ�ܣ�����0 */	
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
 ** Brief : ��ȡ������������ָ����ŵ�Ŀ¼��Ϣ
 ** Input : @fDataClassify ��������
			@fCatalog APP�����Ŀ¼��ţ�������Ŀ¼���
			@flowControl ����
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
	/* fCatalog == StorePDUParam.CatalogNum���ϴ�RAMĿ¼��Ϣ */
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
 ** Brief : ��ȡ�˶���������ָ����ŵ�Ŀ¼��Ϣ
 ** Input : @fDataClassify ��������
			@fCatalog APP�����Ŀ¼��ţ�������Ŀ¼���
			@flowControl ����
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
	
	// ��ȡĿ¼������Ϣ
	Store_Algo_CatalogExtRead(StorePDUParam.pPDUStoreInfo, StorePDUParam.Catalog[fCatalog].CatalogSerial, 
		lDataBuf, StorePDUParam.Catalog[fCatalog].ExtDataLen);
	
	#if 0	
	STORE_PDU_RTT_LOG(0, "sizeof(runningRecord_t) %d \n",sizeof(runningRecord_t));
	STORE_PDU_RTT_LOG(0, "sizeof(climbMountainRecord_t) %d \n",sizeof(climbMountainRecord_t));
	STORE_PDU_RTT_LOG(0, "sizeof(swimIndoorRecord_t) %d \n",sizeof(swimIndoorRecord_t));
	#endif
	
	#if 0	// ��ӡĿ¼������Ϣ
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
			/* ת��Ϊ�ṹ����Ϣ */
			memcpy((uint8_t*)&lrunningRecord, lDataBuf, StorePDUParam.Catalog[fCatalog].ExtDataLen);
			
			// ͨ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(fDataClassify >> 8);	// ��������
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(fDataClassify);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 24);	// ��ʼUTC
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(StorePDUParam.Catalog[fCatalog].DataLen >> 8);	// ���ݳ���
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(StorePDUParam.Catalog[fCatalog].DataLen);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_RUN_SAMPLE_INFO >> 8);	// ��������͵�λ 10��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_RUN_SAMPLE_INFO);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_RUN_DATA_CLASSIFY_LEN);	// ���ݵ�Ԫ����				
			
			// �ܲ�����
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StartUTC >> 24); // ��ʼʱ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StartUTC >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StartUTC >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StartUTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Duration >> 24); // ������ʱ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Duration >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Duration >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Duration);	
			memset(&StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen], 0x00, 20);	// ��1~5�׶γ���ʱ��
			StorePDUParam.RTS.RecordLen += 20;
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Distance >> 8); // �ܲ��ܾ���
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Distance);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Step >> 24); // �ܲ���
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Step >> 16);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Step >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Step);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Calorie >> 8); // �ܿ�·��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.Calorie);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StopUTC >> 24); // ����ʱ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StopUTC >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StopUTC >> 8);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StopUTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.ValidDuration >> 24); // ����Ч�ʱ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.ValidDuration >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.ValidDuration >> 8);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.ValidDuration);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.PaceAVG >> 8); // ƽ������
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.PaceAVG);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.FreqAVG >> 8); // ƽ����Ƶ
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.FreqAVG);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StrideAVG >> 8); // ƽ������
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.StrideAVG);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.HrAVG); // ƽ������
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lrunningRecord.HrMax); // �������			
    		break;
    	case eDataClassifyClimbNew:
			/* ת��Ϊ�ṹ����Ϣ */
			memcpy((uint8_t*)&lclimbMountainRecord, lDataBuf, StorePDUParam.Catalog[fCatalog].ExtDataLen);
			
			// ͨ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(fDataClassify >> 8);	// ��������
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(fDataClassify);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 24);	// ��ʼUTC
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(StorePDUParam.Catalog[fCatalog].DataLen >> 8);	// ���ݳ���
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(StorePDUParam.Catalog[fCatalog].DataLen);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_CLIMB_SAMPLE_INFO >> 8);	// ��������͵�λ 10��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_CLIMB_SAMPLE_INFO);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_CLIMB_DATA_CLASSIFY_LEN);	// ���ݵ�Ԫ����				
			
			// ��ɽ����
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.StartUTC >> 24); // ��ʼʱ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.StartUTC >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.StartUTC >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.StartUTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Duration >> 24); // ������ʱ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Duration >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Duration >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Duration);
			memset(&StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen], 0x00, 20);	// ��1~5�׶γ���ʱ��
			StorePDUParam.RTS.RecordLen += 20;
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.UpAltitude >> 8); // ��������
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.UpAltitude);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.DownAltitude >> 8); // �½�����
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.DownAltitude);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.HighestAltitude >> 8); // ��ߺ���
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.HighestAltitude);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.LowestAltitude >> 8); // ��ͺ���
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.LowestAltitude);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Calorie >> 8); // �ܿ�·��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Calorie);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.StopUTC >> 24); // ����ʱ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.StopUTC >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.StopUTC >> 8);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.StopUTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = 0;//(uint8)(lclimbMountainRecord.ValidDuration >> 24); // ����Ч�ʱ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = 0;//(uint8)(lclimbMountainRecord.ValidDuration >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = 0;//(uint8)(lclimbMountainRecord.ValidDuration >> 8);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = 0;//(uint8)(lclimbMountainRecord.ValidDuration);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Step >> 24); // �ܲ���
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Step >> 16);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Step >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Step);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Distance >> 8); // ��ɽ�ܾ���
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.Distance);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.SpeedAVG >> 8); // ƽ������
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.SpeedAVG);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.HrAVG); // ƽ������
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lclimbMountainRecord.HrMax); // �������				
    		break;
		case eDataClassifySwimNew:
			/* ת��Ϊ�ṹ����Ϣ */
			memcpy((uint8_t*)&lswimIndoorRecord, lDataBuf, StorePDUParam.Catalog[fCatalog].ExtDataLen);
			
			// ͨ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(fDataClassify >> 8);	// ��������
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(fDataClassify);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 24);	// ��ʼUTC
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8_t)(StorePDUParam.Catalog[fCatalog].UTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(StorePDUParam.Catalog[fCatalog].DataLen >> 8);	// ���ݳ���
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(StorePDUParam.Catalog[fCatalog].DataLen);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_SWIM_SAMPLE_INFO >> 8);	// ��������͵�λ 10��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_SWIM_SAMPLE_INFO);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(STORE2_SWIM_DATA_CLASSIFY_LEN);	// ���ݵ�Ԫ����				
			
			// ��Ӿ����
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StartUTC >> 24); // ��ʼʱ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StartUTC >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StartUTC >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StartUTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Duration >> 24); // ������ʱ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Duration >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Duration >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Duration);	
			memset(&StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen], 0x00, 20);	// ��1~5�׶γ���ʱ��
			StorePDUParam.RTS.RecordLen += 20;
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Stroke >> 8); // �ܻ�ˮ����
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Stroke);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Calorie >> 8); // �ܿ�·��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Calorie);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StopUTC >> 24); // ����ʱ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StopUTC >> 16);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StopUTC >> 8);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StopUTC);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.ValidDuration >> 24); // ��Ч�ʱ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.ValidDuration >> 16);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.ValidDuration >> 8);	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.ValidDuration);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Distance >> 8); // ��Ӿ�ܾ���
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Distance);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Laps >> 8); // ������
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Laps);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.PaceAVG >> 8); // ƽ���ٶ�
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.PaceAVG);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StrokeAVG >> 8); // ƽ����ˮ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StrokeAVG);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StrokeRateAVG >> 8); // ƽ����ˮ��
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.StrokeRateAVG);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.HrAVG); 			// ƽ������
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.HrMax); 			// �������	
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = 0;//(uint8)(lswimIndoorRecord.Swolf >> 8); 	// SWOLOF
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = 0;//(uint8)(lswimIndoorRecord.Swolf);
			StorePDUParam.RTS.RecordBuf[StorePDUParam.RTS.RecordLen++] = (uint8)(lswimIndoorRecord.Style);		// Ӿ��
    		break;
    	default :
    		break;		
    }
	
	#if 1	// debug����ӡ�������͵�Ŀ¼��Ϣ
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
 ** Brief : �����ϴ�����ָ��Ŀ¼����
			�����������ݺ��˶��������ݹ���һ���ϴ�����
 ** Input : @fDataClassify ��������
			@fUTC UTC������ȷ���ϴ��ĸ�Ŀ¼
			@fPackSerial ����ţ���������ſ�ʼ�ϴ�
			@flowControl ����
 ** Return: 
 ** Call  : 
 ***************/
uint16_t Store_PDU_CatalogDataRTS(uint16 fDataClassify, uint32 fUTC, uint16 fPackSerial, uint8 flowControl)
{
	ble_msg_t bleMsg;
	uint32_t lCatalog;
	
	if(fDataClassify != StorePDUParam.DataClassify)
	/* ������Ч�������� */
	{
		bleMsg.id			= BLE_MSG_SEND;
		bleMsg.packet	= PROT_PACK_TRANS_DATA_RET;
		bleMsg.packet.att.load.content.parameter[0]	= 1;
		bleMsg.packet.att.flowControl				= flowControl;
        Mid_Ble_SendMsg(&bleMsg);		
		return Ret_Fail;
	}
	
	/* ����Ŀ¼�����ҵ�����ʼ���� */
	// �Ȳ���RAMĿ¼
	if(StorePDUParam.RamData.ValidFlg && (StorePDUParam.RamData.UTC == fUTC))
	{
		STORE_PDU_RTT_LOG(0, "Store_PDU_CatalogDataRTS ValidFlg = true \n");
		
		StorePDUParam.RTS.SendCnt = fPackSerial*StorePDUParam.RTS.EachSendLen;
		StorePDUParam.RTS.FlowCtrl = flowControl;

		if(StorePDUParam.RTS.SendCnt < StorePDUParam.RamData.DataLen)
		/* ������Ч�����سɹ�������ʼ�ϴ����� */
		{
			bleMsg.id		= BLE_MSG_SEND;
			bleMsg.packet	= PROT_PACK_TRANS_DATA_RET;
			bleMsg.packet.att.load.content.parameter[0]	= 0;
			bleMsg.packet.att.flowControl				= flowControl;
			Mid_Ble_SendMsg(&bleMsg);
			
			xTimerStart(Store_PDU_TimerHandle,0);
			StorePDUParam.State = eStorePDUCatalogDataRTS;
			StorePDUParam.RamData.UploadFlg = true;			// �ϴ�RAMĿ¼��λ
			return Ret_OK;					
		}
		else
		/* ������Ч����� */
		{
			bleMsg.id			= BLE_MSG_SEND;
			bleMsg.packet	= PROT_PACK_TRANS_DATA_RET;
			bleMsg.packet.att.load.content.parameter[0]	= 3;
			bleMsg.packet.att.flowControl				= flowControl;
			Mid_Ble_SendMsg(&bleMsg);
			return Ret_Fail;				
		}		
	}
	
	// �ٲ��Ҵ���FLASH��Ŀ¼
	for(lCatalog = 0;lCatalog < StorePDUParam.CatalogNum;lCatalog++)
	{
		if(fUTC == StorePDUParam.Catalog[lCatalog].UTC)
		{
			StorePDUParam.RTS.SendCnt = fPackSerial*StorePDUParam.RTS.EachSendLen;
			StorePDUParam.RTS.FlowCtrl = flowControl;
			StorePDUParam.RTS.CurrCatalog = lCatalog;
			
			if(StorePDUParam.RTS.SendCnt < StorePDUParam.Catalog[lCatalog].DataLen)
			/* ������Ч�����سɹ�������ʼ�ϴ����� */
			{
				bleMsg.id		= BLE_MSG_SEND;
				bleMsg.packet	= PROT_PACK_TRANS_DATA_RET;
				bleMsg.packet.att.load.content.parameter[0]	= 0;
				bleMsg.packet.att.flowControl				= flowControl;
				Mid_Ble_SendMsg(&bleMsg);
				
				xTimerStart(Store_PDU_TimerHandle,0);
				StorePDUParam.State = eStorePDUCatalogDataRTS;
				StorePDUParam.RamData.UploadFlg = false;			// �ϴ�RAMĿ¼���
				return Ret_OK;					
			}
			else
			/* ������Ч����� */
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
	
	/* �Ҳ�����ӦUTC��Ŀ¼�����ش��� */
	bleMsg.id			= BLE_MSG_SEND;
	bleMsg.packet	= PROT_PACK_TRANS_DATA_RET;
	bleMsg.packet.att.load.content.parameter[0]	= 2;
	bleMsg.packet.att.flowControl = flowControl;
	Mid_Ble_SendMsg(&bleMsg);
	
	return Ret_OK;	
}

// ɾ�����г�������
uint16_t Store_PDU_DeleteAll(uint8 flowControl)
{
	drERROR_CHECK("Store_PDU_DeleteAll", Ret_Fail);	// ���app�Ƿ��ʹ�ô�ָ��
	
	ble_msg_t bleMsg;
	
	/* ɾ������ */
//	Store_Step_CatalogAllUpload();	
//	Store_Hrd_CatalogAllUpload();	
//  ...	
	
	/* ����ɾ���ɹ�ָ�� */
	bleMsg.id			= BLE_MSG_SEND;
	bleMsg.packet	= PROT_SCENE_TRANS_DELETE_ALL_RET;
	bleMsg.packet.att.load.content.parameter[0]	= 2;	// ������ɾ��
	bleMsg.packet.att.flowControl = flowControl;
    Mid_Ble_SendMsg(&bleMsg);
	
	return Ret_OK;
}

// ɾ��ָ����������
uint16_t Store_PDU_ClassifyDelete(uint16 fDataClassify, uint8 flowControl)
{
	drERROR_CHECK("Store_PDU_ClassifyDelete", Ret_Fail);	// ���app�Ƿ��ʹ�ô�ָ��
	
	ble_msg_t bleMsg;
	
	bleMsg.id			= BLE_MSG_SEND;
	bleMsg.packet	= PROT_SCENE_TRANS_DELETE_CLASS_RET;
	bleMsg.packet.att.load.content.parameter[0]	= (uint8)(fDataClassify >> 8);
	bleMsg.packet.att.load.content.parameter[1]	= (uint8)(fDataClassify);
	bleMsg.packet.att.load.content.parameter[2]	= 1;	/* ɾ��ʧ�� */
	bleMsg.packet.att.flowControl		= flowControl;
    
	if(fDataClassify == StorePDUParam.DataClassify)
	/* ������ɾ����ǰ���ϴ����������� */
	{
		Store_Algo_CatalogAllUpload(StorePDUParam.pPDUStoreInfo);
		bleMsg.packet.att.load.content.parameter[2]	= 0;	/* ɾ���ɹ� */		
	}
	
	Mid_Ble_SendMsg(&bleMsg);	
	
	return Ret_OK;
}

// APP�·�ָ��ɾ������������ָ��UTC���ݣ�Ӳ��FLASH���ݱ��Ϊ���ϴ���
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
	
	/* ɾ��RAM���� */
	if(UTC == StorePDUParam.RamData.UTC)
	{
		switch (fDataClassify)
        {
        	case eDataClassifyStep:
				bleMsg.packet.att.load.content.parameter[6]	= 0;
				Store_Step_RamDataClear();	// ����Ʋ�ram����
        		break;
        	default :
        		break;
        }
	}
	
	if(fDataClassify == StorePDUParam.DataClassify)
	/* ������ɾ����ǰ���ϴ����������� */
	{
		/* ����ָ��UTC�Ƿ���� */
		for(uint32_t i = 0;i < StorePDUParam.CatalogNum;i++)
		{
			if(StorePDUParam.Catalog[i].UTC == UTC)
			{
				bleMsg.packet.att.load.content.parameter[6]	= 0;	// �ҵ��򷵻�ɾ���ɹ�
				Store_Algo_CatalogUpload(StorePDUParam.pPDUStoreInfo, StorePDUParam.Catalog[i].CatalogSerial);
				break;
			}
		}
	}
	
    Mid_Ble_SendMsg(&bleMsg);	
	
	return Ret_OK;
}





/*******************************************************************************
 ** Brief : �����ϴ����˯�߼�¼��Ŀ
 ** Input : @flowControl ����
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
	
	Store_PDU_ParamInit();									// ���֮ǰ���ݣ���ֹ����Ӱ��
	StorePDUParam.RamData.ValidFlg = false;					
	StorePDUParam.RamData.UploadFlg = false;
	StorePDUParam.pPDUStoreInfo = Store_SlpRcd_StoreInfoGet();
	StorePDUParam.CatalogNum = 0;
	StorePDUParam.DataClassify = eDataClassifySlpRcd;
	
	/* ����Ŀ¼������ЩĿ¼��û���ϴ���������������� StorePDUParam �ṹ���� */
	lCatalogSerial = StorePDUParam.pPDUStoreInfo->CatalogSerialBegin;
	for(uint32_t i = 0;i < StorePDUParam.pPDUStoreInfo->CatalogSerialCnt;i++)
	{
		Store_Algo_CatalogRead(StorePDUParam.pPDUStoreInfo, lCatalogSerial, &lCatalogInfo);
		if(eCatalogMarkSealed == lCatalogInfo.Flash.Info.Mark)
		/* ��ȡĿ¼��Ϣ����Ŀ¼MARKΪδ�ϴ����򱣴��� StorePDUParam �ṹ���� */
		{
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].CatalogSerial = lCatalogSerial;
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].DataLen = lCatalogInfo.Flash.Info.DataLen;
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].DataAddr = lCatalogInfo.Flash.Info.DataAddr;
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].UTC = lCatalogInfo.User.Info.UTC;
			StorePDUParam.Catalog[StorePDUParam.CatalogNum].ExtDataLen = lCatalogInfo.User.Info.ExtDataLen;
			StorePDUParam.CatalogNum++;
		}
		
		lCatalogSerial = Store_Algo_NextCatalogGet(StorePDUParam.pPDUStoreInfo, lCatalogSerial);	// ��һĿ¼
	}
	
	lCatalogNum = StorePDUParam.CatalogNum;
	if(lsleepRecord.SleepDuration)
	/* ����˯��ʱ�����㣬˵������RAMĿ¼ */
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
 ** Brief : �����ϴ�˯�ߵ�������
 ** Input : @fCatalog Ŀ¼��� ��0��ʼ
			@flowControl ����
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
	/* ��FLASH��ȡ˯�ߵ��� */
	{
		Store_Algo_CatalogExtRead(StorePDUParam.pPDUStoreInfo, StorePDUParam.Catalog[fCatalog].CatalogSerial, (uint8_t*)&StorePDUParam.RamData.RAM.SleepRecord, sizeof(sleep_record_t));
	}
	else if((fCatalog == StorePDUParam.CatalogNum) && StorePDUParam.RamData.ValidFlg)
	/* fCatalog == StorePDUParam.CatalogNum���ϴ�RAMĿ¼��Ϣ */
	{
		Scene_Sleep_RecordGet(&StorePDUParam.RamData.RAM.SleepRecord);
	}
	else
	{
		drERROR_CHECK_RETURN_ERR("Store_PDU_SleepRecordDataRTS_1", (Ret_InvalidParam));
	}
	
	/* ��ȡ��Ŀ��˯�߼�¼��Ϣ1 RET��H002������˯�ߣ� */
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
	/* ��˯�߷ֶ���Ϣ�����ϴ� */
	{
		xTimerStart(Store_PDU_TimerHandle,0);
		StorePDUParam.State = eStorePDUSleepRecordRTS;
		StorePDUParam.RTS.SendCnt = 0;
	}
	
	return Ret_OK;
}

/*******************************************************************************
 ** Brief : ɾ��˯�ߵ�����Ϣ
 ** Input : @UTC ˯��UTC
			@flowControl ����
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
	
	/* RAMĿ¼ */
	if(StorePDUParam.RamData.RAM.SleepRecord.StartUTC == UTC)
	{
		bleMsg.packet.att.load.content.parameter[4]	= 0;
	}
	
	/* ����ָ��UTC�Ƿ���� */
	for(uint32_t i = 0;i < StorePDUParam.CatalogNum;i++)
	{
		if(StorePDUParam.Catalog[i].UTC == UTC)
		{
			bleMsg.packet.att.load.content.parameter[4]	= 0;	// �ҵ��򷵻�ɾ���ɹ�
			Store_Algo_CatalogUpload(StorePDUParam.pPDUStoreInfo, StorePDUParam.Catalog[i].CatalogSerial);
			break;
		}
	}
	
    Mid_Ble_SendMsg(&bleMsg);	
	
	return Ret_OK;
}











