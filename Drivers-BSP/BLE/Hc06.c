#include "Hc06.h"

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

static void Blue_Buffer_Clear(void)
{
   memset(BlueTooth_Buffer, 0, sizeof(BlueTooth_Buffer));
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart->Instance == USART3)
    {
        uint8_t cnt = CFIFO_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart3_rx);
        HAL_UART_Transmit(&BlueTooth_UART, BlueTooth_Buffer, cnt, HAL_MAX_DELAY);
        Blue_Buffer_Clear();
    }
}
