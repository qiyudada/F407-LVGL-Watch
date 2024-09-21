/**
 * @headerfile
 */
#include "User_WatchDog.h"

/**
 * @other
 */
#include "User_DataManagement.h"
#include "iwdg.h"
/**
 * @brief  Watch Dog Feed task
 * @param  argument: Not used
 * @retval None
 */
void WDOGFeedTask(void *argument)
{

    MX_IWDG_Init();
    while (1)
    {
        HAL_IWDG_Refresh(&hiwdg);
        osDelay(300);
    }
}
