TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/inc/

LIBS += -lpcap


SOURCES += \
        main.cpp \
    nps.cpp \
    device.cpp

HEADERS += \
    inc/nps.h

DISTFILES += \
    readme.md \
    区别对比.png
