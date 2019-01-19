// gsensor
//#include "accelerometer.h"


// c
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "pah_comm.h"
#include "pah_driver_types.h"
#include "pah_driver.h"
#include "pah8series_config.h"

// platform support
#include "system_clock.h"
// motion algorithm
#if defined(ENABLE_PXI_ALG_HRD)
#include "pah8series_api_c.h"
#endif

#include "drv_hrm.h"
extern void (*BspHrmCalculateCompleteCb)(uint8 HrmValue );
extern void (*BspHrmCalculateErrCb)(void);		// ���ʲ�������ص�����

/*============================================================================
STATIC VARIABLES
============================================================================*/
static bool need_log_header = true;
static main_state_s _state = 
	{
		.pxialg_buffer = NULL,	// add by DrL ȷ����ʼ��ΪNULL�����ڷ����ڴ�
	};
static pah_flags_s flags;
preprocessing preproc={
    .trigger_event=0,
    .view_hr_event=0,
    .enable_timer=0,
};


static uint32_t Expo_time_backup[3]={0};
static uint8_t LEDDAC_backup[3]={0};
static float hr = 0.0f;


/*============================================================================
STATIC FUNCTION PROTOTYPES
============================================================================*/
#if defined(PPG_MODE_ONLY)|| defined(ALWAYS_TOUCH)
static void start_healthcare_ppg(void);
#endif
static void start_healthcare_ppg_touch(void);
static void start_healthcare_touch_only(void);
static void stop_healthcare(void);
static void log_pah8series_data_header(uint32_t ch_num, uint32_t ir_ch_num, uint32_t g_sensor_mode);
static void log_pah8series_data(const pah8series_data_t *data);
static void log_pah8series_no_touch(void);
#if defined(ENABLE_PXI_ALG_HRD) && defined(WEAR_INDEX_EN)
static void log_pah8series_wear_info(void);
#endif
static void pah8011_ae_info_check(pah8series_data_t *pxialg_data, bool Tuning);
static void report_fifo_data_hr(uint64_t timestamp, uint8_t *fifo_data, uint32_t fifo_data_num_per_ch, uint32_t ch_num, bool is_touched);
static bool hr_algorithm_process(pah8series_data_t *pxialg_data, uint32_t ch_num);
static bool hr_algorithm_calculate(pah8series_data_t *pxialg_data, uint32_t ch_num);
static void hr_algorithm_close(void);
#if defined(ENABLE_PXI_ALG_HRD)
static void algorithm_param_set(pah8series_param_idx_t param, float value);
#endif
static void Error_Handler(void);

void pah8series_ppg_dri_HRD_init(void)
{
	memset(&_state, 0, sizeof(_state));
	// PAH
    {
       pah_flags_default(&flags);
       flags.stream = pah_stream_dri;
       flags.alg_mode = pah_alg_mode_HR;
        if (!pah_init_with_flags(&flags))
        {
            debug_printf("pah_init_with_flags() fail. \n");
			drERROR_CHECK("pah8series_ppg_dri_HRD_init", Ret_Fail); 
			Error_Handler();
        }
    }
}

void pah8series_ppg_polling_HRD_init(void)
{
	memset(&_state, 0, sizeof(_state));
	// PAH
    {
        pah_flags_default(&flags);
        flags.stream = pah_stream_polling;
        flags.alg_mode = pah_alg_mode_HR;
        if (!pah_init_with_flags(&flags))
        {
            debug_printf("pah_init_with_flags() fail. \n");
			drERROR_CHECK("pah8series_ppg_polling_HRD_init", Ret_Fail); 
			Error_Handler();
        }
    }
}

void pah8series_touch_mode_start(void)
{
		need_log_header=true;
#if defined(Touch_Detect_Green_Led)	
	Set_Touch_Detect_TH( 1024 ,1024) ;  
	//  (  Touch_Th_Hi ,  Touch_Th_Lo ) //customer can set Touch_th by Using Condition
#endif	
    start_healthcare_touch_only();
    _state.status = main_status_start_healthcare;
}


void pah8series_ppg_HRD_start(void)
{
		need_log_header=true;
#if defined(Touch_Detect_Green_Led)	
    Set_Touch_Detect_TH( 1024 ,1024) ;  
	//(  Touch_Th_Hi ,  Touch_Th_Lo ) //customer can set Touch_th by Using Condition
#endif	
#if defined(PPG_MODE_ONLY)|| defined(ALWAYS_TOUCH)
    start_healthcare_ppg();
#else
    start_healthcare_touch_only();
#endif
    _state.status = main_status_start_healthcare;
}

