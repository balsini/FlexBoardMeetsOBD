#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("FlexBoardMeetsOBD");
    createMenus();
    createToolBars();

    statusBar = new StatusBar(this);

    this->setStatusBar(statusBar);
    this->setCentralWidget(&mainWidget);

    serialConfig = new SerialConfiguration(&serial, this, Qt::Window);
    about = new About(this, Qt::Window);
    plots = new Plots(this, Qt::Window);
    bluetoothDevices = new BluetoothDevices(this, Qt::Window);

    vehicle = new Vehicle(&serial, this);
    monitorSelection = new MonitorSelection(vehicle, this, Qt::Window);

    statusBar->showMessage(tr("Ready"));
}

MainWindow::~MainWindow() {}

void MainWindow::createMenus()
{
    exitAct = new QAction(this);
    exitAct->setText(tr("E&xit"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(exitSlot()));

    aboutAct = new QAction(this);
    aboutAct->setText(tr("&About"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(aboutSlot()));

    serialConfigAct = new QAction(this);
    serialConfigAct->setText(tr("&Serial Configuration"));
    connect(serialConfigAct, SIGNAL(triggered()), this, SLOT(serialConfigSlot()));

    alignMonitorAct = new QAction(this);
    alignMonitorAct->setText(tr("&Tile Monitors"));
    connect(alignMonitorAct, SIGNAL(triggered()), this, SLOT(alignMonitorSlot()));

    plotsAct = new QAction(this);
    plotsAct->setText(tr("&Show Plots"));
    connect(plotsAct, SIGNAL(triggered()), this, SLOT(plotsSlot()));

    serialConnectAct = new QAction(this);
    serialConnectAct->setText(tr("&Serial Enable"));
    connect(serialConnectAct, SIGNAL(triggered()), this, SLOT(serialConnectSlot()));

    serialDisconnectAct = new QAction(this);
    serialDisconnectAct->setText(tr("Serial &Disable"));
    connect(serialDisconnectAct, SIGNAL(triggered()), this, SLOT(serialDisconnectSlot()));

    deviceConnectAct = new QAction(this);
    deviceConnectAct->setText(tr("&Bridge Connect"));
    connect(deviceConnectAct, SIGNAL(triggered()), this, SLOT(deviceConnectSlot()));

    deviceInquiryAct = new QAction(this);
    deviceInquiryAct->setText(tr("Bridge In&quiry"));
    connect(deviceInquiryAct, SIGNAL(triggered()), this, SLOT(deviceInquirySlot()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAct);

    devicesMenu = menuBar()->addMenu(tr("&Devices"));
    devicesMenu->addAction(serialConnectAct);
    devicesMenu->addAction(serialDisconnectAct);
    devicesMenu->addSeparator();
    devicesMenu->addAction(deviceConnectAct);
    devicesMenu->addAction(deviceInquiryAct);

    settingsMenu = menuBar()->addMenu(tr("&Configure"));
    settingsMenu->addAction(serialConfigAct);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(alignMonitorAct);
    //viewMenu->addAction(plotsAct);

    questionsMenu = menuBar()->addMenu(tr("&?"));
    questionsMenu ->addAction(aboutAct);
}

void MainWindow::createToolBars()
{
    selectMonitorAct = new QAction(this);
    selectMonitorAct->setText(tr("&Select Monitors"));
    connect(selectMonitorAct, SIGNAL(triggered()), this, SLOT(selectMonitorSlot()));

    monitorToolBar = new QToolBar(tr("File"));
    addToolBar(Qt::LeftToolBarArea, monitorToolBar);
    monitorToolBar->addAction(selectMonitorAct);
    monitorToolBar->addAction(alignMonitorAct);
    monitorToolBar->addSeparator();
    monitorToolBar->addAction(serialConnectAct);
    monitorToolBar->addAction(serialDisconnectAct);
    monitorToolBar->addSeparator();
    monitorToolBar->addAction(deviceConnectAct);
    monitorToolBar->addAction(deviceInquiryAct);
    monitorToolBar->setOrientation(Qt::Vertical);
    monitorToolBar->setAllowedAreas(Qt::LeftToolBarArea);
}

void MainWindow::exitSlot()
{
    this->close();
}

void MainWindow::updateMonitorsSlot()
{
    QList<unsigned int> bitList;
    QList<QMdiSubWindow *> subWindowList;
    bitList.clear();
    subWindowList.clear();
    subWindowList = mainWidget.subWindowList();

    while (!subWindowList.isEmpty())
        subWindowList.takeFirst()->close();

    vehicle->getBitmaskBits(&bitList);
    while (!bitList.isEmpty())
        newMonitor(bitList.takeFirst());

    statusBar->showMessage(tr("Monitors generated and aligned"));
}

void MainWindow::selectMonitorSlot()
{
    monitorSelection->show();
}

void MainWindow::newMonitor(unsigned int identifier)
{
    QString name;
    Monitor * monitorWidget;

    switch (identifier) {
    case 0: // RPM
        name = tr("RPM");
        monitorWidget = new Monitor(name, RPM, this, Qt::SubWindow);
        break;
    case 1: // SPEED
        name = tr("Speed");
        monitorWidget = new Monitor(name, SPEED, this, Qt::SubWindow);
        break;
    case 2: // FUEL
        name = tr("Fuel");
        monitorWidget = new Monitor(name, FUEL, this, Qt::SubWindow);
        break;
    case 3: // WATER_TEMPERATURE
        name = tr("Water Temperature");
        monitorWidget = new Monitor(name, WATER_TEMP, this, Qt::SubWindow);
        break;
    default:
        return;
        break;
    }

    subWindowVector.insert(identifier, monitorWidget);

    //monitorWidget->setValue(17000);
    QMdiSubWindow * subWindow = mainWidget.addSubWindow(monitorWidget);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);

    subWindow->show();

    mainWidget.tileSubWindows();
}

void MainWindow::alignMonitorSlot()
{
    mainWidget.tileSubWindows();
}

void MainWindow::aboutSlot()
{
    about->show();
}

void MainWindow::plotsSlot()
{
    plots->show();
}

void MainWindow::serialConfigSlot()
{
    serialConfig->show();
}

void MainWindow::serialConnectSlot()
{
    if (serial.connect() != -1) {
        statusBar->serialConnectionEstabilished();
        vehicle->start();
    }
    else
        statusBar->serialConnectionLost();
}

void MainWindow::serialDisconnectSlot()
{
    serial.disconnect();
    statusBar->serialConnectionLost();
}

void MainWindow::flexOnlineSlot()
{
    statusBar->flexConnectionEstabilished();
}

void MainWindow::vehicleOnlineSlot()
{
    statusBar->vehicleConnectionEstabilished();
}

void MainWindow::bluetoothInquiryCompleted(inquiry_result_t * data, unsigned int num) {
    bluetoothDevices->showBluetoothInquirySlot(data, num);
}

void MainWindow::bluetoothDeviceChosen(int num)
{
    vehicle->bluetoothDeviceChosen(num);
}

void MainWindow::vehicleDataReady(unsigned char monitor, float data)
{
    qDebug() << "Data ready: " << monitor << " : "<< data;
    if (subWindowVector[monitor] != 0)
        subWindowVector[monitor]->setValue(data);
}

void MainWindow::deviceConnectSlot()
{
    vehicle->bridgeConnect();
}
void MainWindow::deviceInquirySlot()
{
    vehicle->bridgeInquiry();
}

void MainWindow::monitorDead(Monitor * monitor)
{
    vehicle->clearBitmaskBit(subWindowVector.indexOf(monitor));
    subWindowVector[subWindowVector.indexOf(monitor)] = 0;
}
