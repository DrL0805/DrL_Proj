/*
 * ģ��ӿں���
 * �ⲿ��ʹ�ô�ģ��ӿں���/�ⲿ����/�궨��ȣ���������ͷ�ļ����ɣ�
 * #include "xxx_interface.h"
*/

#include "store_interface.h"

/* ���������ʽ��ʼ�� */ 
void Store_Interface_ClearInit(void)
{
	/* APP�ϴ���س�ʼ�� */
	Store_PDU_Init();	

	Store_Step_ClearInit();
	Store_Sleep_ClearInit();
	Store_SlpRcd_ClearInit();
	Store_Hrd_ClearInit();	
	Store_Stress_ClearInit();
	Store_Bodytemp_ClearInit();
	Store_ABC_ClearInit();
	Store_Climb_ClearInit();
	Store_Swim_ClearInit();
	Store_Run_ClearInit();	
	
	
	#if 1 /* ģ������洢���� */ 
//	Store_Step_DateSimulata();
//	Store_Hrd_DateSimulata();
//	Store_Stress_DateSimulata();
//	Store_Bodytemp_DateSimulata();	
//	Store_ABC_DateSimulata();	
//	
//	Store_Run_DateSimulata();
//	Store_Climb_DateSimulata();
//	Store_Swim_DateSimulata();
	
//	Store_SlpRcd_DateSimulata();
//	Store_Sleep_DateSimulata();
//	Store_SleepRecord_DateSimulata();
	#endif
}

/* ���ݻָ���ʽ��ʼ�� */
void Store_Interface_RecoverInit(void)
{
	/* APP�ϴ���س�ʼ�� */
	Store_PDU_Init();	

	Store_Step_RecoverInit();
	Store_Sleep_RecoverInit();
	Store_SlpRcd_RecoverInit();
	Store_Hrd_RecoverInit();	
	Store_Stress_RecoverInit();
	Store_Bodytemp_RecoverInit();
	Store_ABC_RecoverInit();
	Store_Climb_RecoverInit();
	Store_Swim_RecoverInit();
	Store_Run_RecoverInit();

//	Store_Sleep_RecoverInit();	
//	Store_SleepRecord_RecoverInit();	
	
	#if 1 /* ģ������洢���� */ 
//	Store_Step_DateSimulata();
//	Store_Hrd_DateSimulata();
//	Store_Stress_DateSimulata();
//	Store_Bodytemp_DateSimulata();	
//	Store_ABC_DateSimulata();	
//	
//	Store_Run_DateSimulata();
//	Store_Climb_DateSimulata();
//	Store_Swim_DateSimulata();
	
//	Store_Sleep_DateSimulata();
//	Store_SleepRecord_DateSimulata();
	#endif
}


















