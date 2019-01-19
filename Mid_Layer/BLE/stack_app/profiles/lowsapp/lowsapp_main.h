
#ifndef LOWSAPP_API_H
#define LOWSAPP_API_H

#include "wsf_os.h"
#include "stdint.h"
#include "stdbool.h"
#include "att_api.h"
#ifdef __cplusplus
extern "C" {
#endif

//回调:蓝牙接收数据返回给app
typedef void (*ble_recv_data_handler)(const uint8_t *buf,uint16_t len);
    
typedef struct
{
    dmConnId_t    connId;               // Connection ID
    bool_t        lowsappToSend;        // AMOTA notify ready to be sent on this channel
}
lowsappConn_t;

/*! Application message type */
typedef union
{
    wsfMsgHdr_t     hdr;
    dmEvt_t         dm;
    attsCccEvt_t    ccc;
    attEvt_t        att;
} lowsappMsg_t;

typedef enum
{
    SEND_CHANNEL_FIRST          = 0U,
    SEND_CHANNEL_CMD,
    SEND_CHANNEL_DATA,
    SEND_CHANNEL_LAST,
}send_channel_t;


void lowsapp_start(dmConnId_t connId,uint8_t lowsappCccIdx);
void lowsapp_stop(dmConnId_t connId,uint8_t lowsappCccIdx);

void lowsapp_proc_msg(wsfMsgHdr_t *pMsg);
void lowsapp_init(wsfHandlerId_t handlerId);

void lowsapp_send_data(uint8_t *buf, uint8_t len,uint8_t type);
uint8_t lowsapp_write_cback(dmConnId_t connId, uint16_t handle, uint8_t operation,
                       uint16_t offset, uint16_t len, uint8_t *pValue, attsAttr_t *pAttr);

void lowsapp_transfer_data_init(ble_recv_data_handler recv_data_handler);
bool lowsapp_send_idle_check(void);    

#ifdef __cplusplus
};
#endif

#endif /* ANCS_API_H */

