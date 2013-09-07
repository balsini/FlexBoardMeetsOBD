/**
 * @file    mainwindow.h
 * @author  Alessio Balsini <alessio.balsini@gmail.com>
 * @version 1.0
 *
 * @section DESCRIPTION
 *
 * The main window of the GUI.
 */

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

/**
 * The MainWindow class, which creates the main window,
 * containing all the user needs.
 */

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

    /**
     * Creates the Menus of the window.
     */

    void createMenus();

    /**
     * Creates the ToolBars of the window.
     */

    void createToolBars();

    /**
     * Adds a new gauge monitor to the window.
     * @param identifier The monitor identifier.
     */

    void newMonitor(int identifier);

private slots:

    /**
     * Program kill request.
     */

    void exitSlot();

    /**
     * Show the About window request.
     */

    void aboutSlot();

    /**
     * Show the window that selects which gauge
     * monitors to be shown request.
     */

    void selectMonitorSlot();

    /**
     * Show the window for serial port configuration
     * request.
     */

    void serialConfigSlot();

    /**
     * Estabilish serial connection request.
     */

    void serialConnectSlot();

    /**
     * Close serial connection request.
     */

    void serialDisconnectSlot();

    /**
     * Gauge monitors realignment request.
     */

    void alignMonitorSlot();

    /**
     * Connect to Flex request.
     */

    void deviceConnectSlot();

    /**
     * Inquiry request.
     */

    void deviceInquirySlot();

public slots:

    /**
     * Redraws the gauge monitors in the
     * window.
     */

    void updateMonitorsSlot();

    /**
     * It is signaled that Flex is online.
     */

    void flexOnlineSlot();

    /**
     * It is signaled that vehicle is online.
     */

    void vehicleOnlineSlot();

    /**
     * It is signaled that Bluetooth inquiry resulst are ready.
     * @param data Inquiry results.
     * @param num Number of devices found during the inquiry.
     */

    void bluetoothInquiryCompleted(inquiry_result_t * data, unsigned int num);

    /**
     * It is signaled the inquiry device chosen for
     * connection.
     * @param num The device identifier.
     */

    void bluetoothDeviceChosen(int num);

    /**
     * New data coming from vehicle is ready to be shown.
     * @param monitor The monitor to which the data must be sent.
     * @param data The data to be shown.
     */

    void vehicleDataReady(unsigned char monitor, float data);

public:

    /**
     * The MainWindow constructor. This creates all the main
     * window contents.
     * @param The parent widget. Generally main window has no parent.
     */

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**
     * A gauge monitor has been closed.
     */

    void monitorDead(int monitor);
};

#endif // MAINWINDOW_H
