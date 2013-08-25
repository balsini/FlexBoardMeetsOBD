#include "worker.h"
#include "mainwindow.h"

Worker::Worker(Serial * serial, QWidget * parent)
{
    this->parent = parent;
    this->serial = serial;
    this->active = false;
    this->status = PING;
    sync = new QSemaphore(0);

    connect(this, SIGNAL(flexConnectedSignal()), (MainWindow *)parent, SLOT(flexOnlineSlot()));
    connect(this, SIGNAL(bluetoothInquiryCompleted(inquiry_result_t*,uint)), (MainWindow *)parent, SLOT(bluetoothInquiryCompleted(inquiry_result_t*,uint)));
}

Worker::~Worker()
{
    delete sync;
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

int Worker::ping()
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

    return 0;
}

int Worker::inquiry()
{
    inquiry_result_t btDev[2];

    // wait for inquiry (about 20 seconds)
    // FLEX: returns Bluetooth devices

    //receiveDatagram(&data);

    // This is a testing example
    strcpy(btDev[0].addr, "000A3A58F310");
    strcpy(btDev[0].name, "Elm327");
    strcpy(btDev[0].cod,  "12345");

    strcpy(btDev[1].addr, "0003C92DB48F");
    strcpy(btDev[1].name, "Nokia");
    strcpy(btDev[1].cod,  "56789");

    emit bluetoothInquiryCompleted(btDev, 2);

    sync->acquire();
    return 0;
}

int Worker::connection()
{
    // PC: connect to i-th device
    // FLEX: returns connection result

    qDebug() << "connecting to" << btDeviceIndexChosen;

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
        case PING:
            ping();
            status = INQUIRY;
            break;
        case INQUIRY:
            inquiry();
            status = CONNECT;
            break;
        case CONNECT:
            connection();
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

void Worker::bluetoothDeviceChosen(unsigned int num)
{
    btDeviceIndexChosen = num;
    sync->release();
}

