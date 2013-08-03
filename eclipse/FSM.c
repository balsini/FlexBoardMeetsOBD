#include "FSM.h"

Status status_;

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

void BT_init()
{
	LCD_append_row("BT init...");

	// Init UART
	//EE_UART2_Init(38400, BIT8_NO | BIT_STOP_1, CTRL_SIMPLE);

	//Bluetooth initialization
	if (EE_bluetooth_init(2, 115200, BIT8_NO | BIT_STOP_1, CTRL_SIMPLE) == 0) {
		LCD_append("[Done]");
	} else {
		LCD_append("[Fail]");
	}
}

void FSM_dispatch()
{
	Signal s = FSM_getSignals();
	switch (status_) {
	case WELCOME:
		LCD_writeC(0,0,126);
		FSM_tran_(INIT);
		break;
	case INIT:
		switch (s) {
		case B1:
			BT_init();
			break;
		case B4:			////////// TO DO
			FSM_tran_(WAIT);
			break;
		default: break;
		}
		break;
	case WAIT:
		LCD_append_row("WAITING 4E");
		break;
	default: break;
	}
}
