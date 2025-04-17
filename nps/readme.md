1. 用于获取系统中所有可用的网络设备，它可以列出当前计算机安装的网络接口信息，供用户选择一个网络设备进行数据包捕获
2. pcap_freealldevs 函数用于释放资源

3.
pcap_if_t 是一个结构体，表示一个网络设备
alldevs: 返回的链表，链表中的每一个元素表示一个网络设备，NULL结束
errbuf 错误信息缓冲，大小为 PXCAP_ERRBUF_SIZE
4. 成功：0， 失败 -1

```c++
int pcap_findalldevs(pcap_if_t** alldevs, char* errbuf);

struct pcap_if {
        struct pcap_if *next;
        char *name;		/* name to hand to "pcap_open_live()" */
        char *description;	/* textual description of interface, or NULL */
        struct pcap_addr *addresses; /*ip地址和掩码信息等*/
        bpf_u_int32 flags;	/* PCAP_IF_ interface flags，表示设备是否支持混杂模式*/
};
```
***************************************************************************************************

实时捕获：用于打开一个网络接口，从网络上实时捕获数据包
通常用于实时监听网卡上的网络流量
pcap_close用于释放资源
pcap_t *pcap_open_live(const char* device, int snaplen, int promisc, int to_ms, char* errbuf);

device: 要捕获的网卡接口名称
snaplen: 捕获数据包的最大长度（建议65536捕获整个数据包）
promisc: 是否启用混杂模式（1 启用，0 禁用）
    启用混杂模式时，网卡会接受所有通过网卡的数据包，不仅仅是目的地址为本机的。

to_ms: 读取超时时间（单位为毫秒）
    指定多长时间后返回的数据包，即使没有捕获到数据
errbuf: 存储错误消息的缓冲区

成功时，返回一个pcap_t * 类型的句柄，用于后续的捕获操作

```c++
char errbuf[PCAP_ERRBUF_SIZE];
pcap_t *handle = pcap_open_live("eth0", 65535, 1, 1000, errbuf);
if(!handle){
    std::cout <<  "error opening device: << errbuf << std::endl;
    return 1;
}
```

***************************************************************************************************
打开一个已经保存的捕获文件（如.pcap 或 .pcapng文件），并从文件中读取数据包
通常用于对先前捕获的数据包进行分析

pcap_t *pcap_open_offline(const char* filename, char* errbuf);

filename: 要打开的文件路径
errbuf: 存储错误消息的缓冲区

[区别对比.png]

***************************************************************************************************
pcap_loop
用于连续捕获网络数据包，
int pcap_loop(pcap_t *p, int cnt, pcap_handler callback, uy_char * user);

pcap_t *p
类型： 指向打开的捕获回话的句柄
描述：通过pcap_open_live 或 pcap_open_offline 返回的指针，表示一个打开的捕获接口
```c++
pcap_t *handle = pcap_open_live(device_name, 65535, 1,1000, errbuf);
pcap_loop(handle, 10, packet_handler, NULL);
```
int cnt 正整数，指定捕获的最大数据包数，0或者负数： 无限制捕获，直到手动停止，例如ctrl+c 或者调用pcap_break

pcap_handler callback
函数指针，一个回调函数，pcap_loop 在捕获到每个数据包时调用
void callback(u_char* user, const struct pcap_pkthdr* header, const u_char* pkt_data);
u_char* user: 用户自定义数据，通过pcap_loop的第四个参数传递
struct pcap_pkthdr* header 指向捕获数据包头部信息的结构体，包括时间戳，长度等信息
const u_char *pkt_data: 指向实际数据包内容的指针
```c++
void packet_handler(unsigned char* user, const struct pcap_pkthdr* header, const u_char* pkt_data)
{
    printf("Packet captured with length: %d\n", header->len);
}

```
























