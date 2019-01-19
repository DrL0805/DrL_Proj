#include "ui_screen_runingmode.h"
#include "ui_screen_dateandtime.h"


const uint8_t _ic_start_24_h[] = {
24,24,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 1 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 2 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 3 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 4 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 5 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 6 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 7 */
0x00, 0x00, 0x00, 0x00, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 8 */
0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 9 */
0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 10 */
0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, /* scanline 11 */
0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x77, 0x77, 0x70, 0x00, 0x00, 0x00, /* scanline 12 */
0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x77, 0x77, 0x70, 0x00, 0x00, 0x00, /* scanline 13 */
0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, /* scanline 14 */
0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 15 */
0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 16 */
0x00, 0x00, 0x00, 0x00, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 17 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 18 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 19 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 20 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 21 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 22 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 23 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 24 */
};


const uint8_t _ic_hr_24_h[] = {
24,24,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 1 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 2 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 3 */
0x00, 0x00, 0x07, 0x77, 0x00, 0x00, 0x00, 0x00, 0x77, 0x70, 0x00, 0x00, /* scanline 4 */
0x00, 0x07, 0x77, 0x77, 0x77, 0x00, 0x00, 0x77, 0x77, 0x77, 0x70, 0x00, /* scanline 5 */
0x00, 0x77, 0x77, 0x77, 0x77, 0x70, 0x07, 0x77, 0x77, 0x77, 0x77, 0x00, /* scanline 6 */
0x00, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x00, /* scanline 7 */
0x07, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x70, /* scanline 8 */
0x07, 0x77, 0x77, 0x77, 0x77, 0x00, 0x77, 0x77, 0x77, 0x77, 0x77, 0x70, /* scanline 9 */
0x07, 0x77, 0x77, 0x77, 0x77, 0x00, 0x77, 0x00, 0x77, 0x77, 0x77, 0x70, /* scanline 10 */
0x00, 0x77, 0x77, 0x00, 0x77, 0x00, 0x77, 0x00, 0x77, 0x77, 0x77, 0x00, /* scanline 11 */
0x00, 0x77, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x77, 0x00, /* scanline 12 */
0x00, 0x07, 0x77, 0x77, 0x00, 0x77, 0x00, 0x77, 0x00, 0x77, 0x70, 0x00, /* scanline 13 */
0x00, 0x00, 0x77, 0x77, 0x00, 0x77, 0x00, 0x77, 0x77, 0x77, 0x00, 0x00, /* scanline 14 */
0x00, 0x00, 0x07, 0x77, 0x77, 0x77, 0x00, 0x77, 0x77, 0x70, 0x00, 0x00, /* scanline 15 */
0x00, 0x00, 0x00, 0x77, 0x77, 0x77, 0x00, 0x77, 0x77, 0x00, 0x00, 0x00, /* scanline 16 */
0x00, 0x00, 0x00, 0x07, 0x77, 0x77, 0x00, 0x77, 0x70, 0x00, 0x00, 0x00, /* scanline 17 */
0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x00, 0x77, 0x00, 0x00, 0x00, 0x00, /* scanline 18 */
0x00, 0x00, 0x00, 0x00, 0x07, 0x77, 0x77, 0x70, 0x00, 0x00, 0x00, 0x00, /* scanline 19 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 20 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 21 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 22 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 23 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 24 */
};

const uint8_t _ic_gps_24_h[] = {
24,24,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 1 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 2 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 3 */
0x00, 0x00, 0x00, 0x00, 0x07, 0x77, 0x77, 0x70, 0x00, 0x00, 0x00, 0x00, /* scanline 4 */
0x00, 0x00, 0x00, 0x07, 0x77, 0x77, 0x77, 0x77, 0x70, 0x00, 0x00, 0x00, /* scanline 5 */
0x00, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x00, /* scanline 6 */
0x00, 0x00, 0x07, 0x77, 0x00, 0x00, 0x00, 0x00, 0x77, 0x70, 0x00, 0x00, /* scanline 7 */
0x00, 0x00, 0x77, 0x70, 0x00, 0x00, 0x00, 0x00, 0x07, 0x77, 0x00, 0x00, /* scanline 8 */
0x00, 0x00, 0x77, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x77, 0x00, 0x00, /* scanline 9 */
0x00, 0x07, 0x77, 0x00, 0x07, 0x77, 0x77, 0x70, 0x00, 0x77, 0x70, 0x00, /* scanline 10 */
0x00, 0x07, 0x70, 0x00, 0x77, 0x77, 0x77, 0x77, 0x00, 0x07, 0x70, 0x00, /* scanline 11 */
0x07, 0x77, 0x70, 0x00, 0x77, 0x77, 0x77, 0x77, 0x00, 0x07, 0x77, 0x70, /* scanline 12 */
0x07, 0x77, 0x70, 0x00, 0x77, 0x77, 0x77, 0x77, 0x00, 0x07, 0x77, 0x70, /* scanline 13 */
0x00, 0x07, 0x70, 0x00, 0x77, 0x77, 0x77, 0x77, 0x00, 0x07, 0x70, 0x00, /* scanline 14 */
0x00, 0x07, 0x77, 0x00, 0x07, 0x77, 0x77, 0x70, 0x00, 0x77, 0x70, 0x00, /* scanline 15 */
0x00, 0x00, 0x77, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x77, 0x00, 0x00, /* scanline 16 */
0x00, 0x00, 0x77, 0x70, 0x00, 0x00, 0x00, 0x00, 0x07, 0x77, 0x00, 0x00, /* scanline 17 */
0x00, 0x00, 0x07, 0x77, 0x00, 0x00, 0x00, 0x00, 0x77, 0x70, 0x00, 0x00, /* scanline 18 */
0x00, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x00, /* scanline 19 */
0x00, 0x00, 0x00, 0x07, 0x77, 0x77, 0x77, 0x77, 0x70, 0x00, 0x00, 0x00, /* scanline 20 */
0x00, 0x00, 0x00, 0x00, 0x07, 0x77, 0x77, 0x70, 0x00, 0x00, 0x00, 0x00, /* scanline 21 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 22 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 23 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 24 */
};

const uint8_t _ic_battery_empty_24_h[] = {
24,24,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 1 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 2 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 3 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 4 */
0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, /* scanline 5 */
0x00, 0x00, 0x00, 0x07, 0x77, 0x77, 0x77, 0x77, 0x70, 0x00, 0x00, 0x00, /* scanline 6 */
0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, /* scanline 7 */
0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, /* scanline 8 */
0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, /* scanline 9 */
0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, /* scanline 10 */
0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, /* scanline 11 */
0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, /* scanline 12 */
0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, /* scanline 13 */
0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, /* scanline 14 */
0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, /* scanline 15 */
0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, /* scanline 16 */
0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, /* scanline 17 */
0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, /* scanline 18 */
0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, /* scanline 19 */
0x00, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x07, 0x70, 0x00, 0x00, 0x00, /* scanline 20 */
0x00, 0x00, 0x00, 0x07, 0x77, 0x77, 0x77, 0x77, 0x70, 0x00, 0x00, 0x00, /* scanline 21 */
0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x77, 0x77, 0x00, 0x00, 0x00, 0x00, /* scanline 22 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 23 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* scanline 24 */
};

Enum_Common_Screen_SUBID_RUNINGMODE curr_subscreenid_runingmode;

//distance 
typedef enum
{
	ENUM_RMDISTANCE_TARGET_3KM = 0,
	ENUM_RMDISTANCE_TARGET_5KM,
	ENUM_RMDISTANCE_TARGET_10KM,
	ENUM_RMDISTANCE_TARGET_15KM,
	ENUM_RMDISTANCE_TARGET_HMARATHON,         //hmarathon21.1
	ENUM_RMDISTANCE_TARGET_MARATHON,          //marathon42.2
	ENUM_RMDISTANCE_TARGET_50KM,
	ENUM_RMDISTANCE_TARGET_MAX,
}app_runingmodedistancetarget_enum;

char runingmodedistancetarget_3km[] = {"3km"};
char runingmodedistancetarget_5km[] = {"5km"};
char runingmodedistancetarget_10km[] = {"10km"};
char runingmodedistancetarget_15km[] = {"15km"};
//char runingmodedistancetarget_HMARATHON[] = {"3km"};
//char runingmodedistancetarget_MARATHON[] = {"3km"};
char runingmodedistancetarget_50km[] = {"50km"};


//duration
typedef enum
{
	ENUM_RMDURATION_TARGET_20MIN = 0,
	ENUM_RMDURATION_TARGET_30MIN,
	ENUM_RMDURATION_TARGET_60MIN,
	ENUM_RMDURATION_TARGET_90MIN,
	ENUM_RMDURATION_TARGET_120MIN,
	ENUM_RMDURATION_TARGET_180MIN,
	ENUM_RMDURATION_TARGET_240MIN,
	ENUM_RMDURATION_TARGET_MAX,
}app_runingmodedurationtarget_enum;
    

char runingmodedurationtarget_20min[] = {"20min"};
char runingmodedurationtarget_30min[] = {"30min"}; 
char runingmodedurationtarget_60min[] = {"60min"};
char runingmodedurationtarget_90min[] = {"90min"};
char runingmodedurationtarget_120min[] = {"120min"};
char runingmodedurationtarget_180min[] = {"180min"};
char runingmodedurationtarget_240min[] = {"240min"};


//char* runingmodedurationtarget[ENUM_RMDURATION_TARGET_MAX] = {"20min","30min","60min","90min","120min","180min","240min"};


//calorie
typedef enum
{
	ENUM_RMCALORIE_TARGET_100KCAL,
	ENUM_RMCALORIE_TARGET_200KCAL,
	ENUM_RMCALORIE_TARGET_300KCAL,
	ENUM_RMCALORIE_TARGET_500KCAL,
	ENUM_RMCALORIE_TARGET_800KCAL,
	ENUM_RMCALORIE_TARGET_1000KCAL,
	ENUM_RMCALORIE_TARGET_MAX,
}app_runingmodecalorietarget_enum;
    


char runingmodecalorietarget_100kcal[] = {"100kcal"};
char runingmodecalorietarget_200kcal[] = {"200kcal"};
char runingmodecalorietarget_300kcal[] = {"300kcal"};
char runingmodecalorietarget_500kcal[] = {"500kcal"};
char runingmodecalorietarget_800kcal[] = {"800kcal"};
char runingmodecalorietarget_1000kcal[] = {"1000kcal"};

//char* runingmodecalorietarget[ENUM_RMCALORIE_TARGET_MAX] = {"100kcal","200kcal","300kcal","500kcal","800kcal","1000kcal"};


typedef enum
{
	ENUM_RMDISTANCE_WARN_OFF = 0,
	ENUM_RMDISTANCE_WARN_500M,
	ENUM_RMDISTANCE_WARN_1KM,
	ENUM_RMDISTANCE_WARN_2KM,
	ENUM_RMDISTANCE_WARN_3KM,
	ENUM_RMDISTANCE_WARN_5KM,
	ENUM_RMDISTANCE_WARN_MAX,
}enum_runingmode_distancewarn;

char runingmode_distancewarn_500m[] = {"500m"};
char runingmode_distancewarn_1km[] = {"1km"};
char runingmode_distancewarn_2km[] = {"2km"};
char runingmode_distancewarn_3km[] = {"3km"};
char runingmode_distancewarn_5km[] = {"5km"};


typedef enum
{
	ENUM_RMDURATION_WARN_OFF = 0,
	ENUM_RMDURATION_WARN_5MIN,
	ENUM_RMDURATION_WARN_10MIN,
	ENUM_RMDURATION_WARN_15MIN,
	ENUM_RMDURATION_WARN_20MIN,
	ENUM_RMDURATION_WARN_30MIN,
	ENUM_RMDURATION_WARN_60MIN,
	ENUM_RMDURATION_WARN_90MIN,
	ENUM_RMDURATION_WARN_120MIN,
	ENUM_RMDURATION_WARN_MAX,
}enum_runingmode_durationwarn;


char runingmode_durationwarn_5min[] = {"5min"};
char runingmode_durationwarn_10min[] = {"10min"};
char runingmode_durationwarn_15min[] = {"15min"};
char runingmode_durationwarn_20min[] = {"20min"};
char runingmode_durationwarn_30min[] = {"30min"};
char runingmode_durationwarn_60min[] = {"60min"};
char runingmode_durationwarn_90min[] = {"90min"};
char runingmode_durationwarn_120min[] = {"120min"};


typedef enum
{
	ENUM_RMCALORIE_WARN_OFF,
	ENUM_RMCALORIE_WARN_50KCAL,
	ENUM_RMCALORIE_WARN_100KCAL,
	ENUM_RMCALORIE_WARN_150KCAL,
	ENUM_RMCALORIE_WARN_200KCAL,
	ENUM_RMCALORIE_WARN_MAX,
}enum_runingmode_calorie;

char runingmode_calorie_50kcal[] = {"50kcal"};
char runingmode_calorie_100kcal[] = {"100kcal"};
char runingmode_calorie_150kcal[] = {"150kcal"};
char runingmode_calorie_200kcal[] = {"200kcal"};
    


void UI_Set_Curr_SubScreenID_Runingmode(Enum_Common_Screen_SUBID_RUNINGMODE curr_id)
{

    curr_subscreenid_runingmode = curr_id;

}

int UI_Get_Curr_SubScreenID_Runingmode(void)
{

    return curr_subscreenid_runingmode;

}

//RuningMode
void UI_Screen_RuningModeEntry(void)
{



    if(UI_Get_Curr_ScreenID()!=Common_Screen_MainID_Running)
        return;

    switch(curr_subscreenid_runingmode)
    {
        case Common_Screen_SubID_RuningMode_Prepare:
            UI_Screen_RuningModePrepare_Entry();
        break;
        case Common_Screen_SubID_RuningMode_Countdown:
            UI_Screen_RuningModeCountDown_Entry();
        break;
        case Common_Screen_SubID_RuningMode_Setting:
            UI_Screen_RuningModeSetting_Entry();
        break;
        case Common_Screen_SubID_RuningMode_TargetSetting:
            UI_Screen_RuningModeTargetSetting_Entry();
        break;
        case Common_Screen_SubID_RuningMode_TargetSetting_Distance:
            UI_Screen_RuningModeDistanceTargetSetting_Entry();
        break;
        case Common_Screen_SubID_RuningMode_TargetSetting_Duration:
            UI_Screen_RuningModeDurationTargetSetting_Entry();
        break;
        case Common_Screen_SubID_RuningMode_TargetSetting_Calorie:
            UI_Screen_RuningModeCalorieTargetSetting_Entry();
        break;
        case Common_Screen_SubID_RuningMode_WarnSetting:
            UI_Screen_RuningModeWarnSetting_Entry();
        break;
        case Common_Screen_SubID_RuningMode_WarnSetting_Distance:
            UI_Screen_RuningModeDistanceWarnSetting_Entry();
        break;
        case Common_Screen_SubID_RuningMode_WarnSetting_Duration:
            UI_Screen_RuningModeDurationWarnSetting_Entry();
        break;
        case Common_Screen_SubID_RuningMode_WarnSetting_Calorie:
            UI_Screen_RuningModeCalorieWarnSetting_Entry();
        break;
        case Common_Screen_SubID_RuningMode_WarnSetting_Heartrate:
            UI_Screen_RuningModeHrWarnSetting_Entry();
        break;
        case Common_Screen_SubID_RuningMode_WarnSetting_Heartrate_Upperlimit:
            UI_Screen_RuningModeHrWarnUpperLimitSetting_Entry();
        break;
        case Common_Screen_SubID_RuningMode_WarnSetting_Heartrate_Lowerlimit:
            UI_Screen_RuningModeHrWarnLowerLimitSetting_Entry();
        break;
        case Common_Screen_SubID_RuningMode_WarnSetting_Speed:
            UI_Screen_RuningModeSpeedWarnSetting_Entry();
        break;
        case Common_Screen_SubID_RuningMode_WarnSetting_Speed_Upperlimit:
            UI_Screen_RuningModeSpeedUpperLlimitSetting_Entry();
        break;
        case Common_Screen_SubID_RuningMode_WarnSetting_Speed_Lowerlimit:
            UI_Screen_RuningModeSpeedLowerLlimitSetting_Entry();
        break;
        case Common_Screen_SubID_RuningMode_Datadetail:
            UI_Screen_RuningModeDetail_Entry();
        break;
        case Common_Screen_SubID_RuningMode_Pause:
            UI_Screen_RuningModePause_Entry();
        break;
        case Common_Screen_SubID_RuningMode_Continue:
            UI_Screen_RuningModeContinue_Entry();
        break;
        case Common_Screen_SubID_RuningMode_Menu:
            UI_Screen_RuningModeMenu_Entry();
        break;
        case Common_Screen_SubID_RuningMode_Abandon:
            UI_Screen_RuningModeAbandon_Entry();
        break;
        case Common_Screen_SubID_RuningMode_CompleteMenu:
            UI_Screen_RuningModeCompleteMenu_Entry();
        break;
        case Common_Screen_SubID_RuningMode_History:
            UI_Screen_RuningModeHistory_Entry();
        break;
        default:
            UI_Screen_RuningModePrepare_Entry();
            break;
    }

}


//RuningMode
void UI_Screen_RuningModePrepare_Entry(void)
{
    //初始化数据等
    UI_Screen_RuningModePrepare_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModePrepare_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModePrepare_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModePrepare_tpupslidehandle,
                                    UI_Screen_RuningModePrepare_tpdownslidehandle,
                                    UI_Screen_RuningModePrepare_tpleftslidehandle,
                                    UI_Screen_RuningModePrepare_tprightslidehandle);

}

void UI_Screen_RuningModePrepare_Display()
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_Prepare)
        return;

    UI_Common_Clear_Screen(temp_ram);

    UI_Common_Show_ThreeIconBar(temp_ram,0,0,(uint8_t*)image_gps_24_h,(uint8_t*)image_hr_24_h,(uint8_t*)NULL);

    UI_Common_Add_Battery(temp_ram,124,17,1);
    
    UI_Common_Show_ModeListIconStringBar(temp_ram,0,59,(uint8_t*)image_sportmode_run_24_h,(uint8_t*)image_sportmode_start_24_h,(uint8_t*)BtnSport_h,(uint8_t*)gchinesefont_sportscene_start,APP_COLOR_RED,APP_COLOR_WHITE);

    UI_Common_Show_ModeListIconStringBar(temp_ram,0,118,NULL,(uint8_t*)image_sportmode_right_24_h,NULL,(uint8_t*)gchinesefont_sportscene_setting,APP_COLOR_BLACK,APP_COLOR_WHITE);


    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_RuningModePrepare_Exit(void)
{


}

void UI_Screen_RuningModePrepare_shortkeyhandle(void)
{

    //UI_Common_Shake();
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Countdown);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModePrepare_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModePrepare_holdlongkeyhandle(void)
{
}

void UI_Screen_RuningModePrepare_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Countdown);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
            UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
            UI_Screen_draw_Screen();
        }
        break;
        default:
        break;
    }


    
}

