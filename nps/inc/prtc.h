#ifndef PRTC_H
#define PRTC_H

#include "hdr.h"

char* get_mac_str(const unsigned char* mac);

EthII_Hdr* eth_ii_parse(const unsigned char* data);

void eth_ii_print(const EthII_Hdr* eth_ii);

Arp_Hdr* arp_parse(const unsigned char* data);

void arp_print(const Arp_Hdr* apr);

#endif // PRTC_H
