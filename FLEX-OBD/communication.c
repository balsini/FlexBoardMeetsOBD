/*
 * communication.c
 *
 *  Created on: 25/ago/2013
 *      Author: Administrator
 */

#include "communication.h"
#include "ee_usb.h"

int send_command(unsigned char command, unsigned char numbyte, char* req_buffer, char* res_buffer) {
	int i = 0;
	EE_uartusb_sendC((unsigned char)REQUEST);
	EE_uartusb_sendC(command);
	EE_uartusb_sendC(numbyte);
//	for(i=0; i<numbyte; i++)
//		EE_uartusb_sendC(*(unsigned char*)req_buffer++);
//	for(i=0; i < (unsigned char)(command & 0x0F ); i++)
//		*(unsigned char*)res_buffer++ = EE_uartusb_receive_no_timeout();
//	return 0;
}
