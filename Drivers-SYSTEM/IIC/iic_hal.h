#ifndef __IIC_HAL_H
#define __IIC_HAL_H

#include "sys.h"

typedef struct
{
	GPIO_TypeDef * IIC_SDA_PORT;
	GPIO_TypeDef * IIC_SCL_PORT;
	uint16_t IIC_SDA_PIN;
	uint16_t IIC_SCL_PIN;
}iic_bus_t;

void IIC_Init(iic_bus_t *bus);
void IIC_Start(iic_bus_t *bus);
void IIC_Stop(iic_bus_t *bus);
unsigned char IIC_Wait_Ack(iic_bus_t *bus);
void IIC_Send_Ack(iic_bus_t *bus);
void IIC_Send_NotAck(iic_bus_t *bus);
void IIC_Send_Byte(iic_bus_t *bus, unsigned char cSendByte);
unsigned char IIC_Read_Byte(iic_bus_t *bus);


uint8_t IIC_Write_One_Byte(iic_bus_t *bus, uint8_t daddr,uint8_t reg,uint8_t data);
uint8_t IIC_Write_Multi_Byte(iic_bus_t *bus, uint8_t daddr,uint8_t reg,uint8_t length,uint8_t buff[]);
unsigned char IIC_Read_One_Byte(iic_bus_t *bus, uint8_t daddr,uint8_t reg);
uint8_t IIC_Read_Multi_Byte(iic_bus_t *bus, uint8_t daddr, uint8_t reg, uint8_t length, uint8_t buff[]);

#endif
