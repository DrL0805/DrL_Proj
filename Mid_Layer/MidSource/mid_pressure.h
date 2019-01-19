#ifndef MID_PRESSURE_H
#define MID_PRESSURE_H

#define 	AIRPRESSURE

#include "platform_common.h"
#include "drv_airpress.h"

#define MID_PRESS_RTT_DEBUG	2
#if (1 == MID_PRESS_RTT_DEBUG)	// ����ȼ�
#define MID_PRESS_RTT_LOG(...)
#define MID_PRESS_RTT_WARN(...)
#define MID_PRESS_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MID_PRESS_RTT_DEBUG)	// ����ȼ�
#define MID_PRESS_RTT_LOG(...)
#define MID_PRESS_RTT_WARN		RTT_DEBUG_WARN
#define MID_PRESS_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MID_PRESS_RTT_DEBUG)	// ���Եȼ�
#define MID_PRESS_RTT_LOG		RTT_DEBUG_LOG
#define MID_PRESS_RTT_WARN		RTT_DEBUG_WARN
#define MID_PRESS_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define MID_PRESS_RTT_LOG(...)
#define MID_PRESS_RTT_WARN(...)
#define MID_PRESS_RTT_ERR(...)
#endif

typedef enum
{
	eMidPressSampleTemp,		// �ɼ��¶�
	eMidPressSamplePress,		// �ɼ���ѹ
	eMidPressSampleTempPress,	// �¶���ѹ�����ɼ�
	eMidPressSampleMax,
}eMidPressSampleType;

typedef struct
{
	uint8_t						InitedFlg;			// �ѳ�ʼ����־
	uint8_t						TempUpdateFlg;		// �¶Ȳɼ��ɹ���־
	uint8_t						PressUpdateFlg;		// ��ѹ�ɼ��ɹ���־
	uint8_t						ContinuousCvtFlg;	// ����������־
	
	AirpressOSR_e 				Osr;		// ��������
	AirpressMR_e				Mr;			// ��������ʱÿ���������
	eMidPressSampleType			SampleType;	// ��������

	int16						LastTemp;	// ���������¶�ֵ
	int32						LastPress;
}MID_PRESS_PARA_T;

extern void Mid_Press_ParamSet(AirpressOSR_e Osr, eMidPressSampleType SampleType);
extern void Mid_Press_PressStart(void);
extern void Mid_Press_TempUpdate(void);
extern void Mid_Press_PressUpdate(void);
extern MID_PRESS_PARA_T* Mid_Press_ParamPGet(void);

extern uint16_t Mid_Press_Init(void);
extern uint16 Mid_Press_SelfTest(void);
extern void Mid_Press_ContinuousCvtCheck(void);
extern void Mid_Press_Test(void);

typedef enum 
{
	ePressEventStartSample,
	ePressEventDataUpdate,
}PressEventId_e;

typedef struct
{
	PressEventId_e	Id;
	uint8_t 		Param;
}PressEvent_t;

#endif

