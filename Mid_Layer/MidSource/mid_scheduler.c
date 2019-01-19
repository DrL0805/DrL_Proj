/**********************************************************************
**
**模块说明: mid层任务调度接口
**修改日志：(版本，时间，内容，修改人)
**   		V1.0   2018-12-5  初版  DrL
**
**********************************************************************/
// 模块内部头文件包含
#include "mid_scheduler.h"
#include "mid_interface.h"

// 模块外部头文件包含
#include "scene_interface.h"
#include "store_interface.h"
#include "app_remind_manage.h"
#include "app_variable.h"
#include "app_protocal.h"
#include "app_lcd.h"
#include "app_systerm.h"

//yangrui add
#include "ui_keyhandle_main.h"
#include "ui_tphandle_main.h"
#include "ui_screen_other.h"


#if 1	// 测试用临时头文件
#include "drv_bm43.h"
#include "drv_gps.h"
#include "drv_ntc.h"
#endif

static QueueHandle_t 	sSchd_QueueHandle = NULL;				// 队列句柄 fefe 
#define		SCHD_TASK_QUEUE_LENGTH			32			// 
#define 	SCHD_TASK_QUEUE_WAIT_TICK		100			// 队列阻塞时间
#define		SCHD_TASK_QUEUE_SIZE			sizeof(Mid_Schd_TaskMsg_T)

//static TimerHandle_t 	MidSchd_TimerHandle;

// 外部变量
SemaphoreHandle_t	SPI_I2C_M0_SemaphoreHandle;		// flash / 字库，ok

//static void MidSchd_TimerCallBack(TimerHandle_t xTimer)
//{
//	static uint32_t stCnt = 0;
//	
//	MID_SCHD_RTT_LOG(0, "MidSchd_Timer %d \n", stCnt);
//}

void Mid_Mag_EventProcess(MagEvent_t* Event_t)
{
	switch(Event_t->Id)
	{
		case eMagEventDataUpdate:
			Mid_Mag_DataUpdate();
			/* 通知算法模块 */ 
			SceneTaskMsg_t 	tAlgoMsg;
			tAlgoMsg.Id = eAlgoTaskMsgMagnetism;
			Scene_Task_TaskEventSet(&tAlgoMsg);
			break;
		case eMagEventStartSample:
			Mid_Mag_StartSample();
			break;
		case eMagEventStopSample:
			Mid_Mag_StopSample();
			break;		
		default:
			break;	
	}
}

void Mid_Press_EventProcess(PressEvent_t* Event_t)
{
//	MID_PRESS_RTT_LOG(0, "Mid_Press_EventProcess %d \n", Event_t->Id);
	
	MID_PRESS_PARA_T*  MidPressParam = Mid_Press_ParamPGet();
	
	switch(Event_t->Id)
	{
		case ePressEventDataUpdate:
			switch (MidPressParam->SampleType)
            {
				case eMidPressSampleTempPress:
					Mid_Press_TempUpdate();
					Mid_Press_PressUpdate();
//					/* 通知算法模块 */
//					SceneTaskMsg_t 	tAlgoMsg;
//					tAlgoMsg.Id = eAlgoTaskMsgPressure;
//					Scene_Task_TaskEventSet(&tAlgoMsg);				
					break;
				case eMidPressSampleTemp:
//					Mid_Press_TempUpdate();
					break;
				case eMidPressSamplePress:
//					Mid_Press_PressUpdate();
					break;
				default: 
					break;
            }
			break;
		case ePressEventStartSample:
			Mid_Press_PressStart();
			break;			
		default:
			break;	
	}	
}

void Mid_ITemp_EventProcess(ITempEvent_t* Event_t)
{
	MID_IT_RTT_LOG(0, "Mid_ITemp_EventProcess %d \n", Event_t->Id);
	
	switch(Event_t->Id)
	{
		case eITempEventDataUpdate:
			Mid_IT_TempCal();
			break;
		case eITempEventStartSample:
			Mid_IT_ConverStart();
			break;
		case eITempEventStopSample:
			Mid_IT_ConverStop();
			break;		
		default:
			break;	
	}	
}

void Mid_Bat_EventProcess(BatEvent_t* Event_t)
{
//	MID_BAT_RTT_LOG(0, "Mid_Bat_EventProcess %d \n", Event_t->Id);
	uint8_t lBatSoc = 0;
	
	switch(Event_t->Id)
	{
		case eBatEventBatCheck:		// 剩余电量检测，1分钟1次
			Mid_Bat_BatCheck();
			#if 1
			Mid_Bat_SocRead(&lBatSoc);
			MID_BAT_RTT_LOG(0, "Mid_Bat_SocRead %d \n", lBatSoc);
			#endif
			break;
		case eBatEventChargCheck:	// 充电检测，1秒1次
			Mid_Bat_ChargCheck();
			break;
		case eBatEventStatusChange:
			MID_BAT_RTT_LOG(0, "eBatEventStatusChange %d \n", Event_t->BatStatus);
			switch (Event_t->BatStatus)
			{
				case MID_BAT_OFF_CHARGE:
					UI_Screen_Charging_Exit();
					break;
				case MID_BAT_IN_CHARGING:
				case MID_BAT_FULL_CHARGE:
					UI_Commom_Lockinfo_Reset();	// 先解除锁屏，否则锁屏界面无法进入充电界面
					UI_Screen_Charging_Show();
					break;
				case MID_BAT_LOW_LEVEL:
					if(eAppSysStateNormal == App_Sys_StateGet())
					/* 正常模式才有低电提醒，否则UI程序会卡死 */
					{
						UI_Screen_Show_Warn_Screen_Lowpower();
					}
					break;
				case MID_BAT_LOW_ALERT:
					break;
				default :
					drERROR_CHECK("Mid_Bat_StatusChange", Ret_InvalidParam);
					break;
			}
			break;
		default:
			break;	
	}
}

