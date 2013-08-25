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

    int tty_fd;

public:
    Serial();
    ~Serial();
    int writeS(unsigned char * str, unsigned int len);
    int writeC(unsigned char c);
    int readS(void * buffer, unsigned int nbytes);
    char readC();
    QStringList getDevices();
    void setConfig(Serial_t config);
    int connect();
};

#endif // SERIAL_H
