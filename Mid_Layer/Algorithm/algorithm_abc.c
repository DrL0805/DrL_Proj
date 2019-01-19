
#include "algorithm_abc.h"
#include <math.h>
#include <string.h>

#define CHANGE_ALTITUDE_THS 36 /* 气压变化超过36Pa(3m)的时间短于2分钟, 则判断为海拔变化 */

static int32_t SeaPressure = 101325;
static int32_t Pressure = 101325;
static int32_t Altitude = 0;
static bool ChangeAltiFlag = false;
static bool ABInitFlag = false;

#define PRESSURE_BUF_MAX 24 /* 5S保存一次气压值，缓存2分钟气压数据 */
static int32_t pressureBuf[PRESSURE_BUF_MAX];
static uint8_t prsBufIndex, secondCnt;

/*******************************
**设置海拔校正高度
**input: adjustAlti cm
**output: null
********************************/
void alg_ab_set_altitude(int32_t adjustAlti)
{
    Altitude = adjustAlti;
    SeaPressure = Pressure / pow((1.0 - ((Altitude * 0.01) / 44330.0)), 5.255);
}

/*******************************
**设置当前海平面气压
**input: seaLevel Pa
**output: null
********************************/
void alg_ab_set_seaLevel(int32_t seaLevel)
{
    SeaPressure = seaLevel;
    Altitude = (44330 * (1 - powf(((float)Pressure / (float)SeaPressure), (1 / 5.255)))) * 100;
}

/*******************************
**气压、海平面气压、高度数据更新， 1S调用频率
**input: pressure
**output: null
********************************/
void alg_ab_update_pressure(int32_t pressure)
{
    int32_t minPrs = 0x7FFFFFFF, maxPrs = 0xFFFFFFFF, pressSum = 0;

    if (ABInitFlag == false)
    {
        if (pressure >= 30000 && pressure <= 120000)
        {
            ABInitFlag = true;
            prsBufIndex = 0;
            secondCnt = 0;
            Pressure = pressure;
            for (uint8_t i = 0; i < PRESSURE_BUF_MAX; i++)
            {
                pressureBuf[i] = Pressure;
            }

            /* 初始化时海拔使用标准大气压计算 */
            SeaPressure = 101325;
            Altitude = (44330 * (1 - powf(((float)Pressure / (float)SeaPressure), (1 / 5.255)))) * 100;
            ChangeAltiFlag = false;
        }
    }
    else
    {
        if (pressure >= 30000 && pressure <= 120000)
        {
            Pressure = pressure;
        }
        secondCnt++;
        if (secondCnt >= 5)
        {
            secondCnt = 0;
            pressureBuf[prsBufIndex] = Pressure;
            prsBufIndex++;
            if (prsBufIndex >= PRESSURE_BUF_MAX)
            {
                prsBufIndex = 0;
            }
            for (uint8_t i = 0; i < PRESSURE_BUF_MAX; i++)
            {
                if (minPrs > pressureBuf[i])
                {
                    minPrs = pressureBuf[i];
                }
                if (maxPrs < pressureBuf[i])
                {
                    maxPrs = pressureBuf[i];
                }
                pressSum += pressureBuf[i];
            }
            /* 2分钟内气压差是否超过阈值，超过则判断为高度引起的气压变化，未超过则判断为海平面气压引起的变化 */
            if (maxPrs - minPrs > CHANGE_ALTITUDE_THS)
            {
                if (ChangeAltiFlag == false)
                {
                    int32_t pressAvg = 0;
                    pressAvg = (pressSum - minPrs - maxPrs) / (PRESSURE_BUF_MAX - 2);
                    /* 高度开始变化时，海平面气压使用变化前的平均气压和变化前的高度校正 */
                    SeaPressure = pressAvg / pow((1.0 - ((Altitude * 0.01) / 44330.0)), 5.255);
                }
                ChangeAltiFlag = true;
            }
            else
            {
                if (ChangeAltiFlag == true)
                {
                    /* 高度停止变化时，高度使用当前气压和当前海平面气压校正 */
                    Altitude = (44330 * (1 - powf(((float)Pressure / (float)SeaPressure), (1 / 5.255)))) * 100;
                }
                ChangeAltiFlag = false;
                /* 海平面气压5S更新一次 */
                SeaPressure = Pressure / pow((1.0 - ((Altitude * 0.01) / 44330.0)), 5.255);
            }
        }
    }
}

