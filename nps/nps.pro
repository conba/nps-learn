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
    prtc/ethii.cpp \
    prtc/arp.cpp \
    prtc/icmp.cpp \
    prtc/ip.cpp \
    prtc/udp.cpp

HEADERS += \
    inc/nps.h \
    inc/hdr.h \
    inc/prtc.h \
    inc/stack.h

DISTFILES += \
    ../手写网络协议栈/ARP协议.md \
    ../手写网络协议栈/ICMP协议详解.md \
    ../手写网络协议栈/IPv4协议.md \
    ../手写网络协议栈/OSI七层模型.md \
    ../手写网络协议栈/以太网协议.md \
    ../手写网络协议栈/局域网.md \
    readme.md \
    区别对比.png \
    Ethernet_II.png