void pah8series_ppg_HRD_stop(void)
{
// log
    log_pah8series_no_touch();
    _state.alg_status = alg_status_close ;
    _state.Tuning=0 ;
	stop_healthcare();
	_state.status = main_status_idle;
	
#ifdef demo_preprocessing_en	
	preproc.trigger_event=0;
	preproc.view_hr_event=0;
	preproc.enable_timer=0;
#endif
	
	hr_algorithm_close();
}


void 
pah8series_ppg_dri_HRD_task(
        volatile bool*      has_interrupt_pah,
        volatile bool*      has_interrupt_button,
        volatile uint64_t*  interrupt_pah_timestamp)
{
    pah_ret ret = pah_err_unknown;
	
    if (_state.status == main_status_start_healthcare)
    {
        if (*has_interrupt_pah)
        {
            *has_interrupt_pah = false;
    
            ret = pah_task();
            if (ret == pah_success)
            {        
                if (pah_is_ppg_mode() )
                {
                    uint8_t ppg_mode_flag =0 ;
                #if defined(PPG_MODE_ONLY)|| defined(ALWAYS_TOUCH)
                    ppg_mode_flag = 1 ;
                #endif 
                    bool is_touched = pah_is_touched();
                #ifdef ALWAYS_TOUCH
                    is_touched = 1 ;
                #endif
                    if(is_touched || ppg_mode_flag)
                    {
                        uint8_t *fifo_data = pah_get_fifo_data();
                        uint32_t fifo_data_num_per_ch = pah_fifo_data_num_per_ch();
                        uint32_t fifo_ch_num = pah_get_fifo_ch_num();
                        debug_printf("\n*interrupt_pah_timestamp == %d\n",*interrupt_pah_timestamp);                            
                        report_fifo_data_hr(*interrupt_pah_timestamp, fifo_data, fifo_data_num_per_ch, fifo_ch_num, is_touched);
                    }
                    else
                    {	
                        // log
                        log_pah8series_no_touch();
                        _state.alg_status = alg_status_close ;
                        _state.Tuning=0 ;
                        start_healthcare_touch_only();							
                    }
                }
                else if (pah_touch_mode == pah_query_mode())
                {
                    if (pah_is_touched())
                        start_healthcare_ppg_touch();
                }
            }
            else if (ret == pah_pending)
            {
            // ignore
            }
            else
            {
                debug_printf("pah_task fail, ret = %d \n", ret);
				drERROR_CHECK("pah8series_ppg_dri_HRD_task", Ret_Fail); 
				Error_Handler();
            }
        }
    #if 0 // unused
        if(*has_interrupt_button)
        {
            debug_printf("\npah8series_ppg_dri_HRD_task...9\n");
            *has_interrupt_button = false;    
            pah8series_ppg_HRD_stop();
        }
    #endif
    }
    else if (_state.status == main_status_idle)
    {
    #if 0 // unused    
        if (*has_interrupt_button)
        {
            *has_interrupt_button = false;
            pah8series_ppg_HRD_start();
        }
    #endif
    }
}


