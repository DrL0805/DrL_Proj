/*
	FLASH存储算法，目录区与数据区一一对应的存储方法

	以计步数据存储为例，
	首先为计步数据存储分配20Block的存储区域（根据H002所用nandflash，1Block=64page，1page=2048Byte，擦必须以block为单位）
	这20block分为
		目录区：2Block，共256KB
		数据区：18Block，共2304KB
	
	目录区介绍
	每个目录分配512字节，所以256KB的目录区最多512个目录，这512个目录分别进行编号0~511
	目录区的512字节分配：
		0~31（32）字节存放存储相关信息：如对应数据区地址、数据长度、目录状态标志位等等
		32~63（32）字节存放用户相关信息：如UTC时间、数据类型等等
		64~511（448）字节存放用户附加(Extras)信息，如跑步场景档案信息
		解释为何每个目录分配512字节：
		根据实际需要，目录分配64字节基本足够，但是nandflash硬件每个page擦除一次后，允许写入的次数是有限制的
		H002所用nandflash写入次数推荐为4次，所以只能牺牲下存储空间，每个目录分配512字节。

	数据区介绍
	数据区由目录区存储地址所指向的空间，专门用来存放数据
	FLASH写过程
	1）目录创建：（暂存RAM中），并确定此目录对应于数据区的存储地址
		注意1，假如出现异常（如异常掉电等），此数据区是被污染过的。所以目录创建时，需对数据区是否被污染进行检查
		检查方法：从目录指向数据区开始地址，读取256字节，并判断此256字节是否全为0xFF，是则通过检查。
		检查通过，目录创建成功
		检查不通过，此目录指向数据区地址为下一Block的起始地址（因为每使用一个新的block，必须先擦除）
		注意2，目录信息创建后，相关信息暂存于RAM，直到封存前才固话到FLASH。如果早早就写在FLASH，若异常掉电。
		则此目录序号的FLASH区域就被污染了
	2）写入数据：向此目录指向数据区地址写入数据，写入数据后地址自行增加（注意跨Block数据写入以及首尾相接的情况）。
	3）目录封存：确定最终的数据长度，把目录状态标记为已封存。在把此目录结构体参数写入目录对应的FLASH区域中。
	
	FLASH读过程：
	1）确定读取的目录序号，根据此目录序号，确定目录区FLASH地址，并读取这128字节的目录信息。
	2）根据目录信息读取数据信息，根据这128目录信息，追踪到数据区，读取相应数据信息。
	
	FLASH擦过程：
	1）确定需擦除的目录序号
	2）把此目录序号FLASH区域的目录状态，标记为已擦除即可。
	
	FLASH恢复过程：
	FLASH恢复其实就是目录的恢复过程。
	首先明确的一点是，被管理的FLASH区域是有限的，比如计步数据，仅保存最近的30个目录数据。数据大于30个目录后，以FIFO方式标记为"删除"。
	1）遍历所有目录：计步目录共512个，编号0~511。检查目录状态标志位是否是需要恢复的状态。
		若不是：遍历下一个
		若是：保存此目录序号，

	一些特殊情况及处理办法
	情况1：正在存储数据时，突然断电，没有封存目录，这样数据恢复是否会有问题？
		数据恢复时，其实是恢复目录及当前地址。
		因为目录没有被封存，所以此目录区域没被污染，没问题
		因为数据区已写过数据了，所以当前数据写入地址是被污染过的，但是我们有污染检查算法，若被污染，数据指针指向下一block，没问题
*/

#include "store_algo.h"
#include "mid_nandflash.h"

// 获取下一目录序号
uint32_t Store_Algo_NextCatalogGet(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial)
{
	if(CatalogSerial == (fStoreInfo->CatalogSerialMax-1))
		return 0;
	else
		return (CatalogSerial+1);
}

// 获取上一目录序号
uint32_t Store_Algo_LastCatalogGet(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial)
{
	if(CatalogSerial == 0)
		return (fStoreInfo->CatalogSerialMax-1);
	else
		return 	(CatalogSerial-1);
}

// 根据目录序号获取目录地址
uint32_t Store_Algo_CatalogAddrGet(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial)
{
	return (fStoreInfo->CatalogBeginAddr + CatalogSerial*STORE2_CATALOG_INFO_LEN);
}

