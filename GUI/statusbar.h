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

public slots:
    void serialConnectionEstabilished();
    void serialConnectionLost();
    void flexConnectionEstabilished();
    void flexConnectionLost();

public:
    StatusBar(QWidget * parent = 0);
};

#endif // STATUSBAR_H
