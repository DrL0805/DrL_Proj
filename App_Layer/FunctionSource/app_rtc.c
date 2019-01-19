#include "platform_common.h"

#include "mid_interface.h"
#include "app_variable.h"
#include "app_protocal.h"
#include "app_packdata_manage.h"
#include "app_scenedata_manage.h"
#include "app_rtc.h"
#include "app_task.h"
//#include "app_win_common.h"
//#include "app_win_process.h"
#include "app_action_recongnition.h"


#define  LongSitTimeInterval            30    //��������ʱ�䣺��λ��min 
#define  COUTER_5MIN_TIME               300   //�Ʋ���˯�߷ְ����ݴ洢ʱ��������λ����
#define  COUTER_1MIN_TIME               60   //���ʷְ����ݴ洢ʱ��������λ����
#define  BAT_CHECK_TIME                 10   //��ص������ʱ��������λ����
#define  HRM_LOG_CHECK_TIME             2   //���ʼ��ʱ��������λ��min

#define  SCENE_PROCESS_TIME             1  //��������ʱ�䣺��     ��λ����
#define  SCENE_DATA_STORE_TIME          10  //�������ݴ洢ʱ�䣺����λ����

#define  WEATHER_REQ_TIME               1   //������У��·�������Ϣ��ʱ��������λ��min

#define  STEP_STATE_CHANGE_MOTION_VAL   30  //�Ʋ�״̬�л�������ֵ
#define  STEP_STATE_3_SEC_TIME          6  
#define  STEP_STATE_30_SEC_TIME         60  
#define  STEP_STATE_60_SEC_TIME         120 

#define  RTC_ONEHOUR                    60

static uint32 appRtcSecCnt  = 0;
static uint16 appStepSecCnt = 0;
static uint32 appMinCnt     = 0;  //��¼����,����1Сʱ��ʱ����

//**********************************************************************
// �������ܣ�    ���붨ʱ����:�ж϶������ȣ����Ʋ������мƲ��������رմ������Ĺ���
// ���������    ��
// ���ز�����    ��
//**********************************************************************
void App_RtcHalfSec_Process(void)
{
	#if 0
    uint16 motionValTemp;
    multimodule_task_msg_t  msg;

   if (gtSysCfg.stepCountSwitch == SWITCH_ON)
    {
        switch(stepState)
        {   
            //�Ʋ��ر�״̬�£�ÿ�����鶯��ֵ
            case STEP_IDLE_STATE:
            motionValTemp = Mid_UsualScene_ReadMotion();
            if (motionValTemp > STEP_STATE_CHANGE_MOTION_VAL)
            {
                appStepSecCnt = 0;
                
                Mid_SportScene_SecStepClear();
                //�˶�����
                msg.id                       = SPORT_ID;
                msg.module.sportEvent.id     = SPORT_STEP_START;
                MultiModuleTask_EventSet(msg);

                //���ƿ���
                msg.id                        = GESTURE_ID;
                msg.module.gestureEvent.id    = GESTURE_SCENCE_OPEN;
                MultiModuleTask_EventSet(msg);  

                stepState = STEP_PREPAIRE_STATE;
            }
            break;
            //�Ʋ�׼��״̬�£���ʱ30�룬����Ƿ��мƲ�����,�л����Ʋ������״̬
            case STEP_PREPAIRE_STATE:
            appStepSecCnt ++;
            if (appStepSecCnt >= STEP_STATE_30_SEC_TIME)
            {
                 appStepSecCnt = 0;
                if(Mid_SportScene_SecStepRead())
                {
                    stepState = STEP_PROCESS_STATE;
                    Mid_SportScene_SecStepClear();
                }
                else
                {
                    stepState = STEP_IDLE_STATE;
                    //�˶��ر�
                    msg.id                       = SPORT_ID;
                    msg.module.sportEvent.id     = SPORT_STEP_STOP;
                    MultiModuleTask_EventSet(msg);

                    //���ƹر�
                    msg.id                        = GESTURE_ID;
                    msg.module.gestureEvent.id    = GESTURE_SCENCE_CLOSE;
                    MultiModuleTask_EventSet(msg);  
                }
            }
            break;
            //�Ʋ�״̬�£�30�����Ƿ�����Ʋ����л����Ʋ�׼���򱣳ּƲ�״̬
            case STEP_PROCESS_STATE:
            appStepSecCnt ++;
            if (appStepSecCnt >= STEP_STATE_30_SEC_TIME) //ÿ�����ж�һ���Ƿ�����Ʋ�
            {
                appStepSecCnt = 0;

                if (Mid_SportScene_SecStepRead())
                {
                    Mid_SportScene_SecStepClear();
                     stepState = STEP_PROCESS_STATE;
                }
                else
                {
                    stepState = STEP_PREPAIRE_STATE;
                }
            }
            break;

            default:
            break;
        }
    }
   
   if(appStepSecCnt == 0xFFFFFFFF)
       appStepSecCnt = 0x00;
	   
	#endif
}

