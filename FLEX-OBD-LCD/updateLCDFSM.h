/*
 * FSM.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef UPDATELCDFSM_H_
#define UPDATELCDFSM_H_

#include "constants.h"

/**
 * The possible states of the state
 * machine.
 */

typedef enum updateLCDStatus_ {
	WAIT_FOR_BUFFER_FULL,
	ACQUIRE_DATA_BUFFER,
	READ_BUFFER_AND_REFRESH,
	RELEASE_DATA_BUFFER,
	REFRESH_LCD
} updateLCDStatus;

/**
 * Initializes the state machine.
 */

void updateLCDFSM_init();

/**
 * Generates a state transition of the
 * state machine.
 * @param dest The new state.
 */

void updateLCDFSM_tran_(updateLCDStatus dest);

/**
 * Performs the operations defined in the
 * actual status of the state machine.
 */

void updateLCDFSM_dispatch();

#endif /* UPDATELCDFSM_H_ */
