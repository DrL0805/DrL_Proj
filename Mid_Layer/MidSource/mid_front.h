#ifndef MID_FRONT_H
#define MID_FRONT_H

#include "platform_common.h"
#include "drv_font.h"

#define MID_FONT_RTT_DEBUG	3
#if (1 == MID_FONT_RTT_DEBUG)	// 错误等级
#define MID_FONT_RTT_LOG(...)
#define MID_FONT_RTT_WARN(...)
#define MID_FONT_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MID_FONT_RTT_DEBUG)	// 警告等级
#define MID_FONT_RTT_LOG(...)
#define MID_FONT_RTT_WARN		RTT_DEBUG_WARN
#define MID_FONT_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MID_FONT_RTT_DEBUG)	// 调试等级
#define MID_FONT_RTT_LOG		RTT_DEBUG_LOG
#define MID_FONT_RTT_WARN		RTT_DEBUG_WARN
#define MID_FONT_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define MID_FONT_RTT_LOG(...)
#define MID_FONT_RTT_WARN(...)
#define MID_FONT_RTT_ERR(...)
#endif

typedef struct
{
	uint8	wordWidth;//字宽（存储宽度）
	uint8	wordHeight;//字高（存储高度）
	uint8 	validWidth;//字的有效宽度（根据实际字型小于或等于wordWidth）
	uint8 	dataStringLengh;//数据流长度
}font_size_t;

typedef union
{
	uint16	codeGB;
	uint16 	codeUnicode;
	uint8 	codeASCII;
	uint8	codeIndexUI;
}code_t;

typedef struct 
{
	uint8_t*				dataAddr;	// 点阵信息存储地址
	Wordstock_size_s 		sizeKind;	// 字体类型
	code_t 					code;		// 编码值
	font_size_t 			wordSize;   // 字体信息
}font_para_t;

extern void Mid_Font_Init(void);
extern uint16_t Mid_Font_ReadGB(font_para_t *para);
extern uint16 Mid_Font_ReadUnicode(font_para_t *para);
extern uint16 Mid_Font_ReadASCII(font_para_t *para);
extern uint16_t Mid_Font_SelfTest(void);
extern uint16 Mid_Font_ReadFrontSize(font_para_t *para);
extern void Mid_Front_Test(void);

#endif




