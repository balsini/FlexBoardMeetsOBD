/*
 * FSM.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef MAINFSM_H_
#define MAINFSM_H_

#include "constants.h"

/**
 * The possible states of the state
 * machine.
 */

typedef enum mainStatus_ {
	WELCOME, DEAD,

	BT_INQUIRY, BT_INQUIRY_SHOW, BT_INQUIRY_SHOW_MOVE,
	BT_INQUIRY_RESCAN,

	BT_CONNECT, BT_CONNECT_VERIFY,

	BT_INIT, BT_COMMUNICATE
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

#endif /* MAINFSM_H_ */
