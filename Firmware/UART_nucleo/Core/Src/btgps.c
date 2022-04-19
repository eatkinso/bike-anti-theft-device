 
/**
 * @file gps.c
 * @author Elizabeth Atkinson (eatkinso@illinois.edu)
 * @brief GPS NMEA parser
 * @version 0.1
 * @date 2022-04-19
 *
 * @copyright (c) 2022 Elizabeth Atkinson
 * @license Released under the terms of the University of Illinois/NCSA License.
 */

#include "gps.h"
#include "main.h"

/**
  * @brief Query the GPS for a GPGGA packet (UTC time, lat, long).
  * @param huart UART handle for the GPS
  * @param msgbuf pointer to the struct to store the final message
  * @retval 0 on success, 1 on failure
  */
int get_gps(UART_HandleTypeDef * huart, nmea_gpgga_t * msgbuf){
	int dollar=0;
	uint8_t raw[100] = {0};
	// query the GGA message from the GPS.
	char queryGGA[]= "$PSRF103,00,01,10,00,\r\n";

	HAL_UART_Transmit(huart, (uint8_t *)queryGGA, 25, 100);
		for (int i =0; i<90; i++){
			HAL_UART_Receive(huart, &raw[i], 1, 1000);
		  }
		__asm__("nop");
	return 0;
}
