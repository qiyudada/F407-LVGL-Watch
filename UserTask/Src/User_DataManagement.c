#include "User_DataManagement.h"

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
#endif
    return 0;
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
#endif
    return MW_ERROR_DETECT;
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

/**************************************************************
 * @defgroup Watch gross function and data management
 *************************************************************/

MW_InterfaceTypeDef MW_Interface = {

    .BLE = {
        .ConnectionState = 1,
        .Init = MW_BlueTooth_Init,
        .Control = MW_BlueTooth_Control,
        .GetState = MW_BlueTooth_Get_State,
    },
    .NFC = {
        .ConnectionState = 1,
        .Init = MW_NFC_Init,
    },
    .IMU = {
        .ConnectionError = 1,
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
