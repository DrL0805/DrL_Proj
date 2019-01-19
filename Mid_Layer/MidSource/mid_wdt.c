#include "mid_wdt.h"
#include "sm_wdt.h"

static void Mid_WDT_IsrCb(void)
{
	MID_WDT_RTT_LOG(0, "Mid_WDT_IsrCb \n");
}

void Mid_WDT_Init(void)
{
	#if MID_WDT_ENABLE
	MID_WDT_RTT_LOG(0, "Mid_WDT_Init \n");
	
	SMDrv_WDT_Init();
	#endif
}

// 使能开门狗
void Mid_WDT_Enable(void)
{
	#if MID_WDT_ENABLE
	MID_WDT_RTT_LOG(0, "Mid_WDT_Enable \n");
	
	SMDrv_WDT_SetIsrPrio(NVIC_WDT_PRIO);
	SMDrv_WDT_Open(255,127,Mid_WDT_IsrCb);
	SMDrv_WDT_ReStart();
	#endif	
}

// 禁能开门狗
void Mid_WDT_Disable(void)
{
	#if MID_WDT_ENABLE
	MID_WDT_RTT_LOG(0, "Mid_WDT_Disable \n");
	
	SMDrv_WDT_Close();
	#endif
}

// 喂狗
void Mid_WDT_ReStart(void)
{
	#if MID_WDT_ENABLE
	MID_WDT_RTT_LOG(0, "Mid_WDT_ReStart \n");
	
	SMDrv_WDT_ReStart();
	#endif	
}

