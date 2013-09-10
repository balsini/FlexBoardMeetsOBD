/*
 * FSM.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef FSM_H_
#define FSM_H_

typedef enum mainStatus_ {
	WELCOME, DEAD,

	BT_INQUIRY, BT_INQUIRY_SHOW, BT_INQUIRY_SHOW_MOVE,
	BT_INQUIRY_RESCAN,

	BT_CONNECT, BT_CONNECT_VERIFY,

	BT_INIT, BT_COMMUNICATE
} mainStatus;

typedef enum mainSignal_ {ABSENT, B1, B2, B3, B4} Signal;

Signal mainFSM_getSignals();
void mainFSM_init();
void mainFSM_tran_(mainStatus dest);
void mainFSM_dispatch();

#endif /* FSM_H_ */
