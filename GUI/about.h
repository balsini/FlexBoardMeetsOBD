#ifndef ABOUT_H
#define ABOUT_H

#include <QHBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>

#define ABOUT_AUTHORS_NUM 2

class About : public QWidget
{
    Q_OBJECT

    QHBoxLayout * aboutLayout;
    QVBoxLayout * aboutAuthorsLayout;
    QVBoxLayout * aboutToolsLayout;
    QLabel * aboutAuthorsTitle;
    QLabel * aboutAuthors[ABOUT_AUTHORS_NUM];
    QLabel * aboutQt;
    QLabel * aboutDigia;

public:
    About(QWidget *parent = 0, Qt::WindowFlags f = 0);
};

#endif // ABOUT_H
