/*
 * bluetooth.h
 *
 *  Created on: Aug 10, 2013
 *      Author: alessio
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

char EE_bluetooth_receive_no_timeout();
char EE_bluetooth_receive();
int EE_bluetooth_sendS(char * str);
void EE_bluetooth_init();
int EE_bluetooth_connect();
int EE_bluetooth_inquiry();
void EE_bluetooth_free();
int EE_bluetooth_connect_dev(char * bdaddr);

#endif /* BLUETOOTH_H_ */
