#include "scene_findphone.h"
#include "scene_task.h"
#include "app_protocal.h"

Scene_Findphone_Param_t	Scene_Findphone;

static TimerHandle_t 	Findphone_TimerHandle;

static void Findphone_TimerCallBack(TimerHandle_t xTimer)
{
	SceneTaskMsg_t	lSceneTaskMsg;
	
	lSceneTaskMsg.Id = eSceneTaskMsgFindphone;
	lSceneTaskMsg.Param.Findphone.Id = eFindphoneEventTimerCb;
	Scene_Task_TaskEventSet(&lSceneTaskMsg);	

	SCENE_FINDPHONE_RTT_LOG(0, "Findphone_TimerCallBack \n");
}

void Scene_Findphone_Init(void)
{
    Findphone_TimerHandle=xTimerCreate((const char*		)"Findphone_Timer",
									    (TickType_t			)(3000/portTICK_PERIOD_MS),
							            (UBaseType_t		)pdTRUE,
							            (void*				)1,
							            (TimerCallbackFunction_t)Findphone_TimerCallBack);
	
	Scene_Findphone.InitFlg = true;
}

void Scene_Findphone_Start(void)
{
	if(!Scene_Findphone.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Findphone_Start", Ret_NoInit); 
	
	Scene_Findphone.EnableFlg = true;
	
	App_Protocal_FinePhone();	// 发送一次查找手机指令
	
	xTimerStart(Findphone_TimerHandle,3);
	
	SCENE_FINDPHONE_RTT_LOG(0, "Scene_Findphone_Start \n");
}

void Scene_Findphone_Stop(void)
{
	if(!Scene_Findphone.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Findphone_Stop", Ret_NoInit); 
	
	Scene_Findphone.EnableFlg = false;
	
	xTimerStop(Findphone_TimerHandle,3);
	
	SCENE_FINDPHONE_RTT_LOG(0, "Scene_Findphone_Stop \n");
}

void Scene_Findphone_Test(void)
{
	SCENE_FINDPHONE_RTT_LOG(0,"Scene_Findphone_Test \n");
	
	#if 1	// 查找手机指令测试
	static uint8_t tFlg = false;
	
	if(!tFlg && (BLE_CONNECT == geBleState))
	{	
		tFlg = true;
		Scene_Findphone_Start();
	}
	else
	{
		tFlg = false;
		Scene_Findphone_Stop();
	}
	#endif
}








