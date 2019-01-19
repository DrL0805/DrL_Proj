#ifndef         BLE_TASK_H
#define         BLE_TASK_H

/* FreeRTOS includes */
#include "rtos.h"
#include "platform_common.h"
#include "mid_common.h"

//��������ĳ���
#define BLE_TASK_QUEUE_SIZE     32

// ����������󳤶�
//#define	BLE_BUF_LENGTH_MAX		64


// *************************************************************
// protocal common define
// *************************************************************


//����·�ɺ궨�壨�ο�����ͨ��Э�飩
typedef enum
{
    MCU_TO_BLE          = 0x12,  //��MCU�˷��͵�������
    BLE_TO_MCU          = 0x21,  //�������˷��͵�MCU��
    MCU_TO_APP          = 0x13,  //��MCU�˷��͵�Ӧ�ö�
    APP_TO_MCU          = 0x31,  //��Ӧ�ö˷��͵�MCU��
}communicate_route_t;

//�ӿ����ͺ궨�壨�ο�����ͨ��Э�飩
typedef enum
{
    PROTOCAL_SET            = 0x01, //SET�ӿ����͡�����ĳЩ���������͸����ͽӿ���Ҫ�ȴ�Ӧ��
    PROTOCAL_GET            = 0x02, //GET�ӿ����͡���ȡĳЩ���������͸����ͽӿ���Ҫ�ȴ�Ӧ��
    PROTOCAL_CALL           = 0x04, //CALL�ӿ����͡�ִ��ĳЩ���������͸����ͽӿ���Ҫ�ȴ�Ӧ��
    PROTOCAL_RET            = 0x08, //RET�ӿ����͡�����ĳЩ���������ն˵���յ�����֮֡��
                                    //    ����Ҫ����Ӧ�𣬿��øýӿ����͵Ľӿ�֡
    PROTOCAL_ECHO           = 0x80, //ECHO�ӿ����͡�֪ͨ�����͸����ͽӿڲ���Ҫ�ȴ�Ӧ��
}communicate_interface_type;

//ACK֡���ز����궨�壨�ο�����ͨ��Э�飩
typedef enum
{
    SUCCESS                 = 0x00, //�ɹ�
    INTERFACE_UNEXIST       = 0x01, //�ӿڲ�����
    INTERFACE_UNSURPPOT     = 0x02, //�ӿ����Ͳ�֧��
    PARAMATER_ERROR         = 0x03, //�ӿڲ�������
    CHECKSUM_ERROR          = 0x04, //֡У�����
}ack_id;

//�ӿ�����
typedef enum
{
    PROT_LINK               = 0x00, //��·����
    PROT_DEV_INFO           = 0x01, //�豸��Ϣ
    PROT_EVENT              = 0x02, //���޶���
    PROT_INTERACT           = 0x03, //��������
    PROT_DEV_TEST           = 0x04, //�豸����
    PROT_SENSOR             = 0x05, //������
    PROT_UPDATE             = 0x06, //����
    PROT_APP_SPORT_SCENE  	= 0x10, //�ճ��˶�����
    PROT_MOUNTAINEER_SCENE  = 0x11, //��ɽ����
    PROT_RUNNING_SCENE      = 0x12, //��ɽ����
    PROT_SWIMING_SCENE      = 0x13, //��ɽ����
    PROT_SLEEP_SCENE        = 0x14, //��ɽ����
    PROT_HRS_SCENE          = 0x15, //��ɽ����
    PROT_PACK_TRANS         = 0xF0, //���ݰ�����
    PROT_SCENE_PACK_TRANS   = 0xF2, //�������ݰ�����
}app_protocal_interface_type;



// ��·�ӿ�
enum
{
	PROT_BT_STATE	      	= 0x01,
	PROT_BT_CONN_PARAM     	= 0x02,
	PROT_BT_ADV_NAME       	= 0x03,
	PROT_BT_ADV_PROJ_NUM   	= 0x04,
	PROT_BT_CONN_INTV      	= 0x05,
	PROT_BT_FW_VERSION		= 0x06,
	PROT_IOS_PAIR_REQ       = 0x07,
	PROT_LINKLOSS_REMIND_SWITCH = 0x11,
    PROT_LINK_HEARBEAT      = 0x12,
};


