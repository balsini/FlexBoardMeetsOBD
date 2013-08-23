#include "serial.h"

Serial::Serial()
{
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
