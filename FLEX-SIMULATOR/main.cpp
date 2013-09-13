#include <QDebug>

#include "serial.h"
#include "datagram.h"

#include <string>
#include <unistd.h>
#include <math.h>

Serial serial;

unsigned char * bitmask;
int bitmaskSize;
float t;


void receiveBitmask()
{
    Datagram dg;

    qDebug() << "Requesting bitmask";
    sendDatagram(&serial, REQUEST, GET_BITMASK);
    qDebug() << "DONE";

    qDebug() << "Receiving bitmask";
    receiveDatagram(&serial, &dg);
    qDebug() << "DONE";

    qDebug() << "Bitmask:";
    bitmaskSize = dg.size;
    bitmask = new unsigned char[dg.size];
    for (unsigned int i=0; i<dg.size; i++) {
        bitmask[i] = dg.data[i];
        qDebug() << "\t" << bitmask[i];
    }

    destructDatagramData(&dg);
}

void loop()
{
    for (;;) {
        receiveBitmask();
        unsigned char cmd;
        bool goOn = true;
        do {
            //FLEX: request loop

            for (int i=0; i<bitmaskSize*8; i++) {
                qDebug() << "Dentro: "<< i;
                if ((bitmask[i/8] & (0x1 << (i % 8))) != 0) {
                    Datagram dg;
                    unsigned char d;

                    d = (1.0 + sin(t))/2.0 * 125.0;
                    t += 0.01;

                    qDebug() << "Monitor: " << i;
                    qDebug() << "Data:    " << i;
                    qDebug() << " ";
                    constructDatagram(&dg, DATA, i, 1, &d);
                    sendDatagram(&serial,&dg);
                    usleep(10000);
                }
            }

            //FLEX: c’è = readUART1(&something)
        } while (goOn);
        cmd = -1;
        if (cmd == STOP) {
            qDebug() << "Stop request";
            exit(0);
        } else if (cmd != GET_BITMASK) {
            qDebug() << "Expected bitmask request!";
            exit(1);
        }
    }
}

void ping()
{
    Datagram dg;

    receiveDatagram(&serial, &dg);

    if (!(dg.type == REQUEST && dg.id == HELLO)) {
        qDebug() << "\tPing error!";
        exit(1);
    }

    qDebug() << "\tFound PC! Replying";
    sendDatagram(&serial, RESPONSE, HELLO);
}

void inquiry()
{
    Datagram dg;
    // This is a testing example
    /*
    inquiry_result_t btDev[2];
    strcpy(btDev[0].addr, "000A3A58F310");
    strcpy(btDev[0].name, "Elm327");
    strcpy(btDev[0].cod,  "12345");

    strcpy(btDev[1].addr, "0003C92DB48F");
    strcpy(btDev[1].name, "Nokia");
    strcpy(btDev[1].cod,  "56789");
    */

    QString inquiryResult;
    inquiryResult.clear();
    inquiryResult.append(3);
    inquiryResult.append("Nokia,0003C92DB48F,66894.Elm327,000A3A58F310,41847.HTC Vision,0005DY51K8X3,98017.");

    qDebug() << "\tPrinting: \"" <<inquiryResult.toStdString().c_str() << "\"";

    constructDatagram(&dg, RESPONSE, INQUIRY, strlen(inquiryResult.toStdString().c_str()), (unsigned char *)inquiryResult.toStdString().c_str());
    sendDatagram(&serial, &dg);
}

int main()
{
    Datagram dg;
    Serial_t serialConfig;

    t=0;

    serialConfig.baud_rate = 9600;
    serialConfig.bits = 8;
    serialConfig.parity = 0;
    serialConfig.stop_bits = 1;
    serialConfig.device = "ttyUSB0";

    serial.setConfig(serialConfig);
    if (serial.connect() == -1) {
        qDebug() << "Serial connection error!";
        exit(1);
    }
    qDebug() << "Serial connected!";

    qDebug() << "Ping...";
    ping();
    qDebug() << "DONE";

    bool remain = true;
    while (remain) {
        qDebug() << "Inquiry or ok?";
        receiveDatagram(&serial, &dg);
        switch (dg.type) {
        case REQUEST:
            switch (dg.id) {
            case INQUIRY:
                qDebug() << "Inquiry Request...";
                inquiry();
                qDebug() << "DONE";
                break;
            default:
                qDebug() << "Unknown";
                break;
            }
            break;
        case RESPONSE:
            switch (dg.id) {
            case OK:
                qDebug() << "OK";
                remain = false;
                break;
            default:
                qDebug() << "Unknown";
                break;
            }
            break;
        default:
            qDebug() << "Unknown";
            break;
        }
    }

    receiveDatagram(&serial, &dg);
    if (dg.type != REQUEST || dg.id != CONNECT_TO) {
        qDebug() << "Expected connection!";
        qDebug() << "QUIT";
        exit(1);
    }

    qDebug() << "Connecting to: " << *dg.data;
    sendDatagram(&serial, RESPONSE, SUCCESS);
    qDebug() << "DONE";

    loop();
    return 0;
}
