#include <string.h>
#include "algorithm_swim_indoor.h"

#define ABS(a, b) (((a) - (b) > 0) ? (a) - (b) : (b) - (a))

/* 室内游泳算法缓存数据 */
typedef struct
{
	uint8_t stroke; /* 每秒划水数 */
} swimIdBuffer_t;

/* 室内游泳算法体征信息 */
typedef struct
{
	uint8_t weight; /* 体重：单位：kg */
	uint8_t height; /* 身高：单位：cm */
	uint8_t sex;	/* 性别 */
	uint8_t age;	/* 年龄 */
} swimIdBodyInfo_t;

/* 室内游泳心率区间 */
typedef struct
{
	uint8_t Z0Max;
	uint8_t Z1Max;
	uint8_t Z2Max;
	uint8_t Z3Max;
	uint8_t Z4Max;
	uint8_t Z5Max;
} swimIdHrZoneThs_t;

/* 室内游泳运动状态 */
typedef enum
{
	SWIMID_RUN = 0,
	SWIMID_PAUSE,
} swimIdState_e;

/* 室内游泳场景过程数据 */
typedef struct
{
	swimIdBodyInfo_t body;	 /* 人体信息 */
	swimIdHrZoneThs_t zoneThs; /* 心率区间阈值 */
	swimIdState_e state;	   /* 暂停标志 */
	uint32_t hrSum;			   /* 游泳过程心率总和 */
	uint32_t totalStroke;	  /* 总划水次数 */
	uint32_t oldStroke;		   /* 上一秒总划水数 */
	uint16_t totalLaps;		   /* 总趟数 */
	uint16_t oldLaps;		   /* 旧趟数 */
	uint16_t lapOldStroke;	 /* 上一次转身的划水数 */
	uint32_t lapOldSwimTime;   /* 上一次转身的运动时间 */
	uint32_t swimTime;		   /* 游泳总运动时间 */
	uint16_t calorieParm;	  /* 计算卡路里的参数 */
	uint16_t poolLen;		   /* 泳池长度 */
	uint8_t strokeBuffIdx;	 /* 运动过程数据索引 */
} swimIdProcess_t;

static swimIndoorInfo_t SwimIdInfo;   /* 室内游泳数据 */
static swimIdProcess_t SwimIdProcess; /* 室内游泳过程数据 */

#define SWIMID_BUFFER_MAX 12
static swimIdBuffer_t SwimIdBuffer[SWIMID_BUFFER_MAX]; /* 缓存一段时间的运动过程数据 */

/* 游泳卡路里系数 */
#define SWIMMING_CAL 0.00010413 /* 9 * 0.00001157 */

/*******************************
**开始游泳,初始化数据，进入游泳场景时调用
**input: 人体模型数据：sex age height weight. 当前UTC时间：utc.
**output: null
********************************/
void alg_swimIndoor_start(uint8_t sex, uint8_t age, uint8_t height, uint8_t weight, uint32_t utc, uint16_t poolLen)
{
	memset(&SwimIdInfo, 0, sizeof(SwimIdInfo));
	SwimIdInfo.RecordData.StartUTC = utc;

	memset(SwimIdBuffer, 0, sizeof(SwimIdBuffer));

	memset(&SwimIdProcess, 0, sizeof(SwimIdProcess));
	SwimIdProcess.state = SWIMID_RUN;
	SwimIdProcess.body.weight = weight;
	SwimIdProcess.body.height = height;
	SwimIdProcess.body.sex = sex;
	SwimIdProcess.body.age = age;
	SwimIdProcess.poolLen = poolLen;

	SwimIdProcess.zoneThs.Z0Max = (220 - age) * 0.50;
	SwimIdProcess.zoneThs.Z1Max = (220 - age) * 0.60;
	SwimIdProcess.zoneThs.Z2Max = (220 - age) * 0.70;
	SwimIdProcess.zoneThs.Z3Max = (220 - age) * 0.80;
	SwimIdProcess.zoneThs.Z4Max = (220 - age) * 0.90;
	SwimIdProcess.zoneThs.Z5Max = (220 - age);

	/* 根据性别计算卡路里基数 */
	if (age == 0)
	{
		/* 男 */
		SwimIdProcess.calorieParm = 66.5 + (13.75 * weight) + (5.003 * height) - (6.775 * age); //Men
	}
	else
	{
		/* 女 */
		SwimIdProcess.calorieParm = 655.1 + (9.563 * weight) + (1.850 * height) - (4.676 * age); //Women
	}
}

