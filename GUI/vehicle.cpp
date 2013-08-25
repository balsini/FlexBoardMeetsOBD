#include "vehicle.h"

Vehicle::Vehicle(Serial * serial)
{
    this->serial = serial;
    clearBitmask();

    Worker * worker = new Worker(serial);
    worker->moveToThread(&workerThread);
    connect(worker, SIGNAL(resultReady(Datagram)), this, SLOT(handleDatagram(Datagram)));
    workerThread.start();
}

void Vehicle::clearBitmask()
{
    for (unsigned int i=0; i<VEHICLE_BITMASK_SIZE; i++)
        bitmask[i] = 0;
}

void Vehicle::setBitmaskBit(unsigned int bit)
{
    bitmask[bit/8] |= 0x1 << (bit % 8);
}

void Vehicle::getBitmaskBits(QList<unsigned int> * bitList)
{
    for (unsigned int i=0; i<VEHICLE_BITMASK_SIZE*8; i++) {
        if (bitmask[i/8] & (0x1 << (i % 8)))
            bitList->append(i);
    }
}

void Vehicle::handleDatagram(Datagram datagram)
{}
