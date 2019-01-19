#ifndef BAT_APP_H
#define	BAT_APP_H

#include "platform_common.h"

#define MID_BAT_RTT_DEBUG	3
#if (1 == MID_BAT_RTT_DEBUG)
#define MID_BAT_RTT_LOG(...)
#define MID_BAT_RTT_WARN(...)
#define MID_BAT_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MID_BAT_RTT_DEBUG)
#define MID_BAT_RTT_LOG(...)
#define MID_BAT_RTT_WARN	RTT_DEBUG_WARN
#define MID_BAT_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MID_BAT_RTT_DEBUG)
#define MID_BAT_RTT_LOG		RTT_DEBUG_LOG
#define MID_BAT_RTT_WARN		RTT_DEBUG_WARN
#define MID_BAT_RTT_ERR		RTT_DEBUG_ERR
#else
#define MID_BAT_RTT_LOG(...)
#define MID_BAT_RTT_WARN(...)
#define MID_BAT_RTT_ERR(...)
#endif

typedef void (*midbat_cb)(uint8 bat_msg);

typedef enum
{
    MID_BAT_OFF_CHARGE 		= 0x00,
    MID_BAT_IN_CHARGING,
    MID_BAT_FULL_CHARGE,
    MID_BAT_LOW_LEVEL,		// 低电（如电量低于10%），仅到电池电量小于10%时，报警一次
    MID_BAT_LOW_ALERT,   	// 电量计低电报警，当电池电量低时，会一直触发报警
}BatStatusType_e;

typedef enum 
{
	BOTTUN_CELL = 0,
	CHARGING_CELL,
}BatCellType_e;

typedef enum 
{
	eBatEventBatCheck,		// 电池电量监测
	eBatEventChargCheck,	// 充电检测
	eBatEventStatusChange,
}BatEventId_e;

typedef struct
{
	BatEventId_e		Id;
	BatStatusType_e		BatStatus;	// 充电状态
}BatEvent_t;

extern void Mid_Bat_Init(void);
extern void Mid_Bat_ChargeStateRead(uint8 *dataTemp);
extern uint8 Mid_Bat_SocRead(uint8 *pu8Soc);
extern void Mid_Bat_BatCheck(void);
extern void Mid_Bat_ChargCheck(void);
extern uint16 Mid_Bat_SelfTest(void);
extern void Mid_Bat_Test(void);

#endif			//BAT_APP_H

