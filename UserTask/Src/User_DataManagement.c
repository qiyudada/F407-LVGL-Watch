#include "User_DataManagement.h"

/************************************************************************************
 * @defgroup RTC area
 ***********************************************************************************/
/**
 * @brief get current time and date
 * @param  nowdatetime: pointer to the current time and date
 * @retval None
 */
void MW_RTC_Get_TimeDate(MW_DateTimeTypeDef *nowdatetime)
{

#if RTC_Manage_file
    if (nowdatetime != NULL)
    {
        RTC_DateTypeDef nowdate;
        RTC_TimeTypeDef nowtime;
        HAL_RTC_GetTime(&hrtc, &nowtime, RTC_FORMAT_BIN);
        HAL_RTC_GetDate(&hrtc, &nowdate, RTC_FORMAT_BIN);
        nowdatetime->Year = nowdate.Year;
        nowdatetime->Month = nowdate.Month;
        nowdatetime->Date = nowdate.Date;
        nowdatetime->WeekDay = weekday_calculate(nowdatetime->Year, nowdatetime->Month, nowdatetime->Date, 20);
        nowdatetime->Hours = nowtime.Hours;
        nowdatetime->Minutes = nowtime.Minutes;
        nowdatetime->Seconds = nowtime.Seconds;
    }
#else
    nowdatetime->Year = 24;
    nowdatetime->Month = 6;
    nowdatetime->Date = 23;
    nowdatetime->WeekDay = 7;
    nowdatetime->Hours = 11;
    nowdatetime->Minutes = 59;
    nowdatetime->Seconds = 55;
#endif
}
/**
 * @brief  set current date
 * @param  year(xx),month(xx),date(xx)
 * @retval None
 */
void MW_RTC_Set_Date(uint8_t year, uint8_t month, uint8_t date)
{
#if RTC_Manage_file
    RTC_SetDate(year, month, date);
#endif
}
/**
 * @brief  set current time
 * @param  hours(xx),minutes(xx),seconds(xx)
 * @retval None
 */

void MW_RTC_Set_Time(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
#if RTC_Manage_file
    RTC_SetTime(hours, minutes, seconds);
#endif
}

/**
 * @brief  calculate weekday
 * @param  setyear(xx),setmonth(xx),setday(xx),century(20)
 * @retval weekday
 */
uint8_t MW_weekday_calculate(uint8_t setyear, uint8_t setmonth, uint8_t setday, uint8_t century)
{
    int w;
    if (setmonth == 1 || setmonth == 2)
    {
        setyear--, setmonth += 12;
    }
    w = setyear + setyear / 4 + century / 4 + 26 * (setmonth + 1) / 10 + setday - 1 - 2 * century;
    while (w < 0)
        w += 7;
    w %= 7;
    w = (w == 0) ? 7 : w;
    return w;
}

/************************************************************************************
 * @defgroup Bluetooth area
 ***********************************************************************************/

/**
 * @brief  Bluetooth init
 */
void MW_BlueTooth_Init(void)
{
#if Bluetooth_Manage_file
    BlueTooth_Init();
#endif
}

/**
 * @brief  Bluetooth control
 */
void MW_BlueTooth_Control(short mode)
{
#if Bluetooth_Manage_file
    BlueTooth_Control(mode);
#endif
}

void MW_BlueTooth_Buffer_Clear(void)
{
#if Bluetooth_Manage_file
    Blue_Buffer_Clear();
#endif
}

/**
 * @brief  Bluetooth get state
 */
uint8_t MW_BlueTooth_Get_State(void)
{
#if Bluetooth_Manage_file
    return BlueTooth_Get_State();
#else
    return MW_ERROR_DETECT;
#endif
}

/************************************************************************************
 * @defgroup Mpu6050 area
 ***********************************************************************************/
/**
 * @brief  Mpu6050 init
 * @return 0:success, others:fail
 */
uint8_t MW_MPU_Init(void)
{
#if Mpu6050_Manage_file
    return mpu_dmp_init();
#else
    return MW_ERROR_DETECT;
#endif
}
/**
 * @brief  Mpu6050 wrist enable
 */
void MW_MPU_Wrist_Enable(void)
{
#if Mpu6050_Manage_file
    MW_Interface.IMU.wrist_is_enabled = 1;
#endif
}
/**
 * @brief  Mpu6050 wrist disable
 */
void MW_MPU_Wrist_Disable(void)
{
#if Mpu6050_Manage_file
    MW_Interface.IMU.wrist_is_enabled = 0;
#endif
}
/**
 * @brief  Mpu6050 get steps
 * @return steps
 */
uint16_t MW_MPU_Get_Steps(void)
{
#if Mpu6050_Manage_file
    unsigned long STEPS = 0;
    if (!MW_Interface.IMU.ConnectionError)
        dmp_get_pedometer_step_count(&STEPS);
    return (uint16_t)STEPS;
#else
    return 0;
#endif
}

/**
 * @brief  Mpu6050 set steps
 * @return 0:success, others:fail
 */
int MW_MPU_Set_Steps(unsigned long count)
{
#if Mpu6050_Manage_file
    if (!MW_Interface.IMU.ConnectionError)
        return dmp_set_pedometer_step_count(count);
    return 0;
#endif
}

/************************************************************************************
 * @defgroup NFC(RC522) area
 ***********************************************************************************/
/**
 * @brief  NFC init
 */
uint8_t MW_NFC_Init(void)
{
#if NFC_Manage_file
    return PCD_Init_RST();
#else
    return MW_ERROR_DETECT;
#endif
}

/************************************************************************************
 * @defgroup DTH11 area
 ***********************************************************************************/
/**
 * @brief  DTH11 init
 */
uint8_t MW_DTH11_Init(void)
{
#if DTH11_Manage_file
    return DHT11_Init();
#else
    return MW_ERROR_DETECT;
#endif
}

void MW_DHT11_Read_Data(int *humi, int *temp)
{
#if DTH11_Manage_file
    if (!MW_Interface.DTH11.ConnectionError)
    {
        DHT11_Read_Data(temp, humi);
    }
#else
    return MW_ERROR_DETECT;
#endif
}

/**************************************************************
 * @defgroup Watch gross function and data management
 *************************************************************/

MW_InterfaceTypeDef MW_Interface = {

    .RealTime = {
        .GetTimeDate = MW_RTC_Get_TimeDate,
        .SetDate = MW_RTC_Set_Date,
        .SetTime = MW_RTC_Set_Time,
        .CalculateWeekday = MW_weekday_calculate,
    },
    .DTH11 = {
        .ConnectionError = 1,
        .temperature = 26,
        .humidity = 50,
        .Init = MW_DTH11_Init,
        .GetHumiTemp = MW_DHT11_Read_Data,
    },
    .BLE = {
        .ConnectionState = 1,
        .Init = MW_BlueTooth_Init,
        .Control = MW_BlueTooth_Control,
        .BufferClean = MW_BlueTooth_Buffer_Clear,
    },
    .NFC = {
        .ConnectionState = 1,
        .Init = MW_NFC_Init,
    },
    .IMU = {
        .ConnectionError = 0,
        .Steps = 0,
        .wrist_is_enabled = 0,
        .wrist_state = WRIST_UP,
        .Init = MW_MPU_Init,
        .WristEnable = MW_MPU_Wrist_Enable,
        .WristDisable = MW_MPU_Wrist_Disable,
        .GetSteps = MW_MPU_Get_Steps,
        .SetSteps = MW_MPU_Set_Steps,
    },

};
