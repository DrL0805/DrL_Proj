
#include "scene_common.h"
#include "app_variable.h"

void Scene_Cnm_HrZoneGet(hrZoneRange_t* fhrZone)
{
	alg_common_get_hrzone(gtBodyInfo.age, fhrZone);
}

/*******************************************************************************
 * Brief : 根据心率区间和上下限，获取上下限心率值
 * Input : @Zone 心率区间，取值1~5
 * Return: @UpDownLimit 上下限标志，0上限，1下限
 * Call  : 
 ***************/
uint8_t Scene_Cnm_HrLimitGet(uint8_t Zone, uint8_t UpDownFlg)
{
	hrZoneRange_t fhrZoneRange;
	uint8_t lHrZone;
	
	alg_common_get_hrzone(gtBodyInfo.age, &fhrZoneRange);
	
	if(0 == UpDownFlg)	// 上限
	{
		switch (Zone)
        {
        	case 1: lHrZone = fhrZoneRange.HrZone0; break;
        	case 2: lHrZone = fhrZoneRange.HrZone1; break;
			case 3: lHrZone = fhrZoneRange.HrZone2; break;
			case 4: lHrZone = fhrZoneRange.HrZone3; break;
			case 5: lHrZone = fhrZoneRange.HrZone4; break;
        	default :
				drERROR_CHECK("Scne_Cnm_HrLimitGet", Ret_InvalidParam);	
				lHrZone = fhrZoneRange.HrZone0;		
        		break;
        }
	}
	else // 下限
	{
		switch (Zone)
        {
        	case 1: lHrZone = fhrZoneRange.HrZone1; break;
        	case 2: lHrZone = fhrZoneRange.HrZone2; break;
			case 3: lHrZone = fhrZoneRange.HrZone3; break;
			case 4: lHrZone = fhrZoneRange.HrZone4; break;
			case 5: lHrZone = fhrZoneRange.HrZone5; break;
        	default :
				drERROR_CHECK("Scne_Cnm_HrLimitGet", Ret_InvalidParam);
				lHrZone = fhrZoneRange.HrZone5;				
        		break;
        }		
	}

	return lHrZone;
}















