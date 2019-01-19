
#include <string.h>
#include "algorithm_climbMountain.h"

#define ABS(a, b) (((a) - (b) > 0) ? (a) - (b) : (b) - (a))

/* 登山算法缓存数据 */
typedef struct
{
    int32_t altitude;    /* cm 高度数据缓存 */
    uint16_t betterDist; /* cm 更准确的距离 */
    uint8_t step;        /* 步数 */
} climbMtBuffer_t;

/* 登山算法体征信息 */
typedef struct
{
    uint8_t weight; /* 体重：单位：kg */
    uint8_t height; /* 身高：单位：cm */
    uint8_t sex;    /* 性别 */
    uint8_t age;    /* 年龄 */
} climbMtBodyInfo_t;

/* 登山心率区间 */
typedef struct
{
    uint8_t Z0Max;
    uint8_t Z1Max;
    uint8_t Z2Max;
    uint8_t Z3Max;
    uint8_t Z4Max;
    uint8_t Z5Max;
} climbMtHrZoneThs_t;

typedef enum
{
    CLIMBMT_RUN = 0,
    CLIMBMT_PAUSE,
} climbMtState_e;

/* 登山场景过程数据 */
typedef struct
{
    climbMtBodyInfo_t body;     /* 人体信息 */
    climbMtHrZoneThs_t zoneThs; /* 心率区间阈值 */
    climbMtState_e state;       /* 暂停标志 */
    uint32_t hrSum;             /* 登山过程心率总和 */
    uint32_t distanceCM;        /* cm 登山总距离 */
    uint32_t oldStep;           /* 上一秒总步数 */
    int32_t oldAltitude;        /* cm 记录上次的高度 */
    uint16_t calorieParm;       /* 计算卡路里的参数 */
    uint16_t upTime;            /* *s 上山总时间 */
    uint16_t downTime;          /* *s 下山总时间 */
    uint32_t upAltitude;        /* *cm 上山总高度 */
    uint32_t downAltitude;      /* *cm 下山总高度 */
    float oldLongitude;         /* 上次的经度 */
    float oldLatitude;          /* 上次的纬度 */
    uint8_t climbBuffIdx;       /* 运动过程数据索引 */
    uint8_t secCnt;             /* 秒计数 */
} climbMtProcess_t;

#define GPS_DIST_MAX 800 /* cm 登山GPS变化2秒最大距离 */
#define GPS_DIST_MIN 80  /* cm 登山GPS变化2秒最小距离 */

#define ALTITUDE_CHANGE_MAX 200 /* cm 登山高度变化2秒最大高度 */
#define ALTITUDE_CHANGE_MIN 10   /* cm 登山高度变化2秒最小高度 */
#define ALTITUDE_CHANGE_MAX_20 1000 /* cm 登山高度变化20秒最大高度 */
#define ALTITUDE_CHANGE_MIN_20 100   /* cm 登山高度变化20秒最小高度 */

static climbMountainInfo_t ClimbMtInfo; /* 登山数据 */
static climbMtProcess_t ClimbMtProcess; /* 登山过程数据 */

#define CLIMBMT_BUFFER_MAX 10
static climbMtBuffer_t ClimbMtBuffer[CLIMBMT_BUFFER_MAX]; /* 缓存一段时间的运动过程数据 */

/* 平滑 */
#define SMOOTH_NUM 4
static uint8_t smoothCnt = 0;
static float smoothArrX[SMOOTH_NUM];
static float smoothArrY[SMOOTH_NUM];

/* 上山负重0-9磅卡路里系数 */
#define CLIMB_HILL_0_9 0.0000752 /* 6.5 * 0.00001157 */
/* 下山卡路里系数 */
#define CLIMB_DOWN 0.00004628 /* 4 * 0.00001157 */