/*******************************
**游泳过程数据更新,进入游泳场景后每秒调用一次
**input: 当前心率：hr.
**output: bool true:单趟信息更新
********************************/
bool alg_swimIndoor_update(uint8_t hr)
{
	uint8_t nowStroke = 0, sumStroke = 0;
	bool lapReturn = false;

	/* 暂停状态下不做处理 */
	if (SwimIdProcess.state == SWIMID_PAUSE)
	{
		return lapReturn;
	}

	/* 游泳时长累加 */
	nowStroke = SwimIdProcess.totalStroke - SwimIdProcess.oldStroke;
	SwimIdInfo.RecordData.Duration += 1;														/* *s 游泳总时间 */
	SwimIdInfo.RecordData.Stroke = SwimIdProcess.totalStroke;									/* 游泳总划水数 */
	SwimIdInfo.RecordData.Laps = SwimIdProcess.totalLaps;										/* 游泳总趟数 */
	SwimIdInfo.RecordData.Distance = SwimIdProcess.poolLen * SwimIdInfo.RecordData.Laps * 0.01; /* 游泳总距离 */

	/* 更新游泳缓存数据 */
	if (SwimIdProcess.strokeBuffIdx >= SWIMID_BUFFER_MAX)
	{
		for (uint8_t i = 0; i < (SWIMID_BUFFER_MAX - 1); i++)
		{
			SwimIdBuffer[i].stroke = SwimIdBuffer[i + 1].stroke;
		}
		SwimIdProcess.strokeBuffIdx = SWIMID_BUFFER_MAX - 1;
	}
	SwimIdBuffer[SwimIdProcess.strokeBuffIdx].stroke = nowStroke;
	SwimIdProcess.strokeBuffIdx++;

	/* 取2秒前的10S数据计算 */
	for (uint8_t i = 0; i < (SWIMID_BUFFER_MAX - 2); i++)
	{
		sumStroke += SwimIdBuffer[i].stroke;
	}
	SwimIdInfo.RealTimeData.StrokeRate = sumStroke * 6;

	if (SwimIdInfo.RealTimeData.StrokeRate != 0)
	{
		SwimIdProcess.swimTime += 1;
	}
	SwimIdInfo.RecordData.ValidDuration = SwimIdProcess.swimTime;
	SwimIdInfo.RecordData.Calorie = SwimIdProcess.calorieParm * SwimIdProcess.swimTime * SWIMMING_CAL;

	/* 更新单趟数据 */
	if (SwimIdProcess.totalLaps != SwimIdProcess.oldLaps)
	{
		SwimIdInfo.LapData.LapDuration = SwimIdProcess.swimTime - SwimIdProcess.lapOldSwimTime; /* 单趟活动时长 */
		SwimIdInfo.LapData.LapStroke = SwimIdProcess.totalStroke - SwimIdProcess.lapOldStroke;  /* 单趟划水数 */
		SwimIdProcess.lapOldStroke = SwimIdProcess.totalStroke;
		SwimIdProcess.lapOldSwimTime = SwimIdProcess.swimTime;

		SwimIdInfo.LapData.LapStrokeRate = SwimIdInfo.LapData.LapStroke / (SwimIdInfo.LapData.LapDuration * 0.017); /* 单趟划水率 */
		SwimIdInfo.LapData.LapPace = SwimIdInfo.LapData.LapDuration * (10000 / SwimIdProcess.poolLen);				/* 单趟配速 */
		SwimIdInfo.LapData.LapSwolf = SwimIdInfo.LapData.LapDuration + SwimIdInfo.LapData.LapStroke;				/* 单趟swolf */

		lapReturn = true; /* 单趟数据更新标志 */
	}

	/* 更新心率 */
	SwimIdInfo.RealTimeData.HR = hr;
	/* 更新最大心率 */
	if (hr > SwimIdInfo.RecordData.HrMax)
	{
		SwimIdInfo.RecordData.HrMax = hr;
	}
	/* 累加总心率用于算平均心率 */
	SwimIdProcess.hrSum += hr;
	/* 计算心率区间并累加心率区间时间 */
	if (hr <= SwimIdProcess.zoneThs.Z0Max)
	{
		SwimIdInfo.HrZone = HR_ZONE_0;
	}
	else if (hr <= SwimIdProcess.zoneThs.Z1Max)
	{
		SwimIdInfo.HrZone = HR_ZONE_1;
		SwimIdInfo.RecordData.HrZoneDuration.HrZone1++;
	}
	else if (hr <= SwimIdProcess.zoneThs.Z2Max)
	{
		SwimIdInfo.HrZone = HR_ZONE_2;
		SwimIdInfo.RecordData.HrZoneDuration.HrZone2++;
	}
	else if (hr <= SwimIdProcess.zoneThs.Z3Max)
	{
		SwimIdInfo.HrZone = HR_ZONE_3;
		SwimIdInfo.RecordData.HrZoneDuration.HrZone3++;
	}
	else if (hr <= SwimIdProcess.zoneThs.Z4Max)
	{
		SwimIdInfo.HrZone = HR_ZONE_4;
		SwimIdInfo.RecordData.HrZoneDuration.HrZone4++;
	}
	else
	{
		SwimIdInfo.HrZone = HR_ZONE_5;
		SwimIdInfo.RecordData.HrZoneDuration.HrZone5++;
	}

	SwimIdProcess.oldStroke = SwimIdProcess.totalStroke;
	SwimIdProcess.oldLaps = SwimIdProcess.totalLaps;

	return lapReturn;
}

