#ifndef MID_WDT_H
#define MID_WDT_H

#define MID_WDT_RTT_DEBUG	2
#if (1 == MID_WDT_RTT_DEBUG)	// 错误等级
#define MID_WDT_RTT_LOG(...)
#define MID_WDT_RTT_WARN(...)
#define MID_WDT_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MID_WDT_RTT_DEBUG)	// 警告等级
#define MID_WDT_RTT_LOG(...)
#define MID_WDT_RTT_WARN		RTT_DEBUG_WARN
#define MID_WDT_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MID_WDT_RTT_DEBUG)	// 调试等级
#define MID_WDT_RTT_LOG		RTT_DEBUG_LOG
#define MID_WDT_RTT_WARN		RTT_DEBUG_WARN
#define MID_WDT_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define MID_WDT_RTT_LOG(...)
#define MID_WDT_RTT_WARN(...)
#define MID_WDT_RTT_ERR(...)
#endif

#define MID_WDT_ENABLE	0

extern void Mid_WDT_Init(void);
extern void Mid_WDT_Enable(void);
extern void Mid_WDT_Disable(void);
extern void Mid_WDT_ReStart(void);

#endif









