#ifndef  MID_RTC_H
#define  MID_RTC_H

#include "platform_common.h"

#define MID_RTC_RTT_DEBUG	3
#if (1 == MID_RTC_RTT_DEBUG)	// ����ȼ�
#define MID_RTC_RTT_LOG(...)
#define MID_RTC_RTT_WARN(...)
#define MID_RTC_RTT_ERR		RTT_DEBUG_ERR
#elif (2 == MID_RTC_RTT_DEBUG)	// ����ȼ�
#define MID_RTC_RTT_LOG(...)
#define MID_RTC_RTT_WARN		RTT_DEBUG_WARN
#define MID_RTC_RTT_ERR		RTT_DEBUG_ERR
#elif (3 == MID_RTC_RTT_DEBUG)	// ���Եȼ�
#define MID_RTC_RTT_LOG		RTT_DEBUG_LOG
#define MID_RTC_RTT_WARN		RTT_DEBUG_WARN
#define MID_RTC_RTT_ERR		RTT_DEBUG_ERR
#else							// ���Թر�
#define MID_RTC_RTT_LOG(...)
#define MID_RTC_RTT_WARN(...)
#define MID_RTC_RTT_ERR(...)
#endif


typedef enum
{
    eMidRTCWeekSUN,
    eMidRTCWeekMON,
    eMidRTCWeekTUE,
    eMidRTCWeekWED,
    eMidRTCWeekTHU,
    eMidRTCWeekFRI,
    eMidRTCWeekSAT,
	eMidRTCWeekMax,
}eMidRTCWeek;

typedef enum
{
    eMidRTCMonthJAN     = 1,
    eMidRTCMonthFEB,
    eMidRTCMonthMAR,
    eMidRTCMonthAPR,
    eMidRTCMonthMAY,
    eMidRTCMonthJUN,
    eMidRTCMonthJUL,
    eMidRTCMonthAUG,
    eMidRTCMonthSEP,
    eMidRTCMonthOCT,
    eMidRTCMonthNOV,
    eMidRTCMonthDEC,
} eMidRTCMonth;

typedef struct 
{
    uint8  			year;
    eMidRTCMonth  	month;
    uint8  			day;
    uint8  			hour;
    uint8  			min;
    uint8  			sec;
    eMidRTCWeek  	week;
    uint16 			zone;
}rtc_time_s;

typedef struct
{
	uint8_t 	HalfSecCnt;
	rtc_time_s	RTC;			// ������������ʱ��RTC
	uint32_t 	UTC;			// ������������ʱ��RTC��ӦUTC
	
	uint16_t    cityCode;		// �ڶ�����ʱ�䣬���д���
	rtc_time_s	WordRTC;		// �ڶ�����ʱ�䣬RTCʱ��
}MidRTCParam_t;

typedef enum
{
    eMidRTCMsgDay,     //RTCһ��ʱ���ʱ�����Ϣ
	eMidRTCMsgHour,
    eMidRTCMsgMin,     //RTCÿ���Ӽ�ʱ�����Ϣ
    eMidRTCMsgSec,     //RTCÿ���ʱ�����Ϣ
    eMidRTCMsgHalfSec, //���RtcSecCbInit��ʱ���룬��ʱ�����Ϣ
}eMidRTCMsg;

//**********************************************************************
// ��������: RTC��ʼ��
//       RTCӲ����ʼ����ע���жϻص�����������ʼ��ʱ��ṹ�����
// ��������� ��
// ���ز�������
//**********************************************************************
extern void Mid_Rtc_Init(void);
extern eMidRTCMsg RtcSecPeriodProcess(void);

//**********************************************************************
// ��������: ����Rtc timer
// �����������
// ���ز�������
//**********************************************************************
extern void Mid_Rtc_Start(void);

//**********************************************************************
// ��������: ֹͣRtc timer
// �����������  
// ���ز�������  
//**********************************************************************
extern void Mid_Rtc_Stop(void);

//**********************************************************************
// ��������: ��ȡ��ǰRTCʱ��, �ѵ�ǰ��ʱ�䱣�浽ʱ��ṹ����
// ��������������ʱ��ṹ����������浱ǰʱ��
// ���ز�������
//**********************************************************************
extern void Mid_Rtc_TimeRead(rtc_time_s *timeTemp);

