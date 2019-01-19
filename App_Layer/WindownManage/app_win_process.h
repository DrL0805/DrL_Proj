#ifndef APP_WIN_PROCESS_H
#define APP_WIN_PROCESS_H

#include "app_win_common.h"


#define APP_WIN_LOCK_TIMEOUT	(10)
#define APP_WIN_RECOVER_TIMEOUT	(300)	// 5min


typedef 	eAppWinHandle WinInitFunc(void);
typedef 	eAppWinHandle CallBackFunc(eAppWinHandle sysHandle, App_Win_Msg_T message);

typedef struct
{
	uint16 			HandleIndex;
	WinInitFunc 		*WinInit;
	CallBackFunc 		*CallBack;
}APP_WIN_T;

typedef struct
{
	bool				WinRecoverFlg;		// ���ڻָ���־
	
	eAppWinHandle		CurrWinHanle;		// ��ǰһ�����
	eAppSubWinHandle	CurrSubWinHandle;	// ��ǰ�������
	eAppWinHandle		LastWinHanle;		// �ϴ�һ���������������״̬�Ĵ��ڻָ�
	eAppSubWinHandle	LastSubWinHandle;	// �ϴζ������
	
	uint32_t 			LockWinCnt;			// ���д��ڼ�ʱ����������״̬
}App_Win_Param_T;

extern eAppWinHandle App_Window_Process(App_Win_Msg_T message);
extern eAppWinHandle App_Window_Init(eAppWinHandle eAppWinNew);
extern void App_Window_LockWinCnt(void);


void App_Win_TaskEventSet(App_Win_Msg_T* msg);
void App_Win_TaskCreate(void);

/* ȫ�ֱ������� */
extern App_Win_Param_T	AppWinParam;

#endif

