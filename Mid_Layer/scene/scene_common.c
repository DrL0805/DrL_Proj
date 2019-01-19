
#include "scene_common.h"
#include "app_variable.h"

void Scene_Cnm_HrZoneGet(hrZoneRange_t* fhrZone)
{
	alg_common_get_hrzone(gtBodyInfo.age, fhrZone);
}

/*******************************************************************************
 * Brief : ������������������ޣ���ȡ����������ֵ
 * Input : @Zone �������䣬ȡֵ1~5
 * Return: @UpDownLimit �����ޱ�־��0���ޣ�1����
 * Call  : 
 ***************/
uint8_t Scene_Cnm_HrLimitGet(uint8_t Zone, uint8_t UpDownFlg)
{
	hrZoneRange_t fhrZoneRange;
	uint8_t lHrZone;
	
	alg_common_get_hrzone(gtBodyInfo.age, &fhrZoneRange);
	
	if(0 == UpDownFlg)	// ����
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
	else // ����
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