void 
pah8series_ppg_polling_HRD_task(
        volatile bool*      has_interrupt_pah,
        volatile bool*      has_interrupt_button )
{
	pah_ret ret = pah_err_unknown;
	// unused
        if (*has_interrupt_pah)
            *has_interrupt_pah = false;
        
        if (_state.status == main_status_start_healthcare)
        {
            ret = pah_task();
            if (ret == pah_success)
            {
                if (pah_is_ppg_mode())
                {
                    
                    uint8_t ppg_mode_flag =0 ;
                #if defined(PPG_MODE_ONLY)|| defined(ALWAYS_TOUCH)
                    ppg_mode_flag = 1 ;
                #endif
                    bool is_touched = pah_is_touched();
					#ifdef ALWAYS_TOUCH
						   is_touched = 1 ;
					#endif
                    if (is_touched || ppg_mode_flag)
                    {
                            uint32_t timestamp = get_tick_count();
                            uint8_t *fifo_data = pah_get_fifo_data();
                            uint32_t fifo_data_num_per_ch = pah_fifo_data_num_per_ch();
                            uint32_t fifo_ch_num = pah_get_fifo_ch_num();
                            //bool is_touched = pah_is_touched();
                            report_fifo_data_hr(timestamp, fifo_data, fifo_data_num_per_ch, fifo_ch_num, is_touched);
                    }
                
                    else
                    {
                            // log
                            log_pah8series_no_touch();
							_state.alg_status = alg_status_close ;
							_state.Tuning=0 ;
                            start_healthcare_touch_only();                   
                    }
                
                }
                else if (pah_touch_mode == pah_query_mode())
                {
                        if (pah_is_touched())
                                start_healthcare_ppg_touch();
                }
            }
            else if (ret == pah_pending)
            {
                // ignore
            }
            else
            {
                debug_printf("pah_task fail, ret = %d \n", ret);
				drERROR_CHECK("pah8series_ppg_polling_HRD_task", Ret_Fail); 
				Error_Handler();
            }
            #if 0 // unused
            if (*has_interrupt_button)
            {
                *has_interrupt_button = false;
                pah8series_ppg_HRD_stop();
            }
			      #endif 
        }
        else if (_state.status == main_status_idle)
        {
            #if 0 // unused
            if (*has_interrupt_button)
            {
                *has_interrupt_button = false;
                
                pah8series_ppg_HRD_start();
				
            }
			#endif
        }
}

void 
pah8series_touch_mode_dri_task(
        volatile bool*      has_interrupt_pah,
        volatile bool*      has_interrupt_button ,
        volatile uint64_t*  interrupt_pah_timestamp)
{
    pah_ret ret = pah_err_unknown;
    if (_state.status == main_status_start_healthcare)
    {
        if (*has_interrupt_pah)
        {
            *has_interrupt_pah = false;
    
            ret = pah_task();
            if (ret == pah_success)
            {
                bool touch_flag;
                pah_read_touch_flag(&touch_flag);
                if (touch_flag)
                {        
                    debug_printf("Touch \n");
                }else
                {        
                    debug_printf("No Touch \n");
                }
            }
            
        }
            
        if (*has_interrupt_button)
        {
            *has_interrupt_button = false;
                
                pah8series_ppg_HRD_stop();
            }
        }
        else if (_state.status == main_status_idle)
        {
            if (*has_interrupt_button)
            {
                *has_interrupt_button = false;
                
                start_healthcare_touch_only();
            }
        }
}

void 
pah8series_touch_mode_polling_task(
        bool*       has_interrupt_pah,
        bool*       has_interrupt_button)
{
	// unused
        if (*has_interrupt_pah)
                *has_interrupt_pah = false;
        
        if (_state.status == main_status_start_healthcare)
        {
            if (pah_touch_mode == pah_query_mode())
            {
                bool touch_flag;
                pah_read_touch_flag(&touch_flag);
                if (touch_flag)
                {        
                    debug_printf("Touch \n");
                }else
                {        
                    debug_printf("No Touch \n");
                }
            }
           
            
            if (*has_interrupt_button)
            {
                *has_interrupt_button = false;
        
                stop_healthcare();
                _state.status = main_status_idle;
            }
        }
        else if (_state.status == main_status_idle)
        {
            if (*has_interrupt_button)
            {
                *has_interrupt_button = false;
                
                //start_healthcare_ppg();
                start_healthcare_touch_only();
                _state.status = main_status_start_healthcare;
            }
        }
}

//void 
//pah8series_ppg_preproc_HRD_task(
//		volatile bool*		has_interrupt_pah,
//		volatile bool*		has_interrupt_button,
//		volatile uint64_t*	interrupt_pah_timestamp)
//{
//	pah_ret ret = pah_err_unknown;
//	
//	if(_state.status == main_status_start_healthcare){
//		if(!nrf_gpio_pin_read(15)){	
//			preproc.trigger_event=1;
//			preproc.enable_timer=0;
//			debug_printf("Button&Touch&ACC Event\n");
//		}
//		if(!nrf_gpio_pin_read(16)){
//			preproc.view_hr_event=1;
//			preproc.enable_timer=0;
//			debug_printf("View Heart Rate Value\n");
//		}
//		
//		if(preproc.trigger_event||preproc.view_hr_event){		
//	        if(*has_interrupt_pah){
//	            *has_interrupt_pah = false;

