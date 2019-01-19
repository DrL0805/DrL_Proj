
#include <string.h>
#include "algorithm_running.h"

/* 跑步算法缓存数据 */
typedef struct
{
    uint16_t betterDist; /* cm 更准确的距离 */
    uint8_t step;        /* 步数 */
} runningBuffer_t;

/* 跑步算法体征信息 */
typedef struct
{
    uint8_t weight; /* 体重：单位：kg */
    uint8_t height; /* 身高：单位：cm */
    uint8_t sex;    /* 性别 */
    uint8_t age;    /* 年龄 */
} runningBodyInfo_t;

/* 跑步心率区间 */
typedef struct
{
    uint8_t Z0Max;
    uint8_t Z1Max;
    uint8_t Z2Max;
    uint8_t Z3Max;
    uint8_t Z4Max;
    uint8_t Z5Max;
} runningHrZoneThs_t;

typedef enum
{
    RUNNING_RUN = 0,
    RUNNING_PAUSE,
} runningRunState_e;

/* 跑步场景过程数据 */
typedef struct
{
    runningBodyInfo_t body;     /* 人体信息 */
    runningHrZoneThs_t zoneThs; /* 心率区间阈值 */
    runningRunState_e runState; /* 暂停标志 */
    uint32_t hrSum;             /* 跑步过程心率总和 */
    uint32_t distanceCM;        /* cm 跑步总距离 */
    uint32_t oldStep;           /* 上一秒总步数 */
    float oldLongitude;         /* 经度 */
    float oldLatitude;          /* 纬度 */
    uint8_t runBuffIdx;         /* 运动过程数据索引 */
    uint8_t secCnt;             /* 秒计数 */
} runningProcess_t;

#define GPS_DIST_MAX 800 /* cm 跑步2秒最大距离 */
#define GPS_DIST_MIN 80 /* cm 跑步2秒最小距离 */

static runningInfo_t RunInfo;       /* 跑步数据 */
static runningProcess_t RunProcess; /* 跑步过程数据 */

#define RUN_BUFFER_MAX 10
static runningBuffer_t RunBuffer[RUN_BUFFER_MAX]; /* 缓存一段时间的运动过程数据 */

/* 平滑 */
#define SMOOTH_NUM 4
static uint8_t smoothCnt = 0;
static float smoothArrX[SMOOTH_NUM];
static float smoothArrY[SMOOTH_NUM];

/*******************************
**开始跑步,初始化数据，进入跑步场景时调用
**input: 人体模型数据：sex age height weight. 当前UTC时间：utc. 当前计步步数：step. 当前高度：altitude.
**output: null
********************************/
void alg_running_start(uint8_t sex, uint8_t age, uint8_t height, uint8_t weight, uint32_t utc, uint32_t step, int32_t altitude)
{
    memset(&RunInfo, 0, sizeof(RunInfo));
    RunInfo.RecordData.StartUTC = utc;

    memset(RunBuffer, 0, sizeof(RunBuffer));

    memset(&RunProcess, 0, sizeof(RunProcess));
    RunProcess.runState = RUNNING_RUN;
    RunProcess.oldStep = step;
    RunProcess.body.weight = weight;
    RunProcess.body.height = height;
    RunProcess.body.sex = sex;
    RunProcess.body.age = age;

    RunProcess.zoneThs.Z0Max = (220 - age) * 0.50;
    RunProcess.zoneThs.Z1Max = (220 - age) * 0.60;
    RunProcess.zoneThs.Z2Max = (220 - age) * 0.70;
    RunProcess.zoneThs.Z3Max = (220 - age) * 0.80;
    RunProcess.zoneThs.Z4Max = (220 - age) * 0.90;
    RunProcess.zoneThs.Z5Max = (220 - age);

    smoothCnt = 0;
	for(uint8_t i = 0; i < SMOOTH_NUM; i++)
	{		
		smoothArrX[i] = 0;
		smoothArrY[i] = 0;
	}
}

