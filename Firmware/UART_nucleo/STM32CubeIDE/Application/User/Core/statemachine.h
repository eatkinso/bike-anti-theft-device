 /**
 * @file statemachine.h
 * @author Elizabeth Atkinson (eatkinso@illinois.edu)
 * @date 2022-04-19
 *
 */

#ifndef STATEMACHINE
#define STATEMACHINE

#include "main.h"
typedef enum states{
	IDLE,
	UNLOCKED,
	TRANSIT,
	ALARM,
	FAULT
} statemachine_state_t;

void run_statemachine(UART_HandleTypeDef * gpsuart, UART_HandleTypeDef * rfiduart);








#endif
