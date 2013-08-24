#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("FlexBoardMeetsOBD");
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    createMenus();
    createToolBars();

    mainWidget = new QMdiArea(this);
    this->setCentralWidget(mainWidget);

    serialConfig = new SerialConfiguration(&serial, this, Qt::Window);
    about = new About(this, Qt::Window);

    vehicle = new Vehicle(&serial);
    monitorSelection = new MonitorSelection(vehicle, this, Qt::Window);

    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
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


    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAct);

    settingsMenu = menuBar()->addMenu(tr("&Configure"));
    settingsMenu->addAction(serialConfigAct);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(alignMonitorAct);

    questionsMenu = menuBar()->addMenu(tr("&?"));
    questionsMenu ->addAction(aboutAct);
}

void MainWindow::createToolBars()
{
    selectMonitorAct = new QAction(this);
    selectMonitorAct->setText(tr("&Select Monitors"));
    connect(selectMonitorAct, SIGNAL(triggered()), this, SLOT(selectMonitorSlot()));

    editMonitorAct = new QAction(this);
    editMonitorAct->setText(tr("&Edit Monitors"));
    connect(editMonitorAct, SIGNAL(triggered()), this, SLOT(editMonitorSlot()));

    serialConnectAct = new QAction(this);
    serialConnectAct->setText(tr("&Serial Connect"));
    connect(serialConnectAct, SIGNAL(triggered()), this, SLOT(serialConnectSlot()));

    monitorToolBar = new QToolBar(tr("File"));
    addToolBar(Qt::LeftToolBarArea, monitorToolBar);
    monitorToolBar->addAction(selectMonitorAct);
    monitorToolBar->addAction(editMonitorAct);
    monitorToolBar->addAction(alignMonitorAct);
    monitorToolBar->addSeparator();
    monitorToolBar->addAction(serialConnectAct);
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
    subWindowList = mainWidget->subWindowList();

    while (!subWindowList.isEmpty())
        subWindowList.takeFirst()->close();

    vehicle->getBitmaskBits(&bitList);
    while (!bitList.isEmpty())
        newMonitor(bitList.takeFirst());
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
    default:
        return;
        break;
    }

    monitorWidget->setValue(0);
    QMdiSubWindow * subWindow = mainWidget->addSubWindow(monitorWidget);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);

    subWindow->show();

    mainWidget->tileSubWindows();
}

void MainWindow::alignMonitorSlot()
{
    mainWidget->tileSubWindows();
}

void MainWindow::aboutSlot()
{
    about->show();
}

void MainWindow::serialConfigSlot()
{
    serialConfig->show();
}

void MainWindow::serialConnectSlot()
{
    serial.connect();
    serial.writeS("Hello World!", 12);
}
