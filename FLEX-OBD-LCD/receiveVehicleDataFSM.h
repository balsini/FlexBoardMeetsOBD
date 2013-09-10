/*
 * FSM.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef RECEIVEVEHICLEDATAFSM_H_
#define RECEIVEVEHICLEDATAFSM_H_

#include "constants.h"

typedef enum receiveVehicleDataStatus_ {
	ELM327_INIT,
	REQUEST_DATA,
	RECEIVE_DATA,
	ACQUIRE_DATA_BUFFER_,
	WRITE_BUFFER,
	RELEASE_DATA_BUFFER_
} receiveVehicleDataStatus;

void receiveVehicleDataFSM_init();
void receiveVehicleDataFSM_tran_(receiveVehicleDataStatus dest);
void receiveVehicleDataFSM_dispatch();

#endif /* RECEIVEVEHICLEDATAFSM_H_ */
