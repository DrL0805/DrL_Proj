#ifndef OS_H
#define OS_H

/* FreeRTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "timers.h"

#define TASK_PRIORITY_IDLE          (tskIDLE_PRIORITY)                  /**< Idle priority */
#define TASK_PRIORITY_LOW           (tskIDLE_PRIORITY + 2)              /**< Low priority */
#define TASK_PRIORITY_MIDDLE_LOW    (tskIDLE_PRIORITY + 4)              /**< Middle low priority */
#define TASK_PRIORITY_MIDDLE        (tskIDLE_PRIORITY + 6)             /**< Middle priority */
#define TASK_PRIORITY_MIDDLE_HIGH   (tskIDLE_PRIORITY + 8)             /**< Middle high priority */
#define TASK_PRIORITY_HIGH          (tskIDLE_PRIORITY + 10)             /**< High priority */
#define TASK_PRIORITY_REALTIME      (tskIDLE_PRIORITY + 12)             /**< Highest priority */
#define TASK_PRIORITY_START			(tskIDLE_PRIORITY + 14)				// 初始化任务

#endif // RTOS_H

