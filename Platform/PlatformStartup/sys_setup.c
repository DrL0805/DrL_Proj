// system
#include "platform_common.h"
#include "system_task.h"
#include "wsf_types.h"
#include "sys_setup.h"
#include "rtos.h"

#if(APOLLO_OTA_TYPE == APOLLO_OTA_VER_2)
#if(SMOVT_TYPE == SMOVT_H002)
#include "h002_memory_v2.h"
#elif(SMOVT_TYPE == SMOVT_H003)
#include "h003_memory_v2.h"
#endif
#include "amotas_api.h"
#endif

int main(void)
{
    const ble_otaflag_t *checkflag;

    //step 1: read OTA Flag
    checkflag = (ble_otaflag_t *)OTA_FLAG_ROM_ADDR;

	/* 系统初始化 */
	System_Init();
	SEGGER_RTT_Init();

    if(checkflag->u8IsOTA == TRUE)
    {
        //进入OTA模式
        CreateOTA_Task();
    }
    else
    {
        //在更新场景/主题过程中出现异常复位重启，需对其数据进行校验，
        //若数据完整，则更新；否则清除标记
        if(checkflag->u8IsUpdate == TRUE)
        {
            ;
        }

        /* 
            创建开始任务，让外设在OS系统内初始化
            因为有些外设初始化过程中用到OS相关函数
            注：开始任务优先级必须最高
        */
        xTaskCreate(start_task, "start_task", 1024, NULL, TASK_PRIORITY_START, NULL); 
    }

	vTaskStartScheduler();
    while(1)
	{
		RTT_DEBUG_printf(0,"Sys Init Fail \n");
	}
}