//**********************************************************************
// 函数功能: 按键调度任务处理函数
// 输入参数：
// 返回参数：
//static font_para_t	FontPram; 


uint8_t stFlashWriteBuf[2177], stFlashReadBuf[2177];
static void KeyTest(void)
{
	
	#if 0	// 
	App_Var_Test();
	#endif
	
	#if 0	// GPS解析
	char* GPGSV0 = "$GPGSV,3,1,12,03,19,305,20,04,20,181,,10,10,169,30,14,68,073,38*70";
	char* GPGSV1 = "$GPGSV,3,2,12,16,48,226,42,22,30,285,26,25,,,21,26,75,268,40*42";
	char* GPGSV2 = "$GPGSV,3,3,12,27,06,188,29,29,21,063,36,31,47,010,21,32,52,115,41*7E";
	char* GPRMC = "$GPRMC,120726.00,A,2235.1195,N,11352.0901,E,0.0,215.2,121118,,,A*56";
	
	Drv_GPS_InfoParse((char *)GPGSV0);	vTaskDelay(100);
	Drv_GPS_InfoParse((char *)GPGSV1);	vTaskDelay(100);
	Drv_GPS_InfoParse((char *)GPGSV2);	vTaskDelay(100);
	Drv_GPS_InfoParse((char *)GPRMC);	vTaskDelay(100);
	
	UI_Set_Curr_ScreenID(Common_Screen_MainID_Test);
	UI_Screen_draw_Screen();	
	#endif
	
	#if 0	// 栈溢出勾股函数测试
	uint8_t buf[2048];
	
	for(uint32_t i = 2047; i > 0; i--)
	{
		buf[i] = 0x55;
		vTaskDelay(1);
	}	
	#endif
	
	#if 0	/// 内存申请失败勾股函数测试
	
	for(uint32_t i = 0;i < 1024;i++)
	{
		pvPortMalloc(1024);
	}
	
	#endif
	
	#if 0
	static bool lInitFlg = false;
	if(!lInitFlg)
	{
		lInitFlg = true;
		UI_Set_Curr_ScreenID(Common_Screen_MainID_Test);
		UI_Screen_draw_Screen();		
	}
	else
	{
		UI_Screen_draw_Screen();
	}

	#endif
	
	#if 0	// 罗盘场景测试
//	Scene_ABC_CompassCalibrationStart();
	Scene_ABC_CompassEnable();
	#endif
	
	#if 0	// LCD硬件定时器测试
	static uint32_t lsTimer = 0;
	static bool lsFlg = false;
	
	lsTimer += 250;
	lsTimer = lsTimer % 3000;	
	if(!lsFlg)
	{
		lsFlg = true;
		App_Lcd_HardTimerStart(lsTimer);
		MID_SCHD_RTT_LOG(0, "App_Lcd_HardTimerStart %d \n",lsTimer);
	}
	else
	{
		lsFlg = false;
		App_Lcd_HardTimerStop();
		MID_SCHD_RTT_LOG(0, "App_Lcd_HardTimerStop %d \n",lsTimer);
	}
	
	
	
//void App_Lcd_HardTimerStop(void);	
	#endif
	
	#if 0	// 背光等级调节
	static uint8_t tDuty = 0;
	
	tDuty += 10;
	tDuty = tDuty % 110;
	Mid_Lcd_BLDutySet(tDuty);
	MID_SCHD_RTT_LOG(0, "Mid_Lcd_BLDutySet %d \n",tDuty);
	#endif
	
	#if 0
	App_Lcd_Test();
	#endif
	
	#if 1	// TP复位
//	Drv_Touch_Wakeup();
	#endif
	
	#if 0	// 提醒测试
	UI_Screen_Warn_Test();
	#endif
	
	#if 0 	// NTC 体温
	Drv_NTC_StartSample();
	#endif
	
	#if 0  // 消息提醒存储
//	MID_SCHD_RTT_LOG(0, "sizeof(RemindMsg_t) %d \n",sizeof(RemindMsg_t));
	
	RemindStore_t	tRemindStore;
	RemindMsg_t	tRemindMsg;
	
	App_RemindManage_DetailRemindRead(&tRemindStore);
	
	MID_SCHD_RTT_LOG(0, "tRemindStore: RemindCnt %d, FirstPos %d \n",tRemindStore.RemindCnt, tRemindStore.FirstPos);
	
	for(uint32_t i = 0;i < tRemindStore.RemindCnt;i++)
	{
		App_RemindManag_StoreGet(i, &tRemindMsg);
		MID_SCHD_RTT_LOG(0, "tRemindMsg.RemindType %d ",tRemindMsg.RemindType);
		MID_SCHD_RTT_LOG(0,"20%d/%d/%d %02d:%02d:%02d \r\n",tRemindMsg.RTC.year, tRemindMsg.RTC.month, tRemindMsg.RTC.day, tRemindMsg.RTC.hour, tRemindMsg.RTC.min, tRemindMsg.RTC.sec);
	}
	
	#endif
	
	
	#if 0	// 模拟收到蓝牙消息
    ble_msg_t ble_msg;

    ble_msg.id = BLE_MSG_RECEIVE;
	ble_msg.packet	= PROT_PACK_TRANS_DATA_UPLOAD;
    Ble_SendMsgToQueue(&ble_msg);	
	#endif
	
	#if 0 // 字节顺序测试
	
	typedef struct
	{
		uint8_t u8[2];
		bool	ubool;
		uint16_t u16;
		uint32_t u322;
		bool	ubooll;
	}Struct_t;
	
	uint32_t tu32Buf[8] = {0x11223344, 0x55667788};
	uint8_t tu8Buf[32];
	Struct_t tStruct;
	
	memcpy(tu8Buf, (uint8_t*)tu32Buf, 6);
	for(uint32_t i = 0;i < 6;i++)
	{
		MID_SCHD_RTT_LOG(0, "%02X ",tu8Buf[i]);
	}
	
	MID_SCHD_RTT_LOG(0, "sizeof(Struct_t) %d ",sizeof(Struct_t));
	
	#endif
	
	#if 0	// 睡眠档案存储上传测试
		#if 1	
		Store_SleepRecord_DataRead();
		#endif
		
		#if 0	
		PDU_Upload_CatalogInfoGet(eDataClassifySwimNew, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifySwimNew, 0, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifySwimNew, 1, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifySwimNew, 2, 0x66);
		PDU_Upload_CatalogDataRTS(eDataClassifySwimNew, 64 , 0, 0x88);
		#endif
	#endif	
	
	#if 0	// ABC数据存储与上传
		#if 1	// ABC数据读取测试
		Store_ABC_DataRead();
		#endif
		
		#if 1	// ABC数据上传测试
		#endif
		
		#if 0 // 获取气压最新数据，用于UI显示		
		int32_t tBuf[144];
		Store_ABC_UIPressureGet(tBuf, 0);
		
		MID_SCHD_RTT_LOG(0, "Store_ABC_UIPressureGet: \n");
		for(uint32_t i = 0;i < 144;i++)
		{
			if((0 == i%10) && (0 != i))
			{
				MID_SCHD_RTT_LOG(0, "\n");
			}
			MID_SCHD_RTT_LOG(0, "%08X ", tBuf[i]);
			vTaskDelay(2);
		}MID_SCHD_RTT_LOG(0, "\n");	
		#endif
		
		#if 0 // 获取海拔最新数据，用于UI显示
		int32_t ttttBuf[135];
		Store_ABC_UIAltitudeGet(ttttBuf, 135);
		
		MID_SCHD_RTT_LOG(0, "Store_ABC_UIAltitudeGet: \n");
		for(uint32_t i = 0;i < 135;i++)
		{
			if((0 == i%10) && (0 != i))
			{
				MID_SCHD_RTT_LOG(0, "\n");
			}
			MID_SCHD_RTT_LOG(0, "%08X ", ttttBuf[i]);
			vTaskDelay(2);
		}MID_SCHD_RTT_LOG(0, "\n");				
		#endif	
	#endif		
	
	#if 0	// 游泳数据存储与上传
		#if 1	// 游泳数据读取测试
		Store_Swim_DataRead();
		#endif
		
		#if 0	// 游泳数据上传测试
		PDU_Upload_CatalogInfoGet(eDataClassifySwimNew, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifySwimNew, 0, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifySwimNew, 1, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifySwimNew, 2, 0x66);
		PDU_Upload_CatalogDataRTS(eDataClassifySwimNew, 64 , 0, 0x88);
		#endif
	#endif		
	
	#if 0	// 登山数据存储与上传
		#if 1	// 登山数据读取测试
		Store_Climb_DataRead();
		#endif
		
		#if 0	// 登山数据上传测试
		PDU_Upload_CatalogInfoGet(eDataClassifyClimbNew, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifyClimbNew, 0, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifyClimbNew, 1, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifyClimbNew, 2, 0x66);
		PDU_Upload_CatalogDataRTS(eDataClassifyClimbNew, 153 , 0, 0x88);
		#endif
	#endif		
	
	#if 0	// 睡眠档案信息
	Store_SlpRcd_DataRead();
	#endif
	
	#if 0	// 睡眠存储与上传
		#if 1	// 体温数据读取测试
		Store_Sleep_DataRead();
		#endif
		
		#if 0	// 体温数据上传测试
		PDU_Upload_CatalogInfoGet(eDataClassifySleep, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifySleep, 0, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifySleep, 1, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifySleep, 2, 0x66);
		PDU_Upload_CatalogDataRTS(eDataClassifySleep, 64 , 0, 0x88);
		#endif
	#endif		
	
	#if 0	// 体温数据存储与上传
		#if 1	// 体温数据读取测试
		Store_Bodytemp_DataRead();
		#endif
		
		#if 0	// 体温数据上传测试
		PDU_Upload_CatalogInfoGet(eDataClassifyBodytemp, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifyBodytemp, 0, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifyBodytemp, 1, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifyBodytemp, 2, 0x66);
		PDU_Upload_CatalogDataRTS(eDataClassifyBodytemp, 64 , 0, 0x88);
		#endif
		
		#if 0 // 体温读取最新数测试
		int16_t tBuf[144];
		Store_Bodytemp_UIDataGet(tBuf, 144);
		
		MID_SCHD_RTT_LOG(0, "Store_Bodytemp_UIDataGet: \n");
		for(uint32_t i = 0;i < 144;i++)
		{
			if((0 == i%32) && (0 != i))
			{
				MID_SCHD_RTT_LOG(0, "\n");
				vTaskDelay(10);
			}
			MID_SCHD_RTT_LOG(0, "%04X ", tBuf[i]);
		}MID_SCHD_RTT_LOG(0, "\n");
		#endif			
	#endif		
	
	#if 0	// 人体压力数据存储与上传
		#if 1	// 人体压力数据读取测试
		Store_Stress_DataRead();
		#endif
		
		#if 0	// 人体压力数据上传测试
		PDU_Upload_CatalogInfoGet(eDataClassifyStress, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifyStress, 0, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifyStress, 1, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifyStress, 2, 0x66);
		PDU_Upload_CatalogDataRTS(eDataClassifyStress, 64 , 0, 0x88);
		#endif
		
		#if 1 // 人体压力读取最新数测试
		uint8_t tBuf[144];
		Store_Stress_UIDataGet(tBuf, 144);
		
		MID_SCHD_RTT_LOG(0, "Store_Stress_UIDataGet: \n");
		for(uint32_t i = 0;i < 144;i++)
		{
			if((0 == i%32) && (0 != i))
			{
				MID_SCHD_RTT_LOG(0, "\n");
			}
			MID_SCHD_RTT_LOG(0, "%02X ", tBuf[i]);
		}MID_SCHD_RTT_LOG(0, "\n");
		#endif		
	#endif	
	
	#if 0	// 心率数据存储与上传
		#if 1	// 心率数据读取测试
		Store_Hrd_DataRead();
		#endif
		
		#if 0	// 心率数据上传测试
		PDU_Upload_CatalogInfoGet(eDataClassifyHeartRate, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifyHeartRate, 0, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifyHeartRate, 1, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifyHeartRate, 2, 0x66);
		PDU_Upload_CatalogDataRTS(eDataClassifyHeartRate, 64 , 0, 0x88);
		#endif
		
		#if 1 // 心率读取最新数测试
		uint8_t tBuf[135];
		Store_Hrd_UIDataGet(tBuf, 135);
		
		MID_SCHD_RTT_LOG(0, "Store_Hrd_UIDataGet: \n");
		for(uint32_t i = 0;i < 135;i++)
		{
			if((0 == i%32) && (0 != i))
			{
				MID_SCHD_RTT_LOG(0, "\n");
			}
			MID_SCHD_RTT_LOG(0, "%02X ", tBuf[i]);
		}MID_SCHD_RTT_LOG(0, "\n");
		#endif
	#endif	
	
	#if 1	// 跑步数据存储与上传
		#if 0	// 跑步档案读取测试
		Store_RunRecord_DataRead();
		#endif
		
		#if 0	// 跑步数据读取测试
		Store_Run_DataRead();
		#endif

		#if 0	// 跑步数据上传测试
		PDU_Upload_CatalogInfoGet(eDataClassifyRunNew, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifyRunNew, 0, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifyRunNew, 1, 0x66);
		PDU_Upload_CatalogDetailGet(eDataClassifyRunNew, 2, 0x66);
		PDU_Upload_CatalogDataRTS(eDataClassifyRunNew, 142, 10, 0x88);
		#endif
	#endif
	
	#if 0	// 计步数据存储与上传
		#if 1	// 计步数据读取测试
		Store_Step_DataRead();
		#endif
		
		#if 0	// 计步数据上传测试
		PDU_Upload_CatalogInfoGet(eDataClassifyStep, 0x66);
//		PDU_Upload_CatalogDetailGet(eDataClassifyStep, 0, 0x66);
//		PDU_Upload_CatalogDetailGet(eDataClassifyStep, 1, 0x66);
//		PDU_Upload_CatalogDetailGet(eDataClassifyStep, 2, 0x66);
//		PDU_Upload_CatalogDataRTS(eDataClassifyStep, 0, 0, 0x88);
		#endif
		
		#if 0 // 计步读取最新数测试
		uint16_t tBuf[24];	// 最新24小时数据
		Store_Step_UIDataGet(tBuf, 24);
		
		MID_SCHD_RTT_LOG(0, "Store_Step_UIDataGet: \n");
		for(uint32_t i = 0;i < 24;i++)
		{
			if((0 == i%32) && (0 != i))
			{
				MID_SCHD_RTT_LOG(0, "\n");
			}
			MID_SCHD_RTT_LOG(0, "%d ", tBuf[i]);
		}MID_SCHD_RTT_LOG(0, "\n");
		#endif		
	#endif
	
	#if 0	// flash分part存储测试，慎重，会擦除已存储的数据
	Store_Part_Test();
	#endif
	
	#if 0	// 数据存储测试
	uint8_t tBuf[256];
	
//	// 读写系统信息测试
//	Store_Cmn_SysInfoWriteUpdate();
//	Store_Cmn_SysInfoReadUpdate();

	// 时间信息测试
	Store_Cmn_TimeInfoWriteUpdate();
	Store_Cmn_TimeInfoReadUpdate();
	#endif
	
	#if 0	// 罗盘测试
	static uint8_t stFlg = false;
//	compass_t tCompassInfo;
	uint16_t	tAngle;
	uint8_t tStatus;
	
	if(!stFlg)
	{
		stFlg = true;
		Scene_ABC_CompassEnable();
		Scene_ABC_CompassCalibrationStart();
	}
	else
	{
		tStatus = Scene_ABC_CompassAngleGet(&tAngle);		// 读取罗盘数据
		
		MID_SCHD_RTT_LOG(0,"Compass angle %d, calState %d \n", tAngle, tStatus);
	}
	
	#endif
	
	#if 0	// ABC气压场景测试
	MID_SCHD_RTT_LOG(0,"Scene_ABC_PresssureGet %d \n", Scene_ABC_PresssureGet());
	MID_SCHD_RTT_LOG(0,"Scene_ABC_altitudeGet %d \n", Scene_ABC_altitudeGet());
	MID_SCHD_RTT_LOG(0,"Scene_ABC_seaLevelGet %d \n", Scene_ABC_seaLevelGet());
	#endif
	
	#if 0	// 读取睡眠数据
	sleep_ui_info	tSleepInfo;
	
	Scene_Sleep_RecordGet(&tSleepInfo);
	
	MID_SCHD_RTT_LOG(0, "tSleepInfo (%d:%d)->(%d:%d) %d %d \n", 
		tSleepInfo.StartHour, tSleepInfo.StartMin, 
		tSleepInfo.StopHour, tSleepInfo.StopMin, 
		tSleepInfo.DurationM, tSleepInfo.Quality);
	#endif
	
	#if 0	//	压力算法
	Scene_Stress_SampleStart(eSceneMeasureWay feMeasure)
	
	#endif
	
	#if 0	// 打印任务执行情况
	uint8_t pcWriteBuffer[500];
	MID_SCHD_RTT_LOG(0, "Task Info ========================================\r\n");
	MID_SCHD_RTT_LOG(0, "Name        Status Priority  Stack   Num \n");
	vTaskList((char *)&pcWriteBuffer);
	MID_SCHD_RTT_LOG(0, "%s \n", pcWriteBuffer);

	MID_SCHD_RTT_LOG(0, "Name         RunningCnt    UsageRate  \n");
	vTaskGetRunTimeStats((char *)&pcWriteBuffer);
	MID_SCHD_RTT_LOG(0, "%s \n", pcWriteBuffer);	
	
	MID_SCHD_RTT_LOG(0,"FreeHeapSize %d \n", xPortGetFreeHeapSize());
	#endif
	
	#if 0	// 内存获取实验
	uint32_t 	Freemem = 0;
	static uint8_t * tpBuf = NULL;
	if(NULL == tpBuf)
	{
		MID_SCHD_RTT_LOG(0,"pvPortMalloc \n");
		tpBuf = pvPortMalloc(100);
	}
	else
	{
		MID_SCHD_RTT_LOG(0,"vPortFree \n");
		vPortFree(tpBuf);
		tpBuf = NULL;	// 是否后指针一定要置为NULL
	}
	
	Freemem = xPortGetFreeHeapSize();
	MID_SCHD_RTT_LOG(0,"Freemem %d \n", Freemem);
	#endif
	

	
	#if 1	// 气压环温	
//	MID_SCHD_RTT_LOG(0,"Mid_Press_SelfTest %02X \n", Mid_Press_SelfTest());
	#endif
	
	#if 0	// 心率测试
	Scene_Hrm_SampleStart(eSceneMeasureIM);
	#endif
	

	
	#if 0	// 读取身高体重信息
	MID_SCHD_RTT_LOG(0,"age %d, Height %d, Weight %d, sex %d \r\n", gtBodyInfo.age,gtBodyInfo.Height,gtBodyInfo.Weight,gtBodyInfo.sex);
	#endif
	

	
	#if 0	// 获取RTC时间测试
	// 手表主动向APP获取时间接口好像不能用，待和app确认
	App_Protocal_AdjustTimeprocess();
	#endif
	

	

	


	#if 0	// 马达任务测试
	Mid_Motor_ShakeStart(eMidMotorShake2Hz, 1);
	#endif
	
	#if 0	// 地磁任务测试

	#endif
	
	#if 1	// 加速度计任务测试
	#endif 
	

	
	#if 0	// 窗口任务测试
	App_Win_Msg_T Msg;
	Msg.MenuTag = eWinMenukey;
	
	App_Win_TaskEventSet(&Msg);
	#endif
}

