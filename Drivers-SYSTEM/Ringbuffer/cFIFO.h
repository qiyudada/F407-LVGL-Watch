#ifndef _CFIFO_H_
#define _CFIFO_H_
 
#ifdef __cplusplus
extern "C" {
#endif
 
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "sys.h"
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
/* USER CODE END Includes */
 
/* USER CODE BEGIN Private defines */
 
#define CFIFO_SIZE 1024           //环形队列CFIFO大小
 
 
/*环形CFIFO结构体*/
typedef struct
{
	uint16_t Head;       //环形CFIFO队列头
	uint16_t Tail;	     //环形CFIFO队列尾
    uint16_t Lenght;     //环形CFIFO数据长度
	uint8_t  BUFF[CFIFO_SIZE];     //环形CFIFO缓存区
}CfifoBuff;
 
 
/* USER CODE END Private defines */
 
 
/* USER CODE BEGIN Prototypes */
void CfifoBuff_Init(CfifoBuff * Cfifo_pointer);  //CFIFO初始化
void CfifoBuff_Clear(CfifoBuff * Cfifo_pointer); //CFIFO数据清除
int16_t CfifoBuff_Write(CfifoBuff * Cfifo_pointer,char * User_buff,uint16_t num); //CFIFO数据写人
int16_t CfifoBuff_Read(CfifoBuff * Cfifo_pointer,char * User_buff,uint16_t num); //CFIFO数据读出
/* USER CODE END Prototypes */
 
#ifdef __cplusplus
}
#endif
 
#endif /* _CFIFO_H_ */
 
 