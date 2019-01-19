#include "platform_common.h"

#include "mid_common.h"
#include "mid_interface.h"
#include "app_variable.h"
#include "app_protocal.h"
#include "app_remind_manage.h"
#include "ui_screen_warn.h"
#include "app_time.h"

/*******************macro define*******************/
#define 	SECT_END 			0x0000 		//����ν�β�жϷ�

//������Ϣ�б�ṹ��
typedef struct
{
    uint8 u8StoreId;
    uint16 u16MsgId;
}RemindMsgList_t;

static RemindMsg_t	RemindMsg;	
static RemindMsg_t	RemindCall;		// ����������Ϣ����Ϊ�������豣��Ҳû��ɾ�������Ե�������
static RemindMsg_t RemindStore[MSG_STORE_NUM];   //��¼5����Ϣ
static RemindMsgList_t RemidList[MSG_STORE_NUM+1];
static uint8 u8RemindCnt = 0;     //��¼��Ϣ�������ֵ5
static uint16 u16CurrMsgId = 0xFFFF;   //��¼��ǰ��ϢID

static uint16 u16CancleMsgId = 0xFFFF;

uint8_t 	protocalCache[APP_REMIND_MSG_MAX_LENGHT];	// �洢����utf-8��ʽ����������
uint8_t 	protocalCacheCnt;	// �������ݻ�������������� APP_REMIND_MSG_MAX_LENGHT �ֽ�
uint8_t 	flowCnt;			// �������ݰ����ؼ���

//**********************************************************************
// ��������: �ж���Ϣ�������Ƿ���null:null
// �����������
// ���ز�����true:��ϢΪnull
//**********************************************************************
static uint8 App_RemindManag_IsNULL(void)
{
    //0x6E,0x75,0x6C,0x6C,0x3A,0x6E,0x75,0x6C,0x6C
    uint8 u8null[10] = "null:null";
    uint8 u8i,u8j,u8z;

    for(u8i = 0; u8i < protocalCacheCnt; u8i++)
    {
        u8j = 0;
        if(protocalCache[u8i] == u8null[u8j])
        {
            for(u8z = u8i + 1,u8j = 1; u8z < protocalCacheCnt; u8z++,u8j++)
            {
                if(protocalCache[u8z] != u8null[u8j])
                    break;
                //��Ϣ��������null:null
                if(u8j >= 8)
                    return TRUE;
            }
        }
    }
    return FALSE;
}

//**********************************************************************
// ��������:	�������������ֵ�UTF-8���볤��
// ���������	pInput: UTF-8����
// ���ز�����	��
static int16_t GetSingleUTF8CodeLen(const uint8_t pInput)
{
	unsigned char c = pInput;
	// 0xxxxxxx ����0
	// 10xxxxxx ������
	// 110xxxxx ����2
	// 1110xxxx ����3
	// 11110xxx ����4
	// 111110xx ����5
	// 1111110x ����6
	if(c< 0x80) return 0;
	if(c>=0x80 && c<0xC0) return -1;
	if(c>=0xC0 && c<0xE0) return 2;
	if(c>=0xE0 && c<0xF0) return 3;
	if(c>=0xF0 && c<0xF8) return 4;
	if(c>=0xF8 && c<0xFC) return 5;
	if(c>=0xFC) return 6;
	return -1;
}
	
//**********************************************************************
// ��������:	��һ���ַ���UTF8����ת����Unicode(UCS-2��UCS-4)����
// ���������	UTF8code��  ��UTF-8����������
//				Unicode��   ת�����ɵ�Unicode����
// ���ز�����	�ɹ��򷵻ظ��ַ���UTF8������ռ�õ��ֽ���; ʧ���򷵻�0. 
// * ע��: 
// *     1. UTF8û���ֽ�������, ����Unicode���ֽ���Ҫ��; 
// *        �ֽ����Ϊ���(Big Endian)��С��(Little Endian)����; 
// *        ��Intel�������в���С�˷���ʾ, �ڴ˲���С�˷���ʾ. (�͵�ַ���λ) 
static uint16_t SINGLE_UTF8_TO_UNICODE(const uint8_t* UTF8code, uint16_t *Unicode)  
{
//    assert(pInput != NULL && Unic != NULL);  
  
    // b1 ��ʾUTF-8�����pInput�еĸ��ֽ�, b2 ��ʾ�θ��ֽ�, ...  
	char b1, b2, b3, b4, b5, b6;  
  
    *Unicode = 0x0; // �� *Unic ��ʼ��Ϊȫ��  
    int utfbytes = GetSingleUTF8CodeLen(*UTF8code);  
    unsigned char *pOutput = (unsigned char *) Unicode;  
  
	switch ( utfbytes )  
    {  
		case 0:  
        *pOutput     = *UTF8code;  
        utfbytes    += 1;  
        break;  

        case 2:  
        b1 = *UTF8code;  
        b2 = *(UTF8code + 1);  
        if ( (b2 & 0xE0) != 0x80 )  
            return 0;  
        *pOutput     = (b1 << 6) + (b2 & 0x3F);  
        *(pOutput+1) = (b1 >> 2) & 0x07;  
        break;  

        case 3:  
        b1 = *UTF8code;  
        b2 = *(UTF8code + 1);  
        b3 = *(UTF8code + 2);  
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80) )  
            return 0;  
        *pOutput     = (b2 << 6) + (b3 & 0x3F);  
        *(pOutput+1) = (b1 << 4) + ((b2 >> 2) & 0x0F);  
        break;  

        case 4:  
        b1 = *UTF8code;  
        b2 = *(UTF8code + 1);  
        b3 = *(UTF8code + 2);  
        b4 = *(UTF8code + 3);  
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)  
                || ((b4 & 0xC0) != 0x80) )  
            return 0;  
        *pOutput     = (b3 << 6) + (b4 & 0x3F);  
        *(pOutput+1) = (b2 << 4) + ((b3 >> 2) & 0x0F);  
        *(pOutput+2) = ((b1 << 2) & 0x1C)  + ((b2 >> 4) & 0x03);  
        break;  

        case 5:  
        b1 = *UTF8code;  
        b2 = *(UTF8code + 1);  
        b3 = *(UTF8code + 2);  
        b4 = *(UTF8code + 3);  
        b5 = *(UTF8code + 4);  
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)  
                || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80) )  
            return 0;  
        *pOutput     = (b4 << 6) + (b5 & 0x3F);  
        *(pOutput+1) = (b3 << 4) + ((b4 >> 2) & 0x0F);  
        *(pOutput+2) = (b2 << 2) + ((b3 >> 4) & 0x03);  
        *(pOutput+3) = (b1 << 6);  
        break; 

        case 6:  
        b1 = *UTF8code;  
        b2 = *(UTF8code + 1);  
        b3 = *(UTF8code + 2);  
        b4 = *(UTF8code + 3);  
        b5 = *(UTF8code + 4);  
        b6 = *(UTF8code + 5);  
        if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)  
                || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80)  
                || ((b6 & 0xC0) != 0x80) )  
            return 0;  
        *pOutput     = (b5 << 6) + (b6 & 0x3F);  
        *(pOutput+1) = (b5 << 4) + ((b6 >> 2) & 0x0F);  
        *(pOutput+2) = (b3 << 2) + ((b4 >> 4) & 0x03);  
        *(pOutput+3) = ((b1 << 6) & 0x40) + (b2 & 0x3F);  
        break;  

        default:  
        return 0;  