void UI_Screen_RuningModePrepare_tpupslidehandle(void)
{


}

void UI_Screen_RuningModePrepare_tpdownslidehandle(void)
{


}

void UI_Screen_RuningModePrepare_tpleftslidehandle(void)
{


}

void UI_Screen_RuningModePrepare_tprightslidehandle(void)
{


    UI_Set_Curr_ScreenID(Common_Screen_MainID_Modelist);
    UI_Screen_draw_Screen();

}


extern UI_Common_sportmode_countdown_s sportmode_countdown;

void UI_Screen_RuningModeCountDown_Entry(void)
{

    UI_Common_SportModeCountDownInfoDefault();
    UI_Screen_RuningModeCountDown_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModeCountDown_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeCountDown_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeCountDown_tpupslidehandle,
                                    UI_Screen_RuningModeCountDown_tpdownslidehandle,
                                    UI_Screen_RuningModeCountDown_tpleftslidehandle,
                                    UI_Screen_RuningModeCountDown_tprightslidehandle);
}



void UI_Screen_RuningModeCountDown_Display_Timerhandle(void)
{
        UI_Screen_RuningModeCountDown_Display();
}


void  UI_Screen_RuningModeCountDown_Display(void)
{
    int ctime = 0;
    uint8_t* fontinfo = NULL;
    double angle = 0;
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_Countdown)
        return;

    UI_Common_Clear_Screen(temp_ram);
    
    if(sportmode_countdown.curr_time<sportmode_countdown.total_time)
    {
        ctime = (sportmode_countdown.total_time -sportmode_countdown.curr_time)/1000;
        angle = (double)sportmode_countdown.curr_time/(double)sportmode_countdown.total_time*2*PI;
        UI_Common_DispRuningModeCountDownRound(temp_ram,angle);
        sportmode_countdown.curr_time = sportmode_countdown.curr_time + sportmode_countdown.segment_time;
        
        UI_Common_set_timer_handle(UI_Screen_RuningModeCountDown_Display_Timerhandle);
        App_Lcd_TimerStart(sportmode_countdown.segment_time);
    }
    else
    {
        UI_Screen_RuningModeCountDown_Exit();
        //开启跑步模式
        Scene_Run_Enable();
        //跑步模式中，不允许进入大休眠
        UI_Commom_Set_Allow_Lockstate2(0);
        UI_Common_Shake();
        UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Datadetail);
        UI_Screen_draw_Screen();
        
        return;
    }

    switch(ctime)
    {
        case 1:
            fontinfo = (uint8_t*)font_tgl_96_1_h;
            break;
        case 2:
            fontinfo = (uint8_t*)font_tgl_96_2_h;
            break;
        case 3:
            fontinfo = (uint8_t*)font_tgl_96_3_h;
            break;
        default:
            fontinfo = (uint8_t*)font_tgl_96_1_h;
            break;
    
    }
    
    UI_Common_AddBWsourcePic(temp_ram,74,53,(uint8_t*)fontinfo,APP_COLOR_BLACK,APP_COLOR_WHITE);

    
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_RuningModeCountDown_Exit(void)
{
     UI_Common_set_timer_handle(NULL);
     App_Lcd_TimerStop();
}

void UI_Screen_RuningModeCountDown_shortkeyhandle(void)
{

    #if 0
        UI_Screen_RuningModeCountDown_Exit();
        UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
        UI_Screen_draw_Screen();
    #endif

}

void UI_Screen_RuningModeCountDown_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeCountDown_holdlongkeyhandle(void)
{
}

void UI_Screen_RuningModeCountDown_tpclickhandle(int point_x,int point_y)
{


    
}

void UI_Screen_RuningModeCountDown_tpupslidehandle(void)
{


}

void UI_Screen_RuningModeCountDown_tpdownslidehandle(void)
{


}

void UI_Screen_RuningModeCountDown_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeCountDown_tprightslidehandle(void)
{

    UI_Screen_RuningModeCountDown_Exit();
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
    UI_Screen_draw_Screen();


}

 

Struct_runningmode_setting runningmode_setting_info;

void UI_Screen_RuningModeSetting_Init(void)
{

    runningmode_setting_info.target_type = Enum_runningmode_setting_target_off;
    runningmode_setting_info.target_distance = 0;
    runningmode_setting_info.target_duration = 0;
    runningmode_setting_info.target_calorie = 0;

    runningmode_setting_info.target_index =0;
    
    runningmode_setting_info.warn_distance = 0;
    runningmode_setting_info.warn_duration = 0;
    runningmode_setting_info.warn_calorie = 0;

    runningmode_setting_info.warn_distance_index = 0;
    runningmode_setting_info.warn_duration_index = 0;
    runningmode_setting_info.warn_calorie_index = 0;
    
    runningmode_setting_info.heartrate_uplimit = 0;
    runningmode_setting_info.heartrate_lowlimit = 0;

    runningmode_setting_info.heartrate_uplimit_index = 0;
    runningmode_setting_info.heartrate_lowlimit_index = 0;
    
    runningmode_setting_info.speed_uplimit_switch = 0;
    runningmode_setting_info.speed_uplimit = 0;
    runningmode_setting_info.speed_lowlimit = 0;
    runningmode_setting_info.speed_lowlimit_switch = 0;

    
        
}

void UI_Screen_RuningModeSetting_Getsetting(Struct_runningmode_setting *info)
{

    memcpy(info, &runningmode_setting_info, sizeof(Struct_runningmode_setting));

}



//跑步设置列表
void UI_Screen_RuningModeSetting_Entry(void)
{

    UI_Screen_RuningModeSetting_Display();
    
    UI_Common_set_key_handle(UI_Screen_RuningModeSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeSetting_tpupslidehandle,
                                    UI_Screen_RuningModeSetting_tpdownslidehandle,
                                    UI_Screen_RuningModeSetting_tpleftslidehandle,
                                    UI_Screen_RuningModeSetting_tprightslidehandle);
    
}

void UI_Screen_RuningModeSetting_Display(void)
{

    uint8_t* fontinfo = NULL;

    int fontinfo_type = 0;

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_Setting)
        return;

    UI_Common_Clear_Screen(temp_ram);
    

    if(runningmode_setting_info.target_type == Enum_runningmode_setting_target_off)
    {
        fontinfo = (uint8_t*)gchinesefont_sportscene_turnoff_s;
        fontinfo_type = 0;
    }
    else if(runningmode_setting_info.target_type == Enum_runningmode_setting_target_distance)
    {
    #if 0
        //distance 
        typedef enum
        {
            ENUM_RMDISTANCE_TARGET_3KM = 0,
            ENUM_RMDISTANCE_TARGET_5KM,
            ENUM_RMDISTANCE_TARGET_10KM,
            ENUM_RMDISTANCE_TARGET_15KM,
            ENUM_RMDISTANCE_TARGET_HMARATHON,         //hmarathon21.1
            ENUM_RMDISTANCE_TARGET_MARATHON,          //marathon42.2
            ENUM_RMDISTANCE_TARGET_50KM,
            ENUM_RMDISTANCE_TARGET_MAX,
        }app_runingmodedistancetarget_enum;
    #endif
    #if 0
        switch(runningmode_setting_info.target_index)
        {

            case ENUM_RMDISTANCE_TARGET_3KM:
                fontinfo = (uint8_t *)gchinesefont_sportscene_target_distance_3km_s;
            break;
            case ENUM_RMDISTANCE_TARGET_5KM:
                fontinfo = (uint8_t *)gchinesefont_sportscene_target_distance_5km_s;
            break;
            case ENUM_RMDISTANCE_TARGET_10KM:
                fontinfo = (uint8_t *)gchinesefont_sportscene_target_distance_10km_s;
            break;
            case ENUM_RMDISTANCE_TARGET_15KM:
                fontinfo = (uint8_t *)gchinesefont_sportscene_target_distance_15km_s;
            break;
            case ENUM_RMDISTANCE_TARGET_HMARATHON:
                fontinfo = (uint8_t *)gchinesefont_sportscene_target_distance_halfmarathon_s;
            break;
            case ENUM_RMDISTANCE_TARGET_MARATHON:
                fontinfo = (uint8_t *)gchinesefont_sportscene_target_distance_marathon_s;
            break;
            case ENUM_RMDISTANCE_TARGET_50KM:
                fontinfo = (uint8_t *)gchinesefont_sportscene_target_distance_50km_s;
            break;
            default:
            break;
        }

        const char runingmodedistancetarget_3km[] = {"3km"};
        const char runingmodedistancetarget_5km[] = {"5km"};
        const char runingmodedistancetarget_10km[] = {"10km"};
        const char runingmodedistancetarget_15km[] = {"15km"};
        const char runingmodedistancetarget_HMARATHON[] = {"3km"};
        const char runingmodedistancetarget_MARATHON[] = {"3km"};
        const char runingmodedistancetarget_50km[] = {"50km"};

        
    #else


    
        switch(runningmode_setting_info.target_index)
        {
        
            case ENUM_RMDISTANCE_TARGET_3KM:
                fontinfo = (uint8_t*)runingmodedistancetarget_3km;
                fontinfo_type = 1;
            break;
            case ENUM_RMDISTANCE_TARGET_5KM:
                fontinfo = (uint8_t*)runingmodedistancetarget_5km;
                fontinfo_type = 1;
            break;
            case ENUM_RMDISTANCE_TARGET_10KM:
                fontinfo = (uint8_t*)runingmodedistancetarget_10km;
                fontinfo_type = 1;
            break;
            case ENUM_RMDISTANCE_TARGET_15KM:
                fontinfo = (uint8_t*)runingmodedistancetarget_15km;
                fontinfo_type = 1;
            break;
            case ENUM_RMDISTANCE_TARGET_HMARATHON:
                fontinfo = (uint8_t*)gchinesefont_sportscene_target_distance_halfmarathon_s;
                fontinfo_type = 0;
            break;
            case ENUM_RMDISTANCE_TARGET_MARATHON:
                fontinfo = (uint8_t*)gchinesefont_sportscene_target_distance_marathon_s;
                fontinfo_type = 0;
            break;
            case ENUM_RMDISTANCE_TARGET_50KM:
                fontinfo = (uint8_t*)runingmodedistancetarget_50km;
                fontinfo_type = 1;
            break;
            default:
            break;
        }
    
    #endif
    }
    else if(runningmode_setting_info.target_type == Enum_runningmode_setting_target_duration)
    {

    
        //duration
    #if 0
            //duration
            typedef enum
            {
                ENUM_RMDURATION_TARGET_20MIN = 0,
                ENUM_RMDURATION_TARGET_30MIN,
                ENUM_RMDURATION_TARGET_60MIN,
                ENUM_RMDURATION_TARGET_90MIN,
                ENUM_RMDURATION_TARGET_120MIN,
                ENUM_RMDURATION_TARGET_180MIN,
                ENUM_RMDURATION_TARGET_240MIN,
                ENUM_RMDURATION_TARGET_MAX,
            }app_runingmodedurationtarget_enum;
    #endif
        
        switch(runningmode_setting_info.target_index)
        {

            case ENUM_RMDURATION_TARGET_20MIN:
                fontinfo = (uint8_t*)runingmodedurationtarget_20min;
                fontinfo_type = 1;
            break;
            case ENUM_RMDURATION_TARGET_30MIN:
                fontinfo = (uint8_t*)runingmodedurationtarget_30min;
                fontinfo_type = 1;
            break;
            case ENUM_RMDURATION_TARGET_60MIN:
                fontinfo = (uint8_t*)runingmodedurationtarget_60min;
                fontinfo_type = 1;
            break;
            case ENUM_RMDURATION_TARGET_90MIN:
                fontinfo = (uint8_t*)runingmodedurationtarget_90min;
                fontinfo_type = 1;
            break;
            case ENUM_RMDURATION_TARGET_120MIN:
                fontinfo = (uint8_t*)runingmodedurationtarget_120min;
                fontinfo_type = 1;
            break;
            case ENUM_RMDURATION_TARGET_180MIN:
                fontinfo = (uint8_t*)runingmodedurationtarget_180min;
                fontinfo_type = 1;
            break;
            case ENUM_RMDURATION_TARGET_240MIN:
                fontinfo = (uint8_t*)runingmodedurationtarget_240min;
                fontinfo_type = 1;
            break;            
            default:
            break;


        
        }
    }
    else if(runningmode_setting_info.target_type == Enum_runningmode_setting_target_calorie)
    {

    #if 0
            //calorie
            typedef enum
            {
                ENUM_RMCALORIE_TARGET_100KCAL,
                ENUM_RMCALORIE_TARGET_200KCAL,
                ENUM_RMCALORIE_TARGET_300KCAL,
                ENUM_RMCALORIE_TARGET_500KCAL,
                ENUM_RMCALORIE_TARGET_800KCAL,
                ENUM_RMCALORIE_TARGET_1000KCAL,
                ENUM_RMCALORIE_TARGET_MAX,
            }app_runingmodecalorietarget_enum;
    #endif
        
        switch(runningmode_setting_info.target_index)
        {

            case ENUM_RMCALORIE_TARGET_100KCAL:
                fontinfo = (uint8_t*)runingmodecalorietarget_100kcal;
                fontinfo_type = 1;
            break;
            case ENUM_RMCALORIE_TARGET_200KCAL:
                fontinfo = (uint8_t*)runingmodecalorietarget_200kcal;
                fontinfo_type = 1;
            break;
            case ENUM_RMCALORIE_TARGET_300KCAL:
                fontinfo = (uint8_t*)runingmodecalorietarget_300kcal;
                fontinfo_type = 1;
            break;
            case ENUM_RMCALORIE_TARGET_500KCAL:
                fontinfo = (uint8_t*)runingmodecalorietarget_500kcal;
                fontinfo_type = 1;
            break;
            case ENUM_RMCALORIE_TARGET_800KCAL:
                fontinfo = (uint8_t*)runingmodecalorietarget_800kcal;
                fontinfo_type = 1;
            break;
            case ENUM_RMCALORIE_TARGET_1000KCAL:
                fontinfo = (uint8_t*)runingmodecalorietarget_1000kcal;
                fontinfo_type = 1;
            break;
            default:
            break;
        
        }
    }


    UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t*)gchinesefont_sportscene_target,(uint8_t*)fontinfo,NULL,fontinfo_type);
    UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t*)gchinesefont_sportscene_warn,NULL,NULL,0);

    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_RuningModeSetting_Exit(void)
{
}

void UI_Screen_RuningModeSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_RuningModeSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_TargetSetting);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        break;
        default:
        break;
    }


    
}


void UI_Screen_RuningModeSetting_tpupslidehandle(void)
{
}

void UI_Screen_RuningModeSetting_tpdownslidehandle(void)
{
}

void UI_Screen_RuningModeSetting_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
    UI_Screen_draw_Screen();

}

// target 

static int targetsetting_page_number = 0;

void UI_Screen_RuningModeTargetSetting_Entry(void)
{

    UI_Screen_RuningModeTargetSetting_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModeSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeTargetSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeTargetSetting_tpupslidehandle,
                                    UI_Screen_RuningModeTargetSetting_tpdownslidehandle,
                                    UI_Screen_RuningModeTargetSetting_tpleftslidehandle,
                                    UI_Screen_RuningModeTargetSetting_tprightslidehandle);
    
}

void UI_Screen_RuningModeTargetSetting_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_TargetSetting)
        return;

    UI_Common_Clear_Screen(temp_ram);
    

    if(targetsetting_page_number == 0)
    {
        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t*)gchinesefont_sportscene_target_notarget,(uint8_t*)NULL,NULL,0);
        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t*)gchinesefont_sportscene_target_distance,(uint8_t*)NULL,NULL,0);
        UI_Common_List_RarrowDoubleline(temp_ram,0,118,(uint8_t*)gchinesefont_sportscene_target_duration,(uint8_t*)NULL,NULL,0);
    }
    else
    {
        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t*)gchinesefont_sportscene_target_calorie,(uint8_t*)NULL,NULL,0);
    }

    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_RuningModeTargetSetting_Exit(void)
{

    targetsetting_page_number =0;

}

void UI_Screen_RuningModeTargetSetting_shortkeyhandle(void)
{

    UI_Screen_RuningModeTargetSetting_Exit();

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeTargetSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeTargetSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_RuningModeTargetSetting_None(void)
{

    runningmode_setting_info.target_type = Enum_runningmode_setting_target_off;
    runningmode_setting_info.target_distance = 0;
    runningmode_setting_info.target_duration = 0;
    runningmode_setting_info.target_calorie = 0;

}


void UI_Screen_RuningModeTargetSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(targetsetting_page_number == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
            
                UI_Screen_RuningModeTargetSetting_Exit();
                UI_Screen_RuningModeTargetSetting_None();
                UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                UI_Screen_RuningModeTargetSetting_Exit();
                UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_TargetSetting_Distance);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
            
                UI_Screen_RuningModeTargetSetting_Exit();
                UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_TargetSetting_Duration);
                UI_Screen_draw_Screen();
            }
            break;
            default:
            break;
        }
    }
    else
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
            
                UI_Screen_RuningModeTargetSetting_Exit();
                UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_TargetSetting_Calorie);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            break;
            default:
            break;
        }
    }


    
}