void KeyPowerTest(void)
{
//	Mid_Schd_TaskMsg_T Msg;

	#if  0	// 陀螺仪角速度
	Mid_Gyro_ParamSet(eMidGyroSampleRate25HZ, eMidGyroSampleRange1000S);
	Mid_Gyro_StartSample();
	#endif
	
	#if  0	// 地磁
	Msg.Id = eSchdTaskMsgMagnetism;
	Msg.Param.Mag.Id = eMagEventStartSample;
	
	Mid_Motor_On();
	vTaskDelay(10000);
	Mid_Motor_Off();
	
	Mid_Schd_TaskEventSet(&Msg);	
	#endif	
	
	#if 0	// 马达
	Mid_Motor_On();
	vTaskDelay(500);
	Mid_Motor_Off();
	#endif
	
	#if 0	// 心率测量
	Scene_Hrm_SampleStart(eSceneMeasureIM);
	#endif
	
	#if 0// flash擦写读
//	xTimerStart(MidSchd_TimerHandle,0);	
	Mid_NandFlash_SelfTest();
	#endif
	
	#if 0	// 电量检测
	#endif
	
	#if 0 // 红外体温
	Msg.Id = eSchdTaskMsgITemp;
	Msg.Param.ITemp.Id = eITempEventStartSample;
	Mid_Schd_TaskEventSet(&Msg);	
	#endif
	
	#if 0 	// NTC 体温
	Drv_NTC_StartSample();
	#endif
	
	#if 0	// 硅麦
	Mid_Mic_Samle();
	#endif
}

