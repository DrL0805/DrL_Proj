#ifndef	__APP_LCD_H
#define __APP_LCD_H

#include "platform_common.h"
#include "mid_Lcd.h"
//#include "app_win_common.h"
//yangrui add
#include "ui_display_main.h"
#include "ui_timerhandle_main.h"

#define APP_LCD_RTT_DEBUG	3
#if (1 == APP_LCD_RTT_DEBUG)	// 错误等级
#define APP_LCD_RTT_LOG(...)
#define APP_LCD_RTT_WARN(...)
#define APP_LCD_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == APP_LCD_RTT_DEBUG)	// 警告等级
#define APP_LCD_RTT_LOG(...)
#define APP_LCD_RTT_WARN	RTT_DEBUG_WARN
#define APP_LCD_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == APP_LCD_RTT_DEBUG)	// 调试等级
#define APP_LCD_RTT_LOG		RTT_DEBUG_LOG
#define APP_LCD_RTT_WARN	RTT_DEBUG_WARN
#define APP_LCD_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define APP_LCD_RTT_LOG(...)
#define APP_LCD_RTT_WARN(...)
#define APP_LCD_RTT_ERR(...)
#endif

// LCD事件类型
typedef enum
{
	eAppLcdEventOuter,	// 外部事件，如按键事件
	eAppLcdEventInside,	// 内部事件，如定时轮询事件
	eAppLcdEventCmd	// 内部事件，如定时轮询事件
	/* 其他事件自行定义 */
}eAppLcdEvent;

typedef struct
{
	/* 消息内容自定义 */
	uint8_t Id;
}App_lcd_Msg_t;

/* 中间层任务调度数据结构体 */
typedef struct
{
	bool	 			RefreshFlg;		// 强制刷新标志
	eAppLcdEvent 		Id;				// lcd触发的事件类型
	union
	{
//		App_Win_Msg_T		Outer;			// 外部事件消息内容
		App_lcd_Msg_t		Inside;			// 内部事件消息内容
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



