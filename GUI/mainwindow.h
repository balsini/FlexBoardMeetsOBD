#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtDebug>

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
//#include <QDockWidget>

#include <QMdiArea>
#include <QMdiSubWindow>

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
#include "monitor.h"
#include "about.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    SerialConfiguration * serialConfig;
    About * about;

    QMdiArea * mainWidget;

    QToolBar * monitorToolBar;

    QMenu * fileMenu;
    QMenu * questionsMenu;
    QMenu * settingsMenu;
    QMenu * viewMenu;

    QAction * exitAct;
    QAction * aboutAct;
    QAction * serialConfigAct;
    QAction * newMonitorAct;
    QAction * editMonitorAct;
    QAction * serialConnectAct;
    QAction * alignMonitorAct;

    Serial serial;

    void createMenus();
    void createToolBars();

private slots:
    void exitSlot();
    void aboutSlot();
    void newMonitorSlot();
    void serialConfigSlot();
    void serialConnectSlot();
    void alignMonitorSlot();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