//**********************************************************************
// ��������: ����RTCʱ��,   ����ϵͳʱ��
// ��������������ʱ��ṹ�������ϵͳʱ�����
// ���ز�������
//**********************************************************************
extern void Mid_Rtc_TimeWrite(rtc_time_s *timeTemp);
extern MidRTCParam_t* Mid_RTC_ParamPGet(void);

//**********************************************************************
// ��������: ������ݺ��·ݣ���ѯ�·ݶ�Ӧ������
// ���������   
//        year_1�����
//        month_1:�·�
// ���ز�����    
//        0xff:��ѯʧ��
//        ����ֵ�������·ݵ�����
//**********************************************************************
extern uint8 MonthDay(uint16 year_1, uint8 month_1);

// ******************************************************************************
// *Funtion name:TimeTransformUtc
// *Description :��ʱ��ת��ΪUTCʱ�䣬������ʱ��
// *
// *Input: ��ǰʱ����Ϣ,����Ҫʱ����Ϣ
// *Output:	0x00:	ת���ɹ�
// 			0xff:	ת��ʧ��
// /*****************************************************************************
extern uint16 TimeTransformUtc(rtc_time_s *timeTemp, uint32 *utcTemp);

// ******************************************************************************
// *Funtion name:UtcTransformTime
// *Description :��UTCʱ��ת��Ϊ
// *
// *Input: ��ǰʱ����Ϣ������ʱ��
// *Output:����0ʱ����UTCʱ��
// /*****************************************************************************
extern uint16 UtcTransformTime(uint32 utcTemp, rtc_time_s *timeTemp);

// ******************************************************************************
// *Funtion name:TimeZoneTransform
// *Description :��������curtime��Ϣ��ת��ΪĿ��ʱ��ʱ��
// *
// *Input:	curTime����ǰʱ�䣬��Ҫ������ȷ�ĵ�ǰʱ����ʱ��
// *		aimTime��������Ŀ��ʱ��������ʱ����Ϣ����Ҫ���룬
// *Output:	0x00:	ת���ɹ�
// *		0xff:	ת��ʧ��
// /*****************************************************************************
extern uint16 TimeZoneTransform(rtc_time_s *curTime, rtc_time_s *aimTime);

// ******************************************************************************
// *Funtion name:Read_GMT_Utc
// *Description :����0ʱ����UTCʱ��
// *
// *Input: data
// *Output:None
// /*****************************************************************************
extern uint32 Read_GMT_Utc(void);

// ******************************************************************************
// *Funtion name:Read_Cur_Utc
// *Description :���ص�ǰʱ���UTCʱ��
// *
// *Input: none
// *Output: 0 : ת��ʧ��
// 			������UTCʱ��
// /*****************************************************************************
extern uint32 Mid_Rtc_ReadCurUtc(void);

// ******************************************************************************
// *Funtion name:TimePeriodJudge
// *Description :�ж���һ�����Ƿ����ƶ���ʱ�����
// *
// *Input:	startTime:	ʱ��ο�ʼʱ�̣�������ʱ�䣬��λΪ��
// 			endTime:	ʱ��ν���ʱ�̣�������ʱ�䣬��λΪ��
// 			inputTime:	�����ʱ�̣��жϸ�ʱ���Ƿ���ʱ����ڣ���λΪ��
// *Output: 0 : ���ڸ�ʱ�����
// 			1 : �ڸ�ʱ�����
// /*****************************************************************************
extern uint16 TimePeriodJudge(uint32 startTime, uint32 endTime, uint32 inputTime);

//**********************************************************************
// ��������: ���������գ����㵱ǰ������һ���еĵڼ���
//    ���������գ�ʹ�ò�������ڵ���Ч��ΧΪ2000/1/1��2099/12/30
// ���������   
//    LocalYear��ʵ����� - 2000��LocalYear ����Ч��ΧΪ0-99��
//    LocalMonth:�·�           ��LocalMonth����Ч��ΧΪ1-12��
//    LocalDay:��               ��LocalDay  ����Ч��ΧΪ1-31��
// ���ز�����    
// Intervaldays: һ���еĵڼ���
//**********************************************************************
extern uint16 Mid_Rtc_AutoDay(uint8 LocalYear,uint8 LocalMonth,uint8 LocalDay);


extern void Mid_RTC_Test(void);

#endif          //  RTC_APP_H

