#include "prtc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

char* get_mac_str(const unsigned char* mac)
{
    char* mac_str = (char*)malloc(ETH_II_MAC_LEN + 1);
    memset(mac_str, 0x00, ETH_II_MAC_LEN + 1);
    memcpy(mac_str, mac, ETH_II_MAC_LEN);

    if(mac_str == NULL)
        return NULL;

    // 会自动扩展内存
    sprintf(mac_str, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    return mac_str;
}

EthII_Hdr* eth_ii_parse(const unsigned char* data)
{
    EthII_Hdr* eth_ii = (EthII_Hdr*)malloc(sizeof(EthII_Hdr));
    if(eth_ii == NULL)
        return eth_ii;

     memcpy(eth_ii, data, sizeof(EthII_Hdr));
     eth_ii->type = ntohs(eth_ii->type);

     return eth_ii;
}

void eth_ii_print(const EthII_Hdr* eth_ii)
{
    if(eth_ii == NULL) return;
    if(eth_ii->type == 0x0800)
        printf("IPV4");
    else if (eth_ii->type == 0x86DD)
        printf("IPV6");
    else if(eth_ii->type == 0x0806)
        printf("ARP");
    else {
        printf("Unknown");
    }

    char* source_mac = get_mac_str(eth_ii->source_mac);
    char* target_mac = get_mac_str(eth_ii->target_mac);

    printf(":\t %s -> %s\n", source_mac, target_mac);

    if(source_mac)
        free(source_mac);

    if(target_mac)
        free(target_mac);
}
