/*
 * constants.h
 *
 *  Created on: 05/ago/2013
 *      Author: Alessio
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include "ee.h"

#define BT_UART			2
#define BT_BAUD_RATE	9600
#define BT_PARAM		BIT8_NO | BIT_STOP_1
#define BT_CONG_CTRL	CTRL_SIMPLE

#define USB_UART		1
#define USB_BAUD_RATE	9600
#define USB_PARAM		BIT8_NO | BIT_STOP_1
#define USB_CONG_CTRL	CTRL_SIMPLE

#endif /* CONSTANTS_H_ */
