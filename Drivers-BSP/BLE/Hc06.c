#include "Hc06.h"

CfifoBuff BlueTooth_FIFO;

/**
 * @brief BlueTooth Initation
 */
void BlueTooth_Init(void)
{
	CfifoBuff_Init(&BlueTooth_FIFO);
    HAL_UART_Receive_DMA(&BlueTooth_UART, BlueTooth_FIFO.BUFF, sizeof(BlueTooth_FIFO.BUFF)); // 开启中断接收数据
    __HAL_UART_ENABLE_IT(&BlueTooth_UART, UART_IT_IDLE);
}

static void Blue_Buffer_Clear(void)
{
    
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (__HAL_UART_GET_FLAG(&BlueTooth_UART, UART_FLAG_IDLE) != RESET)
    {
        __HAL_UART_CLEAR_IDLEFLAG(&BlueTooth_UART);
        BlueTooth_UART.RxXferCount = sizeof(BlueTooth_FIFO.BUFF);
        BlueTooth_UART.pRxBuffPtr = BlueTooth_FIFO.BUFF;
        HAL_UART_Transmit(&BlueTooth_UART, BlueTooth_FIFO.BUFF, sizeof(BlueTooth_FIFO.BUFF), 1000);
			
    }
}