#ifndef     SYS_VARIABLE_H
#define     SYS_VARIABLE_H

#define		PROTOCAL_LENGTH			32

//ͨ�Ŷ����е�ͨ��ID
typedef enum 
{
    BLE_MSG_SEND_WITH_RESEND,  //�ط�
    BLE_MSG_SEND,              //��������/CMD
    BLE_MSG_RECEIVE,           //����������
    BLE_MSG_RESEND_TIMEOUT,    //�ط���ʱ
} ble_msg_id;

//���ݿ�������
typedef union
{
    uint8  data[PROTOCAL_LENGTH - 5];
    struct 
    {
        uint8 interfaceType;                  //�ӿ����� 
        uint8 interfaceIndex1;                //�ӿ�����1
        uint8 interfaceIndex2;                //�ӿ�����2
        uint8 parameter[PROTOCAL_LENGTH - 8]; //���ز���
    }content;
}load_t;

//BLE���ݴ���֡������
typedef union
{
    uint8 data[PROTOCAL_LENGTH];
    struct 
    {
        uint8 startSign;  //֡ͷ
        uint8 version;    //�汾
        uint8 loadLength; //����
        uint8 routeMsg;   //·����Ϣ
        uint8 flowControl;//������Ϣ
        load_t load;       //�ӿ����ͼ�����
    }att;
    uint32 resendToutId;//�ط���Ϣ��ID��
} protocal_msg_t;

//�������ݽ���֡
typedef struct
{
    ble_msg_id  id;
    protocal_msg_t packet;  //BLE���ݴ���֡
}ble_msg_t;

typedef void (*protocal_cb)(ble_msg_t *protocal);

#define 	DebugUartModule  		1//
#define     SYS_APP_HANDLE_NUM      20



uint32 VersionRead(void);

uint8 Mid_SystermReset(void);

#endif      // SYS_VARIABLE_H
