/**********************************************************************************************
**
**ģ��˵��: BLE Э��ջ�ṩ��APP�ķ���ӿڶ���
**����汾���޸���־(ʱ�䣬����),�޸���:
**  fix 1:  2018.5.27 ���ӻ�оapp����״̬��ʾ���Խ����оapp��������״̬������Ӳ������ͬ������
**  fix 2:  2018.6.4  �ֻ�������Ȩ����;�Ͽ��������Ϻ󲻷�������Ȩ����о������Ȩ�ɹ�������
**  fix 3:  2018.6.6  �������Ӻͻ�оapp����ͬ�����⣬��Ҫ���������㲥
**  fix 4:  2018.6.7  ����OTA�����и�״̬�ķ���,�Լ���ؿ���
**  fix 5:  2018.6.9  �����쳣�Ͽ������ֿ��������,���Ͽ�����
**  fix 6:  2018.6.12 �޸���OTA��Ƶ����Ϣ���ѣ���������ʧ��
**  fix 7:  2018.6.13 �ӿ�ʼOTA��ʱ���ʱ������:��Щ�ֻ����ֽ������ݾͳ�ʱ
**  fix 8:  2018.6.20 IOS��Ϣ���عرգ��Կ���Ӧ��Ϣ(���ѣ���ʾ����)��
**  
***********************************************************************************************/
#include "platform_common.h"
#include "platform_debugcof.h"
#include "mid_common.h"

#include "app_variable.h"
#include "app_protocal.h"
#include "app_cachedata_manage.h"
#include "app_packdata_manage.h"
#include "app_sleepdata_manage.h"
#include "app_scenedata_manage.h"
#include "app_rtc.h"
#include "app_task.h"
#include "app_remind_manage.h"
#include "app_systerm.h"
#include "app_lcd.h"
#include "app_time.h"

#include "BLE_Stack.h"  //BLE stack
#include "sm_os.h"
#include "sm_sys.h"
#include "mid_motor.h"

#include "mid_interface.h"
#include "scene_interface.h"
#include "store_interface.h"
#include "store_part.h"


#define APP_ProtocalTimeOut   15
#define APP_AuthorTimeOut     60
#define APP_TakePhotoTimeOut  15
#define APP_PaireTimeOut      60
#define APP_AdjustTimeOut     15
#define APP_Hrm_TimeOut       30
#define APP_OTATIMERFREQ      1     //OTA���ݽ��ռ��Ƶ�� 1s


#if (APP_PROTOCAL_DEBUG ==1)
#define ENABLE_PRINT_DATA       0
#define Analy_Debug(x) RTT_DEBUG_printf x
#else
#define ENABLE_PRINT_DATA       0
#define Analy_Debug(x)
#endif

#define BCD_TO_DEC(bcd) ( ((bcd) >> 4) * 10 + ((bcd) & 0x0f) )
#define DEC_TO_BCD(dec) ( (((dec) / 10) << 4) + (((dec) % 10) & 0x0f) )

#define BLE_OTA_RECV_TIMEOUT          15 * 1000   //15S
#define BLE_CONNECT_ERROR_TIMEOUT     15 * 1000   //15S

// protocal
//ble 
const protocal_msg_t    OPEN_BLE_PROTOCAL =
{
    0x23,0x01,0x04,0x12,0x80,0x01,0x00,0x1,0x01
};

const protocal_msg_t    CLOSE_BLE_PROTOCAL =
{
    0x23,0x01,0x04,0x12,0x80,0x01,0x00,0x1,0x00
};

const protocal_msg_t    GET_BLE_STATUS_PROTOCAL =
{
    0x23,0x01,0x04,0x21,0x80,0x02,0x00,0x1,0x00
};

//app interface 
const protocal_msg_t    FIND_PHONE_PROTOCAL=
{
    0x23,0x01,0x03,0x13,0x80,0x04,0x03,0x11
};

const protocal_msg_t    TACK_PICTURE_PROTOCAL=
{
    0x23,0x01,0x03,0x13,0x80,0x04,0x03,0x22,
};

//adjust mode ret
const protocal_msg_t    EXIT_ADJUST_PROTOCAL=
{
    0x23,0x01,0x04,0x13,0x80,0x04,0x03,0x31,0x00,
};

const protocal_msg_t    ACCEPT_CALL_PROTOCAL=
{
    0x23,0x01,0x04,0x13,0x80,0x04,0x03,0x03,01
};

const protocal_msg_t    ACCEPT_CALL_IOS_PROTOCAL =
{
    0x23,0x01,0x04,0x12,0x80,0x04,0x03,0x03,0x01
};

//version
const protocal_msg_t    PROJECT_VER_PROTOCAL =
{
    0x23,0x01,0x06,0x13,0x80,0x08,0x01,0x02
};

//author
const protocal_msg_t AUTHOR_PASS_PROTOCAL =
{
    0x23,0x01,0x04,0x13,0x80,0x01,0x01,0x05,0x01
};

const protocal_msg_t AUTHOR_NG_PROTOCAL =
{
    0x23,0x01,0x04,0x13,0x80,0x01,0x01,0x05,0x00
};

const protocal_msg_t ADJUST_TIME_PROTOCAL =
{
    0x23,0x01,0x03,0x13,0x80,0x02,0x01,0x08
};
const protocal_msg_t GET_WEATHER_PROTOCAL =
{
    0x23,0x01,0x03,0x13,0x80,0x02,0x01,0x10
};
const protocal_msg_t BLE_LINKINV_FEEDBACK =
{
    0x23,0x01,0x05,0x13,0x80,0x80,0x00,0x05,0xff,0xff
};
const protocal_msg_t APP_SPORTSCENE_PROTOCAL =
{
	0x23,0x01,0x05,0x13,0x80,0x80,0x10,0x03,
};
    
const protocal_msg_t ALARM_TO_APP_PROTOCAL = 
{
    0x23,0x01,0x04,0x13,0x80,0x80,0x01,0x0A,
};

const protocal_msg_t HRM_TO_APP_PROTOCAL = 
{
    0x23,0x01,0x04,0x13,0x80,0x80,0x15,0x03,
};


//�������Ӽ��
const protocal_msg_t CONN_INBTERAVLE_PROTOCAL =
{
    0x23,0x01,0x04,0x12,0x80,0x04,0x00,0x05
};

//�������Ӽ��
const protocal_msg_t COMMON_ACK_PROTOCAL =
{
    0x23,0x01,0x01,0x13,0x80,0x00,0x00
};


uint16 dailyBleLinkInvSwitchWay;

uint8  debugu8Option;

typedef enum
{
	APP_PROTOCAL_DISCONNECTED = 0,  //APPδ��Ȩ
	APP_PROTOCAL_RECVAUTHREQEST,    //APP���յ�������Ȩ����
	APP_PROTOCAL_ANCSDISCOVER,      //ANCS������
	APP_PROTOCAL_CONNECTED,         //APP������Ȩ�ɹ���������
}app_conn_type;

//fix 1: ���ӻ�оapp����״̬��ʾ���Խ����оapp��������״̬������Ӳ������ͬ������
//��оapp��������״̬: ��������Ȩ�ɹ����Ϊ׼
//����Ӳ������:��Э��ջ����
static app_conn_type eAppProBleConn = APP_PROTOCAL_DISCONNECTED;
//fix 1: 2018.6.1


//fix 4:����OTA�����и�״̬�ķ���
//OTA�������ݳ�ʱ��¼
static uint32 u32OtaRecvTimeout =0;

//**********************************************************************
// ��������: ���ѽ���
// �����������
// ���ز�����    
//**********************************************************************
void App_NewMsgAnalysis(uint8_t PhoneSystem, uint32 remindstate, uint8 protocaltype)
{
    uint8_t      i;
    uint32_t     temp;
    uint8        validflag = 0;
//    menuMessage  message;
  
    for(i = 0; i < 32; i++)
    {
        temp = remindstate & (0x00000001 << i);
        switch(temp)
        {
            case APP_REMIND_QQ:
            case APP_REMIND_WECHAT:
            case APP_REMIND_TXWEIBO:
            case APP_REMIND_SKYPE:
            case APP_REMIND_XLWEIBO:
            case APP_REMIND_FACEBOOK:
            case APP_REMIND_TWITTER:
            case APP_REMIND_WHATAPP:
            case APP_REMIND_LINE:
            case APP_REMIND_OTHER1:
            case APP_REMIND_CALENDARMSG:
            case APP_REMIND_EMAIL:
            case APP_REMIND_OTHER2:           
            case APP_REMIND_PERSON:
            case APP_REMIND_TIM:
//            validflag       = 1;
//            message.val = PhoneSystem;
//            message.state   = protocaltype;
//            message.op   = UASUAL_MSG_REMIND;//Ӧ����Ϣ
//            WinDowHandle = App_Window_Process(WinDowHandle,TAG_REMIND,message);
            break;

            case APP_REMIND_MSG:    //�ֻ�����
//            validflag       = 1;
//            message.val = PhoneSystem;
//            message.state   = protocaltype;
//            message.op   = MESSAGE_REMIND;
//            WinDowHandle = App_Window_Process(WinDowHandle,TAG_REMIND,message);
            break;

            case APP_REMIND_CALL:   //����   
//			validflag       = 1;
//            message.val = PhoneSystem;
//            message.state   = protocaltype;           
//            message.op    = PHONE_CALL_REMIND;
//            WinDowHandle  = App_Window_Process(WinDowHandle,TAG_REMIND,message);
            break;
            
            case APP_REMIND_MISSCALL:
//            validflag       = 1;
//            message.val = PhoneSystem;
//            message.state   = protocaltype; 
//            message.op    = PHONE_MISS_CALL;
//            WinDowHandle  = App_Window_Process(WinDowHandle,TAG_REMIND,message);
            break;

            default:break;
        }

        if (validflag)
        {
           break;
        }
   }
}

//**********************************************************************
// ��������: ͨ�ã��ã�
// �����������
// ���ز�����    
//**********************************************************************
static void Protocal_SendACK(ble_msg_t *protocal,uint8 u8Status)
{
	ble_msg_t bleMsg;
	uint8 u8route =  protocal->packet.att.routeMsg;

    bleMsg.id       = BLE_MSG_SEND;
    bleMsg.packet   = COMMON_ACK_PROTOCAL;
	bleMsg.packet.att.routeMsg   = ((u8route & 0xf0) >> 4) + (u8route << 4);
	bleMsg.packet.att.flowControl =protocal->packet.att.flowControl; 
	bleMsg.packet.att.load.data[0] = u8Status;
	bleMsg.packet.att.load.data[1] = BLE_Stack_CheckSum(bleMsg.packet.data,bleMsg.packet.att.loadLength + 5);
    Mid_Ble_SendMsg(&bleMsg);
}

//////////////////////////////////////////////////////////////////////////////////
//                       ��·����00H, PROT_LINK��
//////////////////////////////////////////////////////////////////////////////////

//**********************************************************************
// ��������: ����:��������״̬�����ı�����
// ���������u8Status:BLE״̬
// ���ز�����	
//**********************************************************************
static void App_BleStatus_Change(uint8 u8Status)
{
//    movt_task_msg_t     movtMsg;
//	menuMessage        message;

    if(u8Status == BT_ADV_OFF) //��������
    {
        if ((gtSysCfg.bleDiscRemindSwitch == SWITCH_ON) && geBleState == BLE_CONNECT)//���ӶϿ�
        {
//			MOD_PDU_RTT_LOG(0,"BLE OFF \n");
//            message.val   = debugu8Option;
//            message.state = BLE_DICONNECT_STATE;
//            message.op    = BLE_REMIND;
//            WinDowHandle  = App_Window_Process(WinDowHandle,TAG_REMIND,message);
        }      

        geBleState    = BLE_SLEEP;
        //У����������ر�
        #if 0
        if (movtState.state == MOVT_STATE_ADJUST)
        {    
			movtState.timeCnt = 0;
            movtState.state   = MOVT_STATE_NORMAL;
            movtMsg.id  	  = MOVT_MSG_MC_RECOVER;
            MovtTask_EventSet(movtMsg);
        } 
        #endif
    
        if (gtPhoneState.state == PHONE_STATE_PHOTO)
        {
//            message.state   = EXIT_TAKE_PHOTO_MODE;
//            message.op   	= TAKE_PHOTO_REMIND;
//            WinDowHandle 	= App_Window_Process(WinDowHandle,TAG_REMIND,message);      
            gtPhoneState.state = PHONE_STATE_NORMAL;
        }             
    }
    
    if(u8Status == BT_ADV_ON)  //�����㲥
    {
        if ((gtSysCfg.bleDiscRemindSwitch == SWITCH_ON) && geBleState == BLE_CONNECT)//���ӶϿ�
        {
//             message.val   = debugu8Option;
//            message.state = BLE_DICONNECT_STATE;
//            message.op    = BLE_REMIND;
//            WinDowHandle  = App_Window_Process(WinDowHandle,TAG_REMIND,message);
        }      

        geBleState      = BLE_BROADCAST;
        //У����������Ͽ�
        #if 0
        if (movtState.state == MOVT_STATE_ADJUST)
        {
			movtState.timeCnt = 0;
            movtState.state   = MOVT_STATE_NORMAL;
            movtMsg.id  = MOVT_MSG_MC_RECOVER;
            MovtTask_EventSet(movtMsg);
        }
        #endif
    
        if (gtPhoneState.state == PHONE_STATE_PHOTO)
        {
			gtPhoneState.timeCnt  = 0;
//            message.state   = EXIT_TAKE_PHOTO_MODE;
//            message.op   	= TAKE_PHOTO_REMIND;
//            WinDowHandle 	= App_Window_Process(WinDowHandle,TAG_REMIND,message);
            gtPhoneState.state = PHONE_STATE_NORMAL;
        }                          
    }
    
    if(u8Status == BT_CONNECTED)  //��������
    {                    
        geBleState      = BLE_CONNECT; 
		#if(AIR_PRESSURE_SUPPORT == 0)
        //�����ϣ�����һ������
        App_Protocal_GetWeatherProcess();   
		#endif

        if (eAppSysStateNormal == App_Sys_StateGet())
        {
            App_Protocal_AdjustTimeprocess();
        }
    }
}

//**********************************************************************
// ��������:    ���������㲥��
// ���������    
// ���ز�����    ��
//**********************************************************************
static void Analysis_SaveAdvName(protocal_msg_t *protocal)
{
    uint8 BrocastName[32] = {0xFF};
    uint8 j;
    uint8 length;
    length = protocal->att.loadLength - 0x03;
    length = (length > BLE_BRODCASTNAME_MAXLENGTH) ? BLE_BRODCASTNAME_MAXLENGTH : length;

    //��һ��byteд���ݳ��ȣ��ӵڶ���byte��ʼд�㲥���������������nand flash��д����
    memset(BrocastName,0xFF,32);
    BrocastName[0] = length; 
    for(j=0; j < length; j++)
    {
        BrocastName[j+1] = protocal->att.load.content.parameter[j];
    }
    #if 0
    BrocastName[j+1] = '\0';
    Err_Info((0,"save avd name=%s\n",BrocastName));
    BrocastName[j+1] = 0xFF;
    #endif
    Store_Part_Write(eStorePart256B,10,BrocastName,BLE_BRODCASTNAME_MAXLENGTH+1);
}

