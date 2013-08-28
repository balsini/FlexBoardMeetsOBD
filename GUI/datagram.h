#ifndef DATAGRAM_H
#define DATAGRAM_H

#define REQUEST     0x00
#define RESPONSE    0x01
#define DATA        0x02

#define HELLO       0x00
#define CONNECT_TO  0x01
#define GET_BITMASK 0x02
#define STOP        0x03
#define SUCCESS     0x04
#define FAIL        0x05
#define INQUIRY     0x06
#define OK          0x07

typedef struct Datagram_ {
    unsigned char type;     // Discriminates if command or data
    unsigned char id;       // Discriminates the command/data identifier
    unsigned char size;     // Size of following data entry
    unsigned char * data;
} Datagram;

void constructDatagram(Datagram * dg,
                       unsigned char type,
                       unsigned char id,
                       unsigned char size = 0,
                       unsigned char * data = 0);
void destructDatagramData(Datagram * dg);
void sendDatagram(void * serial, Datagram * datagram);
void sendDatagram(void * serial, unsigned char type, unsigned char id);
void receiveDatagram(void * serial, Datagram * datagram);
void receiveDatagramTimeout(void * serial, Datagram * datagram);
float translateDatagramData(Datagram * datagram);

#endif // PCFLEX_DATAGRAM_H
