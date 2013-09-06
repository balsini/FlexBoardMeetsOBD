/**
 * @file    serial.h
 * @author  Alessio Balsini <alessio.balsini@gmail.com>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * Serial connection management.
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <QDebug>

#include <QList>
#include <QDir>

#include <string>

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <termios.h>
#include <fcntl.h>

/**
 * This struct contains the basic serial connection
 * parameters.
 */

typedef struct Serial_t_ {
    std::string device;
    unsigned int baud_rate;
    unsigned char parity;
    unsigned char bits;
    unsigned char stop_bits;
} Serial_t;

/**
 * The Serial class allows to configure serial device,
 * estabilish a serial connection and exchanging serial
 * data.
 */

class Serial
{
    QStringList devicesList;
    Serial_t serialConfig;  // Temporary configuration
    struct termios attribs; // Real configuration

    fd_set select_set;
    int tty_fd;
    struct timeval tv;

public:

    /**
     * Initializes the class with default values.
     */

    Serial();
    ~Serial();

    /**
     * Writes a string to serial port.
     * @param str The string to be sent.
     * @param len The string length.
     * @return The bytes sent number.
     */

    int writeS(unsigned char * str, unsigned int len);

    /**
     * Writes a char to serial port.
     * @param c The character to be sent.
     * @return The bytes sent number.
     */

    int writeC(unsigned char c);

    /**
     * Reads a string from serial port. This function
     * has no timeout, so it may lock forever if no data
     * is received.
     * @param buffer Buffer in which the string will be
     * stored.
     * @param nbytes The desired string length.
     * @return The number of bytes received.
     */

    int readS(void * buffer, unsigned int nbytes);

    /**
     * Reads a string from serial port with timeout.
     * If no data is received in a short period, then
     * the function returns.
     * @param buffer Buffer in which the string will be
     * stored.
     * @param nbytes The desired string length.
     * @return -1 If timeout is expired.
     * @return 0 If data is received.
     */

    int readSTimeout(void * buffer, unsigned int nbytes);

    /**
     * Reads a character from serial port. This function
     * has no timeout, so it may lock forever if no data
     * is received.
     * @return The character read.
     */

    unsigned char readC();

    /**
     * Reads a character from serial port. If no data is
     * received in a short period, then the function
     * returns.
     * @param buff The buffer in which data is stored.
     * @return -1 If timeout is expired.
     * @return 0 If data is received.
     */

    int readCTimeout(unsigned char * buff);

    /**
     * Flushes serial data buffer.
     */

    void flush();

    /**
     * Gets the list of serial devices.
     * @return The list of serial devices found.
     */

    QStringList getDevices();

    /**
     * Sets the serial configuration.
     * @param config The struct containing all the basic
     * configuration parameters.
     */

    void setConfig(Serial_t config);

    /**
     * Establishes the serial connection.
     * @return The file descriptor associated to
     * the serial device.
     */

    int connect();

    /**
     * Closes the file descriptor associated to
     * the serial device.
     */

    void disconnect();
};

#endif // SERIAL_H
