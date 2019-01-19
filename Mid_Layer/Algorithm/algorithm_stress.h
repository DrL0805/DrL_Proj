#ifndef _ALGORITHM_STRESS_H_
#define _ALGORITHM_STRESS_H_

#include <stdint.h>

typedef struct
{
    uint8_t score;    /* 压力分数 */
    uint8_t level;    /* 压力等级 0：静息 1：压力低 2：压力中 3：压力高*/  
} stress_t;

/*******************************
**压力指数算法初始化
**input: null
**output: null
********************************/
void alg_stress_init(void); /* 压力指数算法初始化 */

/*******************************
**压力指数算法处理
**input: sdnn, rmssd, rri, hr
**output: null
********************************/
void alg_stress_process(float sdnn, float rmssd, float rri, uint8_t hr); /* 压力指数算法处理 */

/*******************************
**获取压力分数和压力等级
**input: null
**output: stressScore 0-100 stressLevel :0-3
********************************/
void alg_stress_get_score(stress_t *stress); /* 获取压力分数 */

#endif
