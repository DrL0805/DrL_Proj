#include "scene_alarm.h"
#include "mid_motor.h"
#include "mid_rtc.h"

static SceneAlarmParam_t	SceneAlarmParam;

//**********************************************************************
// 函数功能: 闹钟贪睡检查。每隔10分钟提醒一次，共提醒五次。
// 输入参数：无
// 返回参数：
//	    0xff 闹钟响铃；0x00 闹钟不响铃
// 调用：Scene_Alarm_Check
static uint16 Mid_AlarmClock_DelayRing(void)
{
	if(SceneAlarmParam.RingSwitch)
	{
		SceneAlarmParam.accTimer++;
		if(SceneAlarmParam.accTimer == ALARM_SNOOZE_DURATION_MIN)
		{
			SceneAlarmParam.RingCnt++;
			if(SceneAlarmParam.RingCnt > 4)//如果闹钟有效，闹钟第一次响应没有计数
			{
				SceneAlarmParam.RingSwitch = 0;
			}
			else
			{
				SceneAlarmParam.accTimer = 0;
				SCENE_ALARM_RTT_LOG(0, "Mid_AlarmClock_DelayRing, RingCnt %d \n", SceneAlarmParam.RingCnt);
				return 0xff;
			}
		}
	}
	return 0x00;
}

//**********************************************************************
// 函数功能:	闹钟贪睡功能打开，若一个闹钟贪睡次数未完，又来了新的闹钟。则重置贪睡次数
// 输入参数：	
// 返回参数：
// 调用:Scene_Alarm_Check
static void Mid_AlarmClock_DelayRing_Open(void)
{
	SceneAlarmParam.RingSwitch 	        = 1;
	SceneAlarmParam.accTimer			= 0;
	SceneAlarmParam.RingCnt			= 0;
}

//**********************************************************************
// 函数功能:检测闹钟状态，RTC每分钟调用一次
// 输入参数：	
//      curtime：当前的RTC time
// 返回参数： 0xff 闹钟响铃；0x00 闹钟不响铃
// 调用:外部调用，每分钟调用一次，检测是否有闹钟产生
uint8 Scene_Alarm_Check(void)
{
	uint8 i;
	uint16 ret = 0;
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	
	for(i = 0; i < SCENE_ALARM_MAX_ALARM_NUM; i++)
	{
		// 判断当前闹钟是否有效
		if(SceneAlarmParam.Clock[i].alarmswitch)			//alarm is open
		{
			// 判断当前闹钟是重复闹钟还是单次闹钟
			if (SceneAlarmParam.Clock[i].ReptMap & 0x80)	//repeat
			{
				// 若为重复闹钟，根据当前星期几判断闹钟是响应
				if((SceneAlarmParam.Clock[i].ReptMap & (0x01 << lMidRTC->RTC.week)) && SceneAlarmParam.Clock[i].hour == lMidRTC->RTC.hour
					&& SceneAlarmParam.Clock[i].min == lMidRTC->RTC.min) 
				{
					if(SceneAlarmParam.Clock[i].RingSwitch)	// 贪睡开关
					{
						Mid_AlarmClock_DelayRing_Open();	
					}
                    SceneAlarmParam.curRingAlarmId = i;
					SCENE_ALARM_RTT_LOG(0, "Scene_Alarm_Check, Id %d  \n", SceneAlarmParam.curRingAlarmId);
					return 0xff;	
				}
			}
			else//single
			{
				// 若为单次闹钟，无论星期几都响。
                if(SceneAlarmParam.Clock[i].hour == lMidRTC->RTC.hour && SceneAlarmParam.Clock[i].min == lMidRTC->RTC.min)				
			    {
					if(SceneAlarmParam.Clock[i].RingSwitch)	// 贪睡开关
					{
						Mid_AlarmClock_DelayRing_Open();
					}
					SceneAlarmParam.curRingAlarmId = i;		// 当前响铃的闹钟ID
					SceneAlarmParam.Clock[i].alarmswitch = 0;	// 单次闹钟，响一次后关闭
					SCENE_ALARM_RTT_LOG(0, "Scene_Alarm_Check, Id %d  \n", SceneAlarmParam.curRingAlarmId);
                    return 0xff;
				}						
			}
		}
	}
	
	// 判断当前是否处于贪睡状态，且贪睡时间到
	ret |= Mid_AlarmClock_DelayRing();
	
	return ret;
}

