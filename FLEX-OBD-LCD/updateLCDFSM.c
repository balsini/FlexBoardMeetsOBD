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
	unsigned int value;
	unsigned int i;
	Signal s;
	updateLCDFSM_tran_(WAIT_FOR_BUFFER_FULL);
	for (;;) {
		switch (updateLCDStatus_) {
		case WAIT_FOR_BUFFER_FULL:
			updateLCDFSM_tran_(ACQUIRE_DATA_BUFFER);
			break;
		case ACQUIRE_DATA_BUFFER:
			GetResource(VEHICLE_DATA_BUFFER);
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
					vehicleDataBuffer.ready |= VEHICLE_DATA_VERSION;
					vehicleDataBuffer.ready |= VEHICLE_DATA_RPM;
					break;
				case 1:
					LCD_appendR("RPM:");
					LCD_appendR("Speed:");
					vehicleDataBuffer.ready |= VEHICLE_DATA_RPM;
					vehicleDataBuffer.ready |= VEHICLE_DATA_SPEED;
					break;
				case 2:
					LCD_appendR("Speed:");
					LCD_appendR("Cool.Temp.:");
					vehicleDataBuffer.ready |= VEHICLE_DATA_COOLANT_TEMP;
					vehicleDataBuffer.ready |= VEHICLE_DATA_SPEED;
					break;
				case 3:
					LCD_appendR("Cool.Temp.:");
					LCD_appendR("Fuel:");
					vehicleDataBuffer.ready |= VEHICLE_DATA_COOLANT_TEMP;
					vehicleDataBuffer.ready |= VEHICLE_DATA_FUEL;
					break;
				case 4:
					LCD_appendR("Fuel:");
					LCD_appendR("Elm Vers.:");
					vehicleDataBuffer.ready |= VEHICLE_DATA_VERSION;
					vehicleDataBuffer.ready |= VEHICLE_DATA_FUEL;
					break;
				default:
					break;
				}
			}

			switch (updateLCDScroll) {
			case 0:
				if (vehicleDataBuffer.ready & VEHICLE_DATA_VERSION) {
					vehicleDataBuffer.ready ^= VEHICLE_DATA_VERSION;
					for (i=0; vehicleDataBuffer.Elm327version[i] != '\0'; i++)
						LCD_writeC(12 + i, 0, vehicleDataBuffer.Elm327version[i]);
					while (12 + i <= 15) {
						LCD_writeC(12 + i, 0, ' ');
						i++;
					}
				} else {
					LCD_writeC(13, 0, '?');
					LCD_writeC(14, 0, '?');
					LCD_writeC(15, 0, '?');
				}
				if (vehicleDataBuffer.ready & VEHICLE_DATA_RPM) {
					vehicleDataBuffer.ready ^= VEHICLE_DATA_RPM;
					value = vehicleDataBuffer.RPM;
					for (i=0; i<5; i++)
						LCD_writeC(15-i, 1, ' ');
					for (i=0; value != 0; i++) {
						LCD_writeC(15-i, 1, (value % 10) + '0');
						value /= 10;
					}
					if (i==0)
						LCD_writeC(15, 1, '0');
				}
				break;
			case 1:
				if (vehicleDataBuffer.ready & VEHICLE_DATA_RPM) {
					vehicleDataBuffer.ready ^= VEHICLE_DATA_RPM;
					value = vehicleDataBuffer.RPM;
					for (i=0; i<5; i++)
						LCD_writeC(15-i, 0, ' ');
					for (i=0; value != 0; i++) {
						LCD_writeC(15-i, 0, (value % 10) + '0');
						value /= 10;
					}
					if (i==0)
						LCD_writeC(15, 0, '0');
				}
				if (vehicleDataBuffer.ready & VEHICLE_DATA_SPEED) {
					vehicleDataBuffer.ready ^= VEHICLE_DATA_SPEED;
					value = vehicleDataBuffer.speed;
					for (i=0; i<3; i++)
						LCD_writeC(15-i, 1, ' ');
					for (i=0; value != 0; i++) {
						LCD_writeC(15-i, 1, (value % 10) + '0');
						value /= 10;
					}
					if (i==0)
						LCD_writeC(15, 1, '0');
				}
				break;
			case 2:
				if (vehicleDataBuffer.ready & VEHICLE_DATA_SPEED) {
					vehicleDataBuffer.ready ^= VEHICLE_DATA_SPEED;
					value = vehicleDataBuffer.speed;
					for (i=0; i<3; i++)
						LCD_writeC(15-i, 0, ' ');
					for (i=0; value != 0; i++) {
						LCD_writeC(15-i, 0, (value % 10) + '0');
						value /= 10;
					}
					if (i==0)
						LCD_writeC(15, 0, '0');
				}
				if (vehicleDataBuffer.ready & VEHICLE_DATA_COOLANT_TEMP) {
					vehicleDataBuffer.ready ^= VEHICLE_DATA_COOLANT_TEMP;
					value = vehicleDataBuffer.coolantTemp;
					for (i=0; i<3; i++)
						LCD_writeC(15-i, 1, ' ');
					for (i=0; value != 0; i++) {
						LCD_writeC(15-i, 1, (value % 10) + '0');
						value /= 10;
					}
					if (i==0)
						LCD_writeC(15, 1, '0');
				}
				break;
			case 3:
				if (vehicleDataBuffer.ready & VEHICLE_DATA_COOLANT_TEMP) {
					vehicleDataBuffer.ready ^= VEHICLE_DATA_COOLANT_TEMP;
					value = vehicleDataBuffer.coolantTemp;
					for (i=0; i<3; i++)
						LCD_writeC(15-i, 0, ' ');
					for (i=0; value != 0; i++) {
						LCD_writeC(15-i, 0, (value % 10) + '0');
						value /= 10;
					}
					if (i==0)
						LCD_writeC(15, 0, '0');
				}
				if (vehicleDataBuffer.ready & VEHICLE_DATA_FUEL) {
					vehicleDataBuffer.ready ^= VEHICLE_DATA_FUEL;
					value = vehicleDataBuffer.fuelRemaining;
					for (i=0; i<3; i++)
						LCD_writeC(15-i, 1, ' ');
					for (i=0; value != 0; i++) {
						LCD_writeC(15-i, 1, (value % 10) + '0');
						value /= 10;
					}
					if (i==0)
						LCD_writeC(15, 1, '0');
				}
				break;
			case 4:
				if (vehicleDataBuffer.ready & VEHICLE_DATA_FUEL) {
					vehicleDataBuffer.ready ^= VEHICLE_DATA_FUEL;
					value = vehicleDataBuffer.fuelRemaining;
					for (i=0; i<3; i++)
						LCD_writeC(15-i, 0, ' ');
					for (i=0; value != 0; i++) {
						LCD_writeC(15-i, 0, (value % 10) + '0');
						value /= 10;
					}
					if (i==0)
						LCD_writeC(15, 0, '0');
				}
				if (vehicleDataBuffer.ready & VEHICLE_DATA_VERSION) {
					vehicleDataBuffer.ready ^= VEHICLE_DATA_VERSION;
					for (i=0; vehicleDataBuffer.Elm327version[i] != '\0'; i++)
						LCD_writeC(12 + i, 1, vehicleDataBuffer.Elm327version[i]);
					while (12 + i <= 15) {
						LCD_writeC(12 + i, 1, ' ');
						i++;
					}
				} else {
					LCD_writeC(13, 1, '?');
					LCD_writeC(14, 1, '?');
					LCD_writeC(15, 1, '?');
				}
				break;
			default:
				break;
			}
			updateLCDFSM_tran_(RELEASE_DATA_BUFFER);
			break;
			case RELEASE_DATA_BUFFER:
				ReleaseResource(VEHICLE_DATA_BUFFER);
				return;
				break;
			default:
				return;
				break;
		}
	}
}

