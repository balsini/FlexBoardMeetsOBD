#include "FSM.h"

Status status_;
char blink_counter = 0;
char blink = 0;
char lcd_changed;

inquiry_result_t inquiry_result[9];
int inquiry_result_num;
int inquiry_selector[2]; // Pointer for row and column

Signal FSM_getSignals()
{
	char b = buttons_get();
	if ((b & 1) != 0)
		return B1;
	if ((b & 2) != 0)
		return B2;
	if ((b & 4) != 0)
		return B3;
	if ((b & 8) != 0)
		return B4;
	return ABSENT;
}

void FSM_init()
{
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
			if (blink_counter++ == 3) {
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
			LCD_append_row("BT Init...");
			// Bluetooth initialization
			if (EE_bluetooth_init(9600, BIT8_NO | BIT_STOP_1, CTRL_SIMPLE)) {
				LCD_append("[Done]");
				LCD_append_row("Go Mstr...");
				// Switch to Master mode
				if (EE_bluetooth_set_master())
					LCD_append("[Done]");
				else {
					LCD_append("[Fail]");
					FSM_tran_(DEAD);
					return;
				}
			} else {
				LCD_append("[Fail]");
				LCD_append_row("Reboot BT device");
				FSM_tran_(DEAD);
				return;
			}
			FSM_tran_(BT_INQUIRY);
			break;
		case BT_INQUIRY:
			LCD_append_row("Inquiry...");
			inquiry_result_num = EE_bluetooth_inquiry(inquiry_result);
			LCD_append("[Done]");
			inquiry_selector[0] = inquiry_selector[1] = 0;
			LCD_append_row("Devices found: ");
			LCD_appendC(inquiry_result_num + '0');
			if (inquiry_result_num == 0) {
				LCD_append_row("Push to rescan");
				FSM_tran_(BT_INQUIRY_RESCAN);
			} else {
				LCD_append_row("");
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
					LCD_append(inquiry_result[inquiry_selector[1]].name);
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
			LCD_append_row("Connecting...");
			FSM_tran_(DEAD);
			break;
		case BT_INQUIRY_SHOW_MOVE:
			break;
		case WAIT:
			LCD_append_row("WAITING 4E");
			FSM_tran_(DEAD);
			return;
			break;
		default:
			break;
	}
}