//**********************************************************************
// �������ܣ�    1�붨ʱ����
// ���������    ��
// ���ز�����    ��
//**********************************************************************
void App_RtcSec_Process(void)
{
	#if 0
    menuMessage        message;
    uint16_t          staystillTimeTemp;
    uint32_t          curUtcTimeTemp;
    uint16            stepTemp;  
    scene_data_s       sceneDataTemp;
    multimodule_task_msg_t  msg;

    appRtcSecCnt++;
    backstageTimeCounterSec++ ;

    //ÿ��������
    if (movtState.state == MOVT_STATE_NORMAL)
    {
        App_Rtc_Movt();
    }else if (movtState.state == MOVT_STATE_ADJUST)
    {
        movtState.timeCnt ++;
        //У�볬ʱ����
        if (movtState.timeCnt > movtState.timeMax)
        {
            App_Rtc_MovtRecover();
            App_Rtc_Movt();
            movtState.timeCnt = 0;
            movtState.state = MOVT_STATE_NORMAL;
        }      
    }
    else
        ;

    //ʱ��ˢ��,1s
    if(App_Win_Attr_IsShowTime(WinDowHandle) == TRUE)
    {
        message.op   = RTC_SEC;
        WinDowHandle = App_Window_Process(WinDowHandle,TAG_TIME,message);
    }  

    //��ִ�о����¼�(��̨�����ճ�����) 
    staystillTimeTemp = Mid_UsualScene_StandstillTimeRead();//����ʱ���ȡ
    staystillTimeTemp = staystillTimeTemp; //for comnpile
   
    //��̨����
    //ÿ�����˶�ʱ��
    if (gtSysCfg.stepCountSwitch == SWITCH_ON)
    {
        msg.id                       = SPORT_ID;
        msg.module.sportEvent.id     = SPORT_STEP_DUARATION_PROCESS;
        MultiModuleTask_EventSet(msg); 
    }

    //ÿ����´洢��̨������ʣ��˲�����
    if (gtSysCfg.heartrateSwitch == SWITCH_ON)
    {
        msg.id                        = HEARTRATE_LOG_ID;
        msg.module.hrmLogEvent.id     = HRM_LOG_STORAGE_PROCESS;
        MultiModuleTask_EventSet(msg);
    }

    //�˶���������ÿSCENE_PROCESS_TIME�봦��һ��
    if (sceneSwitch != SCENE_NULL && (appRtcSecCnt % SCENE_PROCESS_TIME == 0))
    {
		curUtcTimeTemp  = Mid_Rtc_ReadCurUtc();
        switch(sceneSwitch)
        {
        case SCENE_RUNNING:
            if(appRtcSecCnt % SCENE_DATA_STORE_TIME == 0)
            {
                //�洢��һ�ε�����
                Mid_Scene_LogDataRead(RUN_SCENE_TYPE, &sceneDataTemp);
                App_SceneData_SaveDynamic(curUtcTimeTemp, RUN_SCENE_DATA_CLASSIFY, &sceneDataTemp);
                //����һ����ͳ��
            }
            msg.id                       = SCENE_ID;
            msg.module.sceneEvent.id     = RUN_SCENE_PROCESS;
            MultiModuleTask_EventSet(msg); 
            break;

#if (AIR_PRESSURE_SUPPORT == 1)			
        case SCENE_CLIMB:
            if(appRtcSecCnt % SCENE_DATA_STORE_TIME == 0)
            {
                //�洢��һ�ε�����
                Mid_Scene_LogDataRead(CLIMB_SCENE_TYPE, &sceneDataTemp);
                App_SceneData_SaveDynamic(curUtcTimeTemp, CLIMB_SCENE_DATA_CLASSIFY, &sceneDataTemp);
                //����һ����ͳ��
            }
           
            msg.id                       = SCENE_ID;
            msg.module.sceneEvent.id     = CLIMB_SCENE_PROCESS;
            MultiModuleTask_EventSet(msg); 
            break;

        case SCENE_SWING:
            if(appRtcSecCnt % SCENE_DATA_STORE_TIME == 0)
            {
                //�洢��һ�ε�����
                Mid_Scene_LogDataRead(SWING_SCENE_TYPE, &sceneDataTemp);
                App_SceneData_SaveDynamic(curUtcTimeTemp, SWING_SCENE_DATA_CLASSIFY, &sceneDataTemp);
                //����һ����ͳ��
            }

            msg.id                       = SCENE_ID;
            msg.module.sceneEvent.id     = SWING_SCENE_PROCESS;
            MultiModuleTask_EventSet(msg); 
            break;
#endif
        default:
            break;
        }
    }

    //ÿ5���Ӵ洢�Ʋ���˯�߷ְ�����
    if (backstageTimeCounterSec % COUTER_5MIN_TIME == 0 && gtSysCfg.stepCountSwitch == SWITCH_ON)
    {
        curUtcTimeTemp  = Mid_Rtc_ReadCurUtc();
        stepTemp        = Mid_SportScene_5minStepRead();
        App_PackData_Step5MinSave(curUtcTimeTemp - 300, stepTemp);

        #ifndef SLEEP_PACK_DUMMY
        App_PackData_Sleep5MinSave(curUtcTimeTemp - 300, stepTemp, Mid_UsualScene_SleepMotionRead());
        #endif
        //�洢�����
        Mid_SportScene_5minStepClear();
        Mid_UsualScene_SleepMotionClear();
    }

    //�����ֻ�ǿ����״̬
    if (gtPhoneState.state != PHONE_STATE_NORMAL)
    {
        gtPhoneState.timeCnt ++; //״̬ά�ּ�ʱ
        //״̬��ʱ���˳�����
        if (gtPhoneState.timeCnt > gtPhoneState.timeMax)
        {
             switch(gtPhoneState.state)
            {
                case PHONE_STATE_PHOTO:
                message.state   = EXIT_TAKE_PHOTO_MODE;
                message.op      = TAKE_PHOTO_REMIND;
                WinDowHandle    = App_Window_Process(WinDowHandle,TAG_REMIND,message);
                break;

                case PHONE_STATE_AUTHOR:

                break;

                case PHONE_STATE_PAIRE:
                // message.state = EXIT_PAIRE_STATE;
                // message.op    = PAIRE_REMIND;
                // WinDowHandle  = App_Window_Process(WinDowHandle,TAG_REMIND,message);
                break;

                case PHONE_STATE_HRM:
                //�ر�ʵʱ���ʳ������������ر���Ҫ�ɶԳ��֣�
                msg.id                                  = HEARTRATE_ID;     
                msg.module.hrmEvent.id                  = HRM_STOP;
                MultiModuleTask_EventSet(msg); 
                break;
            }
            gtPhoneState.state    = PHONE_STATE_NORMAL,
            gtPhoneState.timeCnt  = 0;
        } 
    }
	
    //fix:app���������Ӳ�ͬ����ʱ����Ҫ���������㲥,��OTA���ճ�ʱ���
    App_Protocal_Monitor();
    //fix: 2018.6.6

    //����Խ�磬��λ
    if(backstageTimeCounterSec == 0xFFFFFFFF)
        backstageTimeCounterSec = 0x00;
    if(appRtcSecCnt == 0xFFFFFFFF)
        appRtcSecCnt = 0x00;
	#endif
}