//            break;  
    }   
    return utfbytes;  
}

//**********************************************************************
// ��������: �����µ���Ϣ�����ӵ���ʷ��Ϣ�б���
// ���������
// ���ز�����	
//**********************************************************************
static void App_RemindManag_Store(void)
{
    uint8 u8index =0;
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();

#if 0
    SEGGER_RTT_printf(0,"u8RemindCnt=%d\n",u8RemindCnt);
    for(u8index =0; u8index < u8RemindCnt; u8index++)
        SEGGER_RTT_printf(0,"list %d: store=%d,msg=%d\n",u8index,RemidList[u8index].u8StoreId,RemidList[u8index].u16MsgId);
#endif

    //list��0~4��ʾ��Ϣ���µ���
    for(u8index = u8RemindCnt; u8index > 0; u8index--)
    {
        RemidList[u8index].u16MsgId = RemidList[u8index - 1].u16MsgId;
        RemidList[u8index].u8StoreId = RemidList[u8index - 1].u8StoreId;
    }

    //����RemindStore���ĸ����������������
    //������Ϊ5�����򸲸���ɵ���Ϣ��������µ���Ч��������
    if(u8RemindCnt == MSG_STORE_NUM)
    {
        u8index = RemidList[MSG_STORE_NUM].u8StoreId;
    }
    else
    {
        for(u8index = 0; u8index < MSG_STORE_NUM; u8index++)
        {
            if(RemindStore[u8index].RemindType == INVALID_MESAGE)
            {
                break;
            }
        }
    }

    if(u8index >= MSG_STORE_NUM)
    {
        Err_Info((0,"Error: remid list is wrong!!\n"));
        return;
    }

    //����ǰ����Ϣ��Ϣ copy����ʷ��Ϣ��
	memcpy(&RemindMsg.RTC, &lMidRTC->RTC, sizeof(rtc_time_s));
    RemindMsg.u16MsgID = u16CurrMsgId;
	memcpy(&RemindStore[u8index], &RemindMsg, sizeof(RemindMsg_t));

    //RemidList�е�һ�����ݼ�¼������Ϣ����Ϣ��ͨ��RemidList��msg id�ʹ洢λ�ù�������
    RemidList[0].u16MsgId = u16CurrMsgId;
    RemidList[0].u8StoreId = u8index;
    //u8RemindCnt��Ϣ�������Ϊ5
    u8RemindCnt++;
    if(u8RemindCnt >= 5)
    {
        u8RemindCnt = 5;
    }
}

// ��ȡ�洢��������Ϣ
uint16_t App_RemindManag_StoreGet(uint8_t Serial, RemindMsg_t* tRemindMsg)
{
#if 0  //��û����

	if(Serial >= RemindStore.RemindCnt)
		return 0xFF;
	
	memcpy(tRemindMsg, &RemindStore.RemindMsg[(RemindStore.FirstPos+Serial)%5], sizeof(RemindMsg_t));
	
#endif
	return 0;
}


