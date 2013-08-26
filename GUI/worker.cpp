#include "worker.h"
#include "mainwindow.h"

Worker::Worker(Serial * serial, QWidget * parent)
{
    this->parent = parent;
    this->serial = serial;
    this->active = false;
    this->status = WAIT;
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

void Worker::sendDatagram(unsigned char type, unsigned char id)
{
    Datagram dg;
    constructDatagram(&dg, type, id);
    sendDatagram(&dg);
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
    Datagram dg;

    // PC: I'm alive!
    sendDatagram(REQUEST, HELLO);

    // FLEX: I'm alive!
    receiveDatagram(&dg);
    destructDatagramData(&dg);

    if (dg.type == RESPONSE && dg.id == HELLO) {
        // Flex is alive
        emit flexConnectedSignal();
        return 0;
    }

    // Flex is not alive
    return -1;
}

int Worker::inquiry()
{
    //Datagram dg;

    // This is a testing example
    inquiry_result_t btDev[2];
    strcpy(btDev[0].addr, "000A3A58F310");
    strcpy(btDev[0].name, "Elm327");
    strcpy(btDev[0].cod,  "12345");

    strcpy(btDev[1].addr, "0003C92DB48F");
    strcpy(btDev[1].name, "Nokia");
    strcpy(btDev[1].cod,  "56789");

    // wait for inquiry (about 20 seconds)
    // FLEX: returns Bluetooth devices

    //sendDatagram(REQUEST, INQUIRY);
    //receiveDatagram(&dg);

    emit bluetoothInquiryCompleted(btDev, 2);

    sync->acquire();

    if (btDeviceIndexChosen == -1)
        return -1;

    sendDatagram(RESPONSE, SUCCESS);

    return 0;
}

int Worker::connection()
{
    Datagram dg;
    unsigned char * btDev = new unsigned char[1];
    *btDev = (unsigned char)btDeviceIndexChosen;

    // PC: connect to i-th device

    constructDatagram(&dg, REQUEST, CONNECT_TO, 1, btDev);
    sendDatagram(&dg);
    destructDatagramData(&dg);

    // FLEX: returns connection result

    receiveDatagram(&dg);
    if (dg.type == RESPONSE && dg.id == SUCCESS) {
        // Flex is alive
        emit flexConnectedSignal();
        return 0;
    }

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
            if (ping() == 0)
                status = WAIT;
            break;
        case INQUIRY_REQ:
            inquiry();
            status = CONNECT;
            break;
        case CONNECT:
            connection();
            status = WAIT;
            break;
        case SEND_BITMASK:
            sendBitmask();
            status = WAIT;
            break;
        case DATA_LOOP:
            dataLoop();
            break;
        case WAIT:
            sync->acquire();
            break;
        case QUIT:
            return 0;
            break;
        default: break;
        }
    }
    return 0;
}

void Worker::bluetoothDeviceChosen(int num)
{
    btDeviceIndexChosen = num;
    sync->release();
}

void Worker::bridgeInquiry()
{
    status = INQUIRY_REQ;
    sync->release();
}

void Worker::bridgeConnect()
{
    status = PING;
    sync->release();
}

