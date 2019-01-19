#ifndef _ALGORITHM_ABC_H_
#define _ALGORITHM_ABC_H_

#include <stdint.h>
#include <stdbool.h>

/*****************************
    Altimeter（高度計）
    Barometer（气压計）
    Compass（指南针） 
*******************************/

/* V1.2更改：提高校准速度，校准时调用频率改为25HZ，地磁需设置25HZ以上采样率，正反转都可以校准成功 */
/* V1.3更改：增加地磁在PCB的方向设置宏定义 */

#define MAG_ORIENTATION  2  /* 地磁方向：0、1、2、3。指南针的角度和实际有90度的整数倍偏差时可更改此宏定义 */

/*******************************
**设置海拔校正高度
**input: adjustAlti cm
**output: null
********************************/
void alg_ab_set_altitude(int32_t adjustAlti); /* 设置海拔校正高度 */

/*******************************
**设置当前海平面气压
**input: seaLevel Pa
**output: null
********************************/
void alg_ab_set_seaLevel(int32_t seaLevel); /* 设置当前海平面气压 */

/*******************************
**更新实时气压 每秒更新
**input: pressure Pa
**output: null
********************************/
void alg_ab_update_pressure(int32_t pressure); /* 每秒更新实时气压 */

/* Altimeter（高度計）
   Barometer（气压計）
   返回参数结构体 */
typedef struct
{
    int32_t pressure;
    int32_t seaLevel;
    int32_t altitude;
} ab_value_t;

/*******************************
**Pa, 获取实时气压, Pa, 获取当前海平面气压, cm, 获取当前海拔高度
**input: null
**output: AB_Value_t
********************************/
void alg_ab_get(ab_value_t *ab_value);

/*******************************
**指南针初始化
**input: 保存的校准参数 uint8_t len:17 byte
**output: null
********************************/
void alg_compass_init(uint8_t *calParm); /* 指南针初始化 */

/* 指南针校准状态 */
typedef enum
{
    COMPASS_CAL_ING = 0,
    COMPASS_CAL_DONE,
    COMPASS_CAL_FAIL,
    COMPASS_CAL_NONE,   
} calState_e;

/*******************************
**指南针校准初始化,校准前调用
**input: null
**output: null
********************************/
void alg_compass_calibration_init(void);

/*******************************
**指南针校准，校准方法：进入校准模式后，提示用户转动手表，校准时地磁传感器设置25HZ以上采样率
**校准前先调用初始化函数，再按25HZ频率调用校准函数，传入地磁传感器数据，校准成功后返回01, 外部读取并保存校准参数至flash.校准失败返回02
**input: magValue 地磁三轴数据
**output: 00:校准中，01:校准成功，02:校准失败。calParm[17]:校准参数，校准完成后保存至flash
********************************/
calState_e alg_compass_calibration(int16_t *magValue, uint8_t *calParm);

/*******************************
**0-359, 获取与北极的角度
**input: magValue 地磁三轴数据
**output: compassValue：angle 与北极的夹角，calState_e：校准状态: COMPASS_CAL_NONE: 未校准，COMPASS_CAL_DONE：已校准
********************************/
calState_e alg_compass_getAngle(int16_t *magValue, uint16_t *angle); /* 0-359度, 获取与北极的夹角 */

#endif
