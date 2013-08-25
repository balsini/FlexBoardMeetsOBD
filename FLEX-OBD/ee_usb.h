/*
 * ee_usb.h
 *
 *  Created on: 24/ago/2013
 *      Author: Administrator
 */

#ifndef EE_USB_H_
#define EE_USB_H_

#include "ee.h"
#include "eeuart.h"

int EE_uartusb_init(EE_UINT32 baud, EE_UINT16 byteformat, EE_UINT16 mode);
void EE_uartusb_sencc(char);
void EE_uartusb_sendS(char*);
unsigned char EE_uartusb_receive();
unsigned char EE_uartusb_receive_no_timeout();

#endif /* EE_USB_H_ */
