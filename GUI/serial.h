#ifndef SERIAL_H
#define SERIAL_H

#include <QList>
#include <QDir>

class Serial
{
    QStringList devicesList;

public:
    Serial();
    QStringList getDevices()
    {
        QStringList ttyFilters;
        QDir devDir("/dev/");

        devicesList.clear();
        ttyFilters << "tty*";
        devicesList = devDir.entryList(ttyFilters, QDir::System, QDir::Time);

        QStringList returnList(devicesList);
        return returnList;
    }
};

#endif // SERIAL_H
