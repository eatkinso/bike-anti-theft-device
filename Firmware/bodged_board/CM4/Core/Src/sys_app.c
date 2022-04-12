/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    sys_app.c
  * @author  MCD Application Team
  * @brief   Initializes HW and SW system entities (not related to the radio)
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

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "platform.h"
#include "sys_app.h"
#include "stm32_seq.h"
#include "stm32_systime.h"
#include "stm32_lpm.h"
#include "timer_if.h"
#include "utilities_def.h"
#include "msg_id.h"
#include "mbmuxif_sys.h"
#include "mbmuxif_trace.h"
#include "mbmuxif_radio.h"
#include "mbmuxif_lora.h"
#ifdef ALLOW_KMS_VIA_MBMUX /* currently not supported */
/* #include "mbmuxif_kms.h" */
#endif /* ALLOW_KMS_VIA_MBMUX */

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* External variables ---------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
#define MAX_TS_SIZE (int) 16

/**
  * Defines the maximum battery level
  */
#define LORAWAN_MAX_BAT   254
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
uint32_t InstanceIndex;
uint8_t SYS_Cm0plusRdyNotificationFlag = 0;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/**
  * @brief Initialize MBMUX, wait CM0PLUS is ready, gets CM0PLUS capabilities, Initialize other features
  */
