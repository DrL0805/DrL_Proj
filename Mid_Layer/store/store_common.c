#include "store_common.h"
#include "store_part.h"
#include "app_variable.h"
#include "bsp_common.h"
#include "scene_alarm.h"
#include "scene_sedentary.h"
#include "mid_rtc.h"

// 根据逻辑地址，读取存储信息
void Store_Cmn_InfoRead(uint32_t LogAddr, uint8_t* pBuf, uint32_t Len)
{
	Mid_NandFlash_Read(pBuf, LogAddr, Len);
	
	#if 0	// debug
	for(uint32_t i = 0;i < Len;i++)
	{
		STORE_RTT_LOG(0, "%02X ", pBuf[i]);
	}STORE_RTT_LOG(0, "\r\n");
	#endif
}

// 系统配置信息读取更新到RAM
void Store_Cmn_SysInfoReadUpdate(void)
{
	uint8_t lBuf[256];
	uint8_t lIdStr[] = "DrL";
	
	/* 读取FLASH数据 */
	Store_Part_Read(eStorePart256B, 0, lBuf, 256);
	
	if(drCMN_ArrayCmp(lBuf, lIdStr, 3))
	/* 识别码匹配，说明存过数据，开始恢复 */
	{
		/* 系统语言 */
		if(lBuf[32] < eSysLangugeMax)	
		{
			gtSysCfg.systermLanguge = lBuf[32];
		}
		else
		{
			gtSysCfg.systermLanguge = SYS_ENGLISH_TYPE;
		}	

		/* 时间制式 */
		if(lBuf[33] < eSysTimeTypeMax)	
		{
			gtSysCfg.systermTimeType = lBuf[33];
		}
		else
		{
			gtSysCfg.systermTimeType = SYS_TIME_24_TYPE;
		}		
		
		/* 计步开关 */
		if(lBuf[34] < eSysSwitchMax)	
		{
			gtSysCfg.stepCountSwitch = lBuf[34];
		}
		else
		{
			gtSysCfg.stepCountSwitch = SWITCH_ON;
		}
		
		/* 心率开关 */
		if(lBuf[35] < eSysSwitchMax)	
		{
			gtSysCfg.heartrateSwitch = lBuf[35];
		}
		else
		{
			gtSysCfg.heartrateSwitch = SWITCH_ON;
		}	
		
		/* 天气预测开关 */
		if(lBuf[36] < eSysSwitchMax)	
		{
			gtSysCfg.weatherSwitch = lBuf[36];
		}
		else
		{
			gtSysCfg.weatherSwitch = SWITCH_OFF;
		}		
		
		/* 计步完成提醒开关 */
		if(lBuf[37] < eSysSwitchMax)	
		{
			gtSysCfg.stepCompleteRemindSwitch= lBuf[37];
		}
		else
		{
			gtSysCfg.stepCompleteRemindSwitch = SWITCH_ON;
		}	
		
		/* 蓝牙断开提醒开关 */
		if(lBuf[38] < eSysSwitchMax)	
		{
			gtSysCfg.bleDiscRemindSwitch = lBuf[38];
		}
		else
		{
			gtSysCfg.bleDiscRemindSwitch = SWITCH_ON;
		}	
		
		/* 久坐提醒开关 */
		if(lBuf[39] < eSysSwitchMax)	
		{
			gtSysCfg.longSitRemindSwitch = lBuf[39];
		}
		else
		{
			gtSysCfg.longSitRemindSwitch = SWITCH_ON;
		}	

		/* 消息免打扰开关 */
		if(lBuf[40] < eSysSwitchMax)	
		{
			gtSysCfg.notDisturbSwitch = lBuf[40];
		}
		else
		{
			gtSysCfg.notDisturbSwitch = SWITCH_ON;
		}	

		/* 手势识别开关 */
		if(lBuf[41] < eSysSwitchMax)	
		{
			gtSysCfg.gestureSwitch = lBuf[41];
		}
		else
		{
			gtSysCfg.gestureSwitch = SWITCH_ON;
		}		

		/* 消息提醒开关 */
		gtSysCfg.appRemindSwitch = (lBuf[42] << 0) | (lBuf[43] << 8) | (lBuf[44] << 16) | (lBuf[45] << 24);
		
		/* 详情提醒开关 */
		gtSysCfg.appDetailRemindSwitch = (lBuf[46] << 0) | (lBuf[47] << 8) | (lBuf[48] << 16) | (lBuf[49] << 24);
	}
}

