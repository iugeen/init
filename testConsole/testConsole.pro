#-------------------------------------------------
#
# Project created by QtCreator 2014-04-06T11:45:43
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = testConsole
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += link_pkgconfig
PKGCONFIG += opencv

TEMPLATE = app


SOURCES += main.cpp

INCLUDEPATH += /usr/include/opencv
INCLUDEPATH += /usr/include/opencv2
#LIBS += -L/usr/lib -lopencv_core -lopencv_highgui

#INCLUDEPATH +=`pkg-config opencv --cflags`

LIBS +=`pkg-config opencv --libs`
