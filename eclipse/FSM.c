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
	status_ = INIT;
}

void FSM_tran_(Status dest)
{
	status_ = dest;
}

void BT_init()
{
	LCD_append_row("BT Init...");

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
	char a[3]={' ', 126, '\0'};
	Signal s = FSM_getSignals();
	switch (status_) {
	case INIT:
		LCD_append(a);
		switch (s) {
		case B1:
			LCD_append("B");
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
