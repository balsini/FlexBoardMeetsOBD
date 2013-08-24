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
#include "monitorselection.h"
#include "vehicle.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    SerialConfiguration * serialConfig;
    About * about;
    MonitorSelection * monitorSelection;

    QMdiArea * mainWidget;

    QToolBar * monitorToolBar;

    QMenu * fileMenu;
    QMenu * questionsMenu;
    QMenu * settingsMenu;
    QMenu * viewMenu;

    QAction * exitAct;
    QAction * aboutAct;
    QAction * serialConfigAct;
    QAction * selectMonitorAct;
    QAction * editMonitorAct;
    QAction * serialConnectAct;
    QAction * alignMonitorAct;

    Serial serial;
    Vehicle * vehicle;

    void createMenus();
    void createToolBars();
    void newMonitor(unsigned int identifier);

private slots:
    void exitSlot();
    void aboutSlot();
    void selectMonitorSlot();
    void editMonitorSlot() {}
    void serialConfigSlot();
    void serialConnectSlot();
    void alignMonitorSlot();

public slots:
    void updateMonitorsSlot();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
