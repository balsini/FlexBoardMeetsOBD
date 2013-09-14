/*
 * FSM.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef RECEIVEVEHICLEDATAFSM_H_
#define RECEIVEVEHICLEDATAFSM_H_

#include "constants.h"

/**
 * The possible states of the state
 * machine.
 */

typedef enum receiveVehicleDataStatus_ {
	ELM327_INIT,
	OBTAIN_VEHICLE_DATA,
	ACQUIRE_DATA_BUFFER_,
	WRITE_BUFFER,
	RELEASE_DATA_BUFFER_
} receiveVehicleDataStatus;

/**
 * Initializes the state machine.
 */

void receiveVehicleDataFSM_init();

/**
 * Generates a state transition of the
 * state machine.
 * @param dest The new state.
 */

void receiveVehicleDataFSM_tran_(receiveVehicleDataStatus dest);

/**
 * Performs the operations defined in the
 * actual status of the state machine.
 */

void receiveVehicleDataFSM_dispatch();

#endif /* RECEIVEVEHICLEDATAFSM_H_ */
