/**
 * @headerfile
 */
#include "User_HardwareInit.h"

/**
 * @others
 */
#include "User_TaskInit.h"
#include "User_DataManagement.h"
#include "user_DataSaveTask.h"
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
        /*----------Delay Init---------- */
        // Delay_init();
        /*----------LED Init---------- */
        Led_Init();
        /*----------Key Init---------- */
        key_init();
        /*----------DTH11 Init---------- */
        uint8_t num = 3;
        while (num && MW_Interface.DTH11.ConnectionError)
        {
            num--;
            MW_Interface.DTH11.ConnectionError = MW_Interface.DTH11.Init();
            Delay_ms(100);
        }
        /*----------NFC Init---------- */
        num = 3;
        while (num && MW_Interface.NFC.ConnectionState)
        {
            num--;
            MW_Interface.NFC.ConnectionState = MW_Interface.NFC.Init();
            Delay_us(100);
        }
        /*-------bluetooth Init------- */
        MW_Interface.BLE.Init();
        MW_Interface.BLE.Control(0);
        MW_Interface.BLE.ConnectionState = 0; // set not connection state
        Delay_ms(1000);
        /*----------Mpu6050 Init---------- */
        num = 3;
        while (num && MW_Interface.IMU.ConnectionError)
        {
            num--;
            MW_Interface.IMU.ConnectionError = MW_Interface.IMU.Init();
            Delay_ms(300);
        }
        /*----------AT24Cxx(EEPROM) Init---------- */
        AT24Cxx_Init();
        /*----------Data  read Init---------- */
        if (!AT24Cxx_Epprom_Check())
        {
            uint8_t recbuf[3];
            SettingGet(recbuf, 0x10, 2);
            if ((recbuf[0] != 0 && recbuf[0] != 1) || (recbuf[1] != 0 && recbuf[1] != 1))
            {
                MW_Interface.IMU.wrist_is_enabled = 0;
                MW_Interface.BLE.ConnectionState = 0;
            }
            else
            {
                MW_Interface.IMU.wrist_is_enabled = recbuf[0];
                MW_Interface.BLE.ConnectionState = 0;
            }

            RTC_DateTypeDef nowdate;
            HAL_RTC_GetDate(&hrtc, &nowdate, RTC_FORMAT_BIN);

            SettingGet(recbuf, 0x20, 3);
            if (recbuf[0] == nowdate.Date)
            {
                uint16_t steps = 0;
                steps = recbuf[1] & 0x00ff;
                steps = steps << 8 | recbuf[2];
                if (!MW_Interface.IMU.ConnectionError)
                    dmp_set_pedometer_step_count((unsigned long)steps);
            }
        }
       
        /*---------------LCD Init---------- */
        LCD_Init();
        LCD_Fill(0, 0, MY_DISP_HOR_RES, MY_DISP_VER_RES, YELLOW);
        Delay_ms(1000);
        LCD_Fill(0, 0, MY_DISP_HOR_RES, MY_DISP_VER_RES, WHITE);
        LCD_ShowString2(84, 140, 116, 156, 16, "Welcome!", Purple);
        Delay_ms(2000);
         /*--------PWM Init----------*/
        LED_PWM_Init();
        LED_Set_Light(5);
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
