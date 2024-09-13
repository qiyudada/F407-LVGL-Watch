#include "key.h"
#include "LED.h"
#include "Delay.h"
#include "Hc06.h"

/**
 * @brief       按键初始化函数
 * @param       无
 * @retval      无
 */
void key_init(void)
{
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/**
 * @brief       按键扫描函数
 * @note        该函数有响应优先级(同时按下多个按键):  KEY2 > KEY1
 * @param       mode:0 / 1, 具体含义如下:
 *   @arg       0,  不支持连续按(当按键按下不放时, 只有第一次调用会返回键值,
 *                  必须松开以后, 再次按下才会返回其他键值)
 *   @arg       1,  支持连续按(当按键按下不放时, 每次调用该函数都会返回键值)
 * @retval      键值, 定义如下:
 *              KEY1_PRES, 2, KEY1按下
 *              KEY2_PRES, 3, KEY2按下
 */
uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1; /* 按键按松开标志 */
    uint8_t keyval = 0;

    if (mode)
        key_up = 1; /* 支持连按 */

    if (key_up && (KEY1 == 0 || KEY2 == 0)) /* 按键松开标志为1, 且有任意一个按键按下了 */
    {
        Delay_ms(10); /* 去抖动 */
        key_up = 0;

        if (KEY1 == 0)
            keyval = KEY1_PRES;

        if (KEY2 == 0)
            keyval = KEY2_PRES;
    }
    else if (KEY1 == 1 && KEY2 == 1) /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
    }

    return keyval; /* 返回键值 */
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    Delay_ms(20); /* 消抖 */
    switch (GPIO_Pin)
    {

    case KEY1_GPIO_PIN:
        if (KEY1 == 0)
        {
            LED1_TOGGLE(); /* LED1 状态取反 */
        }
        break;

    case KEY2_GPIO_PIN:
        if (KEY2 == 0)
        {
            LED1_TOGGLE(); /* LED1 状态取反 */
            LED0_TOGGLE(); /* LED0 状态取反 */
        }
        break;

    default:
        break;
    }
}
