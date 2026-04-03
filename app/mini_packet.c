#include "mini_packet.h"

#include <stdio.h>

int mini_packet_encode(char *buffer,
                       size_t buffer_size,
                       const mini_packet_t *packet)
{
    if ((buffer == NULL) || (packet == NULL) || (buffer_size == 0U))
    {
        return -1;
    }

    return snprintf(buffer,
                    buffer_size,
                    "MMHALOW,1,%lu,%ld,%ld",
                    (unsigned long) packet->seq,
                    (long) packet->temperature_milli_degC,
                    (long) packet->humidity_milli_RH);
}

int mini_packet_decode(const char *line, mini_packet_t *packet)
{
    unsigned long seq = 0U;
    long temp = 0;
    long hum = 0;
    int version = 0;

    if ((line == NULL) || (packet == NULL))
    {
        return -1;
    }

    if (sscanf(line, "MMHALOW,%d,%lu,%ld,%ld", &version, &seq, &temp, &hum) != 4)
    {
        return -1;
    }

    if (version != 1)
    {
        return -1;
    }

    packet->seq = (uint32_t) seq;
    packet->temperature_milli_degC = (int32_t) temp;
    packet->humidity_milli_RH = (int32_t) hum;

    return 0;
}
