
#include "app_win_idle.h"

static eAppWinHandle App_Win_KeyMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message);


#define AppLockWinMenuNum (sizeof(AppLockWinMenu)/sizeof(AppLockWinMenu[0]))	
App_Win_Menu_T	AppLockWinMenu[] = 
{
	{eWinMenukey, App_Win_KeyMenuHandler},
};

//**********************************************************************
// �������ܣ�  ���ڲ˵�������
// ���������  WinHandle	��ǰ���ھ��
// 				message		�������
// ���ز�����  �ɹ������Ĵ��ھ��
static eAppWinHandle App_Win_KeyMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message)
{
	APP_WIN_RTT_LOG(0,"App_Win_KeyMenuHandler \r\n");
	
//	eAppWinHandle TmpWinHandle = WinHandle;
	
	switch(message.val)
	{
		case MID_KEY0_SHORT:
			/* ����״̬��5min�ڣ��̰��ָ�֮ǰ���ڡ�����5min�ص�ʱ�䴰�� */
			if(AppWinParam.LockWinCnt < APP_WIN_RECOVER_TIMEOUT)
			{
				AppWinParam.CurrWinHanle = AppWinParam.LastWinHanle;
				AppWinParam.WinRecoverFlg = true;
			}
			else
			{
				AppWinParam.CurrWinHanle = eTimeWinHandle;
			}
			break;
		case MID_KEY0_HOLDSHORT:
			break;
		case MID_KEY0_HOLDLONG:
			/* ����12�����ִ�ģʽ*/
			AppWinParam.CurrWinHanle = eStoreWinHandle;
			break;
		default: break;
	}
	
	return AppWinParam.CurrWinHanle;	
}

//**********************************************************************
// �������ܣ�  ���д��ڳ�ʼ��
// ���������  
// ���ز�����  �ɹ������Ĵ��ھ��
eAppWinHandle App_LockWin_Init(void)
{
	APP_WIN_RTT_LOG(0,"App_LockWin_Init \r\n");
	
	// ������������
	AppWinParam.CurrWinHanle = eLockWinHandle;
	AppWinParam.CurrSubWinHandle = eAppSubWinHandle0;
	
	return AppWinParam.CurrWinHanle;	
}

//**********************************************************************
// �������ܣ�  ���ڻص�����
// ���������  eAppWinHandle	��ǰ���ھ��
// 			   App_Win_Msg_T 	�������
// ���ز�����  �µĴ��ھ��
eAppWinHandle App_LockWin_Cb(eAppWinHandle WinHandle, App_Win_Msg_T message)
{
	APP_WIN_RTT_LOG(0,"App_LockWin_Cb \r\n");
	
	uint32_t TmpWinMenuIndex;
	
	#if 1
	if(eLockWinHandle != WinHandle)
		return eErrWinHandle;
	#endif
	
	// ��Ѱ���ڲ˵������ţ����ڽ�����ȷ�Ļص�����
	for(TmpWinMenuIndex = 0;TmpWinMenuIndex < AppLockWinMenuNum;TmpWinMenuIndex++)
	{
		if(AppLockWinMenu[TmpWinMenuIndex].MenuTag == message.MenuTag)
			break;
	}
	
	// �˵�������Ч��������Ӧ�Ĵ�����
	if((TmpWinMenuIndex < AppLockWinMenuNum) && (NULL != AppLockWinMenu[TmpWinMenuIndex].callback))
	{
		return AppLockWinMenu[TmpWinMenuIndex].callback(WinHandle, message);
	}

	return WinHandle;
}
