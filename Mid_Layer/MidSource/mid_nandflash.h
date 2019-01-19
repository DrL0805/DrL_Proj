#ifndef	MID_NANDFLASH_H
#define	MID_NANDFLASH_H

#include "platform_common.h"
#include "drv_nandflash.h"

#define MID_NANDFLASH_RTT_DEBUG	3
#if (1 == MID_NANDFLASH_RTT_DEBUG)	// ����ȼ�
#define MID_NANDFLASH_RTT_LOG(...)
#define MID_NANDFLASH_RTT_WARN(...)
#define MID_NANDFLASH_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MID_NANDFLASH_RTT_DEBUG)	// ����ȼ�
#define MID_NANDFLASH_RTT_LOG(...)
#define MID_NANDFLASH_RTT_WARN		RTT_DEBUG_WARN
#define MID_NANDFLASH_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MID_NANDFLASH_RTT_DEBUG)	// ���Եȼ�
#define MID_NANDFLASH_RTT_LOG		RTT_DEBUG_LOG
#define MID_NANDFLASH_RTT_WARN		RTT_DEBUG_WARN
#define MID_NANDFLASH_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define MID_NANDFLASH_RTT_LOG(...)
#define MID_NANDFLASH_RTT_WARN(...)
#define MID_NANDFLASH_RTT_ERR(...)
#endif

#define PAGE_SIZE            2048  
#define BLOCK_PAGES          64  
#define BLOCKS_PER_ZONE      1024  			// ÿ1024block��һ��LUT[]���й���
#define BYTE_PER_BLOCK		(2048*64)		// ÿblock�ж���byte
 
/*  
H003����NandFlash��4096�飬��Ϊ4��ZONE����Ϊ��ZONEԭ��
1������ram������ͬnandflashоƬ��ֲ
2��LUT[]����ʱ����ͻȻ����̫��ram�飬����ϵͳ����
*/
#define	ZONE_NUM			(4)		

#define MAX_PHY_BLOCKS_PER_ZONE     BLOCKS_PER_ZONE  	// ����������
#define MAX_LOG_BLOCKS_PER_ZONE     1000  				// �޳�������ʹ�õ�block����
#define MAX_SPARE_BLOCKS_PER_ZONE	(MAX_PHY_BLOCKS_PER_ZONE - MAX_LOG_BLOCKS_PER_ZONE)	// ����block����

#define ERASE_BLOCKSZIE         (BLOCK_PAGES*PAGE_SIZE)  

#define GET_BLOCK_FROM_ADDRESS(x)   (x>>17)  

#define VALID_BLOCK         (1<<12)  
#define FREE_BLOCK          (1<<13)  
#define BACKBAD_BLOCK       (1<<14)  
#define BAD_BLOCK           (1<<15) 

#define LOG_CONVERT_PHY_FAILED_ADDR 0xFFFFFFFF
#define INVALID_BLOCK_INDEX			0xFFFF

typedef struct
{
	bool 		LUTInitFlg;					// ������������־
	uint16_t	LUTBlockIndex[ZONE_NUM];	// ÿ��zone�Ļ���LUT����������zone�Ļ���LUT�����ĸ�block��
}Mid_NandFlash_Param_t;

//extern uint16_t Mid_NandFlash_PageRead(uint8_t* pdata,uint32_t LogAddr, uint32_t length);
//extern uint16_t Mid_NandFlash_PageWrite(uint8_t* pdata,uint32_t LogAddr, uint32_t length);
//extern uint16_t Mid_NandFlash_BlockErase(uint32_t LogAddr);

extern uint16_t Mid_NandFlash_Read(uint8_t* pdata,uint32_t LogAddr, uint32_t length);
extern uint16_t Mid_NandFlash_Write(uint8_t* pdata,uint32_t LogAddr, uint32_t length);
extern uint16_t Mid_NandFlash_Erase(uint32_t LogStartAddr, uint32_t LogEndAddr);
extern uint16_t Mid_NandFlash_Init(void);
extern uint16_t Mid_NandFlash_SelfTest(void);
extern void Mid_NandFlash_Test(void);

#endif










