/*
 * ee_uartusb.h
 *
 *  Created on: 11/sep/2013
 *      Author: Alessio
 */

#ifndef EE_UARTUSB_H_
#define EE_UARTUSB_H_

#include "ee.h"
#include "eeuart.h"
#include "constants.h"

/**
 * Initializes the UART to make UART-USB available.
 *
 * \param baud Baudrate of UART-USB device.
 * \param byteformat UART-USB UART parameters.
 * \param mode UART-USB UART flow control.
 */

void EE_uartusb_init(EE_UINT32 baud,
		EE_UINT16 byteformat,
		EE_UINT16 mode);

/**
 * Sends a string via UART-USB
 * \param str String to be sent. The string
 * termination character will not be sent.
 */

void EE_uartusb_sendS(char * str);

/**
 * Sends a character via UART-USB.
 * \param c Character to be sent.
 */

void EE_uartusb_sendC(unsigned char c);

/**
 * Receives a char via UART-USB. This function has
 * a timeout.
 * \return The character received via UART-USB. If
 *   no data is received, then 0xFF value is returned.
 */

unsigned char EE_uartusb_receive();

/**
 * Receives a char via UART-USB. This function has
 * no timeout, so it can wait forever if no data is
 * transmitted.
 * \return The character received via UART-USB.
 */

unsigned char EE_uartusb_receive_no_timeout();

#endif /* EE_UARTUSB_H_ */
