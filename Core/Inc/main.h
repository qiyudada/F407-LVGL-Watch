/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "log.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_BL_Pin GPIO_PIN_10
#define LCD_BL_GPIO_Port GPIOF
#define RC522_RST_Pin GPIO_PIN_0
#define RC522_RST_GPIO_Port GPIOC
#define T_CLK_Pin GPIO_PIN_5
#define T_CLK_GPIO_Port GPIOA
#define T_CS_Pin GPIO_PIN_0
#define T_CS_GPIO_Port GPIOB
#define MOSI_Pin GPIO_PIN_1
#define MOSI_GPIO_Port GPIOB
#define MISO_Pin GPIO_PIN_2
#define MISO_GPIO_Port GPIOB
#define PEN_Pin GPIO_PIN_11
#define PEN_GPIO_Port GPIOF
#define BLE_EN_Pin GPIO_PIN_12
#define BLE_EN_GPIO_Port GPIOF
#define BLE_STATE_Pin GPIO_PIN_13
#define BLE_STATE_GPIO_Port GPIOF
#define BLE_TX_Pin GPIO_PIN_10
#define BLE_TX_GPIO_Port GPIOB
#define BLE_RX_Pin GPIO_PIN_11
#define BLE_RX_GPIO_Port GPIOB
#define KEY1_Pin GPIO_PIN_12
#define KEY1_GPIO_Port GPIOD
#define KEY1_EXTI_IRQn EXTI15_10_IRQn
#define KEY2_Pin GPIO_PIN_13
#define KEY2_GPIO_Port GPIOD
#define KEY2_EXTI_IRQn EXTI15_10_IRQn
#define RS_Pin GPIO_PIN_2
#define RS_GPIO_Port GPIOG
#define MPU6050_INT_Pin GPIO_PIN_5
#define MPU6050_INT_GPIO_Port GPIOG
#define MPU6050_INT_EXTI_IRQn EXTI9_5_IRQn
#define RC522_SDA_Pin GPIO_PIN_6
#define RC522_SDA_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_7
#define LED_GPIO_Port GPIOC
#define Serial_TX_Pin GPIO_PIN_9
#define Serial_TX_GPIO_Port GPIOA
#define Serial_RX_Pin GPIO_PIN_10
#define Serial_RX_GPIO_Port GPIOA
#define DTH11_Pin GPIO_PIN_3
#define DTH11_GPIO_Port GPIOD
#define RD_Pin GPIO_PIN_4
#define RD_GPIO_Port GPIOD
#define WR_Pin GPIO_PIN_5
#define WR_GPIO_Port GPIOD
#define LCD_CS_Pin GPIO_PIN_12
#define LCD_CS_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
