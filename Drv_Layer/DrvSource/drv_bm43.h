#ifndef DRV_BM43_H__
#define DRV_BM43_H__


#include <math.h>
#include "platform_common.h"

uint8 Drv_BM43_Open(void);
uint8 Drv_BM43_Close(void);
void bm43_conversion_start(void);
void bm43_conversion_stop(void);
int32_t bm43_calculate_temp(void);

extern uint8_t Drv_BM43_SelfTest(void);
uint32_t Drv_BM43_init(void);

#endif // DRV_BM43_H__