/*******************************
**获取当前游泳数据
**input: null
**output: 游泳数据结构体：swimIndoorInfo_t 
********************************/
void alg_swimIndoor_get_info(swimIndoorInfo_t *info)
{
	memcpy(info, &SwimIdInfo, sizeof(SwimIdInfo));
}

/*******************************
**结束游泳，退出游泳场景
**input: 当前UTC时间
**output: null
********************************/
void alg_swimIndoor_stop(uint32_t utc)
{
	/* 更新结束UTC时间 */
	SwimIdInfo.RecordData.StopUTC = utc;
	/* *次/min 平均划水率*/
	if (SwimIdInfo.RecordData.ValidDuration != 0)
	{
		SwimIdInfo.RecordData.StrokeRateAVG = SwimIdInfo.RecordData.Stroke * 60 / SwimIdInfo.RecordData.ValidDuration;
	}
	/* *s/100m 平均配速*/
	if (SwimIdInfo.RecordData.Distance != 0)
	{
		SwimIdInfo.RecordData.PaceAVG = SwimIdInfo.RecordData.ValidDuration * (10000 / SwimIdInfo.RecordData.Distance);
	}
	/* *次/趟 平均划水次数*/
	if (SwimIdInfo.RecordData.Laps != 0)
	{
		SwimIdInfo.RecordData.StrokeAVG = SwimIdInfo.RecordData.Stroke / SwimIdInfo.RecordData.Laps;
	}
	/* 平均Swolf */
	if (SwimIdInfo.RecordData.Laps != 0)
	{
		SwimIdInfo.RecordData.SwolfAvg = SwimIdInfo.RecordData.ValidDuration / SwimIdInfo.RecordData.Laps + SwimIdInfo.RecordData.StrokeAVG;
	}
	/* 平均心率 */
	if (SwimIdInfo.RecordData.Duration != 0)
	{
		SwimIdInfo.RecordData.HrAVG = SwimIdProcess.hrSum / SwimIdInfo.RecordData.Duration;
	}
}

/*******************************
**暂停游泳场景
**input: null
**output: null 
********************************/
void alg_swimIndoor_pause(void)
{
	SwimIdProcess.state = SWIMID_PAUSE;
}

/*******************************
**继续游泳场景
**input: null
**output: null 
********************************/
void alg_swimIndoor_continue(void)
{
	SwimIdProcess.state = SWIMID_RUN;
}

/*******************************
**计算划水数
**input: 加速度三轴数据：accelValue
**output: TotalStroke
********************************/
#define STK_VALID_AXIS 0	 /* X轴：0，Y轴：1, 计算划水数算法使用的加速度轴，此轴为加速度器件在PCB上9点-3点方向轴，比如数据采集器 9点-3点方向轴为X轴 */
#define STK_SMOOTH_WIN 12	/* 移动平均窗口平滑次数 */
#define STK_DETECT_WIN 15	/* 波峰波谷检测滑动窗口, 此数为奇数 */
#define STK_SUB1 2			 /* 容错次数 */
#define STK_SUB2 3			 /* 容错次数 */
#define STK_PEAK_VALE_ABS 30 /* 波峰波谷最小阈值 */
#define STK_PP_THS_MIN 20	/* 两周期最小采样点数 */
#define STK_PP_THS_MAX 100   /* 两周期最大采样点数 */
#define STK_PRE_START_CNT 5  /* 游泳状态确认计数 */

