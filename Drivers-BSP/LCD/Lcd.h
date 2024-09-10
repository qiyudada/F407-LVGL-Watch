#ifndef __LCD_H
#define __LCD_H

#include "stm32f4xx_hal.h"
#include "main.h"
#include <stdlib.h>
#include "Delay.h"
// #include "lvgl.h"

// LCD重要参数集
typedef struct
{
    uint16_t width;   // LCD 宽度
    uint16_t height;  // LCD 高度
    uint16_t id;      // LCD ID
    uint8_t dir;      // 横屏还是竖屏控制：0，竖屏；1，横屏。
    uint16_t wramcmd; // 开始写gram指令
    uint16_t rramcmd; // 开始读gram指令
    uint16_t setxcmd; // 设置x坐标指令
    uint16_t setycmd; // 设置y坐标指令
} _lcd_dev;
// LCD参数
extern _lcd_dev lcddev; // 管理LCD重要参数

//-----------------LCD端口定义----------------
/*Define at main.h which created in stm32cubemx*/
#define LCD_LED(N) HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, N == 1 ? GPIO_PIN_SET : GPIO_PIN_RESET) // LCD背光

/* FSMC相关参数 定义
 * 注意: 我们默认是通过FSMC块1来连接LCD, 块1有4个片选: FSMC_NE1~4
 *
 * 修改LCD_FSMC_NEX, 对应的LCD_CS_GPIO相关设置也得改
 * 修改LCD_FSMC_AX , 对应的LCD_RS_GPIO相关设置也得改
 */
#define LCD_FSMC_NEX    (4) /* 使用FSMC_NE4接LCD_CS,取值范围只能是: 1~4 */
#define LCD_FSMC_AX     (12) /* 使用FSMC_A6接LCD_RS,取值范围是: 0 ~ 25 */


#define LCD_FSMC_BCRX        FSMC_Bank1->BTCR[(LCD_FSMC_NEX - 1) * 2]       /* BCR寄存器,根据LCD_FSMC_NEX自动计算 */
#define LCD_FSMC_BTRX        FSMC_Bank1->BTCR[(LCD_FSMC_NEX - 1) * 2 + 1]   /* BTR寄存器,根据LCD_FSMC_NEX自动计算 */
#define LCD_FSMC_BWTRX       FSMC_Bank1E->BWTR[(LCD_FSMC_NEX - 1) * 2]      /* BWTR寄存器,根据LCD_FSMC_NEX自动计算 */

/* LCD_BASE的详细解算方法:
 * 我们一般使用FSMC的块1(BANK1)来驱动TFTLCD液晶屏(MCU屏), 块1地址范围总大小为256MB,均分成4块:
 * 存储块1(FSMC_NE1)地址范围: 0x6000 0000 ~ 0x63FF FFFF
 * 存储块2(FSMC_NE2)地址范围: 0x6400 0000 ~ 0x67FF FFFF
 * 存储块3(FSMC_NE3)地址范围: 0x6800 0000 ~ 0x6BFF FFFF
 * 存储块4(FSMC_NE4)地址范围: 0x6C00 0000 ~ 0x6FFF FFFF
 *-----------------------------------------------------------------------------------------
 * LCD->LCD_REG,对应LCD_RS = 0(LCD寄存器); LCD->LCD_RAM,对应LCD_RS = 1(LCD数据)
 * 则 LCD->LCD_RAM的地址为:  0x6C00 0000 + 2^6 * 2 = 0x6C00 0080
 *    LCD->LCD_REG的地址可以为 LCD->LCD_RAM之外的任意地址.
 * 由于我们使用结构体管理LCD_REG 和 LCD_RAM(REG在前,RAM在后,均为16位数据宽度)
 * 因此 结构体的基地址(LCD_BASE) = LCD_RAM - 2 = 0x6C00 0080 -2
 *-----------------------------------------------------------------------------------------
 * 更加通用的计算公式为((片选脚FSMC_NEX)X=1/2/3/4, (RS接地址线FSMC_Ay)y=0~25):
 *          LCD_BASE = (0x6000 0000 + (0x400 0000 * (x - 1))) | (2^y * 2 -2)
 *          等效于(使用移位操作)
 *          LCD_BASE = (0x6000 0000 + (0x400 0000 * (x - 1))) | ((1 << y) * 2 -2)
 */
#define LCD_BASE (uint32_t)((0x60000000 + (0x4000000 * (LCD_FSMC_NEX - 1))) | (((1 << LCD_FSMC_AX) * 2) - 2))
#define LCD ((LCD_TypeDef *)LCD_BASE)


/******************************User Configuration****************************************** */
#define USE_HORIZONTAL 0    // 定义液晶屏顺时针旋转方向 	0-0度旋转，1-90度旋转，2-180度旋转，3-270度旋转
#define LCD_USE8BIT_MODEL 0 // 定义数据总线是否使用8位模式 0,使用16位模式.1,使用8位模式
/********************************************************************************** */
// 定义LCD的尺寸
#define LCD_W 240
#define LCD_H 320

// TFTLCD部分外要调用的函数
extern uint16_t POINT_COLOR; // 默认红色
extern uint16_t BACK_COLOR;  // 背景颜色.默认为白色

// LCD地址结构体
typedef struct
{
    volatile uint16_t LCD_REG;
    volatile uint16_t LCD_RAM;
} LCD_TypeDef;

// 画笔颜色
#define WHITE   0xFFFF
#define BLACK   0x0000
#define BLUE    0x001F
#define BRED    0XF81F
#define GRED    0XFFE0
#define GBLUE   0X07FF
#define RED     0xF800
#define MAGENTA 0xF81F  //Purple
#define GREEN   0x07E0  
#define CYAN    0x7FFF
#define YELLOW  0xFFE0
#define BROWN   0XBC40  // 棕色
#define BRRED   0XFC07  // 棕红色
#define GRAY    0X8430  // 灰色

// GUI颜色
#define DARKBLUE 0X01CF  // 深蓝色
#define LIGHTBLUE 0X7D7C // 浅蓝色
#define GRAYBLUE 0X5458  // 灰蓝色

// 以上三色为PANEL的颜色
#define LIGHTGREEN 0X841F // 浅绿色
#define LIGHTGRAY 0XEF5B  // 浅灰色(PANNEL)
#define LGRAY 0XC618      // 浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE 0XA651  // 浅灰蓝色(中间层颜色)
#define LBBLUE 0X2B12     // 浅棕蓝色(选择条目的反色)

/********************************************************************************** */

void LCD_Init(void);

uint16_t LCD_read(void);

void LCD_Clear(uint16_t Color);

void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);

void LCD_DrawPoint(uint16_t x, uint16_t y);

uint16_t LCD_ReadPoint(uint16_t x, uint16_t y);

void LCD_SetWindows(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd);

uint16_t LCD_RD_DATA(void);

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);

void LCD_WR_REG(uint16_t data);

void LCD_WR_DATA(uint16_t data);

void LCD_ReadReg(uint16_t LCD_Reg, uint8_t *Rval, int n);

void LCD_WriteRAM_Prepare(void);

void LCD_ReadRAM_Prepare(void);

void Lcd_WriteData_16Bit(uint16_t Data);

uint16_t Lcd_ReadData_16Bit(void);

void LCD_direction(uint8_t direction);

uint16_t Color_To_565(uint8_t r, uint8_t g, uint8_t b);

uint16_t LCD_Read_ID(void);

#endif
