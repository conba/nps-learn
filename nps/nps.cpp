#include "nps.h"
#include "hdr.h"
#include "prtc.h"
#include <stdlib.h>

#if 1

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

    pcap_loop(handle, 5, device_handler, NULL);

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
