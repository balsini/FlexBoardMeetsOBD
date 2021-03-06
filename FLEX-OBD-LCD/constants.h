/*
 * constants.h
 *
 *  Created on: 05/ago/2013
 *      Author: Alessio
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "ee.h"

typedef enum Signal_ {ABSENT, B1, B2, B3, B4} Signal;

/**
 * The UART port associated to the
 * Bluetooth module.
 */

#define BT_UART			2

/**
 * The UART baudrate to communicate with the
 * bluetooth module.
 */

#define BT_BAUD_RATE	9600

/**
 * The UART configuragion for the Bluetooth
 * communication.
 */

#define BT_PARAM		BIT8_NO | BIT_STOP_1

/**
 * The UART flow control for the Bluetooth
 * communication.
 */

#define BT_CONG_CTRL	CTRL_SIMPLE

#endif /* CONSTANTS_H_ */
