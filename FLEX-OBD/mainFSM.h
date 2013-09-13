/*
 * mainFSM.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef FSM_H_
#define FSM_H_

typedef enum mainStatus_ {
	MAIN_START, MAIN_DEAD,

	WAIT_FOR_PING, WAIT_FOR_REQUEST,

	BT_INIT, BT_INQUIRY, BT_INQUIRY_SHOW,
	BT_CONNECT
} mainStatus;

void mainFSM_init();
void mainFSM_tran_(mainStatus dest);
void mainFSM_dispatch();

#endif /* FSM_H_ */
