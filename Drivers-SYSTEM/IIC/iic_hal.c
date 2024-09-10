#include "iic_hal.h"
#include "delay.h"

/**
  * @brief SDA线输入模式配置
  * @param None
  * @retval None
  */
void SDA_Input_Mode(iic_bus_t *bus)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    GPIO_InitStructure.Pin = bus->IIC_SDA_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(bus->IIC_SDA_PORT, &GPIO_InitStructure);
}

/**
  * @brief SDA线输出模式配置
  * @param None
  * @retval None
  */
void SDA_Output_Mode(iic_bus_t *bus)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    GPIO_InitStructure.Pin = bus->IIC_SDA_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(bus->IIC_SDA_PORT, &GPIO_InitStructure);
}

/**
  * @brief SDA线输出一个位
  * @param val 输出的数据
  * @retval None
  */
void SDA_Output(iic_bus_t *bus, uint16_t val)
{
    if ( val )
    {
        bus->IIC_SDA_PORT->BSRR |= bus->IIC_SDA_PIN;
    }
    else
    {
        bus->IIC_SDA_PORT->BSRR = (uint32_t)bus->IIC_SDA_PIN << 16U;
    }
}

/**
  * @brief SCL线输出一个位
  * @param val 输出的数据
  * @retval None
  */
void SCL_Output(iic_bus_t *bus, uint16_t val)
{
    if ( val )
    {
        bus->IIC_SCL_PORT->BSRR |= bus->IIC_SCL_PIN;
    }
    else
    {
         bus->IIC_SCL_PORT->BSRR = (uint32_t)bus->IIC_SCL_PIN << 16U;
    }
}

/**
  * @brief SDA输入一位
  * @param None
  * @retval GPIO读入一位
  */
uint8_t SDA_Input(iic_bus_t *bus)
{
	if(HAL_GPIO_ReadPin(bus->IIC_SDA_PORT, bus->IIC_SDA_PIN) == GPIO_PIN_SET){
		return 1;
	}else{
		return 0;
	}
}

/**
  * @brief IIC起始信号
  * @param None
  * @retval None
  */
void IIC_Start(iic_bus_t *bus)
{
    SDA_Output(bus,1);
    //delay1(DELAY_TIME);
		Delay_us(2);
    SCL_Output(bus,1);
		Delay_us(1);
    SDA_Output(bus,0);
		Delay_us(1);
    SCL_Output(bus,0);
		Delay_us(1);
}

/**
  * @brief IIC结束信号
  * @param None
  * @retval None
  */
void IIC_Stop(iic_bus_t *bus)
{
    SCL_Output(bus,0);
		Delay_us(2);
    SDA_Output(bus,0);
		Delay_us(1);
    SCL_Output(bus,1);
		Delay_us(1);
    SDA_Output(bus,1);
		Delay_us(1);

}

/**
  * @brief IIC等待确认信号
  * @param None
  * @retval None
  */
unsigned char IIC_Wait_Ack(iic_bus_t *bus)
{
    unsigned short cErrTime = 5;
    SDA_Input_Mode(bus);
    SCL_Output(bus,1);
    while(SDA_Input(bus))
    {
        cErrTime--;
				Delay_us(1);
        if (0 == cErrTime)
        {
            SDA_Output_Mode(bus);
            IIC_Stop(bus);
            return ERROR;
        }
    }
    SDA_Output_Mode(bus);
    SCL_Output(bus,0);
		Delay_us(2);
    return SUCCESS;
}

/**
  * @brief IIC发送确认信号
  * @param None
  * @retval None
  */
void IIC_Send_Ack(iic_bus_t *bus)
{
    SDA_Output(bus,0);
		Delay_us(1);
    SCL_Output(bus,1);
		Delay_us(1);
    SCL_Output(bus,0);
		Delay_us(1);
	
}

/**
  * @brief IIC发送非确认信号
  * @param None
  * @retval None
  */
void IIC_Send_NotAck(iic_bus_t *bus)
{
    SDA_Output(bus,1);
		Delay_us(1);
    SCL_Output(bus,1);
		Delay_us(1);
    SCL_Output(bus,0);
		Delay_us(2);

}

/**
  * @brief IIC发送一个字节
  * @param cSendByte 需要发送的字节
  * @retval None
  */