//**********************************************************************
// ��������:	�����������
// ���������	��
// ���ز�����	��
static void App_RemindManage_CallProcess(uint8 phoneSystem)
{
	//uint8_t 	phoneType;
	uint8_t 	utfbytesIndex 	= 0;
	uint16_t 	utfbytes;//,utfbytes1,utfbytes2;
	uint16_t 	unicodeTemp;//,unicodeTemp1,unicodeTemp2;
	uint8_t 	endFlagNum = 0;

    //fix:����յ�ͬһ���绰ʱ�����������������ظ������
    memset(&RemindCall.Detail.PhoneCall,0,sizeof(PhoneCallDetail_t));
    //fix:2019.1.12

	if (phoneSystem == IOS)
	{
		if (*(protocalCache + utfbytesIndex) == 0xE2)	//�ɣϣӺ���ǰ����2��80������
		{
			utfbytesIndex += 3;
		}
	}

	for(;;)
	{
		if (utfbytesIndex >= protocalCacheCnt)
		{
			break;
		}
		utfbytes 	 = SINGLE_UTF8_TO_UNICODE((const uint8_t*)(protocalCache + utfbytesIndex),&unicodeTemp);  

		if(utfbytes == 0)//�쳣����
			break;

		switch(endFlagNum)
		{
			case 0://����
				if (utfbytes == 1 && (unicodeTemp == SECT_END))//���ַ�
				{
					endFlagNum += 1;
				}
				else
				{
					RemindCall.Detail.PhoneCall.name[RemindCall.Detail.PhoneCall.namelen++] = unicodeTemp;
				}
				break;
			case 1:	//����-����绰
				if (utfbytes == 1 && (unicodeTemp == SECT_END))//���ַ�
				{
					endFlagNum += 1;
				}
				else
				{
					RemindCall.Detail.PhoneCall.detail[RemindCall.Detail.PhoneCall.detaillen++] = unicodeTemp;
				}
				break;
			case 2: break;	//������
			default: break;
		}
		utfbytesIndex 	+= utfbytes;
	}
	
	APP_REMIND_RTT_LOG(0, "PHONE_FAMILIAR \r\n");
	
	#if 1	// debug
	// ��ϵ������
	for(uint32_t t = 0; t < RemindCall.Detail.PhoneCall.namelen;t++)
	{
		APP_REMIND_RTT_LOG(0,"\\u%04X", RemindCall.Detail.PhoneCall.name[t]);
	}APP_REMIND_RTT_LOG(0,"\r\n");
	
	// ��Ϣ���ݣ�����绰
	for(uint32_t t = 0; t < RemindCall.Detail.PhoneCall.detaillen;t++)
	{
		APP_REMIND_RTT_LOG(0,"\\u%04X", RemindCall.Detail.PhoneCall.detail[t]);
	}APP_REMIND_RTT_LOG(0,"\r\n");				
	#endif	

	UI_Screen_Show_Warn_Screen_Call();
	Mid_Motor_ShakeStart(eMidMotorShake2Hz, 5);
}

//**********************************************************************
// ��������:	δ�������������
// ���������	��
// ���ز�����	��
// ע����Щ��׿�ֻ��ղ���δ����������
static void App_RemindManage_MissCallProcess(uint8 phoneSystem)
{
	//uint8_t 	phoneType;
	uint8_t 	utfbytesIndex 	= 0;
	uint16_t 	utfbytes;//,utfbytes1,utfbytes2;
	uint16_t 	unicodeTemp;//,unicodeTemp1,unicodeTemp2;
	uint8_t 	endFlagNum = 0;	

	if (phoneSystem == IOS)
	{
		if (*(protocalCache + utfbytesIndex) == 0xE2)//�ɣϣӺ���ǰ����2��80������
		{
			utfbytesIndex += 3;
		}
	}

	for(;;)
	{
		if (utfbytesIndex >= protocalCacheCnt)
		{
			break;
		}
		utfbytes 	 = SINGLE_UTF8_TO_UNICODE((const uint8_t*)(protocalCache + utfbytesIndex),&unicodeTemp); 

		if(utfbytes == 0)//�쳣����
			break;

		switch(endFlagNum)
		{
			case 0://����
				if (utfbytes == 1 && (unicodeTemp == SECT_END))//���ַ�
				{
					endFlagNum += 1;
				}
				else
				{
					RemindMsg.Detail.PhoneMiss.name[RemindMsg.Detail.PhoneMiss.namelen++] = unicodeTemp;
//							appRemindMsg.remindMsg.name[appRemindMsg.remindMsg.namelen++] = unicodeTemp;
				}	    		
				break;
			case 1://����-����绰
				if (utfbytes == 1 && (unicodeTemp == SECT_END))//���ַ�
				{
					endFlagNum += 1;
				}
				else
				{
					RemindMsg.Detail.PhoneMiss.detail[RemindMsg.Detail.PhoneMiss.detaillen++] = unicodeTemp;
//							appRemindMsg.remindMsg.content.u.detail[appRemindMsg.remindMsg.content.u.detaillen++] = unicodeTemp;
				}
				break;
			case 2: break;
			default: break;
		}
		utfbytesIndex 	+= utfbytes;
	}
	
	APP_REMIND_RTT_LOG(0, "PHONE_FAMILIAR \r\n");
	
	#if 1	// debug
	// ��ϵ������
	for(uint32_t t = 0; t < RemindMsg.Detail.PhoneMiss.namelen;t++)
	{
		APP_REMIND_RTT_LOG(0,"\\u%04X", RemindMsg.Detail.PhoneMiss.name[t]);
	}APP_REMIND_RTT_LOG(0,"\r\n");
	
	// ��Ϣ���ݣ�����绰
	for(uint32_t t = 0; t < RemindMsg.Detail.PhoneMiss.detaillen;t++)
	{
		APP_REMIND_RTT_LOG(0,"\\u%04X", RemindMsg.Detail.PhoneMiss.detail[t]);
	}APP_REMIND_RTT_LOG(0,"\r\n");				
	#endif		

	App_RemindManag_Store();
	UI_Screen_Show_Warn_Screen_Message();	
}

