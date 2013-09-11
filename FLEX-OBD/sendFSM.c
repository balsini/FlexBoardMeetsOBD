/*
 * sendFSM.c
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#include "sendFSM.h"

#include "constants.h"
#include "ee_uartusb.h"
#include "ee_bluetooth.h"
#include "ee_elm327.h"
#include "datagram.h"

sendStatus sendStatus_;

void sendFSM_init()
{
	sendStatus_ = SEND_START;
}

void sendFSM_tran_(sendStatus dest)
{
	sendStatus_ = dest;
}

void sendFSM_dispatch()
{
	switch (sendStatus_) {
		default:
			EE_bluetooth_release();
			break;
	}
}

