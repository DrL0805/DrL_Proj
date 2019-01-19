
#include "app_win_pwron.h"

static eAppWinHandle App_Win_PwrOnMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message);

#define AppPwronWinMenuNum (sizeof(AppPwronWinMenu)/sizeof(AppPwronWinMenu[0]))	
App_Win_Menu_T	AppPwronWinMenu[] = 
{
	{eWinMenuPwrOn, App_Win_PwrOnMenuHandler},
};

//**********************************************************************
// �������ܣ�  ���ڲ˵�������
// ���������  WinHandle	��ǰ���ھ��
// 				message		�������
// ���ز�����  �ɹ������Ĵ��ھ��
static eAppWinHandle App_Win_PwrOnMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message)
{
	APP_WIN_RTT_LOG(0,"App_Win_PwrOnMenuHandler \r\n");

	/* ����������ɣ�����ʱ��ģʽ */
	AppWinParam.CurrWinHanle = eTimeWinHandle;
	
	return AppWinParam.CurrWinHanle;
}

//**********************************************************************
// �������ܣ�  ���ڳ�ʼ��
// ���������  
// ���ز�����  �ɹ������Ĵ��ھ��
eAppWinHandle App_PwronWin_Init(void)
{
	APP_WIN_RTT_LOG(0,"App_PwronWin_Init \r\n");
	
	AppWinParam.CurrWinHanle = ePwronWinHandle;
	AppWinParam.CurrSubWinHandle = eAppSubWinHandle0;
	
	// ϵͳ���ܿ���
	Mod_Sys_PwrOn();
	
	// ģ�ⷢ�Ϳ�����������¼���ֱ�ӽ�����һ����
//	App_Win_Msg_T WinMsg;
//	WinMsg.MenuTag = eWinMenuPwrOn;
//	WinMsg.val = 0;
//	App_Win_TaskEventSet(&WinMsg);
	
	return AppWinParam.CurrWinHanle;
}

//**********************************************************************
// �������ܣ�  ���ڻص�����
// ���������  WinHandle	��ǰ���ھ��
// 			   message 		�������
// ���ز�����  �µĴ��ھ��
eAppWinHandle App_PwronWin_Cb(eAppWinHandle WinHandle, App_Win_Msg_T message)
{
	APP_WIN_RTT_LOG(0,"App_PwronWin_Cb \r\n");
	
	#if 1
	if(ePwronWinHandle != WinHandle)
		return eErrWinHandle;
	#endif
	
	// ��Ѱ���ڲ˵������ţ����ڽ�����ȷ�Ļص�����
	uint32_t TmpWinMenuIndex;
	for(TmpWinMenuIndex = 0;TmpWinMenuIndex < AppPwronWinMenuNum;TmpWinMenuIndex++)
	{
		if(AppPwronWinMenu[TmpWinMenuIndex].MenuTag == message.MenuTag)
			break;
	}	
	
	// �˵�������Ч��������Ӧ�Ĵ�����������������
	if((TmpWinMenuIndex < AppPwronWinMenuNum) && (NULL != AppPwronWinMenu[TmpWinMenuIndex].callback))
	{
		return AppPwronWinMenu[TmpWinMenuIndex].callback(WinHandle, message);
	}

	return WinHandle;
}




