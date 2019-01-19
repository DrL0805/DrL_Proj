/*
 * 模块接口函数
 * 外部需使用此模块接口函数/外部变量/宏定义等，包含以下头文件即可：
 * #include "xxx_interface.h"
*/

#include "scene_interface.h"

void Scene_Interface_Init(void)
{
	Scene_Step_Init();	// 计步最先初始化
	
	Scene_Run_Init();
	Scene_Climb_Init();
	Scene_Swim_Init();
	
	Scene_StopWatch_Init();
	Scene_Countdown_Init();
	Scene_Sedentary_Init();
	Scene_Hrm_Init();
	Scene_Stress_Init();
	Scene_ABC_ABInit();
	Scene_Findphone_Init();
	Scene_Gesture_Init();
	Scene_Sleep_Init();
	Scene_ABC_CompassInit();
	Scene_Stair_Init();
	Scene_Weather_Init();
}


void Scene_Interface_Enable(void)
{
	Scene_Step_Enable();	// 计步最先使能
	
	Scene_Sedentary_Enable();
	Scene_Hrm_Enable();
	Scene_Stress_Enable();
	Scene_ABC_ABEnable();
	Scene_Gesture_Enable();
	Scene_Sleep_Enable();
	Scene_Stair_Enable();
}

void Scene_Interface_Disable(void)
{
	Scene_Sedentary_Disable();
}















