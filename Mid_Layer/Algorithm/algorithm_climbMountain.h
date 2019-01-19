#ifndef _ALGORITHM_CLIMB_MOUNTAIN_H_
#define _ALGORITHM_CLIMB_MOUNTAIN_H_

#include <stdint.h>
#include "algorithm_common.h"

/* 登山实时记录信息 */
typedef struct
{
    int16_t Altitude; /* m 海拔 */
    int16_t Speed;    /* m/h 当前垂直速度 */
    uint8_t Hr;       /* 心率 */
    union {
        float f;
        uint8_t u8[4];
    } Longitude; /* 经度 */
    union {
        float f;
        uint8_t u8[4];
    } Latitude; /* 纬度 */
} climbMountainRealTimeData_t;

/* 登山历史信息 */
typedef struct
{
    uint32_t StartUTC;               /* 开始UTC时间戳 */
    uint32_t StopUTC;                /* 结束UTC时间戳 */
    uint32_t Duration;               /* *s 总时长*/
    uint32_t ValidDuration;          /* *s 活动时长*/
    hrZoneDuration_t HrZoneDuration; /* *S 心率区间时长 */
    uint32_t Step;                   /* *step 总步数 */
    uint32_t Distance;               /* *m 登山总距离 */
    uint16_t UpAltitude;             /* m 总爬升高度 */
    uint16_t DownAltitude;           /* m 总下降高度 */
    int16_t HighestAltitude;         /* m 登山过程最高海拔 */
    int16_t LowestAltitude;          /* m 登山过程最低海拔 */
    uint16_t SpeedAVG;               /* m/h 平均速度 */
    uint16_t Calorie;                /* *kcal 卡路里 */
    uint8_t HrAVG;                   /* 平均心率 */
    uint8_t HrMax;                   /* 最大心率 */
} climbMountainRecord_t;

/* 登山运动信息 */
typedef struct
{
    hrZone_e HrZone;                          /* 当前心率区间 */
    climbMountainRealTimeData_t RealTimeData; /* 登山实时数据 */
    climbMountainRecord_t RecordData;         /* 登山记录数据 */
} climbMountainInfo_t;

/*******************************
**开始登山,初始化数据，进入登山场景时调用
**input: 人体模型数据：sex age height weight. 当前UTC时间：utc. 当前计步步数：step. 当前高度：altitude.
**output: null
********************************/
void alg_climbMountain_start(uint8_t sex, uint8_t age, uint8_t height, uint8_t weight, uint32_t utc, uint32_t step, int32_t altitude); /* 爬山开始,传入人体信息,utc时间,当前计步值,当前高度 */

/*******************************
**登山过程数据更新,进入登山场景后每秒调用一次
**input: 当前计步步数：step. 当前高度：altitude. 当前心率：hr. 当前经纬度：longitude latitude
**output: null
********************************/
void alg_climbMountain_update(uint32_t step, int32_t altitude, uint8_t hr, float longitude, float latitude); /* 每1秒钟调用一次，传入当前的计步值，海拔高度, 心率, 经纬度 */

/*******************************
**获取当前登山数据
**input: null
**output: 登山数据结构体：climbMountainInfo_t 
********************************/
void alg_climbMountain_get_info(climbMountainInfo_t *info); /* 获取当前的登山信息 */

/*******************************
**结束登山，退出登山场景
**input: 当前UTC时间
**output: null
********************************/
void alg_climbMountain_stop(uint32_t utc); /* 结束本次登山 */

/*******************************
**暂停登山场景
**input: null
**output: null 
********************************/
void alg_climbMountain_pause(void); /* 暂停登山场景 */

/*******************************
**继续登山场景
**input: null
**output: null 
********************************/
void alg_climbMountain_continue(uint32_t step, int32_t altitude, float longitude, float latitude); /* 继续登山场景 */

#endif
