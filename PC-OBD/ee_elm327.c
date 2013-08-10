/*
 * ee_elm327.c
 *
 *  Created on: 08/ago/2013
 *      Author: Alessio
 */

#ifndef EE_ELM327_C_
#define EE_ELM327_C_

#include "ee_elm327.h"
#include "bluetooth.h"

char echo_enabled;
char version[4];

inline int EE_elm327_check_response_no_timeout(char * response)
{
	static unsigned char value = 0;
	static char ret;

	ret = 1;
	for (; *response != '\0'; response++) {
		if (*response != (value = EE_bluetooth_receive_no_timeout())) {
			ret = 0;
			break;
		}
	}
	while (EE_bluetooth_receive_no_timeout() != '>') ;
	return ret;
}

void ee_elm327_init()
{
	echo_enabled = 1;
	ee_elm327_set_echo(0);
	ee_elm327_reboot();
}

int ee_elm327_set_echo(char val)
{
	char ret = 0;

	if (echo_enabled == val)
		return 1;

	switch (val) {
	case 0:
		EE_bluetooth_sendS("AT E0\r");
		ret = EE_elm327_check_response_no_timeout("AT E0\rOK\r\r");
		if (ret)
			echo_enabled = 0;
		break;
	case 1:
		EE_bluetooth_sendS("AT E1\r");
		ret = EE_elm327_check_response_no_timeout("OK\r\r");
		if (ret)
			echo_enabled = 1;
		break;
	default:
		break;
	}

	return ret;
}

int ee_elm327_reboot()
{
	int i;
	EE_bluetooth_sendS("AT Z\r");
	while (EE_bluetooth_receive() != 'v') ;
	for (i=0; i<3; i++)
		version[i] = EE_bluetooth_receive();
	version[3] = '\0';
	return EE_elm327_check_response_no_timeout("\r\r");
}

char * ee_elm327_get_version()
{
	return version;
}

#endif /* EE_ELM327_C_ */
