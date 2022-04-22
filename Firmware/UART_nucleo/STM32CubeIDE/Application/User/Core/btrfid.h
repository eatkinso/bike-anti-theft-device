/*
 * btrfid.h
 *
 *  Created on: Apr 19, 2022
 *      Author: eatkinso
 */

#ifndef BT_RFID_H
#define BT_RFID_H

#include "main.h"

int get_rfid(UART_HandleTypeDef * huart, char * msgbuf);


#endif
