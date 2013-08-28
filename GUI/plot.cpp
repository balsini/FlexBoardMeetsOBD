#include "plot.h"

unsigned int PLOT_WINDOW_WIDTH = 800;
unsigned int PLOT_WINDOW_HEIGTH = 200;

Plot::Plot(QWidget * parent, Qt::WindowFlags f)
    : QWidget(parent,f)
{
    QBrush penBrush(Qt::blue);
    QBrush plotBrush(Qt::gray);
    QPen   plotPen(penBrush,2,Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);

    QBrush bgBrush(Qt::lightGray, Qt::CrossPattern);
    this->setWindowTitle(tr("Plots"));

    this->setFixedSize(PLOT_WINDOW_WIDTH, PLOT_WINDOW_HEIGTH);

    layout = new QHBoxLayout(this);
    mainView = new QGraphicsView(this);
    mainScene = new QGraphicsScene(0,0,770, 160,mainView);
    mainView->setScene(mainScene);
    mainScene->setBackgroundBrush(bgBrush);
    layout->addWidget(mainView);
    this->setLayout(layout);

    polygon = mainScene->addPolygon(qp,plotPen,plotBrush);

    newData(0.5);
    newData(0.2);
    newData(0.8);
}

void Plot::newData(float data)
{
    QBrush penBrush(Qt::blue);
    QBrush plotBrush(Qt::gray);
    QPen   plotPen(penBrush,2,Qt::SolidLine,Qt::RoundCap, Qt::RoundJoin);
    float realData = 160 - data*160;

    polygon->moveBy(1,0);

    qp.clear();
    qp << QPointF(0, 0) << QPointF(0, realData) << QPointF(2, realData) << QPointF(2, 0);
    polygon = mainScene->addPolygon(qp,plotPen,plotBrush);
    polygon->setOpacity(0.6);

    this->update();
}
