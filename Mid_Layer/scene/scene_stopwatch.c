/**********************************************************************
**
**ģ��˵��: mid��stop watch�ӿ�
**����汾���޸���־(ʱ�䣬����),�޸���:
**   V1.0   2018.4.24  �޸�����  ZSL  
**
**********************************************************************/
#include "sm_timer.h"
#include "scene_stopwatch.h"

SceneStopWatchParam_t	SceneStopWatchParam;

/*******************************************************************************
 ** Brief : ����жϻص�����
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
static void Scene_StopWatch_IsrCb(void)
{
	SceneStopWatchParam.TotalMs += STOPWATCH_PERIOD_MS;
}

/*******************************************************************************
 ** Brief : ���λ��������������ȫ����λΪ0�������Timer����Ӳ����λ
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_StopWatch_Reset(void)
{
	SceneStopWatchParam.MeasureCnt = 0;
	SceneStopWatchParam.TotalMs = 0;
	SceneStopWatchParam.State = eStopWatchStop;
	
	// ���㲢ֹͣ��ʱ��
    SMDrv_CTimer_Clear(STOPWATCH_CTIMER_MODULE);
}

/*******************************************************************************
 ** Brief : ����ܳ�ʼ��������
			�����Timer����Ӳ�����г�ʼ������ע���жϻص�����������������λ
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_StopWatch_Init(void)
{
    SMDrv_CTimer_Open(STOPWATCH_CTIMER_MODULE,STOPWATCH_PERIOD_MS,Scene_StopWatch_IsrCb);
	
	Scene_StopWatch_Reset();

	SceneStopWatchParam.InitedFlg = true;
}

/*******************************************************************************
 ** Brief : �������
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_StopWatch_Start(void)
{
	SceneStopWatchParam.State = eStopWatchRuning;
	
    SMDrv_CTimer_Start(STOPWATCH_CTIMER_MODULE);
}

/*******************************************************************************
 ** Brief : �ݶ����
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_StopWatch_Suspend(void)
{
	SceneStopWatchParam.State = eStopWatchSuspend;
	
    SMDrv_CTimer_Stop(STOPWATCH_CTIMER_MODULE);
}

/*******************************************************************************
 ** Brief : �����������㣬�ѵ�ǰ���ʱ�䱣������
			�����ʱ���ȡ������������
 ** Input : @NULL 
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_StopWatch_MeasureMark(void)
{
	if(SceneStopWatchParam.MeasureCnt >= STOPWATCH_MAX_STORE)
		return;	
	
	uint32 cntTemp;
	
	// ��ȡ��ǰtickֵ����תΪms��ʱ��ʹ�õ���32768Hz
	cntTemp = (uint32_t)SMDrv_CTimer_ReadCount(STOPWATCH_CTIMER_MODULE) * 0.0305;	// (1000 / 32768)
	
	// ���浱ǰ��������ʱ��ֵ
	SceneStopWatchParam.MeasurePoint[SceneStopWatchParam.MeasureCnt] = SceneStopWatchParam.TotalMs + cntTemp;
	SceneStopWatchParam.MeasureCnt++;
}

/*******************************************************************************
 ** Brief : ��ȡ��ǰ������ֵ
 ** Input : @Methon ��ȡ������0������������0������
 ** Return: @NULL
 ** Call  : 
 ***************/
uint32_t Scene_StopWatch_TotalMsGet(uint8_t Methon)
{	
	if(Methon)
	{
		uint32 cntTemp;
		
		// ��ȡ��ǰtickֵ����תΪms��ʱ��ʹ�õ���32768Hz
		cntTemp = (uint32_t)SMDrv_CTimer_ReadCount(STOPWATCH_CTIMER_MODULE) * 0.0305;	// (1000 / 32768)
		
		return (SceneStopWatchParam.TotalMs + cntTemp);
	}
	else
	{
		return SceneStopWatchParam.TotalMs;
	}
}

/*******************************************************************************
 ** Brief : ��ȡ�����Ľṹ��ָ��
 ** Input : @NULL
 ** Return: @NULL
 ** Call  : 
 ***************/
SceneStopWatchParam_t* Scene_StopWatch_ParamPGet(void)
{
	return &SceneStopWatchParam;
}

/*******************************************************************************
 ** Brief : msֵתΪ h:m:s:msģʽ
 ** Input : @Ms ��ת����Msֵ
 ** Return: @fStopWatchFormat ����ת�����
 ** Call  : 
 ***************/
void Scene_StopWatch_FormatSwitch(uint32_t Ms, SceneStopWatchFormat_t* fStopWatchFormat)
{
	uint32_t tMs = Ms;
	
	fStopWatchFormat->hour = tMs / 3600000;
	
	tMs %= 3600000;
	fStopWatchFormat->min = tMs / 60000;
	
	tMs %= 60000;
	fStopWatchFormat->sec = tMs / 1000;	
	
	tMs %= 1000;
	fStopWatchFormat->ms = tMs;	
}


void Scene_StopWatch_Test(void)
{
	SCENE_STOPWATCH_RTT_LOG(0,"Scene_StopWatch_Test \n");
	
	#if 1	// ������
	SceneStopWatchParam_t* tStopWatchParam;
	
	SceneStopWatchFormat_t	sStopWatchFormat;
	
	uint32_t	tStopWatchTotalMs = 0;
	
	tStopWatchParam = Scene_StopWatch_ParamPGet();
	SCENE_STOPWATCH_RTT_LOG(0,"InitedFlg %d \n", (tStopWatchParam)->InitedFlg);
	SCENE_STOPWATCH_RTT_LOG(0,"MeasureCnt %d \n", (tStopWatchParam)->MeasureCnt);
	SCENE_STOPWATCH_RTT_LOG(0,"State %d \n", (tStopWatchParam)->State);
	SCENE_STOPWATCH_RTT_LOG(0,"TotalMs %d \n", (tStopWatchParam)->TotalMs);
	
	if(eStopWatchStop == tStopWatchParam->State)
	{
		Scene_StopWatch_Start();
		SCENE_STOPWATCH_RTT_LOG(0,"Scene_StopWatch_Start \r\n");
	}
	else
	{
		Scene_StopWatch_MeasureMark();	// ������
		tStopWatchParam = Scene_StopWatch_ParamPGet();	// ��ȡ�²���
		tStopWatchTotalMs = Scene_StopWatch_TotalMsGet(true);	// ��������ʽ��ȡ��ǰ��ʱ��
		
		Scene_StopWatch_FormatSwitch(tStopWatchTotalMs, &sStopWatchFormat);	// ʱ���ʽת��
		
		SCENE_STOPWATCH_RTT_LOG(0,"tStopWatchTatolMs %d, %d:%d:%d:%d \r\n", 
			tStopWatchTotalMs, sStopWatchFormat.hour, sStopWatchFormat.min, sStopWatchFormat.sec, sStopWatchFormat.ms);
		
		for(uint32_t i = 0; i < tStopWatchParam->MeasureCnt; i++)
		{
			SCENE_STOPWATCH_RTT_LOG(0,"%d ", tStopWatchParam->MeasurePoint[i]);
		}SCENE_STOPWATCH_RTT_LOG(0,"\r\n");
	}
	#endif
}










