/**********************************************************************
**
**模块说明: mid层KEY接口
**软件版本，修改日志(时间，内容),修改人:
**   V1.0   2018.4.24  修改流程  ZSL  
**
**********************************************************************/
#include "sm_timer.h"
#include "scene_countdown.h"
#include "scene_task.h"


static SceneCountDownParam_t	SceneCountDownParam;

/*******************************************************************************
 ** Brief : 中断回调函数，当倒计时满后，向上层发送事件
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Mid_Countdown_Isr(void)
{
	SceneTaskMsg_t	lSceneTaskMsg;
	
	if(0 == --SceneCountDownParam.RemainSec)
	{
		Scene_Countdown_Reset();
		
		lSceneTaskMsg.Id = eSceneTaskMsgCountdown;
		lSceneTaskMsg.Param.Countdown.Id = eCountDownEventTimeOut;
		Scene_Task_TaskEventSet(&lSceneTaskMsg);
	}

	SCENE_COUNTDOWN_RTT_LOG(0,"SceneCountDownParam.RemainSec %d \n", Scene_Countdown_RemainRead());
}

/*******************************************************************************
 ** Brief : 倒计时复位
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_Countdown_Reset(void)
{
	SceneCountDownParam.RemainSec = SceneCountDownParam.TotalSec;
	SceneCountDownParam.State = eCountDownStop;

    SMDrv_CTimer_Clear(COUNTDOWN_CTIMER_MODULE);
}

/*******************************************************************************
 ** Brief : 倒计时初始化,硬件初始化，并注册中断回调函数
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_Countdown_Init(void)
{
	SceneCountDownParam.InitedFlg = true;

    SMDrv_CTimer_Open(COUNTDOWN_CTIMER_MODULE, COUNTDOWN_PERIOD_MS, Mid_Countdown_Isr);
    Scene_Countdown_Reset();
}

/*******************************************************************************
 ** Brief : 倒计时开始
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_Countdown_Start(void)
{
	SceneCountDownParam.State = eCountDownRuning;
	
    SMDrv_CTimer_Start(COUNTDOWN_CTIMER_MODULE);
}

/*******************************************************************************
 ** Brief : 倒计时暂停
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_Countdown_Suspend(void)
{
	SceneCountDownParam.State = eCountDownSuspend;
	
    SMDrv_CTimer_Stop(COUNTDOWN_CTIMER_MODULE);
}

/*******************************************************************************
 ** Brief : 读取倒计时剩余时间
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
 uint32_t Scene_Countdown_RemainRead(void)
{
	return SceneCountDownParam.RemainSec;
}

/*******************************************************************************
 ** Brief : 设置/写入倒计时剩余时间
 ** Input : @timeTemp：传入倒计时剩余时间参数 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_Countdown_TimeWrite(uint32_t Sec)
{
	SceneCountDownParam.TotalSec = Sec;
	SceneCountDownParam.RemainSec = Sec;
}

/*******************************************************************************
 ** Brief : 获取参数指针
 ** Input : @NULL
 ** Return: @NULL
 ** Call  : 
 ***************/
SceneCountDownParam_t* Scene_Countdown_ParamPGet(void)
{
	return &SceneCountDownParam;
}

void Scene_Countdown_Test(void)
{
	SCENE_COUNTDOWN_RTT_LOG(0,"Scene_Countdown_Test \n");
	
	#if 1	// 倒计时测试
	Scene_Countdown_TimeWrite(17);
	Scene_Countdown_Start();
	#endif
}







