/*
 * mainFSM.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef FSM_H_
#define FSM_H_

/**
 * The possible states of the state
 * machine.
 */

typedef enum mainStatus_ {
	MAIN_START, MAIN_DEAD,

	WAIT_FOR_PING, WAIT_FOR_REQUEST,

	BT_INIT, BT_INQUIRY, BT_INQUIRY_SHOW,
	BT_CONNECT
} mainStatus;

/**
 * Initializes the state machine.
 */

void mainFSM_init();

/**
 * Generates a state transition of the
 * state machine.
 * @param dest The new state.
 */

void mainFSM_tran_(mainStatus dest);

/**
 * Performs the operations defined in the
 * actual status of the state machine.
 */

void mainFSM_dispatch();

#endif /* FSM_H_ */