/*******************************
**跑步过程数据更新,进入跑步场景后每秒调用一次
**input: 当前计步步数：step. 当前高度：altitude. 当前心率：hr. 当前经纬度：longitude latitude
**output: null
********************************/
uint16_t GPSDist;
void alg_running_update(uint32_t step, int32_t altitude, uint8_t hr, float longitude, float latitude)
{
    uint8_t nowStep = 0;
    uint16_t gpsDist = 0, stepDist = 0, betterDist = 0, sumBetterDist = 0, sumStep = 0;

    /* 跑步暂停状态下不做处理 */
    if (RunProcess.runState == RUNNING_PAUSE)
    {
        return;
    }

    /* 步数及时长累加 */
    if (step > RunProcess.oldStep)
    {
        nowStep = step - RunProcess.oldStep;
    }
    RunInfo.RecordData.Duration += 1;   /* *s 跑步总时间 */
    RunInfo.RecordData.Step += nowStep; /* 跑步总步数增加 */

    RunProcess.secCnt++;
    if (RunProcess.secCnt == 2)
    {
        RunProcess.secCnt = 0;
		
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
        gpsDist = alg_common_gps_distance(latitude, longitude, RunProcess.oldLatitude, RunProcess.oldLongitude) * 100000; /* cm 计算gps距离 */
        if (RunInfo.RealTimeData.Stride != 0)
        {
            stepDist = nowStep * RunInfo.RealTimeData.Stride;
        }
        else
        {
            stepDist = RunProcess.body.height * nowStep * 0.45; /* cm 步数计算跑步距离 = 身高*0.45*步数 */
        }
        GPSDist = gpsDist;
        /* 根据步数距离和GPS距离算出较准确的距离 */
        if ((gpsDist > GPS_DIST_MAX) || (gpsDist < GPS_DIST_MIN))
        {
            betterDist = stepDist;
        }
        else if ((longitude == 0) || (latitude == 0))
        {
            betterDist = stepDist;
        }
        else if ((longitude == RunProcess.oldLongitude) && (latitude == RunProcess.oldLatitude))
        {
            betterDist = stepDist;
        }
        else
        {
            betterDist = gpsDist;
        }

        /* 缓存数据更新 */
        if (RunProcess.runBuffIdx >= RUN_BUFFER_MAX)
        {
            for (uint8_t i = 0; i < (RUN_BUFFER_MAX - 1); i++)
            {
                RunBuffer[i].step = RunBuffer[i + 1].step;
                RunBuffer[i].betterDist = RunBuffer[i + 1].betterDist;
            }
            RunProcess.runBuffIdx = RUN_BUFFER_MAX - 1;
        }
        RunBuffer[RunProcess.runBuffIdx].step = nowStep;
        RunBuffer[RunProcess.runBuffIdx].betterDist = betterDist;
        RunProcess.runBuffIdx++;

        /* 取前20S数据计算实时数据 */
        zeroCnt = 0;
        if (RunProcess.runBuffIdx >= RUN_BUFFER_MAX)
        {
            for (uint8_t i = 0; i < RUN_BUFFER_MAX; i++)
            {
                sumBetterDist += RunBuffer[i].betterDist;
                sumStep += RunBuffer[i].step;
                if (RunBuffer[i].betterDist == 0)
                {
                    zeroCnt++;
                }
            }
        }
        if ((sumBetterDist != 0) && (zeroCnt <= 5))
        {
            RunInfo.RealTimeData.Pace = 2000000 / sumBetterDist; /* 配速 = s/km */
			if(RunInfo.RealTimeData.Pace > 1800)
			{
				RunInfo.RealTimeData.Pace = 0;
			}
            if (sumStep != 0)
            {
                RunInfo.RealTimeData.Freq = sumStep * 3;               /* 步频 = 步数/分钟 */
                RunInfo.RealTimeData.Stride = sumBetterDist / sumStep; /* 步幅 = 距离/步数 */
				if(RunInfo.RealTimeData.Freq > 200)
				{
					RunInfo.RealTimeData.Freq = 200;
				}
				if(RunInfo.RealTimeData.Stride > 200)
				{
					RunInfo.RealTimeData.Stride = 200;
				}
            }
        }
        else
        {
            RunInfo.RealTimeData.Pace = 0;
            RunInfo.RealTimeData.Freq = 0;
            RunInfo.RealTimeData.Stride = 0;
        }

        RunProcess.oldStep = step;
		RunProcess.oldLongitude = longitude;
		RunProcess.oldLatitude = latitude;
    }
    RunInfo.RealTimeData.Longitude.f = longitude;
    RunInfo.RealTimeData.Latitude.f = latitude;

    RunProcess.distanceCM += betterDist;                                                          /* *cm 跑步总距离累加 */
    RunInfo.RecordData.Distance = RunProcess.distanceCM * 0.01;                                   /* *m 跑步总距离 */
    RunInfo.RecordData.Calorie = RunProcess.body.weight * RunInfo.RecordData.Distance * 0.001036; /* 跑步卡路里 = 体重kg * 距离km * 1.036 */

    /* 更新心率 */
    RunInfo.RealTimeData.HR = hr;
    /* 更新最大心率 */
    if (hr > RunInfo.RecordData.HrMax)
    {
        RunInfo.RecordData.HrMax = hr;
    }
    /* 累加总心率用于算平均心率 */
    RunProcess.hrSum += hr;
    /* 计算心率区间并累加心率区间时间 */
    if (hr <= RunProcess.zoneThs.Z0Max)
    {
        RunInfo.HrZone = HR_ZONE_0;
    }
    else if (hr <= RunProcess.zoneThs.Z1Max)
    {
        RunInfo.HrZone = HR_ZONE_1;
        RunInfo.RecordData.HrZoneDuration.HrZone1++;
    }
    else if (hr <= RunProcess.zoneThs.Z2Max)
    {
        RunInfo.HrZone = HR_ZONE_2;
        RunInfo.RecordData.HrZoneDuration.HrZone2++;
    }
    else if (hr <= RunProcess.zoneThs.Z3Max)
    {
        RunInfo.HrZone = HR_ZONE_3;
        RunInfo.RecordData.HrZoneDuration.HrZone3++;
    }
    else if (hr <= RunProcess.zoneThs.Z4Max)
    {
        RunInfo.HrZone = HR_ZONE_4;
        RunInfo.RecordData.HrZoneDuration.HrZone4++;
    }
    else
    {
        RunInfo.HrZone = HR_ZONE_5;
        RunInfo.RecordData.HrZoneDuration.HrZone5++;
    }
}

