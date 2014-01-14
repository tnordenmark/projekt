TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ProjFunc.cpp \
    ProjMain.cpp

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

HEADERS += \
    ProjFunc.h \
    ProjGlob.h \
    ProjStruct.h
