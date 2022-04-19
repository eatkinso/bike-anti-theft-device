/**
 * @file vluart.h
 * @author Logan Power (lmpower2@illinois.edu)
 * @brief Functions for DMA-based variable-length UART.
 * @version 0.1
 * @date 2019-07-29
 * 
 * @copyright Copyright (c) 2019 Laboratory for Advanced Space Systems at Illinois.
 * @license Released under the terms of the University of Illinois/NCSA License.
 */

// Files to include
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// Conditional Includes based on MCU version
#ifdef STM32L0 
#include "stm23l0xx.h"
#endif /* STM32L0 */
#ifdef STM32G0 
#include "stm32g0xx.h"
#include "stm32g0xx_hal.h"
#endif /* STM32G0 */
#ifdef STM32L4
#include "stm32l4xx.h"
#endif /* STM32L4 */

// Globals
extern uint8_t BUFFER_LENGTH;

// Function prototypes
void VLU_Init(UART_HandleTypeDef * huart, uint8_t * working_buffer, uint8_t * byte_buffer, uint8_t buffer_len);
void VLU_IdleLineHandler(UART_HandleTypeDef * huart, 
                          DMA_HandleTypeDef * hdma, 
                          uint8_t * working_buffer, 
                          uint8_t * byte_buffer,
                          void (*msgproc)(uint8_t *));