/*******************************
**开始登山,初始化数据，进入登山场景时调用
**input: 人体模型数据：sex age height weight. 当前UTC时间：utc. 当前计步步数：step. 当前高度：altitude.
**output: null
********************************/
void alg_climbMountain_start(uint8_t sex, uint8_t age, uint8_t height, uint8_t weight, uint32_t utc, uint32_t step, int32_t altitude)
{
    memset(&ClimbMtInfo, 0, sizeof(ClimbMtInfo));
    ClimbMtInfo.RecordData.StartUTC = utc;

    memset(ClimbMtBuffer, 0, sizeof(ClimbMtBuffer));

    memset(&ClimbMtProcess, 0, sizeof(ClimbMtProcess));
    ClimbMtProcess.state = CLIMBMT_RUN;
    ClimbMtProcess.oldStep = step;
    ClimbMtProcess.oldAltitude = altitude;
    ClimbMtProcess.body.weight = weight;
    ClimbMtProcess.body.height = height;
    ClimbMtProcess.body.sex = sex;
    ClimbMtProcess.body.age = age;

    ClimbMtProcess.zoneThs.Z0Max = (220 - age) * 0.50;
    ClimbMtProcess.zoneThs.Z1Max = (220 - age) * 0.60;
    ClimbMtProcess.zoneThs.Z2Max = (220 - age) * 0.70;
    ClimbMtProcess.zoneThs.Z3Max = (220 - age) * 0.80;
    ClimbMtProcess.zoneThs.Z4Max = (220 - age) * 0.90;
    ClimbMtProcess.zoneThs.Z5Max = (220 - age);
	
	smoothCnt = 0;
	for(uint8_t i = 0; i < SMOOTH_NUM; i++)
	{		
		smoothArrX[i] = 0;
		smoothArrY[i] = 0;
	}

    /* 根据性别计算卡路里基数 */
    if (age == 0)
    {
        /* 男 */
        ClimbMtProcess.calorieParm = 66.5 + (13.75 * weight) + (5.003 * height) - (6.775 * age); //Men
    }
    else
    {
        /* 女 */
        ClimbMtProcess.calorieParm = 655.1 + (9.563 * weight) + (1.850 * height) - (4.676 * age); //Women
    }
}

