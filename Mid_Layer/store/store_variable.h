#ifndef STORE_VARIABLE_H
#define STORE_VARIABLE_H

#include "platform_common.h"
#include "algorithm_sleep.h"
#include "mid_common.h"
#include "mid_nandflash.h"	// LOG_ADDR_SET() 等宏定义

#define STORE_RTT_DEBUG	3
#if (1 == STORE_RTT_DEBUG)	// 错误等级
#define STORE_RTT_LOG(...)
#define STORE_RTT_WARN(...)
#define STORE_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == STORE_RTT_DEBUG)	// 警告等级
#define STORE_RTT_LOG(...)
#define STORE_RTT_WARN		RTT_DEBUG_WARN
#define STORE_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == STORE_RTT_DEBUG)	// 调试等级
#define STORE_RTT_LOG		RTT_DEBUG_LOG
#define STORE_RTT_WARN		RTT_DEBUG_WARN
#define STORE_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define STORE_RTT_LOG(...)
#define STORE_RTT_WARN(...)
#define STORE_RTT_ERR(...)
#endif

#define	PDU_DATA_UPLOAD_MAX_LEN		16	// app蓝牙每次上传最大字节 2序号+2类型+16有效数据

// 分类数据的目录数量与数据长度返回协议
static const protocal_msg_t	PROT_PACK_TRANS_CATA_TOTAL_RET =
{
	0x23, 0x01, 0x0B, 0x13, 0x00, 0x08, 0xf0, 0x10,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};

// 分类数据的目录内容返回协议
static const protocal_msg_t	PROT_PACK_TRANS_CATA_RET =
{
	0x23, 0x01, 0x0c, 0x13, 0x00, 0x08, 0xf0, 0x11,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};

// 分类数据的数据包请求结果反馈
static const protocal_msg_t	PROT_PACK_TRANS_DATA_RET =
{
	0x23, 0x01, 0x04, 0x13, 0x00, 0x08, 0xf0, 0x12,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};

// 删除所有数据反馈
static const protocal_msg_t	PROT_PACK_TRANS_DELETE_ALL_RET =
{
	0x23, 0x01, 0x04, 0x13, 0x00, 0x80, 0xf0, 0x30,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};

// 删除某类数据反馈
static const protocal_msg_t	PROT_PACK_TRANS_DELETE_CLASS_RET =
{
	0x23, 0x01, 0x06, 0x13, 0x00, 0x80, 0xf0, 0x31,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};

// 删除目录反馈
static const protocal_msg_t	PROT_PACK_TRANS_DELETE_CATALOG_RET =
{
	0x23, 0x01, 0x0a, 0x13, 0x00, 0x80, 0xf0, 0x32,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};

// 数据包上传协议
static const protocal_msg_t	PROT_PACK_TRANS_DATA_UPLOAD =
{
	0x23, 0x01, 0x17, 0x12, 0x80, 0x01, 0xf0, 0x01,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};

