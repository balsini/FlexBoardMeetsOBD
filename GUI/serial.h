#ifndef SERIAL_H
#define SERIAL_H

#include <QDebug>

#include <QList>
#include <QDir>

#include <string>

#include <termios.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct Serial_t_ {
    std::string device;
    unsigned int baud_rate;
    unsigned char parity;
    unsigned char bits;
    unsigned char stop_bits;
} Serial_t;

class Serial
{
    QStringList devicesList;
    Serial_t serialConfig;  // Temporary configuration
    struct termios attribs; // Real configuration

    fd_set select_set;
    int tty_fd;
    struct timeval tv;

public:
    Serial();
    ~Serial();
    int writeS(unsigned char * str, unsigned int len);
    int writeC(unsigned char c);
    int readS(void * buffer, unsigned int nbytes);
    int readSTimeout(void * buffer, unsigned int nbytes);
    unsigned char readC();
    unsigned char readCTimeout();
    QStringList getDevices();
    void setConfig(Serial_t config);
    int connect();
    void disconnect();
};

#endif // SERIAL_H
