#include "datagram.h"
#include "serial.h"

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

void destructDatagramData(Datagram * dg)
{
    if (dg->size > 0 && dg->data != 0)
        delete dg->data;
}

void sendDatagram(void * serial, Datagram * datagram)
{
    ((Serial *)serial)->writeC(datagram->type);
    ((Serial *)serial)->writeC(datagram->id);
    ((Serial *)serial)->writeC(datagram->size);
    if (datagram->size > 0)
        ((Serial *)serial)->writeS(datagram->data, datagram->size);
}

void sendDatagram(void * serial, unsigned char type, unsigned char id)
{
    Datagram dg;
    constructDatagram(&dg, type, id);
    sendDatagram(serial, &dg);
}

void receiveDatagram(void * serial, Datagram * datagram)
{
    datagram->type = ((Serial *)serial)->readC();
    datagram->id = ((Serial *)serial)->readC();
    datagram->size = ((Serial *)serial)->readC();
    if (datagram->size > 0) {
        datagram->data = new unsigned char[datagram->size];
        ((Serial *)serial)->readS(datagram->data, datagram->size);
    } else {
        datagram->data = 0;
    }
}

int receiveDatagramTimeout(void * serial, Datagram * datagram)
{
    if (((Serial *)serial)->readCTimeout(&datagram->type) == -1)
        return -1;
    datagram->id = ((Serial *)serial)->readC();
    datagram->size = ((Serial *)serial)->readC();
    if (datagram->size > 0) {
        datagram->data = new unsigned char[datagram->size];
        ((Serial *)serial)->readS(datagram->data, datagram->size);
    } else {
        datagram->data = 0;
    }
    return 0;
}

float translateDatagramData(Datagram * dg)
{
    float ret = 0;
    for (unsigned int i=0; i<dg->size; i++) {
        ret *= 256;
        ret += dg->data[i];
    }
    return ret;
}
