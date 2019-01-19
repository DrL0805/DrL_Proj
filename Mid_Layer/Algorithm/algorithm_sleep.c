
#include <string.h>
#include "algorithm_sleep.h"

typedef enum
{
	NONE_SLEEP = 0, /* 未入睡 */
	ENTER_SLEEP,	/* 入睡 */
} sleep_state_e;

typedef struct
{
	uint16_t minSumMax;		/* 30分钟内每分钟动作值要小于此值 */
	uint8_t minFreqMax;		/* 30分钟内每分钟动作次数要小于此值 */
	uint16_t packSumMax;	/* 30分钟内每分钟动作值大于此值的个数要小于packSumMaxCnt */
	uint8_t packSumMaxCnt;  /* 30分钟内每分钟动作值大于packSumMax的个数要小于此值 */
	uint8_t packFreqMax;	/* 30分钟内每分钟动作次数大于此值的个数要小于packFreqMaxCnt */
	uint8_t packFreqMaxCnt; /* 30分钟内每分钟动作次数大于packFreqMax的个数要小于此值 */
} sleep_condition_t;

typedef struct
{
	uint8_t hour;
	uint8_t min;
} sleep_rtc_t;

typedef struct
{
	uint16_t actSum; /* 一分钟内动作值 */
	uint8_t actCnt;  /* 一分钟内动作次数 */
} minute_data_t;

/* 当前睡眠状态记录 */
typedef struct
{
	sleep_record_t rcd;
	uint16_t actFreq;
	uint8_t state;
} sleep_record_temp_t;

/* 当前睡眠状态记录 */
typedef struct
{
	uint8_t state;		 /* 当前入睡或醒来状态 */
	uint8_t interval;	/* 每两段睡眠的判定间隔时间计数 */
	uint8_t secCnt;		 /* 秒计数 */
	uint8_t minCnt;		 /* 分计数 */
	uint16_t noACTCnt;   /* 持续无动作计数 */
	uint16_t deepSlpCnt; /* 深睡状态时间计数 */
} sleep_process_t;

#define ABS(a, b) (((a) - (b) > 0) ? (a) - (b) : (b) - (a))

#define ONE_ACT_THRESHOLD 2 /* 单轴动作阈值，小于该值判断为干扰，过滤 */
#define ALL_ACT_THRESHOLD 6 /* 三轴动作总阈值,小于该值判断为无动作状态 */
#define ACT(a, b) (ABS(a, b) < ONE_ACT_THRESHOLD ? 0 : ABS(a, b))

#define WAKE_ACT_SUM_THRE 2200 /* 单次清醒动作阈值，单次超过该值判断为醒来 */
#define WAKE_ACT_FREQ_THRE 30  /* 单次清醒动作频次阈值，单次超过该值判断为醒来 */

#define START_SLEEP_HOUR 20   /* 默认睡眠区间开始时间 */
#define STOP_SLEEP_HOUR 10	/* 默认睡眠区间结束时间 */
#define SLEEP_DURATION_MIN 60 /* 入睡最小记录时间 */
#define START_ADD_DURATION 28 /* 判断进入睡眠后往前推的时间 */
#define JUDGE_INTERVAL 30	 /* 每两段睡眠的判定间隔时间 */

#define DEEP_NO_ACT_FRE_MAX 3		/* 单分钟内深睡判定动作频率阈值 */
#define DEEP_NO_ACT_SUM_MAX 80		/* 单分钟内深睡判定动作总值阈值 */
#define DEEP_SLEEP_MIN_DURATION 10  /* *m 深睡状态段最小时间 */
#define DEEP_SLEEP_DEC_DURATION 5	/* *m 判断进入深睡后往前推的深睡时间,要比DEEP_SLEEP_MIN_DURATION小 */
#define LIGHT_SLEEP_MIN_DURATION 10 /* *m 浅睡状态段最小时间 */

#define MIN_NO_ACT_THS 2	   /* 单分钟内无动作判定频率阈值 */
#define NO_ACT_WAKE_TIME 60	/* 持续无动作唤醒时间 */
#define SLEEP_DURATION_MAX 720 /* *m 单次睡眠最大时间 */
#define ACT_PERCENT 0.5		   /* 当一整段睡眠中动作频次小于此百分比，则判定为静置状态 */