void Module_Test(void)
{
	#if (3 == MID_RTC_RTT_DEBUG)
//	Mid_RTC_Test();
	#endif
	
	#if (3 == MID_PRESS_RTT_DEBUG)
//	Mid_Press_Test();
	#endif
	
	#if (3 == SCENE_ALARM_RTT_DEBUG)
	Scene_Alarm_Test();
	#endif
	
	#if (3 == SCENE_WEATHER_RTT_DEBUG)
	Scene_Weather_Test();
	#endif
	
	#if (3 == SCENE_STOPWATCH_RTT_DEBUG)
	Scene_StopWatch_Test();
	#endif	
	
	#if (3 == SCENE_COUNTDOWN_RTT_DEBUG)
	Scene_Countdown_Test();
	#endif
	
	#if (3 == SCENE_FINDPHONE_RTT_DEBUG)
	Scene_Findphone_Test();
	#endif

	#if (3 == DRV_GPS_RTT_DEBUG)
//	Drv_GPS_Test(1);
	#endif
	
	#if 0
	Mid_Motor_Test();
	#endif
	
	#if (3 == MID_GYRO_RTT_DEBUG)
//	Mid_Gyro_Test();
	#endif
	
	#if (3 == MID_MAG_RTT_DEBUG)
//	Mid_Mag_Test();
	#endif	
	
	#if (3 == MID_HRM_RTT_DEBUG)
	Mid_Hrm_Test();
	#endif		
	
	#if (3 == MID_LCD_RTT_DEBUG)
//	Mid_LCD_Test();
	#endif
	
	#if 0
	Drv_Touch_Test();
	#endif	
	
	#if 0
	Mid_6Dof_Test();
	#endif	
	
}

