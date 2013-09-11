/*
 * ee_usb.c
 *
 *  Created on: 24/ago/2013
 *      Author: Administrator
 */

#include "ee_uartusb.h"

void EE_uartusb_init(EE_UINT32 baud, EE_UINT16 byteformat, EE_UINT16 mode)
{
#if USB_UART == 1
	EE_UART1_Init(baud, byteformat, mode);
#else
	EE_UART2_Init(baud, byteformat, mode);
#endif
}

void EE_uartusb_sendC(unsigned char c)
{
#if USB_UART == 1
	EE_UART1_Send(c);
#else
	EE_UART2_Send(c);
#endif
}

void EE_uartusb_sendS(unsigned char * str)
{
	for (; *str != '\0'; str++)
		EE_uartusb_sendC(*str);
}

unsigned char EE_uartusb_receive_no_timeout()
{
	static unsigned char RxBuff;
#if USB_UART == 1
	while(EE_UART1_Receive(&RxBuff)) ;
#else
	while(EE_UART2_Receive(&RxBuff)) ;
#endif
	return RxBuff;
}

unsigned char EE_uartusb_receive()
{
	volatile static unsigned int i;
	volatile static unsigned int limit = 0xFFFD;
	static unsigned char RxBuff;
	i = 0;
#if USB_UART == 1
	while(EE_UART1_Receive(&RxBuff) && i < limit)
		i++;
#else
	while(EE_UART2_Receive(&RxBuff) && i < limit)
		i++;
#endif
	return i < limit ? RxBuff : 0xFF;
}
