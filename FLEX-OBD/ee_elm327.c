/*
 * ee_elm327.c
 *
 *  Created on: 08/ago/2013
 *      Author: Alessio
 */

#ifndef EE_ELM327_C_
#define EE_ELM327_C_

#include "ee_elm327.h"
#include "ee_bluetooth.h"

char echo_enabled;
char version[4];

MPR_t MPR[4];

void EE_elm327_MPR_assign(char * mode, char * PID, char byte, MPR_index_t index)
{
	MPR[index].mode[0] = mode[0];
	MPR[index].mode[1] = mode[1];
	MPR[index].mode[2] = '\0';
	MPR[index].PID[0] = PID[0];
	MPR[index].PID[1] = PID[1];
	MPR[index].PID[2] = '\0';
	MPR[index].return_byte_num = byte;
}

void EE_elm327_MPR_init()
{
	EE_elm327_MPR_assign("01", "05", 1, ENGINE_COOLANT_TEMP);
	EE_elm327_MPR_assign("01", "0C", 2, ENGINE_RPM);
	EE_elm327_MPR_assign("01", "0D", 1, VEHICLE_SPEED);
	EE_elm327_MPR_assign("01", "11", 1, THROTTLE_POSITION);
}

int hex_converter(char * hex, char len)
{
    int i;
    int ret = 0;
    int power = 1;

    for (i=0; i<len; i++) {
        if (hex[len-i-1] <= 'F' && hex[len-i-1] >= 'A')
            ret += (hex[len-i-1] - 'A' + 10) * power;
        else if (hex[len-i-1] <= '9' && hex[len-i-1] >= '0')
            ret += (hex[len-i-1] - '0') * power;
        else
            return -1;
        power *= 16;
    }

	return ret;
}

int ee_elm327_get(MPR_index_t identifier)
{
	char return_value[25];
	int i;

	EE_bluetooth_sendS(MPR[identifier].mode);
	EE_bluetooth_sendS(" ");
	EE_bluetooth_sendS(MPR[identifier].PID);
	EE_bluetooth_sendS("\r\n");

	for (i=0; i<5; i++)
		EE_bluetooth_receive();

	i=0;
	for (;;) {
		return_value[i*2] = EE_bluetooth_receive();
		return_value[i*2 + 1] = EE_bluetooth_receive();
		i++;
		if (i<MPR[identifier].return_byte_num)
			EE_bluetooth_receive(); // spacing
		else
			break;
	}
	return_value[i] = '\0';

	while (EE_bluetooth_receive() != '>') ;

	return hex_converter(return_value, MPR[identifier].return_byte_num);
}

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
	EE_elm327_MPR_init();
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
