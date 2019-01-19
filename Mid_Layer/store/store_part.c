 /*
	store_part�洢�㷨
	ģ����
	H002����nandflash��1block=64page=64*2048byte��FLASH��Ӳ�������кܶ����ƣ�
	���������blockΪ��λ��ÿpageÿ�β��������д��������Ƽ�����4�ȡ��������ȡ�
	����APP����ʹ��FLASHʱ�ͻ�ܲ����㡣
	��˷�װһ��part�㣬����APP���FLASH�Ĳ������ͺͲ���RAMһ����ֻ��Ҫ����д���ɣ����迼�ǲ����Ȳ�����
	
	�洢�������
	��store_part����100block��block�������100~199
	part256Byte������40block��100~139����2048/256*40 = 320part
	part512Byte������20block��140~159����2048/512*20 = 80part
	part1024Byte������20block��160~179����2048/1024*20 = 40part
	part2024Byte������20block��180~199����2048/2048*20 = 20part
	
	ע��
	1��store_partģ�飬��Ϊÿ�β��������һ��FLASH�����Բ�������FLASHƵ�������ĳ�����
	2��store_part����ÿblock��page0�洢���ݣ�page1~63�������ھ����㷨�����Ǵ��㷨��ʱ��δʵ�֡�
*/

#include "store_part.h"
#include "mid_nandflash.h"

StorePartParam_t	StorePart;

/*******************************************************************************
 * Brief : ģ���ʼ��
 * Input : @NULL 
 * Return: @NULL
 * Call  : ��ʼ���׶ε���һ��
 ***************/
void Store_Part_Init(void)
{
	StorePart.InitFlg = true;
}

/*******************************************************************************
 * Brief : ����part��Ż�ȡ����byte��ַ
 * Input : @Part part���
		   @PartType StorePartType_eö�ٱ�����part����
 * Return: @��ַ
 * Call  : �ڲ�Store_Part_Read()��������
 ***************/
static uint32_t Store_Part_ByteAddrGet(uint32_t Part, StorePartType_e PartType)
{
	uint32_t tLogAddr;
	uint32_t lPartPerPage;	// ÿpage��Ϊ����part
	
	switch (PartType)
    {
    	case eStorePart256B:
			lPartPerPage = 8;	// 2048 / 256
			tLogAddr = STORE_PART_BEGIN_ADDR_256B + 
						(Part / lPartPerPage) * LOG_BYTE_OF_BLOCK + 		// block��ַ
						(Part % lPartPerPage) * 256 ;	// �ֽڵ�ַ		
    		break;
    	case eStorePart512B:
			lPartPerPage = 4;	// 2048 / 512
			tLogAddr = STORE_PART_BEGIN_ADDR_512B + 
						(Part / lPartPerPage) * LOG_BYTE_OF_BLOCK + 		// block��ַ
						(Part % lPartPerPage) * 512 ;	// �ֽڵ�ַ	
    		break;
		case eStorePart1KB:
			lPartPerPage = 2;	// 2048 / 1024
			tLogAddr = STORE_PART_BEGIN_ADDR_1KB + 
						(Part / lPartPerPage) * LOG_BYTE_OF_BLOCK + 		// block��ַ
						(Part % lPartPerPage) * 1024 ;	// �ֽڵ�ַ	
    		break;
		case eStorePart2KB:
			lPartPerPage = 1;	// 2048 / 2048
			tLogAddr = STORE_PART_BEGIN_ADDR_2KB + Part*LOG_BYTE_OF_BLOCK;// block��ַ
    		break;
    	default :
    		break;
    }

	return tLogAddr;
}

/*******************************************************************************
 * Brief : ����part��Ż�ȡ����Block��ַ
 * Input : @Part part���
		   @PartType StorePartType_eö�ٱ�����part����
 * Return: ��ȡ�ĵ�ַ��ַ
 * Call  : �ڲ�Store_Part_Write()��������
 ***************/
static uint32_t Store_Part_BlockAddrGet(uint32_t Part, StorePartType_e PartType)
{
	uint32_t tLogAddr;
	uint32_t lPartPerPage;	// ÿpage��Ϊ����part
	
	switch (PartType)
    {
    	case eStorePart256B:
			lPartPerPage = 8;	// 2048 / 256
			tLogAddr = STORE_PART_BEGIN_ADDR_256B + 
						(Part / lPartPerPage) * LOG_BYTE_OF_BLOCK;		
    		break;
    	case eStorePart512B:
			lPartPerPage = 4;	// 2048 / 512
			tLogAddr = STORE_PART_BEGIN_ADDR_512B + 
						(Part / lPartPerPage) * LOG_BYTE_OF_BLOCK;
    		break;
		case eStorePart1KB:
			lPartPerPage = 2;	// 2048 / 1024
			tLogAddr = STORE_PART_BEGIN_ADDR_1KB + 
						(Part / lPartPerPage) * LOG_BYTE_OF_BLOCK;
    		break;
		case eStorePart2KB:
			//lPartPerPage = 1;	// 2048 / 2048
			tLogAddr = STORE_PART_BEGIN_ADDR_2KB + Part*LOG_BYTE_OF_BLOCK;
    		break;
    	default :
    		break;
    }

	return tLogAddr;
}

