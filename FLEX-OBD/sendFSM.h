/*
 * sendFSM.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef SENDFSM_H_
#define SENDFSM_H_

typedef enum sendStatus_ {
	SEND_START, SEND_DEAD
} sendStatus;

void sendFSM_init();
void sendFSM_tran_(sendStatus dest);
void sendFSM_dispatch();

#endif /* SENDFSM_H_ */