//**********************************************************************
// ��������: ������·��������
// ���������protocal:Э������
// ���ز�����	
//**********************************************************************
static uint8 Analysis_Link(ble_msg_t *protocal)
{
    uint8       u8Route;     //��¼·��
    uint8       u8FlowCtl;   //��¼���غ�
//    app_task_msg_t  appMsg;

    
#if(ENABLE_PRINT_DATA ==1)
    uint8 i;
    RTT_DEBUG_printf(0,"Link Data:\n");
    for(i = 0; i < protocal->packet.att.loadLength + 6; i++)
    {
        RTT_DEBUG_printf(0,"0x%x,",protocal->packet.data[i]);
    }
    RTT_DEBUG_printf(0,"\n");
#endif

    protocal->id = BLE_MSG_SEND;
    u8Route     = ((protocal->packet.att.routeMsg & 0xf0)>>4) + ( protocal->packet.att.routeMsg<<4); 
    u8FlowCtl   = protocal->packet.att.flowControl; 
    

    switch(protocal->packet.att.load.content.interfaceIndex2)
    {
    case PROT_BT_STATE:     //0x01: 
        if (protocal->packet.att.load.content.interfaceType == PROTOCAL_ECHO)//ble�����乤��״̬
        {
            App_BleStatus_Change(protocal->packet.att.load.content.parameter[0]);
        }
        if (protocal->packet.att.load.content.interfaceType == PROTOCAL_GET)  //��ȡ��������״̬
        {
                        
        }               
        break;

    case PROT_BT_CONN_PARAM:  //0x02: 
        
        break;
    case PROT_BT_ADV_NAME:    //0x03:    ���������㲥��
        //step 1: set adv name to BLE
        if(protocal->packet.att.loadLength - 3 > 11)   //��Э��������������ת��Ϊ�ַ���
            protocal->packet.data[11 + 8] = '\0';
        else
            protocal->packet.data[protocal->packet.att.loadLength + 5] = '\0';  //
        App_Protocal_SetBtAdvName(&protocal->packet.data[8]); 

        //step 2: save adv name to flash
        Analysis_SaveAdvName(&protocal->packet);

        //step 3: send back ACK
        Protocal_SendACK(protocal, SUCCESS);
        break;
    case PROT_BT_ADV_PROJ_NUM: //0x04: 
        
        break;
    case PROT_BT_CONN_INTV:    //0x05: 
        
        break;
    case PROT_BT_FW_VERSION:  //0x06: ������������汾��Ϣ
        
        break;
    
    case PROT_LINKLOSS_REMIND_SWITCH: //0x11: �Ͽ����ѿ���
	if (protocal->packet.att.load.content.interfaceType == PROTOCAL_SET)
	{
		Protocal_SendACK(protocal, SUCCESS); 
		gtSysCfg.bleDiscRemindSwitch = protocal->packet.att.load.content.parameter[0];

		// ����flash�洢�¼�
		Store_Task_Msg_T Store_Task_Msg;
		Store_Task_Msg.Id = eStoreTaskMsgCmn;
		Store_Task_Msg.Param.StoreCmn.Id = eStoreCmnEvenBodyInfoWrite;
		Store_Task_EventSet(&Store_Task_Msg);
	}
	else
	{
		protocal->packet.att.loadLength += 1;
		protocal->packet.att.routeMsg = u8Route;
		protocal->packet.att.flowControl = u8FlowCtl;
		protocal->packet.att.load.content.interfaceType = PROTOCAL_RET; 
		protocal->packet.att.load.content.parameter[0]  = gtSysCfg.bleDiscRemindSwitch;
		protocal->packet.data[protocal->packet.att.loadLength + 5] = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5);
		Mid_Ble_SendMsg(protocal);
	}
	break;
    case PROT_LINK_HEARBEAT:    //0x12:  ��·����
        
        break;
    }
    return Ret_OK;
}

//////////////////////////////////////////////////////////////////////////////////
//                       �豸��Ϣ��01H, PROT_DEV_INFO��
//////////////////////////////////////////////////////////////////////////////////

//**********************************************************************
// ��������: ��������״̬
// ���������u8status:����״̬
// ���ز�����
//**********************************************************************
static void App_Ble_UpdateConnStatus(app_conn_type status)
{
    //status:
    //APP_PROTOCAL_RECVAUTHREQEST: ��һ�׶�����
    //APP_PROTOCAL_ANCSDISCOVER:   ��һ�׶�����,ANCS����
    //APP_PROTOCAL_CONNECTED:      �ڶ������׶�����
    //�����׶�������ӣ������ܲ���Ӱ�죬���ʧ�ܾͻ��Զ��Ͽ���������
    eAppProBleConn = status;
}

//**********************************************************************
// ��������: �����豸��Ϣ����
// ���������protocal:Э������
// ���ز�����	
//**********************************************************************
static uint8 Analysis_DeviceInfo(ble_msg_t *protocal)
{
	SceneWeahterParam_t tWeather;
    uint32  u32temp;
    uint8   u8temp;      //��¼�м�ֵ
    uint8   u8Route;     //��¼·��
	uint8 	u8FlowCtl;   //��¼���غ�
    uint8         batType;
//    rtc_time_s    appRtcTemp;
    alarm_clock_t alarmconfiginfo;
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
    

#if(ENABLE_PRINT_DATA ==1)
    uint8 i;
    RTT_DEBUG_printf(0,"DeviceInfo Data:\n");
    for(i = 0; i < protocal->packet.att.loadLength + 6; i++)
    {
        RTT_DEBUG_printf(0,"0x%x,",protocal->packet.data[i]);
    }
    RTT_DEBUG_printf(0,"\n");
#endif
	
	protocal->id = BLE_MSG_SEND;
	u8Route 	= ((protocal->packet.att.routeMsg & 0xf0)>>4) + ( protocal->packet.att.routeMsg<<4); 
	u8FlowCtl 	= protocal->packet.att.flowControl; 
	
    switch(protocal->packet.att.load.content.interfaceIndex2)
    {
    case PROT_PROD_NAME:  //0x01:  ��Ʒ����
        
         break;
    case PROT_PROD_VER:   //0x02:  �̼��汾��
        u32temp = VersionRead();
        protocal->packet = PROJECT_VER_PROTOCAL;
        protocal->packet.att.routeMsg = u8Route;
		protocal->packet.att.flowControl = u8FlowCtl;
		protocal->packet.att.load.content.interfaceType = PROTOCAL_RET; 
        protocal->packet.att.load.content.parameter[0] = (uint8)(u32temp >> 16);
        protocal->packet.att.load.content.parameter[1] = (uint8)(u32temp >> 8);
        protocal->packet.att.load.content.parameter[2] = (uint8)(u32temp);
        protocal->packet.att.load.content.parameter[3] = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5);
        Mid_Ble_SendMsg(protocal);
        break;
    case PROT_PROD_DATE:   //0x03: ��������
        
        break;
    case PROT_PROD_SOC:     //0x04:  ʣ�����
    case PROT_PROD_SOC_NEW:
		batType = Mid_Bat_SocRead(&u8temp);
		protocal->packet.att.routeMsg = u8Route;
		protocal->packet.att.flowControl = u8FlowCtl;
		protocal->packet.att.load.content.interfaceType = PROTOCAL_RET; 
		if(protocal->packet.att.load.content.interfaceIndex2 == PROT_PROD_SOC)
		{           
			protocal->packet.att.loadLength += 1;
			protocal->packet.att.load.content.parameter[0] = u8temp;   //ʣ�����
			protocal->packet.att.load.content.parameter[1] = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5);
		}
		else
		{
			protocal->packet.att.loadLength += 2;
			protocal->packet.att.load.content.parameter[0] = batType;  //�ɳ����
			protocal->packet.att.load.content.parameter[1] = u8temp;   //ʣ�����
			protocal->packet.att.load.content.parameter[2] = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5);
		}
		Mid_Ble_SendMsg(protocal);
		break;

    case PROT_PROD_AUTH:    //0x05: ��Ȩ
		if(protocal->packet.att.load.content.parameter[0] == 0x00)  //apply author
		{
			//step 1:send ACK
			App_Ble_UpdateConnStatus(APP_PROTOCAL_RECVAUTHREQEST);
			Protocal_SendACK(protocal, SUCCESS);

			//step 2:set author phonestate
			gtPhoneState.timeCnt  = 0;
			gtPhoneState.timeMax  = APP_AuthorTimeOut;
			gtPhoneState.state    = PHONE_STATE_AUTHOR;

			// �������ʾ��Ȩ
			Mid_Motor_ShakeStart(eMidMotorShake2Hz, 2);	

			#if 0 // ֱ�ӷ�����Ȩ�����ڲ���
			App_Protocal_AuthorPass();
			#endif
		}
		else if(protocal->packet.att.load.content.parameter[0] == 0x01)  //enforce author
		{
			App_Ble_UpdateConnStatus(APP_PROTOCAL_RECVAUTHREQEST);
			Protocal_SendACK(protocal, SUCCESS); 
			App_Protocal_AuthorPass();
			gtPhoneState.state = PHONE_STATE_NORMAL;  
			gtPhoneState.timeCnt  = 0;
		}
		else
		{
			Protocal_SendACK(protocal, PARAMATER_ERROR);
		}
    break;

    case PROT_PROD_SN:  //0x06		SN��	
    Protocal_SendACK(protocal, SUCCESS);
    App_Protocal_RetSN(protocal);
    break;

    case PROT_DATE:   //rtc ʱ�� 0x08	
    if (protocal->packet.att.load.content.interfaceType == PROTOCAL_SET || 
        protocal->packet.att.load.content.interfaceType == PROTOCAL_RET)
    {
        Protocal_SendACK(protocal, SUCCESS);
		lMidRTC->RTC.year   = ((protocal->packet.att.load.content.parameter[0]>>4) & 0x0f) * 10 
                   + (protocal->packet.att.load.content.parameter[0] & 0x0f);

		lMidRTC->RTC.month  = (eMidRTCMonth)(((protocal->packet.att.load.content.parameter[1]>>4) & 0x0f) * 10 
                       + (protocal->packet.att.load.content.parameter[1] & 0x0f));                              

		lMidRTC->RTC.day    = ((protocal->packet.att.load.content.parameter[2]>>4) & 0x0f) * 10 
                       + (protocal->packet.att.load.content.parameter[2] & 0x0f);

		lMidRTC->RTC.hour   = ((protocal->packet.att.load.content.parameter[3]>>4) & 0x0f) * 10 
                       + (protocal->packet.att.load.content.parameter[3] & 0x0f);
      
		lMidRTC->RTC.min    = ((protocal->packet.att.load.content.parameter[4]>>4) & 0x0f) * 10 
                       + (protocal->packet.att.load.content.parameter[4] & 0x0f);

		lMidRTC->RTC.sec    = ((protocal->packet.att.load.content.parameter[5]>>4) & 0x0f) * 10 
                       + (protocal->packet.att.load.content.parameter[5] & 0x0f);

		lMidRTC->RTC.zone   = ((uint16)protocal->packet.att.load.content.parameter[6] & 0x8000) 
                       | ((uint16)protocal->packet.att.load.content.parameter[6] << 8)
                       | ((uint16)protocal->packet.att.load.content.parameter[7]);

		lMidRTC->RTC.week   = (eMidRTCWeek)(protocal->packet.att.load.content.parameter[8]);
	   
	   TimeTransformUtc(&lMidRTC->RTC, &lMidRTC->UTC);	// RTCʱ��תUTC������������ʲôʱ����RTC��ֱ��תUTC������תΪ0ʱ����UTC
//		lMidRTC->UTC = Read_GMT_Utc();	// ����0ʱ����UTCʱ��
	   
	   // ����LCDˢ���¼�
	   App_Schd_TaskMsg_T	AppMsg;
	   AppMsg.Id = eAppSchdMsgLcd;
	   AppMsg.Param.Lcd.ScreenId = Common_Screen_MainID_DateAndTime;
	   App_Schd_TaskEventSet(&AppMsg, 0);
	   
	   // ����flash�洢�¼�
		Store_Task_Msg_T Store_Task_Msg;
		Store_Task_Msg.Id = eStoreTaskMsgCmn;
		Store_Task_Msg.Param.StoreCmn.Id = eStoreCmnEventTimeInfoWrite;
		Store_Task_EventSet(&Store_Task_Msg);
	   
    }else if (protocal->packet.att.load.content.interfaceType == PROTOCAL_GET)
    {
        protocal->packet.att.loadLength += 9;
        protocal->packet.att.routeMsg = u8Route;
        protocal->packet.att.flowControl = u8FlowCtl;
        protocal->packet.att.load.content.interfaceType = PROTOCAL_RET; 
        protocal->packet.att.load.content.parameter[0] = (lMidRTC->RTC.year  / 10)<<4 | (lMidRTC->RTC.year % 10);
        protocal->packet.att.load.content.parameter[1] = (lMidRTC->RTC.month  / 10)<<4 | (lMidRTC->RTC.month % 10);
        protocal->packet.att.load.content.parameter[2] = (lMidRTC->RTC.day  / 10)<<4 | (lMidRTC->RTC.day % 10);
        protocal->packet.att.load.content.parameter[3] = (lMidRTC->RTC.hour  / 10)<<4 | (lMidRTC->RTC.hour % 10);
        protocal->packet.att.load.content.parameter[4] = (lMidRTC->RTC.min  / 10)<<4 | (lMidRTC->RTC.min % 10);
        protocal->packet.att.load.content.parameter[5] = (lMidRTC->RTC.sec  / 10)<<4 | (lMidRTC->RTC.sec % 10);
        protocal->packet.att.load.content.parameter[6] = (uint8_t)((lMidRTC->RTC.zone & 0x8f00) >> 8);
        protocal->packet.att.load.content.parameter[7] = (uint8_t)(lMidRTC->RTC.zone & 0x00ff);
        protocal->packet.att.load.content.parameter[8] = lMidRTC->RTC.week;
        protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5); 
        Mid_Ble_SendMsg(protocal);
    }
    break;

    case PROT_SEC_CITY_DATE: //0x09 �ڶ�����ʱ��
    if (protocal->packet.att.load.content.interfaceType == PROTOCAL_SET)
    {
        Protocal_SendACK(protocal, SUCCESS);

        lMidRTC->WordRTC.year   = ((protocal->packet.att.load.content.parameter[0]>>4) & 0x0f) * 10 
                   + (protocal->packet.att.load.content.parameter[0] & 0x0f);

       lMidRTC->WordRTC.month  = (eMidRTCMonth)(((protocal->packet.att.load.content.parameter[1]>>4) & 0x0f) * 10 
                       + (protocal->packet.att.load.content.parameter[1] & 0x0f));                              

       lMidRTC->WordRTC.day    = ((protocal->packet.att.load.content.parameter[2]>>4) & 0x0f) * 10 
                       + (protocal->packet.att.load.content.parameter[2] & 0x0f);

       lMidRTC->WordRTC.hour   = ((protocal->packet.att.load.content.parameter[3]>>4) & 0x0f) * 10 
                       + (protocal->packet.att.load.content.parameter[3] & 0x0f);
      
       lMidRTC->WordRTC.min    = ((protocal->packet.att.load.content.parameter[4]>>4) & 0x0f) * 10 
                       + (protocal->packet.att.load.content.parameter[4] & 0x0f);

       lMidRTC->WordRTC.sec    = ((protocal->packet.att.load.content.parameter[5]>>4) & 0x0f) * 10 
                       + (protocal->packet.att.load.content.parameter[5] & 0x0f);

       lMidRTC->WordRTC.zone   = ((uint16)protocal->packet.att.load.content.parameter[6] & 0x8000) 
                       | ((uint16)protocal->packet.att.load.content.parameter[6] << 8)
                       | ((uint16)protocal->packet.att.load.content.parameter[7]);

       lMidRTC->WordRTC.week   = (eMidRTCWeek)(protocal->packet.att.load.content.parameter[8]);

       lMidRTC->cityCode    = ((uint16)protocal->packet.att.load.content.parameter[9] << 8)
                            |(uint16)protocal->packet.att.load.content.parameter[10];                     
   
	   // ����flash�洢�¼�
		Store_Task_Msg_T Store_Task_Msg;
		Store_Task_Msg.Id = eStoreTaskMsgCmn;
		Store_Task_Msg.Param.StoreCmn.Id = eStoreCmnEventTimeInfoWrite;
		Store_Task_EventSet(&Store_Task_Msg);
	}
    if (protocal->packet.att.load.content.interfaceType == PROTOCAL_GET)
    {
        protocal->packet.att.loadLength += 11;
        protocal->packet.att.routeMsg = u8Route;
        protocal->packet.att.flowControl = u8FlowCtl;
        protocal->packet.att.load.content.interfaceType = PROTOCAL_RET; 
        protocal->packet.att.load.content.parameter[0] = (lMidRTC->WordRTC.year  / 10)<<4 | (lMidRTC->WordRTC.year % 10);
        protocal->packet.att.load.content.parameter[1] = (lMidRTC->WordRTC.month  / 10)<<4 | (lMidRTC->WordRTC.month % 10);
        protocal->packet.att.load.content.parameter[2] = (lMidRTC->WordRTC.day  / 10)<<4 | (lMidRTC->WordRTC.day % 10);
        protocal->packet.att.load.content.parameter[3] = (lMidRTC->WordRTC.hour  / 10)<<4 | (lMidRTC->WordRTC.hour % 10);
        protocal->packet.att.load.content.parameter[4] = (lMidRTC->WordRTC.min  / 10)<<4 | (lMidRTC->WordRTC.min % 10);
        protocal->packet.att.load.content.parameter[5] = (lMidRTC->WordRTC.sec  / 10)<<4 | (lMidRTC->WordRTC.sec % 10);
        protocal->packet.att.load.content.parameter[6] = (uint8_t)((lMidRTC->WordRTC.zone & 0x8f00) >> 8);
        protocal->packet.att.load.content.parameter[7] = (uint8_t)(lMidRTC->WordRTC.zone & 0x00ff);
        protocal->packet.att.load.content.parameter[8] = lMidRTC->WordRTC.week;
        protocal->packet.att.load.content.parameter[9] = (uint8_t)((lMidRTC->cityCode & 0x8f00) >> 8);
        protocal->packet.att.load.content.parameter[10] = (uint8_t)(lMidRTC->cityCode& 0x00ff);
        protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5); 
        Mid_Ble_SendMsg(protocal);
    }          
    break; 

    case PROT_SEC_CITY_DST: //0x0D	// �ڶ�����DST

    break;

    case PROT_ALARM_CLK: //0x0A	// ����
