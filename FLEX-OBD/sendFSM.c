/*
 * sendFSM.c
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#include "sendFSM.h"

#include "constants.h"
#include "ee_uartusb.h"
#include "ee_bluetooth.h"
#include "ee_elm327.h"
#include "datagram.h"
#include "vehicleData.h"

sendStatus sendStatus_;

void sendFSM_init()
{
	GetResource(USB_MUTEX);
}

void sendFSM_tran_(sendStatus dest)
{
	sendStatus_ = dest;
}

void sendFSM_dispatch()
{
	Datagram dg;
	int i;
	unsigned int value;
	unsigned char buff[16];
	sendFSM_tran_(WAIT_FOR_BUFFER_FULL);
	for (;;) {
		switch (sendStatus_) {
		case WAIT_FOR_BUFFER_FULL:
			sendFSM_tran_(ACQUIRE_DATA_BUFFER_);
			break;
		case ACQUIRE_DATA_BUFFER_:
			GetResource(VEHICLE_DATA_BUFFER);
			sendFSM_tran_(READ_BUFFER);
			break;
		case READ_BUFFER:
			if (vehicleDataBuffer.ready & VEHICLE_DATA_RPM) {
				vehicleDataBuffer.ready ^= VEHICLE_DATA_RPM;
				value = vehicleDataBuffer.RPM;
				for (i=0; value != 0; i++) {
					buff[i] = value % 256;
					value /= 256;
				}
				buff[i] = '\0';
				if (i == 0) {
					buff[0] = 0;
					buff[1] = '\0';
					i = 1;
				}
				constructDatagram(&dg, DATA, RPM_, i, buff);
				sendDatagram(&dg);
			}
			if (vehicleDataBuffer.ready & VEHICLE_DATA_SPEED) {
				vehicleDataBuffer.ready ^= VEHICLE_DATA_SPEED;
				value = vehicleDataBuffer.speed;
				for (i=0; value != 0; i++) {
					buff[i] = value % 256;
					value /= 256;
				}
				buff[i] = '\0';
				if (i == 0) {
					buff[0] = 0;
					buff[1] = '\0';
					i = 1;
				}
				constructDatagram(&dg, DATA, SPEED_, i, buff);
				sendDatagram(&dg);
			}
			if (vehicleDataBuffer.ready & VEHICLE_DATA_COOLANT_TEMP) {
				vehicleDataBuffer.ready ^= VEHICLE_DATA_COOLANT_TEMP;
				value = vehicleDataBuffer.coolantTemp;
				for (i=0; value != 0; i++) {
					buff[i] = value % 256;
					value /= 256;
				}
				buff[i] = '\0';
				if (i == 0) {
					buff[0] = 0;
					buff[1] = '\0';
					i = 1;
				}
				constructDatagram(&dg, DATA, WATER_TEMP_, i, buff);
				sendDatagram(&dg);
			}
			if (vehicleDataBuffer.ready & VEHICLE_DATA_FUEL) {
				vehicleDataBuffer.ready ^= VEHICLE_DATA_FUEL;
				value = vehicleDataBuffer.fuelRemaining;
				for (i=0; value != 0; i++) {
					buff[i] = value % 256;
					value /= 256;
				}
				buff[i] = '\0';
				if (i == 0) {
					buff[0] = 0;
					buff[1] = '\0';
					i = 1;
				}
				constructDatagram(&dg, DATA, FUEL_, i, buff);
				sendDatagram(&dg);
			}
			sendFSM_tran_(RELEASE_DATA_BUFFER_);
			break;
		case RELEASE_DATA_BUFFER_:
			ReleaseResource(VEHICLE_DATA_BUFFER);
			return;
			break;
		default:
			return;
			break;
		}
	}
}
