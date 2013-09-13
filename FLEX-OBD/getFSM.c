/*
 * getFSM.c
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#include "getFSM.h"

#include "constants.h"
#include "ee_uartusb.h"
#include "ee_bluetooth.h"
#include "ee_elm327.h"
#include "datagram.h"
#include "vehicleData.h"

vehicleData vehicleDataBuffer;

getStatus getStatus_;

void getFSM_init()
{
	vehicleDataBuffer.ready = 0;
	EE_bluetooth_acquire();
	getFSM_tran_(ELM327_INIT);
}

void getFSM_tran_(getStatus dest)
{
	getStatus_ = dest;
}

void getFSM_dispatch()
{
	int speed = 0;
	int RPM = 0;
	int coolantTemp = 0;
	int fuelRemaining = 0;
	for (;;) {
		switch (getStatus_) {
		case ELM327_INIT:
#ifdef DEBUGGING
			EE_uartusb_sendS("Get tasks init\r\n");
#endif
			ee_elm327_init();
			getFSM_tran_(OBTAIN_VEHICLE_DATA);
			break;
		case OBTAIN_VEHICLE_DATA:
			RPM = ee_elm327_get(ENGINE_RPM);
			speed = ee_elm327_get(VEHICLE_SPEED);
			coolantTemp = ee_elm327_get(ENGINE_COOLANT_TEMP);
			fuelRemaining = ee_elm327_get(FUEL_REMAINING);
			getFSM_tran_(ACQUIRE_DATA_BUFFER);
			break;
		case ACQUIRE_DATA_BUFFER:
			GetResource(VEHICLE_DATA_BUFFER);
			getFSM_tran_(WRITE_BUFFER);
			break;
		case WRITE_BUFFER:
			if (vehicleDataBuffer.speed != speed) {
				vehicleDataBuffer.speed = speed;
				vehicleDataBuffer.ready |= VEHICLE_DATA_SPEED;
			}
			if (vehicleDataBuffer.RPM != RPM) {
				vehicleDataBuffer.RPM = RPM / 4;
				vehicleDataBuffer.ready |= VEHICLE_DATA_RPM;
			}
			if (vehicleDataBuffer.coolantTemp != coolantTemp) {
				vehicleDataBuffer.coolantTemp = coolantTemp - 40;
				vehicleDataBuffer.ready |= VEHICLE_DATA_COOLANT_TEMP;
			}
			if (vehicleDataBuffer.fuelRemaining != fuelRemaining) {
				vehicleDataBuffer.fuelRemaining = fuelRemaining;
				vehicleDataBuffer.ready |= VEHICLE_DATA_FUEL;
			}
			getFSM_tran_(RELEASE_DATA_BUFFER);
			break;
		case RELEASE_DATA_BUFFER:
			ReleaseResource(VEHICLE_DATA_BUFFER);
			getFSM_tran_(OBTAIN_VEHICLE_DATA);
			return;
			break;
		default:
			return;
			break;
		}
	}
}

