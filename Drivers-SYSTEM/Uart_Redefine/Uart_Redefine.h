#ifndef __UART_REDEFINE_H
#define __UART_REDEFINE_H

#include "sys.h"
#include "usart.h"
#include <stdio.h>

int fputc(int ch, FILE *f);
int fgetc(FILE *f);

#endif