void UI_Screen_RuningModeTargetSetting_tpupslidehandle(void)
{
    if(targetsetting_page_number ==0)
    {
        targetsetting_page_number =1;
    }
    else
    {
        targetsetting_page_number =0;
    }

    //UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_TargetSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeTargetSetting_tpdownslidehandle(void)
{
    if(targetsetting_page_number ==0)
    {
        targetsetting_page_number =1;
    }
    else
    {
        targetsetting_page_number =0;
    }

    //UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_TargetSetting);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeTargetSetting_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeTargetSetting_tprightslidehandle(void)
{

    UI_Screen_RuningModeTargetSetting_Exit();

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();

}


//warn
static int warn_page_number = 0;

void UI_Screen_RuningModeWarnSetting_Entry(void)
{
    warn_page_number =0;

    UI_Screen_RuningModeWarnSetting_Display();
    
    UI_Common_set_key_handle(UI_Screen_RuningModeWarnSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeWarnSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeWarnSetting_tpupslidehandle,
                                    UI_Screen_RuningModeWarnSetting_tpdownslidehandle,
                                    UI_Screen_RuningModeWarnSetting_tpleftslidehandle,
                                    UI_Screen_RuningModeWarnSetting_tprightslidehandle);
    
}

void UI_Screen_RuningModeWarnSetting_Display(void)
{

    uint8_t* fontinfo = NULL;
    char* fontinfo_string = NULL;
    int fontinfo_type = 0;
    
    char info[16]={0};
    hrZoneRange_t hr_info;
    Scene_Cnm_HrZoneGet(&hr_info);
    int temp_a,temp_b;

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_WarnSetting)
        return;

    UI_Common_Clear_Screen(temp_ram);
    

    if(warn_page_number ==0)
    {        
        switch(runningmode_setting_info.warn_distance)
        {
            case 0:
                fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                fontinfo_string = NULL;
                fontinfo_type = 0;
            break;
            case 500:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_distancewarn_500m;
                fontinfo_type = 2;
            break;
            case 1000:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_distancewarn_1km;
                fontinfo_type = 2;
            break;
            case 2000:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_distancewarn_2km;
                fontinfo_type = 2;
            break;
            case 3000:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_distancewarn_3km;
                fontinfo_type = 2;
            break;
            case 5000:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_distancewarn_5km;
                fontinfo_type = 2;
            break;
            default:
            break;
        }

        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_target_distance,(uint8_t*)fontinfo,(uint8_t*)fontinfo_string,fontinfo_type);

        switch(runningmode_setting_info.warn_duration_index)
        {
            case 0:
                fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                fontinfo_string = NULL;
                fontinfo_type = 0;
            break;
            case 1:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_durationwarn_5min;
                fontinfo_type = 2;
            break;
            case 2:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_durationwarn_10min;
                fontinfo_type = 2;
            break;
            case 3:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_durationwarn_15min;
                fontinfo_type = 2;
            break;
            case 4:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_durationwarn_20min;
                fontinfo_type = 2;
            break;
            case 5:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_durationwarn_30min;
                fontinfo_type = 2;
            break;
            case 6:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_durationwarn_60min;
                fontinfo_type = 2;
            break;
            case 7:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_durationwarn_90min;
                fontinfo_type = 2;
            break;
            case 8:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_durationwarn_120min;
                fontinfo_type = 2;
            break;
            default:
            break;
        }
        
        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_target_duration,(uint8_t*)fontinfo,(uint8_t*)fontinfo_string,fontinfo_type);
        
        switch(runningmode_setting_info.warn_calorie)
        {
            case 0:
                fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
                fontinfo_string = NULL;
                fontinfo_type = 0;
            break;
            case 50:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_calorie_50kcal;
                fontinfo_type = 2;
            break;
            case 100:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_calorie_100kcal;
                fontinfo_type = 2;
            break;
            case 150:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_calorie_150kcal;
                fontinfo_type = 2;
            break;
            case 200:
                fontinfo = (uint8_t *)gchinesefont_sportmode_every;
                fontinfo_string = runingmode_calorie_200kcal;
                fontinfo_type = 2;
            break;
            default:
            break;
        }
        UI_Common_List_RarrowDoubleline(temp_ram,0,118,(uint8_t *)gchinesefont_sportscene_target_calorie,(uint8_t*)fontinfo,(uint8_t*)fontinfo_string,fontinfo_type);
    }
    else if(warn_page_number ==1)
    {

        if(runningmode_setting_info.heartrate_uplimit == 0&&runningmode_setting_info.heartrate_lowlimit == 0)
        {
            fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
            UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_warn_heartrate,fontinfo,NULL,0);
        }
        else if(runningmode_setting_info.heartrate_uplimit == 0)
        {
            switch(runningmode_setting_info.heartrate_lowlimit)
            {
                case 1:
                    sprintf(info,">%d",hr_info.HrZone0);
                break;
                case 2:
                    sprintf(info,">%d",hr_info.HrZone1);
                break;
                case 3:
                    sprintf(info,">%d",hr_info.HrZone2);
                break;
                case 4:
                    sprintf(info,">%d",hr_info.HrZone3);
                break;
                case 5:
                    sprintf(info,">%d",hr_info.HrZone4);
                break;
                default:
                break;
            }
            UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_warn_heartrate,(uint8_t*)info,NULL,1);
            
        }
        else if(runningmode_setting_info.heartrate_lowlimit == 0)
        {
            switch(runningmode_setting_info.heartrate_uplimit)
            {
                case 1:
                    sprintf(info,"<%d",hr_info.HrZone1);
                break;
                case 2:
                    sprintf(info,"<%d",hr_info.HrZone2);
                break;
                case 3:
                    sprintf(info,"<%d",hr_info.HrZone3);
                break;
                case 4:
                    sprintf(info,"<%d",hr_info.HrZone4);
                break;
                case 5:
                    sprintf(info,"<%d",hr_info.HrZone5);
                break;
                default:
                break;
            }
            
            UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_warn_heartrate,(uint8_t*)info,NULL,1);
        
        }
        else
        {
            switch(runningmode_setting_info.heartrate_lowlimit)
            {
                case 1:
                    temp_a=hr_info.HrZone0;
                break;
                case 2:
                    temp_a=hr_info.HrZone1;
                break;
                case 3:
                    temp_a=hr_info.HrZone2;
                break;
                case 4:
                    temp_a=hr_info.HrZone3;
                break;
                case 5:
                    temp_a=hr_info.HrZone4;
                break;
                default:
                break;
            }

            switch(runningmode_setting_info.heartrate_uplimit)
            {
                case 1:
                    temp_b=hr_info.HrZone1;
                break;
                case 2:
                    temp_b=hr_info.HrZone2;
                break;
                case 3:
                    temp_b=hr_info.HrZone3;
                break;
                case 4:
                    temp_b=hr_info.HrZone4;
                break;
                case 5:
                    temp_b=hr_info.HrZone5;
                break;
                default:
                break;
            }
            
            sprintf(info,"%d - %d",temp_a,temp_b);
            UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_warn_heartrate,(uint8_t*)info,NULL,1);
            
        
        }


        if(runningmode_setting_info.speed_lowlimit_switch == 0&&runningmode_setting_info.speed_uplimit_switch == 0)
        {
            fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
            UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_warn_minkm,(uint8_t*)fontinfo,NULL,0);
        }
        else if(runningmode_setting_info.speed_lowlimit_switch == 0)
        {
        
            sprintf(info,"<%02d'%02d\"",runningmode_setting_info.speed_uplimit/60,runningmode_setting_info.speed_uplimit%60);
            UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_warn_minkm,(uint8_t*)info,NULL,1);
        }
        else if(runningmode_setting_info.speed_uplimit_switch == 0)
        {

            sprintf(info,">%02d'%02d\"",runningmode_setting_info.speed_lowlimit/60,runningmode_setting_info.speed_lowlimit%60);
            UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_warn_minkm,(uint8_t*)info,NULL,1);
        
        }
        else
        {

            sprintf(info,"%02d'%02d\" - %02d'%02d\"",runningmode_setting_info.speed_lowlimit/60,runningmode_setting_info.speed_lowlimit%60,runningmode_setting_info.speed_uplimit/60,runningmode_setting_info.speed_uplimit%60);
            UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_warn_minkm,(uint8_t*)info,NULL,1);
        }

        
    }

    UI_Display_Prepare(temp_ram);
    
    
}

void UI_Screen_RuningModeWarnSetting_Exit(void)
{

    warn_page_number = 0;

}


void UI_Screen_RuningModeWarnSetting_shortkeyhandle(void)
{

    UI_Screen_RuningModeWarnSetting_Exit();
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeWarnSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeWarnSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_RuningModeWarnSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    

    if(warn_page_number == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Distance);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Duration);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Calorie);
                UI_Screen_draw_Screen();
            }
            break;
            default:
            break;
        }
    }
    else
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Heartrate);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Speed);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            break;
            default:
            break;
        }
        
    }


}


void UI_Screen_RuningModeWarnSetting_tpupslidehandle(void)
{

    if(warn_page_number == 0)
        warn_page_number = 1;
    else if(warn_page_number == 1)
        warn_page_number = 0;

    UI_Screen_RuningModeWarnSetting_Display();
    UI_Screen_Redraw_Screen();

    
}


void UI_Screen_RuningModeWarnSetting_tpdownslidehandle(void)
{

    if(warn_page_number == 0)
        warn_page_number = 1;
    else if(warn_page_number == 1)
        warn_page_number = 0;
    
    UI_Screen_RuningModeWarnSetting_Display();
    UI_Screen_Redraw_Screen();

    
}


void UI_Screen_RuningModeWarnSetting_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeWarnSetting_tprightslidehandle(void)
{

    UI_Screen_RuningModeWarnSetting_Exit();

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();

}




void UI_Screen_RuningModeDistanceTargetSetting_Entry(void)
{
    int i = 0;
        
    UI_Common_ScreenCleanListInfo();

    curr_list.total_count = ENUM_RMDISTANCE_TARGET_MAX;
    curr_list.total_list_page_count = (ENUM_RMDISTANCE_TARGET_MAX+2)/3;

    for(i = 0;i<ENUM_RMDISTANCE_TARGET_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }

    if(runningmode_setting_info.target_type == Enum_runningmode_setting_target_distance)
    {
        curr_list.icon_list[runningmode_setting_info.target_index]=(uint8_t *)radiobtn_checked_h;
    }
    

    curr_list.string_list[ENUM_RMDISTANCE_TARGET_3KM]=(uint8_t *)gchinesefont_sportscene_target_distance_3km;
    curr_list.string_list[ENUM_RMDISTANCE_TARGET_5KM]=(uint8_t *)gchinesefont_sportscene_target_distance_5km;
    curr_list.string_list[ENUM_RMDISTANCE_TARGET_10KM]=(uint8_t *)gchinesefont_sportscene_target_distance_10km;
    curr_list.string_list[ENUM_RMDISTANCE_TARGET_15KM]=(uint8_t *)gchinesefont_sportscene_target_distance_15km;
    curr_list.string_list[ENUM_RMDISTANCE_TARGET_HMARATHON]=(uint8_t *)gchinesefont_sportscene_target_distance_halfmarathon;
    curr_list.string_list[ENUM_RMDISTANCE_TARGET_MARATHON]=(uint8_t *)gchinesefont_sportscene_target_distance_marathon;
    curr_list.string_list[ENUM_RMDISTANCE_TARGET_50KM]=(uint8_t *)gchinesefont_sportscene_target_distance_50km;
    
    UI_Screen_RuningModeDistanceTargetSetting_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModeDistanceTargetSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeDistanceTargetSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeDistanceTargetSetting_tpupslidehandle,
                                    UI_Screen_RuningModeDistanceTargetSetting_tpdownslidehandle,
                                    UI_Screen_RuningModeDistanceTargetSetting_tpleftslidehandle,
                                    UI_Screen_RuningModeDistanceTargetSetting_tprightslidehandle);


    
    
}

void UI_Screen_RuningModeDistanceTargetSetting_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_TargetSetting_Distance)
        return;

    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);

    
}

void UI_Screen_RuningModeDistanceTargetSetting_Exit(void)
{


}

void UI_Screen_RuningModeDistanceTargetSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeDistanceTargetSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeDistanceTargetSetting_holdlongkeyhandle(void)
{
}




void UI_Screen_RuningModeDistanceTargetSetting_3KM(void)
{

    runningmode_setting_info.target_type = Enum_runningmode_setting_target_distance;
    runningmode_setting_info.target_distance = 3000;
    runningmode_setting_info.target_index = ENUM_RMDISTANCE_TARGET_3KM;
    
    runningmode_setting_info.target_duration = 0;
    runningmode_setting_info.target_calorie = 0;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeDistanceTargetSetting_5KM(void)
{

    runningmode_setting_info.target_type = Enum_runningmode_setting_target_distance;
    runningmode_setting_info.target_distance = 5000;
    runningmode_setting_info.target_index = ENUM_RMDISTANCE_TARGET_5KM;
    
    runningmode_setting_info.target_duration = 0;
    runningmode_setting_info.target_calorie = 0;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeDistanceTargetSetting_10KM(void)
{
    
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_distance;
    runningmode_setting_info.target_distance = 10000;
    runningmode_setting_info.target_index = ENUM_RMDISTANCE_TARGET_10KM;
    
    runningmode_setting_info.target_duration = 0;
    runningmode_setting_info.target_calorie = 0;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeDistanceTargetSetting_15KM(void)
{
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_distance;
    runningmode_setting_info.target_distance = 15000;
    runningmode_setting_info.target_index = ENUM_RMDISTANCE_TARGET_15KM;
    
    runningmode_setting_info.target_duration = 0;
    runningmode_setting_info.target_calorie = 0;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeDistanceTargetSetting_HMARATHON(void)
{
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_distance;
    runningmode_setting_info.target_distance = 21100;
    runningmode_setting_info.target_index = ENUM_RMDISTANCE_TARGET_HMARATHON;
    
    runningmode_setting_info.target_duration = 0;
    runningmode_setting_info.target_calorie = 0;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeDistanceTargetSetting_MARATHON(void)
{
    
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_distance;
    runningmode_setting_info.target_distance = 42200;
    runningmode_setting_info.target_index = ENUM_RMDISTANCE_TARGET_MARATHON;
    
    runningmode_setting_info.target_duration = 0;
    runningmode_setting_info.target_calorie = 0;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeDistanceTargetSetting_50KM(void)
{
    
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_distance;
    runningmode_setting_info.target_distance = 50000;
    runningmode_setting_info.target_index = ENUM_RMDISTANCE_TARGET_50KM;
    
    runningmode_setting_info.target_duration = 0;
    runningmode_setting_info.target_calorie = 0;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeDistanceTargetSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_RuningModeDistanceTargetSetting_3KM();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_RuningModeDistanceTargetSetting_5KM();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_RuningModeDistanceTargetSetting_10KM();
            }
            break;
            default:
            break;
        }
    }
    else if(curr_list.curr_list_page == 1)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_RuningModeDistanceTargetSetting_15KM();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                UI_Screen_RuningModeDistanceTargetSetting_HMARATHON();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
            
                UI_Screen_RuningModeDistanceTargetSetting_MARATHON();
            }
            break;
            default:
            break;
        }
    }
    else if(curr_list.curr_list_page == 2)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
            
                UI_Screen_RuningModeDistanceTargetSetting_50KM();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            break;
            default:
            break;
        }
    }

    
}


void UI_Screen_RuningModeDistanceTargetSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_RuningModeDistanceTargetSetting_Display();
    App_Lcd_TimerStart(10);

}

void UI_Screen_RuningModeDistanceTargetSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_RuningModeDistanceTargetSetting_Display();
    App_Lcd_TimerStart(10);

}

void UI_Screen_RuningModeDistanceTargetSetting_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeDistanceTargetSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_TargetSetting);
    UI_Screen_draw_Screen();

}


