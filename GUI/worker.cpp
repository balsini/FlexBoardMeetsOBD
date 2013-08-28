#include "worker.h"
#include "vehicle.h"
#include "mainwindow.h"

Worker::Worker(Serial * serial, void * vehicle, QWidget * parent)
{
    this->parent = parent;
    this->serial = serial;
    this->active = false;
    this->status = WAIT;
    sync = new QSemaphore(0);

    this->vehicle = vehicle;

    connect(this, SIGNAL(flexConnectedSignal()), (MainWindow *)parent, SLOT(flexOnlineSlot()));
    connect(this, SIGNAL(vehicleConnectedSignal()), (MainWindow *)parent, SLOT(vehicleOnlineSlot()));
    connect(this, SIGNAL(bluetoothInquiryCompleted(inquiry_result_t*,uint)), (MainWindow *)parent, SLOT(bluetoothInquiryCompleted(inquiry_result_t*,uint)));
    connect(this, SIGNAL(resultReady(unsigned char,float)), (MainWindow *)parent, SLOT(vehicleDataReady(unsigned char,float)));
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

unsigned char Worker::parseInquiryDatagram(inquiry_result_t ** result, Datagram * dg)
{
    int i,j;
    unsigned char num;
    unsigned char * iterator = dg->data;
    inquiry_result_t * res;

    num = *iterator;
    iterator++;
    res = new inquiry_result_t[num];

    for (j=0; j<num; j++) {
        for (i=0; *iterator!=','; i++) {
            res[j].name[i] = *iterator;
            iterator++;
        }
        iterator++;
        for (i=0; *iterator!=','; i++) {
            res[j].addr[i] = *iterator;
            iterator++;
        }
        iterator++;
        for (i=0; *iterator!='.'; i++) {
            res[j].cod[i] = *iterator;
            iterator++;
        }
        iterator++;
    }
    *result = res;
    return num;
}

int Worker::bridge_connect()
{
    Datagram dg;
    dg.data = 0;

    // PC: I'm alive!
    sendDatagram(serial, (unsigned char)REQUEST, (unsigned char)HELLO);

    // FLEX: I'm alive!
    if (receiveDatagramTimeout(serial, &dg) == -1) {
        // Flex is not alive
        serial->flush();
        return -1;
    } else if (dg.type == RESPONSE && dg.id == HELLO) {
        // Flex is alive
        emit flexConnectedSignal();
        return 0;
    } else {
        // Flex is not alive
        serial->flush();
        return -1;
    }
}

int Worker::inquiry()
{
    Datagram dg;
    inquiry_result_t * btDev;
    unsigned char btDevNum;

    // wait for inquiry (about 20 seconds)
    // FLEX: returns Bluetooth devices

    sendDatagram(serial, REQUEST, INQUIRY);
    receiveDatagram(serial, &dg);
    if (!(dg.type == RESPONSE && dg.id == INQUIRY))
        return -1;

    btDevNum = parseInquiryDatagram(&btDev, &dg);

    emit bluetoothInquiryCompleted(btDev, btDevNum);

    sync->acquire();

    if (btDeviceIndexChosen == -1)
        return -1;

    sendDatagram(serial, RESPONSE, OK);

    return 0;
}

int Worker::connection()
{
    Datagram dg;
    unsigned char * btDev = new unsigned char;
    *btDev = (unsigned char)btDeviceIndexChosen;

    // PC: connect to i-th device

    constructDatagram(&dg, REQUEST, CONNECT_TO, 1, btDev);
    sendDatagram(serial, &dg);
    destructDatagramData(&dg);

    // FLEX: returns connection result

    receiveDatagram(serial, &dg);
    if (dg.type == RESPONSE && dg.id == SUCCESS) {
        // Flex is alive
        emit vehicleConnectedSignal();
        return 0;
    }
    return -1;
}

int Worker::sendBitmask()
{
    Datagram dg;
    unsigned char * bitmask;

    // FLEX: requests the bitmask

    receiveDatagram(serial, &dg);

    if (dg.type != REQUEST || dg.id != GET_BITMASK) {
        qDebug() << "Expected bitmap request!";
        return -1;
    }

    // PC: sends the bitmask

    bitmask = new unsigned char[((Vehicle *)vehicle)->getBitmaskSize()];
    ((Vehicle *)vehicle)->getBitmask(bitmask);
    constructDatagram(&dg,
                      RESPONSE,
                      GET_BITMASK,
                      ((Vehicle *)vehicle)->getBitmaskSize(),
                      bitmask);

    sendDatagram(serial, &dg);
    destructDatagramData(&dg);

    // switch to data request loop

    return 0;
}


void Worker::dataLoop()
{
    Datagram dg;
    unsigned char monitor;
    float data;

    if (receiveDatagramTimeout(serial, &dg) != -1) {

        monitor = dg.id;
        data = translateDatagramData(&dg);

        emit resultReady(monitor, data);
    }
}

void Worker::kill()
{
    sendDatagram(serial, REQUEST, STOP);
}

void Worker::run()
{
    exec();
}

int Worker::exec()
{
    for (;;) {
        switch (status) {
        case BRIDGE_CONNECT:
            bridge_connect();
            status = WAIT;
            break;
        case INQUIRY_REQ:
            if (inquiry() == 0)
                status = CONNECT;
            else
                status = WAIT;
            break;
        case CONNECT:
            if (connection() == 0)
                status = SEND_BITMASK;
            else
                status = WAIT;
            break;
        case SEND_BITMASK:
            if (sendBitmask() == 0)
                status = DATA_LOOP;
            else
                status = WAIT;
            break;
        case DATA_LOOP:
            dataLoop();
            break;
        case KILL:
            kill();
            status = QUIT;
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
    status = BRIDGE_CONNECT;
    sync->release();
}

void Worker::bitmaskUpdated()
{
    if (status == DATA_LOOP)
        status = SEND_BITMASK;
}

void Worker::killRequest()
{
    if (status == DATA_LOOP)
        status = KILL;
}
