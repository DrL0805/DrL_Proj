#ifndef MID_HRM_H
#define MID_HRM_H

#include "platform_common.h"
#include "drv_hrm.h"

#define MID_HRM_RTT_DEBUG	2
#if (1 == MID_HRM_RTT_DEBUG)	// ����ȼ�
#define MID_HRM_RTT_LOG(...)
#define MID_HRM_RTT_WARN(...)
#define MID_HRM_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MID_HRM_RTT_DEBUG)	// ����ȼ�
#define MID_HRM_RTT_LOG(...)
#define MID_HRM_RTT_WARN	RTT_DEBUG_WARN
#define MID_HRM_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MID_HRM_RTT_DEBUG)	// ���Եȼ�
#define MID_HRM_RTT_LOG		RTT_DEBUG_LOG
#define MID_HRM_RTT_WARN	RTT_DEBUG_WARN
#define MID_HRM_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define MID_HRM_RTT_LOG(...)
#define MID_HRM_RTT_WARN(...)
#define MID_HRM_RTT_ERR(...)
#endif

#define HRM_INVALID_VALUE	0		// ��Ч����ֵ
#define HRM_UNWEAR_TIMEOUT	3		// δ�����ⳬʱʱ��

typedef enum
{
	eMidHrmEventCalculate,
	eMidHrmEventHrmComplete,		// ���ʼ������
	eMidHrmEventHrvComplete,		// ѹ���������
	eMidHrmEventHrdErr,				// ���ʼ������
	eMidHrmEventHrvErr,				// ѹ���������
	eMidHrmEventUnwear,				// δ���
	eMidHrmEventTimeout,			// �㷨��ʱ
}eMidHrmEventType;

// ���ʵ�ǰ״̬
typedef enum
{
	eMidHrmStateIdle,		// ����
	eMidHrmStateMeasuring,	// ������
//	eMidHrmStateUnwear,		// δ���
//	eMidHrmStateDone,		// �������
}eMidHrmStateType;

typedef struct
{
	bool				InitFlg;
	bool				HrUpdateFlg;		// ���ʲ���ֵ���±�־��ÿ�ο�ʼ����ʱ��λ
	eMidHrmStateType	State;				// ���ʼ�״̬
	eHrmMeasuretype		MeasureType;		// �������ͣ����ʡ�ѹ��
	
	uint8_t		UnwearCnt;			// δ���������
	uint8_t		TimeoutCnt;			// �㷨��ʱ����

	uint8_t		CurrHeartRate;		// ��ǰ���µ�����ֵ��0xFF��ʾ��Ч
	uint8_t		LastHeartRate;		// �ϴ���Ч������ֵ
}Mid_Hrm_Param_t;

extern void Mid_Hrm_AccelMenSet(int16 *fifodata);
extern void Mid_Hrm_Start(eHrmMeasuretype Type);
extern void Mid_Hrm_Stop(void);
extern void Mid_Hrm_Calculate(void);
extern void Mid_Hrm_UnwearCheck(void);
extern void Mid_Hrm_TimeoutCheck(void);
extern void Mid_Hrm_Init(void);
extern void Mid_Hrm_TouchStatusRead(uint8 *ui8istouch);
extern Mid_Hrm_Param_t* Mid_Hrm_ParamPGet(void);
extern uint16 Mid_Hrm_FactoryTestRead(uint16 ui16lightleak[3]);
extern uint8 Mid_Hrm_FactoryTest(void);
extern void Mid_Hrm_Test(void);

#endif





