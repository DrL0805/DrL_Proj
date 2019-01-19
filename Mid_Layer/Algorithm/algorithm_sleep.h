#ifndef _ALGORITHM_SLEEP_H_
#define _ALGORITHM_SLEEP_H_

#include <stdint.h>

#define ACC_RANGE	2  /* ������Χ��+-2g,+-4g,+-8g,+-16g */

/* ˯������ */
typedef enum
{
	ALG_SLEEP_EXCELLENT,
	ALG_SLEEP_GOOD,
	ALG_SLEEP_ONLY_FAIR,
	ALG_SLEEP_POOR,
} sleep_quality_e;

/* ˯��״̬ */
typedef enum
{
	ALG_SLEEP_WAKE,  /* ���� */
	ALG_SLEEP_LIGHT, /* ǳ˯ */
	ALG_SLEEP_DEEP,  /* ��˯ */
	ALG_SLEEP_REM,   /* �����۶� */
} sleep_period_e;

/* ˯����ϸʱ����״̬ */
typedef struct
{
	sleep_period_e State; /* ����˯�ߵ�˯��״̬ */
	uint16_t Duration;	/* *m ˯��ʱ��:���� */
} sleep_segment_t;

/* ˯�����״̬���� */
#define SLEEP_SEGMENT_MAX 30

/* ˯�߼�¼��Ϣ */
typedef struct
{
	uint8_t StartHour;		 /* ��ʼʱ�䣺ʱ , ˯�߿�ʼ����ʱ��RTC��ʽ */
	uint8_t StartMin;		 /* ��ʼʱ�䣺�� */
	uint8_t StopHour;		 /* ����ʱ�䣺ʱ */
	uint8_t StopMin;		 /* ����ʱ�䣺�� */
	uint32_t StartUTC;		 /* ˯�߿�ʼUTC , ˯�߿�ʼ����ʱ��UTC��ʽ */
	uint32_t StopUTC;		 /* ˯�߽���UTC */
	uint16_t SleepDuration;  /* *m ��˯��ʱ��������������ʱ�� */
	sleep_quality_e Quality; /* ˯������ */

	uint16_t TotalDuration; /* *m ��˯��ʱ������������ʱ�������������ĸ�ʱ�����ܺ� */
	uint16_t WakeDuration;  /* *m ����ʱ�� */
	uint16_t LightDuration; /* *m ǳ˯ʱ�� */
	uint16_t DeepDuration;  /* *m ��˯ʱ�� */
	uint16_t RemDuration;   /* *m �����۶�ʱ�� */

	uint8_t SegmentCnt;							  /* �ӿ�ʼʱ�䵽����ʱ���м�����ϸʱ��� */
	sleep_segment_t SleepData[SLEEP_SEGMENT_MAX]; /* ÿ�ξ���ʱ����״̬ */
} sleep_record_t;

/*******************************
**˯���㷨������ʼ�����ϵ����
**input: null
**output: null 
********************************/
void alg_sleep_init(void);

/*******************************
**˯���㷨����ÿ���ӵ���һ�Σ�������������0xFF
**input: ���ٶȴ��������ݣ�accValue������ֵ��hr
**output: null 
********************************/
void alg_sleep_process(int16_t *accelValue, uint8_t hr);

/*******************************
**��ȡ˯�߼�¼����
**input: null
**output: ˯�߼�¼��Ϣ��sleep_record *record
********************************/
void alg_sleep_get_record(sleep_record_t *sleepRecord);

/*******************************
**���ǰһ���˯�߼�¼��0��ʱ���ã��㷨���������˯�߼�¼����������Ʋ���Ϣ
**input: null
**output: null
********************************/
void alg_sleep_clr_record(void);

/*******************************
**�û���������ʱ���ô˺�������ǿ���ж����ѣ�������������������
**input: null
**output: null
********************************/
void alg_sleep_wake(void);

#endif // _ALGORITHM_SLEEP_H_
