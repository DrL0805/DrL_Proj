/**********************************************************************
**
**ģ��˵��: �����洢��ʷģ�飬����UI��ʾ
			��ʷģ������˵��������ʷģ��ע������h002���˵����Ҫ�󣬶��˶���ʷ���ݽ��б������ʾ
			����H002�����Ҫ���˶���ʷ��FIFO��ʽ��ౣ��30��
**�޸���־��(�汾��ʱ�䣬���ݣ��޸���)
**   		V1.0   2018-11-22  ����  DrL
**
**********************************************************************/

#include "store_history.h"
#include "store_run.h"
#include "store_climb.h"
#include "store_swim.h"
#include "store_algo.h"

#include "bsp_common.h"


StoreHistoryParam_t		StoreHistoryParam;

/*******************************************************************************
 * Brief : ��ʼ����ʷģ��
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Store_History_Init(void)
{
	StoreHistoryParam.InitFlg = true;
	
	StoreHistoryParam.ListCnt = 0;
	StoreHistoryParam.ListPos = 0;
}

/*******************************************************************************
 * Brief : ����һ��������ʷ��¼
 * Input : @fStoreHistoryRecord	������¼�ṹ�� 
 * Return: @NULL
 * Call  : ��ÿ��������������Ҫ��ӵ��˶���ʷʱ����
 ***************/
void Store_History_ListAdd(StoreHistoryList_t* fStoreHistoryList)
{
	if(!StoreHistoryParam.InitFlg)
	{
		Store_History_Init();
	}

	memcpy(&StoreHistoryParam.ListBuf[StoreHistoryParam.ListPos], fStoreHistoryList, sizeof(StoreHistoryList_t));
	
	if(StoreHistoryParam.ListCnt < STORE_HISTORY_LIST_MAX)
	/* �洢�б�δ����+1 */
	{
		StoreHistoryParam.ListCnt++;
	}
	
	// ��ǰ�洢λ��NEXT
	StoreHistoryParam.ListPos = drCMN_CyclePosNext(STORE_HISTORY_LIST_MAX, StoreHistoryParam.ListPos, 1);
}

/*******************************************************************************
 * Brief : ��ȡĳ�˶���ʷ�б�ָ��
 * Input : @fSerial	��ţ���ŷ�Χ0~StoreHistoryParam.ListCnt��
			�����������ţ�Ĭ�Ϸ������0�Ĳ���
 * Return: @NULL
 * Call  : UI��ʾ�˶��б�ʱ����
 ***************/
StoreHistoryList_t* Store_History_ListPGet(uint8_t fSerial)
{
	uint8_t lTmpSerial;
	
	if(fSerial >= StoreHistoryParam.ListCnt)
	/* ��Ϊ������ţ��������[0]���б� */
	{
		drERROR_CHECK("Store_History_ListPGet", Ret_InvalidParam);
		return &StoreHistoryParam.ListBuf[0];
	}

	if(StoreHistoryParam.ListCnt < STORE_HISTORY_LIST_MAX)
	/* �б�洢δ����˵��δFIFOѭ����������洢λ��ΪBuf[0] */
	{
		return &StoreHistoryParam.ListBuf[fSerial];
	}
	else
	/* �б�洢������˵����FIFOѭ����������洢λ��ΪBuf[ListPos] */
	{
		lTmpSerial = drCMN_CyclePosNext(STORE_HISTORY_LIST_MAX, StoreHistoryParam.ListPos, fSerial);
		return &StoreHistoryParam.ListBuf[lTmpSerial];
	}
}

/*******************************************************************************
 * Brief : ��ȡĳ�˶���ʷ��ϸ������Ϣ����flash�ж�ȡ
 * Input : @fSerial	���
           @fStoreHistoryRecord �ṹ��ָ��
 * Return: @NULL
 * Call  : UI��ʾ�˶���ϸ��ʷʱ����
 ***************/
void Store_History_RecordGet(uint8_t fSerial, StoreHistoryRecord_t* fStoreHistoryRecord)
{
	StoreHistoryList_t* lStoreHistoryList;
	StoreInfo_t* lStoreInfo;
	CatalogInfo_t	lCatalog;
//	uint8_t 		lDataBuf[512];	
	
	// ��ȡ�˶���ʷlist��Ϣ
	lStoreHistoryList = Store_History_ListPGet(fSerial);
	fStoreHistoryRecord->DataClassify = lStoreHistoryList->DataClassify;	// ��ֵ��������

	switch (fStoreHistoryRecord->DataClassify)
    {
    	case eDataClassifyRunNew:
			lStoreInfo = Store_Run_StoreInfoGet();
			Store_Algo_CatalogRead(lStoreInfo, lStoreHistoryList->CatalogSerial, &lCatalog);
		
			#if 0 /* Ŀ¼��Ϣ */
			STORE_HISTORY_RTT_LOG(0, "Store_Algo_CatalogRead \n");
			STORE_HISTORY_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
			STORE_HISTORY_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
			STORE_HISTORY_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
			STORE_HISTORY_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
			STORE_HISTORY_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
			STORE_HISTORY_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
			#endif
			
			Store_Algo_CatalogExtRead(lStoreInfo, lStoreHistoryList->CatalogSerial, (uint8_t*)&fStoreHistoryRecord->Record.Run, lCatalog.User.Info.ExtDataLen);
			#if 0 /* Ŀ¼������Ϣ */
			STORE_HISTORY_RTT_LOG(0, "Store_Algo_CatalogExtRead \n");
			for(uint32_t t = 0;t < lCatalog.User.Info.ExtDataLen;t++)
			{
				if((0 == t%32) && (0 != t))
				{
					STORE_HISTORY_RTT_LOG(0, "\n");
				}
				STORE_HISTORY_RTT_LOG(0, "%02X ", lDataBuf[t]);
			}STORE_HISTORY_RTT_LOG(0, "\n");
			#endif
    		break;
    	case eDataClassifyClimbNew:
			lStoreInfo = Store_Climb_StoreInfoGet();
			Store_Algo_CatalogRead(lStoreInfo, lStoreHistoryList->CatalogSerial, &lCatalog);
			Store_Algo_CatalogExtRead(lStoreInfo, lStoreHistoryList->CatalogSerial, (uint8_t*)&fStoreHistoryRecord->Record.Climb, lCatalog.User.Info.ExtDataLen);			
    		break;
		case eDataClassifySwimNew:
			lStoreInfo = Store_Swim_StoreInfoGet();
			Store_Algo_CatalogRead(lStoreInfo, lStoreHistoryList->CatalogSerial, &lCatalog);
			Store_Algo_CatalogExtRead(lStoreInfo, lStoreHistoryList->CatalogSerial, (uint8_t*)&fStoreHistoryRecord->Record.Swim, lCatalog.User.Info.ExtDataLen);			
    		break;
    	default :
    		break;
    }
}

