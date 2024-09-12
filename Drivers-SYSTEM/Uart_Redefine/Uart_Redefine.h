#ifndef __UART_REDEFINE_H
#define __UART_REDEFINE_H

#include "sys.h"
#include "usart.h"
#include <stdio.h>

/*define serial port*/
#define Serial_Uart huart1


int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif
