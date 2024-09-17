/**
 * @headerfile
 */
#include "User_TaskInit.h"

/**
 * @other headerfile
 */
#include "User_HardwareInit.h"
#include "User_KeyTask.h"
#include "User_ScreenNew.h"
#include "User_SensorUpdate.h"
/*------------------------------------------------*/

/**
 * @defgroup Handler
 */
/*Hardware Initiation Task*/
osThreadId_t HardwareInit_TaskHandle;
const osThreadAttr_t HardwareInitTask_attributes = {
    .name = "HardwareInitTask",
    .stack_size = 128 * 10,
    .priority = (osPriority_t)osPriorityHigh3,
};

/*LVGL Handler task*/
osThreadId_t LvHandler_TaskHandle;
const osThreadAttr_t LvHandlerTask_attributes = {
    .name = "LvHandlerTask",
    .stack_size = 128 * 24,
    .priority = (osPriority_t)osPriorityLow,
};

/*Key detection task*/
osThreadId_t KeyTaskHandle;
const osThreadAttr_t KeyTask_attributes = {
    .name = "KeyTask",
    .stack_size = 128 * 5,
    .priority = (osPriority_t)osPriorityNormal,
};

/*ScrRenew task*/
osThreadId_t ScrRenewTaskHandle;
const osThreadAttr_t ScrRenewTask_attributes = {
  .name = "ScrRenewTask",
  .stack_size = 128 * 10,
  .priority = (osPriority_t) osPriorityLow1,
};


osThreadId_t SensorDataTaskHandle;
const osThreadAttr_t SensorDataTask_attributes = {
  .name = "SensorDataTask",
  .stack_size = 128 * 5,
  .priority = (osPriority_t) osPriorityLow1,
};

/*------------------------------------------------*/
/**
 * @defgroup Queue
 */

osMessageQueueId_t Key_MessageQueue;
osMessageQueueId_t Skip_MessageQueue;

/**
 * @brief  Initialize all the tasks
 */
void User_Tasks_Init(void)
{
    /* add queues, ... */
    Key_MessageQueue = osMessageQueueNew(1, 1, NULL);
    Skip_MessageQueue = osMessageQueueNew(1, 1, NULL);

    /* add threads, ... */
    HardwareInit_TaskHandle = osThreadNew(HardwareInitTask, NULL, &HardwareInitTask_attributes);
    LvHandler_TaskHandle = osThreadNew(LvHandlerTask, NULL, &LvHandlerTask_attributes);
    KeyTaskHandle = osThreadNew(KeyTask, NULL, &KeyTask_attributes);
    ScrRenewTaskHandle = osThreadNew(ScreenNewTask, NULL, &ScrRenewTask_attributes);
	SensorDataTaskHandle = osThreadNew(SensorDataUpdateTask, NULL, &SensorDataTask_attributes);

}

void TaskTickHook(void)
{
    lv_tick_inc(1);
}

/**
 * @brief  LVGL Handler task, to run the lvgl
 * @param  argument: Not used
 * @retval None
 */
void LvHandlerTask(void *argument)
{
    while (1)
    {
        lv_task_handler();
        osDelay(1);
    }
}