static void alg_swim_stroke_process(int16_t *accelValue)
{
	static int8_t stkSmoothWin[STK_SMOOTH_WIN], stkDetectWin[STK_DETECT_WIN]; /* 移动平均窗口, 波峰波谷判断窗口 */
	static uint8_t stkSmoothIdx, stkDetectIdx;								  /* 移动平均窗口索引, 波峰波谷判断窗口索引 */
	static int8_t peak = -127, vale = 127, maxPeak, minVale;				  /* 最近有效的峰谷值，最大最小峰谷值 */
	static uint16_t peakToPeak, peakCycle[STK_PRE_START_CNT], peakAvg;		  /* 最近的采样间隔周期，平均周期 */
	static uint8_t peakFlag, valeFlag;										  /* 检测到峰谷标志 */
	static uint8_t updateCnt, dynamicThr;									  /* 动态阈值更新 */
	static uint8_t startFlag, preStartCnt, clearPreCnt;						  /* 预确认开始游泳状态 */

	int8_t accValue = 0;
	int32_t stkSmoothSum = 0;

	/* 数值缩小 */
	accValue = accelValue[STK_VALID_AXIS] >> 8; /* 此轴为9点-3点方向轴，H001 9点-3点方向轴为X轴 */

	/* 移动平均滤波 */
	stkSmoothWin[stkSmoothIdx] = accValue;
	stkSmoothIdx++;
	if (stkSmoothIdx >= STK_SMOOTH_WIN)
	{
		stkSmoothIdx = 0;
	}
	for (uint8_t i = 0; i < STK_SMOOTH_WIN; i++)
	{
		stkSmoothSum += stkSmoothWin[i];
	}
	accValue = stkSmoothSum / STK_SMOOTH_WIN;

	/* 峰谷判断滑动窗口丢掉旧值，入新值*/
	if (stkDetectIdx >= STK_DETECT_WIN)
	{
		for (uint8_t i = 0; i < (STK_DETECT_WIN - 1); i++)
		{
			stkDetectWin[i] = stkDetectWin[i + 1];
		}
		stkDetectIdx = STK_DETECT_WIN - 1;
	}
	stkDetectWin[stkDetectIdx] = accValue;
	stkDetectIdx++;

	/* 动态阈值更新 */
	if (updateCnt < STK_PP_THS_MAX)
	{
		updateCnt++;
		if (maxPeak < accValue)
		{
			maxPeak = accValue;
		}
		if (minVale > accValue)
		{
			minVale = accValue;
		}
	}
	else
	{
		/* 动态阈值为波峰波谷乘系数 */
		dynamicThr = ABS(maxPeak, minVale) * 0.4;
		/* 动态阈值最小值 */
		if (dynamicThr < STK_PEAK_VALE_ABS)
		{
			dynamicThr = STK_PEAK_VALE_ABS;
		}
		maxPeak = 0;
		minVale = 0;
		updateCnt = 0;
	}

	/* 在滑动窗口中判断波峰, 波峰位于窗口中间 */
	if ((stkDetectWin[STK_DETECT_WIN / 2] > stkDetectWin[STK_DETECT_WIN / 2 - 1]) && (stkDetectWin[STK_DETECT_WIN / 2] >= stkDetectWin[STK_DETECT_WIN / 2 + 1]))
	{
		uint8_t cnt = 0;
		for (uint8_t i = 0; i < (STK_DETECT_WIN / 2); i++)
		{
			if (stkDetectWin[i] < stkDetectWin[i + 1])
			{
				cnt++;
			}
		}
		if (cnt >= (STK_DETECT_WIN / 2 - STK_SUB2))
		{
			cnt = 0;
			for (uint8_t i = (STK_DETECT_WIN / 2); i < (STK_DETECT_WIN - 1); i++)
			{
				if (stkDetectWin[i] >= stkDetectWin[i + 1])
				{
					cnt++;
				}
			}
			if (cnt >= (STK_DETECT_WIN / 2 - STK_SUB1))
			{
				/* 记录最大的一个波峰 */
				if (stkDetectWin[STK_DETECT_WIN / 2] > peak)
				{
					peak = stkDetectWin[STK_DETECT_WIN / 2];
					peakFlag = 1;
				}
			}
		}
	}
	/* 在滑动窗口中判断波谷, 波谷位于窗口中间 */
	if ((stkDetectWin[STK_DETECT_WIN / 2] <= stkDetectWin[STK_DETECT_WIN / 2 - 1]) && (stkDetectWin[STK_DETECT_WIN / 2] < stkDetectWin[STK_DETECT_WIN / 2 + 1]))
	{
		uint8_t cnt = 0;
		for (uint8_t i = 0; i < (STK_DETECT_WIN / 2); i++)
		{
			if (stkDetectWin[i] >= stkDetectWin[i + 1])
			{
				cnt++;
			}
		}
		if (cnt >= (STK_DETECT_WIN / 2 - STK_SUB1))
		{
			cnt = 0;
			for (uint8_t i = (STK_DETECT_WIN / 2); i < (STK_DETECT_WIN - 1); i++)
			{
				if (stkDetectWin[i] < stkDetectWin[i + 1])
				{
					cnt++;
				}
			}
			if (cnt >= (STK_DETECT_WIN / 2 - STK_SUB2))
			{
				/* 记录最小的一个波谷 */
				if (stkDetectWin[STK_DETECT_WIN / 2] < vale)
				{
					vale = stkDetectWin[STK_DETECT_WIN / 2];
					valeFlag = 1;
				}
			}
		}
	}

	/* 如果检测到波峰波谷 */
	if ((peakFlag == 1) && (valeFlag == 1))
	{
		/* 如果波峰波谷距离超过动态阈值 */
		if (ABS(peak, vale) > dynamicThr)
		{
			/* 如果相邻两波峰波谷的周期在限定范围内 */
			if ((peakToPeak > STK_PP_THS_MIN) && (peakToPeak < STK_PP_THS_MAX))
			{
				/* 预确认过滤，滤除偶然动作误判 */
				if (startFlag == 0)
				{
					peakCycle[preStartCnt] = peakToPeak;
					preStartCnt++;
					if (preStartCnt == STK_PRE_START_CNT)
					{
						/* 前几个波峰波谷平均周期作为判断周期 */
						uint16_t peakSum = 0;
						for (uint8_t i = 1; i < STK_PRE_START_CNT; i++)
						{
							peakSum += peakCycle[i];
						}
						peakAvg = peakSum / (STK_PRE_START_CNT - 1);

						/* 游泳状态确定 */
						startFlag = 1;
						SwimIdProcess.totalStroke += STK_PRE_START_CNT;
						preStartCnt = 0;
					}
				}
				/* 已处于确认阶段 */
				else
				{
					/* 周期必须在判断周期一定范围内 */
					if (ABS(peakToPeak, peakAvg) < (peakAvg * 0.4))
					{
						SwimIdProcess.totalStroke++;
					}
					/* 否则重新开始预确认游泳状态 */
					else
					{
						startFlag = 0;
						preStartCnt = 0;
					}
				}
				clearPreCnt = 0;
			}
			peakToPeak = 0;
			peakFlag = 0;
			valeFlag = 0;
			peak = -127;
			vale = 127;
		}
	}
	peakToPeak++;

	/* 停止周期超过游泳周期，重新预确认游泳状态 */
	clearPreCnt++;
	if (clearPreCnt > STK_PP_THS_MAX)
	{
		clearPreCnt = 0;
		startFlag = 0;
		preStartCnt = 0;
	}
}

