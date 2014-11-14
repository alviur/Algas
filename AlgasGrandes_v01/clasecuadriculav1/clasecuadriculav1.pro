#-------------------------------------------------
#
# Project created by QtCreator 2014-10-25T09:08:56
#
#-------------------------------------------------

QT       -= gui

TARGET = clasecuadriculav1
TEMPLATE = lib

DEFINES += CLASECUADRICULAV1_LIBRARY

SOURCES += clasecuadriculav1.cpp

HEADERS += clasecuadriculav1.h\
        clasecuadriculav1_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
