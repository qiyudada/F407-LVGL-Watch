/**
 * @headerfile
 */
#include "User_SensorUpdate.h"

/**
 * @other
 */
#include "User_TaskInit.h"
#include "User_DataManagement.h"

/**
 * @brief  Sensor data update task
 * @param  argument: Not used
 * @retval None
 */
void SensorDataUpdateTask(void *argument)
{
  while (1)
  {
    uint8_t SensorUpdataStr;
    if (osMessageQueueGet(SensorUpdata_MessageQueue, &SensorUpdataStr, NULL, 0) == osOK)
    {
      // steps
      if (!(MW_Interface.IMU.ConnectionError))
      {
        MW_Interface.IMU.Steps = MW_Interface.IMU.GetSteps();
      }

      // temp and humi
      if (!(MW_Interface.DTH11.ConnectionError))
      {
        // temp and humi messure
        int humi, temp;
        MW_Interface.DTH11.GetHumiTemp(&humi, &temp);
        // check
        if (temp > -10 && temp < 50 && humi > 0 && humi < 100)
        {
          MW_Interface.DTH11.humidity = humi;
          MW_Interface.DTH11.temperature = temp;
        }
      }

      // send data save message queue
      uint8_t Datastr = 3;
      osMessageQueuePut(DataSave_MessageQueue, &Datastr, 0, 1);
    }
    osDelay(500);
  }
}
