#include <math.h>
#include <stdint.h>
#include "algorithm_common.h"

#define PI 3.1415926
#define EARTH_R 6371.0

static double toRadians(double x)
{
    return x * PI / 180.0;
}

/* 根据两点经纬度计算距离 */
double alg_common_gps_distance(float lat1, float lon1, float lat2, float lon2)
{
    double latAvg = toRadians(lat1 + lat2) * 0.5;
    double disLat = EARTH_R * cos(latAvg) * toRadians(lon1 - lon2);
    double disLon = EARTH_R * toRadians(lat1 - lat2);
    return sqrt(disLat * disLat + disLon * disLon);
}

/*******************************
**获取心率区间范围值
**input: age 年龄
**output: hrZoneRange_t 心率区间值
********************************/
void alg_common_get_hrzone(uint8_t age, hrZoneRange_t *hrZone)
{
    hrZone->HrZone0 = (220 - age) * 0.50;
    hrZone->HrZone1 = (220 - age) * 0.60;
    hrZone->HrZone2 = (220 - age) * 0.70;
    hrZone->HrZone3 = (220 - age) * 0.80;
    hrZone->HrZone4 = (220 - age) * 0.90;
    hrZone->HrZone5 = (220 - age);
}
