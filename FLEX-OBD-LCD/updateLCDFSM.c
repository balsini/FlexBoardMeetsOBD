/*
 * FSM.c
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#include "updateLCDFSM.h"

#include "vehicleData.h"
#include "LCD.h"
#include "buttons.h"

updateLCDStatus updateLCDStatus_;

unsigned char updateLCDScroll;
unsigned char updateLCDLastScroll;

void updateLCDFSM_init()
{
	updateLCDScroll = 0;
	updateLCDLastScroll = updateLCDScroll + 1;
	LCD_init();
}

void updateLCDFSM_tran_(updateLCDStatus dest)
{
	updateLCDStatus_ = dest;
}

void updateLCDFSM_dispatch()
{
	Signal s;
	updateLCDFSM_tran_(WAIT_FOR_BUFFER_FULL);
	for (;;) {
		switch (updateLCDStatus_) {
		case WAIT_FOR_BUFFER_FULL:
			updateLCDFSM_tran_(ACQUIRE_DATA_BUFFER);
			break;
		case ACQUIRE_DATA_BUFFER:
			updateLCDFSM_tran_(READ_BUFFER_AND_REFRESH);
			break;
		case READ_BUFFER_AND_REFRESH:
			// Handling buttons and updating scroll
			s = getSignals();
			switch (s) {
			case B1:
			case B2:
				updateLCDScroll = (updateLCDScroll + 1) % VEHICLE_DATA_SIZE;
				break;
			case B3:
			case B4:
				if (!updateLCDScroll)
					updateLCDScroll = VEHICLE_DATA_SIZE - 1;
				else
					updateLCDScroll--;
				break;
			default:
				break;
			}

			// If scroll has changed, then update the fields
			if (updateLCDScroll != updateLCDLastScroll) {
				updateLCDLastScroll = updateLCDScroll;
				LCD_init();
				switch (updateLCDScroll) {
				case 0:
					LCD_appendR("Elm Vers.:");
					LCD_appendR("RPM:");
					break;
				case 1:
					LCD_appendR("RPM:");
					LCD_appendR("Speed:");
					break;
				case 2:
					LCD_appendR("Speed:");
					LCD_appendR("Elm Vers.:");
					break;
				default:
					break;
				}
			}

			switch (updateLCDScroll) {
			case 0:
				LCD_writeC(11, 0, 'v');
				LCD_writeC(5, 1, 'R');
				break;
			case 1:
				LCD_writeC(5, 0, 'R');
				LCD_writeC(7, 1, 'S');
				break;
			case 2:
				LCD_writeC(7, 0, 'S');
				LCD_writeC(11, 1, 'v');
				break;
			default:
				break;
			}
			updateLCDFSM_tran_(RELEASE_DATA_BUFFER);
			break;
			case RELEASE_DATA_BUFFER:
				return;
				break;
			default:
				break;
		}
	}
}

