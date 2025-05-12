#include "prtc.h"
#include <stdlib.h>
#include <string.h>

IP_Hdr* ip_parse(const unsigned char* data)
{
    IP_Hdr* ip_hdr = (IP_Hdr*)malloc(sizeof(IP_Hdr));

    if(ip_hdr == nullptr)
        return nullptr;

    memcpy(ip_hdr, data, sizeof(IP_Hdr));

    if(!ip_checksum(ip_hdr))
        return nullptr;

    ip_hdr->len = ntohs(ip_hdr->len);
    ip_hdr->identification = ntohs(ip_hdr->identification);
    ip_hdr->ff.v = ntohs(ip_hdr->ff.v);

//    ip_hdr->src = ntohl(ip_hdr->src);
//    ip_hdr->dst = ntohl(ip_hdr->dst);

    return ip_hdr;
}

bool ip_checksum(IP_Hdr* ip_hdr)
{
    // 计算校验和
    uint16_t recv_checksum = ip_hdr->checksum;

    if (recv_checksum == 0)
        return true;

    ip_hdr->checksum = 0;
    if(checksum(ip_hdr, ip_hdr->ihl * 4) == recv_checksum)
    {
        ip_hdr->checksum = recv_checksum;
        return true;
    }

    free(ip_hdr);
    return false;
}

void ip_print(const IP_Hdr* ip)
{
    printf("\t\t Header: %u bytes, Total: %u bytes\n", ip->ihl * 4, ip->len);
    printf("\t\t CHK: %#4x\n", ip->checksum);
    printf("\t\t TTL: %u\n", ip->ttl);

    if(ip->protocol == IP_TOP_TCP)
    {
        printf("\t\t TOP: TCP\n");
    }
    else
    {
        printf("\t\t TOP: UDP\n");;
    }

    printf("\t\t %s -> %s\n", get_ip_str(ip->src), get_ip_str(ip->dst));
}