// 系统配置信息写入更新到FLASH
void Store_Cmn_SysInfoWriteUpdate(void)
{
	uint8_t lBuf[256] = {'D', 'r', 'L'};
	
	lBuf[32] = gtSysCfg.systermLanguge;
	lBuf[33] = gtSysCfg.systermTimeType;
	lBuf[34] = gtSysCfg.stepCountSwitch;
	lBuf[35] = gtSysCfg.heartrateSwitch;
	lBuf[36] = gtSysCfg.weatherSwitch;
	lBuf[37] = gtSysCfg.stepCompleteRemindSwitch;
	lBuf[38] = gtSysCfg.bleDiscRemindSwitch;
	lBuf[39] = gtSysCfg.longSitRemindSwitch;
	lBuf[40] = gtSysCfg.notDisturbSwitch;
	lBuf[41] = gtSysCfg.gestureSwitch;
	lBuf[42] = (uint8_t)(gtSysCfg.appRemindSwitch >> 0);
	lBuf[43] = (uint8_t)(gtSysCfg.appRemindSwitch >> 8);
	lBuf[44] = (uint8_t)(gtSysCfg.appRemindSwitch >> 16);
	lBuf[45] = (uint8_t)(gtSysCfg.appRemindSwitch >> 24);
	lBuf[46] = (uint8_t)(gtSysCfg.appDetailRemindSwitch >> 0);
	lBuf[47] = (uint8_t)(gtSysCfg.appDetailRemindSwitch >> 8);
	lBuf[48] = (uint8_t)(gtSysCfg.appDetailRemindSwitch >> 16);
	lBuf[49] = (uint8_t)(gtSysCfg.appDetailRemindSwitch >> 24);
	
	Store_Part_Write(eStorePart256B, 0, lBuf, 256);
}

// 出厂信息读
void Store_Cmn_FactoryInfoReadUpdate(void)
{
	// 出厂信息在生产阶段固话，无需读到ram
}

// 出厂信息写
void Store_Cmn_FactoryInfoWriteUpdate(void)
{
	/* 出厂信息在生产阶段固话，不可写 */

	
	#if 0	// 写测试数据
	uint8_t * tpBuf = NULL;
	uint32_t tLogAddr = 0;

	/* 内存获取，并初始化 */
	tpBuf = pvPortMalloc(STORE_MAX_MALLOC_LEN);
	memset(tpBuf, 0xFF, STORE_MAX_MALLOC_LEN);
	
	/* 数据准备 */
	memcpy(tpBuf+STORE_FACTORY_ADDR_ID, StoreFactoryIdString, strlen(StoreFactoryIdString));	// 标识符
	memset(tpBuf+STORE_FACTORY_ADDR_SN, 0x66, 32);	// sn
	memset(tpBuf+STORE_FACTORY_ADDR_MAC, 0x77, 32);	// sn
	
	/* flash操作 */ 
	tLogAddr = LOG_ADDR_SET(STORE_BLOCK_FACTORY,0,0);
	Mid_NandFlash_Erase(tLogAddr, tLogAddr);	// 写前先擦除	
	Mid_NandFlash_Write(tpBuf, tLogAddr, STORE_MAX_MALLOC_LEN);	
	
	// 内存释放
	vPortFree(tpBuf);	
	#endif
}