//�궨���豸��Ϣ��ȡ����ο�����ͨ��Э�飩
typedef enum
{
    PROT_PROD_NAME     = 0x01, //��Ʒ����
    PROT_PROD_VER      = 0x02, //�̼��汾��
    PROT_PROD_DATE     = 0x03, //��������
    PROT_PROD_SOC      = 0x04, //ʣ�����
    PROT_PROD_AUTH     = 0x05, //��Ȩ
    PROT_PROD_SN       = 0x06, //SN ��
    PROT_PROD_PHONE_MOD= 0x07, //�ֻ��ͺ�
    PROT_DATE          = 0x08, //ʱ������
    PROT_SEC_CITY_DATE = 0x09, //�ڶ�����ʱ������
    PROT_ALARM_CLK     = 0x0A, //��������
	PROT_ALARM_CLK2    = 0x0B, //��������2
    PROT_WEIGHT_HEIGHT = 0x0E, //��ߡ�����
	PROT_SEC_CITY_DST  = 0x0D, //�ڶ�����DST
	PROT_PHONE_WEATHER = 0x10, //�ֻ��·�������Ϣ
	PROT_PROD_SOC_NEW  = 0x14, // ����ʣ�����
}app_protocal_interface_dev_info;


typedef enum
{
	PROT_EVENT_OP      = 0x01,
	PROT_EVENT_INFO    = 0x02,
}app_protocal_interface_event;

//�궨�彻����������ο�����ͨ��Э�飩
typedef enum
{
    PROT_NEW_MSG                    = 0x01, //����Ϣ
    PROT_MSG_SWITCH                 = 0x02, //֪ͨ����
    PROT_INCALL_RESP                = 0x03, //����֪ͨ������ֻ��Ʒ����
    PROT_CANCEL_MSG                 = 0x04, //��Ϣȡ��֪ͨ
	PROT_CANCEL_MSG_NEW             = 0x14, //��Ϣȡ��֪ͨ���£�
    PROT_MSG_DETAIL_SWITCH          = 0x05, //��Ϣ���鿪�أ�ֻ��Ʒ����
    PROT_MSG_DETAIL                 = 0x06, //��Ϣ����
	PROT_MSG_DETAIL_NEW             = 0x16, //��Ϣ���飨�£�
    PROT_FIND_PHONE                 = 0x11, //�����ֻ���ֻ��Ʒ����
    PROT_PHOTO_MODE                 = 0x21, //���롢�˳�����
    PROT_PHOTO_REQ                  = 0x22, //��������
    PROT_PHOTO_HEARTBEAT            = 0x23, //����״̬������Ϣ
    PROT_WATCH_HAND_MODE            = 0x31, //���롢�˳�У��ģʽ
    PROT_WATCH_HAND_CTRL            = 0x32, //ָ�����
    PROT_WATCH_HAND_PARAM           = 0x33, //����У�����
    PROT_WATCH_HAND_HEARTBEAT       = 0x34, //У��ģʽ������Ϣ
	PROT_LONG_SIT_SWITCH 			= 0x51, //����
    PROT_LONG_SIT_PARAM             = 0x52, //��������
    PROT_DND_SWITCH                 = 0x61, //���ſ���
    PROT_DND_PARAM                  = 0x62, //���Ų���
    PROT_SYS_SETTING                = 0x91, //ϵͳ����
}app_protocal_interface_interact;

//�˶���������궨��
typedef enum
{
    PROT_SCENE_DS_MODE              = 0x01, //����ʹ��
    PROT_SCENE_DS_GOAL              = 0x02, //�˶�Ŀ��
    PROT_SCENE_DS_TOTAL_APP_STEPS 	= 0x03, //�����ܲ���
    PROT_SCENE_DS_HIS_STEPS         = 0x04,
    PROT_SCENE_DS_HIS_STEPS_TRANS   = 0x05,
}app_protocal_interface_daily_sport_scene;

//�˶���������궨��
typedef enum
{
    PROT_MEASURE_DATA_HRS_GET       = 0x02, //��ȡ����ֵ
    PROT_MEASURE_DATA_HRS_START     = 0x03, //�����������ʲ���
}app_protocal_interface_hrs_scene;

//��������������궨��
typedef enum
{
	PORT_SENSOR_DATA_UPDATE         = 0x01,
    PROT_CAMPASS_CTRL               = 0x02, //ָ�������
    PROT_DECLINATION_CONFIG         = 0x03, //��ƫ������
    PROT_PR_TMP_UPLOAD              = 0x11, //��ѹ�������¶�ʵʱ�����ϴ�
    PROT_PR_TMP_HIS_UPLOAD          = 0x12, //��ѹ�������¶ȴ�������ʷ������Ϣ
    PROT_PR_TMP_TRANS               = 0x13, //��ѹ�������¶ȴ�������ʷ���ݴ���
	  
}app_protocal_interface_sensor;


