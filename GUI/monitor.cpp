#include "monitor.h"

#define MONITOR_WIDTH 150
#define MONITOR_HEIGHT 150

Monitor::Monitor(const QString &title, QWidget *parent)
    : QDockWidget(title, parent)
{
    this->setMinimumWidth(MONITOR_HEIGHT);
    this->setMaximumWidth(MONITOR_HEIGHT);
    this->setMinimumHeight(MONITOR_HEIGHT);
    this->setMaximumHeight(MONITOR_HEIGHT);
}
