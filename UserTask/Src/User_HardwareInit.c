/**
 * @headerfile
 */
#include "User_HardwareInit.h"

/**
 * @others
 */
#include "User_TaskInit.h"
#include "User_DataManagement.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "ui.h"
/**
 * @brief Hardware Init Task
 */
void HardwareInitTask(void *argument)
{
    while (1)
    {
        /*----------LED Init---------- */
        led_init();
        /*----------Key Init---------- */
        key_init();
        /*----------NFC Init---------- */
        uint8_t num = 3;
        while (num && MW_Interface.NFC.ConnectionState)
        {
            num--;
            MW_Interface.NFC.ConnectionState = MW_Interface.NFC.Init();
            Delay_us(100);
        }
        /*-------bluetooth Init------- */
        MW_Interface.BLE.Init();
        Delay_ms(1000);
        /*----------Mpu6050 Init---------- */
        num = 3;
        while (num && MW_Interface.IMU.ConnectionError)
        {
            num--;
            MW_Interface.IMU.ConnectionError = MW_Interface.IMU.Init();
            Delay_ms(300);
        }
        /*---------------LCD Init---------- */
        LCD_Init();
        LCD_Fill(0, 0, MY_DISP_HOR_RES, MY_DISP_VER_RES, YELLOW);
        Delay_ms(1000);
        LCD_Fill(0, 0, MY_DISP_HOR_RES, MY_DISP_VER_RES, WHITE);
        LCD_ShowString2(80, 140, 116, 156, 16, "Welcome!", Purple);
        Delay_ms(2000);
        /*---------Touch Init---------- */
        tp_dev.init();
        /*----------Lvgl Init---------- */
        lv_init();
        lv_port_disp_init();
        lv_port_indev_init();
        ui_init();
        /*----------Lvgl app---------- */

        log_info("Hardware initiate has been completed!");

        osThreadTerminate(HardwareInit_TaskHandle);
        osDelay(500);
    }
}
