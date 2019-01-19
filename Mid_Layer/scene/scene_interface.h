#ifndef     SCENE_INTERFACE_H
#define     SCENE_INTERFACE_H

// scene
#include "app_variable.h"

#include "scene_weather.h"
#include "scene_sedentary.h"
#include "scene_hrm.h"
#include "scene_abc.h"
#include "scene_stress.h"
#include "scene_run.h"
#include "scene_climb.h"
#include "scene_swim.h"
#include "scene_findphone.h"
#include "scene_gesture.h"
#include "scene_sleep.h"
#include "scene_step.h"
#include "scene_stairs.h"
#include "scene_alarm.h"
#include "scene_stopwatch.h"
#include "scene_countdown.h"

#include "scene_task.h"

extern void Scene_Interface_Init(void);
extern void Scene_Interface_Enable(void);
extern void Scene_Interface_Disable(void);

#endif      //MID_INTERFACE_H


