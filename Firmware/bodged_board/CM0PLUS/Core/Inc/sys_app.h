/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sys_app.h
  * @author  MCD Application Team
  * @brief   Function prototypes for sys_app.c file
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
#ifndef __SYS_APP_H__
#define __SYS_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "platform.h"
#include "mbmux_table.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported defines ----------------------------------------------------------*/
/* currently not supported */
/* #define ALLOW_KMS_VIA_MBMUX */

/* USER CODE BEGIN ED */

/* USER CODE END ED */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macros -----------------------------------------------------------*/
/* USER CODE BEGIN APP_PRINT */
#define APP_PRINTF(...)
#define APP_LOG(TS,VL,...)
/* USER CODE END APP_PRINT */

/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/**
  * @brief initialize MBMUXIF System and send a notification to Cm4 when ready
  */
void SystemApp_Init(void);

/**
  * @brief  callback to get the board 64 bits unique ID
  * @param  id unique ID
  */
void GetUniqueId(uint8_t *id);

/**
  * @brief  callback to get the board 32 bits unique ID (LSB)
  * @retval devAddr Device Address
  */
uint32_t GetDevAddr(void);

/**
  * @brief Returns sec and msec based on the systime in use
  * @param buff to update with timestamp
  * @param size of updated buffer
  */
void TimestampNow(uint8_t *buff, uint16_t *size);

/**
  * @brief  Process System Command
  * @param  ComObj exchange buffer parameter
  */
void Process_Sys_Cmd(MBMUX_ComParam_t *ComObj);
#ifdef ALLOW_KMS_VIA_MBMUX /* currently not supported */
/**
  * @brief  Process KMS Command
  * @param  ComObj exchange buffer parameter
  */
void Process_Kms_Cmd(MBMUX_ComParam_t *ComObj);
#endif /* ALLOW_KMS_VIA_MBMUX */

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* __SYS_APP_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