/*******************************************************************************
 * Brief : д���ݵ�part����
 * Input : @PartType StorePartType_eö�ٱ�����part����
		   @Part part���
		   @DataBuf ��д�������ָ��
           @DataLen ��д������ݳ���
 * Return: ������
 * Call  : �ⲿ����
 ***************/
void Store_Part_Write(StorePartType_e PartType, uint32_t Part, uint8_t* DataBuf, uint32_t DataLen)
{
	if(!StorePart.InitFlg)	drERROR_CHECK_RETURN_NULL("Store_Part_Write", Ret_NoInit); 
	
	uint32_t tLogBlockAddr;
	uint8_t* tpBuf;
	
	/* part�����Ч���жϡ����ݳ�����Ч���ж� */
	switch (PartType)
    {
    	case eStorePart256B:
			if((Part >= STORE_PART_NUM_256B) || (DataLen > 256)) drERROR_CHECK_RETURN_NULL("Store_Part_Write", Ret_InvalidParam); 
    		break;
    	case eStorePart512B:
			if((Part >= STORE_PART_NUM_512B) || (DataLen > 512)) drERROR_CHECK_RETURN_NULL("Store_Part_Write", Ret_InvalidParam); 	
    		break;
		case eStorePart1KB:
			if((Part >= STORE_PART_NUM_1KB) || (DataLen > 1024)) drERROR_CHECK_RETURN_NULL("Store_Part_Write", Ret_InvalidParam);  	
    		break;
		case eStorePart2KB:
			if((Part >= STORE_PART_NUM_2KB) || (DataLen > 2048)) drERROR_CHECK_RETURN_NULL("Store_Part_Write", Ret_InvalidParam); 
    		break;
    	default :
			drERROR_CHECK_RETURN_NULL("Store_Part_Write", Ret_InvalidParam); 
    		break;
    }
	
	tpBuf= pvPortMalloc(STORE_MAX_MALLOC_LEN);
	
	/* ��ȡ��д�����ݵĵ�ַ */
	tLogBlockAddr = Store_Part_BlockAddrGet(Part, PartType);

	/* �ȴ�flash��ȡpageȫ������ */
	Mid_NandFlash_Read(tpBuf, tLogBlockAddr, 2048);
	
	/* ��ram���޸����� */
	switch (PartType)
    {
    	case eStorePart256B:
			memcpy(tpBuf + (Part % 8)*256, DataBuf, DataLen);	// 8 = 2048 / 256��ÿpage��Ϊ����part	
    		break;
    	case eStorePart512B:
			memcpy(tpBuf + (Part % 4)*512, DataBuf, DataLen);	// 4 = 2048 / 512��ÿpage��Ϊ����part
    		break;
		case eStorePart1KB:
			memcpy(tpBuf + (Part % 2)*1024, DataBuf, DataLen);	// 2 = 2048 / 1024��ÿpage��Ϊ����part	
    		break;
		case eStorePart2KB:
			memcpy(tpBuf, DataBuf, DataLen);	// 1 = 2048 / 2048��ÿpage��Ϊ����part	
    		break;
    	default :
			break;
    }	

	/* �ٰ���������ȫ��д��FLASH�� */
	Mid_NandFlash_Erase(tLogBlockAddr, tLogBlockAddr);
	Mid_NandFlash_Write(tpBuf, tLogBlockAddr, 2048);
	
	vPortFree(tpBuf);
}

/*******************************************************************************
 * Brief : ��part���������
 * Input : @PartType StorePartType_eö�ٱ�����part����
		   @Part part���
		   @DataBuf ����ȡ������ָ��
           @DataLen ����ȡ�����ݳ���
 * Return: ������
 * Call  : �ⲿ����
 ***************/