//**********************************************************************
// ��������:	������Ϣ��������
// ���������	��
// ���ز�����	��
static void App_RemindManage_MessgeProcess(uint8 phoneSystem)
{
	
	// ��ϵ�˺͵绰���빫��ram�����ķ�ʽ
	
	uint8_t 	utfbytesIndex 	= 0;
	uint16_t 	utfbytes;//,utfbytes1,utfbytes2;
	uint16_t 	unicodeTemp;//,unicodeTemp1,unicodeTemp2;
	uint8_t 	endFlagNum = 0;	

	if (phoneSystem == IOS)
	{
		if (*(protocalCache + utfbytesIndex) == 0xE2)//�ɣϣӺ���ǰ����2��80������
		{
			utfbytesIndex += 3;
		}
	}
	
	for(;;)
	{
		if (utfbytesIndex >= protocalCacheCnt)
		{
			break;
		}
		utfbytes 	 = SINGLE_UTF8_TO_UNICODE((const uint8_t*)(protocalCache + utfbytesIndex),&unicodeTemp);   		

		if(utfbytes == 0)//�쳣����
			break;

		switch(endFlagNum)
		{
			case 0:	//����
				if (utfbytes == 1 && (unicodeTemp == SECT_END))//���ַ�
				{
					endFlagNum += 1;
				}
				else
				{
					RemindMsg.Detail.PhoneMsg.name[RemindMsg.Detail.PhoneMsg.namelen++] = unicodeTemp;
					if(RemindMsg.Detail.PhoneMsg.namelen >= APP_REMIND_NANE_MAX_LENGHT)
					{
						endFlagNum += 1;
					}
				}	    		
				break;
			case 1:	//����-��Ϣ����
				if (utfbytes == 1 && (unicodeTemp == SECT_END))//���ַ�
				{
					endFlagNum += 1;
				}
				else
				{
					RemindMsg.Detail.PhoneMsg.detail[RemindMsg.Detail.PhoneMsg.detaillen++] = unicodeTemp;
					if(RemindMsg.Detail.PhoneMsg.detaillen >= APP_REMIND_DATAIL_MAX_LENGHT)
					{
						endFlagNum += 1;
					}
				}
				break;
			case 2: break;
			default: break;
		}
		utfbytesIndex 	+= utfbytes;
	}	
	
	#if 1	// debug
	APP_REMIND_RTT_LOG(0, "PHONE_FAMILIAR \r\n");
	
	// ��ϵ������
	for(uint32_t t = 0; t < RemindMsg.Detail.PhoneMsg.namelen;t++)
	{
		APP_REMIND_RTT_LOG(0,"\\u%04X", RemindMsg.Detail.PhoneMsg.name[t]);
	}APP_REMIND_RTT_LOG(0,"\r\n");
	
	// ��������
	for(uint32_t t = 0; t < RemindMsg.Detail.PhoneMsg.detaillen;t++)
	{
		APP_REMIND_RTT_LOG(0,"\\u%04X", RemindMsg.Detail.PhoneMsg.detail[t]);
	}APP_REMIND_RTT_LOG(0,"\r\n");
	#endif	
	
	App_RemindManag_Store();	
	UI_Screen_Show_Warn_Screen_Message();
	Mid_Motor_ShakeStart(eMidMotorShake2Hz, 2);
}

//**********************************************************************
// ��������:	΢����Ϣ��������
// ���������	��
// ���ز�����	��
static void App_RemindManage_MsgDetailProcess(uint8 phoneSystem,uint8_t msg_type)
{
	uint8_t 	utfbytesIndex 	= 0;
	uint16_t 	utfbytes;
	uint16_t 	unicodeTemp;
	uint8_t 	endFlagNum = 0;
	//uint32_t 	size = 0;

//	//�����Ϣ�ṹ��
//	memset(&RemindMsg,0,sizeof(RemindMsg_t));
	
	for(;;)
	{
		if (utfbytesIndex >= protocalCacheCnt)
		{
			break;
		}
		utfbytes 	 = SINGLE_UTF8_TO_UNICODE((const uint8_t*)(protocalCache + utfbytesIndex),&unicodeTemp);   		
		
		if(utfbytes == 0)	//�쳣����
			break;
		
		switch(endFlagNum)
		{
			case 0:	// Ӧ��������΢�š�QQ��
                switch(msg_type)
                {
                    case WECHAT_MESAGE:
						if (utfbytes == 1 && (unicodeTemp == SECT_END))//ð��
						{
							endFlagNum += 1;
						}
						else
						{
							RemindMsg.Detail.AppMsg.name[RemindMsg.Detail.AppMsg.namelen++] = unicodeTemp;
							if(RemindMsg.Detail.AppMsg.namelen >= APP_REMIND_NANE_MAX_LENGHT)
							{
								endFlagNum += 1;
							}						
						}                   
						break;
                    default:
						if (utfbytes == 1 && (unicodeTemp == SECT_END))//ð��
						{
							endFlagNum += 1;
						}
						else
						{
							RemindMsg.Detail.AppMsg.name[RemindMsg.Detail.AppMsg.namelen++] = unicodeTemp;
							if(RemindMsg.Detail.AppMsg.namelen >= APP_REMIND_NANE_MAX_LENGHT)
							{
								endFlagNum += 1;
							}						
						}
						break;
                } 		
				break;

			case 1://����-��Ϣ����
				if (utfbytes == 1 && (unicodeTemp == SECT_END))//���ַ�
				{
					endFlagNum += 1;
				}
				else
				{
					RemindMsg.Detail.AppMsg.detail[RemindMsg.Detail.AppMsg.detaillen++] = unicodeTemp;
					if(RemindMsg.Detail.AppMsg.detaillen >= APP_REMIND_DATAIL_MAX_LENGHT)
					{
						endFlagNum += 1;
					}				
				}
				break;
			case 2: break;
			default: break;
		}
		utfbytesIndex 	+= utfbytes;
	}

    #if 0
	// ��ӡ��Ϣ����
	for(uint32_t t = 0; t < RemindMsg.Detail.AppMsg.namelen;t++)
	{
		APP_REMIND_RTT_LOG(0,"\\u%04X", RemindMsg.Detail.AppMsg.name[t]);
	}APP_REMIND_RTT_LOG(0,"\r\n");	
	
	// ��ӡ��Ϣ����Unicode����
	for(uint32_t t = 0; t < RemindMsg.Detail.AppMsg.detaillen;t++)
	{
		APP_REMIND_RTT_LOG(0,"\\u%04X", RemindMsg.Detail.AppMsg.detail[t]);
	}APP_REMIND_RTT_LOG(0,"\r\n");
	#endif
    
	/* ֪ͨ�ϲ����Ϣ���ݽ��д��� */	
	App_RemindManag_Store();
	UI_Screen_Show_Warn_Screen_Message();
	Mid_Motor_ShakeStart(eMidMotorShake2Hz, 2);
}

