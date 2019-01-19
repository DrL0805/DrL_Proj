#ifndef         APP_SYSTERM_H
#define         APP_SYSTERM_H


typedef enum
{
	eAppSysStatePwrRst,		// �ϵ縴λ����
	eAppSysStateOTARst,		// OTA��λ����
	eAppSysStateWDTRst,		// ���Ź���λ����
	eAppSysStateStore,		// �ִ�ģʽ
	eAppSysStateNormal,		// ����ģʽ
	eAppSysStatePwrSaving,	// ʡ��ģʽ
	eAppSysStateWatch,		// ��ͳ��ģʽ
	eAppSysStateMax,
}AppSysStateType_e;


typedef struct
{
	AppSysStateType_e	SysState;
}AppSysParam_t;

extern void App_Sys_Init(void);
extern void App_Sys_StartingUp(void);
extern void App_Sys_Shutdown(void);
extern void App_Sys_StateSet(AppSysStateType_e feAppSysStateType);
extern AppSysStateType_e App_Sys_StateGet(void);
extern void App_Sys_InfoBackup(AppSysStateType_e feAppSysStateType);
extern void App_Sys_InfoRecover(void);

#endif










