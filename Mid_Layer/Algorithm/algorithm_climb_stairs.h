#ifndef _ALGORITHM_CLINB_STAIRS_
#define _ALGORITHM_CLINB_STAIRS_

#include <stdint.h>

/*******************************
**开始/重置爬楼算法：开机或零点清零时调用
**input: total step，current altitude
**output: null
********************************/
void alg_climb_stairs_start(uint32_t totalStep, int32_t altitude); /* 开始/重置爬楼 */

/*******************************
**爬楼算法处理, 每秒钟调用一次
**input: totalStep, current altitude
**output: null
********************************/
void alg_climb_stairs_process(uint32_t totalStep, int32_t altitude); /* 爬楼处理 */

/*******************************
**获取当日爬楼层数
**input: null
**output: floor
********************************/
void alg_climb_stairs_get_floor(uint16_t *upFloor, uint16_t *downFloor); /* 获取上下楼层数 */

/*******************************
**预留接口，暂无特定场景
**暂停爬楼算法，特定场景下的高度变化不计入爬楼数时，在进入特定场景时调用。
**input: null
**output: null
********************************/
void alg_climb_stairs_pause(void); /* 暂停爬楼，进入场景时调用 */

/*******************************
**预留接口，暂无特定场景
**继续爬楼算法，特定场景下的高度变化不计入爬楼数时，在退出特定场景时调用。
**input: null
**output: null
********************************/
void alg_climb_stairs_continue(uint32_t totalStep, int32_t altitude); /* 暂停后继续，退出场景时调用 */

#endif
