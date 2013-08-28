#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QSemaphore>

#include "bluetoothdevices.h"

#include "datagram.h"
#include "serial.h"

typedef enum WorkerStatus_ {
    BRIDGE_CONNECT,
    INQUIRY_REQ,
    CONNECT,
    SEND_BITMASK,
    DATA_LOOP,
    QUIT,
    WAIT
} WorkerStatus;

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

    int bridge_connect();
    int inquiry();
    int connection();
    int sendBitmask();
    void dataLoop();
    unsigned char parseInquiryDatagram(inquiry_result_t ** result, Datagram * dg);

protected:
    void run();
    int exec();

public slots:
    void bluetoothDeviceChosen(int num);
    void bridgeInquiry();
    void bridgeConnect();

public:
    Worker(Serial * serial, void * vehicleParent, QWidget * parent);
    ~Worker();
    void on();
    void off();

signals:
    void flexConnectedSignal();
    void vehicleConnectedSignal();
    void inquiryResultsReadySignal();
    void bluetoothInquiryCompleted(inquiry_result_t * data, unsigned int num);
    void resultReady(unsigned char monitor, float data);
};

#endif // WORKER_H