static void Mid_Key_EventProcess(Mid_Schd_KeyParam_T* Event_t)
{
	MID_SCHD_RTT_LOG(0,"Schd Msg Key %d \r\n", Event_t->Val);
    
	KeyTest();
	KeyPowerTest();
	Module_Test();
//	return ;
	
//	Scene_Run_Test(Msg->Param.Key.Val);
//	Scene_Climb_Test(Msg->Param.Key.Val);
//	Scene_Swim_Test(Msg->Param.Key.Val);
//	Mid_IT_Test();

	if( MID_KEY0_HOLDSHORT == Event_t->Val)
	/* 长按3秒，测试用 */
	{
//		App_Sys_InfoBackup(eAppSysStateWDTRst);
	}

	if( MID_KEY0_HOLDLONG == Event_t->Val)
	/* 长按12秒 */
	{
		App_Sys_Shutdown();
	}
	
	switch(gtPhoneState.state)
	{
		case PHONE_STATE_NORMAL:
		case PHONE_STATE_PHOTO:
            UI_Common_do_key_handle(Event_t->Val);	 //yangrui add
			break;
//		case PHONE_STATE_PHOTO:
//			App_Protocal_TakePhoto();
//			break;
		case PHONE_STATE_AUTHOR:
			gtPhoneState.state = PHONE_STATE_NORMAL;
			App_Protocal_AuthorPass();
			Mid_Motor_ShakeStart(eMidMotorShake1Hz, 1);	
			break;
		case PHONE_STATE_PAIRE:
			break;
		case PHONE_STATE_HRM:
			break;
		default: break;
	}
}

