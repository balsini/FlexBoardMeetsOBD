#include "serial.h"


Serial::Serial()
{
    serialConfig.device = "ttyUSB0";
    serialConfig.baud_rate = 9600;
    serialConfig.parity = 0;
    serialConfig.bits = 8;
    serialConfig.stop_bits = 1;

    // select timeout
    tv.tv_sec = 1;
    tv.tv_usec= 0;

    tty_fd = -1;
}

Serial::~Serial()
{
    if (tty_fd != -1)
        close(tty_fd);
}

QStringList Serial::getDevices()
{
    QStringList ttyFilters;
    QDir devDir("/dev/");

    devicesList.clear();
    ttyFilters << "tty*";
    devicesList = devDir.entryList(ttyFilters, QDir::System, QDir::Time);

    QStringList returnList(devicesList);
    return returnList;
}

void Serial::setConfig(Serial_t config)
{
    serialConfig.device = config.device;
    serialConfig.baud_rate = config.baud_rate;
    serialConfig.parity = config.parity;
    serialConfig.bits = config.bits;
    serialConfig.stop_bits = config.stop_bits;
}


void Serial::disconnect()
{
    if (tty_fd != -1)
        close(tty_fd);
}

int Serial::connect()
{
    std::string device;
    device = "/dev/" + serialConfig.device;

    memset(&attribs, 0, sizeof(attribs));

    // Baud Rate

    switch (serialConfig.baud_rate) {
    case 300:
        cfsetispeed(&attribs, B300);
        cfsetospeed(&attribs, B300);
        break;
    case 600:
        cfsetispeed(&attribs, B600);
        cfsetospeed(&attribs, B600);
        break;
    case 1200:
        cfsetispeed(&attribs, B1200);
        cfsetospeed(&attribs, B1200);
        break;
    case 2400:
        cfsetispeed(&attribs, B2400);
        cfsetospeed(&attribs, B2400);
        break;
    case 4800:
        cfsetispeed(&attribs, B4800);
        cfsetospeed(&attribs, B4800);
        break;
    case 9600:
        cfsetispeed(&attribs, B9600);
        cfsetospeed(&attribs, B9600);
        break;
    case 19200:
        cfsetispeed(&attribs, B19200);
        cfsetospeed(&attribs, B19200);
        break;
    case 38400:
        cfsetispeed(&attribs, B38400);
        cfsetospeed(&attribs, B38400);
        break;
    case 57600:
        cfsetispeed(&attribs, B57600);
        cfsetospeed(&attribs, B57600);
        break;
    case 115200:
        cfsetispeed(&attribs, B115200);
        cfsetospeed(&attribs, B115200);
        break;
    default: break;
    }

    // Parity

    switch (serialConfig.parity) {
    case 1:
        attribs.c_iflag |= PARODD;
        break;
    case 2:
        attribs.c_iflag |= PARENB;
        break;
    default: break;
    }

    // Bits

    switch (serialConfig.bits) {
    case 5:
        attribs.c_cflag |= CS5;
        break;
    case 6:
        attribs.c_cflag |= CS6;
        break;
    case 7:
        attribs.c_cflag |= CS7;
        break;
    case 8:
        attribs.c_cflag |= CS8;
        break;
    default: break;
    }

    // Bit Stops

    switch (serialConfig.stop_bits) {
    case 2:
        attribs.c_cflag |= CSTOPB;
    default: break;
    }

    //attribs.c_lflag |= ICANON;
    attribs.c_cc[VMIN]  = 1;    // read does block
    attribs.c_cc[VTIME] = 8;    // 0 seconds read timeout

    //attribs.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    if (tty_fd != -1)
        close(tty_fd);


    tty_fd = open(device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY | O_SYNC);

    tcsetattr(tty_fd, TCSANOW, &attribs);
    tcflush(tty_fd, TCIFLUSH);

    FD_ZERO(&select_set);
    FD_SET(tty_fd, &select_set);

    return tty_fd;
}

int Serial::writeS(unsigned char * str, unsigned int len)
{
    return write(tty_fd, str, len);
}

int Serial::writeC(unsigned char c)
{
    return write(tty_fd, &c, 1);
}

int Serial::readS(void * buffer, unsigned int nbytes)
{
    for (unsigned int i=0; i<nbytes; i++)
        *(((unsigned char *)buffer)+i) = readC();
    return nbytes;
}

int Serial::readSTimeout(void * buffer, unsigned int nbytes)
{
    int res = readCTimeout((unsigned char *)buffer);
    if (res == 0) {
        for (unsigned int i=1; i<nbytes; i++)
            *(((unsigned char *)buffer)+i) = readC();
        return 0;
    }
    return -1;
}

unsigned char Serial::readC()
{
    static char c;
    select(tty_fd+1, &select_set, NULL, NULL, NULL);
    FD_SET(tty_fd, &select_set);
    read(tty_fd, &c, 1);
    return c;
}

int Serial::readCTimeout(unsigned char * result)
{
    struct timeval tv_temp;

    tv_temp.tv_sec = tv.tv_sec;
    tv_temp.tv_usec = tv.tv_usec;

    if (0 == select(tty_fd+1, &select_set, NULL, NULL, &tv_temp)) {
        FD_SET(tty_fd, &select_set);
        return -1;
    }

    FD_SET(tty_fd, &select_set);
    read(tty_fd, result, 1);
    return 0;
}
