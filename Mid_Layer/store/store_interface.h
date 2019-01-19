/*
 * 模块接口函数
 * 外部需使用此模块接口函数/外部变量/宏定义等，包含以下头文件即可：
 * #include "xxx_interface.h"
*/

#ifndef     STORE_INTERFACE_H
#define     STORE_INTERFACE_H

#include "store_variable.h"

#include "store_common.h"
#include "store_step.h"
#include "store_hrd.h"
#include "store_part.h"
#include "store_upload.h"
#include "store_run.h"
#include "store_stress.h"
#include "store_bodytemp.h"
#include "store_sleep.h"
#include "store_sleep_record.h"
#include "store_climb.h"
#include "store_swim.h"
#include "store_abc.h"
#include "store_pdu.h"
#include "store_history.h"

#include "store_task.h"

extern void Store_Interface_ClearInit(void);
extern void Store_Interface_RecoverInit(void);


#endif      //MID_INTERFACE_H