// 时间信息读
void Store_Cmn_TimeInfoReadUpdate(void)
{
	uint8_t lBuf[256];
	uint8_t lIdStr[] = "DrL";
	SceneSedentaryParam_t* lpSedentary = Scene_Sedentary_ParamPGet();
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	
	/* 读取FLASH数据 */
	Store_Part_Read(eStorePart256B, 1, lBuf, 256);
	
	if(drCMN_ArrayCmp(lBuf, lIdStr, 3))
	/* 识别码匹配，说明存过数据，开始恢复 */
	{
		/* 本地时间 */
		if( (lBuf[32 + 1] <= 12) && 
			(lBuf[32 + 2] <= 31) && 
			(lBuf[32 + 3] <= 24) && 
			(lBuf[32 + 4] < 60) && 
			(lBuf[32 + 5] < 60) &&
			(lBuf[32 + 6] < eMidRTCWeekMax))
		{
			lMidRTC->RTC.year =  	lBuf[32 + 0];
			lMidRTC->RTC.month = 	(eMidRTCMonth)(lBuf[32 + 1]);
			lMidRTC->RTC.day = 	lBuf[32 + 2];
			lMidRTC->RTC.hour = 	lBuf[32 + 3];
			lMidRTC->RTC.min = 	lBuf[32 + 4];
			lMidRTC->RTC.sec = 	lBuf[32 + 5];
			lMidRTC->RTC.week = (eMidRTCWeek)(lBuf[32 + 6]);
			lMidRTC->RTC.zone =   (lBuf[32 + 7] << 8) | (lBuf[32 + 8]);
		}
		else
		{
			// 若flash读取数据有误，则为初始化默认值，无需重复配置
		}

		/* 世界时间 */
		if( (lBuf[48 + 1] <= 12) && 
			(lBuf[48 + 2] <= 31) && 
			(lBuf[48 + 3] <= 24) && 
			(lBuf[48 + 4] < 60) && 
			(lBuf[48 + 5] < 60) &&
			(lBuf[48 + 6] < eMidRTCWeekMax))
		{
			lMidRTC->WordRTC.year =  lBuf[48 + 0]; 
			lMidRTC->WordRTC.month = (eMidRTCMonth)(lBuf[48 + 1]);
			lMidRTC->WordRTC.day =   lBuf[48 + 2];
			lMidRTC->WordRTC.hour =  lBuf[48 + 3];
			lMidRTC->WordRTC.min =   lBuf[48 + 4];
			lMidRTC->WordRTC.sec =   lBuf[48 + 5];
			lMidRTC->WordRTC.week =  (eMidRTCWeek)(lBuf[48 + 6]);
			lMidRTC->WordRTC.zone = (lBuf[48 + 7] << 8) | (lBuf[48 + 8]);
		}
		else
		{
			// 若flash读取数据有误，则为初始化默认值，无需重复配置
		}
		
		/* 勿扰信息 */
		if( (lBuf[64 + 0] <= 24) && 
			(lBuf[64 + 1] <= 60) && 
			(lBuf[64 + 2] <= 24) && 
			(lBuf[64 + 3] <= 60))
		{
			appNotDisturdTimeInfo.StartHour = lBuf[64 + 0];
			appNotDisturdTimeInfo.StartMin =  lBuf[64 + 1];
			appNotDisturdTimeInfo.StopHour =  lBuf[64 + 2];
			appNotDisturdTimeInfo.StopMin =   lBuf[64 + 3];
		}
		else
		{
			// 若flash读取数据有误，则为初始化默认值，无需重复配置
		}
		
		/* 久坐信息 */
		if( (lBuf[80 + 0] <= 24) && 
			(lBuf[80 + 1] <= 60) && 
			(lBuf[80 + 2] <= 24) && 
			(lBuf[80 + 3] <= 60))
		{
			lpSedentary->Info.StartTimeHour = 			lBuf[80 + 0];
			lpSedentary->Info.StartTimeMin = 			lBuf[80 + 1];
			lpSedentary->Info.StopTimeHour = 			lBuf[80 + 2];
			lpSedentary->Info.StopTimeMin = 			lBuf[80 + 3];
			lpSedentary->Info.DisturdStartTimehour = 	lBuf[80 + 4];
			lpSedentary->Info.DisturdStartTimeMin = 	lBuf[80 + 5];
			lpSedentary->Info.DisturdStopTimehour = 	lBuf[80 + 6];
			lpSedentary->Info.DisturdStopTimeMin = 		lBuf[80 + 7];
			lpSedentary->Info.intv_mimute = 		   (lBuf[80 + 8] << 8) | (lBuf[80 + 9]);
		}
		else
		{
			// 若flash读取数据有误，则为初始化默认值，无需重复配置
		}

		/* 城市代号 */
		lMidRTC->cityCode = (lBuf[96 + 0] << 8) | (lBuf[96 + 0]);		
	}
}

