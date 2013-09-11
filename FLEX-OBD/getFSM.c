/*
 * getFSM.c
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#include "getFSM.h"

#include "constants.h"
#include "ee_uartusb.h"
#include "ee_bluetooth.h"
#include "ee_elm327.h"
#include "datagram.h"

getStatus getStatus_;

void getFSM_init()
{
	getStatus_ = GET_START;
}

void getFSM_tran_(getStatus dest)
{
	getStatus_ = dest;
}

void getFSM_dispatch()
{
	switch (getStatus_) {
	default:
		EE_bluetooth_release();
		break;
	}
}

