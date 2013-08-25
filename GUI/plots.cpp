#include "plots.h"

unsigned int PLOT_WINDOW_WIDTH = 800;
unsigned int PLOT_WINDOW_HEIGTH = 600;

Plots::Plots(QWidget * parent, Qt::WindowFlags f)
    : QWidget(parent,f)
{
    this->setWindowTitle(tr("Plots"));

    this->setMinimumHeight(PLOT_WINDOW_HEIGTH);
    this->setMinimumWidth(PLOT_WINDOW_WIDTH);

    layout = new QHBoxLayout(this);
    mainView = new QGraphicsView(this);
    mainScene = new QGraphicsScene(0, 0, PLOT_WINDOW_WIDTH, PLOT_WINDOW_HEIGTH, mainView);

    layout->addWidget(mainView);
    this->setLayout(layout);
}
