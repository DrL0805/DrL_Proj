/**********************************************************************
**
**ģ��˵��: mid��KEY�ӿ�
**����汾���޸���־(ʱ�䣬����),�޸���:
**   V1.0   2018.4.24  �޸�����  ZSL  
**
**********************************************************************/
#include "sm_timer.h"
#include "scene_countdown.h"
#include "scene_task.h"


static SceneCountDownParam_t	SceneCountDownParam;

/*******************************************************************************
 ** Brief : �жϻص�������������ʱ�������ϲ㷢���¼�
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
 ** Brief : ����ʱ��λ
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
 ** Brief : ����ʱ��ʼ��,Ӳ����ʼ������ע���жϻص�����
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
 ** Brief : ����ʱ��ʼ
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
 ** Brief : ����ʱ��ͣ
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
 ** Brief : ��ȡ����ʱʣ��ʱ��
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
 uint32_t Scene_Countdown_RemainRead(void)
{
	return SceneCountDownParam.RemainSec;
}

/*******************************************************************************
 ** Brief : ����/д�뵹��ʱʣ��ʱ��
 ** Input : @timeTemp�����뵹��ʱʣ��ʱ����� 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_Countdown_TimeWrite(uint32_t Sec)
{
	SceneCountDownParam.TotalSec = Sec;
	SceneCountDownParam.RemainSec = Sec;
}

/*******************************************************************************
 ** Brief : ��ȡ����ָ��
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
	
	#if 1	// ����ʱ����
	Scene_Countdown_TimeWrite(17);
	Scene_Countdown_Start();
	#endif
}







