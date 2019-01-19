#ifndef STORE_VARIABLE_H
#define STORE_VARIABLE_H

#include "platform_common.h"
#include "algorithm_sleep.h"
#include "mid_common.h"
#include "mid_nandflash.h"	// LOG_ADDR_SET() �Ⱥ궨��

#define STORE_RTT_DEBUG	3
#if (1 == STORE_RTT_DEBUG)	// ����ȼ�
#define STORE_RTT_LOG(...)
#define STORE_RTT_WARN(...)
#define STORE_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_RTT_DEBUG)	// ����ȼ�
#define STORE_RTT_LOG(...)
#define STORE_RTT_WARN		RTT_DEBUG_WARN
#define STORE_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_RTT_DEBUG)	// ���Եȼ�
#define STORE_RTT_LOG		RTT_DEBUG_LOG
#define STORE_RTT_WARN		RTT_DEBUG_WARN
#define STORE_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define STORE_RTT_LOG(...)
#define STORE_RTT_WARN(...)
#define STORE_RTT_ERR(...)
#endif

#define	PDU_DATA_UPLOAD_MAX_LEN		16	// app����ÿ���ϴ�����ֽ� 2���+2����+16��Ч����

// �������ݵ�Ŀ¼���������ݳ��ȷ���Э��
static const protocal_msg_t	PROT_PACK_TRANS_CATA_TOTAL_RET =
{
	0x23, 0x01, 0x0B, 0x13, 0x00, 0x08, 0xf0, 0x10,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};

// �������ݵ�Ŀ¼���ݷ���Э��
static const protocal_msg_t	PROT_PACK_TRANS_CATA_RET =
{
	0x23, 0x01, 0x0c, 0x13, 0x00, 0x08, 0xf0, 0x11,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};

// �������ݵ����ݰ�����������
static const protocal_msg_t	PROT_PACK_TRANS_DATA_RET =
{
	0x23, 0x01, 0x04, 0x13, 0x00, 0x08, 0xf0, 0x12,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};

// ɾ���������ݷ���
static const protocal_msg_t	PROT_PACK_TRANS_DELETE_ALL_RET =
{
	0x23, 0x01, 0x04, 0x13, 0x00, 0x80, 0xf0, 0x30,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};

// ɾ��ĳ�����ݷ���
static const protocal_msg_t	PROT_PACK_TRANS_DELETE_CLASS_RET =
{
	0x23, 0x01, 0x06, 0x13, 0x00, 0x80, 0xf0, 0x31,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};

// ɾ��Ŀ¼����
static const protocal_msg_t	PROT_PACK_TRANS_DELETE_CATALOG_RET =
{
	0x23, 0x01, 0x0a, 0x13, 0x00, 0x80, 0xf0, 0x32,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};

// ���ݰ��ϴ�Э��
static const protocal_msg_t	PROT_PACK_TRANS_DATA_UPLOAD =
{
	0x23, 0x01, 0x17, 0x12, 0x80, 0x01, 0xf0, 0x01,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};

