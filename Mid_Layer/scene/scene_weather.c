#include "scene_weather.h"

static 	SceneWeahterParam_t SceneWeahterParam;			//��������	

/*******************************************************************************
 ** Brief : ����������ʼ��
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
 ** Brief : ��ȡ������Ϣ
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_Weather_TendencyGet(SceneWeahterParam_t *weatherinfo)
{
	memcpy(weatherinfo, &SceneWeahterParam, sizeof(SceneWeahterParam_t));
}

/*******************************************************************************
 ** Brief : ��ȡ������Ϣ
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
	
	App_Protocal_GetWeatherProcess();	// ��app��ȡ������Ϣ
	vTaskDelay(200);
	Scene_Weather_TendencyGet(&tWeahter);
	SCENE_WEATHER_RTT_LOG(0,"tWeahter %d, %d, %d, %d, \r\n", 
		tWeahter.Status, tWeahter.CurTemperature, tWeahter.MaxTemperature, tWeahter.MinTemperature);
	#endif
}


