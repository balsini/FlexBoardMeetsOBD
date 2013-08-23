#ifndef SERIAL_H
#define SERIAL_H

#include <QList>
#include <QDir>
#include <string>

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
    Serial_t serialConfig;

public:
    Serial();
    QStringList getDevices();
    void setConfig(Serial_t config) {
        serialConfig.device = config.device;
        serialConfig.baud_rate = config.baud_rate;
        serialConfig.parity = config.parity;
        serialConfig.bits = config.bits;
        serialConfig.stop_bits = config.stop_bits;
    }
};

#endif // SERIAL_H
