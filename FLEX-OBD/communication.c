/*
 * communication.c
 *
 *  Created on: 25/ago/2013
 *      Author: Administrator
 */

#include "communication.h"
#include "ee_usb.h"
#include "LCD.h"

int send_command(unsigned char command, unsigned char numbyte, char* req_buffer, unsigned char* res_buffer) {
	int i = 0;
	unsigned char res_type;
	unsigned char res_command;
	unsigned char num_byte_response;
	EE_uartusb_sendC((unsigned char)REQUEST);
	EE_uartusb_sendC(command);
	EE_uartusb_sendC(numbyte);
	for(i=0; i<numbyte; i++)
		EE_uartusb_sendC(*(unsigned char*)req_buffer++);

	res_type = EE_uartusb_receive_no_timeout();
    res_command = EE_uartusb_receive_no_timeout();
    num_byte_response = EE_uartusb_receive_no_timeout();
	for(i=0; i < num_byte_response; i++)
		*res_buffer++ = EE_uartusb_receive_no_timeout();
	return (int)res_command;
}

int send_data(unsigned char type, unsigned char numbyte, unsigned char* data) {
	int i=0;
	unsigned char res_type;
	unsigned char res_command;
	unsigned char response;
	unsigned char num_byte_response;
	EE_uartusb_sendC((unsigned char)DATA);
	EE_uartusb_sendC(type);
	EE_uartusb_sendC(numbyte);
	for(i=0; i<numbyte; i++)
		EE_uartusb_sendC(data[i]);
	res_type = EE_uartusb_receive_no_timeout();
	res_command = EE_uartusb_receive_no_timeout();
	num_byte_response = EE_uartusb_receive_no_timeout();
	response = EE_uartusb_receive_no_timeout();
	return (int)res_command;

}
