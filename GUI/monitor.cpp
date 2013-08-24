#include "monitor.h"

unsigned int MONITOR_WIDTH = 300;
unsigned int MONITOR_HEIGHT = 200;

unsigned int GRAPHICS_WIDTH = MONITOR_WIDTH*3/5;
unsigned int GRAPHICS_HEIGHT = GRAPHICS_WIDTH;

Monitor::Monitor(const QString &title, GaugeType type, QWidget * parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    this->type = type;

    this->setWindowTitle(title);
    this->setMaximumSize(MONITOR_WIDTH, MONITOR_HEIGHT);
    this->setMinimumSize(MONITOR_WIDTH, MONITOR_HEIGHT);

    actualLcd.setSegmentStyle(QLCDNumber::Flat);
    maximumLcd.setSegmentStyle(QLCDNumber::Flat);
    minimumLcd.setSegmentStyle(QLCDNumber::Flat);

    mainView = new QGraphicsView(this);

    mainScene = new QGraphicsScene(0, 0, GRAPHICS_WIDTH, GRAPHICS_HEIGHT, mainView);
    mainScene->setBackgroundBrush(Qt::gray);

    switch (type) {
    case FUEL:
        bg = mainScene->addPixmap(QPixmap(":/images/gauges/fuel/bg.png").scaledToWidth(GRAPHICS_WIDTH));
        arrow = mainScene->addPixmap(QPixmap(":/images/gauges/fuel/arrow.png").scaledToWidth(GRAPHICS_WIDTH));
        minAngle = -31;
        maxAngle = 180 - minAngle;
        maxValue = 100;
        minValue = 0;
        break;
    case RPM:
        bg = mainScene->addPixmap(QPixmap(":/images/gauges/rpm/bg.png").scaledToWidth(GRAPHICS_WIDTH));
        arrow = mainScene->addPixmap(QPixmap(":/images/gauges/rpm/arrow.png").scaledToWidth(GRAPHICS_WIDTH));
        minAngle = -101;
        maxAngle = 145;
        maxValue = 17000;
        minValue = 0;
        break;
    default: break;
    }

    minimum = maxValue;
    maximum = minValue;

    arrow->setTransformOriginPoint(GRAPHICS_WIDTH/2, GRAPHICS_HEIGHT/2);

    arrow->setRotation(angle);

    mainView->setScene(mainScene);

    layout = new QHBoxLayout(this);
    spacer = new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::MinimumExpanding);
    layout->addWidget(mainView);

    actualValueLabel.setText("Actual Value");
    vLayout.addWidget(&actualValueLabel);
    vLayout.addWidget(&actualLcd);

    maximumValueLabel.setText("Maximum Value");
    vLayout.addWidget(&maximumValueLabel);
    vLayout.addWidget(&maximumLcd);

    minimumValueLabel.setText("Minimum Value");
    vLayout.addWidget(&minimumValueLabel);
    vLayout.addWidget(&minimumLcd);

    vLayout.addSpacerItem(spacer);

    layout->addLayout(&vLayout);
}

void Monitor::setValue(float value)
{
    this->value = value;

    angle = minAngle + value / maxValue * (maxAngle - minAngle);

    actualLcd.display(value);

    if (value > maximum)
        maximum = value;
    if (value < minimum)
        minimum = value;

    minimumLcd.display(minimum);
    maximumLcd.display(maximum);
    arrow->setRotation(angle);
}