void UI_Screen_RuningModeDurationTargetSetting_Entry(void)
{

    int i = 0;    
    UI_Common_ScreenCleanListInfo();

    curr_list.total_count = ENUM_RMDURATION_TARGET_MAX;
    curr_list.total_list_page_count = (ENUM_RMDURATION_TARGET_MAX+2)/3;

    for(i = 0;i<ENUM_RMDURATION_TARGET_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    if(runningmode_setting_info.target_type == Enum_runningmode_setting_target_duration)
    {
        curr_list.icon_list[runningmode_setting_info.target_index]=(uint8_t *)radiobtn_checked_h;
    }

    curr_list.string_list[ENUM_RMDURATION_TARGET_20MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_20min;
    curr_list.string_list[ENUM_RMDURATION_TARGET_30MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_30min;
    curr_list.string_list[ENUM_RMDURATION_TARGET_60MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_60min;
    curr_list.string_list[ENUM_RMDURATION_TARGET_90MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_90min;
    curr_list.string_list[ENUM_RMDURATION_TARGET_120MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_120min;
    curr_list.string_list[ENUM_RMDURATION_TARGET_180MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_180min;
    curr_list.string_list[ENUM_RMDURATION_TARGET_240MIN]=(uint8_t *)gchinesefont_sportscene_target_duration_240min;

    UI_Screen_RuningModeDurationTargetSetting_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModeDurationTargetSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeDurationTargetSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeDurationTargetSetting_tpupslidehandle,
                                    UI_Screen_RuningModeDurationTargetSetting_tpdownslidehandle,
                                    UI_Screen_RuningModeDurationTargetSetting_tpleftslidehandle,
                                    UI_Screen_RuningModeDurationTargetSetting_tprightslidehandle);
    
}

void UI_Screen_RuningModeDurationTargetSetting_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_TargetSetting_Duration)
        return;

    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_RuningModeDurationTargetSetting_Exit(void)
{


}

void UI_Screen_RuningModeDurationTargetSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeDurationTargetSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeDurationTargetSetting_holdlongkeyhandle(void)
{
}


void UI_Screen_RuningModeDurationTargetSetting_20MIN(void)
{
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_duration;
    runningmode_setting_info.target_distance = 0;
    runningmode_setting_info.target_duration = 20*60;
    runningmode_setting_info.target_calorie = 0;

    runningmode_setting_info.target_index = ENUM_RMDURATION_TARGET_20MIN;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeDurationTargetSetting_30MIN(void)
{
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_duration;
    runningmode_setting_info.target_distance = 0;
    runningmode_setting_info.target_duration = 30*60;
    runningmode_setting_info.target_calorie = 0;

    runningmode_setting_info.target_index = ENUM_RMDURATION_TARGET_30MIN;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_RuningModeDurationTargetSetting_60MIN(void)
{
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_duration;
    runningmode_setting_info.target_distance = 0;
    runningmode_setting_info.target_duration = 60*60;
    runningmode_setting_info.target_calorie = 0;

    runningmode_setting_info.target_index = ENUM_RMDURATION_TARGET_60MIN;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_RuningModeDurationTargetSetting_90MIN(void)
{
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_duration;
    runningmode_setting_info.target_distance = 0;
    runningmode_setting_info.target_duration = 90*60;
    runningmode_setting_info.target_calorie = 0;

    runningmode_setting_info.target_index = ENUM_RMDURATION_TARGET_90MIN;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_RuningModeDurationTargetSetting_120MIN(void)
{
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_duration;
    runningmode_setting_info.target_distance = 0;
    runningmode_setting_info.target_duration = 120*60;
    runningmode_setting_info.target_calorie = 0;

    runningmode_setting_info.target_index = ENUM_RMDURATION_TARGET_120MIN;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_RuningModeDurationTargetSetting_180MIN(void)
{
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_duration;
    runningmode_setting_info.target_distance = 0;
    runningmode_setting_info.target_duration = 180*60;
    runningmode_setting_info.target_calorie = 0;

    runningmode_setting_info.target_index = ENUM_RMDURATION_TARGET_180MIN;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_RuningModeDurationTargetSetting_240MIN(void)
{
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_duration;
    runningmode_setting_info.target_distance = 0;
    runningmode_setting_info.target_duration = 240*60;
    runningmode_setting_info.target_calorie = 0;

    runningmode_setting_info.target_index = ENUM_RMDURATION_TARGET_240MIN;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();

}


void UI_Screen_RuningModeDurationTargetSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            UI_Screen_RuningModeDurationTargetSetting_20MIN();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Screen_RuningModeDurationTargetSetting_30MIN();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
            UI_Screen_RuningModeDurationTargetSetting_60MIN();
        }
        break;
        default:
        break;
        }
    }
    else if(curr_list.curr_list_page == 1)
    {
        switch(curr_range)
        {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            UI_Screen_RuningModeDurationTargetSetting_90MIN();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Screen_RuningModeDurationTargetSetting_120MIN();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
            UI_Screen_RuningModeDurationTargetSetting_180MIN();
        }
        break;
        default:
        break;
        }
    }
    else if(curr_list.curr_list_page == 2)
    {
        switch(curr_range)
        {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            UI_Screen_RuningModeDurationTargetSetting_240MIN();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:

        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:

        break;
        default:
        break;
        }
    }
    
}



void UI_Screen_RuningModeDurationTargetSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_RuningModeDurationTargetSetting_Display();
    App_Lcd_TimerStart(10);

}


void UI_Screen_RuningModeDurationTargetSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_RuningModeDurationTargetSetting_Display();
    App_Lcd_TimerStart(10);

}


void UI_Screen_RuningModeDurationTargetSetting_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeDurationTargetSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_TargetSetting);
    UI_Screen_draw_Screen();

}

    
void UI_Screen_RuningModeCalorieTargetSetting_Entry(void)
{

    int i = 0;

    UI_Common_ScreenCleanListInfo();

    curr_list.total_count = ENUM_RMCALORIE_TARGET_MAX;
    curr_list.total_list_page_count = (ENUM_RMCALORIE_TARGET_MAX+2)/3;

    for(i = 0;i<ENUM_RMCALORIE_TARGET_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    if(runningmode_setting_info.target_type == Enum_runningmode_setting_target_calorie)
    {
        curr_list.icon_list[runningmode_setting_info.target_index]=(uint8_t *)radiobtn_checked_h;
    }

    curr_list.string_list[ENUM_RMCALORIE_TARGET_100KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_100kcal;
    curr_list.string_list[ENUM_RMCALORIE_TARGET_200KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_200kcal;
    curr_list.string_list[ENUM_RMCALORIE_TARGET_300KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_300kcal;
    curr_list.string_list[ENUM_RMCALORIE_TARGET_500KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_500kcal;
    curr_list.string_list[ENUM_RMCALORIE_TARGET_800KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_800kcal;
    curr_list.string_list[ENUM_RMCALORIE_TARGET_1000KCAL]=(uint8_t *)gchinesefont_sportscene_target_calorie_1000kcal;

    UI_Screen_RuningModeCalorieTargetSetting_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModeCalorieTargetSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeCalorieTargetSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeCalorieTargetSetting_tpupslidehandle,
                                    UI_Screen_RuningModeCalorieTargetSetting_tpdownslidehandle,
                                    UI_Screen_RuningModeCalorieTargetSetting_tpleftslidehandle,
                                    UI_Screen_RuningModeCalorieTargetSetting_tprightslidehandle);
    
}

void UI_Screen_RuningModeCalorieTargetSetting_Display(void)
{
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_TargetSetting_Calorie)
        return;

    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_RuningModeCalorieTargetSetting_Exit(void)
{
}

void UI_Screen_RuningModeCalorieTargetSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeCalorieTargetSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeCalorieTargetSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_RuningModeCalorieTargetSetting_100KCAL(void)
{
    
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_calorie;
    runningmode_setting_info.target_distance = 0;
    runningmode_setting_info.target_duration = 0;
    runningmode_setting_info.target_calorie = 100;

    
    runningmode_setting_info.target_index = ENUM_RMCALORIE_TARGET_100KCAL;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeCalorieTargetSetting_200KCAL(void)
{
    
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_calorie;
    runningmode_setting_info.target_distance = 0;
    runningmode_setting_info.target_duration = 0;
    runningmode_setting_info.target_calorie = 200;

    runningmode_setting_info.target_index = ENUM_RMCALORIE_TARGET_200KCAL;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeCalorieTargetSetting_300KCAL(void)
{
    
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_calorie;
    runningmode_setting_info.target_distance = 0;
    runningmode_setting_info.target_duration = 0;
    runningmode_setting_info.target_calorie = 300;

    runningmode_setting_info.target_index = ENUM_RMCALORIE_TARGET_300KCAL;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeCalorieTargetSetting_500KCAL(void)
{
    
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_calorie;
    runningmode_setting_info.target_distance = 0;
    runningmode_setting_info.target_duration = 0;
    runningmode_setting_info.target_calorie = 500;

    runningmode_setting_info.target_index = ENUM_RMCALORIE_TARGET_500KCAL;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeCalorieTargetSetting_800KCAL(void)
{
    
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_calorie;
    runningmode_setting_info.target_distance = 0;
    runningmode_setting_info.target_duration = 0;
    runningmode_setting_info.target_calorie = 800;

    runningmode_setting_info.target_index = ENUM_RMCALORIE_TARGET_800KCAL;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeCalorieTargetSetting_1000KCAL(void)
{
    
    runningmode_setting_info.target_type = Enum_runningmode_setting_target_calorie;
    runningmode_setting_info.target_distance = 0;
    runningmode_setting_info.target_duration = 0;
    runningmode_setting_info.target_calorie = 1000;

    runningmode_setting_info.target_index = ENUM_RMCALORIE_TARGET_1000KCAL;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();
}


void UI_Screen_RuningModeCalorieTargetSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);
    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_RuningModeCalorieTargetSetting_100KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_RuningModeCalorieTargetSetting_200KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_RuningModeCalorieTargetSetting_300KCAL();
            }
            break;
            default:
            break;
        }
    }
    else if(curr_list.curr_list_page == 1)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_RuningModeCalorieTargetSetting_500KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_RuningModeCalorieTargetSetting_800KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_RuningModeCalorieTargetSetting_1000KCAL();
            }
            break;
            default:
            break;
        }
    }

    
}

void UI_Screen_RuningModeCalorieTargetSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_RuningModeCalorieTargetSetting_Display();
    App_Lcd_TimerStart(10);

}

void UI_Screen_RuningModeCalorieTargetSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_RuningModeCalorieTargetSetting_Display();
    App_Lcd_TimerStart(10);

}

void UI_Screen_RuningModeCalorieTargetSetting_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeCalorieTargetSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_TargetSetting);
    UI_Screen_draw_Screen();

}


void UI_Screen_RuningModeDistanceWarnSetting_Entry(void)
{
    int i = 0;
        
    UI_Common_ScreenCleanListInfo();

    curr_list.total_count = ENUM_RMDISTANCE_WARN_MAX;
    curr_list.total_list_page_count = (ENUM_RMDISTANCE_WARN_MAX+2)/3;

    for(i = 0;i<ENUM_RMDISTANCE_WARN_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    
    curr_list.icon_list[runningmode_setting_info.warn_distance_index]=(uint8_t *)radiobtn_checked_h;
    

    curr_list.string_list[ENUM_RMDISTANCE_WARN_OFF]=(uint8_t *)gchinesefont_sportscene_turnoff;
    curr_list.string_list[ENUM_RMDISTANCE_WARN_500M]=(uint8_t *)gchinesefont_sportscene_warn_distance_500m;
    curr_list.string_list[ENUM_RMDISTANCE_WARN_1KM]=(uint8_t *)gchinesefont_sportscene_warn_distance_1km;
    curr_list.string_list[ENUM_RMDISTANCE_WARN_2KM]=(uint8_t *)gchinesefont_sportscene_warn_distance_2km;
    curr_list.string_list[ENUM_RMDISTANCE_WARN_3KM]=(uint8_t *)gchinesefont_sportscene_warn_distance_3km;
    curr_list.string_list[ENUM_RMDISTANCE_WARN_5KM]=(uint8_t *)gchinesefont_sportscene_warn_distance_5km;
    
    UI_Screen_RuningModeDistanceWarnSetting_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModeDistanceWarnSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeDistanceWarnSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeDistanceWarnSetting_tpupslidehandle,
                                    UI_Screen_RuningModeDistanceWarnSetting_tpdownslidehandle,
                                    UI_Screen_RuningModeDistanceWarnSetting_tpleftslidehandle,
                                    UI_Screen_RuningModeDistanceWarnSetting_tprightslidehandle);


    
    
}

void UI_Screen_RuningModeDistanceWarnSetting_Display(void)
{
    
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_WarnSetting_Distance)
        return;

    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);

    
}

void UI_Screen_RuningModeDistanceWarnSetting_Exit(void)
{


}

void UI_Screen_RuningModeDistanceWarnSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeDistanceWarnSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeDistanceWarnSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_RuningModeDistanceWarnSetting_Off(void)
{

    runningmode_setting_info.warn_distance = 0;

    runningmode_setting_info.warn_distance_index = ENUM_RMDISTANCE_WARN_OFF;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}


void UI_Screen_RuningModeDistanceWarnSetting_500M(void)
{

    runningmode_setting_info.warn_distance = 500;

    runningmode_setting_info.warn_distance_index = ENUM_RMDISTANCE_WARN_500M;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeDistanceWarnSetting_1KM(void)
{

    runningmode_setting_info.warn_distance = 1000;

    runningmode_setting_info.warn_distance_index = ENUM_RMDISTANCE_WARN_1KM;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeDistanceWarnSetting_2KM(void)
{

    runningmode_setting_info.warn_distance = 2000;

    runningmode_setting_info.warn_distance_index = ENUM_RMDISTANCE_WARN_2KM;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeDistanceWarnSetting_3KM(void)
{

    runningmode_setting_info.warn_distance = 3000;

    runningmode_setting_info.warn_distance_index = ENUM_RMDISTANCE_WARN_3KM;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeDistanceWarnSetting_5KM(void)
{

    runningmode_setting_info.warn_distance = 5000;

    runningmode_setting_info.warn_distance_index = ENUM_RMDISTANCE_WARN_5KM;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeDistanceWarnSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_RuningModeDistanceWarnSetting_Off();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_RuningModeDistanceWarnSetting_500M();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_RuningModeDistanceWarnSetting_1KM();
            }
            break;
            default:
            break;
        }
    }
    else if(curr_list.curr_list_page == 1)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_RuningModeDistanceWarnSetting_2KM();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                UI_Screen_RuningModeDistanceWarnSetting_3KM();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
            
                UI_Screen_RuningModeDistanceWarnSetting_5KM();
            }
            break;
            default:
            break;
        }
    }

    
}


void UI_Screen_RuningModeDistanceWarnSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_RuningModeDistanceWarnSetting_Display();
    App_Lcd_TimerStart(10);

}

void UI_Screen_RuningModeDistanceWarnSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_RuningModeDistanceWarnSetting_Display();
    App_Lcd_TimerStart(10);

}

void UI_Screen_RuningModeDistanceWarnSetting_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeDistanceWarnSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();

}



void UI_Screen_RuningModeDurationWarnSetting_Entry(void)
{
    int i = 0;

    UI_Common_ScreenCleanListInfo();

    curr_list.total_count = ENUM_RMDURATION_WARN_MAX;
    curr_list.total_list_page_count = (ENUM_RMDURATION_WARN_MAX+2)/3;

    for(i = 0;i<ENUM_RMDURATION_WARN_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    curr_list.icon_list[runningmode_setting_info.warn_duration_index]=(uint8_t *)radiobtn_checked_h;

    curr_list.string_list[ENUM_RMDURATION_WARN_OFF]=(uint8_t *)gchinesefont_sportscene_turnoff;
    curr_list.string_list[ENUM_RMDURATION_WARN_5MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_5min;
    curr_list.string_list[ENUM_RMDURATION_WARN_10MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_10min;
    curr_list.string_list[ENUM_RMDURATION_WARN_15MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_15min;
    curr_list.string_list[ENUM_RMDURATION_WARN_20MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_20min;
    curr_list.string_list[ENUM_RMDURATION_WARN_30MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_30min;
    curr_list.string_list[ENUM_RMDURATION_WARN_60MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_60min;
    curr_list.string_list[ENUM_RMDURATION_WARN_90MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_90min;
    curr_list.string_list[ENUM_RMDURATION_WARN_120MIN]=(uint8_t *)gchinesefont_sportscene_warn_duration_120min;
    
    UI_Screen_RuningModeDurationWarnSetting_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModeDurationWarnSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeDurationWarnSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeDurationWarnSetting_tpupslidehandle,
                                    UI_Screen_RuningModeDurationWarnSetting_tpdownslidehandle,
                                    UI_Screen_RuningModeDurationWarnSetting_tpleftslidehandle,
                                    UI_Screen_RuningModeDurationWarnSetting_tprightslidehandle);


    
    
}

void UI_Screen_RuningModeDurationWarnSetting_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_WarnSetting_Duration)
        return;

    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);

    
}

void UI_Screen_RuningModeDurationWarnSetting_Exit(void)
{


}

void UI_Screen_RuningModeDurationWarnSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeDurationWarnSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeDurationWarnSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_RuningModeDurationWarnSetting_Off(void)
{

    runningmode_setting_info.warn_duration = 0;

    runningmode_setting_info.warn_duration_index = ENUM_RMDURATION_WARN_OFF;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}


void UI_Screen_RuningModeDurationWarnSetting_5MIN(void)
{

    runningmode_setting_info.warn_duration = 5*60;

    runningmode_setting_info.warn_duration_index = ENUM_RMDURATION_WARN_5MIN;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_RuningModeDurationWarnSetting_10MIN(void)
{

    runningmode_setting_info.warn_duration = 10*60;
    runningmode_setting_info.warn_duration_index = ENUM_RMDURATION_WARN_10MIN;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_RuningModeDurationWarnSetting_15MIN(void)
{

    runningmode_setting_info.warn_duration = 15*60;
    runningmode_setting_info.warn_duration_index = ENUM_RMDURATION_WARN_15MIN;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_RuningModeDurationWarnSetting_20MIN(void)
{

    runningmode_setting_info.warn_duration = 20*60;
    runningmode_setting_info.warn_duration_index = ENUM_RMDURATION_WARN_20MIN;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}




void UI_Screen_RuningModeDurationWarnSetting_30MIN(void)
{

    runningmode_setting_info.warn_duration = 30*60;
    runningmode_setting_info.warn_duration_index = ENUM_RMDURATION_WARN_30MIN;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_RuningModeDurationWarnSetting_60MIN(void)
{

    runningmode_setting_info.warn_duration = 60*60;
    runningmode_setting_info.warn_duration_index = ENUM_RMDURATION_WARN_60MIN;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_RuningModeDurationWarnSetting_90MIN(void)
{

    runningmode_setting_info.warn_duration = 90*60;
    runningmode_setting_info.warn_duration_index = ENUM_RMDURATION_WARN_90MIN;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}



void UI_Screen_RuningModeDurationWarnSetting_120MIN(void)
{

    runningmode_setting_info.warn_duration = 120*60;
    runningmode_setting_info.warn_duration_index = ENUM_RMDURATION_WARN_120MIN;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}




void UI_Screen_RuningModeDurationWarnSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_RuningModeDurationWarnSetting_Off();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_RuningModeDurationWarnSetting_5MIN();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_RuningModeDurationWarnSetting_10MIN();
            }
            break;
            default:
            break;
        }
    }
    else if(curr_list.curr_list_page == 1)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_RuningModeDurationWarnSetting_15MIN();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                UI_Screen_RuningModeDurationWarnSetting_20MIN();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
            
                UI_Screen_RuningModeDurationWarnSetting_30MIN();
            }
            break;
            default:
            break;
        }
    }
    else if(curr_list.curr_list_page == 2)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_RuningModeDurationWarnSetting_60MIN();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
            
                UI_Screen_RuningModeDurationWarnSetting_90MIN();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
            
                UI_Screen_RuningModeDurationWarnSetting_120MIN();
            }
            break;
            default:
            break;
        }
    }

    
}


void UI_Screen_RuningModeDurationWarnSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_RuningModeDurationWarnSetting_Display();
    App_Lcd_TimerStart(10);

}

void UI_Screen_RuningModeDurationWarnSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_RuningModeDurationWarnSetting_Display();
    App_Lcd_TimerStart(10);

}

void UI_Screen_RuningModeDurationWarnSetting_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeDurationWarnSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();

}


    
void UI_Screen_RuningModeCalorieWarnSetting_Entry(void)
{

    int i = 0;

    UI_Common_ScreenCleanListInfo();


    curr_list.total_count = ENUM_RMCALORIE_WARN_MAX;
    curr_list.total_list_page_count = ENUM_RMCALORIE_WARN_MAX/3+1;

    for(i = 0;i<ENUM_RMCALORIE_WARN_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    curr_list.icon_list[runningmode_setting_info.warn_calorie_index]=(uint8_t *)radiobtn_checked_h;

    curr_list.string_list[ENUM_RMCALORIE_WARN_OFF]=(uint8_t *)gchinesefont_sportscene_turnoff;
    curr_list.string_list[ENUM_RMCALORIE_WARN_50KCAL]=(uint8_t *)gchinesefont_sportscene_warn_calorie_50kcal;
    curr_list.string_list[ENUM_RMCALORIE_WARN_100KCAL]=(uint8_t *)gchinesefont_sportscene_warn_calorie_100kcal;
    curr_list.string_list[ENUM_RMCALORIE_WARN_150KCAL]=(uint8_t *)gchinesefont_sportscene_warn_calorie_150kcal;
    curr_list.string_list[ENUM_RMCALORIE_WARN_200KCAL]=(uint8_t *)gchinesefont_sportscene_warn_calorie_200kcal;

    UI_Screen_RuningModeCalorieWarnSetting_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModeCalorieWarnSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeCalorieWarnSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeCalorieWarnSetting_tpupslidehandle,
                                    UI_Screen_RuningModeCalorieWarnSetting_tpdownslidehandle,
                                    UI_Screen_RuningModeCalorieWarnSetting_tpleftslidehandle,
                                    UI_Screen_RuningModeCalorieWarnSetting_tprightslidehandle);
    
}


void UI_Screen_RuningModeCalorieWarnSetting_Display(void)
{
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_WarnSetting_Calorie)
        return;

    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_RuningModeCalorieWarnSetting_Exit(void)
{
}

void UI_Screen_RuningModeCalorieWarnSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeCalorieWarnSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeCalorieWarnSetting_holdlongkeyhandle(void)
{
}


void UI_Screen_RuningModeCalorieWarnSetting_Off(void)
{
    
    runningmode_setting_info.warn_calorie = 0;
    runningmode_setting_info.warn_calorie_index = ENUM_RMCALORIE_WARN_OFF;
    
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}


void UI_Screen_RuningModeCalorieWarnSetting_50KCAL(void)
{
    
    runningmode_setting_info.warn_calorie = 50;
    runningmode_setting_info.warn_calorie_index = ENUM_RMCALORIE_WARN_50KCAL;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeCalorieWarnSetting_100KCAL(void)
{
    
    runningmode_setting_info.warn_calorie = 100;
    runningmode_setting_info.warn_calorie_index = ENUM_RMCALORIE_WARN_100KCAL;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeCalorieWarnSetting_150KCAL(void)
{
    
    runningmode_setting_info.warn_calorie = 150;
    runningmode_setting_info.warn_calorie_index = ENUM_RMCALORIE_WARN_150KCAL;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}

void UI_Screen_RuningModeCalorieWarnSetting_200KCAL(void)
{
    
    runningmode_setting_info.warn_calorie = 200;
    runningmode_setting_info.warn_calorie_index = ENUM_RMCALORIE_WARN_200KCAL;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();
}


void UI_Screen_RuningModeCalorieWarnSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);
    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_RuningModeCalorieWarnSetting_Off();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_RuningModeCalorieWarnSetting_50KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Screen_RuningModeCalorieWarnSetting_100KCAL();
            }
            break;
            default:
            break;
        }
    }
    else if(curr_list.curr_list_page == 1)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                UI_Screen_RuningModeCalorieWarnSetting_150KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Screen_RuningModeCalorieWarnSetting_200KCAL();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            
            break;
            default:
            break;
        }
    }

    
}

void UI_Screen_RuningModeCalorieWarnSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;

    UI_Screen_RuningModeCalorieWarnSetting_Display();
    App_Lcd_TimerStart(10);

}

void UI_Screen_RuningModeCalorieWarnSetting_tpdownslidehandle(void)
{
    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    
    UI_Screen_RuningModeCalorieWarnSetting_Display();
    App_Lcd_TimerStart(10);

}

void UI_Screen_RuningModeCalorieWarnSetting_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeCalorieWarnSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Setting);
    UI_Screen_draw_Screen();

}



void UI_Screen_RuningModeHrWarnSetting_Entry(void)
{

    UI_Screen_RuningModeHrWarnSetting_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModeHrWarnSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeHrWarnSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeHrWarnSetting_tpupslidehandle,
                                    UI_Screen_RuningModeHrWarnSetting_tpdownslidehandle,
                                    UI_Screen_RuningModeHrWarnSetting_tpleftslidehandle,
                                    UI_Screen_RuningModeHrWarnSetting_tprightslidehandle);
    
}

void UI_Screen_RuningModeHrWarnSetting_Display(void)
{

    uint8_t* fontinfo = NULL;
    char info[16]={0};
    hrZoneRange_t hr_info;
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_WarnSetting_Heartrate)
        return;

    UI_Common_Clear_Screen(temp_ram);

    
    Scene_Cnm_HrZoneGet(&hr_info);

    if(runningmode_setting_info.heartrate_uplimit == 0)
    {        
        fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_warn_heartrate_upperlimit,fontinfo,NULL,0);
    }
    else
    {
        switch(runningmode_setting_info.heartrate_uplimit)
        {
            case 1:
                sprintf(info,"%d",hr_info.HrZone1);
            break;
            case 2:
                sprintf(info,"%d",hr_info.HrZone2);
            break;
            case 3:
                sprintf(info,"%d",hr_info.HrZone3);
            break;
            case 4:
                sprintf(info,"%d",hr_info.HrZone4);
            break;
            case 5:
                sprintf(info,"%d",hr_info.HrZone5);
            break;
            default:
            break;
        }

        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_warn_heartrate_upperlimit,(uint8_t*)info,NULL,1);
    }



    
    if(runningmode_setting_info.heartrate_lowlimit == 0)
    {        
        fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_warn_heartrate_lowerlimit,(uint8_t*)fontinfo,NULL,0);
    }
    else
    {
        switch(runningmode_setting_info.heartrate_lowlimit)
        {
            case 1:
                sprintf(info,"%d",hr_info.HrZone0);
            break;
            case 2:
                sprintf(info,"%d",hr_info.HrZone1);
            break;
            case 3:
                sprintf(info,"%d",hr_info.HrZone2);
            break;
            case 4:
                sprintf(info,"%d",hr_info.HrZone3);
            break;
            case 5:
                sprintf(info,"%d",hr_info.HrZone4);
            break;
            default:
            break;
        }

        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_warn_heartrate_lowerlimit,(uint8_t*)info,NULL,1);
        
    }

    UI_Display_Prepare(temp_ram);

}


void UI_Screen_RuningModeHrWarnSetting_Exit(void)
{

}

void UI_Screen_RuningModeHrWarnSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeHrWarnSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeHrWarnSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_RuningModeHrWarnSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Heartrate_Upperlimit);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Heartrate_Lowerlimit);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        
        break;
        default:
        break;
    }


    
}


void UI_Screen_RuningModeHrWarnSetting_tpupslidehandle(void)
{

}

void UI_Screen_RuningModeHrWarnSetting_tpdownslidehandle(void)
{
}

void UI_Screen_RuningModeHrWarnSetting_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeHrWarnSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();

}




void UI_Screen_RuningModeSpeedWarnSetting_Entry(void)
{

    UI_Screen_RuningModeSpeedWarnSetting_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModeSpeedWarnSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeSpeedWarnSetting_tpclickhandle);

    
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeSpeedWarnSetting_tpupslidehandle,
                                    UI_Screen_RuningModeSpeedWarnSetting_tpdownslidehandle,
                                    UI_Screen_RuningModeSpeedWarnSetting_tpleftslidehandle,
                                    UI_Screen_RuningModeSpeedWarnSetting_tprightslidehandle);
    
}

void UI_Screen_RuningModeSpeedWarnSetting_Display(void)
{

    uint8_t* fontinfo = NULL;
    char info[16]={0};
    hrZoneRange_t hr_info;
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_WarnSetting_Speed)
        return;

    UI_Common_Clear_Screen(temp_ram);

    Scene_Cnm_HrZoneGet(&hr_info);

    if(runningmode_setting_info.speed_uplimit_switch == 0)
    {        
        fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_warn_heartrate_minkm_max,(uint8_t*)fontinfo,NULL,0);
    }
    else
    {
        sprintf(info,"%02d'%02d\"",runningmode_setting_info.speed_uplimit/60,runningmode_setting_info.speed_uplimit%60);
        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_warn_heartrate_minkm_max,(uint8_t*)info,NULL,1);
    }

    if(runningmode_setting_info.speed_lowlimit_switch == 0)
    {        
        fontinfo = (uint8_t *)gchinesefont_sportscene_turnoff_s;
        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_warn_heartrate_minkm_min,(uint8_t*)fontinfo,NULL,0);
    }
    else
    {
        sprintf(info,"%02d'%02d\"",runningmode_setting_info.speed_lowlimit/60,runningmode_setting_info.speed_lowlimit%60);
        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_warn_heartrate_minkm_min,(uint8_t*)info,NULL,1);
    }
    
    UI_Display_Prepare(temp_ram);

}

void UI_Screen_RuningModeSpeedWarnSetting_Exit(void)
{


}


void UI_Screen_RuningModeSpeedWarnSetting_shortkeyhandle(void)
{

    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeSpeedWarnSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeSpeedWarnSetting_holdlongkeyhandle(void)
{
}

void UI_Screen_RuningModeSpeedWarnSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        {
            UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Speed_Upperlimit);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Speed_Lowerlimit);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        break;
        default:
        break;
    }


    
}


void UI_Screen_RuningModeSpeedWarnSetting_tpupslidehandle(void)
{
}

void UI_Screen_RuningModeSpeedWarnSetting_tpdownslidehandle(void)
{
}

void UI_Screen_RuningModeSpeedWarnSetting_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeSpeedWarnSetting_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);

    UI_Screen_draw_Screen();

}


//心率上限/下限设置列表
typedef enum
{
	ENUM_RMHRWARN_OFF = 0,
	ENUM_RMHRWARN_RANGE1,
	ENUM_RMHRWARN_RANGE2,
	ENUM_RMHRWARN_RANGE3,
	ENUM_RMHRWARN_RANGE4,
	ENUM_RMHRWARN_RANGE5,
	ENUM_RMHRWARN_MAX,
}app_runingmodehrwarn_enum;


void UI_Screen_RuningModeHrWarnUpperLimitSetting_Entry(void)
{

    int i = 0;
    hrZoneRange_t hr_info;
    
    Scene_Cnm_HrZoneGet(&hr_info);
    
    UI_Common_ScreenCleanListInfo();

    curr_list.curr_list_page = 0;
    curr_list.curr_list_highlight = 0;

    curr_list.total_count = ENUM_RMHRWARN_MAX;
    curr_list.total_list_page_count = (ENUM_RMHRWARN_MAX+2)/3;

    for(i = 0;i<ENUM_RMHRWARN_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    curr_list.icon_list[curr_list.curr_list_highlight]=(uint8_t *)radiobtn_checked_h;

    curr_list.string_list[ENUM_RMHRWARN_OFF]=(uint8_t *)gchinesefont_sportscene_turnoff;
    curr_list.string_list[ENUM_RMHRWARN_RANGE1]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range1;
    curr_list.string_list[ENUM_RMHRWARN_RANGE2]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range2;
    curr_list.string_list[ENUM_RMHRWARN_RANGE3]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range3;
    curr_list.string_list[ENUM_RMHRWARN_RANGE4]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range4;
    curr_list.string_list[ENUM_RMHRWARN_RANGE5]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range5;

        
    sprintf(curr_list.line2_content[1],"%d-%d",hr_info.HrZone0,hr_info.HrZone1);
    sprintf(curr_list.line2_content[2],"%d-%d",hr_info.HrZone1,hr_info.HrZone2);
    sprintf(curr_list.line2_content[3],"%d-%d",hr_info.HrZone2,hr_info.HrZone3);
    sprintf(curr_list.line2_content[4],"%d-%d",hr_info.HrZone3,hr_info.HrZone4);
    sprintf(curr_list.line2_content[5],"%d-%d",hr_info.HrZone4,hr_info.HrZone5);

    UI_Screen_RuningModeHrWarnLlimitSetting_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModeHrWarnLlimitSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeHrWarnUpperLimitSetting_tpclickhandle);
    
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeHrWarnLlimitSetting_tpupslidehandle,
                                    UI_Screen_RuningModeHrWarnLlimitSetting_tpdownslidehandle,
                                    UI_Screen_RuningModeHrWarnLlimitSetting_tpleftslidehandle,
                                    UI_Screen_RuningModeHrWarnLlimitSetting_tprightslidehandle);
    
}


void UI_Screen_RuningModeHrWarnLowerLimitSetting_Entry(void)
{

    int i = 0;
    
    hrZoneRange_t hr_info;
    
    Scene_Cnm_HrZoneGet(&hr_info);

    UI_Common_ScreenCleanListInfo();

    curr_list.curr_list_page = 0;
    curr_list.curr_list_highlight = 0;

    curr_list.total_count = ENUM_RMHRWARN_MAX;
    curr_list.total_list_page_count = (ENUM_RMHRWARN_MAX+2)/3;
    
    for(i = 0;i<ENUM_RMHRWARN_MAX;i++)
    {
         curr_list.icon_list[i] = (uint8_t *)radiobtn_unchecked_h;
    }
    
    curr_list.icon_list[curr_list.curr_list_highlight]=(uint8_t *)radiobtn_checked_h;

    curr_list.string_list[ENUM_RMHRWARN_OFF]=(uint8_t *)gchinesefont_sportscene_turnoff;
    curr_list.string_list[ENUM_RMHRWARN_RANGE1]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range1;
    curr_list.string_list[ENUM_RMHRWARN_RANGE2]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range2;
    curr_list.string_list[ENUM_RMHRWARN_RANGE3]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range3;
    curr_list.string_list[ENUM_RMHRWARN_RANGE4]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range4;
    curr_list.string_list[ENUM_RMHRWARN_RANGE5]=(uint8_t *)gchinesefont_sportscene_warn_heartrate_range5;

    sprintf(curr_list.line2_content[1],"%d-%d",hr_info.HrZone0,hr_info.HrZone1);
    sprintf(curr_list.line2_content[2],"%d-%d",hr_info.HrZone1,hr_info.HrZone2);
    sprintf(curr_list.line2_content[3],"%d-%d",hr_info.HrZone2,hr_info.HrZone3);
    sprintf(curr_list.line2_content[4],"%d-%d",hr_info.HrZone3,hr_info.HrZone4);
    sprintf(curr_list.line2_content[5],"%d-%d",hr_info.HrZone4,hr_info.HrZone5);

    UI_Screen_RuningModeHrWarnLlimitSetting_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModeHrWarnLlimitSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeHrWarnLowerLimitSetting_tpclickhandle);
    
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeHrWarnLlimitSetting_tpupslidehandle,
                                    UI_Screen_RuningModeHrWarnLlimitSetting_tpdownslidehandle,
                                    UI_Screen_RuningModeHrWarnLlimitSetting_tpleftslidehandle,
                                    UI_Screen_RuningModeHrWarnLlimitSetting_tprightslidehandle);
    
}

void UI_Screen_RuningModeHrWarnLlimitSetting_Display(void)
{

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if((UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_WarnSetting_Heartrate_Upperlimit)&&(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_WarnSetting_Heartrate_Lowerlimit))
        return;

    UI_Common_Clear_Screen(temp_ram);
    UI_Common_ShowIconList(temp_ram);
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_RuningModeHrWarnLlimitSetting_Exit(void)
{


}

void UI_Screen_RuningModeHrWarnLlimitSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
    UI_Screen_draw_Screen();

}


void UI_Screen_RuningModeHrWarnLlimitSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeHrWarnLlimitSetting_holdlongkeyhandle(void)
{
}


void UI_Screen_RuningModeHrWarnUpperLimitSetting_Off(void)
{
    
    runningmode_setting_info.heartrate_uplimit = 0;
    runningmode_setting_info.heartrate_uplimit_index = ENUM_RMHRWARN_OFF;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Heartrate);
    UI_Screen_draw_Screen();
}


void UI_Screen_RuningModeHrWarnUpperLimitSetting_Range1(void)
{

    runningmode_setting_info.heartrate_uplimit = 1;
    runningmode_setting_info.heartrate_uplimit_index = ENUM_RMHRWARN_RANGE1;

    if(runningmode_setting_info.heartrate_lowlimit!=0&&runningmode_setting_info.heartrate_lowlimit>runningmode_setting_info.heartrate_uplimit)
    {
        runningmode_setting_info.heartrate_uplimit = 0;
        runningmode_setting_info.heartrate_uplimit_index = ENUM_RMHRWARN_OFF;
        
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
    
}

void UI_Screen_RuningModeHrWarnUpperLimitSetting_Range2(void)
{

    runningmode_setting_info.heartrate_uplimit = 2;
    runningmode_setting_info.heartrate_uplimit_index = ENUM_RMHRWARN_RANGE2;

    if(runningmode_setting_info.heartrate_lowlimit!=0&&runningmode_setting_info.heartrate_lowlimit>runningmode_setting_info.heartrate_uplimit)
    {
        runningmode_setting_info.heartrate_uplimit = 0;
        runningmode_setting_info.heartrate_uplimit_index = ENUM_RMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
        
    }
}

void UI_Screen_RuningModeHrWarnUpperLimitSetting_Range3(void)
{

    runningmode_setting_info.heartrate_uplimit = 3;
    runningmode_setting_info.heartrate_uplimit_index = ENUM_RMHRWARN_RANGE3;
    
    if(runningmode_setting_info.heartrate_lowlimit!=0&&runningmode_setting_info.heartrate_lowlimit>runningmode_setting_info.heartrate_uplimit)
    {
        runningmode_setting_info.heartrate_uplimit = 0;
        runningmode_setting_info.heartrate_uplimit_index = ENUM_RMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
}

void UI_Screen_RuningModeHrWarnUpperLimitSetting_Range4(void)
{
    runningmode_setting_info.heartrate_uplimit = 4;
    runningmode_setting_info.heartrate_uplimit_index = ENUM_RMHRWARN_RANGE4;
    
    if(runningmode_setting_info.heartrate_lowlimit!=0&&runningmode_setting_info.heartrate_lowlimit>runningmode_setting_info.heartrate_uplimit)
    {

        runningmode_setting_info.heartrate_uplimit = 0;
        runningmode_setting_info.heartrate_uplimit_index = ENUM_RMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        runningmode_setting_info.heartrate_uplimit = 4;
        UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
}

void UI_Screen_RuningModeHrWarnUpperLimitSetting_Range5(void)
{
    runningmode_setting_info.heartrate_uplimit = 5;
    runningmode_setting_info.heartrate_uplimit_index = ENUM_RMHRWARN_RANGE5;
    
    if(runningmode_setting_info.heartrate_lowlimit!=0&&runningmode_setting_info.heartrate_lowlimit>runningmode_setting_info.heartrate_uplimit)
    {
        runningmode_setting_info.heartrate_uplimit = 0;
        runningmode_setting_info.heartrate_uplimit_index = ENUM_RMHRWARN_OFF;
    
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
}


void UI_Screen_RuningModeHrWarnLowerLimitSetting_Off(void)
{
    
    runningmode_setting_info.heartrate_lowlimit = 0;
    runningmode_setting_info.heartrate_lowlimit_index = ENUM_RMHRWARN_OFF;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Heartrate);
    UI_Screen_draw_Screen();
}



void UI_Screen_RuningModeHrWarnLowerLimitSetting_Range1(void)
{

    runningmode_setting_info.heartrate_lowlimit = 1;
    runningmode_setting_info.heartrate_lowlimit_index = ENUM_RMHRWARN_RANGE1;
    
    if(runningmode_setting_info.heartrate_uplimit!=0&&runningmode_setting_info.heartrate_lowlimit>runningmode_setting_info.heartrate_uplimit)
    {

        runningmode_setting_info.heartrate_lowlimit = 0;
        runningmode_setting_info.heartrate_lowlimit_index = ENUM_RMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
}

void UI_Screen_RuningModeHrWarnLowerLimitSetting_Range2(void)
{

    runningmode_setting_info.heartrate_lowlimit = 2;
    runningmode_setting_info.heartrate_lowlimit_index = ENUM_RMHRWARN_RANGE2;
    
    if(runningmode_setting_info.heartrate_uplimit!=0&&runningmode_setting_info.heartrate_lowlimit>runningmode_setting_info.heartrate_uplimit)
    {
        runningmode_setting_info.heartrate_lowlimit = 0;
        runningmode_setting_info.heartrate_lowlimit_index = ENUM_RMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
}

void UI_Screen_RuningModeHrWarnLowerLimitSetting_Range3(void)
{
    runningmode_setting_info.heartrate_lowlimit = 3;
    runningmode_setting_info.heartrate_lowlimit_index = ENUM_RMHRWARN_RANGE3;
    
    if(runningmode_setting_info.heartrate_uplimit!=0&&runningmode_setting_info.heartrate_lowlimit>runningmode_setting_info.heartrate_uplimit)
    {

        runningmode_setting_info.heartrate_lowlimit = 0;
        runningmode_setting_info.heartrate_lowlimit_index = ENUM_RMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
}

void UI_Screen_RuningModeHrWarnLowerLimitSetting_Range4(void)
{

    runningmode_setting_info.heartrate_lowlimit = 4;
    runningmode_setting_info.heartrate_lowlimit_index = ENUM_RMHRWARN_RANGE4;
    
    if(runningmode_setting_info.heartrate_uplimit!=0&&runningmode_setting_info.heartrate_lowlimit>runningmode_setting_info.heartrate_uplimit)
    {
        runningmode_setting_info.heartrate_lowlimit = 0;
        runningmode_setting_info.heartrate_lowlimit_index = ENUM_RMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
}

void UI_Screen_RuningModeHrWarnLowerLimitSetting_Range5(void)
{

    runningmode_setting_info.heartrate_lowlimit = 5;
    runningmode_setting_info.heartrate_lowlimit_index = ENUM_RMHRWARN_RANGE5;

    if(runningmode_setting_info.heartrate_uplimit!=0&&runningmode_setting_info.heartrate_lowlimit>runningmode_setting_info.heartrate_uplimit)
    {

        runningmode_setting_info.heartrate_lowlimit = 0;
        runningmode_setting_info.heartrate_lowlimit_index = ENUM_RMHRWARN_OFF;
        UI_Screen_Show_Warn_Screen_Error();
    }
    else
    {
        UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Heartrate);
        UI_Screen_draw_Screen();
    }
}

void UI_Screen_RuningModeHrWarnUpperLimitSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            UI_Screen_RuningModeHrWarnUpperLimitSetting_Off();
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            UI_Screen_RuningModeHrWarnUpperLimitSetting_Range1();
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            UI_Screen_RuningModeHrWarnUpperLimitSetting_Range2();
            break;
            default:
            break;
        }
    }
    else
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            UI_Screen_RuningModeHrWarnUpperLimitSetting_Range3();
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            UI_Screen_RuningModeHrWarnUpperLimitSetting_Range4();
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            UI_Screen_RuningModeHrWarnUpperLimitSetting_Range5();
            break;
            default:
            break;
        }
    }


    
}



void UI_Screen_RuningModeHrWarnLowerLimitSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    if(curr_list.curr_list_page == 0)
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            UI_Screen_RuningModeHrWarnLowerLimitSetting_Off();
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            UI_Screen_RuningModeHrWarnLowerLimitSetting_Range1();
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            UI_Screen_RuningModeHrWarnLowerLimitSetting_Range2();
            break;
            default:
            break;
        }
    }
    else
    {
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            UI_Screen_RuningModeHrWarnLowerLimitSetting_Range3();
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            UI_Screen_RuningModeHrWarnLowerLimitSetting_Range4();
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            UI_Screen_RuningModeHrWarnLowerLimitSetting_Range5();
            break;
            default:
            break;
        }
    }


    
}


void UI_Screen_RuningModeHrWarnLlimitSetting_tpupslidehandle(void)
{
    curr_list.curr_list_page++;
    
    if(curr_list.curr_list_page>=curr_list.total_list_page_count)
    curr_list.curr_list_page=0;


    UI_Screen_RuningModeHrWarnLlimitSetting_Display();
    UI_Screen_Redraw_Screen();
    

}

void UI_Screen_RuningModeHrWarnLlimitSetting_tpdownslidehandle(void)
{

    if(curr_list.curr_list_page==0)
    {
        curr_list.curr_list_page=curr_list.total_list_page_count-1;
    }
    else
    {
        curr_list.curr_list_page--;
    }
    

    UI_Screen_RuningModeHrWarnLlimitSetting_Display();
    UI_Screen_Redraw_Screen();


}

void UI_Screen_RuningModeHrWarnLlimitSetting_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeHrWarnLlimitSetting_tprightslidehandle(void)
{



    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting);
    UI_Screen_draw_Screen();

}





typedef struct 
{
    int temp_switch;
    int temp_curr_page;
    int temp_value1;
    int temp_value1_step;
    int temp_value1_min;
    int temp_value1_max;
    int temp_value2;
    int temp_value2_step;
    int temp_value2_min;
    int temp_value2_max;
    bool isloop;
}app_sportmode_speedwarn_s;

app_sportmode_speedwarn_s sportmode_speedwarn_info = {0x00};


//配速上限/下限设置状态
//runningmode_setting_info

void UI_Screen_RuningModeSpeedUpperLlimitSetting_Init()
{

    sportmode_speedwarn_info.temp_switch = runningmode_setting_info.speed_uplimit_switch;
    sportmode_speedwarn_info.temp_curr_page = 0;
    
    sportmode_speedwarn_info.temp_value1  = runningmode_setting_info.speed_uplimit/60;
    sportmode_speedwarn_info.temp_value1_step = 1;
    sportmode_speedwarn_info.temp_value1_min  = 0;
    sportmode_speedwarn_info.temp_value1_max = 99;
    
    sportmode_speedwarn_info.temp_value2  = runningmode_setting_info.speed_uplimit%60;
    sportmode_speedwarn_info.temp_value2_step = 10;
    sportmode_speedwarn_info.temp_value2_min  = 0;
    sportmode_speedwarn_info.temp_value2_max = 50;
    
    sportmode_speedwarn_info.isloop  =TRUE;
    
}

void UI_Screen_RuningModeSpeedUpperLlimitSetting_Save()
{


    runningmode_setting_info.speed_uplimit_switch = sportmode_speedwarn_info.temp_switch;
    runningmode_setting_info.speed_uplimit = sportmode_speedwarn_info.temp_value1*60 +sportmode_speedwarn_info.temp_value2;

}

void UI_Screen_RuningModeSpeedUpperLlimitSetting_Entry(void)
{   

    UI_Screen_RuningModeSpeedUpperLlimitSetting_Init();

    UI_Screen_RuningModeSpeedLlimitSetting_Display();
    
    UI_Common_set_key_handle(UI_Screen_RuningModeSpeedLlimitSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeSpeedUpperLlimitSetting_tpclickhandle);
    
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeSpeedLlimitSetting_tpupslidehandle,
                                    UI_Screen_RuningModeSpeedLlimitSetting_tpdownslidehandle,
                                    UI_Screen_RuningModeSpeedLlimitSetting_tpleftslidehandle,
                                    UI_Screen_RuningModeSpeedLlimitSetting_tprightslidehandle);
    
}

void UI_Screen_RuningModeSpeedLowerLlimitSetting_Init()
{

    sportmode_speedwarn_info.temp_switch = runningmode_setting_info.speed_lowlimit_switch;
    sportmode_speedwarn_info.temp_curr_page = 0;
    
    sportmode_speedwarn_info.temp_value1 = runningmode_setting_info.speed_lowlimit/60;
    sportmode_speedwarn_info.temp_value1_step = 1;
    sportmode_speedwarn_info.temp_value1_min  = 0;
    sportmode_speedwarn_info.temp_value1_max = 99;
    
    sportmode_speedwarn_info.temp_value2  = runningmode_setting_info.speed_lowlimit%60;
    sportmode_speedwarn_info.temp_value2_step = 10;
    sportmode_speedwarn_info.temp_value2_min  = 0;
    sportmode_speedwarn_info.temp_value2_max = 50;
    
    sportmode_speedwarn_info.isloop  = TRUE;

}

void UI_Screen_RuningModeSpeedLowerLlimitSetting_Save()
{


    runningmode_setting_info.speed_lowlimit_switch = sportmode_speedwarn_info.temp_switch;
    runningmode_setting_info.speed_lowlimit = sportmode_speedwarn_info.temp_value1*60 +sportmode_speedwarn_info.temp_value2;

}



void UI_Screen_RuningModeSpeedLowerLlimitSetting_Entry(void)
{


    UI_Screen_RuningModeSpeedLowerLlimitSetting_Init();

    UI_Screen_RuningModeSpeedLlimitSetting_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModeSpeedLlimitSetting_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeSpeedLowerLlimitSetting_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeSpeedLlimitSetting_tpupslidehandle,
                                    UI_Screen_RuningModeSpeedLlimitSetting_tpdownslidehandle,
                                    UI_Screen_RuningModeSpeedLlimitSetting_tpleftslidehandle,
                                    UI_Screen_RuningModeSpeedLlimitSetting_tprightslidehandle);
    
}

void UI_Screen_RuningModeSpeedLlimitSetting_Display(void)
{

    char content[8];
    int len;

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if((UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_WarnSetting_Speed_Lowerlimit)&&(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_WarnSetting_Speed_Upperlimit))
        return;

    UI_Common_Clear_Screen(temp_ram);

    if(sportmode_speedwarn_info.temp_curr_page == 0)
    {
    
        if(sportmode_speedwarn_info.temp_switch == 0)
        {
        
            UI_Common_AddBWsourcePic(temp_ram,64,76,(uint8_t*)iamge_bw_ullimit_off_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
        }
        else
        {

            sprintf(content,"%02d",sportmode_speedwarn_info.temp_value1);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,80,4,16,16,16,APP_COLOR_CYAN,content,len,ENUM_TEXTBOX_RIGHT);
            
            sprintf(content,"'%02d\"",sportmode_speedwarn_info.temp_value2);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,96,4,32,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            
            
            //line
            UI_Common_Draw_Hline(temp_ram,0,24,176,1,APP_COLOR_WHITE,TRUE);

            //arrow
            UI_Common_AddBWsourcePic(temp_ram,76,32,(uint8_t*)iamge_bw_ullimit_arrow_up_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            UI_Common_AddBWsourcePic(temp_ram,76,144,(uint8_t*)iamge_bw_ullimit_arrow_down_h,APP_COLOR_BLACK,APP_COLOR_WHITE);

            //switch
            UI_Common_AddBWsourcePic(temp_ram,4,76,(uint8_t*)iamge_bw_ullimit_on_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
            //frame
            UI_Common_AddBWsourcePic(temp_ram,55,68,(uint8_t*)iamge_bw_ullimit_frame_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            //frame
            UI_Common_AddBWsourcePic(temp_ram,124,68,(uint8_t*)iamge_bw_ullimit_frame_h,APP_COLOR_BLACK,APP_COLOR_WHITE);


            sprintf(content,"%02d",sportmode_speedwarn_info.temp_value1);
            UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,64,75,48,48,APP_COLOR_CYAN,content,2,48,ENUM_TEXTBOX_CENTER);
            
            sprintf(content,"%02d",sportmode_speedwarn_info.temp_value2);
            UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,138,82,36,36,APP_COLOR_WHITE,content,2,36,ENUM_TEXTBOX_CENTER);
        
        }
        
    
}
    else
    {

            sprintf(content,"%02d'",sportmode_speedwarn_info.temp_value1);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,56,4,24,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_RIGHT);
            
            sprintf(content,"%02d",sportmode_speedwarn_info.temp_value2);
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,80,4,16,16,16,APP_COLOR_CYAN,content,len,ENUM_TEXTBOX_LEFT);
            
            sprintf(content,"\"");
            len = strlen(content);
            UI_Common_Draw_AscStr_textbox(temp_ram,100,4,8,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
            
            //line
            UI_Common_Draw_Hline(temp_ram,0,24,176,1,APP_COLOR_WHITE,TRUE);

            //arrow
            UI_Common_AddBWsourcePic(temp_ram,76,32,(uint8_t*)iamge_bw_ullimit_arrow_up_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            UI_Common_AddBWsourcePic(temp_ram,76,144,(uint8_t*)iamge_bw_ullimit_arrow_down_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            
            //frame
            UI_Common_AddBWsourcePic_withoffsetx(temp_ram,0,68,(uint8_t*)iamge_bw_ullimit_frame_h,APP_COLOR_BLACK,APP_COLOR_WHITE,12);
            //frame
            UI_Common_AddBWsourcePic(temp_ram,55,68,(uint8_t*)iamge_bw_ullimit_frame_h,APP_COLOR_BLACK,APP_COLOR_WHITE);
            //OK
            UI_Common_AddBWsourcePic(temp_ram,124,76,(uint8_t*)iamge_bw_ullimit_ok_h,APP_COLOR_BLACK,APP_COLOR_CYAN);


            sprintf(content,"%02d",sportmode_speedwarn_info.temp_value1);
            UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,2,82,36,36,APP_COLOR_WHITE,content,2,36,ENUM_TEXTBOX_CENTER);
            sprintf(content,"%02d",sportmode_speedwarn_info.temp_value2);
            UI_Common_Draw_NumberImage_textbox_Bystringinfo(temp_ram,64,75,48,48,APP_COLOR_CYAN,content,2,48,ENUM_TEXTBOX_CENTER);
            
     }

        
    UI_Display_Prepare(temp_ram);
     
}

void UI_Screen_RuningModeSpeedLlimitSetting_Exit(void)
{


}

void UI_Screen_RuningModeSpeedLlimitSetting_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeSpeedLlimitSetting_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeSpeedLlimitSetting_holdlongkeyhandle(void)
{
}


typedef enum 
{
	Enum_Limitsetting_Invalid,
	Enum_Limitsetting_Button0,
	Enum_Limitsetting_Button1,
	Enum_Limitsetting_Button2,
	Enum_Limitsetting_Button3,
	Enum_Limitsetting_Button4,
	Enum_Limitsetting_Max,
}Enum_Limitsetting_Button;
    
Enum_Limitsetting_Button UI_Common_Limitsetting_Get_Button_Bypoint(int point_x,int point_y)
{

    Enum_Limitsetting_Button temp_button = Enum_Limitsetting_Invalid;

   if(point_y>=28 && point_y<= 60)
    {
        if(point_x>=64 && point_x<= 112)
        {
            temp_button=Enum_Limitsetting_Button1;
        }
    }
    else if(point_y >=76 && point_y<= 124)
    {
        if(point_x>=4 && point_x<= 52)
        {
            temp_button = Enum_Limitsetting_Button2;
        }
        else if(point_x>=64 && point_x<= 112)
        {
            temp_button = Enum_Limitsetting_Button0;
        }
        else if(point_x>=124 && point_x<= 172)
        {
            temp_button = Enum_Limitsetting_Button4;
        }

    }
    else if(point_y>=140 && point_y<= 172)
    {

        if(point_x>=64 && point_x<= 112)
        {
            temp_button=Enum_Limitsetting_Button3;
        }
    }

   return temp_button;

}



void UI_Screen_RuningModeSpeedUpperLlimitSetting_Button0(void)
{
    
    if(sportmode_speedwarn_info.temp_curr_page == 0)
    {
        if(sportmode_speedwarn_info.temp_switch == 0)
        {
            sportmode_speedwarn_info.temp_switch = 1;

            UI_Screen_RuningModeSpeedLlimitSetting_Display();
            UI_Screen_Redraw_Screen();
            
        
        }
      
    }

}

void UI_Screen_RuningModeSpeedUpperLlimitSetting_Button1(void)
{
        if(sportmode_speedwarn_info.temp_curr_page == 0)
        {
            if(sportmode_speedwarn_info.temp_switch == 1)
            {
                sportmode_speedwarn_info.temp_value1 = sportmode_speedwarn_info.temp_value1 + sportmode_speedwarn_info.temp_value1_step;

                if(sportmode_speedwarn_info.temp_value1 > sportmode_speedwarn_info.temp_value1_max)
                {
                    if(sportmode_speedwarn_info.isloop == 1)
                    {
                        sportmode_speedwarn_info.temp_value1 = sportmode_speedwarn_info.temp_value1_min;
                    }
                    else
                    {
                        sportmode_speedwarn_info.temp_value1 = sportmode_speedwarn_info.temp_value1_max;
                    
}
                }
             }
            
        }
        else if(sportmode_speedwarn_info.temp_curr_page == 1)
        {

            sportmode_speedwarn_info.temp_value2 = sportmode_speedwarn_info.temp_value2 + sportmode_speedwarn_info.temp_value2_step;
            
            if(sportmode_speedwarn_info.temp_value2 > sportmode_speedwarn_info.temp_value2_max)
            {
                if(sportmode_speedwarn_info.isloop == 1)
                {
                    sportmode_speedwarn_info.temp_value2 = sportmode_speedwarn_info.temp_value2_min;
                }
                else
                {
                    sportmode_speedwarn_info.temp_value2 = sportmode_speedwarn_info.temp_value2_max;
                
}
            }
            
        }
        
        UI_Screen_RuningModeSpeedLlimitSetting_Display();
        UI_Screen_Redraw_Screen();
        
}

void UI_Screen_RuningModeSpeedUpperLlimitSetting_Button2(void)
{
    
    if(sportmode_speedwarn_info.temp_curr_page == 0)
    {
        if(sportmode_speedwarn_info.temp_switch == 1)
        {
            sportmode_speedwarn_info.temp_switch = 0;
    
            UI_Screen_RuningModeSpeedLlimitSetting_Display();
            UI_Screen_Redraw_Screen();
        
        }
    }

}

void UI_Screen_RuningModeSpeedUpperLlimitSetting_Button3(void)
{

    if(sportmode_speedwarn_info.temp_curr_page == 0)
    {
        if(sportmode_speedwarn_info.temp_switch == 1)
        {
            sportmode_speedwarn_info.temp_value1 = sportmode_speedwarn_info.temp_value1 - sportmode_speedwarn_info.temp_value1_step;
    
            if(sportmode_speedwarn_info.temp_value1 < sportmode_speedwarn_info.temp_value1_min)
            {
                if(sportmode_speedwarn_info.isloop == 1)
                {
                    sportmode_speedwarn_info.temp_value1 = sportmode_speedwarn_info.temp_value1_max;
                }
                else
                {
                    sportmode_speedwarn_info.temp_value1 = sportmode_speedwarn_info.temp_value1_min;
                
}
            }
    
         }
        
    }
    else if(sportmode_speedwarn_info.temp_curr_page == 1)
    {
    
        sportmode_speedwarn_info.temp_value2 = sportmode_speedwarn_info.temp_value2 - sportmode_speedwarn_info.temp_value2_step;
        
        if(sportmode_speedwarn_info.temp_value2 < sportmode_speedwarn_info.temp_value2_min)
        {
            if(sportmode_speedwarn_info.isloop == 1)
            {
                sportmode_speedwarn_info.temp_value2 = sportmode_speedwarn_info.temp_value2_max;
            }
            else
            {
                sportmode_speedwarn_info.temp_value2 = sportmode_speedwarn_info.temp_value2_min;
            
}
        }
        
        
    }

    UI_Screen_RuningModeSpeedLlimitSetting_Display();
    UI_Screen_Redraw_Screen();
    
}

void UI_Screen_RuningModeSpeedUpperLlimitSetting_Button4(void)
{

    int32 temp_value;
    
    if(sportmode_speedwarn_info.temp_curr_page == 1)
    {
        if(sportmode_speedwarn_info.temp_value1!=0||sportmode_speedwarn_info.temp_value2!=0)
        {
            temp_value = sportmode_speedwarn_info.temp_value1*60+sportmode_speedwarn_info.temp_value2;
            
            if(runningmode_setting_info.speed_lowlimit_switch==1&&runningmode_setting_info.speed_lowlimit<=temp_value)
            {
                UI_Screen_Show_Warn_Screen_Error();
            }
            else
            {
                UI_Screen_RuningModeSpeedUpperLlimitSetting_Save();
                UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Speed);
                UI_Screen_draw_Screen();
            }
        }
        else
        {
            UI_Screen_Show_Warn_Screen_Error();
        }
    }
}