//	            ret = pah_task();
//	            if(ret == pah_success){
//	                
//	                if(pah_is_ppg_mode()){
//	                    uint8_t ppg_mode_flag =0 ;
//	                #if defined(PPG_MODE_ONLY)|| defined(ALWAYS_TOUCH)
//	                    ppg_mode_flag = 1 ;
//	                #endif 
//	                    bool is_touched = pah_is_touched();
//						#ifdef ALWAYS_TOUCH
//						   is_touched = 1 ;
//						#endif
//	                    if(is_touched || ppg_mode_flag){
//	                        uint8_t *fifo_data = pah_get_fifo_data();
//	                        uint32_t fifo_data_num_per_ch = pah_fifo_data_num_per_ch();
//	                        uint32_t fifo_ch_num = pah_get_fifo_ch_num();
//	                        
//	                        report_fifo_data_hr(*interrupt_pah_timestamp, fifo_data, fifo_data_num_per_ch, fifo_ch_num, is_touched);
//	                    }                    
//	                    else{
//							preproc.trigger_event=0;
//							//preproc.view_hr_event=0;
//	                        log_pah8series_no_touch();
//                            _state.alg_status = alg_status_close;
//                            _state.Tuning=0 ;
//	                        start_healthcare_touch_only();							
//	                    }
//	                }
//	                else if(pah_touch_mode == pah_query_mode()){
//	                    if(pah_is_touched())
//	                        start_healthcare_ppg_touch();
//	                }
//	            }
//	            else if(ret == pah_pending){
//	                // ignore
//	            }
//	            else{
//	                debug_printf("pah_task fail, ret = %d \n", ret);
//	                Error_Handler();
//	            }
//	        }
//		}
//		#if 0 // unused
//		if(*has_interrupt_button){
//            *has_interrupt_button = false; 
//            pah8series_ppg_HRD_stop();
//        }
//		#endif 
//		//Stop preproc condition
//		if(preproc.enable_timer==50){
//			preproc.trigger_event=0;
//			preproc.view_hr_event=0;
//			preproc.enable_timer=0;
//			// log
//			log_pah8series_no_touch();
//            _state.alg_status = alg_status_close ;
//            _state.Tuning=0 ;
//			start_healthcare_touch_only();
//			*has_interrupt_pah=true;
//		}
//    }
//    else if(_state.status == main_status_idle){
//		#if 0 // unused
//    	if (*has_interrupt_button){
//            *has_interrupt_button = false;
//            pah8series_ppg_HRD_start();
//        }
//		#endif 
//    }
//}

void hrd_alg_task(void)
{
    switch(_state.alg_status)
	{
	case alg_status_process:
        {
	        hr_algorithm_process(&_state.pxialg_data, _state.pxialg_data.nf_ppg_channel);
            _state.alg_status = alg_status_idle;
	    }
	    break;

	case alg_status_close:
        {
	        hr_algorithm_close();
            _state.alg_status = alg_status_idle;
	    }
	break;

	case alg_status_idle:
		{
		}
		break;
		
	default:
	    break;
    }
}


static void log_pah8series_data_header(uint32_t ch_num, uint32_t ir_ch_num, uint32_t g_sensor_mode)
{
    //log pah8series data header
    // (1)Using total channel numbers;
    // (2)reserved;
    // (3)reserved;
    // (4)IR channel number;
    // (5)MEMS mode 0:2G, 1:4G, 2:8G
    log_printf("PPG CH#, %d, %d, %d, %d, %d\n", ch_num, pah8011_setting_version(), 0, ir_ch_num, g_sensor_mode);
}

static void log_pah8series_data(const pah8series_data_t *pxialg_data)
{
    int i = 0;
    uint32_t *ppg_data = (uint32_t *)pxialg_data->ppg_data;
    int16_t *mems_data = pxialg_data->mems_data;
    int data_num = pxialg_data->nf_ppg_channel * pxialg_data->nf_ppg_per_channel;
    
    log_printf("Frame Count, %d \n", pxialg_data->frame_count);
    log_printf("Time, %d \n", pxialg_data->time);
    log_printf("PPG, %d, %d, ", pxialg_data->touch_flag, data_num);
    for (i = 0; i < data_num; ++i)
    {
        log_printf("%d, ", *ppg_data);
        ppg_data++;
    }
    log_printf("\n");	
    log_printf("MEMS, %d, ", pxialg_data->nf_mems);
    for (i = 0; i < pxialg_data->nf_mems * 3; ++i)
    {
        log_printf("%d, ", *mems_data);
        mems_data++;
    }
    log_printf("\n");
#if defined(ENABLE_PXI_ALG_HRD)	&& defined(WEAR_INDEX_EN)
    if((pxialg_data->touch_flag==0x11 && ((int)hr)))        
        _state.wIndex_data.Wear_Num++;
    if((int)hr)
        _state.wIndex_data.Wear_FC_total++;
#endif	
}

