/*
 * FSM.c
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#include "updateLCDFSM.h"

#include "vehicleData.h"
#include "LCD.h"

updateLCDStatus updateLCDStatus_;

void updateLCDFSM_init()
{
	LCD_init();
	//LCD_appendR("Elm v.");
	//LCD_appendS(ee_elm327_get_version());
}

void updateLCDFSM_tran_(updateLCDStatus dest)
{
	updateLCDStatus_ = dest;
}

void updateLCDFSM_dispatch()
{
	updateLCDFSM_tran_(WAIT_FOR_BUFFER_FULL);
	for (;;) {
		switch (updateLCDStatus_) {
		case WAIT_FOR_BUFFER_FULL:
			updateLCDFSM_tran_(ACQUIRE_DATA_BUFFER);
			break;
		case ACQUIRE_DATA_BUFFER:
			updateLCDFSM_tran_(READ_BUFFER);
			break;
		case READ_BUFFER:
			updateLCDFSM_tran_(RELEASE_DATA_BUFFER);
			break;
		case RELEASE_DATA_BUFFER:
			updateLCDFSM_tran_(REFRESH_LCD);
			break;
		case REFRESH_LCD:
			return;
			break;
		default:
			break;
		}
	}
}

