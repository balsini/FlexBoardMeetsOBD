#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include <QSemaphore>

#include "bluetoothdevices.h"

#include "datagram.h"
#include "serial.h"

typedef enum WorkerStatus_ {
    PING,
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

    bool active;
    WorkerStatus status;
    QSemaphore * sync;

    int btDeviceIndexChosen;

    int ping();
    int inquiry();
    int connection();
    void sendBitmask();
    void dataLoop();
    void sendDatagram(Datagram * datagram);
    void sendDatagram(unsigned char type, unsigned char id);
    void receiveDatagram(Datagram * datagram);

protected:
    void run();
    int exec();

public slots:
    void bluetoothDeviceChosen(int num);
    void bridgeInquiry();
    void bridgeConnect();

public:
    Worker(Serial * serial, QWidget * parent);
    ~Worker();
    void on();
    void off();

signals:
    void resultReady(Datagram data);
    void flexConnectedSignal();
    void inquiryResultsReadySignal();
    void bluetoothInquiryCompleted(inquiry_result_t * data, unsigned int num);
};

#endif // WORKER_H