// 时间信息写
void Store_Cmn_TimeInfoWriteUpdate(void)
{
	uint8_t lBuf[256] = {'D', 'r', 'L'};
	SceneSedentaryParam_t* lpSedentary = Scene_Sedentary_ParamPGet();
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	
	// 当地时间
	lBuf[32 + 0] = lMidRTC->RTC.year;
	lBuf[32 + 1] = lMidRTC->RTC.month;
	lBuf[32 + 2] = lMidRTC->RTC.day;
	lBuf[32 + 3] = lMidRTC->RTC.hour;
	lBuf[32 + 4] = lMidRTC->RTC.min;
	lBuf[32 + 5] = lMidRTC->RTC.sec;
	lBuf[32 + 6] = lMidRTC->RTC.week;
	lBuf[32 + 7] = lMidRTC->RTC.zone >> 8;
	lBuf[32 + 8] = lMidRTC->RTC.zone;
	
	// 世界时间
	lBuf[48 + 0] = lMidRTC->WordRTC.year;
	lBuf[48 + 1] = lMidRTC->WordRTC.month;
	lBuf[48 + 2] = lMidRTC->WordRTC.day;
	lBuf[48 + 3] = lMidRTC->WordRTC.hour;
	lBuf[48 + 4] = lMidRTC->WordRTC.min;
	lBuf[48 + 5] = lMidRTC->WordRTC.sec;
	lBuf[48 + 6] = lMidRTC->WordRTC.week;
	lBuf[48 + 7] = lMidRTC->WordRTC.zone >> 8;
	lBuf[48 + 8] = lMidRTC->WordRTC.zone;	

	// 勿扰信息
	lBuf[64 + 0] = appNotDisturdTimeInfo.StartHour;
	lBuf[64 + 1] = appNotDisturdTimeInfo.StartMin;
	lBuf[64 + 2] = appNotDisturdTimeInfo.StopHour;
	lBuf[64 + 3] = appNotDisturdTimeInfo.StopMin;	

	// 久坐信息
	lBuf[80 + 0] = lpSedentary->Info.StartTimeHour;
	lBuf[80 + 1] = lpSedentary->Info.StartTimeMin;
	lBuf[80 + 2] = lpSedentary->Info.StopTimeHour;
	lBuf[80 + 3] = lpSedentary->Info.StopTimeMin;
	lBuf[80 + 4] = lpSedentary->Info.DisturdStartTimehour;
	lBuf[80 + 5] = lpSedentary->Info.DisturdStartTimeMin;
	lBuf[80 + 6] = lpSedentary->Info.DisturdStopTimehour;
	lBuf[80 + 7] = lpSedentary->Info.DisturdStopTimeMin;
	lBuf[80 + 8] = lpSedentary->Info.intv_mimute >> 8;
	lBuf[80 + 9] = lpSedentary->Info.intv_mimute;
	
	// 城市代号
	lBuf[96 + 0] = lMidRTC->cityCode >> 8;
	lBuf[96 + 1] = lMidRTC->cityCode;		
	
	Store_Part_Write(eStorePart256B, 1, lBuf, 256);	
}


