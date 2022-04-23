 
/**
 * @file gps.c
 * @author Elizabeth Atkinson (eatkinso@illinois.edu)
 * @brief GPS NMEA parser
 * @version 0.1
 * @date 2022-04-19
 *
 */

#include "btgps.h"
#include "main.h"
#include <math.h>

/**
  * @brief Query the GPS for a GPGGA packet (UTC time, lat, long).
  * @param h.uart UART handle for the GPS
  * @param msgbuf pointer to the struct to store the final message
  * @retval 0 on success, 1 on failure
  */
int get_gps(UART_HandleTypeDef * huart, nmea_gpgga_t * msgbuf){
	char raw[100] = {"0"};
	typedef enum nmea_field{
		header,
		utc,
		lat,
		ns,
		lontd,
		ew,
		pfix,
		sat,
		nomsg,
		msgdone
	} nmea_field_t;
	nmea_field_t next_field=nomsg;
	int field_i = 0;
	// query the GGA message from the GPS.
	char queryGGA[]= "$PSRF103,00,01,10,00,\r\n";
	HAL_UART_Transmit(huart, (uint8_t *)queryGGA, 25, 100);
	// Receive bytes one-by-one into the raw buffer.
	for (int i =0; i<90; i++){
		HAL_UART_Receive(huart, (uint8_t *)&raw[i], 1, 1000);
	  }
	// Process the raw message buffer to get the message.
	for (int i=0; i<90; i++){
		switch(next_field){
			case nomsg	:
				// check for the $GPGGA that starts the message.
				if ((raw[i]=='$')&&(raw[i+1]=='G')&&(raw[i+2]=='P')&&(raw[i+3]=='G')&&(raw[i+4]=='G')&&(raw[i+5]=='A')){
					next_field=header; // increment to the next field
				}
				break;
			case header :
				if (raw[i] == ','){
					next_field=utc; // increment to the next field on the delimiter comma
					field_i = 0; // reset the field index
					break;
				}
				break;
			case utc	:
				if (raw[i] == ','){
					next_field=lat; // increment to the next field on the delimiter comma
					field_i = 0; // reset the field index
					break;
				}
				msgbuf->UTC_Time[field_i] = raw[i];
				field_i ++;
				break;
			case lat	:
				if (raw[i] == ','){
					next_field=ns; // increment to the next field on the delimiter comma
					field_i = 0; // reset the field index
					break;
				}
				msgbuf->latitude[field_i] = raw[i];
				field_i ++;
				break;
			case ns		:
				if (raw[i] == ','){
					next_field=lontd; // increment to the next field on the delimiter comma
					field_i = 0; // reset the field index
					break;
				}
				msgbuf->NS=raw[i];
				break;
			case lontd	:
				if (raw[i] == ','){
					next_field=ew; // increment to the next field on the delimiter comma
					field_i = 0; // reset the field index
					break;
				}
				msgbuf->longitude[field_i]=raw[i];
				field_i ++;
				break;
			case ew		:
				if (raw[i] == ','){
					next_field=pfix; // increment to the next field on the delimiter comma
					field_i = 0; // reset the field index
					break;
				}
				msgbuf->EW=raw[i];
				break;
			case pfix	:
				if (raw[i] == ','){
					next_field=sat; // finished message
					break;
				}
				msgbuf->pos_fix=raw[i];
				break;
			case sat	:
				if (raw[i] == ','){
					next_field=msgdone; // finished message
					break;
				}
				msgbuf->sat_used=raw[i];
			case msgdone:
				break;
			}
	}
	return 0;
}


double char2rad(char * sourcearray, int len, int expo_start){
    double sum = 0;
//    double expo = 1;
    int expo = expo_start;
    for (int i=0; i<len;i++){
        if (sourcearray[i]!='.'){
        expo = expo - 1; // exponent of the digit
        double digit = sourcearray[i] - '0';
        double tenp = pow(10,expo);
        double val = digit*tenp;
        sum = sum + val;
        }
    }
    double rad = sum*(3.14159/180);
    return rad;
}


double getdistance(char* lat1, char* long1, char * lat2, char * long2){
	double latrad1 = char2rad(lat1, 9, 2);
	double longrad1 = char2rad(long1, 10, 3);
	double latrad2 = char2rad(lat2, 9, 2);
	double longrad2 = char2rad(long2, 10, 3);
	double dphi = latrad1-latrad2;
	double dlambda = longrad1-longrad2;
	double phi_m = (latrad1+latrad2)/2;
	double R = 6371009; // earth radius
	double term2 = pow(cos(phi_m)*dlambda, 2);
	double d = R*(sqrt((dphi*dphi)+term2));
	return d;
}


