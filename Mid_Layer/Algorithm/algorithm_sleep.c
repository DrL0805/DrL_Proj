
#include <string.h>
#include "algorithm_sleep.h"

typedef enum
{
	NONE_SLEEP = 0, /* δ��˯ */
	ENTER_SLEEP,	/* ��˯ */
} sleep_state_e;

typedef struct
{
	uint16_t minSumMax;		/* 30������ÿ���Ӷ���ֵҪС�ڴ�ֵ */
	uint8_t minFreqMax;		/* 30������ÿ���Ӷ�������ҪС�ڴ�ֵ */
	uint16_t packSumMax;	/* 30������ÿ���Ӷ���ֵ���ڴ�ֵ�ĸ���ҪС��packSumMaxCnt */
	uint8_t packSumMaxCnt;  /* 30������ÿ���Ӷ���ֵ����packSumMax�ĸ���ҪС�ڴ�ֵ */
	uint8_t packFreqMax;	/* 30������ÿ���Ӷ����������ڴ�ֵ�ĸ���ҪС��packFreqMaxCnt */
	uint8_t packFreqMaxCnt; /* 30������ÿ���Ӷ�����������packFreqMax�ĸ���ҪС�ڴ�ֵ */
} sleep_condition_t;

typedef struct
{
	uint8_t hour;
	uint8_t min;
} sleep_rtc_t;

typedef struct
{
	uint16_t actSum; /* һ�����ڶ���ֵ */
	uint8_t actCnt;  /* һ�����ڶ������� */
} minute_data_t;

/* ��ǰ˯��״̬��¼ */
typedef struct
{
	sleep_record_t rcd;
	uint16_t actFreq;
	uint8_t state;
} sleep_record_temp_t;

/* ��ǰ˯��״̬��¼ */
typedef struct
{
	uint8_t state;		 /* ��ǰ��˯������״̬ */
	uint8_t interval;	/* ÿ����˯�ߵ��ж����ʱ����� */
	uint8_t secCnt;		 /* ����� */
	uint8_t minCnt;		 /* �ּ��� */
	uint16_t noACTCnt;   /* �����޶������� */
	uint16_t deepSlpCnt; /* ��˯״̬ʱ����� */
} sleep_process_t;

#define ABS(a, b) (((a) - (b) > 0) ? (a) - (b) : (b) - (a))

#define ONE_ACT_THRESHOLD 2 /* ���ᶯ����ֵ��С�ڸ�ֵ�ж�Ϊ���ţ����� */
#define ALL_ACT_THRESHOLD 6 /* ���ᶯ������ֵ,С�ڸ�ֵ�ж�Ϊ�޶���״̬ */
#define ACT(a, b) (ABS(a, b) < ONE_ACT_THRESHOLD ? 0 : ABS(a, b))

#define WAKE_ACT_SUM_THRE 2200 /* �������Ѷ�����ֵ�����γ�����ֵ�ж�Ϊ���� */
#define WAKE_ACT_FREQ_THRE 30  /* �������Ѷ���Ƶ����ֵ�����γ�����ֵ�ж�Ϊ���� */

#define START_SLEEP_HOUR 20   /* Ĭ��˯�����俪ʼʱ�� */
#define STOP_SLEEP_HOUR 10	/* Ĭ��˯���������ʱ�� */
#define SLEEP_DURATION_MIN 60 /* ��˯��С��¼ʱ�� */
#define START_ADD_DURATION 28 /* �жϽ���˯�ߺ���ǰ�Ƶ�ʱ�� */
#define JUDGE_INTERVAL 30	 /* ÿ����˯�ߵ��ж����ʱ�� */

#define DEEP_NO_ACT_FRE_MAX 3		/* ����������˯�ж�����Ƶ����ֵ */
#define DEEP_NO_ACT_SUM_MAX 80		/* ����������˯�ж�������ֵ��ֵ */
#define DEEP_SLEEP_MIN_DURATION 10  /* *m ��˯״̬����Сʱ�� */
#define DEEP_SLEEP_DEC_DURATION 5	/* *m �жϽ�����˯����ǰ�Ƶ���˯ʱ��,Ҫ��DEEP_SLEEP_MIN_DURATIONС */
#define LIGHT_SLEEP_MIN_DURATION 10 /* *m ǳ˯״̬����Сʱ�� */

