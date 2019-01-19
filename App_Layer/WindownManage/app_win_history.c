
#include "app_win_history.h"


static eAppWinHandle App_Win_KeyMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message);
static eAppWinHandle App_Win_SlideMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message);
static eAppWinHandle App_Win_ClickMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message);
static eAppWinHandle App_Win_LockMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message);


#define AppHistoryWinMenuNum (sizeof(AppHistoryWinMenu)/sizeof(AppHistoryWinMenu[0]))	
App_Win_Menu_T	AppHistoryWinMenu[] = 
{
	{eWinMenukey, App_Win_KeyMenuHandler},
	{eWinMenuSlide, App_Win_SlideMenuHandler},
	{eWinMenuClick, App_Win_ClickMenuHandler},
	{eWinMenuLock, App_Win_LockMenuHandler},
};

//**********************************************************************
// �������ܣ�  ���ڲ˵�������
// ���������  WinHandle	��ǰ���ھ��
// 				message		�������
// ���ز�����  �ɹ������Ĵ��ھ��
static eAppWinHandle App_Win_KeyMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message)
{
	APP_WIN_RTT_LOG(0,"App_Win_KeyMenuHandler \r\n");

	switch(message.val)
	{
		case MID_KEY0_SHORT:
			/* ��ʱ��ģʽ�¶̰�����ʱ��ģʽ */
			AppWinParam.CurrWinHanle = eTimeWinHandle;
			break;
		case MID_KEY0_HOLDSHORT:
			break;
		case MID_KEY0_HOLDLONG:
			/* ʱ��ģʽ�³���12�����ִ�ģʽ*/
			AppWinParam.CurrWinHanle = eStoreWinHandle;
			break;
		default: break;
	}
	
	return AppWinParam.CurrWinHanle;	
}

//**********************************************************************
// �������ܣ�  ���ڲ˵�������
// ���������  WinHandle	��ǰ���ھ��
// 				message		�������
// ���ز�����  �ɹ������Ĵ��ھ��
static eAppWinHandle App_Win_SlideMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message)
{
	APP_WIN_RTT_LOG(0,"App_Win_SlideMenuHandler \r\n");

	switch(message.val)
	{
		case 0:		// �ϻ�
			AppWinParam.CurrWinHanle = eTimeWinHandle;
			break;
		case 1:		// �»�
			AppWinParam.CurrWinHanle = eABCWinHandle;
			break;
		case 2:		// ��
			break;
		case 3:		// �һ�
			break;
		default: break;
	}
	
	return AppWinParam.CurrWinHanle;
}

//**********************************************************************
// �������ܣ�  ���ڲ˵�������
// ���������  WinHandle	��ǰ���ھ��
// 				message		�������
// ���ز�����  �ɹ������Ĵ��ھ��
static eAppWinHandle App_Win_ClickMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message)
{
	APP_WIN_RTT_LOG(0,"App_Win_ClickMenuHandler \r\n");
	
	return AppWinParam.CurrWinHanle;	
}

//**********************************************************************
// �������ܣ�  ���ڲ˵�������
// ���������  WinHandle	��ǰ���ھ��
// 				message		�������
// ���ز�����  �ɹ������Ĵ��ھ��
static eAppWinHandle App_Win_LockMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message)
{
	APP_WIN_RTT_LOG(0,"App_Win_LockMenuHandler \r\n");

	// ��������ǰ����֮ǰ��������
	AppWinParam.LastWinHanle = AppWinParam.CurrWinHanle;
	AppWinParam.LastSubWinHandle = AppWinParam.CurrSubWinHandle;	
	
	// ������������
	AppWinParam.CurrWinHanle = eLockWinHandle;
	AppWinParam.LockWinCnt = 0;
	
	return AppWinParam.CurrWinHanle;	
}

//**********************************************************************
// �������ܣ�  ���ڳ�ʼ��
// ���������  
// ���ز�����  �ɹ������Ĵ��ھ��
eAppWinHandle App_HistoryWin_Init(void)
{
	APP_WIN_RTT_LOG(0,"App_HistoryWin_Init \r\n");
	
	if(AppWinParam.WinRecoverFlg)
	{
		AppWinParam.WinRecoverFlg = false;
		AppWinParam.CurrWinHanle = eHistoryWinHandle;
		AppWinParam.CurrSubWinHandle = AppWinParam.LastSubWinHandle;
	}
	else
	{
		AppWinParam.CurrWinHanle = eHistoryWinHandle;
		AppWinParam.CurrSubWinHandle = eAppSubWinHandle0;
	}
	
	return AppWinParam.CurrWinHanle;
}

//**********************************************************************
// �������ܣ�  ���ڻص�����
// ���������  WinHandle	��ǰ���ھ��
// 			   message 		�������
// ���ز�����  �µĴ��ھ��
eAppWinHandle App_HistoryWin_Cb(eAppWinHandle WinHandle, App_Win_Msg_T message)
{
	APP_WIN_RTT_LOG(0,"App_HistoryWin_Cb \r\n");
	
	#if 1
	if(eHistoryWinHandle != WinHandle)
		return eErrWinHandle;
	#endif

	// ��Ѱ���ڲ˵������ţ����ڽ�����ȷ�Ļص�����
	uint32_t TmpWinMenuIndex;
	for(TmpWinMenuIndex = 0;TmpWinMenuIndex < AppHistoryWinMenuNum;TmpWinMenuIndex++)
	{
		if(AppHistoryWinMenu[TmpWinMenuIndex].MenuTag == message.MenuTag)
			break;
	}
	
	// �˵�������Ч��������Ӧ�Ĵ�����
	if((TmpWinMenuIndex < AppHistoryWinMenuNum) && (NULL != AppHistoryWinMenu[TmpWinMenuIndex].callback))
	{
		return AppHistoryWinMenu[TmpWinMenuIndex].callback(WinHandle, message);
	}

	return WinHandle;
}










