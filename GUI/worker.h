#ifndef WORKER_H
#define WORKER_H

#define COMMAND 0
#define HELLO 0xA8
#define CONNECT_TO 0x11

#include <QThread>
#include <QSemaphore>

#include "bluetoothdevices.h"

#include "datagram.h"
#include "serial.h"

typedef enum WorkerStatus_ {
    PING,
    INQUIRY,
    CONNECT,
    SEND_BITMASK,
    DATA_LOOP,
    QUIT
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

    unsigned int btDeviceIndexChosen;

    int ping();
    int inquiry();
    int connection();
    void sendBitmask();
    void dataLoop();
    void sendDatagram(Datagram * datagram);
    void receiveDatagram(Datagram * datagram);

protected:
    void run();
    int exec();

public slots:
    void bluetoothDeviceChosen(unsigned int num);

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
