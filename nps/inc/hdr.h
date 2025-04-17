#ifndef HDR_H
#define HDR_H

#include <stdint.h>

#define ETH_II_MAC_LEN 6

typedef struct
{
    uint8_t target_mac[ETH_II_MAC_LEN];
    uint8_t source_mac[ETH_II_MAC_LEN];
    uint16_t type;
} EthII_Hdr;

#endif // HDR_H
