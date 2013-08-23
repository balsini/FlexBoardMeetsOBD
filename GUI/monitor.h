#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>

class Monitor : public QWidget
{
    Q_OBJECT


public:
    Monitor(const QString & title, QWidget * parent = 0, Qt::WindowFlags f = 0);
};

#endif // MONITOR_H
