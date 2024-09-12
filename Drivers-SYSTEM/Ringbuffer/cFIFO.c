#include "cFIFO.h"

/*环形CFIFO初始化*/
void CfifoBuff_Init(CfifoBuff *Cfifo_pointer)
{
    // 初始化相关信息
    Cfifo_pointer->Head = 0;
    Cfifo_pointer->Tail = 0;
    Cfifo_pointer->Lenght = 0;
    memset(Cfifo_pointer->BUFF, '\0', CFIFO_SIZE); // 环形CFIFO缓存区初始化
}

/*环形CFIFO数据清除*/
void CfifoBuff_Clear(CfifoBuff *Cfifo_pointer)
{
    // 清除相关信息
    Cfifo_pointer->Head = 0;
    Cfifo_pointer->Tail = 0;
    Cfifo_pointer->Lenght = 0;
    memset(Cfifo_pointer->BUFF, '\0', CFIFO_SIZE); // 环形CFIFO缓存区清除
}

/*环形CFIFO数据写入*/
/*
 *参数说明:
 *         Cfifo_pointer————环形CFIFO结构体
 *         User_buff————待写入数据
 *         num————写入数据长度
 *
 *返回值说明：正确写入到FIFO缓存区中的数据长度
 *
 *功能说明：将User_buff中的数据写入到环形CFIFO缓存区
 *
 */
int16_t CfifoBuff_Write(CfifoBuff *Cfifo_pointer, char *User_buff, uint16_t num)
{
    int16_t i, wrint_num;

    if (Cfifo_pointer->Lenght >= CFIFO_SIZE) // 判断缓存区是否已满
    {
        wrint_num = -1;

        return wrint_num; // 数据溢出
    }

    if (Cfifo_pointer->Lenght + num < CFIFO_SIZE) // 判断写入的数据长度是否超出当前可写入的最大值
    {
        wrint_num = num;
    }
    else
    {
        wrint_num = CFIFO_SIZE - Cfifo_pointer->Lenght;
    }

    for (i = 0; i < wrint_num; i++)
    {
        Cfifo_pointer->BUFF[Cfifo_pointer->Tail] = *(User_buff + i);

        Cfifo_pointer->Tail = (Cfifo_pointer->Tail + 1) % CFIFO_SIZE; // 防止越界非法访问
    }

    Cfifo_pointer->Lenght += wrint_num;

    return wrint_num; // 返回正确写入的数据长度
}

/*环形CFIFO读取*/
/*
 *参数说明:
 *         Cfifo_pointer————环形CFIFO结构体
 *         User_buff————读取数据存放地
 *         num————读取数据长度
 *
 *返回值说明：正确读取到User_buff的数据长度
 *
 *功能说明：将环形CFIFO缓存区的数据读取到User_buff
 *
 */
int16_t CfifoBuff_Read(CfifoBuff *Cfifo_pointer, char *User_buff, uint16_t num)
{
    int16_t i, read_num;

    if (Cfifo_pointer->Lenght == 0) // 判断非空
    {
        read_num = -1;

        return read_num; // 没有数据
    }

    if (Cfifo_pointer->Lenght - num >= 0) // 判断读取的数据长度是否超出当前可读取的最大值
    {
        read_num = num;
    }
    else
    {
        read_num = Cfifo_pointer->Lenght;
    }

    for (i = 0; i < read_num; i++)
    {
        *(User_buff + i) = Cfifo_pointer->BUFF[Cfifo_pointer->Head];

        Cfifo_pointer->Head = (Cfifo_pointer->Head + 1) % CFIFO_SIZE; // 防止越界非法访问
    }

    Cfifo_pointer->Lenght -= read_num;

    return read_num; // 返回正确写入的数据长度
}
