#-------------------------------------------------
#
# Project created by QtCreator 2012-08-12T18:45:52
#
#-------------------------------------------------

QT       += core gui

TARGET = PackFileInspector
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    packfileinspector.cpp

HEADERS  += mainwindow.h \
    packfileinspector.h

LIBS += -L/usr/lib/ \
        -lboost_filesystem \
        -lboost_system

FORMS    +=
