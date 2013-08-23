#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("FlexBoardMeetsOBD");
    createMenus();
    createToolBars();
    serialConfig = new SerialConfiguration(this, Qt::Window);
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

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAct);
    settingsMenu = menuBar()->addMenu(tr("&Configure"));
    settingsMenu->addAction(serialConfigAct);
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

    monitorToolBar = new QToolBar(tr("File"));
    addToolBar(Qt::RightToolBarArea, monitorToolBar);
    monitorToolBar->addAction(newMonitorAct);
    monitorToolBar->addAction(editMonitorAct);
    monitorToolBar->setOrientation(Qt::Vertical);
    monitorToolBar->setAllowedAreas(Qt::RightToolBarArea);
}

void MainWindow::exitSlot()
{
    this->close();
}

void MainWindow::newMonitorSlot() {
    Monitor * monitorWidget = new Monitor(tr("Monitor"), this);
    addDockWidget(Qt::TopDockWidgetArea, monitorWidget);
}

void MainWindow::aboutSlot()
{
    about->show();
}

void MainWindow::serialConfigSlot()
{
    serialConfig->show();
}
