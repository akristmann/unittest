#-------------------------------------------------
#
# Project created by QtCreator 2015-06-19T15:06:01
#
#-------------------------------------------------

QT       += testlib
QT       += network
QT       -= gui

TARGET = tst_unittesttest
CONFIG   += console
CONFIG   -= app_bundle

SOURCES +=  ../clockwidget/udpserver.cpp \
            ../clockwidget/udpclient.cpp

HEADERS  +=  ../clockwidget/udpserver.h \
             ../clockwidget/udpclient.h


TEMPLATE = app


SOURCES += tst_unittesttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
