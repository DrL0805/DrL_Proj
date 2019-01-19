#ifndef _ALGORITHM_RUNNING_H_
#define _ALGORITHM_RUNNING_H_

#include <stdint.h>
#include "algorithm_common.h"

/* 跑步实时运动信息 */
typedef struct
{
    uint16_t Pace;   /* s/km 配速 实时更新 */
    uint16_t Freq;   /* step/min 步频 实时更新 */
    uint16_t Stride; /* cm 步幅 实时更新*/
    uint8_t HR;      /* 次 心率记录 */
    union {
        float f;
        uint8_t u8[4];
    } Longitude; /* 经度 */
    union {
        float f;
        uint8_t u8[4];
    } Latitude; /* 纬度 */
} runningRealTimeData_t;

/* 跑步历史信息 */
typedef struct
{
    uint32_t StartUTC;               /* 开始UTC时间戳 */
	uint32_t StopUTC;                /* 结束UTC时间戳 */
    uint32_t Duration;               /* *s 总时长*/
	uint32_t ValidDuration;          /* *s 活动时长*/
    hrZoneDuration_t HrZoneDuration; /* *S 心率区间时长 */
    uint32_t Step;                   /* *step 跑步总步数 */
    uint16_t Distance;               /* *m 跑步总距离 */
    uint16_t Calorie;                /* *kcal 卡路里 */
    uint16_t PaceAVG;                /* s/km 平均配速 */
    uint16_t FreqAVG;                /* step/min 平均步频*/
    uint16_t StrideAVG;              /* cm 平均步幅*/
    uint8_t HrAVG;                   /* 平均心率 */
    uint8_t HrMax;                   /* 最大心率 */
} runningRecord_t;

/* 跑步运动信息 */
typedef struct
{
    hrZone_e HrZone;                    /* 当前心率区间 */
    runningRealTimeData_t RealTimeData; /* 跑步实时数据 */
    runningRecord_t RecordData;         /* 跑步记录数据 */
} runningInfo_t;

/*******************************
**开始跑步,初始化数据，进入跑步场景时调用
**input: 人体模型数据：sex age height weight. 当前UTC时间：utc. 当前计步步数：step. 当前高度：altitude.
**output: null
********************************/
void alg_running_start(uint8_t sex, uint8_t age, uint8_t height, uint8_t weight, uint32_t utc, uint32_t step, int32_t altitude); /* 跑步开始,传入人体信息,utc时间,当前计步值,当前高度 */

/*******************************
**跑步过程数据更新,进入跑步场景后每秒调用一次
**input: 当前计步步数：step. 当前高度：altitude. 当前心率：hr. 当前经纬度：longitude latitude
**output: null
********************************/
void alg_running_update(uint32_t step, int32_t altitude, uint8_t hr, float longitude, float latitude); /* 每1秒钟调用一次，传入当前的计步值,高度,心率,经纬度 */

/*******************************
**获取当前跑步数据
**input: null
**output: 跑步数据结构体：runningInfo_t 
********************************/
void alg_running_get_info(runningInfo_t *info); /* 获取当前的跑步信息 */

/*******************************
**结束跑步，退出跑步场景
**input: 当前UTC时间
**output: null
********************************/
void alg_running_stop(uint32_t utc); /* 结束本次跑步 */

/*******************************
**暂停跑步场景
**input: null
**output: null 
********************************/
void alg_running_pause(void); /* 暂停跑步场景 */

/*******************************
**继续跑步场景
**input: null
**output: null 
********************************/
void alg_running_continue(uint32_t step, int32_t altitude, float longitude, float latitude); /* 继续跑步场景 */

#endif
