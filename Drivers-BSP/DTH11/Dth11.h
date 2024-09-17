#ifndef _DTH11_H
#define _DTH11_H


#include "sys.h"

/*DTH11 Pin define*/
#define DTH11_Port GPIOD
#define DTH11_PIN GPIO_PIN_3

#define DHT11_HIGH HAL_GPIO_WritePin(DTH11_Port, DTH11_PIN, GPIO_PIN_SET)  // 输出高电平
#define DHT11_LOW HAL_GPIO_WritePin(DTH11_Port, DTH11_PIN, GPIO_PIN_RESET) // 输出低电平
#define DHT11_IO_IN HAL_GPIO_ReadPin(DTH11_Port, DTH11_PIN)				   // 读取IO口电平


uint8_t DHT11_Init(void);

uint8_t DHT11_Read_Bit(void);

uint8_t DHT11_Read_Data(int *temp, int *humi);

void DHT11_PinCfgAsOutput(void);

void DHT11_PinCfgAsInput(void);

void DHT11_Start(void);

int DHT11_Wait_Ack(void);

void DHT11_Test(void);

#endif
