#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtDebug>

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>

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
#include <QVector>

#include "serialconfiguration.h"
#include "monitor.h"
#include "about.h"
#include "monitorselection.h"
#include "vehicle.h"
#include "statusbar.h"
#include "bluetoothdevices.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    SerialConfiguration * serialConfig;
    About * about;
    MonitorSelection * monitorSelection;
    BluetoothDevices * bluetoothDevices;

    QMdiArea mainWidget;
    QVector<void *> * subWindowVector;

    QToolBar * monitorToolBar;

    StatusBar * statusBar;

    QMenu * fileMenu;
    QMenu * devicesMenu;
    QMenu * questionsMenu;
    QMenu * settingsMenu;
    QMenu * viewMenu;

    QAction * exitAct;
    QAction * aboutAct;
    QAction * serialConfigAct;
    QAction * selectMonitorAct;
    QAction * serialConnectAct;
    QAction * serialDisconnectAct;
    QAction * alignMonitorAct;

    QAction * deviceConnectAct;
    QAction * deviceInquiryAct;

    Serial serial;
    Vehicle * vehicle;

    void createMenus();
    void createToolBars();
    void newMonitor(unsigned int identifier);

private slots:
    void exitSlot();
    void aboutSlot();
    void selectMonitorSlot();
    void serialConfigSlot();
    void serialConnectSlot();
    void serialDisconnectSlot();
    void alignMonitorSlot();
    void deviceConnectSlot();
    void deviceInquirySlot();

public slots:
    void updateMonitorsSlot();
    void flexOnlineSlot();
    void vehicleOnlineSlot();
    void bluetoothInquiryCompleted(inquiry_result_t * data, unsigned int num);
    void bluetoothDeviceChosen(int num);
    void vehicleDataReady(unsigned char monitor, float data);

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void monitorDead(Monitor * monitor);
};

#endif // MAINWINDOW_H