void UI_Screen_RuningModeSpeedUpperLlimitSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Limitsetting_Button button;
    button = UI_Common_Limitsetting_Get_Button_Bypoint(point_x,point_y);

    if(button == Enum_Limitsetting_Invalid)
        return;

    switch(button)
    {
        case Enum_Limitsetting_Button0:
            UI_Screen_RuningModeSpeedUpperLlimitSetting_Button0();
        break;
        case Enum_Limitsetting_Button1:
            UI_Screen_RuningModeSpeedUpperLlimitSetting_Button1();
        break;
        case Enum_Limitsetting_Button2:
            UI_Screen_RuningModeSpeedUpperLlimitSetting_Button2();
        break;
        case Enum_Limitsetting_Button3:
            UI_Screen_RuningModeSpeedUpperLlimitSetting_Button3();
        break;
        case Enum_Limitsetting_Button4:
            UI_Screen_RuningModeSpeedUpperLlimitSetting_Button4();
        break;
        default:
        break;
    }

}





void UI_Screen_RuningModeSpeedLowerLlimitSetting_Button0(void)
{
    if(sportmode_speedwarn_info.temp_curr_page == 0)
    {
        if(sportmode_speedwarn_info.temp_switch == 0)
        {
            sportmode_speedwarn_info.temp_switch = 1;

            UI_Screen_RuningModeSpeedLlimitSetting_Display();
            UI_Screen_Redraw_Screen();
        
        }
      
    }

}

void UI_Screen_RuningModeSpeedLowerLlimitSetting_Button1(void)
{        

        if(sportmode_speedwarn_info.temp_curr_page == 0)
        {
            if(sportmode_speedwarn_info.temp_switch == 1)
            {
                sportmode_speedwarn_info.temp_value1 = sportmode_speedwarn_info.temp_value1 + sportmode_speedwarn_info.temp_value1_step;

                if(sportmode_speedwarn_info.temp_value1 > sportmode_speedwarn_info.temp_value1_max)
                {
                    if(sportmode_speedwarn_info.isloop == 1)
                    {
                        sportmode_speedwarn_info.temp_value1 = sportmode_speedwarn_info.temp_value1_min;
                    }
                    else
                    {
                        sportmode_speedwarn_info.temp_value1 = sportmode_speedwarn_info.temp_value1_max;
                    
}
                }
             }
            
        }
        else if(sportmode_speedwarn_info.temp_curr_page == 1)
        {

            sportmode_speedwarn_info.temp_value2 = sportmode_speedwarn_info.temp_value2 + sportmode_speedwarn_info.temp_value2_step;
            
            if(sportmode_speedwarn_info.temp_value2 > sportmode_speedwarn_info.temp_value2_max)
            {
                if(sportmode_speedwarn_info.isloop == 1)
                {
                    sportmode_speedwarn_info.temp_value2 = sportmode_speedwarn_info.temp_value2_min;
                }
                else
                {
                    sportmode_speedwarn_info.temp_value2 = sportmode_speedwarn_info.temp_value2_max;
                
}
            }
            
        }
        
        UI_Screen_RuningModeSpeedLlimitSetting_Display();
        UI_Screen_Redraw_Screen();
        
}

void UI_Screen_RuningModeSpeedLowerLlimitSetting_Button2(void)
{

    if(sportmode_speedwarn_info.temp_curr_page == 0)
    {
        if(sportmode_speedwarn_info.temp_switch == 1)
        {
            sportmode_speedwarn_info.temp_switch = 0;
    
            UI_Screen_RuningModeSpeedLlimitSetting_Display();
            UI_Screen_Redraw_Screen();
        
        }
    }

}

void UI_Screen_RuningModeSpeedLowerLlimitSetting_Button3(void)
{
    
    if(sportmode_speedwarn_info.temp_curr_page == 0)
    {
        if(sportmode_speedwarn_info.temp_switch == 1)
        {
            sportmode_speedwarn_info.temp_value1 = sportmode_speedwarn_info.temp_value1 - sportmode_speedwarn_info.temp_value1_step;
    
            if(sportmode_speedwarn_info.temp_value1 < sportmode_speedwarn_info.temp_value1_min)
            {
                if(sportmode_speedwarn_info.isloop == 1)
                {
                    sportmode_speedwarn_info.temp_value1 = sportmode_speedwarn_info.temp_value1_max;
                }
                else
                {
                    sportmode_speedwarn_info.temp_value1 = sportmode_speedwarn_info.temp_value1_min;
                
}
            }
    
         }
        
    }
    else if(sportmode_speedwarn_info.temp_curr_page == 1)
    {
        sportmode_speedwarn_info.temp_value2 = sportmode_speedwarn_info.temp_value2 - sportmode_speedwarn_info.temp_value2_step;
        
        if(sportmode_speedwarn_info.temp_value2 < sportmode_speedwarn_info.temp_value2_min)
        {
            if(sportmode_speedwarn_info.isloop == 1)
            {
                sportmode_speedwarn_info.temp_value2 = sportmode_speedwarn_info.temp_value2_max;
            }
            else
            {
                sportmode_speedwarn_info.temp_value2 = sportmode_speedwarn_info.temp_value2_min;
            
}
        }
        
        
    }

    UI_Screen_RuningModeSpeedLlimitSetting_Display();
    UI_Screen_Redraw_Screen();
    

}

void UI_Screen_RuningModeSpeedLowerLlimitSetting_Button4(void)
{

    int32 temp_value;
    
    if(sportmode_speedwarn_info.temp_curr_page == 1)
    {
        if(sportmode_speedwarn_info.temp_value1!=0||sportmode_speedwarn_info.temp_value2!=0)
        {
            temp_value = sportmode_speedwarn_info.temp_value1*60+sportmode_speedwarn_info.temp_value2;
            
            if(runningmode_setting_info.speed_uplimit_switch==1&&runningmode_setting_info.speed_uplimit>=temp_value)
            {
                UI_Screen_Show_Warn_Screen_Error();
            }
            else
            {
        
                UI_Screen_RuningModeSpeedLowerLlimitSetting_Save();
                UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Speed);
                UI_Screen_draw_Screen();
            }
        }
        else
        {
            UI_Screen_Show_Warn_Screen_Error();
        }
    }
}


void UI_Screen_RuningModeSpeedLowerLlimitSetting_tpclickhandle(int point_x,int point_y)
{

    Enum_Limitsetting_Button button;
    button = UI_Common_Limitsetting_Get_Button_Bypoint(point_x,point_y);

    RTT_DEBUG_printf(0,"button = %d",button);

    if(button == Enum_Limitsetting_Invalid)
        return;

    switch(button)
    {
        case Enum_Limitsetting_Button0:
            UI_Screen_RuningModeSpeedLowerLlimitSetting_Button0();
        break;
        case Enum_Limitsetting_Button1:
            UI_Screen_RuningModeSpeedLowerLlimitSetting_Button1();
        break;
        case Enum_Limitsetting_Button2:
            UI_Screen_RuningModeSpeedLowerLlimitSetting_Button2();
        break;
        case Enum_Limitsetting_Button3:
            UI_Screen_RuningModeSpeedLowerLlimitSetting_Button3();
        break;
        case Enum_Limitsetting_Button4:
            UI_Screen_RuningModeSpeedLowerLlimitSetting_Button4();
        break;
        default:
        break;
    }

}


void UI_Screen_RuningModeSpeedLlimitSetting_tpupslidehandle(void)
{
}

void UI_Screen_RuningModeSpeedLlimitSetting_tpdownslidehandle(void)
{
}

void UI_Screen_RuningModeSpeedLlimitSetting_tpleftslidehandle(void)
{
    if(sportmode_speedwarn_info.temp_curr_page == 0)
    {
        sportmode_speedwarn_info.temp_curr_page = 1;
        UI_Screen_RuningModeSpeedLlimitSetting_Display();
        UI_Screen_Redraw_Screen();
    }

}

void UI_Screen_RuningModeSpeedLlimitSetting_tprightslidehandle(void)
{

    if(sportmode_speedwarn_info.temp_curr_page == 0)
    {
        runningmode_setting_info.speed_uplimit_switch = sportmode_speedwarn_info.temp_switch;
        UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_WarnSetting_Speed);
        UI_Screen_draw_Screen();
    }
    else
    {
        sportmode_speedwarn_info.temp_curr_page = 0;
        UI_Screen_RuningModeSpeedLlimitSetting_Display();
        UI_Screen_Redraw_Screen();
        
    }

    

}

//page 1 page 2

static int detail_page_number = 0;

void UI_Screen_RuningModeDetail_Goback()
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Datadetail);
    UI_Set_Curr_ScreenID(Common_Screen_MainID_Running);
    UI_Screen_draw_Screen();

}


void  UI_Screen_RuningModeDetail_Timerhandle(void)
{

    UI_Screen_RuningModeDetail_Display();

    UI_Common_set_timer_handle(UI_Screen_RuningModeDetail_Timerhandle);
    App_Lcd_TimerStart(1000);

}


void UI_Screen_RuningModeDetail_Entry(void)
{   
        
    UI_Screen_RuningModeDetail_Timerhandle();

    UI_Common_set_key_handle(UI_Screen_RuningModeDetail_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeDetail_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeDetail_tpupslidehandle,
                                    UI_Screen_RuningModeDetail_tpdownslidehandle,
                                    UI_Screen_RuningModeDetail_tpleftslidehandle,
                                    UI_Screen_RuningModeDetail_tprightslidehandle);
    
    
}

void UI_Screen_RuningModeDetail_Display(void)
{

    runningInfo_t curr_info;
    int temp_h,temp_m,temp_s;
    char string_content[16];
    int string_len;
    float temp_f;
    int temp_a,temp_b;
    uint8_t *fontinfo;
	MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
    
    SysTimeType_e curr_type = App_Var_SysTimeTypeGet();
    ui_common_time_12hour_s curr_12hour_time = {0};

    
    MID_PRESS_PARA_T* curr_press_info;
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_Datadetail)
        return;

    UI_Common_Clear_Screen(temp_ram);

    Scene_Run_InfoGet(&curr_info);

    if(detail_page_number==0)
    {
    
        UI_Common_Show_SportModeDataDetailBG(temp_ram,0,1,0);
        //(uint8_t *lcdram,int x,int y,int width,int height,uint8_t *title,char* data,int datalen,uint8_t font_color)

        temp_h = curr_info.RecordData.Duration/3600;
        temp_m = curr_info.RecordData.Duration%3600/60;
        temp_s = curr_info.RecordData.Duration%60;

        sprintf(string_content,"%02d:%02d:%02d",temp_h,temp_m,temp_s);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,0,176,58,gchinesefont_sportscene_datadetail_timing,string_content,string_len,APP_COLOR_WHITE);
        
        temp_f = (float)curr_info.RecordData.Distance/1000;
        //memset(string_content,0,16);
        sprintf(string_content,"%0.2f",temp_f);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,59,87,58,gchinesefont_sportscene_datadetail_distance,string_content,string_len,APP_COLOR_WHITE);


        temp_a = curr_info.RealTimeData.Pace/60;
        temp_b = curr_info.RealTimeData.Pace%60; 
        sprintf(string_content,"%d'%2d\"",temp_a,temp_b);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,88,59,87,58,gchinesefont_sportscene_datadetail_minkm,string_content,string_len,APP_COLOR_WHITE);

        switch(curr_info.HrZone)
        {
            case HR_ZONE_0:
                fontinfo = (uint8_t *)gchinesefont_sportscene_datadetail_nothing;
                break;
            case HR_ZONE_1:
                fontinfo = (uint8_t *)gchinesefont_sportscene_datadetail_warmup;
            break;
            case HR_ZONE_2:
                fontinfo = (uint8_t *)gchinesefont_sportscene_datadetail_fatburning;
            break;
            case HR_ZONE_3:
                fontinfo = (uint8_t *)gchinesefont_sportscene_datadetail_aerobicendurance;
            break;
            case HR_ZONE_4:
                fontinfo = (uint8_t *)gchinesefont_sportscene_datadetail_physicalstrengthen;
            break;
            case HR_ZONE_5:
                fontinfo = (uint8_t *)gchinesefont_sportscene_datadetail_anaerobicendurance;
            break;
            default:
                fontinfo = (uint8_t *)gchinesefont_sportscene_datadetail_nothing;
                break;
            
        }

        if(curr_info.RealTimeData.HR == 0)
        {
            sprintf(string_content,"--");
        }
        else
        {
            sprintf(string_content,"%d",curr_info.RealTimeData.HR);
        }
        
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_HrData(temp_ram,0,118,176,58,fontinfo,string_content,string_len,APP_COLOR_WHITE,curr_info.HrZone);
        
    }
    else
    {
        UI_Common_Show_SportModeDataDetailBG(temp_ram,1,1,1);
        //(uint8_t *lcdram,int x,int y,int width,int height,uint8_t *title,char* data,int datalen,uint8_t font_color)
        
        sprintf(string_content,"%d",curr_info.RecordData.Step);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,0,87,58,gchinesefont_sportscene_datadetail_stepnumber,string_content,string_len,APP_COLOR_WHITE);

        temp_f = (float)curr_info.RealTimeData.Stride/100;
        //memset(string_content,0,16);
        sprintf(string_content,"%0.2f",temp_f);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,89,0,87,58,gchinesefont_sportscene_datadetail_stride,string_content,string_len,APP_COLOR_WHITE);


        sprintf(string_content,"%d",curr_info.RealTimeData.Freq);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,59,87,58,gchinesefont_sportscene_datadetail_stridefrequency,string_content,string_len,APP_COLOR_WHITE);

        sprintf(string_content,"%d",curr_info.RecordData.Calorie);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,89,59,87,58,gchinesefont_sportscene_datadetail_calorie,string_content,string_len,APP_COLOR_WHITE);

        if(curr_type == SYS_TIME_24_TYPE)
        {
            sprintf(string_content,"%d:%2d",lMidRTC->RTC.hour,lMidRTC->RTC.min);
            string_len = strlen(string_content);
            UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,118,87,58,gchinesefont_sportscene_datadetail_currenttime,string_content,string_len,APP_COLOR_WHITE);
            
        }
        else
        {
        
            UI_Common_Get_Time_12hour(&curr_12hour_time);
            
            //14-80
            if(curr_12hour_time.is_am ==1)
            {
                sprintf(string_content,"%d:%02d AM",curr_12hour_time.hour,curr_12hour_time.min);
            }
            else
            {
                sprintf(string_content,"%d:%02d PM",curr_12hour_time.hour,curr_12hour_time.min);
            }
            
            string_len = strlen(string_content);
            UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,0,118,87,58,gchinesefont_sportscene_datadetail_currenttime,string_content,string_len,APP_COLOR_WHITE);
        }

		curr_press_info = Mid_Press_ParamPGet();

        temp_f = (float)curr_press_info->LastTemp/100;
        sprintf(string_content,"%0.1fC",temp_f);
        string_len = strlen(string_content);
        UI_Common_Show_SportModeDataDetail_CommonData(temp_ram,89,118,87,58,gchinesefont_sportscene_datadetail_temperature,string_content,string_len,APP_COLOR_WHITE);

    }

    UI_Display_Prepare(temp_ram);
    
}



void UI_Screen_RuningModeDetail_Exit(void)
{
    detail_page_number = 0;
}


void UI_Screen_RuningModeDetail_shortkeyhandle(void)
{

    UI_Screen_RuningModeDetail_Exit();
    UI_Common_Shake();
    //暂停跑步模式
    Scene_Run_Pause();
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Pause);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeDetail_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeDetail_holdlongkeyhandle(void)
{
}

void UI_Screen_RuningModeDetail_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        break;
        default:
        break;
    }

    
}


void UI_Screen_RuningModeDetail_tpupslidehandle(void)
{

    if(detail_page_number == 0)
        detail_page_number =1;
    else
        detail_page_number =0;
    
    //UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Datadetail);
    //UI_Screen_draw_Screen();
    UI_Screen_RuningModeDetail_Display();
    UI_Screen_Redraw_Screen();
    

}

void UI_Screen_RuningModeDetail_tpdownslidehandle(void)
{

    if(detail_page_number == 0)
        detail_page_number =1;
    else
        detail_page_number =0;
    
    UI_Screen_RuningModeDetail_Display();
    UI_Screen_Redraw_Screen();

}

void UI_Screen_RuningModeDetail_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeDetail_tprightslidehandle(void)
{

    //UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
    //记录历史状态
    UI_Set_Go_back_handle(UI_Screen_RuningModeDetail_Goback);
    
    UI_Screen_RuningModeDetail_Exit();
    
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}



void UI_Screen_RuningModePause_Timerhandle(void)
{

    UI_Screen_RuningModePause_Exit();

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Menu);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModePause_Entry(void)
{   

    UI_Screen_RuningModePause_Display();

    UI_Common_set_timer_handle(UI_Screen_RuningModePause_Timerhandle);
    App_Lcd_TimerStart(500);

    UI_Common_clean_tp_handle();
    UI_Common_clean_key_handle();
    
}

void UI_Screen_RuningModePause_Display(void)
{
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_Pause)
        return;

    UI_Common_Clear_Screen(temp_ram);
    UI_Common_Show_PlayPause(temp_ram,1);
    UI_Display_Prepare(temp_ram);

    
}

void UI_Screen_RuningModePause_Exit(void)
{
    App_Lcd_TimerStop();
}


void UI_Screen_RuningModeContinue_Timerhandle(void)
{

        UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Datadetail);
        UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeContinue_Entry(void)
{   

    UI_Screen_RuningModeContinue_Display();
    UI_Common_set_timer_handle(UI_Screen_RuningModeContinue_Timerhandle);
    App_Lcd_TimerStart(500);

    UI_Common_clean_tp_handle();
    UI_Common_clean_key_handle();
    
}

void UI_Screen_RuningModeContinue_Display(void)
{
    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_Continue)
        return;

    UI_Common_Clear_Screen(temp_ram);
    UI_Common_Show_PlayPause(temp_ram,0);
    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_RuningModeContinue_Exit(void)
{


}


//static int menu_page_number = 0;


void UI_Screen_RuningModeMenu_Entry(void)
{   

    UI_Screen_RuningModeMenu_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModeMenu_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeMenu_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeMenu_tpupslidehandle,
                                    UI_Screen_RuningModeMenu_tpdownslidehandle,
                                    UI_Screen_RuningModeMenu_tpleftslidehandle,
                                    UI_Screen_RuningModeMenu_tprightslidehandle);
}