static void MBMUXIF_Init(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Exported functions ---------------------------------------------------------*/
void SystemApp_Init(void)
{
  /* USER CODE BEGIN SystemApp_Init_1 */

  /* USER CODE END SystemApp_Init_1 */

  /*Initialize MBMux (to be done after LPM because MBMux uses the sequencer) */
  MBMUXIF_Init();

  /* USER CODE BEGIN SystemApp_Init_2 */

  /* USER CODE END SystemApp_Init_2 */
}

void Process_Sys_Notif(MBMUX_ComParam_t *ComObj)
{
  /* USER CODE BEGIN Process_Sys_Notif_1 */

  /* USER CODE END Process_Sys_Notif_1 */
  uint32_t  notif_ack_id;

  notif_ack_id = ComObj->MsgId;

  switch (notif_ack_id)
  {
    case SYS_RTC_ALARM_MSG_ID:
      /* USER CODE BEGIN Process_Sys_Notif_RTC_ALARM */

      /* USER CODE END Process_Sys_Notif_RTC_ALARM */
      break;
    case SYS_OTHER_MSG_ID:
      APP_LOG(TS_ON, VLEVEL_H, "CM4<(System)\r\n");
      /* prepare ack buffer*/
      ComObj->ParamCnt = 0;
      ComObj->ReturnVal = 0; /* dummy value  */
      /* USER CODE BEGIN Process_Sys_Notif_OTHER */

      /* USER CODE END Process_Sys_Notif_OTHER */
      break;
    default:
      /* USER CODE BEGIN Process_Sys_Notif_DEFAULT */

      /* USER CODE END Process_Sys_Notif_DEFAULT */
      break;
  }

  /* Send ack*/
  APP_LOG(TS_ON, VLEVEL_H, "CM4>(System)\r\n");
  MBMUXIF_SystemSendAck(FEAT_INFO_SYSTEM_ID);
  /* USER CODE BEGIN Process_Sys_Notif_2 */

  /* USER CODE END Process_Sys_Notif_2 */
}

void UTIL_SEQ_EvtIdle(uint32_t TaskId_bm, uint32_t EvtWaited_bm)
{
  /**
    * overwrites the __weak UTIL_SEQ_EvtIdle() in stm32_seq.c
    * all to process all tack except TaskId_bm
    */
  /* USER CODE BEGIN UTIL_SEQ_EvtIdle_1 */

  /* USER CODE END UTIL_SEQ_EvtIdle_1 */
  UTIL_SEQ_Run(~TaskId_bm);
  /* USER CODE BEGIN UTIL_SEQ_EvtIdle_2 */

  /* USER CODE END UTIL_SEQ_EvtIdle_2 */
  return;
}

uint8_t GetBatteryLevel(void)
{
  uint8_t batteryLevel = 0;

  /* USER CODE BEGIN GetBatteryLevel_0 */

  /* USER CODE END GetBatteryLevel_0 */

  return batteryLevel;  /* 1 (very low) to 254 (fully charged) */
}

uint16_t GetTemperatureLevel(void)
{
  uint16_t temperatureLevel = 0;

  /* USER CODE BEGIN GetTemperatureLevel */

  /* USER CODE END GetTemperatureLevel */
  return temperatureLevel;
}

/* USER CODE BEGIN EF */

/* USER CODE END EF */

/* Private functions ---------------------------------------------------------*/
static void MBMUXIF_Init(void)
{
  /* USER CODE BEGIN MBMUXIF_Init_1 */

  /* USER CODE END MBMUXIF_Init_1 */
  FEAT_INFO_List_t *p_cm0plus_supported_features_list;
  int8_t init_status;

  APP_LOG(TS_ON, VLEVEL_H, "\r\nCM4: System Initialization started \r\n");

  init_status = MBMUXIF_SystemInit();
  if (init_status < 0)
  {
    Error_Handler();
  }

  /* start CM0PLUS */
  /* Note: when debugging in order to connect with the debugger CPU2 shall be start using workspace CM4 starts CM0PLUS */
  /* On the other hand is up to the developer make sure the CM0PLUS debugger is run after CM4 debugger */
  HAL_PWREx_ReleaseCore(PWR_CORE_CPU2);

  /* CM4 has started and it has reset the mailbox and initialized the MbMux; */
  /* once CM0PLUS is also initialized it send a SYS notification */
  MBMUXIF_SetCpusSynchroFlag(CPUS_BOOT_SYNC_ALLOW_CPU2_TO_START);

  APP_LOG(TS_ON, VLEVEL_H, "CM4: System Initialization done: Wait for CM0PLUS \r\n");

  MBMUXIF_WaitCm0MbmuxIsInitialized();

  APP_LOG(TS_ON, VLEVEL_H, "CM0PLUS: System Initialization started \r\n");

  p_cm0plus_supported_features_list = MBMUXIF_SystemSendCm0plusInfoListReq();
  MBMUX_SetCm0plusFeatureListPtr(p_cm0plus_supported_features_list);

  APP_LOG(TS_ON, VLEVEL_H, "System Initialization CM4-CM0PLUS completed \r\n");

  MBMUXIF_SetCpusSynchroFlag(CPUS_BOOT_SYNC_RTC_REGISTERED);
  APP_LOG(TS_ON, VLEVEL_H, "System_Priority_A Registration for RTC Alarm handling completed \r\n");

  init_status = MBMUXIF_LoraInit();
  if (init_status < 0)
  {
    Error_Handler();
  }
  APP_LOG(TS_ON, VLEVEL_H, "Radio registration CM4-CM0PLUS completed \r\n");

  /* USER CODE BEGIN MBMUXIF_Init_Last */

  /* USER CODE END MBMUXIF_Init_Last */
}
/* USER CODE BEGIN PrFD */

/* USER CODE END PrFD */

/* HAL overload functions ---------------------------------------------------------*/

/* Use #if 0 if you want to keep the default HAL instead overcharge them*/
/* USER CODE BEGIN Overload_HAL_weaks_1 */
#if 1
/* USER CODE END Overload_HAL_weaks_1 */

/**
  * @note This function overwrites the __weak one from HAL
  */
uint32_t HAL_GetTick(void)
{
  /* TIMER_IF can be based on other counter the SysTick e.g. RTC */
  /* USER CODE BEGIN HAL_GetTick_1 */

  /* USER CODE END HAL_GetTick_1 */
  return TIMER_IF_GetTimerValue();
  /* USER CODE BEGIN HAL_GetTick_2 */

  /* USER CODE END HAL_GetTick_2 */
}

/**
  * @note This function overwrites the __weak one from HAL
  */
void HAL_Delay(__IO uint32_t Delay)
{
  /* TIMER_IF can be based on other counter the SysTick e.g. RTC */
  /* USER CODE BEGIN HAL_Delay_1 */

  /* USER CODE END HAL_Delay_1 */
  TIMER_IF_DelayMs(Delay);
  /* USER CODE BEGIN HAL_Delay_2 */

  /* USER CODE END HAL_Delay_2 */
}
/* USER CODE BEGIN Overload_HAL_weaks_2 */
#endif
/* Redefine here your own if needed */

/* USER CODE END Overload_HAL_weaks_2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
