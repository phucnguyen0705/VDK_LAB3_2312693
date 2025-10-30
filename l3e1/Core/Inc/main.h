/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define s0_Pin GPIO_PIN_0
#define s0_GPIO_Port GPIOA
#define s1_Pin GPIO_PIN_1
#define s1_GPIO_Port GPIOA
#define s2_Pin GPIO_PIN_2
#define s2_GPIO_Port GPIOA
#define s3_Pin GPIO_PIN_3
#define s3_GPIO_Port GPIOA
#define s4_Pin GPIO_PIN_4
#define s4_GPIO_Port GPIOA
#define s5_Pin GPIO_PIN_5
#define s5_GPIO_Port GPIOA
#define s6_Pin GPIO_PIN_6
#define s6_GPIO_Port GPIOA
#define dot_Pin GPIO_PIN_7
#define dot_GPIO_Port GPIOA
#define b1_Pin GPIO_PIN_0
#define b1_GPIO_Port GPIOB
#define b2_Pin GPIO_PIN_1
#define b2_GPIO_Port GPIOB
#define b3_Pin GPIO_PIN_2
#define b3_GPIO_Port GPIOB
#define l1_Pin GPIO_PIN_12
#define l1_GPIO_Port GPIOB
#define l2_Pin GPIO_PIN_13
#define l2_GPIO_Port GPIOB
#define l3_Pin GPIO_PIN_14
#define l3_GPIO_Port GPIOB
#define l4_Pin GPIO_PIN_15
#define l4_GPIO_Port GPIOB
#define snr_Pin GPIO_PIN_8
#define snr_GPIO_Port GPIOA
#define sny_Pin GPIO_PIN_9
#define sny_GPIO_Port GPIOA
#define sng_Pin GPIO_PIN_10
#define sng_GPIO_Port GPIOA
#define wer_Pin GPIO_PIN_11
#define wer_GPIO_Port GPIOA
#define wey_Pin GPIO_PIN_12
#define wey_GPIO_Port GPIOA
#define weg_Pin GPIO_PIN_13
#define weg_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
