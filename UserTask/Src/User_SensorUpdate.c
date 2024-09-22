/**
 * @headerfile
 */
#include "User_SensorUpdate.h"

/**
 * @other
 */
#include "User_TaskInit.h"
#include "User_DataManagement.h"
#include "User_PageManagement.h"
#include "ui.h"

/**
 * @brief  MPU6050 Check the state
 * @param  argument: Not used
 * @retval None
 */
void MPUCheckTask(void *argument)
{
  while (1)
  {
    if (MW_Interface.IMU.wrist_is_enabled)
    {
      if (MPU_isHorizontal())
      {
        MW_Interface.IMU.wrist_state = WRIST_UP;
      }
      else
      {
        if (WRIST_UP == MW_Interface.IMU.wrist_state)
        {
          MW_Interface.IMU.wrist_state = WRIST_DOWN;
          if (Page_Get_NowPage()->page_obj == &ui_HomePage ||
              Page_Get_NowPage()->page_obj == &ui_MenuPage ||
              Page_Get_NowPage()->page_obj == &ui_MessageArcPage)
          {
            uint8_t Stopstr;
            osMessageQueuePut(Stop_MessageQueue, &Stopstr, 0, 1); // sleep
          }
        }
        MW_Interface.IMU.wrist_state = WRIST_DOWN;
      }
    }
    osDelay(300);
  }
}

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
      if (!MW_Interface.TEMT6000.Init())
      {
        uint8_t light_level;
        if (!MW_Interface.TEMT6000.LightSensor_Read(&light_level))
        {
          MW_Interface.TEMT6000.Light_Intensity = light_level;
        }
      }
      // send data save message queue
      uint8_t Datastr = 3;
      osMessageQueuePut(DataSave_MessageQueue, &Datastr, 0, 1);
    }
    osDelay(500);
  }
}
