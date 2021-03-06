/**
 * @file    datagram.h
 * @author  Alessio Balsini <alessio.balsini@gmail.com>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The data structures used to manage communication
 * packets during communication with PC.
 */

#ifndef DATAGRAM_H
#define DATAGRAM_H

/**
 * Request type.
 */

#define REQUEST     0x00

/**
 * Response type.
 */

#define RESPONSE    0x01

/**
 * Data type.
 */

#define DATA        0x02


/**
 * Hello response (like ping).
 */

#define HELLO       0x00

/**
 * Connect to specified device request.
 */

#define CONNECT_TO  0x01

/**
 * Bitmask request.
 */

#define GET_BITMASK 0x02

/**
 * Stop the data loop request.
 */

#define STOP        0x03

/**
 * Affermative response.
 */

#define SUCCESS     0x04

/**
 * Negative response.
 */

#define FAIL        0x05

/**
 * Inquiry request/response.
 */

#define INQUIRY     0x06

/**
 * Handshake response.
 */

#define OK          0x07

/**
  * Data struct which defines the packet.
  */

typedef struct Datagram_ {
    unsigned char type;     // Discriminates if command or data
    unsigned char id;       // Discriminates the command/data identifier
    unsigned char size;     // Size of following data entry
    unsigned char * data;
} Datagram;

/**
  * Packet constructor.
  * @param dg Datagram which will be filled.
  * @param type The type of the datagram (REQUEST, RESPONSE or DATA).
  * @param id The identifier of the type (i.e. GET_BITMASK or OK).
  * @param size The size of data field.
  * @param data The data of the packet.
  */

void constructDatagram(Datagram * dg,
                       unsigned char type,
                       unsigned char id,
                       unsigned char size,
                       unsigned char * data);

/**
  * Datagram sender.
  * @param datagram The datagram to be sent.
  */

void sendDatagram(Datagram * datagram);

/**
  * Datagram sender. It is similar to sendDatagram(), but it
  * is useful to directly send datagrams with no data.
  * @param type The type of the datagram to be sent.
  * @param id The identifier of the datagram to be sent.
  */

void sendDatagramSmall(unsigned char type, unsigned char id);

/**
  * Datagram receiver without timeout. This function may wait
  * forever if no data is received.
  * @param datagram The buffer in which the datagram will be stored.
  */

void receiveDatagram(Datagram * datagram);

#endif // PCFLEX_DATAGRAM_H
