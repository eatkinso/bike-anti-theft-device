/**
  ******************************************************************************
  * @file    PKA/PKA_ModularExponentiationCRT/Src/plaintext.c
  * @author  MCD Application Team
  * @brief   This file reflect the content of plaintext.bin.
  *          plaintext.bin has been created using openssl
  *            openssl rand 256 > plaintext.bin
  *            (256 correspond to 2048 bit, size of the modulus)
  *          plaintext.c has been created using xxd external tool in version V1.10 27oct98.
  *          Command line: 
  *            xxd -i plaintext.bin
  *          Additional modification for easier usage:
  *           Replaced unsigned char by const uint8_t
  *           Replaced unsigned int by const uin32_t
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the 
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "main.h"

const uint8_t plaintext_bin[] = {
  0x57, 0x82, 0x91, 0xe5, 0x9a, 0xa4, 0x96, 0x60, 0x65, 0x02, 0xa6, 0x67,
  0x1b, 0x82, 0x45, 0xef, 0xfd, 0x88, 0x0d, 0xc4, 0x00, 0x88, 0xe2, 0x30,
  0x8c, 0x39, 0x0d, 0x6a, 0x4b, 0xed, 0x0e, 0xa8, 0x11, 0x78, 0x40, 0x50,
  0x7b, 0x09, 0xab, 0xd8, 0xf2, 0x2a, 0x00, 0xb6, 0xb1, 0x87, 0x6c, 0xb0,
  0xb0, 0x14, 0x2f, 0x3a, 0x08, 0x7d, 0x0c, 0xa9, 0xb5, 0x4a, 0x16, 0x97,
  0x83, 0xc1, 0xa2, 0xc5, 0xda, 0xcb, 0x9b, 0x54, 0x79, 0x36, 0x3d, 0xc0,
  0x15, 0x03, 0xda, 0xfe, 0xd8, 0x4e, 0x56, 0xf2, 0x37, 0x49, 0xbd, 0xa2,
  0xf6, 0x65, 0x17, 0xb9, 0x87, 0xa9, 0x80, 0x38, 0xa9, 0x76, 0xc5, 0xde,
  0x7a, 0x77, 0xe4, 0x48, 0xb5, 0x43, 0x13, 0xfe, 0x4c, 0x19, 0xbb, 0x83,
  0xa2, 0xa8, 0x36, 0x7b, 0xdd, 0xf3, 0xca, 0x9d, 0xf3, 0x5a, 0x17, 0x00,
  0xa0, 0x6a, 0x7b, 0xa4, 0xcc, 0x23, 0x15, 0xdf, 0x3e, 0x6b, 0x83, 0xba,
  0x97, 0xe3, 0x7d, 0x57, 0xc9, 0x15, 0x34, 0xa9, 0xd1, 0x3c, 0x32, 0x4f,
  0x7f, 0x71, 0x07, 0x6b, 0x57, 0x60, 0xbb, 0x89, 0x93, 0x9d, 0x10, 0x84,
  0x31, 0x40, 0x90, 0x12, 0xe2, 0x3c, 0x4f, 0x9c, 0xd6, 0x57, 0x34, 0x2f,
  0xc5, 0x58, 0x9d, 0xc1, 0xf7, 0x2d, 0xff, 0x66, 0x4b, 0x00, 0x7a, 0x3f,
  0xcf, 0x87, 0x69, 0x19, 0x69, 0x58, 0x9c, 0xe1, 0xed, 0xcd, 0x36, 0x81,
  0xe4, 0x61, 0x7a, 0xcd, 0xb6, 0x61, 0x79, 0x9e, 0xba, 0xac, 0xde, 0x9b,
  0x1e, 0x7e, 0xe4, 0x9c, 0xce, 0x71, 0x0f, 0x84, 0xa6, 0x9a, 0x73, 0x93,
  0x70, 0xa8, 0xca, 0x36, 0x53, 0xaf, 0x4d, 0x83, 0xa6, 0xda, 0x92, 0xbe,
  0x39, 0x18, 0x41, 0x94, 0x5c, 0xff, 0x70, 0xcc, 0x4d, 0xa4, 0xfb, 0x8f,
  0xb1, 0x54, 0xeb, 0x66, 0x30, 0xf0, 0x29, 0xc6, 0x6b, 0xb1, 0xfc, 0xc5,
  0x6d, 0xc5, 0xfc, 0x93
};
const uint32_t plaintext_bin_len = 256;
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
