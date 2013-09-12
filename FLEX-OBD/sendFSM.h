/*
 * sendFSM.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef SENDFSM_H_
#define SENDFSM_H_

#define FUEL_	0
#define SPEED_	1
#define RPM_	2
#define WATER_TEMP_ 3


typedef enum sendStatus_ {
	WAIT_FOR_BUFFER_FULL,
	ACQUIRE_DATA_BUFFER_,
	READ_BUFFER,
	RELEASE_DATA_BUFFER_
} sendStatus;

void sendFSM_init();
void sendFSM_tran_(sendStatus dest);
void sendFSM_dispatch();

#endif /* SENDFSM_H_ */