// 获取当前响铃的闹钟参数
void Scene_Alarm_CurrAlarmGet(alarm_clock_t *alarm_clock)
{
	Scene_Alarm_Read(alarm_clock, SceneAlarmParam.curRingAlarmId);
}

//**********************************************************************
// 函数功能:某个闹钟配置信息写入
// 输入参数：	
//      configinfo：闹钟的配置信息
//      group ：闹钟ID（0-4）
// 返回参数：无
//	  调用：外部
 void Scene_Alarm_Write(alarm_clock_t *configinfo, uint8_t group)
{
	if(group >= SCENE_ALARM_MAX_ALARM_NUM) drERROR_CHECK_RETURN_NULL("Scene_Alarm_Write", Ret_InvalidParam); 

	memcpy(&SceneAlarmParam.Clock[group], configinfo, sizeof(alarm_clock_t));

	if ((SceneAlarmParam.curRingAlarmId == group) && (SceneAlarmParam.Clock[group].alarmswitch == 0))
	{
		SceneAlarmParam.RingSwitch = 0;	//设置当前在响的闹钟关闭时，贪睡响关闭
	}	
}

//**********************************************************************
// 函数功能:某个闹钟配置信息读取
// 输入参数：	
//      configinfo：闹钟的配置信息（传入变量，保存信息）
//      group ：闹钟ID（0-4）
// 返回参数：无
//	   调用：外部
 void Scene_Alarm_Read(alarm_clock_t *configinfo, uint8_t group)
{
	if(group >= SCENE_ALARM_MAX_ALARM_NUM) drERROR_CHECK_RETURN_NULL("Scene_Alarm_Read", Ret_InvalidParam); 

	memcpy(configinfo, &SceneAlarmParam.Clock[group], sizeof(alarm_clock_t));
}

//**********************************************************************
// 函数功能:读取闹钟的有效个数
// 输入参数：无
// 返回参数：闹钟的有效个数
// 调用：外部
uint8 Scene_Alarm_ValidNumRead(void)
{
	uint8 validAlarmNun = 0;

	for (uint32_t numCnt = 0; numCnt < SCENE_ALARM_MAX_ALARM_NUM; numCnt ++)
	{
		//全部为0，闹钟被设置为无效
		if (!(SceneAlarmParam.Clock[numCnt].ReptMap == 0 && SceneAlarmParam.Clock[numCnt].alarmswitch == 0  && 
			 SceneAlarmParam.Clock[numCnt].hour == 0 && SceneAlarmParam.Clock[numCnt].min == 0))
		{
				validAlarmNun++;
		}
	}
	return validAlarmNun;
}

// 停止当前闹钟
void Scene_Alarm_Stop(void)
{
	SCENE_ALARM_RTT_LOG(0, "Scene_Alarm_Stop \n");
	
	SceneAlarmParam.RingSwitch = 0;
	Mid_Motor_ShakeStop();
}

// 当前闹钟贪睡
void Scene_Alarm_Delay(void)
{
	SCENE_ALARM_RTT_LOG(0, "Scene_Alarm_Delay \n");
	
	Mid_Motor_ShakeStop();
}

//**********************************************************************
// 函数功能: 获取参数的结构体指针
// 输入参数：
// 返回参数：
SceneAlarmParam_t* Scene_Alarm_ParamPGet(void)
{
	return &SceneAlarmParam;
}

//**********************************************************************
// 函数功能: 闹钟测试
// 输入参数：
// 返回参数：
void Scene_Alarm_Test(void)
{
	SCENE_ALARM_RTT_LOG(0,"Scene_Alarm_Test \n");
	
	#if 1
	alarm_clock_t	tAlarm;
	
	SCENE_ALARM_RTT_LOG(0,"RingSwitch,RingCnt,accTimer,curRingAlarmId : %d %d %d %d \n", 
		SceneAlarmParam.RingSwitch, SceneAlarmParam.RingCnt, SceneAlarmParam.accTimer, SceneAlarmParam.curRingAlarmId);
	for(uint32_t i = 0;i < Scene_Alarm_ValidNumRead();i++)
	{
		Scene_Alarm_Read(&tAlarm, i);
		SCENE_ALARM_RTT_LOG(0,"tAlarm %02X, %02X, %02X, %02X\r\n", 
			tAlarm.hour, tAlarm.min, tAlarm.ReptMap, tAlarm.alarmswitch);
	}
	#endif
}