void UI_Screen_RuningModeMenu_Display(void)
{
    runningInfo_t curr_info;
    char string_distance[16];
    int len_distance;
    char string_duration[16];
    int len_duration;
    int temp_h,temp_m,temp_s;
    float temp_f;

    uint8_t *temp_ram = UI_Display_Get_Tempram();

    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_Menu)
        return;

    UI_Common_Clear_Screen(temp_ram);
    

    #if 0
    if(menu_page_number == 0)
    {
        Scene_Run_InfoGet(&curr_info);

        temp_f = (float)curr_info.RecordData.Distance/1000;
        //memset(string_content,0,16);
        sprintf(string_distance,"%0.2f",temp_f);
        len_distance = strlen(string_distance);

        
        temp_h = curr_info.RecordData.Duration/3600;
        temp_m = curr_info.RecordData.Duration%3600/60;
        temp_s = curr_info.RecordData.Duration%60;
        
        sprintf(string_duration,"%2d:%2d:%2d",temp_h,temp_m,temp_s);
        len_duration = strlen(string_duration);

        UI_Common_Show_ModeMenuHeadBar(lcdram,0,0,string_distance,len_distance,string_duration,len_duration);

        UI_Common_List_RarrowDoubleline(lcdram,0,59,(uint8_t *)gchinesefont_sportscene_datadetail_continue,NULL,0);
        UI_Common_List_RarrowDoubleline(lcdram,0,118,(uint8_t *)gchinesefont_sportscene_datadetail_complete,NULL,0);
    }
    else
    {
        UI_Common_List_RarrowDoubleline(lcdram,0,0,(uint8_t *)gchinesefont_sportscene_datadetail_abandon,NULL,0);
        UI_Common_List_RarrowDoubleline(lcdram,0,59,(uint8_t *)gchinesefont_sportscene_datadetail_keeponrunning,NULL,0);
    }
    #else
    
    Scene_Run_InfoGet(&curr_info);
    
    temp_f = (float)curr_info.RecordData.Distance/1000;
    //memset(string_content,0,16);
    sprintf(string_distance,"%0.2f",temp_f);
    len_distance = strlen(string_distance);
    
    
    temp_h = curr_info.RecordData.Duration/3600;
    temp_m = curr_info.RecordData.Duration%3600/60;
    temp_s = curr_info.RecordData.Duration%60;
    
    sprintf(string_duration,"%2d:%2d:%2d",temp_h,temp_m,temp_s);
    len_duration = strlen(string_duration);
    
    UI_Common_Show_ModeMenuHeadBar(temp_ram,0,0,string_distance,len_distance,string_duration,len_duration);
    
    UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_datadetail_continue,NULL,NULL,0);
    UI_Common_List_RarrowDoubleline(temp_ram,0,118,(uint8_t *)gchinesefont_sportscene_datadetail_complete,NULL,NULL,0);
    
    #endif

    UI_Display_Prepare(temp_ram);

}

void UI_Screen_RuningModeMenu_Exit(void)
{

    //menu_page_number = 0;

}

void UI_Screen_RuningModeMenu_shortkeyhandle(void)
{

    UI_Screen_RuningModeMenu_Exit();
    UI_Common_Shake();
    //继续跑步模式
    Scene_Run_Continue();
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Continue);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeMenu_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeMenu_holdlongkeyhandle(void)
{
}

void UI_Screen_RuningModeMenu_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);


    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Screen_RuningModeMenu_Exit();
            UI_Common_Shake();
            //继续跑步模式
            Scene_Run_Continue();
            UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Continue);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
            UI_Screen_RuningModeMenu_Exit();
            UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_CompleteMenu);
            UI_Screen_draw_Screen();
        }
        break;
        default:
        break;
    }
        
    
}


void UI_Screen_RuningModeMenu_tpupslidehandle(void)
{
    #if 0
    if(menu_page_number == 0)
        menu_page_number =1;
    else
        menu_page_number =0;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Menu);
    UI_Screen_draw_Screen();
    #endif

}

void UI_Screen_RuningModeMenu_tpdownslidehandle(void)
{
    #if 0
    if(menu_page_number == 0)
        menu_page_number =1;
    else
        menu_page_number =0;
    
    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Menu);
    UI_Screen_draw_Screen();
    #endif

}

void UI_Screen_RuningModeMenu_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeMenu_tprightslidehandle(void)
{

    #if 0
        UI_Screen_RuningModeMenu_Exit();
        UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Prepare);
        UI_Screen_draw_Screen();
    #endif

}


void UI_Screen_RuningModeCompleteMenu_Entry(void)
{   

    UI_Screen_RuningModeCompleteMenu_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModeCompleteMenu_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeCompleteMenu_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeCompleteMenu_tpupslidehandle,
                                    UI_Screen_RuningModeCompleteMenu_tpdownslidehandle,
                                    UI_Screen_RuningModeCompleteMenu_tpleftslidehandle,
                                    UI_Screen_RuningModeCompleteMenu_tprightslidehandle);
}

void UI_Screen_RuningModeCompleteMenu_Display(void)
{

        uint8_t *temp_ram = UI_Display_Get_Tempram();
        
        if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_CompleteMenu)
            return;
        
        UI_Common_Clear_Screen(temp_ram);

        #if 0

        runningInfo_t curr_info;
        char string_distance[16];
        int len_distance;
        char string_duration[16];
        int len_duration;
        int temp_h,temp_m,temp_s;
        float temp_f;

        Scene_Run_InfoGet(&curr_info);

        temp_f = (float)curr_info.RecordData.Distance/1000;
        //memset(string_content,0,16);
        sprintf(string_distance,"%0.2f",temp_f);
        len_distance = strlen(string_distance);

        
        temp_h = curr_info.RecordData.Duration/3600;
        temp_m = curr_info.RecordData.Duration%3600/60;
        temp_s = curr_info.RecordData.Duration%60;
        
        sprintf(string_duration,"%2d:%2d:%2d",temp_h,temp_m,temp_s);
        len_duration = strlen(string_duration);

        UI_Common_Show_ModeMenuHeadBar(lcdram,0,0,string_distance,len_distance,string_duration,len_duration);
        
        UI_Common_List_RarrowDoubleline(lcdram,0,59,(uint8_t *)gchinesefont_sportscene_datadetail_datadetail,NULL,0);
        UI_Common_List_RarrowDoubleline(lcdram,0,118,(uint8_t *)gchinesefont_sportscene_datadetail_exit,NULL,0);
        #else
        UI_Common_List_RarrowDoubleline(temp_ram,0,0,(uint8_t *)gchinesefont_sportscene_save,NULL,NULL,0);
        UI_Common_List_RarrowDoubleline(temp_ram,0,59,(uint8_t *)gchinesefont_sportscene_abandon_confirm_yes,NULL,NULL,0);
        #endif

        UI_Display_Prepare(temp_ram);
    

}

void UI_Screen_RuningModeCompleteMenu_Exit(void)
{


}
void UI_Screen_RuningModeCompleteMenu_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Menu);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeCompleteMenu_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeCompleteMenu_holdlongkeyhandle(void)
{
}

void UI_Screen_RuningModeCompleteMenu_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    #if 0
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_History);
                UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            {
                UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
                UI_Screen_draw_Screen();
            }
            break;
            default:
            break;
        }
    #else
        switch(curr_range)
        {
            case Enum_Common_ListScreen_Tprange_0:
            case Enum_Common_ListScreen_Tprange_1:
            {
                    UI_Common_Shake();
                    //关闭跑步模式
                    Scene_Run_Disable();
                    //退出模式，重置大休眠状态
                    UI_Commom_Set_Allow_Lockstate2(1);
                    
                    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_History);
                    UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_2:
            case Enum_Common_ListScreen_Tprange_3:
            {
                    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Abandon);
                    UI_Screen_draw_Screen();
            }
            break;
            case Enum_Common_ListScreen_Tprange_4:
            case Enum_Common_ListScreen_Tprange_5:
            
            break;
            default:
            break;
        }
    #endif

    
    
}


void UI_Screen_RuningModeCompleteMenu_tpupslidehandle(void)
{
}

void UI_Screen_RuningModeCompleteMenu_tpdownslidehandle(void)
{
}

void UI_Screen_RuningModeCompleteMenu_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeCompleteMenu_tprightslidehandle(void)
{

}

void UI_Screen_RuningModeAbandon_Entry(void)
{   

    UI_Screen_RuningModeAbandon_Display();

    UI_Common_set_key_handle(UI_Screen_RuningModeAbandon_shortkeyhandle,NULL,NULL);

    UI_Common_set_tp_click_handle(UI_Screen_RuningModeAbandon_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeAbandon_tpupslidehandle,
                                    UI_Screen_RuningModeAbandon_tpdownslidehandle,
                                    UI_Screen_RuningModeAbandon_tpleftslidehandle,
                                    UI_Screen_RuningModeAbandon_tprightslidehandle);
}

void UI_Screen_RuningModeAbandon_Display(void)
{

    
    uint8_t *temp_ram = UI_Display_Get_Tempram();
    
    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_Abandon)
        return;
    
    UI_Common_Clear_Screen(temp_ram);
    
    UI_Common_AddBWsourcePic(temp_ram,4,63,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_CYAN);
    //UI_Common_AddPic(lcdram,4,122,(uint8_t*)BtnFullRed_h);
    UI_Common_AddBWsourcePic(temp_ram,4,122,(uint8_t*)iamge_bw_BtnFull_h,APP_COLOR_BLACK,APP_COLOR_RED);
    
    UI_Common_Draw_FontStr_textbox(temp_ram,0,0,176,58,(uint8_t *)gchinesefont_sportscene_abandon_confirm,APP_COLOR_WHITE,APP_COLOR_BLACK);
    
    UI_Common_Draw_FontStr_textbox(temp_ram,0,59,176,58,(uint8_t *)gchinesefont_sportscene_abandon_confirm_no,APP_COLOR_BLACK,APP_COLOR_CYAN);
    UI_Common_Draw_FontStr_textbox(temp_ram,0,118,176,58,(uint8_t *)gchinesefont_sportscene_abandon_confirm_yes,APP_COLOR_BLACK,APP_COLOR_RED);

    UI_Display_Prepare(temp_ram);
    
}

void UI_Screen_RuningModeAbandon_Exit(void)
{


}

void UI_Screen_RuningModeAbandon_shortkeyhandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Menu);
    UI_Screen_draw_Screen();

}

void UI_Screen_RuningModeAbandon_holdshortkeyhandle(void)
{
}

void UI_Screen_RuningModeAbandon_holdlongkeyhandle(void)
{
}

void UI_Screen_RuningModeAbandon_tpclickhandle(int point_x,int point_y)
{

    Enum_Common_ListScreen_Tprange curr_range;
    curr_range = UI_Common_List_Get_Tprange_Bypoint(point_x,point_y);

    switch(curr_range)
    {
        case Enum_Common_ListScreen_Tprange_0:
        case Enum_Common_ListScreen_Tprange_1:
        break;
        case Enum_Common_ListScreen_Tprange_2:
        case Enum_Common_ListScreen_Tprange_3:
        {
            UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Menu);
            UI_Screen_draw_Screen();
        }
        break;
        case Enum_Common_ListScreen_Tprange_4:
        case Enum_Common_ListScreen_Tprange_5:
        {
            UI_Set_Go_back_handle(NULL);
            //关闭跑步模式
            Scene_Run_Disable();
            //退出模式，重置大休眠状态
            UI_Commom_Set_Allow_Lockstate2(1);
            
            UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
            UI_Screen_draw_Screen();
        }
        
        break;
        default:
        break;
    }
        
    
}


void UI_Screen_RuningModeAbandon_tpupslidehandle(void)
{


}

void UI_Screen_RuningModeAbandon_tpdownslidehandle(void)
{


}

void UI_Screen_RuningModeAbandon_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeAbandon_tprightslidehandle(void)
{

    UI_Set_Curr_SubScreenID_Runingmode(Common_Screen_SubID_RuningMode_Menu);
    UI_Screen_draw_Screen();

}


static int history_page_number = 0;

void UI_Screen_RuningModeHistory_Entry(void)
{

    UI_Screen_RuningModeHistory_Display();
    
    UI_Common_set_key_handle(UI_Screen_RuningModeHistory_shortkeyhandle,NULL,NULL);
    
    UI_Common_set_tp_click_handle(UI_Screen_RuningModeHistory_tpclickhandle);
    UI_Common_set_tp_slide_handle(UI_Screen_RuningModeHistory_tpupslidehandle,
                                    UI_Screen_RuningModeHistory_tpdownslidehandle,
                                    UI_Screen_RuningModeHistory_tpleftslidehandle,
                                    UI_Screen_RuningModeHistory_tprightslidehandle);
    
}


void UI_Screen_RuningModeHistory_Display(void)
{
    
    int hour;
    int min;
    int second;

    //int width;
    //int height;
    //int total_width = 0;
    //int x;
    //int temp_value;
    
    runningInfo_t curr_info;
    rtc_time_s rtc_time;

    char content[32] = {0};
    int len;
    float temp_f;
    int temp_a,temp_b;

    uint8_t *temp_ram = UI_Display_Get_Tempram();
    if(UI_Get_Curr_SubScreenID_Runingmode()!=Common_Screen_SubID_RuningMode_History)
        return;
    UI_Common_Clear_Screen(temp_ram);

    Scene_Run_InfoGet(&curr_info);

    //首页
    if(history_page_number == 0)
    {

        //title
        UI_Common_Draw_FontStr_textbox(temp_ram,8,8,160,16,(uint8_t *)gchinesefont_sportscene_history_running,APP_COLOR_WHITE,APP_COLOR_BLACK);

        UtcTransformTime(curr_info.RecordData.StartUTC, &rtc_time);
        
        sprintf(content,"%02d/%02d/%02d  %02d:%02d",rtc_time.year,rtc_time.month,rtc_time.day,rtc_time.hour,rtc_time.min);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,8,32,160,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_CENTER);

        #if 0
		MidRTCParam_t* lMidRTC = Mid_RTC_ParamPGet();
        sprintf(content,"%02d:%02d",lMidRTC->RTC.hour,lMidRTC->RTC.min);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,94,32,80,12,12,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        #endif

        //距离
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_distance[0]-8,59,gchinesefont_sportscene_datadetail_distance[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_distance,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        temp_f = (float)curr_info.RecordData.Distance/1000;
        //memset(string_content,0,16);
        sprintf(content,"%0.2fkm",temp_f);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        //时长
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_time[0]-8,101,gchinesefont_sportscene_datadetail_time[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_time,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,105,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        hour = curr_info.RecordData.Duration/3600;
        min = curr_info.RecordData.Duration%3600/60;
        second = curr_info.RecordData.Duration%60;
        sprintf(content,"%02d:%02d:%02d",hour,min,second);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,101,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        
        //活动时长
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_activitytime[0]-8,142,gchinesefont_sportscene_datadetail_activitytime[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_activitytime,APP_COLOR_WHITE,APP_COLOR_BLACK);
        //UI_Common_Draw_FontStr_textbox(lcdram,84-gchinesefont_sportscene_datadetail_minkm[0]-gchinesefont_sportscene_average[0]-8,142,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,146,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        hour = curr_info.RecordData.ValidDuration/3600;
        min = curr_info.RecordData.ValidDuration%3600/60;
        second = curr_info.RecordData.ValidDuration%60;
        sprintf(content,"%02d:%02d:%02d",hour,min,second);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,142,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        
        
    }
    else if(history_page_number == 1)
    {

        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_minkm[0]-8,18,gchinesefont_sportscene_datadetail_minkm[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_minkm,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_minkm[0]-gchinesefont_sportscene_average[0]-8,18,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,22,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);
        
        temp_a = curr_info.RecordData.PaceAVG/60;
        temp_b = curr_info.RecordData.PaceAVG%60; 
        sprintf(content,"%d'%2d\"",temp_a,temp_b);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,18,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        
        
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_calorie[0]-8,59,gchinesefont_sportscene_datadetail_calorie[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_calorie,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        sprintf(content,"%dkcal",curr_info.RecordData.Calorie);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_stridefrequency[0]-8,101,gchinesefont_sportscene_datadetail_stridefrequency[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_stridefrequency,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_stridefrequency[0]-gchinesefont_sportscene_average[0]-8,101,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,105,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        sprintf(content,"%dspm",curr_info.RecordData.FreqAVG);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,101,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_stride[0]-8,142,gchinesefont_sportscene_datadetail_stride[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_stride,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_sportscene_datadetail_stride[0]-gchinesefont_sportscene_average[0]-8,142,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,146,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        temp_f =(float)curr_info.RecordData.StrideAVG/100;
        sprintf(content,"%0.2fm",temp_f);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,142,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);

        
            
    }
    else
    {
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-8,18,gchinesefont_heartrate_detail_heartrate[0],16,(uint8_t *)gchinesefont_heartrate_detail_heartrate,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-gchinesefont_sportscene_average[0]-8,18,gchinesefont_sportscene_average[0],16,(uint8_t *)gchinesefont_sportscene_average,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,22,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        sprintf(content,"%d",curr_info.RecordData.HrAVG);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,18,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        

        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-8,59,gchinesefont_heartrate_detail_heartrate[0],16,(uint8_t *)gchinesefont_heartrate_detail_heartrate,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_Draw_FontStr_textbox(temp_ram,84-gchinesefont_heartrate_detail_heartrate[0]-gchinesefont_sportscene_datadetail_max[0]-8,59,gchinesefont_sportscene_datadetail_max[0],16,(uint8_t *)gchinesefont_sportscene_datadetail_max,APP_COLOR_WHITE,APP_COLOR_BLACK);
        UI_Common_AddBWsourcePic(temp_ram,84,63,(uint8_t*)image_datadetail_dot_h,APP_COLOR_BLACK,APP_COLOR_RED);

        sprintf(content,"%d",curr_info.RecordData.HrMax);
        len = strlen(content);
        UI_Common_Draw_AscStr_textbox(temp_ram,100,59,68,16,16,APP_COLOR_WHITE,content,len,ENUM_TEXTBOX_LEFT);
        

    }
    
    UI_Display_Prepare(temp_ram);

}


void UI_Screen_RuningModeHistory_Exit(void)
{

    history_page_number = 0;

}


void UI_Screen_RuningModeHistory_shortkeyhandle(void)
{

        UI_Screen_RuningModeHistory_Exit();
        UI_Set_Go_back_handle(NULL);
        UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
        UI_Screen_draw_Screen();

}


void UI_Screen_RuningModeHistory_tpclickhandle(int point_x,int point_y)
{
    
}

void UI_Screen_RuningModeHistory_tpupslidehandle(void)
{
    int total_page;

    total_page = 3;
    
    if(history_page_number < total_page-1)
    {
        history_page_number++;
        UI_Screen_draw_Screen();
    }
    else
    {
    }


}

void UI_Screen_RuningModeHistory_tpdownslidehandle(void)
{

    if(history_page_number>0)
    {
        history_page_number--;
        UI_Screen_draw_Screen();
    }
    else
    {
        
    }
    

}

void UI_Screen_RuningModeHistory_tpleftslidehandle(void)
{
}

void UI_Screen_RuningModeHistory_tprightslidehandle(void)
{

    UI_Screen_RuningModeHistory_Exit();
    UI_Set_Go_back_handle(NULL);
    UI_Set_Curr_ScreenID(Common_Screen_MainID_DateAndTime);
    UI_Screen_draw_Screen();

}









#if 0
void UI_Screen_RuningModeSave_Entry(uint8_t *lcdram)
{   
    UI_Screen_RuningModeSave_Display(lcdram);

}

void UI_Screen_RuningModeSave_Display(uint8_t *lcdram)
{

    

}

void UI_Screen_RuningModeSave_Exit(void)
{


}
#endif


