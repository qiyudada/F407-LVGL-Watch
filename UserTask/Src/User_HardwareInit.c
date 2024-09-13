/**
 * @headerfile
 */
#include "User_HardwareInit.h"

/**
 * @others
 */
#include "User_TaskInit.h"
#include "User_DataManagement.h"
/**
 * @brief Hardware Init Task
 */
void HardwareInitTask(void *argument)
{
    while (1)
    {
        vTaskSuspendAll();
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
        LCD_ShowString2(72, MY_DISP_VER_RES / 2,88,(MY_DISP_VER_RES / 2)+16,16,(uint8_t *)"Welcome!",Purple);
        Delay_ms(1000);
        /*---------Touch Init---------- */
        tp_dev.init();
        /*----------Lvgl Init---------- */
        lv_init();
        lv_port_disp_init();
        lv_port_indev_init();
        /*----------Lvgl app---------- */

        log_info("Hardware initiate has been completed!");

        xTaskResumeAll();

        osThreadTerminate(HardwareInit_TaskHandle);
        osDelay(500);
    }
}
