/*
 * constants.h
 *
 *  Created on: 05/ago/2013
 *      Author: Alessio
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "ee.h"

//#define	DEBUGGING

/**
 * The UART port associated to the
 * Bluetooth module.
 */

#define BT_UART			1

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


/**
 * The UART port associated to the
 * UART-USB module.
 */

#define USB_UART		2

/**
 * The UART configuragion for the UART-USB
 * communication.
 */

#define USB_BAUD_RATE	9600

/**
 * The UART configuragion for the UART-USB
 * communication.
 */

#define USB_PARAM		BIT8_NO | BIT_STOP_1

/**
 * The UART flow control for the UART-USB
 * communication.
 */

#define USB_CONG_CTRL	CTRL_SIMPLE

#endif /* CONSTANTS_H_ */