// 修改目录mark标记
uint16_t Store_Algo_CatalogMark(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial, CatalogMart_e Mark)
{
	uint32_t tLogAddr;
	CatalogInfo_t	lCatalogInfo;
	
	tLogAddr = Store_Algo_CatalogAddrGet(fStoreInfo, CatalogSerial);
	
	// 读取目录信息
	Mid_NandFlash_Read((uint8_t*)&lCatalogInfo, tLogAddr, sizeof(CatalogInfo_t));
	
	// 修改目录mark，并写入到flash
	lCatalogInfo.Flash.Info.Mark = Mark;
	Mid_NandFlash_Write((uint8_t*)&lCatalogInfo, tLogAddr, sizeof(CatalogInfo_t));	
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : 检查此FLASH区域是否被污染（使用过），
		污染检查算法：从开始地址读取256字节，并判断此256字节是否全为0xFF，是则通过检查
 * Input : @fLogAddr 待检查的FLASH地址
 * Return: Ret_OK没被污染，否则已被污染
 * Call  : 
 ***************/
uint16_t Store_Algo_PolluteCheck(uint32_t fLogAddr)
{
	uint8_t lBuf[256];
	
	Mid_NandFlash_Read(lBuf, fLogAddr, 256);
	for(uint32_t i = 0;i < 256;i++)
	{
		if(0xFF != lBuf[i])
			return Ret_Fail;
	}

	return Ret_OK; 
}

/*******************************************************************************
 * Brief : 获取当前地址的下一block开始地址（注意循环存储情况）
 * Input : @fStoreInfo 存储信息结构体
		   @fLogAddr 当前地址
 * Return: 下一block地址
 * Call  : 
 ***************/
uint32_t Store_Algo_NextBlockAddr(StoreInfo_t* fStoreInfo, uint32_t fLogAddr)
{
	uint32_t lLogAddr;
	
	lLogAddr = fLogAddr+LOG_BYTE_OF_BLOCK;
	if(lLogAddr >= fStoreInfo->DataEndAddr)
	{
		// 超过最大地址，回到开始地址
		lLogAddr = fStoreInfo->DataBeginAddr;
	}
	else
	{
		// 未超过最大地址，指向下一block起始地址
		lLogAddr = ((lLogAddr >> 17) << 17);
	}
	
	STORE_ALGO_RTT_WARN(0, "[WARN] Store_Algo_NextBlockAddr 0x%X \n", lLogAddr);
	
	return lLogAddr;
}

/*******************************************************************************
 * Brief : 目录创建
 * Input : @fStoreInfo 存储信息结构体
 * Return: 
 * Call  : 
 ***************/
uint16_t Store_Algo_CatalogCreate(StoreInfo_t* fStoreInfo)
{
	if(eStoreStatusNull != fStoreInfo->Status) drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogCreate", Ret_DeviceBusy);
	
	uint32_t lAddr;
	
	/* 获取下一目录序号，若是新block，需先擦除*/
	fStoreInfo->CatalogSerialEnd = Store_Algo_NextCatalogGet(fStoreInfo, fStoreInfo->CatalogSerialEnd);
	if(0 == (fStoreInfo->CatalogSerialEnd % STORE2_CATALOG_NUM_PER_BLOCK))
	{
		lAddr =  Store_Algo_CatalogAddrGet(fStoreInfo, fStoreInfo->CatalogSerialEnd);
		Mid_NandFlash_Erase(lAddr, lAddr);
		STORE_ALGO_RTT_WARN(0, "[WARN] Store_Algo_CatalogCreate Erase 0x%X \n", lAddr);
	}
	
	/* 检查数据区是否被污染，若被污染，数据地址指向下一block */
	if(Ret_OK != Store_Algo_PolluteCheck(fStoreInfo->DataCurrAddr))
	{
		fStoreInfo->DataCurrAddr = Store_Algo_NextBlockAddr(fStoreInfo, fStoreInfo->DataCurrAddr);
	}
	
	fStoreInfo->Catalog.Flash.Info.DataLen = 0;
	fStoreInfo->Catalog.Flash.Info.DataAddr = fStoreInfo->DataCurrAddr;
	fStoreInfo->Catalog.Flash.Info.Mark = eCatalogMarkUsing;
	
	/* 创建成功，开始允许存储数据 */
	fStoreInfo->Status = eStoreStatusIng;	
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : 数据存储，若超过FLASH区域，循环写入
 * Input : @fStoreInfo 存储信息结构体
           @DataBuf 数据指针
           @DataLen 数据长度
 * Return: 
 * Call  : 
 ***************/
uint16_t Store_Algo_DataSave(StoreInfo_t* fStoreInfo, uint8_t* DataBuf, uint32_t DataLen)
{
	if(eStoreStatusIng != fStoreInfo->Status) drERROR_CHECK_RETURN_ERR("Store_Algo_DataSave", Ret_NoInit);
	if(0 == DataLen) drERROR_CHECK_RETURN_ERR("Store_Algo_DataSave", Ret_InvalidParam);
	
	uint32_t lRemainWriteLen;	// 剩余FLASH可写数据长度
	uint32_t lOverWriteLen;		// 超出FLASH待写数据长度
	
	/* 若是新block，需先擦除 */
	if(0 == (fStoreInfo->DataCurrAddr % LOG_BYTE_OF_BLOCK))
	{
		STORE_ALGO_RTT_WARN(0, "[WARN] Store_Algo_DataSave Erase 0x%X \n", fStoreInfo->DataCurrAddr);
		Mid_NandFlash_Erase(fStoreInfo->DataCurrAddr, fStoreInfo->DataCurrAddr);
	}
	
	/* 循环读写算法，注意边界处理 */
	if((fStoreInfo->DataCurrAddr + DataLen - 1) > fStoreInfo->DataEndAddr)
	/* 若当前写入数据超过最大地址，则分开写入 */
	{
		STORE_ALGO_RTT_WARN(0, "[WARN] Store_Algo_DataSave Split 0x%X \n", (fStoreInfo->DataCurrAddr + DataLen - 1));
		
		lRemainWriteLen = fStoreInfo->DataEndAddr - fStoreInfo->DataCurrAddr + 1;
		lOverWriteLen = DataLen - lRemainWriteLen;
		
		/* 先把剩余FLASH区域写完 */
		Mid_NandFlash_Write(DataBuf, fStoreInfo->DataCurrAddr, lRemainWriteLen);
		
		/* 多余数据循环写到FLASH头部 */
		Mid_NandFlash_Erase(fStoreInfo->DataBeginAddr, fStoreInfo->DataBeginAddr);	// 新block写前先擦除
		Mid_NandFlash_Write(DataBuf+lRemainWriteLen, fStoreInfo->DataBeginAddr, lOverWriteLen);
		fStoreInfo->DataCurrAddr = fStoreInfo->DataBeginAddr + lOverWriteLen;
	}
	else
	/* 否则一次性写入 */
	{
		Mid_NandFlash_Write(DataBuf, fStoreInfo->DataCurrAddr, DataLen);
		
		/* 如果FLASH区域刚好写完，则当前地址指向FLASH开始地址 */
		if((fStoreInfo->DataCurrAddr + DataLen - 1) == fStoreInfo->DataEndAddr)
			fStoreInfo->DataCurrAddr = fStoreInfo->DataBeginAddr;
		else
			fStoreInfo->DataCurrAddr += DataLen;
	}
	
	fStoreInfo->Catalog.Flash.Info.DataLen += DataLen;
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : 目录封存
 * Input : @fStoreInfo 存储信息结构体
           @ExtDataBuf 目录附加信息指针，若为NULL则无附加信息（无视ExtDataLen）
           @ExtDataLen 目录附加信息长度
 * Return: 
 * Call  : 
 ***************/
uint16_t Store_Algo_CatalogSeal(StoreInfo_t* fStoreInfo, uint8_t* ExtDataBuf, uint32_t ExtDataLen)
{
	if(eStoreStatusIng != fStoreInfo->Status) drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogSeal", Ret_NoInit);
	if(ExtDataLen > STORE2_CATALOG_EXT_INFO_LEN) drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogSeal", Ret_InvalidParam);

	uint32_t tLogAddr = 0;
	uint8_t lpBuf[STORE2_CATALOG_INFO_LEN];	
	
	/* 把目录相关数据，缓存在临时RAM中 */
	fStoreInfo->Catalog.User.Info.ExtDataLen = ExtDataLen;
	fStoreInfo->Catalog.Flash.Info.Mark = eCatalogMarkSealed;
	memcpy(lpBuf, fStoreInfo->Catalog.Flash.Buf, STORE2_CATALOG_FLASH_INFO_LEN);	// 存储信息
	memcpy(lpBuf+STORE2_CATALOG_FLASH_INFO_LEN, fStoreInfo->Catalog.User.Buf, STORE2_CATALOG_USER_INFO_LEN);		// 用户信息
	if(NULL != ExtDataBuf)
	{
		memcpy(lpBuf+STORE2_CATALOG_FLASH_INFO_LEN+STORE2_CATALOG_USER_INFO_LEN, ExtDataBuf, ExtDataLen);	// 附加信息
	}
	
	/* 目录信息存入FLASH */
	tLogAddr = Store_Algo_CatalogAddrGet(fStoreInfo, fStoreInfo->CatalogSerialEnd);
	Mid_NandFlash_Write(lpBuf, tLogAddr, STORE2_CATALOG_INFO_LEN);	
	
	/* 若首次封存，初始化开始目录序号 */
	if(0 == fStoreInfo->CatalogSerialCnt)
	{
		fStoreInfo->CatalogSerialBegin = fStoreInfo->CatalogSerialEnd;
	}
	
	/* 若超过目录最大存储数，删除开始目录 */
	if(fStoreInfo->CatalogSerialCnt >= fStoreInfo->CatalogSerialMax)
	{
		Store_Algo_CatalogMark(fStoreInfo, fStoreInfo->CatalogSerialBegin, eCatalogMarkCover);	// 标记目录被覆盖
		fStoreInfo->CatalogSerialBegin = Store_Algo_NextCatalogGet(fStoreInfo, fStoreInfo->CatalogSerialBegin);	// 开始目录顺移		
	}
	else
	{
		fStoreInfo->CatalogSerialCnt++;
	}	
	
	fStoreInfo->Status = eStoreStatusNull;	
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : 读取数据信息，若超过FLASH区域，循环读取
 * Input : @fStoreInfo 存储信息结构体，待读取的数据类型
           @fCatalogInfo 目录信息结构体，待读取的目录
           @Offset 偏移地址
		   @DataBuf 数据指针
           @DataLen 数据长度
 * Return: 
 * Call  : 
 ***************/
uint16_t Store_Algo_DataRead(StoreInfo_t* fStoreInfo, CatalogInfo_t* fCatalogInfo, uint32_t Offset, uint8_t* DataBuf, uint32_t DataLen)
{
	if((DataLen+Offset) > fCatalogInfo->Flash.Info.DataLen) drERROR_CHECK_RETURN_ERR("Store_Algo_DataRead", Ret_InvalidParam);
	
	uint32_t lRemainReadLen;	// 剩余FLASH可读数据长度
	uint32_t lOverReadLen;		// 超出FLASH待读数据长度	
	uint32_t lAddr;
	
	/* 循环读写算法，注意边界处理 */
	if((fCatalogInfo->Flash.Info.DataAddr + Offset - 1) > fStoreInfo->DataEndAddr)
	/* 数据地址+偏移地址超过End地址，计算循环地址，一次性读取 */
	{
		STORE_ALGO_RTT_WARN(0, "[WARN] Store_Algo_DataRead Begin 0x%X \n", (fCatalogInfo->Flash.Info.DataAddr + Offset - 1));
		lAddr = Offset - (fStoreInfo->DataEndAddr - fCatalogInfo->Flash.Info.DataAddr + 1); 	// 计算循环后的偏移地址
		Mid_NandFlash_Read(DataBuf, fStoreInfo->DataBeginAddr + lAddr, DataLen);
	}
	else if((fCatalogInfo->Flash.Info.DataAddr + Offset + DataLen - 1) > fStoreInfo->DataEndAddr)
	/* 数据地址+偏移地址+读取长度超过End地址，分开读取 */
	{
		STORE_ALGO_RTT_WARN(0, "[WARN] Store_Algo_DataRead Split 0x%X \n", (fCatalogInfo->Flash.Info.DataAddr + Offset + DataLen - 1));
		
		lRemainReadLen = fStoreInfo->DataEndAddr - (fCatalogInfo->Flash.Info.DataAddr + Offset) + 1;
		lOverReadLen = DataLen - lRemainReadLen;
		
		/* 先把剩余FLASH区域读完 */
		Mid_NandFlash_Read(DataBuf, fCatalogInfo->Flash.Info.DataAddr+Offset, lRemainReadLen);
		
		/* 多余数据循环从FLASH头部读取 */
		Mid_NandFlash_Read(DataBuf+lRemainReadLen, fStoreInfo->DataBeginAddr, lOverReadLen);
	}
	else
	/* 否则一次性读取 */
	{
		Mid_NandFlash_Read(DataBuf, fCatalogInfo->Flash.Info.DataAddr+Offset, DataLen);
	}

	return Ret_OK;
}

/*
 *  恢复算法，4中情况（假设有6个目录，3个需要恢复）
 *  1, Y Y Y N N N
    2, N N Y Y Y N
    3, N N N Y Y Y 
    4, Y N N N Y Y
	1）读取首目录和尾目录看数据是否需要恢复
		若首尾都有目录需要恢复，说明待恢复目录首尾连接
		否则，说明待恢复目录没首尾连接

	恢复原理
	如果异常掉电，部分数据区有数据写入但是没有封存目录。会被污染算法过滤掉
 */
uint16_t Store_Algo_CatalogRecover(StoreInfo_t* fStoreInfo)
{
	bool tRecoverFlg = false;	// 有数据需要恢复标志
	bool lFirstFlg = false, lLastFlg = false; // 首尾目录有效标志
	uint32_t tCatalog0 ,tCatalog1;
	CatalogInfo_t lCatalogInfo;
	
	/* 检测首目录是否有效 */
	Store_Algo_CatalogRead(fStoreInfo, 0, &lCatalogInfo);
	if((eCatalogMarkSealed == lCatalogInfo.Flash.Info.Mark) || 
	    (eCatalogMarkUpload == lCatalogInfo.Flash.Info.Mark) || 
		(eCatalogMarkIgnore == lCatalogInfo.Flash.Info.Mark))
	{
		lFirstFlg = true;
	}
	
	/* 检测尾目录是否有效 */
	Store_Algo_CatalogRead(fStoreInfo, (fStoreInfo->CatalogSerialMax-1), &lCatalogInfo);
	if((eCatalogMarkSealed == lCatalogInfo.Flash.Info.Mark) || 
	    (eCatalogMarkUpload == lCatalogInfo.Flash.Info.Mark) || 
		(eCatalogMarkIgnore == lCatalogInfo.Flash.Info.Mark))
	{
		lLastFlg = true;
	}
	
	if(lFirstFlg && lLastFlg)
	/* 若首尾都需恢复，说明首尾连接 */
	{
		/* 从头部寻找CatalogEnd：若目录不是待恢复类型，说明找到了 */
		for(uint32_t i = 0;i < fStoreInfo->CatalogSerialMax;i++)
		{
			Store_Algo_CatalogRead(fStoreInfo, i, &lCatalogInfo);
			if((eCatalogMarkSealed == lCatalogInfo.Flash.Info.Mark) || 
				(eCatalogMarkUpload == lCatalogInfo.Flash.Info.Mark) || 
				(eCatalogMarkIgnore == lCatalogInfo.Flash.Info.Mark))
			{
				fStoreInfo->CatalogSerialEnd = i;
			}
			else
			{
				break;	// 此目录不需要恢复，说明End目录已找到，退出循环
			}			
		}

		/* 从尾部寻找CatalogBegin：若目录不是待恢复类型，说明找到了 */
		for(uint32_t i = (fStoreInfo->CatalogSerialMax - 1);i > 0;i--)
		{
			Store_Algo_CatalogRead(fStoreInfo, i, &lCatalogInfo);
			if((eCatalogMarkSealed == lCatalogInfo.Flash.Info.Mark) || 
				(eCatalogMarkUpload == lCatalogInfo.Flash.Info.Mark) || 
				(eCatalogMarkIgnore == lCatalogInfo.Flash.Info.Mark))
			{
				fStoreInfo->CatalogSerialBegin = i;
			}
			else
			{
				break;	// 此目录不需要恢复，说明Begin目录已找到，退出循环
			}			
		}
		
		fStoreInfo->CatalogSerialCnt = (fStoreInfo->CatalogSerialMax - fStoreInfo->CatalogSerialBegin) + 
								(fStoreInfo->CatalogSerialEnd + 1);
		
		/* 恢复数据区当前地址，注：倘若异常掉电等情况，导致恢复的DataCurrAddr被
			污染过，写入数据时会使用污染算法进行处理，所以不要担心 */
		Store_Algo_CatalogRead(fStoreInfo, fStoreInfo->CatalogSerialEnd, &lCatalogInfo);
		fStoreInfo->DataCurrAddr = (lCatalogInfo.Flash.Info.DataAddr + lCatalogInfo.Flash.Info.DataLen);
	}
	else
	/* 数据恢复，未跨首尾 */
	{
		for(uint32_t i = 0;i < fStoreInfo->CatalogSerialMax;i++)	// 遍历整个目录
		{
			Store_Algo_CatalogRead(fStoreInfo, i, &lCatalogInfo);
			if((eCatalogMarkSealed == lCatalogInfo.Flash.Info.Mark) || 
				(eCatalogMarkUpload == lCatalogInfo.Flash.Info.Mark) || 
				(eCatalogMarkIgnore == lCatalogInfo.Flash.Info.Mark))
			{
				if(false == tRecoverFlg)
				{
					tRecoverFlg = true;
					tCatalog0 = i;		// 找到开始目录
					tCatalog1 = i;
				}
				else
				{
					tCatalog1 = i;		// 结束目录
				}
			}
			else
			{
				/* tRecoverFlg = true 说明有数据恢复，且开始/结束目录已有序号值
					如果有数据恢复，但下一个目录不是待恢复目录，说明首尾目录均已找到，退出遍历 */
				if(tRecoverFlg)
				{
					break;
				}
			}
		}
		
		if(tRecoverFlg)
		{
			fStoreInfo->CatalogSerialBegin = tCatalog0;
			fStoreInfo->CatalogSerialEnd = tCatalog1;
			fStoreInfo->CatalogSerialCnt = tCatalog1 - tCatalog0 + 1;
			
			/* 恢复数据区当前地址，注：倘若异常掉电等情况，导致恢复的DataCurrAddr被
				污染过，写入数据时会使用污染算法进行处理，所以不要担心 */
			Store_Algo_CatalogRead(fStoreInfo, fStoreInfo->CatalogSerialEnd, &lCatalogInfo);
			fStoreInfo->DataCurrAddr = (lCatalogInfo.Flash.Info.DataAddr + lCatalogInfo.Flash.Info.DataLen);			
		}
	}
	
	/* 若恢复的目录数量，大于允许保存的最大目录数，返回错误 */
	if(fStoreInfo->CatalogSerialCnt > fStoreInfo->CatalogSerialMaxSave) 
		drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogRecover", Ret_Fail);
	
	/* 若CatalogSerialEnd的下一目录被污染过，返回错误 */
	Store_Algo_CatalogRead(fStoreInfo, Store_Algo_NextCatalogGet(fStoreInfo, fStoreInfo->CatalogSerialEnd), &lCatalogInfo);
	if(eCatalogMarkUnuse != lCatalogInfo.Flash.Info.Mark)
		drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogRecover", Ret_DeviceError);	
	
	#if 0
	STORE_ALGO_RTT_LOG(0, "Store_Algo_CatalogRecover: \n");
	STORE_ALGO_RTT_LOG(0, "  .Status %d \n", fStoreInfo->Status);
	STORE_ALGO_RTT_LOG(0, "  .CatalogBeginAddr 0x%X \n", fStoreInfo->CatalogBeginAddr);
	STORE_ALGO_RTT_LOG(0, "  .CatalogEndAddr 0x%X \n", fStoreInfo->CatalogEndAddr);
	STORE_ALGO_RTT_LOG(0, "  .CatalogSerialMax %d \n", fStoreInfo->CatalogSerialMax);
	STORE_ALGO_RTT_LOG(0, "  .CatalogSerialMaxSave %d \n", fStoreInfo->CatalogSerialMaxSave);
	STORE_ALGO_RTT_LOG(0, "  .CatalogSerialBegin %d \n", fStoreInfo->CatalogSerialBegin);
	STORE_ALGO_RTT_LOG(0, "  .CatalogSerialEnd %d \n", fStoreInfo->CatalogSerialEnd);
	STORE_ALGO_RTT_LOG(0, "  .CatalogSerialCnt %d \n", fStoreInfo->CatalogSerialCnt);
	STORE_ALGO_RTT_LOG(0, "  .DataBeginAddr 0x%X \n", fStoreInfo->DataBeginAddr);
	STORE_ALGO_RTT_LOG(0, "  .DataEndAddr 0x%X \n", fStoreInfo->DataEndAddr);
	STORE_ALGO_RTT_LOG(0, "  .DataCurrAddr 0x%X \n", fStoreInfo->DataCurrAddr);
	#endif
	
	return Ret_OK;	
}
 
/*******************************************************************************
 * Brief : 读取目录信息，不包括附加信息
 * Input : @fStoreInfo 存储信息结构体
           @CatalogSerial 目录物理序号
           @CatalogInfo 目录信息结构体
 * Return: 
 * Call  : 
 ***************/
uint16_t Store_Algo_CatalogRead(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial, CatalogInfo_t* CatalogInfo)
{
	if(CatalogSerial >= fStoreInfo->CatalogSerialMax) drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogRead", CatalogSerial);
	
	uint32_t tLogAddr;
	
	tLogAddr = Store_Algo_CatalogAddrGet(fStoreInfo, CatalogSerial);
	
	// 读取目录信息
	Mid_NandFlash_Read((uint8_t*)CatalogInfo, tLogAddr, sizeof(CatalogInfo_t));	
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : 读取目录附加信息
 * Input : @fStoreInfo 存储信息结构体
           @CatalogSerial 目录物理序号
           @DataBuf 数据存放指针
		   @DataLen 读取长度
 * Return: 
 * Call  : 
 ***************/
uint16_t Store_Algo_CatalogExtRead(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial, uint8_t* DataBuf, uint32_t DataLen)
{
	if(CatalogSerial >= fStoreInfo->CatalogSerialMax) drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogExtRead", Ret_InvalidParam);
	if(DataLen > STORE2_CATALOG_EXT_INFO_LEN) drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogExtRead", Ret_InvalidParam);
	
	uint32_t tLogAddr;
	
	tLogAddr = Store_Algo_CatalogAddrGet(fStoreInfo, CatalogSerial);
	
	// 目录附加信息，
	Mid_NandFlash_Read(DataBuf, tLogAddr+STORE2_CATALOG_FLASH_INFO_LEN+STORE2_CATALOG_USER_INFO_LEN, DataLen);	
	
	return Ret_OK;
}

// 指定目录标记已上传（即APP的删除指令）
uint16_t Store_Algo_CatalogUpload(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial)
{
	if(CatalogSerial >= fStoreInfo->CatalogSerialMax) drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogUpload", Ret_InvalidParam);
	
	Store_Algo_CatalogMark(fStoreInfo, CatalogSerial, eCatalogMarkUpload);
	
	return Ret_OK;
}

// 所有目录标记已上传（即APP的删除指令）
uint16_t Store_Algo_CatalogAllUpload(StoreInfo_t* fStoreInfo)
{
	uint32_t lCatalogSerial;
	
	lCatalogSerial = fStoreInfo->CatalogSerialBegin;
	for(uint32_t i = 0;i < fStoreInfo->CatalogSerialCnt;i++)
	{
		Store_Algo_CatalogMark(fStoreInfo, lCatalogSerial, eCatalogMarkUpload);
		lCatalogSerial = Store_Algo_NextCatalogGet(fStoreInfo, lCatalogSerial);
	}
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : 清除已创建的目录信息，封存目录为"忽略"
 * Input : @fStoreInfo 存储信息结构体
 * Return: 
 * Call  : 1）运动数据放弃保存；2）基础数据已上传给APP
 ***************/
uint16_t Store_Algo_CatalogClear(StoreInfo_t* fStoreInfo)
{
	#if 0	// 不封存当前目录
	if(eStoreStatusIng == fStoreInfo->Status)
	/* 如果当前目录正在使用，则封存为"忽略" */
	{
		Store_Algo_CatalogSeal(fStoreInfo, NULL, 0);	// 先封存此目录
		Store_Algo_CatalogMark(fStoreInfo, fStoreInfo->CatalogSerialEnd, eCatalogMarkIgnore);	// 再把此目录mark为忽略
	}
	#endif
	
	fStoreInfo->Status = eStoreStatusNull;
	
	return Ret_OK;
}