void Store_Part_Read(StorePartType_e PartType, uint32_t Part, uint8_t* DataBuf, uint32_t DataLen)
{
	uint32_t tLogByteAddr;
	
	if(!StorePart.InitFlg)	drERROR_CHECK_RETURN_NULL("Store_Part_Write", Ret_NoInit); 
	
	/* part�����Ч���жϡ����ݳ�����Ч���ж� */
	switch (PartType)
    {
    	case eStorePart256B:
			if((Part >= STORE_PART_NUM_256B) || (DataLen > 256)) drERROR_CHECK_RETURN_NULL("Store_Part_Read", Ret_InvalidParam); 
    		break;
    	case eStorePart512B:
			if((Part >= STORE_PART_NUM_512B) || (DataLen > 512)) drERROR_CHECK_RETURN_NULL("Store_Part_Read", Ret_InvalidParam); 	
    		break;
		case eStorePart1KB:
			if((Part >= STORE_PART_NUM_1KB) || (DataLen > 1024)) drERROR_CHECK_RETURN_NULL("Store_Part_Read", Ret_InvalidParam); 	
    		break;
		case eStorePart2KB:
			if((Part >= STORE_PART_NUM_2KB) || (DataLen > 2048)) drERROR_CHECK_RETURN_NULL("Store_Part_Read", Ret_InvalidParam); 	
    		break;
    	default :
			 drERROR_CHECK_RETURN_NULL("Store_Part_Read", Ret_InvalidParam); 
    		break;
    }
	
	/* ��ȡ��ȡ���ݵ�ַ */
	tLogByteAddr = Store_Part_ByteAddrGet(Part, PartType);
	
	/* ��FLASH��ȡ���� */
	Mid_NandFlash_Read(DataBuf, tLogByteAddr, DataLen);
}

/*******************************************************************************
 * Brief : partģ�����
		   ������ģ��д����������ڶ�������ͨ��RTT��ӡ������������ֵ��д����Ƿ���ͬ
		   ע�⣺���Ժ������޸�partģ���������ݣ����������
 * Input : @NULL
 * Return: @NULL
 * Call  : �ⲿ����
 ***************/
void Store_Part_Test(void)
{
	uint8_t tWriteBuf[256];
	uint8_t tReadBuf[256];
	uint8_t tLen = 16;
	
	#if 1	// part_256B
	for(uint32_t i = 0;i < STORE_PART_NUM_256B;i++)
	{
		memset(tWriteBuf, (uint8_t)(i), tLen);
		Store_Part_Write(eStorePart256B, i, tWriteBuf, tLen);
	}
	
	for(uint32_t i = 0;i < STORE_PART_NUM_256B;i++)
	{
		Store_Part_Read(eStorePart256B, i, tReadBuf, tLen);
		
		STORE_PART_RTT_LOG(0, "Store_Part_Read256B %02X: ", i);
		for(uint32_t i = 0;i < tLen;i++)
		{
			STORE_PART_RTT_LOG(0, "%02X ", tReadBuf[i]);
		}STORE_PART_RTT_LOG(0, "\n");		
	}	
	#endif
	
	#if 1	// part_512B
	for(uint32_t i = 0;i < STORE_PART_NUM_512B;i++)
	{
		memset(tWriteBuf, (uint8_t)(i+1), tLen);
		Store_Part_Write(eStorePart512B, i, tWriteBuf, tLen);
	}

	for(uint32_t i = 0;i < STORE_PART_NUM_512B;i++)
	{
		Store_Part_Read(eStorePart512B, i, tReadBuf, tLen);
		
		STORE_PART_RTT_LOG(0, "Store_Part_Read512B %02X: ", i);
		for(uint32_t i = 0;i < tLen;i++)
		{
			STORE_PART_RTT_LOG(0, "%02X ", tReadBuf[i]);
		}STORE_PART_RTT_LOG(0, "\n");		
	}	
	#endif	
	
	#if 1	// part_1KB
	for(uint32_t i = 0;i < STORE_PART_NUM_1KB;i++)
	{
		memset(tWriteBuf, (uint8_t)(i), tLen);
		Store_Part_Write(eStorePart1KB, i, tWriteBuf, tLen);
	}

	for(uint32_t i = 0;i < STORE_PART_NUM_1KB;i++)
	{
		Store_Part_Read(eStorePart1KB, i, tReadBuf, tLen);
		
		STORE_PART_RTT_LOG(0, "Store_Part_Read1KB %02X: ", i);
		for(uint32_t i = 0;i < tLen;i++)
		{
			STORE_PART_RTT_LOG(0, "%02X ", tReadBuf[i]);
		}STORE_PART_RTT_LOG(0, "\n");		
	}	
	#endif	
	
	#if 1	// part_2KB
	for(uint32_t i = 0;i < STORE_PART_NUM_2KB;i++)
	{
		memset(tWriteBuf, (uint8_t)(i), tLen);
		Store_Part_Write(eStorePart2KB, i, tWriteBuf, tLen);
	}
	
	for(uint32_t i = 0;i < STORE_PART_NUM_2KB;i++)
	{
		Store_Part_Read(eStorePart2KB, i, tReadBuf, tLen);
		
		STORE_PART_RTT_LOG(0, "Store_Part_Read2KB %02X: ", i);
		for(uint32_t i = 0;i < tLen;i++)
		{
			STORE_PART_RTT_LOG(0, "%02X ", tReadBuf[i]);
		}STORE_PART_RTT_LOG(0, "\n");		
	}	
	#endif		
}