typedef enum
{
    PROT_UPDATE_REQ                 = 0x01,  //��������
    PROT_UPDATE_IMAGE_INFO,                  //������Ϣ
    PROT_UPDATE_IMAGE_DATA,                  //��������
    PROT_UPDATE_IMAGE_END,                   //���������
    PROT_UPDATE_FW,                          //���¹̼�
}app_protocal_interface_updata;

// ˯�����ݴ���ӿ�
typedef enum
{
    DAILY_SLEEP_HABIT_NEW                       = 0x01,
    DAILY_SLEEP_GOAL_NEW                        = 0x02,
    PROT_SCENE_SLEEP_RECORD_CONTENT                          = 0x03,
    PROT_SCENE_SLEEP_RECORD_INFO                       = 0x04,
	PROT_SCENE_SLEEP_RECORD_INFO_NEW                       = 0x14,
	PROT_SCENE_SLEEP_RECORD_DEL                       = 0x05,
}app_protocal_sleep_scene_type;

// ���ݰ�����ӿ�
typedef enum
{
	PORT_SCENE_PACK_TRANS_GET_CONTENT_COUNT			    = 0x10,
	PORT_SCENE_PACK_TRANS_GET_CONTENT_INFO			    = 0x11,
	PORT_SCENE_PACK_TRANS_GET_PKG						= 0x12,
	PORT_SCENE_PACK_TRANS_AUTO_UPDATE_CONTENT_COUNT	    = 0x20,
	PORT_SCENE_PACK_TRANS_AUTO_UPDATE_CONTENT_INFO	    = 0x21,
	PORT_SCENE_PACK_TRANS_DEL_ALL						= 0x30,
	PORT_SCENE_PACK_TRANS_DEL_DATATYPE				    = 0x31,
	PORT_SCENE_PACK_TRANS_DEL_CONTENT_UTC				= 0x32,
}app_protocal_scene_pack_trans_type;


// ���ݰ�����ӿ�
typedef enum
{
    PORT_PACK_TRANS_CH1                         = 0x01,
    PORT_PACK_TRANS_GET_CONTENT_COUNT           = 0x10,
    PORT_PACK_TRANS_GET_CONTENT_INFO            = 0x11,
    PORT_PACK_TRANS_GET_PKG                     = 0x12,
    PORT_PACK_TRANS_AUTO_UPDATE_CONTENT_COUNT   = 0x20,
    PORT_PACK_TRANS_AUTO_UPDATE_CONTENT_INFO    = 0x21,
    PORT_PACK_TRANS_DEL_ALL                     = 0x30,
    PORT_PACK_TRANS_DEL_DATATYPE                = 0x31,
    PORT_PACK_TRANS_DEL_CONTENT_UTC             = 0x32,
}app_protocal_pack_trans_type;

//�ӿ�����1�ͽӿ�����2�ϳ�����궨��
typedef enum
{
    //PROT_DEV_INFO
    RET_PROT_PROD_NAME                  = 0x0101, //��Ʒ����
    RET_PROT_PROD_VER                   = 0x0102, //�̼��汾��
    RET_PROT_PROD_DATE                  = 0x0103, //��������
    RET_PROT_PROD_SOC                   = 0x0104, //ʣ�����
    RET_PROT_PROD_AUTH                  = 0x0105, //��Ȩ
    RET_PROT_PROD_SN                    = 0x0106, //SN ��
    RET_PROT_PROD_PHONE_SYS             = 0x0106, //�ֻ�����ϵͳ
    RET_PROT_PROD_PHONE_MOD             = 0x0107, //�ֻ��ͺ�
    RET_PROT_DATE                       = 0X0108, //ʱ������
    RET_PROT_SEC_CITY_DATE              = 0X0109, //�ڶ�����ʱ������
    RET_PROT_ALARM_CLK                  = 0X010A, //��������
    RET_PORT_SCENE_DS_TOTAL_APP_STEPS 	= 0x1003, //�����ܲ���
    RET_PROT_MSG_SWITCH                 = 0x0302, //֪ͨ����
    RET_PORT_BLEDISCREMIND_SWITCH       = 0x0011, //������·����
	RET_PORT_LONGSIT_SWITCH             = 0x0351, //�������ѿ���
	RET_PROT_LONG_SIT_PARAM             = 0x0352, //�������Ѳ�������
	RET_PORT_NOTDISTURB_SWITCH          = 0x0361, //�������ѿ���
    RET_PROT_DND_PARAM                  = 0x0362, //�������Ѳ�������
}app_protocal_ret_type;

