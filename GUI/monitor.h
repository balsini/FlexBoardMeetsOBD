#ifndef MONITOR_H
#define MONITOR_H

#define KDE_LIBS

#ifdef DEBUGGING
#include <QDebug>
#include <QScrollBar>
#endif

#ifdef KDE_LIBS
#include "ksignalplotter.h"
#else
#include "plot.h"
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

#ifdef KDE_LIBS
    KSignalPlotter * plot;
#else
    Plot * plot;
#endif

    float minAngle;
    float maxAngle;
    float minValue;
    float maxValue;

    float angle;
    float value;
    float minimum;
    float maximum;

    QColor color;

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
    QColor getColor();
    void setValue(float value);
};

#endif // MONITOR_H
