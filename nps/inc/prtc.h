#ifndef PRTC_H
#define PRTC_H

#include "hdr.h"

#include <arpa/inet.h>
#include <pcap.h>

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

EthII_Hdr* eth_ii_parse(const unsigned char* data);

void eth_ii_print(const EthII_Hdr* eth_ii);

#define ARP_GRATUITOUS  1
#define ARP_REQUESE     2


Arp_Hdr* arp_parse(const unsigned char* data);

void arp_print(const Arp_Hdr* apr);

int arp_send(pcap_t* handle, char* tpa, uint8_t type);


IP_Hdr* ip_parse(const unsigned char* data);

void ip_print(const IP_Hdr* ip);

#endif // PRTC_H