//		if (protocal->packet.att.load.content.interfaceType == PROTOCAL_SET)
//		{
//			Protocal_SendACK(protocal, SUCCESS);
//			alarmconfiginfo.hour = ((protocal->packet.att.load.content.parameter[1]>>4) & 0x0f) * 10 
//								+ (protocal->packet.att.load.content.parameter[1] & 0x0f);
//			alarmconfiginfo.min  = ((protocal->packet.att.load.content.parameter[2]>>4) & 0x0f) * 10 
//								+ (protocal->packet.att.load.content.parameter[2] & 0x0f);
//			alarmconfiginfo.ReptMap  = protocal->packet.att.load.content.parameter[3];
//			alarmconfiginfo.alarmswitch = protocal->packet.att.load.content.parameter[4];

//			Scene_Alarm_Write(&alarmconfiginfo,protocal->packet.att.load.content.parameter[0]-1);

//			// ����flash�洢�¼�
//			Store_Task_Msg_T Store_Task_Msg;
//			Store_Task_Msg.Id = eStoreTaskMsgCmn;
//			Store_Task_Msg.Param.StoreCmn.Id = eStoreCmnEventAlarmInfoWrite;
//			Store_Task_EventSet(&Store_Task_Msg);
//			
//			#if 0	// debug
//			STORE_RTT_LOG(0, "PROT_ALARM_CLK:");
//			for(uint32_t i = 0;i < 32;i++)
//			{
//				MOD_PDU_RTT_LOG(0, "%02X ", protocal->packet.data[i]);
//			}MOD_PDU_RTT_LOG(0, "\n");
//			#endif
//		}
		
//		if (protocal->packet.att.load.content.interfaceType == PROTOCAL_GET)
//		{
//			if((protocal->packet.att.load.content.parameter[0]) > 0)//ret assigned alarm
//			{
//				Scene_Alarm_Read(&alarmconfiginfo, protocal->packet.att.load.content.parameter[0]-1);
//				protocal->packet.att.loadLength += 4;
//				protocal->packet.att.routeMsg = u8Route;
//				protocal->packet.att.flowControl = u8FlowCtl;
//				protocal->packet.att.load.content.interfaceType = PROTOCAL_RET; 
//				protocal->packet.att.load.content.parameter[1] = (alarmconfiginfo.hour / 10)<<4 | (alarmconfiginfo.hour % 10);
//				protocal->packet.att.load.content.parameter[2] = (alarmconfiginfo.min / 10)<<4  | (alarmconfiginfo.min % 10);
//				protocal->packet.att.load.content.parameter[3] = alarmconfiginfo.ReptMap;
//				protocal->packet.att.load.content.parameter[4] = alarmconfiginfo.alarmswitch;
//				protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5); 
//				Mid_Ble_SendMsg(protocal);
//			}
//			else//all alarm
//			{
//				//group 1
//				Scene_Alarm_Read(&alarmconfiginfo, 0);
//				protocal->packet.att.loadLength += 5;
//				protocal->packet.att.routeMsg = u8Route;
//				protocal->packet.att.flowControl = u8FlowCtl;
//				protocal->packet.att.load.content.interfaceType = PROTOCAL_RET; 
//				protocal->packet.att.load.content.parameter[0] = 0x01;
//				protocal->packet.att.load.content.parameter[1] = (alarmconfiginfo.hour / 10)<<4 | (alarmconfiginfo.hour % 10);
//				protocal->packet.att.load.content.parameter[2] = (alarmconfiginfo.min / 10)<<4  | (alarmconfiginfo.min % 10);
//				protocal->packet.att.load.content.parameter[3] = alarmconfiginfo.ReptMap;
//				protocal->packet.att.load.content.parameter[4] = alarmconfiginfo.alarmswitch;
//				protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5); 
//				Mid_Ble_SendMsg(protocal);
//				vTaskDelay(50);//delay 100 tick

//				//group 2
//				Scene_Alarm_Read(&alarmconfiginfo, 1);
//				protocal->packet.att.load.content.parameter[0] = 0x02;
//				protocal->packet.att.load.content.parameter[1] = (alarmconfiginfo.hour / 10)<<4 | (alarmconfiginfo.hour % 10);
//				protocal->packet.att.load.content.parameter[2] = (alarmconfiginfo.min / 10)<<4  | (alarmconfiginfo.min % 10);
//				protocal->packet.att.load.content.parameter[3] = alarmconfiginfo.ReptMap;
//				protocal->packet.att.load.content.parameter[4] = alarmconfiginfo.alarmswitch;

//				protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5);  
//				Mid_Ble_SendMsg(protocal);
//				vTaskDelay(50);//delay 100 tick

//				//group 3
//				Scene_Alarm_Read(&alarmconfiginfo, 2);
//				protocal->packet.att.load.content.parameter[0] = 0x03;
//				protocal->packet.att.load.content.parameter[1] = (alarmconfiginfo.hour / 10)<<4 | (alarmconfiginfo.hour % 10);
//				protocal->packet.att.load.content.parameter[2] = (alarmconfiginfo.min / 10)<<4  | (alarmconfiginfo.min % 10);
//				protocal->packet.att.load.content.parameter[3] = alarmconfiginfo.ReptMap;
//				protocal->packet.att.load.content.parameter[4] = alarmconfiginfo.alarmswitch;

//				protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5);  
//				Mid_Ble_SendMsg(protocal);
//			}
//		}
		break;
	case PROT_ALARM_CLK2:	// ����2
		if (protocal->packet.att.load.content.interfaceType == PROTOCAL_SET)
		/* ����������Ϣ */
		{
			Protocal_SendACK(protocal, SUCCESS);

			alarmconfiginfo.hour = ((protocal->packet.att.load.content.parameter[1]>>4) & 0x0f) * 10 
								+ (protocal->packet.att.load.content.parameter[1] & 0x0f);
			alarmconfiginfo.min  = ((protocal->packet.att.load.content.parameter[2]>>4) & 0x0f) * 10 
								+ (protocal->packet.att.load.content.parameter[2] & 0x0f);
			alarmconfiginfo.ReptMap  = protocal->packet.att.load.content.parameter[3];
			alarmconfiginfo.alarmswitch = protocal->packet.att.load.content.parameter[4];
			alarmconfiginfo.RingSwitch = protocal->packet.att.load.content.parameter[5];
			alarmconfiginfo.RingDurtion = protocal->packet.att.load.content.parameter[6];
			alarmconfiginfo.AlertLevel = protocal->packet.att.load.content.parameter[7];
			Scene_Alarm_Write(&alarmconfiginfo, protocal->packet.att.load.content.parameter[0]-1);

			if(protocal->packet.att.load.content.parameter[0] == SCENE_ALARM_MAX_ALARM_NUM)
			/* �յ����һ�����ӣ�����flash�洢�¼�
				��Ϊÿ��app���ᷢȫ������ */
			{
				Store_Task_Msg_T Store_Task_Msg;
				Store_Task_Msg.Id = eStoreTaskMsgCmn;
				Store_Task_Msg.Param.StoreCmn.Id = eStoreCmnEventAlarmInfoWrite;
				Store_Task_EventSet(&Store_Task_Msg);				
			}
		}
		else if(protocal->packet.att.load.content.interfaceType == PROTOCAL_GET)
		/* ��ȡ������Ϣ */
		{
			MOD_PDU_RTT_LOG(0,"PROT_ALARM_CLK2 GET \n");
			protocal->packet.att.loadLength = 11;
			protocal->packet.att.routeMsg = u8Route;
			protocal->packet.att.load.content.interfaceType = PROTOCAL_RET;
			if((protocal->packet.att.load.content.parameter[0]) > 0)
			/* ��ȡָ������ */
			{
				Scene_Alarm_Read(&alarmconfiginfo, protocal->packet.att.load.content.parameter[0]-1);
				protocal->packet.att.flowControl = u8FlowCtl++;
//				protocal->packet.att.load.content.parameter[0] = ;	// ��Ų���
				protocal->packet.att.load.content.parameter[1] = (alarmconfiginfo.hour / 10)<<4 | (alarmconfiginfo.hour % 10); ;	// ʱ
				protocal->packet.att.load.content.parameter[2] = (alarmconfiginfo.min / 10)<<4  | (alarmconfiginfo.min % 10);	// ��
				protocal->packet.att.load.content.parameter[3] = alarmconfiginfo.ReptMap;	// �ظ�λͼ
				protocal->packet.att.load.content.parameter[4] = alarmconfiginfo.alarmswitch;	// �¼�״̬
				protocal->packet.att.load.content.parameter[5] = alarmconfiginfo.RingSwitch;	// ̰˯���ܿ���
				protocal->packet.att.load.content.parameter[6] = alarmconfiginfo.RingDurtion;	// ̰˯ʱ������
				protocal->packet.att.load.content.parameter[7] = alarmconfiginfo.AlertLevel;	// �������ѵȼ�
				protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data, protocal->packet.att.loadLength + 5);  
				Mid_Ble_SendMsg(protocal);				
			}
			else
			/* ��ȡȫ������ */
			{
				for(uint32_t i = 0;i < SCENE_ALARM_MAX_ALARM_NUM;i++)
				{
					protocal->packet.att.flowControl = u8FlowCtl++;
					Scene_Alarm_Read(&alarmconfiginfo, i);
					protocal->packet.att.load.content.parameter[0] = i+1;	// ������Ŵ�1��ʼ
					protocal->packet.att.load.content.parameter[1] = (alarmconfiginfo.hour / 10)<<4 | (alarmconfiginfo.hour % 10); ;	// ʱ
					protocal->packet.att.load.content.parameter[2] = (alarmconfiginfo.min / 10)<<4  | (alarmconfiginfo.min % 10);	// ��
					protocal->packet.att.load.content.parameter[3] = alarmconfiginfo.ReptMap;	// �ظ�λͼ
					protocal->packet.att.load.content.parameter[4] = alarmconfiginfo.alarmswitch;	// �¼�״̬
					protocal->packet.att.load.content.parameter[5] = alarmconfiginfo.RingSwitch;	// ̰˯���ܿ���
					protocal->packet.att.load.content.parameter[6] = alarmconfiginfo.RingDurtion;	// ̰˯ʱ������
					protocal->packet.att.load.content.parameter[7] = alarmconfiginfo.AlertLevel;	// �������ѵȼ�
					protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data, protocal->packet.att.loadLength + 5);  
					Mid_Ble_SendMsg(protocal);
					vTaskDelay(10);
				}
			}
		}
		break;
    case PROT_WEIGHT_HEIGHT://0x0E	// �������
	MOD_PDU_RTT_LOG(0,"PROT_WEIGHT_HEIGHT %d \n",protocal->packet.att.load.content.interfaceType);
    if (protocal->packet.att.load.content.interfaceType == PROTOCAL_SET)
    {
        Protocal_SendACK(protocal, SUCCESS);
        gtBodyInfo.Height   = protocal->packet.att.load.content.parameter[0];
        gtBodyInfo.Weight   = protocal->packet.att.load.content.parameter[1];     
        gtBodyInfo.age          = protocal->packet.att.load.content.parameter[2];
        gtBodyInfo.sex          = protocal->packet.att.load.content.parameter[3];

	   // ����flash�洢�¼�
		Store_Task_Msg_T Store_Task_Msg;
		Store_Task_Msg.Id = eStoreTaskMsgCmn;
		Store_Task_Msg.Param.StoreCmn.Id = eStoreCmnEvenBodyInfoWrite;
		Store_Task_EventSet(&Store_Task_Msg);
    }
    else if (protocal->packet.att.load.content.interfaceType == PROTOCAL_GET)
    {
        protocal->packet.att.loadLength += 4;
        protocal->packet.att.routeMsg = u8Route;
        protocal->packet.att.flowControl = u8FlowCtl;
        protocal->packet.att.load.content.interfaceType = PROTOCAL_RET; 
        protocal->packet.att.load.content.parameter[0] = gtBodyInfo.Height;
        protocal->packet.att.load.content.parameter[1] = gtBodyInfo.Weight;
        protocal->packet.att.load.content.parameter[2] = gtBodyInfo.age;
        protocal->packet.att.load.content.parameter[3] = gtBodyInfo.sex;
        protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5);  
        Mid_Ble_SendMsg(protocal);        
    }
    else
    {
        Protocal_SendACK(protocal, PARAMATER_ERROR);
    }
    break;

    case PROT_PHONE_WEATHER: //0x10		// ����
    Protocal_SendACK(protocal, SUCCESS);
	
    tWeather.Status = (SceneWeahterStatus_e)(protocal->packet.att.load.content.parameter[0] <<8 
                                | protocal->packet.att.load.content.parameter[1]);
    tWeather.MinTemperature =  protocal->packet.att.load.content.parameter[2]; 
    tWeather.MaxTemperature =  protocal->packet.att.load.content.parameter[3];   
    tWeather.CurTemperature =  protocal->packet.att.load.content.parameter[4];                       
	Scene_Weather_TendencySet(&tWeather);
	
