/**
 * @file    about.h
 * @author  Alessio Balsini <alessio.balsini@gmail.com>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The About window file.
 */

#ifndef ABOUT_H
#define ABOUT_H

#include <QHBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QDesktopWidget>

/**
 * Number of authors.
 */

#define ABOUT_AUTHORS_NUM 1

/**
 * The About class, which creates the About window.
 */

class About : public QWidget
{
    Q_OBJECT

    QHBoxLayout * aboutLayout;
    QVBoxLayout * aboutAuthorsLayout;
    QVBoxLayout * aboutToolsLayout;
    QLabel * aboutAuthorsTitle;
    QLabel * aboutAuthors[ABOUT_AUTHORS_NUM];
    QLabel * aboutUniPi;
    QLabel * aboutSSSUP;
    QLabel * aboutQt;
    QLabel * aboutDigia;

public:

    /**
     * Class constructor, which generates the window.
     * @param parent The class's parent widget.
     * @param f Window flags.
     */

    About(QWidget *parent = 0, Qt::WindowFlags f = 0);
};

#endif // ABOUT_H
