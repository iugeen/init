#-------------------------------------------------
#
# Project created by QtCreator 2014-04-06T11:39:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testQt5
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH +=`pkg-config opencv --cflags`

LIBS +=`pkg-config opencv --libs`
