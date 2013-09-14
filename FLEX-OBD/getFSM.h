/*
 * getFSM.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef GETFSM_H_
#define GETFSM_H_

/**
 * The possible states of the state
 * machine.
 */

typedef enum getStatus_ {
	ELM327_INIT,
	OBTAIN_VEHICLE_DATA,
	ACQUIRE_DATA_BUFFER,
	WRITE_BUFFER,
	RELEASE_DATA_BUFFER
} getStatus;

/**
 * Initializes the state machine.
 */

void getFSM_init();

/**
 * Generates a state transition of the
 * state machine.
 * @param dest The new state.
 */

void getFSM_tran_(getStatus dest);

/**
 * Performs the operations defined in the
 * actual status of the state machine.
 */

void getFSM_dispatch();

#endif /* GETFSM_H_ */
