/**
 * @file    plot.h
 * @author  Alessio Balsini <alessio.balsini@gmail.com>
 * @version 0
 *
 * @section DESCRIPTION
 *
 * Not working. Please, ignore this class.
 */

#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QBrush>
#include <QPen>
#include <QPolygon>
#include <QGraphicsPolygonItem>

class Plot : public QWidget
{
    Q_OBJECT

    QHBoxLayout * layout;
    QGraphicsView * mainView;
    QGraphicsScene * mainScene;
    QGraphicsPolygonItem * polygon;
    QPolygonF qp;

public:
    Plot(QWidget * parent = 0, Qt::WindowFlags f = 0);

public slots:
    void newData(float data);
};

#endif // PLOT_H
