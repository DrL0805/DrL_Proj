#include "platform_common.h"
#include "bsp_common.h"




//多传感器芯片管理
MultiSensor_s multisensor =
{
	.accelstate = uinit,
	.gyrostate 	= uinit,
	.magstate 	= uinit,
};

//共享总线管理
ShareBusSpi_s sharebusspi =
{
	.ExtFlash 	= BusUninit,
	.NandFlash 	= BusUninit,
	.WordStack 	= BusUninit,
};    

ShareBusI2c_s sharebusi2c =
{
	.Accels 	= BusUninit,
	.Gyros 		= BusUninit,
	.Mags 		= BusUninit,
	.Pressure	= BusUninit,
	.Hrm 		= BusUninit,
};


/*******************************************************************************
 * Brief : 比较两数组值是否完相同
 * Input : @str1 数组1
		   @str2 数组2
		   @len	比较的长度
 * Return: true：相同，false：不同
 * Call  : 
 ***************/
bool drCMN_ArrayCmp(uint8_t *str1, uint8_t *str2, uint8_t len)
{
	uint8_t i;
	for(i = 0; i < len ; i++)
	{
		if(str1[i] != str2[i])
			return false;
	}
	return true;
}

/*******************************************************************************
 * Brief : 循环获取下一序号
 * Input : @MaxPos 位置数量，序号范围 0~(fPosNum-1)
		   @CurrPos 当前序号
		   @fShift 移动次数及方向（正数前移，负数后移）
 * Return: 下一序号
 * Call  : 
 ***************/
uint32_t drCMN_CyclePosNext(uint32_t fPosNum, uint32_t fCurrPos, int32_t fShift)
{
	uint32_t lTmp0 = fShift % fPosNum;	// 剔除循环的情况，真正移动次数
	
	if(fShift >= 0)	// 前移
	{
		return ((fCurrPos + lTmp0) % fPosNum);
	}
	else			// 后移
	{
		return (((fCurrPos + lTmp0)+fPosNum) % fPosNum);	// 先+fPosNum是为了把负数转换为正数，且位置不变
	}
}


// 获取两个数的最大公约数
uint32_t drCnm_GCDGet(uint32_t a, uint32_t b)
{
    uint32_t r;
    while (b != 0)
	{
        r = a % b; 
		a = b; 
		b = r;
    }
    return a;
}





















