
#include "algorithm_sedentary.h"

#define ABS(a, b) (((a) - (b) > 0) ? (a) - (b) : (b) - (a))
#define ABS0(a) (((a) - (0) > 0) ? (a) - (0) : (0) - (a))

#define ONE_ACT_THRESHOLD 3 /* 单轴动作阈值，小于该值判断为干扰，过滤 */
#define ACT(a, b) (ABS(a, b) < ONE_ACT_THRESHOLD ? 0 : ABS(a, b))

#define ALL_ACT_THRESHOLD 12 /* 三轴动作总阈值,小于该值判断为无动作状态 */

static uint16_t SedentaryTime;
static uint32_t oldStep;
static int8_t accOld[3];           /* 上次的三轴值 */
static uint8_t SecCnt, MinRestCnt; /* 分计数，秒计数 */
static uint8_t NoActMinCnt;

/*******************************
**开始/重置久坐提醒
**input: total step
**output: null
********************************/
void alg_sedentary_start(uint32_t totalStep)
{
    SedentaryTime = 0;
    oldStep = totalStep;
    SecCnt = 0;
    MinRestCnt = 0;
    NoActMinCnt = 0;
}

/*******************************
**久坐算法处理, 每秒钟调用一次
**input: accelValue，totalStep
**output: null
********************************/
void alg_sedentary_process(int16_t *accelValue, uint32_t totalStep)
{
    int8_t accValue[3];
    uint16_t actSum = 0;

    for (uint8_t i = 0; i < 3; i++)
    {
        /* 转为8bit数据,同时减小干扰 */
        accValue[i] = accelValue[i] >> 8;
        /* 三轴总动作值 */
        actSum += ACT(accValue[i], accOld[i]);
        /* 保存旧值 */
        accOld[i] = accValue[i];
    }

    /* 一分钟内累加动作值和动作频次 */
    if (SecCnt < 60)
    {
        /* 一分钟内总动作值 */
        if (actSum < ALL_ACT_THRESHOLD)
        {
            MinRestCnt++;
        }
        else
        {
            MinRestCnt = 0;
        }
    }
    /* 时间计数 */
    SecCnt++;
    if (SecCnt == 60)
    {
        SecCnt = 0;
        /* 久坐时间累加1分钟 */
        SedentaryTime++;
        if (MinRestCnt >= 58)
        {
            MinRestCnt = 0;
            NoActMinCnt++;
        }
        else
        {
			MinRestCnt = 0;
            NoActMinCnt = 0;
        }
    }
    /* 连续30分钟静止状态则久坐清零,防止误判静置为久坐 */
    if (NoActMinCnt >= 30)
    {
        NoActMinCnt = 0;
        SedentaryTime = 0;
    }
    /* 产生记步则久坐清零 */
    if (totalStep > oldStep)
    {
        SedentaryTime = 0;
    }
    oldStep = totalStep;
}

/*******************************
**获取久坐时间，单位min
**input: null
**output: sit time
********************************/
void alg_sedentary_get_time(uint16_t *sedentaryTime)
{
    *sedentaryTime = SedentaryTime;
}
