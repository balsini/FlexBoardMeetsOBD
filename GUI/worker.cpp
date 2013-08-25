#include "worker.h"

Worker::Worker(Serial * serial)
{
    this->serial = serial;
    this->active = false;
}
