#include "platform_common.h"

#include "mid_common.h"
#include "mid_interface.h"
#include "app_variable.h"
#include "app_protocal.h"
#include "app_remind_manage.h"
#include "ui_screen_warn.h"
#include "app_time.h"

/*******************macro define*******************/
#define 	SECT_END 			0x0000 		//详情段结尾判断符

//定义消息列表结构体
typedef struct
{
    uint8 u8StoreId;
    uint16 u16MsgId;
}RemindMsgList_t;

static RemindMsg_t	RemindMsg;	
static RemindMsg_t	RemindCall;		// 保存来电信息，因为来电无需保存也没有删除，所以单独处理
static RemindMsg_t RemindStore[MSG_STORE_NUM];   //记录5条消息
static RemindMsgList_t RemidList[MSG_STORE_NUM+1];
static uint8 u8RemindCnt = 0;     //记录消息数，最大值5
static uint16 u16CurrMsgId = 0xFFFF;   //记录当前消息ID

static uint16 u16CancleMsgId = 0xFFFF;

uint8_t 	protocalCache[APP_REMIND_MSG_MAX_LENGHT];	// 存储最新utf-8格式的提醒数据
uint8_t 	protocalCacheCnt;	// 提醒数据缓存计数，最大接收 APP_REMIND_MSG_MAX_LENGHT 字节
uint8_t 	flowCnt;			// 提醒数据包流控计数

//**********************************************************************
// 函数功能: 判断消息详情中是否有null:null
// 输入参数：无
// 返回参数：true:消息为null
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
                //消息详情中有null:null
                if(u8j >= 8)
                    return TRUE;
            }
        }
    }
    return FALSE;
}