/*******************************
**获取当前跑步数据
**input: null
**output: 跑步数据结构体：runningInfo_t 
********************************/
void alg_running_get_info(runningInfo_t *info)
{
    memcpy(info, &RunInfo, sizeof(runningInfo_t));
}

/*******************************
**结束跑步，退出跑步场景
**input: 当前UTC时间
**output: null 
********************************/
void alg_running_stop(uint32_t utc)
{
    /* 更新结束UTC时间 */
    RunInfo.RecordData.StopUTC = utc;
    /* 平均配速 */
    if (RunInfo.RecordData.Distance != 0)
    {
        RunInfo.RecordData.PaceAVG = RunInfo.RecordData.Duration * 1000 / RunInfo.RecordData.Distance;
    }
    /* 平均步频 */
    if ((RunInfo.RecordData.Duration / 60) != 0)
    {
        RunInfo.RecordData.FreqAVG = RunInfo.RecordData.Step / (RunInfo.RecordData.Duration / 60);
    }
    /* 平均步幅 */
    if (RunInfo.RecordData.Step != 0)
    {
        RunInfo.RecordData.StrideAVG = RunInfo.RecordData.Distance * 100 / RunInfo.RecordData.Step;
    }
    /* 平均心率 */
    if (RunInfo.RecordData.Duration != 0)
    {
        RunInfo.RecordData.HrAVG = RunProcess.hrSum / RunInfo.RecordData.Duration;
    }
}

/*******************************
**暂停跑步场景
**input: null
**output: null 
********************************/
void alg_running_pause(void)
{
    RunProcess.runState = RUNNING_PAUSE;
}

/*******************************
**继续跑步场景
**input: null
**output: null 
********************************/
void alg_running_continue(uint32_t step, int32_t altitude, float longitude, float latitude)
{
    RunProcess.runState = RUNNING_RUN;

    RunProcess.oldStep = step;
    RunProcess.oldLongitude = longitude;
    RunProcess.oldLatitude = latitude;
	
	smoothCnt = SMOOTH_NUM;
	for(uint8_t i = 0; i < SMOOTH_NUM; i++)
	{		
		smoothArrX[i] = longitude;
		smoothArrY[i] = latitude;
	}
}