/*******************************
**Pa, 获取实时气压, Pa, 获取当前海平面气压, cm, 获取当前海拔高度
**input: null
**output: AB_Value_t
********************************/
void alg_ab_get(ab_value_t *ab_value)
{
    ab_value->pressure = Pressure;
    ab_value->seaLevel = SeaPressure;

    if (ChangeAltiFlag == true)
    {
        Altitude = (44330 * (1 - powf(((float)Pressure / (float)SeaPressure), (1 / 5.255)))) * 100;
    }
    ab_value->altitude = Altitude;
}

/****************************************
***** 指南针相关 ************************
****************************************/
typedef struct calParm
{
    uint8_t Flag;
    float Xa;
    float Xb;
    float Ya;
    float Yb;
} CalParm_t;

#define PI 3.14159265f
#define CALIBRATION_FLAG 0x5A
#define CALIBRATION_MASK 0x0FFF
#define CALIBRATION_TIMEOUT 750 /* * 40ms */

static uint16_t CalCnt, CalFlagR, CalFlagL, oldAngle; /* 校准计数,校准过程标志 */
static uint8_t CalState;
static CalParm_t CalParm; /* 校准参数 */
static int16_t Xmax = -32767;
static int16_t Xmin = 32767;
static int16_t Ymax = -32767;
static int16_t Ymin = 32767;

/* 校准平滑 */
#define SMOOTH_NUM 12
static uint8_t smoothCnt = 0;
static int16_t smoothArrX[SMOOTH_NUM];
static int16_t smoothArrY[SMOOTH_NUM];

/*********************************
**指南针初始化，读取保存的校准参数
**input: 保存的校准参数 uint8_t len:17 byte
**output: null
**********************************/
void alg_compass_init(uint8_t *calParm)
{
    memcpy(&CalParm, calParm, sizeof(CalParm_t));
    if (CalParm.Flag != CALIBRATION_FLAG)
    {
        CalParm.Flag = 0;
        CalState = COMPASS_CAL_NONE;
        CalParm.Xa = 1;
        CalParm.Xb = 0;
        CalParm.Ya = 1;
        CalParm.Yb = 0;
    }
    else
    {
        CalState = COMPASS_CAL_DONE;
    }
}

/*******************************
**指南针校准初始化,校准前调用
**input: null
**output: null
********************************/
void alg_compass_calibration_init(void)
{
    CalParm.Flag = 0;
    CalState = COMPASS_CAL_NONE;
    CalParm.Xa = 1;
    CalParm.Xb = 0;
    CalParm.Ya = 1;
    CalParm.Yb = 0;
    CalCnt = 0;
    CalFlagR = 0;
	CalFlagL = 0;
    oldAngle = 0;

    Xmax = -32767;
    Xmin = 32767;
    Ymax = -32767;
    Ymin = 32767;
	
	smoothCnt = 0;
	for(uint8_t i = 0; i < SMOOTH_NUM; i++)
	{		
		smoothArrX[i] = 0;
		smoothArrY[i] = 0;
	}
}

