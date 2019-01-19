#ifndef _ALGORITHM_COMMON_H_
#define _ALGORITHM_COMMON_H_

#include <stdint.h>

/* 心率区间枚举 */
typedef enum
{
    HR_ZONE_0,
    HR_ZONE_1,
    HR_ZONE_2,
    HR_ZONE_3,
    HR_ZONE_4,
    HR_ZONE_5,
} hrZone_e;

/* 心率区间时长*/
typedef struct
{
    uint32_t HrZone1;
    uint32_t HrZone2;
    uint32_t HrZone3;
    uint32_t HrZone4;
    uint32_t HrZone5;
} hrZoneDuration_t;

/* 心率区间范围 */
typedef struct
{
    uint8_t HrZone0;
    uint8_t HrZone1;
    uint8_t HrZone2;
    uint8_t HrZone3;
    uint8_t HrZone4;
    uint8_t HrZone5;
} hrZoneRange_t;

/* 泳姿枚举 */
typedef enum
{
    SWIM_NONE_STYLE,   /* 未识别 */
    SWIM_FREESTYLE,    /* 自由泳 */
    SWIM_BREASTSTROKE, /* 蛙泳 */
    SWIM_BACKSTROKE,   /* 仰泳 */
    SWIM_BUTTERFLY,    /* 蝶泳 */
    SWIM_MEDLEY,       /* 混合泳 */
} swimStyle_e;

/* 根据两点经纬度计算距离 */
double alg_common_gps_distance(float lat1, float lon1, float lat2, float lon2);

/*******************************
**获取心率区间范围值
**input: age 年龄
**output: hrZoneRange_t 心率区间值
********************************/
void alg_common_get_hrzone(uint8_t age, hrZoneRange_t *hrZone);

#endif
