#-------------------------------------------------
#
# Project created by QtCreator 2013-08-21T20:30:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = GUI
TEMPLATE = app


SOURCES += \
    main.cpp\
    mainwindow.cpp\
    serial.cpp \
    serialconfiguration.cpp \
    monitor.cpp \
    about.cpp \
    monitorselection.cpp

HEADERS  += \
    mainwindow.h\
    serial.h \
    serialconfiguration.h \
    monitor.h \
    about.h \
    monitorselection.h

RESOURCES += \
    images.qrc

FORMS += \
    form.ui