/*******************************
**计算趟数
**input: 地磁三轴数据：magValue
**output: TotalLaps
********************************/

/* 获取中位数，用于中值滤波 */
static int8_t alg_medfilt(int8_t *bArray, uint8_t iFilterLen)
{
	uint8_t i, j; // 循环变量
	int8_t bTemp;

	// 用冒泡法对数组进行排序
	for (j = 0; j < iFilterLen - 1; j++)
	{
		for (i = 0; i < iFilterLen - j - 1; i++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				// 互换
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}

	// 计算中值
	if ((iFilterLen & 1) > 0)
	{
		// 数组有奇数个元素，返回中间一个元素
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else
	{
		// 数组有偶数个元素，返回中间两个元素平均值
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}

	return bTemp;
}

#define LAP_VALID_AXIS 1   /* X轴：0，Y轴：1, 计算转身算法使用的地磁轴，此轴为地磁器件在PCB上6点-12点方向轴，比如数据采集器 6点-12点方向轴为Y轴 */
#define LAP_MEDFILT_WIN 32 /* 中值滤波窗口大小 */
#define LAP_SMOOTH_WIN 32  /* 平滑窗口大小 */
#define LAP_DETECT_WIN 75  /* 检测窗口大小 */
#define LAP_DETECT_THS 10  /* 转身检测阈值 */
#define LAP_STROKE_MIN 6   /* 两转身间最小划水数 */

static void alg_swim_lap_process(int16_t *magValue)
{
	static int8_t lapMedfiltWin[LAP_MEDFILT_WIN], lapSmoothWin[LAP_SMOOTH_WIN], lapDetectWin[LAP_DETECT_WIN]; /* 中值滤波窗口, 移动平均及检测窗口 */
	static uint8_t lapMedfiltIdx, lapSmoothIdx, lapDetectIdx;												  /* 中值滤波窗口索引, 移动平均及检测窗口索引 */
	static uint8_t lapDetectFlag, lapDetectCnt;

	int8_t magValid = 0;
	int32_t lapSmoothSum = 0;
	int8_t maxMag = -126, minMag = 126;

	/* 获取判断轴数据并数值缩小 */
	magValid = magValue[LAP_VALID_AXIS] >> 8; /* 此轴为地磁6点-12点方向轴，如数据采集器 6点-12点方向轴为Y轴 */

	/* 缓存最近的数据进行滤波 */
	lapMedfiltWin[lapMedfiltIdx] = magValid;
	lapMedfiltIdx++;
	if (lapMedfiltIdx >= LAP_MEDFILT_WIN)
	{
		lapMedfiltIdx = 0;
	}
	/* 中值滤波 */
	magValid = alg_medfilt(lapMedfiltWin, LAP_MEDFILT_WIN);

	/* 缓存最近中值滤波后的数据进行平滑 */
	lapSmoothWin[lapSmoothIdx] = magValid;
	lapSmoothIdx++;
	if (lapSmoothIdx >= LAP_SMOOTH_WIN)
	{
		lapSmoothIdx = 0;
	}
	for (uint8_t i = 0; i < LAP_SMOOTH_WIN; i++)
	{
		lapSmoothSum += lapSmoothWin[i];
	}
	magValid = lapSmoothSum / LAP_SMOOTH_WIN;

	/* 缓存最近的数据来检测是否发生转身 */
	lapDetectWin[lapDetectIdx] = magValid;
	lapDetectIdx++;
	if (lapDetectIdx >= LAP_DETECT_WIN)
	{
		lapDetectIdx = 0;
	}
	/* 获取检测窗口内的最大值和最小值 */
	for (uint8_t i = 0; i < LAP_DETECT_WIN; i++)
	{
		if (lapDetectWin[i] > maxMag)
		{
			maxMag = lapDetectWin[i];
		}
		else if (lapDetectWin[i] < minMag)
		{
			minMag = lapDetectWin[i];
		}
	}

	/* 检测是否满足转身 */
	if ((lapDetectFlag == 0) && (ABS(minMag, maxMag) > LAP_DETECT_THS))
	{
		if (SwimIdProcess.totalStroke - SwimIdProcess.lapOldStroke > LAP_STROKE_MIN)
		{
			SwimIdProcess.totalLaps++;
			lapDetectFlag = 1;
		}
	}
	/* 避免在同个转身重复记录转身 */
	if (lapDetectFlag == 1)
	{
		lapDetectCnt++;
		if (lapDetectCnt > LAP_DETECT_WIN)
		{
			lapDetectCnt = 0;
			lapDetectFlag = 0;
		}
	}
}

/*******************************
**游泳运动数据更新,进入游泳场景按25HZ频率调用, 用于计算划水数，泳姿识别，转身等运动数据
**input: 加速度三轴数据：accelValue. 地磁三轴数据：magValue
**output: null
********************************/
void alg_swimIndoor_calculate(int16_t *accelValue, int16_t *magValue)
{
	/* 暂停状态下不做处理 */
	if (SwimIdProcess.state == SWIMID_PAUSE)
	{
		return;
	}

	alg_swim_stroke_process(accelValue);
	alg_swim_lap_process(magValue);
}