//	// ����flash�洢�¼�
//	Store_Task_Msg_T Store_Task_Msg;
//	Store_Task_Msg.Id = eStoreTaskMsgCmn;
//	Store_Task_Msg.Param.Store.Type = eStoreTypeSystem;
//	Store_Task_EventSet(&Store_Task_Msg);	
    break;
    }
    return Ret_OK;
}

//////////////////////////////////////////////////////////////////////////////////
//                       �������ƣ�03H, PROT_INTERACT��
//////////////////////////////////////////////////////////////////////////////////


//**********************************************************************
// ��������: ����������������
// ���������protocal:Э������
// ���ز�����	
//**********************************************************************
static uint8 Analysis_Interact(ble_msg_t *protocal)
{
    // ble_msg_t bleMsg;
//    uint8_t u8temp;
	uint8   u8Route;     //��¼·��
	uint8 	u8FlowCtl;   //��¼���غ�
	uint16 u16MsgID;
	SceneSedentaryParam_t* lpSedentary = Scene_Sedentary_ParamPGet();
	
#if (ENABLE_PRINT_DATA ==1)
    uint8 i;
    RTT_DEBUG_printf(0,"Interact Data:\n");
    for(i = 0; i < protocal->packet.att.loadLength + 6; i++)
    {
        RTT_DEBUG_printf(0,"0x%x,",protocal->packet.data[i]);
    }
    RTT_DEBUG_printf(0,"\n");
#endif
	
	protocal->id = BLE_MSG_SEND;
	u8Route 	= ((protocal->packet.att.routeMsg & 0xf0)>>4) + ( protocal->packet.att.routeMsg<<4); 
	u8FlowCtl 	= protocal->packet.att.flowControl; 
	
	MOD_PDU_RTT_LOG(0,"Analysis_Interact %02X \n",protocal->packet.att.load.content.interfaceIndex2);
	
	switch(protocal->packet.att.load.content.interfaceIndex2)
    {
		case PROT_NEW_MSG:  //0x01: ����Ϣ֪ͨ����δʹ�ã�ʹ�õ�����Ϣ���飩
			break;
		case PROT_MSG_SWITCH://0x02��֪ͨ���أ�app������Ϣ���ѿ���ʱ���ʹ�ָ��
			if (protocal->packet.att.load.content.interfaceType == PROTOCAL_GET)//��ȡ
			{
				protocal->packet.att.loadLength += 4;
				protocal->packet.att.routeMsg = u8Route;
				protocal->packet.att.flowControl = u8FlowCtl;
				protocal->packet.att.load.content.interfaceType = PROTOCAL_RET;
				protocal->packet.att.load.content.parameter[0] = (gtSysCfg.appRemindSwitch >> 24)& 0xff;
				protocal->packet.att.load.content.parameter[1] = (gtSysCfg.appRemindSwitch >> 16)& 0xff;
				protocal->packet.att.load.content.parameter[2] = (gtSysCfg.appRemindSwitch >> 8) & 0xff;
				protocal->packet.att.load.content.parameter[3] = gtSysCfg.appRemindSwitch & 0xff;
				
				protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5); 
				Mid_Ble_SendMsg(protocal);
			}else if (protocal->packet.att.load.content.interfaceType == PROTOCAL_SET)//���� 
			{
			   gtSysCfg.appRemindSwitch     = ((uint32)protocal->packet.att.load.content.parameter[0] << 24) 
													+ ((uint32)protocal->packet.att.load.content.parameter[1] << 16)
													+ ((uint32)protocal->packet.att.load.content.parameter[2] << 8)
													+ ((uint32)protocal->packet.att.load.content.parameter[3]);
			   Protocal_SendACK(protocal,SUCCESS);

                //add: ����ANCS���鿪��
                BLE_Stack_SetAncsMsgSwitch(gtSysCfg.appRemindSwitch);
                //add: 2018.11.30

				// ����flash�洢�¼�
				Store_Task_Msg_T Store_Task_Msg;
				Store_Task_Msg.Id = eStoreTaskMsgCmn;
				Store_Task_Msg.Param.StoreCmn.Id = eStoreCmnEventSysInfoWrite;
				Store_Task_EventSet(&Store_Task_Msg);
			}
			else
			{
				Protocal_SendACK(protocal,PARAMATER_ERROR);
			}
			break;
		case PROT_INCALL_RESP:   // 0x03: ����֪ͨ������ֻ��Ʒ����
			break;
		case PROT_CANCEL_MSG:    //0x04:��Ϣȡ��֪ͨ���ɣ� ,��ҵ��绰DrL��H002ʹ���µ���Ϣȡ��֪ͨ
			break;
		case PROT_CANCEL_MSG_NEW:    //0x14:��Ϣȡ��֪ͨ���£�
		    #if 0
    		{
                uint8 i;
                SEGGER_RTT_printf(0,"msg cancel Data:\n");
                for(i = 0; i < protocal->packet.att.loadLength + 6; i++)
                {
                    SEGGER_RTT_printf(0,"0x%x,",protocal->packet.data[i]);
                }
                SEGGER_RTT_printf(0,"\n");
            }
            #endif
            //android��Ϣ��app�����������Ack��IOS��ANCS�������ack
            if (protocal->packet.att.routeMsg == 0x31)
            {
                Protocal_SendACK(protocal,SUCCESS);
            }
            u16MsgID = ((uint16)protocal->packet.att.load.content.parameter[4] << 8) + protocal->packet.att.load.content.parameter[5];
            //SEGGER_RTT_printf(0,"u16MsgID =%d\n",u16MsgID);
            App_RemindManage_Cancel(u16MsgID); 
			break;
        case PROT_MSG_DETAIL_SWITCH: //0x05: ��Ϣ���鿪��
			if (protocal->packet.att.load.content.interfaceType == PROTOCAL_SET)//���� 
			{
			   gtSysCfg.appDetailRemindSwitch     = ((uint32)protocal->packet.att.load.content.parameter[0] << 24) 
														+ ((uint32)protocal->packet.att.load.content.parameter[1] << 16)
														+ ((uint32)protocal->packet.att.load.content.parameter[2] << 8)
														+ ((uint32)protocal->packet.att.load.content.parameter[3]);
				// ����flash�洢�¼�
				Store_Task_Msg_T Store_Task_Msg;
				Store_Task_Msg.Id = eStoreTaskMsgCmn;
				Store_Task_Msg.Param.StoreCmn.Id = eStoreCmnEventSysInfoWrite;
				Store_Task_EventSet(&Store_Task_Msg);
			}
			break;
		case PROT_MSG_DETAIL://0x06:��Ϣ����֪ͨ���ɣ�,H002ʹ���µ���Ϣ����֪ͨ
			#if 1
			gtSysCfg.appDetailRemindSwitch = gtSysCfg.appRemindSwitch;	//����������Ϣ���鿪�أ��������ѿ���
			
			//Analy_Debug((0,"appDetailRemindSwitch=0x%x,remind type=%d\n",gtSysCfg.appDetailRemindSwitch,protocal->packet.att.load.content.parameter[0]));
			//fix 8:IOS��Ϣ���عرգ��Կ���Ӧ��Ϣ(���ѣ���ʾ����)��
			if((gtSysCfg.appDetailRemindSwitch & (0x01 << protocal->packet.att.load.content.parameter[0])) == 0x0000)
			{
				return Ret_OK;
			}
			//fix 8:2018.6.20
			if (gtSysCfg.appDetailRemindSwitch && (gtPhoneState.state != PHONE_STATE_PHOTO))//����֪ͨ�Ž��д���
			{
				if(!((gtSysCfg.notDisturbSwitch == SWITCH_ON) && (App_Time_NotDisturdTimeCheck())))//����ʱ����ڲ�����
				{
					if (protocal->packet.att.routeMsg == 0x21)
					{
						gePhoneSystem = IOS;
					}
					else
					{
						gePhoneSystem = ANDROID;
					}
				   App_RemindManage_Process(protocal->packet,gePhoneSystem);
				}
			}
			#endif
			break;
		case PROT_MSG_DETAIL_NEW://0x16:��Ϣ����֪ͨ���£�
		    #if 0
			{
            uint8 i;
            SEGGER_RTT_printf(0,"msg detail Data:\n");
            for(i = 0; i < protocal->packet.att.loadLength + 6; i++)
            {
                SEGGER_RTT_printf(0,"0x%x,",protocal->packet.data[i]);
            }
            SEGGER_RTT_printf(0,"\n");
            }
			#endif
			
            //����������Ϣ���鿪�أ��������ѿ���
            gtSysCfg.appDetailRemindSwitch = gtSysCfg.appRemindSwitch;
            
            //Analy_Debug((0,"appDetailRemindSwitch=0x%x,remind type=%d\n",systermConfig.appDetailRemindSwitch,protocal->packet.att.load.content.parameter[0]));
            //fix 8:IOS��Ϣ���عرգ��Կ���Ӧ��Ϣ(���ѣ���ʾ����)��
            if((gtSysCfg.appDetailRemindSwitch & (0x01 << protocal->packet.att.load.content.parameter[0])) == 0x0000)
            {
                return Ret_OK;
            }
            //fix 8:2018.6.20
            if (gtSysCfg.appDetailRemindSwitch && (gtPhoneState.state != PHONE_STATE_PHOTO))//����֪ͨ�Ž��д���
            {
                if(!((gtSysCfg.notDisturbSwitch == SWITCH_ON) && (App_Time_NotDisturdTimeCheck())))//����ʱ����ڲ�����
                {
                    if (protocal->packet.att.routeMsg == 0x21)
                    {
                        gePhoneSystem = IOS;
                    }
                    else
                    {
                        gePhoneSystem = ANDROID;
                    }
                   App_RemindManage_Process_New(protocal->packet,gePhoneSystem);
                }
            }
			break;
		case PROT_PHOTO_MODE: //����
			if (protocal->packet.att.load.content.parameter[0] == 0x00)//�˳�
			{
				gtPhoneState.state   = PHONE_STATE_NORMAL;
				gtPhoneState.timeCnt = 0;
				UI_Screen_Close_Warn_Screen_Camera();
				 MOD_PDU_RTT_LOG(0,"UI_Screen_Close_Warn_Screen_Camera \n");
			}
			else if (protocal->packet.att.load.content.parameter[0] == 0x01)//����
			{
				gtPhoneState.state   = PHONE_STATE_PHOTO;
				gtPhoneState.timeCnt = 0;
				gtPhoneState.timeMax = APP_TakePhotoTimeOut;
				UI_Screen_Show_Warn_Screen_Camera();
				 MOD_PDU_RTT_LOG(0,"UI_Screen_Show_Warn_Screen_Camera \n");
			}
			Protocal_SendACK(protocal,SUCCESS);
			break;

		case PROT_PHOTO_HEARTBEAT: //��������
			if (gtPhoneState.state == PHONE_STATE_PHOTO)
			{
				gtPhoneState.state   = PHONE_STATE_PHOTO;
				gtPhoneState.timeCnt = 0;
				gtPhoneState.timeMax = APP_TakePhotoTimeOut;
			}
			break;
        case PROT_WATCH_HAND_MODE://У��:0x31
			Protocal_SendACK(protocal,SUCCESS);
			#if 0
			if(protocal->packet.att.load.content.parameter[0] == 0x01)//����У��
			{
				movtState.timeCnt 	= 0;
				movtState.state     = MOVT_STATE_ADJUST;
				movtMsg.id          = MOVT_MSG_MC_STOP;
				MovtTask_EventSet(movtMsg);
				Protocal_SendACK(protocal,SUCCESS);
			}
			else if(protocal->packet.att.load.content.parameter[0] == 0x00)//�˳�У��
			{
				Protocal_SendACK(protocal,SUCCESS);
				movtState.timeCnt 	= 0;
				movtState.state     = MOVT_STATE_NORMAL;
				movtMsg.id          = MOVT_MSG_MC_RECOVER;
				MovtTask_EventSet(movtMsg);
				App_Rtc_Movt();            
			}
			else
			{
				Protocal_SendACK(protocal, PARAMATER_ERROR);
			}
			#else
			Protocal_SendACK(protocal,SUCCESS);
			#endif
			break;

        case PROT_WATCH_HAND_CTRL:
			Protocal_SendACK(protocal, SUCCESS);
			break;
        case PROT_WATCH_HAND_PARAM: // У�������0x33
			Protocal_SendACK(protocal, SUCCESS);
			#if 0
			if (movtState.state == MOVT_STATE_ADJUST)
			{
				//if(protocal->packet.att.load.content.parameter[0] == MOVT_2PIN_M) // ����RTCʱ���Ǹ�����
				 if(protocal->packet.att.load.content.parameter[0] == MOVT_3PIN_M || protocal->packet.att.load.content.parameter[0] == MOVT_2PIN_M) // ����RTCʱ���Ǹ�����
				{
					movtMsg.id          = MOVT_MSG_MC_SET_CUR_AIM;
					movtMsg.cur         = (((uint16_t)protocal->packet.att.load.content.parameter[1] << 8)
										 + protocal->packet.att.load.content.parameter[2])/10;
					movtMsg.aim         = movtMsg.cur;
					MovtTask_EventSet(movtMsg);           
				}
			}
			#endif
			break;
        case PROT_WATCH_HAND_HEARTBEAT: // У����������0x34
			break;
		case PROT_LONG_SIT_SWITCH:    //0x51: ����
			if(protocal->packet.att.load.content.interfaceType == PROTOCAL_SET)
			{
				Protocal_SendACK(protocal,SUCCESS);
				gtSysCfg.longSitRemindSwitch = protocal->packet.att.load.content.parameter[0];

				// ����flash�洢�¼�
				Store_Task_Msg_T Store_Task_Msg;
				Store_Task_Msg.Id = eStoreTaskMsgCmn;
				Store_Task_Msg.Param.StoreCmn.Id = eStoreCmnEventSysInfoWrite;
				Store_Task_EventSet(&Store_Task_Msg);
			}
			else if (protocal->packet.att.load.content.interfaceType == PROTOCAL_GET)
			{
				protocal->packet.att.loadLength += 1;
				protocal->packet.att.routeMsg = u8Route;
				protocal->packet.att.flowControl = u8FlowCtl;
				protocal->packet.att.load.content.interfaceType = PROTOCAL_RET;
				protocal->packet.att.load.content.parameter[0] = gtSysCfg.longSitRemindSwitch;
		
				protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5);  
				Mid_Ble_SendMsg(protocal);
			}
			else
			{
				Protocal_SendACK(protocal,PARAMATER_ERROR);
			}
			break;
		case PROT_LONG_SIT_PARAM:     //0x52: ��������
			if(protocal->packet.att.load.content.interfaceType == PROTOCAL_SET)
			{
				Protocal_SendACK(protocal,SUCCESS);
				lpSedentary->Info.StartTimeHour = ((protocal->packet.att.load.content.parameter[0]>>4) & 0x0f) * 10 			
											   + (protocal->packet.att.load.content.parameter[0] & 0x0f);
				lpSedentary->Info.StartTimeMin  = ((protocal->packet.att.load.content.parameter[1]>>4) & 0x0f) * 10 			
											   + (protocal->packet.att.load.content.parameter[1] & 0x0f);
				lpSedentary->Info.StopTimeHour  = ((protocal->packet.att.load.content.parameter[2]>>4) & 0x0f) * 10 			
											   + (protocal->packet.att.load.content.parameter[2] & 0x0f);
				lpSedentary->Info.StopTimeMin   = ((protocal->packet.att.load.content.parameter[3]>>4) & 0x0f) * 10 			
											   + (protocal->packet.att.load.content.parameter[3] & 0x0f);
				
				lpSedentary->Info.DisturdStartTimehour  = ((protocal->packet.att.load.content.parameter[4]>>4) & 0x0f) * 10 			
														+ (protocal->packet.att.load.content.parameter[4] & 0x0f);
				lpSedentary->Info.DisturdStartTimeMin   = ((protocal->packet.att.load.content.parameter[5]>>4) & 0x0f) * 10 			
														+ (protocal->packet.att.load.content.parameter[5] & 0x0f);
				lpSedentary->Info.DisturdStopTimehour   = ((protocal->packet.att.load.content.parameter[6]>>4) & 0x0f) * 10 			
														+ (protocal->packet.att.load.content.parameter[6] & 0x0f);
				lpSedentary->Info.DisturdStopTimeMin    = ((protocal->packet.att.load.content.parameter[7]>>4) & 0x0f) * 10 			
														+ (protocal->packet.att.load.content.parameter[7] & 0x0f);
				lpSedentary->Info.intv_mimute           = (protocal->packet.att.load.content.parameter[8] *256) + protocal->packet.att.load.content.parameter[9];
				
				//fix :����ʱ��������ϴ󡣸��¾������Ѳ���֮������������������¼���
				if(gtSysCfg.longSitRemindSwitch == 0x01)
				{
				   Scene_Sedentary_Reset();
				}

				// ����flash�洢�¼�
				Store_Task_Msg_T Store_Task_Msg;
				Store_Task_Msg.Id = eStoreTaskMsgCmn;
				Store_Task_Msg.Param.StoreCmn.Id = eStoreCmnEventTimeInfoWrite;
				Store_Task_EventSet(&Store_Task_Msg);
				
			}else if(protocal->packet.att.load.content.interfaceType == PROTOCAL_GET)
			{
				protocal->packet.att.loadLength += 10;
				protocal->packet.att.routeMsg = u8Route;
				protocal->packet.att.flowControl = u8FlowCtl;
				protocal->packet.att.load.content.interfaceType = PROTOCAL_RET;
				protocal->packet.att.load.content.parameter[0] = (lpSedentary->Info.StartTimeHour / 10)<<4 
													   | (lpSedentary->Info.StartTimeHour % 10);
				protocal->packet.att.load.content.parameter[1] = (lpSedentary->Info.StartTimeMin / 10)<<4 
													   | (lpSedentary->Info.StartTimeMin % 10);
				protocal->packet.att.load.content.parameter[2] = (lpSedentary->Info.StopTimeHour / 10)<<4 
													   | (lpSedentary->Info.StopTimeHour % 10);
				protocal->packet.att.load.content.parameter[3] = (lpSedentary->Info.StopTimeMin / 10)<<4 
													   | (lpSedentary->Info.StopTimeMin % 10);
				
				protocal->packet.att.load.content.parameter[4] = (lpSedentary->Info.DisturdStartTimehour / 10)<<4 
													   | (lpSedentary->Info.DisturdStartTimehour % 10);
				protocal->packet.att.load.content.parameter[5] = (lpSedentary->Info.DisturdStartTimeMin / 10)<<4 
													   | (lpSedentary->Info.DisturdStartTimeMin % 10);
				protocal->packet.att.load.content.parameter[6] = (lpSedentary->Info.DisturdStopTimehour / 10)<<4 
													   | (lpSedentary->Info.DisturdStopTimehour % 10);
				protocal->packet.att.load.content.parameter[7] = (lpSedentary->Info.DisturdStopTimeMin / 10)<<4 
													   | (lpSedentary->Info.DisturdStopTimeMin % 10);
				protocal->packet.att.load.content.parameter[8] = (lpSedentary->Info.intv_mimute >> 8)& 0xff;
				protocal->packet.att.load.content.parameter[9] = lpSedentary->Info.intv_mimute & 0xff;
				protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5);  
				Mid_Ble_SendMsg(protocal);
			}
			else
			{
				 Protocal_SendACK(protocal,PARAMATER_ERROR);
			}
			break;
		case PROT_DND_SWITCH:         //0x61: ���ſ���
			if(protocal->packet.att.load.content.interfaceType == PROTOCAL_SET)
			{
				Protocal_SendACK(protocal,SUCCESS);
				gtSysCfg.notDisturbSwitch = protocal->packet.att.load.content.parameter[0];

				// ����flash�洢�¼�
				Store_Task_Msg_T Store_Task_Msg;
				Store_Task_Msg.Id = eStoreTaskMsgCmn;
				Store_Task_Msg.Param.StoreCmn.Id = eStoreCmnEventSysInfoWrite;
				Store_Task_EventSet(&Store_Task_Msg);
			}
			else if(protocal->packet.att.load.content.interfaceType == PROTOCAL_GET)
			{
				protocal->packet.att.loadLength += 1;
				protocal->packet.att.routeMsg = u8Route;
				protocal->packet.att.flowControl = u8FlowCtl;
				protocal->packet.att.load.content.interfaceType = PROTOCAL_RET;
				protocal->packet.att.load.content.parameter[0] = gtSysCfg.notDisturbSwitch;
		
				protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5);  
				Mid_Ble_SendMsg(protocal);
			}
			else
			{
				Protocal_SendACK(protocal,PARAMATER_ERROR);
			}		
			break;
		case PROT_DND_PARAM:          //0x62: ���Ų���
			if(protocal->packet.att.load.content.interfaceType == PROTOCAL_SET)
			{
				Protocal_SendACK(protocal,SUCCESS);
				appNotDisturdTimeInfo.StartHour = ((protocal->packet.att.load.content.parameter[0]>>4) & 0x0f) * 10 			
											   + (protocal->packet.att.load.content.parameter[0] & 0x0f);
				appNotDisturdTimeInfo.StartMin  = ((protocal->packet.att.load.content.parameter[1]>>4) & 0x0f) * 10 			
											   + (protocal->packet.att.load.content.parameter[1] & 0x0f);
				appNotDisturdTimeInfo.StopHour  = ((protocal->packet.att.load.content.parameter[2]>>4) & 0x0f) * 10 			
											   + (protocal->packet.att.load.content.parameter[2] & 0x0f);
				appNotDisturdTimeInfo.StopMin   = ((protocal->packet.att.load.content.parameter[3]>>4) & 0x0f) * 10 			
											   + (protocal->packet.att.load.content.parameter[3] & 0x0f);

				// ����flash�洢�¼�
				Store_Task_Msg_T Store_Task_Msg;
				Store_Task_Msg.Id = eStoreTaskMsgCmn;
				Store_Task_Msg.Param.StoreCmn.Id = eStoreCmnEventTimeInfoWrite;
				Store_Task_EventSet(&Store_Task_Msg);
			}
			else if(protocal->packet.att.load.content.interfaceType == PROTOCAL_GET)
			{
				protocal->packet.att.loadLength += 4;
				protocal->packet.att.routeMsg = u8Route;
				protocal->packet.att.flowControl = u8FlowCtl;
				protocal->packet.att.load.content.interfaceType = PROTOCAL_RET;
				protocal->packet.att.load.content.parameter[0] = (appNotDisturdTimeInfo.StartHour / 10)<<4 
													   | (appNotDisturdTimeInfo.StartHour % 10);
				protocal->packet.att.load.content.parameter[1] = (appNotDisturdTimeInfo.StartMin / 10)<<4 
													   | (appNotDisturdTimeInfo.StartMin % 10);
				protocal->packet.att.load.content.parameter[2] = (appNotDisturdTimeInfo.StopHour / 10)<<4 
													   | (appNotDisturdTimeInfo.StopHour % 10);
				protocal->packet.att.load.content.parameter[3] = (appNotDisturdTimeInfo.StopMin / 10)<<4 
													   | (appNotDisturdTimeInfo.StopMin % 10);
				protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5);  
				Mid_Ble_SendMsg(protocal);
			}
			else
			{
				Protocal_SendACK(protocal,PARAMATER_ERROR);
			}
			break;

		case PROT_SYS_SETTING:  //0x91ϵͳ����
			if(protocal->packet.att.load.content.interfaceType == PROTOCAL_SET)
			{
				Protocal_SendACK(protocal,SUCCESS);
				
				if(protocal->packet.att.load.content.parameter[0] < eSysLangugeMax)
					gtSysCfg.systermLanguge = protocal->packet.att.load.content.parameter[0];
				
				if(protocal->packet.att.load.content.parameter[1] < eSysTimeTypeMax)
					gtSysCfg.systermTimeType = protocal->packet.att.load.content.parameter[1];

				// ����flash�洢�¼�
				Store_Task_Msg_T Store_Task_Msg;
				Store_Task_Msg.Id = eStoreTaskMsgCmn;
				Store_Task_Msg.Param.StoreCmn.Id = eStoreCmnEventSysInfoWrite;
				Store_Task_EventSet(&Store_Task_Msg);

			}else if (protocal->packet.att.load.content.interfaceType == PROTOCAL_GET)
			{
				protocal->packet.att.loadLength += 2;
				protocal->packet.att.routeMsg = u8Route;
				protocal->packet.att.flowControl = u8FlowCtl;
				protocal->packet.att.load.content.interfaceType = PROTOCAL_RET;
				protocal->packet.att.load.content.parameter[0] = gtSysCfg.systermLanguge; 
				protocal->packet.att.load.content.parameter[1] = gtSysCfg.systermTimeType;
				protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5);  
				Mid_Ble_SendMsg(protocal);
			}
			else
			{
				Protocal_SendACK(protocal,PARAMATER_ERROR);
			}
			break;
		default:
			break;
    }
	return Ret_OK;
}

