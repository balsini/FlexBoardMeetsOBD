/*
 * FSM.h
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#ifndef UPDATELCDFSM_H_
#define UPDATELCDFSM_H_

#include "constants.h"

typedef enum updateLCDStatus_ {
	WAIT_FOR_BUFFER_FULL,
	ACQUIRE_DATA_BUFFER,
	READ_BUFFER_AND_REFRESH,
	RELEASE_DATA_BUFFER,
	REFRESH_LCD
} updateLCDStatus;

void updateLCDFSM_init();
void updateLCDFSM_tran_(updateLCDStatus dest);
void updateLCDFSM_dispatch();

#endif /* UPDATELCDFSM_H_ */
