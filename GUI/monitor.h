#ifndef MONITOR_H
#define MONITOR_H

#include <QDockWidget>

class Monitor : public QDockWidget
{
public:
    Monitor(const QString & title, QWidget *parent = 0);
};

#endif // MONITOR_H
