#ifndef VEHICLE_H
#define VEHICLE_H

#include "serial.h"

#define ELM327_BITMASK_SIZE 4

class Vehicle
{
    char bitmask[ELM327_BITMASK_SIZE];

    Serial * serial;

public:
    Vehicle(Serial * serial);
    void clearBitmask();
    void setBitmaskBit(unsigned int bitIdentifier);
    void getBitmaskBits(QList<unsigned int> * bitList);
};

#endif // VEHICLE_H