//////////////////////////////////////////////////////////////////////////////////
//                       �豸���ԣ�04H, PROT_DEV_TEST��
//////////////////////////////////////////////////////////////////////////////////


//**********************************************************************
// ��������: ����������������
// ���������bleMsg:Э������
// ���ز�����	
//**********************************************************************
static uint8 Analysis_DevTest(ble_msg_t *protocal)
{
    return Ret_OK;

}

//////////////////////////////////////////////////////////////////////////////////
//                       ��������05H, PORT_SENSOR��
//////////////////////////////////////////////////////////////////////////////////


//**********************************************************************
// ��������: ����������������
// ���������bleMsg:Э������
// ���ز�����	
//**********************************************************************
static uint8 Analysis_Sensor(ble_msg_t *protocal)
{
    return Ret_OK;

}

//////////////////////////////////////////////////////////////////////////////////
//                       ������06H, PROT_UPDATE��
//////////////////////////////////////////////////////////////////////////////////
enum updatetype
{
    UPDATE_OTA = 0x00,
    UPDATE_SCENCE,
    UPDATE_MOVT,
};
//**********************************************************************
// ��������: OTA����
// ���������bleMsg:Э������
// ���ز�����	
//**********************************************************************
static uint8 Analysis_Update(ble_msg_t *protocal)
{
    uint8 u8UpdType = protocal->packet.att.load.content.parameter[0];

    Protocal_SendACK(protocal, SUCCESS);
    vTaskDelay(10);  //�ȴ�ack���ͳɹ�

    switch(u8UpdType)
    {
    case UPDATE_OTA:
        //step 1:�ڴ˴����ӱ����ֳ���Ϣ
    
        //step 2:����OTA flag
        BLE_Stack_StoreOTAFlag();
    
        //step 3:��λϵͳ
    	Mid_SystermReset();
        break;
    }
	
    return Ret_OK;
}

//////////////////////////////////////////////////////////////////////////////////
//                   �ճ��˶�������10H, PROT_DAILY_SPORT_SCENE��
//////////////////////////////////////////////////////////////////////////////////


//**********************************************************************
// ��������: ����������������
// ���������protocal:Э������
// ���ز�����	
//**********************************************************************
static uint8 Analysis_Sport(ble_msg_t *protocal)
{
    uint32  u32temp;
    uint8   u8Route;     //��¼·��
    ble_msg_t bleMsg;
//    stepSportInfo_s  sportInfoTemp;
//    app_task_msg_t  appMsg;
	SceneStepParam_t* tpSceneStep = Scene_Step_ParamPGet();

#if(ENABLE_PRINT_DATA ==1)
    uint8 i;
    RTT_DEBUG_printf(0,"Sport Data:\n");
    for(i = 0; i < protocal->packet.att.loadLength + 6; i++)
    {
        RTT_DEBUG_printf(0,"0x%x,",protocal->packet.data[i]);
    }
    RTT_DEBUG_printf(0,"\n");
#endif
    
    u8Route     = ((protocal->packet.att.routeMsg & 0xf0)>>4) + ( protocal->packet.att.routeMsg<<4); 
	bleMsg.packet = (protocal->packet);
	bleMsg.id     = BLE_MSG_SEND;
    bleMsg.packet.att.routeMsg = u8Route;
	
    switch(protocal->packet.att.load.content.interfaceIndex2)
    {
        case PROT_SCENE_DS_MODE:	// ����ʹ��
			if (protocal->packet.att.load.content.parameter[0] == 0x01) //�����ճ��˶�������
			{
				/* code */
			}
			else
			{

			}
			break;
        case PROT_SCENE_DS_GOAL:	// �˶�Ŀ��
			if(protocal->packet.att.load.content.interfaceType == PROTOCAL_SET)     //set
			{
				u32temp     = 0;
				u32temp    = ((uint32_t)protocal->packet.att.load.content.parameter[0] << 8)
								+ protocal->packet.att.load.content.parameter[1];
				Protocal_SendACK(protocal, SUCCESS);
				Scene_Step_AimSet(u32temp);

			   // ����LCDˢ���¼�
			   App_Schd_TaskMsg_T	AppMsg;
			   AppMsg.Id = eAppSchdMsgLcd;
			   AppMsg.Param.Lcd.ScreenId = Common_Screen_MainID_Step;
			   App_Schd_TaskEventSet(&AppMsg, 0);
			}
			else if(protocal->packet.att.load.content.interfaceType == PROTOCAL_GET)//get
			{
				bleMsg.packet.att.loadLength += 2;
				bleMsg.packet.att.load.content.interfaceType = PROTOCAL_RET; 
				bleMsg.packet.att.load.content.parameter[0] = (tpSceneStep->stepAim >> 8)& 0xff;
				bleMsg.packet.att.load.content.parameter[1] = (uint8)tpSceneStep->stepAim;
				bleMsg.packet.data[bleMsg.packet.att.loadLength + 5]  = BLE_Stack_CheckSum(bleMsg.packet.data,bleMsg.packet.att.loadLength + 5); 
				Mid_Ble_SendMsg(&bleMsg);
			} 
			else
			{
				Protocal_SendACK(protocal, PARAMATER_ERROR);
			}            
			break;
        case PROT_SCENE_DS_TOTAL_APP_STEPS:		// ��ǰ�ܲ���
			bleMsg.packet.att.loadLength += 2;
			bleMsg.packet.att.load.content.interfaceType = PROTOCAL_RET; 
			bleMsg.packet.att.load.content.parameter[0] = (tpSceneStep->totalStep >> 8) & 0xff;
			bleMsg.packet.att.load.content.parameter[1] = (uint8)tpSceneStep->totalStep;
			bleMsg.packet.data[bleMsg.packet.att.loadLength + 5]  = BLE_Stack_CheckSum(bleMsg.packet.data,bleMsg.packet.att.loadLength + 5); 
			Mid_Ble_SendMsg(&bleMsg);
			break;
        case PROT_SCENE_DS_HIS_STEPS:
			break;
        case PROT_SCENE_DS_HIS_STEPS_TRANS:
			break;
		default:
			break;
    }               
    return Ret_OK;
}

