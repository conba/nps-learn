#include "prtc.h"
#include "arpa/inet.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_ip_str(const uint32_t tpa)
{
    char* ip = (char*)malloc(17);

    inet_ntop(AF_INET, (in_addr_t*)&tpa, ip, 16);

    return ip;
}

Arp_Hdr* arp_parse(const unsigned char *data)
{
    Arp_Hdr* arp_hdr = (Arp_Hdr*)malloc(sizeof(Arp_Hdr));
    if(!arp_hdr) return nullptr;

    memcpy(arp_hdr, data, sizeof(Arp_Hdr));

    arp_hdr->h_type = ntohs(arp_hdr->h_type);
    arp_hdr->p_type = ntohs(arp_hdr->p_type);
    arp_hdr->operate = ntohs(arp_hdr->operate);
//    arp_hdr->spa = ntohl(arp_hdr->spa);
//    arp_hdr->tpa = ntohl(arp_hdr->tpa);

    return arp_hdr;
}

void arp_print(const Arp_Hdr *arp)
{
    if(arp->p_type == ETH_II_TYPE_IPV4)
    {
        char* target_ip = get_ip_str(arp->tpa);
        char* source_ip = get_ip_str(arp->spa);
        printf("\t\t who has %s, tell %s\n", target_ip, source_ip);

        free(target_ip);
        free(source_ip);
    }
}


extern struct in_addr HOST_IP;

int arp_send(pcap_t* handle, char* tpa, uint8_t type)
{
    EthII_Hdr eth_ii_hdr = {.type = htons(ETH_II_TYPE_ARP)};
    host_mac(eth_ii_hdr.source_mac);
    memset(eth_ii_hdr.target_mac, 0xFF, ETH_II_MAC_LEN);
    Arp_Hdr arp_hdr = {
        .h_type = htons(1),
        .p_type = htons(ETH_II_TYPE_IPV4),
        .h_len = 6,
        .p_len = 4,
        .operate = htons(1),
        .spa = HOST_IP.s_addr
    };

    host_mac(arp_hdr.sha);
    int pl = 0;  // 数据包的长度
    if(type == ARP_GRATUITOUS)
    {
        pl = 60;
        memset(arp_hdr.tha, 0xFF, ETH_II_MAC_LEN);
        arp_hdr.tpa = arp_hdr.spa;
    }
    else
    {
        pl = sizeof(EthII_Hdr) + sizeof(Arp_Hdr);
        memset(arp_hdr.tha, 0x00, ETH_II_MAC_LEN);
        arp_hdr.tpa = from_ip_str(tpa);
    }

    uint8_t data[pl];
    memset(data, 0x00, pl);
    memcpy(data, &eth_ii_hdr, sizeof(EthII_Hdr));
    memcpy(data + sizeof(EthII_Hdr), &arp_hdr, sizeof(Arp_Hdr));

    if(pcap_sendpacket(handle, data, pl) != 0)
    {
        fprintf(stderr, "Error sending packet: %s\n", pcap_geterr(handle));
    }
    else
    {
        printf("send successfuly. \n");
    }

    return 0;
}

