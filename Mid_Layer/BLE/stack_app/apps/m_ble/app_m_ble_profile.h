#ifndef _APP_M_BLE_PROFILE_h
#define _APP_M_BLE_PROFILE_h
#include "stdint.h"
#include "stdbool.h"
#include "ancs_api.h"

#define BLE_HEARD    0x23
#define BLE_VERSON   0X01
#define BLE_FLOW     0X01

#define BT_ADV_OFF   0X00    //关蓝牙，蓝牙关闭状态
#define BT_ADV_ON    0X01    //开蓝牙，蓝牙开启状态
#define BT_CONNECTED 0X02    //蓝牙已连接

#define PROT_INTERACT                   (0x03)
#define PROT_NEW_MSG                    (0x01)
#define PROT_MSG_SWITCH                 (0x02)
#define PROT_INCALL_RESP                (0x03)
#define PROT_CANCEL_MSG                 (0x04)
#define PROT_MSG_DETAIL                 (0x06)
#define PROT_CANCEL_MSG_NEW             (0x14)
#define PROT_MSG_DETAIL_NEW             (0x16)

#define PORT_PACK_TRANS                 (0xf0)
#define PORT_PACK_TRANS_CH1             (0x01)

#define BIT(n)			(uint32_t)(0x00000001 << (n))
#define BYTE3(n)		((uint8_t)(((n)>>24) & 0xff))
#define BYTE2(n)		((uint8_t)(((n)>>16) & 0xff))
#define BYTE1(n)		((uint8_t)(((n)>> 8) & 0xff))
#define BYTE0(n)		((uint8_t)(((n)>> 0) & 0xff))

//消息详情数据大小定义
#define TITLE_TEMP_MAX_LEN        49
#define SUBTITLE_TEMP_MAX_LEN     49
#define MSG_TEMP_MAX_LEN          149
#define APPID_TEMP_MAX_LEN        50

typedef enum
{
    SET =0x01,
    GET =0x02,
    CALL=0x04,
    ECHO=0x80,
    RET =0x08,
}OP_TYPE;

enum
{
    BLE_TO_MCU =0x21,
    BLE_TO_APP =0x23,
    MCU_TO_BLE =0x12,
    MCU_TO_APP =0X13,
    APP_TO_MCU =0X31,
    APP_TO_BLE =0x32,
};

enum
{
    HEARD_IDX  =0,
    VERSON_IDX =1,
    MSG_LEN    =2,
    ROL_IDX    =3,
    FLOW_IDX   =4,
    INTER_TYPE =5,
    INTER_IDX,
    PARAM_IDX  =8
};

typedef enum
{
    TYPE_ANCS_MSG_QQ			    = (0),
    TYPE_ANCS_MSG_WECHAT		    = (1),
    TYPE_ANCS_MSG_TENCENT_WEIBO		= (2),
    TYPE_ANCS_MSG_SKYPE				= (3),
    TYPE_ANCS_MSG_SINA_WEIBO		= (4),
    TYPE_ANCS_MSG_FACEBOOK			= (5),
    TYPE_ANCS_MSG_TWITTER			= (6),
    TYPE_ANCS_MSG_WHATAPP			= (7),
    TYPE_ANCS_MSG_LINE				= (8),
    TYPE_ANCS_MSG_OTHER1		    = (9),
    TYPE_ANCS_MSG_INCALL		    = (10),
    TYPE_ANCS_MSG_MESSAGE			= (11),
    TYPE_ANCS_MSG_MISSCALL			= (12),
    TYPE_ANCS_MSG_CALENDAR			= (13),
    TYPE_ANCS_MSG_EMAIL				= (14),
    TYPE_ANCS_MSG_OTHER2		    = (15),
    TYPE_ANCS_MSG_INCALL_KNOW	    = (16),
    TYPE_ANCS_MSG_TIM               = (17),
    TYPE_ANCS_MSG_TAOBAO            = (18),  //淘宝
    TYPE_ANCS_MSG_JINGDONG          = (19),  //京东 
    TYPE_ANCS_MSG_DINGDING          = (20),  //叮叮
    TYPE_ANCS_MSG_INSTAGRAM         = (21),  //Instagram
    TYPE_ANCS_MSG_TYPE_INVALID      = (0xFF) //无效
}ANCS_EVENT_TYPE;

//record msg detail every data
typedef struct 
{
    uint8_t title_len;
    uint8_t subtitle_len;
    uint8_t msg_len;
    uint8_t app_id_len;
    uint8_t title_buf[TITLE_TEMP_MAX_LEN+1];               //标题缓存大小
    uint8_t subtitle_buf[SUBTITLE_TEMP_MAX_LEN+1];         //副标题缓存大小
    uint8_t msg_buf[MSG_TEMP_MAX_LEN+1];                   //消息缓存大小
    uint8_t app_id_buf[APPID_TEMP_MAX_LEN+1];              //应用名称缓存大小
}msg_detail_t;

typedef struct
{
    uint8_t type;
    uint8_t str_len;
    const uint8_t *str;
}ancs_app_id_type;

typedef struct 
{
    uint8_t frame_head;
    uint8_t version;
    uint8_t par_lenth;
    uint8_t route;
    uint8_t flow;
    uint8_t interface[3];
    uint8_t buf[12];      //param +check_sum
}send_msg_frame_t;

//**********************************************************************
// 函数功能: 获取ble模式
// 输入参数: u8Mode 
// 返回参数： BLE_MODE_OTA       OTA模式
//            BLE_MODE_NORMAL   正常通讯模式
//**********************************************************************
extern uint8 BLE_Stack_GetMode(void);

#endif 

