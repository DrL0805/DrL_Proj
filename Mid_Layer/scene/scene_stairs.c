#include "scene_stairs.h"
#include "scene_step.h"
#include "scene_abc.h"

SceneStairParam_t	SceneStairParam;

/*******************************************************************************
 * Brief : ��¥���㷨
 * Input : @NULL 
 * Return: @NULL
 * Call  : ÿ�����һ��
 ***************/
void Scene_Stair_Algorithm(void)
{
	if(!SceneStairParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Stair_Algorithm", Ret_NoInit); 
	
	if(SceneStairParam.EnableFlg)
	{
		ab_value_t lab_value;
		Scene_ABC_ABGet(&lab_value);		
		SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();		
		
		alg_climb_stairs_process(lpSceneStepParam->totalStep, lab_value.altitude);
	}
}

void Scene_Stair_Init(void)
{
	SceneStairParam.InitFlg = true;
}

/*******************************************************************************
 * Brief : �����¥���ݣ���ʼ����ÿ��������
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Stair_Clear(void)
{
	ab_value_t lab_value;
	Scene_ABC_ABGet(&lab_value);		
	SceneStepParam_t* lpSceneStepParam = Scene_Step_ParamPGet();
	
	alg_climb_stairs_start(lpSceneStepParam->totalStep, lab_value.altitude);
}

void Scene_Stair_Enable(void)
{
	if(!SceneStairParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Stair_Enable", Ret_NoInit); 

	Scene_Stair_Clear();
	
	SceneStairParam.EnableFlg = true;
}

void Scene_Stair_Disable(void)
{
	if(!SceneStairParam.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Stair_Disable", Ret_NoInit); 
	
	SceneStairParam.EnableFlg = false;
}

/*******************************************************************************
 * Brief : ��ȡ��¥�ݲ����ṹ��ָ�룬�ٴ�֮ǰ�ȼ��㵱����¥�����ܺ�
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
SceneStairParam_t* Scene_Stair_ParamPGet(void)
{
	uint16_t lUpFloor,lDownFloor;
	
	alg_climb_stairs_get_floor(&lUpFloor, &lDownFloor);
	SceneStairParam.DayFloor = lUpFloor+lDownFloor;
	
	return &SceneStairParam;
}














