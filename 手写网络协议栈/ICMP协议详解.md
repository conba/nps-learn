# ICMP协议详解

ICMP（Internet Control Message Protocol，互联网控制消息协议）是一种网络层协议（基于IP协议），主要用于传递控制信息，检车和报告网络中的通信问题，ICMP是IPv4和IPv6协议的重要组成部分，常见于网络故障诊断和错误报告。

## ICMP协议的特点

1. **工作在网络层**：ICMP是IP协议的一部分，直接在IP协议之上运行，协议号为1（IPv4）.
2. **非面向连接**：ICMP本身不提供面向连接的服务，仅用于传递控制信息
3. **错误报告和诊断**：ICMP用于报告网络问题，例如目的地不可达，超时等。
4. **不纠正问题**：ICMP仅通知发送方问题的存在，不负责解决问题

## ![](image\ICMP主要功能.png)

## ICMP数据包格式

![](image\ICMP协议.svg)

**抓包结果**

![](E:\working\github\nps-learn\手写网络协议栈\image\ICMP内容.png)

## ICMP数据包嵌套在IP数据包中，其格式如下

| 字段         | 长度（位，bit） | 描述                                                         |
| ------------ | --------------- | ------------------------------------------------------------ |
| Type         | 8               | 消息类型，用于表示ICMP功能                                   |
| Code         | 8               | 子类型，进一步说明消息类型                                   |
| Checksum     | 16              | 校验和，用于检查ICMP消息的完整性（ICMP的Checksum包含数据部分） |
| Message Body | 可变            | 包含具体的ICMP消息内容，例如IP头部或时间戳信息等             |

## 常见的ICMP消息类型

| Type | Code | 消息名称                 | 描述                                             |
| ---- | ---- | ------------------------ | ------------------------------------------------ |
| 0    | 0    | Echo Reply               | Ping的应答消息                                   |
| 3    | 0-15 | Destination Unreasonable | 目的地不可达，包括网络不可达，端口不可达等子类型 |
| 4    | 0    | Source Quench（已废弃）  | 请求发送方减缓发送速率（现代网络中已废弃）       |
| 5    | 0-3  | Redirect                 | 通知主机使用更优的路由                           |
| 8    | 0    | Echo Request             | Ping的消息请求                                   |
| 11   | 0-1  | Time Exceeded            | 数据包在传输过程中超时，TTL为0时触发             |
| 12   | 0-1  | Parameter Problem        | 数据包的头部字段有错误                           |
| 13   | 0    | Timestamp Request        | 请求时间戳信息，用于时间同步                     |
| 14   | 0    | Timestamp Reply          | 恢复时间戳信息                                   |

![](image\ICMP拓展.png)