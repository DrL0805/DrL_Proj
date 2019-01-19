#include "scene_sleep.h"
#include "mid_interface.h"

SceneSleepParam_t	SceneSleep;

/*******************************************************************************
 ** Brief : ˯���㷨������ȡ�������ݻص�����
 ** Input : @xyzData  ������������
			@Interval ��������
 ** Return: @NULL
 ** Call  : ˯���㷨��1��1��
 ***************/
void Scene_Sleep_algorithm(int16 *xyzData, uint32_t Interval)
{
	if(!SceneSleep.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Sleep_algorithm", Ret_NoInit); 
	
	if(SceneSleep.EnableFlg)
	{
		SceneSleep.IntervalMs += Interval;
		if(SceneSleep.IntervalMs >= SLEEP_SCENE_PERIOD_MS)
		{
			SceneSleep.IntervalMs -= SLEEP_SCENE_PERIOD_MS;
			
			alg_sleep_process(xyzData, 0xFF);
		}	
	}
}

/*******************************************************************************
 ** Brief : ˯����Ϣ��ʼ��
 ** Input : @NULL
 ** Return: @NULL
 ** Call  : ��ʼ������һ��
 ***************/
void Scene_Sleep_Init(void)
{	
	SceneSleep.InitFlg = true;
}
 
/*******************************************************************************
 ** Brief : ���ǰһ��˯������
 ** Input : @NULL
 ** Return: @NULL
 ** Call  : ÿ��������
 ***************/
void Scene_Sleep_Clear(void)
{
	alg_sleep_clr_record();
}

/*******************************************************************************
 ** Brief : ���ػ�ȡ˯��������Ϣ������UI����
 ** Input : @NULL
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_Sleep_RecordGet(sleep_record_t *sleepRecord)
{
	alg_sleep_get_record(sleepRecord);
}

/*******************************************************************************
 ** Brief : ˯�߳�������
 ** Input : @NULL
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_Sleep_Enable(void)
{
	if(!SceneSleep.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Sleep_Enable", Ret_NoInit); 

	alg_sleep_init();
	alg_sleep_clr_record();
	
	SceneSleep.IntervalMs = 0;
	SceneSleep.EnableFlg = true;
}

/*******************************************************************************
 ** Brief : ˯�߳����ر�
 ** Input : @NULL
 ** Return: @NULL
 ** Call  : 
 ***************/
void Scene_Sleep_Disable(void)
{
	if(!SceneSleep.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Sleep_Disable", Ret_NoInit); 

	SceneSleep.EnableFlg = false;
}












