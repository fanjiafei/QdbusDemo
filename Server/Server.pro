#-------------------------------------------------
#
# Project created by QtCreator 2018-01-19T14:43:48
#
#-------------------------------------------------

QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    company.cpp


HEADERS  += mainwindow.h \
    company.h

FORMS    += mainwindow.ui