//////////////////////////////////////////////////////////////////////////////////
//                       ��ɽ������11H��
//////////////////////////////////////////////////////////////////////////////////


//**********************************************************************
// ��������: ����������������
// ���������protocal:Э������
// ���ز�����	
//**********************************************************************
static uint8 Analysis_Climbing(ble_msg_t *protocal)
{
    return Ret_OK;

}

//////////////////////////////////////////////////////////////////////////////////
//                       �ܲ�������12H��
//////////////////////////////////////////////////////////////////////////////////


//**********************************************************************
// ��������: ����������������
// ���������protocal:Э������
// ���ز�����    
//**********************************************************************
static uint8 Analysis_RunningScene(ble_msg_t *protocal)
{
    return Ret_OK;

}

//////////////////////////////////////////////////////////////////////////////////
//                       ��Ӿ������13H��
//////////////////////////////////////////////////////////////////////////////////


//**********************************************************************
// ��������: ����������������
// ���������protocal:Э������
// ���ز�����    
//**********************************************************************
static uint8 Analysis_SwingScene(ble_msg_t *protocal)
{
    return Ret_OK;

}

//////////////////////////////////////////////////////////////////////////////////
//                      ˯�߳�����14H��
//////////////////////////////////////////////////////////////////////////////////


//**********************************************************************
// ��������: ����������������
// ���������protocal:Э������
// ���ز�����    
//**********************************************************************
static uint8 Analysis_SleepScene(ble_msg_t *protocal)
{
#if(ENABLE_PRINT_DATA ==1)
    uint8 i;
    RTT_DEBUG_printf(0,"DeviceInfo Data:\n");
    for(i = 0; i < protocal->packet.att.loadLength + 6; i++)
    {
        RTT_DEBUG_printf(0,"0x%x,",protocal->packet.data[i]);
    }
    RTT_DEBUG_printf(0,"\n");
#endif

    switch(protocal->packet.att.load.content.interfaceIndex2)
    {
        case DAILY_SLEEP_HABIT_NEW://0x01��	// �ճ�˯��ϰ������
			break;
        case DAILY_SLEEP_GOAL_NEW://0x02	// �ճ�˯��Ŀ������
			break;
        case PROT_SCENE_SLEEP_RECORD_CONTENT://0x03		// ��ȡ���˯�߼�¼��Ŀ
			MOD_PDU_RTT_LOG(0, "PROT_SCENE_SLEEP_RECORD_CONTENT \n");
			Store_PDU_SleepRecordCatalogRTS(protocal->packet.att.flowControl);
			break;
        case PROT_SCENE_SLEEP_RECORD_INFO://0x04��H001�ȵľ�˯�ߵ�����ʽ
			break;
		case PROT_SCENE_SLEEP_RECORD_INFO_NEW:	//0x14�� H002�ĵ���˯�ߵ�����ʽ
			MOD_PDU_RTT_LOG(0, "PROT_SCENE_SLEEP_RECORD_INFO_NEW \n");
			Store_PDU_SleepRecordDataRTS(protocal->packet.att.load.content.parameter[0], protocal->packet.att.flowControl);
			break;
		case PROT_SCENE_SLEEP_RECORD_DEL:	// ����UTCɾ��˯�ߵ���
			MOD_PDU_RTT_LOG(0, "PROT_SCENE_SLEEP_RECORD_DEL \n");
			Protocal_SendACK(protocal, SUCCESS);
			Store_PDU_SleepRecordDelete((uint32_t)((protocal->packet.att.load.content.parameter[0] << 24) + (protocal->packet.att.load.content.parameter[1] << 16) +
										(protocal->packet.att.load.content.parameter[2] << 8) + protocal->packet.att.load.content.parameter[3]), 
										 protocal->packet.att.flowControl);
			break;
        default:
			break;
    }

    return Ret_OK;
}

//////////////////////////////////////////////////////////////////////////////////
//                      ˯�߳�����15H��
//////////////////////////////////////////////////////////////////////////////////


//**********************************************************************
// ��������: ����������������
// ���������protocal:Э������
// ���ز�����    
//**********************************************************************
static uint8 Analysis_HeartScene(ble_msg_t *protocal)
{
//    //uint8   u8temp;      //��¼�м�ֵ
//    uint8   u8Route;     //��¼·��
//    //uint8   u8FlowCtl;   //��¼���غ�
//    ble_msg_t bleMsg;


//#if(ENABLE_PRINT_DATA ==1)
//    uint8 i;
//    RTT_DEBUG_printf(0,"Sport Data:\n");
//    for(i = 0; i < protocal->packet.att.loadLength + 6; i++)
//    {
//        RTT_DEBUG_printf(0,"0x%x,",protocal->packet.data[i]);
//    }
//    RTT_DEBUG_printf(0,"\n");
//#endif
//    
//    u8Route       = ((protocal->packet.att.routeMsg & 0xf0)>>4) + ( protocal->packet.att.routeMsg<<4); 
//    bleMsg.packet = (protocal->packet);
//    bleMsg.id     = BLE_MSG_SEND;
//    bleMsg.packet.att.routeMsg = u8Route;
//    
//    switch(protocal->packet.att.load.content.interfaceIndex2)
//    {
//        case PROT_MEASURE_DATA_HRS_GET:
//        #if 0 //�ݲ�����app���ʳ���
//        u8temp = 0;
//        Mid_Hrm_Read(&u8temp);
//        bleMsg.packet.att.loadLength += 1;
//        bleMsg.packet.att.load.content.interfaceType = PROTOCAL_RET; 
//        bleMsg.packet.att.load.content.parameter[0] = u8temp;
//        bleMsg.packet.data[bleMsg.packet.att.loadLength + 5]  = BLE_Stack_CheckSum(bleMsg.packet.data,bleMsg.packet.att.loadLength + 5); 
//        Mid_Ble_SendMsg(&bleMsg);
//        #endif
//        break;

//        case PROT_MEASURE_DATA_HRS_START:
//        Protocal_SendACK(protocal, SUCCESS);
//        #if 0//�ݲ�����app���ʳ���
//        if (gtPhoneState.state != PHONE_STATE_HRM)
//        {
//            //�������ʳ�����ʱ
//            gtPhoneState.state = PHONE_STATE_HRM;
//            gtPhoneState.timeCnt  = 0;
//            gtPhoneState.timeMax = APP_Hrm_TimeOut;

//            //����ʵʱ���ʼ��
//            msg.id                        = HEARTRATE_ID;       
//            msg.module.hrmEvent.id        = HRM_START;
//            MultiModuleTask_EventSet(msg);
//        }
//        #endif    
//        break;

//        default:
//        break;
//    }                

    return Ret_OK;
}


//////////////////////////////////////////////////////////////////////////////////
//                    ���ݰ����䣨f0H, PROT_PACK_TRANS��
//////////////////////////////////////////////////////////////////////////////////


//**********************************************************************
// ��������: ����������������
// ���������protocal:Э������
// ���ز�����
//**********************************************************************
static uint8 Analysis_PackTrans(ble_msg_t *protocal)
{
    switch(protocal->packet.att.routeMsg)
    {
        case BLE_TO_MCU:
        break;
		
        case APP_TO_MCU:
        switch(protocal->packet.att.load.content.interfaceIndex2)
        {
            case PORT_PACK_TRANS_GET_CONTENT_COUNT://0x10����ȡĿ¼���������ݳ���
				MOD_PDU_RTT_LOG(0, "PORT_PACK_TRANS_GET_CONTENT_COUNT \n");
//				PDU_Upload_CatalogInfoGet(((uint16_t)(protocal->packet.att.load.content.parameter[0]) << 8) + protocal->packet.att.load.content.parameter[1],
//												protocal->packet.att.flowControl);
				Store_PDU_CatalogInfoRTS(((uint16_t)(protocal->packet.att.load.content.parameter[0]) << 8) + protocal->packet.att.load.content.parameter[1],
												protocal->packet.att.flowControl);			
				break;
            case PORT_PACK_TRANS_GET_CONTENT_INFO://0x11���ѻ�֪��Ŀ¼����£�ָ��Ŀ¼��ż��������ͣ���ȡָ�����Ŀ¼����Ϣ
				MOD_PDU_RTT_LOG(0, "PORT_PACK_TRANS_GET_CONTENT_INFO \n");
//				PDU_Upload_CatalogDetailGet(((uint16_t)(protocal->packet.att.load.content.parameter[0]) << 8) + protocal->packet.att.load.content.parameter[1],
//										((uint16_t)(protocal->packet.att.load.content.parameter[2]) << 8) + protocal->packet.att.load.content.parameter[3],
//										protocal->packet.att.flowControl);
				Store_PDU_BaseCatalogDetailRTS(((uint16_t)(protocal->packet.att.load.content.parameter[0]) << 8) + protocal->packet.att.load.content.parameter[1],
										((uint16_t)(protocal->packet.att.load.content.parameter[2]) << 8) + protocal->packet.att.load.content.parameter[3],
										protocal->packet.att.flowControl);
				break;
            case PORT_PACK_TRANS_GET_PKG://0x12�������ϴ�ָ����UTC��Ŀ¼�����������ݶΣ���Ӱ���ż�������ԣ�
				MOD_PDU_RTT_LOG(0, "PORT_PACK_TRANS_GET_PKG \n");
//				PDU_Upload_CatalogDataRTS((uint16_t)((protocal->packet.att.load.content.parameter[0] << 8) + protocal->packet.att.load.content.parameter[1]),
//										(uint32_t)((protocal->packet.att.load.content.parameter[2] << 24) + (protocal->packet.att.load.content.parameter[3] << 16) +
//										(protocal->packet.att.load.content.parameter[4] << 8) + protocal->packet.att.load.content.parameter[5]),
//										(uint16_t)((protocal->packet.att.load.content.parameter[6] << 8) + protocal->packet.att.load.content.parameter[7]),
//										protocal->packet.att.flowControl);
				Store_PDU_CatalogDataRTS((uint16_t)((protocal->packet.att.load.content.parameter[0] << 8) + protocal->packet.att.load.content.parameter[1]),
										(uint32_t)((protocal->packet.att.load.content.parameter[2] << 24) + (protocal->packet.att.load.content.parameter[3] << 16) +
										(protocal->packet.att.load.content.parameter[4] << 8) + protocal->packet.att.load.content.parameter[5]),
										(uint16_t)((protocal->packet.att.load.content.parameter[6] << 8) + protocal->packet.att.load.content.parameter[7]),
										protocal->packet.att.flowControl);			
				break;
            case PORT_PACK_TRANS_AUTO_UPDATE_CONTENT_COUNT:
            case PORT_PACK_TRANS_AUTO_UPDATE_CONTENT_INFO:
				break;
            case PORT_PACK_TRANS_DEL_ALL://0x30 :ɾ����������
				MOD_PDU_RTT_LOG(0, "PORT_PACK_TRANS_DEL_ALL \n");
				Protocal_SendACK(protocal,SUCCESS);
//				PDU_Upload_DeleteAll(protocal->packet.att.flowControl);
				Store_PDU_DeleteAll(protocal->packet.att.flowControl);
				break;
            case PORT_PACK_TRANS_DEL_DATATYPE://0x31 �� ɾ��ָ�����͵�����
				MOD_PDU_RTT_LOG(0, "PORT_PACK_TRANS_DEL_DATATYPE \n");
				Protocal_SendACK(protocal,SUCCESS);
//				PDU_Upload_ClassifyDelete((uint16_t)((protocal->packet.att.load.content.parameter[0] << 8) + protocal->packet.att.load.content.parameter[1]), 
//								protocal->packet.att.flowControl);
				Store_PDU_ClassifyDelete((uint16_t)((protocal->packet.att.load.content.parameter[0] << 8) + protocal->packet.att.load.content.parameter[1]), 
								protocal->packet.att.flowControl);
				break;
            case PORT_PACK_TRANS_DEL_CONTENT_UTC://0x32�� ��UTCɾ������
				MOD_PDU_RTT_LOG(0, "PORT_PACK_TRANS_DEL_CONTENT_UTC \n");
				Protocal_SendACK(protocal,SUCCESS);
//				PDU_Upload_CatalogUTCDelete((uint16_t)((protocal->packet.att.load.content.parameter[0] << 8) + protocal->packet.att.load.content.parameter[1]), 
//											(uint32_t)((protocal->packet.att.load.content.parameter[2] << 24) + (protocal->packet.att.load.content.parameter[3] << 16) +
//											(protocal->packet.att.load.content.parameter[4] << 8) + protocal->packet.att.load.content.parameter[5]),
//											protocal->packet.att.flowControl);
				Store_PDU_UTCCatalogDelete((uint16_t)((protocal->packet.att.load.content.parameter[0] << 8) + protocal->packet.att.load.content.parameter[1]), 
											(uint32_t)((protocal->packet.att.load.content.parameter[2] << 24) + (protocal->packet.att.load.content.parameter[3] << 16) +
											(protocal->packet.att.load.content.parameter[4] << 8) + protocal->packet.att.load.content.parameter[5]),
											protocal->packet.att.flowControl);
				break;
        }
        break;
    default:
        break;
    }
	
    return Ret_OK;
}

//////////////////////////////////////////////////////////////////////////////////
//                    ���ݰ����䣨f0H, PROT_PACK_TRANS��
//////////////////////////////////////////////////////////////////////////////////


