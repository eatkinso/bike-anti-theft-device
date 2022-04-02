/**
  ******************************************************************************
  * @file    sfu_low_level_flash_ext.c
  * @author  MCD Application Team
  * @brief   SFU Flash Low Level Interface module
  *          This file provides set of firmware functions to manage SFU external
  *          flash low level interface.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "sfu_low_level_flash_ext.h"
#include "sfu_low_level_security.h"

/* Private defines -----------------------------------------------------------*/

/* Functions Definition ------------------------------------------------------*/

/* No external flash available on this product
   ==> return SFU_ERROR except for SFU_LL_FLASH_EXT_Init and SFU_LL_FLASH_EXT_Config_Exe which are called
       systematically during startup phase */

SFU_ErrorStatus SFU_LL_FLASH_EXT_Init(void)
{
  return SFU_SUCCESS;
}

SFU_ErrorStatus SFU_LL_FLASH_EXT_Erase_Size(SFU_FLASH_StatusTypeDef *pFlashStatus, uint8_t *pStart, uint32_t Length)
{
  UNUSED(pFlashStatus);
  UNUSED(pStart);
  UNUSED(Length);
  return SFU_ERROR;
}

SFU_ErrorStatus SFU_LL_FLASH_EXT_Write(SFU_FLASH_StatusTypeDef *pFlashStatus, uint8_t  *pDestination,
                                       const uint8_t *pSource, uint32_t Length)
{
  UNUSED(pFlashStatus);
  UNUSED(pDestination);
  UNUSED(pSource);
  UNUSED(Length);
  return SFU_ERROR;
}

SFU_ErrorStatus SFU_LL_FLASH_EXT_Read(uint8_t *pDestination, const uint8_t *pSource, uint32_t Length)
{
  UNUSED(pDestination);
  UNUSED(pSource);
  UNUSED(Length);
  return SFU_ERROR;
}

SFU_ErrorStatus SFU_LL_FLASH_EXT_Compare(const uint8_t *pFlash, const uint32_t Pattern1, const uint32_t Pattern2, uint32_t Length)
{
  UNUSED(pFlash);
  UNUSED(Pattern1);
  UNUSED(Pattern2);
  UNUSED(Length);
  return SFU_ERROR;
}
SFU_ErrorStatus SFU_LL_FLASH_EXT_Config_Exe(uint32_t SlotNumber)
{
  UNUSED(SlotNumber);
  return SFU_SUCCESS;
}