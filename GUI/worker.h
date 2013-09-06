/**
 * @file    worker.h
 * @author  Alessio Balsini <alessio.balsini@gmail.com>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * A thread which serially communicates with the Flex.
 */

#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QSemaphore>

#include "bluetoothdevices.h"

#include "datagram.h"
#include "serial.h"

/**
 * The worker's state machine's possible states.
 */

typedef enum WorkerStatus_ {
    BRIDGE_CONNECT,
    INQUIRY_REQ,
    CONNECT,
    SEND_BITMASK,
    DATA_LOOP,
    QUIT,
    KILL,
    WAIT
} WorkerStatus;

/**
 * The Worker class is a thread which serially
 * communicates with the Flex, acting as a layer
 * between the Flex and the higher levels.
 */

class Worker : public QThread
{
    Q_OBJECT

    QThread workerThread;
    QWidget * parent;

    Serial * serial;
    void * vehicle;

    bool active;
    WorkerStatus status;
    QSemaphore * sync;

    int btDeviceIndexChosen;

    /**
     * Pings the Flex, checking if it's alive.
     * @return 0 If the Flex is alive.
     * @return -1 If Flex does not send the pong
     * during the timeout interval.
     */

    int bridge_connect();

    /**
     * Requests the Bluetooth inquiry to the Flex
     * and returns the results to higher levels.
     * @return 0 If user chooses a device.
     * @return -1 If user discards the inquiry
     * results.
     */

    int inquiry();

    /**
     * Establishes the connection to the vehicle.
     * @return 0 If the connection is established.
     * @return -1 If something went wrong.
     */

    int connection();

    /**
     * Sends the bitmask to the vehicle.
     * @return 0 If everything is ok.
     * @return -1 If something went wrong.
     */

    int sendBitmask();

    /**
     * Retrieves data from the Flex and sends it
     * to higher levels.
     */

    void dataLoop();

    /**
     * Inquiry datagram is parsed to be managed in
     * a more confortable format.
     * @param result The inquiry_result_t vector in
     * which the inquiry result will be inserted.
     * @param The datagram to be parsed.
     * @return The number of devices discovered by
     * the inquiry.
     */

    unsigned char parseInquiryDatagram(inquiry_result_t ** result, Datagram * dg);

    /**
     * Kills the worker.
     */

    void kill();

protected:

    /**
     * Simply calls exec().
     */

    void run();

    /**
     * Is the state machine which manages the
     * communication with the Flex.
     */

    int exec();

public slots:

    /**
     * The Bluetooth connection will be established with
     * the device chosen.
     * @param num The identifier of the Bluetooth
     * device chosen.
     */

    void bluetoothDeviceChosen(int num);

    /**
     * The Bluetooth inquiry will be requested to the Flex.
     */

    void bridgeInquiry();

    /**
     * The connection to the Flex will be established.
     */

    void bridgeConnect();

    /**
     * The new bitmask will be sent to the Flex.
     */

    void bitmaskUpdated();

public:

    /**
     * Worker constructor.
     * @param serial The Serial identifier for data transmission.
     * @param vehicleParent The parent Vehicle.
     * @param parent The parent widget.
     */

    Worker(Serial * serial, void * vehicleParent, QWidget * parent);
    ~Worker();

    /**
     * Requests the Worker to shut down.
     */

    void killRequest();

signals:

    /**
     * Signals that Flex is connected.
     */

    void flexConnectedSignal();

    /**
     * Signals that vehicle is connected.
     */

    void vehicleConnectedSignal();

    /**
     * Signals the results of the inquiry.
     * @param data The inquiry results vector.
     * @param num The number of inquiry results.
     */

    void bluetoothInquiryCompleted(inquiry_result_t * data, unsigned int num);

    /**
     * Signals that new data is ready for one of the monitors.
     * @param monitor The monitor identifier for the data.
     * @param data The data for the monitor.
     */

    void resultReady(unsigned char monitor, float data);
};

#endif // WORKER_H