static void log_pah8series_no_touch(void)
{
    static const int DUMMY_PPG_DATA_NUM = 20;
    static const int DUMMY_PPG_CH_NUM = 2;
    int i = 0;
    
    log_printf("Frame Count, 0 \n");
    log_printf("Time, %d \n", DUMMY_PPG_DATA_NUM * 50); // 20Hz = 50ms
    log_printf("PPG, 0, %d, ", DUMMY_PPG_DATA_NUM * DUMMY_PPG_CH_NUM);
    for (i = 0; i < DUMMY_PPG_DATA_NUM * DUMMY_PPG_CH_NUM; i++)
    {
        log_printf("0, ");
    }
    log_printf("\n");
    log_printf("MEMS, %d, ", DUMMY_PPG_DATA_NUM);
    for (i = 0; i < DUMMY_PPG_DATA_NUM * 3; ++i)
    {
        log_printf("0, ");
    }
    log_printf("\n\n");

#if defined(ENABLE_PXI_ALG_HRD) && defined(WEAR_INDEX_EN)
	if(_state.wIndex_data.Wear_FC_total)
	log_pah8series_wear_info();
	_state.wIndex_data.Wear_Num=_state.wIndex_data.Wear_FC_total=0;	
#endif
}

#if defined(ENABLE_PXI_ALG_HRD) && defined(WEAR_INDEX_EN)
static void log_pah8series_wear_info(void){
    float wear_ratio;
    wear_ratio=((float)_state.wIndex_data.Wear_Num/(float)(_state.wIndex_data.Wear_FC_total+1)*100);
		log_printf("Total frame count %d after Heart Rate release, Wear index trigger num %d. Trigger percentage "LOG_FLOAT_MARKER"\n" \
    , _state.wIndex_data.Wear_FC_total+1, _state.wIndex_data.Wear_Num, LOG_FLOAT(wear_ratio));
}
#endif

static void report_fifo_data_hr(uint64_t timestamp, uint8_t *fifo_data, uint32_t fifo_data_num_per_ch, uint32_t ch_num, bool is_touched)
{
    //enable_timer++;
    // gsensor
#if defined(ENABLE_MEMS_ZERO)
    _state.pxialg_data.mems_data = _state.mems_data;
    _state.pxialg_data.nf_mems = fifo_data_num_per_ch;
#else
    accelerometer_get_fifo(&_state.pxialg_data.mems_data, &_state.pxialg_data.nf_mems);
#endif  // ENABLE_MEMS_ZERO
        
    _state.pxialg_data.touch_flag = is_touched ? 1 : 0;
    _state.pxialg_data.time = (uint32_t)(timestamp - _state.last_report_time);
    _state.pxialg_data.ppg_data = (int32_t*)fifo_data;
    _state.pxialg_data.nf_ppg_channel = ch_num;
    _state.pxialg_data.nf_ppg_per_channel = fifo_data_num_per_ch;
    ++_state.pxialg_data.frame_count;
    
    _state.last_report_time = timestamp;
#ifdef Timing_Tuning
    if(_state.Tuning)
    {
        pah_do_timing_tuning(_state.pxialg_data.time, _state.pxialg_data.nf_ppg_per_channel,50.0f);
    }
	_state.Tuning=1;
#endif
    debug_printf("\n_state.pxialg_data.time == %d\n", _state.pxialg_data.time);

	pah8011_ae_info_read(_state.Expo_time, _state.LEDDAC, &_state.Touch_data);
	_state.alg_status = alg_status_process ;	
}

