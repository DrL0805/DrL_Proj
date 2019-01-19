//*****************************************************************************
//
//! @file   ancc_api.c
//!
//! @brief  apple notification center service client.
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#ifndef ANCC_API_V2_H
#define ANCC_API_V2_H

#include "att_api.h"
#include "platform_feature.h"

#ifdef __cplusplus
extern "C" {
#endif

//�Ƿ�֧��NC��ȡNP�ϰ�װapp���ض����ԣ�Ŀǰ��Ӧ�ò���Ҫ���ر�
#define READ_NP_APP_ATTR     0

#define TITLE_MAX_LEN        49
#define SUBTITLE_MAX_LEN     49
#define MSG_MAX_LEN          149

//�ֱ���ios����attribute���ݳ���
#define ATTR_TITLE_REQUEST_LEX   128   //title��subtitle
#define ATTR_MSG_REQUEST_LEX     150   //msg

//timer��ʱ��״̬��ͬʱҲ�Ƕ�ʱʱ��
#define ANCS_TIMER_PARSE         200   //ANCS��������������һ����Ϣ
#define ANCS_TIMER_UPLOAD        50    //�ϴ����ݸ�����

/**************************************************************************************************
  Macros
**************************************************************************************************/
/* ANCS Service */                          // 7905F431-B5CE-4E99-A40F-4B1E122D00D0
#define ATT_UUID_ANCS_SERVICE               0xd0, 0x00, 0x2d, 0x12, 0x1e, 0x4b, 0x0f, 0xa4,\
                                            0x99, 0x4e, 0xce, 0xb5, 0x31, 0xf4, 0x05, 0x79
/* ANCS characteristics */
                                            // 9FBF120D-6301-42D9-8C58-25E699A21DBD
#define ATT_UUID_NOTIFICATION_SOURCE        0xbd, 0x1d, 0xa2, 0x99, 0xe6, 0x25, 0x58, 0x8c, \
                                            0xd9, 0x42, 0x01, 0x63, 0x0d, 0x12, 0xbf, 0x9f

                                            //69D1D8F3-45E1-49A8-9821-9BBDFDAAD9D9
#define ATT_UUID_CTRL_POINT                 0xd9, 0xd9, 0xaa, 0xfd, 0xbd, 0x9b, 0x21, 0x98,\
                                            0xa8, 0x49, 0xe1, 0x45, 0xf3, 0xd8, 0xd1, 0x69
                                            
                                            // 22EAC6E9-24D6-4BB5-BE44-B36ACE7C7BFB
#define ATT_UUID_DATA_SOURCE                0xfb, 0x7b, 0x7c, 0xce, 0x6a, 0xb3, 0x44, 0xbe,\
                                            0xb5, 0x4b, 0xd6, 0x24, 0xe9, 0xc6, 0xea, 0x22

#define ANCC_LIST_ELEMENTS                  32   //�ֱ��Ŀǰ���֧����ʾ5�����������32���㹻��Ĭ����64
#define ANCC_APP_IDENTIFIER_SIZE_BYTES      64   //
#define ANCC_ATTRI_BUFFER_SIZE_BYTES        512

/**@brief Category IDs for iOS notifications. */
typedef enum
{
    BLE_ANCS_CATEGORY_ID_OTHER,                     /**< The iOS notification belongs to the "other" category.  */
    BLE_ANCS_CATEGORY_ID_INCOMING_CALL,             /**< The iOS notification belongs to the "Incoming Call" category. */
    BLE_ANCS_CATEGORY_ID_MISSED_CALL,               /**< The iOS notification belongs to the "Missed Call" category. */
    BLE_ANCS_CATEGORY_ID_VOICE_MAIL,                /**< The iOS notification belongs to the "Voice Mail" category. */
    BLE_ANCS_CATEGORY_ID_SOCIAL,                    /**< The iOS notification belongs to the "Social" category. */
    BLE_ANCS_CATEGORY_ID_SCHEDULE,                  /**< The iOS notification belongs to the "Schedule" category. */
    BLE_ANCS_CATEGORY_ID_EMAIL,                     /**< The iOS notification belongs to the "E-mail" category. */
    BLE_ANCS_CATEGORY_ID_NEWS,                      /**< The iOS notification belongs to the "News" category. */
    BLE_ANCS_CATEGORY_ID_HEALTH_AND_FITNESS,        /**< The iOS notification belongs to the "Health and Fitness" category. */
    BLE_ANCS_CATEGORY_ID_BUSINESS_AND_FINANCE,      /**< The iOS notification belongs to the "Buisness and Finance" category. */
    BLE_ANCS_CATEGORY_ID_LOCATION,                  /**< The iOS notification belongs to the "Location" category. */
    BLE_ANCS_CATEGORY_ID_ENTERTAINMENT              /**< The iOS notification belongs to the "Entertainment" category. */
} ancc_category_id_values_t;

/**@brief Event IDs for iOS notifications. */
typedef enum
{
    BLE_ANCS_EVENT_ID_NOTIFICATION_ADDED,           /**< The iOS notification was added. */
    BLE_ANCS_EVENT_ID_NOTIFICATION_MODIFIED,        /**< The iOS notification was modified. */
    BLE_ANCS_EVENT_ID_NOTIFICATION_REMOVED          /**< The iOS notification was removed. */
} ancc_evt_id_values_t;

/**@brief Control point command IDs that the Notification Consumer can send to the Notification Provider. */
typedef enum
{
    BLE_ANCS_COMMAND_ID_GET_NOTIF_ATTRIBUTES,       /**< Requests attributes to be sent from the NP to the NC for a given notification. */
    //ע:NC��ȡNP�ϰ�װapp���ض�����,�˲���Ӧ����δ�õ�,�����������
    BLE_ANCS_COMMAND_ID_GET_APP_ATTRIBUTES,         /**< Requests attributes to be sent from the NP to the NC for a given iOS App. */
    BLE_ANCS_COMMAND_ID_GET_PERFORM_NOTIF_ACTION,   /**< Requests an action to be performed on a given notification, for example dismiss an alarm. */
} ancc_command_id_values_t;

/**@brief IDs for iOS notification attributes. */
typedef enum
{
    BLE_ANCS_NOTIF_ATTR_ID_APP_IDENTIFIER,          /**< Identifies that the attribute data is of an "App Identifier" type. */
    BLE_ANCS_NOTIF_ATTR_ID_TITLE,                   /**< Identifies that the attribute data is a "Title". Needs to be followed by a 2-bytes max length parameter*/
    BLE_ANCS_NOTIF_ATTR_ID_SUBTITLE,                /**< Identifies that the attribute data is a "Subtitle". Needs to be followed by a 2-bytes max length parameter*/
    BLE_ANCS_NOTIF_ATTR_ID_MESSAGE,                 /**< Identifies that the attribute data is a "Message". Needs to be followed by a 2-bytes max length parameter*/
    BLE_ANCS_NOTIF_ATTR_ID_MESSAGE_SIZE,            /**< Identifies that the attribute data is a "Message Size". */
    BLE_ANCS_NOTIF_ATTR_ID_DATE,                    /**< Identifies that the attribute data is a "Date". */
    BLE_ANCS_NOTIF_ATTR_ID_POSITIVE_ACTION_LABEL,   /**< The notification has a "Positive action" that can be executed associated with it. */
    BLE_ANCS_NOTIF_ATTR_ID_NEGATIVE_ACTION_LABEL,   /**< The notification has a "Negative action" that can be executed associated with it. */
} ancc_notif_attr_id_values_t;

/**@brief ActionID values. */
typedef enum
{
    BLE_ANCS_NOTIF_ACTION_ID_POSITIVE,
    BLE_ANCS_NOTIF_ACTION_ID_NEGATIVE,
} ancc_notif_action_id_values_t;


#define BLE_ANCS_EVENT_FLAG_SILENT          0       /**< 0b.......1 Silent: First (LSB) bit is set. All flags can be active at the same time.*/
#define BLE_ANCS_EVENT_FLAG_IMPORTANT       1       /**< 0b......1. Important: Second (LSB) bit is set. All flags can be active at the same time.*/
#define BLE_ANCS_EVENT_FLAG_PREEXISTING     2       /**< 0b.....1.. Pre-existing: Third (LSB) bit is set. All flags can be active at the same time.*/
#define BLE_ANCS_EVENT_FLAG_POSITIVE_ACTION 3       /**< 0b....1... Positive action: Fourth (LSB) bit is set. All flags can be active at the same time.*/
#define BLE_ANCS_EVENT_FLAG_NEGATIVE_ACTION 4       /**< 0b...1.... Negative action: Fifth (LSB) bit is set. All flags can be active at the same time. */

/*! ancs client enumeration of handle indexes of characteristics to be discovered */
enum
{
  ANCC_NOTIFICATION_SOURCE_HDL_IDX,             // ANCC Notification Source Handle
  ANCC_NOTIFICATION_SOURCE_CCC_HDL_IDX,         // ANCC Notification Source CCC Handle 
  ANCC_CONTROL_POINT_HDL_IDX,                   // ANCC Control Point Handle
  ANCC_DATA_SOURCE_HDL_IDX,                     // ANCC Data Source Handle
  ANCC_DATA_SOURCE_CCC_HDL_IDX,                 // ANCC Data Source CCC Handle
  ANCC_HDL_LIST_LEN                             /*! Handle list length */
};  

typedef enum
{
    NOTI_ATTR_NEW_NOTIFICATION = 0,
    NOTI_ATTR_NEW_ATTRIBUTE,
    NOTI_ATTR_RECEIVING_ATTRIBUTE
}enum_active_state_t;


/*! Configurable parameters */
typedef struct
{
    wsfTimerTicks_t     period;                 /*! action timer expiration period in ms */
} anccCfg_t;

/**@brief Typedef for iOS notifications. */
typedef struct
{
    uint8_t event_id;           /**< This field informs the accessory whether the given iOS notification was added, modified, or removed. The enumerated values for this field are defined in EventID Values.. */
    uint8_t event_flags;        /**< A bitmask whose set bits inform an NC of specificities with the iOS notification. */
    uint8_t category_id;        /**< A numerical value providing a category in which the iOS notification can be classified. */
    uint8_t category_count;     /**< The current number of active iOS notifications in the given category. */
    uint32_t notification_uid;  /**< A 32-bit numerical value that is the unique identifier (UID) for the iOS notification. */
    bool_t  noti_valid;         /**< A flag to indicate whether the notification is still valid in the list. */
}attr_notif_t;

//��������list��������ios�յ���Ϣʱ�·���NC����Ϣ�����Ϣ
//��Ϣ�����ݽṹ:����Ϣ���У��ȵ��������󣬶���ԭ���Ķѽṹ
typedef struct
{
    uint8_t u8attCnt;   //��¼��Ϣ����
    uint8_t u8pushIdx;  //ios�·���Ϣ��Ϣʱ��������list��λ�ã�ָ���λ��������Ч
    uint8_t u8popIdx;   //�豸��ios�ֻ�������Ϣ��list��λ��,ָ���λ����������Ч��
    attr_notif_t list[ANCC_LIST_ELEMENTS];  //��¼ios�ֻ��·�����Ϣ����Ϣ��Ϊѭ��bufferʹ��
}ancc_notif_t;

//��¼�����δ������notification��������Ϣ������������Ϣ��Ӧ��ʱ��Ӧ
typedef struct
{
    uint8_t isValid;    //�Ƿ��������δ������event
    attr_notif_t call_notif;  //��¼�¼������Ϣ
}ancc_call_notif_t;

//�˽ṹ�����ڽ���ancs����
typedef struct
{
    enum_active_state_t attrState;
    //uint16_t  handle;        // handle to indicate the current active notification in the list
    attr_notif_t currMsg;   //��¼��ǰ�����attr��Ϣ�¼������Ϣ����ֵ��msgInfo��call��pop�õ�
    uint16_t  parseIndex;
    uint16_t  bufIndex;
    uint16_t  attrLength;   //attr ID���ݳ���
    uint8_t   attrId;
    uint8_t   attrtype;     //����attr ���ͣ�GET_MSG_OP_STATE��ֵ������
    uint8_t   attrDataBuf[ANCC_ATTRI_BUFFER_SIZE_BYTES];   //���ڻ���������ݲ�ȫʱδ����������
}active_notif_t;

typedef struct 
{
    uint32_t u32Uid;         //noti Uid
    uint8_t  u8AppType;      //��ϢӦ������
    uint16_t u16TtlIdx;      //�����±�
    uint16_t u16SubTtlIdx;   //�������±�
    uint16_t u16MsgIdx;      //��Ϣ�����±�
    uint16_t u16TtlLen;      //���ⳤ��
    uint16_t u16SubTtlLen;   //�����ⳤ��
    uint16_t u16MsgLen;      //��Ϣ���ݳ���
}attr_info_t;

typedef struct
{
    dmConnId_t          connId;
    uint16_t*           hdlList;
    uint8_t             timerStatus;    //timer״̬������/���������ϴ���ֵ:ANCS_TIMER_PARSE,ANCS_TIMER_UPLOAD
    wsfTimer_t          actionTimer;                     // perform actions with proper delay    
    //ancc_notif_t        anccList[ANCC_LIST_ELEMENTS];    // buffer size = MAX_LIST_ELEMENTS*sizeof(ancc_notif_t)
    ancc_notif_t        msgInfo;  //��¼ios�ֻ��·�����Ϣ��Ϣ
    ancc_call_notif_t   call;
    active_notif_t      active;
    attr_info_t         attr;     //���ڼ�¼����attrDataBuf����ʱ��attr��λ�ã����ں�����װ����
} anccCb_t;

/**************************************************************************************************
  Function Prototypes
**************************************************************************************************/
void AncsPerformNotiAction(dmConnId_t connId,uint16_t *pHdlList, uint32_t notiUid, ancc_notif_action_id_values_t actionId);
void AncsGetAppAttribute(dmConnId_t connId,uint16_t *pHdlList, uint8_t* appId);
void AnccGetNotificationAttribute(dmConnId_t connId,uint16_t *pHdlList, uint32_t notiUid);
void AnccNtfValueUpdate(uint16_t *pHdlList, attEvt_t * pMsg);

void AncsActionNext(void);
void AnccActionStart(uint8_t u8TimerStatus);
void AnccValueUpdate(attEvt_t *pMsg);

#ifdef __cplusplus
};
#endif

#endif /* ANCC_API_H */
