#ifndef	SCENE_ALARM_H
#define	SCENE_ALARM_H

#include "platform_common.h"
//#include "app_variable.h"

#define SCENE_ALARM_RTT_DEBUG	2
#if (1 == SCENE_ALARM_RTT_DEBUG)	// ����ȼ�
#define SCENE_ALARM_RTT_LOG(...)
#define SCENE_ALARM_RTT_WARN(...)
#define SCENE_ALARM_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == SCENE_ALARM_RTT_DEBUG)	// ����ȼ�
#define SCENE_ALARM_RTT_LOG(...)
#define SCENE_ALARM_RTT_WARN		RTT_DEBUG_WARN
#define SCENE_ALARM_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == SCENE_ALARM_RTT_DEBUG)	// ���Եȼ�
#define SCENE_ALARM_RTT_LOG		RTT_DEBUG_LOG
#define SCENE_ALARM_RTT_WARN	RTT_DEBUG_WARN
#define SCENE_ALARM_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define SCENE_ALARM_RTT_LOG(...)
#define SCENE_ALARM_RTT_WARN(...)
#define SCENE_ALARM_RTT_ERR(...)
#endif

#define	ALARM_SNOOZE_DURATION_MIN	(1)	// ����̰˯ʱ������λmin
#define SCENE_ALARM_MAX_ALARM_NUM	(3)		// �����������

// ���Ӳ����ṹ�壬����ͨ��Э��
typedef struct 
{
	uint8 hour;
	uint8 min;
	uint8 ReptMap;			// �ظ�λͼ bit0~bit6: sun~sat, bit7: �ظ�����
	uint8 alarmswitch;	    // �����¼����� 1: alarm open, 0: alarm close
	uint8 RingSwitch;		// ̰˯���أ�0�� 1��
	uint8 RingDurtion;		// ̰˯ʱ��min
	uint8 AlertLevel;		// �������ѵȼ�
}alarm_clock_t;

typedef struct
{
	uint8_t 			RingSwitch;		// ����̰˯���ܿ��أ�1 ��ǰ���ڴ���̰˯ģʽ
	uint8_t 			RingCnt;		// ̰˯���������5��
	uint8_t 			accTimer;		// ̰˯ʱ���ۻ���ÿ10����һ��
	uint8_t		 		curRingAlarmId;	// ��ǰ���Ӿ����ͨ����ȡ���ֵ���ж��ĸ��������ˣ�
	
	alarm_clock_t	Clock[SCENE_ALARM_MAX_ALARM_NUM];	// ��������
}SceneAlarmParam_t;

uint8 Scene_Alarm_Check(void);
void Scene_Alarm_Write(alarm_clock_t *configinfo, uint8_t group);
void Scene_Alarm_Read(alarm_clock_t *configinfo, uint8_t group);
uint8 Scene_Alarm_ValidNumRead(void);
void Scene_Alarm_CurrAlarmGet(alarm_clock_t *alarm_clock);	
void Scene_Alarm_Stop(void);
void Scene_Alarm_Delay(void);
SceneAlarmParam_t* Scene_Alarm_ParamPGet(void);
void Scene_Alarm_Test(void);

#endif			//	ALARM_APP_H





