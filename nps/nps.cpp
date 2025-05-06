#include "nps.h"
#include "hdr.h"
#include "prtc.h"
#include <stdlib.h>

#if 1
#define USE_FILTER

int main()
{
    pcap_if_t *alldevs = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];

    // 获取网卡
    pcap_if_t* device = device_find(alldevs, "ens33");
    if(device == NULL)
    {
        fprintf(stderr, "not device found\n");
        exit(-1);
    }

    pcap_t *handle = pcap_open_live(device->name, 65536, 1, 1000, errbuf);
    if(!handle)
    {
        fprintf(stderr, "Unable to open device: %s\n", errbuf);
        pcap_freealldevs(alldevs);
        exit(-1);
    }

#ifdef USE_FILTER

    // set filter
    struct bpf_program fp;
    char filter_exp[] = "arp or ip";
    bpf_u_int32 net = 0;

    // complie filter
    if(pcap_compile(handle, &fp, filter_exp, 0, net) == -1)
    {
        printf("Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return 1;
    }

    if(pcap_setfilter(handle, &fp) == -1)
    {
        fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
        exit(-1);
    }

#endif

    // start
//    pcap_loop(handle, 10, device_handler, NULL);



    for (int i = 0; i < 10; i++)
    {
        arp_send(handle, "10.110.9.55", ARP_REQUESE);
    }










    pcap_freealldevs(alldevs);

    return 0;
}

#endif

#if 0

int main()
{
    pcap_if_t *alldevs = NULL;
    char errbuf[PCAP_ERRBUF_SIZE];

    devices_info(alldevs);

    return 0;
}

#endif
