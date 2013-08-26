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

#define SPEED        0
#define RPM          1

//BITMASKS
#define MSPEED 0x80
#define MRPM   0x40
#define MTEMP  0x20

int send_command(unsigned char, unsigned char, char*, unsigned char*);
int send_data(unsigned char, unsigned char, unsigned char*);

#endif /* COMMUNICATION_H_ */
