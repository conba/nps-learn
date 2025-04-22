#include "nps.h"
#include "hdr.h"
#include "prtc.h"

#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

struct in_addr HOST_IP;

void devices_info(pcap_if_t *alldevs)
{
    pcap_if_t* device = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];

    if(pcap_findalldevs(&alldevs, errbuf) != 0)
    {
        fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
        return;
    }

    printf("Netword device find: \n");

    // 遍历设备列表
    for (device = alldevs; device != NULL; device = device->next)
    {
        printf("\nDevice Name: %s\n", device->name);
        if(device->flags & PCAP_IF_LOOPBACK)
        {
            printf("Loopback enabled\n");
        }

        if(device->description)
            printf("Description: %s\n", device->description);
        else
            printf("No description available.\n");

        pcap_addr_t* addr = NULL;

        // bianli
        for (addr = device->addresses; addr != NULL; addr = addr->next)
        {
            if(addr->addr && addr->addr->sa_family == AF_INET)
            {
                struct sockaddr_in* ip_addr = (struct sockaddr_in*)addr->addr;
                struct sockaddr_in* netmask = (struct sockaddr_in*)addr->netmask;

                printf("IP Address: %s\n", inet_ntoa(ip_addr->sin_addr));
                if(netmask)
                    printf("Subnet Mask: %s\n", inet_ntoa(netmask->sin_addr));
            }
        }
    }

    pcap_freealldevs(alldevs);
}

pcap_if_t *device_find(pcap_if_t* alldevs, const char* name)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    char nbuf[64];

//    sprintf(nbuf, "\\Device\\NPF_%s", name);
    sprintf(nbuf, "%s", name);

    if(pcap_findalldevs(&alldevs, errbuf) != 0)
    {
        fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
        return NULL;
    }

    for(pcap_if_t* device = alldevs; device != NULL; device = device->next)
    {
        if(!strcmp(device->name, nbuf))
        {
            pcap_addr_t* addr = NULL;
            for(addr = device->addresses; addr != NULL; addr = addr->next)
            {
                if(addr->addr && addr->addr->sa_family == AF_INET)
                {
                    struct sockaddr_in* ip_addr = (struct sockaddr_in*)(addr->addr);
//                    char* ip_str = inet_ntoa(ip_addr->sin_addr);
                    printf("--------%d\n", ip_addr->sin_addr);
                    char dip_str[17] = {0};
                    inet_ntop(AF_INET, (in_addr_t*)&(ip_addr->sin_addr), dip_str, 16);
                    printf("host ip is %s\n", dip_str);
                    inet_pton(AF_INET, dip_str, &HOST_IP);
                    printf("--------%d\n", HOST_IP);
                }
            }
            return device;
        }
    }

    return NULL;
}


void device_handler(unsigned char *user,
                    const struct pcap_pkthdr *header,
                    const unsigned char *pkt_data)
{
    printf("\n Packet captured:\n");
    printf("Timestamp: %1d.%1d seconds\n", header->ts.tv_sec, header->ts.tv_usec);
    printf("Packet length: %d bytes\n", header->len);

    EthII_Hdr* eth_ii = eth_ii_parse(pkt_data);

    eth_ii_print(eth_ii);

    pkt_data += sizeof(EthII_Hdr);

    Arp_Hdr* arp = nullptr;

    switch (eth_ii->type)
    {
    case ETH_II_TYPE_ARP:
        arp = arp_parse(pkt_data);
        arp_print(arp);
        break;
    default:
//        printf("Unknown packet type: %d\n", eth_ii->type);
        break;
    }


    if(eth_ii)
        free(eth_ii);
}

