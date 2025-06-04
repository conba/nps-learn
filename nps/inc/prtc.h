#ifndef PRTC_H
#define PRTC_H

#include "hdr.h"

#include <arpa/inet.h>
#include <pcap.h>
#include <iostream>

#define HOSTMAC "F8:E4:3B:1B:9C:E0"

char* get_mac_str(const unsigned char* mac);

static uint32_t from_ip_str(const char* ip)
{
    struct in_addr addr;
    if(inet_pton(AF_INET, ip, &addr) <= 0)
    {
        perror("inet_pton error");
        return 0;
    }

    return addr.s_addr;
}

static int host_mac(uint8_t *mac_val)
{
    const char* mac = HOSTMAC;

    for(int i = 0; i < ETH_II_MAC_LEN; ++i)
    {
        if(sscanf(mac + 3 * i, "%2hhx", &mac_val[i]) != 1)
            return -1;
    }

    return 0;
}

static uint16_t checksum(void *data, int len)
{
    uint32_t sum = 0;
    uint16_t *ptr = (uint16_t*)data;
    // 遍历数据，按16位单元累加
    while (len > 1)
    {
        sum += *ptr++;
        if (sum > 0xFFFF)
        {
            sum = (sum & 0xFFFF) + 1; // 如果有进位，将进位加回
        }
        len -= 2;
    }
    // 如果长度是奇数，处理最后一个字节
    if (len == 1)
    {
        uint8_t last_byte = *(uint8_t *)ptr;
        sum += (last_byte << 8); // 高位补齐
        if (sum > 0xFFFF)
        {
            sum = (sum & 0xFFFF) + 1;
        }
    }
    // 取反，返回校验和
    return ~sum;
}

char* get_ip_str(const uint32_t tpa);

EthII_Hdr* eth_ii_parse(const unsigned char* data);

void eth_ii_print(const EthII_Hdr* eth_ii);

#define ARP_GRATUITOUS  1
#define ARP_REQUESE     2

Arp_Hdr* arp_parse(const unsigned char* data);

void arp_print(const Arp_Hdr* apr);

int arp_send(pcap_t* handle, char* tpa, uint8_t type);


#define IPv4_VERSION    4
#define IPv6_VERSION    6
#define IP_TOP_ICMP     1
#define IP_TOP_TCP      6
#define IP_TOP_UDP      17

IP_Hdr* ip_parse(const unsigned char* data);

void ip_print(const IP_Hdr* ip);

bool ip_checksum(IP_Hdr* ip_hdr);

Icmp_Hdr* icmp_parse(const unsigned char* data, uint16_t len);
bool icmp_checksum(Icmp_Hdr* icmp_hdr, uint16_t len);
void icmp_print(const Icmp_Hdr* icmp);

Udp_Hdr* udp_parse(const unsigned char* data, uint16_t len);
bool udp_checksum(Udp_Hdr* udp_hdr, uint16_t len);
void udp_print(const Udp_Hdr* udp);


Tcp_Hdr* tcp_parse(const unsigned char* data);
bool tcp_checksum(Tcp_Hdr* tcp_hdr);
void tcp_print(Tcp_Hdr* tcp);

#endif // PRTC_H
