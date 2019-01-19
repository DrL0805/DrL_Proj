#include "scene_alarm.h"
#include "mid_motor.h"
#include "mid_rtc.h"

static SceneAlarmParam_t	SceneAlarmParam;

//**********************************************************************
// ��������: ����̰˯��顣ÿ��10��������һ�Σ���������Ρ�
// �����������
// ���ز�����
//	    0xff �������壻0x00 ���Ӳ�����
// ���ã�Scene_Alarm_Check
static uint16 Mid_AlarmClock_DelayRing(void)
{
	if(SceneAlarmParam.RingSwitch)
	{
		SceneAlarmParam.accTimer++;
		if(SceneAlarmParam.accTimer == ALARM_SNOOZE_DURATION_MIN)
		{
			SceneAlarmParam.RingCnt++;
			if(SceneAlarmParam.RingCnt > 4)//���������Ч�����ӵ�һ����Ӧû�м���
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
// ��������:	����̰˯���ܴ򿪣���һ������̰˯����δ�꣬�������µ����ӡ�������̰˯����
// ���������	
// ���ز�����
// ����:Scene_Alarm_Check
static void Mid_AlarmClock_DelayRing_Open(void)
{
	SceneAlarmParam.RingSwitch 	        = 1;
	SceneAlarmParam.accTimer			= 0;
	SceneAlarmParam.RingCnt			= 0;
}

//**********************************************************************
// ��������:�������״̬��RTCÿ���ӵ���һ��
// ���������	
//      curtime����ǰ��RTC time
// ���ز����� 0xff �������壻0x00 ���Ӳ�����
// ����:�ⲿ���ã�ÿ���ӵ���һ�Σ�����Ƿ������Ӳ���
uint8 Scene_Alarm_Check(void)
{
	uint8 i;
	uint16 ret = 0;
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
	
	for(i = 0; i < SCENE_ALARM_MAX_ALARM_NUM; i++)
	{
		// �жϵ�ǰ�����Ƿ���Ч
		if(SceneAlarmParam.Clock[i].alarmswitch)			//alarm is open
		{
			// �жϵ�ǰ�������ظ����ӻ��ǵ�������
			if (SceneAlarmParam.Clock[i].ReptMap & 0x80)	//repeat
			{
				// ��Ϊ�ظ����ӣ����ݵ�ǰ���ڼ��ж���������Ӧ
				if((SceneAlarmParam.Clock[i].ReptMap & (0x01 << lMidRTC->RTC.week)) && SceneAlarmParam.Clock[i].hour == lMidRTC->RTC.hour
					&& SceneAlarmParam.Clock[i].min == lMidRTC->RTC.min) 
				{
					if(SceneAlarmParam.Clock[i].RingSwitch)	// ̰˯����
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
				// ��Ϊ�������ӣ��������ڼ����졣
                if(SceneAlarmParam.Clock[i].hour == lMidRTC->RTC.hour && SceneAlarmParam.Clock[i].min == lMidRTC->RTC.min)				
			    {
					if(SceneAlarmParam.Clock[i].RingSwitch)	// ̰˯����
					{
						Mid_AlarmClock_DelayRing_Open();
					}
					SceneAlarmParam.curRingAlarmId = i;		// ��ǰ���������ID
					SceneAlarmParam.Clock[i].alarmswitch = 0;	// �������ӣ���һ�κ�ر�
					SCENE_ALARM_RTT_LOG(0, "Scene_Alarm_Check, Id %d  \n", SceneAlarmParam.curRingAlarmId);
                    return 0xff;
				}						
			}
		}
	}
	
	// �жϵ�ǰ�Ƿ���̰˯״̬����̰˯ʱ�䵽
	ret |= Mid_AlarmClock_DelayRing();
	
	return ret;
}

// ��ȡ��ǰ��������Ӳ���
void Scene_Alarm_CurrAlarmGet(alarm_clock_t *alarm_clock)
{
	Scene_Alarm_Read(alarm_clock, SceneAlarmParam.curRingAlarmId);
}

//**********************************************************************
// ��������:ĳ������������Ϣд��
// ���������	
//      configinfo�����ӵ�������Ϣ
//      group ������ID��0-4��
// ���ز�������
//	  ���ã��ⲿ
 void Scene_Alarm_Write(alarm_clock_t *configinfo, uint8_t group)
{
	if(group >= SCENE_ALARM_MAX_ALARM_NUM) drERROR_CHECK_RETURN_NULL("Scene_Alarm_Write", Ret_InvalidParam); 

	memcpy(&SceneAlarmParam.Clock[group], configinfo, sizeof(alarm_clock_t));

	if ((SceneAlarmParam.curRingAlarmId == group) && (SceneAlarmParam.Clock[group].alarmswitch == 0))
	{
		SceneAlarmParam.RingSwitch = 0;	//���õ�ǰ��������ӹر�ʱ��̰˯��ر�
	}	
}

//**********************************************************************
// ��������:ĳ������������Ϣ��ȡ
// ���������	
//      configinfo�����ӵ�������Ϣ�����������������Ϣ��
//      group ������ID��0-4��
// ���ز�������
//	   ���ã��ⲿ
 void Scene_Alarm_Read(alarm_clock_t *configinfo, uint8_t group)
{
	if(group >= SCENE_ALARM_MAX_ALARM_NUM) drERROR_CHECK_RETURN_NULL("Scene_Alarm_Read", Ret_InvalidParam); 

	memcpy(configinfo, &SceneAlarmParam.Clock[group], sizeof(alarm_clock_t));
}

//**********************************************************************
// ��������:��ȡ���ӵ���Ч����
// �����������
// ���ز��������ӵ���Ч����
// ���ã��ⲿ
uint8 Scene_Alarm_ValidNumRead(void)
{
	uint8 validAlarmNun = 0;

	for (uint32_t numCnt = 0; numCnt < SCENE_ALARM_MAX_ALARM_NUM; numCnt ++)
	{
		//ȫ��Ϊ0�����ӱ�����Ϊ��Ч
		if (!(SceneAlarmParam.Clock[numCnt].ReptMap == 0 && SceneAlarmParam.Clock[numCnt].alarmswitch == 0  && 
			 SceneAlarmParam.Clock[numCnt].hour == 0 && SceneAlarmParam.Clock[numCnt].min == 0))
		{
				validAlarmNun++;
		}
	}
	return validAlarmNun;
}

// ֹͣ��ǰ����
void Scene_Alarm_Stop(void)
{
	SCENE_ALARM_RTT_LOG(0, "Scene_Alarm_Stop \n");
	
	SceneAlarmParam.RingSwitch = 0;
	Mid_Motor_ShakeStop();
}

// ��ǰ����̰˯
void Scene_Alarm_Delay(void)
{
	SCENE_ALARM_RTT_LOG(0, "Scene_Alarm_Delay \n");
	
	Mid_Motor_ShakeStop();
}

//**********************************************************************
// ��������: ��ȡ�����Ľṹ��ָ��
// ���������
// ���ز�����
SceneAlarmParam_t* Scene_Alarm_ParamPGet(void)
{
	return &SceneAlarmParam;
}

//**********************************************************************
// ��������: ���Ӳ���
// ���������
// ���ز�����
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




