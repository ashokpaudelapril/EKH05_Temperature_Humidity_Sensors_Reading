#include "temp_app.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "demo_temperature.h"
#include "mini_packet.h"

#ifndef TEMP_APP_USE_HALOW_UDP
#define TEMP_APP_USE_HALOW_UDP 0
#endif

#if TEMP_APP_USE_HALOW_UDP
#include "mm_app_common.h"
#include "lwip/fcntl.h"
#include "lwip/inet.h"
#include "lwip/sockets.h"

#ifndef TEMP_APP_HALOW_REMOTE_IP
#define TEMP_APP_HALOW_REMOTE_IP "192.168.4.2"
#endif

#ifndef TEMP_APP_HALOW_REMOTE_PORT
#define TEMP_APP_HALOW_REMOTE_PORT 5000
#endif
#endif

extern UART_HandleTypeDef hlpuart1;

__weak int temp_app_halow_send_line(const char *line, size_t len)
{
#if TEMP_APP_USE_HALOW_UDP
    static bool net_ready = false;
    static int tx_sock = -1;
    static struct sockaddr_in remote_addr;
    int sent = 0;

    if ((line == NULL) || (len == 0U))
    {
        return -1;
    }

    if (!net_ready)
    {
        app_wlan_init();
        app_wlan_start();

        tx_sock = lwip_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (tx_sock < 0)
        {
            return -2;
        }

        memset(&remote_addr, 0, sizeof(remote_addr));
        remote_addr.sin_family = AF_INET;
        remote_addr.sin_port = PP_HTONS(TEMP_APP_HALOW_REMOTE_PORT);
        remote_addr.sin_addr.s_addr = ipaddr_addr(TEMP_APP_HALOW_REMOTE_IP);

        if (remote_addr.sin_addr.s_addr == IPADDR_NONE)
        {
            return -3;
        }

        net_ready = true;
    }

    sent = lwip_sendto(
        tx_sock,
        line,
        len,
        0,
        (const struct sockaddr *)&remote_addr,
        (socklen_t)sizeof(remote_addr));

    if (sent < 0)
    {
        return -4;
    }

    return 0;
#else
    HAL_StatusTypeDef rc;

    if ((line == NULL) || (len == 0U))
    {
        return -1;
    }

    rc = HAL_UART_Transmit(&hlpuart1, (uint8_t *) line, (uint16_t) len, 100U);
    if (rc != HAL_OK)
    {
        return -2;
    }

    rc = HAL_UART_Transmit(&hlpuart1, (uint8_t *)"\r\n", 2U, 100U);
    if (rc != HAL_OK)
    {
        return -3;
    }

    return 0;
#endif
}

void temp_app_run_forever(void)
{
    uint32_t sequence = 0;
    mini_packet_t pkt;
    char frame[96];
    int frame_len = 0;

    temperature_init();

    printf("SENSOR NODE: boot complete\r\n");
    printf("SENSOR NODE: reading SHT4x and preparing TX payload every 10s\r\n");
    if (TEMP_APP_USE_HALOW_UDP)
    {
        printf("SENSOR NODE: transport=HaLow UDP dst=%s:%u\r\n",
               TEMP_APP_HALOW_REMOTE_IP,
               (unsigned)TEMP_APP_HALOW_REMOTE_PORT);
    }
    else
    {
        printf("SENSOR NODE: transport=UART fallback on LPUART1\r\n");
    }

    while (1)
    {
        th_value_t th;

        temperature_process();
        th = get_th_values();

        pkt.seq = sequence;
        pkt.temperature_milli_degC = th.temperature_milli_degC;
        pkt.humidity_milli_RH = th.humidity_milli_RH;

        frame_len = mini_packet_encode(frame, sizeof(frame), &pkt);

        if (frame_len > 0)
        {
            int tx_rc = temp_app_halow_send_line(frame, (size_t) frame_len);

            printf("SENSOR_TX payload=%s\r\n", frame);
            if (tx_rc == 0)
            {
                printf("SENSOR_TX status=sent\r\n");
            }
            else
            {
                printf("SENSOR_TX status=failed rc=%d\r\n", tx_rc);
            }
        }
        else
        {
            printf("SENSOR_TX encode_error seq=%lu\r\n", (unsigned long) sequence);
        }

        printf("SENSOR_TX_METRIC seq=%lu temp_c=%.3f hum_rh=%.3f\r\n",
               (unsigned long) sequence,
               th.temperature_milli_degC / 1000.0f,
               th.humidity_milli_RH / 1000.0f);

         sequence++;

         /* 10s interval keeps logs readable and aligns with planned wireless publish rate. */
         HAL_Delay(10000);
    }
}
