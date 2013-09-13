#-------------------------------------------------
#
# Project created by QtCreator 2013-08-26T19:21:37
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SerialFlexSimulator
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    serial.cpp \
    datagram.cpp

HEADERS += \
    serial.h \
    datagram.h