//**********************************************************************
// ��������: ����������������
// ���������protocal:Э������
// ���ز�����    
//**********************************************************************
static uint8 Analysis_ScenePackTrans(ble_msg_t *protocal)
{
    switch(protocal->packet.att.routeMsg)
    {
        case BLE_TO_MCU:
			break;
        case APP_TO_MCU:
        switch(protocal->packet.att.load.content.interfaceIndex2)
        {
            case PORT_SCENE_PACK_TRANS_GET_CONTENT_COUNT://0x10����ȡĿ¼���������ݳ���
				MOD_PDU_RTT_LOG(0, "PORT_SCENE_PACK_TRANS_GET_CONTENT_COUNT \n");
//				PDU_Scene_CatalogInfoGet(((uint16_t)(protocal->packet.att.load.content.parameter[0]) << 8) + protocal->packet.att.load.content.parameter[1],
//												protocal->packet.att.flowControl);	
				Store_PDU_CatalogInfoRTS(((uint16_t)(protocal->packet.att.load.content.parameter[0]) << 8) + protocal->packet.att.load.content.parameter[1],
												protocal->packet.att.flowControl);
				break;
            case PORT_SCENE_PACK_TRANS_GET_CONTENT_INFO://0x11���ѻ�֪��Ŀ¼����£�ָ��Ŀ¼��ż��������ͣ���ȡָ�����Ŀ¼����Ϣ 
				MOD_PDU_RTT_LOG(0, "PORT_SCENE_PACK_TRANS_GET_CONTENT_INFO \n");
//				PDU_Scene_CatalogDetailGet(((uint16_t)(protocal->packet.att.load.content.parameter[0]) << 8) + protocal->packet.att.load.content.parameter[1],
//										((uint16_t)(protocal->packet.att.load.content.parameter[2]) << 8) + protocal->packet.att.load.content.parameter[3],
//										protocal->packet.att.flowControl);	
				Store_PDU_SceneCatalogDetailRTS(((uint16_t)(protocal->packet.att.load.content.parameter[0]) << 8) + protocal->packet.att.load.content.parameter[1],
										((uint16_t)(protocal->packet.att.load.content.parameter[2]) << 8) + protocal->packet.att.load.content.parameter[3],
										protocal->packet.att.flowControl);	
				break;
            case PORT_SCENE_PACK_TRANS_GET_PKG://0x12�������ϴ�ָ����UTC��Ŀ¼�����������ݶΣ���Ӱ���ż�������ԣ� 
				MOD_PDU_RTT_LOG(0, "PORT_SCENE_PACK_TRANS_GET_PKG \n");
//				PDU_Scene_CatalogDataRTS((uint16_t)((protocal->packet.att.load.content.parameter[0] << 8) + protocal->packet.att.load.content.parameter[1]),
//										(uint32_t)((protocal->packet.att.load.content.parameter[2] << 24) + (protocal->packet.att.load.content.parameter[3] << 16) +
//										(protocal->packet.att.load.content.parameter[4] << 8) + protocal->packet.att.load.content.parameter[5]),
//										(uint16_t)((protocal->packet.att.load.content.parameter[6] << 8) + protocal->packet.att.load.content.parameter[7]),
//										protocal->packet.att.flowControl);
				Store_PDU_CatalogDataRTS((uint16_t)((protocal->packet.att.load.content.parameter[0] << 8) + protocal->packet.att.load.content.parameter[1]),
										(uint32_t)((protocal->packet.att.load.content.parameter[2] << 24) + (protocal->packet.att.load.content.parameter[3] << 16) +
										(protocal->packet.att.load.content.parameter[4] << 8) + protocal->packet.att.load.content.parameter[5]),
										(uint16_t)((protocal->packet.att.load.content.parameter[6] << 8) + protocal->packet.att.load.content.parameter[7]),
										protocal->packet.att.flowControl);
				break;
            case PORT_SCENE_PACK_TRANS_AUTO_UPDATE_CONTENT_COUNT:	// �Զ��ϴ�Ŀ¼��
				break;
            case PORT_SCENE_PACK_TRANS_AUTO_UPDATE_CONTENT_INFO:	// �Զ��ϴ�Ŀ¼����
				break;
            case PORT_SCENE_PACK_TRANS_DEL_ALL://0x30 :ɾ����������
				MOD_PDU_RTT_LOG(0, "PORT_SCENE_PACK_TRANS_DEL_ALL \n");
				Protocal_SendACK(protocal,SUCCESS);
				Store_PDU_DeleteAll(protocal->packet.att.flowControl);
				break;
            case PORT_SCENE_PACK_TRANS_DEL_DATATYPE://0x31 �� ɾ��ָ�����͵�����
				MOD_PDU_RTT_LOG(0, "PORT_SCENE_PACK_TRANS_DEL_DATATYPE \n");
				Protocal_SendACK(protocal,SUCCESS);
				Store_PDU_ClassifyDelete((uint16_t)((protocal->packet.att.load.content.parameter[0] << 8) + protocal->packet.att.load.content.parameter[1]), 
								protocal->packet.att.flowControl);			
				break;
            case PORT_SCENE_PACK_TRANS_DEL_CONTENT_UTC://0x32�� ��UTCɾ������
				MOD_PDU_RTT_LOG(0, "PORT_SCENE_PACK_TRANS_DEL_CONTENT_UTC \n");
				Protocal_SendACK(protocal,SUCCESS);
				Store_PDU_UTCCatalogDelete((uint16_t)((protocal->packet.att.load.content.parameter[0] << 8) + protocal->packet.att.load.content.parameter[1]), 
											(uint32_t)((protocal->packet.att.load.content.parameter[2] << 24) + (protocal->packet.att.load.content.parameter[3] << 16) +
											(protocal->packet.att.load.content.parameter[4] << 8) + protocal->packet.att.load.content.parameter[5]),
											protocal->packet.att.flowControl);			
            break;
        }
        break;
    default:
        break;
    }
    return Ret_OK;
}


//fix 3: �������Ӻͻ�оapp���Ӳ�ͬ�����⣬��Ҫ���������㲥
//**********************************************************************
// ��������: ���������㲥
// ���������    
// ���ز�����
//**********************************************************************
static void App_Protocal_ResetAdv(void)
{
    uint8 u8BleConnStatus;
    static uint8 u8ConnExpFlag = FALSE;//��ʾ�����쳣��־
    static uint32 u32ConnTimeout = 0;

    //step 1:��ȡ������·����״̬
    BLE_Stack_Interact(BLE_STATUS_GET,&u8BleConnStatus,0x00); //��ȡ��������״̬

    //step 2:�ж������Ƿ�������²㲻ͬ��
    //���²����Ӳ�ͬ������: �����������ϣ�app��Disconnect״̬
    if((u8BleConnStatus == BT_CONNECTED) && (eAppProBleConn == APP_PROTOCAL_DISCONNECTED) && (u8ConnExpFlag == FALSE))
    {
        u32ConnTimeout = SMOS_GetTickCount();
        u8ConnExpFlag = TRUE;  //��⵽���²����Ӳ�ͬ��
        Err_Info((0,"Error: App check that connect is no same\n"));
    }

    //step 2-1:���²�����ͬ����reset�����쳣��־
    if(((u8BleConnStatus == BT_CONNECTED) && (eAppProBleConn >= APP_PROTOCAL_ANCSDISCOVER)) ||
        ((u8BleConnStatus == BT_ADV_ON) && (eAppProBleConn == APP_PROTOCAL_DISCONNECTED)))
    {
        //Err_Info((0,"warning: reset connect flag\n"));
        u8ConnExpFlag = FALSE;   //��λ�����쳣��־
    }

    //step 3:�ϲ���������Ӳ�ͬ��һ:���������ϣ�appδ���ӣ����������㲥
    //���������㲥����:�������²����Ӳ�ͬ�������ҳ���10s
    if((u8ConnExpFlag == TRUE) && ((SMOS_GetTickCount() - u32ConnTimeout) >= BLE_CONNECT_ERROR_TIMEOUT))
    {
        uint8 u8adv;

        Err_Info((0,"Error: connect is wrong,need resart BLE ADV\n"));
        //step 3-1: �رչ㲥
        u8adv = BT_ADV_OFF;
        BLE_Stack_Interact(BLE_STATUS_SET,&u8adv,0);

        //step 3-2: �����㲥
        u8adv = BT_ADV_ON;
        BLE_Stack_Interact(BLE_STATUS_SET,&u8adv,0);
        u8ConnExpFlag = FALSE;     //��λ�����쳣��־
    }

    //step 4:�ϲ���������Ӳ�ͬ����:app�����ϣ������ǶϿ����������Ҫ��λ������ʾ״̬
    //  ����app����״̬Ϊ�Ͽ��������һ������жϣ���ʱ��Ƭ���л�task��ʱ����
    if((u8BleConnStatus == BT_ADV_ON) && (eAppProBleConn >= APP_PROTOCAL_ANCSDISCOVER))
    {        
        App_Ble_UpdateConnStatus(APP_PROTOCAL_DISCONNECTED); //�����Ͽ�
        App_BleStatus_Change((uint8)BT_ADV_ON);
    }
    //step 3 ��step 4:��Ϊ��ͬ���ϲ�����������ϵĲ�ͬ��
}
//fix: 2018.6.6

//fix 4:����OTA�����и�״̬�ķ���
//**********************************************************************
// ��������: OTA�������ݳ�ʱ
// ���������u8status:����״̬
// ���ز�����
//**********************************************************************
static uint8 App_Ble_CheckRecvTimeout(void)
{
    if(BLE_Stack_GetMode() == BLE_MODE_OTA)
    {
//        menuMessage message;

        if((SMOS_GetTickCount() - u32OtaRecvTimeout) >= BLE_OTA_RECV_TIMEOUT)
        {
            //fix 6: system will go back normal mode, due to ota fail.
            BLE_Stack_SetMode(BLE_MODE_NORMAL);
            //fix: 2018.6.12

            //step 1: exit ota mode
//            App_OtaSystermRecover();
//            message.state = OTA_EXIT;
//            message.op    = OTA_REMIND;
//            WinDowHandle  = App_Window_Process(WinDowHandle,TAG_REMIND,message);
        }

        return TRUE;
    }
    return FALSE;
}

//**********************************************************************
// ��������: ����OTA״̬
// ���������u8status:����״̬
// ���ز�����
// ˵    ��: ����ʵ���� App_Protocal_OTAStatus��
//**********************************************************************
static void App_Ble_UpdateOTAStatus(Ble_Ota_Status status)
{
    if(status == BLE_OTA_START)   //OTA������ʼ,��Ļ��ʾ"������..."
    {
        //fix 6: system will be in OTA mode, other module will stop working.
        BLE_Stack_SetMode(BLE_MODE_OTA);
        //fix: 2018.6.12
        //fix 7:�ӿ�ʼOTA��ʱ��ʼ��ʱ����Щ�ֻ����ֽ������ݾͳ�ʱ
        u32OtaRecvTimeout = SMOS_GetTickCount();
        //fix 7:2018.6.13

        //step :����Ӧ�����Ĺ��ܣ���Ļ��ʾ
//        App_BleOTA_Cb(0x01);
    }
    else if(status == BLE_OTA_RECV)   //OTA�����������ݣ����ճ�ʱ����
    {
        u32OtaRecvTimeout = SMOS_GetTickCount();
    }
    else if(status == BLE_OTA_RESET)   //OTA������λ
    {
//        App_BleOTA_Cb(0x02);
    }
    else if(status == BLE_OTA_ERROR)   //OTA����ʧ��,��Ļ�˳���ʾ������ʾ
    {
        //fix 6: system will go back normal mode, due to ota fail.
        BLE_Stack_SetMode(BLE_MODE_NORMAL);
        //fix: 2018.6.12
        
        //step : exit ota mode
//        App_BleOTA_Cb(0x00);
    }
    else
        ;
}
//fix: 2018.6.7

//**********************************************************************
// ��������: ����״̬�����ı�֪ͨ
// ���������echo:֪ͨ״̬���ͣ�u8Status:״̬
// ���ز�����
//**********************************************************************
static void App_Ble_Echo(Ble_Echo_Type echo,uint32 u32Status,uint8 u8Option)
{
//     menuMessage         message;

    if(echo == BLE_CONN_STATUS_ECHO)
    {
        //u32Status:����״̬��u8Option:����Э��ջ������Ϣ
        Analy_Debug((0,"App_Ble_Echo =%d,reason=0x%x\n",u32Status,u8Option));
        //fix 1:ֻ���ڻ�оapp�����ϵ�״̬�£��Ÿ����������ӶϿ���״̬��
        //      �Ա������ֻ����о���ӹ����г������Ӳ��ȶ����ص����쳣�Ͽ�״̬
        if((eAppProBleConn > APP_PROTOCAL_DISCONNECTED) && (u32Status == BT_ADV_ON))
        {
            if(eAppProBleConn >= APP_PROTOCAL_ANCSDISCOVER)
            {
				if (SWITCH_ON == gtSysCfg.bleDiscRemindSwitch)//���ӶϿ�
				/* ���������Ͽ������¼� */
				{
					UI_Screen_Show_Warn_Screen_Btconnect();
					Mid_Motor_ShakeStart(eMidMotorShake1Hz, 3);	
//					MOD_PDU_RTT_LOG(0, " UI_Screen_Show_Warn_Screen_Btconnect \n");
				}
            }

            App_Ble_UpdateConnStatus(APP_PROTOCAL_DISCONNECTED); //�����Ͽ�
        }
        //fix 1: 2018.6.1
    }
    else if(echo == BLE_PAIRING_PASSKEY_ECHO)
    {
//        Analy_Debug((0,"paring pass key =%d\n",u32Status));
        //��ʾ�������pin��(passkey)
//        MultiModuleTask_EventSet(PAIRE_MOTO);
//		gtPhoneState.timeCnt  = 0;
//		gtPhoneState.timeMax  = APP_PaireTimeOut;
//        gtPhoneState.state    = PHONE_STATE_PAIRE;
//        message.val   = u32Status;
//        message.state = ENTER_PAIRE_STATE;
//        message.op    = PAIRE_REMIND;
//        WinDowHandle  = App_Window_Process(WinDowHandle,TAG_REMIND,message);
    }
    else if(echo == BLE_PAIRING_AUTH_STATUS)
    {
//        Analy_Debug((0,"paring auth result =%d\n",u32Status));
//        //u32Status = 0x00:��Գɹ���=0x01:���ʧ��
//        message.val   = u32Status;
//        message.state = EXIT_PAIRE_STATE;
//        message.op    = PAIRE_REMIND;
//        WinDowHandle  = App_Window_Process(WinDowHandle,TAG_REMIND,message);

        //fix 3:�������Ӻͻ�оapp����ͬ������
        if(u32Status == 0x00)
        {
            //��Գɹ������ӳɹ�
            App_Ble_UpdateConnStatus(APP_PROTOCAL_CONNECTED); //��������
        }
        else
        {
            //���ʧ�ܣ������Զ��Ͽ�
            App_Ble_UpdateConnStatus(APP_PROTOCAL_DISCONNECTED); //�����Ͽ�
        }
        //fix
    }
    else if(echo == BLE_OTA_ECHO)      //OTA����״̬����
    {
        Analy_Debug((0,"OTA =%d\n",u32Status));
        //fix 4:����OTA�����и�״̬�ķ���
        App_Ble_UpdateOTAStatus((Ble_Ota_Status)u32Status);
        //fix: 2018.6.7
    }
    else if(echo == BLE_ANCS_DISCOVERING)
    {
        //fix 3:ANCS��λ���֣�����ֻ�ֻ������������Ӧ��APP��Ҳ����֧��ANCS����
        App_Ble_UpdateConnStatus(APP_PROTOCAL_ANCSDISCOVER);

        //fix:IOS�ֻ�ANCS���ܲ���Ҫapp֧�֣��յ����¼���������ʾ����״̬
        geBleState = BLE_CONNECT;   // just for ancs
    }
    else
        ;
}

//**********************************************************************
// ��������: Э�����������
// ���������protocal:Э������
// ���ز�����
//**********************************************************************
static void Protocal_Analysis(ble_msg_t *protocal)
{   
    if(protocal->packet.att.loadLength == 1)
    {
        // ����ACK��ɾ���ط�����
        Mid_Ble_DelResendMsg(&protocal->packet);
        return ;
    }
	
	#if 1	// debug
	MOD_PDU_RTT_LOG(0, "BLE_RX %02X %02X %02X %02X %02X, ",	
								protocal->packet.att.startSign, 
								protocal->packet.att.version, 
								protocal->packet.att.loadLength, 
								protocal->packet.att.routeMsg,
								protocal->packet.att.flowControl);
	MOD_PDU_RTT_LOG(0, "%02X %02X %02X, ",protocal->packet.att.load.content.interfaceType, 
														protocal->packet.att.load.content.interfaceIndex1,
														protocal->packet.att.load.content.interfaceIndex2);
	if(protocal->packet.att.loadLength >= 3)	
	{
		for(uint32_t i = 0;i < (protocal->packet.att.loadLength-3);i++)  //(msg->packet.att.loadLength-3)
		{
			RTT_DEBUG_LOG(0, "%02X ", protocal->packet.att.load.content.parameter[i]);
		}RTT_DEBUG_LOG(0, "\n");
	}
	else
	// ACK��loadLengthΪ1
	{
		for(uint32_t i = 0;i < protocal->packet.att.loadLength;i++)  //(msg->packet.att.loadLength-3)
		{
			RTT_DEBUG_LOG(0, "%02X ", protocal->packet.att.load.content.parameter[i]);
		}RTT_DEBUG_LOG(0, "\n");
	}	
	#endif
	
    switch(protocal->packet.att.load.content.interfaceIndex1)
    {
    case PROT_LINK:              //0x00:��·����
        Analysis_Link(protocal);
        break;
    case PROT_DEV_INFO:          //0x01:�豸��Ϣ
        Analysis_DeviceInfo(protocal);
        break;
    case PROT_INTERACT:          //0x03:��������
        Analysis_Interact(protocal);
        break;
    case PROT_DEV_TEST:          //0x04:�豸����
        Analysis_DevTest(protocal);    
        break;
    case PROT_SENSOR:            //0x05:������
        Analysis_Sensor(protocal); 
        break;
    case PROT_UPDATE:            //0x06:����
        Analysis_Update(protocal);
        break;
    case PROT_APP_SPORT_SCENE:   //0x10:�ճ��˶�����
        Analysis_Sport(protocal);
        break;
    case PROT_MOUNTAINEER_SCENE: //0x11:��ɽ����
        Analysis_Climbing(protocal);
        break;
    case PROT_RUNNING_SCENE: //0x12:�ܲ�����
        Analysis_RunningScene(protocal);
        break;
    case PROT_SWIMING_SCENE: //0x13:��Ӿ����
        Analysis_SwingScene(protocal);
        break;
    case PROT_SLEEP_SCENE: //0x14:˯�߳���
        Analysis_SleepScene(protocal);
        break;
    case PROT_HRS_SCENE: //0x15:���ʳ���
        Analysis_HeartScene(protocal);
        break;
    case PROT_PACK_TRANS:        //0xf0:���ݰ�����
        Analysis_PackTrans(protocal);
        break;
    case PROT_SCENE_PACK_TRANS:        //0xf2:�������ݰ�����
		Analysis_ScenePackTrans(protocal);
		break;
    case PROT_EVENT:             //0x02: ���޶���
    default:
        break;
    }
}

