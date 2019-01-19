
#ifndef _DRV_GPS_H
#define _DRV_GPS_H

#include "platform_common.h"

#define DRV_GPS_RTT_DEBUG	2
#if (1 == DRV_GPS_RTT_DEBUG)	// 错误等级
#define DRV_GPS_RTT_LOG(...)
#define DRV_GPS_RTT_WARN(...)
#define DRV_GPS_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == DRV_GPS_RTT_DEBUG)	// 警告等级
#define DRV_GPS_RTT_LOG(...)
#define DRV_GPS_RTT_WARN		RTT_DEBUG_WARN
#define DRV_GPS_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == DRV_GPS_RTT_DEBUG)	// 调试等级
#define DRV_GPS_RTT_LOG		RTT_DEBUG_LOG
#define DRV_GPS_RTT_WARN		RTT_DEBUG_WARN
#define DRV_GPS_RTT_ERR		RTT_DEBUG_ERR
#else							// 调试关闭
#define DRV_GPS_RTT_LOG(...)
#define DRV_GPS_RTT_WARN(...)
#define DRV_GPS_RTT_ERR(...)
#endif

typedef enum 
{
	eGPSEventColdStart,
	eGPSEventHotStart,
	eGPSEventIdle,
}GPSEventId_e;	

typedef enum
{
	/* 冷启动过程 */
	eGPSColdStartProcessPwrOn,		// 先打开系统电源，再打开1.8V电源，再打开0.7V电源
	eGPSColdStartProcessCmdGCD,
	
	/* 热启动上电过程 */
	eGPSHotStartProcessPwrOn,		// 先打开系统电源，再打开1.8V电源，再打开0.7V电源
	eGPSHotStartProcessCmdGSOP,	// @GSOP，配置操作模式：默认模式，采样周期1S
	eGPSHotStartProcessCmdAEPS,	// @AEPS，使能AEP功能：手册无此指令
	eGPSHotStartProcessCmdBSSL,	// @BSSL，输出数据选择：默认全部输出，若后续有些数据不需要输出，可配置。节约CPU资源和功耗
	eGPSHotStartProcessCmdGNS,	// @GNS，选择卫星系统：默认GPS系统
	eGPSHotStartProcessCmdGTIM,	// @GTIM，设置当前UTC时间，发送UTC热启动才有效
	eGPSHotStartProcessCmdGSR,	// @GSR，时间精确的热启动
	
	/* 休眠掉电过程 */
	eGPSIdleProcessCmdGSTP,	// @GSTP， 停止GPS，进入IDLE模式
	eGPSIdleProcessCmdAEPG,	// @AEPG AEPS 0，等待产生AEP数据，约30~60秒
	eGPSIdleProcessCmdBUP,	// @BUP，位置信息存入FLASH，后续热启动需要
	eGPSIdleProcessPwrOff,	// 断电	
}GPSProcessStep_e;

typedef enum
{
	GPSProcessResultSuc,
	GPSProcessResultFai,
}GPSProcessResult_e;

typedef enum
{
	eGPSStateIdle = 1,
	eGPSStateColdStart,
	eGPSStateHotStart,
}GPSState_e;

typedef struct
{
	GPSEventId_e			Id;			// 操作内容
	GPSProcessStep_e 		Step;		// 操作步骤
	GPSProcessResult_e		Result;		// 操作结果
}DrvGPSOperate_t;

typedef struct
{
	bool			InitFlg;
	
	uint8_t			State;				// 0空闲，1冷启动，2热启动
	uint32_t 		SearchingCnt;		// 搜星计时，0 为搜星， 非零增加 正在搜星，非零暂停，搜星时间。
	
	DrvGPSOperate_t	Operate;
}DrvGPSParam_t;

typedef struct
{
	GPSEventId_e	Id;
	uint8_t 		Param;
}GPSEvent_t;

extern void Drv_GPS_Init(void);
extern void Drv_GPS_ColdStart(void);
extern void Drv_GPS_UartParse(uint8_t* fDataBuf, uint32_t fDataLen);
extern void Drv_GPS_HotStart(void);
extern void Drv_GPS_Idle(void);

extern void Drv_GPS_EventProcess(GPSEvent_t* Event_t);
extern void Drv_GPS_Test(uint8_t fExtEvent);


/**********************************************************************
**
**模块说明: GPS数据解析模块，当收到GPS原始串口数据后，调用此模块，解析提取出想
			要的GPS数据
**修改日志：
**
**********************************************************************/

#define GPS_PART_NUM		(40)	// 拆分的最大模块数
#define GPS_PART_BUF_LEN	(12)	// 每个模块最大长度
#define GPS_GSV_SV_MAX		(20)	// 最大存储的可见卫星数量

typedef enum
{
	GPS_MSG_NULL,	// 无效的 GPS 数据
	GPS_MSG_GGA,	// GPS定位信息
	GPS_MSG_GLL,	// 地理定位信息
	GPS_MSG_GNS,	// 
	GPS_MSG_GSA,	// 当前卫星信息
	GPS_MSG_GSV,	// 可见卫星信息
	GPS_MSG_RMC,	// 推荐最小定位信息
	GPS_MSG_VTG,	// 地面速度信息
	GPS_MSG_ZDA		// 时间与日期信息
}GPS_MSG_TYPE_M;

typedef struct
{
	bool		ParseSucFlg;					// 数据解析成功标志
	uint8_t 	PartCnt;						// 模块计数
	uint8_t		PartDataLen[GPS_PART_NUM];		// 每个模块的字符串长度
	char		PartData[GPS_PART_NUM][GPS_PART_BUF_LEN];	// 每个模块的字符串内容
}DRV_GPS_PART_T;

typedef struct
{
	uint8_t SatelliteNum;	// 可见卫星数
	uint8_t SatelliteCnt;	// 已解析存储的卫星数
	struct
	{
		uint8_t ID;				// 卫星编号
		uint8_t Elevation;		// 仰角，0~90，单位度
		uint16_t Azimuth;		// 方位角，0~359，单位度
		uint8_t SNR;			// 载噪比，0~99，单位dB-Hz
	}SatelliteInfo[GPS_GSV_SV_MAX];
}DRV_GPS_GSV_T;

typedef struct
{
	double 	UTC;
	char	Status;	// V 数据无效，A 数据有效
	double	Lat;	// 纬度
	char	uLat;	// 纬度方向，N北，S南
	double	Lon;	// 经度，
	char	uLon;	// 经度方向，E东，W西
	double		Spd;	// 对地速度，单位节
	double		Cog;	// 对地真航向，单位度
	uint32_t	Date;	// 日期（dd 为日， mm 为月， yy 为年）
	double 		Mv;		// 磁偏角，单位为度。 固定为空
	char		MvE;	// 磁偏角方向： E-东， W-西。 固定为空
	char		Mode;	// 定位模式标志,A 自动
}DRV_GPS_RMC_T;

extern void Drv_GPS_InfoParse(char* GPSBuffer);


#endif


