void IIC_Send_Byte(iic_bus_t *bus,unsigned char cSendByte)
{
    unsigned char  i = 8;
    while (i--)
    {
        SCL_Output(bus,0);
        Delay_us(2);
        SDA_Output(bus, cSendByte & 0x80);
				Delay_us(1);
        cSendByte += cSendByte;
				Delay_us(1);
        SCL_Output(bus,1);
				Delay_us(1);
    }
    SCL_Output(bus,0);
		Delay_us(2);
}

/**
  * @brief IIC接收一个字节
  * @param None
  * @retval 接收到的字节
  */
unsigned char IIC_Read_Byte(iic_bus_t *bus)
{
    unsigned char i = 8;
    unsigned char cR_Byte = 0;
    SDA_Input_Mode(bus);
    while (i--)
    {
        cR_Byte += cR_Byte;
        SCL_Output(bus,0);
				Delay_us(2);
        SCL_Output(bus,1);
				Delay_us(1);
        cR_Byte |=  SDA_Input(bus);
    }
    SCL_Output(bus,0);
    SDA_Output_Mode(bus);
    return cR_Byte;
}

uint8_t IIC_Write_One_Byte(iic_bus_t *bus, uint8_t daddr,uint8_t reg,uint8_t data)
{				   	  	    																 
  IIC_Start(bus);  
	
	IIC_Send_Byte(bus,daddr<<1);	    
	if(IIC_Wait_Ack(bus))	//等待应答
	{
		IIC_Stop(bus);		 
		return 1;		
	}
	IIC_Send_Byte(bus,reg);
	IIC_Wait_Ack(bus);	   	 										  		   
	IIC_Send_Byte(bus,data);     						   
	IIC_Wait_Ack(bus);  		    	   
  IIC_Stop(bus);
	Delay_us(1);
	return 0;
}

uint8_t IIC_Write_Multi_Byte(iic_bus_t *bus, uint8_t daddr,uint8_t reg,uint8_t length,uint8_t buff[])
{			
	unsigned char i;	
  IIC_Start(bus);  
	
	IIC_Send_Byte(bus,daddr<<1);	    
	if(IIC_Wait_Ack(bus))
	{
		IIC_Stop(bus);
		return 1;
	}
	IIC_Send_Byte(bus,reg);
	IIC_Wait_Ack(bus);	
	for(i=0;i<length;i++)
	{
		IIC_Send_Byte(bus,buff[i]);     						   
		IIC_Wait_Ack(bus); 
	}		    	   
  IIC_Stop(bus);
	Delay_us(1);
	return 0;
} 

unsigned char IIC_Read_One_Byte(iic_bus_t *bus, uint8_t daddr,uint8_t reg)
{
	unsigned char dat;
	IIC_Start(bus);
	IIC_Send_Byte(bus,daddr<<1);
	IIC_Wait_Ack(bus);
	IIC_Send_Byte(bus,reg);
	IIC_Wait_Ack(bus);
	
	IIC_Start(bus);
	IIC_Send_Byte(bus,(daddr<<1)+1);
	IIC_Wait_Ack(bus);
	dat = IIC_Read_Byte(bus);
	IIC_Send_NotAck(bus);
	IIC_Stop(bus);
	return dat;
}


uint8_t IIC_Read_Multi_Byte(iic_bus_t *bus, uint8_t daddr, uint8_t reg, uint8_t length, uint8_t buff[])
{
	unsigned char i;
	IIC_Start(bus);
	IIC_Send_Byte(bus,daddr<<1);
	if(IIC_Wait_Ack(bus))
	{
		IIC_Stop(bus);		 
		return 1;		
	}
	IIC_Send_Byte(bus,reg);
	IIC_Wait_Ack(bus);
	
	IIC_Start(bus);
	IIC_Send_Byte(bus,(daddr<<1)+1);
	IIC_Wait_Ack(bus);
	for(i=0;i<length;i++)
	{
		buff[i] = IIC_Read_Byte(bus);
		if(i<length-1)
		{IIC_Send_Ack(bus);}
	}
	IIC_Send_NotAck(bus);
	IIC_Stop(bus);
	return 0;
}


//
void IIC_Init(iic_bus_t *bus)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    GPIO_InitStructure.Pin = bus->IIC_SDA_PIN ;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(bus->IIC_SDA_PORT, &GPIO_InitStructure);
		
		GPIO_InitStructure.Pin = bus->IIC_SCL_PIN ;
    HAL_GPIO_Init(bus->IIC_SCL_PORT, &GPIO_InitStructure);
}