#define MIN_NO_ACT_THS 2	   /* ���������޶����ж�Ƶ����ֵ */
#define NO_ACT_WAKE_TIME 60	/* �����޶�������ʱ�� */
#define SLEEP_DURATION_MAX 720 /* *m ����˯�����ʱ�� */
#define ACT_PERCENT 0.5		   /* ��һ����˯���ж���Ƶ��С�ڴ˰ٷֱȣ����ж�Ϊ����״̬ */

#define SLEEP_JUDGE_WIN 30 /* ˯���жϴ���Ϊ30���� */
/* ��˯����״̬�жϾ���ֵ */
const sleep_condition_t SleepCondition = {2200, 30, 1000, 5, 10, 5};

#define SLEEP_FAKE_RECORD

#ifdef SLEEP_FAKE_RECORD
const sleep_record_t fakeRecord = {
	23, 30, 7, 40, 1537889400, 1537918800, 440, ALG_SLEEP_EXCELLENT, 490, 50, 352, 88, 0, 15, {
																								  {ALG_SLEEP_LIGHT, 50},
																								  {ALG_SLEEP_DEEP, 20},
																								  {ALG_SLEEP_LIGHT, 30},
																								  {ALG_SLEEP_DEEP, 10},
																								  {ALG_SLEEP_LIGHT, 40},
																								  {ALG_SLEEP_DEEP, 28},
																								  {ALG_SLEEP_LIGHT, 70},
																								  {ALG_SLEEP_WAKE, 30},
																								  {ALG_SLEEP_LIGHT, 40},
																								  {ALG_SLEEP_DEEP, 15},
																								  {ALG_SLEEP_LIGHT, 60},
																								  {ALG_SLEEP_WAKE, 20},
																								  {ALG_SLEEP_LIGHT, 30},
																								  {ALG_SLEEP_DEEP, 15},
																								  {ALG_SLEEP_LIGHT, 32},
																							  }};
#endif

static minute_data_t MinRcd[SLEEP_JUDGE_WIN]; /* ��¼�����Сʱ��ÿ���ӵĶ�����ֵ������Ƶ�μ�¼ */
static sleep_process_t SlpProcess;			  /* ˯���㷨����������� */
static sleep_record_temp_t SlpRcdTemp;		  /* ��ǰ˯�߼�¼���� */
static sleep_record_t SlpRecord[2];			  /* ������ʾ��˯�����ݣ�0�����㣬0Ϊ��ʾ���ݣ�1Ϊ�ݴ����� */

static void sleep_recode_start(void);  /* ��ʼһ��˯�߼�¼ */
static void sleep_recode_save(void);   /* ����һ��˯�߼�¼ */
static void sleep_recode_update(void); /* ����˯�߼�¼ */
static uint8_t sleep_time_judge(void); /* �ж�˯��ʱ���Ƿ���Ԥ��ʱ���� */
static uint8_t sleep_type_judge(void); /* ��30�ֵĻ������������ж� */

/*******************************
**��ȡϵͳ��UTC,RTCʱ�䣬UTCתRTC, ��Ҫ�滻Ϊϵͳ�Ļ�ȡUTC��RTC,UTCתRTC�ĺ���
**input: null
**output: null
********************************/
#include "mid_rtc.h"
static uint32_t sleep_get_utc(void)
{
	uint32_t utcTemp = 0;

	utcTemp = Mid_Rtc_ReadCurUtc();

	return utcTemp;
}
static sleep_rtc_t sleep_utc_to_rtc(uint32_t utc)
{
	sleep_rtc_t rtc = {0, 0};

	rtc_time_s rtcTime;
	UtcTransformTime(utc, &rtcTime);

	rtc.hour = rtcTime.hour;
	rtc.min = rtcTime.min;

	return rtc;
}

/*******************************
**˯���㷨������ʼ�����ϵ����
**input: null
**output: null
********************************/
void alg_sleep_init(void)
{
	for (uint8_t i = 0; i < SLEEP_JUDGE_WIN; i++)
	{
		MinRcd[i].actSum = 0xFFFF;
		MinRcd[i].actCnt = 0xFF;
	}
	memset(&SlpProcess, 0, sizeof(SlpProcess));
	SlpProcess.interval = JUDGE_INTERVAL;

	memset(&SlpRcdTemp, 0, sizeof(SlpRcdTemp));

	memset(SlpRecord, 0, sizeof(SlpRecord));
}

