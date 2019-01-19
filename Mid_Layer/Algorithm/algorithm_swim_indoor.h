#ifndef _ALGORITHM_SWIM_INDOOR_H_
#define _ALGORITHM_SWIM_INDOOR_H_

#include <stdint.h>
#include <stdbool.h>
#include "algorithm_common.h"

/* 游泳实时运动信息 */
typedef struct
{
    uint8_t StrokeRate; /* *次/min 实时划水率 */
    uint8_t HR;         /* 次 心率记录 */
} swimIndoorRealTimeData_t;

/* 单趟信息 */
typedef struct
{
    uint16_t LapDuration;  /* *s 本趟时长 */
    uint8_t LapStroke;     /* *次 本趟划水次数 */
    uint8_t LapStrokeRate; /* *次/min 本趟划水率 */
    uint16_t LapPace;      /* *s/100m 本趟配速 */
    uint16_t LapSwolf;     /* *划水数+划水用秒数 本趟Swolf */
    swimStyle_e LapStyle;  /* 本趟泳姿 */
} swimIndoorLapData_t;

/* 游泳历史记录信息 */
typedef struct
{
    uint32_t StartUTC;               /* 开始UTC时间戳 */
    uint32_t StopUTC;                /* 结束UTC时间戳 */
    uint32_t Duration;               /* *s 总时长, 不记录暂停时长 */
    uint32_t ValidDuration;          /* *s 活动时长, 只记录有活动的时长 */
    hrZoneDuration_t HrZoneDuration; /* *s 心率区间时长,每个心率区间持续的时间 */
    uint16_t Distance;               /* *m 总距离 */
    uint16_t Stroke;                 /* *次 总划水次数 */
    uint16_t Calorie;                /* *kcal 总卡路里 */
    uint16_t Laps;                   /* *趟 总趟数 */
    uint16_t PaceAVG;                /* *s/100m 平均配速 */
    uint16_t StrokeAVG;              /* *次/趟 平均划水次数 */
    uint16_t StrokeRateAVG;          /* *次/min 平均划水率 */
    uint16_t SwolfAvg;               /* 平均swolf */
    uint8_t HrAVG;                   /* 平均心率 */
    uint8_t HrMax;                   /* 最大心率 */
    swimStyle_e Style;               /* 总泳姿 */
} swimIndoorRecord_t;

/* 游泳运动信息 */
typedef struct
{
    hrZone_e HrZone;                       /* 当前心率区间 */
    swimIndoorRealTimeData_t RealTimeData; /* 游泳实时数据 */
    swimIndoorLapData_t LapData;           /* 游泳单趟数据 */
    swimIndoorRecord_t RecordData;         /* 游泳记录数据 */
} swimIndoorInfo_t;

/*******************************
**开始游泳,初始化数据，进入游泳场景时调用
**input: 人体模型数据：sex age height weight. 当前UTC时间：utc. 泳池长度：poolLen cm
**output: null
********************************/
void alg_swimIndoor_start(uint8_t sex, uint8_t age, uint8_t height, uint8_t weight, uint32_t utc, uint16_t poolLen); /* 游泳开始,传入人体信息,utc时间,泳池长度 */

/*******************************
**游泳运动数据更新,进入游泳场景按25HZ频率调用, 用于计算划水数，泳姿识别，转身等运动数据
**input: 加速度三轴数据：accelValue. 地磁三轴数据：magValue
**output: null
********************************/
void alg_swimIndoor_calculate(int16_t *accelValue, int16_t *magValue);

/*******************************
**游泳过程数据更新,进入游泳场景后每秒调用一次
**input: 当前心率：hr.
**output: bool true:单趟数据更新，请读取单趟数据保存
********************************/
bool alg_swimIndoor_update(uint8_t hr); /* 每1秒钟调用一次，传入当前的心率 */

/*******************************
**获取当前游泳数据
**input: null
**output: 游泳数据结构体：swimIndoorInfo_t 
********************************/
void alg_swimIndoor_get_info(swimIndoorInfo_t *info); /* 获取当前的游泳信息 */

/*******************************
**结束游泳，退出游泳场景
**input: 当前UTC时间
**output: null
********************************/
void alg_swimIndoor_stop(uint32_t utc); /* 结束本次游泳 */

/*******************************
**暂停游泳场景
**input: null
**output: null 
********************************/
void alg_swimIndoor_pause(void); /* 暂停游泳场景 */

/*******************************
**继续游泳场景
**input: null
**output: null 
********************************/
void alg_swimIndoor_continue(void); /* 继续游泳场景 */

#endif
