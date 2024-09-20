/**
 * @headerfile
 */
#include "user_DataSaveTask.h"

/**
 * @other
 */
#include "User_TaskInit.h"
#include "User_DataManagement.h"

/******************************************
EEPROM Data description:
[0x00]:0x55 for check
[0x01]:0xAA for check

[0x10]:user wrist setting, HWInterface.IMU.wrist_is_enabled
[0x11]:user ui_APPSy_EN setting

[0x20]:Last Save Day(0-31)
[0x21]:Day Steps

*******************************************/

uint8_t SettingSave(uint8_t *buf, uint8_t addr, uint8_t lenth)
{
	if (!AT24Cxx_Epprom_Check())
	{
		// for(int i=10000;i>0;i--)
		// {

		// }
		Delay_ms(10);
		AT24Cxx_Write(addr, buf, lenth);
		return 0;
	}
	return 1;
}

uint8_t SettingGet(uint8_t *buf, uint8_t addr, uint8_t lenth)
{
	if (!AT24Cxx_Epprom_Check())
	{
		Delay_ms(10);
		AT24Cxx_Read(addr, buf, lenth);
		return 0;
	}
	return 1;
}

/**
 * @brief  Data Save in the EEPROM
 * @param  argument: Not used
 * @retval None
 */
void DataSaveTask(void *argument)
{

	while (1)
	{
		uint8_t Datastr = 0;
		if (osMessageQueueGet(DataSave_MessageQueue, &Datastr, NULL, 1) == osOK)
		{
			/****************
			Setting change
			date change
			Step change
			****************/
			uint8_t dat[3];
			dat[0] = MW_Interface.IMU.wrist_is_enabled;
			dat[1] = MW_Interface.BLE.ConnectionState;
			SettingSave(dat, 0x10, 2);

			RTC_DateTypeDef nowdate;
			HAL_RTC_GetDate(&hrtc, &nowdate, RTC_FORMAT_BIN);

			SettingGet(dat, 0x20, 3);
			if (dat[0] != nowdate.Date)
			{
				if (!MW_Interface.IMU.ConnectionError)
					MW_Interface.IMU.SetSteps(0);

				dat[0] = nowdate.Date;
				dat[2] = 0;
				dat[1] = 0;
				SettingSave(dat, 0x20, 3);
			}
			else
			{
				uint16_t temp = MW_Interface.IMU.GetSteps();
				dat[0] = nowdate.Date;
				dat[2] = temp & 0xff;
				dat[1] = temp >> 8 & 0xff;
				SettingSave(dat, 0x20, 3);
			}
		}
		osDelay(100);
	}
}
