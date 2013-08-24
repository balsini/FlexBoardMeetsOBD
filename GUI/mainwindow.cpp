#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("FlexBoardMeetsOBD");
    createMenus();
    createToolBars();

    mainWidget = new QMdiArea(this);
    this->setCentralWidget(mainWidget);

    serialConfig = new SerialConfiguration(&serial, this, Qt::Window);
    about = new About(this, Qt::Window);
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
    newMonitorAct = new QAction(this);
    newMonitorAct->setText(tr("&New Monitor"));
    connect(newMonitorAct, SIGNAL(triggered()), this, SLOT(newMonitorSlot()));

    editMonitorAct = new QAction(this);
    editMonitorAct->setText(tr("&Edit Monitors"));
    connect(editMonitorAct, SIGNAL(triggered()), this, SLOT(editMonitorSlot()));

    serialConnectAct = new QAction(this);
    serialConnectAct->setText(tr("&Serial Connect"));
    connect(serialConnectAct, SIGNAL(triggered()), this, SLOT(serialConnectSlot()));

    monitorToolBar = new QToolBar(tr("File"));
    addToolBar(Qt::LeftToolBarArea, monitorToolBar);
    monitorToolBar->addAction(newMonitorAct);
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

void MainWindow::newMonitorSlot()
{
    static unsigned int i = 0;
    QString name;

    name = tr("Monitor ");
    name.append(QString::number(i));
    Monitor * monitorWidget = new Monitor(name, FUEL, this, Qt::SubWindow);
    monitorWidget->setValue(50);
    QMdiSubWindow * subWindow = mainWidget->addSubWindow(monitorWidget);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);

    subWindow->show();

    mainWidget->tileSubWindows();
    i++;
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
