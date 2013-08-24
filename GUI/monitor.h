#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

typedef enum GaugeType_ {
    FUEL, SPEED, RPM
} GaugeType;

class Monitor : public QWidget
{
    Q_OBJECT

    GaugeType type;

    QGraphicsView * mainView;
    QGraphicsScene * mainScene;
    QGraphicsPixmapItem * bg;
    QGraphicsPixmapItem * arrow;

    float minAngle;
    float maxAngle;
    float minValue;
    float maxValue;

    float angle;
    float value;
public:
    Monitor(const QString & title, GaugeType type, QWidget * parent = 0, Qt::WindowFlags f = 0);
    void setValue(float value);
};

#endif // MONITOR_H
