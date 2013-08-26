#include "datagram.h"

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