//**********************************************************************
// �������ܣ�    1Сʱ��ʱ����
// ���������    ��
// ���ز�����    ��
//**********************************************************************
static void App_RtcHour_Process(void)
{
	#if 0
    //������app��ȡ������Ϣ
    if(geBleState == BLE_CONNECT)
    {
       App_Protocal_GetWeatherProcess();
    }

    //ÿСʱ����һ��˯�߽��
    App_SleepData_Save();
	#endif
}

//**********************************************************************
// �������ܣ�    1�ֶ�ʱ����
// ���������    ��
// ���ز�����    ��
//**********************************************************************
void App_RtcMin_Process(void)
{
}

//**********************************************************************
// �������ܣ�    1�춨ʱ����
// ���������    ��
// ���ز�����    ��
//**********************************************************************
void App_RtcDay_Process(void)
{ 
	#if 0
    app_task_msg_t  appMsg;
    
    //ÿ������˶�����
     Mid_SportScene_ClearInfo();

    if (geBleState == BLE_CONNECT)
    {
        App_Protocal_AdjustTimeprocess();
    }

    //ÿ24Сʱ���һ�μƲ��ְ�Ŀ¼
    if(gtSysCfg.stepCountSwitch == SWITCH_ON)
    {
        App_PackData_StepSaveCache();
        App_PackData_SleepSaveCache();       
    }

    //ÿ24Сʱ���һ�����ʷְ�����Ŀ¼
    if (gtSysCfg.heartrateSwitch == SWITCH_ON)
    {
        App_PackData_HrmSaveCache();
        Mid_HeartRateScene_Clear();
    }

    //���ñ����¼�                                        
    appMsg.id   = APP_CACEH_DATA_SAVE;
    appMsg.para = CACHE_SPORT_TYPE;
    App_Task_EventSet(appMsg);
	#endif
}

