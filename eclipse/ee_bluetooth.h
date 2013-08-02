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

/*
 * Initializes the UART to make Bluetooth available.
 * baud defines the UART channel.
 */

int EE_bluetooth_init(EE_UINT8 uart,
		EE_UINT32 baud,
		EE_UINT16 byteformat,
		EE_UINT16 mode);

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
unsigned char EE_bluetooth_receive();

#endif /* EE_BLUETOOTH_H_ */
