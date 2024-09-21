#ifndef __USER_RUNMODE_H__
#define __USER_RUNMODE_H__

/**
 * @extern def
 */
#include "sys.h"
 
extern uint16_t IdleTimerCount;


void IdleTimerCallback(void *argument);


#endif
