#ifndef WORKER_H
#define WORKER_H

#define COMMAND 0
#define HELLO 0xA8
#define CONNECT_TO 0x11

#include <QThread>

#include "datagram.h"
#include "serial.h"

typedef enum WorkerStatus_ {
    INITIALIZATION,
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

    int initialization();
    void sendBitmask();
    void dataLoop();
    void sendDatagram(Datagram * datagram);
    void receiveDatagram(Datagram * datagram);

protected:
    void run();
    int exec();

public:
    Worker(Serial * serial, QWidget * parent);
    void on();
    void off();

signals:
    void resultReady(Datagram data);
    void flexConnectedSignal();
};

#endif // WORKER_H
