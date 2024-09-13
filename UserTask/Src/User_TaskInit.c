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

/**
 * @brief  Initialize all the tasks
 */
void User_Tasks_Init(void)
{
    HardwareInit_TaskHandle = osThreadNew(HardwareInitTask, NULL, &HardwareInitTask_attributes);
    
}

void TaskTickHook(void)
{
    lv_tick_inc(1);
}