//**********************************************************************
// 函数功能:	计算完整单个字的UTF-8编码长度
// 输入参数：	pInput: UTF-8编码
// 返回参数：	无
static int16_t GetSingleUTF8CodeLen(const uint8_t pInput)
{
	unsigned char c = pInput;
	// 0xxxxxxx 返回0
	// 10xxxxxx 不存在
	// 110xxxxx 返回2
	// 1110xxxx 返回3
	// 11110xxx 返回4
	// 111110xx 返回5
	// 1111110x 返回6
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
// 函数功能:	将一个字符的UTF8编码转换成Unicode(UCS-2和UCS-4)编码
// 输入参数：	UTF8code：  以UTF-8编码数据流
//				Unicode：   转换生成的Unicode编码
// 返回参数：	成功则返回该字符的UTF8编码所占用的字节数; 失败则返回0. 
// * 注意: 
// *     1. UTF8没有字节序问题, 但是Unicode有字节序要求; 
// *        字节序分为大端(Big Endian)和小端(Little Endian)两种; 
// *        在Intel处理器中采用小端法表示, 在此采用小端法表示. (低地址存低位) 
static uint16_t SINGLE_UTF8_TO_UNICODE(const uint8_t* UTF8code, uint16_t *Unicode)  
{
//    assert(pInput != NULL && Unic != NULL);  
  
    // b1 表示UTF-8编码的pInput中的高字节, b2 表示次高字节, ...  
	char b1, b2, b3, b4, b5, b6;  
  
    *Unicode = 0x0; // 把 *Unic 初始化为全零  
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
// 函数功能: 将最新的消息，增加到历史消息列表中
// 输入参数：
// 返回参数：	
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

    //list中0~4表示消息从新到旧
    for(u8index = u8RemindCnt; u8index > 0; u8index--)
    {
        RemidList[u8index].u16MsgId = RemidList[u8index - 1].u16MsgId;
        RemidList[u8index].u8StoreId = RemidList[u8index - 1].u8StoreId;
    }

    //查找RemindStore中哪个区域可以用来保存
    //提醒数为5条，则覆盖最旧的消息；否则更新到无效的区域中
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

    //将当前的消息信息 copy到历史消息中
	memcpy(&RemindMsg.RTC, &lMidRTC->RTC, sizeof(rtc_time_s));
    RemindMsg.u16MsgID = u16CurrMsgId;
	memcpy(&RemindStore[u8index], &RemindMsg, sizeof(RemindMsg_t));

    //RemidList中第一个数据记录最新消息的信息，通过RemidList将msg id和存储位置关联起来
    RemidList[0].u16MsgId = u16CurrMsgId;
    RemidList[0].u8StoreId = u8index;
    //u8RemindCnt消息条数最大为5
    u8RemindCnt++;
    if(u8RemindCnt >= 5)
    {
        u8RemindCnt = 5;
    }
}

// 获取存储的提醒信息
uint16_t App_RemindManag_StoreGet(uint8_t Serial, RemindMsg_t* tRemindMsg)
{
#if 0  //暂没有用

	if(Serial >= RemindStore.RemindCnt)
		return 0xFF;
	
	memcpy(tRemindMsg, &RemindStore.RemindMsg[(RemindStore.FirstPos+Serial)%5], sizeof(RemindMsg_t));
	
#endif
	return 0;
}


//**********************************************************************
// 函数功能:	来电解析处理
// 输入参数：	无
// 返回参数：	无
static void App_RemindManage_CallProcess(uint8 phoneSystem)
{
	//uint8_t 	phoneType;
	uint8_t 	utfbytesIndex 	= 0;
	uint16_t 	utfbytes;//,utfbytes1,utfbytes2;
	uint16_t 	unicodeTemp;//,unicodeTemp1,unicodeTemp2;
	uint8_t 	endFlagNum = 0;

    //fix:多次收到同一个电话时，来电提醒中姓名重复的情况
    memset(&RemindCall.Detail.PhoneCall,0,sizeof(PhoneCallDetail_t));
    //fix:2019.1.12

	if (phoneSystem == IOS)
	{
		if (*(protocalCache + utfbytesIndex) == 0xE2)	//ＩＯＳ号码前　Ｅ2　80　ＡＤ
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

		if(utfbytes == 0)//异常错误
			break;

		switch(endFlagNum)
		{
			case 0://姓名
				if (utfbytes == 1 && (unicodeTemp == SECT_END))//空字符
				{
					endFlagNum += 1;
				}
				else
				{
					RemindCall.Detail.PhoneCall.name[RemindCall.Detail.PhoneCall.namelen++] = unicodeTemp;
				}
				break;
			case 1:	//内容-呼入电话
				if (utfbytes == 1 && (unicodeTemp == SECT_END))//空字符
				{
					endFlagNum += 1;
				}
				else
				{
					RemindCall.Detail.PhoneCall.detail[RemindCall.Detail.PhoneCall.detaillen++] = unicodeTemp;
				}
				break;
			case 2: break;	//无内容
			default: break;
		}
		utfbytesIndex 	+= utfbytes;
	}
	
	APP_REMIND_RTT_LOG(0, "PHONE_FAMILIAR \r\n");
	
	#if 1	// debug
	// 联系人姓名
	for(uint32_t t = 0; t < RemindCall.Detail.PhoneCall.namelen;t++)
	{
		APP_REMIND_RTT_LOG(0,"\\u%04X", RemindCall.Detail.PhoneCall.name[t]);
	}APP_REMIND_RTT_LOG(0,"\r\n");
	
	// 消息内容：呼入电话
	for(uint32_t t = 0; t < RemindCall.Detail.PhoneCall.detaillen;t++)
	{
		APP_REMIND_RTT_LOG(0,"\\u%04X", RemindCall.Detail.PhoneCall.detail[t]);
	}APP_REMIND_RTT_LOG(0,"\r\n");				
	#endif	

	UI_Screen_Show_Warn_Screen_Call();
	Mid_Motor_ShakeStart(eMidMotorShake2Hz, 5);
}

//**********************************************************************
// 函数功能:	未接来电解析处理
// 输入参数：	无
// 返回参数：	无
// 注：有些安卓手机收不到未接来电提醒
static void App_RemindManage_MissCallProcess(uint8 phoneSystem)
{
	//uint8_t 	phoneType;
	uint8_t 	utfbytesIndex 	= 0;
	uint16_t 	utfbytes;//,utfbytes1,utfbytes2;
	uint16_t 	unicodeTemp;//,unicodeTemp1,unicodeTemp2;
	uint8_t 	endFlagNum = 0;	

	if (phoneSystem == IOS)
	{
		if (*(protocalCache + utfbytesIndex) == 0xE2)//ＩＯＳ号码前　Ｅ2　80　ＡＤ
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

		if(utfbytes == 0)//异常错误
			break;

		switch(endFlagNum)
		{
			case 0://姓名
				if (utfbytes == 1 && (unicodeTemp == SECT_END))//空字符
				{
					endFlagNum += 1;
				}
				else
				{
					RemindMsg.Detail.PhoneMiss.name[RemindMsg.Detail.PhoneMiss.namelen++] = unicodeTemp;
//							appRemindMsg.remindMsg.name[appRemindMsg.remindMsg.namelen++] = unicodeTemp;
				}	    		
				break;
			case 1://内容-呼入电话
				if (utfbytes == 1 && (unicodeTemp == SECT_END))//空字符
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
	// 联系人姓名
	for(uint32_t t = 0; t < RemindMsg.Detail.PhoneMiss.namelen;t++)
	{
		APP_REMIND_RTT_LOG(0,"\\u%04X", RemindMsg.Detail.PhoneMiss.name[t]);
	}APP_REMIND_RTT_LOG(0,"\r\n");
	
	// 消息内容：呼入电话
	for(uint32_t t = 0; t < RemindMsg.Detail.PhoneMiss.detaillen;t++)
	{
		APP_REMIND_RTT_LOG(0,"\\u%04X", RemindMsg.Detail.PhoneMiss.detail[t]);
	}APP_REMIND_RTT_LOG(0,"\r\n");				
	#endif		

	App_RemindManag_Store();
	UI_Screen_Show_Warn_Screen_Message();	
}

//**********************************************************************
// 函数功能:	短信信息解析处理
// 输入参数：	无
// 返回参数：	无
static void App_RemindManage_MessgeProcess(uint8 phoneSystem)
{
	
	// 联系人和电话号码公用ram解析的方式
	
	uint8_t 	utfbytesIndex 	= 0;
	uint16_t 	utfbytes;//,utfbytes1,utfbytes2;
	uint16_t 	unicodeTemp;//,unicodeTemp1,unicodeTemp2;
	uint8_t 	endFlagNum = 0;	

	if (phoneSystem == IOS)
	{
		if (*(protocalCache + utfbytesIndex) == 0xE2)//ＩＯＳ号码前　Ｅ2　80　ＡＤ
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

		if(utfbytes == 0)//异常错误
			break;

		switch(endFlagNum)
		{
			case 0:	//姓名
				if (utfbytes == 1 && (unicodeTemp == SECT_END))//空字符
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
			case 1:	//内容-信息内容
				if (utfbytes == 1 && (unicodeTemp == SECT_END))//空字符
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
	
	// 联系人姓名
	for(uint32_t t = 0; t < RemindMsg.Detail.PhoneMsg.namelen;t++)
	{
		APP_REMIND_RTT_LOG(0,"\\u%04X", RemindMsg.Detail.PhoneMsg.name[t]);
	}APP_REMIND_RTT_LOG(0,"\r\n");
	
	// 短信内容
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
// 函数功能:	微信信息解析处理
// 输入参数：	无
// 返回参数：	无
static void App_RemindManage_MsgDetailProcess(uint8 phoneSystem,uint8_t msg_type)
{
	uint8_t 	utfbytesIndex 	= 0;
	uint16_t 	utfbytes;
	uint16_t 	unicodeTemp;
	uint8_t 	endFlagNum = 0;
	//uint32_t 	size = 0;

//	//清除信息结构体
//	memset(&RemindMsg,0,sizeof(RemindMsg_t));
	
	for(;;)
	{
		if (utfbytesIndex >= protocalCacheCnt)
		{
			break;
		}
		utfbytes 	 = SINGLE_UTF8_TO_UNICODE((const uint8_t*)(protocalCache + utfbytesIndex),&unicodeTemp);   		
		
		if(utfbytes == 0)	//异常错误
			break;
		
		switch(endFlagNum)
		{
			case 0:	// 应用名，如微信、QQ等
                switch(msg_type)
                {
                    case WECHAT_MESAGE:
						if (utfbytes == 1 && (unicodeTemp == SECT_END))//冒号
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
						if (utfbytes == 1 && (unicodeTemp == SECT_END))//冒号
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

			case 1://内容-信息内容
				if (utfbytes == 1 && (unicodeTemp == SECT_END))//空字符
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
	// 打印消息名称
	for(uint32_t t = 0; t < RemindMsg.Detail.AppMsg.namelen;t++)
	{
		APP_REMIND_RTT_LOG(0,"\\u%04X", RemindMsg.Detail.AppMsg.name[t]);
	}APP_REMIND_RTT_LOG(0,"\r\n");	
	
	// 打印消息内容Unicode编码
	for(uint32_t t = 0; t < RemindMsg.Detail.AppMsg.detaillen;t++)
	{
		APP_REMIND_RTT_LOG(0,"\\u%04X", RemindMsg.Detail.AppMsg.detail[t]);
	}APP_REMIND_RTT_LOG(0,"\r\n");
	#endif
    
	/* 通知上层对消息数据进行处理 */	
	App_RemindManag_Store();
	UI_Screen_Show_Warn_Screen_Message();
	Mid_Motor_ShakeStart(eMidMotorShake2Hz, 2);
}

//**********************************************************************
// 函数功能:	初始化提醒信息存储
// 输入参数：	无
// 返回参数：	无
void App_RemindManage_Init(void)
{
    uint8 u8i;

    //消息类型都初始化为无效
    for(u8i = 0; u8i < MSG_STORE_NUM; u8i++)
        RemindStore[u8i].RemindType = 0xFF;
}

//**********************************************************************
// 函数功能:	未操作的提醒信息总条数获取
// 输入参数： 	msgClassify：       信息类型
// 				listNum： 			信息编号，记录根据接收到的先后顺序从1开始编号
// 返回参数：	无

void App_RemindManage_MissRemindSumRead(uint32_t msgClassify,uint8_t *listSumNum)
{

}

//**********************************************************************
// 函数功能:	提醒信息读取
// 输入参数：	dailyMissRemindMsg: 存储信息的结构体
// 				msgClassify：       信息类型
// 				listNum： 			信息编号，记录根据接收到的先后顺序从1开始编号
// 返回参数：	无

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
// 函数功能:	删除一条提醒信息
// 输入参数：	msgClassify: 删除的类型
// 				listnum： 	 删除的编号，记录根据接收到的先后顺序从1开始编号
// 返回参数：	无

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
//	//目录更新
//	for (i = listnum - 1; i < misssRemindNum[msgClassify] - 1; ++i)
//	{
//		misssRemindCatalog[msgClassify][i] 	= misssRemindCatalog[msgClassify][i + 1];
//	}
//	misssRemindCatalog[msgClassify][i] 		= 0;
//	misssRemindNum[msgClassify] 			-= 1;	
}

//**********************************************************************
// 函数功能:	读取当前缓存的提醒信息
// 输入参数：	protocal： 协议内容
// 返回参数：	无
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
// 函数功能:	读取最新一条提醒信息
// 输入参数：	ftRemindMsg:指向消息
// 返回参数：	无
//*********************************************************************
void App_RemindManage_CurrDetailRead(RemindMsg_t* ftRemindMsg)
{
    if(ftRemindMsg != NULL)
    {
        //消息取消时，会将RemindType置成无效，RemindType无效时不copy数据
        ftRemindMsg->RemindType = INVALID_MESAGE;
        //fix:返回消息列表中最新的一条消息，而非最后一条，否则接收到多条信息后在及时提醒中删除消息会死机
        if(RemindStore[RemidList[0].u8StoreId].RemindType != INVALID_MESAGE)
        {
            memcpy(ftRemindMsg, &RemindStore[RemidList[0].u8StoreId], sizeof(RemindMsg_t));
        }
        //fix:2018.11.19
    }
}

//**********************************************************************
// 函数功能:	读取当前来电信息
// 输入参数：	ftRemindMsg:指向消息
// 返回参数：	无
//*********************************************************************
void App_RemindManage_CurrCallRead(RemindMsg_t* ftRemindMsg)
{
	memcpy(ftRemindMsg, &RemindCall, sizeof(RemindMsg_t));
}


//**********************************************************************
// 函数功能:	提醒信息解析处理，先把数据存入CACHE
// 输入参数：	protocal： 协议内容
// 返回参数：	无
// 调用：收到app提醒消息是调用一次
void App_RemindManage_Process(protocal_msg_t protocal,uint8 phoneSystem)
{
	static uint8_t firstPackFlag = 1;
	
	switch(protocal.att.load.content.parameter[1])
	{
		case FLOW_END:
			if (firstPackFlag)//只有一包的情形需作特别处理
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
			firstPackFlag = 1;	//接收到尾包，下一次接收应为第一次包开始

			//fix :如果消息详情是无效的，就不显示,否则会显示"null:null"
			if(App_RemindManag_IsNULL() == TRUE)
				return;
			//fix: 2018.6.26

			// utf-8编码原始数据打印
			for(uint32_t t = 0; t < protocalCacheCnt;t++)
			{
				APP_REMIND_RTT_LOG(0,"%02X ",protocalCache[t]);
			}APP_REMIND_RTT_LOG(0,"\r\n");
			
			/* 清空旧数据，以免对新数据产生影响 */
			memset(&RemindMsg, 0x00, sizeof(RemindMsg_t));
			RemindMsg.RemindType = protocal.att.load.content.parameter[0];
//			APP_REMIND_RTT_LOG(0,"RemindMsg.RemindType %d", RemindMsg.RemindType);
			
			switch(protocal.att.load.content.parameter[0])//信息接收完，分别作处理
			{
				case PHONE_CALL_IN:					
				case FAMILIAR_PHONE_CALL:	// 来电提醒
					App_RemindManage_CallProcess(phoneSystem);
					break;
				case MISS_PHONE_CALL:		// 未接来电提醒
					App_RemindManage_MissCallProcess(phoneSystem);	// 部分安卓手机收不到
					break;
				case PHONE_MESSAGE:			// 短信提醒
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
		case FLOW_START://如果是第一包数据，清0该数组
			memset(protocalCache,0,APP_REMIND_MSG_MAX_LENGHT);
			flowCnt 			= 0;
			protocalCacheCnt 	= 0;
			firstPackFlag 		= 0;//首包接收到，清标识
		default:	//只作数据入缓存		
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
// 函数功能:	提醒信息解析处理，先把数据存入CACHE
// 输入参数：	protocal： 协议内容
// 返回参数：	无

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
		if (firstPackFlag)//只有一包的情形需作特别处理
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
		firstPackFlag = 1;	//接收到尾包，下一次接收应为第一次包开始

        //fix :如果消息详情是无效的，就不显示,否则会显示"null:null"
        if(App_RemindManag_IsNULL() == TRUE)
            return;
        //fix: 2018.6.26

        /* 清空旧数据，以免对新数据产生影响 */
        memset(&RemindMsg, 0x00, sizeof(RemindMsg_t));
        RemindMsg.RemindType = protocal.att.load.content.parameter[0];
//          APP_REMIND_RTT_LOG(0,"RemindMsg.RemindType %d", RemindMsg.RemindType);

		switch(protocal.att.load.content.parameter[0])//信息接收完，分别作处理
		{
			case PHONE_CALL_IN:
			case FAMILIAR_PHONE_CALL:
			App_RemindManage_CallProcess(phoneSystem);
			break;

			case MISS_PHONE_CALL:
			App_RemindManage_MissCallProcess(phoneSystem);
            //fix :有未接来电，在time模式下未显示未接来电图标
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

    case FLOW_START://如果是第一包数据，清0该数组
		memset(protocalCache,0,APP_REMIND_MSG_MAX_LENGHT);
		flowCnt 			= 0;
		protocalCacheCnt 	= 0;
		firstPackFlag 		= 0;//首包接收到，清标识
		u16CurrMsgId = ((uint16)protocal.att.load.content.parameter[1] << 8) + protocal.att.load.content.parameter[2];

    default://只作数据入缓存		
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
// 函数功能: 取消u16MsgId指定的消息，该消息可能是历史消息，也可能是当前最新的消息
// 输入参数：u16MsgId消息ID 
// 返回参数：	
//**********************************************************************
void App_RemindManage_Cancel(uint16 u16MsgId)
{
#if 1
    u16CancleMsgId = u16MsgId;
//    UI_Screen_Test_App_Show();
#else
    uint8 u8index =0, i;

    //无消息可以取消
    if(u8RemindCnt == 0)
    {
        Err_Info((0,"Warning: no msg remind can be canceled\n"));
        return ;
    }

    //Err_Info((0,"App_RemindManage_Cancel %d\n",u8RemindCnt));
    //从列表中查找消息对应的存储位置
    for(u8index =0; u8index < u8RemindCnt; u8index++)
    {
        if(u16MsgId == RemidList[u8index].u16MsgId)
            break;
    }
    //要取消的消息已不存在
    if(u8index >= u8RemindCnt)
    {
        Err_Info((0,"Warning: msg %d is not exist\n",u16MsgId));
        return ;
    }

    //将取消的消息对应的位置置为无效，新来消息可以使用
    RemindStore[RemidList[u8index].u8StoreId].RemindType = INVALID_MESAGE;
    //清除RemidList中u16MsgId消息的信息:以其后的数据相继前一个数据的方式
    for(i = u8index; i < u8RemindCnt - 1; i++)
    {
        RemidList[i].u16MsgId = RemidList[i + 1].u16MsgId;
        RemidList[i].u8StoreId = RemidList[i + 1].u8StoreId;
    }
    u8RemindCnt--;

    //如果取消的消息是当前最新的消息，则将当前的最新消息设置为无效
    if(u16MsgId == u16CurrMsgId)
    {
        RemindMsg.RemindType = INVALID_MESAGE;
        UI_Screen_Show_Warn_Screen_Message();
    }
#endif
}

//获取取消消息的ID
void App_RemindManage_GetCancelMsgId(uint16 *pu16MsgId)
{
    if(pu16MsgId != NULL)
    {
        *pu16MsgId = u16CancleMsgId;
    }
}

//**********************************************************************
// 函数功能: 手表APP删除已读消息
// 输入参数：u16MsgId消息ID 
// 返回参数：	
//**********************************************************************
void App_RemindManage_DeleteMsg(uint16 u16MsgId)
{
    uint8 u8index =0, i;

    //无消息可以取消
    if(u8RemindCnt == 0)
    {
        Err_Info((0,"Warning: no msg remind can be canceled\n"));
        return ;
    }

    //Err_Info((0,"App_RemindManage_Cancel %d\n",u8RemindCnt));
    //从列表中查找消息对应的存储位置
    for(u8index =0; u8index < u8RemindCnt; u8index++)
    {
        if(u16MsgId == RemidList[u8index].u16MsgId)
            break;
    }
    //要取消的消息已不存在
    if(u8index >= u8RemindCnt)
    {
        Err_Info((0,"Warning: msg %d is not exist\n",u16MsgId));
        return ;
    }

    //将取消的消息对应的位置置为无效，新来消息可以使用
    RemindStore[RemidList[u8index].u8StoreId].RemindType = INVALID_MESAGE;
    //清除RemidList中u16MsgId消息的信息:以其后的数据相继前一个数据的方式
    for(i = u8index; i < u8RemindCnt - 1; i++)
    {
        RemidList[i].u16MsgId = RemidList[i + 1].u16MsgId;
        RemidList[i].u8StoreId = RemidList[i + 1].u8StoreId;
    }
    u8RemindCnt--;

    //如果取消的消息是当前最新的消息，则将当前的最新消息设置为无效
    if(u16MsgId == u16CurrMsgId)
    {
        RemindMsg.RemindType = INVALID_MESAGE;
    }
}

//**********************************************************************
// 函数功能: 手表APP删除所有消息
// 输入参数：u16MsgId消息ID 
// 返回参数：	
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
// 函数功能: 处理ancs消息
// 输入参数：
// 返回参数：	
//**********************************************************************

void App_RemindManage_ParseAncs(ancs_msg_info_t *info, uint8_t *pu8Msg,uint8_t u8MsgLen)
{
    if(info == NULL)
        return ;

	/** 勿扰时间段内不提醒 */ 
	 if((gtSysCfg.notDisturbSwitch == SWITCH_ON) && (App_Time_NotDisturdTimeCheck()))
		 return ;

    if(info->u8ProType == PROT_CANCEL_MSG_NEW) //消息取消
    {
        //只有取消来电时通过类型判断，其他情况都用消息ID
        if(info->u8MsgType == PHONE_CALL_IN)  //取消来电
        {
            UI_Screen_Warn_Call_Exit();
        }
        else
        {
            //App_RemindManage_Cancel(info->u16MsgId);  //暂先不支持手机读取/删除消息时，手表同步删除
        }
    }
    else if(info->u8ProType == PROT_MSG_DETAIL_NEW)  //消息详情或消息提醒
    {
        if((pu8Msg != NULL) && (u8MsgLen > 0))  //消息详情
        {
            memset(&RemindMsg, 0x00, sizeof(RemindMsg_t));
            memset(protocalCache,0,APP_REMIND_MSG_MAX_LENGHT);
            RemindMsg.RemindType = info->u8MsgType;
            u16CurrMsgId = info->u16MsgId;
            memcpy(protocalCache,pu8Msg,u8MsgLen);
            protocalCacheCnt = u8MsgLen;

            switch(info->u8MsgType)//信息接收完，分别作处理
            {
            case PHONE_CALL_IN:
            case FAMILIAR_PHONE_CALL:
                App_RemindManage_CallProcess(IOS);
                break;
            case MISS_PHONE_CALL:
                App_RemindManage_MissCallProcess(IOS);
                //fix :有未接来电，在time模式下未显示未接来电图标
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