//**********************************************************************
// ��������:	��ʼ��������Ϣ�洢
// ���������	��
// ���ز�����	��
void App_RemindManage_Init(void)
{
    uint8 u8i;

    //��Ϣ���Ͷ���ʼ��Ϊ��Ч
    for(u8i = 0; u8i < MSG_STORE_NUM; u8i++)
        RemindStore[u8i].RemindType = 0xFF;
}

//**********************************************************************
// ��������:	δ������������Ϣ��������ȡ
// ��������� 	msgClassify��       ��Ϣ����
// 				listNum�� 			��Ϣ��ţ���¼���ݽ��յ����Ⱥ�˳���1��ʼ���
// ���ز�����	��

void App_RemindManage_MissRemindSumRead(uint32_t msgClassify,uint8_t *listSumNum)
{

}

//**********************************************************************
// ��������:	������Ϣ��ȡ
// ���������	dailyMissRemindMsg: �洢��Ϣ�Ľṹ��
// 				msgClassify��       ��Ϣ����
// 				listNum�� 			��Ϣ��ţ���¼���ݽ��յ����Ⱥ�˳���1��ʼ���
// ���ز�����	��

void App_RemindManage_MissRemindRead(app_remind_msg_t *dailyMissRemindMsg,uint32_t msgClassify,uint8_t listNum)
{
//	if (msgClassify > REMIND_CLASSIFY_NUM)
//	{
//		return;
//	}

//	if (misssRemindNum[msgClassify] == 0)
//	{
//		return;
//	}

//	if (listNum == 0 || listNum > APP_REMIND_MSG_MAX_LIST)
//	{
//		return;
//	}

//	Mid_RemindMsg_Read(dailyMissRemindMsg->data,misssRemindCatalog[msgClassify][listNum - 1],msgClassify);	
}

//**********************************************************************
// ��������:	ɾ��һ��������Ϣ
// ���������	msgClassify: ɾ��������
// 				listnum�� 	 ɾ���ı�ţ���¼���ݽ��յ����Ⱥ�˳���1��ʼ���
// ���ز�����	��

void App_RemindManage_MissRemindDelete(uint32_t msgClassify,uint8_t listnum)
{
//	uint8_t 	i;

//	if (msgClassify > REMIND_CLASSIFY_NUM)
//	{
//		return;
//	}

//	if (misssRemindNum[msgClassify] == 0)
//	{
//		return;
//	}

//	if (listnum == 0)
//	{
//		return;
//	}
//	//Ŀ¼����
//	for (i = listnum - 1; i < misssRemindNum[msgClassify] - 1; ++i)
//	{
//		misssRemindCatalog[msgClassify][i] 	= misssRemindCatalog[msgClassify][i + 1];
//	}
//	misssRemindCatalog[msgClassify][i] 		= 0;
//	misssRemindNum[msgClassify] 			-= 1;	
}

//**********************************************************************
// ��������:	��ȡ��ǰ�����������Ϣ
// ���������	protocal�� Э������
// ���ز�����	��
//*********************************************************************
void App_RemindManage_DetailRemindRead(RemindStore_t* tRemindStore)
{
    uint8 u8cnt;

    if(tRemindStore != NULL)
    {
        tRemindStore->FirstPos =0;
        tRemindStore->RemindCnt = u8RemindCnt;
        //Err_Info((0,"\nDetailRemindRead = %d\n",u8RemindCnt));
        for(u8cnt = 0; u8cnt < u8RemindCnt; u8cnt++)
        {
    	    memcpy(&tRemindStore->RemindMsg[u8cnt], &RemindStore[RemidList[u8cnt].u8StoreId], sizeof(RemindMsg_t));
        }
    }
}

