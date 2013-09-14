/*
 * sendFSM.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef SENDFSM_H_
#define SENDFSM_H_

/**
 * The fuel identifier for PC communications.
 */

#define FUEL_	0

/**
 * The speed identifier for PC communications.
 */

#define SPEED_	1

/**
 * The RPM identifier for PC communications.
 */

#define RPM_	2

/**
 * The water temperature identifier for
 * PC communications.
 */

#define WATER_TEMP_ 3

/**
 * The possible states of the state
 * machine.
 */

typedef enum sendStatus_ {
	WAIT_FOR_BUFFER_FULL,
	ACQUIRE_DATA_BUFFER_,
	READ_BUFFER,
	RELEASE_DATA_BUFFER_
} sendStatus;

/**
 * Initializes the state machine.
 */

void sendFSM_init();

/**
 * Generates a state transition of the
 * state machine.
 * @param dest The new state.
 */

void sendFSM_tran_(sendStatus dest);

/**
 * Performs the operations defined in the
 * actual status of the state machine.
 */

void sendFSM_dispatch();

#endif /* SENDFSM_H_ */
