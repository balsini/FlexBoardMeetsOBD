#-------------------------------------------------
#
# Project created by QtCreator 2013-08-21T20:30:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app

LIBS += -lkde3support \
    -lkdeclarative \
-lkdecorations \
-lkdecore \
-lkdefakes \
-lkdesu \
-lkdeui \
-lkdewebkit

SOURCES += \
    main.cpp\
    mainwindow.cpp\
    serial.cpp \
    serialconfiguration.cpp \
    monitor.cpp \
    about.cpp \
    monitorselection.cpp \
    vehicle.cpp \
    statusbar.cpp \
    worker.cpp \
    bluetoothdevices.cpp \
    datagram.cpp \
    plot.cpp \
    ksignalplotter.cpp

HEADERS  += \
    mainwindow.h\
    serial.h \
    serialconfiguration.h \
    monitor.h \
    about.h \
    monitorselection.h \
    vehicle.h \
    statusbar.h \
    datagram.h \
    worker.h \
    bluetoothdevices.h \
    plot.h \
    ksignalplotter.h \
    ksignalplotter_p.h

RESOURCES += \
    images.qrc

FORMS += \
    form.ui
