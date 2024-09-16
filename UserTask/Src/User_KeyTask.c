/**
 * @headerfile
 */
#include "User_KeyTask.h"

/**
 * @otherfile
 */
#include "key.h"


void Key_Task(void *argument)
{
	uint8_t keystr=0;
	uint8_t Stopstr=0;
	uint8_t IdleBreakstr=0;
	while(1)
	{
		switch(key_scan(0))
		{
			
		}
		osDelay(1);
	}
}