// ��ȡ���˯�߼�¼��ĿRET
static const protocal_msg_t	PROT_SCENE_SLEEP_RECORD_CONTENT_RET =	
{
	0x23, 0x01, 0x04, 0x13, 0x00, 0x08, 0x14, 0x03,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// ��ȡ��Ŀ��˯�߼�¼��Ϣ1 RET��H002������˯�ߣ�
static const protocal_msg_t	PROT_SCENE_SLEEP_RECORD_INFO_NEW_RET =
{
	0x23, 0x01, 0x0E, 0x13, 0x00, 0x08, 0x14, 0x14,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	
};

// ��ȡ��Ŀ��˯�߼�¼��Ϣ1 ECHO��H002������˯�ߣ�
static const protocal_msg_t	PROT_SCENE_SLEEP_RECORD_INFO_NEW_ECHO =
{
	0x23, 0x01, 0x07, 0x13, 0x00, 0x80, 0x14, 0x14,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	
};

// ɾ����Ŀ��˯�߼�¼��ϢECHO
static const protocal_msg_t	PROT_SCENE_SLEEP_RECORD_DEL_ECHO =
{
	0x23, 0x01, 0x08, 0x13, 0x00, 0x80, 0x14, 0x05,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	
};


// ***************************************************************************
// ***************************************************************************
// ���� **********************************************************************
// ***************************************************************************
// ***************************************************************************
// �������ݵ�Ŀ¼���������ݳ��ȷ���Э��
static const protocal_msg_t	PROT_SCENE_TRANS_CATA_TOTAL_RET =
{
	0x23, 0x01, 0x0B, 0x13, 0x00, 0x08, 0xf2, 0x10,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// �������ݵ�Ŀ¼���ݷ���Э��
static const protocal_msg_t	PROT_SCENE_TRANS_CATA_RET =
{
	0x23, 0x01, 0x03, 0x13, 0x00, 0x08, 0xf2, 0x11,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// �������ݵ����ݰ�����������
static const protocal_msg_t	PROT_SCENE_TRANS_DATA_RET =
{
	0x23, 0x01, 0x04, 0x13, 0x00, 0x08, 0xf2, 0x12,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// ɾ���������ݷ���
static const protocal_msg_t	PROT_SCENE_TRANS_DELETE_ALL_RET =
{
	0x23, 0x01, 0x04, 0x13, 0x00, 0x80, 0xf2, 0x30,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// ɾ��ĳ�����ݷ���
static const protocal_msg_t	PROT_SCENE_TRANS_DELETE_CLASS_RET =
{
	0x23, 0x01, 0x06, 0x13, 0x00, 0x80, 0xf2, 0x31,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// ɾ��Ŀ¼����
static const protocal_msg_t	PROT_SCENE_TRANS_DELETE_CATALOG_RET =
{
	0x23, 0x01, 0x0a, 0x13, 0x00, 0x80, 0xf2, 0x32,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// ���ݰ��ϴ�Э��
static const protocal_msg_t	PROT_SCENE_TRANS_DATA_UPLOAD =
{
	0x23, 0x01, 0x17, 0x12, 0x80, 0x01, 0xf0, 0x01,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

///* Ŀ¼��Ϣ��־λ */
//#define STORE_CATALOG_UNUSE	0xFF		// δʹ��
//#define STORE_CATALOG_USING	0xFE		// ����ʹ��
//#define STORE_CATALOG_SEALED	0xFC	// �ѷ��
//#define STORE_CATALOG_UPLOADED	0xF8	// ���ϴ�
//#define STORE_CATALOG_COVER		0xF0	// �Ѹ���
//#define STORE_CATALOG_deleted	0x00	// ��ɾ��

/* һЩ�������� *************************************/
#define STORE_MAX_MALLOC_LEN				(2048)	// �洢����ʱ��malloc������ֽڳ���
#define STORE_DATA_LEN						(2000)	// ��Ч��������ֽ�
#define STORE_CATALOG_LEN					(48)	// Ŀ¼��ռ�ֽ�
#define STORE_CATALOG_PER_BLOCK				(64)	// ÿblock�ж���Ŀ¼
#define STORE_MAX_SAVE_CATALOG_NUM			(30)	// ��󱣴��Ŀ¼������ʱ��ֵ��FIFO��ʽ����

/* ����ģ��洢block���� */
#define 	STORE_BLOCK_FACTORY			(10)
#define 	STORE_BLOCK_BLE				(11)
#define 	STORE_BLOCK_SYSTOM			(12)
#define 	STORE_BLOCK_TIME			(13)

/* ˯�ߵ����洢��Ϣ */
#define 	STORE_SLEEP_RECORD_ALLOT_BLOCK				(5)										// �Ʋ��洢����block��
#define 	STORE_SLEEP_RECORD_MAX_CATALOG_NUM			(STORE_SLEEP_RECORD_ALLOT_BLOCK * 64)	// ���Ŀ¼���������������������
#define 	STORE_SLEEP_RECORD_MAX_SAVE_CATALOG_NUM		(30)									// ��󱣴��Ŀ¼������������ֵ�ᱻ����
#define 	STORE_SLEEP_RECORD_BEGIN_ADDR				(LOG_ADDR_SET(50,0,0))
#define 	STORE_SLEEP_RECORD_END_ADDR 				(LOG_ADDR_SET(55,0,0) - 1)
#define 	STORE_SLEEP_RECORD_LOG_MAX				 	1 // 
#define 	STORE_SLEEP_RECORD_DATA_CLASSIFY_LEN		255	// ������һ���ϴ�ֵ

/* Part������Ϣ *************************************/
#define STORE_PART_NUM_256B			(320)
#define STORE_PART_NUM_512B			(80)
#define STORE_PART_NUM_1KB			(40)
#define STORE_PART_NUM_2KB			(20)
#define STORE_PART_BEGIN_ADDR_256B  (LOG_ADDR_SET(100,0,0))
#define STORE_PART_BEGIN_ADDR_512B  (LOG_ADDR_SET(140,0,0))
#define STORE_PART_BEGIN_ADDR_1KB   (LOG_ADDR_SET(160,0,0))
#define STORE_PART_BEGIN_ADDR_2KB   (LOG_ADDR_SET(180,0,0))

/* ������Ϣ�洢��ַ *************************************/
#define STORE_FACTORY_CODE_ID				"factory"
#define STORE_FACTORY_ADDR_ID				(96)	// "factory"
#define STORE_FACTORY_ADDR_VER				(112)
#define STORE_FACTORY_ADDR_SN				(128)
#define STORE_FACTORY_ADDR_MAC				(160)
#define STORE_FACTORY_ADDR_MANAGER_SN		(192)	// �ͻ�SN
#define STORE_FACTORY_ADDR_SOFTWARE			(224)	
#define STORE_FACTORY_ADDR_HARDWARE			(256)

/* ������Ϣ�洢��ַ *************************************/
#define STORE_BLE_CODE_ID						"ble"
#define STORE_BLE_ADDR_ID						(96)	// "ble"
#define STORE_BLE_ADDR_VER						(112)
#define STORE_BLE_ADDR_NAME						(128)

/* ϵͳ���ô洢��ַ *************************************/
#define STORE_SYS_CODE_ID						"system"
#define STORE_SYS_ADDR_ID						(96)	// "system"
#define STORE_SYS_ADDR_VER						(112)
#define STORE_SYS_ADDR_LANGUAGE					(128)	// ϵͳ����
#define STORE_SYS_ADDR_TIME_FORMAT				(129)	// ʱ����ʽ
#define STORE_SYS_ADDR_STEP_SWITCH				(130)	// ��̨�Ʋ�����
#define STORE_SYS_ADDR_HRD_SWITCH				(131)	// ��̨���ʿ���
#define STORE_SYS_ADDR_WEATHER_SWITCH			(132)	// ����Ԥ�⿪��
#define STORE_SYS_ADDR_STEP_REMIND_SWITCH		(133)	// �˶����Ʋ���������ѿ���
#define STORE_SYS_ADDR_BLE_OFF_REMIND_SWITCH	(134)	// �����Ͽ�����
#define STORE_SYS_ADDR_SEDENTARY_REMIND_SWITCH	(135)	// �������ѿ���
#define STORE_SYS_ADDR_NO_DISTURB_SWITCH		(136)	// ���ſ���
#define STORE_SYS_ADDR_APP_REMIND_SWITCH		(137)	// �ֻ����ѿ���
#define STORE_SYS_ADDR_APP_DETAIL_REMIND_SWITCH	(141)	// �������ѿ���
#define STORE_SYS_ADDR_GESTURE					(145)	// ���ƿ���
#define STORE_SYS_ADDR_HEIGHT					(256)	// ���
#define STORE_SYS_ADDR_WEIGHT					(257)	// ����
#define STORE_SYS_ADDR_SEX						(258)	// �Ա�
#define STORE_SYS_ADDR_AGE						(259)	// ����

/* ʱ����Ϣ�洢��ַ *************************************/
#define STORE_TIME_CODE_ID						"time"
#define STORE_TIME_ADDR_ID						(96)	// "time"
#define STORE_TIME_ADDR_VER						(112)
#define STORE_TIME_ADDR_LOCAL_TIME				(128)		// ����ʱ��
#define STORE_TIME_ADDR_WORD_TIME				(160)		// ����ʱ��
#define STORE_TIME_ADDR_CITY_CODE				(192)		// ���д���
#define STORE_TIME_ADDR_NO_DISTURB				(194)		// ����ʱ���
#define STORE_TIME_ADDR_SEDENTARY				(226)		// ����ʱ���
#define STORE_TIME_ADDR_ALARM_0					(258)		// ����1
#define STORE_TIME_ADDR_ALARM_1					(274)		// ����2
#define STORE_TIME_ADDR_ALARM_2					(290)		// ����3
#define STORE_TIME_ADDR_ALARM_3					(306)		// ����4
#define STORE_TIME_ADDR_ALARM_4					(322)		// ����5



/* һЩ�������� */
#define STORE2_MAX_SAVE_CATALOG_NUM			(30)	// ��󱣴��Ŀ¼������ʱ��ֵ��FIFO��ʽ����


/* Ŀ¼��غ� */
#define STORE2_CATALOG_INFO_LEN			(512)	// ÿ��Ŀ¼������ֽ�
#define STORE2_CATALOG_FLASH_INFO_LEN	(32)	// Ŀ¼�洢��Ϣ��ռ�ֽ�
#define STORE2_CATALOG_USER_INFO_LEN	(32)	// Ŀ¼�û���Ϣ��ռ�ֽ�
#define STORE2_CATALOG_EXT_INFO_LEN		(448)	// Ŀ¼������Ϣ��ռ�ֽ�
#define STORE2_CATALOG_NUM_PER_BLOCK	(256)	// ÿblock�ж���Ŀ¼,2048/512*64

/* ���������ݴ洢��Ϣ */
#define STORE2_RUN_MAX_ALLOT_CATALOG		(512)	// �����Ŀ¼����������ռ䣩��ÿblock�ɷ���256��Ŀ¼����2block
#define STORE2_RUN_MAX_SAVE_CATALOG			(30)	// �����Ŀ¼������������ֵ��FIFO��ʽ����
#define STORE2_RUN_CATALOG_BEGIN_ADDR		(LOG_ADDR_SET(200,0,0))
#define STORE2_RUN_CATALOG_END_ADDR 		(LOG_ADDR_SET(202,0,0) - 1)
#define STORE2_RUN_DATA_BEGIN_ADDR			(LOG_ADDR_SET(202,0,0))
#define STORE2_RUN_DATA_END_ADDR 			(LOG_ADDR_SET(220,0,0) - 1)
#define STORE2_RUN_LOG_MAX					142 // 142 * 14 = 1988
#define STORE2_RUN_DATA_CLASSIFY_LEN		14	
#define STORE2_RUN_SAMPLE_INFO				((DATASAMPLE_UNIT_1S << 12) | 10)// 2 bytes ������Ϣ����4bit��ʾ��λ����12bitΪ��ֵ

/* ��ɽ���ݴ洢��Ϣ */
#define STORE2_CLIMB_MAX_ALLOT_CATALOG		(512)	// �����Ŀ¼����������ռ䣩��ÿblock�ɷ���256��Ŀ¼����2block
#define STORE2_CLIMB_MAX_SAVE_CATALOG		(30)	// �����Ŀ¼������������ֵ��FIFO��ʽ����
#define STORE2_CLIMB_CATALOG_BEGIN_ADDR		(LOG_ADDR_SET(220,0,0))
#define STORE2_CLIMB_CATALOG_END_ADDR 		(LOG_ADDR_SET(222,0,0) - 1)
#define STORE2_CLIMB_DATA_BEGIN_ADDR		(LOG_ADDR_SET(222,0,0))
#define STORE2_CLIMB_DATA_END_ADDR 			(LOG_ADDR_SET(240,0,0) - 1)
#define STORE2_CLIMB_LOG_MAX				153 // 153 * 13 = 1989
#define STORE2_CLIMB_DATA_CLASSIFY_LEN		13	
#define STORE2_CLIMB_SAMPLE_INFO			((DATASAMPLE_UNIT_1S << 12) | 10)	// 2 bytes ������Ϣ����4bit��ʾ��λ����12bitΪ��ֵ

/* ��Ӿ���ݴ洢��Ϣ */
#define STORE2_SWIM_MAX_ALLOT_CATALOG		(512)	// �����Ŀ¼����������ռ䣩��ÿblock�ɷ���256��Ŀ¼����2block
#define STORE2_SWIM_MAX_SAVE_CATALOG		(30)	// �����Ŀ¼������������ֵ��FIFO��ʽ����
#define STORE2_SWIM_CATALOG_BEGIN_ADDR		(LOG_ADDR_SET(240,0,0))
#define STORE2_SWIM_CATALOG_END_ADDR 		(LOG_ADDR_SET(242,0,0) - 1)
#define STORE2_SWIM_DATA_BEGIN_ADDR			(LOG_ADDR_SET(242,0,0))
#define STORE2_SWIM_DATA_END_ADDR 			(LOG_ADDR_SET(260,0,0) - 1)
#define STORE2_SWIM_LOG_MAX					200 // 200*5 = 1000
#define STORE2_SWIM_DATA_CLASSIFY_LEN		5
#define STORE2_SWIM_SAMPLE_INFO				((DATASAMPLE_UNIT_1S << 12) | 10)	// 2 bytes ������Ϣ����4bit��ʾ��λ����12bitΪ��ֵ

/* �Ʋ����ݴ洢��Ϣ */
#define STORE2_STEP_MAX_ALLOT_CATALOG		(512)	// �����Ŀ¼����������ռ䣩��ÿblock�ɷ���256��Ŀ¼����2block
#define STORE2_STEP_MAX_SAVE_CATALOG		(30)	// �����Ŀ¼������������ֵ��FIFO��ʽ����
#define STORE2_STEP_CATALOG_BEGIN_ADDR		(LOG_ADDR_SET(260,0,0))
#define STORE2_STEP_CATALOG_END_ADDR 		(LOG_ADDR_SET(262,0,0) - 1)
#define STORE2_STEP_DATA_BEGIN_ADDR			(LOG_ADDR_SET(262,0,0))
#define STORE2_STEP_DATA_END_ADDR 			(LOG_ADDR_SET(280,0,0) - 1)
#define STORE2_STEP_LOG_MAX					144 // 5minһ������һ��288
#define STORE2_STEP_DATA_CLASSIFY_LEN		2
#define STORE2_STEP_SAMPLE_INFO				((DATASAMPLE_UNIT_1S << 12) | 300)	// 2 bytes ������Ϣ����4bit��ʾ��λ����12bitΪ��ֵ

/* ˯�����ݴ洢��Ϣ */
#define STORE2_SLEEP_MAX_ALLOT_CATALOG		(512)	// �����Ŀ¼����������ռ䣩��ÿblock�ɷ���256��Ŀ¼����2block
#define STORE2_SLEEP_MAX_SAVE_CATALOG		(30)	// �����Ŀ¼������������ֵ��FIFO��ʽ����
#define STORE2_SLEEP_CATALOG_BEGIN_ADDR		(LOG_ADDR_SET(280,0,0))
#define STORE2_SLEEP_CATALOG_END_ADDR 		(LOG_ADDR_SET(282,0,0) - 1)
#define STORE2_SLEEP_DATA_BEGIN_ADDR		(LOG_ADDR_SET(282,0,0))
#define STORE2_SLEEP_DATA_END_ADDR 			(LOG_ADDR_SET(300,0,0) - 1)
#define STORE2_SLEEP_LOG_MAX				144 // 5minһ������һ��288
#define STORE2_SLEEP_DATA_CLASSIFY_LEN		2
#define STORE2_SLEEP_SAMPLE_INFO			((DATASAMPLE_UNIT_1S << 12) | 300)	// 2 bytes ������Ϣ����4bit��ʾ��λ����12bitΪ��ֵ

/* �������ݴ洢��Ϣ */
#define STORE2_HRD_MAX_ALLOT_CATALOG	(512)	// �����Ŀ¼����������ռ䣩��ÿblock�ɷ���256��Ŀ¼����2block
#define STORE2_HRD_MAX_SAVE_CATALOG		(30)	// �����Ŀ¼������������ֵ��FIFO��ʽ����
#define STORE2_HRD_CATALOG_BEGIN_ADDR	(LOG_ADDR_SET(300,0,0))
#define STORE2_HRD_CATALOG_END_ADDR 	(LOG_ADDR_SET(302,0,0) - 1)
#define STORE2_HRD_DATA_BEGIN_ADDR		(LOG_ADDR_SET(302,0,0))
#define STORE2_HRD_DATA_END_ADDR 		(LOG_ADDR_SET(320,0,0) - 1)
#define STORE2_HRD_LOG_MAX				360 // 2minһ������һ��720
#define STORE2_HRD_DATA_CLASSIFY_LEN	1
#define STORE2_HRD_SAMPLE_INFO			((DATASAMPLE_UNIT_1S << 12) | 120)	// 2 bytes ������Ϣ����4bit��ʾ��λ����12bitΪ��ֵ

/* ����ѹ�����ݴ洢��Ϣ */
#define STORE2_STRESS_MAX_ALLOT_CATALOG		(512)	// �����Ŀ¼����������ռ䣩��ÿblock�ɷ���256��Ŀ¼����2block
#define STORE2_STRESS_MAX_SAVE_CATALOG		(30)	// �����Ŀ¼������������ֵ��FIFO��ʽ����
#define STORE2_STRESS_CATALOG_BEGIN_ADDR	(LOG_ADDR_SET(320,0,0))
#define STORE2_STRESS_CATALOG_END_ADDR 		(LOG_ADDR_SET(322,0,0) - 1)
#define STORE2_STRESS_DATA_BEGIN_ADDR		(LOG_ADDR_SET(322,0,0))
#define STORE2_STRESS_DATA_END_ADDR 		(LOG_ADDR_SET(340,0,0) - 1)
#define STORE2_STRESS_LOG_MAX				144 // 10minһ������һ��144
#define STORE2_STRESS_DATA_CLASSIFY_LEN		2	
#define STORE2_STRESS_SAMPLE_INFO			((DATASAMPLE_UNIT_1S << 12) | 600)	// 2 bytes ������Ϣ����4bit��ʾ��λ����12bitΪ��ֵ

/* �������ݴ洢��Ϣ */
#define STORE2_BODYTEMP_MAX_ALLOT_CATALOG	(512)	// �����Ŀ¼����������ռ䣩��ÿblock�ɷ���256��Ŀ¼����2block
#define STORE2_BODYTEMP_MAX_SAVE_CATALOG	(30)	// �����Ŀ¼������������ֵ��FIFO��ʽ����
#define STORE2_BODYTEMP_CATALOG_BEGIN_ADDR	(LOG_ADDR_SET(340,0,0))
#define STORE2_BODYTEMP_CATALOG_END_ADDR 	(LOG_ADDR_SET(342,0,0) - 1)
#define STORE2_BODYTEMP_DATA_BEGIN_ADDR		(LOG_ADDR_SET(342,0,0))
#define STORE2_BODYTEMP_DATA_END_ADDR 		(LOG_ADDR_SET(360,0,0) - 1)
#define STORE2_BODYTEMP_LOG_MAX				360 // 2minһ������һ��720
#define STORE2_BODYTEMP_DATA_CLASSIFY_LEN	2	
#define STORE2_BODYTEMP_SAMPLE_INFO			((DATASAMPLE_UNIT_1S << 12) | 120)	// 2 bytes ������Ϣ����4bit��ʾ��λ����12bitΪ��ֵ

/* ABC���ݴ洢��Ϣ */
#define STORE2_ABC_MAX_ALLOT_CATALOG	(512)	// �����Ŀ¼����������ռ䣩��ÿblock�ɷ���256��Ŀ¼����2block
#define STORE2_ABC_MAX_SAVE_CATALOG		(30)	// �����Ŀ¼������������ֵ��FIFO��ʽ����
#define STORE2_ABC_CATALOG_BEGIN_ADDR	(LOG_ADDR_SET(360,0,0))
#define STORE2_ABC_CATALOG_END_ADDR 	(LOG_ADDR_SET(362,0,0) - 1)
#define STORE2_ABC_DATA_BEGIN_ADDR		(LOG_ADDR_SET(362,0,0))
#define STORE2_ABC_DATA_END_ADDR 		(LOG_ADDR_SET(380,0,0) - 1)
#define STORE2_ABC_LOG_MAX				120 // 2minһ������һ��720
#define STORE2_ABC_DATA_CLASSIFY_LEN	12 	
#define STORE2_ABC_LOG_MAX_LEN			(STORE2_ABC_LOG_MAX*STORE2_ABC_DATA_CLASSIFY_LEN)
#define STORE2_ABC_SAMPLE_INFO			((DATASAMPLE_UNIT_1S << 12) | 120)	// 2 bytes ������Ϣ����4bit��ʾ��λ����12bitΪ��ֵ

/* ˯�ߵ������ݴ洢��Ϣ */
#define STORE2_SLPRCD_MAX_ALLOT_CATALOG		(512)	// �����Ŀ¼����������ռ䣩��ÿblock�ɷ���256��Ŀ¼����2block
#define STORE2_SLPRCD_MAX_SAVE_CATALOG		(30)	// �����Ŀ¼������������ֵ��FIFO��ʽ����
#define STORE2_SLPRCD_CATALOG_BEGIN_ADDR	(LOG_ADDR_SET(380,0,0))
#define STORE2_SLPRCD_CATALOG_END_ADDR 		(LOG_ADDR_SET(382,0,0) - 1)
#define STORE2_SLPRCD_DATA_BEGIN_ADDR		(LOG_ADDR_SET(382,0,0))
#define STORE2_SLPRCD_DATA_END_ADDR 		(LOG_ADDR_SET(400,0,0) - 1)
//#define STORE2_SLEEPRECORD_LOG_MAX				120 // 2minһ������һ��720
//#define STORE2_SLEEPRECORD_DATA_CLASSIFY_LEN	12 	
//#define STORE2_SLEEPRECORD_LOG_MAX_LEN			(STORE2_ABC_LOG_MAX*STORE2_ABC_DATA_CLASSIFY_LEN)
//#define STORE2_SLEEPRECORD_SAMPLE_INFO			((DATASAMPLE_UNIT_1S << 12) | 120)	// 2 bytes ������Ϣ����4bit��ʾ��λ����12bitΪ��ֵ

/* GPS���ݴ洢��Ϣ */
#define STORE2_GPS_MAX_ALLOT_CATALOG		(512)	// �����Ŀ¼����������ռ䣩��ÿblock�ɷ���256��Ŀ¼����2block
#define STORE2_GPS_MAX_SAVE_CATALOG			(30)	// �����Ŀ¼������������ֵ��FIFO��ʽ����
#define STORE2_GPS_CATALOG_BEGIN_ADDR		(LOG_ADDR_SET(400,0,0))
#define STORE2_GPS_CATALOG_END_ADDR 		(LOG_ADDR_SET(402,0,0) - 1)
#define STORE2_GPS_DATA_BEGIN_ADDR			(LOG_ADDR_SET(402,0,0))
#define STORE2_GPS_DATA_END_ADDR 			(LOG_ADDR_SET(420,0,0) - 1)
#define STORE2_GPS_LOG_MAX					128 	// 128 * 8 = 1024
#define STORE2_GPS_DATA_CLASSIFY_LEN		8 	
#define STORE2_GPS_LOG_MAX_LEN				(STORE2_GPS_LOG_MAX*STORE2_GPS_DATA_CLASSIFY_LEN)
#define STORE2_GPS_SAMPLE_INFO				((DATASAMPLE_UNIT_1S << 12) | 120)	// 2 bytes ������Ϣ����4bit��ʾ��λ����12bitΪ��ֵ




/* ������λ */
typedef enum
{
	DATASAMPLE_UNIT_1US		= 1,
	DATASAMPLE_UNIT_1MS,
	DATASAMPLE_UNIT_1S,
	DATASAMPLE_UNIT_10US,
	DATASAMPLE_UNIT_10MS,
	DATASAMPLE_UNIT_10S,
}data_sample_uint_e;

typedef enum
{
	eStoreStatusNull,	// δ���ٴ洢Ŀ¼����ʼ������Ŀ¼����
	eStoreStatusIng,	// ���ڴ洢���ݣ�Ŀ¼������
}StoreStatus_e;

typedef enum	// Ŀ¼״̬��־λ����
{
	eCatalogMarkDeleted = 0x00,	// ��ɾ��
	eCatalogMarkCover = 0xE0,	// �Ѹ���
	
	/* ���ݻָ�ʱ�����ָ����ԡ��ϴ���������������� */
	eCatalogMarkIgnore = 0xF0,	// �Ѻ��ԣ����ܲ�������������ݱ�����
	eCatalogMarkUpload = 0xF8,	// ���ϴ�
	eCatalogMarkSealed = 0xFC,	// �ѷ��
	
	eCatalogMarkUsing = 0xFE,	// ����ʹ��
	eCatalogMarkUnuse = 0xFF,	// δʹ��
}CatalogMart_e;

typedef struct	// Ŀ¼flash�洢��Ϣ�ṹ��
{
	uint32_t 		DataLen;	// ��Ŀ¼��Ӧ���������ݳ���
	uint32_t 		DataAddr;	// ��Ŀ¼��Ӧ��������ַ
	CatalogMart_e 	Mark;		// Ŀ¼Mark��δʹ�á�����ʹ�á���ɾ����
}CatalogFlashInfo_t;

typedef struct	// Ŀ¼�û���Ϣ�ṹ��
{
	uint32_t UTC;
	uint16_t DataClassify;			// �������ͣ�����Э�飬��Ʋ����ܲ�����Ӿ��
	uint16_t ExtDataLen;			// ������Ϣ����
}CatalogUserInfo_t;

typedef struct	// Ŀ¼��Ϣ�ṹ��
{
	union
	{
		uint8_t 			Buf[STORE2_CATALOG_FLASH_INFO_LEN];
		CatalogFlashInfo_t	Info;
	}Flash;
	
	union
	{
		uint8_t 			Buf[STORE2_CATALOG_USER_INFO_LEN];
		CatalogUserInfo_t	Info;
	}User;
}CatalogInfo_t;


typedef struct	// �洢��Ϣ�ṹ�壬ÿ�ִ洢���ͣ��Ʋ���˯�ߡ���Ӿ�ȣ�������һ�������Ľṹ��
{
	CatalogInfo_t		Catalog;		// ��ǰ�洢���ݵ�Ŀ¼��Ϣ
	
	StoreStatus_e		Status;			// �洢״̬				
	
	uint32_t 			CatalogBeginAddr;	// �̶�ֵ��Ŀ¼�洢��ʼ��ʼ
	uint32_t 			CatalogEndAddr;		// �̶�ֵ��Ŀ¼�洢������ַ��������
	
	uint32_t			CatalogSerialMax;		// �̶�ֵ�����Ŀ¼�����ɷ���Ĵ洢�ռ����
	uint32_t			CatalogSerialMaxSave;	// �̶�ֵ������������Ŀ¼
	uint32_t 			CatalogSerialBegin;		// ��Ч�洢Ŀ¼��ʼ��ţ���Ŀ¼Cnt����Ŀ¼MaxSave����ǰĿ¼Begin��Ǳ����ǣ�Ȼ��+1
	uint32_t			CatalogSerialEnd;		// ��Ч�洢Ŀ¼������ţ�ÿ�δ���Ŀ¼ʱ+1
	uint32_t			CatalogSerialCnt;		// �Ѵ洢Ŀ¼������ÿ�η��Ŀ¼ʱ+1����󲻳���MaxSave
	
	uint32_t 			DataBeginAddr;	// �̶�ֵ�����ݴ洢��ʼ��ʼ
	uint32_t 			DataEndAddr;	// �̶�ֵ�����ݴ洢������ַ��������	
	uint32_t 			DataCurrAddr;	// ��ǰ���ݴ洢��ַ
}StoreInfo_t;













#endif