/*******************************
**˯���㷨����ÿ���ӵ���һ�Σ�������������0xFF
**input: ���ٶȴ��������ݣ�accValue������ֵ��hr
**output: null
********************************/
void alg_sleep_process(int16_t *accelValue, uint8_t hr)
{
	static int8_t accOld[3]; /* �ϴε�����ֵ */

	int8_t accValue[3];
	uint16_t actSum = 0;
	for (uint8_t i = 0; i < 3; i++)
	{
		/* תΪ8bit����,ͬʱ��С���� */
		accValue[i] = accelValue[i] >> (16 / ACC_RANGE);
		/* �����ܶ���ֵ */
		actSum += ACT(accValue[i], accOld[i]);
	}

	/* һ�������ۼӶ���ֵ�Ͷ���Ƶ�� */
	if (SlpProcess.secCnt < 60)
	{
		/* һ�������ܶ���ֵ */
		MinRcd[SlpProcess.minCnt].actSum += actSum;
		/* һ�����ڶ���Ƶ�� */
		if (actSum > ALL_ACT_THRESHOLD)
		{
			MinRcd[SlpProcess.minCnt].actCnt++;
		}
	}

	/* ʱ����� */
	SlpProcess.secCnt++;
	if (SlpProcess.secCnt == 60)
	{
		SlpProcess.secCnt = 0;
		SlpProcess.minCnt++;
		if (SlpProcess.minCnt == SLEEP_JUDGE_WIN)
		{
			SlpProcess.minCnt = 0;
		}
		MinRcd[SlpProcess.minCnt].actSum = 0;
		MinRcd[SlpProcess.minCnt].actCnt = 0;
	}

	/* ����1���������жϴ��� */
	if (SlpProcess.secCnt == 59)
	{
		/* �жϼ���������� */
		if (SlpProcess.interval <= JUDGE_INTERVAL)
		{
			SlpProcess.interval++;
		}
		/* ��ǰ�������ü�����һ */
		if (MinRcd[SlpProcess.minCnt].actCnt < MIN_NO_ACT_THS)
		{
			SlpProcess.noACTCnt++;
		}
		else
		{
			SlpProcess.noACTCnt = 0;
		}
		/* �ж����30���ӵ�˯��״̬ */
		SlpProcess.state = sleep_type_judge();
		/* ����״̬���� */
		if (SlpRcdTemp.state == NONE_SLEEP)
		{
			/* ��˯������1.�жϴ�������������������2.����״̬����С�ڴ���ʱ���2��3.˯���жϼ��������� */
			if ((SlpProcess.state == ENTER_SLEEP) && (SlpProcess.noACTCnt < (SLEEP_JUDGE_WIN - 2)) && (SlpProcess.interval >= JUDGE_INTERVAL))
			{
				/* ����״̬�л�Ϊ��˯״̬����¼��˯���ͺ͵�ǰ��˯ʱ�� */
				sleep_recode_start();
			}
		}
		else
		{
			/* ��ǰ��˯������������ */
			SlpRcdTemp.actFreq += MinRcd[SlpProcess.minCnt].actCnt;

			/* С�����жϣ�����һ��ʱ��С�����������˯״̬*/
			if ((MinRcd[SlpProcess.minCnt].actCnt <= DEEP_NO_ACT_FRE_MAX) && (MinRcd[SlpProcess.minCnt].actSum <= DEEP_NO_ACT_SUM_MAX))
			{
				SlpProcess.deepSlpCnt++;
				/* ��ǳ˯�л�����˯ */
				if ((SlpProcess.deepSlpCnt >= DEEP_SLEEP_MIN_DURATION) && (SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt].State == ALG_SLEEP_LIGHT) && (SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt].Duration >= (DEEP_SLEEP_MIN_DURATION + LIGHT_SLEEP_MIN_DURATION)))
				{
					/* ���˯��ʱ��������Ƿ����� */
					if (SlpRcdTemp.rcd.SegmentCnt < (SLEEP_SEGMENT_MAX - 2))
					{
						SlpRcdTemp.rcd.SegmentCnt++;
						SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt].State = ALG_SLEEP_DEEP;
						SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt - 1].Duration -= (DEEP_SLEEP_MIN_DURATION - DEEP_SLEEP_DEC_DURATION);
						SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt].Duration += (DEEP_SLEEP_MIN_DURATION - DEEP_SLEEP_DEC_DURATION);
					}
				}
			}
			else
			{
				/* ����˯�л���ǳ˯ */
				if ((SlpProcess.deepSlpCnt > DEEP_SLEEP_MIN_DURATION) && (SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt].State == ALG_SLEEP_DEEP))
				{
					/* ���˯��ʱ��������Ƿ����� */
					if (SlpRcdTemp.rcd.SegmentCnt < (SLEEP_SEGMENT_MAX - 1))
					{
						SlpRcdTemp.rcd.SegmentCnt++;
						SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt].State = ALG_SLEEP_LIGHT;
					}
				}
				/* ���������˯״̬���� */
				SlpProcess.deepSlpCnt = 0;
			}
			/* ˯��״̬ʱ���ۼ� */
			SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt].Duration++;

			/* ��⵽����������Ϊ��˯��״̬����������˯�� */
			if (SlpProcess.state == NONE_SLEEP)
			{
				sleep_recode_save();
			}
			/* ����⵽�����������ƾ���״̬����������˯�� */
			else if (SlpProcess.noACTCnt > NO_ACT_WAKE_TIME)
			{
				sleep_recode_save();
			}
			/* �������ڶ���ֵ�Ͷ���Ƶ�γ�������������˯�� */
			else if ((MinRcd[SlpProcess.minCnt].actSum > WAKE_ACT_SUM_THRE) || (MinRcd[SlpProcess.minCnt].actCnt > WAKE_ACT_FREQ_THRE))
			{
				sleep_recode_save();
			}
			/* ˯��ʱ�����12Сʱ����������˯�� */
			else if ((sleep_get_utc() - SlpRcdTemp.rcd.StartUTC) / 60 > SLEEP_DURATION_MAX)
			{
				sleep_recode_save();
			}
			/* ��������״̬ */
			else if (hr == 0)
			{
				sleep_recode_save();
			}
		}
	}

	/* ������һ��ļ��ٶ�����ֵ */
	for (uint8_t i = 0; i < 3; i++)
	{
		accOld[i] = accValue[i];
	}
}

