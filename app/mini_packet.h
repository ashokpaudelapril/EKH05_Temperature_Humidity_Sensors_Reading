#ifndef MINI_PACKET_H
#define MINI_PACKET_H

#include <stdint.h>
#include <stddef.h>

typedef struct
{
    uint32_t seq;
    int32_t temperature_milli_degC;
    int32_t humidity_milli_RH;
} mini_packet_t;

int mini_packet_encode(char *buffer,
                       size_t buffer_size,
                       const mini_packet_t *packet);

int mini_packet_decode(const char *line, mini_packet_t *packet);

#endif