//����״��ö��
typedef enum
{
	WEATHER_0000_SUNNY  			= 0x0000, //��
	WEATHER_0001_CLOUDY  			= 0x0001, //����
	WEATHER_0002_OVERCAST  			= 0x0002, //��
	WEATHER_0003_HAZE  				= 0x0003, //��
	WEATHER_0004_ICERAIN  			= 0x0004, //����	
	WEATHER_0005_FOGGY 		    	= 0x0005, //��
	
	WEATHER_0100_LIGHT_RAIN  		= 0x0100, //С��
	WEATHER_0101_MODERATE_RAIN 		= 0x0101, //����
	WEATHER_0102_HEAVY_RAIN  		= 0x0102, //����
	WEATHER_0103_RAINSTORM  		= 0x0103, //����
	WEATHER_0104_BIG_RAINSTORM 		= 0x0104, //����
	WEATHER_0105_SUPPER_RAINSTORM 	= 0x0105, //�ش���
	
	WEATHER_0200_SNOW_SHOWER 		= 0x0200, //��ѩ
	WEATHER_0201_LIGHT_SHOWER  		= 0x0201, //Сѩ
	WEATHER_0202_MODERATE_SNOW 		= 0x0202, //��ѩ
	WEATHER_0203_HEAVY_SNOW  		= 0x0203, //��ѩ
	WEATHER_0204_BLIZZARD 			= 0x0204, //��ѩ
	
	WEATHER_0300_DUST  				= 0x0300, //����
	WEATHER_0301_DUSTBLOW  			= 0x0301, //��ɳ
	WEATHER_0302_SANDSTORM 			= 0x0302, //ɳ����
	WEATHER_0303_STRONG_SANDSTORM	= 0x0303, //ǿɳ����

	WEATHER_0400_SHOWER  			= 0x0400, //����
	WEATHER_0401_THUNDER_RAIN  		= 0x0401, //������
	WEATHER_0402_SLEETY 			= 0x0402, //���ѩ
	WEATHER_0403_HAIL 				= 0x0403, //������б���

	WEATHER_0500_S_TO_M_RAIN  		= 0x0500, //С��-����
	WEATHER_0501_M_TO_H_RAIN 		= 0x0501, //����-����
	WEATHER_0502_H_TO_TH_RAIN  		= 0x0502, //����-����
	WEATHER_0503_TH_TO_BH_RAIN  	= 0x0503, //����-����
	WEATHER_0504_BH_TO_SH_RAIN 		= 0x0504, //����-�ش���

	WEATHER_0600_S_TO_M_SNOW  		= 0x0600, //Сѩ-��ѩ
	WEATHER_0601_M_TO_H_SNOW  		= 0x0601, //��ѩ-��ѩ
	WEATHER_0602_H_TO_TH_SNOW   	= 0x0602, //��ѩ-��ѩ
	
}app_protocal_weather_type;


//**********************************************************************
// ��������:  �����������У��ֵ
// ��������� protocal
// ���ز����� У��ֵ 
//**********************************************************************
extern uint8 Mid_Ble_CheckSum(protocal_msg_t *protocal);

//**********************************************************************
// ��������: ���ط���Ϣ��������ɾ�������رճ�ʱ��ʱ��
// ���������    
//         msg����Ϣ��ַ
// ���ز����� 
//**********************************************************************
extern ret_type Mid_Ble_DelResendMsg(protocal_msg_t *msg);

//**********************************************************************
// ��������: ����ͨ��Э�����ݣ��������ݣ������Լ�ACK
// ���������msg��ָ����Э������ָ��
// ���ز�����
//    Ret_QueueFull:��Ϣ������
//    Ret_OK:       ���ͳɹ�
//**********************************************************************
extern ret_type Mid_Ble_SendMsg(ble_msg_t *msg);

//**********************************************************************
// ��������:  ����callback
// ��������� cb
// ���ز����� �� 
//**********************************************************************
extern void Mid_Ble_SetCallBack(protocal_cb cb);

//**********************************************************************
// ��������:  ��ʼ������ģ��
// ��������� ��
// ���ز����� �� 
//**********************************************************************
extern void Mid_Ble_Init(void);

extern ret_type Ble_SendMsgToQueue(ble_msg_t *msg);	// DrL ����

extern void Mid_Ble_SetAdvNameDefault(void);

#endif      //BLE_APP_H



