#include "platform_common.h"
#include "mid_common.h"
#include "image_info.h"
#include "sm_sys.h"

uint16		sysAppHandle;
uint16		sysAppHandleBak;


void NullFunc(void)
{
	
}

//**********************************************************************
// 函数功能:	获取总架构信息
// 输入参数：	无
// 返回参数：	无
uint32 VersionRead(void)
{
	return PROJECT_VERSION;
}

uint8 Mid_SystermReset(void)
{
	SMDrv_SYS_DisableMasterIsr();
    SMDrv_SYS_PowerOnReset();  
	return Ret_OK;	
}