/*******************************
**��ȡ˯�߼�¼����
**input: null
**output: ˯�߼�¼��Ϣ��sleep_record *record
********************************/
void alg_sleep_get_record(sleep_record_t *sleepRecord)
{
#ifdef SLEEP_FAKE_RECORD
	memcpy(sleepRecord, &fakeRecord, sizeof(sleep_record_t));
#else
	memcpy(sleepRecord, &SlpRecord[0], sizeof(sleep_record_t));
#endif
}

/*******************************
**���ǰһ���˯�߼�¼��0��ʱ���ã��㷨���������˯�߼�¼����������Ʋ���Ϣ
**input: null
**output: null
********************************/
void alg_sleep_clr_record(void)
{
	memcpy(&SlpRecord[0], &SlpRecord[1], sizeof(sleep_record_t));
	memset(&SlpRecord[1], 0, sizeof(sleep_record_t));
}

/*******************************
**�û���������ʱ���ô˺�������ǿ���ж����ѣ�������������������
**input: null
**output: null
********************************/
void alg_sleep_wake(void)
{
	if (SlpRcdTemp.state == ENTER_SLEEP)
	{
		sleep_recode_save();
	}
}

/*******************************
**�жϴ˶�˯���Ƿ�������ϰ��˯�������ڣ����ڴ������ڲ���¼
**input: null
**output: ���ڣ�0���ڣ�1
********************************/
static uint8_t sleep_time_judge(void)
{
	sleep_rtc_t startRtc, stopRtc;
	startRtc = sleep_utc_to_rtc(SlpRcdTemp.rcd.StartUTC);
	stopRtc = sleep_utc_to_rtc(SlpRcdTemp.rcd.StopUTC);
	if ((startRtc.hour <= START_SLEEP_HOUR) && (startRtc.hour >= STOP_SLEEP_HOUR) && (stopRtc.hour <= START_SLEEP_HOUR) && (stopRtc.hour >= STOP_SLEEP_HOUR) && (stopRtc.hour > startRtc.hour))
	{
		return 0;
	}
	return 1;
}

