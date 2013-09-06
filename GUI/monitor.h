/**
 * @file    monitor.h
 * @author  Alessio Balsini <alessio.balsini@gmail.com>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The gauge monitor, which shows the gauge, actual,
 * maximum and minimum reached data and history plot.
 */

#ifndef MONITOR_H
#define MONITOR_H

/**
 * With this define, the KDE's ksignalplotter is
 * used for plotting gauge data.
 */

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

/**
 * Gauge type enumerator, for distinguishing
 * between classes of gauges.
 */

typedef enum GaugeType_ {
    FUEL, SPEED, RPM, WATER_TEMP
} GaugeType;

/**
 * The Monitor class, which creates a window
 * that contains the gauge, actual, maximum and
 * minimum data and an history plot.
 */

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

    /**
     * Shows the plot.
     */

    void plotSlot();

#ifdef DEBUGGING
    void valueChanged(int i);
#endif

public:
    /**
     * Constructs the monitor.
     * @param title The name of the monitor.
     * @param type The monitor class (i.e. SPEED or RPM).
     * @param parent The parent widget.
     * @param f The window flags.
     */

    Monitor(const QString & title, GaugeType type, QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~Monitor();

    /**
     * Returns the plot's color.
     * @return The plot's color.
     */

    QColor getColor();

    /**
     * Adds a new value to the gauge.
     * @param value The new value to be added.
     */

    void setValue(float value);
};

#endif // MONITOR_H