//**********************************************************************
// ��������: OTA״̬����
// ���������u16param: = 0x00:�˳�OTA����
//           = 0x01: ����OTA����
//           = 0x02: OTA������λ
// ���ز�����
//**********************************************************************
void App_Protocal_OTAStatus(uint16 u16param)
{
//    menuMessage  message;

    if(u16param == 0x01)   //����OTA����
    {
//        App_OtaSystermSuspend();
//        message.state = OTA_ENTER;
//        message.op    = OTA_REMIND;
//        WinDowHandle  = App_Window_Process(WinDowHandle,TAG_REMIND,message);
    }
    else if(u16param == 0x00)  //�˳�OTA����
    {
//        App_OtaSystermRecover();
//        message.state = OTA_EXIT;
//        message.op    = OTA_REMIND;
//        WinDowHandle  = App_Window_Process(WinDowHandle,TAG_REMIND,message);
    }
    else if(u16param == 0x02)  //OTA������λ
    {
//        //step 1:write OTA reset flag to flash
//        App_WriteResetFlag(OTA_RESET);
//        //step 1: ��mcu��λ֮ǰ��������
//        //�������ݴ洢
//        App_CacheDataSaveAll();    
//        
//        //step 2: ��λMCU
//        SMDrv_SYS_Rest_POI();
    }
    else
        ;
}

//**********************************************************************
// ��������: �����Ͽ�ʱ���öϿ�״̬���˳�OTA��������
// ���������
// ���ز�����
//**********************************************************************
void App_Protocal_BleDisConn(void)
{
//    menuMessage  message;

    //fix 5: �����쳣�Ͽ������ֿ��������,���Ͽ�����
    if(BLE_Stack_GetMode() == BLE_MODE_OTA)
    {
        //fix 6: system will go back normal mode, due to ota fail.
        BLE_Stack_SetMode(BLE_MODE_NORMAL);
        //fix 6: 2018.6.12
    
        //step : exit ota mode
//        App_OtaSystermRecover();
//        message.state = OTA_EXIT;
//        message.op    = OTA_REMIND;
//        WinDowHandle  = App_Window_Process(WinDowHandle,TAG_REMIND,message);
    }

    App_BleStatus_Change((uint8)BT_ADV_ON);
    //fix 5:  2018.6.9
}

//**********************************************************************
// ��������: ��������״̬��OTA�������ճ�ʱ���
// ���������    
// ���ز�����
//**********************************************************************
void App_Protocal_Monitor(void)
{
    //step 1: ��������״̬���
    //App_Protocal_ResetAdv();

    //step 2: OTA�������ݳ�ʱ����
    App_Ble_CheckRecvTimeout();
}

//**********************************************************************
// ��������: ��ʼ��Э�����ģ�飬��mid��ע��Э������ص�����
// ���������    
// ���ز�����
//**********************************************************************
void App_Protocal_Init(void)
{
    //step 2:Set exchange callback
    Mid_Ble_SetCallBack(Protocal_Analysis);
    //Set BLE Echo status callback
    BLE_Stack_SetEcho_CallBack(App_Ble_Echo);
#if((ANCS_VER_TYPE  == ANCS_VER_2) && (ANCS_DETIL_TYPE != ANCS_NONE))
    BLE_Stack_SetAncsCallBack(App_RemindManage_ParseAncs);
#endif
}

//**********************************************************************
// ��������: ��Ȩ�ɹ�
// ���������    
// ���ز�����
//**********************************************************************
void App_Protocal_AuthorPass(void)
{
	ble_msg_t bleMsg;
    uint8 u8len,u8BleConnStatus;

    //fix 2: �ֻ�������Ȩ����;�Ͽ��������Ϻ󲻷�������Ȩ����о������Ȩ�ɹ�������
    //  �ڽ��յ�������Ȩ����������ϵ�״̬ʱ���ܷ�����Ȩ�ɹ�����
    //  a.�н��յ�������Ȩ�����������Ȩ��
    //  b.�Ƚ��յ���Ȩ���󣬺��жϿ������������Ϊû�н��յ���Ȩ����
    if(eAppProBleConn >= APP_PROTOCAL_RECVAUTHREQEST)
    {
    	bleMsg.id = BLE_MSG_SEND;
    	bleMsg.packet = AUTHOR_PASS_PROTOCAL;
        u8len = bleMsg.packet.att.loadLength + 5;
    	bleMsg.packet.data[u8len] = BLE_Stack_CheckSum(bleMsg.packet.data,bleMsg.packet.att.loadLength + 5);
        Mid_Ble_SendMsg(&bleMsg);
    
        //fix 1: ��о������Ȩ�ɹ�����󣬻�оapp��������״̬
        BLE_Stack_Interact(BLE_STATUS_GET,&u8BleConnStatus,0x00); //��ȡ��������״̬
        if(u8BleConnStatus == BT_CONNECTED)
        {
            App_Ble_UpdateConnStatus(APP_PROTOCAL_CONNECTED);
            App_BleStatus_Change((uint8)BT_CONNECTED);
        }
        else
        {
            App_Ble_UpdateConnStatus(APP_PROTOCAL_DISCONNECTED);
        }
        //fix 1: 2018.6.1
    }
    //fix 2: 2018.6.4
}


//**********************************************************************
// ��������: ����
// ���������
// ���ز�����
//**********************************************************************
void App_Protocal_TakePhoto(void)
{
	ble_msg_t bleMsg;
    uint8 u8len;

	bleMsg.id = BLE_MSG_SEND;
	bleMsg.packet = TACK_PICTURE_PROTOCAL;
    u8len = bleMsg.packet.att.loadLength + 5;
	bleMsg.packet.data[u8len] = BLE_Stack_CheckSum(bleMsg.packet.data,bleMsg.packet.att.loadLength + 5);
    Mid_Ble_SendMsg(&bleMsg);
	
	Mid_Motor_ShakeStart(eMidMotorShake1Hz, 1);
}

//**********************************************************************
// ��������: �����ֻ�
// ���������    
// ���ز�����
//**********************************************************************
void App_Protocal_FinePhone(void)
{
	ble_msg_t bleMsg;
    uint8 u8len;

	bleMsg.id = BLE_MSG_SEND;
	bleMsg.packet   = FIND_PHONE_PROTOCAL;
    u8len = bleMsg.packet.att.loadLength + 5;
	bleMsg.packet.data[u8len] = BLE_Stack_CheckSum(bleMsg.packet.data,bleMsg.packet.att.loadLength + 5);
    Mid_Ble_SendMsg(&bleMsg);
}

//**********************************************************************
// ��������: ��������ʱ�ķ���
// ���������
//	 fePhoneSystem: �ֻ�ϵͳ���ͣ���׿ IOS
//   fePhoneCallOpt    :���ܽӣ��������
// ���ز�����
//**********************************************************************
void App_Protocal_PhoneCallRet(PhoneSystem_e fePhoneSystem, PhoneCallOpt_e fePhoneCallOpt)
{
    ble_msg_t bleMsg;
    uint8 u8len;
	
	if(fePhoneCallOpt < ePhoneCallIgnore)
	/* ��ʱû���������ָ�� */
	{
		bleMsg.id = BLE_MSG_SEND;
		if (fePhoneSystem == IOS )
		{
			bleMsg.packet = ACCEPT_CALL_IOS_PROTOCAL;
		}
		else
		{
			bleMsg.packet = ACCEPT_CALL_PROTOCAL;
		}		
		
		bleMsg.packet.att.load.content.parameter[0] = fePhoneCallOpt;
		u8len = bleMsg.packet.att.loadLength + 5;
		bleMsg.packet.data[u8len] = BLE_Stack_CheckSum(bleMsg.packet.data,bleMsg.packet.att.loadLength + 5);
		Mid_Ble_SendMsg(&bleMsg);	
	}
}

//**********************************************************************
// ��������: ����״̬����
// ���������newblestate
// ���ز�����
//**********************************************************************
void App_Protocal_BleStateSet(uint8 newblestate)
{
   if((newblestate != BLE_SLEEP) && (newblestate != BLE_BROADCAST) && //��,���㲥
      (newblestate != BLE_POWERON) && (newblestate != BLE_POWEROFF))  //�����ϵ� /����
       return ;
   


	if ((newblestate == BLE_POWERON) || (newblestate == BLE_POWEROFF))
	{
		BLE_Stack_Interact(BLE_POWERONOFF,&newblestate,0);
	}
	else
	{
		BLE_Stack_Interact(BLE_STATUS_SET,&newblestate,0);
	}
	
	/* �޸�����״̬ */
	if((newblestate == BLE_POWERON) || (newblestate == BLE_BROADCAST))
	{
		geBleState = BLE_BROADCAST;	
	}
	
	if(newblestate == BLE_SLEEP)
	{
		geBleState = BLE_SLEEP;	
	}
	
	if(newblestate == BLE_POWEROFF)
	{
		geBleState = BLE_POWEROFF;
	}
}

//**********************************************************************
// ��������: �ֱ���������ͬ��ʱ��
// ���������
// ���ز�����
//**********************************************************************
void App_Protocal_AdjustTimeprocess(void)
{
    ble_msg_t bleMsg;
    uint8 u8len;

    bleMsg.id = BLE_MSG_SEND;
    bleMsg.packet   = ADJUST_TIME_PROTOCAL;
    u8len = bleMsg.packet.att.loadLength + 5;
    bleMsg.packet.data[u8len] = BLE_Stack_CheckSum(bleMsg.packet.data,bleMsg.packet.att.loadLength + 5);
    Mid_Ble_SendMsg(&bleMsg);
}

//**********************************************************************
// ��������: �ֱ���������������Ϣ
// ���������
// ���ز�����
//**********************************************************************
void App_Protocal_GetWeatherProcess(void)
{
    ble_msg_t bleMsg;
    uint8 u8len;
    bleMsg.id = BLE_MSG_SEND;
    bleMsg.packet   = GET_WEATHER_PROTOCAL;
    u8len = bleMsg.packet.att.loadLength + 5;
    bleMsg.packet.data[u8len] = BLE_Stack_CheckSum(bleMsg.packet.data,bleMsg.packet.att.loadLength + 5);
    Mid_Ble_SendMsg(&bleMsg);
}

//**********************************************************************
// ��������: ���������㲥��
// ���������    
// ���ز�����
//**********************************************************************
void App_Protocal_SetBtAdvName(uint8 *name)
{
    uint8 u8len = 0;

    if(name == NULL) return ;

    while(name[u8len] != '\0')u8len++;
    u8len %= 12;

    BLE_Stack_Interact(BLE_AVD_NAME_SET,name,u8len);
}

//**********************************************************************
// ��������: ������������
// ������������ӱ��    
// ���ز�����
//**********************************************************************
void App_Protocal_AlarmRing(uint8 alarmId)
{
    ble_msg_t bleMsg;

    bleMsg.id       = BLE_MSG_SEND;
    bleMsg.packet   = ALARM_TO_APP_PROTOCAL;
    bleMsg.packet.att.load.content.parameter[0] = alarmId;
    bleMsg.packet.data[bleMsg.packet.att.loadLength + 5] = BLE_Stack_CheckSum(bleMsg.packet.data,bleMsg.packet.att.loadLength + 5);
    Mid_Ble_SendMsg(&bleMsg);
}

//**********************************************************************
// ��������: �������ʳ����µ�����ֵ
// ���������ʵʱ����ֵ    
// ���ز�����
//**********************************************************************
void App_Protocal_HrmRet(uint8 hrval)
{
    ble_msg_t bleMsg;

    bleMsg.id       = BLE_MSG_SEND;
    bleMsg.packet   = HRM_TO_APP_PROTOCAL;
    bleMsg.packet.att.load.content.parameter[0] = hrval;
    bleMsg.packet.data[bleMsg.packet.att.loadLength + 5] = BLE_Stack_CheckSum(bleMsg.packet.data,bleMsg.packet.att.loadLength + 5);
    Mid_Ble_SendMsg(&bleMsg);
}

//**********************************************************************
// ��������: �������Ӽ��
// ���������
// ���ز�����
//**********************************************************************
void App_Protocal_SetConnInterval(uint8 u8Inter)
{
	BLE_Stack_Interact(BLE_AVD_NAME_SET,&u8Inter,0);
}

//**********************************************************************
// ��������: ����SN��
// ���������
// protocal: Э������ָ��
// ���ز�����
//**********************************************************************
void App_Protocal_RetSN(ble_msg_t *protocal)
{
     uint8           snData[30];

    uint8   u8Route;     //��¼·��
    uint8   u8FlowCtl;   //��¼���غ�

    protocal->id = BLE_MSG_SEND;
    u8Route     = ((protocal->packet.att.routeMsg & 0xf0)>>4) + ( protocal->packet.att.routeMsg<<4); 
    u8FlowCtl   = protocal->packet.att.flowControl; 

	/* ��flash��ȡSN */
	Store_Cmn_SnRead(snData, 20);
	
    protocal->packet.att.loadLength += 0x0B;
    protocal->packet.att.routeMsg = u8Route;
    protocal->packet.att.flowControl = u8FlowCtl;
    protocal->packet.att.load.content.interfaceType = PROTOCAL_RET;

	/* ����SN��10�ֽ� */
    protocal->packet.att.load.content.parameter[0]  = 0; //��ʮ�ֽ�
	memcpy(protocal->packet.att.load.content.parameter+1, snData, 10);
    protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5); 
    Mid_Ble_SendMsg(protocal);
    vTaskDelay(2);
	
	/* ����SN��10�ֽ� */
    protocal->packet.att.load.content.parameter[0] = 1; //��ʮ�ֽ�
	memcpy(protocal->packet.att.load.content.parameter+1, snData+10, 10);
    protocal->packet.data[protocal->packet.att.loadLength + 5]  = BLE_Stack_CheckSum(protocal->packet.data,protocal->packet.att.loadLength + 5); 
    Mid_Ble_SendMsg(protocal);
}



    
    


