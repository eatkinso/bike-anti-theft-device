 /**
 * @file btrfid.c
 * @author Elizabeth Atkinson (eatkinso@illinois.edu)
 * @brief ID-3LA RFID UART driver
 * @version 0.1
 * @date 2022-04-19
 *
 */

#include "btrfid.h"
#include "main.h"

int get_rfid_msg(uint8_t * rfidmsgbuf, uint8_t * rawmsgbuf2){
	int msgindex;
	typedef enum rfid_field{
		before,
		msg,
		after
	}rfid_field_t;
	rfid_field_t next_field=before;
	for (int i = 0; i < 50; i ++){
		switch (next_field){
		case before:
			if (rawmsgbuf2[i]==0x3F){
				next_field=msg;
				msgindex=0;
				rfidmsgbuf[msgindex]=rawmsgbuf2[i];
				msgindex++;
			}
			break;
		case msg:
			rfidmsgbuf[msgindex]=rawmsgbuf2[i];
			msgindex++;
			if (rawmsgbuf2[i]==0xF2){
				next_field=after;
			}
			break;
		case after:
				break;
		}
	}
	return 0;
}




