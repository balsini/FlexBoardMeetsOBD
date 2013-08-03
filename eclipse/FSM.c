#include "FSM.h"

Status status_;
char blink_counter = 0;
char blink = 0;

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
			else
				LCD_append("[Fail]");
		} else {
			LCD_append("[Fail]");
			LCD_append_row("Reboot BT device");
		}
		FSM_tran_(DEAD);
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

