#ifndef PLOTS_H
#define PLOTS_H

#include <QWidget>
#include <QGraphicsView>
#include <QHBoxLayout>

class Plots : public QWidget
{
    Q_OBJECT

    QHBoxLayout * layout;
    QGraphicsView * mainView;
    QGraphicsScene * mainScene;

public:
    Plots(QWidget * parent = 0, Qt::WindowFlags f = 0);
};

#endif // PLOTS_H