static void Mid_Gyro_EventProcess(Mid_Schd_TaskMsg_T* Msg)
{

	// 读取并更新一次传感器数据，通知其他外设需要自取
	Mid_Gyro_DataUpdate();	
	
	#if 0 // debug
	int16_t	tData[3];
	Mid_Gyro_DataRead(tData);
	MID_SCHD_RTT_LOG(0,"Gyro: %d, %d, %d \r\n",tData[0],tData[1],tData[2]);
	#endif
}

static void Mid_Uart_EventProcess(Mid_Schd_UartParam_T* UartEvent)
{
    uint16_t u16ReadLen = 0;
    uint8_t u8Buffer[128];
	Mid_Schd_TaskMsg_T SchdMsg;
	ble_msg_t ble_msg;
	static uint8_t lGPsBuf[256];
	static uint8_t lGPSLen = 0;
	static bool		lGPSFlg = false;
	
	switch (UartEvent->Module)
    {
    	case GPS_UART_MODULE:
			SMDrv_UART_ReadBytes(GPS_UART_MODULE,u8Buffer,32,&u16ReadLen);
			Drv_GPS_UartParse(u8Buffer, u16ReadLen);	

			#if 0
			for(uint32_t i = 0;i < u16ReadLen;i++)
			{
				if(0x24 == u8Buffer[i])	// 首字符 $
				{
					lGPSLen = 0;
					lGPsBuf[lGPSLen++] = u8Buffer[i];
					lGPSFlg = true;
				}
				else if(0x0A == u8Buffer[i])	// 尾字符 \r\n
				{
					lGPsBuf[lGPSLen++] = u8Buffer[i];
					if(lGPSFlg)
					{
						lGPSFlg = false;
						Drv_GPS_InfoParse((char *)lGPsBuf);
//						UI_Set_Curr_ScreenID(Common_Screen_MainID_Test);
//						UI_Screen_draw_Screen();
						for(uint32_t j = 0;j < lGPSLen;j++)
						{
							MID_SCHD_RTT_LOG(0,"%c", lGPsBuf[j]);
						}//MID_SCHD_RTT_LOG(0,"-----\n", lCnt++);						
					}
				}
				else	// 过程数据
				{
					lGPsBuf[lGPSLen++] = u8Buffer[i];
				}
			}
		
		
			
			#endif
		
    		break;
    	case BASE_UART_MODULE:
			SMDrv_UART_ReadBytes(BASE_UART_MODULE,u8Buffer,32,&u16ReadLen);
		//	SMDrv_UART_WriteBytes(BASE_UART_MODULE,u8Buffer,u16ReadLen,&u16LenWritten);
		//	for(uint32_t i = 0;i < u16ReadLen;i++)
		//	{
		//		MID_SCHD_RTT_LOG(0,"%02X ", u8Buffer[i]);
		//	}MID_SCHD_RTT_LOG(0,"\r\n");
			
			// 串口模拟按键、触摸等，调试windows切换逻辑
			switch(u8Buffer[0])
			{
				case 0x23:	// 模拟蓝牙
					ble_msg.id = BLE_MSG_RECEIVE;
					memcpy(ble_msg.packet.data, u8Buffer, PROTOCAL_LENGTH);
					Ble_SendMsgToQueue(&ble_msg);				
					break;
				default:
					SchdMsg.Id = (eSchdTaskMsgId)(u8Buffer[0]);								// 触摸，eSchdTaskMsgTouch
					SchdMsg.Param.Touch.Type = (eTouchGIDType)(u8Buffer[1]);					// Flick，eTouchGIDFlick
					switch(SchdMsg.Param.Touch.Type)
					{
						case eTouchGIDTap:
							SchdMsg.Param.Touch.GID.Tap.XCoord = u8Buffer[2];	// X坐标
							SchdMsg.Param.Touch.GID.Tap.YCoord = u8Buffer[3];	// Y坐标
							Mid_Schd_TaskEventSet(&SchdMsg);
							break;
						case eTouchGIDFlick:
							SchdMsg.Param.Touch.GID.Flick.Direction = (eTouchFlickDirection)(u8Buffer[2]);	// 方向
							Mid_Schd_TaskEventSet(&SchdMsg);
							break;
						default:
							break;
					}			
					break;
			}			
    		break;
    	default:
    		break;
    }	
}

