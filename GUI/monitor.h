#ifndef MONITOR_H
#define MONITOR_H

#ifdef DEBUGGING
#include <QDebug>
#include <QScrollBar>
#endif

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QLCDNumber>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QPushButton>

#include "plot.h"

typedef enum GaugeType_ {
    FUEL, SPEED, RPM, WATER_TEMP
} GaugeType;

class Monitor : public QWidget
{
    Q_OBJECT

    GaugeType type;

    void * parent;

    QHBoxLayout * layout;
    QGraphicsView * mainView;
    QGraphicsScene * mainScene;
    QGraphicsPixmapItem * bg;
    QGraphicsPixmapItem * arrow;

    QLCDNumber actualLcd;
    QLCDNumber maximumLcd;
    QLCDNumber minimumLcd;
    QLabel actualValueLabel;
    QLabel maximumValueLabel;
    QLabel minimumValueLabel;
    QSpacerItem * spacer;
    QVBoxLayout vLayout;

    QPushButton plotButton;

    Plot * plot;

    float minAngle;
    float maxAngle;
    float minValue;
    float maxValue;

    float angle;
    float value;
    float minimum;
    float maximum;

#ifdef DEBUGGING
    QScrollBar scrollBar;
#endif

private slots:
    void plotSlot();

#ifdef DEBUGGING
    void valueChanged(int i);
#endif


public:
    Monitor(const QString & title, GaugeType type, QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~Monitor();
    void setValue(float value);
};

#endif // MONITOR_H
