
#include "algorithm_stress.h"
#include "math.h"
#include <string.h>

static stress_t Stress;

/*******************************
**压力指数算法初始化
**input: null
**output: null
********************************/
void alg_stress_init(void)
{
    Stress.score = 0;
    Stress.level = 0;
}

/*******************************
**压力指数算法处理
**input: sdnn, rmssd, rri, hr
**output: null
********************************/
void alg_stress_process(float sdnn, float rmssd, float rri, uint8_t hr)
{
	Stress.score = 100 - log(rmssd) * 15.38;
    if(Stress.score < 26)
    {
        Stress.level = 0;
    }
    else if((Stress.score >= 26) && (Stress.score < 51))
    {
        Stress.level = 1;
    }
    else if((Stress.score >= 51) && (Stress.score < 76))
    {
        Stress.level = 2;
    }
    else
    {
        Stress.level = 3;
    }    
}

/*******************************
**获取压力分数和压力等级
**input: null
**output: stressScore 0-100 stressLevel :0-3
********************************/
void alg_stress_get_score(stress_t *stress) /* 获取压力分数 */
{
	memcpy(stress, &Stress, sizeof(stress_t));
	
	/*  
		注：以下两种方式都不可以
		stress = &Stress;	
		*stress = Stress;	
	*/
}



