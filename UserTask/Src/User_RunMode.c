/**
 * @headerfile
 */
#include "User_RunMode.h"

/**
 * @other
 */
#include "User_TaskInit.h"

/**
 * @def
 */
uint16_t IdleTimerCount = 0;
uint8_t ui_LTimeValue = 50;
uint8_t ui_TTimeValue = 60;
uint8_t ui_LightSliderValue = 50;

void IdleTimerCallback(void *argument)
{
    IdleTimerCount += 1;
    uint8_t UpdateTimerCount = 0;
    if (IdleTimerCount == (ui_LTimeValue))
    {
        uint8_t Idlestr = 0;
        // send the Light off message
        osMessageQueuePut(Idle_MessageQueue, &Idlestr, 0, 1);
    }
    if (IdleTimerCount == (ui_TTimeValue))
    {
        uint8_t Stopstr = 1;
        IdleTimerCount = 0;
        // send the Stop message
        osMessageQueuePut(Stop_MessageQueue, &Stopstr, 0, 1);
    }

    osMessageQueuePut(SensorUpdata_MessageQueue, &UpdateTimerCount, 0, 1);
}

/**
 * @brief  Enter Idle state
 * @param  argument: Not used
 * @retval None
 */
void IdleEnterTask(void *argument)
{
    uint8_t Idlestr = 0;
    uint8_t IdleBreakstr = 0;
    while (1)
    {
        // light get dark
        if (osMessageQueueGet(Idle_MessageQueue, &Idlestr, NULL, 1) == osOK)
        {
			//LCD_Set_Light(5);
        }
        // resume light if light got dark and idle state breaked by key pressing or screen touching
        if (osMessageQueueGet(IdleBreak_MessageQueue, &IdleBreakstr, NULL, 1) == osOK)
        {
            IdleTimerCount = 0;
            //LCD_Set_Light(ui_LightSliderValue);
        }
        osDelay(10);
    }
}
