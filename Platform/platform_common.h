#ifndef PLATFORM_COMMON_H
#define PLATFORM_COMMON_H

#include "platform_debugcof.h"
#include "platform_feature.h"
#include "rtos.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#ifdef keil   //keil
#include <stdbool.h>
#include <stdint.h>

typedef uint64_t  uint64;
typedef uint32_t  uint32;
typedef uint16_t  uint16;
typedef uint8_t   uint8;

typedef int64_t  int64;
typedef int32_t  int32;
typedef int16_t  int16;
typedef int8_t   int8;
#endif

typedef enum
{
	Ret_OK,            
	Ret_Fail,          
	Ret_InvalidParam,
	Ret_DeviceBusy,    
	Ret_NoInit, 
	Ret_NoDevice,
	Ret_QueueFull,   //?óáD?y
	Ret_QueueEmpty,  //?óáD??
	Ret_DeviceError,
	Ret_Timeout,
	ret_RepetitiveOperate,	// 重复操作
}ret_type;

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif


#define RTT_DEBUG_LEVEL		3		/* RTT调试等级，0调试关闭，1错误等级，2警告等级，3调试等级，*/ 
#define ERR_CHECK_ENABLE	0		/* 开启错误校验，1开启，0关闭 */

/* 临时调试DEBUG */
#if 1
#define RTT_DEBUG_printf	SEGGER_RTT_printf
#else
#define RTT_DEBUG_printf(...)
#endif

/* 模块调试DEBUG */
#if (1 == RTT_DEBUG_LEVEL)		// 错误等级
#define RTT_DEBUG_LOG(...)
#define RTT_DEBUG_WARN(...)
#define RTT_DEBUG_ERR		SEGGER_RTT_printf
#elif (2 == RTT_DEBUG_LEVEL)	// 警告等级
#define RTT_DEBUG_LOG(...)
#define RTT_DEBUG_WARN		SEGGER_RTT_printf
#define RTT_DEBUG_ERR		SEGGER_RTT_printf
#elif (3 == RTT_DEBUG_LEVEL)	// 调试等级
#define RTT_DEBUG_LOG		SEGGER_RTT_printf
#define RTT_DEBUG_WARN		SEGGER_RTT_printf
#define RTT_DEBUG_ERR		SEGGER_RTT_printf
#else							// 调试关闭
#define RTT_DEBUG_LOG(...)
#define RTT_DEBUG_WARN(...)
#define RTT_DEBUG_ERR(...)
#endif


#if ERR_CHECK_ENABLE
/* 错误检测宏，若错误，打印错误信息 */
#define drERROR_CHECK(ERR_STR, ERR_CODE)                             \
	{															\
		do                                                      \
		{                                                       \
			char lErrStr[] =  (ERR_STR);				\
			uint16_t lErrCode = (ERR_CODE);         \
			if ((ERR_CODE) != Ret_OK)      				\
			{                                                   \
				SEGGER_RTT_printf(0, "[ERR] %s %d \n", lErrStr, lErrCode);   \
			}                                                   \
		} while (0);							\
	}

/* 错误检测宏，若错误，打印错误信息并调用return退出此函数 */	
#define drERROR_CHECK_RETURN_NULL(ERR_STR, ERR_CODE)                             \
	{															\
		do                                                      \
		{                                                       \
			char lErrStr[] =  (ERR_STR);				\
			uint16_t lErrCode = (ERR_CODE);         \
			if ((ERR_CODE) != Ret_OK)      				\
			{                                                   \
				SEGGER_RTT_printf(0, "[ERR] %s 0x%04X \n", lErrStr, lErrCode);   \
				return ;							\
			}                                                   \
		} while (0);							\
	}

/* 错误检测宏，若错误，打印错误信息，并return错误码退出此函数 */	
#define drERROR_CHECK_RETURN_ERR(ERR_STR, ERR_CODE)                             \
	{															\
		do                                                      \
		{                                                       \
			char lErrStr[] =  (ERR_STR);				\
			uint16_t lErrCode = (ERR_CODE);         \
			if ((ERR_CODE) != Ret_OK)      				\
			{                                                   \
				SEGGER_RTT_printf(0, "[ERR] %s 0x%04X \n", lErrStr, lErrCode);   \
				return lErrCode;							\
			}                                                   \
		} while (0);							\
	}	
#else
#define drERROR_CHECK(ERR_STR, ERR_CODE) {do{if(ERR_CODE) ;}while(0);}
#define drERROR_CHECK_RETURN_NULL(ERR_STR, ERR_CODE) {do{ if(ERR_CODE) return; }while(0);}
#define drERROR_CHECK_RETURN_ERR(ERR_STR, ERR_CODE) {do{ if(ERR_CODE)  return ERR_CODE; }while(0);}
#endif


typedef void comm_cb(void);
typedef	void func(void);


#endif

