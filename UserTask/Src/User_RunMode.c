/**
 * @headerfile
 */
#include "User_RunMode.h"

/**
 * @other
 */
#include "User_DataManagement.h"
#include "User_TaskInit.h"
#include "main.h"
#include "iwdg.h"
#include "usart.h"

/**
 * @def
 */
uint16_t IdleTimerCount = 0;
uint8_t ui_LTimeValue = 50;
uint8_t ui_TTimeValue = 60;
uint8_t ui_LightSliderValue = 50;

void IdleTimerCallback(void *argument)
{
    uint8_t SensorUpdataStr = 3;
    IdleTimerCount += 1;
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
    osMessageQueuePut(SensorUpdata_MessageQueue, &SensorUpdataStr, 0, 1);
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
            LED_Set_Light(5);
        }
        // resume light if light got dark and idle state breaked by key pressing or screen touching
        if (osMessageQueueGet(IdleBreak_MessageQueue, &IdleBreakstr, NULL, 1) == osOK)
        {
            IdleTimerCount = 0;
            LED_Set_Light(ui_LightSliderValue);
        }
        osDelay(10);
    }
}

/**
 * @brief  enter the stop mode and resume
 * @param  argument: Not used
 * @retval None
 */
void StopEnterTask(void *argument)
{
    uint8_t Stopstr;
    uint8_t SensorUpdataStr;
    uint8_t Wrist_Flag = 0;
    while (1)
    {
        if (osMessageQueueGet(Stop_MessageQueue, &Stopstr, NULL, 0) == osOK)
        {

        /****************************** your sleep operations *****************************/
        sleep:
            IdleTimerCount = 0;

            // sensors

            // lcd
            LCD_LED(0);
            LED_Close_Light();

            /***********************************************************************************/

            vTaskSuspendAll();

            // systick int
            CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
            // enter stop mode
            HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFI);

            // here is the sleep period

            // resume run mode and reset the sysclk
            SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
            HAL_SYSTICK_Config(SystemCoreClock / (1000U / uwTickFreq));
            SystemClock_Config();
            HAL_IWDG_Refresh(&hiwdg);

            xTaskResumeAll();

            /****************************** your wakeup operations ******************************/

            // MPU Check
            if (MW_Interface.IMU.wrist_is_enabled)
            {
                uint8_t hor;
                hor = MPU_isHorizontal();
                if (hor && MW_Interface.IMU.wrist_state == WRIST_DOWN)
                {
                    MW_Interface.IMU.wrist_state = WRIST_UP;
                    Wrist_Flag = 1;
                    // resume, go on
                }
                else if (!hor && MW_Interface.IMU.wrist_state == WRIST_UP)
                {
                    MW_Interface.IMU.wrist_state = WRIST_DOWN;
                    IdleTimerCount = 0;
                    goto sleep;
                }
            }

            //
            if (!KEY1 || !KEY2 || !T_PEN || Wrist_Flag)
            {
                Wrist_Flag = 0;
                // resume, go on
            }
            else
            {
                IdleTimerCount = 0;
                goto sleep;
            }
            // lcd
            LCD_LED(1);
            LED_Set_Light(ui_LightSliderValue);

            osMessageQueuePut(SensorUpdata_MessageQueue, &SensorUpdataStr, 0, 1);
            /**************************************************************************************/
        }
        osDelay(100);
    }
}
