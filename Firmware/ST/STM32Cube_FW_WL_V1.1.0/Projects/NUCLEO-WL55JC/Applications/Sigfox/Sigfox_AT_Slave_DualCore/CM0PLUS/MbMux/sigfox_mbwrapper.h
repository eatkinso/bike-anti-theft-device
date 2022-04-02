/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sigfox_mbwrapper.h
  * @author  MCD Application Team
  * @brief   This file implements the CM0 side wrapper of the SigfoxMac interface
  *          shared between M0 and M4.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#ifndef __SIGFOX_MBWRAPPER_CM0PLUS_H__
#define __SIGFOX_MBWRAPPER_CM0PLUS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "mbmux_table.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/

/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Process_Sigfox_Cmd(MBMUX_ComParam_t *ComObj);

/*!
  * @brief   Measures the battery level
  * @return  Battery level [0: node is connected to an external
  *          power source, 1..254: battery level, where 1 is the minimum
  *          and 254 is the maximum value, 255: the node was not able
  *          to measure the battery level]
  */
uint16_t GetBatteryLevel_mbwrapper(void);

/*!
  * @brief   Measures the temperature level
  * @return  Temperature level
  */
int16_t GetTemperatureLevel_mbwrapper(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /*__SIGFOX_MBWRAPPER_CM0PLUS_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
