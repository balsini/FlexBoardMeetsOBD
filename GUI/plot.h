#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QBrush>

class Plot : public QWidget
{
    Q_OBJECT

    QHBoxLayout * layout;
    QGraphicsView * mainView;
    QGraphicsScene * mainScene;

public:
    Plot(QWidget * parent = 0, Qt::WindowFlags f = 0);
};

#endif // PLOT_H