//**********************************************************************
// ��������:	��ȡ����һ��������Ϣ
// ���������	ftRemindMsg:ָ����Ϣ
// ���ز�����	��
//*********************************************************************
void App_RemindManage_CurrDetailRead(RemindMsg_t* ftRemindMsg)
{
    if(ftRemindMsg != NULL)
    {
        //��Ϣȡ��ʱ���ὫRemindType�ó���Ч��RemindType��Чʱ��copy����
        ftRemindMsg->RemindType = INVALID_MESAGE;
        //fix:������Ϣ�б������µ�һ����Ϣ���������һ����������յ�������Ϣ���ڼ�ʱ������ɾ����Ϣ������
        if(RemindStore[RemidList[0].u8StoreId].RemindType != INVALID_MESAGE)
        {
            memcpy(ftRemindMsg, &RemindStore[RemidList[0].u8StoreId], sizeof(RemindMsg_t));
        }
        //fix:2018.11.19
    }
}

//**********************************************************************
// ��������:	��ȡ��ǰ������Ϣ
// ���������	ftRemindMsg:ָ����Ϣ
// ���ز�����	��
//*********************************************************************
void App_RemindManage_CurrCallRead(RemindMsg_t* ftRemindMsg)
{
	memcpy(ftRemindMsg, &RemindCall, sizeof(RemindMsg_t));
}


//**********************************************************************
// ��������:	������Ϣ���������Ȱ����ݴ���CACHE
// ���������	protocal�� Э������
// ���ز�����	��
// ���ã��յ�app������Ϣ�ǵ���һ��
void App_RemindManage_Process(protocal_msg_t protocal,uint8 phoneSystem)
{
	static uint8_t firstPackFlag = 1;
	
	switch(protocal.att.load.content.parameter[1])
	{
		case FLOW_END:
			if (firstPackFlag)//ֻ��һ�������������ر���
			{
				memset(protocalCache,0,APP_REMIND_MSG_MAX_LENGHT);
				flowCnt 			= 0;
				protocalCacheCnt 	= 0;
			}
			
			for(uint8_t i = 2; i <= protocal.att.loadLength - 4; i ++)
			{
				if (protocalCacheCnt >= APP_REMIND_MSG_MAX_LENGHT)
				{
					break;
				}
				protocalCache[protocalCacheCnt] = protocal.att.load.content.parameter[i];
				protocalCacheCnt ++;    
			}
			firstPackFlag = 1;	//���յ�β������һ�ν���ӦΪ��һ�ΰ���ʼ

			//fix :�����Ϣ��������Ч�ģ��Ͳ���ʾ,�������ʾ"null:null"
			if(App_RemindManag_IsNULL() == TRUE)
				return;
			//fix: 2018.6.26

			// utf-8����ԭʼ���ݴ�ӡ
			for(uint32_t t = 0; t < protocalCacheCnt;t++)
			{
				APP_REMIND_RTT_LOG(0,"%02X ",protocalCache[t]);
			}APP_REMIND_RTT_LOG(0,"\r\n");
			
			/* ��վ����ݣ�����������ݲ���Ӱ�� */
			memset(&RemindMsg, 0x00, sizeof(RemindMsg_t));
			RemindMsg.RemindType = protocal.att.load.content.parameter[0];
//			APP_REMIND_RTT_LOG(0,"RemindMsg.RemindType %d", RemindMsg.RemindType);
			
			switch(protocal.att.load.content.parameter[0])//��Ϣ�����꣬�ֱ�������
			{
				case PHONE_CALL_IN:					
				case FAMILIAR_PHONE_CALL:	// ��������
					App_RemindManage_CallProcess(phoneSystem);
					break;
				case MISS_PHONE_CALL:		// δ����������
					App_RemindManage_MissCallProcess(phoneSystem);	// ���ְ�׿�ֻ��ղ���
					break;
				case PHONE_MESSAGE:			// ��������
					App_RemindManage_MessgeProcess(phoneSystem);
					break;
				case TIM_MESAGE:
				case WECHAT_MESAGE:
				case QQ_MESAGE:
					App_RemindManage_MsgDetailProcess(phoneSystem,protocal.att.load.content.parameter[0]);
					break;
				default:
					App_RemindManage_MsgDetailProcess(phoneSystem,protocal.att.load.content.parameter[0]);
					break;
			}
			break;
		case FLOW_START://����ǵ�һ�����ݣ���0������
			memset(protocalCache,0,APP_REMIND_MSG_MAX_LENGHT);
			flowCnt 			= 0;
			protocalCacheCnt 	= 0;
			firstPackFlag 		= 0;//�װ����յ������ʶ
		default:	//ֻ�������뻺��		
			if (flowCnt != protocal.att.load.content.parameter[1])
			{
				return;
			}

			for(uint8_t i = 2; i <= protocal.att.loadLength - 4; i ++)
			{	
				if (protocalCacheCnt >= APP_REMIND_MSG_MAX_LENGHT)
				{
					break;
				}
				protocalCache[protocalCacheCnt] = protocal.att.load.content.parameter[i];
				protocalCacheCnt ++;    
			}
			flowCnt ++;
			break;
	}
}

//**********************************************************************
// ��������:	������Ϣ���������Ȱ����ݴ���CACHE
// ���������	protocal�� Э������
// ���ز�����	��

