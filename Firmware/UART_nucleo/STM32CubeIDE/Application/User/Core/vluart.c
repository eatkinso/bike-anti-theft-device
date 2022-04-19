/**
 * @file vluart.c
 * @author Logan Power (lmpower2@illinois.edu)
 * @brief Functions for DMA-based variable-length UART.
 * @version 0.1
 * @date 2019-07-29
 * 
 * @copyright Copyright (c) 2019 Laboratory for Advanced Space Systems at Illinois.
 * @license Released under the terms of the University of Illinois/NCSA License.
 */

#include "vluart.h"

uint8_t BUFFER_LENGTH;

/**
 * @brief Perform some basic preparation tasks, and begin listening to serial.
 * 
 * @param huart Handle of serial peripheral to use.
 * @param working_buffer Buffer that the interpreter should operate on.  Pointer to an array/memory block of length buffer_len bytes.
 * @param byte_buffer Buffer that the DMA controller writes to.  Pointer to an array/memory block of length buffer_len bytes.
 * @param buffer_len Length of the buffer arrays.  This is also set in the global to be the maximum single message length.
 * 
 * Note that this function will cause an idle line interrupt to be fired immediately after it completes.
 * This behavior is intentional, as that interrupt will return no data but disable again until more data is received.
 */
void VLU_Init(UART_HandleTypeDef * huart, uint8_t * working_buffer, uint8_t * byte_buffer, uint8_t buffer_len)
{
  // Clear the buffers.
  memset(byte_buffer, 0, buffer_len);
  memset(byte_buffer, 0, buffer_len);
  // Set the global buffer length.
  BUFFER_LENGTH = buffer_len;
  // Start reading and enable the interrupt.
  HAL_UART_Receive_DMA(huart, byte_buffer, buffer_len);
  __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
}

/**
 * @brief Function to be inserted into the UART interrupt callback function.
 * 
 * @param huart Handle for UART device that was the one being interrupted.
 * @param hdma Handle for DMA controller that is reading the UART device.
 * @param working_buffer Pointer to working buffer, i.e. the one the message handler will process from.
 * @param byte_buffer Pointer to the byte buffer, i.e. the one that the DMA controller will write to.
 */
void VLU_IdleLineHandler(UART_HandleTypeDef * huart, 
                          DMA_HandleTypeDef * hdma, 
                          uint8_t * working_buffer, 
                          uint8_t * byte_buffer,
                          void (*msgproc)(uint8_t *))
{
  // Check to see if the IDLE bit is flipped.
  // This mask isolates the IDLE bit.
  // uint32_t mask = 0b00000000000000000000000000010000;
  uint32_t mask = 0x00000010;
  if (huart->Instance->ISR && mask) {
    // The IDLE bit is flipped, so this was an IDLE interrupt.
    // Turn the IDLE bit off.
    huart->Instance->ICR |= mask;
    /* WORKAROUND for the first byte missing thing.  
    If we have only read one byte, don't treat it as a separate message. */
    if (hdma->Instance->CNDTR >= BUFFER_LENGTH-1) goto endirq;
    // Copy the message to the working buffer.
    memcpy(working_buffer, byte_buffer, BUFFER_LENGTH);
    memset(byte_buffer, 0, BUFFER_LENGTH);
    // Attempt to reset the DMA controller
    HAL_UART_DMAPause(huart);
    hdma->Instance->CCR &= -2;
    hdma->Instance->CNDTR = BUFFER_LENGTH;
    hdma->Instance->CCR |= 1;
    HAL_UART_DMAResume(huart);
    // Run the message processing subroutine.
    msgproc(working_buffer);
    // The message processing routine is responsible for resetting the working buffer when it is done.
  }
  endirq:
  HAL_UART_IRQHandler(huart);
}