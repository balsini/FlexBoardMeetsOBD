/*
 * getFSM.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef GETFSM_H_
#define GETFSM_H_

typedef enum getStatus_ {
	GET_START,
	ELM327_INIT,
	OBTAIN_VEHICLE_DATA,
	ACQUIRE_DATA_BUFFER,
	WRITE_BUFFER,
	RELEASE_DATA_BUFFER
} getStatus;

void getFSM_init();
void getFSM_tran_(getStatus dest);
void getFSM_dispatch();

#endif /* GETFSM_H_ */
