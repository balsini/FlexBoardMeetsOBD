/*
 * ee_bluetooth.c
 *
 *  Created on: 26/mar/2013
 *      Author: Alessio
 */

#include "ee_bluetooth.h"

char uartNum;

inline void EE_bluetooth_sendC(unsigned char c)
{
	if (uartNum == 1)
		EE_UART1_Send(c);
	else
		EE_UART2_Send(c);
}

inline void EE_bluetooth_sendS(char * str)
{
	while (*str != '\0') {
		EE_bluetooth_sendC(*(unsigned char *)str);
		str++;
	}
}

inline unsigned char EE_bluetooth_receive()
{
	static unsigned char RxBuff;
	if (uartNum == 1)
		while(EE_UART1_Receive(&RxBuff) != 0);
	else
		while(EE_UART2_Receive(&RxBuff) != 0);
	return RxBuff;
}

/*
 * 0 is returned if the response is wrong,
 * 1 otherwise
 */

inline int EE_bluetooth_check_response(char * response)
{
	while (*response != '\0') {
		if (*response != EE_bluetooth_receive())
			return 0;
		response++;
	}
	return 1;
}

int EE_bluetooth_alive()
{
	int alive;
	EE_bluetooth_sendS("$$$");
	alive = EE_bluetooth_check_response("CMD");
	if (alive) {
		EE_bluetooth_sendS("---");
		EE_bluetooth_sendC(13); // <cr>
	}
	return alive;
}

int EE_bluetooth_init(EE_UINT8 uart,
		EE_UINT32 baud,
		EE_UINT16 byteformat,
		EE_UINT16 mode)
{
	uartNum = uart;

	if (uartNum == 1) {
		EE_UART1_Init(baud, byteformat, mode);
	} else {
		EE_UART2_Init(baud, byteformat, mode);
	}

	return EE_bluetooth_alive() == 1 ? 0 : -1;
}
