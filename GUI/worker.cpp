#include "worker.h"
#include "mainwindow.h"

Worker::Worker(Serial * serial, QWidget * parent)
{
    this->parent = parent;
    this->serial = serial;
    this->active = false;
    this->status = INITIALIZATION;

    connect(this, SIGNAL(flexConnectedSignal()), (MainWindow *)parent, SLOT(flexOnlineSlot()));
}

void Worker::on()
{
    active = true;
}

void Worker::off()
{
    active = false;
}

void Worker::sendDatagram(Datagram * datagram)
{
    serial->writeC(datagram->type);
    serial->writeC(datagram->id);
    serial->writeC(datagram->size);
    if (datagram->size > 0)
        serial->writeS(datagram->data, datagram->size);
}

void Worker::receiveDatagram(Datagram * datagram)
{
    datagram->type = serial->readC();
    datagram->id = serial->readC();
    datagram->size = serial->readC();
    if (datagram->size > 0) {
        datagram->data = new unsigned char[datagram->size];
        serial->readS(datagram->data, datagram->size);
    } else {
        datagram->data = 0;
    }
}

int Worker::initialization()
{
    Datagram data;

    // PC: I'm alive!
    data.type = COMMAND;
    data.id = HELLO;
    data.size = 0;

    sendDatagram(&data);

    // FLEX: I'm alive!
    receiveDatagram(&data);
    if (data.size != 0)
        delete[] data.data;

    if (data.type != COMMAND || data.id != HELLO) // Flex is not alive
        return -1;

    // Flex is alive
    emit flexConnectedSignal();

    // wait for inquiry (about 20 seconds)
    receiveDatagram(&data);

    /*
     * Do some stuff with it
     */

    // FLEX: returns Bluetooth devices
    // PC: connect to i-th device
    // FLEX: returns connection result

    return 0;
}

void Worker::sendBitmask()
{
    // FLEX: requests the bitmask
    // PC: sends the bitmask

    // switch to data request loop
}


void Worker::dataLoop()
{
    // do {
    //   FLEX: fa il ciclo di richieste
    //   FLEX: c’è = readUART1(&qualcosa)
    // } while (!c’è || (c’è &&qualcosa == continua));
    // if (qualcosa == smetti)
    //   FSM_TRAN_(DEAD)
    // if (qualcosa == cambia_bitmask)
    //   FSM_TRAN_(MANDA_BITMASK)

    /*
     *Datagram data;
     *while (active) {
     *  serial->readS(&data, sizeof(data));
     *  emit resultReady(data);
     *}
     */
}

void Worker::run()
{
    exec();
}

int Worker::exec()
{
    for (;;) {
        switch (status) {
        case INITIALIZATION:
            initialization();
            status = SEND_BITMASK;
            break;
        case SEND_BITMASK:
            sendBitmask();
            status = DATA_LOOP;
            break;
        case DATA_LOOP:
            dataLoop();
            break;
        default:
            return 0;
            break;
        }
    }
}