//uint8 hrmbuf[15000];//max lenght may up to 13KB
static bool hr_algorithm_calculate(pah8series_data_t *pxialg_data, uint32_t ch_num)
{
    bool has_updated = false;
    
#if defined(ENABLE_PXI_ALG_HRD)
    uint8_t ret = 0;
    
    // Algorithm support only data length >= 10
    if (pxialg_data->nf_ppg_per_channel < 10)
    {
        debug_printf("hr_algorithm_calculate(). fifo_data_num_per_ch = %d, is not enough to run algorithm \n", pxialg_data->nf_ppg_per_channel);
        return false;
    }

  #ifdef WEAR_INDEX_EN		
    if(pxialg_data->touch_flag==0x11){
        if(!(int)hr){
			  pah8series_reset();
			  return false;
		    }
	  }
  #endif
    
    // Initialize algorithm
    if (!_state.pxialg_has_init)
    {
        uint32_t pxialg_open_size = 0;
		
        pxialg_open_size = pah8series_query_open_size();
        debug_printf("pah8series_query_open_size() = %d \n", pxialg_open_size);
		
        _state.pxialg_buffer = gHrdCalBuf;	//malloc(pxialg_open_size);
		
        ret = pah8series_open(_state.pxialg_buffer);
        if (ret != MSG_SUCCESS)
        {
            debug_printf("pah8series_open() failed, ret = %d \n", ret);
            return false;
        }

        log_printf("pah8series_version = %d \n", pah8series_version());

		algorithm_param_set(PAH8SERIES_PARAM_IDX_GSENSOR_MODE, (float)ALG_GSENSOR_MODE);
        algorithm_param_set(PAH8SERIES_PARAM_IDX_PPG_CH_NUM, (float)ch_num);
        algorithm_param_set(PAH8SERIES_PARAM_IDX_HAS_IR_CH, (float)PPG_IR_CH_NUM);

        _state.pxialg_has_init = true;
    }
    
    // Calculate Heart Rate
    ret = pah8series_entrance(pxialg_data);
    if (ret == MSG_HR_READY)
    {
  #ifdef demo_preprocessing_en    
        if(preproc.view_hr_event)
        {
  #endif		
        int hr_trust_level = 0;
        int16_t grade = 0;    
        pah8series_get_hr(&hr);
        pah8series_get_hr_trust_level(&hr_trust_level);
        pah8series_get_signal_grade(&grade);
		
		BspHrmCalculateCompleteCb((uint8_t)hr);	//���ʼ����������Ч�ص�
        
        log_printf("hr = %d, hr_trust_level = %d, grade = %d \n", (int)hr, hr_trust_level, grade);
  #ifdef demo_preprocessing_en    
        }
  #endif        
        has_updated = true;
    }
    else
    {
        switch (ret)
        {
            case MSG_SUCCESS:
                debug_printf("Algorithm entrance success. \n");
                break;
            case MSG_ALG_NOT_OPEN:
                debug_printf("Algorithm is not initialized. \n");
                break;
            case MSG_MEMS_LEN_TOO_SHORT:
                debug_printf("MEMS data length is shorter than PPG data length. \n");
                break;
            case MSG_NO_TOUCH:
                debug_printf("PPG is no touch. \n");
                break;
            case MSG_PPG_LEN_TOO_SHORT:
                debug_printf("PPG data length is too short. \n");
                break;
            case MSG_FRAME_LOSS:
                debug_printf("Frame count is not continuous. \n");
                break;
            default:
                debug_printf("Algorithm unhandle error = %d \n", ret);
                break;
        }
    }       
#endif // ENABLE_PXI_ALG_HRD
    return has_updated;
}

static void hr_algorithm_close(void)
{
    hr = 0.0f;
#if defined(ENABLE_PXI_ALG_HRD)
    if (_state.pxialg_has_init)
    {
        _state.pxialg_has_init = false;
        
        pah8series_close();
    }
#endif // ENABLE_PXI_ALG_HRD
}


#if defined(PPG_MODE_ONLY)|| defined(ALWAYS_TOUCH)
static void start_healthcare_ppg(void)
{
    // gsensor
    #ifndef ENABLE_MEMS_ZERO  
    accelerometer_start();
    #endif  
    // PAH
    if (!pah_enter_mode(pah_ppg_mode))
        Error_Handler();
    _state.last_report_time = get_tick_count();
}
#endif

static void start_healthcare_ppg_touch()
{
    // gsensor
#ifndef ENABLE_MEMS_ZERO 
    accelerometer_start();
#endif 
    // PAH
    if (!pah_enter_mode(pah_ppg_touch_mode))
    {
		drERROR_CHECK("start_healthcare_ppg_touch", Ret_Fail); 
		Error_Handler();
	}
    
    _state.last_report_time = get_tick_count();
}

