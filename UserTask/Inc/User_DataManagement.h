#ifndef _User_DataManagement_H_
#define _User_DataManagement_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*Main include*/
#include <stdio.h>
#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"

/*Gross management*/
#define User_Manage_file 1

#if (User_Manage_file)

#define Lvgl_Manage_file        1
#define LCD_Manage_file         1
#define Key_Manage_file         1
#define NFC_Manage_file         1
#define LED_Manage_file         1
#define Touch_Manage_file       1
#define Mpu6050_Manage_file     1
#define Bluetooth_Manage_file   1

#endif

/*child file include */
#if (Lvgl_Manage_file)
#include "lvgl.h"
#endif

#if (LCD_Manage_file)
#include "LCD.h"
#include "GUI.h"
#endif

#if (Touch_Manage_file)
#include "24cxx.h"
#include "touch.h"
#endif

#if (Key_Manage_file)
#include "key.h"
#endif

#if (NFC_Manage_file)
#include "RC522.h"
#endif

#if (LED_Manage_file)
#include "led.h"
#endif

#if (Mpu6050_Manage_file)
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#endif

#if (Bluetooth_Manage_file)
#include "Hc06.h"
#endif

/*-----------------------------------------------------------------------------------------------------------*/
/**
 * @enum error message
 */

#define MW_ERROR_NONE       0
#define MW_ERROR_DETECT     9

/*-----------------------------------------------------------------------------------------------------------*/
/**
 * @brief  MW IMU wrist state defines
 */
#define WRIST_UP 1
#define WRIST_DOWN 0

    /**
     * @brief MW IMU Interface definition
     */
    typedef struct
    {
        uint8_t ConnectionError;
        uint16_t Steps;
        uint8_t wrist_state;
        uint8_t wrist_is_enabled;

        uint8_t (*Init)(void);
        void (*WristEnable)(void);
        void (*WristDisable)(void);
        uint16_t (*GetSteps)(void);
        int (*SetSteps)(unsigned long count);
    } MW_IMU_InterfaceTypeDef;

    /**
     * @brief  MW DTH11 Interface definition
     */
    typedef struct
    {
        uint8_t ConnectionError;
        uint8_t temperature;
        uint8_t humidity;
        uint8_t (*Init)(void);
        void (*GetHumiTemp)(float *humi, float *temp);
    } MW_DTH11_InterfaceTypeDef;

    /**
     * @brief  MW BLE Interface definition
     */
    typedef struct
    {
        uint8_t ConnectionState;
        void (*Init)(void);
        void (*Control)(short mode);
        GPIO_PinState (*GetState)(void);
    } MW_BLE_InterfaceTypeDef;

    /**
     * @brief  MW NFC Interface definition
     */
    typedef struct
    {
        uint8_t ConnectionState;
        uint8_t (*Init)(void);
    } MW_NFC_InterfaceTypeDef;

    /**
     * @brief  Hardware Interface structure definition
     */
    typedef struct
    {
        MW_IMU_InterfaceTypeDef IMU;
        MW_DTH11_InterfaceTypeDef DTH11;
        MW_BLE_InterfaceTypeDef BLE;
        MW_NFC_InterfaceTypeDef NFC;

    } MW_InterfaceTypeDef;

    extern MW_InterfaceTypeDef MW_Interface;

#ifdef __cplusplus
}
#endif

#endif
