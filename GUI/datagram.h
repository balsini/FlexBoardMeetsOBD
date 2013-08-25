#ifndef DATAGRAM_H
#define DATAGRAM_H

typedef struct Datagram_ {
    unsigned char type;     // Discriminates if command or data
    unsigned char id;       // Discriminates the command/data identifier
    unsigned char size;     // Size of following data entry
    unsigned char * data;
} Datagram;

#endif // PCFLEX_DATAGRAM_H