//**********************************************************************
void App_RemindManage_Process_New(protocal_msg_t protocal,uint8 phoneSystem)
{
	uint8_t 	i;
    
	static uint8_t firstPackFlag = 1;
	//uint16_t 	ret;
 	//uint32_t 	catalogStartAddrTemp = 0;

	switch(protocal.att.load.content.parameter[3])
    {
    case FLOW_END:
		if (firstPackFlag)//ֻ��һ�������������ر���
		{
			memset(protocalCache,0,APP_REMIND_MSG_MAX_LENGHT);
			flowCnt 			= 0;
			protocalCacheCnt 	= 0;
		}
		for(i = 4; i < protocal.att.loadLength - 3; i ++)
		{
			if (protocalCacheCnt >= APP_REMIND_MSG_MAX_LENGHT)
			{
				break;
			}
			protocalCache[protocalCacheCnt] = protocal.att.load.content.parameter[i];
			protocalCacheCnt++;
		}
		firstPackFlag = 1;	//���յ�β������һ�ν���ӦΪ��һ�ΰ���ʼ

        //fix :�����Ϣ��������Ч�ģ��Ͳ���ʾ,�������ʾ"null:null"
        if(App_RemindManag_IsNULL() == TRUE)
            return;
        //fix: 2018.6.26

        /* ��վ����ݣ�����������ݲ���Ӱ�� */
        memset(&RemindMsg, 0x00, sizeof(RemindMsg_t));
        RemindMsg.RemindType = protocal.att.load.content.parameter[0];
//          APP_REMIND_RTT_LOG(0,"RemindMsg.RemindType %d", RemindMsg.RemindType);

		switch(protocal.att.load.content.parameter[0])//��Ϣ�����꣬�ֱ�������
		{
			case PHONE_CALL_IN:
			case FAMILIAR_PHONE_CALL:
			App_RemindManage_CallProcess(phoneSystem);
			break;

			case MISS_PHONE_CALL:
			App_RemindManage_MissCallProcess(phoneSystem);
            //fix :��δ�����磬��timeģʽ��δ��ʾδ������ͼ��
            //App_Remind_Win_MissCallAdd();
            //fix :2018.7.16
			break;
			case PHONE_MESSAGE:
			App_RemindManage_MessgeProcess(phoneSystem);
			break;
            
            case TIM_MESAGE:
			case WECHAT_MESAGE:
			case QQ_MESAGE:
			App_RemindManage_MsgDetailProcess(phoneSystem,protocal.att.load.content.parameter[0]);
			break;

			default:
			App_RemindManage_MsgDetailProcess(phoneSystem,protocal.att.load.content.parameter[0]);
			break;
		}	
		break;

    case FLOW_START://����ǵ�һ�����ݣ���0������
		memset(protocalCache,0,APP_REMIND_MSG_MAX_LENGHT);
		flowCnt 			= 0;
		protocalCacheCnt 	= 0;
		firstPackFlag 		= 0;//�װ����յ������ʶ
		u16CurrMsgId = ((uint16)protocal.att.load.content.parameter[1] << 8) + protocal.att.load.content.parameter[2];

    default://ֻ�������뻺��		
		if (flowCnt != protocal.att.load.content.parameter[3])
		{
			return;
		}

		for(i = 4; i < protocal.att.loadLength - 3; i ++)
		{	
			if (protocalCacheCnt >= APP_REMIND_MSG_MAX_LENGHT)
			{
				break;
			}
			protocalCache[protocalCacheCnt] = protocal.att.load.content.parameter[i];
			protocalCacheCnt ++;
		}
		flowCnt ++;
		break;
	}
}

//**********************************************************************
// ��������: ȡ��u16MsgIdָ������Ϣ������Ϣ��������ʷ��Ϣ��Ҳ�����ǵ�ǰ���µ���Ϣ
// ���������u16MsgId��ϢID 
// ���ز�����	
//**********************************************************************
void App_RemindManage_Cancel(uint16 u16MsgId)
{
#if 1
    u16CancleMsgId = u16MsgId;
//    UI_Screen_Test_App_Show();
#else
    uint8 u8index =0, i;

    //����Ϣ����ȡ��
    if(u8RemindCnt == 0)
    {
        Err_Info((0,"Warning: no msg remind can be canceled\n"));
        return ;
    }

    //Err_Info((0,"App_RemindManage_Cancel %d\n",u8RemindCnt));
    //���б��в�����Ϣ��Ӧ�Ĵ洢λ��
    for(u8index =0; u8index < u8RemindCnt; u8index++)
    {
        if(u16MsgId == RemidList[u8index].u16MsgId)
            break;
    }
    //Ҫȡ������Ϣ�Ѳ�����
    if(u8index >= u8RemindCnt)
    {
        Err_Info((0,"Warning: msg %d is not exist\n",u16MsgId));
        return ;
    }

    //��ȡ������Ϣ��Ӧ��λ����Ϊ��Ч��������Ϣ����ʹ��
    RemindStore[RemidList[u8index].u8StoreId].RemindType = INVALID_MESAGE;
    //���RemidList��u16MsgId��Ϣ����Ϣ:�������������ǰһ�����ݵķ�ʽ
    for(i = u8index; i < u8RemindCnt - 1; i++)
    {
        RemidList[i].u16MsgId = RemidList[i + 1].u16MsgId;
        RemidList[i].u8StoreId = RemidList[i + 1].u8StoreId;
    }
    u8RemindCnt--;

    //���ȡ������Ϣ�ǵ�ǰ���µ���Ϣ���򽫵�ǰ��������Ϣ����Ϊ��Ч
    if(u16MsgId == u16CurrMsgId)
    {
        RemindMsg.RemindType = INVALID_MESAGE;
        UI_Screen_Show_Warn_Screen_Message();
    }
#endif
}

