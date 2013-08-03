/*
 * ee_bluetooth.c
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#include "ee_bluetooth.h"

/*
 * Sending commands are like
 * <COMMAND>,<VALUE><'\r'>
 * Responses are like
 * <RESPONSE><"\r\n">
 */

int EE_bluetooth_commandModeEnter()
{
	EE_bluetooth_sendS("$$$");
	return EE_bluetooth_check_response("CMD");
}

int EE_bluetooth_commandModeLeave()
{
	EE_bluetooth_sendS("---\r");
	return EE_bluetooth_check_response("END");
}

void EE_bluetooth_sendC(unsigned char c)
{
#if BT_UART == 1
	EE_UART1_Send(c);
#else
	EE_UART2_Send(c);
#endif
}

void EE_bluetooth_sendS(char * str)
{
	for (; *str != '\0'; str++)
		EE_bluetooth_sendC(*(unsigned char *)str);
}

inline unsigned char EE_bluetooth_receive()
{
	static unsigned int i;
	static unsigned int limit = 50000;
	static unsigned char RxBuff;
	i = 0;
#if BT_UART == 1
	while(EE_UART1_Receive(&RxBuff) != 0 && i < limit)
		i++;
#else
	while(EE_UART2_Receive(&RxBuff) != 0 && i < limit)
		i++;
#endif
	return i < limit ? RxBuff : 0xFF;
}


int EE_bluetooth_set_slave()
{
	int ret;
	EE_bluetooth_commandModeEnter();
	// Check if already in Master mode
	EE_bluetooth_sendS("GM\r");
	if (EE_bluetooth_check_response("Slav"))
		return 1;	// Already in Master mode

	// Forces the Master mode
	EE_bluetooth_sendS("SM,0\r");
	EE_bluetooth_check_response("AOK");

	// Checks if changes took effect
	EE_bluetooth_sendS("GM\r");
	ret = EE_bluetooth_check_response("Slav");
	EE_bluetooth_commandModeLeave();
	return ret;
}

int EE_bluetooth_set_master()
{
	int ret;
	EE_bluetooth_commandModeEnter();
	// Check if already in Master mode
	EE_bluetooth_sendS("GM\r");
	if (EE_bluetooth_check_response("Mstr"))
		return 1;	// Already in Master mode

	// Forces the Master mode
	EE_bluetooth_sendS("SM,1\r");
	EE_bluetooth_check_response("AOK");

	// Checks if changes took effect
	EE_bluetooth_sendS("GM\r");
	ret = EE_bluetooth_check_response("Mstr");
	EE_bluetooth_commandModeLeave();
	return ret;
}

/*
 * 0 is returned if the response is wrong,
 * 1 otherwise
 */

int EE_bluetooth_check_response(char * response)
{
	int correct = 1;
	unsigned char value = 0;
	for (; *response != '\0'; response++) {
		if (*response != (value = EE_bluetooth_receive())) {
			correct = 0;
			break;
		}
	}
	if (value == 0xFF)
		return 0;
	while ((value = EE_bluetooth_receive()) != 0x0D) {
		if (value == 0xFF)
				return 0;
	}
	while ((value = EE_bluetooth_receive()) != 0x0A) {
		if (value == 0xFF)
				return 0;
	}
	return correct;
}

int EE_bluetooth_alive()
{
	if (EE_bluetooth_commandModeEnter())
		return EE_bluetooth_commandModeLeave();
	return 0;
}

int EE_bluetooth_init(EE_UINT32 baud,
		EE_UINT16 byteformat,
		EE_UINT16 mode)
{
#if BT_UART == 1
	EE_UART1_Init(baud, byteformat, mode);
#else
	EE_UART2_Init(baud, byteformat, mode);
#endif

	return EE_bluetooth_alive();
}
