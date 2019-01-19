#ifndef STORE_STEP_H
#define STORE_STEP_H

#include "store_variable.h"
#include "app_variable.h"

#define STORE_STEP_RTT_DEBUG	2
#if (1 == STORE_STEP_RTT_DEBUG)	// ����ȼ�
#define STORE_STEP_RTT_LOG(...)
#define STORE_STEP_RTT_WARN(...)
#define STORE_STEP_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_STEP_RTT_DEBUG)	// ����ȼ�
#define STORE_STEP_RTT_LOG(...)
#define STORE_STEP_RTT_WARN		RTT_DEBUG_WARN
#define STORE_STEP_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_STEP_RTT_DEBUG)	// ���Եȼ�
#define STORE_STEP_RTT_LOG		RTT_DEBUG_LOG
#define STORE_STEP_RTT_WARN		RTT_DEBUG_WARN
#define STORE_STEP_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define STORE_STEP_RTT_LOG(...)
#define STORE_STEP_RTT_WARN(...)
#define STORE_STEP_RTT_ERR(...)
#endif

typedef struct
{
	uint16_t LogBuf[24];	// buf[0~23]���ֱ��Ӧһ���0~23��
}StoreStepUI_t;

typedef struct
{
	bool			InitFlg;
	
	uint32_t 		LogCnt;						
	uint8_t			LogBuf[STORE2_STEP_LOG_MAX * STORE2_STEP_DATA_CLASSIFY_LEN];
	
	uint32_t    	CumsumStep;						// �����ۼӼƲ�ֵ
	StoreStepUI_t	UI;								// ��������UI��ʾ�����ݣ��Ʋ�UI�Ƚ����⣬ÿ��Ʋ���Ϣ����ա�
}StoreStepParam_t;

extern void Store_Step_ClearInit(void);
extern void Store_Step_RecoverInit(void);
extern StoreInfo_t* Store_Step_StoreInfoGet(void);
extern StoreStepParam_t* Store_Step_ParamPGet(void);
extern void Store_Step_algorithm(void);
extern uint16_t Store_Step_CatalogCreate(void);
extern uint16_t Store_Step_DataSave(void);
extern uint16_t Store_Step_CatalogSeal(void);
extern uint16_t Store_Step_DataRead(void);
extern uint16_t Store_Step_CatalogAllUpload(void);
extern void Store_Step_RamDataClear(void);
extern void Store_Step_DateSimulata(void);

void Store_Step_UIDataGet(uint16_t* Buf, uint32_t Len);
void Store_Step_UIDataUpdate(void);


#endif








