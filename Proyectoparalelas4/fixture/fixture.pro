#-------------------------------------------------
#
# Project created by QtCreator 2017-12-18T17:22:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fixture
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    verror.cpp \
    vok.cpp

HEADERS  += mainwindow.h \
    verror.h \
    vok.h

FORMS    += mainwindow.ui \
    verror.ui \
    vok.ui

RESOURCES +=

DISTFILES += \
    ../../ok.png
