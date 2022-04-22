 /**
 * @file statemachine.c
 * @author Elizabeth Atkinson (eatkinso@illinois.edu)
 * @brief Bike anti-theft device project state machine
 * @date 2022-04-19
 *
 */

#include "statemachine.h"

void run_statemachine(UART_HandleTypeDef * gpsuart, UART_HandleTypeDef * rfiduart){
	statemachine_state_t mystate = IDLE;

	while (1){
		switch (mystate){
		case IDLE:
			break;
		case UNLOCKED:
			break;
		case TRANSIT:
			break;
		case ALARM:
			break;
		case FAULT:
			break;

		}
	}
}

