#include "vehicle.h"
#include "mainwindow.h"

Vehicle::Vehicle(Serial * serial, QWidget * parent)
{
    this->parent = parent;
    this->serial = serial;
    clearBitmask();

    worker = new Worker(serial, this, parent);
    worker->moveToThread(&workerThread);
}

Vehicle::~Vehicle()
{
    worker->killRequest();
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

void Vehicle::clearBitmaskBit(unsigned int bit)
{
    bitmask[bit/8] &= 0xFF ^ (0x1 << (bit % 8));
}

void Vehicle::bitmaskUpdated()
{
    emit worker->bitmaskUpdated();
}

void Vehicle::getBitmask(unsigned char * bitMask)
{
    for (unsigned int i=0; i<VEHICLE_BITMASK_SIZE; i++)
        bitMask[i] = bitmask[i];
}

void Vehicle::getBitmaskBits(QList<unsigned int> * bitList)
{
    for (unsigned int i=0; i<VEHICLE_BITMASK_SIZE*8; i++) {
        if (bitmask[i/8] & (0x1 << (i % 8)))
            bitList->append(i);
    }
}

unsigned char Vehicle::getBitmaskSize()
{
    return VEHICLE_BITMASK_SIZE;
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

void Vehicle::bridgeInquiry()
{
    worker->bridgeInquiry();
}

void Vehicle::bridgeConnect()
{
    worker->bridgeConnect();
}