void Store_Cmn_AlarmInfoReadUpdate(void)
{
	uint8_t lBuf[256];
	uint8_t lIdStr[] = "DrL";
	alarm_clock_t tAlarm;
	uint8_t lAlarmLen = 16;
	
	/* 读取FLASH数据 */
	Store_Part_Read(eStorePart256B, 2, lBuf, 256);
	
	#if 0	// 打印读取的闹钟是否正确
	STORE_CMN_RTT_LOG(0, "Store_Cmn_AlarmInfoReadUpdate \n");
	for(uint32_t i = 0;i < SCENE_ALARM_MAX_ALARM_NUM;i++)
	{
		STORE_CMN_RTT_LOG(0, "Alarm %d: ", i);
		for(uint32_t t = 0;t < sizeof(alarm_clock_t);t++)
		{
			STORE_CMN_RTT_LOG(0, "%02X ", lBuf[32+i*lAlarmLen + t]);
		}STORE_CMN_RTT_LOG(0, "\n");
	}
	#endif
	
	if(drCMN_ArrayCmp(lBuf, lIdStr, 3))
	/* 识别码匹配，说明存过数据，开始恢复 */
	{
		for(uint32_t i = 0;i < SCENE_ALARM_MAX_ALARM_NUM;i++)
		{
			memcpy((uint8_t *)&tAlarm, lBuf+32+lAlarmLen*i, sizeof(alarm_clock_t));
			Scene_Alarm_Write(&tAlarm,i);		
		}
	}
}


void Store_Cmn_AlarmInfoWriteUpdate(void)
{
	alarm_clock_t tAlarm;
	uint8_t lBuf[256] = {'D', 'r', 'L'};
	uint8_t lAlarmLen = 16;

	for(uint32_t i = 0;i < SCENE_ALARM_MAX_ALARM_NUM;i++)
	{
		Scene_Alarm_Read(&tAlarm,i);
		memcpy(lBuf+32+lAlarmLen*i, (uint8_t *)&tAlarm, sizeof(alarm_clock_t));
	}
	
	#if 0	// 打印写入的闹钟是否正确
	STORE_CMN_RTT_LOG(0, "Store_Cmn_AlarmInfoWriteUpdate \n");
	for(uint32_t i = 0;i < SCENE_ALARM_MAX_ALARM_NUM;i++)
	{
		STORE_CMN_RTT_LOG(0, "Alarm %d: ", i);
		for(uint32_t t = 0;t < sizeof(alarm_clock_t);t++)
		{
			STORE_CMN_RTT_LOG(0, "%02X ", lBuf[32+i*lAlarmLen + t]);
		}STORE_CMN_RTT_LOG(0, "\n");
	}
	#endif
	
	Store_Part_Write(eStorePart256B, 2, lBuf, 256);	
}

void Store_Cmn_BodyInfoReadUpdate(void)
{
	uint8_t lBuf[256];
	uint8_t lIdStr[] = "DrL";
	
	/* 读取FLASH数据 */
	Store_Part_Read(eStorePart256B, 3, lBuf, 256);
	
	if(drCMN_ArrayCmp(lBuf, lIdStr, 3))
	/* 识别码匹配，说明存过数据，开始恢复 */
	{
		/* 身高 */
		gtBodyInfo.Height = lBuf[32];
		
		/* 体重 */
		gtBodyInfo.Weight = lBuf[33];
		
		/* 性别 */
		if(lBuf[34] < 2)	
		{
			gtBodyInfo.sex = lBuf[34];
		}
		else
		{
			gtBodyInfo.sex = 0;
		}
		
		/* 年龄 */
		gtBodyInfo.age = lBuf[35];
	}
}


void Store_Cmn_BodyInfoWriteUpdate(void)
{
	uint8_t lBuf[256] = {'D', 'r', 'L'};
	
	lBuf[32] = gtBodyInfo.Height;
	lBuf[33] = gtBodyInfo.Weight;
	lBuf[34] = gtBodyInfo.sex;
	lBuf[35] = gtBodyInfo.age;
	
	Store_Part_Write(eStorePart256B, 3, lBuf, 256);
}

