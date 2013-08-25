#ifndef WORKER_H
#define WORKER_H

#include <QThread>

#include "datagram.h"
#include "serial.h"

class Worker : public QObject
{
    Q_OBJECT

    QThread workerThread;

    Serial * serial;

    bool active;

public:
    Worker(Serial * serial);
    void on() {
        active = true;
    }
    void off() {
        active = false;
    }

public slots:
    void doWork() {
        Datagram data;
        while (active) {
            serial->readS(&data, sizeof(data));
            emit resultReady(data);
        }
    }

signals:
    void resultReady(Datagram data);
};

#endif // WORKER_H
