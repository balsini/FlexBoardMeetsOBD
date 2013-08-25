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
    QThread workerThread;

public slots:
    void handleDatagram(Datagram datagram);

public:
    Vehicle(Serial * serial);
    void clearBitmask();
    void setBitmaskBit(unsigned int bitIdentifier);
    void getBitmaskBits(QList<unsigned int> * bitList);
};

#endif // VEHICLE_H
