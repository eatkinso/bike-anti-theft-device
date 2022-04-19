/*
 * gps.h
 *
 *  Created on: Apr 19, 2022
 *      Author: eatkinso
 */

#ifndef APPLICATION_USER_CORE_GPS_H_
#define APPLICATION_USER_CORE_GPS_H_

#include "main.h"

typedef struct {
	uint8_t UTC_Time[10]; // hhmmss.sss
	uint8_t latitude[9]; // ddmm.mmmm
	char NS; // North/South indicator
	uint8_t longitude[10]; // dddmm.mmmm
	char EW; // East/West indicator
	uint8_t pos_fix; // 0: fix invalid, 1: GPSSPS mode, fix valid, 2: Diff. GPS, fix valid, 3-5; res., 6: dead reckoning, fix valid
	uint8_t sat_used; // number of satellites used
	// there are more fields but we don't care about them
} nmea_gpgga_t;



int get_gps(UART_HandleTypeDef * huart, nmea_gpgga_t * msgbuf);


#endif /* APPLICATION_USER_CORE_GPS_H_ */

