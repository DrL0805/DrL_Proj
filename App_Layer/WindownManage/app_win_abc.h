#ifndef APP_WIN_ABC_H
#define APP_WIN_ABC_H

#include "app_win_common.h"
#include "app_win_process.h"

// ���ڲ�������
typedef struct
{
	uint8_t Id;
}App_ABCWin_Param_T;

eAppWinHandle App_ABCWin_Init(void);
eAppWinHandle App_ABCWin_Cb(eAppWinHandle WinHandle, App_Win_Msg_T message);

#endif

