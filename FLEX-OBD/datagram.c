#include "datagram.h"
#include "ee_uartusb.h"

void constructDatagram(Datagram * dg,
		unsigned char type,
		unsigned char id,
		unsigned char size,
		unsigned char * data)
{
	dg->type = type;
	dg->id = id;
	dg->size = size;
	dg->data = data;
}

void sendDatagram(Datagram * datagram)
{
	EE_uartusb_sendC(datagram->type);
	EE_uartusb_sendC(datagram->id);
	EE_uartusb_sendC(datagram->size);
	if (datagram->size > 0)
		EE_uartusb_sendS((char *)datagram->data);
}

void sendDatagramSmall(unsigned char type, unsigned char id)
{
	Datagram dg;
	dg.type = type;
	dg.id = id;
	dg.size = 0;
	dg.data = 0;
	sendDatagram(&dg);
}

void receiveDatagram(Datagram * datagram)
{
	int i;
	datagram->type = EE_uartusb_receive_no_timeout();
	datagram->id = EE_uartusb_receive_no_timeout();
	datagram->size = EE_uartusb_receive_no_timeout();
	if (datagram->size > 0) {
		for (i=0; i<datagram->size; i++)
			datagram->data[i] = EE_uartusb_receive_no_timeout();
	}
}
