#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("FlexBoardMeetsOBD");
    createMenus();
    createToolBars();
    serialConfig = new SerialConfiguration(this, Qt::Window);
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
    serialConfigAct->setText(tr("&Serial Config"));
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
    deleteMonitorAct = new QAction(this);
    deleteMonitorAct->setText(tr("&Delete Monitor"));
    connect(deleteMonitorAct, SIGNAL(triggered()), this, SLOT(deleteMonitorSlot()));
    editMonitorAct = new QAction(this);
    editMonitorAct->setText(tr("&Edit Monitor"));
    connect(editMonitorAct, SIGNAL(triggered()), this, SLOT(editMonitorSlot()));

    monitorToolBar = new QToolBar(tr("File"));
    addToolBar(Qt::RightToolBarArea, monitorToolBar);
    monitorToolBar->addAction(newMonitorAct);
    monitorToolBar->addAction(editMonitorAct);
    monitorToolBar->addAction(deleteMonitorAct);
    monitorToolBar->setOrientation(Qt::Vertical);
    monitorToolBar->setAllowedAreas(Qt::RightToolBarArea);
}

void MainWindow::exitSlot()
{
    this->close();
}

void MainWindow::newMonitorSlot() {
    QDockWidget *dockWidget = new QDockWidget(tr("Monitor"), this);
    addDockWidget(Qt::TopDockWidgetArea, dockWidget);
}

void MainWindow::aboutSlot()
{
#define aboutAuthorsNum 2
    QHBoxLayout * aboutLayout;
    QVBoxLayout * aboutAuthorsLayout;
    QVBoxLayout * aboutToolsLayout;
    QLabel * aboutAuthorsTitle;
    QLabel * aboutAuthors[aboutAuthorsNum];
    QLabel * aboutQt;
    QLabel * aboutDigia;
    QWidget * aboutWidget = new QWidget(this, Qt::Window);

    aboutWidget->setWindowTitle(tr("About"));
    aboutWidget->setMinimumWidth(450);
    aboutWidget->setMaximumWidth(450);
    aboutWidget->setMinimumHeight(250);
    aboutWidget->setMaximumHeight(250);

    aboutQt = new QLabel(aboutWidget);
    //aboutQt->setMinimumSize(200,200);
    aboutQt->setPixmap(QPixmap(":/images/qt/qt_logo.png").scaledToHeight(150));

    aboutDigia = new QLabel(aboutWidget);
    //aboutDigia->setMinimumSize(200,200);
    aboutDigia->setPixmap(QPixmap(":/images/qt/digia_logo.png").scaledToHeight(65));

    aboutAuthorsTitle = new QLabel(tr("Authors"), aboutWidget);
    aboutAuthorsTitle->setFont(QFont("Fantasy", 20, QFont::Bold));
    aboutAuthors[0] = new QLabel(tr("Alessio Balsini"), aboutWidget);
    aboutAuthors[1] = new QLabel(tr("David Librera"), aboutWidget);
    for (unsigned int i=0; i<aboutAuthorsNum; i++)
        aboutAuthors[i]->setFont(QFont("Monospace", 14));

    aboutLayout = new QHBoxLayout();
    aboutAuthorsLayout = new QVBoxLayout();
    aboutToolsLayout = new QVBoxLayout();

    aboutAuthorsLayout->addSpacing(50);
    aboutAuthorsLayout->addWidget(aboutAuthorsTitle);
    aboutAuthorsLayout->addSpacing(15);
    aboutAuthorsLayout->addWidget(aboutAuthors[0]);
    aboutAuthorsLayout->addWidget(aboutAuthors[1]);
    aboutAuthorsLayout->addSpacing(50);
    aboutToolsLayout->addWidget(aboutQt);
    aboutToolsLayout->addWidget(aboutDigia);
    aboutLayout->addLayout(aboutAuthorsLayout);
    aboutLayout->addSpacing(70);
    aboutLayout->addLayout(aboutToolsLayout);
    aboutWidget->setLayout(aboutLayout);

    aboutWidget->move(QApplication::desktop()->screen()->rect().center() - aboutWidget->rect().center());
    aboutWidget->show();
}

void MainWindow::serialConfigSlot()
{
    serialConfig->show();
}