/*******************************
**��˯�߻����¼������˯�߼�¼
**input: null
**output: null
********************************/
static void sleep_recode_update(void)
{
	uint8_t recordIndex = 0;

	sleep_rtc_t rtcTime = sleep_utc_to_rtc(SlpRcdTemp.rcd.StopUTC);
	/* 0������ʼʱ���˯�߱����ڽ���˯�� */
	if (rtcTime.hour < START_SLEEP_HOUR)
	{
		recordIndex = 0;
	}
	/* ���ڿ�ʼʱ���˯�߱�������һ�� */
	else if (rtcTime.hour >= START_SLEEP_HOUR)
	{
		recordIndex = 1;
	}
	/* �����û���� */
	if (SlpRecord[recordIndex].StartUTC == 0)
	{
		memcpy(&SlpRecord[recordIndex], &SlpRcdTemp.rcd, sizeof(sleep_record_t));
	}
	/* ����������� */
	else
	{
		/* �������˯�ߵĿ�ʼʱ����ϴ�˯�ߵĽ���ʱ�����2Сʱ */
		if ((SlpRcdTemp.rcd.StartUTC - SlpRecord[recordIndex].StopUTC) > 7200)
		{
			/* ����²�����˯��ʱ�����֮ǰ��ʱ�䣬����д˯��ʱ�䣬���򶪵�����˯�� */
			// if (SlpRcdTemp.rcd.SleepDuration > SlpRecord[recordIndex].SleepDuration)
			// {
				memcpy(&SlpRecord[recordIndex], &SlpRcdTemp.rcd, sizeof(sleep_record_t));
			// }
		}
		/* ����˯��ƴ�� */
		else
		{
			/* ˯����ʱ��β��������ʱ��� */
			if ((SlpRecord[recordIndex].SegmentCnt + SlpRcdTemp.rcd.SegmentCnt) < (SLEEP_SEGMENT_MAX - 1))
			{
				/* ��������ʱ��� */
				SlpRecord[recordIndex].SleepData[SlpRecord[recordIndex].SegmentCnt].State = ALG_SLEEP_WAKE;
				SlpRecord[recordIndex].SleepData[SlpRecord[recordIndex].SegmentCnt].Duration = (SlpRcdTemp.rcd.StartUTC - SlpRecord[recordIndex].StopUTC) / 60;
				SlpRecord[recordIndex].SegmentCnt++;
				/* ����ʱ���ƴ��������ʱ����� */
				for (uint8_t i = 0; i < SlpRcdTemp.rcd.SegmentCnt; i++)
				{
					SlpRecord[recordIndex].SleepData[SlpRecord[recordIndex].SegmentCnt].State = SlpRcdTemp.rcd.SleepData[i].State;
					SlpRecord[recordIndex].SleepData[SlpRecord[recordIndex].SegmentCnt].Duration = SlpRcdTemp.rcd.SleepData[i].Duration;
					SlpRecord[recordIndex].SegmentCnt++;
				}
				/* ˯�߽���ʱ����� */
				SlpRecord[recordIndex].StopUTC = SlpRcdTemp.rcd.StopUTC;
			}
		}
	}
	/* ˯����������ת�������㣬��ʼ����ʱ��UTCתRTC */
	sleep_rtc_t startRtc, stopRtc;
	startRtc = sleep_utc_to_rtc(SlpRecord[recordIndex].StartUTC);
	stopRtc = sleep_utc_to_rtc(SlpRecord[recordIndex].StopUTC);
	SlpRecord[recordIndex].StartHour = startRtc.hour;
	SlpRecord[recordIndex].StartMin = startRtc.min;
	SlpRecord[recordIndex].StopHour = stopRtc.hour;
	SlpRecord[recordIndex].StopMin = stopRtc.min;
	/* �ۼ�ǰ��0 */
	SlpRecord[recordIndex].WakeDuration = 0;
	SlpRecord[recordIndex].LightDuration = 0;
	SlpRecord[recordIndex].DeepDuration = 0;
	SlpRecord[recordIndex].RemDuration = 0;
	/* ѭ���ۼӼ����˯�߽׶�ʱ�� */
	for (uint8_t i = 0; i < SlpRecord[recordIndex].SegmentCnt; i++)
	{
		if (SlpRecord[recordIndex].SleepData[i].State == ALG_SLEEP_WAKE)
		{
			SlpRecord[recordIndex].WakeDuration += SlpRecord[recordIndex].SleepData[i].Duration;
		}
		else if (SlpRecord[recordIndex].SleepData[i].State == ALG_SLEEP_LIGHT)
		{
			SlpRecord[recordIndex].LightDuration += SlpRecord[recordIndex].SleepData[i].Duration;
		}
		else if (SlpRecord[recordIndex].SleepData[i].State == ALG_SLEEP_DEEP)
		{
			SlpRecord[recordIndex].DeepDuration += SlpRecord[recordIndex].SleepData[i].Duration;
		}
		else if (SlpRecord[recordIndex].SleepData[i].State == ALG_SLEEP_REM)
		{
			SlpRecord[recordIndex].RemDuration += SlpRecord[recordIndex].SleepData[i].Duration;
		}
	}
	/* ��ʱ�����ڽ���ʱ�����ʼʱ�� */
	SlpRecord[recordIndex].TotalDuration = (SlpRecord[recordIndex].StopUTC - SlpRecord[recordIndex].StartUTC) / 60;
	/* ˯��ʱ��������ʱ��������ʱ�� */
	SlpRecord[recordIndex].SleepDuration = SlpRecord[recordIndex].TotalDuration - SlpRecord[recordIndex].WakeDuration;
	/* ʱ��ȱʧ�򲹳� */
	if (SlpRecord[recordIndex].LightDuration + SlpRecord[recordIndex].DeepDuration < SlpRecord[recordIndex].SleepDuration)
	{
		uint16_t durationTemp = SlpRecord[recordIndex].SleepDuration - SlpRecord[recordIndex].LightDuration - SlpRecord[recordIndex].DeepDuration;
		SlpRecord[recordIndex].SleepData[SlpRecord[recordIndex].SegmentCnt - 1].Duration += durationTemp;
		if (SlpRecord[recordIndex].SleepData[SlpRecord[recordIndex].SegmentCnt - 1].State == ALG_SLEEP_LIGHT)
		{
			SlpRecord[recordIndex].LightDuration += durationTemp;
		}
		else if (SlpRecord[recordIndex].SleepData[SlpRecord[recordIndex].SegmentCnt - 1].State == ALG_SLEEP_DEEP)
		{
			SlpRecord[recordIndex].DeepDuration += durationTemp;
		}
	}
	/* ʱ��������� */
	else if (SlpRecord[recordIndex].LightDuration + SlpRecord[recordIndex].DeepDuration > SlpRecord[recordIndex].SleepDuration)
	{
		uint16_t durationTemp =  SlpRecord[recordIndex].LightDuration + SlpRecord[recordIndex].DeepDuration - SlpRecord[recordIndex].SleepDuration;
		uint16_t decTemp = 0, decCnt = 0;
		while(decTemp < durationTemp)
		{
			decCnt++;
			decTemp += SlpRecord[recordIndex].SleepData[SlpRecord[recordIndex].SegmentCnt - decCnt].Duration;			
		}		
		SlpRecord[recordIndex].SleepData[SlpRecord[recordIndex].SegmentCnt - decCnt].Duration = decTemp - durationTemp;
		SlpRecord[recordIndex].SegmentCnt -= (decCnt - 1);
		SlpRecord[recordIndex].LightDuration = 0;
		SlpRecord[recordIndex].DeepDuration = 0;
		for (uint8_t i = 0; i < SlpRecord[recordIndex].SegmentCnt; i++)
		{
			if (SlpRecord[recordIndex].SleepData[i].State == ALG_SLEEP_LIGHT)
			{
				SlpRecord[recordIndex].LightDuration += SlpRecord[recordIndex].SleepData[i].Duration;
			}
			else if (SlpRecord[recordIndex].SleepData[i].State == ALG_SLEEP_DEEP)
			{
				SlpRecord[recordIndex].DeepDuration += SlpRecord[recordIndex].SleepData[i].Duration;
			}
		}
	}
	/* ����˯��ʱ���ж�˯������ */
	if (SlpRecord[recordIndex].SleepDuration > 420)
	{
		SlpRecord[recordIndex].Quality = ALG_SLEEP_EXCELLENT;
	}
	else if (SlpRecord[recordIndex].SleepDuration > 360)
	{
		SlpRecord[recordIndex].Quality = ALG_SLEEP_GOOD;
	}
	else if (SlpRecord[recordIndex].SleepDuration > 300)
	{
		SlpRecord[recordIndex].Quality = ALG_SLEEP_ONLY_FAIR;
	}
	else
	{
		SlpRecord[recordIndex].Quality = ALG_SLEEP_POOR;
	}
}