#define SLEEP_JUDGE_WIN 30 /* 睡眠判断窗口为30分钟 */
/* 入睡清醒状态判断经验值 */
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

static minute_data_t MinRcd[SLEEP_JUDGE_WIN]; /* 记录最近半小时内每分钟的动作总值，动作频次记录 */
static sleep_process_t SlpProcess;			  /* 睡眠算法处理过程数据 */
static sleep_record_temp_t SlpRcdTemp;		  /* 当前睡眠记录数据 */
static sleep_record_t SlpRecord[2];			  /* 用于显示的睡眠数据，0点清零，0为显示数据，1为暂存数据 */

static void sleep_recode_start(void);  /* 开始一段睡眠记录 */
static void sleep_recode_save(void);   /* 保存一段睡眠记录 */
static void sleep_recode_update(void); /* 更新睡眠记录 */
static uint8_t sleep_time_judge(void); /* 判断睡眠时间是否在预设时间内 */
static uint8_t sleep_type_judge(void); /* 对30分的滑动窗口数据判断 */

/*******************************
**获取系统的UTC,RTC时间，UTC转RTC, 需要替换为系统的获取UTC和RTC,UTC转RTC的函数
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
**睡眠算法参数初始化，上电调用
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
**睡眠算法处理，每秒钟调用一次，不带心率则传入0xFF
**input: 加速度传感器数据：accValue，心率值：hr
**output: null
********************************/
void alg_sleep_process(int16_t *accelValue, uint8_t hr)
{
	static int8_t accOld[3]; /* 上次的三轴值 */

	int8_t accValue[3];
	uint16_t actSum = 0;
	for (uint8_t i = 0; i < 3; i++)
	{
		/* 转为8bit数据,同时减小干扰 */
		accValue[i] = accelValue[i] >> (16 / ACC_RANGE);
		/* 三轴总动作值 */
		actSum += ACT(accValue[i], accOld[i]);
	}

	/* 一分钟内累加动作值和动作频次 */
	if (SlpProcess.secCnt < 60)
	{
		/* 一分钟内总动作值 */
		MinRcd[SlpProcess.minCnt].actSum += actSum;
		/* 一分钟内动作频次 */
		if (actSum > ALL_ACT_THRESHOLD)
		{
			MinRcd[SlpProcess.minCnt].actCnt++;
		}
	}

	/* 时间计数 */
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

	/* 到达1分钟数据判断处理 */
	if (SlpProcess.secCnt == 59)
	{
		/* 判断间隔计数递增 */
		if (SlpProcess.interval <= JUDGE_INTERVAL)
		{
			SlpProcess.interval++;
		}
		/* 当前连续静置计数加一 */
		if (MinRcd[SlpProcess.minCnt].actCnt < MIN_NO_ACT_THS)
		{
			SlpProcess.noACTCnt++;
		}
		else
		{
			SlpProcess.noACTCnt = 0;
		}
		/* 判断最近30分钟的睡眠状态 */
		SlpProcess.state = sleep_type_judge();
		/* 醒来状态处理 */
		if (SlpRcdTemp.state == NONE_SLEEP)
		{
			/* 入睡条件：1.判断窗口内数据满足条件。2.静置状态计数小于窗口时间减2。3.睡眠判断间隔计数到达。 */
			if ((SlpProcess.state == ENTER_SLEEP) && (SlpProcess.noACTCnt < (SLEEP_JUDGE_WIN - 2)) && (SlpProcess.interval >= JUDGE_INTERVAL))
			{
				/* 醒来状态切换为入睡状态，记录入睡类型和当前入睡时间 */
				sleep_recode_start();
			}
		}
		else
		{
			/* 当前入睡动作次数增加 */
			SlpRcdTemp.actFreq += MinRcd[SlpProcess.minCnt].actCnt;

			/* 小动作判断，持续一段时间小动作则进入深睡状态*/
			if ((MinRcd[SlpProcess.minCnt].actCnt <= DEEP_NO_ACT_FRE_MAX) && (MinRcd[SlpProcess.minCnt].actSum <= DEEP_NO_ACT_SUM_MAX))
			{
				SlpProcess.deepSlpCnt++;
				/* 从浅睡切换到深睡 */
				if ((SlpProcess.deepSlpCnt >= DEEP_SLEEP_MIN_DURATION) && (SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt].State == ALG_SLEEP_LIGHT) && (SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt].Duration >= (DEEP_SLEEP_MIN_DURATION + LIGHT_SLEEP_MIN_DURATION)))
				{
					/* 检测睡眠时间段数组是否会溢出 */
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
				/* 从深睡切换到浅睡 */
				if ((SlpProcess.deepSlpCnt > DEEP_SLEEP_MIN_DURATION) && (SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt].State == ALG_SLEEP_DEEP))
				{
					/* 检测睡眠时间段数组是否会溢出 */
					if (SlpRcdTemp.rcd.SegmentCnt < (SLEEP_SEGMENT_MAX - 1))
					{
						SlpRcdTemp.rcd.SegmentCnt++;
						SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt].State = ALG_SLEEP_LIGHT;
					}
				}
				/* 清除连续深睡状态计数 */
				SlpProcess.deepSlpCnt = 0;
			}
			/* 睡眠状态时间累加 */
			SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt].Duration++;

			/* 检测到窗口内数据为无睡眠状态，结束本次睡眠 */
			if (SlpProcess.state == NONE_SLEEP)
			{
				sleep_recode_save();
			}
			/* 当检测到连续处于疑似静置状态，结束本次睡眠 */
			else if (SlpProcess.noACTCnt > NO_ACT_WAKE_TIME)
			{
				sleep_recode_save();
			}
			/* 单分钟内动作值和动作频次超出，结束本次睡眠 */
			else if ((MinRcd[SlpProcess.minCnt].actSum > WAKE_ACT_SUM_THRE) || (MinRcd[SlpProcess.minCnt].actCnt > WAKE_ACT_FREQ_THRE))
			{
				sleep_recode_save();
			}
			/* 睡眠时间大于12小时，结束本次睡眠 */
			else if ((sleep_get_utc() - SlpRcdTemp.rcd.StartUTC) / 60 > SLEEP_DURATION_MAX)
			{
				sleep_recode_save();
			}
			/* 心率脱腕状态 */
			else if (hr == 0)
			{
				sleep_recode_save();
			}
		}
	}

	/* 保存上一秒的加速度三轴值 */
	for (uint8_t i = 0; i < 3; i++)
	{
		accOld[i] = accValue[i];
	}
}

