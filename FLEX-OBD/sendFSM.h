/*
 * sendFSM.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef SENDFSM_H_
#define SENDFSM_H_

typedef enum sendStatus_ {
	START, DEAD,

	WAIT_FOR_PING,

	BT_INIT, BT_INQUIRY, BT_INQUIRY_SHOW,
	BT_INQUIRY_RESCAN, BT_CONNECT
} sendStatus;

void sendFSM_init();
void sendFSM_tran_(sendStatus dest);
void sendFSM_dispatch();

#endif /* SENDFSM_H_ */
