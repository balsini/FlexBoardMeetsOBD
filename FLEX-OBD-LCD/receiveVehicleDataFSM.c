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
	EE_bluetooth_acquire();
}

void receiveVehicleDataFSM_tran_(receiveVehicleDataStatus dest)
{
	receiveVehicleDataStatus_ = dest;
}

void receiveVehicleDataFSM_dispatch()
{
	receiveVehicleDataFSM_tran_(REQUEST_DATA);
	for (;;) {
		switch (receiveVehicleDataStatus_) {
		case ELM327_INIT:
			ee_elm327_init();
			receiveVehicleDataFSM_tran_(REQUEST_DATA);
			break;
		case REQUEST_DATA:
			receiveVehicleDataFSM_tran_(RECEIVE_DATA);
			break;
		case RECEIVE_DATA:
			receiveVehicleDataFSM_tran_(ACQUIRE_DATA_BUFFER_);
			break;
		case ACQUIRE_DATA_BUFFER_:
			receiveVehicleDataFSM_tran_(WRITE_BUFFER);
			break;
		case WRITE_BUFFER:
			receiveVehicleDataFSM_tran_(RELEASE_DATA_BUFFER_);
			break;
		case RELEASE_DATA_BUFFER_:
			receiveVehicleDataFSM_tran_(REQUEST_DATA);
			return;
			break;
		default:
			break;
		}
	}
}