/*******************************
**获取睡眠记录详情
**input: null
**output: 睡眠记录信息：sleep_record *record
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
**清除前一天的睡眠记录，0点时调用，算法内清除本日睡眠记录，类似于清计步信息
**input: null
**output: null
********************************/
void alg_sleep_clr_record(void)
{
	memcpy(&SlpRecord[0], &SlpRecord[1], sizeof(sleep_record_t));
	memset(&SlpRecord[1], 0, sizeof(sleep_record_t));
}

/*******************************
**用户交互操作时调用此函数，则强制判断清醒，如操作按键，充电等情况
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
**判断此段睡眠是否有落在习惯睡眠区间内，不在此区间内不记录
**input: null
**output: 不在：0，在：1
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
**将睡眠缓存记录更新至睡眠记录
**input: null
**output: null
********************************/
static void sleep_recode_update(void)
{
	uint8_t recordIndex = 0;

	sleep_rtc_t rtcTime = sleep_utc_to_rtc(SlpRcdTemp.rcd.StopUTC);
	/* 0点至开始时间的睡眠保存在今日睡眠 */
	if (rtcTime.hour < START_SLEEP_HOUR)
	{
		recordIndex = 0;
	}
	/* 大于开始时间的睡眠保存在下一天 */
	else if (rtcTime.hour >= START_SLEEP_HOUR)
	{
		recordIndex = 1;
	}
	/* 如果还没数据 */
	if (SlpRecord[recordIndex].StartUTC == 0)
	{
		memcpy(&SlpRecord[recordIndex], &SlpRcdTemp.rcd, sizeof(sleep_record_t));
	}
	/* 如果已有数据 */
	else
	{
		/* 如果本次睡眠的开始时间和上次睡眠的结束时间相差2小时 */
		if ((SlpRcdTemp.rcd.StartUTC - SlpRecord[recordIndex].StopUTC) > 7200)
		{
			/* 如果新产生的睡眠时间大于之前的时间，则重写睡眠时间，否则丢掉本次睡眠 */
			// if (SlpRcdTemp.rcd.SleepDuration > SlpRecord[recordIndex].SleepDuration)
			// {
				memcpy(&SlpRecord[recordIndex], &SlpRcdTemp.rcd, sizeof(sleep_record_t));
			// }
		}
		/* 两段睡眠拼接 */
		else
		{
			/* 睡眠总时间段不超过最大时间段 */
			if ((SlpRecord[recordIndex].SegmentCnt + SlpRcdTemp.rcd.SegmentCnt) < (SLEEP_SEGMENT_MAX - 1))
			{
				/* 增加清醒时间段 */
				SlpRecord[recordIndex].SleepData[SlpRecord[recordIndex].SegmentCnt].State = ALG_SLEEP_WAKE;
				SlpRecord[recordIndex].SleepData[SlpRecord[recordIndex].SegmentCnt].Duration = (SlpRcdTemp.rcd.StartUTC - SlpRecord[recordIndex].StopUTC) / 60;
				SlpRecord[recordIndex].SegmentCnt++;
				/* 缓存时间段拼接至已有时间段上 */
				for (uint8_t i = 0; i < SlpRcdTemp.rcd.SegmentCnt; i++)
				{
					SlpRecord[recordIndex].SleepData[SlpRecord[recordIndex].SegmentCnt].State = SlpRcdTemp.rcd.SleepData[i].State;
					SlpRecord[recordIndex].SleepData[SlpRecord[recordIndex].SegmentCnt].Duration = SlpRcdTemp.rcd.SleepData[i].Duration;
					SlpRecord[recordIndex].SegmentCnt++;
				}
				/* 睡眠结束时间后移 */
				SlpRecord[recordIndex].StopUTC = SlpRcdTemp.rcd.StopUTC;
			}
		}
	}
	/* 睡眠其他数据转换及计算，开始结束时间UTC转RTC */
	sleep_rtc_t startRtc, stopRtc;
	startRtc = sleep_utc_to_rtc(SlpRecord[recordIndex].StartUTC);
	stopRtc = sleep_utc_to_rtc(SlpRecord[recordIndex].StopUTC);
	SlpRecord[recordIndex].StartHour = startRtc.hour;
	SlpRecord[recordIndex].StartMin = startRtc.min;
	SlpRecord[recordIndex].StopHour = stopRtc.hour;
	SlpRecord[recordIndex].StopMin = stopRtc.min;
	/* 累加前清0 */
	SlpRecord[recordIndex].WakeDuration = 0;
	SlpRecord[recordIndex].LightDuration = 0;
	SlpRecord[recordIndex].DeepDuration = 0;
	SlpRecord[recordIndex].RemDuration = 0;
	/* 循环累加计算各睡眠阶段时长 */
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
	/* 总时长等于结束时间减开始时间 */
	SlpRecord[recordIndex].TotalDuration = (SlpRecord[recordIndex].StopUTC - SlpRecord[recordIndex].StartUTC) / 60;
	/* 睡眠时长等于总时长减清醒时长 */
	SlpRecord[recordIndex].SleepDuration = SlpRecord[recordIndex].TotalDuration - SlpRecord[recordIndex].WakeDuration;
	/* 时间缺失则补偿 */
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
	/* 时间多出则减掉 */
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
	/* 根据睡眠时长判断睡眠质量 */
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
**开始一段睡眠记录
**input: null
**output: null
********************************/
static void sleep_recode_start(void)
{
	memset(&SlpRcdTemp, 0, sizeof(SlpRcdTemp));
	/* 睡眠开始时间要加上判断窗口时间 */
	SlpRcdTemp.rcd.StartUTC = sleep_get_utc() - START_ADD_DURATION * 60;
	SlpRcdTemp.state = SlpProcess.state;

	/* 从浅睡时间段开始 */
	SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt].State = ALG_SLEEP_LIGHT;
	SlpRcdTemp.rcd.SleepData[SlpRcdTemp.rcd.SegmentCnt].Duration += START_ADD_DURATION;

	SlpProcess.noACTCnt = 0;
	SlpProcess.deepSlpCnt = 0;
	SlpProcess.interval = 0;
}

