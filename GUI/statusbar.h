#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QStatusBar>
#include <QLabel>

class StatusBar : public QStatusBar
{
    Q_OBJECT

    QLabel serialStatusText;
    QLabel serialStatusImg;
    QLabel flexStatusText;
    QLabel flexStatusImg;
    QLabel vehicleStatusText;
    QLabel vehicleStatusImg;

public slots:
    void serialConnectionEstabilished();
    void serialConnectionLost();
    void flexConnectionEstabilished();
    void flexConnectionLost();
    void vehicleConnectionEstabilished();
    void vehicleConnectionLost();

public:
    StatusBar(QWidget * parent = 0);
};

#endif // STATUSBAR_H