/*******************************
**��ʼһ��˯�߼�¼
**input: null
**output: null
********************************/
static void sleep_recode_start(void)
{
	memset(&SlpRcdTemp, 0, sizeof(SlpRcdTemp));
	/* ˯�߿�ʼʱ��Ҫ�����жϴ���ʱ�� */
	SlpRcdTemp.rcd.StartUTC = sleep_get_utc() - START_ADD_DURATION * 60;
	SlpRcdTemp.state = SlpProcess.state;

	/* ��ǳ˯ʱ��ο�ʼ */
	SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt].State = ALG_SLEEP_LIGHT;
	SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt].Duration += START_ADD_DURATION;

	SlpProcess.noACTCnt = 0;
	SlpProcess.deepSlpCnt = 0;
	SlpProcess.interval = 0;
}

/*******************************
**����һ��˯�߼�¼�����ж��Ƿ���Ч
**input: null
**output: null
********************************/
static void sleep_recode_save(void)
{
	SlpProcess.state = NONE_SLEEP;
	SlpRcdTemp.state = NONE_SLEEP;

	SlpRcdTemp.rcd.SegmentCnt++;
	SlpRcdTemp.rcd.StopUTC = sleep_get_utc();
	/* ����״̬�������ȥ����ʱ�� */
	if (SlpProcess.noACTCnt > NO_ACT_WAKE_TIME)
	{
		SlpRcdTemp.rcd.StopUTC = SlpRcdTemp.rcd.StopUTC - NO_ACT_WAKE_TIME * 60;
	}
	/* ˯��ʱ����ڽ���ʱ�����ʼʱ�� */
	if (SlpRcdTemp.rcd.StopUTC > SlpRcdTemp.rcd.StartUTC)
	{
		SlpRcdTemp.rcd.SleepDuration = (SlpRcdTemp.rcd.StopUTC - SlpRcdTemp.rcd.StartUTC) / 60;
	}
	else
	{
		SlpRcdTemp.rcd.SleepDuration = 0;
	}
	/* �ж�˯��ʱ���Ƿ�������С��¼ʱ��, �Ƿ��Ǿ���״̬ */
	if ((SlpRcdTemp.rcd.SleepDuration > SLEEP_DURATION_MIN) && (SlpRcdTemp.actFreq >= (SlpRcdTemp.rcd.SleepDuration * ACT_PERCENT)))
	{
		/* ��˯��ʱ�䲻����ϰ��˯�����䣬�򲻼�¼ */
		if (sleep_time_judge() == 0)
		{
			return;
		}
		/* ��˯�߻����¼������˯�߼�¼ */
		sleep_recode_update();
		
		SlpProcess.interval = 0;
		SlpProcess.noACTCnt = 0;
		SlpProcess.deepSlpCnt = 0;
	}
}

