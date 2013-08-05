/*
 * ee_bluetooth.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef EE_BLUETOOTH_H_
#define EE_BLUETOOTH_H_

#include "ee.h"
#include "eeuart.h"

#include "LCD.h"

// Inquiry result is a matrix of maximum 9 rows, where
// each element is like:
// <BT addr>,<BT name>,<COD>

typedef struct inquiry_result_t_ {
	char addr[13];
	char name[17];
	char cod[7];
} inquiry_result_t;

/*
 * Initializes the UART to make Bluetooth available.
 * baud defines the UART channel.
 */

int EE_bluetooth_init(EE_UINT32 baud,
		EE_UINT16 byteformat,
		EE_UINT16 mode);

/*
 * Brings Bluetooth module to Master mode
 */

int EE_bluetooth_set_master();

/*
 * Brings Bluetooth module to Slave mode
 */

int EE_bluetooth_set_slave();

/*
 * Returns 1 if Bluetooth module returns values in command mode
 * 0 otherwise.
 */

int EE_bluetooth_alive();

/*
 * Sends a string via Bluetooth
 */

void EE_bluetooth_sendS(char * string);

/*
 * Receives a char via Bluetooth
 */

inline unsigned char EE_bluetooth_receive();
inline unsigned char EE_bluetooth_receive_no_timeout();

/*
 * Makes a Bluetooth inquiry, scanning for
 * other devices.
 * Results of the inquiry are stored in
 * dest container.
 */

int EE_bluetooth_inquiry(inquiry_result_t * dest);

/*
 * Functions for mutual exclusion on the BT resource
 */
void EE_bluetooth_acquire();
void EE_bluetooth_release();

#endif /* EE_BLUETOOTH_H_ */