static void Mid_Touch_EventProcess(TouchGIDParam_t* TouchEvent)
{
	switch(TouchEvent->Type)
	{
		case eTouchIsrProcess:	// 触摸中断
			Drv_Touch_IsrProcess();
			break;
		case eTouchGIDTap:	// 单击
			MID_SCHD_RTT_LOG(0,"eTouchGIDTap (%d, %d) \n", TouchEvent->GID.Tap.XCoord, TouchEvent->GID.Tap.YCoord);

            UI_Common_do_tp_click_handle(TouchEvent->GID.Tap.XCoord, TouchEvent->GID.Tap.YCoord);
			break;
		case eTouchGIDPress:	// 长按
			MID_SCHD_RTT_LOG(0,"eTouchGIDPress (%d, %d) \n", TouchEvent->GID.Tap.XCoord, TouchEvent->GID.Tap.YCoord);
            
			break;
		case eTouchGIDFlick:	// 滑动
			MID_SCHD_RTT_LOG(0,"eTouchGIDFlick, Direction %d (%d,%d)->(%d,%d) \n", 
				TouchEvent->GID.Flick.Direction, 
				TouchEvent->GID.Flick.XStartCoord, TouchEvent->GID.Flick.YStartCoord, 
				TouchEvent->GID.Flick.XEndCoord, TouchEvent->GID.Flick.YEndCoord);

            UI_Common_do_tp_slide_handle(TouchEvent->GID.Flick.Direction);
			break;
		default:
			break;
	}
}

