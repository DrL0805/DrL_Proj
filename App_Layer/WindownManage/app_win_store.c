
#include "app_win_store.h"

static eAppWinHandle App_Win_KeyMenuHandler(eAppWinHandle WinHandle,App_Win_Msg_T message);

#define AppStoreWinMenuNum (sizeof(AppStoreWinMenu)/sizeof(AppStoreWinMenu[0]))		// ������Ч�˵�����
App_Win_Menu_T	AppStoreWinMenu[] = 
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
	
	switch(message.val)
	{
		case MID_KEY0_SHORT:
			/* �ִ�ģʽ�¶̰���ʾ������Ϣ */
			break;
		case MID_KEY0_HOLDSHORT:
			/* �ִ�ģʽ�³���3����뿪��ģʽ */
			AppWinParam.CurrWinHanle = ePwronWinHandle;
			break;
		case MID_KEY0_HOLDLONG:
			break;
		default: break;
	}
	
	return AppWinParam.CurrWinHanle;
}

//**********************************************************************
// �������ܣ�  ���ڳ�ʼ��
// ���������  
// ���ز�����  �ɹ������Ĵ��ھ��
eAppWinHandle App_StoreWin_Init(void)
{
	APP_WIN_RTT_LOG(0,"App_StoreWin_Init \r\n");
	
	AppWinParam.CurrWinHanle = eStoreWinHandle;
	AppWinParam.CurrSubWinHandle = eAppSubWinHandle0;
	
	return AppWinParam.CurrWinHanle;
}

//**********************************************************************
// �������ܣ�  ���ڻص�����
// ���������  WinHandle	��ǰ���ھ��
// 			   message 		�������
// ���ز�����  �µĴ��ھ��
eAppWinHandle App_StoreWin_Cb(eAppWinHandle WinHandle, App_Win_Msg_T message)
{
	APP_WIN_RTT_LOG(0,"App_StoreWin_Cb \r\n");
	
	uint32_t TmpWinMenuIndex;
	
	#if 1
	if(eStoreWinHandle != WinHandle)
		return eErrWinHandle;
	#endif
	
	// ��Ѱ���ڲ˵������ţ����ڽ�����ȷ�Ļص�����
	for(TmpWinMenuIndex = 0;TmpWinMenuIndex < AppStoreWinMenuNum;TmpWinMenuIndex++)
	{
		if(AppStoreWinMenu[TmpWinMenuIndex].MenuTag == message.MenuTag)
			break;
	}
	
	// �˵�������Ч��������Ӧ�Ĵ�����
	if((TmpWinMenuIndex < AppStoreWinMenuNum) && (NULL != AppStoreWinMenu[TmpWinMenuIndex].callback))
	{
		return AppStoreWinMenu[TmpWinMenuIndex].callback(WinHandle, message);
	}

	return WinHandle;
}




