#ifndef DATAGRAM_H
#define DATAGRAM_H

#define COMMAND 0x00
#define DATA    0x01

#define HELLO   0x00
#define CONNECT_TO 0x01
#define GET_BITMASK 0x02
#define STOP 0x03

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

#endif // PCFLEX_DATAGRAM_H