void Mid_Schd_ParamInit(void)
{
	// 外设访问互斥信号量创建
	SPI_I2C_M0_SemaphoreHandle   = xSemaphoreCreateMutex();	
}

//**********************************************************************
// 函数功能: 中间层调度任务处理函数
// 输入参数：	
// 返回参数：
static void Mid_Schd_TaskProcess(void *pvParameters)
{
	Mid_Schd_TaskMsg_T	Msg;
	
	sSchd_QueueHandle = xQueueCreate(SCHD_TASK_QUEUE_LENGTH, SCHD_TASK_QUEUE_SIZE);
	if(sSchd_QueueHandle == NULL)
	{
		MID_SCHD_RTT_ERR(0,"Schd Queue Create Err \r\n");
	}
	
//	MidSchd_TimerHandle=xTimerCreate((const char*		)"MidSchd_Timer",
//									    (TickType_t			)(1000/portTICK_PERIOD_MS),
//							            (UBaseType_t		)pdTRUE,
//							            (void*				)1,
//							            (TimerCallbackFunction_t)MidSchd_TimerCallBack); 	
	while(1)
	{
		if(xQueueReceive(sSchd_QueueHandle, &Msg, portMAX_DELAY))
		{
			switch(Msg.Id)
			{
				case eSchdTaskMsgKey:
					Mid_Key_EventProcess(&Msg.Param.Key);
					break;
				case eSchdTaskMsgMagnetism:
					Mid_Mag_EventProcess(&Msg.Param.Mag);
					break;
				case eSchdTaskMsgUart:
					Mid_Uart_EventProcess(&Msg.Param.Uart);
					break;
				case eSchdTaskMsgPressure:
					Mid_Press_EventProcess(&Msg.Param.Pressure);
					break;
				case eSchdTaskMsgTouch:
					Mid_Touch_EventProcess(&Msg.Param.Touch);
					break;
				case eSchdTaskMsgITemp:
					Mid_ITemp_EventProcess(&Msg.Param.ITemp);
					break;
				case eSchdTaskMsgBat:
					Mid_Bat_EventProcess(&Msg.Param.Bat);
					break;
				case eSchdTaskMsgGPS:
					Drv_GPS_EventProcess(&Msg.Param.GPS);
					break;				
				default:
					drERROR_CHECK("Mid_Schd_TaskProcess", Ret_InvalidParam);
					break;
			}
		}
	}
}

//**********************************************************************
// 函数功能:	
// 输入参数：
// 返回参数：
void Mid_Schd_TaskEventSet(Mid_Schd_TaskMsg_T* Msg)
{
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

    if(sSchd_QueueHandle == NULL)
        return ;
	
    /* 若中断函数中调用，需判断是否需要进行任务调度 */
    if(xPortIsInsideInterrupt() == pdTRUE)    // 判断是否在中断
    {
		if(pdPASS != xQueueSendToBackFromISR(sSchd_QueueHandle, Msg, &xHigherPriorityTaskWoken))
		{
			MID_SCHD_RTT_ERR(0,"Mid_Schd_TaskEventSet Err \r\n");
		}
		
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
	else
	{
		if(pdPASS != xQueueSendToBack(sSchd_QueueHandle, Msg, SCHD_TASK_QUEUE_WAIT_TICK))
		{
			MID_SCHD_RTT_ERR(0,"Mid_Schd_TaskEventSet Err \r\n");
		}		
	}	
}

void Mid_Schd_TaskCreate(void)
{
    xTaskCreate(Mid_Schd_TaskProcess, "SchdTask", TASK_STACKDEPTH_MID_SCHD, NULL, TASK_PRIORITY_MID_SCHD, NULL);
}



