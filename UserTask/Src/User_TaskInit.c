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
#include "User_BLECommunication.h"
#include "user_DataSaveTask.h"
#include "User_RunMode.h"
#include "User_WatchDog.h"
#include "ui.h"
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
    .stack_size = 128 * 30,
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
    .priority = (osPriority_t)osPriorityLow1,
};

osThreadId_t SensorDataTaskHandle;
const osThreadAttr_t SensorDataTask_attributes = {
    .name = "SensorDataTask",
    .stack_size = 128 * 5,
    .priority = (osPriority_t)osPriorityLow1,
};

/*BLEmessagesendtask*/
osThreadId_t MessageSendTaskHandle;
const osThreadAttr_t MessageSendTask_attributes = {
    .name = "MessageSendTask",
    .stack_size = 128 * 5,
    .priority = (osPriority_t)osPriorityLow1,
};

/*DataSaveTask*/
osThreadId_t DataSaveTaskHandle;
const osThreadAttr_t DataSaveTask_attributes = {
    .name = "DataSaveTask",
    .stack_size = 128 * 5,
    .priority = (osPriority_t)osPriorityLow2,
};

/*Idle Enter Task*/
osThreadId_t IdleEnterTaskHandle;
const osThreadAttr_t IdleEnterTask_attributes = {
    .name = "IdleEnterTask",
    .stack_size = 128 * 5,
    .priority = (osPriority_t)osPriorityHigh,
};

/*Stop Enter Task*/
osThreadId_t StopEnterTaskHandle;
const osThreadAttr_t StopEnterTask_attributes = {
    .name = "StopEnterTask",
    .stack_size = 128 * 16,
    .priority = (osPriority_t)osPriorityHigh1,
};

/*MPUCheckTask*/
osThreadId_t MPUCheckTaskHandle;
const osThreadAttr_t MPUCheckTask_attributes = {
    .name = "MPUCheckTask",
    .stack_size = 128 * 3,
    .priority = (osPriority_t)osPriorityLow2,
};

/*WDOG Feed task*/
osThreadId_t WDOGFeedTaskHandle;
const osThreadAttr_t WDOGFeedTask_attributes = {
    .name = "WDOGFeedTask",
    .stack_size = 128 * 1,
    .priority = (osPriority_t)osPriorityHigh2,
};
/*------------------------------------------------*/
/**
 * @defgroup Queue
 */
osMessageQueueId_t Key_MessageQueue;
osMessageQueueId_t Skip_MessageQueue;
osMessageQueueId_t SensorUpdata_MessageQueue;
osMessageQueueId_t DataSave_MessageQueue;
osMessageQueueId_t IdleBreak_MessageQueue;
osMessageQueueId_t Stop_MessageQueue;
osMessageQueueId_t Idle_MessageQueue;

/* Timers --------------------------------------------------------------------*/
osTimerId_t IdleTimerHandle;

/**
 * @brief  Initialize all the tasks
 */
void User_Tasks_Init(void)
{

    /* start timers, add new ones, ... */
    IdleTimerHandle = osTimerNew(IdleTimerCallback, osTimerPeriodic, NULL, NULL);
    osTimerStart(IdleTimerHandle, 200);

    /* add queues, ... */
    Key_MessageQueue = osMessageQueueNew(1, 1, NULL);
    Skip_MessageQueue = osMessageQueueNew(1, 1, NULL);
    SensorUpdata_MessageQueue = osMessageQueueNew(1, 1, NULL);
    DataSave_MessageQueue = osMessageQueueNew(1, 1, NULL);
    IdleBreak_MessageQueue = osMessageQueueNew(1, 1, NULL);
    Stop_MessageQueue = osMessageQueueNew(1, 1, NULL);
    Idle_MessageQueue = osMessageQueueNew(1, 1, NULL);

    /* add threads, ... */
    LvHandler_TaskHandle = osThreadNew(LvHandlerTask, NULL, &LvHandlerTask_attributes);          // 8
    ScrRenewTaskHandle = osThreadNew(ScreenNewTask, NULL, &ScrRenewTask_attributes);             // 9
    SensorDataTaskHandle = osThreadNew(SensorDataUpdateTask, NULL, &SensorDataTask_attributes);  // 9
    MessageSendTaskHandle = osThreadNew(MessageSendTask, NULL, &MessageSendTask_attributes);     // 9
    MPUCheckTaskHandle = osThreadNew(MPUCheckTask, NULL, &MPUCheckTask_attributes);              // 10
    DataSaveTaskHandle = osThreadNew(DataSaveTask, NULL, &DataSaveTask_attributes);              // 10
    KeyTaskHandle = osThreadNew(KeyTask, NULL, &KeyTask_attributes);                             // 24
    IdleEnterTaskHandle = osThreadNew(IdleEnterTask, NULL, &IdleEnterTask_attributes);           // 40
    StopEnterTaskHandle = osThreadNew(StopEnterTask, NULL, &StopEnterTask_attributes);           // 41
    WDOGFeedTaskHandle = osThreadNew(WDOGFeedTask, NULL, &WDOGFeedTask_attributes);              // 42
    HardwareInit_TaskHandle = osThreadNew(HardwareInitTask, NULL, &HardwareInitTask_attributes); // 43

    /* add  others ... */
    uint8_t SensorUpdataStr;
    osMessageQueuePut(SensorUpdata_MessageQueue, &SensorUpdataStr, 0, 1);
}

/**
 * @brief Support lvgl heartbeat
 */
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
    uint8_t IdleBreakstr = 0;
    while (1)
    {
        if (lv_disp_get_inactive_time(NULL) < 1000)
        {
            // Idle time break, set to 0
            osMessageQueuePut(IdleBreak_MessageQueue, &IdleBreakstr, 0, 0);
        }
        // printf("lv_stack is %d \r\n", (int *)uxTaskGetStackHighWaterMark(LvHandler_TaskHandle));
        lv_task_handler();
        osDelay(1);
    }
}