/*******************************************************************************
 * Brief : ��ȡ�洢��ʷ�ṹ�����ָ��
 * Input : @NULL
 * Return: @NULL
 * Call  : 
 ***************/
StoreHistoryParam_t* Store_History_ParamPGet(void)
{
	return &StoreHistoryParam;
}

void Store_History_Test(void)
{
	#if 1
	{
		StoreHistoryParam_t* lpStoreHistoryParam;
		StoreHistoryRecord_t lStoreHistoryRecord;
		
		lpStoreHistoryParam = Store_History_ParamPGet();
		STORE_HISTORY_RTT_LOG(0, "Store_History_ParamPGet ListCnt %d, ListPos %d \n", lpStoreHistoryParam->ListCnt, lpStoreHistoryParam->ListPos);
		
		for(uint32_t i = 0;i < lpStoreHistoryParam->ListCnt; i++)
		{
			Store_History_RecordGet(i, &lStoreHistoryRecord);
			#if 1	// ��ӡ�洢��Ŀ¼������Ϣ
			{
				switch(lStoreHistoryRecord.DataClassify)
				{
					case eDataClassifyRunNew:
						STORE_HISTORY_RTT_LOG(0, "eDataClassifyRunNew %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d \n",
							lStoreHistoryRecord.Record.Run.StartUTC, lStoreHistoryRecord.Record.Run.StopUTC, lStoreHistoryRecord.Record.Run.Duration,
							lStoreHistoryRecord.Record.Run.ValidDuration, lStoreHistoryRecord.Record.Run.Step, lStoreHistoryRecord.Record.Run.Distance,
							lStoreHistoryRecord.Record.Run.Calorie, lStoreHistoryRecord.Record.Run.PaceAVG, lStoreHistoryRecord.Record.Run.FreqAVG,
							lStoreHistoryRecord.Record.Run.StrideAVG, lStoreHistoryRecord.Record.Run.HrAVG, lStoreHistoryRecord.Record.Run.HrMax);						
						break;
					case eDataClassifyClimbNew:
						STORE_HISTORY_RTT_LOG(0, "eDataClassifyClimbNew %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d \n",
							lStoreHistoryRecord.Record.Climb.StartUTC, lStoreHistoryRecord.Record.Climb.StopUTC, lStoreHistoryRecord.Record.Climb.Duration,
							lStoreHistoryRecord.Record.Climb.Step, lStoreHistoryRecord.Record.Climb.Distance, lStoreHistoryRecord.Record.Climb.UpAltitude,
							lStoreHistoryRecord.Record.Climb.DownAltitude, lStoreHistoryRecord.Record.Climb.HighestAltitude, lStoreHistoryRecord.Record.Climb.LowestAltitude,
							lStoreHistoryRecord.Record.Climb.SpeedAVG, lStoreHistoryRecord.Record.Climb.Calorie, lStoreHistoryRecord.Record.Climb.HrAVG,
							lStoreHistoryRecord.Record.Climb.HrMax);						
						break;
					case eDataClassifySwimNew:
						STORE_HISTORY_RTT_LOG(0, "eDataClassifySwimNew %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d \n",
							lStoreHistoryRecord.Record.Swim.StartUTC, lStoreHistoryRecord.Record.Swim.StopUTC, lStoreHistoryRecord.Record.Swim.Duration, 
							lStoreHistoryRecord.Record.Swim.ValidDuration, lStoreHistoryRecord.Record.Swim.Distance, lStoreHistoryRecord.Record.Swim.Stroke, 
							lStoreHistoryRecord.Record.Swim.Calorie, lStoreHistoryRecord.Record.Swim.Laps, lStoreHistoryRecord.Record.Swim.PaceAVG, 
							lStoreHistoryRecord.Record.Swim.StrokeAVG, lStoreHistoryRecord.Record.Swim.StrokeRateAVG, lStoreHistoryRecord.Record.Swim.SwolfAvg, 
							lStoreHistoryRecord.Record.Swim.HrAVG, lStoreHistoryRecord.Record.Swim.HrMax, lStoreHistoryRecord.Record.Swim.Style);						
						break;
					default:
						break;
				}
			}
			#endif			
		}
	}
	#endif
}





