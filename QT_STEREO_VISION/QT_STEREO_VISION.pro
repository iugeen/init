#-------------------------------------------------
#
# Project created by QtCreator 2014-04-13T12:19:17
#
#-------------------------------------------------

QT       += core gui
CONFIG += qt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QT_STEREO_VISION
TEMPLATE = app

# OpenCV
QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
PKGCONFIG += opencv

SOURCES += main.cpp\
        mainwindow.cpp \
        stereocamera.cpp \
    streovision.cpp

HEADERS  += mainwindow.h \
        stereocamera.h \
    stereovision.h

FORMS    += mainwindow.ui
