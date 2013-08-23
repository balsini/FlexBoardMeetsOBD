#include "monitor.h"

#define MONITOR_WIDTH 150
#define MONITOR_HEIGHT 150

Monitor::Monitor(const QString &title, QWidget * parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    this->setWindowTitle(title);
    this->setMaximumSize(MONITOR_WIDTH, MONITOR_HEIGHT);
    this->setMinimumSize(MONITOR_WIDTH, MONITOR_HEIGHT);
}
