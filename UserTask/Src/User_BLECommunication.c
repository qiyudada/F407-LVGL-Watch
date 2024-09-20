/**
 * @headerfile
 */
#include "User_BLECommunication.h"

/**
 * @other
 */
#include <string.h>
#include <User_DataManagement.h>
#include "log.h"
#include "usart.h"

struct
{
	RTC_DateTypeDef nowdate;
	RTC_TimeTypeDef nowtime;
	int8_t humi;
	int8_t temp;
	uint16_t stepNum;
}BLEMessage;

struct
{
	RTC_DateTypeDef nowdate;
	RTC_TimeTypeDef nowtime;
}TimeSetMessage;


static void StrCMD_Get(uint8_t *str, char *cmd)
{
    uint8_t i = 0;
    while (str[i] != '=')
    {
        cmd[i] = str[i];
        i++;
    }
}


static void TimeFormat_Get(uint8_t * str)
{
	/*char type value transforms to int need to be minus '0'*/
	TimeSetMessage.nowdate.Year = (str[8]-'0')*10+str[9]-'0';
	TimeSetMessage.nowdate.Month = (str[10]-'0')*10+str[11]-'0';
	TimeSetMessage.nowdate.Date = (str[12]-'0')*10+str[13]-'0';
	TimeSetMessage.nowtime.Hours = (str[14]-'0')*10+str[15]-'0';
	TimeSetMessage.nowtime.Minutes = (str[16]-'0')*10+str[17]-'0';
	TimeSetMessage.nowtime.Seconds = (str[18]-'0')*10+str[19]-'0';
	/*uint8_t no negative,so the judge of ( >=0 ) always true*/
	if(TimeSetMessage.nowdate.Year>0 && TimeSetMessage.nowdate.Year<99
		&& TimeSetMessage.nowdate.Month>0 && TimeSetMessage.nowdate.Month<=12
		&& TimeSetMessage.nowdate.Date>0 && TimeSetMessage.nowdate.Date<=31
		&& TimeSetMessage.nowtime.Hours>=0 && TimeSetMessage.nowtime.Hours<=23
		&& TimeSetMessage.nowtime.Minutes>=0 && TimeSetMessage.nowtime.Minutes<=59
		&& TimeSetMessage.nowtime.Seconds>=0 && TimeSetMessage.nowtime.Seconds<=59)
	{
		RTC_SetDate(TimeSetMessage.nowdate.Year, TimeSetMessage.nowdate.Month,TimeSetMessage.nowdate.Date);
		RTC_SetTime(TimeSetMessage.nowtime.Hours,TimeSetMessage.nowtime.Minutes,TimeSetMessage.nowtime.Seconds);
		log_info("Time set success\r\n");
	}
}

/**
  * @brief  send the message via BLE, use uart
  * @param  argument: Not used
  * @retval None
  */
void MessageSendTask(void *argument)
{
	while(1)
	{
		if(HardInt_BLE_flag)
		{
			HardInt_BLE_flag = 0;
			if(!strcmp((char*)BlueTooth_Buffer,"MW"))
			{
				printf("OK\r\n");
			}
			else if(!strcmp((char*)BlueTooth_Buffer,"MW+SEND"))
			{
				HAL_RTC_GetTime(&hrtc,&(BLEMessage.nowtime),RTC_FORMAT_BIN);
				HAL_RTC_GetDate(&hrtc,&BLEMessage.nowdate,RTC_FORMAT_BIN);
				BLEMessage.humi = MW_Interface.DTH11.humidity;
				BLEMessage.temp = MW_Interface.DTH11.temperature;
				BLEMessage.stepNum = MW_Interface.IMU.Steps;

				log_info("data:%2d-%02d\r\n",BLEMessage.nowdate.Month,BLEMessage.nowdate.Date);
				log_info("time:%02d:%02d:%02d\r\n",BLEMessage.nowtime.Hours,BLEMessage.nowtime.Minutes,BLEMessage.nowtime.Seconds);
				log_info("humidity:%d%%\r\n",BLEMessage.humi);
				log_info("temperature:%d\r\n",BLEMessage.temp);
				log_info("Step today:%d\r\n",BLEMessage.stepNum);
			}
			//set time:MW+ST=20240920131420
			else if(strlen((char*)BlueTooth_Buffer)==20)
			{
				char cmd[10];
				memset(cmd,0,sizeof(cmd));
				StrCMD_Get(BlueTooth_Buffer,cmd);
				if(MW_Interface.BLE.ConnectionState && !strcmp(cmd,"MW+ST"))
				{
					TimeFormat_Get(BlueTooth_Buffer);
				}
			}
			memset(BlueTooth_Buffer,0,sizeof(BlueTooth_Buffer));
		}
		osDelay(1000);
	}
}
