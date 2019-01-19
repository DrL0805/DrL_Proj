#ifndef STORE_PART_H
#define STORE_PART_H

#include "store_variable.h"

#define STORE_PART_RTT_DEBUG	2
#if (1 == STORE_PART_RTT_DEBUG)	// ����ȼ�
#define STORE_PART_RTT_LOG(...)
#define STORE_PART_RTT_WARN(...)
#define STORE_PART_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_PART_RTT_DEBUG)	// ����ȼ�
#define STORE_PART_RTT_LOG(...)
#define STORE_PART_RTT_WARN		RTT_DEBUG_WARN
#define STORE_PART_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_PART_RTT_DEBUG)	// ���Եȼ�
#define STORE_PART_RTT_LOG		RTT_DEBUG_LOG
#define STORE_PART_RTT_WARN		RTT_DEBUG_WARN
#define STORE_PART_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define STORE_PART_RTT_LOG(...)
#define STORE_PART_RTT_WARN(...)
#define STORE_PART_RTT_ERR(...)
#endif

/*
	store_partʹ����������ⲿʹ��partģ��洢����ʱ�����ڴ�˵������ֹ���á�
	
	256B����320part��
	���	������		��;
	0~9		DrL			ϵͳ��Ϣ
	 :0		DrL			ϵͳ���ÿ��أ������ѿ��ء��������ء�ϵͳ���Ե�
	 :1		DrL			ʱ����Ϣ��ϵͳʱ�䡢����ʱ�䡢����ʱ�䡢����ʱ�䡢���д��ŵ�
	 :2	    DrL			������Ϣ
	 :3		DrL			������Ϣ��������������
	 :4-9	DrL			����
	10		ZSL			�����㲥��Ϣ
	
	512B����80part��
	���	ʹ����		��;
	
	1KB����40part��
	���	ʹ����		��;
	
	2KB����20part��
	���	ʹ����		��;
	0-4 	ZSL			��������룬���5��
	5		DrL			ϵͳ��λ��Ϣ��WDT/OTA��λǰ��Ҫ�������Ϣ��
*/


typedef enum
{
	eStorePart256B,
	eStorePart512B,
	eStorePart1KB,
	eStorePart2KB
}StorePartType_e;

typedef struct
{
	bool	InitFlg;
}StorePartParam_t;

extern void Store_Part_Init(void);
extern void Store_Part_Write(StorePartType_e PartType, uint32_t Part, uint8_t* DataBuf, uint32_t DataLen);
extern void Store_Part_Read(StorePartType_e PartType, uint32_t Part, uint8_t* DataBuf, uint32_t DataLen);
extern void Store_Part_Test(void);



#endif