/*******************************
**结束一段睡眠记录，并判断是否有效
**input: null
**output: null
********************************/
static void sleep_recode_save(void)
{
	SlpProcess.state = NONE_SLEEP;
	SlpRcdTemp.state = NONE_SLEEP;

	SlpRcdTemp.rcd.SegmentCnt++;
	SlpRcdTemp.rcd.StopUTC = sleep_get_utc();
	/* 静置状态结束则减去静置时间 */
	if (SlpProcess.noACTCnt > NO_ACT_WAKE_TIME)
	{
		SlpRcdTemp.rcd.StopUTC = SlpRcdTemp.rcd.StopUTC - NO_ACT_WAKE_TIME * 60;
	}
	/* 睡眠时间等于结束时间减开始时间 */
	if (SlpRcdTemp.rcd.StopUTC > SlpRcdTemp.rcd.StartUTC)
	{
		SlpRcdTemp.rcd.SleepDuration = (SlpRcdTemp.rcd.StopUTC - SlpRcdTemp.rcd.StartUTC) / 60;
	}
	else
	{
		SlpRcdTemp.rcd.SleepDuration = 0;
	}
	/* 判断睡眠时间是否满足最小记录时间, 是否是静置状态 */
	if ((SlpRcdTemp.rcd.SleepDuration > SLEEP_DURATION_MIN) && (SlpRcdTemp.actFreq >= (SlpRcdTemp.rcd.SleepDuration * ACT_PERCENT)))
	{
		/* 如睡眠时间不处于习惯睡眠区间，则不记录 */
		if (sleep_time_judge() == 0)
		{
			return;
		}
		/* 将睡眠缓存记录更新至睡眠记录 */
		sleep_recode_update();
		
		SlpProcess.interval = 0;
		SlpProcess.noACTCnt = 0;
		SlpProcess.deepSlpCnt = 0;
	}
}

