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
unsigned char EE_bluetooth_receive();

/*
 * Checks the correctness of a command's response value
 */

int EE_bluetooth_check_response(char * response);

#endif /* EE_BLUETOOTH_H_ */
