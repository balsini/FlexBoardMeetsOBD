#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtDebug>

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>

#include <QAction>
#include <QLayout>
#include <QLabel>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QSpacerItem>
#include <QDir>

#include "serialconfiguration.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    SerialConfiguration * serialConfig;

    QToolBar * monitorToolBar;
    QMenu * fileMenu;
    QMenu * questionsMenu;
    QMenu * settingsMenu;
    QAction * exitAct;
    QAction * aboutAct;
    QAction * serialConfigAct;
    QAction * newMonitorAct;
    QAction * editMonitorAct;
    QAction * deleteMonitorAct;

    void createMenus();
    void createToolBars();

private slots:
    void exitSlot();
    void aboutSlot();
    void newMonitorSlot();
    void serialConfigSlot();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