/*******************************
**登山过程数据更新,进入登山场景后每秒调用一次
**input: 当前计步步数：step. 当前高度：altitude. 当前心率：hr. 当前经纬度：longitude latitude
**output: null
********************************/
void alg_climbMountain_update(uint32_t step, int32_t altitude, uint8_t hr, float longitude, float latitude)
{
    uint8_t nowStep = 0;
    uint16_t gpsDist = 0, stepDist = 0, betterDist = 0;
    int16_t nowAltitude = 0;
	int32_t changeAltitude = 0;

    /* 登山暂停状态下不做处理 */
    if (ClimbMtProcess.state == CLIMBMT_PAUSE)
    {
        return;
    }

    /* 步数及时长累加 */
    if (step > ClimbMtProcess.oldStep)
    {
        nowStep = step - ClimbMtProcess.oldStep;
    }
    ClimbMtInfo.RecordData.Duration += 1;   /* *s 登山总时间 */
    ClimbMtInfo.RecordData.Step += nowStep; /* 登山总步数增加 */

    ClimbMtProcess.secCnt++;
    if (ClimbMtProcess.secCnt == 2)
    {
        ClimbMtProcess.secCnt = 0;
		
		float xSum = 0, ySum = 0;
		uint8_t zeroCnt = 0;
		if (smoothCnt >= SMOOTH_NUM)
		{
			for (uint8_t i = 0; i < (SMOOTH_NUM - 1); i++)
			{
				smoothArrX[i] = smoothArrX[i + 1];
				smoothArrY[i] = smoothArrY[i + 1];
			}
			smoothCnt = SMOOTH_NUM - 1;
		}
		smoothArrX[smoothCnt] = longitude;
		smoothArrY[smoothCnt] = latitude;
		smoothCnt++;
		for (uint8_t i = 0; i < smoothCnt; i++)
		{
			if((smoothArrX[i] && smoothArrY[i]) != 0)
			{
				xSum += smoothArrX[i];
				ySum += smoothArrY[i];
			}
			else
			{
				zeroCnt++;
			}
		}
		if((smoothCnt - zeroCnt) != 0)
		{
			longitude = xSum / (smoothCnt - zeroCnt);
			latitude = ySum / (smoothCnt - zeroCnt);
		}
		else
		{
			longitude = 0;
			latitude = 0;
		}

        /* 计算当前2秒的GPS距离和步数距离 */
        gpsDist = alg_common_gps_distance(latitude, longitude, ClimbMtProcess.oldLatitude, ClimbMtProcess.oldLongitude) * 100000; /* cm 计算gps距离 */
        stepDist = ClimbMtProcess.body.height * nowStep * 0.45;                                                                   /* cm 步数计算登山距离 = 身高*0.45*步数 */
        /* 根据步数距离和GPS距离算出较准确的距离 */
        if ((gpsDist > GPS_DIST_MAX) || (gpsDist < GPS_DIST_MIN))
        {
            betterDist = stepDist;
        }
        else if ((longitude == 0) || (latitude == 0))
        {
            betterDist = stepDist;
        }
        else if ((longitude == ClimbMtProcess.oldLongitude) && (latitude == ClimbMtProcess.oldLatitude))
        {
            betterDist = stepDist;
        }
        else
        {
            betterDist = gpsDist;
        }

        /* 缓存数据更新 */
        if (ClimbMtProcess.climbBuffIdx >= CLIMBMT_BUFFER_MAX)
        {
            for (uint8_t i = 0; i < (CLIMBMT_BUFFER_MAX - 1); i++)
            {
                ClimbMtBuffer[i].altitude = ClimbMtBuffer[i + 1].altitude;
            }
            ClimbMtProcess.climbBuffIdx = CLIMBMT_BUFFER_MAX - 1;
        }
        ClimbMtBuffer[ClimbMtProcess.climbBuffIdx].altitude = altitude;
        ClimbMtProcess.climbBuffIdx++;
		
		/* 海拔20秒内变化数值限定 */
		if ((ABS(ClimbMtBuffer[9].altitude, ClimbMtBuffer[0].altitude) > ALTITUDE_CHANGE_MIN_20) && (ABS(ClimbMtBuffer[9].altitude, ClimbMtBuffer[0].altitude) < ALTITUDE_CHANGE_MAX_20))
		{
			changeAltitude = ClimbMtBuffer[9].altitude - ClimbMtBuffer[0].altitude;
		}
		else
		{
			changeAltitude = 0;
		}
        ClimbMtInfo.RealTimeData.Speed = changeAltitude * 1.8; /* m/h 垂直高度 = 高度 / 时间 ((cm / 100) / (20s / 3600) */

        /* 海拔2秒内变化数值 */
        nowAltitude = ABS(ClimbMtProcess.oldAltitude, altitude);
        if ((nowAltitude > ALTITUDE_CHANGE_MIN) && (nowAltitude < ALTITUDE_CHANGE_MAX))
        {
            nowAltitude = ABS(ClimbMtProcess.oldAltitude, altitude);
            ClimbMtInfo.RecordData.ValidDuration += 2;  /* 活动时间累加 */
        }
        else
        {
            nowAltitude = 0;
        }
        /* 累加总爬升和总下降高度 */
        if (changeAltitude > 0)
        {
            ClimbMtProcess.upTime += 1;
            ClimbMtProcess.upAltitude += nowAltitude;
            ClimbMtInfo.RecordData.UpAltitude = ClimbMtProcess.upAltitude * 0.01;
        }
        else if (changeAltitude < 0)
        {
            ClimbMtProcess.downTime += 1;
            ClimbMtProcess.downAltitude += nowAltitude;
            ClimbMtInfo.RecordData.DownAltitude = ClimbMtProcess.downAltitude * 0.01;
        }

        ClimbMtProcess.oldStep = step;
        ClimbMtProcess.oldLongitude = longitude;
        ClimbMtProcess.oldLatitude = latitude;
        ClimbMtProcess.oldAltitude = altitude;
    }
    /* 更新实时信息 */
    ClimbMtInfo.RealTimeData.Altitude = altitude * 0.01;
    ClimbMtInfo.RealTimeData.Longitude.f = longitude;
    ClimbMtInfo.RealTimeData.Latitude.f = latitude;

    /* 更新爬山过程最高和最低海拔 */
    int16_t altitudeM = altitude * 0.01;
    if (altitudeM > ClimbMtInfo.RecordData.HighestAltitude)
    {
        ClimbMtInfo.RecordData.HighestAltitude = altitudeM;
    }
    if (altitudeM < ClimbMtInfo.RecordData.LowestAltitude)
    {
        ClimbMtInfo.RecordData.LowestAltitude = altitudeM;
    }

    /* 更新爬山过程总距离和卡路里 */
    ClimbMtProcess.distanceCM += betterDist;                                                                                                       /* *cm 登山总距离累加 */
    ClimbMtInfo.RecordData.Distance = ClimbMtProcess.distanceCM * 0.01;                                                                            /* *m 登山总距离 */
    ClimbMtInfo.RecordData.Calorie = ClimbMtProcess.calorieParm * (ClimbMtProcess.upTime * CLIMB_HILL_0_9 + ClimbMtProcess.downTime * CLIMB_DOWN); /* 上山时间卡路里加下山时间卡路里 */

    /* 更新心率 */
    ClimbMtInfo.RealTimeData.Hr = hr;
    /* 更新最大心率 */
    if (hr > ClimbMtInfo.RecordData.HrMax)
    {
        ClimbMtInfo.RecordData.HrMax = hr;
    }
    /* 累加总心率用于算平均心率 */
    ClimbMtProcess.hrSum += hr;
    /* 计算心率区间并累加心率区间时间 */
    if (hr <= ClimbMtProcess.zoneThs.Z0Max)
    {
        ClimbMtInfo.HrZone = HR_ZONE_0;
    }
    else if (hr <= ClimbMtProcess.zoneThs.Z1Max)
    {
        ClimbMtInfo.HrZone = HR_ZONE_1;
        ClimbMtInfo.RecordData.HrZoneDuration.HrZone1++;
    }
    else if (hr <= ClimbMtProcess.zoneThs.Z2Max)
    {
        ClimbMtInfo.HrZone = HR_ZONE_2;
        ClimbMtInfo.RecordData.HrZoneDuration.HrZone2++;
    }
    else if (hr <= ClimbMtProcess.zoneThs.Z3Max)
    {
        ClimbMtInfo.HrZone = HR_ZONE_3;
        ClimbMtInfo.RecordData.HrZoneDuration.HrZone3++;
    }
    else if (hr <= ClimbMtProcess.zoneThs.Z4Max)
    {
        ClimbMtInfo.HrZone = HR_ZONE_4;
        ClimbMtInfo.RecordData.HrZoneDuration.HrZone4++;
    }
    else
    {
        ClimbMtInfo.HrZone = HR_ZONE_5;
        ClimbMtInfo.RecordData.HrZoneDuration.HrZone5++;
    }
}