//��ȡȡ����Ϣ��ID
void App_RemindManage_GetCancelMsgId(uint16 *pu16MsgId)
{
    if(pu16MsgId != NULL)
    {
        *pu16MsgId = u16CancleMsgId;
    }
}

//**********************************************************************
// ��������: �ֱ�APPɾ���Ѷ���Ϣ
// ���������u16MsgId��ϢID 
// ���ز�����	
//**********************************************************************
void App_RemindManage_DeleteMsg(uint16 u16MsgId)
{
    uint8 u8index =0, i;

    //����Ϣ����ȡ��
    if(u8RemindCnt == 0)
    {
        Err_Info((0,"Warning: no msg remind can be canceled\n"));
        return ;
    }

    //Err_Info((0,"App_RemindManage_Cancel %d\n",u8RemindCnt));
    //���б��в�����Ϣ��Ӧ�Ĵ洢λ��
    for(u8index =0; u8index < u8RemindCnt; u8index++)
    {
        if(u16MsgId == RemidList[u8index].u16MsgId)
            break;
    }
    //Ҫȡ������Ϣ�Ѳ�����
    if(u8index >= u8RemindCnt)
    {
        Err_Info((0,"Warning: msg %d is not exist\n",u16MsgId));
        return ;
    }

    //��ȡ������Ϣ��Ӧ��λ����Ϊ��Ч��������Ϣ����ʹ��
    RemindStore[RemidList[u8index].u8StoreId].RemindType = INVALID_MESAGE;
    //���RemidList��u16MsgId��Ϣ����Ϣ:�������������ǰһ�����ݵķ�ʽ
    for(i = u8index; i < u8RemindCnt - 1; i++)
    {
        RemidList[i].u16MsgId = RemidList[i + 1].u16MsgId;
        RemidList[i].u8StoreId = RemidList[i + 1].u8StoreId;
    }
    u8RemindCnt--;

    //���ȡ������Ϣ�ǵ�ǰ���µ���Ϣ���򽫵�ǰ��������Ϣ����Ϊ��Ч
    if(u16MsgId == u16CurrMsgId)
    {
        RemindMsg.RemindType = INVALID_MESAGE;
    }
}

//**********************************************************************
// ��������: �ֱ�APPɾ��������Ϣ
// ���������u16MsgId��ϢID 
// ���ز�����	
//**********************************************************************
void App_RemindManage_DeleteAllMsg(void)
{
    uint8 u8index =0, i;
    
    for(u8index =0; u8index < MSG_STORE_NUM;u8index++)
    {
        RemidList[i].u16MsgId = 0;
        RemidList[i].u8StoreId = 0;
        RemindStore[u8index].RemindType = INVALID_MESAGE;
    }
    u8RemindCnt =0;
}

#if((ANCS_VER_TYPE  == ANCS_VER_2) && (ANCS_DETIL_TYPE != ANCS_NONE))
//**********************************************************************
// ��������: ����ancs��Ϣ
// ���������
// ���ز�����	
//**********************************************************************

void App_RemindManage_ParseAncs(ancs_msg_info_t *info, uint8_t *pu8Msg,uint8_t u8MsgLen)
{
    if(info == NULL)
        return ;

	/** ����ʱ����ڲ����� */ 
	 if((gtSysCfg.notDisturbSwitch == SWITCH_ON) && (App_Time_NotDisturdTimeCheck()))
		 return ;

    if(info->u8ProType == PROT_CANCEL_MSG_NEW) //��Ϣȡ��
    {
        //ֻ��ȡ������ʱͨ�������жϣ��������������ϢID
        if(info->u8MsgType == PHONE_CALL_IN)  //ȡ������
        {
            UI_Screen_Warn_Call_Exit();
        }
        else
        {
            //App_RemindManage_Cancel(info->u16MsgId);  //���Ȳ�֧���ֻ���ȡ/ɾ����Ϣʱ���ֱ�ͬ��ɾ��
        }
    }
    else if(info->u8ProType == PROT_MSG_DETAIL_NEW)  //��Ϣ�������Ϣ����
    {
        if((pu8Msg != NULL) && (u8MsgLen > 0))  //��Ϣ����
        {
            memset(&RemindMsg, 0x00, sizeof(RemindMsg_t));
            memset(protocalCache,0,APP_REMIND_MSG_MAX_LENGHT);
            RemindMsg.RemindType = info->u8MsgType;
            u16CurrMsgId = info->u16MsgId;
            memcpy(protocalCache,pu8Msg,u8MsgLen);
            protocalCacheCnt = u8MsgLen;

            switch(info->u8MsgType)//��Ϣ�����꣬�ֱ�������
            {
            case PHONE_CALL_IN:
            case FAMILIAR_PHONE_CALL:
                App_RemindManage_CallProcess(IOS);
                break;
            case MISS_PHONE_CALL:
                App_RemindManage_MissCallProcess(IOS);
                //fix :��δ�����磬��timeģʽ��δ��ʾδ������ͼ��
                //App_Remind_Win_MissCallAdd();
                //fix :2018.7.16
                break;
            case PHONE_MESSAGE:
                App_RemindManage_MessgeProcess(IOS);
                break;
            case TIM_MESAGE:
            case WECHAT_MESAGE:
            case QQ_MESAGE:
                App_RemindManage_MsgDetailProcess(IOS,info->u8MsgType);
                break;
            default:
                App_RemindManage_MsgDetailProcess(IOS,info->u8MsgType);
                break;
            }	
        }
    }
}
#endif

