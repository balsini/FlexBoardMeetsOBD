#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QMenu * fileMenu;
    QToolBar * monitorToolBar;
    QMenu * questionsMenu;
    QAction * exitAct;
    QAction * aboutAct;
    QAction * newMonitorAct;
    QAction * editMonitorAct;
    QAction * deleteMonitorAct;

    void createMenus();
    void createToolBars();

private slots:
    void exitSlot();
    void aboutSlot();
    void newMonitorSlot();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
