#ifndef         APP_SYSTERM_H
#define         APP_SYSTERM_H


typedef enum
{
	eAppSysStatePwrRst,		// 上电复位过程
	eAppSysStateOTARst,		// OTA复位过程
	eAppSysStateWDTRst,		// 开门狗复位过程
	eAppSysStateStore,		// 仓储模式
	eAppSysStateNormal,		// 正常模式
	eAppSysStatePwrSaving,	// 省电模式
	eAppSysStateWatch,		// 传统表模式
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