/*******************************
**获取当前登山数据
**input: null
**output: 登山数据结构体：climbMountainInfo_t 
********************************/
void alg_climbMountain_get_info(climbMountainInfo_t *info)
{
    memcpy(info, &ClimbMtInfo, sizeof(ClimbMtInfo));
}

/*******************************
**结束登山，退出登山场景
**input: 当前UTC时间
**output: null 
********************************/
void alg_climbMountain_stop(uint32_t utc)
{
    /* 更新结束UTC时间 */
    ClimbMtInfo.RecordData.StopUTC = utc;
    /* 平均速度*/
    if (ClimbMtInfo.RecordData.Duration != 0)
    {
        ClimbMtInfo.RecordData.SpeedAVG = ClimbMtInfo.RecordData.Distance * 3.6 / ClimbMtInfo.RecordData.Duration;
    }
    /* 平均心率 */
    if (ClimbMtInfo.RecordData.Duration != 0)
    {
        ClimbMtInfo.RecordData.HrAVG = ClimbMtProcess.hrSum / ClimbMtInfo.RecordData.Duration;
    }
}

/*******************************
**暂停登山场景
**input: null
**output: null 
********************************/
void alg_climbMountain_pause(void)
{
    ClimbMtProcess.state = CLIMBMT_PAUSE;
}

/*******************************
**继续登山场景
**input: null
**output: null 
********************************/
void alg_climbMountain_continue(uint32_t step, int32_t altitude, float longitude, float latitude)
{
    ClimbMtProcess.state = CLIMBMT_RUN;

    ClimbMtProcess.oldStep = step;
    ClimbMtProcess.oldLongitude = longitude;
    ClimbMtProcess.oldLatitude = latitude;
    ClimbMtProcess.oldAltitude = altitude;

    smoothCnt = SMOOTH_NUM;
	for(uint8_t i = 0; i < SMOOTH_NUM; i++)
	{		
		smoothArrX[i] = longitude;
		smoothArrY[i] = latitude;
	}
}
