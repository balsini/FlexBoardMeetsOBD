/*
 * FSM.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef FSM_H_
#define FSM_H_

#include "ee_bluetooth.h"
#include "buttons.h"
#include "constants.h"

typedef enum Status_ {
	WELCOME, BT_INIT,

	BT_INQUIRY, BT_INQUIRY_SHOW, BT_INQUIRY_SHOW_MOVE,
	BT_INQUIRY_RESCAN,

	BT_CONNECT,

	WAIT, DEAD
} Status;

typedef enum Signal_ {ABSENT, B1, B2, B3, B4} Signal;

Signal FSM_getSignals();
void FSM_init();
void FSM_tran_(Status dest);
void FSM_dispatch();

#endif /* FSM_H_ */
