#include "scene_weather.h"

static 	SceneWeahterParam_t SceneWeahterParam;			//天气趋势	

/*******************************************************************************
 ** Brief : 天气场景初始化
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_Weather_Init(void)
{
	SceneWeahterParam.Status 	= WEATHER_TENDENCY_CLOUDY;
	SceneWeahterParam.CurTemperature = SCENE_WEATHER_INVALID_TEMP;
	SceneWeahterParam.MaxTemperature = SCENE_WEATHER_INVALID_TEMP;
	SceneWeahterParam.MinTemperature = SCENE_WEATHER_INVALID_TEMP;
}

/*******************************************************************************
 ** Brief : 获取天气信息
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_Weather_TendencyGet(SceneWeahterParam_t *weatherinfo)
{
	memcpy(weatherinfo, &SceneWeahterParam, sizeof(SceneWeahterParam_t));
}

/*******************************************************************************
 ** Brief : 获取天气信息
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_Weather_TendencySet(SceneWeahterParam_t *weatherinfo)
{
	SCENE_WEATHER_RTT_LOG(0,"Scene_Weather_TendencySet %d, %d, %d, %d, \r\n", 
		weatherinfo->Status, weatherinfo->CurTemperature, weatherinfo->MaxTemperature, weatherinfo->MinTemperature);	
	
	memcpy(&SceneWeahterParam, weatherinfo, sizeof(SceneWeahterParam_t));
}

#include "app_protocal.h"
void Scene_Weather_Test(void)
{
	SCENE_WEATHER_RTT_LOG(0,"Scene_Weather_Test \n");

	#if 1
	SceneWeahterParam_t	tWeahter;
	
	App_Protocal_GetWeatherProcess();	// 向app获取天气信息
	vTaskDelay(200);
	Scene_Weather_TendencyGet(&tWeahter);
	SCENE_WEATHER_RTT_LOG(0,"tWeahter %d, %d, %d, %d, \r\n", 
		tWeahter.Status, tWeahter.CurTemperature, tWeahter.MaxTemperature, tWeahter.MinTemperature);
	#endif
}


