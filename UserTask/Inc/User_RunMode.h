#ifndef __USER_RUNMODE_H__
#define __USER_RUNMODE_H__

/**
 * @extern def
 */
#include "sys.h"
 
extern uint16_t IdleTimerCount;
extern uint8_t ui_LightSliderValue;

void IdleTimerCallback(void *argument);

void IdleEnterTask(void *argument);

void StopEnterTask(void *argument);

#endif
