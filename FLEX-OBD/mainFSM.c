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
#include "getFSM.h"
#include "sendFSM.h"

mainStatus mainStatus_;

inquiry_result_t inquiry_result[9];
int inquiry_result_num;
int inquiry_selector[2]; // Pointer for row and column

unsigned char buffer[255];

unsigned char bitmask[10];

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
	Datagram dg;
	int i, j, k;
	for (;;) {
		switch (mainStatus_) {
		case MAIN_START:
			EE_uartusb_init(USB_BAUD_RATE, USB_PARAM, USB_CONG_CTRL);
#ifdef DEBUGGING
			EE_uartusb_sendS("FSM started\r\n");
#endif
			mainFSM_tran_(BT_INIT);
			break;
		case BT_INIT:
#ifdef DEBUGGING
			EE_uartusb_sendS("Bt initialization\r\n");
#endif
			EE_bluetooth_acquire();
			// Bluetooth initialization
			if (EE_bluetooth_init(BT_BAUD_RATE, BT_PARAM, BT_CONG_CTRL)) {
#ifdef DEBUGGING
				EE_uartusb_sendS("Bt configured\r\n");
#endif
				// Switch to Master mode
				if (EE_bluetooth_set_pairing()) {
					// Forces pin authentication
					EE_bluetooth_set_authentication(1);
					EE_bluetooth_set_pin("6789");
					EE_bluetooth_set_name("Flex_RN42");
					EE_bluetooth_reboot();
#ifdef DEBUGGING
					EE_uartusb_sendS("Bt setted up\r\n");
#endif
				} else {
					mainFSM_tran_(MAIN_DEAD);
					return;
				}
			} else {
				mainFSM_tran_(MAIN_DEAD);
				return;
			}
#ifdef DEBUGGING
			EE_uartusb_sendS("Done!\r\n");
#endif
			mainFSM_tran_(WAIT_FOR_PING);
			break;
		case WAIT_FOR_PING:
#ifdef DEBUGGING
			EE_uartusb_sendS("Waiting for ping\r\n");
#endif
			receiveDatagram(&dg);
			if (dg.type == REQUEST && dg.id == HELLO) {
				sendDatagramSmall(RESPONSE, HELLO);
#ifdef DEBUGGING
				EE_uartusb_sendS("Ping received, sent reply\r\n");
#endif
				mainFSM_tran_(WAIT_FOR_REQUEST);
			}
			break;
		case WAIT_FOR_REQUEST:
#ifdef DEBUGGING
			EE_uartusb_sendS("Waiting for request\r\n");
#endif
			receiveDatagram(&dg);
			if (dg.type == REQUEST && dg.id == INQUIRY)
				mainFSM_tran_(BT_INQUIRY);
			break;
		case BT_INQUIRY:
#ifdef DEBUGGING
			EE_uartusb_sendS("Performing Inquiry\r\n");
#endif
			// Inquiry request
			inquiry_result_num = EE_bluetooth_inquiry(inquiry_result);
			if (inquiry_result_num > 0)
				mainFSM_tran_(BT_INQUIRY_SHOW);
			break;
		case BT_INQUIRY_SHOW:
			k = 0;
			buffer[k++] = inquiry_result_num;
			for (i=0; i<inquiry_result_num; i++) {
				for (j=0; inquiry_result[i].name[j] != '\0'; j++)
					buffer[k++] = inquiry_result[i].name[j];
				buffer[k++] = ',';
				for (j=0; inquiry_result[i].addr[j] != '\0'; j++)
					buffer[k++] = inquiry_result[i].addr[j];
				buffer[k++] = ',';
				for (j=0; inquiry_result[i].cod[j] != '\0'; j++)
					buffer[k++] = inquiry_result[i].cod[j];
				buffer[k++] = '.';
			}
			constructDatagram(&dg, RESPONSE, INQUIRY, k-1, buffer);
#ifdef DEBUGGING
			EE_uartusb_sendS("Send Inquiry results\r\n");
#endif
			sendDatagram(&dg);
#ifdef DEBUGGING
			EE_uartusb_sendS("\r\nReceiving reply\r\n");
#endif
			receiveDatagram(&dg);
			if (dg.type == REQUEST && dg.id == INQUIRY)
				mainFSM_tran_(BT_INQUIRY);
			else if (dg.type == REQUEST && dg.id == CONNECT_TO)
				mainFSM_tran_(BT_CONNECT);
			break;
		case BT_CONNECT:
#ifdef DEBUGGING
			EE_uartusb_sendS("Connecting to\r\n");
			EE_uartusb_sendC(dg.data[0] + '0');
#endif
			EE_bluetooth_connect(inquiry_result[inquiry_selector[dg.data[0]]].addr);
			mainFSM_tran_(MAIN_DEAD);
			break;
		case MAIN_DEAD:
		default:
			EE_bluetooth_release();
			getFSM_init();
			SetRelAlarm(TaskGet, 1500, 100);
			sendFSM_init();
			SetRelAlarm(TaskSend, 1600, 150);
			return;
			break;
		}
	}
}

