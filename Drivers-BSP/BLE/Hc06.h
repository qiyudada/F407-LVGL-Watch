#ifndef __Hc06_H
#define __Hc06_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
 #include "sys.h"

/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
/* USER CODE END Includes */
 
/* USER CODE BEGIN Private defines */
 
 
/* USER CODE END Private defines */
// typedef struct 
// { 
// 	 UART_HandleTypeDef  *handle;    /*HAL库提供的串口句柄*/
// 	 int16_t TransFlag;              /*数据发送标志位*/      
// 	 int32_t DmaSize;                /*DMA缓冲区的大小*/
// 	 int32_t DamOffset;              /*获取数据在DMA缓冲区的偏移量*/
// 	 uint8_t *pReadDma;              /*指向接收DMA缓冲区的首地址*/
// 	 uint8_t *pWriteDma;             /*指向发送DMA缓冲区的首地址*/
// 	 CfifoBuff AcceptCFifo;          /*接受数据的循环缓冲区*/
// 	 CfifoBuff SendCFifo;            /*发送数据的循环缓冲区*/
// }MW_UART_ATTR;	
 
 
// /* USER CODE BEGIN Prototypes */
// int8_t MW_UART_Init(UART_HandleTypeDef *handle);        //初始化
// void MW_UART_IRQHandler(UART_HandleTypeDef *huart);     //串口中断中调用
// int32_t MW_UART_Transmit(uint8_t* buffer,int32_t len);  //CFIFO+DMA+Usart数据发送
// /* USER CODE END Prototypes */
 


#ifdef __cplusplus
}
#endif


#endif
