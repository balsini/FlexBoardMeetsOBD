#include "monitor.h"

#define MONITOR_WIDTH 220
#define MONITOR_HEIGHT 220

Monitor::Monitor(const QString &title, GaugeType type, QWidget * parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    this->type = type;

    this->setWindowTitle(title);
    this->setMaximumSize(MONITOR_WIDTH, MONITOR_HEIGHT);
    this->setMinimumSize(MONITOR_WIDTH, MONITOR_HEIGHT);

    mainView = new QGraphicsView(this);

    mainScene = new QGraphicsScene(0, 0, 300, 300, mainView);
    mainScene->setBackgroundBrush(Qt::gray);

    switch (type) {
    case FUEL:
        bg = mainScene->addPixmap(QPixmap(":/images/gauges/fuel/bg.png").scaledToHeight(MONITOR_HEIGHT-2));
        arrow = mainScene->addPixmap(QPixmap(":/images/gauges/fuel/arrow.png").scaledToHeight(MONITOR_HEIGHT-2));
        angle = minAngle = -31;
        maxAngle = 180 - minAngle;
        maxValue = 100;
        value = minValue = 0;
    default: break;
    }

    arrow->setTransformOriginPoint((MONITOR_HEIGHT-2)/2, (MONITOR_HEIGHT-2)/2);

    arrow->setRotation(angle);

    mainView->setScene(mainScene);
}

void Monitor::setValue(float value)
{
    this->value = value;
    angle = (maxAngle - minAngle) * value / maxValue + minAngle;

    arrow->setRotation(angle);
}
