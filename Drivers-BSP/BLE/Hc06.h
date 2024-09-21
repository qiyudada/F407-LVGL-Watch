#ifndef __Hc06_H
#define __Hc06_H

#ifdef __cplusplus
extern "C" {
#endif


#include "sys.h"

 

#define BlueTooth_UART huart3
#define BLE_BUFFER_SIZE 128
extern uint8_t BlueTooth_Buffer[BLE_BUFFER_SIZE];
extern uint8_t HardInt_BLE_flag;


/*Function*/
void BlueTooth_Init(void);

void BlueTooth_Control(short mode);

void Blue_Buffer_Clear(void);

GPIO_PinState BlueTooth_Get_State(void);



#ifdef __cplusplus
}
#endif


#endif
