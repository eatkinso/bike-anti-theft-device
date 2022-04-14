/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32wlxx_hal.h"
#include "bt_radio.h"

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
#define RFID_NRST_Pin GPIO_PIN_5
#define RFID_NRST_GPIO_Port GPIOB
#define RFID_DATA1_Pin GPIO_PIN_1
#define RFID_DATA1_GPIO_Port GPIOA
#define ALARM_ON_Pin GPIO_PIN_2
#define ALARM_ON_GPIO_Port GPIOA
#define RFSW_VC1_Pin GPIO_PIN_3
#define RFSW_VC1_GPIO_Port GPIOA
#define GPS_NPWR_Pin GPIO_PIN_5
#define GPS_NPWR_GPIO_Port GPIOA
#define RFiD_NPWR_Pin GPIO_PIN_6
#define RFiD_NPWR_GPIO_Port GPIOA
#define RFID_TAG_IN_RANGE_Pin GPIO_PIN_7
#define RFID_TAG_IN_RANGE_GPIO_Port GPIOA
#define RFSW_VC2_Pin GPIO_PIN_2
#define RFSW_VC2_GPIO_Port GPIOB
#define RFID_DATA0_Pin GPIO_PIN_12
#define RFID_DATA0_GPIO_Port GPIOB
#define GPS_STATE_Pin GPIO_PIN_11
#define GPS_STATE_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
