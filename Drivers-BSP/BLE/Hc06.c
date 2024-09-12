#include "Hc06.h"
#include <string.h>
#include "usart.h"

uint8_t BlueTooth_Buffer[128];
extern DMA_HandleTypeDef hdma_usart3_rx;

/**
 * @brief BlueTooth Initation
 */
void BlueTooth_Init(void)
{

    __HAL_UART_ENABLE_IT(&BlueTooth_UART, UART_IT_IDLE);
    HAL_UARTEx_ReceiveToIdle_DMA(&BlueTooth_UART, BlueTooth_Buffer, sizeof(BlueTooth_Buffer));
}
/**
 * @brief BlueTooth Buffer Clear
 */
static void Blue_Buffer_Clear(void)
{
   memset(BlueTooth_Buffer, 0, sizeof(BlueTooth_Buffer));
}
/**
 * @brief Get bluetooth state pin 
 * @details if connect successfully the pin will be High other wise Low
 * @return GPIO_PinState(0-low,1-High)
 */
GPIO_PinState BlueTooth_Get_State(void)
{
    return HAL_GPIO_ReadPin(BLE_STATE_GPIO_Port, BLE_STATE_Pin);
}
/**
 * @brief BlueTooth Control
 * @details 0-Normal working mode,1-Enable AT mode
 */
void BlueTooth_Control(short mode)
{

    HAL_GPIO_WritePin(BLE_EN_GPIO_Port, BLE_EN_Pin, mode == 1 ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

/*Uart DMA Receive Callback*/
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart->Instance == USART3)
    {
        uint8_t cnt = BLE_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart3_rx);
        HAL_UART_Transmit(&BlueTooth_UART, BlueTooth_Buffer, cnt, HAL_MAX_DELAY);
        Blue_Buffer_Clear();
    }
}
