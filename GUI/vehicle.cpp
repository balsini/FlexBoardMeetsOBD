#include "vehicle.h"
#include "mainwindow.h"

Vehicle::Vehicle(Serial * serial, QWidget * parent)
{
    this->parent = parent;
    this->serial = serial;
    clearBitmask();

    worker = new Worker(serial, parent);
    worker->moveToThread(&workerThread);
    //connect(worker, SIGNAL(resultReady(Datagram)), this, SLOT(handleDatagram(Datagram)));
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
{
    qDebug("Received datagram to be hadled");
    qDebug() << datagram.data;
}

void Vehicle::start()
{
    worker->start();
}

void Vehicle::bluetoothDeviceChosen(int num)
{
    worker->bluetoothDeviceChosen(num);
}
