/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "btrfid.h"
#include "btgps.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef enum states{
	BT_IDLE,
	BT_UNLOCKED,
	BT_TRANSIT,
	BT_ALARM,
	BT_SFAULT
} statemachine_state_t;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ALARM_Pin GPIO_PIN_5
#define ALARM_GPIO_Port GPIOB
#define IDLE_Pin GPIO_PIN_8
#define IDLE_GPIO_Port GPIOB
#define TRANSIT_Pin GPIO_PIN_0
#define TRANSIT_GPIO_Port GPIOA
#define UNLOCKED_Pin GPIO_PIN_1
#define UNLOCKED_GPIO_Port GPIOA
#define GPS_NPWR_Pin GPIO_PIN_5
#define GPS_NPWR_GPIO_Port GPIOA
#define RFiD_NPWR_Pin GPIO_PIN_6
#define RFiD_NPWR_GPIO_Port GPIOA
#define RFID_TAG_IN_RANGE_Pin GPIO_PIN_7
#define RFID_TAG_IN_RANGE_GPIO_Port GPIOA
#define RFSW_VC2_Pin GPIO_PIN_2
#define RFSW_VC2_GPIO_Port GPIOB
#define GET_GPS_Pin GPIO_PIN_12
#define GET_GPS_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
