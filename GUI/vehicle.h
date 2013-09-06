/**
 * @file    vehicle.h
 * @author  Alessio Balsini <alessio.balsini@gmail.com>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The vehicle manager.
 */

#ifndef VEHICLE_H
#define VEHICLE_H

#include <QThread>

#include "serial.h"
#include "worker.h"
#include "datagram.h"

/**
 * The size of the bitmask
 */

#define VEHICLE_BITMASK_SIZE 4

/**
 * The Vehicle class manages the higher level
 * connection with the vehicle, managing the
 * bitmask, and acting as a bridge between the
 * GUI and the lower levels.
 */

class Vehicle : public QObject
{
    Q_OBJECT

    char bitmask[VEHICLE_BITMASK_SIZE];

    Serial * serial;
    Worker * worker;
    QThread workerThread;

    QWidget * parent;

public slots:

    /**
     * The datagram arrival is printed on
     * debugging stream.
     */

    void handleDatagram(Datagram datagram);

    /**
     * User has chosen the Bluetoot device to
     * which the connection must be established,
     * so Worker is notified about that.
     * @param num The Bluetooth inquiry identifier.
     */

    void bluetoothDeviceChosen(int num);

    /**
     * Requests the Worker to perform an inquiry.
     */

    void bridgeInquiry();

    /**
     * Requests the Worker to connect to the Flex.
     */

    void bridgeConnect();

    /**
     * Requests the Worker to update the bitmask.
     */

    void bitmaskUpdated();

public:

    /**
     * Vehicle constructor.
     * @param serial The serial identifier for data
     * transmission.
     * @param parent The parent widget.
     */

    Vehicle(Serial * serial, QWidget * parent);
    ~Vehicle();

    /**
     * Sets all the bitmask bits to 0.
     */

    void clearBitmask();

    /**
     * Returns a bitmask copy.
     * @param bitMask the buffer in which the bitmask
     * will be stored.
     */

    void getBitmask(unsigned char * bitMask);

    /**
     * Sets the chosen bitmask bit to 1.
     * @param bitIdentifier The bit identifier to be set.
     */

    void setBitmaskBit(unsigned int bitIdentifier);

    /**
     * Sets the chosen bitmask bit to 0.
     * @param bitIdentifier The bit identifier to be reset.
     */

    void clearBitmaskBit(unsigned int bitIdentifier);

    /**
     * Returns the set bitmask numbers as a list.
     * @param bitList The list which will be filled.
     */

    void getBitmaskBits(QList<unsigned int> * bitList);

    /**
     * Gets the bitmask size.
     * @return The bitmask size in bytes.
     */

    unsigned char getBitmaskSize();

    /**
     * Enables the Worker.
     */

    void start();
};

#endif // VEHICLE_H