/*******************************
**对30分的滑动窗口数据判断
**input: null
**output: sleep_state_e
********************************/
static uint8_t sleep_type_judge(void)
{
	uint8_t minSumCnt = 0, minFreqCnt = 0, sumCnt = 0, freqCnt = 0;

	for (uint8_t i = 0; i < SLEEP_JUDGE_WIN; i++)
	{
		/* 满足一分钟内动作值小于最大阈值的个数 */
		if (MinRcd[i].actSum < SleepCondition.minSumMax)
		{
			minSumCnt++;
		}
		/* 满足一分钟内动作频次小于最大阈值的个数 */
		if (MinRcd[i].actCnt < SleepCondition.minFreqMax)
		{
			minFreqCnt++;
		}
		/* 满足30分钟内动作值大于阈值的个数 */
		if (MinRcd[i].actSum > SleepCondition.packSumMax)
		{
			sumCnt++;
		}
		/* 满足30分钟内动作频次大于阈值的个数 */
		if (MinRcd[i].actCnt > SleepCondition.packFreqMax)
		{
			freqCnt++;
		}
	}

	/* 判断是否满足入睡条件 */
	if ((minSumCnt >= SLEEP_JUDGE_WIN) && (minFreqCnt >= SLEEP_JUDGE_WIN) && (sumCnt < SleepCondition.packSumMaxCnt) && (freqCnt < SleepCondition.packFreqMaxCnt))
	{
		return ENTER_SLEEP;
	}

	return NONE_SLEEP;
}
