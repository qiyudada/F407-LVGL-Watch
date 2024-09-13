#ifndef _User_TaskInit_H_
#define _User_TaskInit_H_

/*
 * @ Data Management
 */
#include "User_DataManagement.h"


/*extern define*/
/*taskhanler*/
extern osThreadId_t HardwareInit_TaskHandle;



void User_Tasks_Init(void);

void TaskTickHook(void);


#endif
