/*
 * FSM.c
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#include "FSM.h"

#include "constants.h"
#include "buttons.h"
#include "ee_bluetooth.h"
#include "ee_elm327.h"

Status status_;
char blink_counter;
char blink;
char lcd_changed;

inquiry_result_t inquiry_result[9];
int inquiry_result_num;
int inquiry_selector[2]; // Pointer for row and column

Signal FSM_getSignals()
{
	char b = buttons_get();
	if (b & 1) return B1;
	if (b & 2) return B2;
	if (b & 4) return B3;
	if (b & 8) return B4;
	return ABSENT;
}

void FSM_init()
{
	blink_counter = 0;
	blink = 0;
	status_ = WELCOME;
}

void FSM_tran_(Status dest)
{
	status_ = dest;
}

void FSM_dispatch()
{
	Signal s = FSM_getSignals();
	switch (status_) {
	case WELCOME:
		switch (s) {
		case ABSENT:
			if (blink_counter++ == 4) {
				blink_counter = 0;
				if (blink++ == 1) {
					blink = 0;
					LCD_writeR(1, " Press any key!");
				} else {
					LCD_writeR(1, "    WELCOME!");
				}
			}
			break;
		default:
			FSM_tran_(BT_INIT);
			break;
		}
		break;
		case BT_INIT:
			EE_bluetooth_acquire();
			LCD_appendR("BT Init...");
			// Bluetooth initialization
			if (EE_bluetooth_init(BT_BAUD_RATE, BT_PARAM, BT_CONG_CTRL)) {
				LCD_appendS("[Done]");
				LCD_appendR("SetMode...");
				// Switch to Master mode
				if (EE_bluetooth_set_pairing()) {
					LCD_appendS("[Done]");
					// Forces pin authentication
					EE_bluetooth_set_authentication(1);
					EE_bluetooth_set_pin("6789");
					EE_bluetooth_set_name("Flex_RN42");
					EE_bluetooth_reboot();
				}
				else {
					LCD_appendS("[Fail]");
					FSM_tran_(DEAD);
					return;
				}
			} else {
				LCD_appendS("[Fail]");
				LCD_appendR("Reboot BT device");
				FSM_tran_(DEAD);
				return;
			}
			FSM_tran_(BT_INQUIRY);
			break;
		case BT_INQUIRY:
			LCD_appendR("Inquiry...");
			// Inquiry request
			inquiry_result_num = EE_bluetooth_inquiry(inquiry_result);
			LCD_appendS("[Done]");
			inquiry_selector[0] = inquiry_selector[1] = 0;
			LCD_appendR("Devices found: ");
			LCD_appendC(inquiry_result_num + '0');
			if (inquiry_result_num == 0) {
				LCD_appendR("Push to rescan");
				FSM_tran_(BT_INQUIRY_RESCAN);
			} else {
				LCD_appendR("");
				lcd_changed = 1;
				FSM_tran_(BT_INQUIRY_SHOW);
			}
			break;
		case BT_INQUIRY_RESCAN:
			switch (s) {
			case ABSENT:
				break;
			default:
				FSM_tran_(BT_INQUIRY);
				break;
			}
			break;
		case BT_INQUIRY_SHOW:
			switch (s) {
			// Commands are VI like:
			// ( )    ( )    ( )    ( )
			// left   down   up    right
			case B1:
				lcd_changed = 1;
				if (!inquiry_selector[0])
					FSM_tran_(BT_CONNECT);
				else
					inquiry_selector[0]--;
				break;
			case B2:
				lcd_changed = 1;
				if (!inquiry_selector[1])
					inquiry_selector[1] = inquiry_result_num - 1;
				else
					inquiry_selector[1]--;
				break;
			case B3:
				lcd_changed = 1;
				inquiry_selector[1] = (inquiry_selector[1] + 1) % inquiry_result_num;
				break;
			case B4:
				lcd_changed = 1;
				if (inquiry_selector[0] == 2)
					FSM_tran_(BT_INQUIRY);
				else
					inquiry_selector[0]++;
				break;
			case ABSENT:
				break;
			}
			if (lcd_changed) {
				lcd_changed = 0;
				switch (inquiry_selector[0]) {
				case 0:
					LCD_writeR(2,"@ ");
					LCD_appendS(inquiry_result[inquiry_selector[1]].name);
					break;
				case 1:
					LCD_writeR(2,inquiry_result[inquiry_selector[1]].addr);
					break;
				case 2:
					LCD_writeR(2,inquiry_result[inquiry_selector[1]].cod);
					LCD_writeC(15,1,'!');
					break;
				default:
					break;
				}
			}
			break;
		case BT_CONNECT:
			LCD_appendR("Estabilish Conn.");
			EE_bluetooth_connect(inquiry_result[inquiry_selector[1]].addr);
			LCD_appendR("Comm|RConn|RScan");
			FSM_tran_(BT_CONNECT_VERIFY);
			break;
		case BT_CONNECT_VERIFY:
			switch (s) {
			case ABSENT:
				break;
			case B1:
				FSM_tran_(BT_COMMUNICATE);
				break;
			case B2:
			case B3:
				FSM_tran_(BT_CONNECT);
				break;
			case B4:
				FSM_tran_(BT_INQUIRY);
				break;
			}
			break;
		case BT_COMMUNICATE:
			ee_elm327_init();
			LCD_appendR("Elm v.");
			LCD_appendS(ee_elm327_get_version());
			FSM_tran_(DEAD);
			break;
		case WAIT:
			LCD_appendR("WAITING 4E");
			FSM_tran_(DEAD);
			return;
			break;
		default:
			EE_bluetooth_release();
			break;
	}
}