/*******************************
**��30�ֵĻ������������ж�
**input: null
**output: sleep_state_e
********************************/
static uint8_t sleep_type_judge(void)
{
	uint8_t minSumCnt = 0, minFreqCnt = 0, sumCnt = 0, freqCnt = 0;

	for (uint8_t i = 0; i < SLEEP_JUDGE_WIN; i++)
	{
		/* ����һ�����ڶ���ֵС�������ֵ�ĸ��� */
		if (MinRcd[i].actSum < SleepCondition.minSumMax)
		{
			minSumCnt++;
		}
		/* ����һ�����ڶ���Ƶ��С�������ֵ�ĸ��� */
		if (MinRcd[i].actCnt < SleepCondition.minFreqMax)
		{
			minFreqCnt++;
		}
		/* ����30�����ڶ���ֵ������ֵ�ĸ��� */
		if (MinRcd[i].actSum > SleepCondition.packSumMax)
		{
			sumCnt++;
		}
		/* ����30�����ڶ���Ƶ�δ�����ֵ�ĸ��� */
		if (MinRcd[i].actCnt > SleepCondition.packFreqMax)
		{
			freqCnt++;
		}
	}

	/* �ж��Ƿ�������˯���� */
	if ((minSumCnt >= SLEEP_JUDGE_WIN) && (minFreqCnt >= SLEEP_JUDGE_WIN) && (sumCnt < SleepCondition.packSumMaxCnt) && (freqCnt < SleepCondition.packFreqMaxCnt))
	{
		return ENTER_SLEEP;
	}

	return NONE_SLEEP;
}
