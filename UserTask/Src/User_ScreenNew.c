/**
 * @headerfile
 */
#include "User_ScreenNew.h"

/**
 * @other
 */
#include "User_TaskInit.h"
#include "ui.h"

/**
 * @brief  Screen renew task
 * @param  argument: Not used
 * @retval None
 */
void ScreenNewTask(void *argument)
{
	uint8_t keystr = 0;
	uint8_t SkipStr = 0;
	while (1)
	{
		if (osMessageQueueGet(Key_MessageQueue, &keystr, NULL, 0) == osOK)
		{
			// key1 pressed
			if (keystr == 1)
			{

				if (Page_Get_NowPage()->page_obj == &ui_HomePage)
				{
					Page_Load(&Page_Menu);
				}
				else
				{
					Page_Back_Bottom();
				}
			}
			// key2 pressed
			else if (keystr == 2)
			{
				Page_Back_Bottom();
			}
		}
		if (osMessageQueueGet(Skip_MessageQueue, &SkipStr, NULL, 0) == osOK)
		{
			if (SkipStr == 1)
			{
				Page_Load(&Page_Music);
			}
		}
		osDelay(10);
	}
}
