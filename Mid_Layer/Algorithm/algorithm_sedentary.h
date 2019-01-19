#ifndef _ALGORITHM_SEDENTARY_H_
#define _ALGORITHM_SEDENTARY_H_

#include <stdint.h>

/*******************************
**开始/重置久坐提醒
**input: total step
**output: null
********************************/
void alg_sedentary_start(uint32_t totalStep); /* 开始/重置久坐提醒 */

/*******************************
**久坐算法处理, 每秒钟调用一次
**input: accelValue，totalStep
**output: null
********************************/
void alg_sedentary_process(int16_t *accelValue, uint32_t totalStep); /* 久坐算法处理 */

/*******************************
**获取久坐时间
**input: null
**output: sit time
********************************/
void alg_sedentary_get_time(uint16_t *sedentaryTime); /* 获取久坐时间 */

#endif
