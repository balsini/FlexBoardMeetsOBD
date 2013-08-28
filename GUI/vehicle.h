#ifndef VEHICLE_H
#define VEHICLE_H

#include <QThread>

#include "serial.h"
#include "worker.h"
#include "datagram.h"

#define VEHICLE_BITMASK_SIZE 4

class Vehicle : public QObject
{
    Q_OBJECT

    char bitmask[VEHICLE_BITMASK_SIZE];

    Serial * serial;
    Worker * worker;
    QThread workerThread;

    QWidget * parent;

public slots:
    void handleDatagram(Datagram datagram);
    void bluetoothDeviceChosen(int num);
    void bridgeInquiry();
    void bridgeConnect();
    void bitmaskUpdated();

public:
    Vehicle(Serial * serial, QWidget * parent);
    ~Vehicle();
    void clearBitmask();
    void getBitmask(unsigned char * bitMask);
    void setBitmaskBit(unsigned int bitIdentifier);
    void clearBitmaskBit(unsigned int bitIdentifier);
    void getBitmaskBits(QList<unsigned int> * bitList);
    unsigned char getBitmaskSize();
    void start();
};

#endif // VEHICLE_H
