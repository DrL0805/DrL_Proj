// system
#include "platform_common.h"
#include "system_task.h"
#include "am_util_delay.h"

// mid层
#include "mid_interface.h"
#include "scene_interface.h"
#include "store_interface.h"
#include "ble_task.h"

// app层
#include "app_lcd.h"
#include "app_protocal.h"
#include "app_variable.h"
#include "ui_display_main.h"
#include "app_task.h"
#include "app_systerm.h"
#include "app_time.h"

// 测试
#include "drv_bm43.h"
#include "drv_ntc.h"
#include "sm_gpio.h"

/*******************************************************************************
 * Brief : BSP硬件初始化
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
static void Bsp_Init(void)
{
	Mid_Schd_ParamInit();	// 共享互斥初始化放在前面
	
	Drv_MTimer_Init();		// 放在初始化前面
	
//	Mid_Uart_Init();
	Mid_Key_Init();
	Mid_Motor_Init();
	Mid_Magnetism_Init();
	Mid_6Dof_Init();
	Mid_Hrm_Init();			// 心率初始化产生约1uA功耗
	Mid_Press_Init();
	Mid_Bat_Init();			// 初始化后产生功耗10uA+
	Mid_Mic_Init();
	Drv_GPS_Init();
	Drv_NTC_Init();
	Mid_IT_Init();
	Mid_Lcd_Init();
	Mid_Rtc_Init();
	Mid_Font_Init();	// 未初始产生化功耗80uA+
	Drv_Touch_Init();
	Mid_WDT_Init();
	Mid_NandFlash_Init();	// 未初始产生化功耗3mA+
    Store_Part_Init();		// 注：FLASH硬件初始化完后，紧接着初始化Store_part
	
	Mid_Ble_Init();			//
//	vTaskDelay(10000);
//	App_Protocal_BleStateSet(BLE_POWEROFF);
    geBleState = BLE_POWEROFF;
}

/*******************************************************************************
 * Brief : 系统Task初始化
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
static void Task_Init(void)
{
	// 中间层任务
	Mid_Schd_TaskCreate();

	// 模块化任务
	Scene_Task_TaskCreate();
	Store_Task_Create();
	
	// 应用层任务
	App_Time_TaskCreate();
	App_Lcd_TaskCreate();
	App_Schd_TaskCreate();
}

//手表应用入口
void start_task(void *pvParameters)
{
	/* 初始化过程中禁止中断和任务调度 */ 
	taskENTER_CRITICAL();  	
	
	Bsp_Init();
	Task_Init();
	
	taskEXIT_CRITICAL();            //退出临界区
	
	vTaskDelete(NULL); 				//删除开始任务
}

