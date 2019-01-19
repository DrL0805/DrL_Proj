#include "scene_gesture.h"
#include "mid_interface.h"
#include "app_protocal.h"

Scene_Gesture_Param_t	Scene_Gesture;

/*******************************************************************************
 * Brief : 手势识别算法，
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Gesture_algorithm(int16 *xyzData, uint32_t Interval)
{
	if(!Scene_Gesture.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Gesture_algorithm", Ret_NoInit); 	

	if(Scene_Gesture.EnableFlg)
	{
		Scene_Gesture.IntervalMs += Interval;
		if(Scene_Gesture.IntervalMs >= GESTURE_SCENE_PERIOD_MS)
		{
			Scene_Gesture.IntervalMs -= GESTURE_SCENE_PERIOD_MS;

			/* 调用动作识别算法 */ 
			switch(gesture_process(xyzData))
			{
				case GESTURE_NULL: 
					break;
				case RAISE_HAND:	/* 抬手 */
					SCENE_GESTURE_RTT_LOG(0, "RAISE_HAND \r\n");
					break;
				case FREE_HAND:		 /* 放手 */
					SCENE_GESTURE_RTT_LOG(0, "FREE_HAND \r\n");
					break;
				case TURN_WRIST:	 /* 翻腕 */
					SCENE_GESTURE_RTT_LOG(0, "TURN_WRIST \r\n");
					break;
				case SHAKE_HAND:	 /* 甩手 */	
					SCENE_GESTURE_RTT_LOG(0, "SHAKE_HAND \r\n");
					switch(gtPhoneState.state)
					{
						case PHONE_STATE_NORMAL:
							break;
						case PHONE_STATE_PHOTO:
							App_Protocal_TakePhoto();
							break;
						case PHONE_STATE_AUTHOR:
							gtPhoneState.state = PHONE_STATE_NORMAL;
							App_Protocal_AuthorPass();
							break;
						case PHONE_STATE_PAIRE:
							break;
						case PHONE_STATE_HRM:
							break;
						default: break;
					}
					break;
				default: break;
			}
		}	
	}
}


/*******************************************************************************
 * Brief : 
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Gesture_Init(void)
{
	Scene_Gesture.InitFlg = true;
}

/*******************************************************************************
 * Brief : 
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/	
void Scene_Gesture_Enable(void)
{
	if(!Scene_Gesture.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Gesture_Enable", Ret_NoInit); 

	Scene_Gesture.IntervalMs = 0;
	Scene_Gesture.EnableFlg = true;
}


/*******************************************************************************
 * Brief : 
 * Input : @NULL 
 * Return: @NULL
 * Call  : 
 ***************/
void Scene_Gesture_Disable(void)
{
	if(!Scene_Gesture.InitFlg) drERROR_CHECK_RETURN_NULL("Scene_Gesture_Disable", Ret_NoInit); 	

	Scene_Gesture.EnableFlg = false;
}





