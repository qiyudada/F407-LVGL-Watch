#ifndef _User_TaskInit_H_
#define _User_TaskInit_H_

/*
 * @ Data Management
 */
#include "User_DataManagement.h"


/*-------------------extern define-------------------*/
/*Message Queue*/
extern osMessageQueueId_t Key_MessageQueue;
extern osMessageQueueId_t Skip_MessageQueue;
extern osMessageQueueId_t SensorUpdata_MessageQueue;

/*Taskhandler*/
extern osThreadId_t HardwareInit_TaskHandle;



void User_Tasks_Init(void);

void TaskTickHook(void);

void LvHandlerTask(void *argument);


#endif
