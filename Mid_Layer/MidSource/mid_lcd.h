#ifndef	_MID_LCD_H
#define	_MID_LCD_H

#include "platform_common.h"
#include "drv_rgb_lcd.h"

#define MID_LCD_RTT_DEBUG		3
#if (1 == MID_LCD_RTT_DEBUG)	// 错误等级
#define MID_LCD_RTT_LOG(...)
#define MID_LCD_RTT_WARN(...)
#define MID_LCD_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MID_LCD_RTT_DEBUG)	// 警告等级
#define MID_LCD_RTT_LOG(...)
#define MID_LCD_RTT_WARN		RTT_DEBUG_WARN
#define MID_LCD_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MID_LCD_RTT_DEBUG)	// 调试等级
#define MID_LCD_RTT_LOG		RTT_DEBUG_LOG
#define MID_LCD_RTT_WARN		RTT_DEBUG_WARN
#define MID_LCD_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define MID_LCD_RTT_LOG(...)
#define MID_LCD_RTT_WARN(...)
#define MID_LCD_RTT_ERR(...)
#endif

typedef enum	// lcd背光等级
{
	eLcdBLGrade_0 = 0,
	eLcdBLGrade_1 = 10,
	eLcdBLGrade_2 = 20,
	eLcdBLGrade_3 = 30,
	eLcdBLGrade_4 = 40,
	eLcdBLGrade_5 = 50,
}eLcdBLGrade;	


typedef struct 
{
	bool		InitFlg;	
	bool		BLRunFlg;		// LCD背光运行标志，用于控制是否开启PWM定时器
	
	eLcdBLGrade	BLGrade;
}MidLcdParam_t;


extern void Mid_Lcd_ExtcominTog(void);
extern void Mid_Lcd_Init(void);
extern void Mid_Lcd_BLDutySet(uint8_t Duty);
extern void Mid_Lcd_Show(void);
extern void Mid_Lcd_Sleep(void);
extern void Mid_LCD_Test(void);

#endif
