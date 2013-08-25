#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow main_window;

    Q_INIT_RESOURCE(images);

    main_window.show();
    
    return application.exec();
}
