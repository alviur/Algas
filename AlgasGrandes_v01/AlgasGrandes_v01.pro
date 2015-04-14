#-------------------------------------------------
#
# Project created by QtCreator 2014-10-24T14:35:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AlgasGrandes_v01
TEMPLATE = app


unix{
    CONFIG += link_pkgconfig
    PKGCONFIG +=opencv
}
win32{
    INCLUDEPATH += C:\opencv246bin\install\include \
                   C:\opencv246bin\install\include\opencv \
                   C:\opencv246bin\install\include\opencv2

    LIBS += -LC:\\opencv246bin\\install\\lib \
            -lopencv_core246.dll \
            -lopencv_highgui246.dll \
            -lopencv_imgproc246.dll \
            -lopencv_features2d246.dll \
            -lopencv_calib3d246.dll \
            -lopencv_video246.dll \
            -lopencv_videostab246.dll

}


SOURCES += main.cpp\
        algas.cpp \
    lib/contourssmall.cpp \
    lib/fourier.cpp \
    lib/linearregretion.cpp \
    lib/scontour.cpp \
    lib/simage.cpp \
    lib/alineation.cpp \
    lib/filter.cpp \
    lib/clasecuadriculav1.cpp \
    lib/checkup.cpp

HEADERS  += algas.h \
    lib/contourssmall.h \
    lib/fourier.h \
    lib/linearregretion.h \
    lib/scontour.h \
    lib/simage.h \
    lib/alineation.h \
    lib/filter.h \
    lib/clasecuadriculav1.h \
    lib/checkup.h

FORMS    += algas.ui