void Store_Cmn_MacWrite(uint8_t* Buf, uint32_t Len)
{
	uint32_t tLogAddr;
	uint8_t* tpBuf;

	tpBuf= pvPortMalloc(STORE_MAX_MALLOC_LEN);
	
	tLogAddr = LOG_ADDR_SET(STORE_BLOCK_FACTORY,0,0);

	/* 先从flash读取page全部数据 */
	Mid_NandFlash_Read(tpBuf, tLogAddr, 2048);
	
	/* 在ram中修改数据 */
	memcpy(tpBuf + STORE_FACTORY_ADDR_MAC, Buf, Len);
	
	/* 再把所有数据全部写入ram中 */
	Mid_NandFlash_Erase(tLogAddr, tLogAddr);
	Mid_NandFlash_Write(tpBuf, tLogAddr, 2048);
	
	vPortFree(tpBuf);	
}

void Store_Cmn_MacRead(uint8_t* Buf, uint32_t Len)
{
	uint32_t tLogAddr = 0;

	/* flash操作 */ 
	tLogAddr = LOG_ADDR_SET(STORE_BLOCK_FACTORY,0,STORE_FACTORY_ADDR_MAC);
	Mid_NandFlash_Read(Buf, tLogAddr, Len);

	#if 0
	STORE_RTT_LOG(0, "Store_Cmn_MacRead:");
	for(uint32_t i = 0;i < Len;i++)
	{
		STORE_RTT_LOG(0, "%02X ", Buf[i]);
	}STORE_RTT_LOG(0, "\n");
	#endif		
}

void Store_Cmn_SnWrite(uint8_t* Buf, uint32_t Len)
{
	uint32_t tLogAddr;
	uint8_t* tpBuf;

	tpBuf= pvPortMalloc(STORE_MAX_MALLOC_LEN);
	
	tLogAddr = LOG_ADDR_SET(STORE_BLOCK_FACTORY,0,0);

	/* 先从flash读取page全部数据 */
	Mid_NandFlash_Read(tpBuf, tLogAddr, 2048);
	
	/* 在ram中修改数据 */
	memcpy(tpBuf + STORE_FACTORY_ADDR_SN, Buf, Len);
	
	/* 再把所有数据全部写入ram中 */
	Mid_NandFlash_Erase(tLogAddr, tLogAddr);
	Mid_NandFlash_Write(tpBuf, tLogAddr, 2048);
	
	vPortFree(tpBuf);	
}

void Store_Cmn_SnRead(uint8_t* Buf, uint32_t Len)
{
	uint32_t tLogAddr = 0;

	/* flash操作 */ 
	tLogAddr = LOG_ADDR_SET(STORE_BLOCK_FACTORY,0,STORE_FACTORY_ADDR_SN);
	Mid_NandFlash_Read(Buf, tLogAddr, Len);

	#if 0
	STORE_RTT_LOG(0, "Store_Cmn_SnRead:");
	for(uint32_t i = 0;i < Len;i++)
	{
		STORE_RTT_LOG(0, "%02X ", Buf[i]);
	}STORE_RTT_LOG(0, "\n");
	#endif		
}

void Store_Cmn_EventProcess(StoreCmnEvent_t* Event_t)
{
	switch(Event_t->Id)
	{
		case eStoreCmnEventSysInfoWrite:
			Store_Cmn_SysInfoWriteUpdate();
			break;
		case eStoreCmnEventTimeInfoWrite:
			Store_Cmn_TimeInfoWriteUpdate();
			break;
		case eStoreCmnEventAlarmInfoWrite:
			Store_Cmn_AlarmInfoWriteUpdate();
			break;
		case eStoreCmnEvenBodyInfoWrite:
			Store_Cmn_BodyInfoWriteUpdate();
			break;		
		default:
			break;	
	}
}





















