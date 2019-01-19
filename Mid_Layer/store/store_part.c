 /*
	store_part存储算法
	模块简介
	H002所用nandflash，1block=64page=64*2048byte。FLASH的硬件操作有很多限制，
	如擦必须以block为单位，每page每次擦除后最大写入次数不推荐超过4等。坏块管理等。
	这样APP层在使用FLASH时就会很不方便。
	因此封装一个part层，这样APP层对FLASH的操作，就和操作RAM一样。只需要读和写即可，无需考虑擦除等操作。
	
	存储区域分配
	给store_part分配100block，block物理序号100~199
	part256Byte：分配40block，100~139，共2048/256*40 = 320part
	part512Byte：分配20block，140~159，共2048/512*20 = 80part
	part1024Byte：分配20block，160~179，共2048/1024*20 = 40part
	part2024Byte：分配20block，180~199，共2048/2048*20 = 20part
	
	注：
	1）store_part模块，因为每次操作都会擦一次FLASH。所以不可用在FLASH频繁操作的场景。
	2）store_part暂用每block的page0存储数据，page1~63后续用于均衡算法，但是此算法暂时还未实现。
*/

#include "store_part.h"
#include "mid_nandflash.h"

StorePartParam_t	StorePart;

/*******************************************************************************
 * Brief : 模块初始化
 * Input : @NULL 
 * Return: @NULL
 * Call  : 初始化阶段调用一次
 ***************/
void Store_Part_Init(void)
{
	StorePart.InitFlg = true;
}

/*******************************************************************************
 * Brief : 根据part序号获取读的byte地址
 * Input : @Part part序号
		   @PartType StorePartType_e枚举变量的part类型
 * Return: @地址
 * Call  : 内部Store_Part_Read()函数调用
 ***************/
static uint32_t Store_Part_ByteAddrGet(uint32_t Part, StorePartType_e PartType)
{
	uint32_t tLogAddr;
	uint32_t lPartPerPage;	// 每page分为几个part
	
	switch (PartType)
    {
    	case eStorePart256B:
			lPartPerPage = 8;	// 2048 / 256
			tLogAddr = STORE_PART_BEGIN_ADDR_256B + 
						(Part / lPartPerPage) * LOG_BYTE_OF_BLOCK + 		// block地址
						(Part % lPartPerPage) * 256 ;	// 字节地址		
    		break;
    	case eStorePart512B:
			lPartPerPage = 4;	// 2048 / 512
			tLogAddr = STORE_PART_BEGIN_ADDR_512B + 
						(Part / lPartPerPage) * LOG_BYTE_OF_BLOCK + 		// block地址
						(Part % lPartPerPage) * 512 ;	// 字节地址	
    		break;
		case eStorePart1KB:
			lPartPerPage = 2;	// 2048 / 1024
			tLogAddr = STORE_PART_BEGIN_ADDR_1KB + 
						(Part / lPartPerPage) * LOG_BYTE_OF_BLOCK + 		// block地址
						(Part % lPartPerPage) * 1024 ;	// 字节地址	
    		break;
		case eStorePart2KB:
			lPartPerPage = 1;	// 2048 / 2048
			tLogAddr = STORE_PART_BEGIN_ADDR_2KB + Part*LOG_BYTE_OF_BLOCK;// block地址
    		break;
    	default :
    		break;
    }

	return tLogAddr;
}

/*******************************************************************************
 * Brief : 根据part序号获取读的Block地址
 * Input : @Part part序号
		   @PartType StorePartType_e枚举变量的part类型
 * Return: 获取的地址地址
 * Call  : 内部Store_Part_Write()函数调用
 ***************/
static uint32_t Store_Part_BlockAddrGet(uint32_t Part, StorePartType_e PartType)
{
	uint32_t tLogAddr;
	uint32_t lPartPerPage;	// 每page分为几个part
	
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
 * Brief : 写数据到part区域
 * Input : @PartType StorePartType_e枚举变量的part类型
		   @Part part序号
		   @DataBuf 待写入的数据指针
           @DataLen 待写入的数据长度
 * Return: 处理结果
 * Call  : 外部调用
 ***************/
void Store_Part_Write(StorePartType_e PartType, uint32_t Part, uint8_t* DataBuf, uint32_t DataLen)
{
	if(!StorePart.InitFlg)	drERROR_CHECK_RETURN_NULL("Store_Part_Write", Ret_NoInit); 
	
	uint32_t tLogBlockAddr;
	uint8_t* tpBuf;
	
	/* part序号有效性判断、数据长度有效性判断 */
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
	
	/* 获取待写入数据的地址 */
	tLogBlockAddr = Store_Part_BlockAddrGet(Part, PartType);

	/* 先从flash读取page全部数据 */
	Mid_NandFlash_Read(tpBuf, tLogBlockAddr, 2048);
	
	/* 在ram中修改数据 */
	switch (PartType)
    {
    	case eStorePart256B:
			memcpy(tpBuf + (Part % 8)*256, DataBuf, DataLen);	// 8 = 2048 / 256，每page分为几个part	
    		break;
    	case eStorePart512B:
			memcpy(tpBuf + (Part % 4)*512, DataBuf, DataLen);	// 4 = 2048 / 512，每page分为几个part
    		break;
		case eStorePart1KB:
			memcpy(tpBuf + (Part % 2)*1024, DataBuf, DataLen);	// 2 = 2048 / 1024，每page分为几个part	
    		break;
		case eStorePart2KB:
			memcpy(tpBuf, DataBuf, DataLen);	// 1 = 2048 / 2048，每page分为几个part	
    		break;
    	default :
			break;
    }	

	/* 再把所有数据全部写入FLASH中 */
	Mid_NandFlash_Erase(tLogBlockAddr, tLogBlockAddr);
	Mid_NandFlash_Write(tpBuf, tLogBlockAddr, 2048);
	
	vPortFree(tpBuf);
}

/*******************************************************************************
 * Brief : 从part区域读数据
 * Input : @PartType StorePartType_e枚举变量的part类型
		   @Part part序号
		   @DataBuf 待读取的数据指针
           @DataLen 待读取的数据长度
 * Return: 处理结果
 * Call  : 外部调用
 ***************/
void Store_Part_Read(StorePartType_e PartType, uint32_t Part, uint8_t* DataBuf, uint32_t DataLen)
{
	uint32_t tLogByteAddr;
	
	if(!StorePart.InitFlg)	drERROR_CHECK_RETURN_NULL("Store_Part_Write", Ret_NoInit); 
	
	/* part序号有效性判断、数据长度有效性判断 */
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
	
	/* 获取读取数据地址 */
	tLogByteAddr = Store_Part_ByteAddrGet(Part, PartType);
	
	/* 从FLASH读取数据 */
	Mid_NandFlash_Read(DataBuf, tLogByteAddr, DataLen);
}

/*******************************************************************************
 * Brief : part模块测试
		   向所有模块写入测试数据在读出，并通过RTT打印出来。看读出值和写入的是否相同
		   注意：测试函数会修改part模块所有数据，需谨慎调用
 * Input : @NULL
 * Return: @NULL
 * Call  : 外部调用
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







