/*
 * mainFSM.c
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#include "mainFSM.h"

#include "constants.h"
#include "ee_uartusb.h"
#include "ee_bluetooth.h"
#include "ee_elm327.h"
#include "datagram.h"

mainStatus mainStatus_;

inquiry_result_t inquiry_result[9];
int inquiry_result_num;
int inquiry_selector[2]; // Pointer for row and column

unsigned char bitmask[10];
unsigned char buffer[10];

void mainFSM_init()
{
	mainStatus_ = MAIN_START;
}

void mainFSM_tran_(mainStatus dest)
{
	mainStatus_ = dest;
}

void mainFSM_dispatch()
{
	switch (mainStatus_) {
	case MAIN_START:
		EE_uartusb_init(USB_BAUD_RATE, USB_PARAM, USB_CONG_CTRL);
		mainFSM_tran_(BT_INIT);
		break;
	case BT_INIT:
		EE_bluetooth_acquire();
		// Bluetooth initialization
		if (EE_bluetooth_init(BT_BAUD_RATE, BT_PARAM, BT_CONG_CTRL)) {
			// Switch to Master mode
			if (EE_bluetooth_set_pairing()) {
				// Forces pin authentication
				EE_bluetooth_set_authentication(1);
				EE_bluetooth_set_pin("6789");
				EE_bluetooth_set_name("Flex_RN42");
				EE_bluetooth_reboot();
			} else {
				mainFSM_tran_(MAIN_DEAD);
				return;
			}
		} else {
			mainFSM_tran_(MAIN_DEAD);
			return;
		}
		mainFSM_tran_(WAIT_FOR_PING);
		break;
	case WAIT_FOR_PING:
		break;
	case BT_INQUIRY:
		// Inquiry request
		inquiry_result_num = EE_bluetooth_inquiry(inquiry_result);
		inquiry_selector[0] = inquiry_selector[1] = 0;
		if (inquiry_result_num == 0)
			mainFSM_tran_(BT_INQUIRY_RESCAN);
		else
			mainFSM_tran_(BT_INQUIRY_SHOW);
		break;
	case BT_INQUIRY_RESCAN:
		mainFSM_tran_(BT_INQUIRY);
		break;
	case BT_INQUIRY_SHOW:
		break;
	case BT_CONNECT:
		EE_bluetooth_connect(inquiry_result[inquiry_selector[1]].addr);
		mainFSM_tran_(MAIN_DEAD);
		break;
	case MAIN_DEAD:
	default:
		EE_bluetooth_release();
		break;
	}
}