//**********************************************************************
// �������ܣ�    ת��ʱ�����
// ���������    ʱ���֡���
// ���ز�����    ����
//**********************************************************************
uint16 App_Rtc_ExchangeTimeforCount(uint8 Hour, uint8 Min, uint8 Sec)
{
    uint16 z;
    uint8 i;
    i = Hour;
    if(Hour > 11)
    {
        i = Hour - 12;
    }
    z = (uint16)i *3600;
    z += (uint16)Min *60;
    z += Sec ;
    
    return z;
}

/********************************************************

                 H001ϵ��û������(����)

����һ����һ�ȣ�һСʱ(3600��)Ҫ��360�ȣ�Ҳ����10����һ��

********************************************************/
void App_Rtc_Movt(void)
{
}

//**********************************************************************
// �������ܣ�    ����ָ�
// ���������    ��
// ���ز�����    ��
//**********************************************************************
void App_Rtc_MovtRecover(void)
{
	#if 0
    movt_task_msg_t  movtMsg;

    movtMsg.id  = MOVT_MSG_MC_RECOVER;
    MovtTask_EventSet(movtMsg);
	#endif
}

//**********************************************************************
// �������ܣ�    ����ʱ����
// ���������    ��
// ���ز�����    ��
//**********************************************************************
uint16_t App_NotDisturdTimeCheck(void)
{
    uint32_t i,j,n;

    //current rtc
    n = gtRTC.hour*3600 + gtRTC.min*60;
    
    i = appNotDisturdTimeInfo.StartHour*3600 + appNotDisturdTimeInfo.StartMin*60;
    j = appNotDisturdTimeInfo.StopHour *3600 + appNotDisturdTimeInfo.StopMin *60;
    
    if(TimePeriodJudge(i,j,n))
    return 0xff;
    
    return 0;
}

//**********************************************************************
// �������ܣ�    ����ʱ����
// ���������    rtcʱ��
// ���ز�����    ��
//**********************************************************************
uint16_t App_LongSitTimeCheck(rtc_time_s *timeTemp)
{
	#if 0
    uint32_t i,j,k,m,n;
    
    //��ǰrtc
    n = timeTemp->hour*3600 + timeTemp->min*60;
    //����������Чʱ���
    i = appLongSitInfo.StartTimeHour*3600 + appLongSitInfo.StartTimeMin*60;
    j = appLongSitInfo.StopTimeHour *3600 + appLongSitInfo.StopTimeMin*60;
    //������������ʱ���
    k = appLongSitInfo.DisturdStartTimehour*3600 + appLongSitInfo.DisturdStartTimeMin*60;
    m = appLongSitInfo.DisturdStopTimehour *3600 + appLongSitInfo.DisturdStopTimeMin*60;
    if(TimePeriodJudge(i,j,n)) //����Чʱ����
    {
        if(TimePeriodJudge(k,m,n))//������ʱ���
        {
            return 0;
        }
        else
        return 0xff;
    }
    return 0;
	#endif
}

//**********************************************************************
// �������ܣ�    ���������жϴ���
// ���������    rtcʱ��
// ���ز�����    ��
//**********************************************************************
void App_LongSitRemindProcesss(rtc_time_s *timeTemp)
{
	#if 0
    uint16_t     LongSitTime;
    uint32_t     LongSitMotion;
    menuMessage  message;
   
    //long sit
    LongSitTime   = Mid_UsualScene_SedentaryTimeRead();
    LongSitMotion = Mid_UsualScene_SedentaryMotionRead();          
    if(LongSitTime >= appLongSitInfo.intv_mimute)                //����ʱ��������õ�ʱ����
    {
        if((LongSitMotion / appLongSitInfo.intv_mimute / 60) > 2)//�����������Լ��ʱ�����2
        {
            if(App_LongSitTimeCheck(timeTemp))      //�Ƿ��ھ���������ʱ���
            {
                message.op   = LONG_SIT_REMIND;
                WinDowHandle = App_Window_Process(WinDowHandle,TAG_REMIND,message);
            }
        }
        Mid_UsualScene_SedentaryClear();
    } 
	#endif
}
                        
//**********************************************************************
// �������ܣ�    �������ּ�⣬ÿ���Ӽ��һ��
// ���������    rtcʱ��
// ���ز�����    ��
//**********************************************************************
void App_AlarmProcess(rtc_time_s *timeTemp)
{
	#if 0
    menuMessage         message;

    if(Mid_AlarmClock_Check(timeTemp))
    { 
        //���ղ�����������
        if (gtPhoneState.state != PHONE_STATE_PHOTO)
        {
             message.op   = ALARM_REMIND;
            WinDowHandle = App_Window_Process(WinDowHandle,TAG_REMIND,message);
        }
    }
	#endif
}


