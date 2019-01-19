#ifndef	__APP_LCD_H
#define __APP_LCD_H

#include "platform_common.h"
#include "mid_Lcd.h"
//#include "app_win_common.h"
//yangrui add
#include "ui_display_main.h"
#include "ui_timerhandle_main.h"

#define APP_LCD_RTT_DEBUG	3
#if (1 == APP_LCD_RTT_DEBUG)	// ����ȼ�
#define APP_LCD_RTT_LOG(...)
#define APP_LCD_RTT_WARN(...)
#define APP_LCD_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == APP_LCD_RTT_DEBUG)	// ����ȼ�
#define APP_LCD_RTT_LOG(...)
#define APP_LCD_RTT_WARN	RTT_DEBUG_WARN
#define APP_LCD_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == APP_LCD_RTT_DEBUG)	// ���Եȼ�
#define APP_LCD_RTT_LOG		RTT_DEBUG_LOG
#define APP_LCD_RTT_WARN	RTT_DEBUG_WARN
#define APP_LCD_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define APP_LCD_RTT_LOG(...)
#define APP_LCD_RTT_WARN(...)
#define APP_LCD_RTT_ERR(...)
#endif

// LCD�¼�����
typedef enum
{
	eAppLcdEventOuter,	// �ⲿ�¼����簴���¼�
	eAppLcdEventInside,	// �ڲ��¼����綨ʱ��ѯ�¼�
	eAppLcdEventCmd	// �ڲ��¼����綨ʱ��ѯ�¼�
	/* �����¼����ж��� */
}eAppLcdEvent;

typedef struct
{
	/* ��Ϣ�����Զ��� */
	uint8_t Id;
}App_lcd_Msg_t;

/* �м������������ݽṹ�� */
typedef struct
{
	bool	 			RefreshFlg;		// ǿ��ˢ�±�־
	eAppLcdEvent 		Id;				// lcd�������¼�����
	union
	{
//		App_Win_Msg_T		Outer;			// �ⲿ�¼���Ϣ����
		App_lcd_Msg_t		Inside;			// �ڲ��¼���Ϣ����
	}Param;
}App_Lcd_TaskMsg_T;

typedef enum
{
	eLcdBacklightOff,
	eLcdBacklightOn,
	eLcdBacklightWait,
}eLcdBacklightType;

typedef struct 
{
	eLcdBacklightType	BacklightType;
	uint32_t 			BacklightCnt;
}App_Lcd_Param_t;

void App_Lcd_ScreenRefresh(uint8_t ScreenMainId);
void App_Lcd_TimerStart(uint32_t TimerMs);
void App_Lcd_TimerStop(void);
void App_Lcd_TaskEventSet(App_Lcd_TaskMsg_T* Msg, uint8_t FromISR);
void App_Lcd_TaskCreate(void);


void App_Lcd_HardTimerStart(uint32_t TimerMs);
void App_Lcd_HardTimerStop(void);

void App_Lcd_Show(void);
#endif



