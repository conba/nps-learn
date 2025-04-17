TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += $$PWD/inc/ \
               $$PWD/prtc \

LIBS += -lpcap


SOURCES += \
        main.cpp \
    nps.cpp \
    device.cpp \
    prtc/ethii.cpp

HEADERS += \
    inc/nps.h \
    inc/hdr.h \
    inc/prtc.h

DISTFILES += \
    readme.md \
    区别对比.png \
    Ethernet_II.png
