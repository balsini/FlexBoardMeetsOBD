#include "monitor.h"
#include "mainwindow.h"

#include <float.h>

unsigned int MONITOR_WIDTH = 350;
unsigned int MONITOR_HEIGHT = 250;

unsigned int GRAPHICS_WIDTH = MONITOR_WIDTH*3/5;
unsigned int GRAPHICS_HEIGHT = GRAPHICS_WIDTH;

Monitor::Monitor(const QString &title, GaugeType type, QWidget * parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    this->type = type;
    this->parent = parent;

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
        maxAngle = 180 + 31;
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
    case SPEED:
        bg = mainScene->addPixmap(QPixmap(":/images/gauges/speed/bg.png").scaledToWidth(GRAPHICS_WIDTH));
        arrow = mainScene->addPixmap(QPixmap(":/images/gauges/speed/arrow.png").scaledToWidth(GRAPHICS_WIDTH));
        minAngle = -45;
        maxAngle = 180+45;
        maxValue = 160;
        minValue = 0;
        break;
    case WATER_TEMP:
        bg = mainScene->addPixmap(QPixmap(":/images/gauges/water_temp/bg.png").scaledToWidth(GRAPHICS_WIDTH));
        arrow = mainScene->addPixmap(QPixmap(":/images/gauges/water_temp/arrow.png").scaledToWidth(GRAPHICS_WIDTH));
        minAngle = -90;
        maxAngle = 180;
        maxValue = 140;
        minValue = 40;
        break;
    default: break;
    }

    minimum = FLT_MAX-1.0;
    maximum = -minimum;

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

    plotButton.setText("&Plot");

#ifdef KDE_LIBS
    plot = new KSignalPlotter(parent, Qt::Window);
    plot->addBeam(Qt::blue);
#else
    plot = new Plot(this, Qt::Window);
#endif

    plot->setWindowTitle(this->windowTitle());
    connect(&plotButton, SIGNAL(released()), this, SLOT(plotSlot()));


#ifdef DEBUGGING
    scrollBar.setOrientation(Qt::Horizontal);
    vLayout.addWidget(&scrollBar);
    connect(&scrollBar, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
#endif

    vLayout.addSpacerItem(spacer);

    vLayout.addWidget(&plotButton);

    layout->addLayout(&vLayout);
}

Monitor::~Monitor()
{
    ((MainWindow *)parent)->monitorDead(this->type);
}

void Monitor::setValue(float value)
{
    static float tmp;
    static float norm;

    this->value = value;

    if (value > maxValue)
        tmp = maxValue;
    else if (value < minValue)
        tmp = minValue;
    else
        tmp = value;

    norm = (tmp - minValue) / (maxValue - minValue);

    angle = minAngle + norm * (maxAngle - minAngle);

    if (value > maximum)
        maximum = value;
    else if (value < minimum)
        minimum = value;

    actualLcd.display(value);
    minimumLcd.display(minimum);
    maximumLcd.display(maximum);
    arrow->setRotation(angle);

#ifdef KDE_LIBS
    plot->addSample(QList<double>() << value);
#else
    emit plot->newData(norm);
#endif
}

void Monitor::plotSlot()
{
    plot->show();
}

#ifdef DEBUGGING
void Monitor::valueChanged(int i)
{
    double fi = i / 100.0;
    double value;
    qDebug() << "i:" << fi;
    value = minValue + (fi * (maxValue - minValue));
    qDebug() << "value:" << value;
    setValue(value);
}
#endif
