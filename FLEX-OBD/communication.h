/*
 * communication.h
 *
 *  Created on: 25/ago/2013
 *      Author: Administrator
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#define REQUEST 0
#define RESPONSE 1
#define DATA    2

#define HELLO        0x01
#define CONNECT_TO   0x11
#define GET_BITMASK  0x22
#define STOP         0x31

int send_command(unsigned char command, unsigned char numbyte, char* req_buffer, char* res_buffer);

#endif /* COMMUNICATION_H_ */
