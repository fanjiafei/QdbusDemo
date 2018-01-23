#-------------------------------------------------
#
# Project created by QtCreator 2018-01-19T14:42:02
#
#-------------------------------------------------

QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    companyInterface.cpp \
    candidate.cpp

HEADERS  += mainwindow.h \
    companyInterface.h \
    candidate.h

FORMS    += mainwindow.ui