/*******************************
**指南针校准，校准方法：进入校准模式后，提示用户转动手表，校准时地磁传感器设置25HZ以上采样率
**校准前先调用初始化函数，再按25HZ频率调用校准函数，传入地磁传感器数据，校准成功后返回01, 外部读取并保存校准参数至flash.校准失败返回02
**input: magValue 地磁三轴数据
**output: 校准结果 00:校准中，01:校准成功，02:校准失败。calParm[17]:校准参数，校准完成后保存至flash
********************************/
calState_e alg_compass_calibration(int16_t *magValue, uint8_t *calParm)
{
    float magX, magY;
    uint16_t angle;

#if (MAG_ORIENTATION == 1)
    magValue[0] *= -1;
#elif (MAG_ORIENTATION == 2)
    magValue[1] *= -1;
#elif (MAG_ORIENTATION == 3)
    magValue[0] *= -1;
    magValue[1] *= -1;
#endif
	
	/* 对地磁数据滤波 */
	int32_t xSum = 0, ySum = 0;
	if (smoothCnt >= SMOOTH_NUM)
    {
        for (uint8_t i = 0; i < (SMOOTH_NUM - 1); i++)
        {
            smoothArrX[i] = smoothArrX[i + 1];
			smoothArrY[i] = smoothArrY[i + 1];
        }
        smoothCnt = SMOOTH_NUM - 1;
    }
    smoothArrX[smoothCnt] = magValue[0];
	smoothArrY[smoothCnt] = magValue[1];
    smoothCnt++;
    for (uint8_t i = 0; i < smoothCnt; i++)
    {
        xSum += smoothArrX[i];
        ySum += smoothArrY[i];
    }
    magValue[0] = xSum / smoothCnt;
    magValue[1] = ySum / smoothCnt;
	
    CalCnt++;
    /* 持续更新X，Y轴最大值最小值 */
    if (magValue[0] > Xmax)
    {
        Xmax = magValue[0];
    }
    if (magValue[1] > Ymax)
    {
        Ymax = magValue[1];
    }
    if (magValue[0] < Xmin)
    {
        Xmin = magValue[0];
    }
    if (magValue[1] < Ymin)
    {
        Ymin = magValue[1];
    }
    /* 将变化范围大的轴系数设为1 */
    if ((Xmax - Xmin) > (Ymax - Ymin))
    {
        CalParm.Xa = 1;
        CalParm.Ya = (float)(Xmax - Xmin) / (float)(Ymax - Ymin);
    }
    else
    {
        CalParm.Ya = 1;
		CalParm.Xa = (float)(Ymax - Ymin) / (float)(Xmax - Xmin);
    }
    CalParm.Xb = CalParm.Xa * ((Xmax - Xmin) * 0.5 - Xmax);
    CalParm.Yb = CalParm.Ya * ((Ymax - Ymin) * 0.5 - Ymax);

    /* 计算角度 */
    magX = CalParm.Xa * magValue[0] + CalParm.Xb;
    magY = CalParm.Ya * magValue[1] + CalParm.Yb;
    double heading = atan2(magX, magY);
    if (heading < 0)
    {
        heading += 2 * PI;
    }
    if (heading > 2 * PI)
    {
        heading -= 2 * PI;
    }
    angle = heading * 180.0 / PI;

    /* 角度变大 */
    if (angle >= oldAngle)
    {
        CalFlagR |= 1 << ((angle + 1) / 30); /* 当转到30度的倍数角度时，将对应位置1，全置1时即覆盖到0-360度后即校准成功 */
    }
    else
    {
		CalFlagR = 0;
    }
	/* 角度变小 */
    if (angle <= oldAngle)
    {
        CalFlagL |= 1 << ((angle + 1) / 30); /* 当转到30度的倍数角度时，将对应位置1，全置1时即覆盖到0-360度后即校准成功 */
    }
    else
    {
		CalFlagL = 0;
    }
    /* 顺时针或逆时针旋转一圈，能一次遍历到0-360度即为校准成功 */
    if (((CalFlagR & CALIBRATION_MASK) == CALIBRATION_MASK) || ((CalFlagL & CALIBRATION_MASK) == CALIBRATION_MASK))
    {
        CalParm.Flag = CALIBRATION_FLAG;
        memcpy(calParm, &CalParm, sizeof(CalParm_t));
        CalState = COMPASS_CAL_DONE;
        return COMPASS_CAL_DONE;
    }
    /* 超时未遍历到0-360度，校准失败 */
    else if (CalCnt > CALIBRATION_TIMEOUT)
    {
        CalState = COMPASS_CAL_FAIL;
        return COMPASS_CAL_FAIL;
    }

    oldAngle = angle;

    CalState = COMPASS_CAL_ING;
    return COMPASS_CAL_ING;
}

/**************************************************************
**0-359度, 获取与北极的角度
**input: magValue 地磁三轴数据
**output: compassValue:angle:与北极的夹角,calState:校准状态
***************************************************************/
calState_e alg_compass_getAngle(int16_t *magValue, uint16_t *angle)
{
    float magX, magY;

#if (MAG_ORIENTATION == 1)
    magValue[0] *= -1;
#elif (MAG_ORIENTATION == 2)
    magValue[1] *= -1;
#elif (MAG_ORIENTATION == 3)
    magValue[0] *= -1;
    magValue[1] *= -1;
#endif

    if (CalParm.Flag != CALIBRATION_FLAG)
    {
        /* 未校准 */
        *angle = 0;
        if (CalState == COMPASS_CAL_ING)
        {
            return COMPASS_CAL_ING;
        }
        return COMPASS_CAL_NONE;
    }
	magX = CalParm.Xa * magValue[0] + CalParm.Xb;
	magY = CalParm.Ya * magValue[1] + CalParm.Yb;
	
    double heading = atan2(magX, magY);
    if (heading < 0)
    {
        heading += 2 * PI;
    }
    if (heading > 2 * PI)
    {
        heading -= 2 * PI;
    }
    *angle = heading * 180.0 / PI;

    return COMPASS_CAL_DONE;
}
