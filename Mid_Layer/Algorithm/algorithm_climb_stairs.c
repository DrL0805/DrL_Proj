
#include "algorithm_climb_stairs.h"

#define ABS(a, b) (((a) - (b) > 0) ? (a) - (b) : (b) - (a))

#define FLOOR_ALTITUDE 300 /* *cm 楼层高度 */
#define BASE_FLASH_TIME 30 /* *S 高度刷新时间 */
#define FLOOR_STEP 10      /* *step 楼层变化一层的最少步数 */

typedef enum
{
    CLIMB_STAIRS_ING = 0,
    CLIMB_STAIRS_PAUSE,
} climbStairs_state_e;

static climbStairs_state_e ClimbState; /* 爬楼算法运行状态 */
static uint16_t UpFloor, DownFloor;    /* 总爬楼数 */
static uint32_t BaseStep;              /* 记录旧步数 */
static int32_t BaseAltitude;           /* 记录旧高度 */
static uint8_t TimeCnt;                /* 时间计数 */

/*******************************
**开始/重置爬楼算法：开机或零点清零时调用
**input: total step，current altitude
**output: null
********************************/
void alg_climb_stairs_start(uint32_t totalStep, int32_t altitude)
{
    ClimbState = CLIMB_STAIRS_ING;
    UpFloor = 0;
    DownFloor = 0;
    BaseStep = totalStep;
    BaseAltitude = altitude;
    TimeCnt = 0;
}

/*******************************
**爬楼算法处理, 每秒钟调用一次
**input: totalStep, current altitude
**output: null
********************************/
void alg_climb_stairs_process(uint32_t totalStep, int32_t altitude)
{
    if (ClimbState == CLIMB_STAIRS_PAUSE)
    {
        return;
    }

    TimeCnt++;
    /* 每隔一段时间刷新基础高度和基础步数 */
    if (TimeCnt > BASE_FLASH_TIME)
    {
        TimeCnt = 0;
        BaseStep = totalStep;
        BaseAltitude = altitude;
    }
    /* 如果在这段时间内高度变化大于设定值 */
    if (ABS(altitude, BaseAltitude) >= FLOOR_ALTITUDE)
    {
        /* 且步数大于设定值 */
        if ((totalStep > BaseStep) && ((totalStep - BaseStep) >= FLOOR_STEP))
        {
            /* 高度增加，上楼 */
            if (altitude > BaseAltitude)
            {
                UpFloor++;
            }
            /* 高度减小，下楼 */
            else
            {
                DownFloor++;
            }
        }
        TimeCnt = 0;
        BaseStep = totalStep;
        BaseAltitude = altitude;
    }
}

/*******************************
**获取当日爬楼层数
**input: null
**output: floor
********************************/
void alg_climb_stairs_get_floor(uint16_t *upFloor, uint16_t *downFloor)
{
    *upFloor = UpFloor;
    *downFloor = DownFloor;
}

/*******************************
**预留接口，暂无特定场景
**暂停爬楼算法，特定场景下的高度变化不计入爬楼数时，在进入特定场景时调用。
**input: null
**output: null
********************************/
void alg_climb_stairs_pause(void)
{
    ClimbState = CLIMB_STAIRS_PAUSE;
}

/*******************************
**预留接口，暂无特定场景
**继续爬楼算法，特定场景下的高度变化不计入爬楼数时，在退出特定场景时调用。
**input: null
**output: null
********************************/
void alg_climb_stairs_continue(uint32_t totalStep, int32_t altitude)
{
    ClimbState = CLIMB_STAIRS_ING;

    TimeCnt = 0;
    BaseStep = totalStep;
    BaseAltitude = altitude;
}