static void start_healthcare_touch_only(void)
{
    // gsensor
#ifndef ENABLE_MEMS_ZERO 
    accelerometer_stop();
#endif 
    
    // PAH
    if (!pah_enter_mode(pah_touch_mode))
    {
		drERROR_CHECK("start_healthcare_touch_only", Ret_Fail); 
		Error_Handler();
	}
}

static void stop_healthcare(void)
{
    // gsensor
#ifndef ENABLE_MEMS_ZERO 
    accelerometer_stop();
#endif     
    // PAH
    if (!pah_enter_mode(pah_stop_mode))
	{
		drERROR_CHECK("stop_healthcare", Ret_Fail); 
		Error_Handler();
	}
        
}





static void pah8011_ae_info_check(pah8series_data_t *pxialg_data, bool Tuning)
{
    uint8_t i;
    uint32_t MIN=0;
    float VAR_MAX=0;
    float AE_VAR=0;
	uint8_t wear_enable_log=0;
    uint32_t *Expo_time  = _state.Expo_time;
    uint8_t  *LEDDAC     = _state.LEDDAC;
//    uint16_t Touch_data  = _state.Touch_data;


	int wear_index=0;
#if defined(ENABLE_PXI_ALG_HRD)	
	pah8series_get_wear_index(Expo_time, LEDDAC, 0, &wear_index);
#ifdef WEAR_INDEX_EN
	wear_enable_log=1;
	if((wear_index)&(pxialg_data->touch_flag))
		pxialg_data->touch_flag = 0x11;
#endif   	
#endif // ENABLE_PXI_ALG_HRD
    for( i = 0 ; i < 3 ; i++)
    {
        if(Expo_time_backup[i]>0)
        {
            MIN = (Expo_time_backup[i] >= Expo_time[i]) ? Expo_time[i] : Expo_time_backup[i];  
            AE_VAR = ((float)Expo_time_backup[i] - (float)Expo_time[i]);
            AE_VAR = ((AE_VAR >= 0.0f) ? AE_VAR : AE_VAR*(-1))/(float)MIN;
            VAR_MAX = (AE_VAR >= VAR_MAX) ? AE_VAR : VAR_MAX;					
        }
        Expo_time_backup[i] = Expo_time[i];	
    }
    for( i = 0 ; i < 3 ; i++)
    {
        if(LEDDAC_backup[i]>0)
        {
            MIN = (LEDDAC_backup[i] >= LEDDAC[i]) ? LEDDAC[i] : LEDDAC_backup[i];
            AE_VAR = ((float)LEDDAC_backup[i] - (float)LEDDAC[i]);
            AE_VAR = ((AE_VAR >= 0.0f) ? AE_VAR : AE_VAR*(-1))/(float)MIN;
            VAR_MAX = (AE_VAR >= VAR_MAX) ? AE_VAR : VAR_MAX;
        }
        LEDDAC_backup[i] = LEDDAC[i];
    }
    log_printf("INFO, %d, %d, %d, %d, %d, %d, ", Expo_time[0],Expo_time[1],Expo_time[2],LEDDAC[0],LEDDAC[1],LEDDAC[2]);
    log_printf("VAR " LOG_FLOAT_MARKER", Wear %d level %d, Tuning %d, T_Data %d, \n", LOG_FLOAT(VAR_MAX),wear_enable_log,wear_index,Tuning,Touch_data);
}



static bool hr_algorithm_process(pah8series_data_t *pxialg_data, uint32_t ch_num)
{
    // log header
    if (need_log_header)
    {
        need_log_header = false;
        log_pah8series_data_header(ch_num, PPG_IR_CH_NUM, ALG_GSENSOR_MODE);
    }
    pah8011_ae_info_check(&_state.pxialg_data, _state.Tuning);
    // log
    log_pah8series_data(&_state.pxialg_data);  
    // hr
    hr_algorithm_calculate(&_state.pxialg_data, ch_num);
    return true;
}


#if defined(ENABLE_PXI_ALG_HRD)
static void algorithm_param_set(pah8series_param_idx_t param, float value)
{
    pah8series_set_param(param, value);
    log_printf("Param[%02d] = "LOG_FLOAT_MARKER" \n", param, LOG_FLOAT(value));
}
#endif


static void Error_Handler(void)
{
    log_printf("GOT ERROR !!! \n");
	RTT_DEBUG_printf(0,"GOT ERROR !!! \n");	// By DrL
	if(NULL != BspHrmCalculateErrCb)
	{
		BspHrmCalculateErrCb();
	}
}

