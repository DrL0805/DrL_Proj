#ifndef _ALGORITHM_SLEEP_H_
#define _ALGORITHM_SLEEP_H_

#include <stdint.h>

#define ACC_RANGE	2  /* 采样范围：+-2g,+-4g,+-8g,+-16g */

/* 睡眠质量 */
typedef enum
{
	ALG_SLEEP_EXCELLENT,
	ALG_SLEEP_GOOD,
	ALG_SLEEP_ONLY_FAIR,
	ALG_SLEEP_POOR,
} sleep_quality_e;

/* 睡眠状态 */
typedef enum
{
	ALG_SLEEP_WAKE,  /* 清醒 */
	ALG_SLEEP_LIGHT, /* 浅睡 */
	ALG_SLEEP_DEEP,  /* 深睡 */
	ALG_SLEEP_REM,   /* 快速眼动 */
} sleep_period_e;

/* 睡眠详细时长和状态 */
typedef struct
{
	sleep_period_e State; /* 本段睡眠的睡眠状态 */
	uint16_t Duration;	/* *m 睡眠时长:分钟 */
} sleep_segment_t;

/* 睡眠最大状态段数 */
#define SLEEP_SEGMENT_MAX 30

/* 睡眠记录信息 */
typedef struct
{
	uint8_t StartHour;		 /* 开始时间：时 , 睡眠开始结束时间RTC格式 */
	uint8_t StartMin;		 /* 开始时间：分 */
	uint8_t StopHour;		 /* 结束时间：时 */
	uint8_t StopMin;		 /* 结束时间：分 */
	uint32_t StartUTC;		 /* 睡眠开始UTC , 睡眠开始结束时间UTC格式 */
	uint32_t StopUTC;		 /* 睡眠结束UTC */
	uint16_t SleepDuration;  /* *m 总睡眠时长，不包括清醒时间 */
	sleep_quality_e Quality; /* 睡眠质量 */

	uint16_t TotalDuration; /* *m 总睡眠时长：包括清醒时长，等于下面四个时长的总和 */
	uint16_t WakeDuration;  /* *m 清醒时长 */
	uint16_t LightDuration; /* *m 浅睡时长 */
	uint16_t DeepDuration;  /* *m 深睡时长 */
	uint16_t RemDuration;   /* *m 快速眼动时长 */

	uint8_t SegmentCnt;							  /* 从开始时间到结束时间有几个详细时间段 */
	sleep_segment_t SleepData[SLEEP_SEGMENT_MAX]; /* 每段具体时长和状态 */
} sleep_record_t;

/*******************************
**睡眠算法参数初始化，上电调用
**input: null
**output: null 
********************************/
void alg_sleep_init(void);

/*******************************
**睡眠算法处理，每秒钟调用一次，不带心率则传入0xFF
**input: 加速度传感器数据：accValue，心率值：hr
**output: null 
********************************/
void alg_sleep_process(int16_t *accelValue, uint8_t hr);

/*******************************
**获取睡眠记录详情
**input: null
**output: 睡眠记录信息：sleep_record *record
********************************/
void alg_sleep_get_record(sleep_record_t *sleepRecord);

/*******************************
**清除前一天的睡眠记录，0点时调用，算法内清除本日睡眠记录，类似于清计步信息
**input: null
**output: null
********************************/
void alg_sleep_clr_record(void);

/*******************************
**用户交互操作时调用此函数，则强制判断清醒，如操作按键，充电等情况
**input: null
**output: null
********************************/
void alg_sleep_wake(void);

#endif // _ALGORITHM_SLEEP_H_
