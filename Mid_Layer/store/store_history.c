/**********************************************************************
**
**模块说明: 场景存储历史模块，用于UI显示
			历史模块整体说明，此历史模块注意满足h002规格说明书要求，对运动历史数据进行保存和显示
			根据H002规格书要求，运动历史已FIFO方式最多保存30条
**修改日志：(版本，时间，内容，修改人)
**   		V1.0   2018-11-22  初版  DrL
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
 * Brief : 初始化历史模块
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
 * Brief : 增加一条场景历史记录
 * Input : @fStoreHistoryRecord	场景记录结构体 
 * Return: @NULL
 * Call  : 在每个场景结束后，需要添加到运动历史时调用
 ***************/
void Store_History_ListAdd(StoreHistoryList_t* fStoreHistoryList)
{
	if(!StoreHistoryParam.InitFlg)
	{
		Store_History_Init();
	}

	memcpy(&StoreHistoryParam.ListBuf[StoreHistoryParam.ListPos], fStoreHistoryList, sizeof(StoreHistoryList_t));
	
	if(StoreHistoryParam.ListCnt < STORE_HISTORY_LIST_MAX)
	/* 存储列表未满，+1 */
	{
		StoreHistoryParam.ListCnt++;
	}
	
	// 当前存储位置NEXT
	StoreHistoryParam.ListPos = drCMN_CyclePosNext(STORE_HISTORY_LIST_MAX, StoreHistoryParam.ListPos, 1);
}

/*******************************************************************************
 * Brief : 获取某运动历史列表指针
 * Input : @fSerial	序号，序号范围0~StoreHistoryParam.ListCnt，
			若传入错误序号，默认返回序号0的参数
 * Return: @NULL
 * Call  : UI显示运动列表时调用
 ***************/
StoreHistoryList_t* Store_History_ListPGet(uint8_t fSerial)
{
	uint8_t lTmpSerial;
	
	if(fSerial >= StoreHistoryParam.ListCnt)
	/* 若为错误序号，返回序号[0]的列表 */
	{
		drERROR_CHECK("Store_History_ListPGet", Ret_InvalidParam);
		return &StoreHistoryParam.ListBuf[0];
	}

	if(StoreHistoryParam.ListCnt < STORE_HISTORY_LIST_MAX)
	/* 列表存储未满，说明未FIFO循环过，最早存储位置为Buf[0] */
	{
		return &StoreHistoryParam.ListBuf[fSerial];
	}
	else
	/* 列表存储已满，说明已FIFO循环过，最早存储位置为Buf[ListPos] */
	{
		lTmpSerial = drCMN_CyclePosNext(STORE_HISTORY_LIST_MAX, StoreHistoryParam.ListPos, fSerial);
		return &StoreHistoryParam.ListBuf[lTmpSerial];
	}
}

/*******************************************************************************
 * Brief : 获取某运动历史详细档案信息，从flash中读取
 * Input : @fSerial	序号
           @fStoreHistoryRecord 结构体指针
 * Return: @NULL
 * Call  : UI显示运动详细历史时调用
 ***************/
void Store_History_RecordGet(uint8_t fSerial, StoreHistoryRecord_t* fStoreHistoryRecord)
{
	StoreHistoryList_t* lStoreHistoryList;
	StoreInfo_t* lStoreInfo;
	CatalogInfo_t	lCatalog;
//	uint8_t 		lDataBuf[512];	
	
	// 获取运动历史list信息
	lStoreHistoryList = Store_History_ListPGet(fSerial);
	fStoreHistoryRecord->DataClassify = lStoreHistoryList->DataClassify;	// 赋值数据类型

	switch (fStoreHistoryRecord->DataClassify)
    {
    	case eDataClassifyRunNew:
			lStoreInfo = Store_Run_StoreInfoGet();
			Store_Algo_CatalogRead(lStoreInfo, lStoreHistoryList->CatalogSerial, &lCatalog);
		
			#if 0 /* 目录信息 */
			STORE_HISTORY_RTT_LOG(0, "Store_Algo_CatalogRead \n");
			STORE_HISTORY_RTT_LOG(0, "  .Flash.Info.DataLen %d \n", lCatalog.Flash.Info.DataLen);
			STORE_HISTORY_RTT_LOG(0, "  .Flash.Info.DataAddr 0x%X \n", lCatalog.Flash.Info.DataAddr);
			STORE_HISTORY_RTT_LOG(0, "  .Flash.Info.Mark %d \n", lCatalog.Flash.Info.Mark);
			STORE_HISTORY_RTT_LOG(0, "  .User.Info.UTC %d \n", lCatalog.User.Info.UTC);
			STORE_HISTORY_RTT_LOG(0, "  .User.Info.DataClassify %d \n", lCatalog.User.Info.DataClassify);
			STORE_HISTORY_RTT_LOG(0, "  .User.Info.ExtDataLen %d \n", lCatalog.User.Info.ExtDataLen);
			#endif
			
			Store_Algo_CatalogExtRead(lStoreInfo, lStoreHistoryList->CatalogSerial, (uint8_t*)&fStoreHistoryRecord->Record.Run, lCatalog.User.Info.ExtDataLen);
			#if 0 /* 目录附加信息 */
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
 * Brief : 获取存储历史结构体参数指针
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
			#if 1	// 打印存储的目录附加信息
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





