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
    prtc/arp.cpp

HEADERS += \
    inc/nps.h \
    inc/hdr.h \
    inc/prtc.h

DISTFILES += \
    ../手写网络协议栈/ARP协议.md \
    ../手写网络协议栈/IPv4协议.md \
    ../手写网络协议栈/OSI七层模型.md \
    ../手写网络协议栈/image/ARP协议.svg \
    ../手写网络协议栈/image/ARP报文结构.png \
    ../手写网络协议栈/image/ARP用途.jpg \
    ../手写网络协议栈/image/ARP表.jpg \
    ../手写网络协议栈/image/ICMP协议.svg \
    ../手写网络协议栈/image/IPv4协议.svg \
    ../手写网络协议栈/image/OSI74.jpg \
    ../手写网络协议栈/image/OSI745.jpg \
    ../手写网络协议栈/image/OSI七层模型.svg \
    ../手写网络协议栈/image/TCP协议.svg \
    ../手写网络协议栈/image/TCP原理.svg \
    ../手写网络协议栈/image/UDP协议.svg \
    ../手写网络协议栈/image/docs.drawio \
    ../手写网络协议栈/image/ipv4报文.png \
    ../手写网络协议栈/image/以太网帧头.svg \
    ../手写网络协议栈/image/协议栈.svg \
    ../手写网络协议栈/image/局域网工作原理.jpg \
    ../手写网络协议栈/image/广播1.jpg \
    ../手写网络协议栈/image/广播2.jpg \
    ../手写网络协议栈/image/数据包分片.svg \
    ../手写网络协议栈/image/模拟网卡.svg \
    ../手写网络协议栈/以太网协议.md \
    ../手写网络协议栈/局域网.md \
    readme.md \
    区别对比.png \
    Ethernet_II.png
