/**
 * @headerfile
 */
#include "User_KeyTask.h"

/**
 * @otherfile
 */
#include "key.h"
#include "ui.h"

void KeyTask(void *argument)
{
	uint8_t keystr = 0;
	uint8_t Skipstr = 0;
	while (1)
	{
		switch (key_scan(0))
		{
		case 1:
			keystr = 1;
			osMessageQueuePut(Key_MessageQueue, &keystr, 0, 1);
			break;
		case 2:
			if (Page_Get_NowPage()->page_obj == &ui_HomePage)
			{
				Skipstr = 1;
				osMessageQueuePut(Skip_MessageQueue, &Skipstr, 0, 1);
			}
			else
			{
				keystr = 2;
				osMessageQueuePut(Key_MessageQueue, &keystr, 0, 1);
				break;
			}
		}
		osDelay(1);
	}
}
