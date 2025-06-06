# UDP协议

UDP（User Datagram Protocol，用户数据报协议）是OSI模型中传输层的一个协议，旨在为应用程序提供一种无需建立连接，快速传输数据的通信方式。一下是对UDP协议的详细解释：

------

注：目前所了解的协议，包括ARP，IP，UDP，ICMP都是面向无连接的协议，他们都只负责数据能送达目的地，但不确保接收方能够接收到数据

# 1. UDP协议的特点

## （1）无连接

* UDP是无连接的协议，发送数据时无需与接收方建立连接
* 每次发送的数据包（称为数据报）独立处理，彼此之间没有关系。

## （2）面向报文

* UDP以报文为传输单位，应用层传递给UDP的数据会保留其边界。
* 每个UDP报文独立存在，报文大小限制为64K以内（实际有效负载为65507字节）

## （3）不可靠传输

* UDP不能保证数据送达，不提供确认，重传，流量控制等机制
* 数据可能丢失，重复或乱序，可靠性需要由应用层处理

## （4）速度块

* UDP头部比较短（8字节），开销小，传输速率高。
* 适用于对速度要求较高，数据丢失影响较小的应用场景。

# 2. UDP报文结构

UDP报文由两个部分组成：头部和数据部分

![](image\UDP协议.svg)

Source Port 可填可不填，Target Port 必须要填。如果对方端口没开，那么数据报会被丢弃

## （1）UDP头部

头部固定为8字节，包含一下字段：

* **源端口号（2字节）：** 发送方的端口号，可选
* **目的端口号（2字节）：** 接收方的端口号，必填
* **长度（2字节）：** UDP报文的总长度（包括头部和数据）。
* **校验和（2字节）：** 用于验证数据完整性，可选**（很多都不检验）**。

## （2）数据部分

* 包含应用程序需要发送的实际数据
* 最大长度受**MTU**（最大传输单元）的限制，通常为几百字节到1Kb

# UDP工作流程

## （1） 发送数据

1. 应用程序通过套接字向UDP层发送数据
2. UDP将数据分为一个或多个报文，并附加头部信息
3. 报文通过IP层发送到网络

## （2）接收数据

1. 网络接收到数据报之后，通过IP层传递给UDP层
2. UDP检查目的端口号，交付给对应的应用程序
3. 如果检验和错误，数据报将被丢弃

-----

# 4. UDP的优缺点

## 优点：

* 简单高效：协议简单，头部开销小，适合实时性较高的场景
* 无需建立连接：不需要建立连接，适合广播和多播
* 灵活性强：可以应用于需要自行管理可靠性和顺序的场景

## 缺点

* 不可靠
* 无拥塞控制

# 5. 典型的应用场景

## （1）实时应用

* 视频会议，网络语音（VoIP）等，对实时性要求较高，但容忍少量数据丢失

## （2）广播与多播

* 在线游戏，网络发现协议（如DHCP），需要同时向多个接收者发送数据

## （3） 快速传输

* DNS查询：快速获取域名解析结果
* 物联网：传输短小并且频繁的数据





