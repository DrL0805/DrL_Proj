/*
	FLASH�洢�㷨��Ŀ¼����������һһ��Ӧ�Ĵ洢����

	�ԼƲ����ݴ洢Ϊ����
	����Ϊ�Ʋ����ݴ洢����20Block�Ĵ洢���򣨸���H002����nandflash��1Block=64page��1page=2048Byte����������blockΪ��λ��
	��20block��Ϊ
		Ŀ¼����2Block����256KB
		��������18Block����2304KB
	
	Ŀ¼������
	ÿ��Ŀ¼����512�ֽڣ�����256KB��Ŀ¼�����512��Ŀ¼����512��Ŀ¼�ֱ���б��0~511
	Ŀ¼����512�ֽڷ��䣺
		0~31��32���ֽڴ�Ŵ洢�����Ϣ�����Ӧ��������ַ�����ݳ��ȡ�Ŀ¼״̬��־λ�ȵ�
		32~63��32���ֽڴ���û������Ϣ����UTCʱ�䡢�������͵ȵ�
		64~511��448���ֽڴ���û�����(Extras)��Ϣ�����ܲ�����������Ϣ
		����Ϊ��ÿ��Ŀ¼����512�ֽڣ�
		����ʵ����Ҫ��Ŀ¼����64�ֽڻ����㹻������nandflashӲ��ÿ��page����һ�κ�����д��Ĵ����������Ƶ�
		H002����nandflashд������Ƽ�Ϊ4�Σ�����ֻ�������´洢�ռ䣬ÿ��Ŀ¼����512�ֽڡ�

	����������
	��������Ŀ¼���洢��ַ��ָ��Ŀռ䣬ר�������������
	FLASHд����
	1��Ŀ¼���������ݴ�RAM�У�����ȷ����Ŀ¼��Ӧ���������Ĵ洢��ַ
		ע��1����������쳣�����쳣����ȣ������������Ǳ���Ⱦ���ġ�����Ŀ¼����ʱ������������Ƿ���Ⱦ���м��
		��鷽������Ŀ¼ָ����������ʼ��ַ����ȡ256�ֽڣ����жϴ�256�ֽ��Ƿ�ȫΪ0xFF������ͨ����顣
		���ͨ����Ŀ¼�����ɹ�
		��鲻ͨ������Ŀ¼ָ����������ַΪ��һBlock����ʼ��ַ����Ϊÿʹ��һ���µ�block�������Ȳ�����
		ע��2��Ŀ¼��Ϣ�����������Ϣ�ݴ���RAM��ֱ�����ǰ�Ź̻���FLASH����������д��FLASH�����쳣���硣
		���Ŀ¼��ŵ�FLASH����ͱ���Ⱦ��
	2��д�����ݣ����Ŀ¼ָ����������ַд�����ݣ�д�����ݺ��ַ�������ӣ�ע���Block����д���Լ���β��ӵ��������
	3��Ŀ¼��棺ȷ�����յ����ݳ��ȣ���Ŀ¼״̬���Ϊ�ѷ�档�ڰѴ�Ŀ¼�ṹ�����д��Ŀ¼��Ӧ��FLASH�����С�
	
	FLASH�����̣�
	1��ȷ����ȡ��Ŀ¼��ţ����ݴ�Ŀ¼��ţ�ȷ��Ŀ¼��FLASH��ַ������ȡ��128�ֽڵ�Ŀ¼��Ϣ��
	2������Ŀ¼��Ϣ��ȡ������Ϣ��������128Ŀ¼��Ϣ��׷�ٵ�����������ȡ��Ӧ������Ϣ��
	
	FLASH�����̣�
	1��ȷ���������Ŀ¼���
	2���Ѵ�Ŀ¼���FLASH�����Ŀ¼״̬�����Ϊ�Ѳ������ɡ�
	
	FLASH�ָ����̣�
	FLASH�ָ���ʵ����Ŀ¼�Ļָ����̡�
	������ȷ��һ���ǣ��������FLASH���������޵ģ�����Ʋ����ݣ������������30��Ŀ¼���ݡ����ݴ���30��Ŀ¼����FIFO��ʽ���Ϊ"ɾ��"��
	1����������Ŀ¼���Ʋ�Ŀ¼��512�������0~511�����Ŀ¼״̬��־λ�Ƿ�����Ҫ�ָ���״̬��
		�����ǣ�������һ��
		���ǣ������Ŀ¼��ţ�

	һЩ�������������취
	���1�����ڴ洢����ʱ��ͻȻ�ϵ磬û�з��Ŀ¼���������ݻָ��Ƿ�������⣿
		���ݻָ�ʱ����ʵ�ǻָ�Ŀ¼����ǰ��ַ��
		��ΪĿ¼û�б���棬���Դ�Ŀ¼����û����Ⱦ��û����
		��Ϊ��������д�������ˣ����Ե�ǰ����д���ַ�Ǳ���Ⱦ���ģ�������������Ⱦ����㷨��������Ⱦ������ָ��ָ����һblock��û����
*/

