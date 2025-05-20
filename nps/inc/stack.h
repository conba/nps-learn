#ifndef STACK_H
#define STACK_H

#include <stdint.h>

#define SP_NULL     0
#define SP_ETH      1
#define SP_ARP      2
#define SP_IPv4     3
#define SP_IPv6     4
#define SP_ICMP     5
#define SP_TCP      6
#define SP_UDP      7

typedef struct stack_node_t
{
    uint8_t protocol;
    uint16_t up_protocol;
    void* data;
}StackNode;

#endif // STACK_H
