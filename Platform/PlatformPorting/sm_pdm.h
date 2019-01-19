#ifndef __SM_PDM_H
#define __SM_PDM_H

#include "platform_common.h"


typedef void (*pdm_DataReady_Cb)(uint32 *buf, uint32 len);

typedef enum  
{
	PDMCLK_10 = 10,
	PDMCLK_12 = 12,
	PDMCLK_14 = 14,
	PDMCLK_22 = 22,
	PDMCLK_37 = 37,
	PDMCLK_46 = 46,

	PDMDATA_11 = 11,
	PDMDATA_15 = 15,
	PDMDATA_29 = 29,
	PDMDATA_34 = 34,
	PDMDATA_36 = 36,
	PDMDATA_45 = 45,
}pdm_pad_t;

typedef enum 
{
	CHESET_NONE		= 0,
	CHESET_LEFT_ONLY,
	CHESET_RIGHT_ONLY,
	CHESET_BOTH,
}pdm_chset_t;


typedef struct 
{
	uint32 		clkPinNum;
	uint32 		dataPinNum;
	uint32 		gain;
	uint32 	 	chset;
}pdm_config_t;

ret_type SMDrv_Pdm_Init(pdm_DataReady_Cb cb);
ret_type SMDrv_Pdm_Open(pdm_config_t *pdmConfig);
ret_type SMDrv_Pdm_Close(pdm_config_t *pdmConfig);
ret_type SMDrv_Pdm_Start(void);
ret_type SMDrv_Pdm_Stop(void);

#endif

