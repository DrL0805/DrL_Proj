#ifndef APP_WIN_SLEEP_H
#define APP_WIN_SLEEP_H

#include "app_win_common.h"
#include "app_win_process.h"

// ˯�ߴ��ڲ�������
typedef struct
{
	uint8_t Id;
}App_SleepWin_Param_T;

eAppWinHandle App_SleepWin_Init(void);
eAppWinHandle App_SleepWin_Cb(eAppWinHandle WinHandle, App_Win_Msg_T message);


#endif

