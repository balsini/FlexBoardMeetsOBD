/*
 * FSM.c
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#include "receiveVehicleDataFSM.h"

#include "buttons.h"
#include "ee_bluetooth.h"
#include "ee_elm327.h"

#include "vehicleData.h"

vehicleData vehicleDataBuffer;

receiveVehicleDataStatus receiveVehicleDataStatus_;

void receiveVehicleDataFSM_init()
{
	vehicleDataBuffer.ready = 0;
	EE_bluetooth_acquire();
	receiveVehicleDataFSM_tran_(ELM327_INIT);
}

void receiveVehicleDataFSM_tran_(receiveVehicleDataStatus dest)
{
	receiveVehicleDataStatus_ = dest;
}

void receiveVehicleDataFSM_dispatch()
{
	int speed = 0;
	int RPM = 0;
	int coolantTemp = 0;
	int fuelRemaining = 0;
	for (;;) {
		switch (receiveVehicleDataStatus_) {
		case ELM327_INIT:
			ee_elm327_init();
			receiveVehicleDataFSM_tran_(OBTAIN_VEHICLE_DATA);
			break;
		case OBTAIN_VEHICLE_DATA:
			RPM = ee_elm327_get(ENGINE_RPM);
			speed = ee_elm327_get(VEHICLE_SPEED);
			coolantTemp = ee_elm327_get(ENGINE_COOLANT_TEMP);
			fuelRemaining = ee_elm327_get(FUEL_REMAINING);
			receiveVehicleDataFSM_tran_(ACQUIRE_DATA_BUFFER_);
			break;
		case ACQUIRE_DATA_BUFFER_:
			GetResource(VEHICLE_DATA_BUFFER);
			receiveVehicleDataFSM_tran_(WRITE_BUFFER);
			break;
		case WRITE_BUFFER:
			if ((vehicleDataBuffer.ready & VEHICLE_DATA_VERSION) == 0) {
				vehicleDataBuffer.Elm327version[0] = version[0];
				vehicleDataBuffer.Elm327version[1] = version[1];
				vehicleDataBuffer.Elm327version[2] = version[2];
				vehicleDataBuffer.Elm327version[3] = version[3];
				vehicleDataBuffer.ready |= VEHICLE_DATA_VERSION;
			}
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
			receiveVehicleDataFSM_tran_(RELEASE_DATA_BUFFER_);
			break;
		case RELEASE_DATA_BUFFER_:
			ReleaseResource(VEHICLE_DATA_BUFFER);
			receiveVehicleDataFSM_tran_(OBTAIN_VEHICLE_DATA);
			return;
			break;
		default:
			return;
			break;
		}
	}
}

