/*
 * FSM.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef MAINFSM_H_
#define MAINFSM_H_

#include "constants.h"

typedef enum mainStatus_ {
	WELCOME, DEAD,

	BT_INQUIRY, BT_INQUIRY_SHOW, BT_INQUIRY_SHOW_MOVE,
	BT_INQUIRY_RESCAN,

	BT_CONNECT, BT_CONNECT_VERIFY,

	BT_INIT, BT_COMMUNICATE
} mainStatus;

void mainFSM_init();
void mainFSM_tran_(mainStatus dest);
void mainFSM_dispatch();

#endif /* MAINFSM_H_ */