#include "store_algo.h"
#include "mid_nandflash.h"

// ��ȡ��һĿ¼���
uint32_t Store_Algo_NextCatalogGet(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial)
{
	if(CatalogSerial == (fStoreInfo->CatalogSerialMax-1))
		return 0;
	else
		return (CatalogSerial+1);
}

// ��ȡ��һĿ¼���
uint32_t Store_Algo_LastCatalogGet(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial)
{
	if(CatalogSerial == 0)
		return (fStoreInfo->CatalogSerialMax-1);
	else
		return 	(CatalogSerial-1);
}

// ����Ŀ¼��Ż�ȡĿ¼��ַ
uint32_t Store_Algo_CatalogAddrGet(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial)
{
	return (fStoreInfo->CatalogBeginAddr + CatalogSerial*STORE2_CATALOG_INFO_LEN);
}

// �޸�Ŀ¼mark���
uint16_t Store_Algo_CatalogMark(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial, CatalogMart_e Mark)
{
	uint32_t tLogAddr;
	CatalogInfo_t	lCatalogInfo;
	
	tLogAddr = Store_Algo_CatalogAddrGet(fStoreInfo, CatalogSerial);
	
	// ��ȡĿ¼��Ϣ
	Mid_NandFlash_Read((uint8_t*)&lCatalogInfo, tLogAddr, sizeof(CatalogInfo_t));
	
	// �޸�Ŀ¼mark����д�뵽flash
	lCatalogInfo.Flash.Info.Mark = Mark;
	Mid_NandFlash_Write((uint8_t*)&lCatalogInfo, tLogAddr, sizeof(CatalogInfo_t));	
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : ����FLASH�����Ƿ���Ⱦ��ʹ�ù�����
		��Ⱦ����㷨���ӿ�ʼ��ַ��ȡ256�ֽڣ����жϴ�256�ֽ��Ƿ�ȫΪ0xFF������ͨ�����
 * Input : @fLogAddr ������FLASH��ַ
 * Return: Ret_OKû����Ⱦ�������ѱ���Ⱦ
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
 * Brief : ��ȡ��ǰ��ַ����һblock��ʼ��ַ��ע��ѭ���洢�����
 * Input : @fStoreInfo �洢��Ϣ�ṹ��
		   @fLogAddr ��ǰ��ַ
 * Return: ��һblock��ַ
 * Call  : 
 ***************/
uint32_t Store_Algo_NextBlockAddr(StoreInfo_t* fStoreInfo, uint32_t fLogAddr)
{
	uint32_t lLogAddr;
	
	lLogAddr = fLogAddr+LOG_BYTE_OF_BLOCK;
	if(lLogAddr >= fStoreInfo->DataEndAddr)
	{
		// ��������ַ���ص���ʼ��ַ
		lLogAddr = fStoreInfo->DataBeginAddr;
	}
	else
	{
		// δ��������ַ��ָ����һblock��ʼ��ַ
		lLogAddr = ((lLogAddr >> 17) << 17);
	}
	
	STORE_ALGO_RTT_WARN(0, "[WARN] Store_Algo_NextBlockAddr 0x%X \n", lLogAddr);
	
	return lLogAddr;
}

/*******************************************************************************
 * Brief : Ŀ¼����
 * Input : @fStoreInfo �洢��Ϣ�ṹ��
 * Return: 
 * Call  : 
 ***************/
uint16_t Store_Algo_CatalogCreate(StoreInfo_t* fStoreInfo)
{
	if(eStoreStatusNull != fStoreInfo->Status) drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogCreate", Ret_DeviceBusy);
	
	uint32_t lAddr;
	
	/* ��ȡ��һĿ¼��ţ�������block�����Ȳ���*/
	fStoreInfo->CatalogSerialEnd = Store_Algo_NextCatalogGet(fStoreInfo, fStoreInfo->CatalogSerialEnd);
	if(0 == (fStoreInfo->CatalogSerialEnd % STORE2_CATALOG_NUM_PER_BLOCK))
	{
		lAddr =  Store_Algo_CatalogAddrGet(fStoreInfo, fStoreInfo->CatalogSerialEnd);
		Mid_NandFlash_Erase(lAddr, lAddr);
		STORE_ALGO_RTT_WARN(0, "[WARN] Store_Algo_CatalogCreate Erase 0x%X \n", lAddr);
	}
	
	/* ����������Ƿ���Ⱦ��������Ⱦ�����ݵ�ַָ����һblock */
	if(Ret_OK != Store_Algo_PolluteCheck(fStoreInfo->DataCurrAddr))
	{
		fStoreInfo->DataCurrAddr = Store_Algo_NextBlockAddr(fStoreInfo, fStoreInfo->DataCurrAddr);
	}
	
	fStoreInfo->Catalog.Flash.Info.DataLen = 0;
	fStoreInfo->Catalog.Flash.Info.DataAddr = fStoreInfo->DataCurrAddr;
	fStoreInfo->Catalog.Flash.Info.Mark = eCatalogMarkUsing;
	
	/* �����ɹ�����ʼ����洢���� */
	fStoreInfo->Status = eStoreStatusIng;	
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : ���ݴ洢��������FLASH����ѭ��д��
 * Input : @fStoreInfo �洢��Ϣ�ṹ��
           @DataBuf ����ָ��
           @DataLen ���ݳ���
 * Return: 
 * Call  : 
 ***************/
uint16_t Store_Algo_DataSave(StoreInfo_t* fStoreInfo, uint8_t* DataBuf, uint32_t DataLen)
{
	if(eStoreStatusIng != fStoreInfo->Status) drERROR_CHECK_RETURN_ERR("Store_Algo_DataSave", Ret_NoInit);
	if(0 == DataLen) drERROR_CHECK_RETURN_ERR("Store_Algo_DataSave", Ret_InvalidParam);
	
	uint32_t lRemainWriteLen;	// ʣ��FLASH��д���ݳ���
	uint32_t lOverWriteLen;		// ����FLASH��д���ݳ���
	
	/* ������block�����Ȳ��� */
	if(0 == (fStoreInfo->DataCurrAddr % LOG_BYTE_OF_BLOCK))
	{
		STORE_ALGO_RTT_WARN(0, "[WARN] Store_Algo_DataSave Erase 0x%X \n", fStoreInfo->DataCurrAddr);
		Mid_NandFlash_Erase(fStoreInfo->DataCurrAddr, fStoreInfo->DataCurrAddr);
	}
	
	/* ѭ����д�㷨��ע��߽紦�� */
	if((fStoreInfo->DataCurrAddr + DataLen - 1) > fStoreInfo->DataEndAddr)
	/* ����ǰд�����ݳ�������ַ����ֿ�д�� */
	{
		STORE_ALGO_RTT_WARN(0, "[WARN] Store_Algo_DataSave Split 0x%X \n", (fStoreInfo->DataCurrAddr + DataLen - 1));
		
		lRemainWriteLen = fStoreInfo->DataEndAddr - fStoreInfo->DataCurrAddr + 1;
		lOverWriteLen = DataLen - lRemainWriteLen;
		
		/* �Ȱ�ʣ��FLASH����д�� */
		Mid_NandFlash_Write(DataBuf, fStoreInfo->DataCurrAddr, lRemainWriteLen);
		
		/* ��������ѭ��д��FLASHͷ�� */
		Mid_NandFlash_Erase(fStoreInfo->DataBeginAddr, fStoreInfo->DataBeginAddr);	// ��blockдǰ�Ȳ���
		Mid_NandFlash_Write(DataBuf+lRemainWriteLen, fStoreInfo->DataBeginAddr, lOverWriteLen);
		fStoreInfo->DataCurrAddr = fStoreInfo->DataBeginAddr + lOverWriteLen;
	}
	else
	/* ����һ����д�� */
	{
		Mid_NandFlash_Write(DataBuf, fStoreInfo->DataCurrAddr, DataLen);
		
		/* ���FLASH����պ�д�꣬��ǰ��ַָ��FLASH��ʼ��ַ */
		if((fStoreInfo->DataCurrAddr + DataLen - 1) == fStoreInfo->DataEndAddr)
			fStoreInfo->DataCurrAddr = fStoreInfo->DataBeginAddr;
		else
			fStoreInfo->DataCurrAddr += DataLen;
	}
	
	fStoreInfo->Catalog.Flash.Info.DataLen += DataLen;
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : Ŀ¼���
 * Input : @fStoreInfo �洢��Ϣ�ṹ��
           @ExtDataBuf Ŀ¼������Ϣָ�룬��ΪNULL���޸�����Ϣ������ExtDataLen��
           @ExtDataLen Ŀ¼������Ϣ����
 * Return: 
 * Call  : 
 ***************/
uint16_t Store_Algo_CatalogSeal(StoreInfo_t* fStoreInfo, uint8_t* ExtDataBuf, uint32_t ExtDataLen)
{
	if(eStoreStatusIng != fStoreInfo->Status) drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogSeal", Ret_NoInit);
	if(ExtDataLen > STORE2_CATALOG_EXT_INFO_LEN) drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogSeal", Ret_InvalidParam);

	uint32_t tLogAddr = 0;
	uint8_t lpBuf[STORE2_CATALOG_INFO_LEN];	
	
	/* ��Ŀ¼������ݣ���������ʱRAM�� */
	fStoreInfo->Catalog.User.Info.ExtDataLen = ExtDataLen;
	fStoreInfo->Catalog.Flash.Info.Mark = eCatalogMarkSealed;
	memcpy(lpBuf, fStoreInfo->Catalog.Flash.Buf, STORE2_CATALOG_FLASH_INFO_LEN);	// �洢��Ϣ
	memcpy(lpBuf+STORE2_CATALOG_FLASH_INFO_LEN, fStoreInfo->Catalog.User.Buf, STORE2_CATALOG_USER_INFO_LEN);		// �û���Ϣ
	if(NULL != ExtDataBuf)
	{
		memcpy(lpBuf+STORE2_CATALOG_FLASH_INFO_LEN+STORE2_CATALOG_USER_INFO_LEN, ExtDataBuf, ExtDataLen);	// ������Ϣ
	}
	
	/* Ŀ¼��Ϣ����FLASH */
	tLogAddr = Store_Algo_CatalogAddrGet(fStoreInfo, fStoreInfo->CatalogSerialEnd);
	Mid_NandFlash_Write(lpBuf, tLogAddr, STORE2_CATALOG_INFO_LEN);	
	
	/* ���״η�棬��ʼ����ʼĿ¼��� */
	if(0 == fStoreInfo->CatalogSerialCnt)
	{
		fStoreInfo->CatalogSerialBegin = fStoreInfo->CatalogSerialEnd;
	}
	
	/* ������Ŀ¼���洢����ɾ����ʼĿ¼ */
	if(fStoreInfo->CatalogSerialCnt >= fStoreInfo->CatalogSerialMax)
	{
		Store_Algo_CatalogMark(fStoreInfo, fStoreInfo->CatalogSerialBegin, eCatalogMarkCover);	// ���Ŀ¼������
		fStoreInfo->CatalogSerialBegin = Store_Algo_NextCatalogGet(fStoreInfo, fStoreInfo->CatalogSerialBegin);	// ��ʼĿ¼˳��		
	}
	else
	{
		fStoreInfo->CatalogSerialCnt++;
	}	
	
	fStoreInfo->Status = eStoreStatusNull;	
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : ��ȡ������Ϣ��������FLASH����ѭ����ȡ
 * Input : @fStoreInfo �洢��Ϣ�ṹ�壬����ȡ����������
           @fCatalogInfo Ŀ¼��Ϣ�ṹ�壬����ȡ��Ŀ¼
           @Offset ƫ�Ƶ�ַ
		   @DataBuf ����ָ��
           @DataLen ���ݳ���
 * Return: 
 * Call  : 
 ***************/
uint16_t Store_Algo_DataRead(StoreInfo_t* fStoreInfo, CatalogInfo_t* fCatalogInfo, uint32_t Offset, uint8_t* DataBuf, uint32_t DataLen)
{
	if((DataLen+Offset) > fCatalogInfo->Flash.Info.DataLen) drERROR_CHECK_RETURN_ERR("Store_Algo_DataRead", Ret_InvalidParam);
	
	uint32_t lRemainReadLen;	// ʣ��FLASH�ɶ����ݳ���
	uint32_t lOverReadLen;		// ����FLASH�������ݳ���	
	uint32_t lAddr;
	
	/* ѭ����д�㷨��ע��߽紦�� */
	if((fCatalogInfo->Flash.Info.DataAddr + Offset - 1) > fStoreInfo->DataEndAddr)
	/* ���ݵ�ַ+ƫ�Ƶ�ַ����End��ַ������ѭ����ַ��һ���Զ�ȡ */
	{
		STORE_ALGO_RTT_WARN(0, "[WARN] Store_Algo_DataRead Begin 0x%X \n", (fCatalogInfo->Flash.Info.DataAddr + Offset - 1));
		lAddr = Offset - (fStoreInfo->DataEndAddr - fCatalogInfo->Flash.Info.DataAddr + 1); 	// ����ѭ�����ƫ�Ƶ�ַ
		Mid_NandFlash_Read(DataBuf, fStoreInfo->DataBeginAddr + lAddr, DataLen);
	}
	else if((fCatalogInfo->Flash.Info.DataAddr + Offset + DataLen - 1) > fStoreInfo->DataEndAddr)
	/* ���ݵ�ַ+ƫ�Ƶ�ַ+��ȡ���ȳ���End��ַ���ֿ���ȡ */
	{
		STORE_ALGO_RTT_WARN(0, "[WARN] Store_Algo_DataRead Split 0x%X \n", (fCatalogInfo->Flash.Info.DataAddr + Offset + DataLen - 1));
		
		lRemainReadLen = fStoreInfo->DataEndAddr - (fCatalogInfo->Flash.Info.DataAddr + Offset) + 1;
		lOverReadLen = DataLen - lRemainReadLen;
		
		/* �Ȱ�ʣ��FLASH������� */
		Mid_NandFlash_Read(DataBuf, fCatalogInfo->Flash.Info.DataAddr+Offset, lRemainReadLen);
		
		/* ��������ѭ����FLASHͷ����ȡ */
		Mid_NandFlash_Read(DataBuf+lRemainReadLen, fStoreInfo->DataBeginAddr, lOverReadLen);
	}
	else
	/* ����һ���Զ�ȡ */
	{
		Mid_NandFlash_Read(DataBuf, fCatalogInfo->Flash.Info.DataAddr+Offset, DataLen);
	}

	return Ret_OK;
}

/*
 *  �ָ��㷨��4�������������6��Ŀ¼��3����Ҫ�ָ���
 *  1, Y Y Y N N N
    2, N N Y Y Y N
    3, N N N Y Y Y 
    4, Y N N N Y Y
	1����ȡ��Ŀ¼��βĿ¼�������Ƿ���Ҫ�ָ�
		����β����Ŀ¼��Ҫ�ָ���˵�����ָ�Ŀ¼��β����
		����˵�����ָ�Ŀ¼û��β����

	�ָ�ԭ��
	����쳣���磬����������������д�뵫��û�з��Ŀ¼���ᱻ��Ⱦ�㷨���˵�
 */
uint16_t Store_Algo_CatalogRecover(StoreInfo_t* fStoreInfo)
{
	bool tRecoverFlg = false;	// ��������Ҫ�ָ���־
	bool lFirstFlg = false, lLastFlg = false; // ��βĿ¼��Ч��־
	uint32_t tCatalog0 ,tCatalog1;
	CatalogInfo_t lCatalogInfo;
	
	/* �����Ŀ¼�Ƿ���Ч */
	Store_Algo_CatalogRead(fStoreInfo, 0, &lCatalogInfo);
	if((eCatalogMarkSealed == lCatalogInfo.Flash.Info.Mark) || 
	    (eCatalogMarkUpload == lCatalogInfo.Flash.Info.Mark) || 
		(eCatalogMarkIgnore == lCatalogInfo.Flash.Info.Mark))
	{
		lFirstFlg = true;
	}
	
	/* ���βĿ¼�Ƿ���Ч */
	Store_Algo_CatalogRead(fStoreInfo, (fStoreInfo->CatalogSerialMax-1), &lCatalogInfo);
	if((eCatalogMarkSealed == lCatalogInfo.Flash.Info.Mark) || 
	    (eCatalogMarkUpload == lCatalogInfo.Flash.Info.Mark) || 
		(eCatalogMarkIgnore == lCatalogInfo.Flash.Info.Mark))
	{
		lLastFlg = true;
	}
	
	if(lFirstFlg && lLastFlg)
	/* ����β����ָ���˵����β���� */
	{
		/* ��ͷ��Ѱ��CatalogEnd����Ŀ¼���Ǵ��ָ����ͣ�˵���ҵ��� */
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
				break;	// ��Ŀ¼����Ҫ�ָ���˵��EndĿ¼���ҵ����˳�ѭ��
			}			
		}

		/* ��β��Ѱ��CatalogBegin����Ŀ¼���Ǵ��ָ����ͣ�˵���ҵ��� */
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
				break;	// ��Ŀ¼����Ҫ�ָ���˵��BeginĿ¼���ҵ����˳�ѭ��
			}			
		}
		
		fStoreInfo->CatalogSerialCnt = (fStoreInfo->CatalogSerialMax - fStoreInfo->CatalogSerialBegin) + 
								(fStoreInfo->CatalogSerialEnd + 1);
		
		/* �ָ���������ǰ��ַ��ע�������쳣�������������»ָ���DataCurrAddr��
			��Ⱦ����д������ʱ��ʹ����Ⱦ�㷨���д������Բ�Ҫ���� */
		Store_Algo_CatalogRead(fStoreInfo, fStoreInfo->CatalogSerialEnd, &lCatalogInfo);
		fStoreInfo->DataCurrAddr = (lCatalogInfo.Flash.Info.DataAddr + lCatalogInfo.Flash.Info.DataLen);
	}
	else
	/* ���ݻָ���δ����β */
	{
		for(uint32_t i = 0;i < fStoreInfo->CatalogSerialMax;i++)	// ��������Ŀ¼
		{
			Store_Algo_CatalogRead(fStoreInfo, i, &lCatalogInfo);
			if((eCatalogMarkSealed == lCatalogInfo.Flash.Info.Mark) || 
				(eCatalogMarkUpload == lCatalogInfo.Flash.Info.Mark) || 
				(eCatalogMarkIgnore == lCatalogInfo.Flash.Info.Mark))
			{
				if(false == tRecoverFlg)
				{
					tRecoverFlg = true;
					tCatalog0 = i;		// �ҵ���ʼĿ¼
					tCatalog1 = i;
				}
				else
				{
					tCatalog1 = i;		// ����Ŀ¼
				}
			}
			else
			{
				/* tRecoverFlg = true ˵�������ݻָ����ҿ�ʼ/����Ŀ¼�������ֵ
					��������ݻָ�������һ��Ŀ¼���Ǵ��ָ�Ŀ¼��˵����βĿ¼�����ҵ����˳����� */
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
			
			/* �ָ���������ǰ��ַ��ע�������쳣�������������»ָ���DataCurrAddr��
				��Ⱦ����д������ʱ��ʹ����Ⱦ�㷨���д������Բ�Ҫ���� */
			Store_Algo_CatalogRead(fStoreInfo, fStoreInfo->CatalogSerialEnd, &lCatalogInfo);
			fStoreInfo->DataCurrAddr = (lCatalogInfo.Flash.Info.DataAddr + lCatalogInfo.Flash.Info.DataLen);			
		}
	}
	
	/* ���ָ���Ŀ¼��������������������Ŀ¼�������ش��� */
	if(fStoreInfo->CatalogSerialCnt > fStoreInfo->CatalogSerialMaxSave) 
		drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogRecover", Ret_Fail);
	
	/* ��CatalogSerialEnd����һĿ¼����Ⱦ�������ش��� */
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
 * Brief : ��ȡĿ¼��Ϣ��������������Ϣ
 * Input : @fStoreInfo �洢��Ϣ�ṹ��
           @CatalogSerial Ŀ¼�������
           @CatalogInfo Ŀ¼��Ϣ�ṹ��
 * Return: 
 * Call  : 
 ***************/
uint16_t Store_Algo_CatalogRead(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial, CatalogInfo_t* CatalogInfo)
{
	if(CatalogSerial >= fStoreInfo->CatalogSerialMax) drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogRead", CatalogSerial);
	
	uint32_t tLogAddr;
	
	tLogAddr = Store_Algo_CatalogAddrGet(fStoreInfo, CatalogSerial);
	
	// ��ȡĿ¼��Ϣ
	Mid_NandFlash_Read((uint8_t*)CatalogInfo, tLogAddr, sizeof(CatalogInfo_t));	
	
	return Ret_OK;
}

/*******************************************************************************
 * Brief : ��ȡĿ¼������Ϣ
 * Input : @fStoreInfo �洢��Ϣ�ṹ��
           @CatalogSerial Ŀ¼�������
           @DataBuf ���ݴ��ָ��
		   @DataLen ��ȡ����
 * Return: 
 * Call  : 
 ***************/
uint16_t Store_Algo_CatalogExtRead(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial, uint8_t* DataBuf, uint32_t DataLen)
{
	if(CatalogSerial >= fStoreInfo->CatalogSerialMax) drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogExtRead", Ret_InvalidParam);
	if(DataLen > STORE2_CATALOG_EXT_INFO_LEN) drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogExtRead", Ret_InvalidParam);
	
	uint32_t tLogAddr;
	
	tLogAddr = Store_Algo_CatalogAddrGet(fStoreInfo, CatalogSerial);
	
	// Ŀ¼������Ϣ��
	Mid_NandFlash_Read(DataBuf, tLogAddr+STORE2_CATALOG_FLASH_INFO_LEN+STORE2_CATALOG_USER_INFO_LEN, DataLen);	
	
	return Ret_OK;
}

// ָ��Ŀ¼������ϴ�����APP��ɾ��ָ�
uint16_t Store_Algo_CatalogUpload(StoreInfo_t* fStoreInfo, uint32_t CatalogSerial)
{
	if(CatalogSerial >= fStoreInfo->CatalogSerialMax) drERROR_CHECK_RETURN_ERR("Store_Algo_CatalogUpload", Ret_InvalidParam);
	
	Store_Algo_CatalogMark(fStoreInfo, CatalogSerial, eCatalogMarkUpload);
	
	return Ret_OK;
}

// ����Ŀ¼������ϴ�����APP��ɾ��ָ�
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
 * Brief : ����Ѵ�����Ŀ¼��Ϣ�����Ŀ¼Ϊ"����"
 * Input : @fStoreInfo �洢��Ϣ�ṹ��
 * Return: 
 * Call  : 1���˶����ݷ������棻2�������������ϴ���APP
 ***************/
uint16_t Store_Algo_CatalogClear(StoreInfo_t* fStoreInfo)
{
	#if 0	// ����浱ǰĿ¼
	if(eStoreStatusIng == fStoreInfo->Status)
	/* �����ǰĿ¼����ʹ�ã�����Ϊ"����" */
	{
		Store_Algo_CatalogSeal(fStoreInfo, NULL, 0);	// �ȷ���Ŀ¼
		Store_Algo_CatalogMark(fStoreInfo, fStoreInfo->CatalogSerialEnd, eCatalogMarkIgnore);	// �ٰѴ�Ŀ¼markΪ����
	}
	#endif
	
	fStoreInfo->Status = eStoreStatusNull;
	
	return Ret_OK;
}













