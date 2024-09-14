/**
 * @headerfile
 */
#include "User_TaskInit.h"

/**
 * @other headerfile
 */
#include "User_HardwareInit.h"

/*--------------------------------*/

/**
 * @defgroup
 */
/*Hardware Initiation*/
osThreadId_t HardwareInit_TaskHandle;
const osThreadAttr_t HardwareInitTask_attributes = {
    .name = "HardwareInitTask",
    .stack_size = 128 * 10,
    .priority = (osPriority_t)osPriorityHigh3,
};

/*LVGL Handler task*/
osThreadId_t LvHandlerTaskHandle;
const osThreadAttr_t LvHandlerTask_attributes = {
    .name = "LvHandlerTask",
    .stack_size = 128 * 24,
    .priority = (osPriority_t)osPriorityLow,
};

/**
 * @brief  Initialize all the tasks
 */
void User_Tasks_Init(void)
{
    HardwareInit_TaskHandle = osThreadNew(HardwareInitTask, NULL, &HardwareInitTask_attributes);
    LvHandlerTaskHandle = osThreadNew(LvHandlerTask, NULL, &LvHandlerTask_attributes);
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