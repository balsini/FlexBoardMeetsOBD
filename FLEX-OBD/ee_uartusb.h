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

void EE_uartusb_init(EE_UINT32 baud,
		EE_UINT16 byteformat,
		EE_UINT16 mode);
void EE_uartusb_sendS(char * str);
void EE_uartusb_sendC(unsigned char c);
unsigned char EE_uartusb_receive();
unsigned char EE_uartusb_receive_no_timeout();

#endif /* EE_UARTUSB_H_ */
