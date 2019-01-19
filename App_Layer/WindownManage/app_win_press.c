
#include "app_win_press.h"

static eAppWinHandle App_Win_KeyMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message);
static eAppWinHandle App_Win_SlideMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message);
static eAppWinHandle App_Win_ClickMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message);
static eAppWinHandle App_Win_LockMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message);

#define AppPressWinMenuNum (sizeof(AppPressWinMenu)/sizeof(AppPressWinMenu[0]))	
App_Win_Menu_T	AppPressWinMenu[] = 
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
			switch (AppWinParam.CurrSubWinHandle)
            {
            	case eAppSubWinHandle0:
            	case eAppSubWinHandle1:
				case eAppSubWinHandle2:
            		AppWinParam.CurrWinHanle = eTimeWinHandle;
					break;
            	default:
            		break;
            }
			break;
		case MID_KEY0_HOLDSHORT:
			switch (AppWinParam.CurrSubWinHandle)
            {
            	case eAppSubWinHandle0:
            	case eAppSubWinHandle1:
				case eAppSubWinHandle2:	
            		break;
            	default:
            		break;
            }			
			break;
		case MID_KEY0_HOLDLONG:
			/* ����״̬�³���12�����ִ�ģʽ*/
			switch (AppWinParam.CurrSubWinHandle)
            {
            	case eAppSubWinHandle0:
            	case eAppSubWinHandle1:
				case eAppSubWinHandle2:
            		AppWinParam.CurrWinHanle = eStoreWinHandle;
					break;
            	default:
            		break;
            }			
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
			switch (AppWinParam.CurrSubWinHandle)
            {
            	case eAppSubWinHandle0:
					AppWinParam.CurrWinHanle = eBodyTempWinHandle;
					break;
            	case eAppSubWinHandle1:
					AppWinParam.CurrSubWinHandle = eAppSubWinHandle2;
					break;
				case eAppSubWinHandle2:
            		AppWinParam.CurrSubWinHandle = eAppSubWinHandle1;
					break;
            	default:
            		break;
            }			
			break;
		case 1:		// �»�
			switch (AppWinParam.CurrSubWinHandle)
            {
            	case eAppSubWinHandle0:
					AppWinParam.CurrWinHanle = eHeartWinHandle;
					break;
            	case eAppSubWinHandle1:
					AppWinParam.CurrSubWinHandle = eAppSubWinHandle2;
					break;
				case eAppSubWinHandle2:
            		AppWinParam.CurrSubWinHandle = eAppSubWinHandle1;
					break;
            	default:
            		break;
            }
			break;
		case 2:		// ��
			break;
		case 3:		// �һ�
			switch (AppWinParam.CurrSubWinHandle)
            {
            	case eAppSubWinHandle0: 
					break;
            	case eAppSubWinHandle1:
				case eAppSubWinHandle2:
					AppWinParam.CurrSubWinHandle = eAppSubWinHandle0;
					break;
            	default: break;
            }			
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

	switch (AppWinParam.CurrSubWinHandle)
	{
		case eAppSubWinHandle0: 
			AppWinParam.CurrSubWinHandle = eAppSubWinHandle1;
			break;
		case eAppSubWinHandle1:
		case eAppSubWinHandle2:
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
eAppWinHandle App_PressWin_Init(void)
{
	APP_WIN_RTT_LOG(0,"App_PressWin_Init \r\n");
	
	if(AppWinParam.WinRecoverFlg)
	{
		AppWinParam.WinRecoverFlg = false;
		AppWinParam.CurrWinHanle = ePressWinHandle;
		AppWinParam.CurrSubWinHandle = AppWinParam.LastSubWinHandle;
	}
	else
	{
		AppWinParam.CurrWinHanle = ePressWinHandle;
		AppWinParam.CurrSubWinHandle = eAppSubWinHandle0;
	}
	
	return AppWinParam.CurrWinHanle;
}

//**********************************************************************
// �������ܣ�  ���ڻص�����
// ���������  WinHandle	��ǰ���ھ��
// 			   message 		�������
// ���ز�����  �µĴ��ھ��
eAppWinHandle App_PressWin_Cb(eAppWinHandle WinHandle, App_Win_Msg_T message)
{
	APP_WIN_RTT_LOG(0,"App_PressWin_Cb \r\n");
	
	#if 1
	if(ePressWinHandle != WinHandle)
		return eErrWinHandle;
	#endif

	// ��Ѱ���ڲ˵������ţ����ڽ�����ȷ�Ļص�����
	uint32_t TmpWinMenuIndex;
	for(TmpWinMenuIndex = 0;TmpWinMenuIndex < AppPressWinMenuNum;TmpWinMenuIndex++)
	{
		if(AppPressWinMenu[TmpWinMenuIndex].MenuTag == message.MenuTag)
			break;
	}	
	
	// �˵�������Ч��������Ӧ�Ĵ�����
	if((TmpWinMenuIndex < AppPressWinMenuNum) && (NULL != AppPressWinMenu[TmpWinMenuIndex].callback))
	{
		return AppPressWinMenu[TmpWinMenuIndex].callback(WinHandle, message);
	}

	return WinHandle;
}