// 获取最近睡眠记录条目RET
static const protocal_msg_t	PROT_SCENE_SLEEP_RECORD_CONTENT_RET =	
{
	0x23, 0x01, 0x04, 0x13, 0x00, 0x08, 0x14, 0x03,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// 获取条目的睡眠记录信息1 RET（H002所用新睡眠）
static const protocal_msg_t	PROT_SCENE_SLEEP_RECORD_INFO_NEW_RET =
{
	0x23, 0x01, 0x0E, 0x13, 0x00, 0x08, 0x14, 0x14,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	
};

// 获取条目的睡眠记录信息1 ECHO（H002所用新睡眠）
static const protocal_msg_t	PROT_SCENE_SLEEP_RECORD_INFO_NEW_ECHO =
{
	0x23, 0x01, 0x07, 0x13, 0x00, 0x80, 0x14, 0x14,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	
};

// 删除条目的睡眠记录信息ECHO
static const protocal_msg_t	PROT_SCENE_SLEEP_RECORD_DEL_ECHO =
{
	0x23, 0x01, 0x08, 0x13, 0x00, 0x80, 0x14, 0x05,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 	
};


// ***************************************************************************
// ***************************************************************************
// 场景 **********************************************************************
// ***************************************************************************
// ***************************************************************************
// 分类数据的目录数量与数据长度返回协议
static const protocal_msg_t	PROT_SCENE_TRANS_CATA_TOTAL_RET =
{
	0x23, 0x01, 0x0B, 0x13, 0x00, 0x08, 0xf2, 0x10,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// 分类数据的目录内容返回协议
static const protocal_msg_t	PROT_SCENE_TRANS_CATA_RET =
{
	0x23, 0x01, 0x03, 0x13, 0x00, 0x08, 0xf2, 0x11,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// 分类数据的数据包请求结果反馈
static const protocal_msg_t	PROT_SCENE_TRANS_DATA_RET =
{
	0x23, 0x01, 0x04, 0x13, 0x00, 0x08, 0xf2, 0x12,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// 删除所有数据反馈
static const protocal_msg_t	PROT_SCENE_TRANS_DELETE_ALL_RET =
{
	0x23, 0x01, 0x04, 0x13, 0x00, 0x80, 0xf2, 0x30,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// 删除某类数据反馈
static const protocal_msg_t	PROT_SCENE_TRANS_DELETE_CLASS_RET =
{
	0x23, 0x01, 0x06, 0x13, 0x00, 0x80, 0xf2, 0x31,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// 删除目录反馈
static const protocal_msg_t	PROT_SCENE_TRANS_DELETE_CATALOG_RET =
{
	0x23, 0x01, 0x0a, 0x13, 0x00, 0x80, 0xf2, 0x32,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

// 数据包上传协议
static const protocal_msg_t	PROT_SCENE_TRANS_DATA_UPLOAD =
{
	0x23, 0x01, 0x17, 0x12, 0x80, 0x01, 0xf0, 0x01,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

///* 目录信息标志位 */
//#define STORE_CATALOG_UNUSE	0xFF		// 未使用
//#define STORE_CATALOG_USING	0xFE		// 正在使用
//#define STORE_CATALOG_SEALED	0xFC	// 已封存
//#define STORE_CATALOG_UPLOADED	0xF8	// 已上传
//#define STORE_CATALOG_COVER		0xF0	// 已覆盖
//#define STORE_CATALOG_deleted	0x00	// 已删除

/* 一些公共参数 *************************************/
#define STORE_MAX_MALLOC_LEN				(2048)	// 存储操作时需malloc申请的字节长度
#define STORE_DATA_LEN						(2000)	// 有效数据最大字节
#define STORE_CATALOG_LEN					(48)	// 目录所占字节
#define STORE_CATALOG_PER_BLOCK				(64)	// 每block有多少目录
#define STORE_MAX_SAVE_CATALOG_NUM			(30)	// 最大保存的目录数，超时此值后FIFO方式覆盖

/* 各个模块存储block区域 */
#define 	STORE_BLOCK_FACTORY			(10)
#define 	STORE_BLOCK_BLE				(11)
#define 	STORE_BLOCK_SYSTOM			(12)
#define 	STORE_BLOCK_TIME			(13)

/* 睡眠档案存储信息 */
#define 	STORE_SLEEP_RECORD_ALLOT_BLOCK				(5)										// 计步存储分配block数
#define 	STORE_SLEEP_RECORD_MAX_CATALOG_NUM			(STORE_SLEEP_RECORD_ALLOT_BLOCK * 64)	// 最大目录数量（分配的物理数量）
#define 	STORE_SLEEP_RECORD_MAX_SAVE_CATALOG_NUM		(30)									// 最大保存的目录数量，超过此值会被丢弃
#define 	STORE_SLEEP_RECORD_BEGIN_ADDR				(LOG_ADDR_SET(50,0,0))
#define 	STORE_SLEEP_RECORD_END_ADDR 				(LOG_ADDR_SET(55,0,0) - 1)
#define 	STORE_SLEEP_RECORD_LOG_MAX				 	1 // 
#define 	STORE_SLEEP_RECORD_DATA_CLASSIFY_LEN		255	// 随便给的一个较大值

/* Part分区信息 *************************************/
#define STORE_PART_NUM_256B			(320)
#define STORE_PART_NUM_512B			(80)
#define STORE_PART_NUM_1KB			(40)
#define STORE_PART_NUM_2KB			(20)
#define STORE_PART_BEGIN_ADDR_256B  (LOG_ADDR_SET(100,0,0))
#define STORE_PART_BEGIN_ADDR_512B  (LOG_ADDR_SET(140,0,0))
#define STORE_PART_BEGIN_ADDR_1KB   (LOG_ADDR_SET(160,0,0))
#define STORE_PART_BEGIN_ADDR_2KB   (LOG_ADDR_SET(180,0,0))

/* 出厂信息存储地址 *************************************/
#define STORE_FACTORY_CODE_ID				"factory"
#define STORE_FACTORY_ADDR_ID				(96)	// "factory"
#define STORE_FACTORY_ADDR_VER				(112)
#define STORE_FACTORY_ADDR_SN				(128)
#define STORE_FACTORY_ADDR_MAC				(160)
#define STORE_FACTORY_ADDR_MANAGER_SN		(192)	// 客户SN
#define STORE_FACTORY_ADDR_SOFTWARE			(224)	
#define STORE_FACTORY_ADDR_HARDWARE			(256)

/* 蓝牙信息存储地址 *************************************/
#define STORE_BLE_CODE_ID						"ble"
#define STORE_BLE_ADDR_ID						(96)	// "ble"
#define STORE_BLE_ADDR_VER						(112)
#define STORE_BLE_ADDR_NAME						(128)

/* 系统配置存储地址 *************************************/
#define STORE_SYS_CODE_ID						"system"
#define STORE_SYS_ADDR_ID						(96)	// "system"
#define STORE_SYS_ADDR_VER						(112)
#define STORE_SYS_ADDR_LANGUAGE					(128)	// 系统语言
#define STORE_SYS_ADDR_TIME_FORMAT				(129)	// 时间制式
#define STORE_SYS_ADDR_STEP_SWITCH				(130)	// 后台计步开关
#define STORE_SYS_ADDR_HRD_SWITCH				(131)	// 后台心率开关
#define STORE_SYS_ADDR_WEATHER_SWITCH			(132)	// 天气预测开关
#define STORE_SYS_ADDR_STEP_REMIND_SWITCH		(133)	// 运动（计步）完成提醒开关
#define STORE_SYS_ADDR_BLE_OFF_REMIND_SWITCH	(134)	// 蓝牙断开开关
#define STORE_SYS_ADDR_SEDENTARY_REMIND_SWITCH	(135)	// 久坐提醒开关
#define STORE_SYS_ADDR_NO_DISTURB_SWITCH		(136)	// 勿扰开关
#define STORE_SYS_ADDR_APP_REMIND_SWITCH		(137)	// 手机提醒开关
#define STORE_SYS_ADDR_APP_DETAIL_REMIND_SWITCH	(141)	// 详情提醒开关
#define STORE_SYS_ADDR_GESTURE					(145)	// 手势开关
#define STORE_SYS_ADDR_HEIGHT					(256)	// 身高
#define STORE_SYS_ADDR_WEIGHT					(257)	// 体重
#define STORE_SYS_ADDR_SEX						(258)	// 性别
#define STORE_SYS_ADDR_AGE						(259)	// 年龄

/* 时间信息存储地址 *************************************/
#define STORE_TIME_CODE_ID						"time"
#define STORE_TIME_ADDR_ID						(96)	// "time"
#define STORE_TIME_ADDR_VER						(112)
#define STORE_TIME_ADDR_LOCAL_TIME				(128)		// 当地时间
#define STORE_TIME_ADDR_WORD_TIME				(160)		// 世界时间
#define STORE_TIME_ADDR_CITY_CODE				(192)		// 城市代号
#define STORE_TIME_ADDR_NO_DISTURB				(194)		// 勿扰时间段
#define STORE_TIME_ADDR_SEDENTARY				(226)		// 久坐时间段
#define STORE_TIME_ADDR_ALARM_0					(258)		// 闹钟1
#define STORE_TIME_ADDR_ALARM_1					(274)		// 闹钟2
#define STORE_TIME_ADDR_ALARM_2					(290)		// 闹钟3
#define STORE_TIME_ADDR_ALARM_3					(306)		// 闹钟4
#define STORE_TIME_ADDR_ALARM_4					(322)		// 闹钟5



/* 一些公共参数 */
#define STORE2_MAX_SAVE_CATALOG_NUM			(30)	// 最大保存的目录数，超时此值后FIFO方式覆盖


/* 目录相关宏 */
#define STORE2_CATALOG_INFO_LEN			(512)	// 每个目录分配的字节
#define STORE2_CATALOG_FLASH_INFO_LEN	(32)	// 目录存储信息所占字节
#define STORE2_CATALOG_USER_INFO_LEN	(32)	// 目录用户信息所占字节
#define STORE2_CATALOG_EXT_INFO_LEN		(448)	// 目录附加信息所占字节
#define STORE2_CATALOG_NUM_PER_BLOCK	(256)	// 每block有多少目录,2048/512*64

/* 户外跑数据存储信息 */
#define STORE2_RUN_MAX_ALLOT_CATALOG		(512)	// 分配的目录数量（物理空间），每block可分配256个目录，共2block
#define STORE2_RUN_MAX_SAVE_CATALOG			(30)	// 保存的目录数量，超过此值以FIFO方式丢弃
#define STORE2_RUN_CATALOG_BEGIN_ADDR		(LOG_ADDR_SET(200,0,0))
#define STORE2_RUN_CATALOG_END_ADDR 		(LOG_ADDR_SET(202,0,0) - 1)
#define STORE2_RUN_DATA_BEGIN_ADDR			(LOG_ADDR_SET(202,0,0))
#define STORE2_RUN_DATA_END_ADDR 			(LOG_ADDR_SET(220,0,0) - 1)
#define STORE2_RUN_LOG_MAX					142 // 142 * 14 = 1988
#define STORE2_RUN_DATA_CLASSIFY_LEN		14	
#define STORE2_RUN_SAMPLE_INFO				((DATASAMPLE_UNIT_1S << 12) | 10)// 2 bytes 采样信息，高4bit表示单位，低12bit为数值

/* 登山数据存储信息 */
#define STORE2_CLIMB_MAX_ALLOT_CATALOG		(512)	// 分配的目录数量（物理空间），每block可分配256个目录，共2block
#define STORE2_CLIMB_MAX_SAVE_CATALOG		(30)	// 保存的目录数量，超过此值以FIFO方式丢弃
#define STORE2_CLIMB_CATALOG_BEGIN_ADDR		(LOG_ADDR_SET(220,0,0))
#define STORE2_CLIMB_CATALOG_END_ADDR 		(LOG_ADDR_SET(222,0,0) - 1)
#define STORE2_CLIMB_DATA_BEGIN_ADDR		(LOG_ADDR_SET(222,0,0))
#define STORE2_CLIMB_DATA_END_ADDR 			(LOG_ADDR_SET(240,0,0) - 1)
#define STORE2_CLIMB_LOG_MAX				153 // 153 * 13 = 1989
#define STORE2_CLIMB_DATA_CLASSIFY_LEN		13	
#define STORE2_CLIMB_SAMPLE_INFO			((DATASAMPLE_UNIT_1S << 12) | 10)	// 2 bytes 采样信息，高4bit表示单位，低12bit为数值

/* 游泳数据存储信息 */
#define STORE2_SWIM_MAX_ALLOT_CATALOG		(512)	// 分配的目录数量（物理空间），每block可分配256个目录，共2block
#define STORE2_SWIM_MAX_SAVE_CATALOG		(30)	// 保存的目录数量，超过此值以FIFO方式丢弃
#define STORE2_SWIM_CATALOG_BEGIN_ADDR		(LOG_ADDR_SET(240,0,0))
#define STORE2_SWIM_CATALOG_END_ADDR 		(LOG_ADDR_SET(242,0,0) - 1)
#define STORE2_SWIM_DATA_BEGIN_ADDR			(LOG_ADDR_SET(242,0,0))
#define STORE2_SWIM_DATA_END_ADDR 			(LOG_ADDR_SET(260,0,0) - 1)
#define STORE2_SWIM_LOG_MAX					200 // 200*5 = 1000
#define STORE2_SWIM_DATA_CLASSIFY_LEN		5
#define STORE2_SWIM_SAMPLE_INFO				((DATASAMPLE_UNIT_1S << 12) | 10)	// 2 bytes 采样信息，高4bit表示单位，低12bit为数值

/* 计步数据存储信息 */
#define STORE2_STEP_MAX_ALLOT_CATALOG		(512)	// 分配的目录数量（物理空间），每block可分配256个目录，共2block
#define STORE2_STEP_MAX_SAVE_CATALOG		(30)	// 保存的目录数量，超过此值以FIFO方式丢弃
#define STORE2_STEP_CATALOG_BEGIN_ADDR		(LOG_ADDR_SET(260,0,0))
#define STORE2_STEP_CATALOG_END_ADDR 		(LOG_ADDR_SET(262,0,0) - 1)
#define STORE2_STEP_DATA_BEGIN_ADDR			(LOG_ADDR_SET(262,0,0))
#define STORE2_STEP_DATA_END_ADDR 			(LOG_ADDR_SET(280,0,0) - 1)
#define STORE2_STEP_LOG_MAX					144 // 5min一个包，一天288
#define STORE2_STEP_DATA_CLASSIFY_LEN		2
#define STORE2_STEP_SAMPLE_INFO				((DATASAMPLE_UNIT_1S << 12) | 300)	// 2 bytes 采样信息，高4bit表示单位，低12bit为数值

/* 睡眠数据存储信息 */
#define STORE2_SLEEP_MAX_ALLOT_CATALOG		(512)	// 分配的目录数量（物理空间），每block可分配256个目录，共2block
#define STORE2_SLEEP_MAX_SAVE_CATALOG		(30)	// 保存的目录数量，超过此值以FIFO方式丢弃
#define STORE2_SLEEP_CATALOG_BEGIN_ADDR		(LOG_ADDR_SET(280,0,0))
#define STORE2_SLEEP_CATALOG_END_ADDR 		(LOG_ADDR_SET(282,0,0) - 1)
#define STORE2_SLEEP_DATA_BEGIN_ADDR		(LOG_ADDR_SET(282,0,0))
#define STORE2_SLEEP_DATA_END_ADDR 			(LOG_ADDR_SET(300,0,0) - 1)
#define STORE2_SLEEP_LOG_MAX				144 // 5min一个包，一天288
#define STORE2_SLEEP_DATA_CLASSIFY_LEN		2
#define STORE2_SLEEP_SAMPLE_INFO			((DATASAMPLE_UNIT_1S << 12) | 300)	// 2 bytes 采样信息，高4bit表示单位，低12bit为数值

/* 心率数据存储信息 */
#define STORE2_HRD_MAX_ALLOT_CATALOG	(512)	// 分配的目录数量（物理空间），每block可分配256个目录，共2block
#define STORE2_HRD_MAX_SAVE_CATALOG		(30)	// 保存的目录数量，超过此值以FIFO方式丢弃
#define STORE2_HRD_CATALOG_BEGIN_ADDR	(LOG_ADDR_SET(300,0,0))
#define STORE2_HRD_CATALOG_END_ADDR 	(LOG_ADDR_SET(302,0,0) - 1)
#define STORE2_HRD_DATA_BEGIN_ADDR		(LOG_ADDR_SET(302,0,0))
#define STORE2_HRD_DATA_END_ADDR 		(LOG_ADDR_SET(320,0,0) - 1)
#define STORE2_HRD_LOG_MAX				360 // 2min一个包，一天720
#define STORE2_HRD_DATA_CLASSIFY_LEN	1
#define STORE2_HRD_SAMPLE_INFO			((DATASAMPLE_UNIT_1S << 12) | 120)	// 2 bytes 采样信息，高4bit表示单位，低12bit为数值

/* 人体压力数据存储信息 */
#define STORE2_STRESS_MAX_ALLOT_CATALOG		(512)	// 分配的目录数量（物理空间），每block可分配256个目录，共2block
#define STORE2_STRESS_MAX_SAVE_CATALOG		(30)	// 保存的目录数量，超过此值以FIFO方式丢弃
#define STORE2_STRESS_CATALOG_BEGIN_ADDR	(LOG_ADDR_SET(320,0,0))
#define STORE2_STRESS_CATALOG_END_ADDR 		(LOG_ADDR_SET(322,0,0) - 1)
#define STORE2_STRESS_DATA_BEGIN_ADDR		(LOG_ADDR_SET(322,0,0))
#define STORE2_STRESS_DATA_END_ADDR 		(LOG_ADDR_SET(340,0,0) - 1)
#define STORE2_STRESS_LOG_MAX				144 // 10min一个包，一天144
#define STORE2_STRESS_DATA_CLASSIFY_LEN		2	
#define STORE2_STRESS_SAMPLE_INFO			((DATASAMPLE_UNIT_1S << 12) | 600)	// 2 bytes 采样信息，高4bit表示单位，低12bit为数值

/* 体温数据存储信息 */
#define STORE2_BODYTEMP_MAX_ALLOT_CATALOG	(512)	// 分配的目录数量（物理空间），每block可分配256个目录，共2block
#define STORE2_BODYTEMP_MAX_SAVE_CATALOG	(30)	// 保存的目录数量，超过此值以FIFO方式丢弃
#define STORE2_BODYTEMP_CATALOG_BEGIN_ADDR	(LOG_ADDR_SET(340,0,0))
#define STORE2_BODYTEMP_CATALOG_END_ADDR 	(LOG_ADDR_SET(342,0,0) - 1)
#define STORE2_BODYTEMP_DATA_BEGIN_ADDR		(LOG_ADDR_SET(342,0,0))
#define STORE2_BODYTEMP_DATA_END_ADDR 		(LOG_ADDR_SET(360,0,0) - 1)
#define STORE2_BODYTEMP_LOG_MAX				360 // 2min一个包，一天720
#define STORE2_BODYTEMP_DATA_CLASSIFY_LEN	2	
#define STORE2_BODYTEMP_SAMPLE_INFO			((DATASAMPLE_UNIT_1S << 12) | 120)	// 2 bytes 采样信息，高4bit表示单位，低12bit为数值

/* ABC数据存储信息 */
#define STORE2_ABC_MAX_ALLOT_CATALOG	(512)	// 分配的目录数量（物理空间），每block可分配256个目录，共2block
#define STORE2_ABC_MAX_SAVE_CATALOG		(30)	// 保存的目录数量，超过此值以FIFO方式丢弃
#define STORE2_ABC_CATALOG_BEGIN_ADDR	(LOG_ADDR_SET(360,0,0))
#define STORE2_ABC_CATALOG_END_ADDR 	(LOG_ADDR_SET(362,0,0) - 1)
#define STORE2_ABC_DATA_BEGIN_ADDR		(LOG_ADDR_SET(362,0,0))
#define STORE2_ABC_DATA_END_ADDR 		(LOG_ADDR_SET(380,0,0) - 1)
#define STORE2_ABC_LOG_MAX				120 // 2min一个包，一天720
#define STORE2_ABC_DATA_CLASSIFY_LEN	12 	
#define STORE2_ABC_LOG_MAX_LEN			(STORE2_ABC_LOG_MAX*STORE2_ABC_DATA_CLASSIFY_LEN)
#define STORE2_ABC_SAMPLE_INFO			((DATASAMPLE_UNIT_1S << 12) | 120)	// 2 bytes 采样信息，高4bit表示单位，低12bit为数值

/* 睡眠档案数据存储信息 */
#define STORE2_SLPRCD_MAX_ALLOT_CATALOG		(512)	// 分配的目录数量（物理空间），每block可分配256个目录，共2block
#define STORE2_SLPRCD_MAX_SAVE_CATALOG		(30)	// 保存的目录数量，超过此值以FIFO方式丢弃
#define STORE2_SLPRCD_CATALOG_BEGIN_ADDR	(LOG_ADDR_SET(380,0,0))
#define STORE2_SLPRCD_CATALOG_END_ADDR 		(LOG_ADDR_SET(382,0,0) - 1)
#define STORE2_SLPRCD_DATA_BEGIN_ADDR		(LOG_ADDR_SET(382,0,0))
#define STORE2_SLPRCD_DATA_END_ADDR 		(LOG_ADDR_SET(400,0,0) - 1)
//#define STORE2_SLEEPRECORD_LOG_MAX				120 // 2min一个包，一天720
//#define STORE2_SLEEPRECORD_DATA_CLASSIFY_LEN	12 	
//#define STORE2_SLEEPRECORD_LOG_MAX_LEN			(STORE2_ABC_LOG_MAX*STORE2_ABC_DATA_CLASSIFY_LEN)
//#define STORE2_SLEEPRECORD_SAMPLE_INFO			((DATASAMPLE_UNIT_1S << 12) | 120)	// 2 bytes 采样信息，高4bit表示单位，低12bit为数值

/* GPS数据存储信息 */
#define STORE2_GPS_MAX_ALLOT_CATALOG		(512)	// 分配的目录数量（物理空间），每block可分配256个目录，共2block
#define STORE2_GPS_MAX_SAVE_CATALOG			(30)	// 保存的目录数量，超过此值以FIFO方式丢弃
#define STORE2_GPS_CATALOG_BEGIN_ADDR		(LOG_ADDR_SET(400,0,0))
#define STORE2_GPS_CATALOG_END_ADDR 		(LOG_ADDR_SET(402,0,0) - 1)
#define STORE2_GPS_DATA_BEGIN_ADDR			(LOG_ADDR_SET(402,0,0))
#define STORE2_GPS_DATA_END_ADDR 			(LOG_ADDR_SET(420,0,0) - 1)
#define STORE2_GPS_LOG_MAX					128 	// 128 * 8 = 1024
#define STORE2_GPS_DATA_CLASSIFY_LEN		8 	
#define STORE2_GPS_LOG_MAX_LEN				(STORE2_GPS_LOG_MAX*STORE2_GPS_DATA_CLASSIFY_LEN)
#define STORE2_GPS_SAMPLE_INFO				((DATASAMPLE_UNIT_1S << 12) | 120)	// 2 bytes 采样信息，高4bit表示单位，低12bit为数值




/* 采样单位 */
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
	eStoreStatusNull,	// 未开辟存储目录：初始化或者目录封存后
	eStoreStatusIng,	// 正在存储数据：目录创建后
}StoreStatus_e;

typedef enum	// 目录状态标志位类型
{
	eCatalogMarkDeleted = 0x00,	// 已删除
	eCatalogMarkCover = 0xE0,	// 已覆盖
	
	/* 数据恢复时，仅恢复忽略、上传、封存这三种类型 */
	eCatalogMarkIgnore = 0xF0,	// 已忽略，如跑步放弃，则此数据被忽略
	eCatalogMarkUpload = 0xF8,	// 已上传
	eCatalogMarkSealed = 0xFC,	// 已封存
	
	eCatalogMarkUsing = 0xFE,	// 正在使用
	eCatalogMarkUnuse = 0xFF,	// 未使用
}CatalogMart_e;

typedef struct	// 目录flash存储信息结构体
{
	uint32_t 		DataLen;	// 此目录对应数据区数据长度
	uint32_t 		DataAddr;	// 此目录对应数据区地址
	CatalogMart_e 	Mark;		// 目录Mark，未使用、正在使用、已删除等
}CatalogFlashInfo_t;

typedef struct	// 目录用户信息结构体
{
	uint32_t UTC;
	uint16_t DataClassify;			// 数据类型，根据协议，如计步、跑步、游泳等
	uint16_t ExtDataLen;			// 附加信息长度
}CatalogUserInfo_t;

typedef struct	// 目录信息结构体
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


typedef struct	// 存储信息结构体，每种存储类型（计步、睡眠、游泳等），都有一个这样的结构体
{
	CatalogInfo_t		Catalog;		// 当前存储数据的目录信息
	
	StoreStatus_e		Status;			// 存储状态				
	
	uint32_t 			CatalogBeginAddr;	// 固定值，目录存储开始起始
	uint32_t 			CatalogEndAddr;		// 固定值，目录存储结束地址（包括）
	
	uint32_t			CatalogSerialMax;		// 固定值，最大目录数，由分配的存储空间决定
	uint32_t			CatalogSerialMaxSave;	// 固定值，被保存的最大目录
	uint32_t 			CatalogSerialBegin;		// 有效存储目录开始序号，若目录Cnt大于目录MaxSave，则当前目录Begin标记被覆盖，然后+1
	uint32_t			CatalogSerialEnd;		// 有效存储目录结束序号，每次创建目录时+1
	uint32_t			CatalogSerialCnt;		// 已存储目录计数，每次封存目录时+1，最大不超过MaxSave
	
	uint32_t 			DataBeginAddr;	// 固定值，数据存储开始起始
	uint32_t 			DataEndAddr;	// 固定值，数据存储结束地址（包括）	
	uint32_t 			DataCurrAddr;	// 当前数据存储地址
}StoreInfo_t;













#endif



